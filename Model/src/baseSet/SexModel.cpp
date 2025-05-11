#include "SexModel.h"

SexModel::SexModel():
    _ID(0)
  ,_SexName("")
  ,_orderNo(0)
{

}

uint SexModel::getID() const
{
    return _ID;
}

void SexModel::setID(const uint &ID)
{
    _ID = ID;
}

QString SexModel::getSexName() const
{
    return _SexName;
}

void SexModel::setSexName(const QString &SexName)
{
    _SexName = SexName;
}

uint SexModel::getOrderNo() const
{
    return _orderNo;
}

void SexModel::setOrderNo(const uint &orderNo)
{
    _orderNo = orderNo;
}
