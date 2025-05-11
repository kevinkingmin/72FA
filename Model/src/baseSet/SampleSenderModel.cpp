#include "SampleSenderModel.h"

SampleSenderModel::SampleSenderModel():
    _ID(0)
  ,_senderName("")
  ,_shortKey("")
  ,_remark("")
{
}

uint SampleSenderModel::getID() const
{
    return _ID;
}

void SampleSenderModel::setID(const uint &ID)
{
    _ID = ID;
}

QString SampleSenderModel::getSenderName() const
{
    return _senderName;
}

void SampleSenderModel::setSenderName(const QString &senderName)
{
    _senderName = senderName;
}

QString SampleSenderModel::getShortKey() const
{
    return _shortKey;
}

void SampleSenderModel::setShortKey(const QString &shortKey)
{
    _shortKey = shortKey;
}

QString SampleSenderModel::getRemark() const
{
    return _remark;
}

void SampleSenderModel::setRemark(const QString &remark)
{
    _remark = remark;
}
