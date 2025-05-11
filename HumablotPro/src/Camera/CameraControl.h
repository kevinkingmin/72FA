#pragma once

#include <QObject>

#include "../Include/GenICam/CAPI/SDK.h"
#include "RGBConvert.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp> 

using namespace cv;

class CameraControl : public QObject
{
	Q_OBJECT

public:
	CameraControl(QObject *parent);
	~CameraControl();

	int m_nFrameRate = 1; //图像帧率

	bool OpenCamera();

	bool CloseCamera();

	//void CreateOneImage(int nSampleID,  int	nTestPaperID, QString test_project_name);
	void CreateOneImage(QString nSampleID, int	nTestPaperID, QString test_project_name);

	Mat GetOneMat();

	//更改曝光值
	int32_t ModifyCamralExposureTime(GENICAM_Camera *pGetCamera, double exposureTimeValue);

private:




	int32_t CreateStreamSource(GENICAM_Camera *pGetCamera, GENICAM_StreamSource **ppStreamSource);




};
