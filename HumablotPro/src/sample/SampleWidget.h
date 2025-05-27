#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QWidget>
#include "../Include/TCPClient/TcpClient.h"

namespace Ui {
class SampleWidget;
}

class InitiPaperPosThread;
class AddSampleWidget;
class TestDataListWidget;
class IrrigationSystemLiquidWidget;
class EmptyWasteBottleWidget;
class PrepareReagentWidget;
class TestSampleWidget;
class SelectProcessDialog;
class PrepareReagentDialog;
class ProgressDialog;
class BatchAddSampleWidgets;

class SampleWidget : public QWidget
{
    Q_OBJECT
    typedef  enum
    {
        STACK_ADD_SAMPLE=0,//添加样本
        STACK_TESTDATALIST,//待测数据
        STACK_PREPAREREAGENT,//试剂准备
        STACK_TESTSAMPLE,//样本测试界面
        STACK_END,//表示最后一个
    }STACKPAGEENUM;

public:
    explicit SampleWidget(QWidget *parent = nullptr);
    ~SampleWidget();
    void setProgressDialog(ProgressDialog *progressDialog);
	///显示功能按钮
	void ShowFunctionBtn(bool status);
	void ReturnSampleEdit();
    void setTcpClient(TcpClient *tcpClient);
public slots:
	void slotReFreshListUi();
	void slotAlarmInfo1(QString alarm_info,QString code_type);
private slots:
    void on_btnPre_clicked();
    void on_btnNext_clicked();
    void on_btnCancel_clicked();
    void on_btnReTest_clicked();
	void on_changebtnNextEnable(bool enable_flage);
	void on_changebtnSaveEnable(bool enable_flage);
	void on_btnDelete_clicked();
	void on_btnDeleteAll_clicked();
	void on_btnSaveAdd_clicked();
	void on_btnReQuestLisAll_clicked();
	void on_btnRequestLis_clicked();
	void on_btnIncubation_clicked();
	void on_btnBatchAdd_clicked();

public:
	friend class InitiPaperPosThread;

signals:
	void sglAlarmInfo(QString info,QString code_type);

private:
    void initUi();
    void stackIndexChange();
private:
    Ui::SampleWidget *ui;
    AddSampleWidget *m_addSampleWidget;
    TestDataListWidget *m_testDataListWidget;
    IrrigationSystemLiquidWidget *m_irrigateSLiquidWidget;
    PrepareReagentWidget *m_prepareReagent;    
    SelectProcessDialog *m_selectPDialog;
    PrepareReagentDialog *m_prepareRDialog;
    TestSampleWidget *m_testSampleWidget;
	InitiPaperPosThread *m_run_paper_pos_thread;
    TcpClient                     *m_tcpClient;
public:
	int mCheckCameraPos = 0;
};

#endif // SAMPLEWIDGET_H
