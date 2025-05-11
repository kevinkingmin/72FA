#include "SampleArm.h"
#include "ObjectInfo.h"
#include <QTime>
#include "src/cmd/Command.h"
#include "src/local_log.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

SampleArm::SampleArm(QObject *parent)
    :Component(parent)
    ,_sampleSuckPos(0)
{    
}

SampleArm::~SampleArm()
{
}

int SampleArm::suck(const ushort volum, const bool sensorEnable, const uchar cupType, const uchar suckPos)
{
    Command cmd;
    uchar able=sensorEnable?1:0;
    if(cmd.generateSpecimenArmSuckCommand(volum,able,cupType,suckPos)<0)
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

int SampleArm::spit(const ushort volum, const bool sensorEnable, const uchar spitPos)
{
    Command cmd;
    uchar able=sensorEnable?1:0;
    if(cmd.generateSpecimenArmSpitCommand(volum,able,spitPos)<0)
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

int SampleArm::suckAndSpit(const ushort volum, const uchar sensorEnable, const uchar cupType, const uchar suckPos, const uchar spitPos)
{
    Command cmd;
    if(cmd.generateSpecimenArmSuckAndSplitCommand(volum,sensorEnable,cupType,suckPos,spitPos)<0)
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

int SampleArm::wash(const ushort innerTime, const ushort outerTime, const ushort wasteTime)
{
    Command cmd;
    if(cmd.generateSpecimenArmWashCommand(innerTime,outerTime,wasteTime)<0)
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

int SampleArm::inquireSamplePlungerPumpStepsFrom1uL()
{
    Command cmd;
    if(cmd.generateInquirePlungerPumpVolumeValueConvertToStepsValueCommand()<0)
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

int SampleArm::inquireSampleNeedleAirColumnValue()
{
    Command cmd;
    if(cmd.generateInquireSampleAirColumnParameterCommand()<0)
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

int SampleArm::inquireBlockNeedleRValue()
{
    Command cmd;
    if(cmd.generateInquireNeedleBlockReferanceValueCommand()<0)
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

int SampleArm::inquireXMotorParas()
{
    Command cmd;
    if(cmd.generateInquireMotorXAxisPositionCommand()<0)
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

int SampleArm::inquireYMotorParas()
{
    Command cmd;
    if(cmd.generateInquireMotorYAxisPositionCommand()<0)
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

int SampleArm::inquireZMotorParas()
{
    Command cmd;
    if(cmd.generateInquireMotorZAxisPositionCommand()<0)
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

int SampleArm::controlDetectLevelEnable(const bool &isEnable)
{
    Command cmd;
    if(cmd.generateSpecimenLiquidLevelProbeSwitchAction(isEnable)<0)
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

int SampleArm::writeBlockNeedleRValue(const SampleArm::NeedleBlockPara &para)
{
    Command cmd;
    if(cmd.generateBlockNeedleParameterActionCommand(para.minValue,para.maxValue)<0)
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

int SampleArm::writeXMotorParas(const SampleArm::XMotorPara &para)
{
    Command cmd;
    if(cmd.generateWriteMotorXAxisPositionCommand(para.cupSpace,
                                                  para.rackSSpace,
                                                  para.rackLSpace,
                                                  para.rackPos,
                                                  para.rectSlotSpace,
                                                  para.rectDiscSpace,
                                                  para.sNeedleSpitXPos,
                                                  para.suckLiquidPos,
                                                  para.photographPos,
                                                  para.scanerXPos,
                                                  para.scanerChangePos,
                                                  para.cameraCalibratePos,
                                                  para.liquidDetectCalibratePos,
                                                  para.scanerSelfCheckPos,
                                                  para.scanerXPos2nd)<0)
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

int SampleArm::writeYMotorParas(const SampleArm::YMotorPara &para)
{
    Command cmd;
    if(cmd.generateWriteMotorYAxisPositionCommand(para.fstRackPos,
                                                  para.scdRackPos,
                                                  para.needleWashPos,
                                                  para.startDrawWastePos,
                                                  para.spitYPos,
                                                  para.startWasteSlotPos)<0)
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

int SampleArm::writeZMotorParas(const SampleArm::ZMotorPara &para)
{
    Command cmd;
    if(cmd.generateWriteMotorZAxisPositionCommand(para.washHeight,
                                                  para.standartCupHeight,
                                                  para.bloodingCupHeight,
                                                  para.microCupHeight,
                                                  para.startDetectLevelHeight,
                                                  para.spitHeight,
                                                  para.detectLevel2ndDescendHeight,
                                                  para.wasteSlotHeight)<0)
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

int SampleArm::write1ulToStepsToSamplePlungerPumps(const int &steps)
{
    Command cmd;
    if(cmd.generateWritePlungerPumpVolumeValueConvertToStepsValueCommand(steps)<0)
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

int SampleArm::writeSampleNeedleAirColumnValue(const ushort &volumn)
{
    Command cmd;
    if(cmd.generateSampleAirColumnParameterWriteActionCommand(volumn)<0)
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

int SampleArm::getStepsFrom1ul() const
{
    return _stepsFrom1ul;
}

void SampleArm::setStepsFrom1ul(int stepsFrom1ul)
{
    setInquireResponseFlag(FLAG_IDLE);
    _stepsFrom1ul = stepsFrom1ul;
}

ushort SampleArm::getNeedleAirColumn() const
{
    return _needleAirColumn;
}

void SampleArm::setNeedleAirColumn(const ushort &needleAirColumn)
{
    setInquireResponseFlag(FLAG_IDLE);
    _needleAirColumn = needleAirColumn;
}

SampleArm::NeedleBlockPara SampleArm::getBlockPara() const
{
    return _blockPara;
}

void SampleArm::setBlockPara(const NeedleBlockPara &blockPara)
{
    setInquireResponseFlag(FLAG_IDLE);
    _blockPara = blockPara;
}

SampleArm::XMotorPara SampleArm::getXMotorPara() const
{
    return _xMotorPara;
}

void SampleArm::setXMotorPara(const XMotorPara &xMotorPara)
{
    setInquireResponseFlag(FLAG_IDLE);
    _xMotorPara = xMotorPara;
}

SampleArm::YMotorPara SampleArm::getYMotorPara() const
{
    return _yMotorPara;
}

void SampleArm::setYMotorPara(const YMotorPara &yMotorPara)
{
    setInquireResponseFlag(FLAG_IDLE);
    _yMotorPara = yMotorPara;
}

SampleArm::ZMotorPara SampleArm::getZMotorPara() const
{
    return _zMotorPara;
}

void SampleArm::setZMotorPara(const ZMotorPara &zMotorPara)
{
    setInquireResponseFlag(FLAG_IDLE);
    _zMotorPara = zMotorPara;
}

int SampleArm::getSampleSuckPos() const
{
	dLog("sampleSuckPos:{}", _sampleSuckPos);
    return _sampleSuckPos;
}

void SampleArm::setSampleSuckPos(int sampleSuckPos)
{
    _sampleSuckPos = sampleSuckPos;
}

int SampleArm::getCupHeightByCupType(int cupType)
{
    if( _zMotorPara.bloodingCupHeight==0 || _zMotorPara.standartCupHeight==0 || _zMotorPara.microCupHeight==0)
        if(inquireZMotorParas()<0)
        {
            eLog("inquir para error");
            return -1;
        }
    switch (cupType)
    {
    case eStandardCup:
        return _zMotorPara.standartCupHeight;
    case eBloodCup:
        return _zMotorPara.bloodingCupHeight;
    case eMicrCup:
        return _zMotorPara.microCupHeight;
    }
    eLog("unknown cup type ,type:{}",cupType);
    return -1;
}

