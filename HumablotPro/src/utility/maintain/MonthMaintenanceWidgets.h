#ifndef MonthMaintenanceWidgets_H
#define MonthMaintenanceWidgets_H

#include <QWidget>
#include <QMap>
#include <QButtonGroup>
#include "ui_MonthMaintenanceWidgets.h"
#include "src/comm/GlobalData.h"

class CustomButton;
class InstrumentStateModel;
class Instrument;
class ProgressDialog;
 
namespace Ui {
	class MonthMaintenanceWidgetsClass;
}


class MonthMaintenanceWidgets : public QWidget
{
	Q_OBJECT

public:
	MonthMaintenanceWidgets(QWidget *parent = nullptr);
	~MonthMaintenanceWidgets();
	using PumpPosState = GlobalData::PumpPosState;
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

	void on_pushButton_clicked();


	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
	void on_pushButton_7_clicked();
	void on_pushButton_8_clicked();
	void on_pushButton_9_clicked();
	void on_pushButton_10_clicked();

	//void on_btn_up_step_clicked();
	void on_btn_down_step_clicked();

	void on_btn_down_step_2_clicked();
	

	void on_btnFlash_clicked();
	void on_btnReady_clicked();
	void on_btnDelay_clicked();

	void slotMonthMaintain(int result);

	void slotPumpCalibrateResult_Month(int pumpNo, int fstSteps, int SndSteps);

	
signals:
	void sglPumpStateChanged();//用来更新TestSampleWidget::btnFlushWidget
	void ChangeBtnNextSignal(bool flage);

	//void Onchk_1State();
	//void Onchk_2State();
	//void Onchk_3State();
	//void Onchk_4State();

private:
	//Ui::MonthMaintenanceWidgetsClass ui;

	Ui::MonthMaintenanceWidgetsClass *ui;
	InstrumentStateModel *_InstrumentState;
	Instrument * _instr;

	QVector<uchar> getCheckBtn();
	QVector<uchar> mOutVect;


public:
	int step_index = 0;
	QString _pixPath;
	QString _emptyFile;
	QString _flushFile;
	QString _readyFile;
	QString _delayFile;

	int _maintainStep;
	int _maintainType;

	QTimer *myTimer;// 定义定时器对象

	bool all_select_flage = false;

	void HideGroupBox();
	void createPumpBtn(QPushButton *pushButton,bool selected_status);
	QButtonGroup *getBtnGroup() const;
	QButtonGroup *_btnGroup;

	void changeIcon(const QString &fileName, PumpPosState state);
	void setCenterImageColor(QImage &image, QColor &color);

	int m_i = 0;
	int m_i_max = 0;
	int m_j = 0;
	bool mMonthMaintenance_run_flage = false;

	bool m_add = false;

	void updateUI();
	bool m_finish_flage = false;

	ProgressDialog *m_progressDialog;
	void setProgressDialog(ProgressDialog *progressDialog);

};
#endif