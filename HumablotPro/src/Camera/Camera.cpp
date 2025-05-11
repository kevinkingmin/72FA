#include "..\Include\Precomp\precompile.h"
#include "Camera.h"
#include <QObject>
#include <QDateTime>
#include <QSettings>
#include <QMessageBox>
#include <QMutex>
#include <QDir>
#include <iostream>
#include "../Include/Analysis/analysis.h"
//#include "../Include/Media/ImageConvert.h"
//#include "RGBConvert.h"
#include "src/comm/GlobalData.h"
#include "../utility/TestPaper.h"
#include "../utility/TestPaperManage.h"
#include "../utility/ReagentManager.h"
#include "../utility/TubeManage.h"
#include "CameraControl.h"
#include "CameraParametersSet.h"
#include <QDesktopWidget>
#include <exception>
#include "TestResultDataManage.h"
#include "Render.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Utilities/log.h"



using namespace std;
using namespace cv;




//#define DEFAULT_SHOW_RATE 4
//
//QMutex					m_mutexQue;					/* 队列锁 */
//std::list<FrameBufferSPtr>  m_displayQue;           /* 显示队列 */
//
//
//void sobelCallback(int state, void* userData);
//void onGetFrame(GENICAM_Frame* pFrame);
//void addConvertedImage(const FrameBufferSPtr& sptrConvertedImage);
//FrameBufferSPtr getConvertedImage();
//
//
//
///* 图像数据回调 */
//static void onGetFrame(GENICAM_Frame* pFrame)
//{
//	/* 判断数据帧的有效性 */
//	bool isValid = pFrame->valid(pFrame);
//	if (0 != isValid)
//	{
//		//TRACE("frame is invalid!\n");
//		return;
//	}
//	else
//	{
//		uint64_t blockId = pFrame->getBlockId(pFrame);
//		//TRACE("blockId = %d.\n", blockId);
//	}
//
//	/* 转码 */
//	FrameBufferSPtr sptrConvertFrameBuffer;
//	if (ConvertToBGR24(pFrame, sptrConvertFrameBuffer))
//	{
//		addConvertedImage(sptrConvertFrameBuffer);
//	}
//
//	pFrame->release(pFrame);
//	return;
//}
//
///* 添加一张图片到队列中 */
//static void addConvertedImage(const FrameBufferSPtr& sptrConvertedImage)
//{
//	m_mutexQue.lock();
//	if (m_displayQue.size() >= DEFAULT_SHOW_RATE)
//	{
//		m_displayQue.pop_front();
//	}
//	m_displayQue.push_back(sptrConvertedImage);
//	m_mutexQue.unlock();
//}
//
///* 从队列获取一张图片 */
//static FrameBufferSPtr getConvertedImage()
//{
//	FrameBufferSPtr sptrConvertedImage;
//	m_mutexQue.lock();
//
//	if (!m_displayQue.empty())
//	{
//		sptrConvertedImage = m_displayQue.front();
//		m_displayQue.pop_front();
//	}
//
//	m_mutexQue.unlock();
//	return sptrConvertedImage;
//}

Camera::Camera(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_ShowModal, true);
	//linshi start
	//m_Timer = new QTimer(this);
	//connect(m_Timer, &QTimer::timeout, this, &Camera::updateImage);
	//linshi end

	//InitStateTableWidget();//初始化列表
	QPixmap pix;
	QString image_path = "";
	image_path = QCoreApplication::applicationDirPath() + "/res/testPaperMat.png";
	pix.load(image_path);  //图片路径
	ui.label->setScaledContents(true);//设置图片适应label
	ui.label->resize(650, 45);
	ui.label->setPixmap(pix);
	ui.pushButtonCutImage->setVisible(false);
	ui.PushButton_ResultList->setVisible(false);

	ui.pushButton_Open->setVisible(false);
	ui.pushButton_Display->setVisible(false);
	ui.pushButton_Close->setVisible(false);
	ui.PushButton_PictureAnalysis->setVisible(false);
	ui.PushButton_ResultList->setVisible(false);
	ui.pushButtonCutImage->setVisible(false);
	ui.pushButton_SaveFile->setVisible(false);
	ui.label->setVisible(false);
	/* 启动显示线程 */
	//m_displayThread = std::thread(std::bind(&Camera::DisplayThreadProc, this));
}

