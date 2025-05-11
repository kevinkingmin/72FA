#include "ProcessParaModel.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QVariant>

ProcessParaModel::ProcessParaModel()
    :_id(0)
    ,_companyId(0)
    ,_groupId(0)
    ,_groupName("")
    ,_groupNameCode("")
    ,_stepName("")
    ,_stepNameCode("")
    ,_actIndex(0)
    ,_actId(0)
    ,_actName("")
    ,_actNameCode("")
    ,_isPopWindow(false)
    ,_popWindowDes("")
    ,_popWindowDesCode("")
    ,_paras{}
{
}

int ProcessParaModel::getId() const
{
    return _id;
}

void ProcessParaModel::setId(int id)
{
    _id = id;
}

int ProcessParaModel::getCompanyId() const
{
    return _companyId;
}

void ProcessParaModel::setCompanyId(int companyId)
{
    _companyId = companyId;
}

int ProcessParaModel::getGroupId() const
{
    return _groupId;
}

void ProcessParaModel::setGroupId(int groupId)
{
    _groupId = groupId;
}

QString ProcessParaModel::getGroupName() const
{
    return _groupName;
}

void ProcessParaModel::setGroupName(const QString &groupName)
{
    _groupName = groupName;
}

QString ProcessParaModel::getStepName() const
{
    return _stepName;
}

void ProcessParaModel::setStepName(const QString &stepName)
{
    _stepName = stepName;
}

int ProcessParaModel::getActIndex() const
{
    return _actIndex;
}

void ProcessParaModel::setActIndex(int index)
{
    _actIndex = index;
}

int ProcessParaModel::getActId() const
{
    return _actId;
}

void ProcessParaModel::setActId(int actId)
{
    _actId = actId;
}

QString ProcessParaModel::getActName() const
{
    return _actName;
}

void ProcessParaModel::setActName(const QString &actName)
{
    _actName = actName;
}

bool ProcessParaModel::getIsPopWindow() const
{
    return _isPopWindow;
}

void ProcessParaModel::setIsPopWindow(bool isPopWindow)
{
    _isPopWindow = isPopWindow;
}

QString ProcessParaModel::getPopWindowDes() const
{
    return _popWindowDes;
}

void ProcessParaModel::setPopWindowDes(const QString &popWindowDes)
{
    _popWindowDes = popWindowDes;
}

QVector<ProcessParaModel::ParaStrt> ProcessParaModel::getParas() const
{
    return _paras;
}

void ProcessParaModel::setParas(QString &str)
{
    auto vect = strToVect(str);
    _paras.swap(vect);
}

QVector<ProcessParaModel::ParaStrt> ProcessParaModel::strToVect(const QString &str)
{
    QVector<ParaStrt>vect;
    if(str.isNull() || str.isEmpty())
        return vect;
    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &parse_error);
    if (document.isNull() ||(parse_error.error != QJsonParseError::NoError))
        return vect;
    auto arr=document.array();
    for(auto it:arr)
    {
        ParaStrt m;
        m.id=it.toObject().value("id").toInt();
        m.paraName=it.toObject().value("paraName").toString();
        m.paraValue=it.toObject().value("paraValue").toDouble();
        vect.push_back(m);
    }
    return vect;
}

QString ProcessParaModel::vectToStr(const QVector<ProcessParaModel::ParaStrt> &vect)
{
    if(vect.empty())return "";
    QJsonArray array;
    int i=0;
    for(auto it:vect)
    {
        QJsonObject obj;
        obj.insert("id",it.id);
        obj.insert("paraName",it.paraName);
        obj.insert("paraValue",it.paraValue);
        array.insert(i,obj);
        i++;
    }
    QJsonDocument doc;
    doc.setArray(array);
    QString jsonStr=doc.toJson(QJsonDocument::Compact);
    return jsonStr;
}

QString ProcessParaModel::getPopWindowDesCode() const
{
    return _popWindowDesCode;
}

void ProcessParaModel::setPopWindowDesCode(const QString &popWindowDesCode)
{
    _popWindowDesCode = popWindowDesCode;
}

QString ProcessParaModel::getActNameCode() const
{
    return _actNameCode;
}

void ProcessParaModel::setActNameCode(const QString &actNameCode)
{
    _actNameCode = actNameCode;
}

QString ProcessParaModel::getStepNameCode() const
{
    return _stepNameCode;
}

void ProcessParaModel::setStepNameCode(const QString &stepNameCode)
{
    _stepNameCode = stepNameCode;
}

QString ProcessParaModel::getGroupNameCode() const
{
    return _groupNameCode;
}

void ProcessParaModel::setGroupNameCode(const QString &groupNameCode)
{
    _groupNameCode = groupNameCode;
}

