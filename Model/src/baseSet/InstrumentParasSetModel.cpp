#include "InstrumentParasSetModel.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QVariant>

InstrumentParasSetModel::InstrumentParasSetModel()
	:_id(0)
	, _paras{}
	, _preIntFileld1(0)
	, _remark("")
{

}

uint InstrumentParasSetModel::getId() const
{
    return _id;
}

void InstrumentParasSetModel::setId(const uint &id)
{
    _id = id;
}

QVector<InstrumentParasSetModel::paraStruct> InstrumentParasSetModel::getParas() const
{
    return _paras;
}

void InstrumentParasSetModel::setParas(QString &str)
{
    auto vect = strToVect(str);
    _paras.swap(vect);
}

int InstrumentParasSetModel::getPreIntFileld1() const
{
    return _preIntFileld1;
}

void InstrumentParasSetModel::setPreIntFileld1(int preIntFileld1)
{
    _preIntFileld1 = preIntFileld1;
}

QString InstrumentParasSetModel::getRemark() const
{
    return _remark;
}

void InstrumentParasSetModel::setRemark(const QString &remark)
{
    _remark = remark;
}

QVector<InstrumentParasSetModel::paraStruct> InstrumentParasSetModel::strToVect(const QString &str)
{
    QVector<paraStruct>vect;
    if(str.isNull() || str.isEmpty())
        return vect;
    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &parse_error);
    if (document.isNull() ||(parse_error.error != QJsonParseError::NoError))
        return vect;
    auto arr=document.array();
    for(auto it:arr)
    {
        paraStruct m;
        m.id=it.toObject().value("id").toInt();
        m.para=it.toObject().value("para").toDouble();
        m.paraName=it.toObject().value("paraName").toString();
        vect.push_back(m);
    }
    return vect;
}

QString InstrumentParasSetModel::vectToStr(QVector<InstrumentParasSetModel::paraStruct> vect)
{
    if(vect.empty())return "";
    QJsonArray array;
    int i=0;
    for(auto it:vect)
    {
        QJsonObject obj;
        obj.insert("id",it.id);
        obj.insert("para",it.para);
        obj.insert("paraName",it.paraName);
        array.insert(i,obj);
        i++;
    }
    QJsonDocument doc;
    doc.setArray(array);
    QString jsonStr=doc.toJson(QJsonDocument::Compact);
    return jsonStr;
}
