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
//   bool bResult;
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
    bResult = AnalysisOneSample(paperId, test_id, sampleId);
    if (bResult == false)
    {
        return false;
    }
    return true;
}


bool PictureAnalysis::isExistCutoffLine(TestPaperStrt& paper)
{
    for(ItemModel& item:paper.itemParamVect)
    {
        if(item.getItemType() == 1) return true;
    }
    return false;
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
    paper.hasCutOff = isExistCutoffLine(paper);
    QString pictureRootPath;
    // 获取要分析的膜条路径
    if(!SystemSetDao::instance()->getPicturePathRoot(pictureRootPath))
    {
        eLog("picture root path error:{}", static_cast<int>(Error::PictureNotFound));
        return false;
    }
    paper.pictureRootPath = pictureRootPath + "/";
    paper.pictureAnalysisPath = paper.pictureRootPath + "/" + "analysised" + "/";
    paper.picturePath = paper.pictureRootPath + "/" + "original" + "/" + paper.testId + "" + ".png";

    if(paperParam.getPaperType() == TestPaperModel::PAPER_TYPE_CONTINUOUS) // 连续膜条处理
    {
        if(paper.itemParamVect.size() != paperParam.getTotalNumber())
        {
            eLog("item config error:{}", static_cast<int>(Error::ItemConfigError));
            return false;
        }
        resultCode = ContinuousPaperHandle(paper);
    }else
    {
        if(paper.itemParamVect.back().getSegmentIndex() != paperParam.getTotalNumber())
        {
            eLog("item config segment error:{}", static_cast<int>(Error::ItemConfigError));
            return false;
        }
        resultCode = SegmentPaperHandle(paper);
    }

    double cutoffGray = paper.hasCutOff ? paper.itemResultVect[1].grayValue : paperParam.getCutOffValue();
    QMap<int, StandardCurveParameter> curveMap;
    standard_curve curve_obj(nullptr);
    for(int i = 0; i < paper.itemParamVect.count(); i++)
    {
        ItemModel& item = paper.itemParamVect[i];
        if(i >= paper.itemResultVect.count())
        {
            continue;
        }
        TestPaperItemResult& result = paper.itemResultVect[i];
        StandardCurveParameter curveParameter;
        int curveId = paper.itemParamVect[i].getCurveId();
        if(!curveMap.contains(curveId))
        {
            curve_obj.GetStandardCurveParameter(curveParameter, curveId);
            curveMap.insert(curveId, curveParameter);
        }else
        {
            curveParameter = curveMap.take(curveId);
        }
        if(item.getItemType() == 0)
        {
            result.grayRatio = 1;
        }else if(item.getItemType() == 1)
        {
            result.grayRatio = 1;
        }else
        {
            if(paper.hasCutOff)
            {
                double settingBackgroundValue = paperParam.getPaperBackgroundValue();
                result.grayValue = 1.0 * result.grayValue / result.backgroundGrayValue * settingBackgroundValue;
            }
            double a_item = 0, b_cut = 0, c1 = 0;
            a_item = qLn((result.grayValue < 1 ? 1 : result.grayValue) / 255);
            b_cut = qLn(cutoffGray < 1 ? 1 : cutoffGray  / 255);
            c1 =  a_item/ b_cut;
            if(std::isnan(c1) || std::isinf(c1))
            {
                result.grayRatio = 0;
            }else
            {
                result.grayRatio = curve_obj.Calc(curveParameter, c1) + item.getResultOffset();
            }
        }
    }
    UpdateSampleAnalysisState(paper, resultCode);
    //根据灰度值计算结果写到数据库
    if (resultCode != Error::NoError)
    {
        if (!SaveTestData(paper)) return false;
    }
    qDebug()<<"resultCode="<<static_cast<int>(resultCode);
    return true;
}

