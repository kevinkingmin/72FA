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
#include "../Include/DAO/baseSet/SystemSetDao.h"
#include "../Include/DAO/baseSet/JudgeDao.h"
#include "../Include/Model/result/JudgeRules.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "../Include/DAO/baseSet/TestPaperDao.h"
#include "../Include/DAO/baseSet/ItemDao.h"
#include "../Include/Model/baseSet/TestPaperModel.h"
#include "../Include/Model/baseSet/ItemModel.h"
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
#include <QDebug>
#include "../Include/Model/sample/SampleTestModel.h"
#include "../Include/Model/result/JudgeRules.h"
#include "../Include/Utilities/log.h"
#include "standard_curve.h"

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
//   auto dao = AnalysisDao::instance();
//   m_test_project_name = sampleId;
//   auto SampleQuery = dao->SelectSamples(m_test_project_name, &bResult);
//   if (bResult == false)
//   {
//       QMessageBox::warning(nullptr, "tip", "检索样本数据失败！", QMessageBox::Ok);
//       return false;
//   }
//   while (SampleQuery.next())
//   {
//       m_nSampleID = SampleQuery.value("sampleNo").toString();//.toInt();
//       m_nTestPaperID = SampleQuery.value("paperId").toInt();
//       AnalysisOneSample(m_nTestPaperID,1,file_path,"1","");
//   }
   return true;
}


bool PictureAnalysis::AnalysisOne(QString test_id, int paperId, QString sampleId)
{
    bool bResult = false;
//    auto dao = AnalysisDao::instance();
//    auto SampleQuery = dao->SelectTestIdFromSamples(test_id, &bResult);
//    if (bResult == false)
//    {
//        return false;
//    }
//    int companyId = 1;
//    companyId = dao->SelectCampanyId(&bResult).toInt();
    bResult = AnalysisOneSample(paperId, test_id, sampleId);
    if (bResult == false)
    {
        return false;
    }
    return true;
}

bool PictureAnalysis::AnalysisOneSample(int paperId, QString testId, QString sampleId)
{
    Error resultCode = Error::NoError;
    TestPaperStrt paper;
    paper.testId = testId;
    paper.sampleId = sampleId;
    if(!TestPaperDao::instance()->getModel(paperId, paper.paperParam)) return false;
    TestPaperModel& paperParam = paper.paperParam;
    paper.itemParamVect = ItemDao::instance()->selectItems(paperId);

//    if (GetTestPaperParameter(testPaperParameterStruct, paper_id, company_id) == false) return false;
//    testPaperParameterStruct.sampleId = sampleId;
//    testPaperParameterStruct.Id=testId;
    // 根据不同的类型选择不同的方式
//    dLog("company_id = " + std::to_string(company_id) + "type = " + std::to_string(testPaperParameterStruct.set_calculate_point));
//    qDebug() << "company_id = " << company_id << "type = " << testPaperParameterStruct.set_calculate_point;
    if(paperParam.getPaperType() == TestPaperModel::PAPER_TYPE_CONTINUOUS) // 连续膜条处理
    {
//        int code = CalcImageItemContinuous(testPaperParameterStruct, testId);
//        resultCode = code;
    }else
    {
        resultCode = CalcImageItemSegmentation(paper);
        qDebug()<<"resultCode="<<static_cast<int>(resultCode);
//        resultCode = code;
    }
/*
    if(company_id == 6)
    {// 艾康单独处理
        int code = CalcImageItemWz(testPaperParameterStruct, testId);
        resultCode = code;
    }else
    {// 统一处理
        if(testPaperParameterStruct.paperType == 0)
        {// 连续膜条
            int code = CalcImageItemContinuous(testPaperParameterStruct, testId);
            resultCode = code;
        }else if(testPaperParameterStruct.paperType == 1)
        {// 分段膜条
            int code = CalcImageItemSegmentation(testPaperParameterStruct, testId);
            resultCode = code;
        }else
        {
            return false;
        }
    }
    double cutoffGray = testPaperParameterStruct.isCutOff == 1 ? testPaperParameterStruct.dItemGrayValue[1] : testPaperParameterStruct.cutOffValue;
    QMap<int, StandardCurveParameter> curveMap;
    standard_curve curve_obj(nullptr);
    for(int i = 0; i < testPaperParameterStruct.nTotalNumber+2; i++)
    {
        StandardCurveParameter curveParameter;
        int curveId = testPaperParameterStruct.dItemCurveId[i];
        if(!curveMap.contains(curveId))
        {
            curve_obj.GetStandardCurveParameter(curveParameter, curveId);
            curveMap.insert(curveId, curveParameter);
        }else
        {
            curveParameter = curveMap.take(curveId);
        }
        if(i == 1)
        {
            testPaperParameterStruct.dItemGrayValue[i] = cutoffGray;
            testPaperParameterStruct.dItemGrayRatio[i] = 1;
            testPaperParameterStruct.dItemErrorCode[i] = 0;
        }else
        {
            if(testPaperParameterStruct.isCutOff == 0)
            {
                double background_value = testPaperParameterStruct.paperBackgroundValue;
                testPaperParameterStruct.dItemGrayValue[i] = 1.0 * testPaperParameterStruct.dItemGrayValue[i] / testPaperParameterStruct.dBackgroundGrayValue[i] * background_value;
            }
            double a_item = 0, b_cut = 0, c1 = 0;
            a_item = qLn((testPaperParameterStruct.dItemGrayValue[i] < 1 ? 1 : testPaperParameterStruct.dItemGrayValue[i]) / 255);
            b_cut = qLn(cutoffGray < 1 ? 1 : cutoffGray  / 255);
            c1 =  a_item/ b_cut;
//            qDebug()<<testPaperParameterStruct.strTestItemName[i] << c1;
            if(std::isnan(c1) || std::isinf(c1))
            {
                testPaperParameterStruct.dItemGrayRatio[i] = 0;
            }else
            {
                testPaperParameterStruct.dItemGrayRatio[i] = curve_obj.Calc(curveParameter, c1)+testPaperParameterStruct.dItemResultOffset[i];
            }
//            qDebug()<<"calc"<<testPaperParameterStruct.strTestItemName[i] << testPaperParameterStruct.dItemGrayRatio[i];
        }
    }

//    qDebug()<<"resultCode" << resultCode;
    UpdateSampleAnalysisState(resultCode);
//    for(int i = 0; i < 32; i++)
//    {
//        qDebug()<<"mysql" << testPaperParameterStruct.dItemPosition[i] << testPaperParameterStruct.dItemGrayValue[i] << testPaperParameterStruct.dItemGrayRatio[i];
//    }
    TestPaperParameter testPaperResult;
    //根据灰度值计算结果写到数据库
    if (resultCode == 88 || resultCode == 81 || resultCode == 82||resultCode == 83)
    {
        testPaperResult.solutionName = solution_name;
        if (SaveTestData(testPaperParameterStruct) == false)
            return false;
    }
    */
    return true;
}

bool PictureAnalysis::SaveTestData(TestPaperStrt testPaperResult)
{
//    auto dao = AnalysisDao::instance();
//    bool bResult;
//    QString strSampleID;
//    QString strTestPaper_ID;
//    QString strItemName;
//    QString strPosition;
//    QString strGrayValue;
//    QString strRatioToCut;
//    QString strDiagnosis;
//    QString strTestDateTime;
//    QString strSolutionName;
//    QString paper_id;
//    QString articleNo;
//    QString manageName;
//    QDateTime nowTime = QDateTime::currentDateTime();
//    QString id;
//    int error_code;

//    strTestDateTime = nowTime.toString("yyyy-MM-dd hh:mm:ss");
//    for (int i = 0; i < (testPaperResult.nTotalNumber + 2); i++)
//    {
//        strSolutionName = testPaperResult.solutionName;
//        paper_id = QString::number(testPaperResult.paperId);
//        articleNo = testPaperResult.articleNo;
//        manageName = testPaperResult.manageName;
//        strSampleID = testPaperResult.sampleId;
//        strTestPaper_ID = QString::number(m_nTestPaperID);
//        strItemName = testPaperResult.strTestItemName[i];
//        strPosition = QString::number(testPaperResult.dItemPosition[i]);
//        if(testPaperResult.dItemGrayValue[i] < 0.01)
//        {
//            strGrayValue = QString::number(0);
//        }else
//        {
//            strGrayValue = QString::number(testPaperResult.dItemGrayValue[i], 'f', 2);
//        }
//        if(testPaperResult.dItemGrayRatio[i] < 0.01)
//        {
//            strRatioToCut = QString::number(0);
//        }
//        else
//        {
//            strRatioToCut = QString::number(testPaperResult.dItemGrayRatio[i], 'f', 2);
//        }
//        strDiagnosis = CaculateResultText(testPaperResult.dItemGrayRatio[i], strItemName, paper_id.toInt(), testPaperResult.dItemErrorCode[i]);
//        error_code = testPaperResult.dItemErrorCode[i];
//        id = testPaperResult.Id;
//        bResult = dao->InsertTestData(
//                    strSolutionName,
//                    id,
//                    paper_id,
//                    articleNo,
//                    manageName,
//                    m_test_project_name,
//                    strSampleID,
//                    strTestPaper_ID,
//                    strItemName,
//                    strPosition,
//                    strGrayValue,
//                    strRatioToCut,
//                    strDiagnosis,
//                    strTestDateTime, strSolutionName,"", error_code);
//        if (bResult == false)
//        {
//            return false;
//        }
//    }
    return true;
}

