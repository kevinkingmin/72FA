#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include <QObject>
#include "instrument_global.h"
#include <functional>
#include <QSharedPointer>
#include <QMap>
#include <QVector>
#include <QSharedPointer>
#include <QTcpSocket>
#include "../Include/Model/baseSet/CommonType.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include <QMutex>

template <class T>
class Singleton;
class Components;
class Functions;
class SerialPortDriver;
class Timing;
class ProcessStepData;
class SampleTestModel;
class ProcessReagentModel;

struct INSTRUMENTSHARED_EXPORT MotorSpeedPara
{
    uchar motorAddress;
    bool photoelectricEnable;
    bool direction;
    uint speed;
    MotorSpeedPara() :motorAddress(0),photoelectricEnable(false),direction(false),speed(0)
    {}
};
typedef enum
{
    inquireMachineNoId=1,
    inquire_main_controller_versionId=2,
    lightControlId=3,
    setBuzzleOnOffId=4,
    inquireMotorSpeedId=5,
    motorMoveConstSpeedId=6,
    motorStopId=7,
    motorInitializeId=8,
    motorsInitializeId=9,
    valveControlId=10,
    pumpFlushIrrigationId=11,
    rockBedWorkingId=12,
    irrigationSystemLiquidId=13,
    washSystemLiquidWayId=14,
    liquidBackFlowId=15,
    fanControlId=16,
    calibrateCameraId=17,
    sampleArmSuckId=18,
    sampleArmWashId=19,
    inquireZMotorParaId=20,
    inquireYMotorParasId=21,
    motorMoveToAbsolutePosId=22,
    convertVolumeToStepsToMachineId=23,
    getWPumpVolumeToStepsId=24,
    controlHeatId=25,
}ActionIdEnum;

class INSTRUMENTSHARED_EXPORT Instrument:public QObject
{
    Q_OBJECT
private:
    Instrument(QObject *parent=nullptr);
    Instrument(Instrument &)=delete;
    Instrument(Instrument &&)=delete;
    Instrument &operator=(const Instrument&)=delete;
    Instrument &operator=(Instrument&&)=delete;
    friend Singleton<Instrument>;
    using ptrTime=QSharedPointer<Timing>;
    using ptrTest=QSharedPointer<SampleTestModel>;
    uint8_t checkFrameData(QByteArray data);
    QByteArray getFrameReceiveRespone(QByteArray data);
    int16_t frameIndex=0;
    char start = 0x01;
    char end = 0x04;
    uint32_t messageId=0;
    QMutex mutex;
public:
    virtual ~Instrument();
    static Instrument*instance();
    void initLog(const QString& path, int level);
    QList<QByteArray>  messageQueueList;
    QVector<QString> getPorts();
    int start_instrument();
    void stop_instrument();
    uint32_t getMessageId();
    bool getMathineCode();
    bool selfCheck();
    bool systemPipWash(uint16_t volume);
    bool pipWash(QList<uint8_t> pumpList,uint16_t volume);
    bool pipFlowback(QList<uint8_t> pumpList,uint16_t volume);
    bool pumpAutoCalibrate(QList<uint8_t> pumpList);
    bool monthlyMaintenance(QList<uint8_t> pumpList);
    bool weeklyMaintenance(QList<uint8_t> pumpList);
    bool incubationByHand(uint16_t time);
    bool scanSampleCode(QString startPosition,QString endPosition);
    bool testStart(QList<QString> sampleTestIds, QList<int> groupIds,const int companyId);
    bool testPause();
    bool testStop();
    bool testContinue();
    bool prepareReagent(QList<uint8_t> pumpList,QString type);
    bool shutdownMaintenance(QList<uint8_t> pumpList);
    bool shutdownBee();
    bool getPDFReport(const QByteArray &datas);
    int16_t initMachineCommand = 0x0001;//开机自检
    int16_t systemPipWashCommand = 0x0002;//系统管路清洗
    int16_t PipWashCommand = 0x0003;//管路清洗
    int16_t PipFlowbackCommand = 0x0004;//管路回流
    int16_t pumpAutoCalibrateCommand = 0x0005;//泵自动校准
    int16_t pumpCalibrateCommand = 0x0006;//泵手动校准
    int16_t liquidDetectionCommand = 0x0007;//管路回流
    int16_t weekMaintenCommand = 0x0008;//周维护
    int16_t monthMaintenCommand = 0x0009;//月维护
    int16_t incubationByHandCommand = 0x000a;//手工孵育
    int16_t pumpAgingCommand = 0x000b;//泵磨合
    int16_t detectionStartCommand = 0x000c;//检测
    int16_t detectionPauseCommand = 0x000d;//检测暂停
    int16_t detectionStopCommand = 0x000e;//检测停止
    int16_t detectionContinueCommand = 0x000f;//检测继续
    int16_t prepareReagentCommand = 0x0010;//试剂充灌
    int16_t scanSampleCodeCommand = 0x0011;//扫码
    int16_t shutdownMaintenCommand = 0x0012;//关机维护
    int16_t shutdownBeeCommand = 0x0013;//关机维护
    int16_t getMachineCodeCommand = 0x0100;//获取机器编号
    int16_t getTemperatureCommand = 0x0101;//获取机器编号
    int16_t getLiquidStateCommand = 0x0102;//获取液位信息  系统液/废液 报警 取消报警
    int16_t frameResponeCommand = 0x0200;//消息收到响应
    int16_t getPDFReportCommand= 0x0015;//打印PDF
    int getUnitReagentVolumn(int companyId,int reagentId);
    //static void write_iccard_log(const std::string &text);
    //static InstrumentType get_instrument_type();

