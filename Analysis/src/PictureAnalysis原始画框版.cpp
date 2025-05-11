#include "PictureAnalysis.h"
#include <QSettings>
#include <QSqlQuery>
#include <QCoreApplication>
#include <QVariant>
#include <QDateTime>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include"iostream"
#include "../Include/DAO/Analysis/AnalysisDao.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Utilities/log.h"
#include "Wave_Low_Top_Info.h"
#include <opencv2/opencv.hpp>
#include <QtCore/qmath.h>
#include <random>
#include <map>
#include <vector>
#include <QtAlgorithms>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <numeric>

using namespace cv;
using namespace std;
#pragma execution_character_set("utf-8")
PictureAnalysis::PictureAnalysis(QObject *parent)
    : QObject(parent)
{
}

PictureAnalysis::~PictureAnalysis()
{
}

bool PictureAnalysis::Analysis(QString sampleId,QString file_path)
{
    bool bResult;
    auto dao = AnalysisDao::instance();
    m_test_project_name = sampleId;
    auto SampleQuery = dao->SelectSamples(m_test_project_name, &bResult);
    if (bResult == false)
    {
        QMessageBox::warning(nullptr, "tip", "检索样本数据失败！", QMessageBox::Ok);
        return false;
    }
    while (SampleQuery.next())
    {
        m_nSampleID = SampleQuery.value("sampleNo").toString();//.toInt();
        m_nTestPaperID = SampleQuery.value("paperId").toInt();
        AnalysisOneSample(m_nTestPaperID,1,file_path,"1","","");
    }
    return true;
}


bool PictureAnalysis::AnalysisOne(QString test_id,int paperId,QString sampleId, QString solution_name, QString patiant_name)
{
    bool bResult;
    auto dao = AnalysisDao::instance();
    auto SampleQuery = dao->SelectTestIdFromSamples(test_id, &bResult);
    if (bResult == false)
    {
        return false;
    }
    int companyId = 1;
    companyId = dao->SelectCampanyId(&bResult).toInt();
    bResult = AnalysisOneSample(paperId, companyId, test_id, sampleId, solution_name, patiant_name);
    if (bResult == false)
    {
        return false;
    }
    return true;
}
//
bool PictureAnalysis::AnalysisOneSample(int paper_id,int company_id,QString testId, QString sampleId, QString solution_name, QString patiant_name)
{
    TestPaperParameter testPaperParameterStruct;
    if (GetTestPaperParameter(testPaperParameterStruct, paper_id, company_id) == false)
        return false;
    testPaperParameterStruct.sampleId = sampleId;
    m_nSampleID = sampleId;
    int start_pix_position = 0;
    IplImage* imgTestPaper = GetTestPaperImage_new_HuoFu20241012(file_path, start_pix_position, testPaperParameterStruct);
    // IplImage* imgTestPaper = GetTestPaperImage(file_path);

    if (NULL == imgTestPaper)
    {
        UpdateSampleAnalysisState(88);
        return false;
    }

    TestPaperParameter testPaperResult;
    int nAnalysisState = AnalysisTestPaperImage(imgTestPaper, file_path, testPaperParameterStruct, testPaperResult, start_pix_position);
    if (UpdateSampleAnalysisState(nAnalysisState) == false)
        return false;
    if (nAnalysisState == 88 || nAnalysisState == 81 || nAnalysisState == 82)
    {
        testPaperResult.solutionName = solution_name;
        if (SaveTestData(testPaperResult) == false)
            return false;
    }
    return true;
}

bool PictureAnalysis::SaveTestData(TestPaperParameter testPaperResult)
{
    auto dao = AnalysisDao::instance();
    bool bResult;
    QString strSampleID;
    QString strTestPaper_ID;
    QString strItemName;
    QString strPosition;
    QString strGrayValue;
    QString strRatioToCut;
    QString strDiagnosis;
    QString strTestDateTime;
    QString strSolutionName;
    QString paper_id;
    QString articleNo;
    QString manageName;
    QDateTime nowTime = QDateTime::currentDateTime();
    QString id;
    int error_code;

    strTestDateTime = nowTime.toString("yyyy-MM-dd hh:mm:ss");
    for (int i = 0; i < (testPaperResult.nTotalNumber + 2); i++)
    {
        strSolutionName = testPaperResult.solutionName;
        paper_id = QString::number(testPaperResult.paperId);
        articleNo = testPaperResult.articleNo;
        manageName = testPaperResult.manageName;
        strSampleID = testPaperResult.sampleId;
        strTestPaper_ID = QString::number(m_nTestPaperID);
        strItemName = testPaperResult.strTestItemName[i];
        strPosition = QString::number(testPaperResult.dItemPosition[i]);
        strGrayValue = QString::number(testPaperResult.dItemGrayValue[i]);
        strRatioToCut = QString::number(testPaperResult.dItemGrayRatio[i]);
        strDiagnosis = CaculateResultText(testPaperResult.dItemGrayRatio[i], strItemName, paper_id.toInt(), testPaperResult.dItemErrorCode[i]);
        error_code = testPaperResult.dItemErrorCode[i];
        id = testPaperResult.Id;
        bResult = dao->InsertTestData(
                    strSolutionName,
                    id,
                    paper_id,
                    articleNo,
                    manageName,
                    m_test_project_name,
                    strSampleID,
                    strTestPaper_ID,
                    strItemName,
                    strPosition,
                    strGrayValue,
                    strRatioToCut,
                    strDiagnosis,
                    strTestDateTime, strSolutionName,"", error_code);
        if (bResult == false)
        {
            return false;
        }
    }
    return true;
}

bool PictureAnalysis::UpdateSampleAnalysisState(int nAnalysisState)
{
    auto dao = AnalysisDao::instance();
    bool bResult;
    QString strSampleID;
    QString strTestPaper_ID;
    QString strTestDateTime;
    QString strAnalysisState = QString::number(nAnalysisState);
    QDateTime nowTime = QDateTime::currentDateTime();
    strTestDateTime = nowTime.toString("yyyy-MM-dd hh:mm:ss");
    strSampleID = m_nSampleID;
    strTestPaper_ID = QString::number(m_nTestPaperID);
    bResult = dao->UpdateSampleAnalysisState(
                m_test_project_name,
                strSampleID,
                strTestPaper_ID,
                strAnalysisState,
                strTestDateTime);
    if (bResult == false)
    {
        return false;
    }
    return true;

}

double PictureAnalysis::GetTestItemWidthSetting()
{
    QString exe_path = QCoreApplication::applicationDirPath() + "/MillimetersToPixels.ini";
    QSettings config_set(exe_path, QSettings::IniFormat);
    double dParameterValue;
    config_set.beginGroup("Camera");
    dParameterValue = config_set.value("MillimetersToPixels").toDouble();
    return dParameterValue;
}

bool PictureAnalysis::GetTestPaperParameter(TestPaperParameter &testPaperParameterStruct,int paper_id, int company_id)
{
    bool bResult;
    auto dao = AnalysisDao::instance();
    QString strControlThreshold = dao->SelectControlThreshold(&bResult,paper_id,company_id);
    m_nControlThreshold = strControlThreshold.toInt();
    QString strCutOffThreshold = dao->SelectCutOffThreshold(&bResult, paper_id, company_id);
    m_nCutOffThreshold = strCutOffThreshold.toInt();
    auto TestPaperQuery = dao->SelectTestPaper(QString::number(paper_id), &bResult);
    if (bResult == false)
    {
        return false;
    }
    testPaperParameterStruct.paperId = paper_id;
    testPaperParameterStruct.articleNo = "调试批号";
    testPaperParameterStruct.solutionName = "调试方案名";
    testPaperParameterStruct.manageName = "调试操作员名称";
    if (TestPaperQuery.next())
    {
        testPaperParameterStruct.strTestPaperName = TestPaperQuery.value("PaperName").toString();
        testPaperParameterStruct.nTotalNumber = TestPaperQuery.value("TotalNumber").toInt();
        testPaperParameterStruct.nTestItemNumber = TestPaperQuery.value("Item_Number").toInt();
        testPaperParameterStruct.nTestItemBlankNumber = (TestPaperQuery.value("TotalNumber").toInt() - TestPaperQuery.value("Item_Number").toInt());
        testPaperParameterStruct.dTotalLenght = TestPaperQuery.value("TestPaparLenght").toDouble();
        testPaperParameterStruct.dOneTestItemLenght = TestPaperQuery.value("rect_Analysis.y").toDouble();
        testPaperParameterStruct.dFunctonalControlPosition = TestPaperQuery.value("FuncPosition").toDouble();
        testPaperParameterStruct.dCufOffPosition = TestPaperQuery.value("cutoffPosition").toDouble();
        testPaperParameterStruct.dTestItemAreaTotalLenght = TestPaperQuery.value("TestAeaLenght").toDouble();
        testPaperParameterStruct.isCutOff = TestPaperQuery.value("isCutOff").toInt();
        testPaperParameterStruct.isFun = TestPaperQuery.value("isFun").toInt();
        testPaperParameterStruct.dHeadAreaLength = TestPaperQuery.value("HeadAreaLength").toDouble();
        testPaperParameterStruct.company_id = TestPaperQuery.value("Company_ID").toInt();
        testPaperParameterStruct.cutoff_value_user = TestPaperQuery.value("cutoffValue").toDouble();
        testPaperParameterStruct.rect_Analysis_x = TestPaperQuery.value("rect_Analysis.x").toDouble();
        testPaperParameterStruct.rect_Analysis_y = TestPaperQuery.value("rect_Analysis.y").toDouble();
        QString rect_Analysis_width = dao->SelectSystemSetDes(&bResult, 20006);
        //testPaperParameterStruct.rect_Analysis_width = GetTestItemWidthSetting();
        testPaperParameterStruct.rect_Analysis_width =  TestPaperQuery.value("rect_Analysis.width").toDouble();
        testPaperParameterStruct.rect_Analysis_height = TestPaperQuery.value("rect_Analysis.height").toDouble();
        testPaperParameterStruct.analysis_height_percentage = TestPaperQuery.value("analysis_height_percentage").toDouble();
        testPaperParameterStruct.head_length = TestPaperQuery.value("head_length").toDouble();
        testPaperParameterStruct.set_calculate_point = TestPaperQuery.value("set_calculate_point").toInt();
        testPaperParameterStruct.point_to_min_percent = TestPaperQuery.value("point_to_min_percent").toDouble();
        testPaperParameterStruct.find_min_times = TestPaperQuery.value("find_min_times").toInt();
        testPaperParameterStruct.left_judge_value = TestPaperQuery.value("left_judge_value").toInt();
        testPaperParameterStruct.wave_pix_width = TestPaperQuery.value("wave_pix_width").toInt();
        testPaperParameterStruct.wave_pix_width_min = TestPaperQuery.value("wave_pix_width_min").toInt();
        testPaperParameterStruct.wave_pix_width_max = TestPaperQuery.value("wave_pix_width_max").toInt();
        testPaperParameterStruct.threshold_value = TestPaperQuery.value("threshold_value").toInt();
        testPaperParameterStruct.background_values = TestPaperQuery.value("background_values").toInt();
        testPaperParameterStruct.zero_value_coefficient = TestPaperQuery.value("zero_value_coefficient").toDouble();
        testPaperParameterStruct.bg_difference = TestPaperQuery.value("bg_difference").toInt();
    }
    auto TestPaperItemQuery = dao->SelectTestPaperItems(QString::number(paper_id), &bResult);
    if (bResult == false)
    {
        return false;
    }
    int nTotalNumber = 0;
    if (testPaperParameterStruct.isCutOff == 1)
    {
        nTotalNumber = 1 + testPaperParameterStruct.nTestItemNumber + testPaperParameterStruct.nTestItemBlankNumber;
    }
    else
    {
        nTotalNumber = testPaperParameterStruct.nTestItemNumber + testPaperParameterStruct.nTestItemBlankNumber;
    }
    testPaperParameterStruct.isNullArea[0] = 0;
    testPaperParameterStruct.strTestItemName[0] = "FC";
    testPaperParameterStruct.dItemPosition[0] = testPaperParameterStruct.dFunctonalControlPosition;
    testPaperParameterStruct.isNullArea[1] = 0;
    testPaperParameterStruct.strTestItemName[1] = "Cut";
    testPaperParameterStruct.dItemPosition[1] = testPaperParameterStruct.dCufOffPosition;
    int index = 2;
    while (TestPaperItemQuery.next())
    {
        testPaperParameterStruct.isNullArea[index] = TestPaperItemQuery.value("IsNull").toInt();
        testPaperParameterStruct.strTestItemName[index] = TestPaperItemQuery.value("itemName").toString();
        testPaperParameterStruct.dItemPosition[index] = TestPaperItemQuery.value("position").toDouble();
        index++;
    }
    return true;
}

IplImage* PictureAnalysis::GetTestPaperImage_new(QString file_path, TestPaperParameter testPaperParameterStruct)
{
    double head_area_length = 0;
    head_area_length = testPaperParameterStruct.dHeadAreaLength;
    bool bResult = true;
    auto dao = AnalysisDao::instance();
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName = strPath + "\\" + file_path + ".png";
    QFileInfo fileInfo(strPathFileName);
    if (!fileInfo.isFile())
    {
        return nullptr;
    }
    IplImage *image = cvLoadImage(strPathFileName.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    IplImage* pImage8uSmooth;
    IplImage  *srcGray;
    QString channelSeq = "";
    channelSeq = image->channelSeq;
    if (channelSeq == "GRAY")
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        pImage8uSmooth = image;
    }
    else
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        cvCvtColor(image, srcGray, CV_BGR2GRAY);
        pImage8uSmooth = srcGray;
    }
    double head_area_length_pix = 0;
    int nTestPaperTop = GetTestPaperTop(pImage8uSmooth);
    int nTestPaperBottom = GetTestPaperBottom(pImage8uSmooth);
    int nTestPaperLeft = GetTestPaperLeft(pImage8uSmooth, nTestPaperTop, nTestPaperBottom);
    if (nTestPaperLeft > 128 || (nTestPaperLeft - 128 > 0))
    {
        nTestPaperLeft = nTestPaperLeft - 128;
    }
    if (nTestPaperLeft - 128 < 0)
    {
        nTestPaperLeft = 0;
    }
    int nTestPaperRight = GetTestPaperRight(pImage8uSmooth, nTestPaperTop, nTestPaperBottom);
    CvRect rect;
    rect.x = nTestPaperLeft;
    rect.y = nTestPaperTop;
    rect.width = nTestPaperRight - nTestPaperLeft;
    rect.height = nTestPaperBottom - nTestPaperTop;
    if (rect.width < 0 || rect.height < 0)
    {
        return NULL;
    }
    CvMat *testPaperMat = cvCreateMatHeader(rect.height, rect.width, CV_MAKETYPE(srcGray->depth, srcGray->nChannels));
    cvGetSubRect(pImage8uSmooth, testPaperMat, rect);
    QString analysised_piture_path = "analysised";
    strPath = piture_root_str + "\\" + analysised_piture_path;
    strPathFileName = strPath + "\\" + file_path + ".png";
    QDir dir;
    if (!dir.exists(strPath))
    {
        dir.mkpath(strPath);
    }
    cvSaveImage(strPathFileName.toStdString().data(), testPaperMat);
    IplImage* imgTestPaper = cvCreateImage(cvGetSize(testPaperMat), 8, 1);
    cvGetImage(testPaperMat, imgTestPaper);
    return imgTestPaper;
}

IplImage* PictureAnalysis::GetTestPaperImage_new_HuoFu20241012(QString file_path, int& start_pix_position, TestPaperParameter testPaperParameter)
{
    bool bResult = true;
    auto dao = AnalysisDao::instance();
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName = strPath + "\\" + file_path + ".png";
    QFileInfo fileInfo(strPathFileName);
    if (!fileInfo.isFile())
    {
        return nullptr;
    }

    double dWidthRatio = 0;
    dWidthRatio = testPaperParameter.rect_Analysis_width;
    double paper_length_pix = testPaperParameter.dTotalLenght*dWidthRatio;

    int head_length = 0;
    head_length = testPaperParameter.head_length;
    int company_id = testPaperParameter.company_id;
    int find_characteristic_number = 1;
    find_characteristic_number = testPaperParameter.left_judge_value;
    double thresh = testPaperParameter.rect_Analysis_x;

    double thresh1 = testPaperParameter.rect_Analysis_height;

    QString analysised_piture_path1 = "analysised";
    QString strPathFileName_new = piture_root_str + "\\" + analysised_piture_path1 + "\\" + file_path + "_new1" + ".png";
    QString strPathFileName_last = piture_root_str + "\\" + analysised_piture_path1 + "\\" + file_path + "" + ".png";
    if(testPaperParameter.paperId==929){
        RotatePng_20241212(strPathFileName, strPathFileName_new, strPathFileName_last, head_length, find_characteristic_number, thresh, thresh1, paper_length_pix, company_id);
    }else if(testPaperParameter.paperId==930){
        RotatePng_20241212(strPathFileName, strPathFileName_new, strPathFileName_last, head_length, find_characteristic_number, thresh, thresh1, paper_length_pix, company_id);
    }else{
        RotatePng_20241012(strPathFileName, strPathFileName_new, strPathFileName_last, head_length, find_characteristic_number, thresh, thresh1, paper_length_pix, company_id);
    }
    IplImage *testPaperMat_Analysis1_need = cvLoadImage(strPathFileName_last.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    IplImage  *srcGray;
    QString channelSeq = "";
    if (testPaperMat_Analysis1_need == NULL)
    {
        return NULL;
    }
    IplImage* imgTestPaper1 = cvCreateImage(cvGetSize(testPaperMat_Analysis1_need), 8, 1);
    double percentage = testPaperParameter.analysis_height_percentage / 100;
    int start_y_axis = 0 + (testPaperMat_Analysis1_need->height - testPaperMat_Analysis1_need->height * percentage) / 2;
    int count_height = testPaperMat_Analysis1_need->height * percentage;
    CvRect rect2;
    rect2.x = 0;
    rect2.y = start_y_axis;
    rect2.width = testPaperMat_Analysis1_need->width;
    rect2.height = count_height;
    if (rect2.width < 0 || rect2.height < 0)
    {
        return NULL;
    }
    CvRect rect3;
    rect3.x = 0;
    rect3.y = start_y_axis;
    rect3.width = testPaperMat_Analysis1_need->width;
    rect3.height = count_height;
    if (rect3.width < 0 || rect3.height < 0)
    {
        return NULL;
    }
    CvMat *testPaperMat_Analysis3 = cvCreateMatHeader(rect3.height, rect3.width, CV_MAKETYPE(testPaperMat_Analysis1_need->depth, testPaperMat_Analysis1_need->nChannels));
    cvGetSubRect(testPaperMat_Analysis1_need, testPaperMat_Analysis3, rect3);
    QString strPathFileName1 = piture_root_str + "\\" + analysised_piture_path1 + "\\tmp" + file_path + ".png";
    cvSaveImage(strPathFileName1.toStdString().data(), testPaperMat_Analysis3);
    IplImage* imgTestPaper5;
    IplImage *image = cvLoadImage(strPathFileName1.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    channelSeq = image->channelSeq;
    if (channelSeq == "GRAY")
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        imgTestPaper5 = image;
    }
    else
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        cvCvtColor(image, srcGray, CV_BGR2GRAY);
        imgTestPaper5 = srcGray;
    }
    return imgTestPaper5;

}

IplImage* PictureAnalysis::GetTestPaperImage_new_HuoFu20230228(QString file_path, int& start_pix_position, TestPaperParameter testPaperParameter)
{
    double dWidthRatio = 0;
    dWidthRatio = testPaperParameter.rect_Analysis_width;
    double paper_length = testPaperParameter.dTotalLenght;
    double paper_length_pix = testPaperParameter.dTotalLenght*dWidthRatio;
    bool bResult = true;
    auto dao = AnalysisDao::instance();
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName = strPath + "\\" + file_path + ".png";
    QFileInfo fileInfo(strPathFileName);
    int head_length = 0;
    head_length = testPaperParameter.head_length;
    int company_id = testPaperParameter.company_id;
    int find_characteristic_number = 1;
    find_characteristic_number = testPaperParameter.left_judge_value;
    double thresh = testPaperParameter.rect_Analysis_x;

    double thresh1 = testPaperParameter.rect_Analysis_height;
    if (!fileInfo.isFile())
    {
        return nullptr;
    }
    QString analysised_piture_path1 = "analysised";
    QString strPathFileName_new = piture_root_str + "\\" + analysised_piture_path1 + "\\" + file_path + "_new1" + ".png";
    QString strPathFileName_last = piture_root_str + "\\" + analysised_piture_path1 + "\\" + file_path + "" + ".png";
    RotatePng_20231206(strPathFileName, strPathFileName_new, strPathFileName_last, head_length, find_characteristic_number, thresh, thresh1, paper_length_pix, company_id);
    IplImage *testPaperMat_Analysis1_need = cvLoadImage(strPathFileName_last.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    IplImage  *srcGray;
    QString channelSeq = "";
    if (testPaperMat_Analysis1_need == NULL)
    {
        return NULL;
    }
    IplImage* imgTestPaper1 = cvCreateImage(cvGetSize(testPaperMat_Analysis1_need), 8, 1);
    double percentage = testPaperParameter.analysis_height_percentage / 100;
    int start_y_axis = 0 + (testPaperMat_Analysis1_need->height - testPaperMat_Analysis1_need->height * percentage) / 2;
    int count_height = testPaperMat_Analysis1_need->height * percentage;
    CvRect rect2;
    rect2.x = 0;
    rect2.y = start_y_axis;
    rect2.width = testPaperMat_Analysis1_need->width;
    rect2.height = count_height;
    if (rect2.width < 0 || rect2.height < 0)
    {
        return NULL;
    }
    CvRect rect3;
    rect3.x = 0;
    rect3.y = start_y_axis;
    rect3.width = testPaperMat_Analysis1_need->width;
    rect3.height = count_height;
    if (rect3.width < 0 || rect3.height < 0)
    {
        return NULL;
    }
    CvMat *testPaperMat_Analysis3 = cvCreateMatHeader(rect3.height, rect3.width, CV_MAKETYPE(testPaperMat_Analysis1_need->depth, testPaperMat_Analysis1_need->nChannels));
    cvGetSubRect(testPaperMat_Analysis1_need, testPaperMat_Analysis3, rect3);
    QString strPathFileName1 = piture_root_str + "\\" + analysised_piture_path1 + "\\tmp" + file_path + ".png";
    cvSaveImage(strPathFileName1.toStdString().data(), testPaperMat_Analysis3);
    IplImage* imgTestPaper5;
    IplImage *image = cvLoadImage(strPathFileName1.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    channelSeq = image->channelSeq;
    if (channelSeq == "GRAY")
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        imgTestPaper5 = image;
    }
    else
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        cvCvtColor(image, srcGray, CV_BGR2GRAY);
        imgTestPaper5 = srcGray;
    }
    return imgTestPaper5;
}

