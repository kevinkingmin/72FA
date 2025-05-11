#include "ProcessStepModel.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QVariant>

ProcessStepModel::ProcessStepModel():
    _id(0)
  ,_tName("")
  ,_actTime(0)
  ,_remark("")
  ,_templateParas{}
{
}

int ProcessStepModel::getId() const
{
    return _id;
}

void ProcessStepModel::setId(int id)
{
    _id = id;
}

QString ProcessStepModel::getTName() const
{
    return _tName;
}

void ProcessStepModel::setTName(const QString &tName)
{
    _tName = tName;
}

int ProcessStepModel::getActTime() const
{
    return _actTime;
}

void ProcessStepModel::setActTime(int actTime)
{
    _actTime = actTime;
}

QString ProcessStepModel::getRemark() const
{
    return _remark;
}

void ProcessStepModel::setRemark(const QString &remark)
{
    _remark = remark;
}

QVector<ProcessStepModel::ParaStrt> ProcessStepModel::getTemplateParas() const
{
    return _templateParas;
}

void ProcessStepModel::setTemplateParas(const QString &&str)
{
    auto vect=strToVect(str);
    _templateParas.swap(vect);
}

QVector<ProcessStepModel::ParaStrt> ProcessStepModel::strToVect(const QString &str)
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

QString ProcessStepModel::vectToStr(const QVector<ProcessStepModel::ParaStrt> &vect)
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


