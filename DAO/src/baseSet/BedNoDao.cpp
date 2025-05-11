#include "BedNoDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../../Include/Comm/singleton.h"
#include "../../Include/Model/baseSet/BedNoModel.h"

BedNoDao::BedNoDao()
{
}

BedNoDao::~BedNoDao()
{
}

void BedNoDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT ID,BedNoName,shortKey,remark FROM tbedno";
    if(!query.exec(sqlStr))
        return;
    QMap<uint,ptrModel>tempMap;
    _map.swap(tempMap);
    uint id=0;
    while (query.next())
    {
        ptrModel pm(new BedNoModel);
        id=query.value("ID").toUInt();
        pm->setID(id);
        pm->setBedNoName(query.value("BedNoName").toString());
        pm->setShortKey(query.value("shortKey").toString());
        pm->setRemark(query.value("remark").toString());
        _map.insert(id,pm);
    }
}

void BedNoDao::queryBindValue(QSqlQuery &query, BedNoDao::ptrModel pm)
{
    query.bindValue(":ID",pm->getID());
    query.bindValue(":BedNoName",pm->getBedNoName());
    query.bindValue(":shortKey",pm->getShortKey());
    query.bindValue(":remark",pm->getRemark());
}

BedNoDao *BedNoDao::instance()
{
    return Singleton<BedNoDao>::instance();
}

bool BedNoDao::deleteById(uint id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    if(id<=0)
        return false;
    QString sqlStr="delete from tbedno where id = "+QString::number(id)+"";

    if(!query.exec(sqlStr))
        return false;

    if(_map.keys().contains(id))
        _map.remove(id);
    else
        getTable();

    return true;
}

bool BedNoDao::updateModel(BedNoDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    QString sqlStr="update tbedno set BedNoName=:BedNoName,shortKey=:shortKey,"
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

bool BedNoDao::insertModel(BedNoDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="insert into tbedno(BedNoName,shortKey,remark) values "
                   "(:BedNoName,:shortKey,:remark)";
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

QVector<BedNoDao::ptrModel> BedNoDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    QVector<ptrModel> outVect;
    auto list = _map.values();
    for(auto it:list)
    {
        auto m=*it;
        ptrModel p(new BedNoModel(std::move(m)));
        outVect.push_back(p);
    }
    return outVect;
}
