#include "AgeUnitDao.h"
#include "../Include/Comm/singleton.h"
#include "../Include/Model/baseSet/AgeUnitModel.h"
#include <QSqlQuery>
#include <QVariant>

AgeUnitDao::~AgeUnitDao()
{
}
AgeUnitDao::AgeUnitDao()
{
}

AgeUnitDao *AgeUnitDao::instance()
{
    return Singleton<AgeUnitDao>::instance();
}

QVector<AgeUnitDao::ptrModel> AgeUnitDao::getAllRows()
{
    if(_vect.isEmpty())
        getTable();
    return _vect;
}

void AgeUnitDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlstr="SELECT * FROM tageunit";
    if(!query.exec(sqlstr))
        return;
    QVector<ptrModel>tempVect;
    _vect.swap(tempVect);
    while (query.next())
    {
        ptrModel model(new AgeUnitModel);
        model->setID(query.value("ID").toUInt());
        model->setAgeName(query.value("AgeName").toString());
        model->setOrderNo(query.value("orderNo").toUInt());
        _vect.push_back(model);
    }
}

