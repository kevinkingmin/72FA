#include "..\include\precomp\precompile.h"
#include "CameraCheckWidgets.h"
#include "src/comm/GlobalData.h"
#include "../../Camera/Camera.h"
#include <QMessageBox>
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
//#include "../Include/BLL/baseSet/SystemSetBLL.h"
//#include "../Include/Model/baseSet/SystemSetModel.h"
#include "src/comm/CustomButton.h"
#include <QMessageBox>
#include <string>
#include <QDateTime>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/ProgressDialog.h"
#include "src/Camera/CameraControl.h"
#include <QtConcurrent/QtConcurrent>
#include <opencv2/opencv.hpp> 
#include <QtCore/qmath.h>  

#include "src/Camera/CameraParametersSet.h"
#include <iostream>
#include <exception>
#include <QSettings>
#include <QMessageBox>
#include <exception>
#include "../Include/Utilities/log.h"
#include "src/comm/GlobalData.h"
#include "src/main/subDialog/MyMessageBox.h"


CameraCheckWidgets::CameraCheckWidgets(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CameraCheckWidgetsClass)
	, _InstrumentState(InstrumentStateModel::instance())
	, _instr(Instrument::instance())
{
	ui->setupUi(this);
    //m_move_pos_thread = new Mythread();
    //connect(this, SIGNAL(preper_save(CameraCheckWidgets *)), m_move_pos_thread, SLOT(StartSend()));//链接信号和槽
    //connect(m_move_pos_thread, SIGNAL(UpdateSignal(int)), this, SLOT(UpdateSlot(int)));
    //m_move_pos_thread->start();
	double value = GetCameraParameter_ExposureTime();
	QString str = "";
	str = QString("%1").arg(value);
	ui->lineEdit_4->setText(str);
	//myo.moveToThread(&thread);//把对象myo移到thread子线程
	//connect(this, SIGNAL(clicked(void)), &myo, SLOT(f()));  //让按钮的点击信号连接工作对象的槽函数
	//thread.start();//执行子线程

	QString sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1229");
	ui->pushButton->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1230");
	ui->pushButton_2->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1231");
	ui->label_3->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1232");
	ui->label_4->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1233");
	ui->pushButton_3->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1234");
	ui->label_6->setText(sz1);


}

void CameraCheckWidgets::UpdateSlot(int num)
{

}

CameraCheckWidgets::~CameraCheckWidgets()
{

}

void CameraCheckWidgets::recv_msg(QString msg)
{
	//ui.label->append(msg);
}

void CameraCheckWidgets::on_pushButton_2_clicked()
{
	int x = ui->lineEdit->text().toInt();
	int y = ui->lineEdit_2->text().toInt();

	if (x > 2440 || x < 1)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1435"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return ;
	}

	if (y > 269 || y < 1)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1435"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return ;
	}

	GetGrayValue();
}

void CameraCheckWidgets::on_pushButton_3_clicked()
{
	QString exe_path = GlobalData::getExePath() + "/config/CameraConfig.ini";
	QSettings config_set(exe_path, QSettings::IniFormat);
	int nResult = 0;
	double dParameterValue;
	int nParameterValue;
	config_set.beginGroup("Camera");
	dParameterValue = config_set.value("ExposureTime").toDouble();
	double value = ui->lineEdit_4->text().toDouble();
	if (value < 1 || value>5000000)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1436"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}
	config_set.setValue("ExposureTime", value);
	QString str = QString("%1").arg(value);
	ui->lineEdit_4->setText(str);
	MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1437"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
	//QMessageBox::warning(0, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "设置相机参数曝光时间失败！", QMessageBox::Ok);
}
double CameraCheckWidgets::GetCameraParameter_ExposureTime()
{
	QString exe_path = GlobalData::getExePath() + "/config/CameraConfig.ini";
	QSettings config_set(exe_path, QSettings::IniFormat);
	int nResult = 0;
	double dParameterValue;
	int nParameterValue;
	config_set.beginGroup("Camera");
	dParameterValue = config_set.value("ExposureTime").toDouble();
	return dParameterValue;
}

void CameraCheckWidgets::setProgressDialog(ProgressDialog *progressDialog)
{
	m_progressDialog = progressDialog;
}

void CameraCheckWidgets::_onFunction()
{
	//while (m_flag) {
	//	int pos = 12;
	//	_instr->moveToPhotoPos(pos);
	//	//qDebug() << "_onFunction:" << QThread::currentThread();
	//	QThread::msleep(1000);
	//	m_flag = false;
	//}
}

void CameraCheckWidgets::TakePic()
{
	//0C：背光灯
    //_instr->lightControl(0x0c, 0);
	Sleep(1000);
    //_instr->lightControl(0x0c, 1);
	//_instr->calibrateCamera();
    //m_move_pos_thread->ChangeFlage(true);
	Sleep(3500);
	CameraControl m_cameraControl(this);
	bool res = m_cameraControl.OpenCamera();
	if (res == false)
	{
		m_cameraControl.CloseCamera();
		m_cameraControl.OpenCamera();

		while (true)
		{
			m_cameraControl.CloseCamera();
			res = m_cameraControl.OpenCamera();
			if (res)
			{
				goto STARTDEALPIC;
			}
			auto state = _InstrumentState->getMachineState();
			if (state.state == enumState::enumUnConn)
			{
				//QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("通讯异常"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
				break;
			}
			else
			{
			}
		}

		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "连接相机失败！", "确定");
		return;
	}
