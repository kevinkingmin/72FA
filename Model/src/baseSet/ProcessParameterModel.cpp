#include "ProcessParameterModel.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QVariant>

const QString ProcessParameterModel::ADD_REAGENT_CODE = "L1901";
const QString ProcessParameterModel::BED_SHAKING_CODE = "L1902";
const QString ProcessParameterModel::DRYING_CODE = "L1903";
const QString ProcessParameterModel::SAMPLING_CODE = "L1904";
const QString ProcessParameterModel::DRAINING_CODE = "L1905";
const QString ProcessParameterModel::PAUSING_CODE = "L1906";

ProcessParameterModel::ProcessParameterModel()
    :_id(0)
    ,_processId(0)
    ,_actType("")
    ,_actName("")
    ,_actCode("")
    ,_paras("")
    ,_paramParseSuccess(false)
    ,_addReagentStrt(false, 2000, "加试剂", 100, false, 0)
    ,_bedShakingStrt(0,0)
    ,_drainingStrt(0)
    ,_pausingStrt("")
    ,_samplingStrt(0)
    ,_dryingStrt(1000, 2, 1000, 37, 1000)
{
}

int ProcessParameterModel::getId() const
{
    return _id;
}

void ProcessParameterModel::setId(int id)
{
    _id = id;
}

int ProcessParameterModel::getProcessId() const
{
    return _processId;
}

void ProcessParameterModel::setProcessId(int processId)
{
    _processId = processId;
}

QString ProcessParameterModel::getActType() const
{
    return _actType;
}

void ProcessParameterModel::setActType(const QString &actType)
{
    _actType = actType;
}

QString ProcessParameterModel::getActName() const
{
    return _actName;
}

void ProcessParameterModel::setActName(const QString &actName)
{
    _actName = actName;
}

QString ProcessParameterModel::getActCode() const
{
    return _actCode;
}

void ProcessParameterModel::setActCode(const QString &actCode)
{
    _actCode = actCode;
}

bool ProcessParameterModel::strToAddReagent(ProcessParameterModel::AddReagentStrt& out, const QString &str)
{
    if(str.isNull() || str.isEmpty()) return false;
    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &parse_error);
    if (document.isNull() ||(parse_error.error != QJsonParseError::NoError)) return false;
    auto obj = document.object();
    out._reagentName=obj.value("reagentName").toString();
    out._reagentMl=obj.value("reagentMl").toDouble();
    out._isBackFlow=obj.value("isBackFlow").toBool();
    out._backFlowMl=obj.value("backFlowMl").toDouble();
    out._isDrainWaster=obj.value("isDrainWaster").toBool();
    out._drainTime=obj.value("drainTime").toDouble();
    return true;
}

QString ProcessParameterModel::AddReagentToStr(const AddReagentStrt &strt)
{
    QJsonObject obj;
    obj.insert("reagentName",strt._reagentName);
    obj.insert("reagentMl",strt._reagentMl);
    obj.insert("isBackFlow",strt._isBackFlow);
    obj.insert("backFlowMl",strt._backFlowMl);
    obj.insert("isDrainWaster",strt._isDrainWaster);
    obj.insert("drainTime",strt._drainTime);

    QJsonDocument doc;
    doc.setObject(obj);
    QString jsonStr=doc.toJson(QJsonDocument::Compact);
    return jsonStr;
}

bool ProcessParameterModel::strToDraining(ProcessParameterModel::DrainingStrt& out, const QString &str)
{
    if(str.isNull() || str.isEmpty()) return false;
    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &parse_error);
    if (document.isNull() ||(parse_error.error != QJsonParseError::NoError)) return false;
    auto obj = document.object();
    out._drainTime=obj.value("drainTime").toDouble();
    return true;
}

QString ProcessParameterModel::drainingToStr(const DrainingStrt &strt)
{
    QJsonObject obj;
    obj.insert("drainTime",strt._drainTime);

    QJsonDocument doc;
    doc.setObject(obj);
    QString jsonStr=doc.toJson(QJsonDocument::Compact);
    return jsonStr;
}

bool ProcessParameterModel::strToPausing(ProcessParameterModel::PausingStrt& out, const QString &str)
{
    if(str.isNull() || str.isEmpty()) return false;
    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &parse_error);
    if (document.isNull() ||(parse_error.error != QJsonParseError::NoError)) return false;
    auto obj = document.object();
    out._notifyMessage=obj.value("notifyMessage").toString();
    return true;
}

