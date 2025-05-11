#include "DiagnosisDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../../Include/Comm/singleton.h"
#include "../../Include/Model/baseSet/DiagnosisModel.h"

DiagnosisDao::DiagnosisDao()
{
}

DiagnosisDao::~DiagnosisDao()
{
}

void DiagnosisDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT ID,StrDiagnosis,shortKey,remark FROM tdiagnosis";
    if(!query.exec(sqlStr))
        return;
    QMap<uint,ptrModel>tempMap;
    _map.swap(tempMap);
    uint id=0;
    while (query.next())
    {
        ptrModel pm(new DiagnosisModel);
        id=query.value("ID").toUInt();
        pm->setID(id);
        pm->setStrDiagnosis(query.value("StrDiagnosis").toString());
        pm->setShortKey(query.value("shortKey").toString());
        pm->setRemark(query.value("remark").toString());
        _map.insert(id,pm);
    }
}

void DiagnosisDao::queryBindValue(QSqlQuery &query, DiagnosisDao::ptrModel pm)
{
    query.bindValue(":ID",pm->getID());
    query.bindValue(":StrDiagnosis",pm->getStrDiagnosis());
    query.bindValue(":shortKey",pm->getShortKey());
    query.bindValue(":remark",pm->getRemark());
}

DiagnosisDao *DiagnosisDao::instance()
{
    return  Singleton<DiagnosisDao>::instance();
}

bool DiagnosisDao::deleteById(uint id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    if(id<=0)
        return false;
    QString sqlStr="delete from tdiagnosis where ID = "+QString::number(id)+"";

    if(!query.exec(sqlStr))
        return false;

    if(_map.keys().contains(id))
        _map.remove(id);
    else
        getTable();

    return true;
}

bool DiagnosisDao::updateModel(DiagnosisDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    QString sqlStr="update tdiagnosis set StrDiagnosis=:StrDiagnosis,shortKey=:shortKey,"
                   "remark=:remark where ID=:ID";
    query.prepare(sqlStr);
    queryBindValue(query,pm);
    if(!query.exec())
        return false;
    if(_map.keys().contains(pm->getID()))
        _map[pm->getID()]=pm;
    else
        getTable();
    return true;
}

bool DiagnosisDao::insertModel(DiagnosisDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="insert into tdiagnosis(StrDiagnosis,shortKey,remark) values "
                   "(:StrDiagnosis,:shortKey,:remark)";
    query.prepare(sqlStr);
    queryBindValue(query,pm);
    if(!query.exec())
        return false;
    uint id=query.lastInsertId().toUInt();
    pm->setID(id);
    if(_map.isEmpty())
        getTable();
    _map.insert(id,pm);
    return true;
}

QVector<DiagnosisDao::ptrModel> DiagnosisDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    return _map.values().toVector();
}
