#include "AgeUnitModel.h"

AgeUnitModel::AgeUnitModel()
    :_ID(0)
    ,_AgeName("")
    ,_orderNo(0)
{

}

uint AgeUnitModel::getID() const
{
    return _ID;
}

void AgeUnitModel::setID(const uint &ID)
{
    _ID = ID;
}

QString AgeUnitModel::getAgeName() const
{
    return _AgeName;
}

void AgeUnitModel::setAgeName(const QString &AgeName)
{
    _AgeName = AgeName;
}

uint AgeUnitModel::getOrderNo() const
{
    return _orderNo;
}

void AgeUnitModel::setOrderNo(const uint &orderNo)
{
    _orderNo = orderNo;
}