IplImage* PictureAnalysis::GetTestPaperImage_new_He(QString file_path, int& start_pix_position, TestPaperParameter testPaperParameter)
{
    bool bResult = true;
    auto dao = AnalysisDao::instance();
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName = strPath + "\\" + file_path + ".png";
    QFileInfo fileInfo(strPathFileName);
    int head_length = 0;
    head_length = testPaperParameter.head_length;
    if (!fileInfo.isFile())
    {
        return nullptr;
    }
    IplImage *image = cvLoadImage(strPathFileName.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    IplImage* pImage8uSmooth;
    IplImage  *srcGray;
    QString channelSeq = "";
    channelSeq = image->channelSeq;
    if (channelSeq == "GRAY")
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        pImage8uSmooth = image;
    }
    else
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        cvCvtColor(image, srcGray, CV_BGR2GRAY);
        pImage8uSmooth = srcGray;
    }
    CvRect rect_Analysis;
    rect_Analysis.x = testPaperParameter.rect_Analysis_x;
    rect_Analysis.y = testPaperParameter.rect_Analysis_y;
    rect_Analysis.width = testPaperParameter.rect_Analysis_width;
    rect_Analysis.height = testPaperParameter.rect_Analysis_height;
    if (rect_Analysis.width < 0 || rect_Analysis.height < 0)
    {
        return NULL;
    }
    CvMat *testPaperMat_Analysis1 = cvCreateMatHeader(rect_Analysis.height, rect_Analysis.width, CV_MAKETYPE(srcGray->depth, srcGray->nChannels));
    cvGetSubRect(pImage8uSmooth, testPaperMat_Analysis1, rect_Analysis);
    QString analysised_piture_path = "analysised";
    strPath = piture_root_str + "\\" + analysised_piture_path;
    strPathFileName = strPath + "\\" + file_path + ".png";
    QDir dir;
    if (!dir.exists(strPath))
    {
        dir.mkpath(strPath);
    }
    cvSaveImage(strPathFileName.toStdString().data(), testPaperMat_Analysis1);
    IplImage *image_need = cvLoadImage(strPathFileName.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    IplImage* pImage8uSmooth_need;
    IplImage  *srcGray_need;

    channelSeq = image_need->channelSeq;
    if (channelSeq == "GRAY")
    {
        int channel = 1;
        int depth = image_need->depth;
        CvSize sz;
        sz.width = image_need->width;
        sz.height = image_need->height;
        srcGray_need = cvCreateImage(sz, depth, channel);
        pImage8uSmooth_need = image_need;
    }
    else
    {
        int channel = 1;
        int depth = image_need->depth;
        CvSize sz;
        sz.width = image_need->width;
        sz.height = image_need->height;
        srcGray_need = cvCreateImage(sz, depth, channel);
        cvCvtColor(image_need, srcGray_need, CV_BGR2GRAY);
        pImage8uSmooth_need = srcGray_need;
    }
    int nTestPaperTop = GetTestPaperTop_New(pImage8uSmooth_need);
    int nTestPaperBottom = GetTestPaperBottom(pImage8uSmooth_need);
    int nTestPaperLeft = GetTestPaperLeft_New_pic2(pImage8uSmooth_need, nTestPaperTop, nTestPaperBottom, testPaperParameter.left_judge_value);
    int nTestPaperRight = GetTestPaperRight_New(pImage8uSmooth_need, nTestPaperTop, nTestPaperBottom);
    CvRect rect3_need;
    rect3_need.x = nTestPaperLeft - head_length;
    rect3_need.y = nTestPaperTop;
    rect3_need.width = nTestPaperRight - (nTestPaperLeft - head_length);
    rect3_need.height = nTestPaperBottom - nTestPaperTop;
    if (rect3_need.width < 0 || rect3_need.height < 0)
    {
        return NULL;
    }
    CvMat *testPaperMat_Analysis1_need = cvCreateMatHeader(rect3_need.height, rect3_need.width, CV_MAKETYPE(srcGray_need->depth, srcGray_need->nChannels));
    cvGetSubRect(pImage8uSmooth_need, testPaperMat_Analysis1_need, rect3_need);
    QDir dir1;
    if (!dir1.exists(strPath))
    {
        dir1.mkpath(strPath);
    }
    cvSaveImage(strPathFileName.toStdString().data(), testPaperMat_Analysis1_need);
    IplImage* imgTestPaper1 = cvCreateImage(cvGetSize(testPaperMat_Analysis1_need), 8, 1);
    double percentage = testPaperParameter.analysis_height_percentage / 100;
    int start_y_axis = 0 + (testPaperMat_Analysis1_need->height - testPaperMat_Analysis1_need->height * percentage) / 2;
    int count_height = testPaperMat_Analysis1_need->height * percentage;
    CvRect rect2;
    rect2.x = 0;
    rect2.y = start_y_axis;
    rect2.width = testPaperMat_Analysis1_need->width;
    rect2.height = count_height;
    if (rect2.width < 0 || rect2.height < 0)
    {
        return NULL;
    }
    IplImage* imgTestPaper3 ;
    image = cvLoadImage(strPathFileName.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    channelSeq = image->channelSeq;
    if (channelSeq == "GRAY")
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        imgTestPaper3 = image;
    }
    else
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        cvCvtColor(image, srcGray, CV_BGR2GRAY);
        imgTestPaper3 = srcGray;
    }
    nTestPaperTop = 0;
    nTestPaperBottom = imgTestPaper3->height;
    nTestPaperLeft = GetTestPaperLeft_New_pic2(imgTestPaper3, nTestPaperTop, nTestPaperBottom, testPaperParameter.left_judge_value);
    nTestPaperRight = GetTestPaperRight_New(imgTestPaper3, nTestPaperTop, nTestPaperBottom);
    CvRect rect3;
    rect3.x = 0;
    rect3.y = start_y_axis;
    rect3.width = testPaperMat_Analysis1_need->width;
    rect3.height = count_height;
    if (rect3.width < 0 || rect3.height < 0)
    {
        return NULL;
    }
    CvMat *testPaperMat_Analysis3 = cvCreateMatHeader(rect3.height, rect3.width, CV_MAKETYPE(srcGray->depth, srcGray->nChannels));
    cvGetSubRect(testPaperMat_Analysis1_need, testPaperMat_Analysis3, rect3);
    QString strPathFileName1 = strPath + "\\tmp" + file_path + ".png";
    cvSaveImage(strPathFileName1.toStdString().data(), testPaperMat_Analysis3);
    IplImage* imgTestPaper5;
    image = cvLoadImage(strPathFileName1.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    channelSeq = image->channelSeq;
    if (channelSeq == "GRAY")
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        imgTestPaper5 = image;
    }
    else
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        cvCvtColor(image, srcGray, CV_BGR2GRAY);
        imgTestPaper5 = srcGray;
    }
    return imgTestPaper5;
}


IplImage* PictureAnalysis::GetTestPaperImage_new_He_20221027_back(QString file_path, int& start_pix_position, TestPaperParameter testPaperParameter)
{
    bool bResult = true;
    auto dao = AnalysisDao::instance();
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName = strPath + "\\" + file_path + ".png";
    QFileInfo fileInfo(strPathFileName);
    if (!fileInfo.isFile())
    {
        return nullptr;
    }
    IplImage *image = cvLoadImage(strPathFileName.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    IplImage* pImage8uSmooth;
    IplImage  *srcGray;
    QString channelSeq = "";
    channelSeq = image->channelSeq;
    if (channelSeq == "GRAY")
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        pImage8uSmooth = image;
    }
    else
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        cvCvtColor(image, srcGray, CV_BGR2GRAY);
        pImage8uSmooth = srcGray;
    }
    CvRect rect_Analysis;
    rect_Analysis.x = testPaperParameter.rect_Analysis_x;
    rect_Analysis.y = testPaperParameter.rect_Analysis_y;
    rect_Analysis.width = testPaperParameter.rect_Analysis_width;
    rect_Analysis.height = testPaperParameter.rect_Analysis_height;
    if (rect_Analysis.width < 0 || rect_Analysis.height < 0)
    {
        return NULL;
    }
    CvMat *testPaperMat_Analysis1 = cvCreateMatHeader(rect_Analysis.height, rect_Analysis.width, CV_MAKETYPE(srcGray->depth, srcGray->nChannels));
    cvGetSubRect(pImage8uSmooth, testPaperMat_Analysis1, rect_Analysis);
    QString analysised_piture_path = "analysised";
    strPath = piture_root_str + "\\" + analysised_piture_path;
    strPathFileName = strPath + "\\" + file_path + ".png";
    QDir dir;
    if (!dir.exists(strPath))
    {
        dir.mkpath(strPath);
    }
    cvSaveImage(strPathFileName.toStdString().data(), testPaperMat_Analysis1);
    IplImage* imgTestPaper1 = cvCreateImage(cvGetSize(testPaperMat_Analysis1), 8, 1);
    double percentage = testPaperParameter.analysis_height_percentage / 100;
    int start_y_axis = 0 + (testPaperMat_Analysis1->height - testPaperMat_Analysis1->height * percentage) / 2;
    int count_height = testPaperMat_Analysis1->height * percentage;
    CvRect rect2;
    rect2.x = 0;
    rect2.y = start_y_axis;
    rect2.width = testPaperMat_Analysis1->width;
    rect2.height = count_height;
    if (rect2.width < 0 || rect2.height < 0)
    {
        return NULL;
    }
    CvMat *testPaperMat_Analysis2 = cvCreateMatHeader(rect2.height, rect2.width, CV_MAKETYPE(srcGray->depth, srcGray->nChannels));
    cvGetSubRect(testPaperMat_Analysis1, testPaperMat_Analysis2, rect2);
    cvSaveImage(strPathFileName.toStdString().data(), testPaperMat_Analysis2);
    IplImage* imgTestPaper3;
    image = cvLoadImage(strPathFileName.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    channelSeq = image->channelSeq;
    if (channelSeq == "GRAY")
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        imgTestPaper3 = image;
    }
    else
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        cvCvtColor(image, srcGray, CV_BGR2GRAY);
        imgTestPaper3 = srcGray;
    }
    int nTestPaperTop = 0;
    int nTestPaperBottom = imgTestPaper3->height;
    int nTestPaperLeft = GetTestPaperLeft_New_pic2(imgTestPaper3, nTestPaperTop, nTestPaperBottom, testPaperParameter.left_judge_value);
    int nTestPaperRight = GetTestPaperRight_New(imgTestPaper3, nTestPaperTop, nTestPaperBottom);
    CvRect rect3;
    rect3.x = nTestPaperLeft;
    rect3.y = nTestPaperTop;
    rect3.width = nTestPaperRight - nTestPaperLeft;
    rect3.height = nTestPaperBottom - nTestPaperTop;
    if (rect3.width < 0 || rect3.height < 0)
    {
        return NULL;
    }
    CvMat *testPaperMat_Analysis3 = cvCreateMatHeader(rect3.height, rect3.width, CV_MAKETYPE(srcGray->depth, srcGray->nChannels));
    cvGetSubRect(testPaperMat_Analysis2, testPaperMat_Analysis3, rect3);
    QString strPathFileName1 = strPath + "\\tmp" + file_path + ".png";
    cvSaveImage(strPathFileName1.toStdString().data(), testPaperMat_Analysis3);
    IplImage* imgTestPaper5;
    image = cvLoadImage(strPathFileName1.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    channelSeq = image->channelSeq;
    if (channelSeq == "GRAY")
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        imgTestPaper5 = image;
    }
    else
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        cvCvtColor(image, srcGray, CV_BGR2GRAY);
        imgTestPaper5 = srcGray;
    }
    int head_length = 0;
    if (testPaperParameter.head_length != 0)
    {
        head_length = testPaperParameter.head_length;
        nTestPaperLeft -= head_length;
    }
    CvRect rect4;
    rect4.x = nTestPaperLeft;
    rect4.y = nTestPaperTop;
    rect4.width = nTestPaperRight - nTestPaperLeft;
    rect4.height = testPaperMat_Analysis1->height;
    if (rect4.width < 0 || rect4.height < 0)
    {
        return NULL;
    }
    CvMat *testPaperMat_Analysis4 = cvCreateMatHeader(rect4.height, rect4.width, CV_MAKETYPE(srcGray->depth, srcGray->nChannels));
    cvGetSubRect(testPaperMat_Analysis1, testPaperMat_Analysis4, rect4);
    cvSaveImage(strPathFileName.toStdString().data(), testPaperMat_Analysis4);
    return imgTestPaper5;
}

IplImage* PictureAnalysis::GetTestPaperImage_new1(QString file_path, int& start_pix_position)
{
    bool bResult = true;
    auto dao = AnalysisDao::instance();
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName = strPath + "\\" + file_path + ".png";
    QFileInfo fileInfo(strPathFileName);
    if (!fileInfo.isFile())
    {
        return nullptr;
    }
    IplImage *image = cvLoadImage(strPathFileName.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    IplImage* pImage8uSmooth;
    IplImage  *srcGray;
    QString channelSeq = "";
    channelSeq = image->channelSeq;
    if (channelSeq == "GRAY")
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        pImage8uSmooth = image;
    }
    else
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        cvCvtColor(image, srcGray, CV_BGR2GRAY);
        pImage8uSmooth = srcGray;
    }
    int nTestPaperTop = GetTestPaperTop(pImage8uSmooth);
    int nTestPaperBottom = GetTestPaperBottom(pImage8uSmooth);
    int nTestPaperLeft = GetTestPaperLeft(pImage8uSmooth, nTestPaperTop, nTestPaperBottom);
    start_pix_position = nTestPaperLeft;
    int TestPaperLeft_Analysis = nTestPaperLeft;
    if (nTestPaperLeft > 128 || (nTestPaperLeft - 128 > 0))
    {
        nTestPaperLeft = nTestPaperLeft - 128;
    }
    nTestPaperLeft = 0;
    int nTestPaperRight = GetTestPaperRight(pImage8uSmooth, nTestPaperTop, nTestPaperBottom);
    CvRect rect;
    rect.x = nTestPaperLeft;
    rect.y = nTestPaperTop;
    rect.width = nTestPaperRight - nTestPaperLeft;
    rect.height = nTestPaperBottom - nTestPaperTop;
    CvRect rect_Analysis;
    rect_Analysis.x = TestPaperLeft_Analysis;
    rect_Analysis.y = nTestPaperTop;
    rect_Analysis.width = nTestPaperRight - nTestPaperLeft - TestPaperLeft_Analysis;
    rect_Analysis.height = nTestPaperBottom - nTestPaperTop;
    if (rect.width < 0 || rect.height < 0)
    {
        return NULL;
    }
    CvMat *testPaperMat = cvCreateMatHeader(rect.height, rect.width, CV_MAKETYPE(srcGray->depth, srcGray->nChannels));
    CvMat *testPaperMat_Analysis = cvCreateMatHeader(rect_Analysis.height, rect_Analysis.width, CV_MAKETYPE(srcGray->depth, srcGray->nChannels));
    cvGetSubRect(pImage8uSmooth, testPaperMat, rect);
    cvGetSubRect(pImage8uSmooth, testPaperMat_Analysis, rect_Analysis);
    QString analysised_piture_path = "analysised";
    strPath = piture_root_str + "\\" + analysised_piture_path;
    strPathFileName = strPath + "\\" + file_path + ".png";
    QDir dir;
    if (!dir.exists(strPath))
    {
        dir.mkpath(strPath);
    }
    cvSaveImage(strPathFileName.toStdString().data(), testPaperMat_Analysis);
    IplImage* imgTestPaper = cvCreateImage(cvGetSize(testPaperMat_Analysis), 8, 1);
    cvGetImage(testPaperMat_Analysis, imgTestPaper);
    return imgTestPaper;
}

IplImage* PictureAnalysis::GetTestPaperImage(QString file_path)
{
    bool bResult = true;
    auto dao = AnalysisDao::instance();
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName = strPath + "\\" + file_path + ".png";
    QFileInfo fileInfo(strPathFileName);
    if (!fileInfo.isFile())
    {
        return nullptr;
    }
    IplImage *image = cvLoadImage(strPathFileName.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    IplImage* pImage8uSmooth;
    IplImage  *srcGray;
    QString channelSeq = "";
    channelSeq = image->channelSeq;
    if (channelSeq == "GRAY")
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        pImage8uSmooth = image;
    }
    else
    {
        int channel = 1;
        int depth = image->depth;
        CvSize sz;
        sz.width = image->width;
        sz.height = image->height;
        srcGray = cvCreateImage(sz, depth, channel);
        cvCvtColor(image, srcGray, CV_BGR2GRAY);
        pImage8uSmooth = srcGray;
    }
    int nTestPaperTop = GetTestPaperTop(pImage8uSmooth);
    int nTestPaperBottom = GetTestPaperBottom(pImage8uSmooth);
    int nTestPaperLeft = GetTestPaperLeft(pImage8uSmooth, nTestPaperTop, nTestPaperBottom);
    if (nTestPaperLeft > 128 || (nTestPaperLeft-128>0))
    {
        nTestPaperLeft = nTestPaperLeft - 128;
    }
    if (nTestPaperLeft - 128 < 0)
    {
        nTestPaperLeft = 0;
    }
    int nTestPaperRight = GetTestPaperRight(pImage8uSmooth, nTestPaperTop, nTestPaperBottom);
    CvRect rect;
    rect.x = nTestPaperLeft;
    rect.y = nTestPaperTop;
    rect.width = nTestPaperRight - nTestPaperLeft;
    rect.height = nTestPaperBottom - nTestPaperTop;
    if (rect.width < 0 || rect.height < 0)
    {
        return NULL;
    }
    CvMat *testPaperMat = cvCreateMatHeader(rect.height,rect.width,CV_MAKETYPE(srcGray->depth, srcGray->nChannels));
    cvGetSubRect(pImage8uSmooth, testPaperMat, rect);
    QString analysised_piture_path = "analysised";
    strPath = piture_root_str + "\\" + analysised_piture_path;
    strPathFileName = strPath + "\\" + file_path + ".png";
    QDir dir;
    if (!dir.exists(strPath))
    {
        dir.mkpath(strPath);
    }
    cvSaveImage(strPathFileName.toStdString().data(), testPaperMat);
    IplImage* imgTestPaper = cvCreateImage(cvGetSize(testPaperMat), 8, 1);
    cvGetImage(testPaperMat, imgTestPaper);
    return imgTestPaper;
}

int  PictureAnalysis::AnalysisTestPaperImage(IplImage  *imgTestPaper,QString testId,TestPaperParameter testPaperParameter,TestPaperParameter &testPaperReal,int start_pix_position)
{
    int head_length = 0;
    head_length = testPaperParameter.head_length;
    testPaperReal.dTotalLenght = imgTestPaper->width;
    double dWidthRatio = 0;
    if (testPaperParameter.rect_Analysis_width < 30)
    {
        dWidthRatio = testPaperParameter.rect_Analysis_width;//18.61
    }
    else
    {
        dWidthRatio = double(imgTestPaper->width - head_length) / testPaperParameter.dTotalLenght;
    }
    testPaperReal.dOneTestItemLenght = dWidthRatio * testPaperParameter.dOneTestItemLenght;//膜条横置时y向 18.61*0.7
    testPaperReal.dTestItemAreaTotalLenght = dWidthRatio * testPaperParameter.dTestItemAreaTotalLenght;
    testPaperReal.dFunctonalControlPosition = dWidthRatio * testPaperParameter.dFunctonalControlPosition;
    testPaperReal.strTestPaperName = testPaperParameter.strTestPaperName;
    testPaperReal.nTotalNumber = testPaperParameter.nTotalNumber;
    testPaperReal.nTestItemNumber = testPaperParameter.nTestItemNumber;
    testPaperReal.nTestItemBlankNumber = testPaperParameter.nTestItemBlankNumber;
    testPaperReal.articleNo = testPaperParameter.articleNo;
    testPaperReal.paperId = testPaperParameter.paperId;
    testPaperReal.solutionName = testPaperParameter.solutionName;
    testPaperReal.manageName = testPaperParameter.manageName;
    testPaperReal.sampleId = testPaperParameter.sampleId;
    testPaperReal.Id = testId;
    int return_value = 88;
    for (int i = 0; i < 32; i++)
    {
        testPaperReal.strTestItemName[i] = testPaperParameter.strTestItemName[i];
        testPaperReal.isNullArea[i] = testPaperParameter.isNullArea[i];
    }
    int nTotalNumber = 1 + testPaperReal.nTestItemNumber + testPaperReal.nTestItemBlankNumber;//1
    //double fDistance = testPaperReal.dTestItemAreaTotalLenght / double(nTotalNumber);
    //double dOneWhiteAreaLenght = fDistance - testPaperReal.dOneTestItemLenght;
    //int nSliceWidth = testPaperReal.dOneTestItemLenght;
    int nPostionY = imgTestPaper->height * 0.1;//0.1
    int nSliceHeight = imgTestPaper->height ;
    //double nBackgroundLeft = 0;
    //double nBackgroundRight = 0;
    //double nBackground = 0;
    //int nPostionX = 0;
    double dFunctonalControlGrayValue = 0;
    int nPostion0 = testPaperReal.dFunctonalControlPosition;//质控线 51.8
    nPostion0 += head_length;
    int left_position = nPostion0 - testPaperReal.dOneTestItemLenght;
    int right_position = nPostion0 + testPaperReal.dOneTestItemLenght;
    bool bResult;
    auto dao = AnalysisDao::instance();
    bResult = dao->Insert_tresult_left_right_pixp(testId, 0, left_position, right_position,"FC", (imgTestPaper->height / 2) - 2, nSliceHeight);
    int error_code = 0;
    //获取质控线的灰度
    dFunctonalControlGrayValue = GetAverage_new_max_para20231121(imgTestPaper, nPostion0, nPostionY, (testPaperReal.dOneTestItemLenght), nSliceHeight, testPaperParameter,error_code);
    testPaperReal.dItemErrorCode[0] = error_code;
    testPaperReal.dItemPosition[0] = nPostion0;
    testPaperReal.dItemGrayValue[0] = dFunctonalControlGrayValue;//质控线灰度值
    if (testPaperReal.dItemGrayValue[0] > m_nControlThreshold)//m_nControlThreshold为设置的质控线灰度值 200
    {
        return_value = 81;
    }
    int start_i = 1;
    if (testPaperParameter.isCutOff == 0)
    {
        start_i = 2;
        testPaperParameter.dItemPosition[1] = -testPaperParameter.cutoff_value_user;
        testPaperReal.dItemGrayValue[1] = testPaperParameter.cutoff_value_user;
        testPaperReal.dItemGrayRatio[1] = 1;
        testPaperReal.dItemErrorCode[1] = 0;
    }

    for (int i = start_i; i <= nTotalNumber; i++)
    {
        double itemGrayValueAverage = 0;
        double dItemPosition = 0;
        dItemPosition = testPaperParameter.dItemPosition[i] * dWidthRatio+ head_length;

        if (dItemPosition > imgTestPaper->width)
        {
            dItemPosition = imgTestPaper->width - 50;
        }

        left_position = dItemPosition - testPaperReal.dOneTestItemLenght;
        right_position = dItemPosition + testPaperReal.dOneTestItemLenght;
        int position_index = i;
        bool bResult;
        auto dao = AnalysisDao::instance();
        bResult = dao->Insert_tresult_left_right_pixp(testId, position_index, left_position, right_position, testPaperReal.strTestItemName[i], (imgTestPaper->height / 2) - 2, nSliceHeight);
        error_code = 0;
        //itemGrayValueAverage = GetAverage_new_max_para20231121(imgTestPaper, dItemPosition, nPostionY, testPaperReal.dOneTestItemLenght, nSliceHeight, testPaperParameter, error_code);
        //c=0的时候灰度值为本底色值，g=12.946718
        //double referenceGrayValue= 12.946718;
        double referenceGrayValue= 13.54521;
        //项目旁最大亮度值 与 理论值进行比较得出补偿值
        double maxGrayValue = getAverage_maxGray(imgTestPaper, referenceGrayValue,dItemPosition, nPostionY, testPaperReal.dOneTestItemLenght, nSliceHeight, testPaperParameter);
        double compensate = 256-referenceGrayValue - maxGrayValue;//正数偏暗  负数偏亮
        itemGrayValueAverage = GetAverage_new_max_para(imgTestPaper, referenceGrayValue,dItemPosition, nPostionY, testPaperReal.dOneTestItemLenght, nSliceHeight, testPaperParameter);

        testPaperReal.dItemErrorCode[i] = error_code;
        testPaperReal.dItemGrayValue[i] = itemGrayValueAverage+compensate;//补偿后的值
        testPaperReal.dItemPosition[i] = dItemPosition;
        if (i == 1)
        {
            if (testPaperReal.dItemGrayValue[i] > m_nCutOffThreshold)
            {
                return_value = 82;
            }
        }
        double cutoff_value = testPaperReal.dItemGrayValue[1];
        double a_cutoff = 5;
        double b = 3;
        double c = 1.44444;

        if(testPaperParameter.paperId == 929||testPaperParameter.paperId == 930){
            double grayValue = 255-testPaperReal.dItemGrayValue[i];//亮度值转变为灰度值

            //方程: y = (A - D) / [1 + (x/C)^B] + D    x浓度  y灰度
            //------------------------------------------------------------------
            double A    =      459.25799;
            double B    =       -0.73845;
            double C    =      256.09656;
            double D    =       13.54521;
            //r^2  =        0.99840
            //本地灰度映射到艾康灰度
            //double aconGrayValue = 4*qPow(10,-5)*qPow(grayValue,3) + 0.0037*qPow(grayValue,2) - 0.5254*grayValue + 12.876;
            //c = qPow(10,1.6037*qLn(aconGrayValue)-1.0707);
            // std::cout<<"grayValue "<<grayValue<<"    aconGrayValue "<<aconGrayValue<<"    c "<<c<<endl;
            //c = -5*qPow(10,-5)*qPow(grayValue,3)+0.0116*qPow(grayValue,2)-0.5042*grayValue+6.0304;
            //c =-1*qPow(10,-5)*qPow(grayValue,3)+0.006*qPow(grayValue,2)-0.2373*grayValue+2.462;  //多项式拟合效果较好的参数
            //-4*10^-8*x^4+2*10^-6*x^3+0.0048*x^2-0.1938*x+1.9234
            //2.742423
            //c =  -7.50597 + (116.52688 +7.50597) / (1 + qPow(M_E,-0.02446*grayValue + 3.05910));
            if((grayValue - D)<=0){
                c=0;
            }else{
                c=exp(log(((A - D) / (grayValue-D)-1)) / B)*C;
            }

            //std::cout<<"grayValue "<<grayValue<<"    c "<<c<<endl;
            testPaperReal.dItemGrayRatio[i] = c;
            testPaperReal.dItemErrorCode[i] = error_code;
        }
        else{

            if (testPaperParameter.isCutOff == 1)
            {
                a_cutoff = cutoff_value / 255;
                b = (testPaperReal.dItemGrayValue[i]) / 255;
                c = qLn(b) / qLn(a_cutoff);
                testPaperReal.dItemGrayRatio[i] = c;
                testPaperReal.dItemErrorCode[i] = error_code;
            }
            else
            {
                a_cutoff = cutoff_value / 255;
                b = (testPaperReal.dItemGrayValue[i]) / 255;
                c = qLn(b) / qLn(a_cutoff);
                testPaperReal.dItemGrayRatio[i] = c;
                testPaperReal.dItemErrorCode[i] = error_code;
            }
        }
    }
    double a_fun = (testPaperReal.dItemGrayValue[0]) / 255;
    double b_cut = (testPaperReal.dItemGrayValue[1]) / 255;
    double c1 =  qLn(a_fun)/ qLn(b_cut);
    testPaperReal.dItemGrayRatio[0] = c1;
    return return_value;
}

