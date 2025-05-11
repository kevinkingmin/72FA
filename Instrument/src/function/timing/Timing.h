#ifndef TIMING_H
#define TIMING_H
#include <QMap>
#include <QMutex>
#include"../Function.h"
#include <QSharedPointer>

class Action;
class SampleTestModel;
class ActionModel;
class ProcessReagentModel;
class ProcessParaModel;

class Timing :public Function
{
	Q_OBJECT
    typedef enum
    {
        eUnknownId=0,
        eBedMotorInitialize=1,
        eDrainageAndAddLiquid=2,
        eRockBedWork=3,
        eBackFlow=4,
        eSampleArmWork=5,
        eHeatRockBed=6,
        eDryPaper=7,
    }ActId;


public:
	Timing();
	virtual ~Timing();
	void resetVariable();

    const QMap<int, QString> &getGroupMap();
    void setGroupMap(QMap<int, QString> &groupMap,const int companyId);
    void setProcessReagentVect(QVector<ProcessReagentModel> processReagentVect);
    void setNeedFillPump(const QMap<int, ushort> &needFillPump);

signals:
    void sglCurrentGroupId(int groupId,int realTime);
    void sglHandleStep(const QString &stepName);
    void sglHandleStepDetail(int stepId,int index,bool isSucess,const QString &stepName);
    void sglPopWindow(QString des);

private:
    bool groupMapIsChanged(const QMap<int,QString> &groupMap);



private:
    QVector<uchar> getFlowBackPumps(int reagentId);
    int actPauseOrRestartOrStop(const ActId pauseType,bool &isPaused);
    int dranAndAdd(QMap<int, QVector<int>> mapPos,int reagentId,int processParaId,int addVolum,int wasteTime);
    int dranLiquid(QMap<int, QVector<int>> mapPos,int wasteTime);
    int addLiquid(QMap<int, QVector<int>> mapPos,int reagentId,int processParaId,int addVolum);

    QString language(const QString id);
private:
    int               _currentGroupId;
    QMap<int,QString> _groupMap;
    int               _companyId;
    ActionModel      *_actModel;
    int               _stepIndex;
    QString           _subStepDesc;

    QMap<int,ushort> _needFillPump;

    int              _processId;

    int              _pauseTime;
};
#endif // TIMING_H