bool PictureAnalysis::SaveTestData(TestPaperStrt& paper)
{
    auto dao = AnalysisDao::instance();
    bool bResult;
    QString strGrayValue;
    QString strRatioToCut;
    QString manageName = SystemSetDao::instance()->getTester();
    QDateTime nowTime = QDateTime::currentDateTime();
    QString solutionName = SystemSetDao::instance()->getDefaultProcessName();
    QString strTestDateTime = nowTime.toString("yyyy-MM-dd hh:mm:ss");
    for (int i = 0; i < paper.itemParamVect.count(); i++)
    {
        ItemModel& item = paper.itemParamVect[i];
        if(i >= paper.itemResultVect.count()) continue;
        TestPaperItemResult& result = paper.itemResultVect[i];
        QString paper_id = QString::number(paper.paperParam.getId());
        QString articleNo = paper.paperParam.getArticleNo();
        QString strItemName = item.getItemName();
        QString strPosition = QString::number(result.lineCenter);
        if(result.grayValue < 0.01)
        {
            strGrayValue = QString::number(0);
        }else
        {
            strGrayValue = QString::number(result.grayValue, 'f', 2);
        }
        if(result.grayRatio < 0.01)
        {
            strRatioToCut = QString::number(0);
        }
        else
        {
            strRatioToCut = QString::number(result.grayRatio, 'f', 2);
        }
        QString strDiagnosis = CaculateResultText(result.grayRatio, strItemName, paper_id.toInt());
        bResult = dao->InsertTestData(
                    solutionName,
                    paper.sampleId,
                    paper_id,
                    articleNo,
                    manageName,
                    paper.sampleId,
                    strItemName,
                    strPosition,
                    strGrayValue,
                    strRatioToCut,
                    strDiagnosis,
                    strTestDateTime, static_cast<int>(result.errorCode));
        if (bResult == false)
        {
            return false;
        }
    }
    return true;
}

bool PictureAnalysis::UpdateSampleAnalysisState(TestPaperStrt& paper, Error error)
{
    auto dao = AnalysisDao::instance();
    bool bResult;
    QString state = QString::number(static_cast<int>(error));
    bResult = dao->UpdateSampleAnalysisState(paper.testId, state);
    if (bResult == false)
    {
        return false;
    }
    return true;
}

/**
 * @brief 分段膜条处理
 * @param testPaperParameterStruct
 * @param testId
 * @return
 */
