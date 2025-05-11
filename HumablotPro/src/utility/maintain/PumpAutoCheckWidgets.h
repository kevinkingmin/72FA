#pragma once

#include <QWidget>
#include "ui_PumpAutoCheckWidgets.h"
#include <QMap>
#include <QButtonGroup>
#include "src/comm/GlobalData.h"

class CustomButton;
class InstrumentStateModel;
class Instrument;
class ProgressDialog;

namespace Ui {
	class PumpAutoCheckWidgetsClass;
}

class PumpAutoCheckWidgets : public QWidget
{
	Q_OBJECT

public:
	PumpAutoCheckWidgets(QWidget *parent = nullptr);
	~PumpAutoCheckWidgets();
	using PumpPosState = GlobalData::PumpPosState;
private:
	Ui::PumpAutoCheckWidgetsClass *ui;


	InstrumentStateModel *_InstrumentState;
	Instrument * _instr;

public slots:
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

	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
	void on_pushButton_7_clicked();
	void on_pushButton_8_clicked();
	void on_pushButton_9_clicked();
	void on_pushButton_10_clicked();

	void on_pushButton_11_clicked();

	void on_pushButton_12_clicked();

	void on_pushButton_13_clicked();
	

	void slotIsStepSuc(int ret, int pumpNo, int fstSteps, int SndSteps);

	void slotIsStepSuc1(int ret);

public:
	int step_index = 0;
	QString _pixPath;
	QString _emptyFile;
	QString _flushFile;
	QString _readyFile;
	QString _delayFile;
	bool all_select_flage = false;


	QVector<uchar> getCheckBtn();
	QVector<uchar> mOutVect;

	bool m_start_pump_auto_check = false;
	int m_finish_pump_auto_check_number = 0;
	int m_need_pump_auto_check_number = 0;

	int m_current_step = 0;
	bool m_current_step_flage = false;
	int m_current_pump_no = 0;

	//Í£Ö¹ÒºÎ»Ì½²â false ½øÐÐÖÐ£¬trueÍ£Ö¹¡£
	bool m_stop_liquid_detect = false;

	bool m_check_pump_status = false;

	ProgressDialog *m_progressDialog;

	void createPumpBtn(QPushButton *pushButton, bool selected_status);
	void setProgressDialog(ProgressDialog *progressDialog);
};
