#include "Instrument.h"
#include "src/local_log.h"
#include "../Include/Comm/singleton.h"
#include "../Include/SerialPortDriver/SerialPortDriver.h"
#include "src/component/MainController.h"
#include "src/component/Buzzle.h"
#include "src/component/Light.h"
#include "src/component/Temperature.h"
#include "src/component/Sensor.h"
#include "src/component/Motor.h"
#include "src/component/Valve.h"
#include "src/component/Liquid.h"
#include "src/component/RockBed.h"
#include "src/component/Fan.h"
#include "src/component/Camera.h"
#include "src/component/SampleArm.h"
#include "src/function/Functions.h"
#include "src/function/maintain/MaintainSystem.h"
#include "src/function/monitor/Monitor.h"
#include "src/function/timing/Timing.h"
#include "src/function/timing/ActionModel.h"
#include "src/component/Camera.h"
#include "../Include/SerialPortDriver/SerialPortDriver.h"
#include "../Include/Model/reagent/ProcessReagentModel.h"
#include "../Include/Model/baseSet/ProcessParaModel.h"
#include "../Include/BLL/baseSet/ProcessParaBLL.h"
#include "../Include/BLL/baseSet/TestPaperBLL.h"
#include "../Include/Model/baseSet/TestPaperModel.h"
#include "../Include/BLL/reagent/ReagentBLL.h"
#include "../Include/Model/reagent/ReagentModel.h"
#include "../Include/Utilities/async_task.h"
#include <QCryptographicHash>
#include <QThread>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtConcurrent/QtConcurrent>

#define TIMING_REAGENT_COVER_MONITOR 1

QByteArray getMd5(QByteArray content){
    QCryptographicHash hash(QCryptographicHash::Md5); // 创建MD5哈希对象
    hash.addData(content); // 添加数据到哈希对象
    return hash.result();
}

Instrument::Instrument(QObject *parent) :QObject(parent)
  , _functions(Functions::instance())
  , _pumpVect{}
  ,_stateModel(InstrumentStateModel::instance())
{
    connect(_functions->getMaintain(), &MaintainSystem::sglRunResult, this, [this](const QString &strResult) {
        emit sglMaintainInfor(strResult);
    });

    connect(_functions->getMaintain(), &MaintainSystem::sglMonthMaintain, this, [this](int result) {
        emit sglMonthMaintain(result);
    });

    connect(_functions->getMaintain(), &MaintainSystem::sglPumpCalibrateFinish, this, [this](int pumpNo, int fstSteps, int SndSteps) {
        emit sglPumpCalibrateResult(pumpNo, fstSteps, SndSteps);
    });

    connect(_functions->getMaintain(), &MaintainSystem::sglSampleBatchNo, this, [this](int pos, QString batchNO) {
        dLog("Scan successful,batchNO:{}", batchNO.toStdString());
        emit sglGetSampleBatchNo(pos, batchNO);
    });

    connect(_functions->getMaintain(), &MaintainSystem::sglMaintainStep, this, [this](int index, QString des) {
        emit sglMaintainStep(index, des);
    });

    tcpsocket = new QTcpSocket(this);
}

Instrument::~Instrument()
{
}

Instrument *Instrument::instance()
{
    return Singleton<Instrument>::instance();
}