QString ProcessParameterModel::PausingToStr(PausingStrt &strt)
{
    QJsonObject obj;
    obj.insert("notifyMessage",strt._notifyMessage);

    QJsonDocument doc;
    doc.setObject(obj);
    QString jsonStr=doc.toJson(QJsonDocument::Compact);
    return jsonStr;
}

bool ProcessParameterModel::strToSampling(ProcessParameterModel::SamplingStrt& out, const QString &str)
{
    if(str.isNull() || str.isEmpty()) return false;
    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &parse_error);
    if (document.isNull() ||(parse_error.error != QJsonParseError::NoError)) return false;
    auto obj = document.object();
    out._sampleUl=obj.value("sampleUl").toDouble();
    return true;
}
QString ProcessParameterModel::SamplingToStr(const SamplingStrt &strt)
{
    QJsonObject obj;
    obj.insert("sampleUl",strt._sampleUl);

    QJsonDocument doc;
    doc.setObject(obj);
    QString jsonStr=doc.toJson(QJsonDocument::Compact);
    return jsonStr;
}

bool ProcessParameterModel::strToBedShaking(ProcessParameterModel::BedShakingStrt& out, const QString &str)
{
    if(str.isNull() || str.isEmpty()) return false;
    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &parse_error);
    if (document.isNull() ||(parse_error.error != QJsonParseError::NoError)) return false;
    auto obj = document.object();
    out._shakeTime=obj.value("shakeTime").toDouble();
    out._bedTemperature=obj.value("bedTemperature").toDouble();
    return true;
}

QString ProcessParameterModel::BedShakingToStr(const BedShakingStrt &strt)
{
    QJsonObject obj;
    obj.insert("shakeTime",strt._shakeTime);
    obj.insert("bedTemperature",strt._bedTemperature);

    QJsonDocument doc;
    doc.setObject(obj);
    QString jsonStr=doc.toJson(QJsonDocument::Compact);
    return jsonStr;
}

bool ProcessParameterModel::strToDrying(ProcessParameterModel::DryingStrt& out, const QString &str)
{
    if(str.isNull() || str.isEmpty()) return false;
    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &parse_error);
    if (document.isNull() ||(parse_error.error != QJsonParseError::NoError)) return false;
    auto obj = document.object();
    out._dryTime=obj.value("dryTime").toDouble();
    out._fanTime=obj.value("fanTime").toDouble();
    out._fanLevel=obj.value("fanLevel").toInt();
    out._bedTime=obj.value("bedTime").toDouble();
    out._bedTemperature=obj.value("bedTemperature").toDouble();
    return true;
}

QString ProcessParameterModel::dryingToStr(const DryingStrt &strt)
{
    QJsonObject obj;
    obj.insert("dryTime",strt._dryTime);
    obj.insert("fanTime",strt._fanTime);
    obj.insert("fanLevel",strt._fanLevel);
    obj.insert("bedTime",strt._bedTime);
    obj.insert("bedTemperature",strt._bedTemperature);

    QJsonDocument doc;
    doc.setObject(obj);
    QString jsonStr=doc.toJson(QJsonDocument::Compact);
    return jsonStr;
}

bool ProcessParameterModel::parsingParas()
{
    if(_actCode == ADD_REAGENT_CODE)
    {
        _paramParseSuccess = strToAddReagent(_addReagentStrt, _paras);
    }else if(_actCode == BED_SHAKING_CODE)
    {
        _paramParseSuccess = strToBedShaking(_bedShakingStrt, _paras);
    }else if (_actCode == DRYING_CODE)
    {
        _paramParseSuccess = strToDrying(_dryingStrt, _paras);
    }else if(_actCode == SAMPLING_CODE)
    {
        _paramParseSuccess = strToSampling(_samplingStrt, _paras);
    }else if(_actCode == DRAINING_CODE)
    {
        _paramParseSuccess = strToDraining(_drainingStrt, _paras);
    }else if(_actCode == PAUSING_CODE)
    {
        _paramParseSuccess = strToPausing(_pausingStrt, _paras);
    }
    return _paramParseSuccess;
}


QString ProcessParameterModel::getParas()
{
    return _paras;
}

void ProcessParameterModel::setParas(QString &str)
{
    _paras = str;
}

bool ProcessParameterModel::getAddReagent(ProcessParameterModel::AddReagentStrt &out)
{
    if(!_paramParseSuccess || _actCode!=ADD_REAGENT_CODE)
    {
        return false;
    }
    out = _addReagentStrt;
    return true;
}

void ProcessParameterModel::setAddReagent(const ProcessParameterModel::AddReagentStrt &strt)
{
    _paras = AddReagentToStr(strt);
}

