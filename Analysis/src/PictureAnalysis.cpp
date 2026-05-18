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
    paper.itemResultVect.resize(paper.itemParamVect.size());// 为每个item预先生成一个默认结果

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
    qDebug()<<"resultCode="<<static_cast<int>(resultCode);
    UpdateSampleAnalysisState(paper, resultCode);
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
        if(resultCode != Error::NoError)
        {
            result.grayValue = 0;
            result.grayRatio = 0;
            result.qualitativeResult = "-";
            continue;
        }
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
            if(!paper.hasCutOff)
            {
                double settingBackgroundValue = paperParam.getPaperBackgroundValue();
                result.grayValue = 1.0 * result.grayValue / result.backgroundGrayValue * settingBackgroundValue;
            }
            double a_item = 0, b_cut = 0, c1 = 0;
            a_item = qLn((result.grayValue < 1 ? 1 : result.grayValue) / 255);
            b_cut = qLn((cutoffGray < 1 ? 1 : cutoffGray)  / 255);
            c1 =  a_item/ b_cut;
            if(std::isnan(c1) || std::isinf(c1))
            {
                result.grayRatio = 0;
            }else
            {
                result.grayRatio = curve_obj.Calc(curveParameter, c1) + item.getResultOffset();
            }
            result.qualitativeResult = CaculateResultText(result.grayRatio, item.getRulesId());
        }
        qDebug() << "final result " << result.grayValue<<result.backgroundGrayValue << result.backgroundGrayValue-result.grayValue << result.grayRatio<<result.qualitativeResult;
    }
    //根据灰度值计算结果写到数据库
    if (!SaveTestData(paper)) return false;
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
                    result.qualitativeResult,
                    strTestDateTime, 0);
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
 * @brief 将范围外的颜色全部设置为黑色
 * @param src
 * @param roi
 */
void PictureAnalysis::maskOutsideRect(cv::Mat& src, const cv::Rect& roi) {
    // 确保 ROI 在图像范围内
    cv::Rect safeRoi = roi & cv::Rect(0, 0, src.cols, src.rows);

    // 创建全黑图像（与 src 同尺寸、同类型）
    cv::Mat black = cv::Mat::zeros(src.size(), src.type());

    // 将 ROI 区域从 src 复制到 black 中
    src(safeRoi).copyTo(black(safeRoi));

    // 替换原图
    src = black;
}


/**
 * @brief 分段膜条旋转操作并剪切
 * @return 错误码
 * 0 成功
 * 1:图片识别失败
 */
