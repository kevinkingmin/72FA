#ifndef ACTIONMODEL_H
#define ACTIONMODEL_H
#include <QObject>
#include <QMap>
#include <QVector>
#include <QMutex>
#include "../Include/Model/sample/TestParasModel.h"

template<class T>
class Singleton;
class SampleModel;
class SampleTestModel;
class Timing;
class ProcessReagentModel;

class ActionModel
{
public:
    using ptrTest=QSharedPointer<SampleTestModel>;

    ActionModel();
    ActionModel(ActionModel &)=delete;
    ActionModel(ActionModel &&)=delete;
    ActionModel &operator=(const ActionModel&)=delete;
    ActionModel &operator=(ActionModel&&)=delete;
    friend Singleton<ActionModel>;
    friend Timing;
public:
    static ActionModel *instance();
    static uint calAddLiquidMotorStep(double liquidVolumeInReactionTube,uint currentReagentVolumn);
    int getPaperIdFun(int slotPos);
    int getPumpNoFun_(int processParaId,int paperId,int reagentId);
    int getPumpNoFun_new(int reagentId,int paperId,int companyId);

    QString getStepName() const;
    void setStepName(const QString &value);

    const QMap<int, int> &getStepRunTime();

    QMap<int, TestParasModel> getTestParasMap() const;
    void setTestParasMap(const QVector<ptrTest> &tests);

    QVector<ProcessReagentModel> getProcessReagentVect() const;
    void setProcessReagentVect(QVector<ProcessReagentModel> processReagentVect);    

    QVector<uchar> getReagentPumpNOVect() const;
    void setReagentPumpNOVect(const QVector<uchar> &reagentPumpNOVect);

private:
    void updateModel();
    void resetField();
private:    
    QMap<int,TestParasModel>_testParasMap;
    QMap<int,int> _stepRunTime;
    QVector<ProcessReagentModel> _processReagentVect;
    QString _stepName;
    QVector<uchar> _reagentPumpNOVect;
    static QMutex _lock;
};

#endif // ACTIONMODEL_H