void Instrument::analysisFrame(){
    mutex.lock();

    //解析
    if(messageQueueList.size()==0){
        mutex.unlock();
        return;
    }
    qDebug()<<"size:"<<messageQueueList.size();

    QByteArray frameData=Instrument::instance()->messageQueueList[0];
    uint32_t messageId = static_cast<uint32_t>(frameData[1] + (frameData[2]<<8) + (frameData[3]<<16) + (frameData[3]<<24));
    int16_t code = static_cast<int16_t>(frameData[11] + (frameData[12]<<8));
    uint16_t index =static_cast<uint16_t>(frameData[5] + (frameData[6]<<8));
    int16_t count =static_cast<int16_t>(frameData[7] + (frameData[8]<<8));
    QByteArray contentData;

    //数据不完整，不连续，删除
    /* if(index!=1){
        messageQueueList.removeAt(0);
        mutex.unlock();
        return;
    }*/

    //数据未接收完,等待
    if(messageQueueList.size()<count){
        mutex.unlock();
        return;
    }

    for(int i=0;i<count;i++){
        QByteArray tempFrameData=messageQueueList[i];
        uint16_t length_low = tempFrameData[9]&0x00ff;
        uint16_t length_high =tempFrameData[10]<<8&0xff00;
        uint16_t length = length_low|length_high;
        for(int j=0;j<length;j++){
            contentData.append(tempFrameData[13+j]);
        }
    }
    for(int i=0;i<count;i++){
        messageQueueList.removeFirst();
    }
    mutex.unlock();

    qDebug()<<"contentData:"<<contentData<<"code:"<<code;
    QJsonDocument doc = QJsonDocument::fromJson(contentData);
    if(doc.isNull()||doc.isEmpty()){
        return;
    }

    if(code==initMachineCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString key = keys[0];
        QJsonValue value = obj.value(key);
        QString result= value.toString();
        emit sglSelfCheckResult(result);
    }else if(code==systemPipWashCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString key = keys[0];
        QJsonValue value = obj.value(key);
        QString result= value.toString();
        emit sglSystemPipWashResult(result);
    }else if(code==PipWashCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString key = keys[0];
        QJsonValue value = obj.value(key);
        QString result= value.toString();
        emit sglPipWashResult(result);
    }else if(code==PipFlowbackCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString key = keys[0];
        QJsonValue value = obj.value(key);
        QString result= value.toString();
        emit sglPipFlowbackResult(result);
    }else if(code==pumpAutoCalibrateCommand){

    }else if(code==pumpCalibrateCommand){

    }else if(code==liquidDetectionCommand){

    }else if(code==weekMaintenCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString key = keys[0];
        QJsonValue value = obj.value(key);
        QString result= value.toString();
        emit sglWeekMaintenResult(result);
    }else if(code==monthMaintenCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString key = keys[0];
        QJsonValue value = obj.value(key);
        QString result= value.toString();
        emit sglMonthMaintenResult(result);
    }else if(code==shutdownMaintenCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString key = keys[0];
        QJsonValue value = obj.value(key);
        QString result= value.toString();
        emit sglShutdownMaintenResult(result);
    }
    else if(code==incubationByHandCommand){

    }else if(code==pumpAgingCommand){

    }else if(code==detectionStartCommand){
        QJsonObject obj = doc.object();
        QString sample = obj.value("sample").toString();
        QString step = obj.value("step").toString();
        QString slot = obj.value("slot").toString();
        QString code = obj.value("resultCode").toString();
        QString time = obj.value("time").toString();
        QString messageType = obj.value("messageType").toString();
        emit sglDetectionStartResult(messageType,sample,slot,step,code,time);
    }else if(code==detectionPauseCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString key = keys[0];
        QJsonValue value = obj.value(key);
        QString result= value.toString();
        emit sglDetectionPauseResult(result);
    }else if(code==detectionStopCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString key = keys[0];
        QJsonValue value = obj.value(key);
        QString result= value.toString();
        emit sglDetectionStopResult(result);
    }else if(code==detectionContinueCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString key = keys[0];
        QJsonValue value = obj.value(key);
        QString result= value.toString();
        emit sglDetectionContinueResult(result);
    }else if(code==getMachineCodeCommand){
        QJsonArray jsonArray =doc.array();
        QJsonObject deviceInfo = jsonArray.at(0).toObject();
        QStringList keys = deviceInfo.keys();
        if(deviceInfo.value(keys[0])=="deviceId"){
            QJsonValue value = deviceInfo.value(keys[1]);
            emit sglGetMachineCodeResult(value.toString());
        }
    }else if(code==getTemperatureCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString key = keys[0];
        QJsonValue value = obj.value(key);
        QString result= value.toString();
        qDebug()<<"secTemperature"<<result.toFloat();
        emit sglOnTemperature(result.toFloat());
    }
    else if(code==prepareReagentCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString key = keys[0];
        QJsonValue value = obj.value(key);
        QString result= value.toString();
        emit sglPrepareReagentResult(value.toString());
    }else if(code==frameResponeCommand){

    }else if(code==scanSampleCodeCommand){

        emit sglScanSampleCodeResult(contentData);
    }else if(code==getLiquidStateCommand){
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();
        QString result= obj.value( keys[0]).toString();
        emit sglLiquidState(result);
    }
}

void Instrument::connected_SLOT()
{
    QObject::connect(tcpsocket, &QTcpSocket::readyRead, this, &Instrument::readyRead_Slot);
    _stateModel->setMachineState(InstrumentStateModel::enumConn);
    getMathineCode();
    QtConcurrent::run([this]() {
        // 这里是线程要执行的任务
        while (isReadFrame) {
            analysisFrame();
            QThread::msleep(200);
        }
    });
}

void Instrument::disconnected_SLOT()
{

}

void Instrument::readyRead_Slot()//定义接收信号的槽
{
    mutex.lock();
    QByteArray buf=tcpsocket->readAll();
    int frameCount=buf.size()/1024;
    qDebug()<<"haverespone size:"<<frameCount;
    qDebug()<<"haverespone:"<<buf.toHex();
    for (int i=0;i<frameCount;i++) {
        //这里做过滤和校验
        QByteArray bufTemp =buf.mid(i*1024, 1024);
        int frameState=checkFrameData(bufTemp);
        qDebug()<<"frameState:"<<frameState;
        if(frameState!=0){
            continue;
        }
        qDebug()<<"haverespone";
        sendBySocket(getFrameReceiveRespone(bufTemp));//应答
        messageQueueList.append(bufTemp);
    }
    mutex.unlock();
}



