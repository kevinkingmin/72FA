#include "ProcessParaDao.h"
#include <QSqlQuery>
#include <QSettings>
#include <QFile>
#include <QTextCodec>
#include "../Include/Utilities/log.h"
#include "../Include/Model/baseSet/ProcessParaModel.h"
#include "../Include/Database/Database.h"
#include "../Include/Comm/singleton.h"

ProcessParaDao::ProcessParaDao()
{
}

void ProcessParaDao::getTable()
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
        return;
    QString sqlStr = "SELECT id,companyId,groupId,groupName,groupNameCode,stepName,stepNameCode,actIndex,actId,actName,actNameCode,isPopWindow,popWindowDes,popWindowDesCode,paras FROM tprocess_para";
    if (!query.exec(sqlStr))
        return;
    QVector<ptrModel>tempVect;
    _vect.swap(tempVect);
    QString paras = "";
    while (query.next())
    {
        ptrModel pm(new ProcessParaModel);
        pm->setId(query.value("id").toInt());
        pm->setCompanyId(query.value("companyId").toInt());
        pm->setGroupId(query.value("groupId").toInt());
        pm->setGroupName(query.value("groupName").toString());
        pm->setGroupNameCode(query.value("groupNameCode").toString());
        pm->setStepName(query.value("stepName").toString());
        pm->setStepNameCode(query.value("stepNameCode").toString());
        pm->setActIndex(query.value("actIndex").toInt());
        pm->setActId(query.value("actId").toInt());
        pm->setActName(query.value("actName").toString());
        pm->setActNameCode(query.value("actNameCode").toString());
        pm->setIsPopWindow(query.value("isPopWindow").toInt()>0);
        pm->setPopWindowDes(query.value("popWindowDes").toString());
        pm->setPopWindowDesCode(query.value("popWindowDesCode").toString());
        paras=query.value("paras").toString();
        pm->setParas(paras);
        _vect.push_back(pm);
    }
}

ProcessParaDao::~ProcessParaDao()
{
}

ProcessParaDao *ProcessParaDao::instance()
{
    return  Singleton<ProcessParaDao>::instance();
}

QVector<ProcessParaDao::ptrModel> ProcessParaDao::getAllRows()
{
    if (_vect.isEmpty())
        getTable();
    return _vect;
}
