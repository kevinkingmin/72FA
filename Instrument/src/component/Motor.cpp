#include "Motor.h"
#include "src/cmd/Command.h"
#include "src/local_log.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include <QTime>

QMap<Motor::MotorAddress,Motor::LightAddress>Motor::_motorLightMap
{
    {MOTOR_COMBINE_A_PERISTALTIC,LIGHT_COMBINDA}
    ,{MOTOR_COMBINE_B_PERISTALTIC,LIGHT_COMBINDB}
    ,{MOTOR_COMBINE_C_PERISTALTIC,LIGHT_COMBINDC}
    ,{MOTOR_COMBINE_D_PERISTALTIC,LIGHT_COMBINDD}
    ,{MOTOR_DILUTION_PERISTALTIC,LIGHT_DILUENT}
    ,{MOTOR_SUBSTRATE_PERISTALTIC,LIGHT_SUBSTRATE}
    ,{MOTOR_ELIMINATION_PERISTALTIC,LIGHT_STOPLIQUID}
    ,{MOTOR_DISTILLED_WATER_PERISTALTIC,LIGHT_DISTILEWATER}
    ,{MOTOR_WASH_WATER_PERISTALTIC,LIGHT_WASHWATER}
    ,{MOTOR_SYSTEM_WATER_PERISTALTIC,LIGHT_SYSTEMLIQUID}
};

Motor::Motor(MotorAddress address, QObject *parent):Component(parent)
  , m_address(address)
  , _leftPhotoelectricFlag(FLAG_IDLE)
  , _rightPhotoelectricFlag(FLAG_IDLE)
  , _currentPosition(0)
{
}

Motor::~Motor()
{
}


int Motor::motorInitialize(const int timeout, const bool isLightOn)
{
    Command cmd;
    if(cmd.generateInitializeMotorCommand(static_cast<unsigned char>(m_address))<0)
        return -1;
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        setComResponseFlag(FLAG_IDLE);
        return -2;
    }
    auto ret{waitCompoundCmdAnswer(timeout)};
    /*
    if(isLightOn)
        motorLightControl(01);
        */
    return ret;
}


int Motor::motorMoveToAbsolutePos(const bool photoelectricEnable,
                                  const bool direction,
                                  const int pulse,
                                  const int timeout,
                                  const bool isLightOn)
{
    Command cmd;
    if(cmd.generateMotorMoveToAbsolutePosActionCommand(static_cast<unsigned char>(m_address),
                                                       photoelectricEnable,
                                                       direction,
                                                       pulse)<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setMoveResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }

    auto ret{waitMoveComplete(timeout)};
    /*
    if(isLightOn)
        motorLightControl(01);
        */
    return ret;
}


int Motor::motorMoveToRelativePos(const bool photoelectricEnable,
                                  const bool direction,
                                  const int pulse,
                                  const int timeout,
                                  const bool isLightOn)
{
    Command cmd;
    if(cmd.generateMotorMoveToRelativePosActionCommand(static_cast<unsigned char>(m_address),
                                                       photoelectricEnable,
                                                       direction,
                                                       pulse)<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setMoveResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }

    auto ret{waitMoveComplete(timeout)};
    /*
    if(isLightOn)
        motorLightControl(01);
        */
    return ret;
}


int Motor::motorMoveConstSpeed(const bool photoelectricEnable,
                               const bool direction,
                               const uint speed,
                               const bool isLightOn)
{
    Command cmd;
    if(cmd.generateMotorTurnConstSpeedActionControl(static_cast<unsigned char>(m_address),
                                                    photoelectricEnable,
                                                    direction,
                                                    speed)<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setMoveResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }

    auto ret{waitMoveComplete()};
    /*
    if(isLightOn)
        motorLightControl(01);
        */
    return ret;
}


int Motor::motorStop()
{
    Command cmd;
    if(cmd.generateMotorStopActionCommand(static_cast<unsigned char>(m_address))<0)
        return -1;
    setMoveResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    return waitMoveComplete();
}



