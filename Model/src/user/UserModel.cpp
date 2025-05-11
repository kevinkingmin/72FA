#include "UserModel.h"

UserModel::UserModel():
    _ID(0)
  ,_GroupID(0)
  ,_LoginName("")
  ,_uPassword("")
  ,_showName("")
  ,_addUser("")
  ,_addTime(0)
  ,_isDelete(false)
{
}

uint UserModel::getID() const
{
    return _ID;
}

void UserModel::setID(const uint &ID)
{
    _ID = ID;
}

uint UserModel::getGroupID() const
{
    return _GroupID;
}

void UserModel::setGroupID(const uint &GroupID)
{
    _GroupID = GroupID;
}

QString UserModel::getLoginName() const
{
    return _LoginName;
}

void UserModel::setLoginName(const QString &LoginName)
{
    _LoginName = LoginName;
}

QString UserModel::getUPassword() const
{
    return _uPassword;
}

void UserModel::setUPassword(const QString &uPassword)
{
    _uPassword = uPassword;
}

QString UserModel::getShowName() const
{
    return _showName;
}

void UserModel::setShowName(const QString &showName)
{
    _showName = showName;
}

QString UserModel::getAddUser() const
{
    return _addUser;
}

void UserModel::setAddUser(const QString &addUser)
{
    _addUser = addUser;
}

quint64 UserModel::getAddTime() const
{
    return _addTime;
}

void UserModel::setAddTime(const quint64 &addTime)
{
    _addTime = addTime;
}

bool UserModel::getIsDelete() const
{
    return _isDelete;
}

void UserModel::setIsDelete(bool isDelete)
{
    _isDelete = isDelete;
}
