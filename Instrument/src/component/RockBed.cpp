#include "RockBed.h"
#include <QTime>
#include "src/cmd/Command.h"
#include "src/local_log.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

RockBed::RockBed(QObject *parent)
    :Component(parent)
    ,_cameraPos(0)
{    
}

RockBed::~RockBed()
{
}

int RockBed::rockBedWorking(uchar speed)
{
    Command cmd;
    if(cmd.generateShakingBedWorkingCommand(speed)<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError && speed>0)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }

    if(waitCompoundCmdAnswer()<0)
        return -3;

    return 0;
}

int RockBed::writeSpeedToBed(const SpeedStruct &para)
{
    Command cmd;
    if(cmd.generateWriteSpeedToRockBedCommand(para.lSpeed,para.mSpeed,para.hSpeed)<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitMachineAnswer()<0)
        return -3;
    return 0;
}

int RockBed::writeDryPaperPosToBed(const int pos)
{
    Command cmd;
    if(cmd.generateSetDryPaperRockBedPosCommand(pos)<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitMachineAnswer()<0)
        return -3;
    return 0;
}

int RockBed::writeCameraPosToBed(const int pos)
{
    Command cmd;
    if(cmd.generateWritePosToRockBedCommand(pos)<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitMachineAnswer()<0)
        return -3;
    return 0;
}

int RockBed::inquireBedSpeed()
{
    Command cmd;
    if(cmd.generateInquireRockBedSpeedCommand()<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitMachineAnswer()<0)
        return -3;
    return 0;
}

int RockBed::inquireBedPos()
{
    Command cmd;
    if(cmd.generateInquireRockBedPosCommand()<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitMachineAnswer()<0)
        return -3;
    return 0;
}

RockBed::SpeedStruct RockBed::getSpeedPara() const
{
    QMutexLocker locker(&_dataLock);
    return _speedPara;
}

void RockBed::setSpeedPara(const SpeedStruct &speedPara)
{
    QMutexLocker locker(&_dataLock);
    setInquireResponseFlag(FLAG_IDLE);
    _speedPara = speedPara;
}

int RockBed::getCameraPos() const
{
    QMutexLocker locker(&_dataLock);
    return _cameraPos;
}

void RockBed::setCameraPos(const int cameraPos)
{
    QMutexLocker locker(&_dataLock);
    setInquireResponseFlag(FLAG_IDLE);
    _cameraPos = cameraPos;
}

