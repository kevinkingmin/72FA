#ifndef COMPONENT_H
#define COMPONENT_H
#include <QObject>
#include <QMutex>
class InstrumentStateModel;

#define MOTORSTART 0x01
#define MOTORCOUNT 0x0F

#define VALVESTART 1
#define VALVECOUNT 7

#define LIGHTSTART 0
#define LIGHTCOUNT 13

#define ENCODERSTART 1
#define ENCODERCOUNT 2
class Component:public QObject
{
public:
    explicit Component(QObject *parent=nullptr);
    virtual ~Component(void);
public:
    enum
    {
        ANSWER_TIMEOUT=5000,
        MOVE_TIMEOUT=90000
    };

    typedef enum
    {
        FLAG_IDLE,
        FLAG_BUSY,
        FLAG_UNKNOWN,
        FLAG_EMPTY,
        FLAG_USED
    }Flag;

    typedef enum
    {
        MOTOR_X_AXIS=MOTORSTART,
        MOTOR_Y_AXIS=0x02,
        MOTOR_Z_AXIS=0x03,
        MOTOR_SAMPLE_PLUNGER=0x04,
        MOTOR_SHAKE_BED=0x05,
        MOTOR_COMBINE_A_PERISTALTIC=0x06,
        MOTOR_COMBINE_B_PERISTALTIC=0x07,
        MOTOR_COMBINE_C_PERISTALTIC=0x08,
        MOTOR_COMBINE_D_PERISTALTIC=0x09,
        MOTOR_DILUTION_PERISTALTIC=0x0A,
        MOTOR_SUBSTRATE_PERISTALTIC=0x0B,
        MOTOR_ELIMINATION_PERISTALTIC=0x0C,
        MOTOR_DISTILLED_WATER_PERISTALTIC=0x0D,
        MOTOR_WASH_WATER_PERISTALTIC=MOTORCOUNT-1,
        MOTOR_SYSTEM_WATER_PERISTALTIC=MOTORCOUNT,
    }MotorAddress;


    typedef enum
    {
        VALVE_SAMPLEADD=VALVESTART,
        VALVE_SAMPLEN_WLIQUID_PUMP=2,
        VALVE_REACT_WLIQUID_PUMP=3,
        VALVE_FANA=11,
        VALVE_FANB=12,
        VALVE_FANC=13,
        VALVE_FAND=14,
    }ValveAddress;

    typedef enum
    {
        LIGHT_WORKING=LIGHTSTART,
        LIGHT_WARNING=0X01,
        LIGHT_COMBINDA=0X02,
        LIGHT_COMBINDB=0X03,
        LIGHT_COMBINDC=0X04,
        LIGHT_COMBINDD=0X05,
        LIGHT_DILUENT=0X06,
        LIGHT_SUBSTRATE=0X07,
        LIGHT_STOPLIQUID=0X08,
        LIGHT_DISTILEWATER=0X09,
        LIGHT_WASHWATER=0X0A,
        LIGHT_SYSTEMLIQUID=0X0B,
        LIGHT_BACKLIGHT=LIGHTCOUNT-1,
    }LightAddress;

    typedef enum
    {
        SERSOR_COVER=0,
        SERSOR_WASTE_BOTTLE_FULL=1,
        SERSOR_SYSTEM_BOTTLE_EMPTY=2,
        SERSOR_COLLIDE_NEEDLE=3,
    }SensorAddress;

    typedef enum
    {
        TEMPERATURE_BED=0,
        TEMP_COUNT=1,
    }TemperatureAddress;

    typedef enum
    {
        ENCODER_X=ENCODERSTART,
        ENCODER_Y=ENCODERCOUNT,
    }EncoderAddress;

    typedef enum
    {
        STATE_NORMAL,
        STATE_ERROR,
    }State;
public:
    int flush_answer();
public:
    Flag getMoveResponseFlag() const;
    void setMoveResponseFlag(const Flag flag);
    Flag getInquireResponseFlag() const;
    void setInquireResponseFlag(const Flag &v);
    Flag getComResponseFlag() const;
    void setComResponseFlag(const Flag &comResponseFlag);
    void setState(const State state);
    State getState() const;

protected:
    int waitMachineAnswer(const int timeout=ANSWER_TIMEOUT);
    int waitMoveComplete(const int timeout=MOVE_TIMEOUT);
    int waitCompoundCmdAnswer(const int timeout=MOVE_TIMEOUT);

    static QMutex _controlLock;
    static QMutex _dataLock;
private:
     Flag _InquireResponseFlag;
     Flag _moveResponseFlag;
     Flag _comResponseFlag;
     State _state;
     Flag _sensorFlag[SensorAddress::SERSOR_COLLIDE_NEEDLE];
     InstrumentStateModel *_instrState;
};

#endif // COMPONENT_H
