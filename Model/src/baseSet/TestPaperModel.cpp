#include "TestPaperModel.h"

const int TestPaperModel::PAPER_TYPE_CONTINUOUS = 0; // 连续膜条
const int TestPaperModel::PAPER_TYPE_SEGMENT = 1; // 分段膜条
const int TestPaperModel::PAPER_TYPE_SEGMENT_INDEPENDENT_FUNC = 2; // 分段膜条(独立功能块)
const int TestPaperModel::PAPER_SHOW_DRAGE_0 = 0; // 膜条展示角度
const int TestPaperModel::PAPER_SHOW_DRAGE_180 = 180; // 膜条展示角度
const int TestPaperModel::PAPER_FUNC_FIND_DIR_HEAD = 0; // 功能线查找方向 头
const int TestPaperModel::PAPER_FUNC_FIND_DIR_TAIL = 1; // 功能线查找方向 尾

TestPaperModel::TestPaperModel()
    :_id(0)
    ,_companyId(0)
    ,_paperName("")
    ,_paperType(0)
    ,_totalNumber(1)
    ,_testItemNumber(1)
    ,_paperMmToPixel(14.3)
    ,_ignoreHeadLenght(0)
    ,_paperLenght(1)
    ,_paperHeight(1)
    ,_testBlockWidth(0)
    ,_funcFindDir(0)
    ,_paperShowAngle(0)
    ,_funcPosition(1)
    ,_funcFindWidth(1)
    ,_funcGrayThreshold(200)
    ,_isBlackPointDetect(0)
    ,_blackPointDetectThreshold(10)
    ,_cutOffThreshold(0)
    ,_cutOffPosition(0)
    ,_cutOffValue(120)
    ,_paperBinarizationThreshold(150)
    ,_paperBackgroundValue(200)
    ,_itemFindWidth(3)
    ,_itemLineWidth(1)
    ,_analysisPercentOfHeight(60)
    ,_analysisPercentOfWidth(100)
    ,_paperColorOnUi(0x00ff00)
    ,_isPaperHide(0)
    ,_articleNo(1)
    ,_paperSortIdxOnUi(1)
{

}
int TestPaperModel::getId()
{
    return _id;
}

void TestPaperModel::setId(int id)
{
    _id = id;
}

QString TestPaperModel::getPaperName()
{
    return _paperName;
}

void TestPaperModel::setPaperName(QString paperName)
{
    _paperName = paperName;
}


int TestPaperModel::getCompanyId()
{
    return _companyId;
}

void TestPaperModel::setCompanyId(int companyId)
{
    _companyId = companyId;
}

int TestPaperModel::getPaperType()
{
    return _paperType;
}

void TestPaperModel::setPaperType(int paperType)
{
    _paperType = paperType;
}

int TestPaperModel::getTotalNumber()
{
    return _totalNumber;
}

void TestPaperModel::setTotalNumber(int totalNumber)
{
    _totalNumber = totalNumber;
}

int TestPaperModel::getTestItemNumber()
{
    return _testItemNumber;
}

void TestPaperModel::setTestItemNumber(int testItemNumber)
{
    _testItemNumber = testItemNumber;
}

double TestPaperModel::getPaperMmToPixel()
{
    return _paperMmToPixel;
} // 毫米对应的像素点数

void TestPaperModel::setPaperMmToPixel(double paperMmToPixel)
{

    _paperMmToPixel = paperMmToPixel;
}

double TestPaperModel::getIgnoreHeadLenght()
{
    return _ignoreHeadLenght;
} // 忽略的头长度

void TestPaperModel::setIgnoreHeadLenght(double ignoreHeadLenght)
{

    _ignoreHeadLenght = ignoreHeadLenght;
}

double TestPaperModel::getPaperLenght()
{
    return _paperLenght;
} // 模块长度

void TestPaperModel::setPaperLenght(double paperLenght)
{

    _paperLenght = paperLenght;
}

double TestPaperModel::getPaperHeight()
{
    return _paperHeight;
} // 膜条高度

void TestPaperModel::setPaperHeight(double paperHeight)
{

    _paperHeight = paperHeight;
}


double TestPaperModel::getAnalysisPaperHeight()
{
    return _paperHeight * _analysisPercentOfHeight / 100;
}

double TestPaperModel::getTestBlockWidth()
{
    return _testBlockWidth;
} // 分段膜条块的宽度

void TestPaperModel::setTestBlockWidth(double testBlockWidth)
{
    _testBlockWidth = testBlockWidth;
}

double TestPaperModel::getTestBlockSpace()
{
    return _testBlockSpace;
} // 分段膜条块的宽度

void TestPaperModel::setTestBlockSpace(double testBlockSpace)
{
    _testBlockSpace = testBlockSpace;
}

int TestPaperModel::getFuncFindDir()
{
    return _funcFindDir;
} // 功能线查找方向

void TestPaperModel::setFuncFindDir(int funcFindDir)
{

    _funcFindDir = funcFindDir;
}

int TestPaperModel::getPaperShowAngle()
{
    return _paperShowAngle;
} // 膜条显示角度

void TestPaperModel::setPaperShowAngle(int paperShowAngle)
{

    _paperShowAngle = paperShowAngle;
}