PictureAnalysis::Error PictureAnalysis::SegmentPaperHandle(TestPaperStrt &paper)
{
    TestPaperModel& paperParam = paper.paperParam;
    double yPercent = paperParam.getAnalysisPercentOfHeightDouble();

    if(yPercent > 1 || yPercent < 0.4)
    {
        return Error::ItemAnalysisHeightError;
    }
    // 读取图片并转换为灰度值
    cv::Mat srcMat = cv::imread(paper.picturePath.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
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
    // 剪切后的图片, 剪裁后经过二值化的图片对象
    cv::Mat cutMat, cutThreshMat;
    Error err = SegmentPaperRotateCut(grayMat, paper, cutMat, cutThreshMat);
    if(err != Error::NoError)
    {
        return err;
    }
    // 段解析
    err = PaperSegmentationParse(cutMat, cutThreshMat, paper);
    if(err != Error::NoError)
    {
        return err;
    }
    // 解析子项目
    return SegmentPaperItemParse(cutMat, paper);
}

/**
 * @brief 分段膜条旋转操作并剪切
 * @return 错误码
 * 0 成功
 * 1:图片识别失败
 */
PictureAnalysis::Error PictureAnalysis::SegmentPaperRotateCut(cv::Mat& srcMat, TestPaperStrt &paper, cv::OutputArray dstMat, cv::OutputArray dst_thresh_mat)
{
    TestPaperModel& paperParam = paper.paperParam;
    double mmPixel= paperParam.getPaperMmToPixel();
    // 段宽度
    double segmentMinWidth = paperParam.getTestBlockWidth() * mmPixel;
    // 膜条高度
    double totalHeigth = paperParam.getPaperHeight() * mmPixel;
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
    QString lightPath = paper.pictureAnalysisPath + paper.sampleId + "-nolight.png";
    cv::imwrite(lightPath.toStdString(), srcMat);

    cv::Mat threshMat;
    cv::threshold(srcMat, threshMat, thresh, 255, THRESH_BINARY);
    // 保存二值化后的图像
        // 保存二值化后的图像
        QString threshPath = paper.pictureAnalysisPath + paper.sampleId + "-thresh.png";
        cv::imwrite(threshPath.toStdString(), threshMat);

    Mat erodedMat;
    {
        // 腐蚀
        Mat eroded_kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        erode(threshMat, erodedMat, eroded_kernel);
        //保存腐蚀后的图片
            QString erodedPath = paper.pictureAnalysisPath + paper.sampleId + "-eroded.png";
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
            qDebug()<<"rect"<<rect.width<<rect.height<<segmentMinWidth<<totalHeigth;
            // TODO::WANGZ
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
            QString maxRectPath = paper.pictureAnalysisPath + paper.sampleId + "-maxRect.png";
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
            QString maxRectPath = paper.pictureAnalysisPath + paper.sampleId + "-maxRect1.png";
            cv::imwrite(maxRectPath.toStdString(), maxRectMat);

    }

    // 灰度图像也做相同旋转，与二值化的图像保持一致
    cv::Mat grayRotMat;
    cv::warpAffine(srcMat, grayRotMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘

    // 开始去噪声，仅对上下边界，目的是精细化边界位置
    int top = -1, bottom = -1;
    cv::Mat maxGrayMat = grayRotMat(maxRect);
    //  保存灰度图片
    QString maxGrayMatPath = paper.pictureAnalysisPath + paper.sampleId + "-maxGrayMat.png";
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
        //剪裁后的图片保存
        QString croppedPath = paper.pictureAnalysisPath + paper.sampleId + ".png";
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
        //剪裁后的图片保存
        QString croppedPath1 = paper.pictureAnalysisPath + paper.sampleId + "-1.png";
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
PictureAnalysis::Error PictureAnalysis::PaperSegmentationParse(cv::Mat& srcMat,cv::Mat& threshMat, TestPaperStrt &paper)
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

        paper.segmentResultVect.push_back(TestPaperSegmentResult(rect.x + static_cast<int>((start+end)/2), end - start));
    }
    return Error::NoError;
}


PictureAnalysis::Error PictureAnalysis::SegmentPaperItemParse(cv::Mat& cutMat, TestPaperStrt &paper)
{
    Error err = Error::NoError;
    QVector<ItemModel>& itemVect = paper.itemParamVect;
    TestPaperModel& paperParam = paper.paperParam;
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
    // 另外存一个图片,用来展示界面
    cv::Mat drawMat = cutMat.clone();
    // 计算各个项目的灰度值
    int itemIdx = 0;
    int blackDetectThreshold = paperParam.getIsBlackPointDetect() ? static_cast<int>(paperParam.getBlackPointDetectThreshold()) : 0;
    auto dao = AnalysisDao::instance();
    bool bResult = false;
    bool ignoreHead = paperParam.getIgnoreHeadLenght() > 0; // 很关键, 头部文字会干扰分段
    double mmPixel= paperParam.getPaperMmToPixel();
    for (int segmentIndex : itemsBySegment.keys())
    {
        const QVector<ItemModel>& itemVectOnSegment = itemsBySegment[segmentIndex];
        int itemCntOnSegment = itemVectOnSegment.size();
        if(itemCntOnSegment == 0) continue;
        int segNo =  ignoreHead ? segmentIndex - 2 : segmentIndex - 1;
        if(segNo < 0) continue;
        int center = static_cast<int>(paper.segmentResultVect[segNo]._center);
        int totalScanWidth = static_cast<int>(paper.segmentResultVect[segNo]._width * 0.9);
        int itemScanWidth = static_cast<int>(1.0 * totalScanWidth / itemCntOnSegment);

        for(const ItemModel& item:itemVectOnSegment)
        {
            paper.itemResultVect.push_back(TestPaperItemResult());
            TestPaperItemResult& itemResult = paper.itemResultVect.back(); // 结果计算
            if(segmentIndex < 1)
            {
                itemResult.errorCode = Error::SegmentSetError;
                continue;
            }
            int positionNo = item.getPositionNo() - 1;
            // 项目范围线的起始点
            int limitStart = static_cast<int>(center - totalScanWidth/2 + (itemCntOnSegment - positionNo - 1) * itemScanWidth);
            int limitWidth = itemScanWidth;
            cv::Rect calcRect(limitStart, 0,  limitWidth, cutMat.rows);
            cv::Mat calMat = cutMat(calcRect);
            err = OneItemParse(calMat, itemResult, static_cast<int>(paperParam.getItemAnalysisWidth()*mmPixel), blackDetectThreshold);
            if(err != Error::NoError) break;
            // 功能线判定
            if(item.getItemType() == 0 && itemResult.grayValue > paperParam.getFuncGrayThreshold())
            {
                err = Error::FuncLineError;
                break;
            }
            if(item.getItemType() == 1 && itemResult.grayValue > paperParam.getCutOffThreshold())
            {
                err = Error::CutOffLineError;
                break;
            }

            itemResult.lineCenter += limitStart;
            double finaleGrayValue = itemResult.grayValue;
            finaleGrayValue = finaleGrayValue < 0 ? 0 : finaleGrayValue;
            // 保存解析后的灰度值
            itemResult.grayValue = finaleGrayValue;
            qDebug() << "result " << itemResult.lineCenter << itemResult.lineWidth << itemResult.grayValue << itemResult.backgroundGrayValue << itemResult.backgroundGrayValue-itemResult.grayValue;
            // 可视化项目线
            cv::Rect roi(itemResult.lineCenter - itemResult.lineWidth/2, 0, itemResult.lineWidth, cutMat.rows);
            cv::rectangle(drawMat, roi, cv::Scalar(0,0,0), 1);
            // 画范围线
            cv::Rect roi1(limitStart, 0, limitWidth, 2);
            cv::rectangle(drawMat, roi1, cv::Scalar(0,0,0), 2);
            // 插入位置信息
            bResult = dao->Insert_tresult_left_right_pixp(paper.testId, static_cast<int>(itemIdx), limitStart, limitStart+limitWidth, item.getItemName(), 0, 2 );
        }
    }
    // 保存最终的分析图片
    QString path = paper.pictureAnalysisPath + paper.sampleId + "-last.png";
    cv::imwrite(path.toStdString(), drawMat);
    return err;
}


/**
 * @brief PictureAnalysis::ContinuousPaperHandle
 * 连续膜条的判读方式
 * @param testPaperParameterStruct
 * @param testId
 * @return
 */
PictureAnalysis::Error PictureAnalysis::ContinuousPaperHandle(TestPaperStrt &paper)
{
    cv::Mat imgMat;
    // 整张图片的处理
    Error code = ContinuousPaperRotateCut(paper, imgMat);
    if(code != Error::NoError)
    {
        return code;
    }
    code = ContinuousPaperItemParse(imgMat, paper);
    if(code != Error::NoError)
    {
        return code;
    }
    //*d-c  作为灰度值存到数据库  计算浓度值
    return Error::NoError;
}

bool PictureAnalysis::SrcImageNeedRotate180(TestPaperModel& paper)
{
    return paper.getPaperShowAngle() == 180;
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
PictureAnalysis::Error PictureAnalysis::ContinuousPaperRotateCut(TestPaperStrt &paper, cv::OutputArray dst)
{
    TestPaperModel& paperParam = paper.paperParam;
    double mmPixel= paperParam.getPaperMmToPixel();
    int thresh = paperParam.getPaperBinarizationThreshold();
    double yPercent = paperParam.getAnalysisPercentOfHeightDouble();
    double totalHeight = paperParam.getPaperHeight() * mmPixel;
    double lineWidth = paperParam.getItemLineWidth() * mmPixel;
    if(yPercent > 1 || yPercent < 0.4)
    {
        return Error::ConfigError;
    }
    // 读取图片并转换为灰度值
    cv::Mat srcMat = cv::imread(paper.picturePath.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
    if(srcMat.empty())
    {
        return Error::PictureNotFound;
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

    // 图片二值化阈值 = 功能线阈值
    cv::Mat threshMat;
    cv::threshold(grayMat, threshMat, thresh, 255, THRESH_BINARY);
    // 保存二值化图像
    QString threshPath = paper.pictureAnalysisPath + paper.sampleId + "-thresh.png";
    cv::imwrite(threshPath.toStdString(), threshMat);

    Mat erodedMat;
    {
        // 腐蚀操作,过滤噪点
        Mat eroded_kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        erode(threshMat, erodedMat, eroded_kernel);
        //保存腐蚀后的图片
        QString erodedPath = paper.pictureAnalysisPath + paper.sampleId + "-eroded.png";
        cv::imwrite(erodedPath.toStdString(), erodedMat);

        // 查找轮廓
        std::vector<std::vector<Point>> contours;
        findContours(erodedMat, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        if(contours.empty())
        {
            return Error::ContourNotFound;
        }
        // 创建掩膜并填充目标轮廓区域
        Mat mask = Mat::zeros(erodedMat.size(), CV_8UC1);
        double heightThreshold = totalHeight * 0.7;
        for(uint i = 0; i < contours.size(); i++)
        {
            cv::Rect rect = cv::boundingRect(contours[i]);
            if(rect.height < heightThreshold)
            {
                drawContours(mask, contours, static_cast<int>(i), Scalar(255), FILLED);
            }
        }
        erodedMat.setTo(Scalar(0), mask);
        //保存腐蚀后的图片
        QString erodedPath1 = paper.pictureAnalysisPath + paper.sampleId + "-eroded1.png";
        cv::imwrite(erodedPath1.toStdString(), erodedMat);
    }
    cv::Mat edgeMat;
    cv::Rect edge;
    cv::Rect bbox;
    cv::Mat rotMat;
    cv::Mat rotedMat;
    cv::Mat rotedErodedMat;
    {
        // 膨胀操作合并相邻轮廓（关键步骤）
        cv::Mat mergedMat;
        cv::Mat dilate_kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(30,20));
        cv::dilate(erodedMat, mergedMat, dilate_kernel);
        //保存图片膨胀后的图片保存
        QString mergedPath = paper.pictureAnalysisPath + paper.sampleId + "-merge.png";
        cv::imwrite(mergedPath.toStdString(), mergedMat);

        // 查找轮廓， 找出最大轮廓值
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(mergedMat, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        if(contours.empty())
        {
            return Error::ContourNotFound;
        }
        auto maxContour = *std::max_element(contours.begin(), contours.end(),[](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b) {
            return cv::contourArea(a) < cv::contourArea(b);
        });
        // 计算最小外接旋转矩形
        cv::RotatedRect rotatedRect = cv::minAreaRect(maxContour);
        float angle = rotatedRect.angle;
        // 角度修正逻辑（OpenCV角度定义特殊）
        if (rotatedRect.size.width < rotatedRect.size.height) {
            angle += 90.0f;
        }
        cv::Point2f center(mergedMat.cols/2.0f, mergedMat.rows/2.0f);
        rotMat = cv::getRotationMatrix2D(center, static_cast<double>(angle), 1.0);
        // 旋转图像并计算新画布尺寸
        bbox = cv::RotatedRect(center, mergedMat.size(), angle).boundingRect();
        rotMat.at<double>(0,2) += (bbox.width/2.0 - static_cast<double>(center.x));
        rotMat.at<double>(1,2) += (bbox.height/2.0 - static_cast<double>(center.y));
        // 旋转形成新图像
        cv::warpAffine(mergedMat, rotedMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘
        //  旋转到水平的膨胀后的图像
        // 保存二值化后的图像
        QString rotPath = paper.pictureAnalysisPath + paper.sampleId + "-roted.png";
        cv::imwrite(rotPath.toStdString(), rotedMat);

        //对旋转到水平的图像重新进行轮廓识别
        std::vector<std::vector<cv::Point>> contours2;
        cv::findContours(rotedMat, contours2, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        if(contours2.empty())
        {
            return Error::ContourNotFound;
        }
        // 圈出的最大轮廓值
        auto maxContour2 = std::max_element(contours2.begin(), contours2.end(), [](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b)
        {
            return cv::contourArea(a) < cv::contourArea(b);
        });
        edge = cv::boundingRect(*maxContour2);

        // 旋转形成新图像
        cv::warpAffine(erodedMat, rotedErodedMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘
        edgeMat = rotedErodedMat(edge);
        // 保存旋转后重新切的图片
        // 保存二值化后的图像
        QString edgePath = paper.pictureAnalysisPath + paper.sampleId + "-edgePath.png";
        cv::imwrite(edgePath.toStdString(), edgeMat);
        double totalLenght = paperParam.getTotalLenght() * mmPixel;
        double paperHeight = paperParam.getPaperHeight() * mmPixel;
        if(edgeMat.cols < totalLenght * 0.9 || edgeMat.rows < paperHeight * 0.9)
        {
            return Error::ContourNotFound;
        }
    }

    if(edgeMat.cols/2 <= 3)
    {
        return Error::ContourNotFound;
    }
    // 重新确定边缘
    int xStart = -1, yTop = -1, yBottom = -1;
    double head_thresh = thresh;
    //按照3个像素的宽度，精细头端位置
    for(int i = 0; i < edgeMat.cols/2-3;i++)
    {
        // x起始坐标，y起始坐标，提取宽度，提取高度
        cv::Rect roi(i, 0, 3, edgeMat.rows);
        cv::Mat tempMat = edgeMat(roi);
        if(cv::mean(tempMat)[0] >= head_thresh)
        {
            xStart = i;
            break;
        }
    }
    //按照3个像素的宽度，精细上端位置
    for(int i = 0; i < edgeMat.rows/2-3;i++)
    {
        cv::Rect roi(0, i, edgeMat.cols, 3);
        cv::Mat tempMat = edgeMat(roi);
        if(cv::mean(tempMat)[0] >= head_thresh)
        {
            yTop = i;
            break;
        }
    }
    if(edgeMat.rows <= 3)
    {
        return Error::ContourNotFound;
    }
    //按照3个像素的宽度，精细底端位置
    for(int i = 0; i < edgeMat.rows - 3;i++)
    {
        cv::Rect roi(0,  edgeMat.rows - i - 3,edgeMat.cols,  3);
        cv::Mat tempMat = edgeMat(roi);
        if(cv::mean(tempMat)[0] >= head_thresh)
        {
            yBottom = i;
            break;
        }
    }
    if(xStart == -1 || yTop == -1 || yBottom == -1)
    {
        return Error::ContourNotFound;
    }
    // 修改边缘值
    edge.x += xStart;
    edge.y += yTop;
    edge.width = edgeMat.cols - xStart;
    edge.height = edgeMat.rows - yTop - yBottom;
    // 二值化裁剪图片
    QString threshCutPath = paper.pictureAnalysisPath + paper.sampleId + "-threshCut.png";
    cv::imwrite(threshCutPath.toStdString(), rotedErodedMat(edge));

    // 灰度图像也做相同旋转，与二值化的图像保持一致
    cv::Mat grayRotMat;
    cv::warpAffine(grayMat, grayRotMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘

    // 裁剪并保存
    int yStart = static_cast<int>(edge.y + (edge.height * (1 - yPercent))/2);
    int height = static_cast<int>(edge.height * yPercent);
    cv::Rect croppedEdge(edge.x, yStart, edge.width, height);
    cv::Mat croppedMat = grayRotMat(croppedEdge);
    int reEdgeStart = 0;
    if(croppedMat.cols < 50) return Error::ContourNotFound;
    // 修正腐蚀参数
    for(int i = 0; i < 50-3;i++)
    {
        cv::Rect roi(i, 0, 3, croppedMat.rows);
        cv::Mat tempMat = croppedMat(roi);
        reEdgeStart = i;
        if(cv::mean(tempMat)[0] >= thresh)
        {
            break;
        }
    }
    cv::Rect reroi(reEdgeStart, 0, croppedMat.cols-reEdgeStart, croppedMat.rows);
    cv::Mat reCroppedMat = croppedMat(reroi);
    //剪裁后的图片保存
    cv::Mat drawMat = grayRotMat(cv::Rect(edge.x+reEdgeStart, edge.y, edge.width-reEdgeStart, edge.height));
    QString drawPath = paper.pictureAnalysisPath + paper.sampleId + ".png";
    cv::imwrite(drawPath.toStdString(), drawMat);
    // 将处理后的对象传递出去
    reCroppedMat.copyTo(dst);
    return Error::NoError;
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
PictureAnalysis::Error PictureAnalysis::ContinuousPaperItemParse(const cv::Mat& srcMat, TestPaperStrt &paper)
{
    Error itemError = Error::NoError;
    TestPaperModel& paperParam = paper.paperParam;

    double mmPixel= paperParam.getPaperMmToPixel();
    QList<int> positionList;
    for(ItemModel& item : paper.itemParamVect)
    {
        positionList.append(static_cast<int>(item.getPosition() * mmPixel));
    }
    // 线宽
    int lineWidth = static_cast<int>(paperParam.getItemLineWidth() * mmPixel);
    // 检测范围
    int lineLimit = static_cast<int>(paperParam.getItemFindWidth() * mmPixel);
    int funcLineLimit = static_cast<int>(paperParam.getFuncFindWidth() * mmPixel);
    int lineCenterRelArraySize = positionList.count();
    // 标记线在X方向的坐标
    int markLineXCenter = 0;
    int markLineLimitStart = positionList[0] - lineLimit;

    // 定义提取区域：
    // 功能线的提取范围可以更大一些
    if(srcMat.cols < markLineLimitStart + funcLineLimit)
    {
        return Error::ContourNotFound;
    }
    cv::Rect roi(markLineLimitStart, 0, funcLineLimit, srcMat.rows);
    cv::Mat markLimitMat = srcMat(roi);

    //保存二值化后的图片
    QString path1 = paper.pictureAnalysisPath + paper.sampleId + "marklimitThresh.png";
    cv::imwrite(path1.toStdString(), markLimitMat);

    // 反向二值化
    cv::Mat thresh;
    cv::threshold(markLimitMat, thresh, paperParam.getPaperBinarizationThreshold(), 255, cv::THRESH_BINARY_INV+cv::THRESH_OTSU);
    QString path2 = paper.pictureAnalysisPath + paper.sampleId + "-marklimitThresh.png";
    cv::imwrite(path2.toStdString(), thresh);

    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    if (contours.empty())
    {
        return Error::ContourNotFound;
    }
    //  计算每个轮廓区域的灰度均值
    int minGrayContourIdx = -1;
    double markMatGray = 255;
    for (uint i = 0; i < contours.size(); i++)
    {
        cv::Rect rect = cv::boundingRect(contours[i]);

        qDebug()<<"rect"<<rect.width<<lineWidth;
        // 跳过过小区域（避免噪声干扰）
        if (rect.width < lineWidth*0.5) continue;
        cv::Mat roi = markLimitMat(rect);
        double meanGray = cv::mean(roi)[0];
        if(meanGray < markMatGray)
        {
            markMatGray = meanGray;
            minGrayContourIdx = static_cast<int>(i);
        }
    }
    qDebug()<<"minGrayContourIdx"<<minGrayContourIdx<<markMatGray;
   if (minGrayContourIdx < 0 || markMatGray > 160)
    {
        return Error::FuncLineError;
    }
    cv::Rect target_rect = cv::boundingRect(contours[static_cast<size_t>(minGrayContourIdx)]);
    {
        // 功能线 解析结果保存
        TestPaperItemResult result;
        result.errorCode = Error::NoError;
        result.grayValue = markMatGray;
        result.lineCenter = markLineLimitStart + target_rect.x + target_rect.width/2;
        result.backgroundGrayValue = 255;
        paper.itemResultVect.push_back(result);
    }

    //保存标记线图片
    cv::Mat cloneMat = markLimitMat.clone();
    cv::rectangle(cloneMat, target_rect, cv::Scalar(255,255,255), 2);
    QString path3 = paper.pictureAnalysisPath + paper.sampleId + "-marklimit.png";
    cv::imwrite(path3.toStdString(), cloneMat);


    // 标记线中心点在膜条中的位置
    markLineXCenter = markLineLimitStart + target_rect.x + target_rect.width/2;
    for(int i = 1; i < lineCenterRelArraySize; i++)
    {
        paper.itemResultVect.push_back(TestPaperItemResult());
        TestPaperItemResult& result = paper.itemResultVect.back();
        // 项目范围线的起始点
        int limitStart = markLineXCenter + positionList[i] - lineLimit/2;
        cv::Rect roi(limitStart, 0,  lineLimit, srcMat.rows );
        cv::Mat calMat = srcMat(roi);
        // 处理计算时的错误码，并不中断其他项目的计算
        Error calcCode = OneItemParse(calMat, result, static_cast<int>(paperParam.getItemAnalysisWidth()*mmPixel), 15);
        if(itemError == Error::NoError)
        {
            itemError = calcCode;
        }
        result.lineCenter += limitStart;
        qDebug() << "result " << result.lineCenter << result.lineWidth << result.grayValue<<result.backgroundGrayValue << result.backgroundGrayValue-result.grayValue;
    }

    cv::Mat drawMat = srcMat.clone();
    auto dao = AnalysisDao::instance();
    bool bResult;
    // 根据返回值进行划线
    for(int i = 0; i < lineCenterRelArraySize; i++)
    {
        TestPaperItemResult& result = paper.itemResultVect[i];
        qDebug()<<"result.lineCenter"<<result.lineCenter<<result.lineWidth<<srcMat.rows;
        // 画轮廓线
        cv::Rect roi(result.lineCenter - result.lineWidth/2, 0, result.lineWidth, srcMat.rows);
        cv::rectangle(drawMat, roi, cv::Scalar(0,0,0), 1);
        // 画范围线
        const QString& itemName = paper.itemParamVect[i].getItemName();
        if(i == 0)
        {
            int xstart = positionList[static_cast<int>(i)] - lineLimit;
            int width = static_cast<int>(lineLimit * 1.5);
            cv::Rect roi1(xstart, 0, width, 2);
            cv::rectangle(drawMat, roi1, cv::Scalar(0,0,0), 2);
            bResult = dao->Insert_tresult_left_right_pixp(paper.sampleId, 0, xstart, xstart+width, itemName, 0,2 );
        }else
        {
            int xstart = markLineXCenter + positionList[static_cast<int>(i)] - lineLimit/2;
            cv::Rect roi1(xstart, 0, lineLimit, 2);
            cv::rectangle(drawMat, roi1, cv::Scalar(0,0,0), 2);
            bResult = dao->Insert_tresult_left_right_pixp(paper.sampleId, 0, xstart, xstart+lineLimit, itemName, 0,2 );
        }
    }

    // 保存最终的分析图片
    QString path = paper.pictureAnalysisPath + paper.sampleId + "-last.png";
    cv::imwrite(path.toStdString(), drawMat);
    return itemError;
}

/**
 * @brief PictureAnalysis::OneItemParse
 * @param srcMat 需要计算的突然
 * @param result 计算后的结果
 * @param lineWidth 显色线线宽
 * @return 0 成功 1过曝 2黑点
 */
PictureAnalysis::Error PictureAnalysis::OneItemParse(const cv::Mat& srcMat, TestPaperItemResult& result, int lineWidth, int bgDiff)
{
    // 寻找颜色最深的区域
    int minIdx = 0;
    double minValue = 255;
    if(srcMat.cols < lineWidth) return Error::ItemLineDetectError;
    // 按照线宽查找区域最深的矩形.
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
    // 行方向查找黑点
    Error err = Error::NoError;
    int higth = 3;
    double preGray = 0;
    if(destMat.rows < higth) return Error::ItemLineDetectError;
    if(bgDiff > 0)
    {
        for(int i = 0; i < destMat.rows - higth; i++)
        {
            cv::Rect roi(0, i, destMat.cols, higth);
            cv::Mat tempMat = destMat(roi);
            double tempGray = cv::mean(tempMat)[0];
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
    // 需要再次判定背景处是否有黑点
    if(bgDiff > 0)
    {
        for(int i = 0; i < stitchAgainMat.rows - higth; i++)
        {
            cv::Rect roi(0, i, stitchAgainMat.cols, higth);
            cv::Mat tempMat = stitchAgainMat(roi);
            double tempGray = cv::mean(tempMat)[0];
            if(i != 0 && std::abs(preGray - tempGray) > bgDiff)
            {
                err = err == Error::NoError ? Error::DetectBlackPoint : err;
            }
            preGray = tempGray;
        }
    }
    result.lineCenter = minIdx+lineWidth/2;
    result.lineWidth = lineWidth;
    result.grayValue = minValue;
    result.backgroundGrayValue = cv::mean(stitchAgainMat)[0];
    result.errorCode = err;
    return err;
}


QString PictureAnalysis::CaculateResultText(double dItemGrayRatio, QString itemName, int paper_id)
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
            key_list.push_back(it.key() -1000);
            value_list.push_back(it.value());
        }
        key_list.push_back(it.key());
        value_list.push_back(it.value());

        if (tmp_i == (mapJudgeRules.count() - 1))
        {
            key_list.push_back(it.key()+2000);
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
    return testResult;
}
