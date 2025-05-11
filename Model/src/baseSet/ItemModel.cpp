#include "ItemModel.h"

ItemModel::ItemModel():
    _ID(0)
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

bool ItemModel::operator==(ItemModel &it) const
{
    if(_ID==it._ID)
    {
        return true;
    }
    return false;
}