    //int get_maincontroller_hardware_version();

    //int get_maincontroller_software_version();

    //void inquireMachineNo();

    //QString get_machine_no();

    //QString get_MCB_Version();

    //void inquire_main_controller_version();

    int init_instrument_environment();
    void setProcessReagentVect(QVector<ProcessReagentModel> processReagentVect);
    //void setIsPause(bool pause);
    //void machineStop();
    const QMap<int, QString> &getGroupMap();
    const QMap<int, int> &getStepRunTime();
    void setGroupMap(QMap<int, QString> &groupMap,const int companyId);

    //void maintain(eMaintainType etype);
    void setReagentPosVolumnMap(const QMap<uchar,ushort> &reagentPosVolumnMap);

    bool getSerialPortIsOpen();
    void onDataArrive(QByteArray datas);
    void onWarnArrive(int code);

    bool send(unsigned char * cmd,unsigned int size) const;

    //bool moveToPhotoPos(const uchar pos);

    // void lightControl(const uchar address, uchar state);
    // void setPumpVect(const QVector<uchar> &pumpVect);

    //void inquireSensorState();

    //void scanSampleBatchNo(QVector<int> posVect);

    //void setBuzzleOnOff(const char state);

    //void inquireMotorSpeed(const QVector<uchar> motorAddressVect);

    //QVector<int> getMotorSpeed(const QVector<uchar> motorAddressVect);

    //void  motorMoveConstSpeed(QVector<MotorSpeedPara>paras);

    //void motorStop(const QVector<uchar> motorAddressVect);

    //void motorInitialize(uchar motorAddress,const int timeout);

    //void motorsInitialize(QVector<uchar>motorVect,const int timeout);

    //void valveControl(int address, const bool enable);

    //void pumpFlushIrrigation(int typeFill,const ushort flushVolumn, const bool isLightOn=true);

    //void rockBedWorking(uchar speed);

    //void pumpCalibrate(const uchar pumpNo, const ushort volume, const bool isLightOn=true);

    //void irrigationSystemLiquid(const ushort volumn);

    void washSystemLiquidWay(const ushort volumn);

    //void liquidBackFlow(const uchar flowType,const ushort flowVolumn,const bool isLightOn=true);