STARTDEALPIC:
	Sleep(3000);
	m_cameraControl.CreateOneImage("test1", 1, "test1");
	//ShowImageDialog.exe
	//Sleep(6000);
	//_mShowImageDialog->ShowPicInfo();
	//_mShowImageDialog->exec();
	//pic_file_path_list.push_back(pic_file_name);
	//调用数据分析并保存到测试结果表
	//todo
	m_cameraControl.CloseCamera();
	while (true)
	{
		res = m_cameraControl.CloseCamera();
		if (!res)
		{
			goto CLOSECAMERAFINISH;
		}
	}
CLOSECAMERAFINISH:
    //_instr->lightControl(0x0c, 0);
	Sleep(200);
	m_cameraControl.destroyed();
	Sleep(200);
    //_instr->motorInitialize(0x02, 60000);
	Sleep(200);
    //_instr->motorInitialize(0x03, 60000);
	Sleep(200);
    //_instr->motorInitialize(0x01, 60000);
	Sleep(200);


}

int CameraCheckWidgets::GetGrayValue()
{
	//ui->
	int x = ui->lineEdit->text().toInt();
	int y = ui->lineEdit_2->text().toInt();

	//if (x > 2440 || x<1)
	//{
	//	QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "坐标超范围！", "确定");
	//	return 0;
	//}

	//if (y > 269 || y<1)
	//{
	//	QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "坐标超范围！", "确定");
	//	return 0;
	//}

	bool bResult = true;
	auto dao = AnalysisUIDao::instance();
	QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
	QString original_piture_path = "original";
	//QString strPath = piture_root_str +"\\"+ test_file_name + "\\" + original_piture_path;
	//QString strPathFileName = strPath + "\\" + QString::number(nSampleID) + +"_" + QString::number(nTestPaperID) + ".png";
	QString strPath = piture_root_str + "\\" + original_piture_path;
	QString strPathFileName = strPath + "\\" + "test1" + ".png";
	QString strPathFileName1 = strPath + "\\" + "test2" + ".png";
	IplImage *srcGray = cvLoadImage(strPathFileName.toStdString().data(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);//从本地读取彩色图

	CvSize sz;
	sz.width = srcGray->width;//宽度
	sz.height = srcGray->height;//高度
	unsigned char * imageData;     //当前帧的数据指针
	imageData = (unsigned char*)srcGray->imageData;
	double aVerage = 0;
	unsigned int sum = 0;
	int count = 0; //一共计算多少个点
	int value = 0;
	IplImage *srcGray_RGB;
	value = ((uchar*)(srcGray->imageData + srcGray->widthStep*y))[x];  //得到灰度值

	//grayToRGB(srcGray);
	//cvtColor(srcGray, cimg, CV_GRAY2RGB);
	//cv::cvtColor(strPathFileName1.toStdString().data(), bmp, cv::COLOR_GRAY2BGR);
	int line_gray_value = 0;
	if(value<125)
	{
		line_gray_value = 255;
	}
	else
	{
		line_gray_value = 0;
	}

	for (int i = 0; i < 50; i++)
	{
		((uchar*)(srcGray->imageData + srcGray->widthStep*(y + i)))[x] = line_gray_value;
	}

	for (int j = 0; j < 50; j++)
	{
		((uchar*)(srcGray->imageData + srcGray->widthStep*(y)))[x+j] = line_gray_value;
		//((uchar*)(srcGray->imageData + srcGray->widthStep*(y + i) + (x + j) * srcGray->nChannels))[c] = 150;
	}

	//((uchar*)(srcGray->imageData + srcGray->widthStep*y))[x] = 100;
	//((uchar*)(srcGray->imageData + srcGray->widthStep*y))[x+1] = 100;
	//((uchar*)(srcGray->imageData + srcGray->widthStep*y))[x+2] = 100;
	//((uchar*)(srcGray->imageData + srcGray->widthStep*y))[x+3] = 100;
	//((uchar*)(srcGray->imageData + srcGray->widthStep*y))[x+4] = 100;

	cvSaveImage(strPathFileName1.toStdString().data(), srcGray);//将图保存到本地

	ShowPicInfo1("test2");
	QString value1 = "";
	value1 = QString("%1").arg(value);
	ui->lineEdit_3->setText(value1);
	return value;


}


//灰度图转彩色图
//Mat CameraCheckWidgets::grayToRGB(const cv::Mat input_img)
//{
//	//创建一个和灰度图一样大小的0值图
//	cv::Mat three_channel = cv::Mat::zeros(input_img.rows, input_img.cols, CV_8UC3);
//	std::vector<cv::Mat> channels;
//	//得到3张单通道图
//	for (int i = 0; i < 3; i++)
//		channels.push_back(input_img);
//
//	//RGB通道图的合并
//	cv::merge(channels, three_channel);
//	return three_channel;
//}


void CameraCheckWidgets::ShowPicInfo(QString file_name)
{

	bool bResult = true;
	auto dao = AnalysisUIDao::instance();
	QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
	QString original_piture_path = "original";
	//QString strPath = piture_root_str +"\\"+ test_file_name + "\\" + original_piture_path;
	//QString strPathFileName = strPath + "\\" + QString::number(nSampleID) + +"_" + QString::number(nTestPaperID) + ".png";
	QString strPath = piture_root_str + "\\" + original_piture_path;
	QString strPathFileName = strPath + "\\" + file_name + ".png";//+ "test1" + ".png";
	QImage image(strPathFileName);
	ui->label_5->setPixmap(QPixmap::fromImage(image));
	ui->label_5->setScaledContents(true);

	QString strPathFileName_new = strPath + "\\" + file_name + "_new" + ".png";
	QString strPathFileName_last = strPath + "\\" + file_name + "_last" + ".png";

	//RotatePng(strPathFileName, strPathFileName_new, strPathFileName_last);

	//GetContoursPic(strPathFileName, strPathFileName_new);

	//QImage image1(strPathFileName_new);
	QImage image1(strPathFileName);
	ui->label_5->setPixmap(QPixmap::fromImage(image1));
	ui->label_5->setScaledContents(true);


	/*
	bool bResult = true;
	auto dao = AnalysisUIDao::instance();
	QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
	QString original_piture_path = "original";
	//QString strPath = piture_root_str +"\\"+ test_file_name + "\\" + original_piture_path;
	//QString strPathFileName = strPath + "\\" + QString::number(nSampleID) + +"_" + QString::number(nTestPaperID) + ".png";
	QString strPath = piture_root_str + "\\" + original_piture_path;
	QString strPathFileName = strPath + "\\" + file_name;//+ "test1" + ".png";


	QImage image(strPathFileName);
	ui->label_5->setPixmap(QPixmap::fromImage(image));
	ui->label_5->setScaledContents(true);
	//ui->label->setPixmap(QPixmap::fromImage(image));
	//label->show();
	*/

}

void CameraCheckWidgets::ShowPicInfo1(QString file_name)
{

	bool bResult = true;
	auto dao = AnalysisUIDao::instance();
	QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
	QString original_piture_path = "original";
	//QString strPath = piture_root_str +"\\"+ test_file_name + "\\" + original_piture_path;
	//QString strPathFileName = strPath + "\\" + QString::number(nSampleID) + +"_" + QString::number(nTestPaperID) + ".png";
	QString strPath = piture_root_str + "\\" + original_piture_path;
	QString strPathFileName = strPath + "\\" + file_name + ".png";//+ "test1" + ".png";
	QImage image(strPathFileName);
	ui->label_5->setPixmap(QPixmap::fromImage(image));
	ui->label_5->setScaledContents(true);

	QString strPathFileName_new = strPath + "\\" + file_name + "_new" + ".png";
	QString strPathFileName_last = strPath + "\\" + file_name + "_last" + ".png";
	//RotatePng1(strPathFileName, strPathFileName_new, strPathFileName_last);
	//QImage image1(strPathFileName_new);
	//RotatePng1(strPathFileName, strPathFileName_new, strPathFileName_last);
	QImage image1(strPathFileName);
	ui->label_5->setPixmap(QPixmap::fromImage(image1));
	ui->label_5->setScaledContents(true);

}

void CameraCheckWidgets::on_pushButton_clicked()
{
	//int *pTest = NULL;
	//(*pTest) = 1;
	//return;
	TakePic();
	ShowPicInfo("test1");


	//ShowPicInfo("202304041329166");
	//ShowPicInfo("2023041311065223");
	//ShowPicInfo("test1");
	//RotatePng("D:/xx.png", "D:/xx23.png","D:/xx3443.jpg");
	//RotatePng("D:/202207131057440.png", "D:/xx231.png", "D:/xx34431.jpg");
	//return;
	//TakePic();
	//ShowPicInfo("test1");
	//ShowPicInfo("202207061357430");
	//ShowPicInfo("202211091453120");
	//ShowPicInfo("202207061357430");
	//ShowPicInfo("202211091138301");
	//ShowPicInfo("34568");
	//ShowPicInfo("34567");
	//int xxx = 34568;
	//QString file_name = QString("%1").arg(xxx);
	//ShowPicInfo(file_name);
	//ShowPicInfo("34569");
	//ShowPicInfo("345");
	//ShowPicInfo("3451");
	//ShowPicInfo("34562");
	//ShowPicInfo("1 (2)");

	//ShowPicInfo("202305180948490");
	
	//ShowPicInfo("202303151029300");
	//ShowPicInfo("202303151029301");
	//ShowPicInfo("202303151029302");
	//ShowPicInfo("202303151029303");
	//ShowPicInfo("202303151029304");
	//ShowPicInfo("202303151029305");
	//ShowPicInfo("202303151029306");
	//ShowPicInfo("202303151029307");

	//ShowPicInfo("202303151033540");
	//ShowPicInfo("202303151033541");
	//ShowPicInfo("202303151033542");
	//ShowPicInfo("202303151033543");
	//ShowPicInfo("202303151033544");
	//ShowPicInfo("202303151033545");
	//ShowPicInfo("202303151033546");
	//ShowPicInfo("202303151033547");
	//for (size_t i = 1; i < 14; i++)
	//{
	//	QString file_name = QString("1 (%1)").arg(i);
	//	ShowPicInfo(file_name);
	//}

	//for (size_t i = 1; i < 31; i++)
	//{
	//	QString file_name = QString("n (%1)").arg(i);
	//	ShowPicInfo(file_name);
	//}

	//for (size_t i = 1; i < 3; i++)
	//{
	//	QString file_name = QString("n (%1)").arg(i);
	//	ShowPicInfo(file_name);
	//}

	//异常旋转
	//ShowPicInfo("202303141156532");
	//ShowPicInfo("202303141149455");
	//ShowPicInfo("202303141030382");

	//ShowPicInfo("202303141129005");
	
	//ShowPicInfo("202303141149450");
	//ShowPicInfo("202303141129005");
	//ShowPicInfo("202303141038222");
	//ShowPicInfo("202303141038220");
	//ShowPicInfo("202303141030383");
	//ShowPicInfo("202303141030382");
	//ShowPicInfo("202303141030381");

	//ShowPicInfo("2023031418061811");
	//ShowPicInfo("2023031418061816");
	//ShowPicInfo("2023031418061834");
	//ShowPicInfo("2023031418061863");
	//ShowPicInfo("2023031418061816");
	//	
	//ShowPicInfo("test1");
	//	
	//ShowPicInfo("202303220858490");
	//ShowPicInfo("202303220858491");
	//ShowPicInfo("202303220858492");
	//ShowPicInfo("202303220858493");


	//ShowPicInfo("202305171430130");
	//202305171430131
	//202305171430132
	//	202305171430133 
	//	202305171430134 
 //202305171430135 
	//	202305171430136
	//	202305171433400 

		
	//2023030716235732.png
	//ShowPicInfo("34563");
	//ShowPicInfo("202211281436130");
	//float temperature;//= 271646722;
	//QString str = "";
	//QString str2 = QString::number(temperature, 'f', 1);
	//str = QString("孵育盘：%1 ℃  ").arg(str2);
}

void CameraCheckWidgets::RotatePng1(QString scr_path, QString new_path, QString last_path1)
{
	Mat src, src1, src_edge, src_gray, src_gray1,src_rotate;
	Mat gray, binImg;
	double angle;
	src = imread(scr_path.toStdString());
	src1 = imread(scr_path.toStdString());

	if (src.rows == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1182"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}

	//imshow("src", src);
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	double thres1 = 130;
	double maxval1 = 160;
	threshold(src1, src1, thres1, maxval1, CV_THRESH_BINARY);
	//imshow("threshold", src_gray);


	Canny(src1, src_edge, 50, 100, 3);
	//Canny(src_gray, src_edge, 16, 200, 5);
	//Canny(src_gray, src_edge, 16, 128, 3);
	//imshow("canny", src_edge);

	//通过霍夫变换检测直线
	//std::vector<Vec2f> plines;
	//第5个参数就是阈值，阈值越大，检测精度越高
	//HoughLines(src_edge, plines, 1, CV_PI / 180, 200, 0, 0);
	//HoughLines(src_edge, plines, 1, CV_PI / 180, 220, 0, 0);

	//通过霍夫变换检测直线
	std::vector<Vec2f> plines;
	//第5个参数就是阈值，阈值越大，检测精度越高
	//HoughLines(src_edge, plines, 1, CV_PI / 180, 200, 0, 0);
	int count_number = 3;
	int value1 = 220;
	int plines_size = 32;


	for (int ii = 220; ii != 0; ii--)
	{
		std::vector<Vec2f> plines1;
		HoughLines(src_edge, plines1, 1, CV_PI / 180, ii, 0, 0);
		if (plines1.size() > plines_size)
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

	//cout << plines.size() << endl;
	//由于图像不同，阈值不好设定，因为阈值设定过高导致无法检测直线，阈值过低直线太多，速度很慢
	//所以根据阈值由大到小设置了三个阈值，如果经过大量试验后，可以固定一个适合的阈值。
	float sum = 0;
	int sum_count = 0;
	//依次画出每条线段
	for (size_t i = 0; i < plines.size(); i++)
	{
		float rho = plines[i][0];
		float theta = plines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 2500 * (-b));//cvRound四舍五入
		pt1.y = cvRound(y0 + 2500 * (a));
		pt2.x = cvRound(x0 - 2500 * (-b));
		pt2.y = cvRound(y0 - 2500 * (a));

		if (qAbs(pt1.y)<1000 && qAbs(pt2.y) < 1000)
		{
			sum += theta;
			line(src_gray, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);//Scalar函数用于调节线段颜色         
			//imshow("直线探测效果图", src_gray);
			//imshow("plines", src_gray);
			sum_count++;
		}
		else
		{
			int xx1 = pt1.y;
			int xx2 = pt2.y;
		}
		//angle = DegreeTrans(average) - 90;
	}

	//float average = sum / plines.size(); //对所有角度求平均，这样做旋转效果会更好
	float average = sum / sum_count; //对所有角度求平均，这样做旋转效果会更好
	angle = average / CV_PI * 180 - 90;
	//angle = -(average-0.5);
	////新建一个感兴趣的区域图，大小跟原图一样大  
	//Mat RoiSrcImg(src.rows, src.cols, CV_8UC3); //注意这里必须选CV_8UC3
	//RoiSrcImg.setTo(0); //颜色都设置为黑色  
	////imshow("新建的ROI", RoiSrcImg);
	////对得到的轮廓填充一下  
	//drawContours(binImg, contours, -1, Scalar(255), CV_FILLED);
	////抠图到RoiSrcImg
	//src.copyTo(RoiSrcImg, binImg);
	//double angle = DegreeTrans(average) - 90;
	//旋转中心为图像中心    
	Point2f center;
	center.x = float(src.cols / 2.0);
	center.y = float(src.rows / 2.0);
	int length = 0;
	length = sqrt(src.cols*src.cols + src.rows*src.rows);
	Mat M = getRotationMatrix2D(center, angle, 1);

	//warpAffine(src, src_rotate, M, Size(length, length), 1, 0, Scalar(255, 255, 255));//仿射变换，背景色填充为白色  
	//warpAffine(src, src_rotate, M, Size(length, length), 1, 0, Scalar(0,0,0));//仿射变换，背景色填充为l黑色
	warpAffine(src, src_rotate, M, Size(length, src.rows), 1, 0, Scalar(0, 0, 0));//仿射变换，背景色填充为l黑色
	//warpAffine(src, src_rotate, M, Size(length, length), 1, 0, Scalar(0, 0, 0));//仿射变换，背景色填充为l黑色

	//imshow("矫正后", src_rotate);
	//imshow("new", src_rotate);
	imwrite(new_path.toStdString(), src_rotate); //将矫正后的图片保存下来
	//返回矫正后的Mat

	//对旋转后的图片进行轮廓提取  
	std::vector<std::vector<Point> > contours2;
	std::vector<std::vector<Point> > contours3;
	Mat raw = imread(new_path.toStdString());
	Mat SecondFindImg;
	//SecondFindImg.setTo(0);
	cvtColor(raw, SecondFindImg, COLOR_BGR2GRAY);  //灰度化  
	//threshold(SecondFindImg, SecondFindImg, 80, 200, CV_THRESH_BINARY);
	//double thres = 80;
	//double maxval = 150;

	double thres = 130;
	double maxval = 160;

	//THRESH_TRIANGLE
	threshold(SecondFindImg, SecondFindImg, thres, maxval, CV_THRESH_BINARY);

	//imshow("gray_picture", SecondFindImg);//输出灰度图

	//threshold(SecondFindImg, SecondFindImg, thres, maxval, CV_THRESH_TRIANGLE);
	findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//cout << "sec contour:" << contours2.size() << endl;
	Mat dstImg;
	Mat dstImg_show;
	Mat dstImg_show_20230412001;
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

		if (rect_area > 50)
		{
			if (rect.width > 15 && rect.height > 30)
			{
				contours3.push_back(contours2[j]);
				//QString strxx = "";
				//strxx = QString("dstImg_show_%1").arg(j);
				//dstImg_show_20230412001 = raw(rect);
				//imshow(strxx.toStdString(), dstImg_show_20230412001);
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
		//符合条件的矩形
		if (rect.height > 22)
		{
			card_y_need.push_back(max_y);
			card_height.push_back(rect.height);
			need_height += rect.height;
			height_22_i++;
		}
	}

	if (height_22_i == 0)
	{
		return;
	}

	need_height = need_height / height_22_i;
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

	//得到平均值
	double sum1 = std::accumulate(std::begin(card_y_need), std::end(card_y_need), 0.0);
	double avg_mean = sum1 / card_y_need.size();
	int avgValue_y_asix = avg_mean;
	minValue_y_asix = avgValue_y_asix;

	int minPosition = min_element(card_x.begin(), card_x.end()) - card_x.begin();
	int maxValue_height = *max_element(card_height.begin(), card_height.end());
	int maxPosition_height = max_element(card_height.begin(), card_height.end()) - card_height.begin();


	//求出要载取区域width,根据最小的X值
	int maxValue_x = *max_element(card_x.begin(), card_x.end());
	int maxPosition_x = max_element(card_x.begin(), card_x.end()) - card_x.begin();

	minValue_x_asix = minValue_x_asix;//minValue_xx;
	//得到需要的图像宽度
	rect = boundingRect(Mat(contours3[maxPosition_x]));
	int need_width = 0;
	int head_width = 120;

	need_width = rect.x + rect.width - minValue_x_asix;
	need_width = (rect.x + rect.width) - minValue_x_asix + head_width; //考虑有些模条无法识别膜条头的问题。

	if (need_height > 65)
	{
		need_height = (boundingRect(Mat(contours3[minPosition])).height + boundingRect(Mat(contours3[maxPosition_x])).height) / 2;
	}

	start_up_x = boundingRect(Mat(contours3[minPosition])).x; //boundingRect(Mat(contours3[minPosition])).width;//rect.x + rect.width;
	start_up_y = minValue_y_asix;//boundingRect(Mat(contours3[minPosition])).y;
	end_up_x = boundingRect(Mat(contours3[maxPosition_x])).x + boundingRect(Mat(contours3[maxPosition_x])).width;//rect.x + rect.width;
	end_up_y = boundingRect(Mat(contours3[maxPosition_x])).y;
	rect_need.x = minValue_x_asix - head_width;//start_up_x;
	rect_need.y = start_up_y;
	rect_need.width = need_width;//end_down_x - start_up_x;
	rect_need.height = need_height;//start_down_y - start_up_y;
	if (rect_need.x<0)
	{
		rect_need.x = 0;
	}
	if (rect_need.y < 0)
	{
		rect_need.y = 0;
	}
	//dstImg = raw(rect_need);
	////imshow("need_raw", dstImg);
	//imwrite(last_path1.toStdString(), dstImg);
}


void CameraCheckWidgets::RotatePng(QString scr_path, QString new_path, QString last_path1)
{
	Mat src, src1, src_edge, src_gray, src_gray1, src_rotate;
	Mat gray, binImg;
	double angle;
	src = imread(scr_path.toStdString());
	src1 = imread(scr_path.toStdString());

	if (src.rows == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1182"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}

	//imshow("src", src);
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	double thres1 = 130;
	double maxval1 = 160;
	threshold(src1, src1, thres1, maxval1, CV_THRESH_BINARY);
	//imshow("threshold", src_gray);


	Canny(src1, src_edge, 50, 100, 3);
	//Canny(src_gray, src_edge, 16, 200, 5);
	//Canny(src_gray, src_edge, 16, 128, 3);
	//imshow("canny", src_edge);

	//通过霍夫变换检测直线
	//std::vector<Vec2f> plines;
	//第5个参数就是阈值，阈值越大，检测精度越高
	//HoughLines(src_edge, plines, 1, CV_PI / 180, 200, 0, 0);
	//HoughLines(src_edge, plines, 1, CV_PI / 180, 220, 0, 0);

	//通过霍夫变换检测直线
	std::vector<Vec2f> plines;
	//第5个参数就是阈值，阈值越大，检测精度越高
	//HoughLines(src_edge, plines, 1, CV_PI / 180, 200, 0, 0);
	int count_number = 3;
	int value1 = 220;
	int plines_size = 32;


	for (int ii = 220; ii != 0; ii--)
	{
		std::vector<Vec2f> plines1;
		HoughLines(src_edge, plines1, 1, CV_PI / 180, ii, 0, 0);
		if (plines1.size() > plines_size)
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

	//cout << plines.size() << endl;
	//由于图像不同，阈值不好设定，因为阈值设定过高导致无法检测直线，阈值过低直线太多，速度很慢
	//所以根据阈值由大到小设置了三个阈值，如果经过大量试验后，可以固定一个适合的阈值。
	float sum = 0;
	int sum_count = 0;
	//依次画出每条线段
	for (size_t i = 0; i < plines.size(); i++)
	{
		float rho = plines[i][0];
		float theta = plines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 2500 * (-b));//cvRound四舍五入
		pt1.y = cvRound(y0 + 2500 * (a));
		pt2.x = cvRound(x0 - 2500 * (-b));
		pt2.y = cvRound(y0 - 2500 * (a));

		if (qAbs(pt1.y) < 1000 && qAbs(pt2.y) < 1000)
		{
			sum += theta;
			line(src_gray, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);//Scalar函数用于调节线段颜色         
			//imshow("直线探测效果图", src_gray);
			//imshow("plines", src_gray);
			sum_count++;
		}
		else
		{
			int xx1 = pt1.y;
			int xx2 = pt2.y;
		}
		//angle = DegreeTrans(average) - 90;
	}

	//float average = sum / plines.size(); //对所有角度求平均，这样做旋转效果会更好
	float average = sum / sum_count; //对所有角度求平均，这样做旋转效果会更好
	angle = average / CV_PI * 180 - 90;
	//angle = -(average-0.5);
	////新建一个感兴趣的区域图，大小跟原图一样大  
	//Mat RoiSrcImg(src.rows, src.cols, CV_8UC3); //注意这里必须选CV_8UC3
	//RoiSrcImg.setTo(0); //颜色都设置为黑色  
	////imshow("新建的ROI", RoiSrcImg);
	////对得到的轮廓填充一下  
	//drawContours(binImg, contours, -1, Scalar(255), CV_FILLED);
	////抠图到RoiSrcImg
	//src.copyTo(RoiSrcImg, binImg);
	//double angle = DegreeTrans(average) - 90;
	//旋转中心为图像中心    
	Point2f center;
	center.x = float(src.cols / 2.0);
	center.y = float(src.rows / 2.0);
	int length = 0;
	length = sqrt(src.cols*src.cols + src.rows*src.rows);
	Mat M = getRotationMatrix2D(center, angle, 1);

	//warpAffine(src, src_rotate, M, Size(length, length), 1, 0, Scalar(255, 255, 255));//仿射变换，背景色填充为白色  
	//warpAffine(src, src_rotate, M, Size(length, length), 1, 0, Scalar(0,0,0));//仿射变换，背景色填充为l黑色
	warpAffine(src, src_rotate, M, Size(length, src.rows), 1, 0, Scalar(0, 0, 0));//仿射变换，背景色填充为l黑色
	//warpAffine(src, src_rotate, M, Size(length, length), 1, 0, Scalar(0, 0, 0));//仿射变换，背景色填充为l黑色

	//imshow("矫正后", src_rotate);
	//imshow("new", src_rotate);
	imwrite(new_path.toStdString(), src_rotate); //将矫正后的图片保存下来
	//返回矫正后的Mat

	//对旋转后的图片进行轮廓提取  
	std::vector<std::vector<Point> > contours2;
	std::vector<std::vector<Point> > contours3;
	Mat raw = imread(new_path.toStdString());
	Mat SecondFindImg;
	//SecondFindImg.setTo(0);
	cvtColor(raw, SecondFindImg, COLOR_BGR2GRAY);  //灰度化  
	//threshold(SecondFindImg, SecondFindImg, 80, 200, CV_THRESH_BINARY);
	//double thres = 80;
	//double maxval = 150;

	double thres = 130;
	double maxval = 160;

	//THRESH_TRIANGLE
	threshold(SecondFindImg, SecondFindImg, thres, maxval, CV_THRESH_BINARY);

	//imshow("gray_picture", SecondFindImg);//输出灰度图

	//threshold(SecondFindImg, SecondFindImg, thres, maxval, CV_THRESH_TRIANGLE);
	findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//cout << "sec contour:" << contours2.size() << endl;
	Mat dstImg;
	Mat dstImg_show;
	Mat dstImg_show_20230412001;
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

		if (rect_area > 50)
		{
			if (rect.width > 15 && rect.height > 30)
			{
				contours3.push_back(contours2[j]);
				//QString strxx = "";
				//strxx = QString("dstImg_show_%1").arg(j);
				//dstImg_show_20230412001 = raw(rect);
				//imshow(strxx.toStdString(), dstImg_show_20230412001);
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
		//符合条件的矩形
		if (rect.height > 22)
		{
			card_y_need.push_back(max_y);
			card_height.push_back(rect.height);
			need_height += rect.height;
			height_22_i++;
		}
	}

	if (height_22_i == 0)
	{
		return;
	}

	need_height = need_height / height_22_i;
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

	//得到平均值
	double sum1 = std::accumulate(std::begin(card_y_need), std::end(card_y_need), 0.0);
	double avg_mean = sum1 / card_y_need.size();
	int avgValue_y_asix = avg_mean;
	minValue_y_asix = avgValue_y_asix;

	int minPosition = min_element(card_x.begin(), card_x.end()) - card_x.begin();
	int maxValue_height = *max_element(card_height.begin(), card_height.end());
	int maxPosition_height = max_element(card_height.begin(), card_height.end()) - card_height.begin();


	//求出要载取区域width,根据最小的X值
	int maxValue_x = *max_element(card_x.begin(), card_x.end());
	int maxPosition_x = max_element(card_x.begin(), card_x.end()) - card_x.begin();

	minValue_x_asix = minValue_x_asix;//minValue_xx;
	//得到需要的图像宽度
	rect = boundingRect(Mat(contours3[maxPosition_x]));
	int need_width = 0;
	int head_width = 120;

	need_width = rect.x + rect.width - minValue_x_asix;
	need_width = (rect.x + rect.width) - minValue_x_asix + head_width; //考虑有些模条无法识别膜条头的问题。

	if (need_height > 65)
	{
		need_height = (boundingRect(Mat(contours3[minPosition])).height + boundingRect(Mat(contours3[maxPosition_x])).height) / 2;
	}

	start_up_x = boundingRect(Mat(contours3[minPosition])).x; //boundingRect(Mat(contours3[minPosition])).width;//rect.x + rect.width;
	start_up_y = minValue_y_asix;//boundingRect(Mat(contours3[minPosition])).y;
	end_up_x = boundingRect(Mat(contours3[maxPosition_x])).x + boundingRect(Mat(contours3[maxPosition_x])).width;//rect.x + rect.width;
	end_up_y = boundingRect(Mat(contours3[maxPosition_x])).y;
	rect_need.x = minValue_x_asix - head_width;//start_up_x;
	rect_need.y = start_up_y;
	rect_need.width = need_width;//end_down_x - start_up_x;
	rect_need.height = need_height;//start_down_y - start_up_y;
	if (rect_need.x < 0)
	{
		rect_need.x = 0;
	}
	if (rect_need.y < 0)
	{
		rect_need.y = 0;
	}
	dstImg = raw(rect_need);
	//imshow("need_raw", dstImg);
	imwrite(last_path1.toStdString(), dstImg);
}


//第一个参数：输入图片名称；第二个参数：输出图片名称
void CameraCheckWidgets::GetContoursPic(QString pSrcFileName, QString pDstFileName)
{
	Mat srcImg = imread(pSrcFileName.toStdString());
	imshow("src pic ", srcImg);
	Mat gray, binImg;
	//灰度化
	cvtColor(srcImg, gray, COLOR_RGB2GRAY);
	imshow("gray pic", gray);
	//二值化
	threshold(gray, binImg, 80, 150, CV_THRESH_BINARY);
	imshow("2 value", binImg);


	//Canny(gray, binImg, 50, 200, 3);

	std::vector<std::vector<Point> > contours;
	std::vector<Rect> boundRect(contours.size());
	//注意第5个参数为CV_RETR_EXTERNAL，只检索外框  
	findContours(binImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //找轮廓
	//cout << contours.size() << endl;
	float angle = 0;
	float sum = 0;
	int valid_number = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		//需要获取的坐标  
		CvPoint2D32f rectpoint[4];
		CvBox2D rect = minAreaRect(Mat(contours[i]));

		cvBoxPoints(rect, rectpoint); //获取4个顶点坐标  

		//cout << angle << endl;

		int line1 = sqrt((rectpoint[1].y - rectpoint[0].y)*(rectpoint[1].y - rectpoint[0].y) + (rectpoint[1].x - rectpoint[0].x)*(rectpoint[1].x - rectpoint[0].x));
		int line2 = sqrt((rectpoint[3].y - rectpoint[0].y)*(rectpoint[3].y - rectpoint[0].y) + (rectpoint[3].x - rectpoint[0].x)*(rectpoint[3].x - rectpoint[0].x));
		//rectangle(binImg, rectpoint[0], rectpoint[3], Scalar(255), 2);
		//面积太小的直接pass
		//if ((line1 * line2 < 600) || (line1<200))
		//{
		//	continue;
		//}
		float tmp = rect.angle;
		if ((line1 * line2 < 600))
		{
			continue;
		}

		//与水平线的角度  
		//sum += (90 + rect.angle);
		if (tmp != 0 && abs(tmp) > 45)
		{
			sum += rect.angle;
			valid_number++;
		}

		//为了让正方形横着放，所以旋转角度是不一样的。竖放的，给他加90度，翻过来  
		//if (line1 > line2)
		//{
		//	angle = 90 + angle;
		//}
		//else
		//{
		//	angle = 90 - angle;
		//}


	}

	float average = sum / valid_number;//contours.size(); //对所有角度求平均，这样做旋转效果会更好

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
	//warpAffine(src, src_rotate, M, Size(length, length), 1, 0, Scalar(255, 255, 255));//仿射变换，背景色填充为白色  
	//warpAffine(src, src_rotate, M, Size(length, length), 1, 0, Scalar(0,0,0));//仿射变换，背景色填充为l黑色
	warpAffine(srcImg, src_rotate, M, Size(length, srcImg.rows), 1, 0, Scalar(0, 0, 0));//仿射变换，背景色填充为l黑色
	//warpAffine(src, src_rotate, M, Size(length, length), 1, 0, Scalar(0, 0, 0));//仿射变换，背景色填充为l黑色

	//imshow("矫正后", src_rotate);
	imshow("new", src_rotate);
	imwrite(pDstFileName.toStdString(), src_rotate); //将矫正后的图片保存下来
}


Mat  CameraCheckWidgets::RotatePic(QString scr_path, QString new_path)
{
	Mat src, src_edge, src_gray, src_rotate;
	Mat gray, binImg;
	double angle;
	src = imread(scr_path.toStdString());
	imshow("文本图片", src);
	cvtColor(src, src_gray, COLOR_RGB2GRAY);
	Canny(src_gray, src_edge, 50, 200, 3);
	imshow("canny", src_edge);

	//通过霍夫变换检测直线
	std::vector<Vec2f> plines;
	//第5个参数就是阈值，阈值越大，检测精度越高
	HoughLines(src_edge, plines, 1, CV_PI / 180, 200, 0, 0);
	//cout << plines.size() << endl;
	//由于图像不同，阈值不好设定，因为阈值设定过高导致无法检测直线，阈值过低直线太多，速度很慢
	//所以根据阈值由大到小设置了三个阈值，如果经过大量试验后，可以固定一个适合的阈值。

	float sum = 0;
	//依次画出每条线段
	for (size_t i = 0; i < plines.size(); i++)
	{
		float rho = plines[i][0];
		float theta = plines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));//cvRound四舍五入
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		sum += theta;
		line(src_gray, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);//Scalar函数用于调节线段颜色         
		imshow("直线探测效果图", src_gray);
		//angle = DegreeTrans(average) - 90;
	}
	float average = sum / plines.size(); //对所有角度求平均，这样做旋转效果会更好
	angle = average / CV_PI * 180 - 90;
	////新建一个感兴趣的区域图，大小跟原图一样大  
	//Mat RoiSrcImg(src.rows, src.cols, CV_8UC3); //注意这里必须选CV_8UC3
	//RoiSrcImg.setTo(0); //颜色都设置为黑色  
	////imshow("新建的ROI", RoiSrcImg);
	////对得到的轮廓填充一下  
	//drawContours(binImg, contours, -1, Scalar(255), CV_FILLED);
	////抠图到RoiSrcImg
	//src.copyTo(RoiSrcImg, binImg);
	//double angle = DegreeTrans(average) - 90;
	//旋转中心为图像中心    
	Point2f center;
	center.x = float(src.cols / 2.0);
	center.y = float(src.rows / 2.0);
	int length = 0;
	length = sqrt(src.cols*src.cols + src.rows*src.rows);
	Mat M = getRotationMatrix2D(center, angle, 1);

	//warpAffine(src, src_rotate, M, Size(length, length), 1, 0, Scalar(255, 255, 255));//仿射变换，背景色填充为白色  
	//warpAffine(src, src_rotate, M, Size(length, length), 1, 0, Scalar(0,0,0));//仿射变换，背景色填充为l黑色
	warpAffine(src, src_rotate, M, Size(length, src.rows), 1, 0, Scalar(0, 0, 0));//仿射变换，背景色填充为l黑色
	return src_rotate;
}


Mat  CameraCheckWidgets::concat(cv::Mat m1, cv::Mat m2)
{
	Mat imgL = m1;//imread("A.jpg");
	Mat imgR = m2;//imread("B.jpg");
	double start = getTickCount();
	Mat grayL, grayR;
	//cvtColor(imgL, grayL, COLOR_BGR2GRAY);
	//cvtColor(imgR, grayR, COLOR_BGR2GRAY);
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
	normalize(matchResult, matchResult, 0, 1, NORM_MINMAX, -1);  //归一化到0--1范围

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
	//cout << "use-time : " << useTime << "s" << endl;

	//imwrite("dst.jpg", dstImg);
	return dstImg;
}
