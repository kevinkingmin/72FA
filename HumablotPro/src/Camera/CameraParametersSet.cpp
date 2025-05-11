#include "..\Include\Precomp\precompile.h"
#include "CameraParametersSet.h"
#include <iostream>
#include <exception>
#include <QSettings>
#include <QMessageBox>
#include <exception>
#include "../Include/Utilities/log.h"
#include "src/comm/GlobalData.h"


CameraParametersSet::CameraParametersSet(QObject *parent)
	: QObject(parent)
{
}

CameraParametersSet::~CameraParametersSet()
{
}



int CameraParametersSet::SetCameraParameterAll(GENICAM_Camera *pCamera)
{
	m_pCamera = pCamera;
	QString exe_path = GlobalData::getExePath() + "/config/CameraConfig.ini";
	QSettings config_set(exe_path, QSettings::IniFormat);

	int nResult = 0;
	double dParameterValue;
	int nParameterValue;
	config_set.beginGroup("Camera");

	nParameterValue = config_set.value("AcquisitionFrameRateEnable").toInt();
	nResult = SetCameraParameter_AcquisitionFrameRateEnable(nParameterValue);	//设置图像帧率设置可否
	if (nResult != 0)
	{
		QMessageBox::warning(0, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "设置相机参数图像帧率设置可否失败！", QMessageBox::Ok);
		return -1;
	}

	dParameterValue = config_set.value("AcquisitionFrameRate").toDouble();

	m_nFrameRate = dParameterValue;

	nResult = SetCameraParameter_AcquisitionFrameRate(dParameterValue);//设置图像帧率
	if (nResult != 0)
	{
		QMessageBox::warning(0, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "设置相机参数图像帧率失败！", QMessageBox::Ok);
		return -1;
	}

	dParameterValue = config_set.value("ExposureTime").toDouble();
	nResult = SetCameraParameter_ExposureTime(dParameterValue);//设置曝光时间
	if (nResult != 0)
	{
		QMessageBox::warning(0, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "设置相机参数曝光时间失败！", QMessageBox::Ok);
		return -1;
	}

	dParameterValue = config_set.value("GainRaw").toDouble();
	nResult = SetCameraParameter_GainRaw(dParameterValue);//设置增益
	if (nResult != 0)
	{
		QMessageBox::warning(0, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "设置相机参数增益失败！", QMessageBox::Ok);
		return -1;
	}

	dParameterValue = config_set.value("Gamma").toDouble();
	nResult = SetCameraParameter_Gamma(dParameterValue);//设置图像伽马值
	if (nResult != 0)
	{
		QMessageBox::warning(0, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "设置相机参数伽马值失败！", QMessageBox::Ok);
		return -1;
	}

	nParameterValue = config_set.value("Brightness").toInt();
	nResult = SetCameraParameter_Brightness(nParameterValue);	//设置亮度
	if (nResult != 0)
	{
		QMessageBox::warning(0, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "设置相机参数亮度失败！", QMessageBox::Ok);
		return -1;
	}

	//nParameterValue = config_set.value("ContrastMode").toInt();
	//nResult = SetCameraParameter_ContrastMode(nParameterValue);	//设置对比度膜式
	//if (nResult != 0)
	//{
	//	QMessageBox::warning(0, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "设置相机参数对比度膜式失败！", QMessageBox::Ok);
	//	return -1;
	//}

	nParameterValue = config_set.value("Contrast").toInt();
	nResult = SetCameraParameter_Contrast(nParameterValue);	//设置对比度
	if (nResult != 0)
	{
		QMessageBox::warning(0, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "设置相机参数对比度失败！", QMessageBox::Ok);
		return -1;
	}

	nParameterValue = config_set.value("ContrastThreshold").toInt();
	nResult = SetCameraParameter_ContrastThreshold(nParameterValue);	//设置对比度阈值
	if (nResult != 0)
	{
		QMessageBox::warning(0, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "设置相机参数对比度阈值失败！", QMessageBox::Ok);
		return -1;
	}


}

