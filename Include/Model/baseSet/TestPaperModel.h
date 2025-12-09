#ifndef TESTPAPERMODEL_H
#define TESTPAPERMODEL_H
#include <QObject>
#include "../Model.h"

class MODELSHARED_EXPORT TestPaperModel
{
public:
    static const int PAPER_TYPE_CONTINUOUS; // 连续膜条
    static const int PAPER_TYPE_SEGMENT; // 分段膜条
    static const int PAPER_SHOW_DRAGE_0; // 膜条展示角度
    static const int PAPER_SHOW_DRAGE_180; // 膜条展示角度
    static const int PAPER_FUNC_FIND_DIR_HEAD; // 功能线查找方向 头
    static const int PAPER_FUNC_FIND_DIR_TAIL; // 功能线查找方向 尾

    TestPaperModel();


    int getId();
    void setId(int id);

    int getCompanyId();
    void setCompanyId(int companyId);

    QString	getPaperName();
    void setPaperName(QString paperName);

    int getPaperType();
    void setPaperType(int paperType);

    int getTotalNumber();
    void setTotalNumber(int totalNumber);

    int getTestItemNumber();
    void setTestItemNumber(int testItemNumber);

    double getPaperMmToPixel();
    void setPaperMmToPixel(double paperMmToPixel);

    double getIgnoreHeadLenght();
    void setIgnoreHeadLenght(double ignoreHeadLenght);

    double getPaperLenght();
    void setPaperLenght(double paperLenght);

    double getPaperHeight();
    void setPaperHeight(double paperHeight);

    // 获取膜条分析高度
    double getAnalysisPaperHeight();

    double getTestBlockWidth();
    void setTestBlockWidth(double testBlockWidth);

    double getTestBlockSpace();
    void setTestBlockSpace(double testBlockSpace);

    int getFuncFindDir();
    void setFuncFindDir(int funcFindDir);

    int getPaperShowAngle();
    void setPaperShowAngle(int paperShowAngle);

    double getFuncPosition();
    void setFuncPosition(double funcPosition);

    double getFuncFindWidth();
    void setFuncFindWidth(double funcFindWidth);

    double getFuncGrayThreshold();
    void setFuncGrayThreshold(double funcGrayThreshold);

    bool getIsBlackPointDetect();
    void setIsBlackPointDetect(bool isBlackPointDetect);

    double getBlackPointDetectThreshold();
    void setBlackPointDetectThreshold(double blackPointDetectThreshold);

    double getCutOffThreshold();
    void setCutOffThreshold(double cutOffThreshold);

    double getCutOffPosition();
    void setCutOffPosition(double cutOffPosition);

    double getCutOffValue();
    void setCutOffValue(double cutOffValue);

    int getPaperBinarizationThreshold();
    void setPaperBinarizationThreshold(int paperBinarizationThreshold);

    double getPaperBackgroundValue();
    void setPaperBackgroundValue(double paperBackgroundValue);

    double getItemFindWidth();
    void setItemFindWidth(double itemFindWidth);

    double getItemLineWidth();
    void setItemLineWidth(double itemLineWidth);

    // 获取分析线宽度
    double getItemAnalysisWidth();

    double getAnalysisPercentOfHeightDouble();
    int getAnalysisPercentOfHeight();
    void setAnalysisPercentOfHeight(int analysisPercentOfHeight);

    double getAnalysisPercentOfWidthDouble();
    int getAnalysisPercentOfWidth();
    void setAnalysisPercentOfWidth(int analysisPercentOfWidth);

    QString getPaperColorOnUi();
    void setPaperColorOnUi(QString paperColorOnUi);

    bool isPaperHide();
    void setPaperHide(bool paperHide);

    QString getArticleNo();
    void setArticleNo(QString articleNo);

    int getPaperSortIdxOnUi();
    void setPaperSortIdxOnUi(int paperSortIdxOnUi);

    int getProcessId();
    void setProcessId(int processId);


private:
    int _id;
    int _companyId;
    QString	_paperName;
    int _paperType;
    // 对于分段膜条是总项目段数, 对于连续模块是总条带数
    int _totalNumber;
    // 测试项目数量
    int _testItemNumber;
    double _paperMmToPixel; // 毫米对应的像素点数
    double _ignoreHeadLenght; // 忽略的头长度
    double _paperLenght; // 模块长度
    double _paperHeight; // 膜条高度
    double _testBlockWidth; // 分段膜条块的最小宽度
    double _testBlockSpace; // 分段膜条块的最小间距
    int _funcFindDir; // 功能线查找方向
    int _paperShowAngle; // 膜条显示角度
    double _funcPosition; // 功能线位置
    double _funcFindWidth; // 功能线查找宽度
    double _funcGrayThreshold; // 功能线灰度阈值
    bool _isBlackPointDetect; // 是否开启黑点检测
    double _blackPointDetectThreshold;// 黑点检测阈值
    double _cutOffThreshold;
    double _cutOffPosition;
    double _cutOffValue;
    int _paperBinarizationThreshold; // 二值化阈值
    double _paperBackgroundValue; // 膜条背景值
    double _itemFindWidth; // 项目查找宽度
    double _itemLineWidth; // 指标线宽
    int _analysisPercentOfHeight; // 高度分析百分比
    int _analysisPercentOfWidth; // 宽度分析百分比
    QString _paperColorOnUi; // UI上显示的颜色
    bool _isPaperHide; // UI上是否显示此膜条
    QString _articleNo; // 货号
    int _paperSortIdxOnUi; // UI上此膜条的排序
    int _processId; // 流程id
};

#endif // TESTPAPERMODEL_H
