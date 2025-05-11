#include "UserGroupDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Model/user/UserGroupModel.h"
#include "../Include/Comm/singleton.h"


UserGroupDao::UserGroupDao()
{
}

UserGroupDao::~UserGroupDao()
{
}

void UserGroupDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;

    QString sqlStr="SELECT ID,GroupName,EnableAddOrDelete,EnableChangePassword FROM tusergroup";
    if(!query.exec(sqlStr))
        return;
    QVector<ptrModel> tempVect;
    _vect.swap(tempVect);
    while (query.next())
    {
        ptrModel pm(new UserGroupModel);
        pm->setID(query.value("ID").toUInt());
        pm->setGroupName(query.value("GroupName").toString());
        pm->setEnableAddOrDelete(query.value("EnableAddOrDelete").toUInt()>0?true:false);
        pm->setEnableChangePassword(query.value("EnableChangePassword").toUInt()>0?true:false);
        _vect.push_back(pm);
    }
}

UserGroupDao *UserGroupDao::instance()
{
    return Singleton<UserGroupDao>::instance();
}

QVector<UserGroupDao::ptrModel> UserGroupDao::getAllRows()
{
    if(_vect.isEmpty())
        getTable();
    return _vect;
}
