#pragma once

#include <QObject>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <QPoint>
#include <QVector>
#include "../Include/Model/baseSet/TestPaperModel.h"
#include "../Include/Model/baseSet/ItemModel.h"

// 判读结果
typedef struct {
    double grayValue; // 灰度值
    double backgroundGrayValue; // 背景值
    double resultOffset; // 结果偏移值
    int errorCode; // 错误代码
    double grayRatio; // 比值
    double positionStart; // 条带起始位置
}TestPaperItemResult;

typedef struct {
    TestPaperModel paperParam; // 膜条参数
    QVector<ItemModel> itemParamVect; // 子项目参数
    QVector<TestPaperItemResult> itemResultVect; // 子项目判读结果
    QString sampleId; //标本id
    QString testId; // 测试id
}TestPaperStrt;

class  PictureAnalysis : public QObject
{
    Q_OBJECT

public:
    enum class Error
    {
        NoError = 0,
        ConfigError, // 配置参数错误
        PictureNotFound, // 图片为找到
        ItemAnalysisHeightError, // 解析高度参数
        PictureToGrayError, // 转灰图片失败
        ContourNotFound, // 轮廓未找到
        DetectSegmentCntError, // 段检测错误
        DetectBlackPoint, // 检测到黑点
        FuncLineError, // 功能线异常
        CutOffLineError, // CutOff线异常
        ItemConfigError, // CutOff线异常


    };
    PictureAnalysis(QObject *parent);
    ~PictureAnalysis();
    bool Analysis(QString test_project_name,QString file_path);
    bool AnalysisOne(QString test_id,int paperId, QString sampleId);
    int CalcImageItemWz(TestPaperStrt &testPaperParameterStruct,QString sampleId);
    int GetTestPaperImageWz(QString filePath,TestPaperStrt &testPaperParameterStruct,cv::OutputArray dst);
    Error CalcImageItemSegmentation(TestPaperStrt &paper);
    Error GetTestPaperImageSegmentation(const QString& filePath, TestPaperStrt &paper);
    int CalcImageItemContinuous(TestPaperStrt &testPaperParameterStruct, QString testId);
    int GetTestPaperImageContinuous(QString filePath,TestPaperStrt &testPaperParameterStruct,cv::OutputArray dst);
private:
//    QString m_test_project_name;
//    QString m_nSampleID;
//    int m_nTestPaperID;
//    int m_nControlThreshold = 0;
//    int m_nCutOffThreshold = 0;

    PictureAnalysis::Error TestPaperSegmentationRotateCut(cv::Mat& srcMat, TestPaperStrt &paper,cv::OutputArray dstMat, cv::OutputArray dstThreshMat);
    PictureAnalysis::Error TestPaperSegmentationParse(cv::Mat& srcMat, cv::Mat& threshMat, TestPaperStrt &paper, QVector<std::tuple<int,int>>& segCenter);

    QString CaculateResultText(double dItemGrayRatio,QString itemName,int paper_id,int error_code);
    bool AnalysisOneSample(int paper_id, QString testId, QString sampleId);
//    bool GetTestPaperParameter(TestPaperParameter &testPaperParameterStruct,int paper_id, int company_id);
    bool UpdateSampleAnalysisState(int nAnalysisState);
    bool SaveTestData(TestPaperStrt testPaperResult);
    int GetTestPaperImageCalcIndexWz(const cv::Mat& src, TestPaperStrt &testPaperParameterStruct,QList<int> lineStartArray, int lineLimit, int lineWidth);
    Error GetTestOneItemCalcIndexWz(const cv::Mat& srcMat, std::tuple<int,int,double,double>& result, int lineWidth, int bgDiff);
    bool SrcImageNeedRotate180(TestPaperModel& paper);
};
