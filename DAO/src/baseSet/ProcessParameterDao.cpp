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

QVector<ProcessParameterDao::ptrModel> ProcessParameterDao::getAllRows(int companyId, const QString& processName)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
        return {};
    QString sqlStr = QString("SELECT * FROM tprocess_parameter WHERE companyId = %1 and processName='%2' ORDER BY id ASC").arg(companyId).arg(processName);
    if (!query.exec(sqlStr))
        return {};
    QVector<ptrModel>tempVect;
    QString paras = "";
    while (query.next())
    {
        ptrModel pm(new ProcessParameterModel);
        pm->setId(query.value("id").toInt());
        pm->setCompanyId(query.value("companyId").toInt());
        pm->setActName(query.value("actName").toString());
        pm->setActCode(query.value("actCode").toString());
        paras=query.value("paras").toString();
        pm->setParas(paras);
        tempVect.push_back(pm);
    }
    return tempVect;
}

// 根据公司ID筛选流程名称
QVector<QString> ProcessParameterDao::getProcessNameByCompany(int companyId)
{
    QVector<QString> processNames;
    QSet<QString> seen;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
        return {};
    QString sqlStr = "SELECT *  FROM tprocess_parameter where companyId = " + QString::number(companyId);
    if (!query.exec(sqlStr))
        return {};
    while (query.next())
    {
        QString name = query.value("processName").toString();
        if(!seen.contains(name))
        {
            seen.insert(name);
            processNames.append(name);
        }
    }
    return processNames;
}