//int32_t Camera::CreateStreamSource(GENICAM_Camera *pGetCamera, GENICAM_StreamSource **ppStreamSource)
//{
//	int32_t isCreateStreamSource;
//	GENICAM_StreamSourceInfo stStreamSourceInfo;
//
//
//	stStreamSourceInfo.channelId = 0;
//	stStreamSourceInfo.pCamera = pGetCamera;
//
//	isCreateStreamSource = GENICAM_createStreamSource(&stStreamSourceInfo, ppStreamSource);
//
//	if (isCreateStreamSource != 0)
//	{
//		//printf("create stream obj  fail.\r\n");
//		return -1;
//	}
//
//	return 0;
//}

Camera::~Camera()
{
}

//pushButton_CameraSetting
void Camera::on_pushButton_CameraSetting_clicked()
{
	////设置相机参数
	CameraParametersSet cameraParametersSet(this);
	GENICAM_System *pSystem;
	GENICAM_Camera *pCameraList;

	pCameraList = new GENICAM_Camera();

	uint32_t cameraCnt = -1;
	int32_t ret;
	ret = GENICAM_getSystemInstance(&pSystem);
	if (ret != 0)
	{
		pSystem->release(pSystem); //释放资源
		pCameraList->release(pCameraList);
		//TRACE("pSystem is null.\r\n");
		QString tip = QString("pSystem is null.");
		eLog(tip.toUtf8());
		return;
	}

	ret = pSystem->discovery(pSystem, &pCameraList, &cameraCnt, typeAll);//发现相机，获得相机列表
	
	GENICAM_Camera *pCamera = &pCameraList[0]; //此示例默认获取相机列表里第一个相机
	cameraParametersSet.SetCameraParameterAll(pCamera);
}
void Camera::on_pushButton_Open_clicked()
{
	CameraControl cameraControl(this);
	bool res = cameraControl.OpenCamera();
	if (res == false)
	{
        QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "连接相机失败！", "确定");
		return ;
	}
	m_nFrameRate = cameraControl.m_nFrameRate;
	///* 发现设备 */
	//GENICAM_System *pSystem;
	//GENICAM_Camera *pCameraList;
	//uint32_t cameraCnt = -1;

	//int32_t ret;
	//ret = GENICAM_getSystemInstance(&pSystem);
	//if (ret != 0)
	//{
	//	pSystem->release(pSystem); //释放资源
	//	pCameraList->release(pCameraList);
	//	//TRACE("pSystem is null.\r\n");
	//	return;
	//}
	//ret = pSystem->discovery(pSystem, &pCameraList, &cameraCnt, typeAll);//发现相机，获得相机列表
	//if (ret != 0)
	//{
	//	//TRACE("discovery device fail.\r\n");
	//	return;
	//}
	//if (cameraCnt < 1)
	//{
	//	//TRACE("there is no device.\r\n");
	//	return;
	//}

	//pCamera = &pCameraList[0]; //此示例默认获取相机列表里第一个相机

	//if (pCamera == NULL)
	//{
	//	return;
	//};

	///* 连接设备 */
	//ret = pCamera->connect(pCamera, accessPermissionControl);

	//if (ret != 0)
	//{
	//	//TRACE("connect camera failed.\n");
	//	return;
	//}

	////设置相机参数
	//CameraParametersSet cameraParametersSet(this);
	//cameraParametersSet.SetCameraParameterAll(pCamera);

	///* 创建流对象 */
	//ret = CreateStreamSource(pCamera, &pStreamSource);
	//if ((ret != 0) || (NULL == pStreamSource))
	//{
	//	//TRACE("create stream obj  fail.\r\n");
	//	return;
	//}

	//pStreamSource->attachGrabbing(pStreamSource, onGetFrame);

	//GENICAM_EGrabStrategy eGrabStrategy = grabStrartegySequential;
	//ret = pStreamSource->startGrabbing(pStreamSource, 0, eGrabStrategy);
	//if (ret != 0)
	//{
	//	//TRACE("StartGrabbing  fail.\n");
	//}

	//pSystem->release(pSystem); //释放资源
	//pCameraList->release(pCameraList);
	//pSystem = NULL;
	//pCameraList = NULL;

}

//void sobelCallback(int state, void* userData) 
//{
//	int a = 1;
//}

