#include "DepartmentModel.h"

DepartmentModel::DepartmentModel():
 _ID(0)
,_DepartmentName("")
,_shortKey("")
{
}

uint DepartmentModel::getID() const
{
    return _ID;
}

void DepartmentModel::setID(const uint &value)
{
    _ID = value;
}

QString DepartmentModel::getDepartmentName() const
{
    return _DepartmentName;
}

void DepartmentModel::setDepartmentName(const QString &value)
{
    _DepartmentName = value;
}

QString DepartmentModel::getShortKey() const
{
    return _shortKey;
}

void DepartmentModel::setShortKey(const QString &value)
{
    _shortKey = value;
}

QString DepartmentModel::getRemark() const
{
    return _remark;
}

void DepartmentModel::setRemark(const QString &remark)
{
    _remark = remark;
}
