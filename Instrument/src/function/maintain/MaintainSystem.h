#ifndef MAINTAINSYSTEM_H
#define MAINTAINSYSTEM_H
#include"../Function.h"
#include <QMap>
#include <QVector>
#include"src/component/Component.h"
#include "../Include/Model/baseSet/CommonType.h"

class Components;
class MaintainSystem:public Function
{
	Q_OBJECT
public:
    MaintainSystem();
    virtual ~MaintainSystem();

public:
    void maintain(eMaintainType type);

    int init_instrument_environment();
    int inquire_main_controller_version();
    void setReagentPosVolumnMap(const QMap<uchar,ushort> &reagentPosVolumnMap);
    void setPumpVect(const QVector<uchar> &pumpVect);
    void scanSampleBatchNo(QVector<int>posVect);    
protected:
    int start();
private:
    int XYZAxisInit();
    int startUpProcess();
    int systemLiquidIrrigate();
    int systemLiquidWash();
    int prepareReagent();
    int pumpFill();
    int tubeSoak();
    int pumpCalibrate();

    int query_param();
    void arouse_process();
    int closeAllValve();
    int initialze_mechanical_structure(const bool isCloseProcess=false);
    int initialze_liquid_way(bool isOpenProcess);
    int initialze_position();

    int arouse_system();
    int all_motor_release_hold_moment(const bool on_off_status);
    int up_down_motor_move_0_speed();
    int actionsValid(int err,QString errStr);
signals:
    void sglRunResult(const QString &resultStr);
    void sglMonthMaintain(int result);
    void sglPumpCalibrateFinish(int pumpNo, int fstSteps, int SndSteps);
    void sglSampleBatchNo(int pos,QString sampleNo);
    void sglMaintainStep(int index,QString des);
private:
    Components *_components;
    eMaintainType _mainType;
    QMap<uchar,ushort> _reagentPosVolumnMap;
    QVector<uchar>_pumpVect;
};

#endif // MAINTAINSYSTEM_H
