#include "SexDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Model/baseSet/SexModel.h"
#include "../Include/Comm/singleton.h"

SexDao::SexDao()
{    
}

SexDao::~SexDao()
{
}

SexDao *SexDao::instance()
{
    return Singleton<SexDao>::instance();
}

QVector<SexDao::ptrModel> SexDao::getAllRows()
{
    if(_vect.isEmpty())
        getTable();
    return _vect;
}

void SexDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;

    QString sqlStr="SELECT ID,SexName,orderNo FROM tsex order by orderNo asc";
    if(!query.exec(sqlStr))
        return;
    QVector<ptrModel> tempVect;
    _vect.swap(tempVect);
    while (query.next())
    {
        ptrModel pm(new SexModel);
        pm->setID(query.value("ID").toUInt());
        pm->setSexName(query.value("SexName").toString());
        pm->setOrderNo(query.value("orderNo").toUInt());
        _vect.push_back(pm);
    }
}
