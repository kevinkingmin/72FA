#include "Liquid.h"
#include "src/cmd/Command.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "src/local_log.h"

QMap<Liquid::ELiquidType,Liquid::LightAddress>Liquid::_LTypeLightMap
{
    {L_COMBINDA,LIGHT_COMBINDA}
    ,{L_COMBINDB,LIGHT_COMBINDB}
    ,{L_COMBINDC,LIGHT_COMBINDC}
    ,{L_COMBINDD,LIGHT_COMBINDD}
    ,{L_DILUENT,LIGHT_DILUENT}
    ,{L_SUBSTRATE,LIGHT_SUBSTRATE}
    ,{L_STOPLIQUID,LIGHT_STOPLIQUID}
    ,{L_DISTILEWATER,LIGHT_DISTILEWATER}
    ,{L_WASHWATER,LIGHT_WASHWATER}
    ,{L_SYSTEMLIQUID,LIGHT_SYSTEMLIQUID}
};

Liquid::Liquid(QObject *parent):Component (parent)
  ,_calibrateFstSteps(0)
  ,_calibrateSndSteps(0)
  ,_50ulSteps(0)
{}

Liquid::~Liquid()
{

}

int Liquid::liquidBackFlow(const uchar flowType, const ushort flowVolumn, const bool isLightOn)
{
    Command cmd;
    if(cmd.generatePeristalticPumpBackFlowCommand(flowType,flowVolumn)<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    auto ret(waitCompoundCmdAnswer());
    /*
    if(isLightOn)
        liquidLightControl(flowType,01);
        */
    return ret;
}

//蠕动泵加液
int Liquid::pumpCalibrate(const uchar pumpNo, const ushort volume,const bool isLightOn)
{
    Command cmd;
    if(cmd.generateCalibratePeristalticPumpCommand(pumpNo,volume)<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }

    auto ret(waitCompoundCmdAnswer(70000));
    /*
    if(isLightOn)
        liquidLightControl(pumpNo,01);
        */
    return ret;
}

int Liquid::pumpFlushIrrigation(const uchar flushType, const ushort flushVolumn, const bool isLightOn)
{
    Command cmd;
    if(cmd.generatePeristalticPumpFillLiquidCommand(flushType,flushVolumn)<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }

    auto ret(waitCompoundCmdAnswer());
    /*
    if(isLightOn)
        liquidLightControl(flushType,01);
        */
    return ret;
}

int Liquid::discardWasteAndSpitByPump(const uchar reactNO,
                                      const uchar spitPos,
                                      const ushort discardWasteTime,
                                      const uchar spitType,
                                      const ushort spitVolumn,
                                      const bool isLightOn)
{
    Command cmd;
    if(cmd.generateDischargeWasteAndPeristalticPumpSpitLiquidCommand(reactNO,spitPos,discardWasteTime,
                                                                     spitType,spitVolumn)<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }

    auto ret(waitCompoundCmdAnswer());
    /*
    if(isLightOn)
        liquidLightControl(spitType,01);
        */
    return ret;
}

int Liquid::irrigationSystemLiquid(const ushort volumn,const bool isLightOn)
{
    Command cmd;
    if(cmd.generateIrrigationSystemLiquidCommand(volumn)<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }

    auto ret(waitCompoundCmdAnswer());
    /*
    if(isLightOn)
        liquidLightControl(L_SYSTEMLIQUID,01);
        */
    return ret;
}

int Liquid::washSystemLiquidWay(const ushort volumn)
{
    Command cmd;
    if(cmd.generateWashSystemLiquidWayCommand(volumn)<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    return waitCompoundCmdAnswer();
}

int Liquid::write50ulToStepsToMachine(const uchar pumpNo, int steps)
{
    Command cmd;
    if(cmd.generateWritePeristalticPumpVolumeValueConvertToStepsValueCommand(pumpNo,steps)<0)
        return -1;
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
        return -2;

    return waitMachineAnswer();
}


int Liquid::inquirePeristalticPumpStepsFrom50ul(const uchar pumpNo)
{
    Command cmd;
    if(cmd.generateInquirePeristalticPumpVolumeValueConvertToStepsValueCommand(pumpNo)<0)
        return -1;
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
        return -2;

    return waitMachineAnswer();
}

void Liquid::setCalibrateSteps(int fstSteps, int SndSteps)
{
    {
        QMutexLocker locker(&_dataLock);
        _calibrateFstSteps=fstSteps;
        _calibrateSndSteps=SndSteps;
    }
    setComResponseFlag(FLAG_IDLE);
}

void Liquid::getCalibrateSteps(int &fstSteps, int &SndSteps)
{
    QMutexLocker locker(&_dataLock);
    fstSteps=_calibrateFstSteps;
    SndSteps=_calibrateSndSteps;
}

int Liquid::get50ulSteps() const
{
    QMutexLocker locker(&_dataLock);
    return _50ulSteps;
}

void Liquid::set50ulSteps(int value)
{
    _50ulSteps = value;
    setInquireResponseFlag(FLAG_IDLE);
}

int Liquid::liquidLightControl(const uchar lType, const uchar state)
{
    if(lType>L_SYSTEMLIQUID)
        return 0;
    auto it(_LTypeLightMap.find(static_cast<ELiquidType>(lType)));
    if(it==_LTypeLightMap.end())//即不需要控制灯的电机
        return 0;

    auto lightAddress(it.value());
    Command cmd;
    if(cmd.generateIndicatorLightOnOffCommand(lightAddress,state)<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    return waitMachineAnswer();
}
