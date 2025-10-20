#include "ProcessDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Model/baseSet/ProcessModel.h"
#include "../Include/Comm/singleton.h"

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
