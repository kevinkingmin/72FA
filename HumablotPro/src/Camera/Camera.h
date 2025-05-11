#pragma once
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include "ui_Camera.h"
#include "../Include/GenICam/CAPI/SDK.h"
//#include "RGBConvert.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp> 
#include <inttypes.h>
#include "qt_windows.h"
#include <thread>
#include <mutex>
#include "myTimer.h"


class Camera : public QWidget
{
	Q_OBJECT
public:
	Camera(QWidget *parent = Q_NULLPTR);
	~Camera();
protected:
	//这是一个虚函数，继承自QEvent.只要重写了这个虚函数
	void closeEvent(QCloseEvent*event);
	//void paintEvent(QPaintEvent *e);
private:
	Ui::Camera ui;
	QTimer *m_Timer;
	cv::Mat m_srcImage;
	int m_nFrameRate = 1; //图像帧率



	//GENICAM_Camera *pCamera = 0;					            /* 相机对象 */
	//GENICAM_StreamSource *pStreamSource = 0;		            /* 流对象 */
public:
    void DisplayThreadProc();


	

//	void Save(FrameBufferSPtr pDisplayFrame);

	//int32_t setSoftTriggerConf(bool bFlag);
	//int32_t CreateStreamSource(GENICAM_Camera *pGetCamera, GENICAM_StreamSource **ppStreamSource);
private slots:
	void updateImage();
	void on_pushButton_Open_clicked();
	void on_pushButton_Display_clicked();
	void on_pushButton_Display_clicked_back();
	void on_pushButton_Close_clicked();
	void on_pushButton_SaveFile_clicked();
	void on_PushButton_PictureAnalysis_clicked();
	void on_PushButton_ResultList_clicked();
	void on_pushButtonCutImage_clicked();
	void on_pushButton_CameraSetting_clicked();
};
