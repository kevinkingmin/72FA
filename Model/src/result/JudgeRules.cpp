#include "JudgeRules.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QDebug>
JudgeRules::JudgeRules()
    :_pkid(0)
    ,_ruleName("")
    ,_parameter({})
{

}

int JudgeRules::getpkid() const
{
	return _pkid;
}
void JudgeRules::setpkid(int pkid)
{
	_pkid = pkid;
}

QString JudgeRules::getRuleName() const
{
    return _ruleName;
}

void JudgeRules::setRuleName(QString name)
{
    _ruleName = name;
}

bool JudgeRules::strToParameter(const QString &str)
{
    if(str.isNull() || str.isEmpty()) return false;
    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &parse_error);
    if (document.isNull() ||(parse_error.error != QJsonParseError::NoError)) return false;
    auto array = document.array();
    _parameter.clear();
    for (auto it : array)
    {
        JudgeRules::ParameterStrt strt;
        strt._k = it.toObject().value("k").toString();
        strt._v =it.toObject().value("v").toDouble();
        _parameter.push_back(strt);
    }
    return true;
}

QString JudgeRules::parameterToStr()
{
    if(_parameter.empty())return "";
    QJsonArray array;
    int i=0;
    for(auto it:_parameter)
    {
        QJsonObject obj;
        obj.insert("k",it._k);
        obj.insert("v",it._v);
        array.insert(i,obj);
        i++;
    }
    QJsonDocument doc;
    doc.setArray(array);
    QString jsonStr=doc.toJson(QJsonDocument::Compact);
    return jsonStr;
}


QVector<JudgeRules::ParameterStrt> JudgeRules::getParameter()
{
    return _parameter;
}

void JudgeRules::setParameter(QVector<JudgeRules::ParameterStrt> parameter)
{
    _parameter = parameter;
}

// 参数是否重复 true重复 false未重复
bool JudgeRules::hasParameterDuplicates(QVector<JudgeRules::ParameterStrt> parameter)
{
    QSet<ParameterStrt> seen;
    for (const auto& param : parameter)
    {
        if (seen.contains(param))
        {
            return true; // 找到重复项
        }
        seen.insert(param);
    }
    return false;
}
