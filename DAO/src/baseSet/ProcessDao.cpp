#include "ProcessDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Model/baseSet/ProcessModel.h"
#include "../Include/Comm/singleton.h"

ProcessDao::ProcessDao()
{    
}

ProcessDao::~ProcessDao()
{
}

ProcessDao *ProcessDao::instance()
{
    return Singleton<ProcessDao>::instance();
}

QVector<ProcessDao::ptrModel> ProcessDao::getAllRows()
{
    if(_vect.isEmpty())
        getTable();
    return _vect;
}

void ProcessDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;

    QString sqlStr="SELECT * FROM tprocess";
    if(!query.exec(sqlStr))
        return;
    QVector<ptrModel> tempVect;
    _vect.swap(tempVect);
    while (query.next())
    {
        ptrModel pm(new ProcessModel);
        pm->setId(query.value("id").toInt());
        pm->setPName(query.value("pName").toString());
        pm->setRemark(query.value("remark").toString());
        pm->setIsDefault(query.value("isDefault").toInt()==0?false:true);
        pm->setAddUser(query.value("addUser").toString());
        pm->setAddTime(query.value("addTime").toLongLong());
        _vect.push_back(pm);
    }
}