double PictureAnalysis::GetAverage(IplImage  *srcGray,int left,int top,int width,int height)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    unsigned char * imageData;
    imageData = (unsigned char*)srcGray->imageData;
    double aVerage = 0;
    unsigned int sum = 0;
    int count = 0;
    int value = 0;
    for (int j = left; j < (left + width); j++)
    {
        for (int i = top; i < (top + height); i++)
        {
            value = ((uchar*)(srcGray->imageData + srcGray->widthStep*i))[j];
            sum += value;
            count++;
        }
    }
    aVerage = double(sum) / double(width *height);
    return aVerage;
}

double PictureAnalysis::CheckImageIsUseful(IplImage  *srcGray, int left, int top, int width, int height, TestPaperParameter testPaperParameter,int &error_code)
{
    error_code = 0;
    double result = 0;
    int result_sum = 0;
    int value = 0;
    QVector<QVector<double>> data_vector;
    QVector<double> result_vector;
    QVector<double> gray_avg_vector;
    QVector<int> error_vector;

    if (srcGray == NULL || srcGray->imageData == NULL) {
        return 0.0001;
    }

    for (int i = (left - width); i < (left + width); i++)
    {
        double vertical_gray_value_sum = 0;
        double vertical_gray_value_avg = 0;
        for (int j = top; j < (top + height); j++)
        {
            vertical_gray_value_sum += ((uchar*)(srcGray->imageData + srcGray->widthStep*j))[i];
        }
        vertical_gray_value_avg = vertical_gray_value_sum / height;
        gray_avg_vector.push_back(vertical_gray_value_avg);
    }
    double result1;
    result1 = CheckWaveWidth(gray_avg_vector, testPaperParameter.wave_pix_width, testPaperParameter.wave_pix_width_min, testPaperParameter.wave_pix_width_max, testPaperParameter.threshold_value, testPaperParameter.background_values, error_code, testPaperParameter.bg_difference, testPaperParameter.zero_value_coefficient, left,1);
    return result1;
    double result2 = 0;
    double max = 0;
    if (!result_vector.isEmpty()) {
        max = result_vector.at(0);
        for (int i = 1; i < result_vector.size(); i++) {
            if (result_vector.at(i) > max) {
                max = result_vector.at(i);
            }
        }
    }
    double max_value = result_vector.at(0);
    int max_index = 0;
    for (int i = 1; i < result_vector.size(); i++) {
        if (result_vector.at(i) > max_value) {
            max_value = result_vector.at(i);
            max_index = i;
        }
    }
    result_vector.remove(max_index);
    error_vector.remove(max_index);
    double sum1 = 0;
    double avg1 = 0;
    for (size_t i = 0; i < result_vector.size(); i++)
    {
        sum1 += result_vector[i];
    }
    avg1 = (double)sum1 / result_vector.size();

    int abnormal_result_number = 0;
    int valid_point_number = 0;
    int valid_result_sum = 0;
    for (size_t i = 0; i < result_vector.size(); i++)
    {
        if ((abs(avg1 - result_vector[i]) > 20) && error_vector[i]==0)
        {
            abnormal_result_number++;
        }
        else
        {
            valid_result_sum += result_vector[i];
            valid_point_number++;
        }
    }
    if (abnormal_result_number > 1 && abnormal_result_number < 4)
    {
        error_code = 10001;
    }
    else
    {
        error_code = error_vector[error_vector.size()-1];
    }
    result2 = (double)valid_result_sum / valid_point_number;
    return result2;
}

double PictureAnalysis::GetAverage_new_max_para20231121(IplImage  *srcGray, int left, int top, int width, int height, TestPaperParameter testPaperParameter,int &error_code)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    unsigned char * imageData;
    imageData = (unsigned char*)srcGray->imageData;
    double aVerage = 0;
    double aVerage_left = 0;
    double aVerage_right = 0;
    unsigned int sum = 0;
    int count = 0;
    int value = 0;
    QList<double> column_gray_avg_list;
    QList<int> gray_x_list;
    bool result;
    double result1;
    int error_code1 = 0;
    result1 = CheckImageIsUseful(srcGray, left, top, width, height, testPaperParameter, error_code1);
    error_code = error_code1;
    return result1;//?

    for (int j = (left - width); j < left; j++)
    {
        int column_sum = 0;
        int column_number = 0;
        for (int i = top; i < (top + height); i++)
        {
            value = ((uchar*)(srcGray->imageData + srcGray->widthStep*i))[j];
            if (value == 255)
            {
                value = 254.9;
            }
            sum += value;
            count++;
            column_sum += value;
            column_number++;
        }
        gray_x_list.append(j);
        double column_avg = double(column_sum) / double(column_number);
        column_gray_avg_list.append(column_avg);
    }
    aVerage_left = double(sum) / double(count);
    sum = 0;
    count = 0;
    for (int j = left; j < (left + width); j++)
    {
        int column_sum = 0;
        int column_number = 0;
        for (int i = top; i < (top + height); i++)
        {
            value = ((uchar*)(srcGray->imageData + srcGray->widthStep*i))[j];
            sum += value;
            count++;
            column_sum += value;
            column_number++;
        }
        gray_x_list.append(j);
        double column_avg = double(column_sum) / double(column_number);
        column_gray_avg_list.append(column_avg);
    }
    double min_value = GetMinValue(column_gray_avg_list);
    int min_index = column_gray_avg_list.indexOf(min_value);
    QMap<int, double> position_gray_map;
    position_gray_map = GetNeedAvgMap(column_gray_avg_list, min_index, min_value, testPaperParameter);
    int delete_min_number = testPaperParameter.find_min_times;
    if (delete_min_number <= 0)
    {
        delete_min_number = 3;
    }
    if (delete_min_number > 10)
    {
        delete_min_number = 3;
    }
    for (size_t i = 0; i < delete_min_number; i++)
    {
        if (position_gray_map.size() == 0)
        {
        }
        else
        {
            i = delete_min_number;
        }
    }
    sum = 0;
    double sum1 = 0;
    QMap<int, double>::iterator iter = position_gray_map.begin();
    while (iter != position_gray_map.end())
    {
        sum1 += iter.value();
        iter++;
    }
    if (position_gray_map.size() > 0)
    {
        aVerage = sum1 / position_gray_map.size();
    }
    else
    {
        double area_gray_value_sum = 0;
        for (size_t i1 = 0; i1 < column_gray_avg_list.size(); i1++)
        {
            area_gray_value_sum += column_gray_avg_list.at(i1);
        }
        aVerage = area_gray_value_sum / column_gray_avg_list.size();
    }
    return aVerage;
}

//获取某个项目旁边最亮的色值
double PictureAnalysis::getAverage_maxGray(IplImage  *srcGray, double referenceGrayValue, int left, int top, int width, int height, TestPaperParameter testPaperParameter){
    unsigned char * imageData;
    imageData = (unsigned char*)srcGray->imageData;
    double aVerage_left = 0;
    unsigned int sum = 0;
    int count = 0;
    int value = 0;
    QList<double> column_gray_avg_list;
    QList<int> gray_x_list;
    for (int j = (left - width); j < left; j++)
    {
        int column_sum = 0;
        int column_number = 0;
        for (int i = top; i < (top + height); i++)
        {
            value = ((uchar*)(srcGray->imageData + srcGray->widthStep*i))[j];
            if (value == 255)
            {
                value = 254.9;
            }
            sum += value;
            count++;
            column_sum += value;
            column_number++;
        }
        gray_x_list.append(j);
        double column_avg = double(column_sum) / double(column_number);
        column_gray_avg_list.append(column_avg);
    }
    aVerage_left = double(sum) / double(count);
    sum = 0;
    count = 0;

    for (int j = left; j < (left + width); j++)
    {
        int column_sum = 0;
        int column_number = 0;
        for (int i = top; i < (top + height); i++)
        {
            value = ((uchar*)(srcGray->imageData + srcGray->widthStep*i))[j];
            sum += value;
            count++;
            column_sum += value;
            column_number++;
        }
        gray_x_list.append(j);
        double column_avg = double(column_sum) / double(column_number);
        column_gray_avg_list.append(column_avg);
    }
    std::sort(column_gray_avg_list.begin(), column_gray_avg_list.end());
    if(testPaperParameter.paperId==929){
        if(column_gray_avg_list.size()<15){
            return aVerage_left;
        }

        return  (column_gray_avg_list[column_gray_avg_list.size()-1]
                +column_gray_avg_list[column_gray_avg_list.size()-2]
                + column_gray_avg_list[column_gray_avg_list.size()-3]
                + column_gray_avg_list[column_gray_avg_list.size()-4]
                + column_gray_avg_list[column_gray_avg_list.size()-5]
                + column_gray_avg_list[column_gray_avg_list.size()-6]
                + column_gray_avg_list[column_gray_avg_list.size()-7]
                + column_gray_avg_list[column_gray_avg_list.size()-8]
                + column_gray_avg_list[column_gray_avg_list.size()-9]
                + column_gray_avg_list[column_gray_avg_list.size()-10]
                + column_gray_avg_list[column_gray_avg_list.size()-11]
                + column_gray_avg_list[column_gray_avg_list.size()-12]
                + column_gray_avg_list[column_gray_avg_list.size()-13]
                + column_gray_avg_list[column_gray_avg_list.size()-14]
                + column_gray_avg_list[column_gray_avg_list.size()-15])/15;
    }else if(testPaperParameter.paperId==930){
        if(column_gray_avg_list.size()<5){
            return aVerage_left;
        }
        return  (column_gray_avg_list[column_gray_avg_list.size()-1]
                +column_gray_avg_list[column_gray_avg_list.size()-2]
                + column_gray_avg_list[column_gray_avg_list.size()-3]
                + column_gray_avg_list[column_gray_avg_list.size()-4]
                + column_gray_avg_list[column_gray_avg_list.size()-5])/5;
    }else{
        if(column_gray_avg_list.size()<5){
            return aVerage_left;
        }
        return  (column_gray_avg_list[column_gray_avg_list.size()-1]
                +column_gray_avg_list[column_gray_avg_list.size()-2]
                + column_gray_avg_list[column_gray_avg_list.size()-3]
                + column_gray_avg_list[column_gray_avg_list.size()-4]
                + column_gray_avg_list[column_gray_avg_list.size()-5])/5;
    }

}

double PictureAnalysis::GetAverage_new_max_para(IplImage  *srcGray, double referenceGrayValue, int left, int top, int width, int height, TestPaperParameter testPaperParameter)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    unsigned char * imageData;
    imageData = (unsigned char*)srcGray->imageData;
    double aVerage = 0;
    double aVerage_left = 0;
    double aVerage_right = 0;
    unsigned int sum = 0;
    int count = 0;
    int value = 0;
    QList<double> column_gray_avg_list;
    QList<int> gray_x_list;
    for (int j = (left - width); j < left; j++)
    {
        int column_sum = 0;
        int column_number = 0;
        for (int i = top; i < (top + height); i++)
        {
            value = ((uchar*)(srcGray->imageData + srcGray->widthStep*i))[j];
            if (value == 255)
            {
                value = 254.9;
            }
            sum += value;
            count++;
            column_sum += value;
            column_number++;
        }
        gray_x_list.append(j);
        double column_avg = double(column_sum) / double(column_number);
        column_gray_avg_list.append(column_avg);
    }
    aVerage_left = double(sum) / double(count);
    sum = 0;
    count = 0;

    for (int j = left; j < (left + width); j++)
    {
        int column_sum = 0;
        int column_number = 0;
        for (int i = top; i < (top + height); i++)
        {
            value = ((uchar*)(srcGray->imageData + srcGray->widthStep*i))[j];
            sum += value;
            count++;
            column_sum += value;
            column_number++;
        }
        gray_x_list.append(j);
        double column_avg = double(column_sum) / double(column_number);
        column_gray_avg_list.append(column_avg);
    }
    double min_value = GetMinValue(column_gray_avg_list);//最小灰度值
    int min_index = column_gray_avg_list.indexOf(min_value);//最小灰度值位于第几列
    QMap<int, double> position_gray_map;
    position_gray_map = GetNeedAvgMap(column_gray_avg_list, min_index, min_value, testPaperParameter);//色差在20%以内的数据计入
    int delete_min_number = testPaperParameter.find_min_times;
    if (delete_min_number <= 0)
    {
        delete_min_number = 3;
    }
    if (delete_min_number > 10)
    {
        delete_min_number = 3;
    }
    for (size_t i = 0; i < delete_min_number; i++)
    {
        if (position_gray_map.size() == 0)
        {
        }
        else
        {
            i = delete_min_number;
        }
    }
    sum = 0;
    double sum1 = 0;
    QMap<int, double>::iterator iter = position_gray_map.begin();
    while (iter != position_gray_map.end())
    {
        sum1 += iter.value();
        iter++;
    }
    if (position_gray_map.size() > 0)
    {
        aVerage = sum1 / position_gray_map.size();
    }
    else
    {
        double area_gray_value_sum = 0;
        for (size_t i1 = 0; i1 < column_gray_avg_list.size(); i1++)
        {
            area_gray_value_sum += column_gray_avg_list.at(i1);
        }
        aVerage = area_gray_value_sum/ column_gray_avg_list.size();
    }
    return aVerage;
}




QVector<double> PictureAnalysis::smoothFilter(const QVector<double> &data, int windowSize) {
    QVector<double> result;
    for (int i = 0; i < data.size(); ++i) {
        double sum = 0.0;
        int count = 0;
        for (int j = i - windowSize; j <= i + windowSize; ++j) {
            if (j >= 0 && j < data.size()) {
                sum += data[j];
                count++;
            }
        }
        result.append(sum / count);
    }
    return result;
}


QVector<double> PictureAnalysis::savitzkyGolayFilter(const QVector<double> &data, int windowSize, int polynomialOrder) {
    QVector<double> smoothedData;
    for (int i = 0; i < data.size(); i++) {
        if (i < windowSize / 2 || i >= data.size() - windowSize / 2) {
            smoothedData.append(data[i]);
            continue;
        }
        double sum = 0.0;
        for (int j = -(windowSize / 2); j <= windowSize / 2; j++) {
            sum += data[i + j] * qPow(j, polynomialOrder);
        }
        smoothedData.append(sum / windowSize);
    }
    return smoothedData;
}

QVector<double> PictureAnalysis::meanFilter(const QVector<double> &data, int windowSize) {
    QVector<double> result;
    for (int i = 0; i < data.size(); ++i) {
        double sum = 0.0;
        int count = 0;
        for (int j = i - windowSize / 2; j <= i + windowSize / 2; ++j) {
            if (j >= 0 && j < data.size()) {
                sum += data[j];
                count++;
            }
        }
        result.append(sum / count);
    }
    return result;
}

double PictureAnalysis::calculateAverage(const QVector<double>& data, int n) {
    QVector<double> sortedData_delete = data;
    int delete_number = 2;
    if (n > 20)
    {
        delete_number = 6;
    }
    else if (n > 10 && n < 20)
    {
        delete_number = 3;
    }
    else if (n < 10 && n>6)
    {
        delete_number = 2;
    }
    else if (n < 6 && n>0)
    {
        delete_number = 1;
    }
    if (sortedData_delete.size() > delete_number)
    {
        sortedData_delete.remove(0, delete_number);
        n -= delete_number;
        if (sortedData_delete.size() > delete_number) {
            sortedData_delete.resize(sortedData_delete.size() - delete_number);
            n -= delete_number;
        }
    }
    QVector<double> sortedData = sortedData_delete;
    std::sort(sortedData.begin(), sortedData.end(), std::greater<double>());

    if (sortedData.size() > 2)
    {
        int indexToRemove1 = std::distance(data.begin(), std::find(data.begin(), data.end(), sortedData[0]));
        int indexToRemove2 = std::distance(data.begin(), std::find(data.begin(), data.end(), sortedData[1]));
        int numToRemove = 2;
        if (n <= numToRemove)
        {
            return 9999;
        }
        sortedData.erase(sortedData.begin(), sortedData.begin() + numToRemove);
        n -= numToRemove;
        int startIndex = (sortedData.size() - n) / 2;
        double sum = 0.0;
        for (int i = startIndex; i < startIndex + n; i++) {
            sum += sortedData[i];
        }
        double average = sum / n;
        return average;
    }
    else
    {
        int indexToRemove1 = std::distance(data.begin(), std::find(data.begin(), data.end(), sortedData[0]));
        int indexToRemove2 = std::distance(data.begin(), std::find(data.begin(), data.end(), sortedData[1]));
        int numToRemove = 1;
        if (n <= numToRemove)
        {
            return 9999;
        }
        sortedData.erase(sortedData.begin(), sortedData.begin() + numToRemove);
        std::sort(sortedData.begin(), sortedData.end());
        sortedData.erase(sortedData.begin(), sortedData.begin() + numToRemove);
        n -= numToRemove;
        int startIndex = (sortedData.size() - n) / 2;
        double sum = 0.0;
        for (int i = startIndex; i < startIndex + n; i++) {
            sum += sortedData[i];
        }
        double average = sum / n;
        return average;
    }
}

struct DataPoint {
    size_t index;
    double value;
};

double PictureAnalysis::standardDeviation(const QVector<double>& data) {
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    double variance = 0.0;
    for (auto value : data) {
        variance += pow(value - mean, 2);
    }
    variance /= data.size();
    return sqrt(variance);
}

void PictureAnalysis::saveQVectorToTxt(const QVector<double> &data, const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (int i = 0; i < data.size(); ++i)
        {
            out << data.at(i) << "\n";
        }
        file.close();
    }
}

void PictureAnalysis::saveQVectorToTxt1(const QVector<int> &data, const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (int i = 0; i < data.size(); ++i)
        {
            out << data.at(i) << "\n";
        }
        file.close();
    }
}

void PictureAnalysis::saveQVectorToTxt2(const QVector<double> &data, const QString &fileName,double zero_value)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (int i = 0; i < data.size(); ++i)
        {
            out <<"original:  "<< data.at(i) << "   Baseline:  "<<zero_value <<"   D-value:  "<<(data.at(i)-zero_value)<< "\n";
        }
        file.close();
    }
}

