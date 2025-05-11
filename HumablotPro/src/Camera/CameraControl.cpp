#include "..\Include\Precomp\precompile.h"
#include "CameraControl.h"
#include <QSettings>
#include <QMessageBox>
#include <QMutex>
#include <QDir>
#include <iostream>
#include "RGBConvert.h"
#include "src/comm/GlobalData.h"
#include "CameraParametersSet.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Media/ImageConvert.h"

#include "../main/CreateDump.h" 

#define DEFAULT_SHOW_RATE 4

using namespace std;
using namespace cv;

GENICAM_Camera *pCamera = 0;			            /* 相机对象 */
GENICAM_StreamSource *pStreamSource = 0;            /* 流对象 */
QMutex					m_mutexQue;					/* 队列锁 */
std::list<FrameBufferSPtr>  m_displayQue;           /* 显示队列 */

void sobelCallback(int state, void* userData);

void onGetFrame(GENICAM_Frame* pFrame);

void addConvertedImage(const FrameBufferSPtr& sptrConvertedImage);

FrameBufferSPtr getConvertedImage();

void sobelCallback(int state, void* userData)
{

}
/* 图像数据回调 */
static void onGetFrame(GENICAM_Frame* pFrame)
{
	/* 判断数据帧的有效性 */
	bool isValid = pFrame->valid(pFrame);
	if (0 != isValid)
	{
		//TRACE("frame is invalid!\n");
		return;
	}
	else
	{
		uint64_t blockId = pFrame->getBlockId(pFrame);
		//TRACE("blockId = %d.\n", blockId);
	}

	/* 转码 */
	FrameBufferSPtr sptrConvertFrameBuffer;
	if (ConvertToBGR24(pFrame, sptrConvertFrameBuffer))
	{
		addConvertedImage(sptrConvertFrameBuffer);
	}

	pFrame->release(pFrame);
	return;
}

/* 添加一张图片到队列中 */
static void addConvertedImage(const FrameBufferSPtr& sptrConvertedImage)
{
	m_mutexQue.lock();
	if (m_displayQue.size() >= DEFAULT_SHOW_RATE)
	{
		m_displayQue.pop_front();
	}
	m_displayQue.push_back(sptrConvertedImage);
	m_mutexQue.unlock();
}

/* 从队列获取一张图片 */
static FrameBufferSPtr getConvertedImage()
{
	FrameBufferSPtr sptrConvertedImage;
	m_mutexQue.lock();

	if (!m_displayQue.empty())
	{
		sptrConvertedImage = m_displayQue.front();
		m_displayQue.pop_front();
	}

	m_mutexQue.unlock();
	return sptrConvertedImage;
}

CameraControl::CameraControl(QObject *parent)
	: QObject(parent)
{
}

CameraControl::~CameraControl()
{
}

int32_t CameraControl::CreateStreamSource(GENICAM_Camera *pGetCamera, GENICAM_StreamSource **ppStreamSource)
{
	int32_t isCreateStreamSource;
	GENICAM_StreamSourceInfo stStreamSourceInfo;

	stStreamSourceInfo.channelId = 0;
	stStreamSourceInfo.pCamera = pGetCamera;

	isCreateStreamSource = GENICAM_createStreamSource(&stStreamSourceInfo, ppStreamSource);

	if (isCreateStreamSource != 0)
	{
		//printf("create stream obj  fail.\r\n");
		return -1;
	}

	return 0;
}
bool CameraControl::OpenCamera()
{
	/* 发现设备 */
	GENICAM_System *pSystem;
	GENICAM_Camera *pCameraList;
	uint32_t cameraCnt = -1;
	pCameraList = new GENICAM_Camera();

	int32_t ret;
	ret = GENICAM_getSystemInstance(&pSystem);
	if (ret != 0)
	{
		pSystem->release(pSystem); //释放资源
		pCameraList->release(pCameraList);
		//TRACE("pSystem is null.\r\n");
		return false;
	}
	ret = pSystem->discovery(pSystem, &pCameraList, &cameraCnt, typeAll);//发现相机，获得相机列表
	if (ret != 0)
	{
		//TRACE("discovery device fail.\r\n");
		return  false;
	}
	if (cameraCnt < 1)
	{
		//TRACE("there is no device.\r\n");
		return  false;
	}

	pCamera = &pCameraList[0]; //此示例默认获取相机列表里第一个相机

	if (pCamera == NULL)
	{
		return false;
	};

	/* 连接设备 */
	ret = pCamera->connect(pCamera, accessPermissionControl);

	if (ret != 0)
	{
		//TRACE("connect camera failed.\n");
		return false;
	}

	//设置相机参数
	CameraParametersSet cameraParametersSet(this);
	cameraParametersSet.SetCameraParameterAll(pCamera);

	/* 创建流对象 */
	ret = CreateStreamSource(pCamera, &pStreamSource);
	if ((ret != 0) || (NULL == pStreamSource))
	{
		//TRACE("create stream obj  fail.\r\n");
		return false;
	}

	pStreamSource->attachGrabbing(pStreamSource, onGetFrame);

	GENICAM_EGrabStrategy eGrabStrategy = grabStrartegySequential;
	ret = pStreamSource->startGrabbing(pStreamSource, 0, eGrabStrategy);
	if (ret != 0)
	{
		//TRACE("StartGrabbing  fail.\n");
		return false;
	}
	pSystem->release(pSystem); //释放资源
	pCameraList->release(pCameraList);
	pSystem = NULL;
	pCameraList = NULL;

	CCreateDump::Instance()->DeclarDumpFile("dumpfile");

}