//if()
//    ui->receivewd->appendPlainText(buf.toUtf8());//接收由tcp发送过来的信息
QByteArray Instrument::getFrameReceiveRespone(QByteArray data){
    data[9] = 0x01;
    data[10] = 0x00;//length
    data[11]=0x00;
    data[12]=0x02;//code

    QByteArray array;
    array.resize(1);
    array[0]=0x00;//0 无需重发 1需要重发
    for(int i=0;i<994;i++){
        data[i+13]=0x00;
    }
    QByteArray md5 = getMd5(array);
    for(int i=0;i<16;i++){
        data[1007+i]=md5[i];
    }
    return data;
}
//1，应答帧，不需要回复
//2，帧结构错误，不需要回复等重发
//3，md5校验错误，不需要回复等重发
uint8_t Instrument::checkFrameData(QByteArray data){
    if(data.size()!=1024){
        return 2;
    }
    if(data[0]!=start||data[1023]!=end){
        return 2;
    }
    //应答帧
    int16_t code =static_cast<int16_t>(data[11] + (data[12]<<8));
    if(code==frameResponeCommand){
        qDebug()<<"code:"<<code;
        return 1;
    }
    uint16_t length_low = data[9]&0x00ff;
    uint16_t length_high =data[10]<<8&0xff00;
    uint16_t length = length_low|length_high;
    qDebug()<<"length_low:"<<length_low<<"length_high:"<<length_high<<"length:"<<length;
    QByteArray tempByteArray;
    for(int i=0;i<length;i++){
        tempByteArray.append(data[i+13]);
    }
    qDebug()<<"content:"<<tempByteArray;
    QByteArray md5 = getMd5(tempByteArray);
    qDebug()<<"md5:"<<md5.toHex();
    for(int i=0;i<16;i++){
        if(md5[i]!=data[1007+i]){
            return 3;
        }
    }
    return 0;
}

bool Instrument::sendBySocket(QByteArray buf){
    if(tcpsocket->state()!=tcpsocket->ConnectedState){
        return false;
    }
    int sendCount =static_cast<int>(tcpsocket->write(buf,buf.length())) ;
    qDebug()<<"sendCount:"<<sendCount;
    qDebug()<<"send:"<<buf.toHex();
    if(sendCount<1024){
        return false;
    }
    return true;
}

int Instrument::getUnitReagentVolumn(int companyId, int reagentId)
{
    auto papers{ TestPaperBLL().getOnUsedRowsByCompanyId(companyId) };
    QVector<int>pIds{};
    for (auto p : papers)
        pIds.push_back(p->getID());

    QVector<int>paperRIds{};
    auto reagents{ ReagentBLL().getAllRows() };
    for (auto r : reagents)
    {
        if (r->getCompanyID() == companyId && pIds.contains(r->getPaperId()))
            paperRIds.push_back(r->getID());
    }

    auto processParaVect{ ProcessParaBLL().getRowByActId(companyId,2) };
    QMap<int, int>reagentIdVolumnMap{};
    for (auto pm : processParaVect)
    {
        if (pm->getCompanyId() != companyId)
            continue;

        auto paras{ pm->getParas() };
        int id{ -99 };
        int v{ 0 };
        for (auto para : paras)
        {
            if (para.id == 1)
                id = static_cast<int>(para.paraValue);
            else if (para.id == 2)
                v = static_cast<int>(para.paraValue);
        }

        if (v <= 0 || id == -99)
        {
            //eLog("para set error");
            continue;
        }

        if (reagentIdVolumnMap.keys().contains(id))
        {
            auto value{ reagentIdVolumnMap.value(id) + v };
            reagentIdVolumnMap[id] = value;
        }
        else
        {
            reagentIdVolumnMap.insert(id, v);
        }

    }

    if (reagentIdVolumnMap.keys().contains(reagentId))
        return reagentIdVolumnMap.value(reagentId);

    if (!reagentIdVolumnMap.keys().contains(-1))
    {
        eLog("tprocess_para set paper reagent id error");
        return 0;
    }

    if (paperRIds.contains(reagentId))
        return reagentIdVolumnMap.value(-1);

    eLog("can not find reagent,companyid may be error,reagentId:{}", reagentId);
    return 0;
}

void Instrument::openSocket(){
    //tcpsocket->connectToHost("192.168.0.47",7200);
    tcpsocket->connectToHost("127.0.0.1",7200);//转为无符号，连接服务器端口
    connect(tcpsocket,SIGNAL(connected()),this,SLOT(connected_SLOT()));
    connect(tcpsocket,SIGNAL(disconnected()),this,SLOT(disconnected_SLOT()));
}

void Instrument::closeSocket(){
    isReadFrame=false;
    QThread::msleep(1000);
    tcpsocket->close();
    tcpsocket->abort();
}

void Instrument::initLog(const QString &path, int level)
{
    QString strPath = path + "/instrument.log";
    log_init(strPath.toLocal8Bit(), level);
    SerialPortDriver::instance()->initLog(path + "/driver.log", level);
}

int Instrument::start_instrument()
{
    openSocket();
    return 0;
}

void Instrument::stop_instrument()
{
    closeSocket();
}

uint32_t Instrument::getMessageId(){
    if(messageId==0xffffffff){
        messageId=0;
    }
    messageId++;
    return messageId;
}

bool Instrument::shutdownBee(){
    uint32_t msgId = getMessageId();
    QByteArray requestCommand;
    requestCommand.fill(0x00,1024);
    requestCommand[0] = start;
    requestCommand[1] = static_cast<char>(msgId);
    requestCommand[2] = static_cast<char>(msgId>>8);
    requestCommand[3] = static_cast<char>(msgId>>16);
    requestCommand[4] = static_cast<char>(msgId>>24);
    requestCommand[5] = 0x01;
    requestCommand[6] = 0x00;
    requestCommand[7] = 0x01;
    requestCommand[8] = 0x00;
    requestCommand[9] = 0x00;
    requestCommand[10] = 0x00;
    requestCommand[11] = static_cast<char>(shutdownBeeCommand);
    requestCommand[12] = static_cast<char>(shutdownBeeCommand>>8);
    requestCommand[1023] = end;
    return sendBySocket(requestCommand);
}