bool ProcessParameterModel::getDraining(ProcessParameterModel::DrainingStrt &out)
{
    if(!_paramParseSuccess || _actCode!=DRAINING_CODE)
    {
        return false;
    }
    out = _drainingStrt;
    return true;
}

void ProcessParameterModel::setDraining(const ProcessParameterModel::DrainingStrt &strt)
{
    _paras = drainingToStr(strt);
}

bool ProcessParameterModel::getPausing(ProcessParameterModel::PausingStrt &out)
{
    if(!_paramParseSuccess || _actCode!=PAUSING_CODE)
    {
        return false;
    }
    out = _pausingStrt;
    return true;
}

void ProcessParameterModel::setPausing(ProcessParameterModel::PausingStrt &strt)
{
    _paras = PausingToStr(strt);
}

bool ProcessParameterModel::getSampling(ProcessParameterModel::SamplingStrt &out)
{
    if(!_paramParseSuccess || _actCode!=SAMPLING_CODE)
    {
        return false;
    }
    out = _samplingStrt;
    return true;
}

void ProcessParameterModel::setSampling(const ProcessParameterModel::SamplingStrt &strt)
{
    _paras = SamplingToStr(strt);
}

bool ProcessParameterModel::getBedShaking(ProcessParameterModel::BedShakingStrt &out)
{
    if(!_paramParseSuccess || _actCode!=BED_SHAKING_CODE)
    {
        return false;
    }
    out = _bedShakingStrt;
    return true;
}

void ProcessParameterModel::setBedShaking(const ProcessParameterModel::BedShakingStrt &strt)
{
    _paras = BedShakingToStr(strt);
}

bool ProcessParameterModel::getDrying(ProcessParameterModel::DryingStrt &out)
{
    if(!_paramParseSuccess || _actCode!=DRYING_CODE)
    {
        return false;
    }
    out = _dryingStrt;
    return true;
}

void ProcessParameterModel::setDrying(const ProcessParameterModel::DryingStrt &strt)
{
    _paras = dryingToStr(strt);
}

// 界面显示的string
QString ProcessParameterModel::toShowString()
{
    QString show = "";
    show += "步骤:";
    show += _actName;
    show+=";";
    if(_actCode == ADD_REAGENT_CODE)
    {
        show+="试剂名称:";
        show+=_addReagentStrt._reagentName;
        show+=";";
        show+="试剂量:";
        show+=QString::number(_addReagentStrt._reagentMl,'f', 2);
        show+="ml;";
        show+="排废液:";
        show+=_addReagentStrt._isDrainWaster?"是":"否";
        show+=";";
        show+="时间:";
        show+=QString::number(_addReagentStrt._drainTime, 'f', 1);
        show+="s;";
        show+="回流:";
        show+=_addReagentStrt._isBackFlow?"是":"否";
        show+=";";
        show+="体积:";
        show+=QString::number(_addReagentStrt._backFlowMl, 'f', 2);
        show+="ml;";
    }else if(_actCode == BED_SHAKING_CODE)
    {
        show+="孵育时间:";
        show+=QString::number(_bedShakingStrt._shakeTime, 'f', 1);
        show+="s;";
        show+="摇床温度:";
        show+=QString::number(_bedShakingStrt._bedTemperature, 'f', 1);
        show+="℃;";

    }else if (_actCode == DRYING_CODE)
    {
        show+="干燥总时间:";
        show+=QString::number(_dryingStrt._dryTime, 'f', 1);
        show+="s;";
        show+="风扇时间:";
        show+=QString::number(_dryingStrt._fanTime, 'f', 1);
        show+="s;";
        show+="风扇等级:";
        show+=QString::number(_dryingStrt._fanLevel);
        show+="摇床时间:";
        show+=QString::number(_dryingStrt._bedTime, 'f', 1);
        show+="s;";
        show+="摇床温度:";
        show+=QString::number(_dryingStrt._bedTemperature, 'f', 1);
        show+="℃;";
    }else if(_actCode == SAMPLING_CODE)
    {
        show+="样本量:";
        show+=QString::number(_samplingStrt._sampleUl, 'f', 1);
        show+="ul;";
    }else if(_actCode == DRAINING_CODE)
    {
        show+="排废液时间:";
        show+=QString::number(_drainingStrt._drainTime, 'f', 1);
        show+="s;";

    }else if(_actCode == PAUSING_CODE)
    {
        show+="暂停流程, 上报信息:";
        show+=_pausingStrt._notifyMessage;
    }
    return show;
}

