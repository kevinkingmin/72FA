#ifndef PREPAREREAGENTWIDGET_H
#define PREPAREREAGENTWIDGET_H

#include <QWidget>
#include <QMap>
#include <QButtonGroup>
#include <QPushButton>

#include "src/comm/GlobalData.h"


class CustomButton;
class SelectProcessDialog;
class SampleTestModel;
class ReagentModel;
class ProcessReagentModel;
class PrepareReagentDialog;
class ProgressDialog;
class InstrumentStateModel;
class Instrument;

namespace Ui {
class PrepareReagentWidget;
}

class PrepareReagentWidget : public QWidget
{
    Q_OBJECT
public:
	using PumpPosState = GlobalData::PumpPosState;
	using ptrTest = QSharedPointer<SampleTestModel>;
	using pReagent = QSharedPointer<ReagentModel>;
    friend PrepareReagentDialog;
    explicit PrepareReagentWidget(QWidget *parent = nullptr);
    ~PrepareReagentWidget();
protected:
    void showEvent(QShowEvent *e);

	//void showEvent(QShowEvent *event) override {
	//	// 调用父类的showEvent函数，确保基类的功能正常工作
	//	QWidget::showEvent(event);

	//	// 在这里可以调用你要执行的特定函数
	//	move_chk_position();
	//}

	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *event);
signals:
    void sglPumpStateChanged();//用来更新TestSampleWidget::btnFlushWidget
	void ChangeBtnNextSignal(bool flage);
private slots:
    void on_btnFlash_clicked();
    void on_btnReady_clicked();
    void on_btnDelay_clicked();

	void on_pushButtonSmall_clicked();

	void on_btnWash_clicked();
	void on_btnFill_clicked();

	void on_btnFill_2_clicked();
	
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

	void slot_btnGroupClicked(int i);
	void onWidgetShow();


public:
    void setSelectPDialog(SelectProcessDialog *selectPDialog);
    void createPumpBtn();
	void ShowCountReagentDose(int reagentId,int index,int paper_id);

	void CloseAllLight();

    void setListTest(const QVector<ptrTest> &listTest);
    QVector<ProcessReagentModel> getProcessReagentVect() const;
    QButtonGroup *getBtnGroup() const;
    void setProgressDialog(ProgressDialog *progressDialog);
    void slotPrepareReagentResult(QString code);

private:
    void changeIcon(const QString &fileName,PumpPosState state);
    void changeSystemLiquidIcon();
    void updatePumpBtnByTest();
	QVector<PrepareReagentWidget::pReagent> GetReagentVect();
	void getIncubation();

    QVector<int> getPaperIds();
    bool setReagentWithPump(QVector<int>usedPos,QVector<pReagent>&regentVect);
    ProcessReagentModel getProcessReagentModel(int id,pReagent r,int processParaId,int paperId);
    void updateBtnByReagents(const QVector<pReagent> &reagentVect);

	void createPumpBtn2(QPushButton *pushButton, bool selected_status);

	void move_chk_position();


public:
	bool m_isIrrigate;//系统液是否充灌
	//1为未跳过充灌，2为跳过充灌
	int m_jump_irrigate;
	int m_pump_no;

	bool all_select_flage = false;
	//选择预充灌的泵号。
	//选择预充灌的泵号。
	QMap<int, ushort> m_preview_wash_map;

	//已经完成充灌或是相关操作的泵号
	QMap<int, ushort> m_finish_map;
	//系统液是否跳过或完成了灌注，false未完成，true完成。
	bool m_system_liquid_finish = false;

	QMap<int, int> m_postion_map;

	///试剂未关联标识
	bool m_paper_connect_reagent_flage = false;
	QVector<pReagent> m_reagentVect;
	//void createPumpBtn(QPushButton *pushButton, bool selected_status);
	QString g_language_type = "";

	//酶的数量
	int m_Enzyme_number = 1;

private:
    Ui::PrepareReagentWidget *ui;
    QButtonGroup *_btnGroup;
    QList<uint8_t> pumpList;

    QString _iconPath;
    QString _pixPath;
    SelectProcessDialog *m_selectPDialog;
    QVector<ptrTest> m_listTest;
    QVector<ProcessReagentModel> _processReagentVect;//试剂不重复，如里存在没有分配的泵，则会分配泵信息

    QString _emptyFile;
    QString _flushFile;
    QString _readyFile;
    QString _delayFile;


    ProgressDialog *m_progressDialog;
    Instrument *_instrument;
	InstrumentStateModel *m_instrState;
	///充灌类型，0为大，1为小
	int m_flushing_type = 0;

	QVector<uchar> getCheckBtn();
	QVector<uchar> mOutVect;
};

#endif // PREPAREREAGENTWIDGET_H
