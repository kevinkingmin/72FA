#include "RemarkModel.h"

RemarkModel::RemarkModel():
    _ID(0)
  , _strRemark("")
  , _RemarkRK("")
  , _shortKey("")
{
}

uint RemarkModel::getID() const
{
    return _ID;
}

void RemarkModel::setID(const uint &ID)
{
    _ID = ID;
}

QString RemarkModel::getStrRemark() const
{
    return _strRemark;
}

void RemarkModel::setStrRemark(const QString &strRemark)
{
    _strRemark = strRemark;
}

QString RemarkModel::getShortKey() const
{
    return _shortKey;
}

void RemarkModel::setShortKey(const QString &shortKey)
{
    _shortKey = shortKey;
}

QString RemarkModel::getRemarkRK() const
{
    return _RemarkRK;
}

void RemarkModel::setRemarkRK(const QString &RemarkRK)
{
    _RemarkRK = RemarkRK;
}
