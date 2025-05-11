#include "Temperature.h"
#include "ObjectInfo.h"
#include <QTime>
#include "src/cmd/Command.h"
#include "src/local_log.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

Temperature::Temperature(QObject *parent)
    :Component(parent)
    ,_DSTTemperature(ABSOLUTEZERO)
    ,_realTimeTemperature(ABSOLUTEZERO)
    ,_monitorFlag(FLAG_IDLE)
    ,_instrState(InstrumentStateModel::instance())
{
}

Temperature::~Temperature()
{
}


int Temperature::dstTemperatureControl(TemperatureAddress address, const bool enable, const float temperature)
{
    Command cmd;
    uchar able=enable?1:0;
    if(cmd.generateTemperatureControlActionCommand(address,able,temperature)<0)
        return -1;

    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitMachineAnswer()<0)
        return -3;
    return 0;
}
//设置pid参数
int Temperature::writeTemperaturePIDPara(TemperatureAddress address, const int p, const int i, const int d)
{
    Command cmd;
    if(cmd.generatePIDTemptureWriteActionCommand(address,p,i,d)<0)
        return -1;

    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitMachineAnswer()<0)
        return -3;
    return 0;
}

int Temperature::inquireDSTTemperature()
{
    Command cmd;
    if(cmd.generateInquireDstTemperatureCommand()<0)
        return -1;

    _DSTTemperature=ABSOLUTEZERO;
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitMachineAnswer()<0)
        return -3;
    return 0;
}

int Temperature::inquireRealTimeTemperature()
{
    Command cmd;
    if(cmd.generateInquireTemperatureCommand()<0)
        return -1;

    _monitorFlag=FLAG_BUSY;
	if (cmd.send() < 0)
		return -2;

    QTime time;
    time.start();
    while(true)
    {
        if(FLAG_IDLE==_monitorFlag)
            return 0;

        int timeElapsed = time.elapsed();
        if(_instrState->getMachineState().state==InstrumentStateModel::enumError)
        {
            return -1;
        }

        if(timeElapsed>ANSWER_TIMEOUT)
        {
            return -3;
        }
        Sleep(5);
    }
}

int Temperature::inquirePIDPara(Component::TemperatureAddress address)
{
    Command cmd;
    if(cmd.generateInquireTemperatureControlPIDParameterCommand(address)<0)
        return -1;

    resetPIDPara(address);
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitMachineAnswer()<0)
        return -3;
    return 0;
}

float Temperature::getDSTTemperature() const
{
    QMutexLocker locker(&_dataLock);
    return _DSTTemperature;
}

void Temperature::setDSTTemperature(float DSTTemperature)
{    
    setInquireResponseFlag(FLAG_IDLE);
    QMutexLocker locker(&_dataLock);
    _DSTTemperature = DSTTemperature;
}

float Temperature::getRealTimeTemperature() const
{
    QMutexLocker locker(&_dataLock);
    return _realTimeTemperature;
}

void Temperature::setRealTimeTemperature(float realTimeTemperature)
{
    QMutexLocker locker(&_dataLock);
    _monitorFlag = FLAG_IDLE;
    _realTimeTemperature = realTimeTemperature;
}

void Temperature::resetPIDPara(const TemperatureAddress address)
{
    _PIDPara[address].paraD=0;
    _PIDPara[address].paraI=0;
    _PIDPara[address].paraP=0;
}

void Temperature::setPIDPara(const PIDStruct &PIDPara, const TemperatureAddress address)
{
    QMutexLocker locker(&_dataLock);
    setInquireResponseFlag(FLAG_IDLE);
    _PIDPara[address]=PIDPara;
}

Temperature::PIDStruct Temperature::getPIDParaByAddress(const Component::TemperatureAddress address)
{
    QMutexLocker locker(&_dataLock);
    return _PIDPara[address];
}
