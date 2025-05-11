#ifndef MOTOR_H
#define MOTOR_H

#include<QMap>
#include"Component.h"
class Command;
class Motor:public Component
{
public:
    struct MotorPara
    {
        uchar holddingCurrent;
        uchar maxCurrent;
        ushort accelerateMax;
        ushort accelerateA1;
        ushort accelerateDMax;
        ushort accelerateD1;
        uint vmaxSpeed;
        uint v1Speed;
        uint vStopSpeed;
        uchar subdividing;
        bool leftSensorEnable;
        bool rightSensorEnable;
        uchar currentScale;
        MotorPara()
            :holddingCurrent(0)
            ,maxCurrent(0)
            ,accelerateMax(0)
            ,accelerateA1(0)
            ,accelerateDMax(0)
            ,accelerateD1(0)
            ,vmaxSpeed(0)
            ,v1Speed(0)
            ,vStopSpeed(0)
            ,subdividing(0)
            ,leftSensorEnable(false)
            ,rightSensorEnable(false)
            ,currentScale(0)
        {}
    };

    explicit Motor(MotorAddress address,QObject *parent=nullptr);
    virtual ~Motor();
    int motorInitialize(const int timeout=MOVE_TIMEOUT,const bool isLightOn=false);

    int motorMoveToAbsolutePos(const bool photoelectricEnable,
                               const bool direction,
                               const int pulse,
                               const int timeout=MOVE_TIMEOUT,
                               const bool isLightOn=false);

    int motorMoveToRelativePos(const bool photoelectricEnable,
                               const bool direction, const int pulse,
                               const int timeout=MOVE_TIMEOUT,
                               const bool isLightOn=false);

    int motorMoveConstSpeed(const bool photoelectricEnable,
                            const bool direction,
                            const uint speed,
                            const bool isLightOn=false);

    int motorStop();

    int motorRealseHoldMoment(const bool onOffStatus);

    int inquirePhotoelectric(const bool photoelectricPos);

    int inquireMotorParameter();

    int inquireMotorPosition();    

    int writeMotorParameter(const MotorPara &para);
    int writeZeroPosition();


    Flag getLeftPhotoelectricFlag() const;
    void setLeftPhotoelectricFlag(const Flag &leftPhotoelectricFlag);

    Flag getRightPhotoelectricFlag() const;
    void setRightPhotoelectricFlag(const Flag &rightPhotoelectricFlag);

    MotorPara getMotorPara() const;
    void setMotorPara(const MotorPara &motorPara);

    int getCurrentPosition() const;
    void setCurrentPosition(int currentPosition);

    MotorAddress getAddress() const;
private:

    int motorLightControl(const uchar state);
private:
    MotorAddress m_address;
    Flag _leftPhotoelectricFlag;
    Flag _rightPhotoelectricFlag;
    MotorPara _motorPara;
    int _currentPosition;
    static QMap<MotorAddress,LightAddress>_motorLightMap;
};

#endif // MOTOR_H