bool Instrument::getPDFReport(const QVector<QString> &testIds)
{
    uint32_t msgId = getMessageId();
    QJsonObject jsonObject;
    QJsonArray array;
    for(QString testId:testIds)
        array.append(testId);
    jsonObject.insert("testId",array);
    QJsonDocument doc(jsonObject);
    QByteArray json = doc.toJson();
    int16_t contentLength=static_cast<int16_t>(json.length());

    QByteArray requestCommand;
    requestCommand.fill(0x00,1024);
    requestCommand[0] = start;
    requestCommand[1] = static_cast<char>(msgId);
    requestCommand[2] = static_cast<char>(msgId>>8);
    requestCommand[3] = static_cast<char>(msgId>>16);
    requestCommand[4] = static_cast<char>(msgId>>24);
    requestCommand[5] = 0x01;
    requestCommand[6] = 0x00;
    requestCommand[7] = 0x01;
    requestCommand[8] = 0x00;
	requestCommand[9] = static_cast<char>(contentLength);
	requestCommand[10] = static_cast<char>(contentLength >> 8);
    requestCommand[11] = static_cast<char>(getPDFReportCommand);
    requestCommand[12] = static_cast<char>(getPDFReportCommand>>8);
    QByteArray md5 = getMd5(json);
    for(int i=0;i<contentLength;i++){
        requestCommand[13+i]=json[i];
    }
    for(int i=0;i<16;i++){
        requestCommand[1007+i]=md5[i];
    }
    requestCommand[1023] = end;
    return sendBySocket(requestCommand);
}

bool Instrument::shutdownMaintenance(QList<uint8_t> pumpList){
    QByteArray requestFrame;
    QJsonObject jsonObject;
    QJsonArray array;
    for(uint8_t pumpNum:pumpList){
        array.append(pumpNum);
    }
    jsonObject.insert("pumpNo",array);
    QJsonDocument doc(jsonObject);
    QByteArray json = doc.toJson();
    int16_t contentLength=static_cast<int16_t>(json.length());
    QByteArray md5 = getMd5(json);
    uint32_t msgId = getMessageId();
    requestFrame.append(1024, char(0));
    requestFrame[0] = start;
    requestFrame[1] = static_cast<char>(msgId);
    requestFrame[2] = static_cast<char>(msgId>>8);
    requestFrame[3] = static_cast<char>(msgId>>16);
    requestFrame[4] = static_cast<char>(msgId>>24);
    requestFrame[5] = 0x01;
    requestFrame[6] = 0x00;
    requestFrame[7] = 0x01;
    requestFrame[8] = 0x00;
    requestFrame[9] = static_cast<char>(contentLength);
    requestFrame[10] = static_cast<char>(contentLength>>8);
    requestFrame[11] = static_cast<char>(shutdownMaintenCommand);
    requestFrame[12] = static_cast<char>(shutdownMaintenCommand>>8);
    for(int i=0;i<contentLength;i++){
        requestFrame[13+i]=json[i];
    }

    for(int i=0;i<16;i++){
        requestFrame[1007+i]=md5[i];
    }
    requestFrame[1023] = end;
    _stateModel->setMachineState(_stateModel->enumRuning);
    return sendBySocket(requestFrame);
}

bool Instrument::monthlyMaintenance(QList<uint8_t> pumpList){
    QByteArray requestFrame;
    QJsonObject jsonObject;
    QJsonArray array;
    for(uint8_t pumpNum:pumpList){
        array.append(pumpNum);
    }
    jsonObject.insert("pumpNo",array);
    QJsonDocument doc(jsonObject);
    QByteArray json = doc.toJson();
    int16_t contentLength=static_cast<int16_t>(json.length());
    QByteArray md5 = getMd5(json);
    uint32_t msgId = getMessageId();
    requestFrame.append(1024, char(0));
    requestFrame[0] = start;
    requestFrame[1] = static_cast<char>(msgId);
    requestFrame[2] = static_cast<char>(msgId>>8);
    requestFrame[3] = static_cast<char>(msgId>>16);
    requestFrame[4] = static_cast<char>(msgId>>24);
    requestFrame[5] = 0x01;
    requestFrame[6] = 0x00;
    requestFrame[7] = 0x01;
    requestFrame[8] = 0x00;
    requestFrame[9] = static_cast<char>(contentLength);
    requestFrame[10] = static_cast<char>(contentLength>>8);
    requestFrame[11] = static_cast<char>(monthMaintenCommand);
    requestFrame[12] = static_cast<char>(monthMaintenCommand>>8);
    for(int i=0;i<contentLength;i++){
        requestFrame[13+i]=json[i];
    }

    for(int i=0;i<16;i++){
        requestFrame[1007+i]=md5[i];
    }
    requestFrame[1023] = end;
    _stateModel->setMachineState(_stateModel->enumRuning);
    return sendBySocket(requestFrame);
}