//设置图像帧率
int CameraParametersSet::SetCameraParameter_AcquisitionFrameRate(double dParameterValue)
{
	int32_t isDoubleNodeSuccess;
	double exposureTimeValue;
	GENICAM_DoubleNode *pDoubleNode = 0;
	GENICAM_DoubleNodeInfo doubleNodeInfo = { 0 };

	doubleNodeInfo.pCamera = m_pCamera;
	memcpy(doubleNodeInfo.attrName, "AcquisitionFrameRate", sizeof("AcquisitionFrameRate"));

	isDoubleNodeSuccess = GENICAM_createDoubleNode(&doubleNodeInfo, &pDoubleNode);
	if (isDoubleNodeSuccess != 0)
	{
		//printf("GENICAM_createDoubleNode fail.\n");
		return -1;
	}


	isDoubleNodeSuccess = pDoubleNode->setValue(pDoubleNode, dParameterValue);
	if (0 != isDoubleNodeSuccess)
	{
		//printf("set ExposureTime fail.\n");
		//注意：需要释放pDoubleNode内部对象内存
		pDoubleNode->release(pDoubleNode);
		return -1;
	}



	return 0;
}

//设置曝光时间
int CameraParametersSet::SetCameraParameter_ExposureTime(double dParameterValue)
{
	int32_t isDoubleNodeSuccess;
	double exposureTimeValue;
	GENICAM_DoubleNode *pDoubleNode = NULL;
	GENICAM_DoubleNodeInfo doubleNodeInfo = { 0 };

	doubleNodeInfo.pCamera = m_pCamera;
	memcpy(doubleNodeInfo.attrName, "ExposureTime", sizeof("ExposureTime"));

	isDoubleNodeSuccess = GENICAM_createDoubleNode(&doubleNodeInfo, &pDoubleNode);
	if (isDoubleNodeSuccess != 0)
	{
		//printf("GENICAM_createDoubleNode fail.\n");
		return -1;
	}


	isDoubleNodeSuccess = pDoubleNode->setValue(pDoubleNode, dParameterValue);
	if (0 != isDoubleNodeSuccess)
	{
		//printf("set ExposureTime fail.\n");
		//注意：需要释放pDoubleNode内部对象内存
		pDoubleNode->release(pDoubleNode);
		return -1;
	}
	return 0;
}

//设置增益
int CameraParametersSet::SetCameraParameter_GainRaw(double dParameterValue)
{
	int32_t isDoubleNodeSuccess;
	double exposureTimeValue;
	GENICAM_DoubleNode *pDoubleNode = NULL;
	GENICAM_DoubleNodeInfo doubleNodeInfo = { 0 };

	doubleNodeInfo.pCamera = m_pCamera;
	memcpy(doubleNodeInfo.attrName, "GainRaw", sizeof("GainRaw"));

	isDoubleNodeSuccess = GENICAM_createDoubleNode(&doubleNodeInfo, &pDoubleNode);
	if (isDoubleNodeSuccess != 0)
	{
		//printf("GENICAM_createDoubleNode fail.\n");
		return -1;
	}

	isDoubleNodeSuccess = pDoubleNode->setValue(pDoubleNode, dParameterValue);
	if (0 != isDoubleNodeSuccess)
	{
		//printf("set ExposureTime fail.\n");
		//注意：需要释放pDoubleNode内部对象内存
		pDoubleNode->release(pDoubleNode);
		return -1;
	}
	return 0;
}

