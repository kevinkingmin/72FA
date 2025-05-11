#include "TestResultModel.h"

int TestResultModel::getID() const
{
    return _ID;
}
void TestResultModel::setID(int ID)
{
    _ID = ID;
}
int TestResultModel::getTestPaperID() const
{
    return _TestPaperID;
}
void TestResultModel::setTestPaperID(int TestPaperID)
{
    _TestPaperID = TestPaperID;
}
QString TestResultModel::getItemName() const
{
    return _itemName;
}
void TestResultModel::setItemName(QString itemName)
{
    _itemName = itemName;
}
int TestResultModel::getPositionNo() const
{
    return _PositionNo;
}
void TestResultModel::setPositionNo(int PositionNo)
{
    _PositionNo = PositionNo;
}

double TestResultModel::getPosition() const
{
    return _Position;
}
void TestResultModel::setPosition(double Position)
{
    _Position = Position;
}

bool TestResultModel::getIsNull() const
{
    return _IsNull;
}
void TestResultModel::setIsNull(bool IsNull)
{
    _IsNull = IsNull;
}