bool Instrument::scanSampleCode(QString startPosition,QString endPosition){
    QByteArray requestFrame;
    QJsonObject jsonObject;
    jsonObject.insert("startPosition",startPosition);
    jsonObject.insert("endPosition",endPosition);
    QJsonDocument doc(jsonObject);
    QByteArray json = doc.toJson();
    int16_t contentLength=static_cast<int16_t>(json.length());
    QByteArray md5 = getMd5(json);
    uint32_t msgId = getMessageId();
    requestFrame.append(1024, char(0));
    requestFrame[0] = start;
    requestFrame[1] = static_cast<char>(msgId);
    requestFrame[2] = static_cast<char>(msgId>>8);
    requestFrame[3] = static_cast<char>(msgId>>16);
    requestFrame[4] = static_cast<char>(msgId>>24);
    requestFrame[5] = 0x01;
    requestFrame[6] = 0x00;
    requestFrame[7] = 0x01;
    requestFrame[8] = 0x00;
    requestFrame[9] = static_cast<char>(contentLength);
    requestFrame[10] = static_cast<char>(contentLength>>8);
    requestFrame[11] = static_cast<char>(scanSampleCodeCommand);
    requestFrame[12] = static_cast<char>(scanSampleCodeCommand>>8);
    for(int i=0;i<contentLength;i++){
        requestFrame[13+i]=json[i];
    }

    for(int i=0;i<16;i++){
        requestFrame[1007+i]=md5[i];
    }
    requestFrame[1023] = end;
    return sendBySocket(requestFrame);
}

bool Instrument::incubationByHand(uint16_t time){
    QByteArray requestFrame;
    QJsonObject jsonObject;
    jsonObject.insert("time",time);//time为 0 的时候停止
    QJsonDocument doc(jsonObject);
    QByteArray json = doc.toJson();
    int16_t contentLength=static_cast<int16_t>(json.length());
    QByteArray md5 = getMd5(json);
    uint32_t msgId = getMessageId();
    requestFrame.append(1024, char(0));
    requestFrame[0] = start;
    requestFrame[1] = static_cast<char>(msgId);
    requestFrame[2] = static_cast<char>(msgId>>8);
    requestFrame[3] = static_cast<char>(msgId>>16);
    requestFrame[4] = static_cast<char>(msgId>>24);
    requestFrame[5] = 0x01;
    requestFrame[6] = 0x00;
    requestFrame[7] = 0x01;
    requestFrame[8] = 0x00;
    requestFrame[9] = static_cast<char>(contentLength);
    requestFrame[10] = static_cast<char>(contentLength>>8);
    requestFrame[11] = static_cast<char>(incubationByHandCommand);
    requestFrame[12] = static_cast<char>(incubationByHandCommand>>8);
    for(int i=0;i<contentLength;i++){
        requestFrame[13+i]=json[i];
    }

    for(int i=0;i<16;i++){
        requestFrame[1007+i]=md5[i];
    }
    requestFrame[1023] = end;

    return sendBySocket(requestFrame);
}

bool Instrument::weeklyMaintenance(QList<uint8_t> pumpList){
    QByteArray requestFrame;
    QJsonObject jsonObject;
    QJsonArray array;
    for(uint8_t pumpNum:pumpList){
        array.append(pumpNum);
    }
    jsonObject.insert("pumpNo",array);
    QJsonDocument doc(jsonObject);
    QByteArray json = doc.toJson();
    int16_t contentLength=static_cast<int16_t>(json.length());
    QByteArray md5 = getMd5(json);
    uint32_t msgId = getMessageId();
    requestFrame.append(1024, char(0));
    requestFrame[0] = start;
    requestFrame[1] = static_cast<char>(msgId);
    requestFrame[2] = static_cast<char>(msgId>>8);
    requestFrame[3] = static_cast<char>(msgId>>16);
    requestFrame[4] = static_cast<char>(msgId>>24);
    requestFrame[5] = 0x01;
    requestFrame[6] = 0x00;
    requestFrame[7] = 0x01;
    requestFrame[8] = 0x00;
    requestFrame[9] = static_cast<char>(contentLength);
    requestFrame[10] = static_cast<char>(contentLength>>8);
    requestFrame[11] = static_cast<char>(weekMaintenCommand);
    requestFrame[12] = static_cast<char>(weekMaintenCommand>>8);
    for(int i=0;i<contentLength;i++){
        requestFrame[13+i]=json[i];
    }

    for(int i=0;i<16;i++){
        requestFrame[1007+i]=md5[i];
    }
    requestFrame[1023] = end;
    _stateModel->setMachineState(_stateModel->enumRuning);
    return sendBySocket(requestFrame);
}

bool Instrument::pumpAutoCalibrate(QList<uint8_t> pumpList){
    QByteArray requestFrame;
    QJsonObject jsonObject;
    QJsonArray array;
    for(uint8_t pumpNum:pumpList){
        array.append(pumpNum);
    }
    jsonObject.insert("pumpNo",array);
    QJsonDocument doc(jsonObject);
    QByteArray json = doc.toJson();
    int16_t contentLength=static_cast<int16_t>(json.length());
    QByteArray md5 = getMd5(json);
    uint32_t msgId = getMessageId();
    requestFrame.append(1024, char(0));
    requestFrame[0] = start;
    requestFrame[1] = static_cast<char>(msgId);
    requestFrame[2] = static_cast<char>(msgId>>8);
    requestFrame[3] = static_cast<char>(msgId>>16);
    requestFrame[4] = static_cast<char>(msgId>>24);
    requestFrame[5] = 0x01;
    requestFrame[6] = 0x00;
    requestFrame[7] = 0x01;
    requestFrame[8] = 0x00;
    requestFrame[9] = static_cast<char>(contentLength);
    requestFrame[10] = static_cast<char>(contentLength>>8);
    requestFrame[11] = static_cast<char>(PipFlowbackCommand);
    requestFrame[12] = static_cast<char>(PipFlowbackCommand>>8);
    for(int i=0;i<contentLength;i++){
        requestFrame[13+i]=json[i];
    }

    for(int i=0;i<16;i++){
        requestFrame[1007+i]=md5[i];
    }
    requestFrame[1023] = end;

    return sendBySocket(requestFrame);
}

