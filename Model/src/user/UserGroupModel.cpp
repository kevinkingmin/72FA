#include "UserGroupModel.h"

UserGroupModel::UserGroupModel():
    _ID(0)
  ,_GroupName("")
  ,_EnableAddOrDelete(false)
  ,_EnableChangePassword(false)
{
}

uint UserGroupModel::getID() const
{
    return _ID;
}

void UserGroupModel::setID(const uint &ID)
{
    _ID = ID;
}

QString UserGroupModel::getGroupName() const
{
    return _GroupName;
}

void UserGroupModel::setGroupName(const QString &GroupName)
{
    _GroupName = GroupName;
}

bool UserGroupModel::getEnableAddOrDelete() const
{
    return _EnableAddOrDelete;
}

void UserGroupModel::setEnableAddOrDelete(bool EnableAddOrDelete)
{
    _EnableAddOrDelete = EnableAddOrDelete;
}

bool UserGroupModel::getEnableChangePassword() const
{
    return _EnableChangePassword;
}

void UserGroupModel::setEnableChangePassword(bool EnableChangePassword)
{
    _EnableChangePassword = EnableChangePassword;
}
