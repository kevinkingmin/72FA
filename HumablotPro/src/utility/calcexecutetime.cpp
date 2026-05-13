#include "calcexecutetime.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMutexLocker>
#include <QDateTime>
#include "../Include/Model/baseSet/ProcessParameterModel.h"
#include "../Include/DAO/baseSet/ProcessParameterDao.h"

// 单例实例的实现
CalcExecuteTime& CalcExecuteTime::instance()
{
    // Meyer's Singleton: 线程安全(C++11起)，懒加载
    static CalcExecuteTime inst;
    return inst;
}

CalcExecuteTime::CalcExecuteTime()
{
}

CalcExecuteTime::~CalcExecuteTime()
{
}

int CalcExecuteTime::solutionStart(const int processId, int bed1ItemCnt, int bed2ItemCnt)
{
    int code = reloadCalcExecuteTime(processId, bed1ItemCnt, bed2ItemCnt);
    if(code != 0) return code;
    timerReset();
    m_solutionTimer.start();
    m_state = MachineState::Running;
    return 0;
}


/**
 * @brief 开始计时（或从暂停中恢复）
 */
void CalcExecuteTime::solutionResume()
{
    QMutexLocker locker(&m_mutex);
    if (m_state == MachineState::Paused)
    {
        // 1. 获取本次暂停段的耗时
        qint64 elapsedSegment = m_pauseTimer.elapsed();
        // 2. 标记为运行
        m_state = MachineState::Running;
        qDebug() << "Timer Paused. Segment:" << elapsedSegment << "ms";
    }
}

/**
 * @brief 暂停计时
 */
void CalcExecuteTime::solutionPause()
{
    QMutexLocker locker(&m_mutex);
    if (m_state == MachineState::Running)
    {
        // 1. 启动定时器
        m_pauseTimer.start();
        // 2. 标记为暂停
        m_state = MachineState::Paused;
    }
}


/**
 * @brief 停止
 */
void CalcExecuteTime::solutionStop()
{
    QMutexLocker locker(&m_mutex);
    m_state = MachineState::Idle;
}

/**
 * @brief 获取暂停的总耗时（毫秒）
 * 如果正在运行，返回：已累积时间 + 当前段运行时间
 * 如果已暂停，返回：已累积时间
 */
QString CalcExecuteTime::formatTotalPausedMs() const
{
    if (m_state == MachineState::Idle) return "00:00:00";
    return msFormat(getTotalPausedMs());
}

/**
 * @brief 获取方案运行总时间(毫秒)
 */
QString CalcExecuteTime::formatTotalSolutionMs() const
{
    if (m_state == MachineState::Idle) return "00:00:00";
    return msFormat(getTotalSolutionMs());
}


/**
 * @brief 重置所有数据
 */
void CalcExecuteTime::timerReset() {
    QMutexLocker locker(&m_mutex);
    m_state = MachineState::Idle;
    m_solutionTimer.invalidate();
    m_pauseTimer.invalidate();
    qDebug() << "Timer Reset";
}

/**
 * @brief 计算从当前ID开始后的总时间
 * @param stepId step对应的数据库ID
 * @return
 */
qint64 CalcExecuteTime::calcRemainTime(const int stepId) const
{
    QMutexLocker locker(&m_mutex);
    qint64 sum = 0;
    // lowerBound 返回第一个 >= targetKey 的迭代器
    auto it = m_data.lowerBound(stepId);

    // 从该位置遍历到末尾
    while (it != m_data.end()) {
        sum += it.value();
        ++it;
    }
    return sum;
}

/**
 * @brief 获取预计完成时间
 * @return
 */
QString CalcExecuteTime::getEstimatedCompletionTime(const int stepId) const
{
    if(m_state != MachineState::Running) return "00:00:00";
    QDateTime estimated = QDateTime::currentDateTime().addMSecs(calcRemainTime(stepId));
    return estimated.toString("HH:mm:ss");
}

/**
 * @brief 获取当前暂停的总耗时（毫秒）
 * 如果已暂停，返回：已累积时间 + 当前段暂停时间
 * 如果未暂停，返回：已累积时间
 */
qint64 CalcExecuteTime::getTotalPausedMs() const
{
    QMutexLocker locker(&m_mutex);
    if (m_state == MachineState::Paused) {
        return m_pauseTimer.elapsed();
    } else {
        return 0;
    }
}

/**
 * @brief 获取方案运行总时间
 * @return
 */
qint64 CalcExecuteTime::getTotalSolutionMs() const
{
    QMutexLocker locker(&m_mutex);
    if(m_state == MachineState::Idle) return 0;
    return m_solutionTimer.elapsed();
}

/**
 * @brief 将毫秒格式化为"HH:MM:SS"
 * @param totalMs
 * @return
 */
QString CalcExecuteTime::msFormat(qint64 totalMs) const
{
    if (totalMs < 0) totalMs = 0;
    qint64 seconds = totalMs / 1000;
    qint64 hours   = seconds / 3600;
    qint64 minutes = (seconds % 3600) / 60;
    qint64 secs    = seconds % 60;
    return QString("%1:%2:%3")
        .arg(hours, 2, 10, QChar('0'))
        .arg(minutes, 2, 10, QChar('0'))
        .arg(secs, 2, 10, QChar('0'));
}

/**
 * @brief 加载流程步骤, 并按照孵育时间强制时间片排列
 */
