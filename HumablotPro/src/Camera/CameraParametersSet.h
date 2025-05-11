#pragma once

#include <QObject>

#include "../Include/GenICam/CAPI/SDK.h"
#include "RGBConvert.h"

class CameraParametersSet : public QObject
{
	Q_OBJECT

public:
	CameraParametersSet(QObject *parent);
	~CameraParametersSet();

	int SetCameraParameterAll(GENICAM_Camera *pCamera);

private:

	int m_nFrameRate = 1; //图像帧率

	GENICAM_Camera *m_pCamera = 0;					            /* 相机对象 */

	int SetCameraParameter_AcquisitionFrameRate(double dParameterValue);//设置图像帧率
	int SetCameraParameter_ExposureTime(double dParameterValue);		//设置曝光时间
	int SetCameraParameter_GainRaw(double dParameterValue);				//设置增益
	int SetCameraParameter_Gamma(double dParameterValue);				//图像伽马值

	int SetCameraParameter_AcquisitionFrameRateEnable(int nParameterValue);	//设置图像帧率设置可否
	int SetCameraParameter_Brightness(int nParameterValue);				//亮度
	int SetCameraParameter_Contrast(int nParameterValue);				//对比度
	int SetCameraParameter_ContrastMode(int nParameterValue);			//对比度膜式
	int SetCameraParameter_ContrastThreshold(int nParameterValue);		//对比度阈值

	int SetCameraWidthParameter();
};