PictureAnalysis::Error PictureAnalysis::SegmentPaperRotateCut(cv::Mat& srcMat, TestPaperStrt &paper, cv::OutputArray dstMat, cv::OutputArray dst_thresh_mat)
{
    bool pictureAnalysisDebug = SystemSetDao::instance()->getPictureAnalysisDebug();
    TestPaperModel& paperParam = paper.paperParam;
    double mmPixel= paperParam.getPaperMmToPixel();
    // 段宽度
    double segmentMinWidth = paperParam.getTestBlockWidth() * mmPixel;
    // 膜条高度
    double totalHeigth = paperParam.getPaperHeight() * mmPixel;
    // 图片二值化阈值
    int thresh = paperParam.getPaperBinarizationThreshold();
    // 按照物理设计切图, 膜条只可能在这个范围
    cv::Rect positionEdge(static_cast<int>(srcMat.cols * 0.08), static_cast<int>(srcMat.rows*0.25),
                      static_cast<int>(srcMat.cols*0.8), static_cast<int>(srcMat.rows*0.5));
    maskOutsideRect(srcMat, positionEdge);
    if(pictureAnalysisDebug)
    {
        QString postionPath = paper.pictureAnalysisPath + paper.sampleId + "-position.png";
        cv::imwrite(postionPath.toStdString(), srcMat);
    }
    // 将反光区域处理
    cv::Mat lightMask;
    cv::threshold(srcMat, lightMask, 250, 255, cv::THRESH_BINARY);

     // 消除噪声点
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5));
    cv::morphologyEx(lightMask, lightMask, cv::MORPH_CLOSE, kernel);
    // 创建黑色替代区域
    cv::Mat black_area = cv::Mat::zeros(srcMat.size(), srcMat.type());
    // 过滤曝光
    cv::Mat noExposureMat = srcMat.clone();
    // 融合图像（仅替换过曝区域）
    noExposureMat.setTo(cv::Scalar(0, 0, 0), lightMask);
    noExposureMat.copyTo(black_area, ~lightMask);  // 反转掩膜
    if(pictureAnalysisDebug)
    {
        // 保存的分析图片
        QString lightPath = paper.pictureAnalysisPath + paper.sampleId + "-nolight.png";
        cv::imwrite(lightPath.toStdString(), noExposureMat);
    }

    cv::Mat threshMat;
    cv::threshold(noExposureMat, threshMat, thresh, 255, THRESH_BINARY);
    if(pictureAnalysisDebug)
    {
        // 保存二值化后的图像
        QString threshPath = paper.pictureAnalysisPath + paper.sampleId + "-thresh.png";
        cv::imwrite(threshPath.toStdString(), threshMat);
    }

    Mat erodedMat;
    {
        // 腐蚀
        Mat eroded_kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        erode(threshMat, erodedMat, eroded_kernel);
        if(pictureAnalysisDebug)
        {
            //保存腐蚀后的图片
            QString erodedPath = paper.pictureAnalysisPath + paper.sampleId + "-eroded.png";
            cv::imwrite(erodedPath.toStdString(), erodedMat);
        }

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
//            qDebug()<<"rect"<<rect.width<<rect.height<<segmentMinWidth<<totalHeigth;
            // TODO::WANGZ
            if (rect.width < segmentMinWidth/3*2 || rect.height < totalHeigth/3*2)
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
        if(pictureAnalysisDebug)
        {
            //保存膨胀后圈出的轮廓
            QString maxRectPath = paper.pictureAnalysisPath + paper.sampleId + "-maxRect.png";
            cv::imwrite(maxRectPath.toStdString(), maxRectMat);
        }

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
        if(pictureAnalysisDebug)
        {
            //保存膨胀后圈出的轮廓
            QString maxRectPath = paper.pictureAnalysisPath + paper.sampleId + "-maxRect1.png";
            cv::imwrite(maxRectPath.toStdString(), maxRectMat);
        }

    }

    // 灰度图像也做相同旋转，与二值化的图像保持一致
    cv::Mat saveRotMat;
    cv::warpAffine(srcMat, saveRotMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘

    cv::Mat grayRotMat;
    cv::warpAffine(noExposureMat, grayRotMat, rotMat, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0,0)); // 黑色填充边缘

    // 开始去噪声，仅对上下边界，目的是精细化边界位置
    int top = -1, bottom = -1;
    cv::Mat maxGrayMat = grayRotMat(maxRect);
    if(pictureAnalysisDebug)
    {
        //  保存灰度图片
        QString maxGrayMatPath = paper.pictureAnalysisPath + paper.sampleId + "-maxGrayMat.png";
        cv::imwrite(maxGrayMatPath.toStdString(), maxGrayMat);
    }

    double edgeThresh = cv::mean(maxGrayMat)[0];
//    qDebug()<<"edgeThresh = "<<edgeThresh;
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
//    qDebug()<<"top = "<<top << "bottom = " << bottom << "totalHeight = "<<totalHeigth;
    if(top < 0 || bottom < 0 || bottom - top < totalHeigth * 0.5)
    {
        return Error::ContourNotFound;
    }
//    qDebug() << edgeThresh << top << bottom;

    {
        // 剪裁膜条并保存
        double yPercent = 1;
        double yCenter = maxRect.y + top + (bottom - top)/2;
        double cutHeight = totalHeigth * yPercent;
        cv::Rect lastEdge(maxRect.x, static_cast<int>(yCenter - cutHeight / 2), maxRect.width, static_cast<int>(cutHeight));
        cv::Mat croppedMat = saveRotMat(lastEdge);
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
        if(pictureAnalysisDebug)
        {
            //剪裁后的图片保存
            QString croppedPath1 = paper.pictureAnalysisPath + paper.sampleId + "-1.png";
            cv::imwrite(croppedPath1.toStdString(), croppedMat1);
        }

        croppedMat1.copyTo(dst_thresh_mat);
    }
    return Error::NoError;
}

#include <vector>
#include <algorithm>
#include <opencv2/core.hpp>

/**
 * @brief 将 Rect 按水平间距分组
 * @param rects  输入矩形列表
 * @param span   分组阈值：相邻矩形右边界到左边界的距离 < span 时归为同一组
 * @return       分组后的二维数组
 */