bool PictureAnalysis::UpdateSampleAnalysisState(int nAnalysisState)
{
//    auto dao = AnalysisDao::instance();
//    bool bResult;
//    QString strSampleID;
//    QString strTestPaper_ID;
//    QString strTestDateTime;
//    QString strAnalysisState = QString::number(nAnalysisState);
//    QDateTime nowTime = QDateTime::currentDateTime();
//    strTestDateTime = nowTime.toString("yyyy-MM-dd hh:mm:ss");
//    strSampleID = m_nSampleID;
//    strTestPaper_ID = QString::number(m_nTestPaperID);
//    bResult = dao->UpdateSampleAnalysisState(
//                m_test_project_name,
//                strSampleID,
//                strTestPaper_ID,
//                strAnalysisState,
//                strTestDateTime);
//    if (bResult == false)
//    {
//        return false;
//    }
    return true;

}

/**
 * @brief 分段膜条处理
 * @param testPaperParameterStruct
 * @param testId
 * @return
 */
PictureAnalysis::Error PictureAnalysis::CalcImageItemSegmentation(TestPaperStrt &paper)
{
    Error err = Error::NoError;
    QString pictureRootPath;
    if(!SystemSetDao::instance()->getPicturePathRoot(pictureRootPath))
    {
        return Error::PictureNotFound;
    }
    // 整张图片的处理
    err = GetTestPaperImageSegmentation(pictureRootPath, paper);
    if(err != Error::NoError)
    {
//        dLog("error code = " + QString::number(static_cast<int>(err)));
//        qDebug()<<"error code = " << static_cast<int>(err);
        return err;
    }
    dLog("error code = 0");
    return Error::NoError;
}

/**
 * @brief 分段膜条旋转操作并剪切
 * @return 错误码
 * 0 成功
 * 1:图片识别失败
 */
