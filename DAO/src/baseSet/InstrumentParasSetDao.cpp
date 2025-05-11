#include "InstrumentParasSetDao.h"
#include "../Include/Comm/singleton.h"
#include "../Include/Model/baseSet/InstrumentParasSetModel.h"
#include <QSqlQuery>
#include <QVariant>

InstrumentParasSetDao::InstrumentParasSetDao()
{
}

void InstrumentParasSetDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT * FROM tinstrument_paras_set";
    if(!query.exec(sqlStr))
        return;
    QMap<uint,InstrumentParasSetModel>tempMap;
    _map.swap(tempMap);
    uint id=0;
    while (query.next())
    {
        InstrumentParasSetModel m;
        id=query.value("ID").toUInt();
        m.setId(id);
        m.setRemark(query.value("remark").toString());
        m.setPreIntFileld1(query.value("preIntFileld1").toInt());
        QString str=query.value("paras").toString();
        m.setParas(str);
        _map.insert(id,m);
    }
}

InstrumentParasSetDao::~InstrumentParasSetDao()
{

}

InstrumentParasSetDao *InstrumentParasSetDao::instance()
{
    return  Singleton<InstrumentParasSetDao>::instance();
}

bool InstrumentParasSetDao::updateModel(InstrumentParasSetModel m)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="UPDATE tinstrument_paras_set SET paras=:paras,preIntFileld1=:preIntFileld1,remark=:remark WHERE id=:id";
    query.prepare(sqlStr);
    query.bindValue(":ID",m.getId());
    auto paraStr=m.vectToStr(m.getParas());
    query.bindValue(":paras",paraStr);
    query.bindValue(":preIntFileld1",m.getPreIntFileld1());
    query.bindValue(":remark",m.getRemark());
    if(!query.exec())
        return false;

    if(_map.keys().contains(m.getId()))
        _map[m.getId()]=m;
    else
        getTable();
    return true;
}

QVector<InstrumentParasSetModel> InstrumentParasSetDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    return _map.values().toVector();
}
