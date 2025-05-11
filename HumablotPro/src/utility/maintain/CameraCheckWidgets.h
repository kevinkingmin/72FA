#pragma once

#include <QWidget>
#include "ui_CameraCheckWidgets.h"
#include "src/comm/GlobalData.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
//#include "thread/MyThread.h"
#include <QMainWindow>
#include <QThread>
#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc.hpp> 
#include <opencv2/highgui.hpp> 

class Camera;
class CustomButton;
class InstrumentStateModel;
class Instrument;
class ProgressDialog;

namespace Ui {
	class MonthMaintenanceWidgetsClass;
}



class CameraCheckWidgets : public QWidget
{
	Q_OBJECT

public:
	CameraCheckWidgets(QWidget *parent = nullptr);
	~CameraCheckWidgets();

	using enumState = InstrumentStateModel::enumState;

private:
	Ui::CameraCheckWidgetsClass *ui;
public:
	InstrumentStateModel *_InstrumentState;
	Instrument * _instr;
	ProgressDialog *m_progressDialog;
	void setProgressDialog(ProgressDialog *progressDialog);
	void TakePic();
	void ShowPicInfo(QString file_name);
	void ShowPicInfo1(QString file_name);
	int GetGrayValue();
	double GetCameraParameter_ExposureTime();

	void RotatePng(QString scr_path, QString new_path, QString last_path1);
	void RotatePng1(QString scr_path, QString new_path, QString last_path1);
	void GetContoursPic(QString pSrcFileName, QString pDstFileName);
	cv::Mat RotatePic(QString scr_path, QString new_path);
	cv::Mat concat(cv::Mat m1, cv::Mat m2);

	void _onFunction();
	void recv_msg(QString msg);
	bool m_flag = false;

    //Mythread *m_move_pos_thread;//ÉùÃ÷RunPaperPosThread¶ÔÏó

	//Mat grayToRGB(const cv::Mat input_img);


public slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void UpdateSlot(int num);


signals:
	void test_signal();
	void preper_save(CameraCheckWidgets *);



};

