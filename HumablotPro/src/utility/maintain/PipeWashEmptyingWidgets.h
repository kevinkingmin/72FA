#pragma once

#include <QMainWindow>
#include "ui_PipeWashEmptyingWidgets.h"
#include <QMap>
#include <QButtonGroup>
#include "src/comm/GlobalData.h"
#include <QTimer>
#include <QMessageBox>

class CustomButton;
class InstrumentStateModel;
class Instrument;
class ProgressDialog;

namespace Ui {
	class PipeWashEmptyingWidgetsClass;
}


class PipeWashEmptyingWidgets : public QMainWindow
{
	Q_OBJECT

public:
	PipeWashEmptyingWidgets(QWidget *parent = nullptr);
	~PipeWashEmptyingWidgets();

	using PumpPosState = GlobalData::PumpPosState;
private:
	Ui::PipeWashEmptyingWidgetsClass *ui;

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

	bool all_select_flage = false;

	QVector<int> getCheckBtn();
	QVector<int> mOutVect;
	QVector<int> mOutVect1;

	unsigned short m_vol = 10;

	QTimer *myTimer;//计时器，头文件include
	int index;//倒计时数字
	int mNeed_times;
	//经过几个步骤，都完成后把checkbox状态更新掉。
	int m_step_number = 0;


	//启动标识
	bool PipeWashEmptyingWidgets_start = false;


	bool m_start_pile_wash = false;
	//第二次充灌标识
	bool m_start_pile_wash1 = false;

	bool m_start_pile_wash2 = false;
	bool m_start_pile_wash3 = false;

	int m_finish_wash_number = 0;
	int m_need_wash_number = 0;

	void createPumpBtn(QPushButton *pushButton, bool selected_status);

	ProgressDialog *m_progressDialog;
	void setProgressDialog(ProgressDialog *progressDialog);
};