double PictureAnalysis::CheckWaveWidth(const QVector<double> &data, int wave_width, int wave_width_min, int wave_width_max, int threshold_value,int background_values,int &error_code,int bg_difference,double zero_value_coefficient,int pix_position,int call_type)
{
    double result = 0;
    if (data.isEmpty()) {
        return false;
    }
    QString programPath = QCoreApplication::applicationDirPath();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString uniqueTimestamp = QString::number(currentDateTime.toMSecsSinceEpoch());
    uniqueTimestamp.append(QRandomGenerator::global()->generate() % 100000);
    QString save_file_name;
    if (call_type == 1)
    {
        save_file_name = QString("%3\\Data\\%1-%2.xls").arg(pix_position).arg(QRandomGenerator::global()->generate() % 1000000).arg(programPath);
        saveQVectorToTxt(data, save_file_name);
    }
    double mean = 0.0;
    for (double value : data) {
        mean += value;
    }
    mean /= data.size();
    QVector<double> largerThanAverage;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i] > mean) {
            largerThanAverage.append(data[i]);
        }
    }
    double variance = 0.0;
    for (double value : data) {
        variance += (value - mean) * (value - mean);
    }
    variance /= data.size();
    double stdDev = sqrt(variance);
    double thresholdxxx = 2.1 * stdDev;
    if (stdDev < 80)
    {
        thresholdxxx = mean ;
    }
    else
    {
        thresholdxxx = stdDev;
    }
    QVector<double> waveformData;
    QVector<double> waveformData1;
    bool inWaveform = false;
    QVector<int> valid_wave_index;
    bool downWaveform = false;
    bool levelWaveform = false;
    bool upWaveform = false;
    int sum_down = 0;
    int sum_up = 0;
    int sum_level = 0;
    for (int i = 1; i < data.size() - 1; i++) {
        if (!inWaveform && data[i] < thresholdxxx && data[i] < data[i - 1] ) {
            inWaveform = true;
        }
        if (!inWaveform && data[i] < thresholdxxx &&  data[i] < data[i + 1]) {
            inWaveform = true;
        }
        if (inWaveform) {
            waveformData.push_back(data[i]);
            valid_wave_index.push_back(i);
        }
        if (inWaveform && (data[i] < thresholdxxx || (data[i] < data[i - 1] && data[i] < data[i + 1]))) {
            inWaveform = false;
        }
    }
    QVector<double> data1 = data;
    QVector<double> data2_max_zero = data;
    qSort(data1.begin(), data1.end());
    double avg_smallest_value = 0;
    double sum_smallest_value = 0;
    double avg_big_value = 0;
    double sum_big_value = 0;
    QVector<double> smallestValues;
    QVector<double> bigValues;
    for (size_t i = 0; i < 10; i++)
    {
        smallestValues.push_back(data1[i]);
        sum_smallest_value += data1[i];
    }
    avg_smallest_value = sum_smallest_value / 10;
    qSort(data1.begin(), data1.end());
    std::vector<double> largestValues(data1.end() - 10, data1.end());
    for (size_t i = 0; i < 10; i++)
    {
        bigValues.push_back(largestValues[i]);
        sum_big_value += largestValues[i];
    }
    avg_big_value = sum_big_value / 10;
    double zero_value_max = 0.001;
    double zero_value_min = 0;
    double zero_value_sum_max = 0;
    double zero_value_sum_min = 0;
    int zero_start_point_max = data.size()*0.10;
    int zero_start_point_min = data.size()*0.10;
    int zero_length_max  = data.size()*0.10;
    int zero_length_min = data.size()*0.10;
    for (size_t i = data1.size() - (zero_start_point_max+ zero_length_max); i < data1.size()- zero_start_point_max; i++)
    {
        zero_value_sum_max += data1[i];
    }

    for (size_t i = zero_start_point_min; i < zero_start_point_min + zero_length_min; i++)
    {
        zero_value_sum_min += data1[i];
    }
    avg_smallest_value = zero_value_sum_min / zero_length_min;
    zero_value_max = zero_value_sum_max / zero_length_max;
    double find_zero_value = (zero_value_max - avg_smallest_value)*zero_value_coefficient;
    double find_zero_value1 = zero_value_max - find_zero_value;
    QVector<double> data_new1;
    QVector<double> data_new2;
    QVector<double> data_new3;
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i] < find_zero_value1)
        {
            data_new1.push_back(1);
        }
        else
        {
            data_new1.push_back(0);
        }
    }
    data_new2.push_back(0);
    data_new2.push_back(0);
    data_new2.push_back(0);
    for (size_t i = 3; i < data.size(); i++)
    {
        if ((data[i] < data[i - 3]) && (data[i - 3] - data[i]) > bg_difference)
        {
            data_new2.push_back(1);
        }
        else
        {
            data_new2.push_back(0);
        }
    }
    data_new3.push_back(0);
    data_new3.push_back(0);
    data_new3.push_back(0);
    for (size_t i = 3; i < data.size(); i++)
    {
        if ((data[i] > data[i - 3]) && (data[i] - data[i - 3]) > bg_difference)
        {
            data_new3.push_back(1);
        }
        else
        {
            data_new3.push_back(0);
        }
    }
    bool start_point = false;
    QVector<int> start_point_index;
    QVector<int> end_point_index;
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data_new1[i] == 1 && data_new2[i] == 1)
        {
            start_point_index.push_back(i);
        }
    }
    for (size_t i = 2; i < data.size(); i++)
    {
        if (data_new1[i] == 0 && data_new3[i] == 1 )
        {
            end_point_index.push_back(i);
        }
    }
    if (call_type == 1)
    {
        save_file_name = QString("%3\\Data\\start-%1-%2-%4-zero_value_max-%5-avg_smallest_value-%6.xls").arg(pix_position).arg(QRandomGenerator::global()->generate() % 1000000).arg(programPath).arg(find_zero_value1).arg(zero_value_max).arg(avg_smallest_value);
        saveQVectorToTxt1(start_point_index, save_file_name);
        save_file_name = QString("%3\\Data\\end-%1-%2-%4-zero_value_max-%5-avg_smallest_value-%6.xls").arg(pix_position).arg(QRandomGenerator::global()->generate() % 1000000).arg(programPath).arg(find_zero_value1).arg(zero_value_max).arg(avg_smallest_value);
        saveQVectorToTxt1(end_point_index, save_file_name);
    }
    QVector<double> need_data;
    int find_need_start_index = 0;
    int find_need_end_index = 0;
    int wave_group_number = 0;
    wave_group_number = findGroupNumber(start_point_index);
    QVector<int> groups_mins = findGroupNumber_mins(end_point_index);
    QVector<int> groups_maxs = findGroupNumber_maxs(start_point_index);
    if (end_point_index.size() > 1 && start_point_index.size() > 1)
    {
        if (groups_mins.size() == 1 && groups_maxs.size() == 1)
        {
            groups_mins.clear();
            groups_maxs.clear();
            groups_mins.push_back(end_point_index[end_point_index.size() / 2]);
            groups_maxs.push_back(start_point_index[start_point_index.size() / 2]);
        }
    }
    if (end_point_index.size() == 0 || start_point_index.size() == 0)
    {
        error_code = 10002;
        if (zero_value_max == 255)
        {
            zero_value_max = 254.9;
        }
        if (zero_value_max == 0)
        {
            zero_value_max = 0.001;
        }
        return zero_value_max;
    }
    find_need_start_index = 0;
    find_need_end_index = 0;
    int valid_wave_number_i = 0;
    int invalid_wave_number_i = 0;
    int first_position_old = 0;
    int prev_position_old = 0;
    if (groups_mins.size() > 1 && groups_maxs.size() > 1)
    {
        QVector<int> groups_maxs1;
        for (size_t ix = 0; ix < groups_mins.size(); ix++)
        {
            if (groups_maxs.size() > 1 && groups_mins.size() > 0)
            {
                int first_position = groups_mins[ix];
                if (ix > 0)
                {
                    prev_position_old = groups_mins[ix - 1];
                }
                for (int i = 0; i < groups_maxs.size(); i++)
                {
                    if (groups_maxs[i] < first_position)
                    {
                        if (ix == 0)
                        {
                            int wave_lenght_i = 0;
                            wave_lenght_i = first_position - groups_maxs[i];
                            if (wave_lenght_i > 0)
                            {
                                groups_maxs1.push_back(groups_maxs[i]);
                                break;
                            }
                        }
                        else
                        {
                            int wave_lenght_i = 0;
                            wave_lenght_i = first_position - groups_maxs[i];
                            if (wave_lenght_i > 0 && groups_maxs[i] > prev_position_old)
                            {
                                groups_maxs1.push_back(groups_maxs[i]);
                                break;
                            }
                        }
                    }
                }
            }
        }
        groups_maxs = groups_maxs1;
    }


    if (groups_mins.size() > groups_maxs.size() || groups_mins.size() == groups_maxs.size())
    {
        for (size_t i = 0; i < groups_maxs.size(); i++)
        {
            int start_i = groups_mins.at(i);
            int end_i = groups_maxs.at(i);
            int wave_lenght_i = start_i - end_i;
            if (wave_lenght_i > 0)
            {
                if (wave_lenght_i > wave_width_min && wave_lenght_i < wave_width_max)
                {
                    valid_wave_number_i++;
                    if (valid_wave_number_i == 1)
                    {
                        find_need_start_index = end_i;
                        find_need_end_index = start_i;
                    }
                }
                else
                {
                    invalid_wave_number_i++;
                }
            }
            else
            {
                invalid_wave_number_i++;
            }
        }
        if (find_need_start_index == 0 && find_need_end_index == 0)
        {
            valid_wave_number_i = 0;
            invalid_wave_number_i = 0;
            for (size_t i = 0; i < groups_maxs.size(); i++)
            {
                if (((i + 1) < groups_mins.size()))
                {
                    int start_i = groups_mins.at(i + 1);
                    int end_i = groups_maxs.at(i);
                    int wave_lenght_i = start_i - end_i;
                    if (wave_lenght_i > 0)
                    {
                        if (wave_lenght_i > wave_width_min && wave_lenght_i < wave_width_max)
                        {
                            valid_wave_number_i++;
                            if (valid_wave_number_i == 1)
                            {
                                find_need_start_index = end_i;
                                find_need_end_index = start_i;
                            }
                        }
                        else
                        {
                            invalid_wave_number_i++;
                        }
                    }
                    else
                    {
                        invalid_wave_number_i++;
                    }
                }

            }
        }

        if (find_need_start_index == 0 && find_need_end_index == 0)
        {
            valid_wave_number_i = 0;
            invalid_wave_number_i = 0;
            for (size_t i = 0; i < groups_maxs.size(); i++)
            {
                if (((i + 2) < groups_mins.size()))
                {
                    int start_i = groups_mins.at(i + 2);
                    int end_i = groups_maxs.at(i);
                    int wave_lenght_i = start_i - end_i;
                    if (wave_lenght_i > 0)
                    {
                        if (wave_lenght_i > wave_width_min && wave_lenght_i < wave_width_max)
                        {
                            valid_wave_number_i++;
                            if (valid_wave_number_i == 1)
                            {
                                find_need_start_index = end_i;
                                find_need_end_index = start_i;
                            }
                        }
                        else
                        {
                            invalid_wave_number_i++;
                        }
                    }
                    else
                    {
                        invalid_wave_number_i++;
                    }
                }
            }
        }
    }
    else
    {
        for (size_t i = 0; i < groups_mins.size(); i++)
        {
            if (groups_mins.size() > 0 && groups_maxs.size() > 0)
            {
                int start_i = groups_mins.at(i);
                int end_i = groups_maxs.at(i);
                int wave_lenght_i = start_i - end_i;
                if (wave_lenght_i > 0)
                {
                    if (wave_lenght_i > wave_width_min && wave_lenght_i < wave_width_max)
                    {
                        valid_wave_number_i++;
                        if (valid_wave_number_i == 1)
                        {
                            find_need_start_index = end_i;
                            find_need_end_index = start_i;
                        }
                    }
                    else
                    {
                        invalid_wave_number_i++;
                        if (groups_mins.size() > 0)
                        {
                        }
                        if (groups_maxs.size() > 0)
                        {
                        }
                    }
                }
                else
                {
                    invalid_wave_number_i++;
                }
            }
        }
    }
    if (find_need_start_index == 0 || find_need_end_index == 0)
    {
        if (find_need_start_index == 0 && find_need_end_index == 0)
        {
            error_code = 10002;
        }
        else
        {
            error_code = 10003;
        }
        if (zero_value_max < background_values)
        {
            error_code = 10000;
        }
        return zero_value_max;
    }

    if (valid_wave_number_i > 1)
    {
        error_code = 9990;
    }

    for (size_t i = find_need_start_index; i < find_need_end_index + 1; i++)
    {
        need_data.push_back(data[i]);
    }

    waveformData = need_data;
    if (waveformData.size() == 0)
    {
        if (start_point_index.size() == 0 && end_point_index.size() == 0)
        {
            error_code = 9994;
        }
        if (start_point_index.size() > 0 && end_point_index.size() == 0)
        {
            error_code = 9997;
        }
        if (start_point_index.size() == 0 && end_point_index.size() > 0)
        {
            error_code = 9998;
        }
        if (find_zero_value1 < background_values)
        {
            error_code = 10000;
        }
        int result_gray = calculateAverage(data, wave_width_min);
        save_file_name = QString("%3\\Data\\result-%1-%2-%4-zero_value_max-%5-avg_smallest_value-%6.xls").arg(pix_position).arg(QRandomGenerator::global()->generate() % 1000000).arg(programPath).arg(find_zero_value1).arg(zero_value_max).arg(avg_smallest_value);
        saveQVectorToTxt2(data, save_file_name, find_zero_value1);
        return find_zero_value1;
    }
    double total_avg_value = 0;
    total_avg_value = (calculateAverage(waveformData, waveformData.size()));
    save_file_name = QString("%3\\Data\\result-%1-%2-%4-zero_value_max-%5-avg_smallest_value-%6.xls").arg(pix_position).arg(QRandomGenerator::global()->generate() % 1000000).arg(programPath).arg(find_zero_value1).arg(zero_value_max).arg(avg_smallest_value);
    saveQVectorToTxt2(waveformData, save_file_name, find_zero_value1);
    return total_avg_value;
}

int PictureAnalysis::findVectorFirstContinuousMax(QVector<int> numbers)
{
    int max_val = 0;
    std::vector<std::vector<int>> groups;
    std::vector<int> tempGroup;
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (i == 0 || numbers[i] != numbers[i - 1] + 1) {
            if (!tempGroup.empty()) {
                groups.push_back(tempGroup);
                tempGroup.clear();
            }
        }
        tempGroup.push_back(numbers[i]);
    }
    if (!tempGroup.empty()) {
        groups.push_back(tempGroup);
    }
    if (!groups.empty()) {
        max_val = *std::max_element(groups[0].begin(), groups[0].end());
    }
    else {
    }
    return max_val;
}

int PictureAnalysis::findVectorSecondContinuousMin(QVector<int> start_point_index)
{
    int maxConsecutive = -1;
    int currentConsecutive = -1;
    int consecutiveCount = 0;
    bool foundFirstConsecutive = false;
    for (int i = 1; i < start_point_index.size(); i++) {
        if (start_point_index[i] == start_point_index[i - 1] + 1) {
            if (currentConsecutive == -1) {
                currentConsecutive = start_point_index[i - 1];
            }
            consecutiveCount++;
            if (consecutiveCount == 2) {
                if (foundFirstConsecutive) {
                    maxConsecutive = currentConsecutive;
                    break;
                }
                else {
                    foundFirstConsecutive = true;
                    currentConsecutive = -1;
                    consecutiveCount = 0;
                }
            }
        }
        else {
            currentConsecutive = -1;
            consecutiveCount = 0;
        }
    }
    return maxConsecutive;
}

QVector<QVector<int>> PictureAnalysis::groupConsecutiveNumbers(const QVector<int>& numbers) {
    QVector<QVector<int>> result;
    QVector<int> temp;
    for (int i = 0; i < numbers.size(); ++i) {
        if (i == 0 || numbers[i] != numbers[i - 1] + 1) {
            if (!temp.isEmpty()) {
                result.push_back(temp);
                temp.clear();
            }
        }
        temp.push_back(numbers[i]);
    }
    if (!temp.isEmpty()) {
        result.push_back(temp);
    }
    return result;
}

QVector<int> PictureAnalysis::findGroupNumber_mins(const QVector<int>& numbers)
{
    QVector<QVector<int>> groups = groupConsecutiveNumbers(numbers);
    QVector<int> groups_mins;
    for (const auto &group : groups) {
        int minVal = group.empty() ? INT_MIN : group[0];
        for (int val : group) {
            if (val < minVal) {
                minVal = val;
            }
        }
        groups_mins.push_back(minVal);
    }
    return groups_mins;
}

QVector<int> PictureAnalysis::findGroupNumber_maxs(const QVector<int>& numbers)
{
    QVector<QVector<int>> groups = groupConsecutiveNumbers(numbers);
    QVector<int> groups_maxs;
    for (const auto &group : groups) {
        int maxVal = group.empty() ? INT_MIN : group[0];
        for (int val : group) {
            if (val > maxVal) {
                maxVal = val;
            }
        }
        groups_maxs.push_back(maxVal);
    }
    return groups_maxs;
}

int PictureAnalysis::findGroupNumber(const QVector<int>& numbers) {
    QVector<QVector<int>> groups = groupConsecutiveNumbers(numbers);
    if (groups.size() < 2) {
        if (groups.size() == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return groups.size();
}

int PictureAnalysis::findSecondGroupMaxValue(const QVector<int>& numbers) {
    QVector<QVector<int>> groups = groupConsecutiveNumbers(numbers);
    if (groups.size() < 2) {
        if (groups.size() == 1)
        {
            QVector<int>& secondGroup = groups[0];
            std::sort(secondGroup.begin(), secondGroup.end());
            return secondGroup.last();
        }
        else
        {
            return 0;
        }
    }

    QVector<int>& secondGroup = groups[1];
    std::sort(secondGroup.begin(), secondGroup.end());
    return secondGroup.last();
}

int PictureAnalysis::findVectorSecondContinuousMax(QVector<int> start_point_index)
{
    int maxConsecutive = -1;
    int currentConsecutive = -1;
    int consecutiveCount = 0;
    bool foundFirstConsecutive = false;

    for (int i = 1; i < start_point_index.size(); i++) {
        if (start_point_index[i] == start_point_index[i - 1] + 1) {
            if (currentConsecutive == -1) {
                currentConsecutive = start_point_index[i - 1];
            }
            consecutiveCount++;
            if (consecutiveCount == 2) {
                if (foundFirstConsecutive) {
                    maxConsecutive = start_point_index[i];
                    break;
                }
                else {
                    foundFirstConsecutive = true;
                    currentConsecutive = -1;
                    consecutiveCount = 0;
                }
            }
        }
        else {
            currentConsecutive = -1;
            consecutiveCount = 0;
        }
    }
    return maxConsecutive;
}

int PictureAnalysis::findVectorContinuousMax(QVector<int> numbers)
{
    int maxStart = 0;
    int maxLength = 1;
    int currentStart = 0;
    int currentLength = 1;
    for (int i = 1; i < numbers.size(); ++i) {
        if (numbers[i] == numbers[i - 1] + 1) {
            currentLength++;
            if (currentLength > maxLength) {
                maxLength = currentLength;
                maxStart = currentStart;
            }
        }
        else {
            currentLength = 1;
            currentStart = i;
        }
    }
    int maxValue = numbers[maxStart];
    for (int i = maxStart + 1; i < maxStart + maxLength; ++i) {
        if (numbers[i] > maxValue) {
            maxValue = numbers[i];
        }
    }
    return maxValue;
}
int PictureAnalysis::findVectorContinuousMin(QVector<int> numbers)
{
    int maxStart = 0;
    int maxLength = 1;
    int currentStart = 0;
    int currentLength = 1;

    for (int i = 1; i < numbers.size(); ++i) {
        if (numbers[i] == numbers[i - 1] + 1) {
            currentLength++;
            if (currentLength > maxLength) {
                maxLength = currentLength;
                maxStart = currentStart;
            }
        }
        else {
            currentLength = 1;
            currentStart = i;
        }
    }
    int minValue = numbers[maxStart];
    for (int i = maxStart + 1; i < maxStart + maxLength; ++i) {
        if (numbers[i] < minValue) {
            minValue = numbers[i];
        }
    }
    return minValue;
}

int PictureAnalysis::countConsecutiveValues(const std::map<int, int>& wave_map, int find_value) {
    std::map<int, int> wave_map1 = wave_map;
    int valueToFind = find_value;
    int intervalCount = 0;
    bool inInterval = false;
    for (const auto& entry : wave_map) {
        if (entry.second == valueToFind) {
            if (!inInterval) {
                inInterval = true;
                intervalCount++;
            }
        }
        else {
            inInterval = false;
        }
    }
    return intervalCount;
}

int PictureAnalysis::CheckWavePattern1(const QVector<double> &data, double threshold) {
    int result;
    QVector<double> filteredData;
    QVector<double> filteredData1;
    QVector<double> filteredData2;
    QVector<double> filteredData3;
    QVector<double> filteredData4;
    if (data.isEmpty()) {
        return 0;
    }
    int minIndex = 0;
    double min_value = 0;
    for (int i = 1; i < data.size(); ++i) {
        if (data[i] < data[minIndex]) {
            min_value = data[i];
            minIndex = i;
        }
    }
    for (int i = 1; i < minIndex; ++i) {
        double diff = data[i] - data[i - 1];
        if (diff <= 0)
        {
            filteredData1.append(data[i-1]);
        }
    }
    for (int i = 1; i < filteredData1.size()+1; ++i) {
        double diff = filteredData1[i] - filteredData1[i - 1];
        if (diff <= 0)
        {
            filteredData2.append(filteredData1[i - 1]);
        }
    }
    for (int i = 1; i < filteredData2.size()+1; ++i) {
        double diff = filteredData2[i] - filteredData2[i - 1];
        if (diff <= 0)
        {
            filteredData.append(filteredData2[i - 1]);
        }
    }
    for (int i = minIndex; i < data.size(); ++i) {
        double diff = data[i] - data[i + 1];
        if (diff <= 0)
        {
            filteredData3.append(data[i]);
        }
    }
    for (int i = 0; i < filteredData3.size(); ++i) {
        double diff = filteredData3[i] - filteredData3[i + 1];
        if (diff <= 0)
        {
            filteredData4.append(filteredData3[i]);
        }
        if (i== (filteredData3.size()-1) && diff == filteredData3[i])
        {
            filteredData4.append(filteredData3[i]);
        }
    }
    for (int i = 0; i < filteredData4.size(); ++i) {
        double diff = filteredData4[i] - filteredData4[i + 1];
        if (diff <= 0)
        {
            filteredData.append(filteredData4[i]);
        }
        if (i == (filteredData4.size() - 1) && diff == filteredData4[i])
        {
            filteredData.append(filteredData4[i]);
        }
    }
    result = CheckWavePattern(filteredData);
    return result;
}

bool PictureAnalysis::isWaveGraph(const QVector<QVector<double>>& data)
{
    if (data.isEmpty() || data[0].isEmpty()) {
        return false;
    }
    int numRows = data.size();
    int numCols = data[0].size();
    int maxRow = 0;
    int maxCol = 0;
    double minValue = data[0][0];
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (data[i][j] < minValue) {
                minValue = data[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }
    int up = maxRow - 1;
    while (up >= 0 && data[up][maxCol] > data[up + 1][maxCol]) {
        --up;
    }
    int down = maxRow + 1;
    while (down < numRows && data[down][maxCol] > data[down - 1][maxCol]) {
        ++down;
    }
    int left = maxCol - 1;
    while (left >= 0 && data[maxRow][left] > data[maxRow][left + 1]) {
        --left;
    }
    int right = maxCol + 1;
    while (right < numCols && data[maxRow][right] > data[maxRow][right - 1]) {
        ++right;
    }
    return up == -1 && down == numRows && left == -1 && right == numCols;
}

int PictureAnalysis::CheckWavePattern(QVector<double> data)
{
    int return_value;
    if (data.isEmpty()) {
        return false;
    }
    int minIndex = 0;
    for (int i = 1; i < data.size(); ++i) {
        if (data[i] < data[minIndex]) {
            minIndex = i;
        }
    }
    int left = minIndex - 1;
    while (left >= 0 && data[left] >= data[left + 1]) {
        --left;
    }
    int right = minIndex + 1;
    while (right < data.size() && data[right] >= data[right - 1]) {
        ++right;
    }
    return left == -1 && right == data.size();
}

double PictureAnalysis::GetMinValue(QList<double> column_gray_avg_list)
{
    auto mm = std::minmax_element(column_gray_avg_list.begin(), column_gray_avg_list.end());
    double min_value = *mm.first;
    return min_value;
}

QMap<int, double> PictureAnalysis::GetNeedAvgMap(QList<double> column_gray_avg_list, int min_gray_postion, double min_gray, TestPaperParameter testPaperParameter)
{
    QMap<int, double> position_gray_map;
    int set_number = testPaperParameter.set_calculate_point;//3 数据库读取
    double percent_value = testPaperParameter.point_to_min_percent;//0.2 数据库读取
    if (set_number <= 0)
    {
        set_number = 3;
    }
    if (set_number > 10)
    {
        set_number = 3;
    }
    if (percent_value <= 0)
    {
        percent_value = 0.2;
    }
    if (percent_value > 1)
    {
        percent_value = 0.2;
    }
    int i_right_start_index = 0;
    int i_left_end_index = 0;
    if (min_gray_postion - set_number < 0)//set_calculate_point
    {
        for (size_t i = 0; i < min_gray_postion; i++)
        {
            double gray_value = 0;
            int number = 0;
            double tmp = (column_gray_avg_list.at(i) - min_gray) / min_gray;
            if (tmp < percent_value)
            {
                gray_value += column_gray_avg_list.at(i);
                number++;
                position_gray_map.insert(i, column_gray_avg_list.at(i));
            }
        }
    }
    else
    {
        int i_left_end_index = min_gray_postion - set_number;
        for (size_t i = i_left_end_index; i < min_gray_postion; i++)
        {
            double gray_value = 0;
            int number = 0;
            double tmp = (column_gray_avg_list.at(i) - min_gray) / min_gray;
            if (tmp < percent_value)
            {
                gray_value += column_gray_avg_list.at(i);
                number++;
                position_gray_map.insert(i, column_gray_avg_list.at(i));
            }
        }
    }
    i_left_end_index = 0;
    if ((column_gray_avg_list.size() - min_gray_postion) < set_number)
    {
        i_right_start_index = min_gray_postion;
        double gray_value = 0;
        int number = 0;
        for (int i = i_right_start_index; i < column_gray_avg_list.size(); ++i)
        {
            double tmp = (column_gray_avg_list.at(i) - min_gray) / min_gray;
            if (tmp < percent_value)
            {
                gray_value += column_gray_avg_list.at(i);
                number++;
                position_gray_map.insert(i, column_gray_avg_list.at(i));
            }
        }
    }
    else
    {
        double gray_value = 0;
        int number = 0;
        for (int i = min_gray_postion; i < min_gray_postion + set_number; ++i)
        {
            double tmp = (column_gray_avg_list.at(i) - min_gray) / min_gray;
            if (tmp < percent_value)//色差在20%以内的数据计入
            {
                gray_value += column_gray_avg_list.at(i);
                number++;
                position_gray_map.insert(i, column_gray_avg_list.at(i));
            }
        }
    }
    return position_gray_map;
}

double PictureAnalysis::GetAverage_new(IplImage  *srcGray,int left,int top,int width,int height)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    unsigned char * imageData;
    imageData = (unsigned char*)srcGray->imageData;
    double aVerage = 0;
    double aVerage_left = 0;
    double aVerage_right = 0;
    unsigned int sum = 0;
    int count = 0;
    int value = 0;
    for (int j = (left- width); j < left; j++)
    {
        for (int i = top; i < (top + height); i++)
        {
            value = ((uchar*)(srcGray->imageData + srcGray->widthStep*i))[j];
            sum += value;
            count++;
        }
    }
    aVerage_left = double(sum) / double(count);
    sum = 0;
    count = 0;
    for (int j = left ; j < (left + width); j++)
    {
        for (int i = top; i < (top + height); i++)
        {
            value = ((uchar*)(srcGray->imageData + srcGray->widthStep*i))[j];
            sum += value;
            count++;
        }
    }
    aVerage_right = double(sum) / double(count);
    aVerage = (aVerage_left + aVerage_right)/2;
    return aVerage;
}

int PictureAnalysis::GetSum(IplImage  *srcGray,int left,int top,int width,int height)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    unsigned char * imageData;
    imageData = (unsigned char*)srcGray->imageData;
    unsigned char aVerage = 0;
    unsigned int sum = 0;
    int count = 0;
    int value = 0;
    for (int j = left; j < (left + width); j++)
    {
        for (int i = top; i < (top + height); i++)
        {
            value = ((uchar*)(srcGray->imageData + srcGray->widthStep*i))[j];
            sum += value;
            count++;
        }
    }
    return sum;
}

int PictureAnalysis::GetTestPaperTop_New(IplImage  *srcGray)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    int left = sz.width / 2;
    int top = 0;
    int width = 100;
    int height = 5;
    double Average0 = GetAverage(srcGray,left,top,width,height);
    double Average1 = 0;
    double Average2 = 0;
    int height2 = 13;
    int i = 0;
    for (i = 0; i < sz.height / 2; i++)
    {
        Average1 = GetAverage(srcGray,left,i,width,height);
        Average2 = GetAverage(srcGray,left,i,width,height2);
        double a1 = Average1 - Average0;
        double a2 = Average2 - Average0;

        if ((a1) > 50 && (a2) > 50)
        {
            break;
        }
    }
    return i + 4;
}


