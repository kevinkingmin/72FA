#include "BarCodeRule.h"
#include <QDateTime>
#include "../Include/Model/baseSet/ItemModel.h"
#include "../Include/Utilities/log.h"

QVector<int> BarCodeRule::_CodeTypeVect{enumReagent,enumCalibrate,enumCalCuve,enumQC,enumDiluent,enumSubstrate};
BarCodeRule::BarCodeRule()
    :_leader("")
    ,_barCodeType(0)
    ,_ItemID(0)
    ,_barCode("")
    ,_stability(0)
    ,_serialnumber("")
    ,_reagentClass(0)
{

}

QString BarCodeRule::getLeader() const
{
    return _leader;
}

void BarCodeRule::setLeader(const QString &leader)
{
    _leader = leader;
}

int BarCodeRule::getBarCodeType() const
{
    return _barCodeType;
}

void BarCodeRule::setBarCodeType(const int &barCodeType)
{
    _barCodeType = barCodeType;
}

int BarCodeRule::getItemID() const
{
    return _ItemID;
}

void BarCodeRule::setItemID(const int &ItemID)
{
    _ItemID = ItemID;
}

QString BarCodeRule::getBarCode() const
{
    return _barCode;
}

void BarCodeRule::setBarCode(const QString &barCode)
{
    _barCode = barCode;
}

qint64 BarCodeRule::getStability() const
{
    return _stability;
}

void BarCodeRule::setStability(const qint64 &stability)
{
    _stability = stability;
}

QString BarCodeRule::getSerialnumber() const
{
    return _serialnumber;
}

void BarCodeRule::setSerialnumber(const QString &serialnumber)
{
    _serialnumber = serialnumber;
}

int BarCodeRule::getReagentClass() const
{
    return _reagentClass;
}

void BarCodeRule::setReagentClass(const int &val)
{
    _reagentClass = val;
}