//回流量读取数据库获得
bool Instrument::pipFlowback(QList<uint8_t> pumpList,uint16_t volume){
    QByteArray requestFrame;
    QJsonObject jsonObject;
    QJsonArray array;
    for(uint8_t pumpNum:pumpList){
        array.append(pumpNum);
    }
    jsonObject.insert("volume", volume);
    jsonObject.insert("pumpNo",array);
    QJsonDocument doc(jsonObject);
    QByteArray json = doc.toJson();
    int16_t contentLength=static_cast<int16_t>(json.length());
    QByteArray md5 = getMd5(json);
    uint32_t msgId = getMessageId();
    requestFrame.append(1024, char(0));
    requestFrame[0] = start;
    requestFrame[1] = static_cast<char>(msgId);
    requestFrame[2] = static_cast<char>(msgId>>8);
    requestFrame[3] = static_cast<char>(msgId>>16);
    requestFrame[4] = static_cast<char>(msgId>>24);
    requestFrame[5] = 0x01;
    requestFrame[6] = 0x00;
    requestFrame[7] = 0x01;
    requestFrame[8] = 0x00;
    requestFrame[9] = static_cast<char>(contentLength);
    requestFrame[10] = static_cast<char>(contentLength>>8);
    requestFrame[11] = static_cast<char>(PipFlowbackCommand);
    requestFrame[12] = static_cast<char>(PipFlowbackCommand>>8);
    for(int i=0;i<contentLength;i++){
        requestFrame[13+i]=json[i];
    }

    for(int i=0;i<16;i++){
        requestFrame[1007+i]=md5[i];
    }
    requestFrame[1023] = end;
    _stateModel->setMachineState(_stateModel->enumRuning);
    return sendBySocket(requestFrame);
}

bool Instrument::pipWash(QList<uint8_t> pumpList,uint16_t volume){
    QByteArray requestFrame;
    QJsonObject jsonObject;
    QJsonArray array;
    for(uint8_t pumpNum:pumpList){
        array.append(pumpNum);
    }
    jsonObject.insert("volume", volume);
    jsonObject.insert("pumpNo",array);
    QJsonDocument doc(jsonObject);
    QByteArray json = doc.toJson();
    int16_t contentLength=static_cast<int16_t>(json.length());
    QByteArray md5 = getMd5(json);
    uint32_t msgId = getMessageId();
    requestFrame.append(1024, char(0));
    requestFrame[0] = start;
    requestFrame[1] = static_cast<char>(msgId);
    requestFrame[2] = static_cast<char>(msgId>>8);
    requestFrame[3] = static_cast<char>(msgId>>16);
    requestFrame[4] = static_cast<char>(msgId>>24);
    requestFrame[5] = 0x01;
    requestFrame[6] = 0x00;
    requestFrame[7] = 0x01;
    requestFrame[8] = 0x00;
    requestFrame[9] = static_cast<char>(contentLength) ;
    requestFrame[10] = static_cast<char>(contentLength>>8);
    requestFrame[11] = static_cast<char>(PipWashCommand);
    requestFrame[12] = static_cast<char>(PipWashCommand>>8);
    for(int i=0;i<contentLength;i++){
        requestFrame[13+i]=json[i];
    }

    for(int i=0;i<16;i++){
        requestFrame[1007+i]=md5[i];
    }
    requestFrame[1023] = end;

    return sendBySocket(requestFrame);
}

bool Instrument::selfCheck(){
    uint32_t msgId = getMessageId();
    QByteArray requestCommand;
    requestCommand.fill(0x00,1024);
    requestCommand[0] = start;
    requestCommand[1] = static_cast<char>(msgId);
    requestCommand[2] = static_cast<char>(msgId>>8);
    requestCommand[3] = static_cast<char>(msgId>>16);
    requestCommand[4] = static_cast<char>(msgId>>24);
    requestCommand[5] = 0x01;
    requestCommand[6] = 0x00;
    requestCommand[7] = 0x01;
    requestCommand[8] = 0x00;
    requestCommand[9] = 0x00;
    requestCommand[10] = 0x00;
    requestCommand[11] = static_cast<char>(initMachineCommand);
    requestCommand[12] = static_cast<char>(initMachineCommand>>8);
    requestCommand[1023] = end;
    return sendBySocket(requestCommand);
}

bool Instrument::systemPipWash(uint16_t volume){
    QByteArray requestFrame;
    QJsonObject jsonObject;
    jsonObject.insert("volume", volume);
    QJsonDocument doc(jsonObject);
    QByteArray json = doc.toJson();
    int16_t contentLength=static_cast<int16_t>(json.length());
    QByteArray md5 = getMd5(json);
    uint32_t msgId = getMessageId();
    requestFrame.append(1024, char(0));
    requestFrame[0] = start;
    requestFrame[1] = static_cast<char>(msgId);
    requestFrame[2] = static_cast<char>(msgId>>8);
    requestFrame[3] = static_cast<char>(msgId>>16);
    requestFrame[4] = static_cast<char>(msgId>>24);
    requestFrame[5] = 0x01;
    requestFrame[6] = 0x00;
    requestFrame[7] = 0x01;
    requestFrame[8] = 0x00;
    requestFrame[9] = static_cast<char>(contentLength) ;
    requestFrame[10] = static_cast<char>(contentLength>>8);
    requestFrame[11] = 0x02;
    requestFrame[12] = 0x00;
    for(int i=0;i<contentLength;i++){
        requestFrame[13+i]=json[i];
    }

    for(int i=0;i<16;i++){
        requestFrame[1007+i]=md5[i];
    }
    requestFrame[1023] = end;

    return sendBySocket(requestFrame);
}

