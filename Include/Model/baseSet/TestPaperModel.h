#ifndef TESTPAPERMODEL_H
#define TESTPAPERMODEL_H
#include <QObject>
#include "../Model.h"

class MODELSHARED_EXPORT TestPaperModel
{
public:
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

    double getTotalLenght();
    void setTotalLenght(double totalLenght);

    double getPaperMmToPixel();
    void setPaperMmToPixel(double paperMmToPixel);

    double getIgnoreHeadLenght();
    void setIgnoreHeadLenght(double ignoreHeadLenght);

    double getPaperLenght();
    void setPaperLenght(double paperLenght);

    double getPaperHeight();
    void setPaperHeight(double paperHeight);

    double getTestBlockWidth();
    void setTestBlockWidth(double testBlockWidth);

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

    bool getIsCutOff();
    void setIsCutOff(bool isCutOff);

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

    int getAnalysisPercentOfHeight();
    void setAnalysisPercentOfHeight(int analysisPercentOfHeight);

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


private:
    int _id;
    int _companyId;
    QString	_paperName;
    int _paperType;
    int _totalNumber;
    int _testItemNumber;
    double _totalLenght;
    double _paperMmToPixel; // 毫米对应的像素点数
    double _ignoreHeadLenght; // 忽略的头长度
    double _paperLenght; // 模块长度
    double _paperHeight; // 膜条高度
    double _testBlockWidth; // 分段膜条块的宽度
    int _funcFindDir; // 功能线查找方向
    int _paperShowAngle; // 膜条显示角度
    double _funcPosition; // 功能线位置
    double _funcFindWidth; // 功能线查找宽度
    double _funcGrayThreshold; // 功能线灰度阈值
    bool _isBlackPointDetect; // 是否开启黑点检测
    double _blackPointDetectThreshold;// 黑点检测阈值
    bool _isCutOff;
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
};

#endif // TESTPAPERMODEL_H