//void CameraControl::CreateOneImage(int nSampleID, int nTestPaperID, QString test_file_name)
void CameraControl::CreateOneImage(QString nSampleID, int nTestPaperID, QString test_file_name)
{
	bool bResult = true;
    auto dao = AnalysisUIDao::instance();
	QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
	QString original_piture_path = "original";
	//QString strPath = piture_root_str +"\\"+ test_file_name + "\\" + original_piture_path;
	//QString strPathFileName = strPath + "\\" + QString::number(nSampleID) + +"_" + QString::number(nTestPaperID) + ".png";
	QString strPath = piture_root_str + "\\" + original_piture_path;
	QString strPathFileName = strPath + "\\" + test_file_name + ".png";
	// 检查目录是否存在，若不存在则新建
	QDir dir;
	if (!dir.exists(strPath))
	{
		bool res = dir.mkpath(strPath);
	}
	bool bCreate = true;
	std::string wn = "imageshow";
	waitKey(10);
	//得到相机拍的一张图片
	FrameBufferSPtr displayFrame = getConvertedImage();
	//如果得到继续往下处理
	if (!displayFrame)
	{
		return;
	}
	//新建一个窗体显示拍照的图片
	if (bCreate)
	{
		//创建opencv显示窗体
		//namedWindow(wn, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED);
		//resizeWindow(wn, 1000, 800);
		//moveWindow(wn, 0, 0);
		bCreate = false;
	}
	/* 生成cv::mat对象 使用opencv的方式进行显示*/
	if (gvspPixelMono8 == displayFrame->PixelFormat())
	{
		cv::Mat img(Size(displayFrame->Width(), displayFrame->Height()), CV_8U, displayFrame->bufPtr());
		//imshow(wn, img);
		/* 保存图片 */
		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		//imwrite("color.png", img, compression_params);
		imwrite(strPathFileName.toStdString(), img, compression_params);
	}
	else
	{
		cv::Mat img(Size(displayFrame->Width(), displayFrame->Height()), CV_8UC3, displayFrame->bufPtr());
		//imshow(wn, img);
		/* 保存图片 */
		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		imwrite(strPathFileName.toStdString(), img, compression_params);
	}
}

Mat CameraControl::GetOneMat()
{
	cv::Mat img1;
	FrameBufferSPtr displayFrame = getConvertedImage();
	if (!displayFrame)
	{
		return img1;
	}

	/* 生成cv::mat对象 使用opencv的方式进行显示*/
	if (gvspPixelMono8 == displayFrame->PixelFormat())
	{
		cv::Mat img(Size(displayFrame->Width(), displayFrame->Height()), CV_8U, displayFrame->bufPtr());
		return img.clone();
	}
	else
	{
		cv::Mat img(Size(displayFrame->Width(), displayFrame->Height()), CV_8UC3, displayFrame->bufPtr());
		return img.clone();
	}
}

bool CameraControl::CloseCamera() 
{
	/* 停止相机拉流 */
	if (NULL != pStreamSource)
	{
		pStreamSource->stopGrabbing(pStreamSource);
		pStreamSource = NULL;
	}
	if (NULL != pCamera)
	{
		/* 断开设备 */
		if (0 != pCamera->disConnect(pCamera))
		{
			//TRACE("disConnect camera fail.\n");
			return false;
		}
	}
	return true;
}

//更改曝光值
int32_t CameraControl::ModifyCamralExposureTime(GENICAM_Camera *pGetCamera, double exposureTimeValue)
{
	int32_t isExposureTimeSuccess;
	GENICAM_DoubleNode doubleNode;
	GENICAM_AcquisitionControl *pAcquisitionCtrl = nullptr;
	GENICAM_AcquisitionControlInfo acquisitionControlInfo = { nullptr };
	acquisitionControlInfo.pCamera = pGetCamera;
	isExposureTimeSuccess = GENICAM_createAcquisitionControl(&acquisitionControlInfo, &pAcquisitionCtrl);
	if (isExposureTimeSuccess != 0)
	{
		//printf("ExposureTime  fail.\n");
		return -1;
	}
	doubleNode = pAcquisitionCtrl->exposureTime(pAcquisitionCtrl);
	doubleNode.setValue(&doubleNode, (exposureTimeValue));
	if (isExposureTimeSuccess != 0)
	{
		//printf("set exposureTime fail.\n");
		doubleNode.release(&doubleNode);
		return -1;
	}
	isExposureTimeSuccess = doubleNode.getValue(&doubleNode, &exposureTimeValue);
	if (isExposureTimeSuccess != 0)
	{
		//printf("get exposureTime fail.\n");
		pAcquisitionCtrl->release(pAcquisitionCtrl);
		doubleNode.release(&doubleNode);
		return -1;
	}
	else
	{
		pAcquisitionCtrl->release(pAcquisitionCtrl);
		//printf("before change ,exposureTime is %f\n", exposureTimeValue);
	}
	doubleNode.getValue(&doubleNode, &exposureTimeValue);
	if (isExposureTimeSuccess != 0)
	{
		//printf("get exposureTime fail.\n");
		doubleNode.release(&doubleNode);
		return -1;
	}
	else
	{
		//printf("after change ,exposureTime is %f\n", exposureTimeValue);
		doubleNode.release(&doubleNode);
	}
	return 0;
}