//设置伽马值
int CameraParametersSet::SetCameraParameter_Gamma(double dParameterValue)
{
	int32_t isDoubleNodeSuccess;
	double exposureTimeValue;
	GENICAM_DoubleNode *pDoubleNode = NULL;
	GENICAM_DoubleNodeInfo doubleNodeInfo = { 0 };

	doubleNodeInfo.pCamera = m_pCamera;
	memcpy(doubleNodeInfo.attrName, "Gamma", sizeof("Gamma"));

	isDoubleNodeSuccess = GENICAM_createDoubleNode(&doubleNodeInfo, &pDoubleNode);
	if (isDoubleNodeSuccess != 0)
	{
		//printf("GENICAM_createDoubleNode fail.\n");
		return -1;
	}


	isDoubleNodeSuccess = pDoubleNode->setValue(pDoubleNode, dParameterValue);
	if (0 != isDoubleNodeSuccess)
	{
		//printf("set ExposureTime fail.\n");
		//注意：需要释放pDoubleNode内部对象内存
		pDoubleNode->release(pDoubleNode);
		return -1;
	}



	return 0;
}

//设置图像帧率设置可否
int CameraParametersSet::SetCameraParameter_AcquisitionFrameRateEnable(int nParameterValue)
{
	int32_t isIntNodeSuccess;
	int64_t widthValue;
	GENICAM_BoolNode *pBoolNode = 0;
	GENICAM_BoolNodeInfo boolNodeInfo = { 0 };

	boolNodeInfo.pCamera = m_pCamera;
	memcpy(boolNodeInfo.attrName, "AcquisitionFrameRateEnable", sizeof("AcquisitionFrameRateEnable"));

	isIntNodeSuccess = GENICAM_createBoolNode(&boolNodeInfo, &pBoolNode);

	if (0 != isIntNodeSuccess)
	{
		//printf("GENICAM_createIntNode fail.\n");
		return -1;
	}

	isIntNodeSuccess = pBoolNode->setValue(pBoolNode, (nParameterValue));
	if (0 != isIntNodeSuccess)
	{
		//printf("set Width fail.\n");
		//注意：需要释放pBoolNode内部对象内存
		pBoolNode->release(pBoolNode);
		return -1;
	}



	return 0;
}

//亮度
int CameraParametersSet::SetCameraParameter_Brightness(int nParameterValue)
{
	int32_t isIntNodeSuccess;
	int64_t widthValue;
	GENICAM_IntNode *pIntNode = 0;
	GENICAM_IntNodeInfo intNodeInfo = { 0 };

	intNodeInfo.pCamera = m_pCamera;
	memcpy(intNodeInfo.attrName, "Brightness", sizeof("Brightness"));

	isIntNodeSuccess = GENICAM_createIntNode(&intNodeInfo, &pIntNode);
	if (0 != isIntNodeSuccess)
	{
		//printf("GENICAM_createIntNode fail.\n");
		return -1;
	}


	isIntNodeSuccess = pIntNode->setValue(pIntNode, (nParameterValue));
	if (0 != isIntNodeSuccess)
	{
		//printf("set Width fail.\n");
		//注意：需要释放pIntNode内部对象内存
		pIntNode->release(pIntNode);
		return -1;
	}



	return 0;
}

//对比度
int CameraParametersSet::SetCameraParameter_Contrast(int nParameterValue)
{
	int32_t isIntNodeSuccess;
	int64_t widthValue;
	GENICAM_IntNode *pIntNode = 0;
	GENICAM_IntNodeInfo intNodeInfo = { 0 };

	intNodeInfo.pCamera = m_pCamera;
	memcpy(intNodeInfo.attrName, "Contrast", sizeof("Contrast"));

	isIntNodeSuccess = GENICAM_createIntNode(&intNodeInfo, &pIntNode);
	if (0 != isIntNodeSuccess)
	{
		//printf("GENICAM_createIntNode fail.\n");
		return -1;
	}


	isIntNodeSuccess = pIntNode->setValue(pIntNode, (nParameterValue));
	if (0 != isIntNodeSuccess)
	{
		//printf("set Width fail.\n");
		//注意：需要释放pIntNode内部对象内存
		pIntNode->release(pIntNode);
		return -1;
	}



	return 0;
}

