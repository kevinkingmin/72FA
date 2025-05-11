#include "WardDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Comm/singleton.h"
#include "../Include/Model/baseSet/WardModel.h"

WardDao::WardDao()
{
}

WardDao::~WardDao()
{
}

void WardDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT ID,wardName,shortKey,remark FROM tward";
    if(!query.exec(sqlStr))
        return;
    QMap<uint,ptrModel>tempMap;
    _map.swap(tempMap);
    uint id=0;
    while (query.next())
    {
        ptrModel pm(new WardModel);
        id=query.value("ID").toUInt();
        pm->setID(id);
        pm->setWardName(query.value("wardName").toString());
        pm->setShortKey(query.value("shortKey").toString());
        pm->setRemark(query.value("remark").toString());
        _map.insert(id,pm);
    }
}

void WardDao::queryBindValue(QSqlQuery &query, WardDao::ptrModel pm)
{
    query.bindValue(":ID",pm->getID());
    query.bindValue(":wardName",pm->getWardName());
    query.bindValue(":shortKey",pm->getShortKey());
    query.bindValue(":remark",pm->getRemark());
}

WardDao *WardDao::instance()
{
    return Singleton<WardDao>::instance();
}

bool WardDao::deleteById(uint id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    if(id<=0)
        return false;
    QString sqlStr="delete from tward where ID = "+QString::number(id)+"";

    if(!query.exec(sqlStr))
        return false;

    if(_map.keys().contains(id))
        _map.remove(id);
    else
        getTable();

    return true;
}

bool WardDao::updateModel(WardDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    QString sqlStr="update tward set wardName=:wardName,shortKey=:shortKey,"
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

bool WardDao::insertModel(WardDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="insert into tward(wardName,shortKey,remark) values "
                   "(:wardName,:shortKey,:remark)";
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

QVector<WardDao::ptrModel> WardDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    return _map.values().toVector();
}
