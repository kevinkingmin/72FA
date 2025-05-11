#pragma once


#include <QWidget>
#include "ui_NewPumpRunningWidgets.h"
#include <QMap>
#include <QButtonGroup>
#include "src/comm/GlobalData.h"
#include <QTimer>
#include <QMessageBox>
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
//#include "../Model.h"


class CustomButton;
//class InstrumentStateModel;
class Instrument;
class ProgressDialog;

namespace Ui {
	class NewPumpRunningWidgetsClass;
}

class NewPumpRunningWidgets : public QWidget
{
	Q_OBJECT

public:
	NewPumpRunningWidgets(QWidget *parent = nullptr);
	~NewPumpRunningWidgets();
	using PumpPosState = GlobalData::PumpPosState;
	using enumState = InstrumentStateModel::enumState;
private:
	Ui::NewPumpRunningWidgetsClass *ui;



public slots:

	void doProcessTimeout();
	void on_chk_1_toggled(bool state);
	void on_chk_2_toggled(bool state);
	void on_chk_3_toggled(bool state);
	void on_chk_4_toggled(bool state);
	void on_chk_5_toggled(bool state);
	void on_chk_6_toggled(bool state);
	void on_chk_7_toggled(bool state);
	void on_chk_8_toggled(bool state);
	void on_chk_9_toggled(bool state);
	void on_cb_all_toggled(bool state);

	//void on_radioButton_toggled(bool state);




	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
	void on_pushButton_7_clicked();
	void on_pushButton_8_clicked();
	void on_pushButton_9_clicked();
	void on_pushButton_10_clicked();

	void on_pushButton_clicked();
	void on_pushButton_11_clicked();
	void on_pushButton_12_clicked();



	void slotIsStepSuc(int ret);


public:
	int step_index = 0;
	QString _pixPath;
	QString _emptyFile;
	QString _flushFile;
	QString _readyFile;
	QString _delayFile;

	bool all_select_flage = false;

	QTimer *myTimer;//计时器，头文件include
	int index;//倒计时数字
	int mNeed_times;

	//true连接信号成功
	bool IsStepSuc_flag = false;
	bool m_start_NewPumpRunningWidgets = false;

	QVector<uchar> getCheckBtn();
	QVector<uchar> mOutVect;
	bool M_need_to_run = false;

	QVector<MotorSpeedPara> m_paras_vector;

	void createPumpBtn(QPushButton *pushButton, bool selected_status);

	ProgressDialog *m_progressDialog;
	void setProgressDialog(ProgressDialog *progressDialog);

	InstrumentStateModel *_InstrumentState;
	Instrument * _instr;
};