bool Instrument::getMathineCode(){
    uint32_t msgId = getMessageId();
    QByteArray requestCommand;
    requestCommand.fill(0x00,1024);
    requestCommand[0] = start;
    requestCommand[1] = static_cast<char>(msgId);
    requestCommand[2] = static_cast<char>(msgId>>8);
    requestCommand[3] = static_cast<char>(msgId>>16);
    requestCommand[4] = static_cast<char>(msgId>>24);
    requestCommand[5] = 0x01;
    requestCommand[6] = 0x00;
    requestCommand[7] = 0x01;
    requestCommand[8] = 0x00;
    requestCommand[9] = 0x00;
    requestCommand[10] = 0x00;
    requestCommand[11] = static_cast<char>(getMachineCodeCommand);
    requestCommand[12] = static_cast<char>(getMachineCodeCommand >>8);
    requestCommand[1023] = end;
    return sendBySocket(requestCommand);
}



/*void Instrument::inquire_main_controller_version()
{
    AsyncTask::post([this] {
        int result{ _functions->getMaintain()->inquire_main_controller_version() };
        if (result < 0)
            emit sglIsStepSuc(-inquire_main_controller_versionId);
        else
            emit sglIsStepSuc(inquire_main_controller_versionId);
    });
}*/

int Instrument::init_instrument_environment()
{
    const int result = _functions->getMaintain()->init_instrument_environment();
    if (result >= 0)
    {
        dLog("set machine state to enumStandby");
        //InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumStandby);
    }
    return(result);
}

bool Instrument::prepareReagent(QList<uint8_t> pumpList,QString type){
    QByteArray requestFrame;
    QJsonObject jsonObject;
    QJsonArray array;
    for(uint8_t pumpNum:pumpList){
        array.append(pumpNum);
    }
    jsonObject.insert("pumpNo",array);
    jsonObject.insert("type",type);
    QJsonDocument doc(jsonObject);
    QByteArray json = doc.toJson();
    int16_t contentLength=static_cast<int16_t>(json.length());
    QByteArray md5 = getMd5(json);
    uint32_t msgId = getMessageId();
    requestFrame.append(1024, char(0));
    requestFrame[0] = start;
    requestFrame[1] = static_cast<char>(msgId);
    requestFrame[2] = static_cast<char>(msgId>>8);
    requestFrame[3] = static_cast<char>(msgId>>16);
    requestFrame[4] = static_cast<char>(msgId>>24);
    requestFrame[5] = 0x01;
    requestFrame[6] = 0x00;
    requestFrame[7] = 0x01;
    requestFrame[8] = 0x00;
    requestFrame[9] = static_cast<char>(contentLength) ;
    requestFrame[10] = static_cast<char>(contentLength>>8);
    requestFrame[11] = static_cast<char>(prepareReagentCommand);
    requestFrame[12] = static_cast<char>(prepareReagentCommand>>8);
    for(int i=0;i<contentLength;i++){
        requestFrame[13+i]=json[i];
    }

    for(int i=0;i<16;i++){
        requestFrame[1007+i]=md5[i];
    }
    requestFrame[1023] = end;

    return sendBySocket(requestFrame);
}

bool Instrument::testContinue(){
    uint32_t msgId = getMessageId();
    QByteArray requestCommand;
    requestCommand.fill(0x00,1024);
    requestCommand[0] = start;
    requestCommand[1] = static_cast<char>(msgId);
    requestCommand[2] = static_cast<char>(msgId>>8);
    requestCommand[3] = static_cast<char>(msgId>>16);
    requestCommand[4] = static_cast<char>(msgId>>24);
    requestCommand[5] = 0x01;
    requestCommand[6] = 0x00;
    requestCommand[7] = 0x01;
    requestCommand[8] = 0x00;
    requestCommand[9] = 0x00;
    requestCommand[10] = 0x00;
    requestCommand[11] = static_cast<char>(detectionContinueCommand);
    requestCommand[12] = static_cast<char>(detectionContinueCommand >>8);
    requestCommand[1023] = end;
    return sendBySocket(requestCommand);
}

bool Instrument::testStop(){
    uint32_t msgId = getMessageId();
    QByteArray requestCommand;
    requestCommand.fill(0x00,1024);
    requestCommand[0] = start;
    requestCommand[1] = static_cast<char>(msgId);
    requestCommand[2] = static_cast<char>(msgId>>8);
    requestCommand[3] = static_cast<char>(msgId>>16);
    requestCommand[4] = static_cast<char>(msgId>>24);
    requestCommand[5] = 0x01;
    requestCommand[6] = 0x00;
    requestCommand[7] = 0x01;
    requestCommand[8] = 0x00;
    requestCommand[9] = 0x00;
    requestCommand[10] = 0x00;
    requestCommand[11] = static_cast<char>(detectionStopCommand);
    requestCommand[12] = static_cast<char>(detectionStopCommand >>8);
    requestCommand[1023] = end;
    return sendBySocket(requestCommand);
}

