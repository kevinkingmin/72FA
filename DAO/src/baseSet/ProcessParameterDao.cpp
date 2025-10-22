#include "ProcessParameterDao.h"
#include <QSet>
#include <QDebug>
#include <QSqlQuery>
#include <QSettings>
#include <QFile>
#include <QTextCodec>
#include "../Include/Utilities/log.h"
#include "../Include/Model/baseSet/ProcessParameterModel.h"
#include "../Include/Database/Database.h"
#include "../Include/Comm/singleton.h"

ProcessParameterDao::ProcessParameterDao()
{
}

ProcessParameterDao::~ProcessParameterDao()
{
}

ProcessParameterDao *ProcessParameterDao::instance()
{
    return  Singleton<ProcessParameterDao>::instance();
}


bool ProcessParameterDao::selectModel(int stepId, ProcessParameterModel& out)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0) return false;
    QString sqlStr = QString("SELECT * FROM tprocess_parameter WHERE id = %1 ORDER BY id ASC").arg(stepId);
    if (!query.exec(sqlStr)) return false;
    QString paras = "";
    if (query.next())
    {
        out.setId(query.value("id").toInt());
        out.setProcessId(query.value("processId").toInt());
        out.setActType(query.value("actType").toString());
        out.setActName(query.value("actName").toString());
        out.setActCode(query.value("actCode").toString());
        paras=query.value("paras").toString();
        out.setParas(paras);
    }
    return true;
}

// 删除
bool ProcessParameterDao::delectModel(int stepId)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0) return false;
    QString sqlStr = QString("DELETE FROM tprocess_parameter WHERE id = %1;").arg(stepId);
    if (!query.exec(sqlStr)) return false;
    return true;
}

QVector<ProcessParameterModel> ProcessParameterDao::getAllRows(int processId)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0) return {};
    QString sqlStr = QString("SELECT * FROM tprocess_parameter WHERE processId = %1 ORDER BY id ASC").arg(processId);
    if (!query.exec(sqlStr)) return {};
    QVector<ProcessParameterModel> tempVect;
    QString paras = "";
    while (query.next())
    {
        ProcessParameterModel model;
        model.setId(query.value("id").toInt());
        model.setProcessId(query.value("processId").toInt());
        model.setActType(query.value("actType").toString());
        model.setActName(query.value("actName").toString());
        model.setActCode(query.value("actCode").toString());
        paras=query.value("paras").toString();
        model.setParas(paras);
        tempVect.push_back(model);
    }
    return tempVect;
}


bool ProcessParameterDao::insert(ProcessParameterModel& model)
{
    qDebug()<<"insert";
    QSqlQuery query;
    if (DAO::createQuery(query) < 0) return false;

    QString sqlStr = QString("INSERT INTO tprocess_parameter (processId, actType, actName, actCode, paras) VALUES (%1, '%2', '%3','%4','%5')")
            .arg(model.getProcessId())
            .arg(model.getActType())
            .arg(model.getActName())
            .arg(model.getActCode())
            .arg(model.getParas());
    if(!query.exec(sqlStr)) return false;
    return true;
}

bool ProcessParameterDao::update(int stepId, ProcessParameterModel& model)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0) return false;

    QString sqlStr = QString("UPDATE tprocess_parameter set processId = %1, actType='%2', actName='%3', actCode='%4', paras='%5' where id = %6")
            .arg(model.getProcessId())
            .arg(model.getActType())
            .arg(model.getActName())
            .arg(model.getActCode())
            .arg(model.getParas())
            .arg(stepId);
    if(!query.exec(sqlStr)) return false;
    return true;
}
