#include "ItemModel.h"


const int ItemModel::ITEM_TYPE_FUNC = 0; // 功能线
const int ItemModel::ITEM_TYPE_CUTOFF = 1; // cutoff线
const int ItemModel::ITEM_TYPE_ITEM = 2; // 项目线

ItemModel::ItemModel():
    _ID(0)
    ,_TestPaperID(0)
    ,_itemName("")
    ,_itemType(2)
    ,_segmentIndex(0)
    ,_PositionNo(0)
    ,_CurveId(0)
    ,_RulesId(0)
    ,_ResultOffset(0)
    ,_Position(0)
    ,_IsNull(0)
    ,_ItemFullName("")
{
}

int ItemModel::getID() const
{
    return _ID;
}

void ItemModel::setID(const int &ID)
{
    _ID = ID;
}

int ItemModel::getTestPaperID() const
{
    return _TestPaperID;
}

void ItemModel::setTestPaperID(int TestPaperID)
{
    _TestPaperID = TestPaperID;
}

QString ItemModel::getItemName() const
{
    return _itemName;
}

void ItemModel::setItemName(const QString &itemName)
{
    _itemName = itemName;
}

int ItemModel::getItemType() const
{
    return _itemType;
}

void ItemModel::setItemType(int itemType)
{
    _itemType = itemType;
}

int ItemModel::getSegmentIndex() const
{
    return _segmentIndex;
}

void ItemModel::setSegmentIndex(int segmentIndex)
{
    _segmentIndex = segmentIndex;
}

int ItemModel::getPositionNo() const
{
    return _PositionNo;
}

void ItemModel::setPositionNo(int PositionNo)
{
    _PositionNo = PositionNo;
}

bool ItemModel::getIsNull() const
{
    return _IsNull;
}

void ItemModel::setIsNull(bool IsNull)
{
    _IsNull = IsNull;
}


int ItemModel::getCurveId() const
{
    return _CurveId;
}

void ItemModel::setCurveId(int curveId)
{
    _CurveId = curveId;
}

int ItemModel::getRulesId() const
{
    return _RulesId;
}

void ItemModel::setRulesId(int ruleId)
{
    _RulesId = ruleId;
}

double ItemModel::getResultOffset() const
{
    return _ResultOffset;
}

void ItemModel::setResultOffset(double resultOffset)
{
    _ResultOffset = resultOffset;
}

double ItemModel::getPosition() const
{
    return _Position;
}

void ItemModel::setPosition(double position)
{
    _Position = position;
}

QString ItemModel::getItemFullName() const
{
    return _ItemFullName;
}

void ItemModel::setItemFullName(QString itemFullName)
{
    _ItemFullName = itemFullName;
}


bool ItemModel::operator==(ItemModel &it) const
{
    if(_ID==it._ID)
    {
        return true;
    }
    return false;
}
