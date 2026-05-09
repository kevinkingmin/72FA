#ifndef CALCEXECUTETIME_H
#define CALCEXECUTETIME_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QHash>
#include <QMutex>
#include <QStringList>
#include <QElapsedTimer>

enum class MachineState {
    Idle = 0,      // 未运行
    Running = 1,   // 运行中
    Paused = 2     // 暂停
};

class CalcExecuteTime
{
public:
    /**
     * @brief 获取单例实例
     * @return CalcTimeCache&
     */
    static CalcExecuteTime& instance();

    /**
     * @brief 获取暂停的总耗时（毫秒）
     * 如果正在运行，返回：已累积时间 + 当前段运行时间
     * 如果已暂停，返回：已累积时间
     */
    QString formatTotalPausedMs() const;

    /**
     * @brief 获取方案运行总时间(毫秒)
     */
    QString formatTotalSolutionMs() const;

    /**
     * @brief 根据原始数据计算后缀和缓存
     */
    QString getEstimatedCompletionTime(const int stepId) const;

    /**
     * @brief 流程执行开始
     * @param processId 流程对应的数据库ID
     * @param bed1ItemCnt 摇床1的项目数量
     * @param bed2ItemCnt 摇床2的项目数量
     * @return
     */
    int solutionStart(const int processId, int bed1ItemCnt, int bed2ItemCnt);
    /**
     * @brief 暂停中恢复
     */
    void solutionResume();

    /**
     * @brief 暂停
     */
    void solutionPause();


    /**
     * @brief 停止
     */
    void solutionStop();



private:
    // 构造函数私有化，禁止外部实例化
    CalcExecuteTime();
    ~CalcExecuteTime();

    // 禁止拷贝和赋值
    CalcExecuteTime(const CalcExecuteTime&) = delete;
    CalcExecuteTime& operator=(const CalcExecuteTime&) = delete;

    /**
     * @brief 重置所有数据
     */
    void timerReset();

    /**
     * @brief 加载流程步骤, 并按照孵育时间强制时间片排列
     */
    int reloadCalcExecuteTime(const int processId, int bed1ItemCnt, int bed2ItemCnt);


    /**
     * @brief 获取暂停的总耗时（毫秒）
     * 如果正在运行，返回：已累积时间 + 当前段运行时间
     * 如果已暂停，返回：已累积时间
     */
    qint64 getTotalPausedMs() const;

    /**
     * @brief 获取方案运行总时间(毫秒)
     */
    qint64 getTotalSolutionMs() const;

    /**
     * @brief 将毫秒格式化为"HH:MM:SS"
     * @param totalMs
     * @return
     */
    QString msFormat(qint64 totalMs) const;

    /**
     * @brief 计算流程剩余时间
     * @param stepId 当前执行到了哪个stepId(数据库主键)
     * @return 后缀和；key 不存在返回 -1
     */
    qint64 calcRemainTime(const int stepId) const;


private:
    /**
     * @brief m_data, key表示执行到的步骤在数据库中的id value表示此步骤需要的时间
     */
    QMap<int, int> m_data;// 按插入顺序: (key, value)
    mutable QMutex m_mutex;// 互斥锁
    MachineState m_state = MachineState::Idle;// 流程运行状态
    qint64 m_pausedMs = 0;// 之前所有暂停段的累计耗时
    QElapsedTimer m_pauseTimer;// 用于测量暂停时间
    QElapsedTimer m_solutionTimer;// 用于测量方案运行时间
};

#endif // CALCEXECUTETIME_H