int CalcExecuteTime::reloadCalcExecuteTime(const int processId, int bed1ItemCnt, int bed2ItemCnt)
{
    QMutexLocker locker(&m_mutex);
    m_data.clear();

    auto processVect = ProcessParameterDao::instance()->getAllRows(processId);
    if (processVect.isEmpty()) return 1;

    // 存放合并后的结果
    QMap<int, int> mergeTimeWarmSpan;

    // 用于时序合并的向量
    // 注意：这里的 Key 是每个“串行时间段”的代表ID（通常是该段第一个步骤的ID）
    QVector<int> stepIdVect;
    QVector<int> bed1TimeWarmSpan;
    QVector<int> bed2TimeWarmSpan;

    int timeSum = 0;          // 当前累积的非Shaking/Drying/Photo指令的时间总和
    long currentSegmentStartId = 0; // 当前累积段的起始步骤ID
    for (ProcessParameterModel& model : processVect)
    {
        int execTime = model.getEstimatedTime();
        model.parsingParas();
        QString actCode = model.getActCode();
        long modelId = model.getId();

        // 1. 暂停指令：跳过，不消耗时间，不改变状态
        if (actCode == ProcessParameterModel::PAUSING_CODE) {
            continue;
        }

        // 2. 干燥指令：同时执行，直接存入最终Map，不参与流水线时序计算
        if (actCode == ProcessParameterModel::DRYING_CODE) {
            mergeTimeWarmSpan.insert(modelId, execTime);
            continue;
        }

        // 3. 拍照指令：同时执行，直接存入最终Map
        if (actCode == ProcessParameterModel::TAKE_PHOTO_CODE) {
            // 拍照时间是针对所有样本的总时间
            mergeTimeWarmSpan.insert(modelId, execTime * (bed1ItemCnt + bed2ItemCnt));
            continue;
        }

        // 4. 摇床指令 (SHAKING)：这是一个同步点，强制分割流水线
        if (actCode == ProcessParameterModel::BED_SHAKING_CODE) {
            // A. 如果之前有累积的普通指令，先将其作为一个段保存
            if (timeSum > 0 && currentSegmentStartId != 0) {
                stepIdVect.push_back(static_cast<int>(currentSegmentStartId));
                bed1TimeWarmSpan.push_back(timeSum * bed1ItemCnt);
                bed2TimeWarmSpan.push_back(timeSum * bed2ItemCnt);
            }

            // B. 将 Shaking 指令本身作为一个独立的段保存
            // Shaking 通常在两个 Bed 上同时发生，或者视为一个阻塞操作
            // 这里 Shaking 时间在 Bed1 和 Bed2 上是相同的，且必须等待完成
            stepIdVect.push_back(static_cast<int>(modelId));
            bed1TimeWarmSpan.push_back(execTime);
            bed2TimeWarmSpan.push_back(execTime);

            // C. 重置累积状态
            timeSum = 0;
            currentSegmentStartId = 0;
            continue;
        }

        // 5. 普通指令：累积时间
        if (currentSegmentStartId == 0) {
            currentSegmentStartId = modelId; // 记录这个新段的起始ID
        }
        timeSum += execTime;
    }

    // 6. 处理尾部剩余的累积指令（如果最后一个指令不是 SHAKING）
    if (timeSum > 0 && currentSegmentStartId != 0) {
        stepIdVect.push_back(static_cast<int>(currentSegmentStartId));
        bed1TimeWarmSpan.push_back(timeSum * bed1ItemCnt);
        bed2TimeWarmSpan.push_back(timeSum * bed2ItemCnt);
    }

    // --- 时序合并逻辑 ---

    // 如果没有生成任何需要合并的段（例如全是 DRYING/PHOTO 或 PAUSE），则直接返回
    if (stepIdVect.isEmpty()) {
        m_data = mergeTimeWarmSpan; // 或者根据需求决定是否清空
        return 1;
    }

    if (bed1ItemCnt > 0 && bed2ItemCnt > 0) {
        int n = stepIdVect.size();
        if (n == 0) return 1;

        // 遍历所有步骤
        for (int i = 0; i < n; i++) {
            int currentStepId = stepIdVect[i];
            int timeContribution = 0;
            if (i == 0) {
                // 第一步：只有 Bed1 在工作
                timeContribution = bed1TimeWarmSpan[0];
            } else {
                // 后续步骤：
                // 1. 并行部分：Bed1[i] 和 Bed2[i-1] 的最大值
                int parallelTime = std::max(bed1TimeWarmSpan[i], bed2TimeWarmSpan[i - 1]);

                // 2. 如果是最后一步，还需要加上 Bed2[i] 的串行尾部时间
                if (i == n - 1) {
                    timeContribution = parallelTime + bed2TimeWarmSpan[i];
                } else {
                    timeContribution = parallelTime;
                }
            }
            mergeTimeWarmSpan.insert(currentStepId, timeContribution);
        }
    } else {
        // 单床模式：直接相加或取对应床的时间
        QVector<int>& bedTimeWarmSpan = (bed1ItemCnt > 0) ? bed1TimeWarmSpan : bed2TimeWarmSpan;

        for (int i = 0; i < stepIdVect.size(); i++) {
            mergeTimeWarmSpan.insert(stepIdVect[i], bedTimeWarmSpan[i]);
        }
    }
    // 将结果保存到成员变量
    m_data = mergeTimeWarmSpan;
    QMapIterator<int, int> i(m_data);
    while (i.hasNext()) {
        i.next();
        qDebug() << "  StepID:" << i.key() << " -> Duration:" << i.value() << "ms";
    }
    return 0;
}
