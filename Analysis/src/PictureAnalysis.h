#pragma once

#include <QObject>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <QPoint>
#include<vector>

typedef struct {
    int testPaperId; // 膜条ID
    QString itemName; // 项目名称
    int PositionNo; // 项目编号
    int curveId; // 标曲ID
    int rulesId; // 规则ID
    double resultOffset; // 结果补偿
    int position; // 项目位置
    bool isNull; // 是否为空
    QString itemFullName; //项目全名
}TestPaperItem;

typedef struct {
    int companyId;
    QString	strTestPaperName;
    int paperType;
    int nTotalNumber;
    int nTestItemNumber;
    double dTotalLenght;
    double paperMmToPixel; // 毫米对应的像素点数
    double ignoreHeadLenght; // 忽略的头长度
    double paperLenght; // 模块长度
    double paperHeight; // 膜条高度
    double testBlockWidth; // 分段膜条块的宽度
    int funcFindDir; // 功能线查找方向
    int paperShowAngle; // 膜条显示角度
    double funcPosition; // 功能线位置
    double funcFindWidth; // 功能线查找宽度
    double funcGrayThreshold; // 功能线灰度阈值
    bool isBlackPointDetect; // 是否开启黑点检测
    double blackPointDetectThreshold;// 黑点检测阈值
    bool isCutOff;
    double cutOffThreshold;
    double cutOffPosition;
    double cutOffValue;
    int paperBinarizationThreshold; // 二值化阈值
    double paperBackgroundValue; // 膜条背景值
    double itemFindWidth; // 项目查找宽度
    double itemLineWidth; // 指标线宽
    int analysisPercentOfHeight; // 高度分析百分比
    int analysisPercentOfWidth; // 宽度分析百分比
    int paperColorOnUi; // UI上显示的颜色
    bool isPaperHide; // UI上是否显示此膜条
    QString articleNo; // 货号
    int paperSortIdxOnUi; // UI上此膜条的排序

    QList<TestPaperItem> items; // 子项目参数

    QString strTestItemName[32];
    bool	isNullArea[32];
    double dItemPosition[32];
    int dItemNo[32];
    int dItemCurveId[32];
    double dItemGrayValue[32];
    double dBackgroundGrayValue[32];
    double dItemResultOffset[32];
    int dItemErrorCode[32];
    double dItemGrayRatio[32];
    QString solutionName;
    QString manageName;
    QString sampleId;
    int paperId;
    QString Id;
}TestPaperParameter, *LPTestPaperParameter;

class  PictureAnalysis : public QObject
{
    Q_OBJECT

public:
    PictureAnalysis(QObject *parent);
    ~PictureAnalysis();
    bool Analysis(QString test_project_name,QString file_path);
    bool AnalysisOne(QString test_id,int paperId, QString sampleId, QString solution_name, QString patiant_name);
    int CalcImageItemWz(TestPaperParameter &testPaperParameterStruct,QString sampleId);
    int GetTestPaperImageWz(QString filePath,TestPaperParameter &testPaperParameterStruct,cv::OutputArray dst);
    int CalcImageItemSegmentation(TestPaperParameter &testPaperParameterStruct, QString testId);
    int GetTestPaperImageSegmentation(QString filePath,TestPaperParameter &testPaperParameterStruct);
    int CalcImageItemContinuous(TestPaperParameter &testPaperParameterStruct, QString testId);
    int GetTestPaperImageContinuous(QString filePath,TestPaperParameter &testPaperParameterStruct,cv::OutputArray dst);
private:
    QString m_test_project_name;
    QString m_nSampleID;
    int m_nTestPaperID;
    int m_nControlThreshold = 0;
    int m_nCutOffThreshold = 0;

    int TestPaperSegmentationRotateCut(cv::Mat& srcMat, TestPaperParameter &testPaperParameterStruct,cv::OutputArray dstMat, cv::OutputArray dstThreshMat);
    int TestPaperSegmentationParse(cv::Mat& srcMat, cv::Mat& threshMat, TestPaperParameter &testPaperParameterStruct,std::vector<std::tuple<int,int>>& segCenter);

    QString CaculateResultText(double dItemGrayRatio,QString itemName,int paper_id,int error_code);
    bool AnalysisOneSample(int paper_id,int company_id,QString testId, QString sampleId, QString solution_name, QString patiant_name);
    bool GetTestPaperParameter(TestPaperParameter &testPaperParameterStruct,int paper_id, int company_id);
    bool UpdateSampleAnalysisState(int nAnalysisState);
    bool SaveTestData(TestPaperParameter testPaperResult);
    int GetTestPaperImageCalcIndexWz(const cv::Mat& src, TestPaperParameter &testPaperParameterStruct,QList<int> lineStartArray, int lineLimit, int lineWidth);
    int GetTestOneItemCalcIndexWz(const cv::Mat& srcMat, std::tuple<int,int,double,double>& result, int lineWidth, int bgDiff);
    bool SrcImageNeedRotate180(TestPaperParameter& self);
};
