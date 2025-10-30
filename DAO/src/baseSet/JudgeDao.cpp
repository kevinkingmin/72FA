#include "JudgeDao.h"
#include <QSqlQuery>
#include <QVariant>
#include <QMap>
#include <QDebug>
#include "../Include/Model/baseSet/ProcessModel.h"
#include "../Include/Comm/singleton.h"

JudgeDao::JudgeDao()
{    
}

JudgeDao::~JudgeDao()
{
}

JudgeDao *JudgeDao::instance()
{
    return Singleton<JudgeDao>::instance();
}

// 获取所有行
QVector<JudgeRules> JudgeDao::getAllRows()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return {};

    QString sqlStr="SELECT * FROM t_judge_rules";
    if(!query.exec(sqlStr)) return {};
    QVector<JudgeRules> tempVect;
    while (query.next())
    {
        JudgeRules model;
        model.setpkid(query.value("pkid").toInt());
        model.setRuleName(query.value("ruleName").toString());
        QString parameterStr = query.value("Parameter").toString();
        model.strToParameter(parameterStr);
        tempVect.push_back(model);
    }
    return tempVect;
}


// 获取名称
QVector<QString> JudgeDao::getAllNames()
{
    QVector<JudgeRules> rules = getAllRows();
    QVector<QString> names;
    for(JudgeRules& rule : rules)
    {
        names.push_back(rule.getRuleName());
    }
    return names;
}

// 根据id获取对象
bool JudgeDao::getModel(const int ruleId, JudgeRules& out)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr = QString("SELECT * FROM t_judge_rules WHERE pkid = %1").arg(ruleId);
    if(!query.exec(sqlStr)) return false;
    if (query.next())
    {
        out.setpkid(query.value("pkid").toInt());
        out.setRuleName(query.value("ruleName").toString());
        QString parameterStr = query.value("Parameter").toString();
        out.strToParameter(parameterStr);
    }
    return true;
}

// 插入新数据
bool JudgeDao::insert(JudgeRules& model)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0) return false;

    // 使用预处理语句进行插入
    query.prepare("INSERT INTO t_judge_rules (ruleName, Parameter) VALUES (?, ?)");
    query.addBindValue(model.getRuleName());
    query.addBindValue(model.parameterToStr());

    if (!query.exec()) {
        qDebug() << "Insert failed!";
        qDebug() << "Executed Query:" << query.executedQuery();
        return false;
    }
    // 🔥 获取刚插入记录的自增主键 ID
    QVariant lastId = query.lastInsertId();
    if (!lastId.isValid()) {
        qDebug() << "Failed to get last insert ID";
        return false;
    }
    // 将生成的 ID 设置回 model（假设你有 setId 方法）
    model.setpkid(lastId.toInt());
    return true;
}

// 更新数据
bool JudgeDao::update(JudgeRules &m)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;
    query.prepare("UPDATE t_judge_rules SET ruleName = ?, Parameter = ? WHERE pkid = ?");
    query.addBindValue(m.getRuleName());
    query.addBindValue(m.parameterToStr());
    query.addBindValue(m.getpkid());

    if (!query.exec())
    {
        qDebug() << "SQL Query:" << query.executedQuery();
        return false;
    }

    return true;
}


QMap<double, QString> JudgeDao::getJudgeValueMap(const QString itemName, const int paperId)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return {};
    QString sqlStr = QString("select * from t_judge_rules where RulesId = (select RulesId from titem where itemName = '%1' and TestPaperID =%2 LIMIT 1) order by GrayValue asc")
            .arg(itemName)
            .arg(paperId);
    if(!query.exec(sqlStr)) return {};

    QMap<double, QString> mapJudgeRules;
    if (!query.next()) return {};
    JudgeRules model;
    model.setpkid(query.value("pkid").toInt());
    model.setRuleName(query.value("ruleName").toString());
    QString parameterStr = query.value("Parameter").toString();
    if(!model.strToParameter(parameterStr))
    {
        return {};
    }
    for(JudgeRules::ParameterStrt& p : model.getParameter())
    {
        mapJudgeRules.insert(p._v, p._k);
    }
    return mapJudgeRules;
}


// 删除数据
bool JudgeDao::deleteModel(int id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;
    query.prepare("DELETE FROM t_judge_rules WHERE pkid = ?");
    query.addBindValue(id);

    if (!query.exec())
    {
        qDebug() << "SQL Query:" << query.executedQuery();
        return false;
    }

    return true;
}