void Camera::on_pushButton_Display_clicked_back()
{
	//bool bCreate = true;
	//std::string wn = "imageshow";

	//while (1)
	//{
	//	waitKey(10);
	//	//if (false == m_bLoopShow)
	//	//{
	//	//	break;
	//	//}

	//	FrameBufferSPtr displayFrame = getConvertedImage();
	//	if (!displayFrame)
	//	{
	//		continue;
	//	}

	//	if (bCreate)
	//	{
	//		//创建opencv显示窗体
	//		namedWindow(wn, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED);

	//		//cv::createButton("确认", sobelCallback, 0, QT_PUSH_BUTTON, 0);


	//		resizeWindow(wn, 1000, 800);
	//		moveWindow(wn, 0, 0);

	//		bCreate = false;
	//	}

	//	/* 生成cv::mat对象 使用opencv的方式进行显示*/
	//	if (gvspPixelMono8 == displayFrame->PixelFormat())
	//	{
	//		cv::Mat img(Size(displayFrame->Width(), displayFrame->Height()), CV_8U, displayFrame->bufPtr());
	//		imshow(wn, img);
	//	}
	//	else
	//	{
	//		cv::Mat img(Size(displayFrame->Width(), displayFrame->Height()), CV_8UC3, displayFrame->bufPtr());
	//		imshow(wn, img);
	//		/* 保存图片 */
	//		/*vector<int> compression_params;
	//		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	//		compression_params.push_back(9);
	//		imwrite("color.jpg", img, compression_params);*/
	//	}

	//	///* 使用GDI显示到界面上 */
	//	//{
	//	//	if (!m_render.isOpen())
	//	//	{
	//	//		m_render.open();
	//	//		if (!m_render.isOpen())
	//	//		{
	//	//			continue;
	//	//		}
	//	//	}
	//	//	m_render.display(displayFrame->bufPtr(), displayFrame->Width(), displayFrame->Height(), displayFrame->PixelFormat());
	//	//}
	//}


}


void Camera::on_pushButton_Display_clicked() 
{
	//linshi
	//m_Timer->start(1000 / m_nFrameRate);
}

