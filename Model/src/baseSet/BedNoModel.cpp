#include "BedNoModel.h"

BedNoModel::BedNoModel():
    _ID(0)
  , _BedNoName("")
  , _shortKey("")
  , _remark("")
{
}

uint BedNoModel::getID() const
{
    return _ID;
}

void BedNoModel::setID(const uint &ID)
{
    _ID = ID;
}

QString BedNoModel::getBedNoName() const
{
    return _BedNoName;
}

void BedNoModel::setBedNoName(const QString &BedNoName)
{
    _BedNoName = BedNoName;
}

QString BedNoModel::getShortKey() const
{
    return _shortKey;
}

void BedNoModel::setShortKey(const QString &shortKey)
{
    _shortKey = shortKey;
}

QString BedNoModel::getRemark() const
{
    return _remark;
}

void BedNoModel::setRemark(const QString &remark)
{
    _remark = remark;
}