std::vector<std::vector<cv::Rect>> PictureAnalysis::groupRectsByHorizontalSpan(const std::vector<cv::Rect>& sorted_rects, int span)
{
    std::vector<std::vector<cv::Rect>> groups;
    if (sorted_rects.empty()) return groups;

    // 遍历分组
    std::vector<cv::Rect> current_group;
    current_group.reserve(sorted_rects.size());
    current_group.push_back(sorted_rects[0]);

    for (size_t i = 1; i < sorted_rects.size(); ++i) {
        const cv::Rect& prev = sorted_rects[i-1];
        const cv::Rect& curr = sorted_rects[i];

        // 计算水平间距：当前左边界 - 上一个右边界
        // 重叠时 gap 为负数，自然满足 < span，会被归入同组（符合直觉）
        int gap = curr.x - (prev.x + prev.width);

        if (gap < span) {
            current_group.push_back(curr);
        } else {
            // 间距过大 → 当前组结束，移入结果集
            groups.emplace_back(std::move(current_group));
            // 复用已分配的内存，开启新组
            current_group.clear();
            current_group.push_back(curr);
        }
    }
    // 存入最后一组
    if (!current_group.empty()) {
        groups.emplace_back(std::move(current_group));
    }

    return groups;
}

struct BlockCandidate {
    size_t startIdx;     // 原始 rects 起始索引
    size_t endIdx;       // 原始 rects 结束索引
    cv::Rect rect;    // 合并后的几何矩形
    double score;     // 综合得分

    // 用于 DP 回溯
    int prevBestIdx;  // 前一个最佳块的索引
};

/**
 * @brief 基于滑动窗口/区间DP的思想
    预处理：计算每个原始矩形的得分。
    生成候选块：只保留那些宽度在 [minWidth, maxWidth] 范围内的连续子序列作为“候选块”。记录它们的起始索引、结束索引、合并后的 Rect 和平均分。
    选择最佳组合：
    如果只需要 1 个块：直接取平均分最高的候选块。
    如果需要 2 个块：遍历所有合法的“左块”，然后在它右侧寻找不重叠且满足 blockSpan 间距的“右块”，求两者得分之和的最大值。
 * @param src
 * @param rects
 * @param blockWidth
 * @return
 */