//对比度膜式
int CameraParametersSet::SetCameraParameter_ContrastMode(int nParameterValue)
{
	int32_t isIntNodeSuccess;
	int64_t widthValue;
	GENICAM_BoolNode *pBoolNode = 0;
	GENICAM_BoolNodeInfo boolNodeInfo = { 0 };

	boolNodeInfo.pCamera = m_pCamera;
	memcpy(boolNodeInfo.attrName, "ContrastMode", sizeof("ContrastMode"));

	isIntNodeSuccess = GENICAM_createBoolNode(&boolNodeInfo, &pBoolNode);
	if (0 != isIntNodeSuccess)
	{
		//printf("GENICAM_createIntNode fail.\n");
		return -1;
	}


	isIntNodeSuccess = pBoolNode->setValue(pBoolNode, (nParameterValue));
	if (0 != isIntNodeSuccess)
	{
		//printf("set Width fail.\n");
		//注意：需要释放pBoolNode内部对象内存
		pBoolNode->release(pBoolNode);
		return -1;
	}



	return 0;
}

//对比度阈值
int CameraParametersSet::SetCameraParameter_ContrastThreshold(int nParameterValue)
{
	int32_t isIntNodeSuccess;
	int64_t widthValue;
	GENICAM_IntNode *pIntNode = 0;
	GENICAM_IntNodeInfo intNodeInfo = { 0 };


	intNodeInfo.pCamera = m_pCamera;
	memcpy(intNodeInfo.attrName, "ContrastThreshold", sizeof("ContrastThreshold"));

	isIntNodeSuccess = GENICAM_createIntNode(&intNodeInfo, &pIntNode);
	if (0 != isIntNodeSuccess)
	{
		//printf("GENICAM_createIntNode fail.\n");
		return -1;
	}


	isIntNodeSuccess = pIntNode->setValue(pIntNode, (nParameterValue));
	if (0 != isIntNodeSuccess)
	{
		//printf("set Width fail.\n");
		//注意：需要释放pIntNode内部对象内存
		pIntNode->release(pIntNode);
		return -1;
	}



	return 0;
}


int CameraParametersSet::SetCameraWidthParameter()
{
	int32_t isIntNodeSuccess;
	int64_t widthValue;
	GENICAM_IntNode *pIntNode = 0;
	GENICAM_IntNodeInfo intNodeInfo = { 0 };

	intNodeInfo.pCamera = m_pCamera;
	memcpy(intNodeInfo.attrName, "Width", sizeof("Width"));

	isIntNodeSuccess = GENICAM_createIntNode(&intNodeInfo, &pIntNode);
	if (0 != isIntNodeSuccess)
	{
		//printf("GENICAM_createIntNode fail.\n");
		return -1;
	}

	widthValue = 0;
	isIntNodeSuccess = pIntNode->getValue(pIntNode, &widthValue);
	if (0 != isIntNodeSuccess)
	{
		//printf("get Width fail.\n");
		//注意：需要释放pIntNode内部对象内存
		pIntNode->release(pIntNode);
		return -1;
	}
	else
	{
		//printf("before change ,Width is %d\n", widthValue);
	}

	isIntNodeSuccess = pIntNode->setValue(pIntNode, (widthValue - 8));
	//isIntNodeSuccess = pIntNode->setValue(pIntNode, (widthValue*2));
	if (0 != isIntNodeSuccess)
	{
		//printf("set Width fail.\n");
		//注意：需要释放pIntNode内部对象内存
		pIntNode->release(pIntNode);
		return -1;
	}

	isIntNodeSuccess = pIntNode->getValue(pIntNode, &widthValue);
	if (0 != isIntNodeSuccess)
	{
		//printf("get Width fail.\n");
		//注意：需要释放pIntNode内部对象内存
		pIntNode->release(pIntNode);
		return -1;
	}
	else
	{
		//printf("after change ,Width is %d\n", widthValue);
		//注意：需要释放pIntNode内部对象内存
		pIntNode->release(pIntNode);
	}

	return 0;

}

