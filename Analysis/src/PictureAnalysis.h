#pragma once

#include <QObject>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <QPoint>
#include<vector>


typedef struct {
    QString	strTestPaperName;
    int nTotalNumber;
    int nTestItemNumber;
    int nTestItemBlankNumber;
    double dTotalLenght;
    double dFunctonalControlPosition;
    double dCufOffPosition;
    double dTestItemAreaTotalLenght;
    double dOneTestItemLenght;
    QString strTestItemName[32];
    bool	isNullArea[32];
    double dItemPosition[32];
    int dItemNo[32];
    double dItemGrayValue[32];
    double dBackgroundGrayValue[32];
    int dItemErrorCode[32];
    double dItemGrayRatio[32];
    QString solutionName;
    QString manageName;
    QString sampleId;
    QString articleNo;
    int paperId;
    QString Id;
    int isCutOff;
    int isFun;
    double dHeadAreaLength;
    double cutoff_value_user;
    double rect_Analysis_x;
    double rect_Analysis_y;
    double rect_Analysis_width;
    double rect_Analysis_height;
    double analysis_height_percentage;
    double head_length;
    int set_calculate_point;
    double	point_to_min_percent;
    double detection_width;
    int	find_min_times;
    int left_judge_value;
    int company_id;

    int wave_pix_width;
    int wave_pix_width_min;
    int wave_pix_width_max;
    int threshold_value;
    int background_values;
    double zero_value_coefficient;
    int bg_difference;

}TestPaperParameter, *LPTestPaperParameter;

class PictureAnalysis : public QObject
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
