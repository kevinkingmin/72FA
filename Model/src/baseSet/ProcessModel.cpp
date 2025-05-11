#include "ProcessModel.h"

ProcessModel::ProcessModel():
     _id(0)
     ,_pName("")
     ,_remark("")
     ,_isDefault(false)
     ,_addUser("")
     ,_addTime(0)
{

}

int ProcessModel::getId() const
{
    return _id;
}

void ProcessModel::setId(int id)
{
    _id = id;
}

QString ProcessModel::getPName() const
{
    return _pName;
}

void ProcessModel::setPName(const QString &pName)
{
    _pName = pName;
}

QString ProcessModel::getRemark() const
{
    return _remark;
}

void ProcessModel::setRemark(const QString &remark)
{
    _remark = remark;
}

bool ProcessModel::getIsDefault() const
{
    return _isDefault;
}

void ProcessModel::setIsDefault(bool isDefault)
{
    _isDefault = isDefault;
}

QString ProcessModel::getAddUser() const
{
    return _addUser;
}

void ProcessModel::setAddUser(const QString &addUser)
{
    _addUser = addUser;
}

qint64 ProcessModel::getAddTime() const
{
    return _addTime;
}

void ProcessModel::setAddTime(const qint64 &addTime)
{
    _addTime = addTime;
}
