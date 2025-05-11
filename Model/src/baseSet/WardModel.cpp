#include "WardModel.h"

WardModel::WardModel():
    _ID(0)
  , _wardName("")
  , _shortKey("")
  , _remark("")
{
}

uint WardModel::getID() const
{
    return _ID;
}

void WardModel::setID(const uint &ID)
{
    _ID = ID;
}

QString WardModel::getWardName() const
{
    return _wardName;
}

void WardModel::setWardName(const QString &wardName)
{
    _wardName = wardName;
}

QString WardModel::getShortKey() const
{
    return _shortKey;
}

void WardModel::setShortKey(const QString &shortKey)
{
    _shortKey = shortKey;
}

QString WardModel::getRemark() const
{
    return _remark;
}

void WardModel::setRemark(const QString &remark)
{
    _remark = remark;
}
