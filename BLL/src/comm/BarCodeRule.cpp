#include "BarCodeRule.h"
#include <QDateTime>
#include "src/baseSet/ItemBll.h"
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

bool BarCodeRule::barCodeValidAndGet(const QString &barCode)
{    
    if(barCode.length()<32)
    {
        eLog("条码长度不对，length:{},barCode:{}",barCode.length(),barCode.toStdString());
        return false;
    }
    auto leader=barCode.mid(0,2);
    if(leader.compare("HC",Qt::CaseInsensitive))//匹配不能功
    {
        eLog("条码解析失败,leader:{}",leader.toStdString());
        return false;
    }

    _barCodeType=barCode.mid(2,2).toInt();
    if(!_CodeTypeVect.contains(_barCodeType))
    {
        eLog("条码解析失败,codeType:{}",_barCodeType);
        return false;
    }

    auto itemId=barCode.mid(4,5).toInt();
    auto vect=ItemBll().getAllRows();
    QVector<int>itemVect;
    for(auto it:vect)
        itemVect.push_back(it->getID());

    if(!itemVect.contains(itemId))
    {
        eLog("条码解析失败,id:{}",itemId);
        return false;
    }
    auto stability=QDateTime::fromString("20"+barCode.mid(24,6), "yyyyMMdd").toMSecsSinceEpoch();
	if (stability <= 10000)
	{
		eLog("时间格式错误！！");
		return false;
	}

    _leader=leader;
    _ItemID=itemId;
    _barCode=barCode.mid(9,10);
    _stability=stability;
    _serialnumber=barCode.mid(19,5);
    _reagentClass=barCode.mid(30,1).toInt();
    return true;
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

bool BarCodeRule::getReagentBarCode(const QString &barCode)
{
   if(!barCodeValidAndGet(barCode))
       return false;

   if(_barCodeType!=enumReagent)
       return false;

   if(_reagentClass!=enumR012 && _reagentClass!=enumR34)
       return false;

   return true;
}

bool BarCodeRule::getUniversalReagentBarCode(const QString &barCode)
{

    if(barCode.length()!=27)
    {
        eLog("条码长度不对，length:{},barCode:{}",barCode.length(),barCode.toStdString());
        return false;
    }

    auto leader=barCode.mid(0,2);
    if(leader.compare("HC",Qt::CaseInsensitive))//匹配不能功
    {
        eLog("条码解析失败,leader:{}",leader.toStdString());
        return false;
    }

    _barCodeType=barCode.mid(2,2).toInt();
    if(_barCodeType!=enumDiluent && _barCodeType!=enumSubstrate)
    {
        eLog("数据类型不对,type:{}",_barCodeType);
        return false;
    }

    auto stability=QDateTime::fromString("20"+barCode.mid(19,6), "yyyyMMdd").toMSecsSinceEpoch();
    if (stability <= 10000)
    {
        eLog("时间格式错误！！");
        return false;
    }

    _leader=leader;
    _ItemID=0;
    _barCode=barCode.mid(4,10);
    _stability=stability;
    _serialnumber=barCode.mid(14,5);
    _reagentClass=barCode.mid(25,1).toInt();

    if(_barCodeType!=enumDiluent && _barCodeType!=enumSubstrate)
        return false;

    if(_reagentClass!=1 && _reagentClass!=2)
        return false;

    return true;
}
