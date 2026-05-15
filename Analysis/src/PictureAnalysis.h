#pragma once

#include <QObject>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <QPoint>
#include <QVector>
#include "../Include/Model/baseSet/TestPaperModel.h"
#include "../Include/Model/baseSet/ItemModel.h"

class  PictureAnalysis : public QObject
{
    Q_OBJECT

public:
    enum class Error
    {
        NoError = 0,
        ConfigError=1, // 配置参数错误
        PictureNotFound=2, // 图片为找到
        ItemAnalysisHeightError=3, // 解析高度参数
        PictureToGrayError=4, // 转灰图片失败
        ContourNotFound=5, // 轮廓未找到
        DetectSegmentCntError=6, // 段检测错误
        DetectBlackPoint=7, // 检测到黑点
        FuncLineError=8, // 功能线异常
        CutOffLineError=9, // CutOff线异常
        ItemConfigError=10, // CutOff线异常
        ItemLineDetectError=11, // 项目线检测异常
        SegmentSetError=12, // 段设置错误
        DetectPictureSizeError=13, // 图像大小检测失败
    };

    // 判读结果
    struct TestPaperItemResult {
        double grayValue; // 灰度值
        double backgroundGrayValue; // 背景值
        double grayRatio; // 比值
        int lineCenter; // 条带中心位置
        int lineWidth; // 条带宽度
        QString qualitativeResult; // 最终的定性结果
        TestPaperItemResult()
            :grayValue(0)
            ,backgroundGrayValue(0)
            ,grayRatio(0)
            ,lineCenter(0)
            ,lineWidth(0)
            ,qualitativeResult("")
        {}
    };

    // 判读的段信息
    struct TestPaperSegmentResult
    {
        double _center; // 中心
        double _width; // 宽度
        TestPaperSegmentResult()
        :_center(0)
        ,_width(0)
        {}
        TestPaperSegmentResult(double center, double width)
            :_center(center)
            ,_width(width)
        {}
    };

    struct TestPaperStrt{
        TestPaperModel paperParam; // 膜条参数
        QVector<ItemModel> itemParamVect; // 子项目参数
        QVector<TestPaperItemResult> itemResultVect; // 子项目判读结果
        QVector<TestPaperSegmentResult> segmentResultVect; // 保存判读后的段信息
        QString sampleId; //标本id
        QString testId; // 测试id
        QString pictureRootPath; // 图片保存跟路径
        QString picturePath; // 图片文件路径
        QString pictureAnalysisPath; // 图片分析后保存的路径
        bool hasCutOff;
        TestPaperStrt()
            :paperParam()
            ,itemParamVect()
            ,itemResultVect()
            ,segmentResultVect()
            ,sampleId("0")
            ,testId("0")
            ,pictureRootPath("")
            ,picturePath("")
            ,pictureAnalysisPath("")
            ,hasCutOff(false)
        {}
    };

    PictureAnalysis(QObject *parent);
    ~PictureAnalysis();
    bool Analysis(QString test_project_name,QString file_path);
    bool AnalysisOne(QString test_id,int paperId, QString sampleId);
//    int CalcImageItemWz(TestPaperStrt &testPaperParameterStruct,QString sampleId);
//    int GetTestPaperImageWz(QString filePath,TestPaperStrt &testPaperParameterStruct,cv::OutputArray dst);
//    Error GetTestPaperImageSegmentation(TestPaperStrt &paper);
private:

    void maskOutsideRect(cv::Mat& src, const cv::Rect& roi);
    // 分段膜条处理
    Error SegmentPaperHandle(TestPaperStrt &paper);
    // 分段膜条旋转裁切
    Error SegmentPaperRotateCut(cv::Mat& srcMat, TestPaperStrt &paper,cv::OutputArray dstMat, cv::OutputArray dstThreshMat);
    Error SegmentPaperRotateCut1(cv::Mat& srcMat, TestPaperStrt &paper, cv::OutputArray dstMat, cv::OutputArray dst_thresh_mat);

    // 膜条段解析
    Error PaperSegmentationParse(cv::Mat& srcMat, cv::Mat& threshMat, TestPaperStrt &paper);
    Error PaperSegmentationParse1(cv::Mat& srcMat,cv::Mat& threshMat, TestPaperStrt &paper);
    std::vector<std::vector<cv::Rect>> groupRectsByHorizontalSpan(const std::vector<cv::Rect>& rects, int span);
    cv::Rect mergeRectsByScore(const cv::Mat& src, const std::vector<cv::Rect>& rects, int blockWidth, int paperBinarizationThresh);
    std::vector<cv::Rect> SegmentationContourFind(const cv::Mat& srcMat, const cv::Mat& threshMat, TestPaperStrt &paper, const QString& path);
    // 分段膜条项目解析
    Error SegmentPaperItemParse(cv::Mat& cutMat, TestPaperStrt &paper);

    // 连续膜条处理
    Error ContinuousPaperHandle(TestPaperStrt &paper);
    // 连续膜条旋转剪切
    Error ContinuousPaperRotateCut(TestPaperStrt &paper,cv::OutputArray dst);
    // 连续膜条项目解析
    Error ContinuousPaperItemParse(const cv::Mat& src, TestPaperStrt &paper);
    // 单项目解析
    Error OneItemParse(const cv::Mat& srcMat, TestPaperItemResult& result, int lineWidth, int bgDiff);
    // 图像旋转
    bool SrcImageNeedRotate180(TestPaperModel& paper);

    QString CaculateResultText(double dItemGrayRatio,const int ruleId);
    bool isExistCutoffLine(TestPaperStrt& paper);
    bool AnalysisOneSample(int paper_id, QString testId, QString sampleId);
//    bool GetTestPaperParameter(TestPaperParameter &testPaperParameterStruct,int paper_id, int company_id);
    bool UpdateSampleAnalysisState(TestPaperStrt& paper, Error error);
    bool SaveTestData(TestPaperStrt& paper);

};
