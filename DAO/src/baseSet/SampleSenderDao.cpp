#include "SampleSenderDao.h"
#include <QSqlQuery>
#include "../../Include/Comm/singleton.h"
#include "../../Include/Model/baseSet/SampleSenderModel.h"

SampleSenderDao::SampleSenderDao()
{
}

SampleSenderDao::~SampleSenderDao()
{
}

void SampleSenderDao::queryBindValue(QSqlQuery &query, SampleSenderDao::prtModel pm)
{
    query.bindValue(":ID",pm->getID());
    query.bindValue(":senderName",pm->getSenderName());
    query.bindValue(":shortKey",pm->getShortKey());
    query.bindValue(":remark",pm->getRemark());
}

void SampleSenderDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT ID,senderName,shortKey,remark FROM tsample_sender";
    if(!query.exec(sqlStr))
        return;
    QMap<uint,prtModel>tempMap;
    _map.swap(tempMap);
    while (query.next())
    {
        prtModel pm(new SampleSenderModel);
        pm->setID(query.value("ID").toUInt());
        pm->setSenderName(query.value("senderName").toString());
        pm->setShortKey(query.value("shortKey").toString());
        pm->setRemark(query.value("remark").toString());
        _map.insert(pm->getID(),pm);
    }
}

SampleSenderDao *SampleSenderDao::instance()
{
    return Singleton<SampleSenderDao>::instance();
}

bool SampleSenderDao::deleteById(uint id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    if(id<=0)
        return false;
    QString sqlStr="delete from tsample_sender where ID = "+QString::number(id)+"";

    if(!query.exec(sqlStr))
        return false;

    if(_map.keys().contains(id))
        _map.remove(id);
    else
        getTable();

    return true;
}

bool SampleSenderDao::updateModel(SampleSenderDao::prtModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    QString sqlStr="update tsample_sender set senderName=:senderName,shortKey=:shortKey,remark=:remark where ID=:ID";
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

bool SampleSenderDao::insertModel(SampleSenderDao::prtModel pm)
{

    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    QString sqlStr="insert into tsample_sender(senderName,shortKey,remark) values (:senderName,:shortKey,:remark)";
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

QVector<SampleSenderDao::prtModel> SampleSenderDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    return _map.values().toVector();
}
