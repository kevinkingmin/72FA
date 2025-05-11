#ifndef INSTRUMENTSTATEMODEL_H
#define INSTRUMENTSTATEMODEL_H

#include <QString>
#include <QVector>
#include <QMap>
#include "../Model.h"

template <class T>
class Singleton;

class MODELSHARED_EXPORT InstrumentStateModel
{
private:
    InstrumentStateModel();
    InstrumentStateModel(InstrumentStateModel &)=delete;
    InstrumentStateModel(InstrumentStateModel &&)=delete;
    InstrumentStateModel &operator=(const InstrumentStateModel&)=delete;
    InstrumentStateModel &operator=(InstrumentStateModel&&)=delete;
    friend Singleton<InstrumentStateModel>;
    void init();
public:
    ~InstrumentStateModel();
    typedef  enum
    {
        enumUnKnown=0,
        enumUnConn=1,
        enumConn=2,
        enumUnInit=3,
        enumIniting=4,
        enumRuning=5,
        enumStandby=6,//待机状态（初始化完成、测试完成、维护完成）
        enumPause=7,
        enumDormant=8,//休眠
        enumMaintain=9,//维护
        enumError=10,
		enumCloseSoft = 11,
    } enumState;

    typedef enum
    {
        enumSampleRuning=1,
        enumCalibrateRuning=2,
        enumQCRuning=3,
    }RuninType;

    struct paraStrc
    {
        enumState state;
        QString nameStr;
        bool isInState;
        bool canInit;
		bool canRun;
        ushort prioty;

        paraStrc():
        state(enumUnKnown)
        ,nameStr("")
        ,isInState(false)
        ,canInit(false)
		,canRun(false)
        ,prioty(0)
        {}
    };

    paraStrc getMachineState();
    void setMachineState(enumState state);
    static InstrumentStateModel *instance();
private:
    QVector<paraStrc>_machineStates;
};

#endif // INSTRUMENTSTATEMODEL_H