    //void fanControl(const uchar runType, const uchar pos);

    //void calibrateCamera();

    //void sampleArmSuck(const ushort volum,const bool sensorEnable,const uchar cupType,const uchar suckPos);

    //void sampleArmWash(const ushort outerTime,const ushort innerTime,const ushort wasteTime);

    //int getSampleSuckPos() const;

    void inquireZMotorPara();

    /*void getZMotorPara(int &washHeight,
                       int &standartCupHeight,
                       int &bloodingCupHeight,
                       int &microCupHeight,
                       int &startDetectLevelHeight,
                       int &spitHeight,
                       int &detectLevel2ndDescendHeight,
                       int &wasteSlotHeight);*/

    //void inquireYMotorParas();

    /*void getYMotorPara(int &fstRackPos,
                       int &scdRackPos,
                       int &needleWashPos,
                       int &startDrawWastePos,
                       int &spitYPos,
                       int &startWasteSlotPos
                       ) const;*/

    /*void motorMoveToAbsolutePos(const char motorAddress,
                                const bool photoelectricEnable,
                                const bool direction,
                                const int pulse);

    void convertVolumeToStepsToMachine(const uchar pumpNo,int steps);

    void getWPumpVolumeToSteps(const uchar pumpNo,int &steps);*/

    //void setNeedFillPump(QMap<int,ushort>pumpMap);

    //void controlHeat(const float temperatureValue, const bool isOn);

    //int getUnitReagentVolumn(int companyId,int reagentId);
    bool sendBySocket(QByteArray buf);
    void closeSocket();
    void openSocket();
signals:
    void sglDataArrive(QByteArray datas);
    void sglScanReagent();
    void sglLiquidState(QString state);
    void sglCurrentGroupIdChanged(int groupId,int realTime);
    void sglMaintainInfor(const QString &strResult);
    void sglHandelStepName(const QString &stepName);

    void sglHandleStepDetail(int stepId,int index,bool isSucess,const QString &stepName);
    void sglMonthMaintain(int result);
    void sglPumpCalibrateResult(int pumpNo, int fstSteps, int SndSteps);

    void sglAutoPumpCalibrateResult(int ret,int pumpNo, int fstSteps, int SndSteps);
    void sglAlarmInfo(int warnCode);
    void sglMinitorTemperature(float temperature);

    void sglMinitorSensorState(ushort code,bool isSucess);

    void sglGetSampleBatchNo(int pos,QString batchNo);

    void sglMaintainStep(int index,QString des);

    void sglIsStepSuc(int ret);

    void sglPopUpWindow(QString windowDes);

    void onSocketDataReceive(QByteArray bytes);

    void sglSelfCheckResult(QString code);

    void sglGetMachineCodeResult(QString code);

    void sglMonthMaintenResult(QString code);

    void sglShutdownMaintenResult(QString code);

    void sglWeekMaintenResult(QString code);

    void sglSystemPipWashResult(QString code);

    void sglPipWashResult(QString code);

    void sglPipFlowbackResult(QString code);

    void sglDetectionStartResult(QString messageType,QString sample,QString slot,QString step,QString code,QString time);

    void sglDetectionPauseResult(QString code);

    void sglDetectionContinueResult(QString code);

    void sglDetectionStopResult(QString code);

    void sglPrepareReagentResult(QString code);

    void sglOnTemperature(float code);

    void sglScanSampleCodeResult(QByteArray resultData);
private:
    Components *_components;
    Functions *_functions;
    //SerialPortDriver *_port;
    ProcessStepData *_ProcessStepData;
    ptrTime _pTime;
    QVector<uchar> _pumpVect;
    QTcpSocket *tcpsocket;
    void analysisFrame();
    bool isReadFrame=true;
    InstrumentStateModel *_stateModel;
private slots:
    void connected_SLOT();
    void disconnected_SLOT();
    void readyRead_Slot();
};

#endif // INSTRUMENT_H