int Motor::motorRealseHoldMoment(const bool onOffStatus)
{
    Command cmd;
    unsigned char status=onOffStatus?1:0;
    if(cmd.generateMotorReleaseMomentActionCommand(static_cast<unsigned char>(m_address),status)<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    return waitMachineAnswer(2000);
}


int Motor::inquirePhotoelectric(const bool photoelectricPos)
{
    Command cmd;
    if(cmd.generateInquirePhotoelectricCommand(static_cast<unsigned char>(m_address),photoelectricPos)<0)
        return -1;

    setInquireResponseFlag(FLAG_BUSY);
    setLeftPhotoelectricFlag(FLAG_UNKNOWN);
    setRightPhotoelectricFlag(FLAG_UNKNOWN);
    if(cmd.send()<0)
    {
        return  -2;
    }
    return waitMachineAnswer();
}


int Motor::inquireMotorParameter()
{
    Command cmd;
    if(cmd.generateInquireMotorParameterCommand(m_address)<0)
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

int Motor::inquireMotorPosition()
{
    Command cmd;
    if(cmd.generateInquireMotorCurrentPositionCommand(m_address)<0)
        return -1;
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
        return -2;

    return waitMachineAnswer();
}

int Motor::writeMotorParameter(const MotorPara &para)
{
    Command cmd;
    if(cmd.generateSetMotorParameterActionCommand(m_address,
                                                  para.holddingCurrent,
                                                  para.maxCurrent,
                                                  para.accelerateMax,
                                                  para.accelerateA1,
                                                  para.accelerateDMax,
                                                  para.accelerateD1,
                                                  para.vmaxSpeed,
                                                  para.v1Speed,
                                                  para.vStopSpeed,
                                                  para.subdividing,
                                                  para.leftSensorEnable,
                                                  para.rightSensorEnable,
                                                  para.currentScale)<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
        return -2;

    return waitMachineAnswer(5000);
}

int Motor::writeZeroPosition()
{
    Command cmd;
    if(cmd.generateSetMotorZeroActionCommand(m_address)<0)
        return -1;
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
        return -2;

    return waitMachineAnswer();
}

Motor::Flag Motor::getLeftPhotoelectricFlag() const
{
    QMutexLocker locker(&_dataLock);
    return _leftPhotoelectricFlag;
}

void Motor::setLeftPhotoelectricFlag(const Flag &leftPhotoelectricFlag)
{
    QMutexLocker locker(&_dataLock);
    _leftPhotoelectricFlag = leftPhotoelectricFlag;
}

Motor::Flag Motor::getRightPhotoelectricFlag() const
{
    QMutexLocker locker(&_dataLock);
    return _rightPhotoelectricFlag;
}

void Motor::setRightPhotoelectricFlag(const Flag &rightPhotoelectricFlag)
{
    QMutexLocker locker(&_dataLock);
    _rightPhotoelectricFlag = rightPhotoelectricFlag;
}

Motor::MotorPara Motor::getMotorPara() const
{
    QMutexLocker locker(&_dataLock);
    return _motorPara;
}

void Motor::setMotorPara(const MotorPara &motorPara)
{   
    setInquireResponseFlag(FLAG_IDLE);
    _motorPara = motorPara;
}

int Motor::getCurrentPosition() const
{
    QMutexLocker locker(&_dataLock);
    return _currentPosition;
}

void Motor::setCurrentPosition(int currentPosition)
{
    setInquireResponseFlag(FLAG_IDLE);
    _currentPosition = currentPosition;
}

Motor::MotorAddress Motor::getAddress() const
{
    QMutexLocker locker(&_dataLock);
    return m_address;
}

int Motor::motorLightControl(const uchar state)
{
    auto it(_motorLightMap.find(m_address));
    if(it==_motorLightMap.end())//即不需要控制灯的电机
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