int PictureAnalysis::GetTestPaperTop(IplImage  *srcGray)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    int left = sz.width / 3;
    int top = 0;
    int width = sz.width / 9;
    int height = 10;
    double Average0 = GetAverage(srcGray,left,top,width,height);
    double Average1 = 0;
    double Average2 = 0;
    int height2 = 3;
    int i = 0;
    for (i = 0; i < sz.height / 2; i++)
    {
        Average1 = GetAverage(srcGray,left,i,width,height);
        Average2 = GetAverage(srcGray,left,i,width,height2);
        double a1 = Average1 - Average0;
        double a2 = Average2 - Average0;
        if ((a1) > 30 &&(a2) > 30)
        {
            break;
        }
    }
    return i + 4;
}

int PictureAnalysis::GetTestPaperBottom(IplImage  *srcGray)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    int height = 10;
    int left = sz.width / 3;
    int top = srcGray->height - height;
    int width = sz.width / 9;
    double Average0 = GetAverage(
                srcGray,
                left,
                top,
                width,
                height);
    double Average1 = 0;
    double Average2 = 0;
    int height2 = 3;
    int i = 0;
    for (i = 0; i < sz.height / 2; i++)
    {
        Average1 = GetAverage(
                    srcGray,
                    left,
                    (sz.height - i) - height,
                    width,
                    height);
        Average2 = GetAverage(
                    srcGray,
                    left,
                    (sz.height - i) - height2,
                    width,
                    height2);
        if ((Average1 - Average0) > 50 &&
                (Average2 - Average0) > 50)
        {
            break;
        }
    }
    return sz.height - i - 4;
}

int PictureAnalysis::GetTestPaperLeft_New(IplImage  *srcGray, int nTestPaperTop, int nTestPaperBottom)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    int left = 0;
    int width = 30;
    int top = nTestPaperTop;
    int height = nTestPaperBottom - nTestPaperTop;
    double Average0 = GetAverage(srcGray, left, top, width, height);
    double Average1 = 0;
    double Average2 = 0;
    int width2 = 4;
    int i = 0;
    for (i = 0; i < sz.width / 2; i++)
    {
        Average1 = GetAverage(srcGray, i, top, width, height);
        Average2 = GetAverage(srcGray, i, top, width2, height);
        if ((Average1 - Average0) > 50 && (Average2 - Average0) > 50)
        {
            break;
        }
    }
    return i + 4;
}

int PictureAnalysis::GetTestPaperLeft_New_pic2(IplImage  *srcGray, int nTestPaperTop, int nTestPaperBottom, int judge_value)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    int left = 0;
    int width = 30;
    int top = nTestPaperTop;
    int height = nTestPaperBottom - nTestPaperTop;
    double Average0 = GetAverage(srcGray, left, top, width, height);
    double Average1 = 0;
    double Average2 = 0;
    int width2 = 4;
    int i = 0;
    for (i = 0; i < sz.width / 2; i++)
    {
        Average1 = GetAverage(srcGray, i, top, width, height);
        Average2 = GetAverage(srcGray, i, top, width2, height);
        if ((Average1 - Average0) > judge_value && (Average2 - Average0) > judge_value)
        {
            break;
        }
    }
    return i + 4;
}

int PictureAnalysis::GetTestPaperLeft(IplImage  *srcGray, int nTestPaperTop, int nTestPaperBottom)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    int left = 0;
    int width = 30;
    int top = nTestPaperTop;
    int height = nTestPaperBottom - nTestPaperTop;
    double Average0 = GetAverage(srcGray,left,top,width,height);
    Average0 = 20;
    double Average1 = 0;
    double Average2 = 0;
    int width2 = 4;
    int i = 0;
    for (i = 0; i < sz.width / 2; i++)
    {
        Average1 = GetAverage(srcGray,i,top,width,height);
        Average2 = GetAverage(srcGray,i,top,width2,height);
        if ((Average1 - Average0) > 40 && (Average2 - Average0) > 40)
        {
            break;
        }
    }
    return i + 4;
}

int PictureAnalysis::GetTestPaperRight_New(IplImage  *srcGray, int nTestPaperTop, int nTestPaperBottom)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    int width = 60;
    int left = sz.width - width;
    int top = nTestPaperTop;
    int height = nTestPaperBottom - nTestPaperTop;
    double Average0 = GetAverage(srcGray, left, top, width, height);
    double Average1 = 0;
    double Average2 = 0;
    int width2 = 4;
    int i = 0;
    for (i = 0; i < sz.width / 2; i++)
    {
        Average1 = GetAverage(srcGray, (sz.width - i) - width, top, width, height);
        Average2 = GetAverage(srcGray, (sz.width - i) - width2, top, width2, height);
        double a1 = Average1 - Average0;
        double a2 = Average2 - Average0;
        if ((a1) > 50 && (a2) > 50)
        {
            break;
        }
    }
    return sz.width - i - 4;
}

int PictureAnalysis::GetTestPaperRight(IplImage  *srcGray, int nTestPaperTop, int nTestPaperBottom)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    int width = 60;
    int left = sz.width - width;
    int top = nTestPaperTop;
    int height = nTestPaperBottom - nTestPaperTop;
    double Average0 = GetAverage(srcGray,left,top,width,height);
    double Average1 = 0;
    double Average2 = 0;
    int width2 = 4;
    int i = 0;
    for (i = 0; i < sz.width / 2; i++)
    {
        Average1 = GetAverage(srcGray,(sz.width - i) - width,top,width,height);
        Average2 = GetAverage(srcGray,(sz.width - i) - width2,top,width2,height);
        double a1 = Average1 - Average0;
        double a2 = Average2 - Average0;
        if ((a1) > 30 && (a2) > 30)
        {
            break;
        }
    }
    return sz.width - i - 4;
}
int PictureAnalysis::GetSlicePostionX(IplImage  *srcGray,int left,int top,int width,int height)
{
    CvSize sz;
    sz.width = srcGray->width;
    sz.height = srcGray->height;
    unsigned char * imageData;
    imageData = (unsigned char*)srcGray->imageData;
    unsigned char aVerage = 0;
    int Sum0 = 0;
    int i = 0;
    int bestIndex = 0;
    int min = width * height * 255;
    int tmp = 0;
    for (i = left - 2 * width; i < (left + 2 * width); i++)
    {
        Sum0 = GetSum(
                    srcGray,
                    i,
                    top,
                    width,
                    height);
        tmp = Sum0;
        if (tmp < min)
        {
            min = tmp;
            bestIndex = i;
        }
    }
    return bestIndex;
}

void PictureAnalysis::ImageFlip(IplImage  *srcTestPaper)
{
    Mat srcCopy = cvarrToMat(srcTestPaper, true);
    transpose(srcCopy, srcCopy);
    flip(srcCopy, srcCopy, 1);
    imwrite("res/rotate270.png", srcCopy);
}

QString PictureAnalysis::CaculateResultText(double dItemGrayRatio, QString itemName, int paper_id,int error_code)
{
    bool bResult = true;
    auto dao = AnalysisUIDao::instance();
    QString sql = "";
    sql.sprintf("select * from t_judge_rules where RulesId = (select RulesId from titem where itemName = '%s' and TestPaperID =%d ) order by GrayValue asc", itemName.toUtf8().data(), paper_id);
    auto JudgeRulesQuery = dao->SelectRecord(&bResult, sql);
    QString testResult = "";
    QMap<double, QString> mapJudgeRules;
    while (JudgeRulesQuery.next())
    {
        double grayValue = JudgeRulesQuery.value("GrayValue").toDouble();
        QString grayWord = JudgeRulesQuery.value("GrayWord").toString();
        mapJudgeRules.insert(grayValue, grayWord);
    }
    QList<double> key_list;
    QList<QString> value_list;
    QMap<double, QString>::Iterator it = mapJudgeRules.begin();
    int tmp_i = 0;
    while (it != mapJudgeRules.end())
    {
        if (tmp_i == 0)
        {
            key_list.push_back(-1000);
            value_list.push_back(it.value());
        }
        key_list.push_back(it.key());
        value_list.push_back(it.value());

        if (tmp_i == (mapJudgeRules.count() - 1))
        {
            key_list.push_back(2000);
            value_list.push_back(it.value());
        }
        tmp_i++;
        it++;
    }
    int key_count = key_list.count();
    int find_index = 0;
    for (int i = 0; i < key_count; )
    {
        double min = key_list[0];
        double max = 1000;
        if (i > 0)
        {
            min = key_list[i - 1];
            max = key_list[i];

            if (dItemGrayRatio > min && dItemGrayRatio <= max)
            {
                find_index = i;
            }
        }
        i++;
    }

    if (value_list.count() > 0)
    {
        testResult = value_list[find_index];
    }
    if (error_code == 10002)
    {
        testResult = "-";
    }
    if (error_code == 10003 )
    {
        testResult = "o";
    }
    return testResult;
}

void PictureAnalysis::RotatePng(QString scr_path, QString new_path, QString last_path1,int head_length, int find_characteristic_number, int thresh,int pix_width)
{
    int need_add_head_length = head_length;
    Mat src, src1, src_edge, src_gray, src_gray1, src_rotate;
    Mat gray, binImg;
    double angle;
    src = imread(scr_path.toStdString());
    src1 = imread(scr_path.toStdString());
    cvtColor(src, src_gray, COLOR_RGB2GRAY);
    double thres1 = 130;
    double maxval1 = 160;
    threshold(src1, src1, thresh, maxval1, CV_THRESH_BINARY);
    Canny(src1, src_edge, 50, 100, 3);
    std::vector<Vec2f> plines;
    int count_number = 3;
    int value1 = 220;
    int num_count1 = 15;
    num_count1 = find_characteristic_number;
    for (int ii = 220; ii != 0; ii--)
    {
        std::vector<Vec2f> plines1;
        HoughLines(src_edge, plines1, 1, CV_PI / 180, ii, 0, 0);
        if (plines1.size() > num_count1)
        {
            plines = plines1;
            break;
        }
    }
    if (plines.size() == 0)
    {
        HoughLines(src_edge, plines, 1, CV_PI / 180, 200, 0, 0);
    }

    if (plines.size() == 0)
    {
        return;
    }
    float sum = 0;
    int sum_count = 0;
    int line_start_x = 2500;
    for (size_t i = 0; i < plines.size(); i++)
    {
        float rho = plines[i][0];
        float theta = plines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + line_start_x * (-b));
        pt1.y = cvRound(y0 + line_start_x * (a));
        pt2.x = cvRound(x0 - line_start_x * (-b));
        pt2.y = cvRound(y0 - line_start_x * (a));
        if (qAbs(pt1.y) < line_start_x && qAbs(pt2.y) < line_start_x)
        {
            sum += theta;
            line(src_gray, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
            sum_count++;
        }
    }
    float average = sum / sum_count;
    angle = average / CV_PI * 180- 90;

    if (angle > 0)
    {
        angle = -angle;
    }
    Point2f center;
    center.x = float(src.cols / 2.0);
    center.y = float(src.rows / 2.0);
    int length = 0;
    length = sqrt(src.cols*src.cols + src.rows*src.rows);
    Mat M = getRotationMatrix2D(center, angle, 1);
    warpAffine(src, src_rotate, M, Size(length, src.rows), 1, 0, Scalar(0, 0, 0));
    imwrite(new_path.toStdString(), src_rotate);
    std::vector<std::vector<Point> > contours2;
    std::vector<std::vector<Point> > contours3;
    Mat raw_new = imread(new_path.toStdString());
    Mat dstImg_show_20230412001;
    Mat dstImg_show_20230518001;
    Mat SecondFindImg;
    cvtColor(raw_new, SecondFindImg, COLOR_BGR2GRAY);
    double thres = thresh;
    double maxval = 160;
    threshold(SecondFindImg, SecondFindImg, thres, maxval, CV_THRESH_BINARY);
    findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    Mat dstImg;
    Mat dstImg_show;
    Rect rect;
    Rect rect1;
    Rect rect_need;
    int start_up_x = 0;
    int start_up_y = 0;
    int start_down_x = 0;
    int start_down_y = 0;
    int end_up_x = 0;
    int end_up_y = 0;
    int end_down_x = 0;
    int end_down_y = 0;
    int jjj = 0;
    int min_x = 0;
    int max_y = 0;
    int max_heigth = 0;
    std::vector<int> card_x;
    std::vector<int> card_x1;
    std::vector<int> card_y;
    std::vector<int> card_y1;
    std::vector<int> card_y_need;
    std::vector<int> card_height;
    int need_height = 0;
    if (contours2.size() == 0)
    {
        return;
    }
    for (int j = 0; j < contours2.size(); j++)
    {
        rect = boundingRect(Mat(contours2[j]));
        int rect_area = rect.area();
        card_x1.push_back(rect.x);
        card_y1.push_back(rect.y);
        if (rect_area > 80)
        {
            if (rect.width > 15 && rect.height > 15)
            {
                contours3.push_back(contours2[j]);
            }
        }
    }
    int minValue_xx = *min_element(card_x1.begin(), card_x1.end());
    int height_22_i = 0;
    for (int j = 0; j < contours3.size(); j++)
    {
        rect = boundingRect(Mat(contours3[j]));
        int rect_area = rect.area();
        min_x = rect.x;
        max_y = rect.y;
        card_x.push_back(min_x);
        if (rect.height > 22)
        {
            card_y_need.push_back(max_y);
            card_height.push_back(rect.height);
            need_height += rect.height;
            height_22_i++;
        }
    }
    if (height_22_i == 0 || need_height==0 )
    {
        return;
    }
    need_height = need_height / height_22_i;
    if (need_height == 0)
    {
        return;
    }
    if (contours3.size() == 0)
    {
        return;
    }
    int minValue_x_asix = *min_element(card_x.begin(), card_x.end());
    int minValue_y_asix = *min_element(card_y_need.begin(), card_y_need.end());
    if (card_y_need.size() == 0)
    {
        return;
    }
    double sum1 = std::accumulate(std::begin(card_y_need), std::end(card_y_need), 0.0);
    double mean = sum1 / card_y_need.size();
    int avgValue_y_asix = mean;
    minValue_y_asix = avgValue_y_asix;
    int minPosition = min_element(card_x.begin(), card_x.end()) - card_x.begin();
    int maxValue_height = *max_element(card_height.begin(), card_height.end());
    int maxPosition_height = max_element(card_height.begin(), card_height.end()) - card_height.begin();
    int maxValue_x = *max_element(card_x.begin(), card_x.end());
    int maxPosition_x = max_element(card_x.begin(), card_x.end()) - card_x.begin();
    minValue_x_asix = minValue_x_asix;
    rect = boundingRect(Mat(contours3[maxPosition_x]));
    int need_width = 0;
    if (need_add_head_length != 0)
    {
        need_width = (rect.x + rect.width) - minValue_x_asix + need_add_head_length;
    }
    else
    {
        need_width = (rect.x + rect.width) - minValue_x_asix;
    }
    if (need_height > 65)
    {
        need_height = (boundingRect(Mat(contours3[minPosition])).height + boundingRect(Mat(contours3[maxPosition_x])).height) / 2;
    }
    start_up_x = boundingRect(Mat(contours3[minPosition])).x;
    start_up_y = minValue_y_asix;
    end_up_x = boundingRect(Mat(contours3[maxPosition_x])).x + boundingRect(Mat(contours3[maxPosition_x])).width;
    end_up_y = boundingRect(Mat(contours3[maxPosition_x])).y;
    if (need_add_head_length != 0)
    {
        rect_need.x = minValue_x_asix - need_add_head_length;
    }
    else
    {
        rect_need.x = minValue_x_asix;
    }
    rect_need.y = start_up_y;
    if (pix_width > raw_new.cols)
    {
        rect_need.width = raw_new.cols;
    }
    else
    {
        rect_need.width = pix_width;
    }
    rect_need.height = need_height;
    if (rect_need.x + pix_width > 2500)
    {
        rect_need.x = 2500- pix_width-10;
    }
    if (rect_need.x < 0)
    {
        rect_need.x = 0;
    }
    if (rect_need.y < 0)
    {
        rect_need.y = 0;
    }
    dstImg_show_20230518001 = raw_new;
    dstImg = dstImg_show_20230518001(rect_need);
    imwrite(last_path1.toStdString(), dstImg);
}
#define GRAY_THRESH 150
#define HOUGH_VOTE 50
#define HOUGH_VOTE 50
double PictureAnalysis::DegreeTrans1(double theta)
{
    double res = theta / CV_PI * 180;
    return res;
}

Point2f PictureAnalysis::linesIntersect11(double b1, double b2, double k1, double k2)
{
    float x, y;
    x = (b2 - b1) / (k1 - k2);
    y = (k1*b2 - k2 * b1) / (k2 - k1);
    if (x < 0)
        x = -x;
    if (y < 0)
        y = -y;
    return Point2f(x, y);
}

void PictureAnalysis::RotatePng_20231117(QString scr_path, QString new_path, QString last_path1, int head_length, int find_characteristic_number, int thresh, int pix_width)
{
    double degree;
    Mat image = imread(scr_path.toStdString());
    Mat gray, blur, canny, imgDil;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, blur, Size(3, 3), 3, 0);
    imshow("blur", blur);
    Canny(blur, canny, 25, 75);
    imshow("canny", canny);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(canny, imgDil, kernel);
    imshow("imgDil", imgDil);
    vector<Vec4i> lines;
    HoughLinesP(imgDil, lines, 1, CV_PI / 180.0, 40, 100, 10);
    for (int i = 0; i < lines.size(); ++i) {
        line(canny, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0, 255, 0), 2, 8);
    }
    vector<Vec4i> heng_lines, shu_lines;
    for (int i = 0; i < lines.size(); ++i) {
        int x = lines[i][0] - lines[i][2];
        int y = lines[i][1] - lines[i][3];
        x = x * x;
        y = y * y;
        if (x < y)
            shu_lines.push_back(lines[i]);
        else
            heng_lines.push_back(lines[i]);
    }

    if (shu_lines.size() < 2 || heng_lines.size() < 2) {
        return;
    }
    int heng_center_y[10], shu_center_x[10];
    for (int i = 0; i < heng_lines.size(); ++i)
        heng_center_y[i] = heng_lines[i][1] + heng_lines[i][3];
    int maxp_heng = max_element(heng_center_y, heng_center_y + heng_lines.size()) - heng_center_y;
    int minp_heng = min_element(heng_center_y, heng_center_y + heng_lines.size()) - heng_center_y;
    for (int i = 0; i < shu_lines.size(); ++i)
        shu_center_x[i] = shu_lines[i][0] + shu_lines[i][2];
    int maxp_shu = max_element(shu_center_x, shu_center_x + shu_lines.size()) - shu_center_x;
    int minp_shu = min_element(shu_center_x, shu_center_x + shu_lines.size()) - shu_center_x;
    double k_heng_min, k_heng_max, k_shu_min, k_shu_max;
    k_heng_min = (double)(heng_lines[minp_heng][3] - heng_lines[minp_heng][1]) / (double)(heng_lines[minp_heng][2] - heng_lines[minp_heng][0]);
    k_heng_max = (double)(heng_lines[maxp_heng][3] - heng_lines[maxp_heng][1]) / (double)(heng_lines[maxp_heng][2] - heng_lines[maxp_heng][0]);
    k_shu_min = (double)(shu_lines[minp_shu][3] - shu_lines[minp_shu][1]) / (double)(shu_lines[minp_shu][2] - shu_lines[minp_shu][0]);
    k_shu_max = (double)(shu_lines[maxp_shu][3] - shu_lines[maxp_shu][1]) / (double)(shu_lines[maxp_shu][2] - shu_lines[maxp_shu][0]);
    double b_heng_min, b_heng_max, b_shu_min, b_shu_max;
    b_heng_min = -k_heng_min * (double)heng_lines[minp_heng][2] + (double)heng_lines[minp_heng][3];
    b_heng_max = -k_heng_max * (double)heng_lines[maxp_heng][2] + (double)heng_lines[maxp_heng][3];
    b_shu_min = -k_shu_min * (double)shu_lines[minp_shu][2] + (double)shu_lines[minp_shu][3];
    b_shu_max = -k_shu_max * (double)shu_lines[maxp_shu][2] + (double)shu_lines[maxp_shu][3];
    Point2f p_zuoshang, p_zuoxia, p_youshang, p_youxia;
    p_zuoshang = linesIntersect11(b_heng_min, b_shu_min, k_heng_min, k_shu_min);
    p_zuoxia = linesIntersect11(b_heng_max, b_shu_min, k_heng_max, k_shu_min);
    p_youshang = linesIntersect11(b_heng_min, b_shu_max, k_heng_min, k_shu_max);
    p_youxia = linesIntersect11(b_heng_max, b_shu_max, k_heng_max, k_shu_max);
    vector<Point2f> ori_pts;
    ori_pts.push_back(p_zuoshang);
    ori_pts.push_back(p_youshang);
    ori_pts.push_back(p_zuoxia);
    ori_pts.push_back(p_youxia);
    cout << ori_pts << endl;
    int dst_width = 432, dst_height = 576;
    vector<Point2f> dst_pts;
    dst_pts.push_back(Point(0, 0));
    dst_pts.push_back(Point(dst_width - 1, 0));
    dst_pts.push_back(Point(0, dst_height - 1));
    dst_pts.push_back(Point(dst_width - 1, dst_height - 1));
    Mat H;
    Mat toushi;
    H = findHomography(ori_pts, dst_pts);
    warpPerspective(image, toushi, H, image.size());
}