std::vector<cv::Rect> PictureAnalysis::findTopKBlocks(
    const cv::Mat& src,
    const std::vector<cv::Rect>& sortedRects,
    size_t K,                // 目标块数量，例如 13
    int expectedBlockWidth,
    int minGap,           // 块之间的最小间距
    int binarizationThresh)
{
    std::vector<cv::Rect> results;
    if (sortedRects.empty() || K <= 0) return results;

    size_t N = sortedRects.size();

    // 2. 预计算每个矩形的密度得分 (0.0 ~ 1.0)
    std::vector<double> densityScores(N, 0.0);
    cv::Rect imgBounds(0, 0, src.cols, src.rows);
    for (size_t i = 0; i < N; ++i) {
        cv::Rect roi = sortedRects[i] & imgBounds;
        if (roi.area() > 0) {
            cv::Mat sub = src(roi);
            double nonZero = cv::countNonZero(sub > binarizationThresh);
            densityScores[i] = nonZero / static_cast<double>(sub.total());
        }
    }

    // 3. 生成所有合法的“候选块”
    // 合法定义：宽度在 [0.8*W, 1.2*W] 之间，且由连续的 rects 组成
    std::vector<BlockCandidate> candidates;
    double minWidth = expectedBlockWidth * 0.8;
    double maxWidth = expectedBlockWidth * 1.2;

    for (size_t i = 0; i < N; ++i) {
        int minX = sortedRects[i].x;
        int maxX = sortedRects[i].x + sortedRects[i].width;
        int minY = sortedRects[i].y;
        int maxY = sortedRects[i].y + sortedRects[i].height;

        double sumDensity = 0.0;

        for (size_t j = i; j < N; ++j) {
            // 更新边界
            minX = std::min(minX, sortedRects[j].x);
            maxX = std::max(maxX, sortedRects[j].x + sortedRects[j].width);
            minY = std::min(minY, sortedRects[j].y);
            maxY = std::max(maxY, sortedRects[j].y + sortedRects[j].height);

            sumDensity += densityScores[j];

            int width = maxX - minX;
            if (width > maxWidth) break; // 剪枝：太宽了，后续 j 只会更宽

            if (width >= minWidth) {
                // 计算得分：
                // 1. 宽度契合度：越接近 expectedBlockWidth 越好
                double widthDiff = std::abs(width - expectedBlockWidth);
                double widthScore = 1.0 - (widthDiff / expectedBlockWidth);
                widthScore = std::max(0.0, widthScore); // 防止负数

                // 2. 平均密度
                double avgDensity = sumDensity / (j - i + 1);
                qDebug()<<"avgDensity"<<i<<j<<avgDensity;

                // 3. 综合得分 (权重可根据实际效果调整)
                double finalScore = avgDensity;// widthScore * 0.6 + avgDensity * 0.4;

                // 只有得分高于某个阈值才加入候选，避免太多垃圾候选
                if (finalScore > 0.3) {
                    cv::Rect r(minX, minY, width, maxY - minY);
                    candidates.push_back({i, j, r, finalScore, -1});
                }
            }
        }
    }

    if (candidates.empty()) return results;

    // 4. 动态规划 (DP) 寻找 K 个最佳不重叠块
    // dp[k][i] 表示：选了 k 个块，且第 k 个块是 candidates[i] 时的最大总得分
    // 由于 K=13 较小，我们可以用滚动数组或二维 vector

    // 为了节省内存，我们只记录路径
    // Structure: bestScoreForCount[i] -> map<candidateIndex, totalScore>
    // 这里简化为：对每个 candidate，记录它作为第 m 个块时的最佳前驱

    // 初始化 DP 表
    // dp[m][c_idx] = max total score using m blocks ending with candidate c_idx
    std::vector<std::vector<double>> dp(static_cast<size_t>(K + 1), std::vector<double>(candidates.size(), -1.0));
    std::vector<std::vector<int>> parent(static_cast<size_t>(K + 1), std::vector<int>(candidates.size(), -1));

    // Base case: m = 1
    for (size_t c = 0; c < candidates.size(); ++c) {
        dp[1][c] = candidates[c].score;
    }

    // Transition: m = 2 to K
    for (size_t m = 2; m <= K; ++m) {
        for (size_t curr = 0; curr < candidates.size(); ++curr) {
            const auto& currCand = candidates[curr];
            double bestPrevScore = -1.0;
            int bestPrevIdx = -1;

            // 遍历所有可能的前一个块 prev
            for (size_t prev = 0; prev < curr; ++prev) {
                const auto& prevCand = candidates[prev];

                // 约束 1: 索引不重叠
                if (prevCand.endIdx >= currCand.startIdx) continue;

//                 约束 2: 几何间距 >= minGap
                int gap = currCand.rect.x - (prevCand.rect.x + prevCand.rect.width);
                if (gap < minGap) continue;

                // 如果前一个状态不可达，跳过
                if (dp[m-1][prev] < 0) continue;

                double total = dp[m-1][prev] + currCand.score;
                if (total > bestPrevScore) {
                    bestPrevScore = total;
                    bestPrevIdx = static_cast<int>(prev);
                }
            }

            if (bestPrevScore > 0) {
                dp[m][curr] = bestPrevScore;
                parent[m][curr] = bestPrevIdx;
            }
        }
    }

    // 5. 回溯找到最佳路径
    // 找到第 K 个块中得分最高的那个
    double maxFinalScore = -1.0;
    int lastCandIdx = -1;

    for (size_t c = 0; c < candidates.size(); ++c) {
        if (dp[K][c] > maxFinalScore) {
            maxFinalScore = dp[K][c];
            lastCandIdx = static_cast<int>(c);
        }
    }

    if (lastCandIdx == -1) {
        qDebug() << "Could not find" << K << "valid blocks. Falling back to greedy top-K.";
        // 降级策略：如果 DP 找不到完整的 K 个，直接取分数最高的 K 个不重叠候选（简单贪心）
        // 这里省略降级代码，直接返回空或部分结果
        return results;
    }

    // 回溯
    std::vector<cv::Rect> finalBlocks;
    int currentIdx = lastCandIdx;
    for (size_t m = K; m >= 1; --m) {
        finalBlocks.push_back(candidates[static_cast<size_t>(currentIdx)].rect);
        currentIdx = parent[m][static_cast<size_t>(currentIdx)];
    }

    // 反转，因为是从后往前找的
    std::reverse(finalBlocks.begin(), finalBlocks.end());

    return finalBlocks;
}


/**
 * @brief 查找轮廓, 并根据轮廓灰度均值切分轮廓
 * @return
 */