double TestPaperModel::getFuncPosition()
{
    return _funcPosition;
} // 功能线位置

void TestPaperModel::setFuncPosition(double funcPosition)
{

    _funcPosition = funcPosition;
}

double TestPaperModel::getFuncFindWidth()
{
    return _funcFindWidth;
} // 功能线查找宽度

void TestPaperModel::setFuncFindWidth(double funcFindWidth)
{

    _funcFindWidth = funcFindWidth;
}

double TestPaperModel::getFuncGrayThreshold()
{
    return _funcGrayThreshold;
} // 功能线灰度阈值

void TestPaperModel::setFuncGrayThreshold(double funcGrayThreshold)
{

    _funcGrayThreshold = funcGrayThreshold;
}

bool TestPaperModel::getIsBlackPointDetect()
{
    return _isBlackPointDetect;
} // 是否开启黑点检测

void TestPaperModel::setIsBlackPointDetect(bool isBlackPointDetect)
{

    _isBlackPointDetect = isBlackPointDetect;
}

double TestPaperModel::getBlackPointDetectThreshold()
{
    return _blackPointDetectThreshold;
}// 黑点检测阈值

void TestPaperModel::setBlackPointDetectThreshold(double blackPointDetectThreshold)
{
    _blackPointDetectThreshold = blackPointDetectThreshold;
}

double TestPaperModel::getCutOffThreshold()
{
    return _cutOffThreshold;
}
void TestPaperModel::setCutOffThreshold(double cutOffThreshold)
{

    _cutOffThreshold = cutOffThreshold;
}
double TestPaperModel::getCutOffPosition()
{
    return _cutOffPosition;
}
void TestPaperModel::setCutOffPosition(double cutOffPosition)
{

    _cutOffPosition = cutOffPosition;
}
double TestPaperModel::getCutOffValue()
{
    return _cutOffValue;
}
void TestPaperModel::setCutOffValue(double cutOffValue)
{

    _cutOffValue = cutOffValue;
}
int TestPaperModel::getPaperBinarizationThreshold()
{
    return _paperBinarizationThreshold;
} // 二值化阈值
void TestPaperModel::setPaperBinarizationThreshold(int paperBinarizationThreshold)
{
    _paperBinarizationThreshold = paperBinarizationThreshold;
}
double TestPaperModel::getPaperBackgroundValue()
{
    return _paperBackgroundValue;
} // 膜条背景值
void TestPaperModel::setPaperBackgroundValue(double paperBackgroundValue)
{

    _paperBackgroundValue = paperBackgroundValue;
}
double TestPaperModel::getItemFindWidth()
{
    return _itemFindWidth;
} // 项目查找宽度
void TestPaperModel::setItemFindWidth(double itemFindWidth)
{
    _itemFindWidth = itemFindWidth;
}
double TestPaperModel::getItemLineWidth()
{
    return _itemLineWidth;
} // 指标线宽
void TestPaperModel::setItemLineWidth(double itemLineWidth)
{

    _itemLineWidth = itemLineWidth;
}

double TestPaperModel::getItemAnalysisWidth()
{
    return _itemLineWidth * getAnalysisPercentOfWidthDouble();
}

int TestPaperModel::getAnalysisPercentOfHeight()
{
    return _analysisPercentOfHeight;
}

double TestPaperModel::getAnalysisPercentOfHeightDouble()
{
    return 1.0*_analysisPercentOfHeight/100;
}

// 高度分析百分比
void TestPaperModel::setAnalysisPercentOfHeight(int analysisPercentOfHeight)
{

    _analysisPercentOfHeight = analysisPercentOfHeight;
}
double TestPaperModel::getAnalysisPercentOfWidthDouble()
{
    return 1.0*_analysisPercentOfWidth/100;
}
int TestPaperModel::getAnalysisPercentOfWidth()
{
    return _analysisPercentOfWidth;
}
// 宽度分析百分比
void TestPaperModel::setAnalysisPercentOfWidth(int analysisPercentOfWidth)
{

    _analysisPercentOfWidth = analysisPercentOfWidth;
}
QString TestPaperModel::getPaperColorOnUi()
{
    return _paperColorOnUi;
} // UI上显示的颜色
void TestPaperModel::setPaperColorOnUi(QString paperColorOnUi)
{
    _paperColorOnUi = paperColorOnUi;
}
bool TestPaperModel::isPaperHide()
{
    return _isPaperHide;
} // UI上是否显示此膜条

void TestPaperModel::setPaperHide(bool paperHide)
{
    _isPaperHide = paperHide;
}

QString TestPaperModel::getArticleNo()
{
    return _articleNo;
} // 货号

void TestPaperModel::setArticleNo(QString articleNo)
{
    _articleNo = articleNo;
}

int TestPaperModel::getPaperSortIdxOnUi()
{
    return _paperSortIdxOnUi;
}

void TestPaperModel::setPaperSortIdxOnUi(int paperSortIdxOnUi)
{
    _paperSortIdxOnUi = paperSortIdxOnUi;
}

int TestPaperModel::getProcessId()
{
    return _processId;
}

void TestPaperModel::setProcessId(int processId)
{
    _processId = processId;
}