void PictureAnalysis::performHorizontalCorrection(const cv::Mat& inputImage) {
    cv::Mat cannyOutput;
    cv::Canny(inputImage, cannyOutput, 50, 150);
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(cannyOutput, lines, 1, CV_PI / 180, 100, 50, 10);
    double angle = 0.0;
    for (size_t i = 0; i < lines.size(); i++) {
        cv::Point pt1 = cv::Point(lines[i][0], lines[i][1]);
        cv::Point pt2 = cv::Point(lines[i][2], lines[i][3]);
        angle += atan2(pt2.y - pt1.y, pt2.x - pt1.x);
    }
    angle /= lines.size();
    cv::Point2f center(static_cast<float>(inputImage.cols / 2), static_cast<float>(inputImage.rows / 2));
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle * 180 / CV_PI, 1.0);
    cv::warpAffine(inputImage, inputImage, rotationMatrix, inputImage.size());
    cv::waitKey(0);
}

double PictureAnalysis::degreesToRadians(double degrees)
{
    return degrees * CV_PI / 180.0;
}

double PictureAnalysis::radiansToDegrees(double radians)
{
    return radians * 180.0 / CV_PI;
}
void PictureAnalysis::RotatePng_20241212(QString scr_path, QString new_path, QString last_path1, int head_length, int find_characteristic_number, int thresh, int thresh1, int pix_width,int company_id)
{
    int debug_status = 0;
    int need_add_head_length = head_length;
    Mat src, src1, src_edge, src_gray, src_gray1, src_rotate, scr_gs, src_gs1;
    Mat src2, src3, src_edge2, src_gray2, src_gray12;
    Mat gray, binImg;
    double angle = 0;
    src = imread(scr_path.toStdString());
    src1 = imread(scr_path.toStdString());
    src3 = imread(scr_path.toStdString());
    int  heightxx = src1.rows;
    int widthxx = src1.cols;
    Rect rect1x_start(0, 0, widthxx / 5, heightxx);
    Rect rect1x_start1(0, 0, (widthxx *3)/ 8, heightxx);
    Rect rect1x_end(widthxx - 500, 0, 1200, heightxx);
    cv::Scalar color = cv::Scalar(0, 0, 0);
    if (need_add_head_length < 10)
    {
        if (company_id == 2)
        {
            rectangle(src1, rect1x_start1, Scalar(0, 0, 0), -1);
            rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
            if (debug_status)
            {
            }
        }
        else
        {
            rectangle(src1, rect1x_start, Scalar(0, 0, 0), -1);
            rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
            if (debug_status)
            {
            }
        }
    }
    else
    {
        rectangle(src1, rect1x_start1, Scalar(0, 0, 0), -1);
        rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
        if (debug_status)
        {
        }
    }
    cvtColor(src1, src_gray, COLOR_RGB2GRAY);
    cvtColor(src, src_gray2, COLOR_RGB2GRAY);
    double thres1 = 130;
    double maxval1 = 150;
    Mat src4;
    threshold(src1, src4, thresh, maxval1, CV_THRESH_BINARY);
    threshold(src1, src2, thresh1, maxval1, CV_THRESH_BINARY);
    if (debug_status)
    {
    }
    Canny(src1, src_edge, 50, 150, 3);
    if (debug_status)
    {
    }
    Canny(src2, src_edge2, 50, 150, 3);
    if (debug_status)
    {
    }
    std::vector<Vec2f> plines;
    double minLineLength = 0;
    double	maxLineGap = 0;
    int count_number = 3;
    int value1 = 220;
    int num_count1 = 15;
    num_count1 = find_characteristic_number;
    if (plines.size() < 1)
    {
        for (int ii = value1; ii != 0; ii--)
        {
            std::vector<Vec2f> plines1;
            HoughLines(src_edge2, plines1, 1, CV_PI / 180, ii, minLineLength, maxLineGap);
            if (plines1.size() > num_count1)
            {
                plines = plines1;
                break;
            }
        }
        if (plines.size() == 0)
        {
            HoughLines(src_edge2, plines, 1, CV_PI / 180, value1 - 20, minLineLength, maxLineGap);
        }
    }
    float sum = 0;
    int sum_count = 0;
    int line_start_x = 2500;
    double k = 0;
    list<double> k_list;
    list<QString> x1_list;
    list<double> angle_list;
    list<double> theta_list;
    if (plines.size() > 2)
    {
        double max_delete_number_ratio = 0.45;
        int delete_number = plines.size() * max_delete_number_ratio;
        std::sort(plines.begin(), plines.end(),
                  [](const cv::Vec2f& a, const cv::Vec2f& b) {
            return std::abs(a[1]) < std::abs(b[1]);
        });
        plines.erase(plines.end() - delete_number, plines.end());
        double min_delete_number_ratio = 0.45;
        delete_number = plines.size() * min_delete_number_ratio;
        std::sort(plines.begin(), plines.end(),
                  [](const cv::Vec2f& a, const cv::Vec2f& b) {
            return std::abs(a[1]) < std::abs(b[1]);
        });
        plines.erase(plines.begin(), plines.begin() + delete_number);
    }
    if (plines.size() == 0)
    {
        return;
    }
    std::map<int, int> angle_map;
    int cnt = 0;
    int max_cnt = 0;
    float best_angle = 0.0;
    int max_angle = 50;
    int max_iter = 300;
    int T_length = src_edge2.cols > src_edge2.rows ? src_edge2.rows : src_edge2.cols;
    for (size_t i = 0; i < plines.size(); i++)
    {

        float rho = plines[i][0];
        float theta = plines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + line_start_x * (-b));
        pt1.y = cvRound(y0 + line_start_x * (a));
        pt2.x = cvRound(x0 - line_start_x * (-b));
        pt2.y = cvRound(y0 - line_start_x * (a));
        int length_pt = sqrt(std::pow(pt2.x - pt1.x, 2) + std::pow(pt2.y - pt1.y, 2));
        if (length_pt < (T_length * 0.05)) continue;
        Point pt_mid((pt1.x + pt2.x) / 2, (pt1.y + pt2.y) / 2);
        float ang_ = atan2((pt2.y - pt1.y)*1.0, (pt2.x - pt1.x)*1.0);
        float theta1 = CV_PI / 2 + ang_;
        float fangle = theta1 / CV_PI * 360;
        fangle = round(180 - fangle);
        if (abs(fangle) < max_angle && pt_mid.y > src_edge2.rows*0.15 && pt_mid.y < src_edge2.rows*(1 - 0.15))
        {
            cnt++;
            sum += theta;
            sum_count++;
            cv::line(src_edge2, pt1, pt2, Scalar(255, 255, 0), 1, cv::LINE_AA);
            if (angle_map.end() == angle_map.find(fangle))
            {
                angle_map[fangle] = 1;
            }
            else
            {
                angle_map[fangle]++;
                if (angle_map[fangle] > max_cnt) {
                    max_cnt = angle_map[fangle];
                    best_angle = fangle;
                }
            }
        }
    }
    if (debug_status)
    {
    }
    float average = sum / sum_count;
    if (sum_count == 0)
    {
        average = 0;
    }
    double angleDegrees1 = average * 180.0 / CV_PI;
    double cz = abs(average - CV_PI /2);
    angle = average / CV_PI * 180 - 90;
    Point2f center;
    center.x = float(src3.cols / 2.0);
    center.y = float(src3.rows / 2.0);
    int length = 0;
    length = sqrt(src3.cols*src3.cols + src3.rows*src3.rows);
    Mat M = getRotationMatrix2D(center, angle, 1);
    warpAffine(src, src_rotate, M, Size(length, src3.rows), 1, 0, Scalar(0, 0, 0));
    if (debug_status)
    {
    }
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(src_edge2, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::Mat contourImage = src_edge2.clone();
    cv::drawContours(contourImage, contours, -1, cv::Scalar(255, 0, 0), 2);
    /*auto dao = AnalysisDao::instance();
    bool bResult = true;
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName2 = strPath + "\\" + "77777" + ".png";
    imwrite(strPathFileName2.toStdString(),contourImage);*/

    cv::RotatedRect boundingBox = cv::minAreaRect(contours[0]);
    float angle1 = boundingBox.angle;

    double anglexx = 0;
    double anglexx1 = 0;
    double anglexx2 = 0;
    for (const auto& contour : contours) {
        cv::Moments mu = cv::moments(contour);
        anglexx = atan2(2 * mu.mu11, mu.m00 - mu.m20) * 180 / CV_PI;
    }

    for (const auto& contour : contours)
    {
        cv::RotatedRect rect = cv::minAreaRect(contour);
        float angle2222 = rect.angle;
        anglexx1 = 90.0 - std::abs(angle2222);
    }
    float correctionAngle = 0;

    if (anglexx < 0)
    {
        correctionAngle =-(90.0 - std::abs(anglexx1));
    }
    else
    {
        correctionAngle = (90.0 - std::abs(anglexx1));
    }
    if (abs(anglexx1) > 35 || abs(anglexx1) == 35|| abs(correctionAngle) > 35 || abs(correctionAngle) == 35)
    {
        if (abs(angle) > 35)
        {
            angle = 0;
        }
        double angleDegrees21 = angle * 180.0 / CV_PI;
        correctionAngle = angle;
    }
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(boundingBox.center, correctionAngle, 1.0);
    cv::Mat rotatedImage;
    cv::warpAffine(src, src_rotate, rotationMatrix, src3.size(), cv::INTER_CUBIC);
    if (debug_status)
    {
        cv::imshow("src_rotate2", src_rotate);
    }
    Mat gray1;
    cvtColor(src_rotate, gray1, COLOR_BGR2GRAY);
    imwrite(new_path.toStdString(), gray1);
    std::vector<std::vector<Point> > contours2;
    std::vector<std::vector<Point> > contours3;
    Mat raw_new = imread(new_path.toStdString());
    Mat dstImg_show_20230412001;
    Mat dstImg_show_20230518001;
    //Mat SecondFindImg;
   // cvtColor(raw_new, SecondFindImg, COLOR_BGR2GRAY);
     Mat dstImg;
    /*double thres = thresh;
    double maxval = 160;
    threshold(SecondFindImg, SecondFindImg, thres, maxval, CV_THRESH_BINARY);
    findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    Mat dstImg;
    Mat dstImg_show;
    Rect rect;
    Rect rect1;
    Rect rect_need;
    int start_up_x = 0;
    int start_up_y = 0;
    int start_down_x = 0;
    int start_down_y = 0;
    int end_up_x = 0;
    int end_up_y = 0;
    int end_down_x = 0;
    int end_down_y = 0;
    int jjj = 0;
    int min_x = 0;
    int max_y = 0;
    int max_heigth = 0;
    std::vector<int> card_x;
    std::vector<int> card_x1;
    std::vector<int> card_y;
    std::vector<int> card_y1;
    std::vector<int> card_y_need;
    std::vector<int> card_height;
    int need_height = 0;
    if (contours2.size() == 0)
    {
        return;
    }
    for (int j = 0; j < contours2.size(); j++)
    {
        rect = boundingRect(Mat(contours2[j]));
        int rect_area = rect.area();
        card_x1.push_back(rect.x);
        card_y1.push_back(rect.y);
        if (rect_area > 80)
        {
            if (rect.width > 15 && rect.height > 15)
            {
                contours3.push_back(contours2[j]);
            }
        }
    }

    int minValue_xx = *min_element(card_x1.begin(), card_x1.end());
    int height_22_i = 0;
    for (int j = 0; j < contours3.size(); j++)
    {
        rect = boundingRect(Mat(contours3[j]));
        int rect_area = rect.area();
        min_x = rect.x;
        max_y = rect.y;
        card_x.push_back(min_x);
        if (rect.height > 22)
        {
            card_y_need.push_back(max_y);
            card_height.push_back(rect.height);
            need_height += rect.height;
            height_22_i++;
        }
    }

    if (height_22_i == 0 || need_height == 0)
    {
        return;
    }
    need_height = need_height / height_22_i;
    if (need_height == 0)
    {
        return;
    }
    if (contours3.size() == 0)
    {
        return;
    }
    int minValue_x_asix = *min_element(card_x.begin(), card_x.end());
    int minValue_y_asix = *min_element(card_y_need.begin(), card_y_need.end());
    if (card_y_need.size() == 0)
    {
        return;
    }
    double sum1 = std::accumulate(std::begin(card_y_need), std::end(card_y_need), 0.0);
    double mean = sum1 / card_y_need.size();
    int avgValue_y_asix = mean;
    minValue_y_asix = avgValue_y_asix;
    int minPosition = min_element(card_x.begin(), card_x.end()) - card_x.begin();
    int maxValue_height = *max_element(card_height.begin(), card_height.end());
    int maxPosition_height = max_element(card_height.begin(), card_height.end()) - card_height.begin();
    int maxValue_x = *max_element(card_x.begin(), card_x.end());
    int maxPosition_x = max_element(card_x.begin(), card_x.end()) - card_x.begin();
    minValue_x_asix = minValue_x_asix;
    rect = boundingRect(Mat(contours3[maxPosition_x]));
   int need_width = 0;
    if (need_add_head_length != 0)
    {
        need_width = (rect.x + rect.width) - minValue_x_asix + need_add_head_length;
    }
    else
    {
        need_width = (rect.x + rect.width) - minValue_x_asix;
    }
    if (need_height > 65)
    {
        need_height = (boundingRect(Mat(contours3[minPosition])).height + boundingRect(Mat(contours3[maxPosition_x])).height) / 2;
    }
    start_up_x = boundingRect(Mat(contours3[minPosition])).x;
    start_up_y = minValue_y_asix;
    end_up_x = boundingRect(Mat(contours3[maxPosition_x])).x + boundingRect(Mat(contours3[maxPosition_x])).width;
    end_up_y = boundingRect(Mat(contours3[maxPosition_x])).y;*/

    dstImg_show_20230518001 = raw_new;

    //将图片查找轮廓后进行裁剪
    //边缘检测
    Mat edges;
    std::vector<std::vector<cv::Point>>  contourSpit;
    std::vector<cv::Point>  merge_list;
    Canny(dstImg_show_20230518001,edges,50,150);
    std::vector<cv::Point>  vertex_list;
    findContours(edges,contourSpit,cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    if(contourSpit.size()==0){
        return;
    }
    RotatedRect rotatedRect;
    for (const auto& cnt : contourSpit){
        //判断轮廓定点数，过少或过多的话代表不是近似矩形，放弃
        rotatedRect = minAreaRect(cnt);
        //cout<<"w111::::"<<rect.size.width<<"h222::::"<<rect.size.height<<endl;
        if(rotatedRect.size.height*rotatedRect.size.width<200){
            continue;
        }

        //rect.size.width
        //cout<<"a:"<<rect.size.height*rect.size.width<<endl;
        double perimeter = arcLength(cnt, true);
        approxPolyDP(cnt,vertex_list, 0.05 * perimeter, true);
       // if(vertex_list.size()<3||vertex_list.size()>16){
       //     continue;
       // }
        for(const auto& cnt2 : cnt){
            merge_list.push_back(cnt2);
        }
    }
    if(merge_list.size()<=50){
        return;
    }
    cv::Rect boundingRectangle = boundingRect(merge_list);
    if(boundingRectangle.empty()){
        return;
    }
    /*std::cout << "Bounding Rectangle: " << std::endl;
    std::cout << "x: " << boundingRectangle.x << std::endl;
    std::cout << "y: " << boundingRectangle.y << std::endl;
    std::cout << "width: " << boundingRectangle.width << std::endl;
    std::cout << "height: " << boundingRectangle.height << std::endl;*/
    cv::Rect crop_region(boundingRectangle.x, boundingRectangle.y, boundingRectangle.width, boundingRectangle.height); // x, y, width, height
    // 裁剪图像
    dstImg = dstImg_show_20230518001(crop_region);
    cvtColor(dstImg, gray1, COLOR_BGR2GRAY);
    //图像旋转180度,根据最大的轮廓提取出图像
    flip(gray1,dstImg,1);
    imwrite(last_path1.toStdString(), dstImg);
}


void PictureAnalysis::RotatePng_20241012(QString scr_path, QString new_path, QString last_path1, int head_length, int find_characteristic_number, int thresh, int thresh1, int pix_width,int company_id)
{
    int debug_status = 0;
    int need_add_head_length = head_length;
    Mat src, src1, src_edge, src_gray, src_gray1, src_rotate, scr_gs, src_gs1;
    Mat src2, src3, src_edge2, src_gray2, src_gray12;
    Mat gray, binImg;
    double angle = 0;
    src = imread(scr_path.toStdString());
    src1 = imread(scr_path.toStdString());
    src3 = imread(scr_path.toStdString());
    int  heightxx = src1.rows;
    int widthxx = src1.cols;
    Rect rect1x_start(0, 0, widthxx / 5, heightxx);
    Rect rect1x_start1(0, 0, (widthxx *3)/ 8, heightxx);
    Rect rect1x_end(widthxx - 500, 0, 1200, heightxx);
    cv::Scalar color = cv::Scalar(0, 0, 0);
    if (need_add_head_length < 10)
    {
        if (company_id == 2)
        {
            rectangle(src1, rect1x_start1, Scalar(0, 0, 0), -1);
            rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
            if (debug_status)
            {
            }
        }
        else
        {
            rectangle(src1, rect1x_start, Scalar(0, 0, 0), -1);
            rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
            if (debug_status)
            {
            }
        }
    }
    else
    {
        rectangle(src1, rect1x_start1, Scalar(0, 0, 0), -1);
        rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
        if (debug_status)
        {
        }
    }
    cvtColor(src1, src_gray, COLOR_RGB2GRAY);
    cvtColor(src, src_gray2, COLOR_RGB2GRAY);
    double thres1 = 130;
    double maxval1 = 150;
    Mat src4;
    threshold(src1, src4, thresh, maxval1, CV_THRESH_BINARY);
    threshold(src1, src2, thresh1, maxval1, CV_THRESH_BINARY);
    if (debug_status)
    {
    }
    Canny(src1, src_edge, 50, 150, 3);
    if (debug_status)
    {
    }
    Canny(src2, src_edge2, 50, 150, 3);
    if (debug_status)
    {
    }
    std::vector<Vec2f> plines;
    double minLineLength = 0;
    double	maxLineGap = 0;
    int count_number = 3;
    int value1 = 220;
    int num_count1 = 15;
    num_count1 = find_characteristic_number;
    if (plines.size() < 1)
    {
        for (int ii = value1; ii != 0; ii--)
        {
            std::vector<Vec2f> plines1;
            HoughLines(src_edge2, plines1, 1, CV_PI / 180, ii, minLineLength, maxLineGap);
            if (plines1.size() > num_count1)
            {
                plines = plines1;
                break;
            }
        }
        if (plines.size() == 0)
        {
            HoughLines(src_edge2, plines, 1, CV_PI / 180, value1 - 20, minLineLength, maxLineGap);
        }
    }
    float sum = 0;
    int sum_count = 0;
    int line_start_x = 2500;
    double k = 0;
    list<double> k_list;
    list<QString> x1_list;
    list<double> angle_list;
    list<double> theta_list;
    if (plines.size() > 2)
    {
        double max_delete_number_ratio = 0.45;
        int delete_number = plines.size() * max_delete_number_ratio;
        std::sort(plines.begin(), plines.end(),
                  [](const cv::Vec2f& a, const cv::Vec2f& b) {
            return std::abs(a[1]) < std::abs(b[1]);
        });
        plines.erase(plines.end() - delete_number, plines.end());
        double min_delete_number_ratio = 0.45;
        delete_number = plines.size() * min_delete_number_ratio;
        std::sort(plines.begin(), plines.end(),
                  [](const cv::Vec2f& a, const cv::Vec2f& b) {
            return std::abs(a[1]) < std::abs(b[1]);
        });
        plines.erase(plines.begin(), plines.begin() + delete_number);
    }
    if (plines.size() == 0)
    {
        return;
    }
    std::map<int, int> angle_map;
    int cnt = 0;
    int max_cnt = 0;
    float best_angle = 0.0;
    int max_angle = 50;
    int max_iter = 300;
    int T_length = src_edge2.cols > src_edge2.rows ? src_edge2.rows : src_edge2.cols;
    for (size_t i = 0; i < plines.size(); i++)
    {

        float rho = plines[i][0];
        float theta = plines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + line_start_x * (-b));
        pt1.y = cvRound(y0 + line_start_x * (a));
        pt2.x = cvRound(x0 - line_start_x * (-b));
        pt2.y = cvRound(y0 - line_start_x * (a));
        int length_pt = sqrt(std::pow(pt2.x - pt1.x, 2) + std::pow(pt2.y - pt1.y, 2));
        if (length_pt < (T_length * 0.05)) continue;
        Point pt_mid((pt1.x + pt2.x) / 2, (pt1.y + pt2.y) / 2);
        float ang_ = atan2((pt2.y - pt1.y)*1.0, (pt2.x - pt1.x)*1.0);
        float theta1 = CV_PI / 2 + ang_;
        float fangle = theta1 / CV_PI * 360;
        fangle = round(180 - fangle);
        if (abs(fangle) < max_angle && pt_mid.y > src_edge2.rows*0.15 && pt_mid.y < src_edge2.rows*(1 - 0.15))
        {
            cnt++;
            sum += theta;
            sum_count++;
            cv::line(src_edge2, pt1, pt2, Scalar(255, 255, 0), 1, cv::LINE_AA);
            if (angle_map.end() == angle_map.find(fangle))
            {
                angle_map[fangle] = 1;
            }
            else
            {
                angle_map[fangle]++;
                if (angle_map[fangle] > max_cnt) {
                    max_cnt = angle_map[fangle];
                    best_angle = fangle;
                }
            }
        }
    }
    if (debug_status)
    {
    }
    float average = sum / sum_count;
    if (sum_count == 0)
    {
        average = 0;
    }
    double angleDegrees1 = average * 180.0 / CV_PI;
    double cz = abs(average - CV_PI /2);
    angle = average / CV_PI * 180 - 90;
    Point2f center;
    center.x = float(src3.cols / 2.0);
    center.y = float(src3.rows / 2.0);
    int length = 0;
    length = sqrt(src3.cols*src3.cols + src3.rows*src3.rows);
    Mat M = getRotationMatrix2D(center, angle, 1);
    warpAffine(src, src_rotate, M, Size(length, src3.rows), 1, 0, Scalar(0, 0, 0));
    if (debug_status)
    {
    }
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(src_edge2, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::Mat contourImage = src_edge2.clone();
    cv::drawContours(contourImage, contours, -1, cv::Scalar(255, 0, 0), 2);
    /*auto dao = AnalysisDao::instance();
    bool bResult = true;
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName2 = strPath + "\\" + "77777" + ".png";
    imwrite(strPathFileName2.toStdString(),contourImage);*/

    cv::RotatedRect boundingBox = cv::minAreaRect(contours[0]);
    float angle1 = boundingBox.angle;

    double anglexx = 0;
    double anglexx1 = 0;
    double anglexx2 = 0;
    for (const auto& contour : contours) {
        cv::Moments mu = cv::moments(contour);
        anglexx = atan2(2 * mu.mu11, mu.m00 - mu.m20) * 180 / CV_PI;
    }

    for (const auto& contour : contours)
    {
        cv::RotatedRect rect = cv::minAreaRect(contour);
        float angle2222 = rect.angle;
        anglexx1 = 90.0 - std::abs(angle2222);
    }
    float correctionAngle = 0;

    if (anglexx < 0)
    {
        correctionAngle =-(90.0 - std::abs(anglexx1));
    }
    else
    {
        correctionAngle = (90.0 - std::abs(anglexx1));
    }
    if (abs(anglexx1) > 35 || abs(anglexx1) == 35|| abs(correctionAngle) > 35 || abs(correctionAngle) == 35)
    {
        if (abs(angle) > 35)
        {
            angle = 0;
        }
        double angleDegrees21 = angle * 180.0 / CV_PI;
        correctionAngle = angle;
    }
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(boundingBox.center, correctionAngle, 1.0);
    cv::Mat rotatedImage;
    cv::warpAffine(src, src_rotate, rotationMatrix, src3.size(), cv::INTER_CUBIC);
    if (debug_status)
    {
        cv::imshow("src_rotate2", src_rotate);
    }
    Mat gray1;
    cvtColor(src_rotate, gray1, COLOR_BGR2GRAY);
    imwrite(new_path.toStdString(), gray1);
    std::vector<std::vector<Point> > contours2;
    std::vector<std::vector<Point> > contours3;
    Mat raw_new = imread(new_path.toStdString());
    Mat dstImg_show_20230412001;
    Mat dstImg_show_20230518001;
    Mat SecondFindImg;
    cvtColor(raw_new, SecondFindImg, COLOR_BGR2GRAY);
    double thres = thresh;
    double maxval = 160;
    threshold(SecondFindImg, SecondFindImg, thres, maxval, CV_THRESH_BINARY);
    findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    Mat dstImg;
    Mat dstImg_show;
    Rect rect;
    Rect rect1;
    Rect rect_need;
    int start_up_x = 0;
    int start_up_y = 0;
    int start_down_x = 0;
    int start_down_y = 0;
    int end_up_x = 0;
    int end_up_y = 0;
    int end_down_x = 0;
    int end_down_y = 0;
    int jjj = 0;
    int min_x = 0;
    int max_y = 0;
    int max_heigth = 0;
    std::vector<int> card_x;
    std::vector<int> card_x1;
    std::vector<int> card_y;
    std::vector<int> card_y1;
    std::vector<int> card_y_need;
    std::vector<int> card_height;
    int need_height = 0;
    if (contours2.size() == 0)
    {
        return;
    }
    for (int j = 0; j < contours2.size(); j++)
    {
        rect = boundingRect(Mat(contours2[j]));
        int rect_area = rect.area();
        card_x1.push_back(rect.x);
        card_y1.push_back(rect.y);
        if (rect_area > 80)
        {
            if (rect.width > 15 && rect.height > 15)
            {
                contours3.push_back(contours2[j]);
            }
        }
    }

    int minValue_xx = *min_element(card_x1.begin(), card_x1.end());
    int height_22_i = 0;
    for (int j = 0; j < contours3.size(); j++)
    {
        rect = boundingRect(Mat(contours3[j]));
        int rect_area = rect.area();
        min_x = rect.x;
        max_y = rect.y;
        card_x.push_back(min_x);
        if (rect.height > 22)
        {
            card_y_need.push_back(max_y);
            card_height.push_back(rect.height);
            need_height += rect.height;
            height_22_i++;
        }
    }

    if (height_22_i == 0 || need_height == 0)
    {
        return;
    }
    need_height = need_height / height_22_i;
    if (need_height == 0)
    {
        return;
    }
    if (contours3.size() == 0)
    {
        return;
    }
    int minValue_x_asix = *min_element(card_x.begin(), card_x.end());
    int minValue_y_asix = *min_element(card_y_need.begin(), card_y_need.end());
    if (card_y_need.size() == 0)
    {
        return;
    }
    double sum1 = std::accumulate(std::begin(card_y_need), std::end(card_y_need), 0.0);
    double mean = sum1 / card_y_need.size();
    int avgValue_y_asix = mean;
    minValue_y_asix = avgValue_y_asix;
    int minPosition = min_element(card_x.begin(), card_x.end()) - card_x.begin();
    int maxValue_height = *max_element(card_height.begin(), card_height.end());
    int maxPosition_height = max_element(card_height.begin(), card_height.end()) - card_height.begin();
    int maxValue_x = *max_element(card_x.begin(), card_x.end());
    int maxPosition_x = max_element(card_x.begin(), card_x.end()) - card_x.begin();
    minValue_x_asix = minValue_x_asix;
    rect = boundingRect(Mat(contours3[maxPosition_x]));
    int need_width = 0;
    if (need_add_head_length != 0)
    {
        need_width = (rect.x + rect.width) - minValue_x_asix + need_add_head_length;
    }
    else
    {
        need_width = (rect.x + rect.width) - minValue_x_asix;
    }
    if (need_height > 65)
    {
        need_height = (boundingRect(Mat(contours3[minPosition])).height + boundingRect(Mat(contours3[maxPosition_x])).height) / 2;
    }
    start_up_x = boundingRect(Mat(contours3[minPosition])).x;
    start_up_y = minValue_y_asix;
    end_up_x = boundingRect(Mat(contours3[maxPosition_x])).x + boundingRect(Mat(contours3[maxPosition_x])).width;
    end_up_y = boundingRect(Mat(contours3[maxPosition_x])).y;
    if (need_add_head_length != 0)
    {
        rect_need.x = minValue_x_asix - need_add_head_length;
    }
    else
    {
        rect_need.x = minValue_x_asix;
    }
    rect_need.y = start_up_y;
    if (pix_width > raw_new.cols)
    {
        rect_need.width = raw_new.cols;
    }
    else
    {
        rect_need.width = pix_width;
    }
    rect_need.height = need_height;
    if (rect_need.x + pix_width > 2500)
    {
        rect_need.x = 2500 - pix_width - 10;
    }
    if (rect_need.x < 0)
    {
        rect_need.x = 0;
    }
    if (rect_need.y < 0)
    {
        rect_need.y = 0;
    }
    dstImg_show_20230518001 = raw_new;
    dstImg = dstImg_show_20230518001(rect_need);
    cvtColor(dstImg, gray1, COLOR_BGR2GRAY);
    //图像旋转180度,根据最大的轮廓提取出图像
    flip(gray1,dstImg,1);
    imwrite(last_path1.toStdString(), dstImg);
}

void PictureAnalysis::RotatePng_20241012_paper930(QString scr_path, QString new_path, QString last_path1, int head_length, int find_characteristic_number, int thresh, int thresh1, int pix_width,int company_id)
{
    int debug_status = 0;
    int need_add_head_length = head_length;
    Mat src, src1, src_edge, src_gray, src_gray1, src_rotate, scr_gs, src_gs1;
    Mat src2, src3, src_edge2, src_gray2, src_gray12;
    Mat gray, binImg;
    src = imread(scr_path.toStdString());
    src1 = imread(scr_path.toStdString());
    src3 = imread(scr_path.toStdString());
    int  heightxx = src1.rows;
    int widthxx = src1.cols;
    Rect rect1x_start(0, 0, widthxx / 5, heightxx);//width 2500   height 320
    Rect rect1x_start1(0, 0, (widthxx *3)/ 8, heightxx);
    Rect rect1x_end(widthxx - 500, 0, 1200, heightxx);
    cv::Scalar color = cv::Scalar(0, 0, 0);
    /* if (need_add_head_length < 10)
    {
        if (company_id == 2)
        {
            rectangle(src1, rect1x_start1, Scalar(0, 0, 0), -1);
            rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
            if (debug_status)
            {
            }
        }
        else
        {
            rectangle(src1, rect1x_start, Scalar(0, 0, 0), -1);
            rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
            if (debug_status)
            {
            }
        }
    }
    else
    {
        rectangle(src1, rect1x_start1, Scalar(0, 0, 0), -1);
        rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
        if (debug_status)
        {
        }
    }*/
    cvtColor(src1, src_gray, COLOR_RGB2GRAY);
    cvtColor(src, src_gray2, COLOR_RGB2GRAY);
    double thres1 = 130;
    double maxval1 = 150;
    Mat src4;
    threshold(src1, src4, thresh, maxval1, CV_THRESH_BINARY);
    threshold(src1, src2, thresh1, maxval1, CV_THRESH_BINARY);
    /*auto dao = AnalysisDao::instance();
    bool bResult = true;
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName = strPath + "\\" + "111111" + ".png";
    QString strPathFileName2 = strPath + "\\" + "222222" + ".png";
    imwrite(strPathFileName.toStdString(),src4);
    imwrite(strPathFileName2.toStdString(),src2);*/
    if (debug_status)
    {
    }
    Canny(src1, src_edge, 50, 150, 3);//边缘检测
    if (debug_status)
    {
    }
    Canny(src2, src_edge2, 50, 150, 3);
    if (debug_status)
    {
    }
    /*auto dao = AnalysisDao::instance();
    bool bResult = true;
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName = strPath + "\\" + "111111" + ".png";
    QString strPathFileName2 = strPath + "\\" + "222222" + ".png";
    imwrite(strPathFileName.toStdString(),src_edge);
    imwrite(strPathFileName2.toStdString(),src_edge2);*/
    std::vector<Vec2f> plines;
    double minLineLength = 0;
    double	maxLineGap = 0;
    int value1 = 220;
    int num_count1 = find_characteristic_number;
    for (int ii = value1; ii != 0; ii--)
    {
        std::vector<Vec2f> plines1;
        HoughLines(src_edge2, plines1, 1, CV_PI / 180, ii, minLineLength, maxLineGap);
        if (plines1.size() > num_count1)
        {
            plines = plines1;
            break;
        }
    }
    if (plines.size() == 0)
    {
        HoughLines(src_edge2, plines, 1, CV_PI / 180, value1 - 20, minLineLength, maxLineGap);
    }

    float sum = 0;
    int sum_count = 0;
    int line_start_x = 2500;
    /* if (plines.size() > 2)
    {
        double max_delete_number_ratio = 0.45;
        int delete_number = plines.size() * max_delete_number_ratio;
        std::sort(plines.begin(), plines.end(),
                  [](const cv::Vec2f& a, const cv::Vec2f& b) {
            return std::abs(a[1]) < std::abs(b[1]);
        });
        plines.erase(plines.end() - delete_number, plines.end());
        double min_delete_number_ratio = 0.45;
        delete_number = plines.size() * min_delete_number_ratio;
        std::sort(plines.begin(), plines.end(),
                  [](const cv::Vec2f& a, const cv::Vec2f& b) {
            return std::abs(a[1]) < std::abs(b[1]);
        });//升序排列
        plines.erase(plines.begin(), plines.begin() + delete_number);
    }*/
    if (plines.size() == 0)
    {
        return;
    }

    /*auto dao = AnalysisDao::instance();
    bool bResult = true;
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName2 = strPath + "\\" + "33333" + ".png";
    imwrite(strPathFileName2.toStdString(),src_edge2);*/


    std::map<int, int> angle_map;
    int cnt = 0;
    int max_cnt = 0;
    float best_angle = 0.0;
    int max_angle = 50;
    int T_length = src_edge2.cols > src_edge2.rows ? src_edge2.rows : src_edge2.cols;
    for (size_t i = 0; i < plines.size(); i++)
    {
        float rho = plines[i][0];//极径
        float theta = plines[i][1];//极角
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;//极坐标转换
        pt1.x = cvRound(x0 + line_start_x * (-b));//极坐标转换为笛卡尔坐标
        pt1.y = cvRound(y0 + line_start_x * (a));
        pt2.x = cvRound(x0 - line_start_x * (-b));
        pt2.y = cvRound(y0 - line_start_x * (a));
        int length_pt = sqrt(std::pow(pt2.x - pt1.x, 2) + std::pow(pt2.y - pt1.y, 2));//三角函数求解
        if (length_pt < (T_length * 0.05)) continue;
        Point pt_mid((pt1.x + pt2.x) / 2, (pt1.y + pt2.y) / 2);//线段中点
        float ang_ = atan2((pt2.y - pt1.y)*1.0, (pt2.x - pt1.x)*1.0);
        float theta1 = CV_PI / 2 + ang_;
        float fangle = theta1 / CV_PI * 360;
        fangle = round(180 - fangle);
        if (abs(fangle) < max_angle && pt_mid.y > src_edge2.rows*0.15 && pt_mid.y < src_edge2.rows*(1 - 0.15))
        {
            cnt++;
            sum += theta;
            sum_count++;
            cv::line(src_edge2, pt1, pt2, Scalar(255, 255, 0), 1, cv::LINE_AA);
            if (angle_map.end() == angle_map.find(fangle))
            {
                angle_map[fangle] = 1;
            }
            else
            {
                angle_map[fangle]++;
                if (angle_map[fangle] > max_cnt) {
                    max_cnt = angle_map[fangle];
                    best_angle = fangle;
                }
            }
        }
    }
    // strPathFileName2 = strPath + "\\" + "44444" + ".png";
    // imwrite(strPathFileName2.toStdString(),src_edge2);

    if (debug_status)
    {
    }
    float average = 0;
    if (sum_count != 0)
    {
        average =  sum / sum_count;
    }
    double angleDegrees1 = average * 180.0 / CV_PI;//极角平均值
    double cz = abs(average - CV_PI /2);
    double  angle = average / CV_PI * 180 - 90;
    Point2f center;
    center.x = float(src3.cols / 2.0);
    center.y = float(src3.rows / 2.0);
    int length = sqrt(src3.cols*src3.cols + src3.rows*src3.rows);
    Mat M = getRotationMatrix2D(center, angle, 1);
    warpAffine(src, src_rotate, M, Size(length, src3.rows), 1, 0, Scalar(0, 0, 0));//仿射变换  针对膜条倾斜的情况将膜条摆正
    /* auto dao = AnalysisDao::instance();
    bool bResult = true;
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName2 = strPath + "\\" + "55555" + ".png";
    imwrite(strPathFileName2.toStdString(),src_rotate);*/



    if (debug_status)
    {
    }
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(src_edge2, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::Mat contourImage = src_rotate.clone();
    cv::drawContours(contourImage, contours, -1, cv::Scalar(255, 0, 0), 2);//绘制轮廓
    auto dao = AnalysisDao::instance();
    bool bResult = true;
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString original_piture_path = "original";
    QString strPath = piture_root_str + "\\" + original_piture_path;
    QString strPathFileName2 = strPath + "\\" + "88888" + ".png";
    imwrite(strPathFileName2.toStdString(),contourImage);


    cv::RotatedRect boundingBox = cv::minAreaRect(contours[0]);
    float angle1 = boundingBox.angle;

    double anglexx = 0;
    double anglexx1 = 0;
    double anglexx2 = 0;
    for (const auto& contour : contours) {
        cv::Moments mu = cv::moments(contour);
        anglexx = atan2(2 * mu.mu11, mu.m00 - mu.m20) * 180 / CV_PI;
    }

    for (const auto& contour : contours)
    {
        cv::RotatedRect rect = cv::minAreaRect(contour);
        float angle2222 = rect.angle;
        anglexx1 = 90.0 - std::abs(angle2222);
    }
    float correctionAngle = 0;

    if (anglexx < 0)
    {
        correctionAngle =-(90.0 - std::abs(anglexx1));
    }
    else
    {
        correctionAngle = (90.0 - std::abs(anglexx1));
    }
    if (abs(anglexx1) > 35 || abs(anglexx1) == 35|| abs(correctionAngle) > 35 || abs(correctionAngle) == 35)
    {
        if (abs(angle) > 35)
        {
            angle = 0;
        }
        double angleDegrees21 = angle * 180.0 / CV_PI;
        correctionAngle = angle;
    }
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(boundingBox.center, correctionAngle, 1.0);
    cv::Mat rotatedImage;
    cv::warpAffine(src, src_rotate, rotationMatrix, src3.size(), cv::INTER_CUBIC);
    if (debug_status)
    {
        cv::imshow("src_rotate2", src_rotate);
    }
    Mat gray1;
    cvtColor(src_rotate, gray1, COLOR_BGR2GRAY);
    imwrite(new_path.toStdString(), gray1);
    std::vector<std::vector<Point> > contours2;
    std::vector<std::vector<Point> > contours3;
    Mat raw_new = imread(new_path.toStdString());
    Mat dstImg_show_20230412001;
    Mat dstImg_show_20230518001;
    Mat SecondFindImg;
    cvtColor(raw_new, SecondFindImg, COLOR_BGR2GRAY);
    double thres = thresh;
    double maxval = 160;
    threshold(SecondFindImg, SecondFindImg, thres, maxval, CV_THRESH_BINARY);
    findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    Mat dstImg;
    Mat dstImg_show;
    Rect rect;
    Rect rect1;
    Rect rect_need;
    int start_up_x = 0;
    int start_up_y = 0;
    int start_down_x = 0;
    int start_down_y = 0;
    int end_up_x = 0;
    int end_up_y = 0;
    int end_down_x = 0;
    int end_down_y = 0;
    int jjj = 0;
    int min_x = 0;
    int max_y = 0;
    int max_heigth = 0;
    std::vector<int> card_x;
    std::vector<int> card_x1;
    std::vector<int> card_y;
    std::vector<int> card_y1;
    std::vector<int> card_y_need;
    std::vector<int> card_height;
    int need_height = 0;
    if (contours2.size() == 0)
    {
        return;
    }
    for (int j = 0; j < contours2.size(); j++)
    {
        rect = boundingRect(Mat(contours2[j]));
        int rect_area = rect.area();
        card_x1.push_back(rect.x);
        card_y1.push_back(rect.y);
        if (rect_area > 80)
        {
            if (rect.width > 15 && rect.height > 15)
            {
                contours3.push_back(contours2[j]);
            }
        }
    }

    int minValue_xx = *min_element(card_x1.begin(), card_x1.end());
    int height_22_i = 0;
    for (int j = 0; j < contours3.size(); j++)
    {
        rect = boundingRect(Mat(contours3[j]));
        int rect_area = rect.area();
        min_x = rect.x;
        max_y = rect.y;
        card_x.push_back(min_x);
        if (rect.height > 22)
        {
            card_y_need.push_back(max_y);
            card_height.push_back(rect.height);
            need_height += rect.height;
            height_22_i++;
        }
    }

    if (height_22_i == 0 || need_height == 0)
    {
        return;
    }
    need_height = need_height / height_22_i;
    if (need_height == 0)
    {
        return;
    }
    if (contours3.size() == 0)
    {
        return;
    }
    int minValue_x_asix = *min_element(card_x.begin(), card_x.end());
    int minValue_y_asix = *min_element(card_y_need.begin(), card_y_need.end());
    if (card_y_need.size() == 0)
    {
        return;
    }
    double sum1 = std::accumulate(std::begin(card_y_need), std::end(card_y_need), 0.0);
    double mean = sum1 / card_y_need.size();
    int avgValue_y_asix = mean;
    minValue_y_asix = avgValue_y_asix;
    int minPosition = min_element(card_x.begin(), card_x.end()) - card_x.begin();
    int maxValue_height = *max_element(card_height.begin(), card_height.end());
    int maxPosition_height = max_element(card_height.begin(), card_height.end()) - card_height.begin();
    int maxValue_x = *max_element(card_x.begin(), card_x.end());
    int maxPosition_x = max_element(card_x.begin(), card_x.end()) - card_x.begin();
    minValue_x_asix = minValue_x_asix;
    rect = boundingRect(Mat(contours3[maxPosition_x]));
    int need_width = 0;
    if (need_add_head_length != 0)
    {
        need_width = (rect.x + rect.width) - minValue_x_asix + need_add_head_length;
    }
    else
    {
        need_width = (rect.x + rect.width) - minValue_x_asix;
    }
    if (need_height > 65)
    {
        need_height = (boundingRect(Mat(contours3[minPosition])).height + boundingRect(Mat(contours3[maxPosition_x])).height) / 2;
    }
    start_up_x = boundingRect(Mat(contours3[minPosition])).x;
    start_up_y = minValue_y_asix;
    end_up_x = boundingRect(Mat(contours3[maxPosition_x])).x + boundingRect(Mat(contours3[maxPosition_x])).width;
    end_up_y = boundingRect(Mat(contours3[maxPosition_x])).y;
    if (need_add_head_length != 0)
    {
        rect_need.x = minValue_x_asix - need_add_head_length;
    }
    else
    {
        rect_need.x = minValue_x_asix;
    }
    rect_need.y = start_up_y;
    if (pix_width > raw_new.cols)
    {
        rect_need.width = raw_new.cols;
    }
    else
    {
        rect_need.width = pix_width;
    }
    rect_need.height = need_height;
    if (rect_need.x + pix_width > 2500)
    {
        rect_need.x = 2500 - pix_width - 10;
    }
    if (rect_need.x < 0)
    {
        rect_need.x = 0;
    }
    if (rect_need.y < 0)
    {
        rect_need.y = 0;
    }
    dstImg_show_20230518001 = raw_new;
    dstImg = dstImg_show_20230518001(rect_need);
    cvtColor(dstImg, gray1, COLOR_BGR2GRAY);
    imwrite(last_path1.toStdString(), gray1);//截取后的图像
}

void PictureAnalysis::RotatePng_20231206(QString scr_path, QString new_path, QString last_path1, int head_length, int find_characteristic_number, int thresh, int thresh1, int pix_width,int company_id)
{
    int debug_status = 0;
    int need_add_head_length = head_length;
    Mat src, src1, src_edge, src_gray, src_gray1, src_rotate, scr_gs, src_gs1;
    Mat src2, src3, src_edge2, src_gray2, src_gray12;
    Mat gray, binImg;
    double angle = 0;
    src = imread(scr_path.toStdString());
    src1 = imread(scr_path.toStdString());
    src3 = imread(scr_path.toStdString());
    int  heightxx = src1.rows;
    int widthxx = src1.cols;
    Rect rect1x_start(0, 0, widthxx / 5, heightxx);
    Rect rect1x_start1(0, 0, (widthxx *3)/ 8, heightxx);
    Rect rect1x_end(widthxx - 500, 0, 1200, heightxx);
    cv::Scalar color = cv::Scalar(0, 0, 0);
    if (need_add_head_length < 10)
    {
        if (company_id == 2)
        {
            rectangle(src1, rect1x_start1, Scalar(0, 0, 0), -1);
            rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
            if (debug_status)
            {
            }
        }
        else
        {
            rectangle(src1, rect1x_start, Scalar(0, 0, 0), -1);
            rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
            if (debug_status)
            {
            }
        }
    }
    else
    {
        rectangle(src1, rect1x_start1, Scalar(0, 0, 0), -1);
        rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
        if (debug_status)
        {
        }
    }
    cvtColor(src1, src_gray, COLOR_RGB2GRAY);
    cvtColor(src, src_gray2, COLOR_RGB2GRAY);
    double thres1 = 130;
    double maxval1 = 150;
    Mat src4;
    threshold(src1, src4, thresh, maxval1, CV_THRESH_BINARY);
    threshold(src1, src2, thresh1, maxval1, CV_THRESH_BINARY);
    if (debug_status)
    {
    }
    Canny(src1, src_edge, 50, 150, 3);
    if (debug_status)
    {
    }
    Canny(src2, src_edge2, 50, 150, 3);
    if (debug_status)
    {
    }
    std::vector<Vec2f> plines;
    double minLineLength = 0;
    double	maxLineGap = 0;
    int count_number = 3;
    int value1 = 220;
    int num_count1 = 15;
    num_count1 = find_characteristic_number;
    if (plines.size() < 1)
    {
        for (int ii = value1; ii != 0; ii--)
        {
            std::vector<Vec2f> plines1;
            HoughLines(src_edge2, plines1, 1, CV_PI / 180, ii, minLineLength, maxLineGap);
            if (plines1.size() > num_count1)
            {
                plines = plines1;
                break;
            }
        }
        if (plines.size() == 0)
        {
            HoughLines(src_edge2, plines, 1, CV_PI / 180, value1 - 20, minLineLength, maxLineGap);
        }
    }
    float sum = 0;
    int sum_count = 0;
    int line_start_x = 2500;
    double k = 0;
    list<double> k_list;
    list<QString> x1_list;
    list<double> angle_list;
    list<double> theta_list;
    if (plines.size() > 2)
    {
        double max_delete_number_ratio = 0.45;
        int delete_number = plines.size() * max_delete_number_ratio;
        std::sort(plines.begin(), plines.end(),
                  [](const cv::Vec2f& a, const cv::Vec2f& b) {
            return std::abs(a[1]) < std::abs(b[1]);
        });
        plines.erase(plines.end() - delete_number, plines.end());
        double min_delete_number_ratio = 0.45;
        delete_number = plines.size() * min_delete_number_ratio;
        std::sort(plines.begin(), plines.end(),
                  [](const cv::Vec2f& a, const cv::Vec2f& b) {
            return std::abs(a[1]) < std::abs(b[1]);
        });
        plines.erase(plines.begin(), plines.begin() + delete_number);
    }
    if (plines.size() == 0)
    {
        return;
    }
    std::map<int, int> angle_map;
    int cnt = 0;
    int max_cnt = 0;
    float best_angle = 0.0;
    int max_angle = 50;
    int max_iter = 300;
    int T_length = src_edge2.cols > src_edge2.rows ? src_edge2.rows : src_edge2.cols;
    for (size_t i = 0; i < plines.size(); i++)
    {

        float rho = plines[i][0];
        float theta = plines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + line_start_x * (-b));
        pt1.y = cvRound(y0 + line_start_x * (a));
        pt2.x = cvRound(x0 - line_start_x * (-b));
        pt2.y = cvRound(y0 - line_start_x * (a));
        int length_pt = sqrt(std::pow(pt2.x - pt1.x, 2) + std::pow(pt2.y - pt1.y, 2));
        if (length_pt < (T_length * 0.05)) continue;
        Point pt_mid((pt1.x + pt2.x) / 2, (pt1.y + pt2.y) / 2);
        float ang_ = atan2((pt2.y - pt1.y)*1.0, (pt2.x - pt1.x)*1.0);
        float theta1 = CV_PI / 2 + ang_;
        float fangle = theta1 / CV_PI * 360;
        fangle = round(180 - fangle);
        if (abs(fangle) < max_angle && pt_mid.y > src_edge2.rows*0.15 && pt_mid.y < src_edge2.rows*(1 - 0.15))
        {
            cnt++;
            sum += theta;
            sum_count++;
            cv::line(src_edge2, pt1, pt2, Scalar(255, 255, 0), 1, cv::LINE_AA);
            if (angle_map.end() == angle_map.find(fangle))
            {
                angle_map[fangle] = 1;
            }
            else
            {
                angle_map[fangle]++;
                if (angle_map[fangle] > max_cnt) {
                    max_cnt = angle_map[fangle];
                    best_angle = fangle;
                }
            }
        }
    }
    if (debug_status)
    {
    }
    float average = sum / sum_count;
    if (sum_count == 0)
    {
        average = 0;
    }
    double angleDegrees1 = average * 180.0 / CV_PI;
    double cz = abs(average - CV_PI /2);
    angle = average / CV_PI * 180 - 90;
    Point2f center;
    center.x = float(src3.cols / 2.0);
    center.y = float(src3.rows / 2.0);
    int length = 0;
    length = sqrt(src3.cols*src3.cols + src3.rows*src3.rows);
    Mat M = getRotationMatrix2D(center, angle, 1);
    warpAffine(src, src_rotate, M, Size(length, src3.rows), 1, 0, Scalar(0, 0, 0));
    if (debug_status)
    {
    }
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(src_edge2, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::Mat contourImage = src_edge2.clone();
    cv::drawContours(contourImage, contours, -1, cv::Scalar(255, 0, 0), 2);

    cv::RotatedRect boundingBox = cv::minAreaRect(contours[0]);
    float angle1 = boundingBox.angle;

    double anglexx = 0;
    double anglexx1 = 0;
    double anglexx2 = 0;
    for (const auto& contour : contours) {
        cv::Moments mu = cv::moments(contour);
        anglexx = atan2(2 * mu.mu11, mu.m00 - mu.m20) * 180 / CV_PI;
    }

    for (const auto& contour : contours)
    {
        cv::RotatedRect rect = cv::minAreaRect(contour);
        float angle2222 = rect.angle;
        anglexx1 = 90.0 - std::abs(angle2222);
    }
    float correctionAngle = 0;

    if (anglexx < 0)
    {
        correctionAngle =-(90.0 - std::abs(anglexx1));
    }
    else
    {
        correctionAngle = (90.0 - std::abs(anglexx1));
    }
    if (abs(anglexx1) > 35 || abs(anglexx1) == 35|| abs(correctionAngle) > 35 || abs(correctionAngle) == 35)
    {
        if (abs(angle) > 35)
        {
            angle = 0;
        }
        double angleDegrees21 = angle * 180.0 / CV_PI;
        correctionAngle = angle;
    }
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(boundingBox.center, correctionAngle, 1.0);
    cv::Mat rotatedImage;
    cv::warpAffine(src, src_rotate, rotationMatrix, src3.size(), cv::INTER_CUBIC);
    if (debug_status)
    {
        cv::imshow("src_rotate2", src_rotate);
    }
    Mat gray1;
    cvtColor(src_rotate, gray1, COLOR_BGR2GRAY);
    imwrite(new_path.toStdString(), gray1);
    std::vector<std::vector<Point> > contours2;
    std::vector<std::vector<Point> > contours3;
    Mat raw_new = imread(new_path.toStdString());
    Mat dstImg_show_20230412001;
    Mat dstImg_show_20230518001;
    Mat SecondFindImg;
    cvtColor(raw_new, SecondFindImg, COLOR_BGR2GRAY);
    double thres = thresh;
    double maxval = 160;
    threshold(SecondFindImg, SecondFindImg, thres, maxval, CV_THRESH_BINARY);
    findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    Mat dstImg;
    Mat dstImg_show;
    Rect rect;
    Rect rect1;
    Rect rect_need;
    int start_up_x = 0;
    int start_up_y = 0;
    int start_down_x = 0;
    int start_down_y = 0;
    int end_up_x = 0;
    int end_up_y = 0;
    int end_down_x = 0;
    int end_down_y = 0;
    int jjj = 0;
    int min_x = 0;
    int max_y = 0;
    int max_heigth = 0;
    std::vector<int> card_x;
    std::vector<int> card_x1;
    std::vector<int> card_y;
    std::vector<int> card_y1;
    std::vector<int> card_y_need;
    std::vector<int> card_height;
    int need_height = 0;
    if (contours2.size() == 0)
    {
        return;
    }
    for (int j = 0; j < contours2.size(); j++)
    {
        rect = boundingRect(Mat(contours2[j]));
        int rect_area = rect.area();
        card_x1.push_back(rect.x);
        card_y1.push_back(rect.y);
        if (rect_area > 80)
        {
            if (rect.width > 15 && rect.height > 15)
            {
                contours3.push_back(contours2[j]);
            }
        }
    }

    int minValue_xx = *min_element(card_x1.begin(), card_x1.end());
    int height_22_i = 0;
    for (int j = 0; j < contours3.size(); j++)
    {
        rect = boundingRect(Mat(contours3[j]));
        int rect_area = rect.area();
        min_x = rect.x;
        max_y = rect.y;
        card_x.push_back(min_x);
        if (rect.height > 22)
        {
            card_y_need.push_back(max_y);
            card_height.push_back(rect.height);
            need_height += rect.height;
            height_22_i++;
        }
    }

    if (height_22_i == 0 || need_height == 0)
    {
        return;
    }
    need_height = need_height / height_22_i;
    if (need_height == 0)
    {
        return;
    }
    if (contours3.size() == 0)
    {
        return;
    }
    int minValue_x_asix = *min_element(card_x.begin(), card_x.end());
    int minValue_y_asix = *min_element(card_y_need.begin(), card_y_need.end());
    if (card_y_need.size() == 0)
    {
        return;
    }
    double sum1 = std::accumulate(std::begin(card_y_need), std::end(card_y_need), 0.0);
    double mean = sum1 / card_y_need.size();
    int avgValue_y_asix = mean;
    minValue_y_asix = avgValue_y_asix;
    int minPosition = min_element(card_x.begin(), card_x.end()) - card_x.begin();
    int maxValue_height = *max_element(card_height.begin(), card_height.end());
    int maxPosition_height = max_element(card_height.begin(), card_height.end()) - card_height.begin();
    int maxValue_x = *max_element(card_x.begin(), card_x.end());
    int maxPosition_x = max_element(card_x.begin(), card_x.end()) - card_x.begin();
    minValue_x_asix = minValue_x_asix;
    rect = boundingRect(Mat(contours3[maxPosition_x]));
    int need_width = 0;
    if (need_add_head_length != 0)
    {
        need_width = (rect.x + rect.width) - minValue_x_asix + need_add_head_length;
    }
    else
    {
        need_width = (rect.x + rect.width) - minValue_x_asix;
    }
    if (need_height > 65)
    {
        need_height = (boundingRect(Mat(contours3[minPosition])).height + boundingRect(Mat(contours3[maxPosition_x])).height) / 2;
    }
    start_up_x = boundingRect(Mat(contours3[minPosition])).x;
    start_up_y = minValue_y_asix;
    end_up_x = boundingRect(Mat(contours3[maxPosition_x])).x + boundingRect(Mat(contours3[maxPosition_x])).width;
    end_up_y = boundingRect(Mat(contours3[maxPosition_x])).y;
    if (need_add_head_length != 0)
    {
        rect_need.x = minValue_x_asix - need_add_head_length;
    }
    else
    {
        rect_need.x = minValue_x_asix;
    }
    rect_need.y = start_up_y;
    if (pix_width > raw_new.cols)
    {
        rect_need.width = raw_new.cols;
    }
    else
    {
        rect_need.width = pix_width;
    }
    rect_need.height = need_height;
    if (rect_need.x + pix_width > 2500)
    {
        rect_need.x = 2500 - pix_width - 10;
    }
    if (rect_need.x < 0)
    {
        rect_need.x = 0;
    }
    if (rect_need.y < 0)
    {
        rect_need.y = 0;
    }
    dstImg_show_20230518001 = raw_new;
    dstImg = dstImg_show_20230518001(rect_need);
    cvtColor(dstImg, gray1, COLOR_BGR2GRAY);
    imwrite(last_path1.toStdString(), gray1);
}

void PictureAnalysis::RotatePng_20231110(QString scr_path, QString new_path, QString last_path1, int head_length, int find_characteristic_number, int thresh, int pix_width)
{
    int need_add_head_length = head_length;
    Mat src, src1, src_edge, src_gray, src_gray1, src_rotate;
    Mat gray, binImg;
    double angle = 0;
    src = imread(scr_path.toStdString());
    src1 = imread(scr_path.toStdString());
    int  heightxx = src1.rows;
    int widthxx = src1.cols;
    Rect rect1x_start(0, 0, widthxx/3, heightxx);
    Rect rect1x_end(widthxx-500, 0, 800, heightxx);
    cv::Scalar color = cv::Scalar(0, 0, 0);
    cv::rectangle(src1, rect1x_start, color, 2, cv::LINE_8);
    rectangle(src1, rect1x_start, Scalar(0, 0, 0), -1);
    rectangle(src1, rect1x_end, Scalar(0, 0, 0), -1);
    cvtColor(src1, src_gray, COLOR_RGB2GRAY);
    double thres1 = 130;
    double maxval1 = 150;
    threshold(src1, src1, thresh, maxval1, CV_THRESH_BINARY);
    Canny(src1, src_edge, 50, 150, 3);
    std::vector<Vec2f> plines;
    double minLineLength = 0;
    double	maxLineGap = 0;
    int count_number = 3;
    int value1 = 220;
    int num_count1 = 15;
    num_count1 = find_characteristic_number;
    if (plines.size() < 1)
    {
        for (int ii = value1; ii != 0; ii--)
        {
            std::vector<Vec2f> plines1;
            HoughLines(src_edge, plines1, 1, CV_PI / 180, ii, minLineLength, maxLineGap);
            if (plines1.size() > num_count1)
            {
                plines = plines1;
                break;
            }
        }
        if (plines.size() == 0)
        {
            HoughLines(src_edge, plines, 1, CV_PI / 180, value1 - 20, minLineLength, maxLineGap);
        }
    }
    float sum = 0;
    int sum_count = 0;
    int line_start_x = 2500;
    double k = 0;
    list<double> k_list;
    list<QString> x1_list;
    list<double> angle_list;
    list<double> theta_list;
    if (plines.size() > 4)
    {
        double max_delete_number_ratio = 0.45;
        int delete_number = plines.size() * max_delete_number_ratio;
        std::sort(plines.begin(), plines.end(),
                  [](const cv::Vec2f& a, const cv::Vec2f& b) {
            return std::abs(a[1]) < std::abs(b[1]);
        });
        plines.erase(plines.end() - delete_number, plines.end());
        double min_delete_number_ratio = 0.45;
        delete_number = plines.size() * min_delete_number_ratio;
        std::sort(plines.begin(), plines.end(),
                  [](const cv::Vec2f& a, const cv::Vec2f& b) {
            return std::abs(a[1]) < std::abs(b[1]);
        });
        plines.erase(plines.begin(), plines.begin() + delete_number);
    }
    if (plines.size() == 0)
    {
        return;
    }
    for (size_t i = 0; i < plines.size(); i++)
    {
        float rho = plines[i][0];
        float theta = plines[i][1];
        Point pt1, pt2;
        double a = cos(theta);
        double	b = sin(theta);
        double x0 = a * rho;
        double	y0 = b * rho;
        pt1.x = cvRound(x0 + line_start_x * (-b));
        pt1.y = cvRound(y0 + line_start_x * (a));
        pt2.x = cvRound(x0 - line_start_x * (-b));
        pt2.y = cvRound(y0 - line_start_x * (a));

        if (qAbs(pt1.y) < line_start_x && qAbs(pt2.y) < line_start_x)
        {
            double current_angle = theta * 180 / CV_PI;
            double current_angle1 = abs(current_angle - 90);
            cv::line(src_edge, pt1, pt2, cv::Scalar(255, 0, 0), 1, cv::LINE_AA);
            sum += theta;
            sum_count++;
            angle_list.push_back(current_angle);
            theta_list.push_back(theta);
            if (theta < CV_PI / 4 || theta > 3 * CV_PI / 4)
            {
            }
        }
    }
    float average = sum / sum_count;
    angle = average / CV_PI * 180 - 90;
    Point2f center;
    center.x = float(src.cols / 2.0);
    center.y = float(src.rows / 2.0);
    int length = 0;
    length = sqrt(src.cols*src.cols + src.rows*src.rows);
    Mat M = getRotationMatrix2D(center, angle, 1);
    warpAffine(src, src_rotate, M, Size(length, src.rows), 1, 0, Scalar(0, 0, 0));
    Mat gray1;
    cvtColor(src_rotate, gray1, COLOR_BGR2GRAY);
    imwrite(new_path.toStdString(), gray1);
    std::vector<std::vector<Point> > contours2;
    std::vector<std::vector<Point> > contours3;
    Mat raw_new = imread(new_path.toStdString());
    Mat dstImg_show_20230412001;
    Mat dstImg_show_20230518001;
    Mat SecondFindImg;
    cvtColor(raw_new, SecondFindImg, COLOR_BGR2GRAY);
    double thres = thresh;
    double maxval = 160;
    threshold(SecondFindImg, SecondFindImg, thres, maxval, CV_THRESH_BINARY);
    findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    Mat dstImg;
    Mat dstImg_show;
    Rect rect;
    Rect rect1;
    Rect rect_need;
    int start_up_x = 0;
    int start_up_y = 0;
    int start_down_x = 0;
    int start_down_y = 0;
    int end_up_x = 0;
    int end_up_y = 0;
    int end_down_x = 0;
    int end_down_y = 0;
    int jjj = 0;
    int min_x = 0;
    int max_y = 0;
    int max_heigth = 0;
    std::vector<int> card_x;
    std::vector<int> card_x1;
    std::vector<int> card_y;
    std::vector<int> card_y1;
    std::vector<int> card_y_need;
    std::vector<int> card_height;
    int need_height = 0;
    if (contours2.size() == 0)
    {
        return;
    }
    for (int j = 0; j < contours2.size(); j++)
    {
        rect = boundingRect(Mat(contours2[j]));
        int rect_area = rect.area();
        card_x1.push_back(rect.x);
        card_y1.push_back(rect.y);
        if (rect_area > 80)
        {
            if (rect.width > 15 && rect.height > 15)
            {
                contours3.push_back(contours2[j]);
            }
        }
    }
    int minValue_xx = *min_element(card_x1.begin(), card_x1.end());
    int height_22_i = 0;
    for (int j = 0; j < contours3.size(); j++)
    {
        rect = boundingRect(Mat(contours3[j]));
        int rect_area = rect.area();
        min_x = rect.x;
        max_y = rect.y;
        card_x.push_back(min_x);
        if (rect.height > 22)
        {
            card_y_need.push_back(max_y);
            card_height.push_back(rect.height);
            need_height += rect.height;
            height_22_i++;
        }
    }
    if (height_22_i == 0 || need_height == 0)
    {
        return;
    }
    need_height = need_height / height_22_i;
    if (need_height == 0)
    {
        return;
    }
    if (contours3.size() == 0)
    {
        return;
    }
    int minValue_x_asix = *min_element(card_x.begin(), card_x.end());
    int minValue_y_asix = *min_element(card_y_need.begin(), card_y_need.end());

    if (card_y_need.size() == 0)
    {
        return;
    }
    double sum1 = std::accumulate(std::begin(card_y_need), std::end(card_y_need), 0.0);
    double mean = sum1 / card_y_need.size();
    int avgValue_y_asix = mean;
    minValue_y_asix = avgValue_y_asix;
    int minPosition = min_element(card_x.begin(), card_x.end()) - card_x.begin();
    int maxValue_height = *max_element(card_height.begin(), card_height.end());
    int maxPosition_height = max_element(card_height.begin(), card_height.end()) - card_height.begin();
    int maxValue_x = *max_element(card_x.begin(), card_x.end());
    int maxPosition_x = max_element(card_x.begin(), card_x.end()) - card_x.begin();
    minValue_x_asix = minValue_x_asix;
    rect = boundingRect(Mat(contours3[maxPosition_x]));
    int need_width = 0;
    if (need_add_head_length != 0)
    {
        need_width = (rect.x + rect.width) - minValue_x_asix + need_add_head_length;
    }
    else
    {
        need_width = (rect.x + rect.width) - minValue_x_asix;
    }

    if (need_height > 65)
    {
        need_height = (boundingRect(Mat(contours3[minPosition])).height + boundingRect(Mat(contours3[maxPosition_x])).height) / 2;
    }
    start_up_x = boundingRect(Mat(contours3[minPosition])).x;
    start_up_y = minValue_y_asix;
    end_up_x = boundingRect(Mat(contours3[maxPosition_x])).x + boundingRect(Mat(contours3[maxPosition_x])).width;
    end_up_y = boundingRect(Mat(contours3[maxPosition_x])).y;
    if (need_add_head_length != 0)
    {
        rect_need.x = minValue_x_asix - need_add_head_length;
    }
    else
    {
        rect_need.x = minValue_x_asix;
    }
    rect_need.y = start_up_y;
    if (pix_width > raw_new.cols)
    {
        rect_need.width = raw_new.cols;
    }
    else
    {
        rect_need.width = pix_width;
    }
    rect_need.height = need_height;

    if (rect_need.x + pix_width > 2500)
    {
        rect_need.x = 2500 - pix_width - 10;
    }
    if (rect_need.x < 0)
    {
        rect_need.x = 0;
    }
    if (rect_need.y < 0)
    {
        rect_need.y = 0;
    }
    dstImg_show_20230518001 = raw_new;
    dstImg = dstImg_show_20230518001(rect_need);
    cvtColor(dstImg, gray1, COLOR_BGR2GRAY);
    imwrite(last_path1.toStdString(), gray1);
}

void PictureAnalysis::GetContoursPic(QString pSrcFileName, QString pDstFileName)
{
    Mat srcImg = imread(pSrcFileName.toStdString());
    Mat gray, binImg;
    cvtColor(srcImg, gray, COLOR_RGB2GRAY);
    threshold(gray, binImg, 80, 150, CV_THRESH_BINARY);
    std::vector<std::vector<Point> > contours;
    std::vector<Rect> boundRect(contours.size());
    findContours(binImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    float angle = 0;
    float sum = 0;
    int valid_number = 0;
    for (int i = 0; i < contours.size(); i++)
    {
        CvPoint2D32f rectpoint[4];
        CvBox2D rect = minAreaRect(Mat(contours[i]));
        cvBoxPoints(rect, rectpoint);
        int line1 = sqrt((rectpoint[1].y - rectpoint[0].y)*(rectpoint[1].y - rectpoint[0].y) + (rectpoint[1].x - rectpoint[0].x)*(rectpoint[1].x - rectpoint[0].x));
        int line2 = sqrt((rectpoint[3].y - rectpoint[0].y)*(rectpoint[3].y - rectpoint[0].y) + (rectpoint[3].x - rectpoint[0].x)*(rectpoint[3].x - rectpoint[0].x));
        float tmp = rect.angle;
        if ((line1 * line2 < 600))
        {
            continue;
        }
        if (tmp != 0 && abs(tmp) > 45)
        {
            sum += rect.angle;
            valid_number++;
        }
    }
    float average = sum / valid_number;
    if (abs(average) > 45)
    {
        if (average < 0)
        {
            average = 90 - abs(average);
        }
        else
        {
            average = average - 90;
        }
    }
    angle = average / CV_PI * 180 - 90;
    angle = average;
    if (valid_number == 0)
    {
        angle = 0;
    }
    Point2f center;
    center.x = float(srcImg.cols / 2.0);
    center.y = float(srcImg.rows / 2.0);
    int length = 0;
    length = sqrt(srcImg.cols*srcImg.cols + srcImg.rows*srcImg.rows);
    Mat M = getRotationMatrix2D(center, angle, 1);
    Mat src_rotate;
    warpAffine(srcImg, src_rotate, M, Size(length, srcImg.rows), 1, 0, Scalar(0, 0, 0));
    imwrite(pDstFileName.toStdString(), src_rotate);
}


Mat  PictureAnalysis::RotatePic(QString scr_path, QString new_path)
{
    Mat src, src_edge, src_gray, src_rotate;
    Mat gray, binImg;
    double angle;
    src = imread(scr_path.toStdString());
    cvtColor(src, src_gray, COLOR_RGB2GRAY);
    Canny(src_gray, src_edge, 50, 200, 3);
    std::vector<Vec2f> plines;
    HoughLines(src_edge, plines, 1, CV_PI / 180, 200, 0, 0);
    float sum = 0;
    for (size_t i = 0; i < plines.size(); i++)
    {
        float rho = plines[i][0];
        float theta = plines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        sum += theta;
        line(src_gray, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
    }
    float average = sum / plines.size();
    angle = average / CV_PI * 180 - 90;
    Point2f center;
    center.x = float(src.cols / 2.0);
    center.y = float(src.rows / 2.0);
    int length = 0;
    length = sqrt(src.cols*src.cols + src.rows*src.rows);
    Mat M = getRotationMatrix2D(center, angle, 1);
    warpAffine(src, src_rotate, M, Size(length, src.rows), 1, 0, Scalar(0, 0, 0));
    return src_rotate;
}

Mat  PictureAnalysis::concat(cv::Mat m1, cv::Mat m2)
{
    Mat imgL = m1;
    Mat imgR = m2;
    double start = getTickCount();
    Mat grayL, grayR;
    grayL = m1;
    grayR = m2;
    Rect rectCut = Rect(372, 122, 128, 360);
    Rect rectMatched = Rect(0, 0, imgR.cols / 2, imgR.rows);
    Mat imgTemp = grayL(Rect(rectCut));
    Mat imgMatched = grayR(Rect(rectMatched));
    int width = imgMatched.cols - imgTemp.cols + 1;
    int height = imgMatched.rows - imgTemp.rows + 1;
    Mat matchResult(height, width, CV_32FC1);
    matchTemplate(imgMatched, imgTemp, matchResult, TM_CCORR_NORMED);
    normalize(matchResult, matchResult, 0, 1, NORM_MINMAX, -1);
    double minValue, maxValue;
    Point minLoc, maxLoc;
    minMaxLoc(matchResult, &minValue, &maxValue, &minLoc, &maxLoc);
    Mat dstImg(imgL.rows, imgR.cols + rectCut.x - maxLoc.x, CV_8UC3, Scalar::all(0));
    Mat roiLeft = dstImg(Rect(0, 0, imgL.cols, imgL.rows));
    imgL.copyTo(roiLeft);
    Mat debugImg = imgR.clone();
    rectangle(debugImg, Rect(maxLoc.x, maxLoc.y, imgTemp.cols, imgTemp.rows), Scalar(0, 255, 0), 2, 8);
    imwrite("match.jpg", debugImg);
    Mat roiMatched = imgR(Rect(maxLoc.x, maxLoc.y - rectCut.y, imgR.cols - maxLoc.x, imgR.rows - 1 - (maxLoc.y - rectCut.y)));
    Mat roiRight = dstImg(Rect(rectCut.x, 0, roiMatched.cols, roiMatched.rows));
    roiMatched.copyTo(roiRight);
    double end = getTickCount();
    double useTime = (end - start) / getTickFrequency();
    return dstImg;
}