PictureAnalysis::Error PictureAnalysis::TestPaperSegmentationRotateCut(cv::Mat& srcMat, TestPaperStrt &paper, cv::OutputArray dstMat, cv::OutputArray dst_thresh_mat)
{

    // 图片保存路径
    QString path;
    if(!SystemSetDao::instance()->getPicturePathRoot(path))
    {
        return Error::PictureNotFound;
    }
    TestPaperModel& paperParam = paper.paperParam;
    double mm_to_pixel= paperParam.getPaperMmToPixel();
    // 段宽度
    double segmentMinWidth = paperParam.getTestBlockWidth() * mm_to_pixel;
    // 膜条高度
    double totalHeigth = paperParam.getPaperHeight() * mm_to_pixel;
    // 图片二值化阈值
    int thresh = paperParam.getPaperBinarizationThreshold();
    // 将反光区域处理
    cv::Mat lightMask;
    cv::threshold(srcMat, lightMask, 250, 255, cv::THRESH_BINARY);
     // 消除噪声点
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5));
    cv::morphologyEx(lightMask, lightMask, cv::MORPH_CLOSE, kernel);
    // 创建黑色替代区域
    cv::Mat black_area = cv::Mat::zeros(srcMat.size(), srcMat.type());
    // 融合图像（仅替换过曝区域）
    srcMat.copyTo(black_area, ~lightMask);  // 反转掩膜
    srcMat = black_area.clone();
    // 保存的分析图片
    QString lightPath = path +"\\" + "analysised" + "\\" + paper.sampleId + "-nolight.png";
    cv::imwrite(lightPath.toStdString(), srcMat);

    cv::Mat threshMat;
    cv::threshold(srcMat, threshMat, thresh, 255, THRESH_BINARY);
    // 保存二值化后的图像
        QString threshPath = path;
        // 保存二值化后的图像
        threshPath = threshPath + +"/" + "analysised" + "/" + paper.sampleId + "-thresh.png";
        cv::imwrite(threshPath.toStdString(), threshMat);

    Mat erodedMat;
    {
        // 腐蚀
        Mat eroded_kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        erode(threshMat, erodedMat, eroded_kernel);
        //保存腐蚀后的图片
            QString erodedPath = path;
            erodedPath = erodedPath + +"/" + "analysised" + "/" + paper.sampleId + "-eroded.png";
            cv::imwrite(erodedPath.toStdString(), erodedMat);

    }
    cv::Mat rotedMat;
    cv::Mat rotMat;
    cv::Rect bbox;
    {
        // 旋转
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(erodedMat, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        if(contours.empty())
        {
            return Error::ContourNotFound;
        }
        // 将符合条件的轮廓合并为最大轮廓,这里的合并是为了更好的旋转
        vector<Point> all_points;
        for (auto& contour : contours)
        {
            cv::Rect rect = cv::boundingRect(contour);
            if (rect.width < segmentMinWidth*0.15 || rect.height < totalHeigth/3*2)
            {
                continue;
            }
            all_points.insert(all_points.end(), contour.begin(), contour.end());
        }
        if(all_points.empty())
        {
            return Error::ContourNotFound;
        }
        vector<Point> maxContour;
        convexHull(all_points, maxContour);
        cv::Rect maxRect = cv::boundingRect(maxContour);
        cv::Mat maxRectMat = erodedMat(maxRect);
        //保存膨胀后圈出的轮廓
            QString maxRectPath = path;
            maxRectPath = maxRectPath + +"/" + "analysised" + "/" + paper.sampleId + "-maxRect.png";
            cv::imwrite(maxRectPath.toStdString(), maxRectMat);

        // 计算最小外接旋转矩形
        cv::RotatedRect rotatedRect = cv::minAreaRect(maxContour);
        float angle = rotatedRect.angle;
        // 角度修正逻辑（OpenCV角度定义特殊）
        if (rotatedRect.size.width < rotatedRect.size.height) {
            angle += 90.0f;
        }
        cv::Point2f center(threshMat.cols/2.0f, threshMat.rows/2.0f);
        rotMat = cv::getRotationMatrix2D(center, static_cast<double>(angle), 1.0);
        // 旋转图像并计算新画布尺寸
        bbox = cv::RotatedRect(center, threshMat.size(), angle).boundingRect();
        rotMat.at<double>(0,2) += (bbox.width/2.0 - static_cast<double>(center.x));
        rotMat.at<double>(1,2) += (bbox.height/2.0 - static_cast<double>(center.y));
        // 旋转形成新图像
        cv::warpAffine(threshMat, rotedMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘
    }
    cv::Rect maxRect;
    cv::Mat maxRectMat;
    {
        // 识别最大轮廓
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(rotedMat, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        if(contours.empty())
        {
            return Error::ContourNotFound;
        }
        // 将符合条件的轮廓合并为最大轮廓,这里的合并是为了更好的旋转
        vector<Point> all_points;
        for (auto& contour : contours)
        {
            cv::Rect rect = cv::boundingRect(contour);
            if (rect.width < segmentMinWidth*0.15 || rect.height < totalHeigth/3*2)
            {
                continue;
            }
            all_points.insert(all_points.end(), contour.begin(), contour.end());
        }
        if(all_points.empty())
        {
            return Error::ContourNotFound;
        }
        vector<Point> maxContour;
        convexHull(all_points, maxContour);
        maxRect = cv::boundingRect(maxContour);
        maxRectMat = rotedMat(maxRect);
        //保存膨胀后圈出的轮廓
            QString maxRectPath = path;
            maxRectPath = maxRectPath + +"/" + "analysised" + "/" + paper.sampleId + "-maxRect1.png";
            cv::imwrite(maxRectPath.toStdString(), maxRectMat);

    }

    // 灰度图像也做相同旋转，与二值化的图像保持一致
    cv::Mat grayRotMat;
    cv::warpAffine(srcMat, grayRotMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘

    // 开始去噪声，仅对上下边界，目的是精细化边界位置
    int top = -1, bottom = -1;
    cv::Mat maxGrayMat = grayRotMat(maxRect);
    //  保存灰度图片
    QString maxGrayMatPath = path;
    maxGrayMatPath = maxGrayMatPath + +"/" + "analysised" + "/" + paper.sampleId + "-maxGrayMat.png";
    cv::imwrite(maxGrayMatPath.toStdString(), maxGrayMat);

    double edgeThresh = cv::mean(maxGrayMat)[0];
    qDebug()<<"edgeThresh = "<<edgeThresh;
    // 描边去噪
    //按照3个像素的宽度，精细上端位置
    for(int i = 0; i < maxGrayMat.rows-3;i++)
    {
        double avg = 0;
        cv::Rect roi(0, i, maxGrayMat.cols, 3);
        cv::Mat tempMat = maxGrayMat(roi);
        avg = cv::mean(tempMat)[0];
        if(avg >= edgeThresh)
        {
            top = i;
            break;
        }
    }
    //按照3个像素的宽度，精细底端位置
    for(int i = 0; i < maxGrayMat.rows - 3;i++)
    {
        double avg = 0;
        cv::Rect roi(0,  maxGrayMat.rows - i - 3, maxGrayMat.cols,  3);
        cv::Mat tempMat = maxGrayMat(roi);
        avg = cv::mean(tempMat)[0];
        if(avg >= edgeThresh)
        {
            bottom = maxGrayMat.rows - i;
            break;
        }
    }
    qDebug()<<"top = "<<top << "bottom = " << bottom << "totalHeight = "<<totalHeigth;
    if(top < 0 || bottom < 0 || bottom - top < totalHeigth * 0.5)
    {
        return Error::ContourNotFound;
    }
    qDebug() << edgeThresh << top << bottom;

    {
        // 剪裁膜条并保存
        double yPercent = 1;
        double yCenter = maxRect.y + top + (bottom - top)/2;
        double cutHeight = totalHeigth * yPercent;
        cv::Rect lastEdge(maxRect.x, static_cast<int>(yCenter - cutHeight / 2), maxRect.width, static_cast<int>(cutHeight));
        cv::Mat croppedMat = grayRotMat(lastEdge);
        QString croppedPath = path;
        //剪裁后的图片保存
        croppedPath = croppedPath +"\\" + "analysised" + "\\" + paper.sampleId + ".png";
        cv::imwrite(croppedPath.toStdString().data(), croppedMat);
    }
    {
        // 裁剪并保存
        double yPercent = paperParam.getAnalysisPercentOfHeightDouble();
        double yCenter = maxRect.y + top + (bottom - top)/2;
        double cutHeight = totalHeigth * yPercent;
        cv::Rect lastEdge(maxRect.x, static_cast<int>(yCenter - cutHeight / 2), maxRect.width, static_cast<int>(cutHeight));
        cv::Mat croppedMat = grayRotMat(lastEdge);
//        std::string croppedPath = path.toStdString();
//        //剪裁后的图片保存
//        croppedPath = croppedPath +"\\" + "analysised" + "\\" + testPaperParameterStruct.sampleId.toStdString().data() + ".png";
//        cv::imwrite(croppedPath, croppedMat);

        // 将处理后的对象传递出去
        croppedMat.copyTo(dstMat);
        //
        cv::Mat croppedMat1 = rotedMat(lastEdge);
        QString croppedPath1 = path;
        //剪裁后的图片保存
        croppedPath1 = croppedPath1 +"\\" + "analysised" + "\\" + paper.sampleId + "-1.png";
        cv::imwrite(croppedPath1.toStdString(), croppedMat1);

        croppedMat1.copyTo(dst_thresh_mat);
    }
    return Error::NoError;
}

/**
 * @brief 片段解析,目的解析出膜条段
 * @param srcMat 需要解析的图片
 * @param testPaperParameterStruct 参数
 * @param segCenter 解析后返回的数据 <0>表示段中心 <1>表示段宽度
 * @return 错误码
 * 0:成功
 * 1:解析失败
 */
PictureAnalysis::Error PictureAnalysis::TestPaperSegmentationParse(cv::Mat& srcMat,cv::Mat& threshMat, TestPaperStrt &paper, QVector<std::tuple<int,int>>& segCenter)
{
    TestPaperModel& paperParam = paper.paperParam;
    QVector<ItemModel>& itemVect = paper.itemParamVect;
    if(itemVect.size() == 0)
    {
        return Error::ItemConfigError;
    }
    // 图片保存路径
    QString path;
    if(!SystemSetDao::instance()->getPicturePathRoot(path))
    {
        return Error::PictureNotFound;
    }
    double mmPixel= paperParam.getPaperMmToPixel();
    double segmentMinWidth = paperParam.getTestBlockWidth() * mmPixel;
    int headWidth = static_cast<int>(paperParam.getIgnoreHeadLenght() * mmPixel);
    double lineWidth = paperParam.getItemLineWidth() * mmPixel;
    bool ignoreHead = paperParam.getIgnoreHeadLenght() > 0;
    // 获取分段总数
    int segCnt = ignoreHead ? paperParam.getTotalNumber() - 1 : paperParam.getTotalNumber();
    if(srcMat.cols < headWidth)
    {
        qDebug()<<"headWidth"<<srcMat.cols<<headWidth;
        return Error::ConfigError;
    }
//    // 将反光区域处理
//    cv::Mat threshMask;
//    cv::threshold(srcMat, threshMask, 250, 255, cv::THRESH_BINARY);
//     // 消除噪声点
//    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5));
//    cv::morphologyEx(threshMask, threshMask, cv::MORPH_CLOSE, kernel);
//    // 创建黑色替代区域
//    cv::Mat black_area = cv::Mat::zeros(srcMat.size(), srcMat.type());
//    // 融合图像（仅替换过曝区域）
//    srcMat.copyTo(black_area, ~threshMask);  // 反转掩膜
//    srcMat = black_area.clone();
    /* 保存的分析图片
    std::string lightPath = path.toStdString() +"\\" + "analysised" + "\\" + testPaperParameterStruct.sampleId.toStdString().data() + "-nolight.png";
    cv::imwrite(lightPath, srcMat);
    */
    // 处理头
    cv::Mat targetRegion = threshMat.colRange(0, headWidth);
    // 将头设置为黑色
    targetRegion.setTo(cv::Scalar(0));
    //
    QString noHeadPath = path;
    noHeadPath = noHeadPath + +"/" + "analysised" + "/" + paper.sampleId + "-nohead.png";
    cv::imwrite(noHeadPath.toStdString(), threshMat);


    // 腐蚀操作
    cv::Mat eroded_kernel = getStructuringElement(MORPH_RECT, Size(1, threshMat.rows));
    cv::Mat erodedMat;
    erode(threshMat, erodedMat, eroded_kernel);
    //保存腐蚀后的图片
        QString erodedPath = path;
        erodedPath = erodedPath + +"/" + "analysised" + "/" + paper.sampleId + "-eroded1.png";
        cv::imwrite(erodedPath.toStdString(), erodedMat);

    {
        // 查找轮廓
        std::vector<std::vector<Point>> contours;
        std::vector<std::vector<Point>> last_contours;
        findContours(erodedMat, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        sort(contours.begin(), contours.end(), [](auto& a, auto& b) { return boundingRect(a).x < boundingRect(b).x; });
        if(contours.empty())
        {
            return Error::ContourNotFound;
        }

        // 子项目描边
        for(auto& contour : contours)
        {
            cv::Rect rect = cv::boundingRect(contour);
            cv::Mat mat = erodedMat(rect);
            if(rect.height < erodedMat.rows * 0.5 || rect.width < lineWidth * 0.5)
            {
                qDebug()<<"contours"<<rect.height<<erodedMat.rows<<rect.width<<lineWidth;
                // 用黑色填充
                mat.setTo(cv::Scalar(0,0,0));
            }
            else
            {
                // 总平均值作为阈值
                double thresh = 200;
                int idx = 0;
                int state = 0;
                // 左右描边
                //按照3个像素的宽度
                for(int i = 0; i < mat.cols;i++)
                {
                    double avg = 0;
                    cv::Rect roi(i, 0, 1, mat.rows);
                    avg = cv::mean(mat(roi))[0];
                    if(state == 0)
                    {// 在黑色区域
                        if(avg > thresh)
                        {// 检测到转白，全部设为黑色
                            cv::Rect roi(idx, 0, i - idx + 1, mat.rows);
                            mat(roi).setTo(cv::Scalar(0,0,0));
                            state = 1;
                            idx = i;
                        }
                    }else
                    {// 在白色区域
                        if(avg < thresh)
                        {// 检测到黑色
                            if(i - idx < lineWidth*0.5)
                            {// 白色区域超过一定宽度
                                cv::Rect roi(idx, 0, i - idx + 1, mat.rows);
                                mat(roi).setTo(cv::Scalar(0,0,0));
                            }
                            state = 0;
                            idx = i;
                        }
                    }
                    if(i == mat.cols - 1 && state == 0)
                    {
                        cv::Rect roi(idx, 0, i - idx + 1, mat.rows);
                        mat(roi).setTo(cv::Scalar(0,0,0));
                    }
                }
            }
        }
//        // 创建掩膜并填充目标轮廓区域
//        Mat mask = Mat::zeros(erodedMat.size(), CV_8UC1);
//        double areaThresh = mm_to_pixel * srcMat.rows * lineWidth * 0.8;
//        for(uint i = 0; i < contours.size(); i++)
//        {
//            if(cv::contourArea(contours[i]) < areaThresh)
//            {
//                drawContours(mask, contours, static_cast<int>(i), Scalar(255), FILLED);
//            }
//        }
//        erodedMat.setTo(Scalar(0), mask);
      // 保存腐蚀后的图片
        QString erodedPath = path;
        erodedPath = erodedPath + +"/" + "analysised" + "/" + paper.sampleId + "-eroded2.png";
        cv::imwrite(erodedPath.toStdString(), erodedMat);

    }

    // 膨胀
    int inflatePixel = static_cast<int>(mmPixel)+3;
    qDebug()<<"inflatePixel"<<inflatePixel;
    cv::Mat inflateMat;
    cv::Mat dilate_kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(inflatePixel,threshMat.rows/3));
    cv::dilate(erodedMat, inflateMat, dilate_kernel);

    //保存膨胀后的图片
        QString inflatePath = path;
        inflatePath = inflatePath + +"/" + "analysised" + "/" + paper.sampleId + "-inflate1.png";
        cv::imwrite(inflatePath.toStdString(), inflateMat);

    // 轮廓识别 分段 排序
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(inflateMat, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    sort(contours.begin(), contours.end(), [](auto& a, auto& b) { return boundingRect(a).x < boundingRect(b).x; });
    if(contours.empty())
    {
        return Error::ContourNotFound;
    }
    vector<cv::Rect> segRects;
    bool need_merge = false;
    cv::Rect wait_merge_rect;
    for (auto& contour : contours)
    {
        cv::Rect rect = cv::boundingRect(contour);
        qDebug()<<"rect.width = " << rect.width << "segmengMinWidth=" << segmentMinWidth << "height="<<rect.height << "rows="<<srcMat.rows;
        if (rect.width < segmentMinWidth * 0.3 || rect.height < srcMat.rows * 0.3)
        {
            continue;
        }
        if (rect.width < segmentMinWidth * 0.8 || rect.height < srcMat.rows * 0.8)
        {
            if(need_merge)
            {
                rect.width = rect.x + rect.width - wait_merge_rect.x;
                rect.x = wait_merge_rect.x;
                inflateMat(rect).setTo(cv::Scalar(255,255,255));
            }else
            {
                wait_merge_rect = rect;
                need_merge = true;
                continue;
            }
        }
        need_merge = false;
        segRects.push_back(rect);
    }
    //保存膨胀后的图片
    QString inflatePath1 = path;
    inflatePath1 = inflatePath1 + +"/" + "analysised" + "/" + paper.sampleId + "-inflate2.png";
    cv::imwrite(inflatePath1.toStdString(), inflateMat);

    dLog("segRects.size() = " + std::to_string(segRects.size()) + "segCnt=" + std::to_string(segCnt));
    if(static_cast<int>(segRects.size()) != segCnt)
    {
        return Error::DetectSegmentCntError;
    }
    // 子项目描边
    for(auto& rect : segRects)
    {
        cv::Mat mat = srcMat(rect);
        // 总平均值作为阈值
        double thresh = cv::mean(mat)[0];
        double start = -1, end = -1;
        // 左右描边
        //按照3个像素的宽度，精细底端位置
        for(int i = 0; i < mat.cols / 2 - 3;i++)
        {
            double avg = 0;
            cv::Rect roi(i, 0, 3, mat.rows);
            cv::Mat tempMat = mat(roi);
            avg = cv::mean(tempMat)[0];
            if(avg >= thresh)
            {
                start = i;
                break;
            }
        }
        for(int i = 0; i < mat.cols / 2 - 3;i++)
        {
            double avg = 0;
            cv::Rect roi(mat.cols - i - 3,  0, 3, mat.rows);
            cv::Mat tempMat = mat(roi);
            avg = cv::mean(tempMat)[0];
            if(avg >= thresh)
            {
                end = mat.cols - i;
                break;
            }
        }
        if(start < 0 || end < 0)
        {
            return Error::DetectSegmentCntError;
        }
        segCenter.push_back(std::make_tuple(rect.x + static_cast<int>((start+end)/2), end - start));
    }
    return Error::NoError;
}

/**
 * @brief 解析分段膜条并计算
 * @param filePath 图片输入路径
 * @param testPaperParameterStruct 参数
 * @return 错误码
 * 0:成功
 * 1:参数设置失败
 * 2:图片解析失败
 */
PictureAnalysis::Error PictureAnalysis::GetTestPaperImageSegmentation(const QString& rootPath, TestPaperStrt& paper)
{
    TestPaperModel& paperParam = paper.paperParam;
    QString picturePath = rootPath + "\\" + "original" + "\\" + paper.testId + "" + ".png";
    double mmPixel= paperParam.getPaperMmToPixel();
    double yPercent = paperParam.getAnalysisPercentOfHeightDouble();
    qDebug()<<"yPercent"<<yPercent;

    if(yPercent > 1 || yPercent < 0.4)
    {
        return Error::ItemAnalysisHeightError;
    }
    // 读取图片并转换为灰度值
    cv::Mat srcMat = cv::imread(picturePath.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
    if(srcMat.empty())
    {
        return Error::PictureToGrayError;
    }

    cv::Mat grayMat;
    // 根据配置确定图片是否需要旋转
    if(SrcImageNeedRotate180(paperParam))
    {
        cv::rotate(srcMat, grayMat, cv::ROTATE_180);
    }
    else
    {
        grayMat = srcMat.clone();
    }
    // 剪切后的图片
    cv::Mat cutMat, cutThreshMat;
    Error err = Error::NoError;
    err = TestPaperSegmentationRotateCut(grayMat, paper, cutMat, cutThreshMat);
    if(err != Error::NoError)
    {
        return err;
    }
    // 图片解析
    QVector<std::tuple<int, int>> segCenter;
    QVector<ItemModel>& itemVect = paper.itemParamVect;
    if(itemVect.size() == 0)
    {
        return Error::ItemConfigError;
    }
    // 将检测带按照段分组
    QMap<int, QVector<ItemModel>> itemsBySegment = {};
    for (const auto& item : itemVect)
    {
        itemsBySegment[item.getSegmentIndex()].append(item);
    }
    err = TestPaperSegmentationParse(cutMat, cutThreshMat, paper, segCenter);
    if(err != Error::NoError)
    {
        return err;
    }
    // 检测线数量
    int lineCnt = itemVect.size();
    // 检测线宽度
    int lineWidth = static_cast<int>(paperParam.getItemLineWidth() * mmPixel);
    // 结果<0> 线中心 <1>线宽度 <2>线平均灰度值 <3>线周围的本底值
    QVector<std::tuple<int,int, double,double>> grayArray(lineCnt, {0,0,0,0});
    // 另外存一个图片,用来可视化
    cv::Mat drawMat = cutMat.clone();
    // 计算各个项目的灰度值
    int itemIdx = 0;
    int blackDetectThreshold = paperParam.getIsBlackPointDetect() ? static_cast<int>(paperParam.getBlackPointDetectThreshold()) : 0;
    auto dao = AnalysisDao::instance();
    bool bResult = false;
    Error itemError = Error::NoError;
    bool ignoreHead = paperParam.getIgnoreHeadLenght() > 0;
    for (int segmentIndex : itemsBySegment.keys())
    {
        const QVector<ItemModel>& itemVectOnSegment = itemsBySegment[segmentIndex];
        int itemCntOnSegment = itemVectOnSegment.size();
        if(itemCntOnSegment == 0) continue;
        int segNo =  ignoreHead ? segmentIndex - 2 : segmentIndex - 1;
        if(segNo < 0) continue;
        int center = std::get<0>(segCenter[segNo]);
        int width = static_cast<int>(std::get<1>(segCenter[segNo])*0.8);
        int itemScanWidth = static_cast<int>(width / itemCntOnSegment);

        for(const ItemModel& item:itemVectOnSegment)
        {
            if(item.getPositionNo() < 1) continue;
            int positionNo = item.getPositionNo() - 1;
            // 项目范围线的起始点
            int limitStart = static_cast<int>(center - width/2 + (itemCntOnSegment - positionNo - 1) * itemScanWidth);
            int limitWidth = itemScanWidth;
            cv::Rect calcRect(limitStart, 0,  limitWidth, cutMat.rows);
            cv::Mat calMat = cutMat(calcRect);
            TestPaperItemResult itemResult; // 结果计算
            // 处理计算时的错误码，并不中断其他项目的计算
            Error calcError = GetTestOneItemCalcIndexWz(calMat, grayArray[itemIdx], lineWidth, blackDetectThreshold);
            // 功能线判定
            if(item.getItemType() == 0 && std::get<2>(grayArray[itemIdx]) > paperParam.getFuncGrayThreshold())
            {
                err = Error::FuncLineError;
                break;
            }
            if(item.getItemType() == 1 && std::get<2>(grayArray[itemIdx]) > paperParam.getCutOffThreshold())
            {
                err = Error::CutOffLineError;
                break;
            }
            if(calcError != Error::NoError)
            {
                itemError = calcError;
            }
            itemResult.errorCode = static_cast<int>(calcError);

            std::get<0>(grayArray[itemIdx]) += limitStart;
            qDebug() << "result " << std::get<0>(grayArray[itemIdx]) << std::get<1>(grayArray[itemIdx]) << std::get<2>(grayArray[itemIdx])<<std::get<3>(grayArray[itemIdx]) << std::get<3>(grayArray[itemIdx])-std::get<2>(grayArray[itemIdx]);
            double finaleGrayValue = std::get<2>(grayArray[itemIdx]);
            finaleGrayValue = finaleGrayValue < 0 ? 0 : finaleGrayValue;
            // 保存解析后的灰度值
            itemResult.grayValue = finaleGrayValue;
            itemResult.backgroundGrayValue = std::get<3>(grayArray[itemIdx]);
            // 可视化项目线
            cv::Rect roi(std::get<0>(grayArray[itemIdx]) - std::get<1>(grayArray[itemIdx])/2, 0, std::get<1>(grayArray[itemIdx]), cutMat.rows);
            cv::rectangle(drawMat, roi, cv::Scalar(0,0,0), 1);
            // 画范围线
            cv::Rect roi1(limitStart, 0, limitWidth, 2);
            cv::rectangle(drawMat, roi1, cv::Scalar(0,0,0), 2);
            itemResult.positionStart = limitStart;
            bResult = dao->Insert_tresult_left_right_pixp(paper.testId, static_cast<int>(itemIdx), limitStart, limitStart+limitWidth, item.getItemName(), 0, 2 );
        }
    }
    // 保存最终的分析图片
    QString path = rootPath;
    path = path +"\\" + "analysised" + "\\" + paper.sampleId + "-last.png";
    cv::imwrite(path.toStdString(), drawMat);
    return err == Error::NoError ? itemError : err;
}

/**
 * @brief PictureAnalysis::CalcImageItemContinuous
 * 连续膜条的判读方式
 * @param testPaperParameterStruct
 * @param testId
 * @return
 */
int PictureAnalysis::CalcImageItemContinuous(TestPaperStrt &paper, QString testId)
{
//    auto dao = AnalysisDao::instance();
//    bool bResult = true;
//    // 获取要分析的膜条路径
//    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
//    double mm_to_pixel= testPaperParameterStruct.paperMmToPixel;
//    QString strPathFileName_last = piture_root_str + "\\" + "original" + "\\" + testId + "" + ".png";

//    cv::Mat imgMat;
//    // 整张图片的处理
//    int code = GetTestPaperImageContinuous(strPathFileName_last,testPaperParameterStruct,imgMat);
//    if(code != 0)
//    {
//        qDebug() << "file wzn " << code;
//        return 81;
//    }

//    //所有的线 包括质控 和 cutoff
//    QList<int> positionList;
//    for(int i=0;i<testPaperParameterStruct.nTestItemNumber+2;i++){
//        positionList.append(static_cast<int>((testPaperParameterStruct.dItemPosition[i]) * mm_to_pixel));
//    }

//    // 线宽
//    int lineWidth = static_cast<int>(testPaperParameterStruct.itemLineWidth * mm_to_pixel);
//    // 检测范围
//    int lineLimit = static_cast<int>(testPaperParameterStruct.itemFindWidth * mm_to_pixel);
//    code = GetTestPaperImageCalcIndexWz(imgMat,testPaperParameterStruct, positionList, lineLimit, lineWidth);
//    if(code != 0)
//    {
//        qDebug() << "file1 wzn " << code;
//        return (code == 3 || code == 4) ? 83 : 81;
//    }
    //*d-c  作为灰度值存到数据库  计算浓度值
    return 88;
}

bool PictureAnalysis::SrcImageNeedRotate180(TestPaperModel& paper)
{
    return paper.getPaperShowAngle() == 1;
}

/**
 * @brief 连续膜条的判读方式 目标将膜条图片精准剪切出来
 * @param inputPath 图片输入路径
 * @param outputPath 图片输出路径
 * @param thresh 图片二值化阈值
 * @return 错误码
 * 1:图片转换失败
 * 2:未找到轮廓
 */
int PictureAnalysis::GetTestPaperImageContinuous(QString filePath, TestPaperStrt &testPaperParameterStruct, cv::OutputArray dst)
{
//    bool bResult = false;
//    auto dao = AnalysisDao::instance();
//    double mmPixel= testPaperParameterStruct.paperMmToPixel;
//    // 查询背景阈值
//    QString threshString = dao->SelectThresholdValue(&bResult,testPaperParameterStruct.paperId,testPaperParameterStruct.companyId);
//    int thresh = threshString.toInt();
//    double yPercent = testPaperParameterStruct.analysisPercentOfHeight / 100;
//    double totalHeight = testPaperParameterStruct.paperHeight;
//    double lineWidth = testPaperParameterStruct.itemLineWidth;
//    if(yPercent > 1 || yPercent < 0.4)
//    {
//        return 1;
//    }
//    // 读取图片并转换为灰度值
//    cv::Mat srcMat = cv::imread(filePath.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
//    if(srcMat.empty())
//    {
//        return 2;
//    }
//    cv::Mat grayMat;
//    // 根据配置确定图片是否需要旋转
//    if(SrcImageNeedRotate180(testPaperParameterStruct))
//    {
//        cv::rotate(srcMat, grayMat, cv::ROTATE_180);
//    }
//    else
//    {
//        grayMat = srcMat.clone();
//    }

//    // 图片二值化阈值 = 功能线阈值
//    cv::Mat threshMat;
//    cv::threshold(grayMat, threshMat, thresh, 255, THRESH_BINARY);
//    // 保存二值化后的图像
//    /*剪裁后的图片保存
//        std::string threshPath = dao->SelectTestPicturesRootPath(&bResult).toStdString();
//        // 保存二值化后的图像
//        threshPath = threshPath + +"/" + "analysised" + "/" + testPaperParameterStruct.sampleId.toStdString().data() + "-thresh.png";
//        cv::imwrite(threshPath, threshMat);
//    */

//    Mat erodedMat;
//    {
//        // 腐蚀操作,过滤噪点
//        Mat eroded_kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
//        erode(threshMat, erodedMat, eroded_kernel);
//        /*保存腐蚀后的图片
//            std::string erodedPath = dao->SelectTestPicturesRootPath(&bResult).toStdString();
//            erodedPath = erodedPath + +"/" + "analysised" + "/" + testPaperParameterStruct.sampleId.toStdString().data() + "-eroded.png";
//            cv::imwrite(erodedPath, erodedMat);
//            */

//        // 查找轮廓
//        std::vector<std::vector<Point>> contours;
//        findContours(erodedMat, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//        if(contours.empty())
//        {
//            return 3;
//        }
//        // 创建掩膜并填充目标轮廓区域
//        Mat mask = Mat::zeros(erodedMat.size(), CV_8UC1);
//        double areaThresh = mmPixel * lineWidth * totalHeight * 0.8;
//        for(uint i = 0; i < contours.size(); i++)
//        {
//            if(cv::contourArea(contours[i]) < areaThresh)
//            {
//                drawContours(mask, contours, static_cast<int>(i), Scalar(255), FILLED);
//            }
//        }
//        erodedMat.setTo(Scalar(0), mask);
//        /*保存腐蚀后的图片
//        std::string erodedPath1 = dao->SelectTestPicturesRootPath(&bResult).toStdString();
//        erodedPath = erodedPath1 + +"/" + "analysised" + "/" + testPaperParameterStruct.sampleId.toStdString().data() + "-eroded1.png";
//        cv::imwrite(erodedPath, erodedMat);
//        */

//    }
//    cv::Mat edgeMat;
//    cv::Rect edge;
//    cv::Rect bbox;
//    cv::Mat rotMat;
//    cv::Mat rotedMat;
//    cv::Mat rotedErodedMat;
//    {
//        // 膨胀操作合并相邻轮廓（关键步骤）
//        cv::Mat mergedMat;
//        cv::Mat dilate_kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(30,20));
//        cv::dilate(erodedMat, mergedMat, dilate_kernel);
//        /*保存图片膨胀后的图片保存
//        std::string mergedPath = dao->SelectTestPicturesRootPath(&bResult).toStdString();
//        // 保存二值化后的图像
//        mergedPath = mergedPath + +"/" + "analysised" + "/" + testPaperParameterStruct.sampleId.toStdString().data() + "-merge.png";
//        cv::imwrite(mergedPath, mergedMat);
//        */

//        // 查找轮廓， 找出最大轮廓值
//        std::vector<std::vector<cv::Point>> contours;
//        cv::findContours(mergedMat, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//        if(contours.empty())
//        {
//            return 3;
//        }
//        auto maxContour = *std::max_element(contours.begin(), contours.end(),[](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b) {
//            return cv::contourArea(a) < cv::contourArea(b);
//        });
//        // 计算最小外接旋转矩形
//        cv::RotatedRect rotatedRect = cv::minAreaRect(maxContour);
//        float angle = rotatedRect.angle;
//        // 角度修正逻辑（OpenCV角度定义特殊）
//        if (rotatedRect.size.width < rotatedRect.size.height) {
//            angle += 90.0f;
//        }
//        cv::Point2f center(mergedMat.cols/2.0f, mergedMat.rows/2.0f);
//        rotMat = cv::getRotationMatrix2D(center, static_cast<double>(angle), 1.0);
//        // 旋转图像并计算新画布尺寸
//        bbox = cv::RotatedRect(center, mergedMat.size(), angle).boundingRect();
//        rotMat.at<double>(0,2) += (bbox.width/2.0 - static_cast<double>(center.x));
//        rotMat.at<double>(1,2) += (bbox.height/2.0 - static_cast<double>(center.y));
//        // 旋转形成新图像
//        cv::warpAffine(mergedMat, rotedMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘
//        /*  旋转到水平的膨胀后的图像
//        std::string rotPath =  dao->SelectTestPicturesRootPath(&bResult).toStdString();
//        // 保存二值化后的图像
//        rotPath = rotPath + +"/" + "analysised" + "/" + testPaperParameterStruct.sampleId.toStdString().data() + "-roted.png";
//        cv::imwrite(rotPath, rotedMat);
//        */

//        //对旋转到水平的图像重新进行轮廓识别
//        std::vector<std::vector<cv::Point>> contours2;
//        cv::findContours(rotedMat, contours2, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//        if(contours2.empty())
//        {
//            return 5;
//        }
//        // 圈出的最大轮廓值
//        auto maxContour2 = std::max_element(contours2.begin(), contours2.end(), [](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b)
//        {
//            return cv::contourArea(a) < cv::contourArea(b);
//        });
//        edge = cv::boundingRect(*maxContour2);

//        // 旋转形成新图像
//        cv::warpAffine(erodedMat, rotedErodedMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘
//        edgeMat = rotedErodedMat(edge);
//        // 保存旋转后重新切的图片
//        /* 保存二值化后的图像
//        std::string edgePath = dao->SelectTestPicturesRootPath(&bResult).toStdString();
//        edgePath = edgePath + +"/" + "analysised" + "/" + testPaperParameterStruct.sampleId.toStdString().data() + "-edgePath.png";
//        cv::imwrite(edgePath, edgeMat);
//        */
//        if(edgeMat.cols < testPaperParameterStruct.dTotalLenght * mmPixel * 0.9 || edgeMat.rows < testPaperParameterStruct.paperHeight * mmPixel * 0.9)
//        {
//            return 4;
//        }
//    }

//    // 重新确定边缘
//    int xStart = -1, yTop = -1, yBottom = -1;
//    double head_thresh = thresh;
//    //按照3个像素的宽度，精细头端位置
//    for(int i = 0; i < edgeMat.cols/2-3;i++)
//    {
//        // x起始坐标，y起始坐标，提取宽度，提取高度
//        cv::Rect roi(i, 0, 3, edgeMat.rows);
//        cv::Mat tempMat = edgeMat(roi);
//        if(cv::mean(tempMat)[0] >= head_thresh)
//        {
//            xStart = i;
//            break;
//        }
//    }
//    //按照3个像素的宽度，精细上端位置
//    for(int i = 0; i < edgeMat.rows/2-3;i++)
//    {
//        cv::Rect roi(0, i, edgeMat.cols, 3);
//        cv::Mat tempMat = edgeMat(roi);
//        if(cv::mean(tempMat)[0] >= head_thresh)
//        {
//            yTop = i;
//            break;
//        }
//    }
//    //按照3个像素的宽度，精细底端位置
//    for(int i = 0; i < edgeMat.rows - 3;i++)
//    {
//        cv::Rect roi(0,  edgeMat.rows - i - 3,edgeMat.cols,  3);
//        cv::Mat tempMat = edgeMat(roi);
//        if(cv::mean(tempMat)[0] >= head_thresh)
//        {
//            yBottom = i;
//            break;
//        }
//    }
//    if(xStart == -1 || yTop == -1 || yBottom == -1)
//    {
//        return 4;
//    }
//    // 修改边缘值
//    edge.x += xStart;
//    edge.y += yTop;
//    edge.width = edgeMat.cols - xStart;
//    edge.height = edgeMat.rows - yTop - yBottom;
//    /* 二值化裁剪图片
//    std::string threshCutPath = dao->SelectTestPicturesRootPath(&bResult).toStdString();
//    threshCutPath = threshCutPath + +"/" + "analysised" + "/" + testPaperParameterStruct.sampleId.toStdString().data() + "-threshCut.png";
//    cv::imwrite(threshCutPath, rotedErodedMat(edge));
//    */

//    // 灰度图像也做相同旋转，与二值化的图像保持一致
//    cv::Mat grayRotMat;
//    cv::warpAffine(grayMat, grayRotMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘

//    /* 旋转后的图片保存
//    std::string grayRotPath = inputPath.toStdString().data();
//    grayRotPath += "calc/";
//    grayRotPath = grayRotPath + fileName.toStdString().data() + "-grayRot.png";
//    cv::imwrite(grayRotPath, grayRotMat(edge));
//    */

//    // 裁剪并保存
//    double yStart = edge.y + (edge.height * (1 - yPercent))/2;
//    double height = edge.height * yPercent;
//    edge.y = static_cast<int>(yStart);
//    edge.height = static_cast<int>(height);
//    cv::Mat croppedMat = grayRotMat(edge);
//    int reEdgeStart = 0;
//    // 修正腐蚀参数
//    for(int i = 0; i < 50-3;i++)
//    {
//        cv::Rect roi(i, 0, 3, croppedMat.rows);
//        cv::Mat tempMat = croppedMat(roi);
//        reEdgeStart = i;
//        if(cv::mean(tempMat)[0] >= thresh)
//        {
//            break;
//        }
//    }
//    cv::Rect reroi( reEdgeStart, 0, croppedMat.cols-reEdgeStart, croppedMat.rows);
//    cv::Mat reCroppedMat = croppedMat(reroi);
//    std::string croppedPath = dao->SelectTestPicturesRootPath(&bResult).toStdString();
//    //剪裁后的图片保存
//    croppedPath = croppedPath +"\\" + "analysised" + "\\" + testPaperParameterStruct.sampleId.toStdString().data() + ".png";
//    cv::imwrite(croppedPath, reCroppedMat);
//    // 将处理后的对象传递出去
//    reCroppedMat.copyTo(dst);

    return 0;
}


/**
 * @brief PictureAnalysis::CalcImageItemWz
 * @param testPaperParameterStruct 膜条参数
 * @param testId 膜条对应的测试ID
 * @return 88 正常 81 标记线异常 83 存在脏污
 */
int PictureAnalysis::CalcImageItemWz(TestPaperStrt &paper, QString testId)
{
//    auto dao = AnalysisDao::instance();
//    bool bResult = true;
//    // 获取要分析的膜条路径
//    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
//    double mm_to_pixel= testPaperParameterStruct.paperMmToPixel;
//    QString strPathFileName_last = piture_root_str + "\\" + "original" + "\\" + testId + "" + ".png";

//    cv::Mat imgMat;
//    // 整张图片的处理 * widthTotal 总宽度   hightTotal总宽度    hightPercent分析高度     thresh灰度阈值
//    int code = GetTestPaperImageWz(strPathFileName_last,testPaperParameterStruct,imgMat);
//    if(code != 0)
//    {
//        qDebug() << "file wzn " << code;
//        return 81;
//    }
//    //所有的线 包括质控 和 cutoff
//    QList<int> positionList;
//    for(int i=0;i<testPaperParameterStruct.nTestItemNumber+2;i++){
//        positionList.append(static_cast<int>((testPaperParameterStruct.dItemPosition[i]) * mm_to_pixel));
//    }

//    // 线宽
//    int lineWidth = static_cast<int>(testPaperParameterStruct.itemLineWidth * mm_to_pixel);
//    // 检测范围
//    int lineLimit = static_cast<int>(testPaperParameterStruct.itemFindWidth * mm_to_pixel);
//    code = GetTestPaperImageCalcIndexWz(imgMat,testPaperParameterStruct, positionList, lineLimit, lineWidth);
//    if(code != 0)
//    {
//        qDebug() << "file1 wzn " << code;
//        return (code == 3 || code == 4) ? 83 : 81;
//    }
    //*d-c  作为灰度值存到数据库  计算浓度值
    return 88;
}

/**
 * @brief 目标将膜条图片精准剪切出来
 * @param inputPath 图片输入路径
 * @param outputPath 图片输出路径
 * @param thresh 图片二值化阈值
 * @return 错误码
 * 1:图片转换失败
 * 2:未找到轮廓
 */
int PictureAnalysis::GetTestPaperImageWz(QString filePath, TestPaperStrt &paper,cv::OutputArray dst)
{
//    double yPercent = testPaperParameterStruct.analysisPercentOfHeight / 100;
//    if(yPercent > 1 || yPercent < 0.4)
//    {
//        return 1;
//    }
//    qDebug()<<"filepath:"<<filePath;
//    // 读取图片并转换为灰度值
//    cv::Mat srcMat = cv::imread(filePath.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
//    if(srcMat.empty())
//    {
//        return 2;
//    }
//    // TODO:: acon膜条旋转180度进行分析
//    cv::Mat grayMat;
//    cv::rotate(srcMat, grayMat, cv::ROTATE_180);

//    // 查询功能线阈值
//    bool bResult;
//    auto dao = AnalysisDao::instance();
//    double mm_to_pixel= testPaperParameterStruct.paperMmToPixel;
//    QString strControlThreshold = dao->SelectControlThreshold(&bResult,testPaperParameterStruct.paperId,testPaperParameterStruct.companyId);
//    m_nControlThreshold = strControlThreshold.toInt();
//    qDebug()<<"m_nControlThreshold:"<<m_nControlThreshold;

//    // 图片二值化阈值 = 功能线阈值
//    int thresh  =125;
//    cv::Mat threshMat;
//    cv::threshold(grayMat, threshMat, thresh, 255, THRESH_BINARY);
//    // 保存二值化后的图像
//    /*剪裁后的图片保存
//        std::string threshPath = dao->SelectTestPicturesRootPath(&bResult).toStdString();
//        // 保存二值化后的图像
//        threshPath = threshPath + +"/" + "analysised" + "/" + testPaperParameterStruct.sampleId.toStdString().data() + "-thresh.png";
//        cv::imwrite(threshPath, threshMat);
//    */

//    // 膨胀操作合并相邻轮廓（关键步骤）
//    cv::Mat mergedMat;
//    cv::Mat dilate_kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(20,20));
//    cv::dilate(threshMat, mergedMat, dilate_kernel);
//    /*保存图片膨胀后的图片保存
//        std::string mergedPath = dao->SelectTestPicturesRootPath(&bResult).toStdString();
//        // 保存二值化后的图像
//        mergedPath = mergedPath + +"/" + "analysised" + "/" + testPaperParameterStruct.sampleId.toStdString().data() + "-merge.png";
//        cv::imwrite(mergedPath, mergedMat);
//    */

//    // 查找轮廓， 找出最大轮廓值
//    std::vector<std::vector<cv::Point>> contours;
//    cv::findContours(mergedMat, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//    if(contours.empty())
//    {
//        return 3;
//    }
//    auto maxContour = *std::max_element(contours.begin(), contours.end(),[](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b) {
//        return cv::contourArea(a) < cv::contourArea(b);
//    });
//    // 计算最小外接旋转矩形
//    cv::RotatedRect rotatedRect = cv::minAreaRect(maxContour);
//    float angle = rotatedRect.angle;
//    //qDebug() << "angle0:" << angle;
//    // 角度修正逻辑（OpenCV角度定义特殊）
//    if (rotatedRect.size.width < rotatedRect.size.height) {
//        angle += 90.0f;
//    }
//    cv::Point2f center(mergedMat.cols/2.0f, mergedMat.rows/2.0f);
//    cv::Mat rotMat = cv::getRotationMatrix2D(center, static_cast<double>(angle), 1.0);
//    // 旋转图像并计算新画布尺寸
//    cv::Rect bbox = cv::RotatedRect(center, mergedMat.size(), angle).boundingRect();
//    rotMat.at<double>(0,2) += (bbox.width/2.0 - static_cast<double>(center.x));
//    rotMat.at<double>(1,2) += (bbox.height/2.0 - static_cast<double>(center.y));
//    // 旋转形成新图像
//    cv::Mat rotedMat;
//    cv::warpAffine(mergedMat, rotedMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘

//    /*  旋转到水平的膨胀后的图像
//    std::string rotPath =  dao->SelectTestPicturesRootPath(&bResult).toStdString();
//    // 保存二值化后的图像
//    rotPath = rotPath + +"/" + "analysised" + "/" + testPaperParameterStruct.sampleId.toStdString().data() + "-roted.png";
//    cv::imwrite(rotPath, rotedMat);
//    */

//    //对旋转到水平的图像重新进行轮廓识别
//    std::vector<std::vector<cv::Point>> contours2;
//    cv::findContours(rotedMat, contours2, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//    if(contours2.empty())
//    {
//        return 5;
//    }
//    // 圈出的最大轮廓值
//    auto maxContour2 = std::max_element(contours2.begin(), contours2.end(), [](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b)
//    {
//        return cv::contourArea(a) < cv::contourArea(b);
//    });
//    cv::Rect edge = cv::boundingRect(*maxContour2);
//    cv::Mat edgeMat = rotedMat(edge);
//    if(edgeMat.cols < testPaperParameterStruct.dTotalLenght * mm_to_pixel * 0.9 || edgeMat.rows < testPaperParameterStruct.paperHeight * mm_to_pixel * 0.9)
//    {
//        return 4;
//    }
//    /* 保存旋转后重新切的图片
//    std::string edgePath = inputPath.toStdString().data();
//    edgePath += "calc/";
//    edgePath = edgePath + fileName.toStdString().data() + "-edgePath.png";
//    cv::imwrite(edgePath, edgeMat);
//    */
//    // 重新确定边缘
//    int xStart = -1, yTop = -1, yBottom = -1;
//    //按照3个像素的宽度，精细头端位置
//    for(int i = 0; i < edgeMat.cols/2-3;i++)
//    {
//        // x起始坐标，y起始坐标，提取宽度，提取高度
//        cv::Rect roi(i, 0, 3, edgeMat.rows);
//        cv::Mat tempMat = edgeMat(roi);
//        if(cv::mean(tempMat)[0] >= thresh)
//        {
//            xStart = i;
//            break;
//        }
//    }
//    //按照3个像素的宽度，精细上端位置
//    for(int i = 0; i < edgeMat.rows/2-3;i++)
//    {
//        cv::Rect roi(0, i, edgeMat.cols, 3);
//        cv::Mat tempMat = edgeMat(roi);
//        if(cv::mean(tempMat)[0] >= thresh)
//        {
//            yTop = i;
//            break;
//        }
//    }
//    //按照3个像素的宽度，精细底端位置
//    for(int i = 0; i < edgeMat.rows - 3;i++)
//    {
//        cv::Rect roi(0,  edgeMat.rows - i - 3,edgeMat.cols,  3);
//        cv::Mat tempMat = edgeMat(roi);
//        if(cv::mean(tempMat)[0] >= thresh)
//        {
//            yBottom = i;
//            break;
//        }
//    }
//    // 修改边缘值
//    edge.x += xStart;
//    edge.y += yTop;
//    edge.width = edgeMat.cols - xStart;
//    edge.height = edgeMat.rows - yTop - yBottom;
//    /* 二值化裁剪图片
//    std::string threshCutPath = inputPath.toStdString().data();
//    threshCutPath += "calc/";
//    threshCutPath = threshCutPath + fileName.toStdString().data() + "-threshCut.png";
//    cv::imwrite(threshCutPath, rotedMat(edge));
//    */

//    // 灰度图像也做相同旋转，与二值化的图像保持一致
//    cv::Mat grayRotMat;
//    cv::warpAffine(grayMat, grayRotMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘
//    if(grayRotMat.cols < testPaperParameterStruct.dTotalLenght * mm_to_pixel || grayRotMat.rows < testPaperParameterStruct.paperHeight*mm_to_pixel*yPercent)
//    {
//        return 6;
//    }

//    /* 旋转后的图片保存
//    std::string grayRotPath = inputPath.toStdString().data();
//    grayRotPath += "calc/";
//    grayRotPath = grayRotPath + fileName.toStdString().data() + "-grayRot.png";
//    cv::imwrite(grayRotPath, grayRotMat(edge));
//    */

//    // 裁剪并保存
//    double yStart = edge.y + (edge.height * (1 - yPercent))/2;
//    double height = edge.height * yPercent;
//    edge.y = static_cast<int>(yStart);
//    edge.height = static_cast<int>(height);
//    cv::Mat croppedMat = grayRotMat(edge);
//    int reEdgeStart = 0;
//    // 修正腐蚀参数
//    for(int i = 0; i < 30-3;i++)
//    {
//        cv::Rect roi(i, 0, 3, croppedMat.rows);
//        cv::Mat tempMat = croppedMat(roi);
//        reEdgeStart = i;
//        if(cv::mean(tempMat)[0] >= thresh)
//        {
//            break;
//        }
//    }
//    cv::Rect reroi( reEdgeStart, 0, croppedMat.cols-reEdgeStart, croppedMat.rows);
//    cv::Mat reCroppedMat = croppedMat(reroi);
//    std::string croppedPath = dao->SelectTestPicturesRootPath(&bResult).toStdString();
//    //剪裁后的图片保存
//    croppedPath = croppedPath +"\\" + "analysised" + "\\" + testPaperParameterStruct.sampleId.toStdString().data() + ".png";
//    cv::imwrite(croppedPath, reCroppedMat);
//    // 将处理后的对象传递出去
//    reCroppedMat.copyTo(dst);

    return 0;
}


/**
 * @brief 目标将圈门圈出，并计算灰度值
 * @param srcMat 图片信息
 * @param outputPath 数据路径
 * @param fileName 输出文件名
 * @param itemCnt 子项目数量
 * @param outGrayArray 0：圈门起始位置 1：圈门宽度 2：圈门内平局灰度值
 * @param lineCenterRelArray[0]:标记线距离膜条前端像素点，其他：项目距离标记线的相对像素点坐标（注意正负）
 * @param lineLimit 子项目可能存在的范围宽度
 * @param lineWidth 子项目线宽
 * @return 0 正常 1 未找到标记线 2 标记线灰度异常 3 计算区域过曝 4 计算区域存在黑点
 */
int PictureAnalysis::GetTestPaperImageCalcIndexWz(const cv::Mat& srcMat, TestPaperStrt &paper,QList<int> lineCenterRelArray, int lineLimit, int lineWidth)
{
    int finalCode = 0;
//    uint lineCenterRelArraySize = static_cast<uint>(lineCenterRelArray.count());
//    std::vector<std::tuple<int,int, double,double>> grayArray(lineCenterRelArraySize, {0,0,0,0});

//    // 标记线在X方向的坐标
//    int markLineXCenter = 0;
//    int markLineLimitStart = lineCenterRelArray[0] - lineLimit;

//    // 定义提取区域：
//    // 这里是故意为之，方便找标记
//    // 向照片头多找一段距离
//    cv::Rect roi(markLineLimitStart, 0, lineLimit*3/2, srcMat.rows);
//    if(srcMat.cols < markLineLimitStart + lineLimit*3/2)
//    {
//        return 2;
//    }
//    cv::Mat markLimitMat = srcMat(roi);

//    /*保存二值化后的图片
//    std::string path1 = "D:/HumablotProFiles/TestPictures/original/a-marklimitThresh.png";
//    cv::imwrite(path1, markLimitMat);
//    */
//    // 反向二值化
//    cv::Mat thresh;
////    cv::adaptiveThreshold(srcMat, thresh, 255,
////                        cv::ADAPTIVE_THRESH_GAUSSIAN_C,
////                        cv::THRESH_BINARY, 11, 2);
//    cv::threshold(markLimitMat, thresh, testPaperParameterStruct.paperBinarizationThreshold, 255, cv::THRESH_BINARY_INV+cv::THRESH_OTSU);

//    /*
//     * std::string path2 = "D:/HumablotProFiles/TestPictures/original/a-marklimitThresh1.png";
//    cv::imwrite(path2, thresh);
//    */
//    /*保存二值化后的图片
//    cv::Mat cloneMat = markLimitMat.clone();
//    cv::rectangle(cloneMat, target_rect, cv::Scalar(255,255,255), 2);
//    cv::Mat m = cloneMat(target_rect);
//    path = path+"-marklimitThresh.png";
//    cv::imwrite(path, thresh);
//    */

//    // 查找轮廓
//    std::vector<std::vector<cv::Point>> contours;
//    cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//    if (contours.empty())
//    {
//        return 1;
//    }
//    //  计算每个轮廓区域的灰度均值
//    int minGrayContourIdx = -1;
//    double markMatGray = 255;
//    for (uint i = 0; i < contours.size(); i++)
//    {
//        cv::Rect rect = cv::boundingRect(contours[i]);
//        // 跳过过小区域（避免噪声干扰）
//        if (rect.width < lineWidth) continue;
//        cv::Mat roi = markLimitMat(rect);
//        double meanGray = cv::mean(roi)[0];
//        if(meanGray < markMatGray)
//        {
//            markMatGray = meanGray;
//            minGrayContourIdx = static_cast<int>(i);
//        }
//    }
//   if (minGrayContourIdx < 0 || markMatGray > 160)
//    {
//        return 2;
//    }
//    cv::Rect target_rect = cv::boundingRect(contours[static_cast<size_t>(minGrayContourIdx)]);
////    //保存二值化后的图片
////    std::string path4 = "D:/HumablotProFiles/TestPictures/original/a-marklimitThresh4.png";
////    cv::imwrite(path4, markLimitMat(target_rect));
//    std::get<0>(grayArray[0]) = markLineLimitStart + target_rect.x + target_rect.width/2;
//    std::get<1>(grayArray[0]) = target_rect.width;
//    std::get<2>(grayArray[0]) = markMatGray;
//    // 标记线结果先保存
//    testPaperParameterStruct.dItemGrayValue[0] = markMatGray;
//    testPaperParameterStruct.dItemPosition[0] = markLineLimitStart + target_rect.x + target_rect.width/2;
//    testPaperParameterStruct.dBackgroundGrayValue[0] = 255;

//    /*保存标记线图片
//    cv::Mat cloneMat = markLimitMat.clone();
//    cv::rectangle(cloneMat, target_rect, cv::Scalar(255,255,255), 2);
//    std::string path1 = outputPath.toStdString().data();
//    path1 += "calc/";
//    path1 += fileName.toStdString().data();
//    path1 = path1+"-marklimit.png";
//    cv::imwrite(path1, cloneMat);
//    */

//    // 标记线中心点在膜条中的位置
//    markLineXCenter = markLineLimitStart + target_rect.x + target_rect.width/2;
////    qDebug() << "markLineXCenter:" << markLineXCenter;
//    //默认fc第一   cutoff第二  以上两个不存在

//    for(uint i = 1; i < lineCenterRelArraySize; i++)
//    {
//        if(testPaperParameterStruct.isCutOff == 0 &&i==1){
//            continue;
//        }
//        // 项目范围线的起始点
//        int limitStart = markLineXCenter + lineCenterRelArray[static_cast<int>(i)] - lineLimit/2;
//        cv::Rect roi(limitStart, 0,  lineLimit, srcMat.rows );
//        cv::Mat calMat = srcMat(roi);
//        // 处理计算时的错误码，并不中断其他项目的计算
//        int calcCode = GetTestOneItemCalcIndexWz(calMat, grayArray[i], lineWidth, 15);
//        if(finalCode == 0)
//        {
//            if(calcCode == 1)
//            {
//                finalCode = 3;
//            }else if (calcCode == 2)
//            {
//                finalCode = 4;
//            }
//        }
//        std::get<0>(grayArray[i]) += limitStart;
//        qDebug() << "result " << std::get<0>(grayArray[i]) << std::get<1>(grayArray[i]) << std::get<2>(grayArray[i])<<std::get<3>(grayArray[i]) << std::get<3>(grayArray[i])-std::get<2>(grayArray[i]);
//        testPaperParameterStruct.dItemErrorCode[i] = 10004;
//        testPaperParameterStruct.dItemGrayValue[i] = std::get<2>(grayArray[i]);
//        testPaperParameterStruct.dBackgroundGrayValue[i] = std::get<3>(grayArray[i]);
//        testPaperParameterStruct.dItemPosition[i] = std::get<0>(grayArray[i]);
//    }

//    cv::Mat drawMat = srcMat.clone();
//    auto dao = AnalysisDao::instance();
//    bool bResult;
//    // 根据返回值进行划线
//    for(uint i = 0; i < lineCenterRelArraySize; i++)
//    {
//        // 画轮廓线
//        cv::Rect roi(std::get<0>(grayArray[i]) - std::get<1>(grayArray[i])/2, 0, std::get<1>(grayArray[i]), srcMat.rows);
//        cv::rectangle(drawMat, roi, cv::Scalar(0,0,0), 1);
//        // 画范围线
//        QString itemName;
//        if(i == 0)
//        {
//            itemName = "FC";
//        }
//        else if(i == 1)
//        {
//            if(testPaperParameterStruct.isCutOff)
//            {
//                itemName = "Cut";
//            }else
//            {
//                continue;
//            }
//        }
//        itemName = testPaperParameterStruct.strTestItemName[i];
//        if(i == 0)
//        {
//            int xstart = lineCenterRelArray[static_cast<int>(i)] - lineLimit;
//            int width = static_cast<int>(lineLimit * 1.5);
//            cv::Rect roi1(xstart, 0, width, 2);
//            cv::rectangle(drawMat, roi1, cv::Scalar(0,0,0), 2);
//            bResult = dao->Insert_tresult_left_right_pixp(testPaperParameterStruct.Id, 0, xstart, xstart+width,itemName, 0,2 );
//        }else
//        {
//            int xstart = markLineXCenter + lineCenterRelArray[static_cast<int>(i)] - lineLimit/2;
//            cv::Rect roi1(xstart, 0, lineLimit, 2);
//            cv::rectangle(drawMat, roi1, cv::Scalar(0,0,0), 2);
//            bResult = dao->Insert_tresult_left_right_pixp(testPaperParameterStruct.Id, 0, xstart, xstart+lineLimit,itemName, 0,2 );
//        }
//    }

//    // 保存最终的分析图片
//    bool issuccess = false;
//    QString path = dao->SelectTestPicturesRootPath(&issuccess);
//    path = path +"\\" + "analysised" + "\\" + testPaperParameterStruct.sampleId.toStdString().data() + "-last.png";
//    cv::imwrite(path.toStdString(), drawMat);
    return finalCode;
}

/**
 * @brief PictureAnalysis::GetTestOneItemCalcIndexWz
 * @param srcMat 需要计算的突然
 * @param result 计算后的结果
 * @param lineWidth 显色线线宽
 * @return 0 成功 1过曝 2黑点
 */
PictureAnalysis::Error PictureAnalysis::GetTestOneItemCalcIndexWz(const cv::Mat& srcMat, std::tuple<int,int,double,double>& result, int lineWidth, int bgDiff)
{
    Error err = Error::NoError;
    // 寻找颜色最深的区域
    int minIdx = 0;
    double minValue = 255;
    for(int i = 0; i < srcMat.cols - lineWidth; i++)
    {
        cv::Rect roi(i, 0, lineWidth, srcMat.rows);
        cv::Mat tempMat = srcMat(roi);
        double tempGray = cv::mean(tempMat)[0];
        if(tempGray < minValue)
        {
            minValue = tempGray;
            minIdx = i;
        }
    }
    cv::Rect destRoi(minIdx, 0, lineWidth, srcMat.rows);
    cv::Mat destMat = srcMat(destRoi);
    // 黑点检测
    int higth = 3;
    double preGray = 0;
    if(bgDiff > 0)
    {
        for(int i = 0; i < destMat.rows - higth; i++)
        {
            cv::Rect roi(0, i, destMat.cols, higth);
            cv::Mat tempMat = destMat(roi);
            double tempGray = cv::mean(tempMat)[0];
            // 引入魔法值15，后续可以写进数据库
            if(i != 0 && std::abs(preGray - tempGray) > bgDiff)
            {
                err = err == Error::NoError ? Error::DetectBlackPoint : err;
            }
            preGray = tempGray;
        }
    }

    // 抠图拼接方便后续去本底
    cv::Rect leftRoi( 0,  0,  minIdx,  srcMat.rows);
    cv::Rect rightRoi( minIdx + lineWidth, 0,  srcMat.cols - minIdx - lineWidth, srcMat.rows);
    cv::Mat stitchMat;
    if(minIdx == 0)
    {
        stitchMat = srcMat(rightRoi);
    }else if(srcMat.cols <= minIdx + lineWidth)
    {
        stitchMat = srcMat(leftRoi);
    }else
    {
        cv::hconcat(srcMat(leftRoi), srcMat(rightRoi), stitchMat);
    }
    // 继续寻找最小值
    int againWidth = stitchMat.cols / 2;
    int againMinIdx = 0;
    double againMinGray = 255;
    for(int i = 0; i < stitchMat.cols - againWidth; i++)
    {
        cv::Rect roi(i, 0, againWidth, srcMat.rows);
        cv::Mat tempMat = stitchMat(roi);
        double tempGray = cv::mean(tempMat)[0];
        if(tempGray < againMinGray)
        {
            againMinGray = tempGray;
            againMinIdx = i;
        }
    }
    // 再次抠图拼接,再次去本底
    leftRoi.width = againMinIdx;
    rightRoi.x = againMinIdx + againWidth;
    rightRoi.width = stitchMat.cols - rightRoi.x;
    cv::Mat stitchAgainMat;
    if(againMinIdx == 0)
    {
        stitchAgainMat = stitchMat(rightRoi);
    }else if(stitchMat.cols <= againMinIdx + lineWidth)
    {
        stitchAgainMat = stitchMat(leftRoi);
    }else
    {
        cv::hconcat(stitchMat(leftRoi), stitchMat(rightRoi), stitchAgainMat);
    }
    if(bgDiff > 0)
    {
        for(int i = 0; i < stitchAgainMat.rows - higth; i++)
        {
            cv::Rect roi(0, i, stitchAgainMat.cols, higth);
            cv::Mat tempMat = stitchAgainMat(roi);
            double tempGray = cv::mean(tempMat)[0];
            // 引入魔法值15，后续可以写进数据库
            if(i != 0 && std::abs(preGray - tempGray) > bgDiff)
            {
                err = err == Error::NoError ? Error::DetectBlackPoint : err;
            }
            preGray = tempGray;
        }
    }
    result = std::make_tuple(minIdx+lineWidth/2, lineWidth, minValue, cv::mean(stitchAgainMat)[0]);
    return err;
}

struct DataPoint {
    size_t index;
    double value;
};


QString PictureAnalysis::CaculateResultText(double dItemGrayRatio, QString itemName, int paper_id,int error_code)
{
    QString testResult = "";
    QMap<double, QString> mapJudgeRules = JudgeDao::instance()->getJudgeValueMap(itemName, paper_id);
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