bool Instrument::testPause(){
    uint32_t msgId = getMessageId();
    QByteArray requestCommand;
    requestCommand.fill(0x00,1024);
    requestCommand[0] = start;
    requestCommand[1] = static_cast<char>(msgId);
    requestCommand[2] = static_cast<char>(msgId>>8);
    requestCommand[3] = static_cast<char>(msgId>>16);
    requestCommand[4] = static_cast<char>(msgId>>24);
    requestCommand[5] = 0x01;
    requestCommand[6] = 0x00;
    requestCommand[7] = 0x01;
    requestCommand[8] = 0x00;
    requestCommand[9] = 0x00;
    requestCommand[10] = 0x00;
    requestCommand[11] = static_cast<char>(detectionPauseCommand);
    requestCommand[12] = static_cast<char>(detectionPauseCommand >>8);
    requestCommand[1023] = end;
    return sendBySocket(requestCommand);
}

bool Instrument::testStart(QList<QString> sampleTestIds, QList<int> groupIds, const int companyId)
{   
    QJsonObject jsonObject;
    QJsonArray sampleTestIdArray;
    for(QString testId:sampleTestIds){
        sampleTestIdArray.append(testId);
    }
    QJsonArray groupIdArray;
    for(int groupId:groupIds){
        groupIdArray.append(groupId);
    }
    jsonObject.insert("testId", sampleTestIdArray);
    jsonObject.insert("process", groupIdArray);
    QJsonDocument doc(jsonObject);
    QByteArray json = doc.toJson();
    int length = json.length();
    int frameCount = length/994;
    if(length%994!=0){
        frameCount++;
    }
    uint32_t msgId = getMessageId();
    for(int i=0;i<frameCount;i++){
        int16_t contentLength;
        QByteArray requestFrame;
        QByteArray jsonTemp;
        if(i!=frameCount-1){
            contentLength=994;
            for (int j=0;j<994;j++) {
                jsonTemp.append(json.at(994*i+j));
            }
        }else {
            if(frameCount%994==0){
                contentLength=994;
                for (int j=0;j<994;j++) {
                    jsonTemp.append(json.at(994*i+j));
                }
            }else {
                contentLength=length%994;
                for (int j=0;j<contentLength;j++) {
                    jsonTemp.append(json.at(994*i+j));
                }
            }
        }
        QByteArray md5 = getMd5(jsonTemp);


        requestFrame.append(1024, char(0));
        requestFrame[0] = start;
        requestFrame[1] = static_cast<char>(msgId);
        requestFrame[2] = static_cast<char>(msgId>>8);
        requestFrame[3] = static_cast<char>(msgId>>16);
        requestFrame[4] = static_cast<char>(msgId>>24);
        requestFrame[5] = static_cast<char>(i+1);
        requestFrame[6] = static_cast<char>((i+1)>>8);
        requestFrame[7] = static_cast<char>(frameCount);
        requestFrame[8] = static_cast<char>(frameCount>>8);
        requestFrame[9] = static_cast<char>(contentLength) ;
        requestFrame[10] = static_cast<char>(contentLength>>8);
        requestFrame[11] = static_cast<char>(detectionStartCommand);
        requestFrame[12] = static_cast<char>(detectionStartCommand>>8);
        for(int j=0;j<contentLength;j++){
            requestFrame[13+j]=jsonTemp[j];
        }

        for(int j=0;j<16;j++){
            requestFrame[1007+j]=md5[j];
        }
        requestFrame[1023] = end;
        sendBySocket(requestFrame);
    }
    return true;
}

void Instrument::setProcessReagentVect(QVector<ProcessReagentModel> processReagentVect)
{
    _pTime->setProcessReagentVect(processReagentVect);
}

const QMap<int, QString> &Instrument::getGroupMap()
{
    return _pTime->getGroupMap();
}

const QMap<int, int> &Instrument::getStepRunTime()
{
    return ActionModel::instance()->getStepRunTime();
}

void Instrument::setGroupMap(QMap<int, QString>& groupMap, const int companyId)
{
    _pTime->setGroupMap(groupMap, companyId);
}

/*void Instrument::maintain(eMaintainType etype)
{
    Function::setIsThreadStop(false);
    _functions->getMaintain()->setPumpVect(_pumpVect);
    _functions->getMaintain()->maintain(etype);
}*/

void Instrument::setReagentPosVolumnMap(const QMap<uchar, ushort> &reagentPosVolumnMap)
{
    _functions->getMaintain()->setReagentPosVolumnMap(reagentPosVolumnMap);
}

bool Instrument::getSerialPortIsOpen()
{
    return SerialPortDriver::instance()->isPortOpen();
}

void Instrument::onDataArrive(QByteArray datas)
{
    emit sglDataArrive(datas);
}

void Instrument::onWarnArrive(int code)
{
    emit sglAlarmInfo(code);
}

bool Instrument::send(unsigned char *cmd, unsigned int size) const
{
    return true;
    if (cmd == nullptr || size <= 0)
    {
        return false;
    }
    QByteArray data = QByteArray(reinterpret_cast<char *>(cmd), static_cast<int>(size));
    if (data.length() < 5)
    {
        return false;
    }
    //_port->writeData(data);
    return true;
}








