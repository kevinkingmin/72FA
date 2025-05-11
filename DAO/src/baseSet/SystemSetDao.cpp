#include "SystemSetDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../../Include/Comm/singleton.h"
#include "../../Include/Model/baseSet/SystemSetModel.h"

SystemSetDao::SystemSetDao()
{
}

SystemSetDao::~SystemSetDao()
{
}

void SystemSetDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT id,saveSet,saveDes,remark FROM tsystemset";
    if(!query.exec(sqlStr))
        return;
    QMap<uint,ptrModel>tempMap;
    _map.swap(tempMap);
    uint id=0;
    while (query.next())
    {
        ptrModel pm(new SystemSetModel);
        id=query.value("id").toUInt();
        pm->setId(id);
        pm->setSaveSet(query.value("saveSet").toInt());
        pm->setSaveDes(query.value("saveDes").toString());
        pm->setRemark(query.value("remark").toString());
        _map.insert(id,pm);
    }
}

void SystemSetDao::queryBindValue(QSqlQuery &query, SystemSetDao::ptrModel pm)
{
    query.bindValue(":id",pm->getId());
    query.bindValue(":saveSet",pm->getSaveSet());
    query.bindValue(":saveDes",pm->getSaveDes());
    query.bindValue(":remark",pm->getRemark());
}

SystemSetDao *SystemSetDao::instance()
{
    return Singleton<SystemSetDao>::instance();
}

bool SystemSetDao::deleteById(uint id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    if(id<=0)
        return false;
    QString sqlStr="delete from tsystemset where id = "+QString::number(id)+"";

    if(!query.exec(sqlStr))
        return false;

    if(_map.keys().contains(id))
        _map.remove(id);
    else
        getTable();

    return true;
}

bool SystemSetDao::updateModel(SystemSetDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    QString sqlStr="update tsystemset set saveSet=:saveSet,saveDes=:saveDes,"
                   "remark=:remark where id=:id";
    query.prepare(sqlStr);
    queryBindValue(query,pm);
    if(!query.exec())
        return false;
    if(_map.keys().contains(pm->getId()))
        _map[pm->getId()]=pm;
    else
        getTable();
    return true;
}

QVector<SystemSetDao::ptrModel> SystemSetDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    return _map.values().toVector();
}
