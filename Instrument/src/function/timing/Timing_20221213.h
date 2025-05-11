#ifndef TIMING_H
#define TIMING_H
#include <QMap>
#include <QMutex>
#include"../Function.h"
#include <QSharedPointer>

class Action;
class Components;
class SampleTestModel;
class ActionModel;
class ProcessReagentModel;
//测试开始后才把要做的项目加入到数据库，否则不加入数据库
//lis过来的数据
class Timing :public Function
{
	Q_OBJECT
public:
    using ptrTest=QSharedPointer<SampleTestModel>;
	Timing();
	virtual ~Timing();
    void addSeqDiagramToMap(QVector<ptrTest> sampleTests, QMap<int, QString>&groupMap);
	void resetVariable();

    const QMap<int, QString> &getGroupMap();
    void setGroupMap(QMap<int, QString> &groupMap);
    void setProcessReagentVect(QVector<ProcessReagentModel> processReagentVect);
    void setNeedFillPump(const QMap<int, ushort> &needFillPump);

signals:
    void sglCurrentGroupId(int groupId,int realTime);
    void sglHandleStep(const QString &stepName);
    void sglHandleStepDetail(int stepId,int index,bool isSucess,const QString &stepName);
protected:
    int start();
private:
    int wettingGroup();
    int addSampleGroup();
    int washingGroup();
    int addReagentGroup();
    int washing_2_Group();
    int addSubStrateGroup();
    int addWaterGroup();
    int addStopLiquidGroup();
    int dryPaperGroup();
private:
    bool groupMapIsChanged(const QMap<int,QString> &groupMap);
    /**
     * @brief bedMotorInitialize:actId=1
     * @return suc>=0,failed<0
     */
    int bedMotorInitialize();

    int backFlow(int group,int index);
    int drainageAndAddLiquid(int group,int index);
    int dryPaper(int group,int index);
    int rockBedWork(int group,int index);
    int sampleArmWork(int group,int index);
private:
    QVector<uchar> getFlowBackPumps(int reagentId);
    int actPauseOrRestartOrStop(bool isWaitPause);
    int dranAndAdd(QMap<int, QVector<int>> mapPos,int reagentId,int processParaId,int addVolum,int wasteTime);
    int dranLiquid(QMap<int, QVector<int>> mapPos,int wasteTime);
    int addLiquid(QMap<int, QVector<int>> mapPos,int reagentId,int processParaId,int addVolum);
private:
    Components *_components;
    int _currentGroupId;
    QMap<int,QString>_groupMap;//存储要执行的时序key=时序号，value=时序名
    ActionModel *_actModel;
    int _stepIndex;
    QString _subStepDesc;
    /**
     * @brief _needFillPump:测试过程中进行充灌。
     */
    QMap<int,ushort> _needFillPump;
};
#endif // TIMING_H