std::vector<cv::Rect> PictureAnalysis::SegmentationContourFind(const cv::Mat& srcMat, const cv::Mat& threshMat, TestPaperStrt &paper, const QString& path)
{
    bool pictureAnalysisDebug = SystemSetDao::instance()->getPictureAnalysisDebug();
    TestPaperModel& paperParam = paper.paperParam;
    double mmPixel= paperParam.getPaperMmToPixel();
    int lineWidth = static_cast<int>(paperParam.getItemLineWidth() * mmPixel);
    int segmentMinWidth = static_cast<int>(paperParam.getTestBlockWidth() * mmPixel);

    cv::Mat contourMarkMat1 = srcMat.clone();
    cv::Mat contourMarkMat2 = srcMat.clone();

    std::vector<cv::Rect> last_rects;
    std::vector<std::vector<Point>> contours;
    findContours(threshMat, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    sort(contours.begin(), contours.end(), [](auto& a, auto& b) { return boundingRect(a).x < boundingRect(b).x; });
    if(contours.empty())
    {
        return last_rects;
    }
    // 对每一个轮廓进行再处理
    for(auto& contour : contours)
    {
        cv::Rect rect = cv::boundingRect(contour);
        if(rect.height < srcMat.rows * 0.75 || rect.width < segmentMinWidth/5)
        {
            qDebug()<<"contours"<<rect.height<<srcMat.rows<<rect.width<<lineWidth;
            continue;
        }
        cv::rectangle(contourMarkMat1, rect, cv::Scalar(255,0,0), 1);
        if(rect.width < lineWidth) continue;
        int cut_thresh = static_cast<int>(cv::mean(srcMat(rect))[0]*0.8);
        qDebug()<<"cut_thresh"<<cut_thresh;
        int recordX = 0;
        int startX = 0;
        bool foundStart = false;
        for(int i = 0; i < rect.width - 3; i++)
        {
            startX = rect.x + i;
            cv::Rect roi(startX, rect.y, 3, rect.height);
            double avg = cv::mean(srcMat(roi))[0];
            if(avg >= cut_thresh)
            {
                if(!foundStart)
                {
                    foundStart = true;
                    recordX = startX;
                }
            }else
            {
                if(foundStart)
                {
                    cv::Rect refinedRect(recordX, rect.y, startX - recordX, rect.height);
                    last_rects.push_back(refinedRect);
                    cv::rectangle(contourMarkMat2, refinedRect, cv::Scalar(255,0,0), 1);
                    foundStart = false;
                }
            }
        }
        if(foundStart)
        {
            cv::Rect refinedRect(recordX, rect.y, rect.x + rect.width - recordX, rect.height);
            last_rects.push_back(refinedRect);
            cv::rectangle(contourMarkMat2, refinedRect, cv::Scalar(255,0,0), 1);
        }
    }
    if(pictureAnalysisDebug)
    {
        QString inflatePath1 = path;
        inflatePath1 = inflatePath1 + +"/" + "analysised" + "/" + paper.sampleId + "-contourMarkMat1.png";
        cv::imwrite(inflatePath1.toStdString(), contourMarkMat1);

        QString inflatePath2 = path;
        inflatePath2 = inflatePath2 + +"/" + "analysised" + "/" + paper.sampleId + "-contourMarkMat2.png";
        cv::imwrite(inflatePath2.toStdString(), contourMarkMat2);
    }
    return last_rects;
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
    bool pictureAnalysisDebug = SystemSetDao::instance()->getPictureAnalysisDebug();
    TestPaperModel& paperParam = paper.paperParam;
    // 图片二值化阈值
    int paperBinarizationThresh = paperParam.getPaperBinarizationThreshold();
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
    int segmentMinWidth = static_cast<int>(paperParam.getTestBlockWidth() * mmPixel);
    int segmentMinSpan = static_cast<int>(1.2 * mmPixel);//paperParam.getTestBlockSpace()
    int headWidth = static_cast<int>(paperParam.getIgnoreHeadLenght() * mmPixel);
    // 获取分段总数
    int segCnt = paperParam.getTotalNumber();
    if(srcMat.cols < headWidth)
    {
//        qDebug()<<"headWidth"<<srcMat.cols<<headWidth;
        return Error::ConfigError;
    }
    // 处理头
    cv::Mat targetRegion = threshMat.colRange(0, headWidth);
    // 将头设置为黑色
    targetRegion.setTo(cv::Scalar(0));
    //
    if(pictureAnalysisDebug)
    {
        QString noHeadPath = path;
        noHeadPath = noHeadPath + +"/" + "analysised" + "/" + paper.sampleId + "-nohead.png";
        cv::imwrite(noHeadPath.toStdString(), threshMat);
    }

    // 查找轮廓
    auto last_rects = SegmentationContourFind(srcMat, threshMat, paper, path);

    // 将块间距小于指定值的进行分组
    // 轮廓合并
    vector<cv::Rect> mergeRects = findTopKBlocks(srcMat, last_rects, static_cast<size_t>(segCnt), segmentMinWidth, segmentMinSpan, paperBinarizationThresh);
    if(static_cast<int>(mergeRects.size()) != segCnt)
    {
        return Error::DetectSegmentCntError;
    }
    cv::Mat contourMarkMat3 = srcMat.clone();
    for(const auto& merge:mergeRects)
    {
        cv::rectangle(contourMarkMat3, merge, cv::Scalar(255,0,0), 1);
        paper.segmentResultVect.push_back(TestPaperSegmentResult(merge.x + merge.width/2, merge.width));
    }
    if(pictureAnalysisDebug)
    {
        QString inflatePath3 = path;
        inflatePath3 = inflatePath3 + +"/" + "analysised" + "/" + paper.sampleId + "-contourMarkMat3.png";
        cv::imwrite(inflatePath3.toStdString(), contourMarkMat3);
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
    double mmPixel= paperParam.getPaperMmToPixel();
    int resultIdx = 0;
    for (int segmentIndex : itemsBySegment.keys())
    {
        const QVector<ItemModel>& itemVectOnSegment = itemsBySegment[segmentIndex];
        int itemCntOnSegment = itemVectOnSegment.size();
        if(itemCntOnSegment == 0) continue;
        int segNo = segmentIndex - 1;
        if(segNo < 0) continue;
        int center = static_cast<int>(paper.segmentResultVect[segNo]._center);
        int totalScanWidth = static_cast<int>(paper.segmentResultVect[segNo]._width * 0.9);
        int itemScanWidth = static_cast<int>(1.0 * totalScanWidth / itemCntOnSegment);

        for(const ItemModel& item:itemVectOnSegment)
        {
            if(resultIdx >= paper.itemResultVect.count())
            {
                err = err == Error::NoError ? Error::SegmentSetError : err;
                continue;
            }
            TestPaperItemResult& itemResult = paper.itemResultVect[resultIdx++]; // 结果计算
            if(segmentIndex < 1)
            {
                err = err == Error::NoError ? Error::SegmentSetError : err;
                continue;
            }
            int positionNo = item.getPositionNo() - 1;
            // 项目范围线的起始点
            int limitStart = static_cast<int>(center - totalScanWidth/2 + positionNo * itemScanWidth);
            int limitWidth = itemScanWidth;
            cv::Rect calcRect(limitStart, 0,  limitWidth, cutMat.rows);
            cv::Mat calMat = cutMat(calcRect);
            Error calcCode = OneItemParse(calMat, itemResult, static_cast<int>(paperParam.getItemAnalysisWidth()*mmPixel), blackDetectThreshold);
            err = err == Error::NoError ? calcCode : err;
            // 功能线判定
            if(item.getItemType() == 0 && itemResult.grayValue > paperParam.getFuncGrayThreshold())
            {
                err = err == Error::NoError ? Error::FuncLineError : err;
            }
            if(item.getItemType() == 1 && itemResult.grayValue > paperParam.getCutOffThreshold())
            {
                err = err == Error::NoError? Error::CutOffLineError : err;
            }

            itemResult.lineCenter += limitStart;
            double finaleGrayValue = itemResult.grayValue;
            finaleGrayValue = finaleGrayValue < 0 ? 0 : finaleGrayValue;
            // 保存解析后的灰度值
            itemResult.grayValue = finaleGrayValue;
//            qDebug() << "result " << itemResult.lineCenter << itemResult.lineWidth << itemResult.grayValue << itemResult.backgroundGrayValue << itemResult.backgroundGrayValue-itemResult.grayValue;
            // 可视化项目线
            cv::Rect roi(itemResult.lineCenter - itemResult.lineWidth/2, 0, itemResult.lineWidth, cutMat.rows);
            cv::rectangle(drawMat, roi, cv::Scalar(0,0,0), 1);
            // 画范围线
            cv::Rect roi1(limitStart, 0, limitWidth, 2);
            cv::rectangle(drawMat, roi1, cv::Scalar(0,0,0), 2);
            // 插入位置信息
            bResult = dao->InsertOrUpdate_tresult_left_right_pixp(paper.testId, static_cast<int>(itemIdx), limitStart, limitStart+limitWidth, item.getItemName(), 0, 2 );
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
    double totalLenght = paperParam.getPaperLenght() * mmPixel;
//    qDebug()<<"totalHeight"<<paperParam.getPaperHeight()<<paperParam.getPaperLenght()<<mmPixel;
    // 是否超出设定值判定函数
    auto isOutOfRange = [](double value, double min, double max)
    {
        return value < min || value > max;
    };

    if(isOutOfRange(yPercent, 0.4, 1))
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
    /* 保存二值化图像
    QString threshPath = paper.pictureAnalysisPath + paper.sampleId + "-thresh.png";
    cv::imwrite(threshPath.toStdString(), threshMat);*/

    Mat erodedMat;
    {
        // 腐蚀操作,过滤噪点
        Mat eroded_kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        erode(threshMat, erodedMat, eroded_kernel);
        /*保存腐蚀后的图片
        QString erodedPath = paper.pictureAnalysisPath + paper.sampleId + "-eroded.png";
        cv::imwrite(erodedPath.toStdString(), erodedMat);*/

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
        /*保存腐蚀后的图片
        QString erodedPath1 = paper.pictureAnalysisPath + paper.sampleId + "-eroded1.png";
        cv::imwrite(erodedPath1.toStdString(), erodedMat);*/
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
        /*保存图片膨胀后的图片保存
        QString mergedPath = paper.pictureAnalysisPath + paper.sampleId + "-merge.png";
        cv::imwrite(mergedPath.toStdString(), mergedMat);*/

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
        /* 保存二值化后的图像
        QString rotPath = paper.pictureAnalysisPath + paper.sampleId + "-roted.png";
        cv::imwrite(rotPath.toStdString(), rotedMat);*/

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
        /* 保存二值化后的图像
        QString edgePath = paper.pictureAnalysisPath + paper.sampleId + "-edgePath.png";
        cv::imwrite(edgePath.toStdString(), edgeMat);*/
//        qDebug()<<"edgeMat"<<edgeMat.cols<<edgeMat.rows<<totalLenght<<totalHeight;
        if(edgeMat.cols < totalLenght * 0.9 || edgeMat.rows < totalHeight * 0.9)
        {
            return Error::DetectPictureSizeError;
        }
    }

    if(edgeMat.cols/2 <= 3)
    {
        return Error::ContourNotFound;
    }
    // 重新确定边缘
    int xStart = -1, xEnd = -1,  yTop = -1, yBottom = -1;
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
    //按照3个像素的宽度，精细尾端位置
    for(int i = 0; i < edgeMat.cols/2-3;i++)
    {
        // x起始坐标，y起始坐标，提取宽度，提取高度
        cv::Rect roi(edgeMat.cols-i-3, 0, 3, edgeMat.rows);
        cv::Mat tempMat = edgeMat(roi);
        if(cv::mean(tempMat)[0] >= head_thresh)
        {
            xEnd = i;
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
    if(xStart == -1 || xEnd == -1 || yTop == -1 || yBottom == -1)
    {
        return Error::ContourNotFound;
    }
    // 修改边缘值
    edge.x += xStart;
    edge.y += yTop;
    edge.width = edgeMat.cols - xStart - xEnd;
    edge.height = edgeMat.rows - yTop - yBottom;
    if(edge.x<0 || edge.y<0 || edge.width<0 || edge.height<0)
    {
        return Error::ContourNotFound;
    }
    /* 二值化裁剪图片
    QString threshCutPath = paper.pictureAnalysisPath + paper.sampleId + "-threshCut.png";
    cv::imwrite(threshCutPath.toStdString(), rotedErodedMat(edge));*/

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
    // 修正膨胀参数
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

    //剪裁后的图片保存
    cv::Mat drawMat = grayRotMat(cv::Rect(edge.x+reEdgeStart, edge.y, edge.width-reEdgeStart, edge.height));
    QString drawPath = paper.pictureAnalysisPath + paper.sampleId + ".png";
    cv::imwrite(drawPath.toStdString(), drawMat);

//    qDebug()<<"drawMat"<<drawMat.cols<<drawMat.rows<<totalLenght<<totalHeight;
    if(drawMat.cols < totalLenght * 0.9 ||
            isOutOfRange(drawMat.rows, totalHeight * 0.8, totalHeight*2))
    {
        return Error::DetectPictureSizeError;
    }

    cv::Rect reroi(reEdgeStart, 0, croppedMat.cols-reEdgeStart, croppedMat.rows);
    cv::Mat reCroppedMat = croppedMat(reroi);
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
    Error err = Error::NoError;
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
    int markLineLimitStart = 0;
    cv::Mat markLimitMat;
    // 从头端开始查找
    if(paperParam.getFuncFindDir() == TestPaperModel::PAPER_FUNC_FIND_DIR_HEAD)
    {
        markLineLimitStart = positionList[0] - funcLineLimit/2;
        markLineLimitStart = markLineLimitStart < 0 ? 0:markLineLimitStart;
        if(markLineLimitStart+funcLineLimit>=srcMat.cols)
        {
            return Error::ConfigError;
        }
    }else
    {
        markLineLimitStart = srcMat.cols + positionList[0] - funcLineLimit/2;
//        qDebug()<<"markLineLimitStart"<<markLineLimitStart<<srcMat.cols<<positionList[0]<<funcLineLimit;
        if(markLineLimitStart < 0 || markLineLimitStart+funcLineLimit>=srcMat.cols)
        {
            return Error::ConfigError;
        }
    }
    // 定义提取区域：
    // 功能线的提取范围可以更大一些
    cv::Rect roi(markLineLimitStart, 0, funcLineLimit, srcMat.rows);
    markLimitMat = srcMat(roi);

    /*保存标记线图片
    cv::Mat cloneMat = markLimitMat.clone();
    QString path3 = paper.pictureAnalysisPath + paper.sampleId + "-marklimit.png";
    cv::imwrite(path3.toStdString(), cloneMat);*/

    //  计算每个轮廓区域的灰度均值
    double markMatGray = 255;
    cv::Rect markRect;
    for (int i = 0; i < markLimitMat.cols - lineWidth; i++)
    {
        cv::Rect tempRect(i, 0, lineWidth, markLimitMat.rows);
        cv::Mat tempMat = markLimitMat(tempRect);
        double meanGray = cv::mean(tempMat)[0];
        if(meanGray < markMatGray)
        {
            markRect = tempRect;
            markMatGray = meanGray;
        }
    }
   if (markMatGray > paperParam.getFuncGrayThreshold())
    {
        return Error::FuncLineError;
    }
   /*保存标记线图片
   cv::rectangle(cloneMat, markRect, cv::Scalar(255,255,255), 2);
   QString path4 = paper.pictureAnalysisPath + paper.sampleId + "-marklimit1.png";
   cv::imwrite(path4.toStdString(), cloneMat);*/
   {
        // 功能线 解析结果保存
        TestPaperItemResult& result = paper.itemResultVect[0];
        result.grayValue = markMatGray;
        result.lineCenter = markLineLimitStart + markRect.x + markRect.width/2;
        result.lineWidth = markRect.width;
        result.backgroundGrayValue = 255;
    }

    // 标记线中心点在膜条中的位置
    markLineXCenter = markLineLimitStart + markRect.x + markRect.width/2;
    for(int i = 1; i < lineCenterRelArraySize; i++)
    {
        TestPaperItemResult& result = paper.itemResultVect[i];
        // 项目范围线的起始点
        int limitStart = markLineXCenter + positionList[i] - lineLimit/2;
        cv::Rect roi(limitStart, 0,  lineLimit, srcMat.rows );
        cv::Mat calMat = srcMat(roi);
        // 处理计算时的错误码，并不中断其他项目的计算
        Error calcCode = OneItemParse(calMat, result, static_cast<int>(paperParam.getItemAnalysisWidth()*mmPixel), static_cast<int>(paperParam.getBlackPointDetectThreshold()));
         err = err == Error::NoError ? calcCode : err;
        ItemModel& item = paper.itemParamVect[i];
        if(item.getItemType() == 1 && result.grayValue > paperParam.getCutOffThreshold())
        {
            err = err == Error::NoError ? Error::CutOffLineError:err;
        }
        result.lineCenter += limitStart;
//        qDebug() << "result " << result.lineCenter << result.lineWidth << result.grayValue<<result.backgroundGrayValue << result.backgroundGrayValue-result.grayValue;
    }

    cv::Mat drawMat = srcMat.clone();
    auto dao = AnalysisDao::instance();
    bool bResult;
    // 根据返回值进行划线
    for(int i = 0; i < lineCenterRelArraySize; i++)
    {
        TestPaperItemResult& result = paper.itemResultVect[i];
//        qDebug()<<"result.lineCenter"<<result.lineCenter<<result.lineWidth<<srcMat.rows;
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
            bResult = dao->InsertOrUpdate_tresult_left_right_pixp(paper.sampleId, 0, xstart, xstart+width, itemName, 0,2 );
        }else
        {
            int xstart = markLineXCenter + positionList[static_cast<int>(i)] - lineLimit/2;
            cv::Rect roi1(xstart, 0, lineLimit, 2);
            cv::rectangle(drawMat, roi1, cv::Scalar(0,0,0), 2);
            bResult = dao->InsertOrUpdate_tresult_left_right_pixp(paper.sampleId, 0, xstart, xstart+lineLimit, itemName, 0,2 );
        }
    }

    // 保存最终的分析图片
    QString path = paper.pictureAnalysisPath + paper.sampleId + "-last.png";
    cv::imwrite(path.toStdString(), drawMat);
    return err;
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
    return err;
}


QString PictureAnalysis::CaculateResultText(double dItemGrayRatio, const int ruleId)
{
    QString testResult = "";
    QMap<double, QString> mapJudgeRules = JudgeDao::instance()->getJudgeValueMap(ruleId);
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
