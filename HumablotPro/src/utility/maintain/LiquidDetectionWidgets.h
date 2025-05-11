#pragma once

#include <QWidget>
#include "ui_LiquidDetectionWidgets.h"
#include <QMap>
#include <QButtonGroup>
#include "src/comm/GlobalData.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

class CustomButton;
class InstrumentStateModel;
class Instrument;
class ProgressDialog;

namespace Ui {
	class LiquidDetectionWidgetsClass;
}

class LiquidDetectionWidgets : public QWidget
{
	Q_OBJECT

public:
	LiquidDetectionWidgets(QWidget *parent = nullptr);
	~LiquidDetectionWidgets();
	using PumpPosState = GlobalData::PumpPosState;
	using enumState = InstrumentStateModel::enumState;
private:
	Ui::LiquidDetectionWidgetsClass *ui;


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
	void on_pushButton_clicked();
	void on_pushButton_11_clicked();

	void slotIsStepSuc(int ret);

public:
	int step_index = 0;
	QString _pixPath;
	QString _emptyFile;
	QString _flushFile;
	QString _readyFile;
	QString _delayFile;

	QVector<uchar> getCheckBtn();
	QVector<uchar> mOutVect;

	bool getgetZMotorPara_finish = false;

	bool z_finish_flage = false;
	bool zz_finish_flage = false;
	bool y_finish_flage = false;
	bool x_finish_flage = false;

	int m_action_id = 0;

	bool m_success_flage = false;

	//液位探测开始标识   false为未开始液位探测 ，true为已经开始液位探测。
	bool start_liquid_detection = false;

	//初始化完成标记 true 为完成，false为未初始化。
	bool m_initialize_flage = false;

	bool sample_finish_flage1 = false;
	bool sample_finish_flage2 = false;

	bool sample_finish_flage = false;

	bool sample_arm_suck_finish = false;

	int m_wash_count = 0;


	bool get_pos_value = false;
	bool y_needleWashPos_flage = false;

	bool one_loop_finish = false;
	bool loop_finish = false;

	int m_pos = 0;
	int m_cup_type = 0;
	int m_pump_pos = 0;
	int m_vol = 5;
	int m_loop_number = 1;
	int m_loop_number1 = 1;
	int m_first_value = 0;
	int m_old_value = 0;
	int m_second_value = 0;
	int m_standartCupHeight = 90000, m_bloodingCupHeight = 134000, m_microCupHeight = 92000;
	void createPumpBtn(QPushButton *pushButton, bool selected_status);

	QString pos_info = "";

	ProgressDialog *m_progressDialog;
	void setProgressDialog(ProgressDialog *progressDialog);
};
