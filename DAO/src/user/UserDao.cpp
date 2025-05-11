#include "UserDao.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include "../Include/Comm/singleton.h"
#include "../Include/Model/user/UserModel.h"

UserDao::UserDao()
{
}

UserDao::~UserDao()
{
}

UserDao *UserDao::instance()
{
    return Singleton<UserDao>::instance();
}

QVector<UserDao::ptrModel> UserDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    return _map.values().toVector();
}

bool UserDao::deleteById(uint id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="delete from tuser where ID="+QString::number(id);
    if(!query.exec(sqlStr))
        return false;
    if(_map.keys().contains(id))
        _map.remove(id);
    else
        getTable();
    return true;
}

bool UserDao::updateModel(UserDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="update tuser set GroupID=:GroupID,LoginName=:LoginName,uPassword=:uPassword,"
                   "showName=:showName,addUser=:addUser,addTime=:addTime,isDelete=:isDelete where ID=:ID";
    query.prepare(sqlStr);
    queryBindValue(query,pm);
    if(!query.exec())
        return false;
    if(_map.keys().contains(pm->getID()))
        _map.insert(pm->getID(),pm);
    else
        getTable();
    return true;
}

bool UserDao::insertModel(UserDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="insert into tuser(GroupID,LoginName,uPassword,showName,addUser,addTime,isDelete) values"
                   "(:GroupID,:LoginName,:uPassword,:showName,:addUser,:addTime,:isDelete)";

    query.prepare(sqlStr);
    queryBindValue(query,pm);
    if(!query.exec())
        return false;
    if(_map.isEmpty())
        getTable();
    pm->setID(query.lastInsertId().toUInt());
    _map.insert(pm->getID(),pm);
    return true;
}

void UserDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT ID,GroupID,LoginName,uPassword,showName,addUser,addTime,isDelete FROM tuser";
    if(!query.exec(sqlStr))
        return;
    QMap<uint,ptrModel>tempMap;
    _map.swap(tempMap);
    while (query.next())
    {
        ptrModel pm(new UserModel);
        pm->setID(query.value("ID").toUInt());
        pm->setGroupID(query.value("GroupID").toUInt());
        pm->setLoginName(query.value("LoginName").toString());
        pm->setUPassword(query.value("uPassword").toString());
        pm->setShowName(query.value("showName").toString());
        pm->setAddUser(query.value("AddUser").toString());
        pm->setAddTime(query.value("AddTime").toULongLong());
        pm->setIsDelete(query.value("isDelete").toUInt()>0?true:false);
        _map.insert(pm->getID(),pm);
    }
}

void UserDao::queryBindValue(QSqlQuery &query, UserDao::ptrModel pm)
{
    query.bindValue(":ID",pm->getID());
    query.bindValue(":GroupID",pm->getGroupID());
    query.bindValue(":LoginName",pm->getLoginName());
    query.bindValue(":uPassword",pm->getUPassword());
    query.bindValue(":showName",pm->getShowName());
    query.bindValue(":addUser",pm->getAddUser());
    query.bindValue(":addTime",pm->getAddTime());
    query.bindValue(":isDelete",pm->getIsDelete()?1:0);
}

QSqlQuery UserDao::SelectRecord(bool *bResult, QString sql)
{
	QSqlQuery query;
	if (DAO::createQuery(query) < 0)
	{
		*bResult = false;
		return query;
	}
	QString strSql;
	strSql = sql;
	*bResult = query.exec(strSql);
	return query;
}
