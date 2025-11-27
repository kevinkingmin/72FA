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
    struct ReagentInfoStrt
    {
        // 试剂名
        QString _reagentName;
        // 膜条名称
        QString _paperName;
        // 泵编号
        int _pumpNo;
        // 试剂量
        float _reagentMl;
        // 死枪量
        float _deadMl;
        // 大灌注量
        float _fillingMl;
        // 小灌注量
        float _fillingMlSmall;
        ReagentInfoStrt()
            :_reagentName("")
            ,_paperName("")
            ,_pumpNo(0)
            ,_reagentMl(0)
            ,_deadMl(0)
            ,_fillingMl(0)
            ,_fillingMlSmall(0)
        {}
        ReagentInfoStrt(const QString& reagentName, const QString& paperName, const int pumpNo, const float reagentMl,
                       const float deadMl, const float fillingMl, const float fillingMlSmall)
            :_reagentName(reagentName)
            ,_paperName(paperName)
            ,_pumpNo(pumpNo)
            ,_reagentMl(reagentMl)
            ,_deadMl(deadMl)
            ,_fillingMl(fillingMl)
            ,_fillingMlSmall(fillingMlSmall)
        {}
    };
	using PumpPosState = GlobalData::PumpPosState;
	using ptrTest = QSharedPointer<SampleTestModel>;
	using pReagent = QSharedPointer<ReagentModel>;
    friend PrepareReagentDialog;
    explicit PrepareReagentWidget(QWidget *parent = nullptr);
    ~PrepareReagentWidget();
protected:
    void showEvent(QShowEvent *e);

	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *event);
signals:
    void sglPumpStateChanged();//用来更新TestSampleWidget::btnFlushWidget
	void ChangeBtnNextSignal(bool flage);
private slots:
    void on_btnFlash_clicked();
    void on_btnReady_clicked();
    void on_btnDelay_clicked();

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

	void onWidgetShow();


public:
    void setSelectPDialog(SelectProcessDialog *selectPDialog);
    void createPumpBtn();
    void ShowCountReagentDose(const ReagentInfoStrt& info);

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
//	QVector<PrepareReagentWidget::pReagent> GetReagentVect();

    QVector<int> getPaperIds();
    void updateBtnByReagents();
	void move_chk_position();


public:
	bool m_isIrrigate;//系统液是否充灌
	//1为未跳过充灌，2为跳过充灌
	int m_jump_irrigate;
	int m_pump_no;

    // 全选标记位
	bool all_select_flage = false;
	//选择预充灌的泵号。
	//选择预充灌的泵号。
    // 延时充灌的泵号
	QMap<int, ushort> m_preview_wash_map;

	//已经完成充灌或是相关操作的泵号
	QMap<int, ushort> m_finish_map;
	//系统液是否跳过或完成了灌注，false未完成，true完成。
	bool m_system_liquid_finish = false;

    // 试剂位置对应的选中选项
	QMap<int, int> m_postion_map;

	///试剂未关联标识
	bool m_paper_connect_reagent_flage = false;
    // 流程中用到的试剂
//	QVector<pReagent> m_reagentVect;
	//void createPumpBtn(QPushButton *pushButton, bool selected_status);
    // 语言类型
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
    // 测试列表
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
    // 位置checkbox的选中状态
	QVector<uchar> mOutVect;
    QMap<int, ReagentInfoStrt> _pumpNoReagentMap;


};

#endif // PREPAREREAGENTWIDGET_H
