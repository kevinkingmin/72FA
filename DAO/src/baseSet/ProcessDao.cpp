#include "ProcessDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Model/baseSet/ProcessModel.h"
#include "../Include/Comm/singleton.h"
#include <QSqlError>
#include <QDebug>

ProcessDao::ProcessDao()
{    
}

ProcessDao::~ProcessDao()
{
}

ProcessDao *ProcessDao::instance()
{
    return Singleton<ProcessDao>::instance();
}

// 获取所有行
QVector<ProcessModel> ProcessDao::getAllRows()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return {};

    QString sqlStr="SELECT * FROM tprocess";
    if(!query.exec(sqlStr)) return {};
    QVector<ProcessModel> tempVect;
    while (query.next())
    {
        ProcessModel model;
        model.setId(query.value("id").toInt());
        model.setProcessName(query.value("processName").toString());
        model.setRemark(query.value("remark").toString());
        model.setCompanyId(query.value("companyId").toInt());
        tempVect.push_back(model);
    }
    return tempVect;
}

// 根据id获取对象
bool ProcessDao::getModel(const int processId, ProcessModel& out)
{
    QVector<ProcessModel> tempVect;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr = QString("SELECT * FROM tprocess WHERE id = %1").arg(processId);
    if(!query.exec(sqlStr)) return false;
    if (query.next())
    {
        out.setId(query.value("id").toInt());
        out.setProcessName(query.value("processName").toString());
        out.setRemark(query.value("remark").toString());
        out.setCompanyId(query.value("companyId").toInt());
    }
    return true;
}

// 根据删除对象
bool ProcessDao::deleteModel(const int processId)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;
    QString sqlStr = QString("DELETE FROM tprocess WHERE id = %1;").arg(processId);
    if (!query.exec(sqlStr)) return false;
    return true;
}


QVector<ProcessModel> ProcessDao::getModelsFromSystemSet()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return {};
    query.prepare("SELECT saveSet FROM tsystemset WHERE id = 5 LIMIT 1");
    if(!query.exec())
    {
        qWarning() << "SQL exec failed:" << query.lastError().text();
        return {};
    }
    int companyId = 0;
    if (query.next())
    {
        companyId = query.value("saveSet").toInt();
    }
    return getModels(companyId);
}


QVector<ProcessModel> ProcessDao::getModels(const int companyId)
{
    QVector<ProcessModel> tempVect;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return {};
    QString sqlStr = QString("SELECT * FROM tprocess WHERE companyId = %1").arg(companyId);
    if(!query.exec(sqlStr)) return {};
    while (query.next())
    {
        ProcessModel model;
        model.setId(query.value("id").toInt());
        model.setProcessName(query.value("processName").toString());
        model.setRemark(query.value("remark").toString());
        model.setCompanyId(query.value("companyId").toInt());
        tempVect.push_back(model);
    }
    return tempVect;
}

// 插入新数据
bool ProcessDao::insert(const int companyId, const QString& processName)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;

    QString sqlStr = QString("INSERT INTO tprocess (companyId, processName) VALUES (%1, '%2')").arg(companyId).arg(processName);
    if(!query.exec(sqlStr)) return false;
    return true;
}
