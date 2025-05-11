#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <QString>
#include <QMutex>
#include <QThread>
#include <QObject>
#include <functional>
#include "Component.h"
#include <QSharedPointer>
#include <QVector>

class Valve;
class MainController;
class Buzzle;
class Motor;
class Sensor;
class Camera;
class Temperature;
class Light;
class Encoder;
class RockBed;
class Fan;
class Scaner;
class SampleArm;
class Liquid;

class AnalysisReciveCmd;

template <class T>
class Singleton;

class Components:public QObject
{
    using PComponent=QSharedPointer<Component>;
    using PValve=QSharedPointer<Valve>;
    using PMainController=QSharedPointer<MainController>;
    using PBuzzle=QSharedPointer<Buzzle>;
    using PMotor=QSharedPointer<Motor>;
    using PSensor=QSharedPointer<Sensor>;
    using PCamera=QSharedPointer<Camera>;
    using PTemperature=QSharedPointer<Temperature>;
    using PLight=QSharedPointer<Light>;
    using PEncoder=QSharedPointer<Encoder>;
    using PRockBed=QSharedPointer<RockBed>;
    using PFan=QSharedPointer<Fan>;
    using PScaner=QSharedPointer<Scaner>;
    using PSampleArm=QSharedPointer<SampleArm>;
    using PLiquid=QSharedPointer<Liquid>;
private:
    Components(QObject *parent = nullptr);
    Components(Components &)=delete;
    Components(Components &&)=delete;
    Components &operator=(const Components&)=delete;
    Components &operator=(Components&&)=delete;
    friend Singleton<Components>;
public:
    typedef enum
    {
        EError=1,
        EPause=2,
        EOther=3,
    }EAlarm;
    using MotorAddress=Component::MotorAddress;
    using ValveAddress=Component::ValveAddress;
    using TemperatureAddress=Component::TemperatureAddress;
    using LightAddress=Component::LightAddress;
    using EncoderAddress=Component::EncoderAddress;

    using funType=std::function<void (QByteArray arr)>;
    using funWarn=std::function<void (int)>;
    static Components*instance();
    virtual~Components();

public:    
    PValve getValveByAddress(ValveAddress addr);
    PMainController get_main_controller();
    PCamera getCamera();
    PSensor getSensor();
    PMotor getMotorByAddress(MotorAddress address);
    PBuzzle getBuzzle();
    PTemperature getTemperature();
    PLight getLightByAddress(LightAddress address);
    PEncoder getEncoderByAddress(EncoderAddress address);
    PRockBed getRockBed();
    PFan getFan();
    PScaner getScaner();
    PSampleArm getSampleArm();
    PLiquid getLiquid();


    void warnAlarm(const EAlarm level);

    void setCmdFun(const funType &cmdFun);
    void setWarnFun(const funWarn &fun);

    bool getIsRestart() const;
    void setIsRestart(bool isRestart);

    void setIsPause(bool isPause);
    bool getIsPause() const;

private:
    void initValve();
    void initMotor();
    void initLight();
    void initEncoder();
    funType getCmdFun() const;
    int analysis(QByteArray cmd,uint size);
    int analysis_compound_response_command();
    int analysis_inquire_response_command();
    int analysis_action_response_command();
    int analysis_report_command();
    void commandArrived(uint size);
private:
    QVector<PValve>    _valveVect;
    PMainController    _mainctroller;
    PCamera            _camera;
    PSensor            _sensor;
    QVector<PMotor>    _motorVect;
    PBuzzle            _buzzle;
    PTemperature       _temperature;
    QVector<PLight>    _lightVect;
    QVector<PEncoder>  _encoderVect;
    PRockBed           _rockBed;
    PFan               _fan;
    PScaner            _scaner;
    PSampleArm         _sampleArm;
    PLiquid            _liquid;


    AnalysisReciveCmd *_reciveCmd;
    static QMutex      _lock;
    unsigned char *    _command;
    uint               _size;
    funType            _cmdFun;
    funWarn            _warnFun;

    bool               _isRestart;
    bool               _isPause;
    QString            _portCom;

    static QMap<int,QString> _alphabetMap;
};

#endif // COMPONENTS_H
