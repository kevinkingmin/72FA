#include "RemarkDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../../Include/Comm/singleton.h"
#include "../../Include/Model/baseSet/RemarkModel.h"

RemarkDao::RemarkDao()
{
}
RemarkDao::~RemarkDao()
{
}

void RemarkDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT ID,strRemark,RemarkRK,shortKey FROM tremark";
    if(!query.exec(sqlStr))
        return;
    QMap<uint,ptrModel>tempMap;
    _map.swap(tempMap);
    uint id=0;
    while (query.next())
    {
        ptrModel pm(new RemarkModel);
        id=query.value("ID").toUInt();
        pm->setID(id);
        pm->setStrRemark(query.value("strRemark").toString());
        pm->setShortKey(query.value("shortKey").toString());
        pm->setRemarkRK(query.value("RemarkRK").toString());
        _map.insert(id,pm);
    }
}

void RemarkDao::queryBindValue(QSqlQuery &query, RemarkDao::ptrModel pm)
{
    query.bindValue(":ID",pm->getID());
    query.bindValue(":strRemark",pm->getStrRemark());
    query.bindValue(":shortKey",pm->getShortKey());
    query.bindValue(":RemarkRK",pm->getRemarkRK());
}

RemarkDao *RemarkDao::instance()
{
    return Singleton<RemarkDao>::instance();
}

bool RemarkDao::deleteById(uint id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    if(id<=0)
        return false;
    QString sqlStr="delete from tremark where ID = "+QString::number(id)+"";

    if(!query.exec(sqlStr))
        return false;

    if(_map.keys().contains(id))
        _map.remove(id);
    else
        getTable();

    return true;
}

bool RemarkDao::updateModel(RemarkDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    QString sqlStr="update tremark set strRemark=:strRemark,shortKey=:shortKey,"
                   "RemarkRK=:RemarkRK where ID=:ID";
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

bool RemarkDao::insertModel(RemarkDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="insert into tremark(strRemark,RemarkRK,shortKey) values "
                   "(:strRemark,:RemarkRK,:shortKey)";
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

QVector<RemarkDao::ptrModel> RemarkDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    return _map.values().toVector();
}
