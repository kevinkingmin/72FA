#include "DepartmentDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../../Include/Comm/singleton.h"
#include "../../Include/Model/baseSet/DepartmentModel.h"

DepartmentDao::DepartmentDao()
{    
}

DepartmentDao::~DepartmentDao()
{
}

DepartmentDao *DepartmentDao::instance()
{
    return Singleton<DepartmentDao>::instance();
}

void DepartmentDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT ID,DepartmentName,shortKey,remark FROM tdepartment";
    if(!query.exec(sqlStr))
        return;
    QMap<uint,ptrModel>tempMap;
    _map.swap(tempMap);
    uint id=0;
    while (query.next())
    {
        ptrModel pm(new DepartmentModel);
        id=query.value("ID").toUInt();
        pm->setID(id);
        pm->setDepartmentName(query.value("DepartmentName").toString());
        pm->setShortKey(query.value("shortKey").toString());
        pm->setRemark(query.value("remark").toString());
        _map.insert(id,pm);
    }
}

void DepartmentDao::queryBindValue(QSqlQuery &query, DepartmentDao::ptrModel pm)
{
    query.bindValue(":ID",pm->getID());
    query.bindValue(":DepartmentName",pm->getDepartmentName());
    query.bindValue(":shortKey",pm->getShortKey());
    query.bindValue(":remark",pm->getRemark());
}

bool DepartmentDao::deleteById(uint id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    if(id<=0)
        return false;
    QString sqlStr="delete from tdepartment where id = "+QString::number(id)+"";

    if(!query.exec(sqlStr))
        return false;

    if(_map.keys().contains(id))
        _map.remove(id);
    else
        getTable();

    return true;
}

bool DepartmentDao::updateModel(DepartmentDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    QString sqlStr="update tdepartment set DepartmentName=:DepartmentName,shortKey=:shortKey,"
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

bool DepartmentDao::insertModel(DepartmentDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="insert into tdepartment(DepartmentName,shortKey,remark) values "
                   "(:DepartmentName,:shortKey,:remark)";
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

QVector<DepartmentDao::ptrModel> DepartmentDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    return _map.values().toVector();
}
