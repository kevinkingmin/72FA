#pragma once

#include <QObject>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <QPoint>
#include<vector>
#include <map>


typedef struct {
    int curveId;
    int curveType;
    double dataGroup1[10];
    double dataGroup2[10];
    double dataGroup3[10];
    double dataGroup4[10];
    double dataGroup5[10];
    double dataGroup6[10];
    double dataGroup7[10];
    double dataGroup8[10];
    double dataGroup9[10];
    double dataGroup10[10];
}StandardCurveParameter, *LPStandardCurveParameter;

class standard_curve : public QObject
{
    Q_OBJECT

public:
    standard_curve(QObject *parent);
    ~standard_curve();

    double Calc(StandardCurveParameter &parameter, double value);
    bool GetStandardCurveParameter(StandardCurveParameter &parapeter, int curveId);
//    bool Analysis(QString test_project_name,QString file_path);
//    bool AnalysisOne(QString test_id,int paperId, QString sampleId, QString solution_name, QString patiant_name);
//    int CalcImageItemWz(TestPaperParameter &testPaperParameterStruct,QString sampleId);
//    int GetTestPaperImageWz(QString filePath,TestPaperParameter &testPaperParameterStruct,cv::OutputArray dst);
//    int CalcImageItemSegmentation(TestPaperParameter &testPaperParameterStruct, QString testId);
//    int GetTestPaperImageSegmentation(QString filePath,TestPaperParameter &testPaperParameterStruct);
//    int CalcImageItemContinuous(TestPaperParameter &testPaperParameterStruct, QString testId);
//    int GetTestPaperImageContinuous(QString filePath,TestPaperParameter &testPaperParameterStruct,cv::OutputArray dst);
private:
    //QMap<int, StandardCurveParameter> curveMap;
//    QString m_test_project_name;
//    QString m_nSampleID;
//    int m_nTestPaperID;
//    int m_nControlThreshold = 0;
//    int m_nCutOffThreshold = 0;

//    int TestPaperSegmentationRotateCut(cv::Mat& srcMat, TestPaperParameter &testPaperParameterStruct,cv::OutputArray dstMat, cv::OutputArray dstThreshMat);
//    int TestPaperSegmentationParse(cv::Mat& srcMat, cv::Mat& threshMat, TestPaperParameter &testPaperParameterStruct,std::vector<std::tuple<int,int>>& segCenter);

//    QString CaculateResultText(double dItemGrayRatio,QString itemName,int paper_id,int error_code);
//    bool AnalysisOneSample(int paper_id,int company_id,QString testId, QString sampleId, QString solution_name, QString patiant_name);
//    bool GetTestPaperParameter(TestPaperParameter &testPaperParameterStruct,int paper_id, int company_id);
//    bool UpdateSampleAnalysisState(int nAnalysisState);
//    bool SaveTestData(TestPaperParameter testPaperResult);
//    int GetTestPaperImageCalcIndexWz(const cv::Mat& src, TestPaperParameter &testPaperParameterStruct,QList<int> lineStartArray, int lineLimit, int lineWidth);
//    int GetTestOneItemCalcIndexWz(const cv::Mat& srcMat, std::tuple<int,int,double,double>& result, int lineWidth, int bgDiff);
//    bool SrcImageNeedRotate180(TestPaperParameter& self);
};
