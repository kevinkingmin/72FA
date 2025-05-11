#include "TestPaperModel.h"

TestPaperModel::TestPaperModel()
    :_ID(0)
    , _PaperName("")
    ,_companyId(0)
    ,_TotalNumber(0)
    ,_itemNumber(0)
    ,_TestPaparLenght(0)
    ,_FuncPosition(0)
    ,_TestAeaLenght(0)
    ,_usageV(0)
    ,_defaultBGRGB("")
    ,_BGRGB("")
    ,_isDelete(false)
	,_articleNo("")
{

}

int TestPaperModel::getID() const
{
    return _ID;
}

void TestPaperModel::setID(int ID)
{
    _ID = ID;
}

QString TestPaperModel::getPaperName() const
{
    return _PaperName;
}



void TestPaperModel::setArticleNo(const QString &articleNo)
{
	_articleNo = articleNo;
}

QString TestPaperModel::getArticleNo() const
{
	return _articleNo;
}

void TestPaperModel::setPaperName(const QString &PaperName)
{
    _PaperName = PaperName;
}

int TestPaperModel::getCompanyId() const
{
    return _companyId;
}

void TestPaperModel::setCompanyId(int companyId)
{
    _companyId = companyId;
}

int TestPaperModel::getTotalNumber() const
{
    return _TotalNumber;
}

void TestPaperModel::setTotalNumber(int TotalNumber)
{
    _TotalNumber = TotalNumber;
}

int TestPaperModel::getItemNumber() const
{
    return _itemNumber;
}

void TestPaperModel::setItemNumber(int itemNumber)
{
    _itemNumber = itemNumber;
}

int TestPaperModel::getTestPaparLenght() const
{
    return _TestPaparLenght;
}

void TestPaperModel::setTestPaparLenght(int TestPaparLenght)
{
    _TestPaparLenght = TestPaparLenght;
}

int TestPaperModel::getFuncPosition() const
{
    return _FuncPosition;
}

void TestPaperModel::setFuncPosition(int FuncPosition)
{
    _FuncPosition = FuncPosition;
}

int TestPaperModel::getTestAeaLenght() const
{
    return _TestAeaLenght;
}

void TestPaperModel::setTestAeaLenght(int TestAeaLenght)
{
    _TestAeaLenght = TestAeaLenght;
}

int TestPaperModel::getUsageV() const
{
    return _usageV;
}

void TestPaperModel::setUsageV(int usageV)
{
    _usageV = usageV;
}

int TestPaperModel::getSort_idx() const
{
	return _sort_idx;
}

void TestPaperModel::setSort_idx(int sort_idx)
{
	_sort_idx = sort_idx;
}

QString TestPaperModel::getDefaultBGRGB() const
{
    return _defaultBGRGB;
}

void TestPaperModel::setDefaultBGRGB(const QString &defaultBGRGB)
{
    _defaultBGRGB = defaultBGRGB;
}

QString TestPaperModel::getBGRGB() const
{
    return _BGRGB;
}

void TestPaperModel::setBGRGB(const QString &BGRGB)
{
    _BGRGB = BGRGB;
}

bool TestPaperModel::getIsDelete() const
{
    return _isDelete;
}

void TestPaperModel::setIsDelete(bool isDelete)
{
    _isDelete = isDelete;
}







