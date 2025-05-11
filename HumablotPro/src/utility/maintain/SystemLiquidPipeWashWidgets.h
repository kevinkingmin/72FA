#pragma once

#include <QWidget>
#include "ui_SystemLiquidPipeWashWidgets.h"
#include <QMap>
#include <QButtonGroup>
#include "src/comm/GlobalData.h"
#include <QTimer>
#include <QMessageBox>

class CustomButton;
class InstrumentStateModel;
class Instrument;
class ProgressDialog;


class SystemLiquidPipeWashWidgets : public QWidget
{
	Q_OBJECT

public:
	SystemLiquidPipeWashWidgets(QWidget *parent = nullptr);
	~SystemLiquidPipeWashWidgets();

//private:
//	Ui::SystemLiquidPipeWashWidgetsClass ui;

	using PumpPosState = GlobalData::PumpPosState;
private:
	Ui::SystemLiquidPipeWashWidgetsClass *ui;
	InstrumentStateModel *_InstrumentState;
	Instrument * _instr;

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
	void slotIsStepSuc(int ret);

public:
	int step_index = 0;
	QString _pixPath;
	QString _emptyFile;
	QString _flushFile;
	QString _readyFile;
	QString _delayFile;


	QVector<int> getCheckBtn();
	QVector<int> mOutVect;

	unsigned short m_vol = 10;

	QTimer *myTimer;//计时器，头文件include
	int index;//倒计时数字
	int mNeed_times;

	int m_action_id = 0;

	bool m_start_system_liquid_pipe_wash = false;
	int m_finish_system_liquid_pipe_number = 0;
	int m_need_system_liquid_pipe_number = 0;
	void updateUI();
	void createPumpBtn(QPushButton *pushButton, bool selected_status);

	ProgressDialog *m_progressDialog;
	void setProgressDialog(ProgressDialog *progressDialog);

	QString g_language_type = "";
};