void Camera::updateImage()
{
	CameraControl cameraControl(this);
	cv::Mat srcImg = cameraControl.GetOneMat();
	Mat temp;
	QImage Qtemp;
	cvtColor(srcImg, temp, CV_GRAY2RGB);//GRAY convert to RGB
	Qtemp = QImage((const unsigned char*)(temp.data), temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	ui.label->setPixmap(QPixmap::fromImage(Qtemp));
	ui.label->setScaledContents(true);//设置图片适应label
	ui.label->resize(Qtemp.width() / 10, Qtemp.height() / 10);
	ui.label->show();
	this->update();
	//FrameBufferSPtr displayFrame = getConvertedImage();
	//if (!displayFrame)
	//{
	//	return;
	//}

	//if (gvspPixelMono8 == displayFrame->PixelFormat())
	//{
	//	cv::Mat srcImg(Size(displayFrame->Width(), displayFrame->Height()), CV_8U, displayFrame->bufPtr());

	//	Mat temp;
	//	QImage Qtemp;

	//	cvtColor(srcImg, temp, CV_GRAY2RGB);//GRAY convert to RGB

	//	Qtemp = QImage((const unsigned char*)(temp.data), temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	//	//}
	//	ui.label->setPixmap(QPixmap::fromImage(Qtemp));
	//	ui.label->setScaledContents(true);//设置图片适应label
	//	ui.label->resize(Qtemp.width() / 10, Qtemp.height() / 10);
	//	ui.label->show();
	//	this->update();
	//}

}

void Camera::on_PushButton_PictureAnalysis_clicked()
{
	Analysis analysis;
	analysis.AnalysisMothed("1","project001");
}

void Camera::on_PushButton_ResultList_clicked()
{
	TestResultDataManage * dataManage = new TestResultDataManage();
	dataManage->m_test_project_name = "project001";
	dataManage->Show_UI_Data();
	dataManage->show();
	dataManage->move(
		(QApplication::desktop()->width() - dataManage->width()) / 2, 
		(QApplication::desktop()->height() - dataManage->height()) / 2);
}

void Camera::on_pushButtonCutImage_clicked()
{
	bool bResult = true;
	auto dao = AnalysisUIDao::instance();
	//QString strPathFileName = GlobalData::getExePath() +"/"+ QDateTime::currentDateTime().toString("yyyyMMddHHmmss")+".png";
	QString root_info = dao->SelectTestPicturesRootPath(&bResult);
	String piture_root_str = root_info.toStdString();
	String project_name = "project001";
	String original_piture_path = project_name + "\\" + "original";
	String strPath = piture_root_str + "\\" + original_piture_path;
	String strPathFileName = strPath + "\\" + "1_1"  + ".png";
	String save_file_name = strPath + "\\" + "1_1_new" + ".png";
	IplImage *img = cvLoadImage("D:\\HumablotProFiles\\TestPictures\\original\\project001.png", CV_LOAD_IMAGE_COLOR);
	//IplImage *img = cvLoadImage("", CV_LOAD_IMAGE_COLOR);
	uchar *data = (uchar *)img->imageData;
	int step = img->widthStep / sizeof(uchar);
	int channels = img->nChannels;
	int R, G, B; ofstream fout;
	fout.open("RGB.txt", ios::app);

	Point* first_point;

	first_point = &Point(0, 0);

	int first_point_flage1 = 1;   //未找到有效点，2，找到有效点，3完成了找到有效起点;
	int start_point_count = 0;

	Point* end_point;//右下角的点
	Point* tmp_point;//临时的点
	bool tmp_point_falge = false;
	bool end_point_flage = false;
	int black_point_count = 0;

	for (int i = 0; i < img->height; i++)
	{
		for (int j = 0; j < img->width; j++)
		{
			B = (int)data[i * step + j * channels + 0];
			G = (int)data[i * step + j * channels + 1];
			R = (int)data[i * step + j * channels + 2];

			//得到左上角的位置点
			if (B > 24 && G > 24 && R > 24 && first_point_flage1==1)
			{
				first_point = new Point(i, j);
				fout << "第一个点：( " << i << ", " << j << " ) = ( " << R << "," << G << "," << B << ")" << endl;
				first_point_flage1 = 2;
			}

			//如果之前还出现0的情况说明上面的点不成立
			if (first_point_flage1==2 && ( B != 0 && G != 0 && R != 0))
			{
				if (start_point_count>20)
				{
					first_point_flage1 = 3;
					start_point_count = 0;
					//再去找有效的启始点
				}
				start_point_count++;
			}

			if (first_point_flage1 == 3 && B < 50 && G < 50 && R < 50 && i>(first_point->x+15))
			{

				if (start_point_count > 200)
				{
					tmp_point = new Point(i, j);
					fout << "右边角点Y值：( " << tmp_point->x << ", " << tmp_point->y << " ) = ( " << R << "," << G << "," << B << ")" << endl;
					start_point_count = 0;
					first_point_flage1 = 4;
				}
				start_point_count++;
			}
			//得到第一个点后，要得到右下角的点
			//if (B == 0 && G == 0 && R == 0 && first_point_flage)
			//{
			//	if (!tmp_point_falge)
			//	{
			//		tmp_point = new Point(i, j);
			//		tmp_point_falge = true;
			//	}

			//	if (black_point_count > 200)
			//	{
			//		//确定这个临时点是有效的终点
			//		fout << "右下角点Y值：( " << tmp_point->x << ", " << tmp_point->y << " ) = ( " << R << "," << G << "," << B << ")" << endl;
			//		
			//	}
			//	else
			//	{
			//		//否则临时点无效，直到找到符合条件的临时点
			//		//black_point_count = 0;
			//		//tmp_point_falge = false;
			//	}

			//	black_point_count++;
			//}
			fout << "( " << i << ", " << j << " ) = ( " << R << "," << G << "," << B << ")" << endl;
		}
	}
	fout.close();

	//cv::Mat img1 = cv::imread(strPathFileName, 1);//
	cv::Mat img1 = cv::imread("D:\\HumablotProFiles\\TestPictures\\original\\project001.png", 1);//
	cv::Mat gray1, gray2, addWeightMat;
	cv::Mat result2;
	cv::Mat subMat = cv::Mat::zeros(img1.size(), CV_8UC1);
	cv::Mat purpleMat;//二值图像
	cv::Mat purpleToMorph;

	int pThreshold = 80;
	int pContrast = 12;
    //D:\HumablotProFiles\TestPictures\project001\original
	//IplImage *img = cvLoadImage("C:\\Users\\Sunstarisme\\Desktop\\Lemon\\All Frames\\2.bmp", CV_LOAD_IMAGE_COLOR);

	//通过上面计算得到图片的非黑四个角的坐标值，代入下面方法进行截取
	//Mat img2 = img1(Range(0, 200), Range(1363, 200));
	Mat img2 = img1(Rect(130, 13, (826-200)+20, 48-13));
	save_file_name = "D:\\HumablotProFiles\\TestPictures\\original\\project001_n.png";
	/* 保存图片 */
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
	imwrite(save_file_name, img2, compression_params);
}

void Camera::on_pushButton_SaveFile_clicked()
{
	CameraControl cameraControl(this);
	cameraControl.CreateOneImage("1", 1, "project001");
	//for (int i = 1; i < 73; i++)
	//{
	//	//int result = Instrument::instance()->get_components()->get_reagentmodule()->set_膜条拍照(i);
	//	//int result = Instrument::instance()->//->get_components()->get_reagentmodule()->set_膜条拍照(i);
	//	//if (result < 0) {
	//	//	//MessageBox(_T("蠕动泵校准"), _T("error"));
	//	//	return;
	//	//}
	//	
	//	//isSave = true;
	//	Sleep(200);
	//}

	//bool bCreate = true;
	//std::string wn = "imageshow";
	//	waitKey(10);
	//	FrameBufferSPtr displayFrame = getConvertedImage();
	//	if (!displayFrame)
	//	{
	//		return;
	//	}
	//	if (bCreate)
	//	{
	//		//创建opencv显示窗体
	//		namedWindow(wn, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED);
	//		resizeWindow(wn, 1000, 800);
	//		moveWindow(wn, 0, 0);

	//		bCreate = false;
	//	}
	//	/* 生成cv::mat对象 使用opencv的方式进行显示*/
	//	if (gvspPixelMono8 == displayFrame->PixelFormat())
	//	{
	//		cv::Mat img(Size(displayFrame->Width(), displayFrame->Height()), CV_8U, displayFrame->bufPtr());
	//		imshow(wn, img);

	//		/* 保存图片 */
	//		vector<int> compression_params;
	//		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	//		compression_params.push_back(9);
	//		imwrite("color.png", img, compression_params);
	//	}
	//	else
	//	{
	//		cv::Mat img(Size(displayFrame->Width(), displayFrame->Height()), CV_8UC3, displayFrame->bufPtr());
	//		imshow(wn, img);
	//		/* 保存图片 */
	//		vector<int> compression_params;
	//		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	//		compression_params.push_back(9);
	//		imwrite("color.png", img, compression_params);
	//	}
}

void Camera::on_pushButton_Close_clicked() 
{
	CameraControl cameraControl(this);
	cameraControl.CloseCamera();
	///* 停止相机拉流 */
	//if (NULL != pStreamSource)
	//{
	//	pStreamSource->stopGrabbing(pStreamSource);
	//	pStreamSource = NULL;
	//}

	//if (NULL != pCamera)
	//{
	//	/* 断开设备 */
	//	if (0 != pCamera->disConnect(pCamera))
	//	{
	//		//TRACE("disConnect camera fail.\n");
	//		return;
	//	}
	//}
}

void Camera::closeEvent(QCloseEvent* event)
{
	on_pushButton_Close_clicked();
	//m_displayThread.join();
}

/* 显示线程 */
void Camera::DisplayThreadProc()
{
	//bool bCreate = true;
	//std::string wn = "imageshow";

	//while (1)
	//{
	//	waitKey(10);
	//	//if (false == m_bLoopShow)
	//	//{
	//	//	break;
	//	//}

	//	FrameBufferSPtr displayFrame = getConvertedImage();
	//	if (!displayFrame)
	//	{
	//		continue;
	//	}

	//	if (bCreate)
	//	{
	//		//创建opencv显示窗体
	//		namedWindow(wn, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED);

	//		//cv::createButton("确认", sobelCallback, 0, QT_PUSH_BUTTON, 0);


	//		resizeWindow(wn, 1000, 800);
	//		moveWindow(wn, 0, 0);

	//		bCreate = false;
	//	}

	//	/* 生成cv::mat对象 使用opencv的方式进行显示*/
	//	if (gvspPixelMono8 == displayFrame->PixelFormat())
	//	{
	//		cv::Mat img(Size(displayFrame->Width(), displayFrame->Height()), CV_8U, displayFrame->bufPtr());
	//		imshow(wn, img);
	//	}
	//	else
	//	{
	//		cv::Mat img(Size(displayFrame->Width(), displayFrame->Height()), CV_8UC3, displayFrame->bufPtr());
	//		imshow(wn, img);
	//		/* 保存图片 */
	//		/*vector<int> compression_params;
	//		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	//		compression_params.push_back(9);
	//		imwrite("color.jpg", img, compression_params);*/
	//	}

	//	///* 使用GDI显示到界面上 */
	//	//{
	//	//	if (!m_render.isOpen())
	//	//	{
	//	//		m_render.open();
	//	//		if (!m_render.isOpen())
	//	//		{
	//	//			continue;
	//	//		}
	//	//	}
	//	//	m_render.display(displayFrame->bufPtr(), displayFrame->Width(), displayFrame->Height(), displayFrame->PixelFormat());
	//	//}
	//}

}





