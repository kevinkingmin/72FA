#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include<QWidget>
#include<QMenuBar>
#include<QToolBar>
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "src/main/subDialog/ShowImageDialog.h"
#include "../Include/TCPClient/TCPClient.h"
#include "WorkerThread.h"

class Camera;
class ReagentWidget;
class UtilityWidget;
class SignalAndSlotHandle;
class SampleWidget;
class Instrument;
class ProgressDialog;
class PumpCalibrateWidget;
class InitiPaperPosThread;
class WeekMaintenanceWidgets;
class MonthMaintenanceWidgets;
class NewPumpRunningWidgets;
class SelfCheckResultShowDialog;

class PipeRefluxWidgets;
class PipeWashWidgets;// *_pipeWashWidgets;
class PipeWashEmptyingWidgets;

class PumpAutoCheckWidgets;// *_pumpAutoCheckWidgets;
class PumpManaCheckWidgets;// *_pumpManaCheckWidgets;
class LiquidDetectionWidgets;// *_liquidDetectionWidgets;
class CameraCheckWidgets;

class TestResultDataAll;
class ManualIncubationWidgets;
class SystemLiquidPipeWashWidgets;


namespace Ui{
    class MainWidget;
}

class MainWidget:public QWidget {
    Q_OBJECT
public:
    typedef enum{
        //基础信息维护
        MENU_ID_SYSTEMSET=0,//【系统参数配制】
        MENU_ID_MAGIC, // 【膜条管理】
        MENU_ID_REAGENT,//【试剂管理】
		MENU_ID_RESULTINFO,//【报告管理】-》【报告管理】
        MENU_ID_SAMPLETUBE,//【样本管管理】-》【报告管理】
        MENU_ID_CAMERA,//【相机参数设置】
		MENU_ID_RULESETTING,//【规则设置】
        //仪器维护
        MENU_ID_SYSTEMLIQUID,//系统液
        MENU_ID_PUMP,//泵启动中
        MENU_ID_PUMP_CALIBRATE,//泵自动校准

		MENU_ID_LIQUID_DETECTION,
		MENU_ID_PERISTALTIC_PUMP_MANA_CHECK,
		MENU_ID_PERISTALTIC_PUMP_AUTO_CHECK,
		MENU_ID_PIPE_WASH,
		MENU_ID_PIPE_REFLUX,
		MENU_ID_SYSTEM_LIQUID_PIPE_WASH,

        MENU_ID_WEEK_MANTAINCE,//周维护
        MENU_ID_MONTH_MANTAINCE,//月维护
		MENU_ID_NEW_PUMP_RUNNING_IN,//新泵磨合

		MENU_ID_CAMERA_CHECK,//相机校准


        MENU_ID_SELFRUNCHECK,//运行自测试
        //历史记录
        MENU_ID_TESTRECORD,//系统液
        MENU_ID_MAINTANCERECORD,//维护历史
        MENU_ID_COMMUNICATERECORD,//外部系统的通信列表
        MENU_ID_SOLUTIONRECORD,//方案
        //编辑
        MENU_ID_EDITGROUP,//试验组列表
        MENU_ID_EDITTEST,//试验记录
        MENU_ID_EDITREAGENT,//试剂记录
        MENU_ID_EDITTUPE,//试管记录
        //应用管理
        MENU_ID_APPLICATION_LOGING,//登录
        MENU_ID_APPLICATION_PASSWORD,//密码更改
        MENU_ID_APPLICATION_USERS,//用户名单
		MENU_ID_APPLICATION_LIS,//用户名单
        MENU_ID_APPLICATION_SET,//设置
        MENU_ID_APPLICATION_CARDSET,//标记卡阅读器设置
        MENU_ID_APPLICATION_CODEADD,//代码录入
        MENU_ID_APPLICATION_ABOUT,//关于应用程序
		MENU_ID_APPLICATION_WELCOME,//关于应用程序
		MENU_ID_APPLICATION_TECHSUPPORT,
		MENU_ID_APPLICATION_HELPMANUAL,
		MENU_ID_APPLICATION_SOFTWAREINFO,
		MENU_ID_APPLICATION_ALARMINFO,
		MENU_ID_APPLICATION_MAN_INCUBAT,//手动孵育
		MENU_ID_APPLICATION_OPERATELOG,
		MENU_ID_APPLICATION_PIPEWASHEMPTY
		//获得支持服务")	
		//查看说明书")	
		//查看软件信息"
		//报警信息)	

    }MENUITEMID;

    typedef  enum
    {
        STACK_PAGE_MENU=0,//菜单
        STACK_PAGE_SAMPLE,//样本管理
    }ENUMSTACKPAGE;

    explicit MainWidget(QWidget *parent, int iFlage,QString userName);
    ~MainWidget();
    using enumState=InstrumentStateModel::enumState;
    void setIndicateLight();
	//用户权限控制
	void authorizedControl();
protected:
    void timerEvent(QTimerEvent *event);
signals:
    void sglLogout();
    void sglMini();
    void sglShowMsgDialog(QString str);
	void sglReActiveMainWindow();
	void sglUpdateTestResultMainWidget(QString a, QString b);
	//刷新SampleWidget窗中的列表
	void sglRefresh_SampleWidget();
	void sglAlarmInfo_SampleWidget(QString a,QString code_type);

public slots:
	void sltUpdateTestResultDataListFromMainWindow(QString a, QString b);
	void slotUpdateSampleWidgetUi();
	void slotMaintainStep(int index, QString des);
private slots:
    void sendDataToServer(const QString &data);
    void slotConnectStatus(bool status);
    void slotLeavePage(int index);
    void on_pBtnLogout_clicked();
    void on_pBtnMini_clicked();
    void on_pBtnAbout_clicked();
    void on_pBtnExit_clicked();
	void slotSoftClose(bool isSuccess);
    void on_pBtnClose_clicked();
    //void on_btnInit_clicked();
	void on_btnReturnMain_clicked();
	//void on_btnPause_clicked();

	void on_btnCloseBeep1_clicked();

	void on_pushButton_osk_open_clicked();
	

	void on_btnSystemLiquidStatus_clicked();
	void on_btnRunState_clicked();
	void on_btnWasteBottle_clicked();
    void removeSubTab(int index);
	void onTabChanged(int index);

    void OnAction_SystemSet();
    void OnAction_MagicManage();
    void OnAction_ReagentManager();
    void OnAction_TubeManage();
    void OnAction_Camera();
	void OnAction_RulesSetting();
    void OnAction_systemLiquid();
    void OnAction_pump();



    void OnAction_pump_calibrate();

	void OnAction_pipe_wash();
	void OnAction_pipe_reflux();
	void OnAction_system_liquid_pipe_wash();
	void OnAction_pump_auto_check();
	void OnAction_pump_mana_check();
	void OnAction_liquid_detection();

    void OnAction_week_mantace();
    void OnAction_month_mantace();
	void OnActive_new_pump_running_in();
    void OnAction_selfRunCheck();
	void OnAction_CloseBeep();
	void OnActive_camera_check();

    void OnAction_testRecord();
    void OnAction_maintaceRecord();
    void OnAction_communicateRecord();
    void OnAction_solutionRecord();
    void OnAction_editGroup();
    void OnAction_editTest();
    void OnAction_editReagent();
    void OnAction_editTupe();
    void OnAction_applicationLogin();
    void OnAction_applicationPassword();
    void OnAction_applicationUsers();
	void OnAction_LisSetting();
    void OnAction_applicationSet();
    void OnAction_applicationCardSet();
    void OnAction_applicationCodeAdd();
    void OnAction_applicationAbout();
	void OnAction_applicationTechSupport();
	void OnAction_applicationHelpManual();
	void OnAction_applicationSoftwareInfo();
    void on_btnSample_clicked();
	void OnAction_ResultManage();
	void OnAction_OperatorLog();
	void OnAction_ManIncubation();//手动孵育
    void on_btnMonthMaintain_clicked();
    void slotMonthMaintain(int result);
	void slotAlarmInfo(int alarmFlage);
	void slotMinitorTemperature(float temperature);//温度监测
	void slotMinitorSensorState(ushort code, bool isSucess);
	//void slotUpdateMainWidgetCoverOpenStatus(int status);
	void slotGetSampleBarCode(QString barCode);


private:
    void initUI();
    void initMenuBar();
    int checkWidgetIndex(MENUITEMID id);
    inline void addTabWidget(QWidget *w, const QString &tabName, const MENUITEMID id);
    void actionClick(MENUITEMID id, const QString &actName, QWidget *w);
    void createBaseSetMenu();//基础信息维护
    void createMantanceMenu();//仪器维护
    void createHistoryMenu();//历史记录
    void createEditMenu();//编辑
    void createApplicationMenu();//应用管理
	void createApplicationHelp();//帮助
	//1为周维护，2为月维护
	void maintainStart(int type);

private:
    Ui::MainWidget *_ui;
    int _timerId;
    int _currentCloseSteps;
    int _totalCloseSteps;
    bool _twinkleFlag;

    QMenuBar *m_pMenuBar;

	QToolBar *m_pToolBar;

	QString toolbar_v_styleString;

	QToolButton* fileButton1;
	QToolButton* fileButton2;
	QToolButton* fileButton3;
	QToolButton* fileButton4;
	QToolButton* fileButton5;
	QToolButton* fileButton6;

    SampleWidget *m_sampleWidget;
    InstrumentStateModel *_InstrumentState;
    Instrument *_instr;
	ShowImageDialog *_mShowImageDialog;

public:
	int _userFlage = 1;
	int m_open_key_word = 0;
	QString mUserName = "";
	int mOpenSoftwareInitFlage = 1;//1为未开机初始化，2为已经开机初始化。
	int mActiveQuery = 2;   //主动查询 ，启动软件时主动查一下状态，并做相应的提示，2为主动查询完成，如果为3就一直不查，也就是点了忽略
	int _maintainStep;
	ProgressDialog *m_progressDialog;
	int _maintainType;
	PumpCalibrateWidget *_pumpCalibrateWidget;
	WeekMaintenanceWidgets *_weekMaintenanceWidgets;
	MonthMaintenanceWidgets *_monthMaintenanceWidgets;
	NewPumpRunningWidgets *_newPumpRunninInWidgets;
	CameraCheckWidgets *_cameraCheckWidgets;

	PipeWashWidgets *_pipeWashWidgets;
	PipeRefluxWidgets *_pipeRefluxWidgets;
	PipeWashEmptyingWidgets *_PipeWashEmptyingWidgets;

	PumpAutoCheckWidgets *_pumpAutoCheckWidgets;
	PumpManaCheckWidgets *_pumpManaCheckWidgets;
	LiquidDetectionWidgets *_liquidDetectionWidgets;
	SelfCheckResultShowDialog *_mSelfCheckResultShowDialog;

	ManualIncubationWidgets *_mManualIncubationWidgets;
	SystemLiquidPipeWashWidgets *_mSystemLiquidPipeWashWidgets;

	QVector<QString> mCheckInfoVector;

	/*因为样式表字符串只能有一个,
	 * 这里我采用拼接的方式,有一个总样式表,
	 * 每次新添加样式表,就添加到总样式表字符串中
	 * 最后直接设置总样式就行
	*/
	QString globel_styleString = "";
	//用来设置样式表的函数:

	QString g_language_type = "";
    TcpClient *m_tcpClient;
    WorkerThread *m_workerThread;
    TestResultDataAll *_mTestResultDataAll;

public:
	void autoSelfCheck();
    void autoSelfCheckResult(QString code);
    void MonthMaintenResult(QString code);
    void shutdownMaintenResult(QString code);
    void onLiquidState(QString state);
    void WeekMaintenResult(QString code);
    void systemPipWashResult(QString code);
    void pipWashResult(QString code);
    void pipFlowbackResultResult(QString code);

    void onMachineCode(QString code);
	void killTimerLs(int timeId);
	void writeAlarmInfo(QString sz, QString fileName);
	void inquireSensorStateMain();
	void openWelcomeWidgets();

	void stopInstrument();
	void pauseInstrument();
	void continueInstrument();

	void add_styleString(QString fileName);

	//01	严重警报	整机立即停机
	//02	一般警报	设备暂停
	//FD	警告	向用户提出告警提示，标记可能受影响的项目
	//FE	警告	向用户提出告警提示
	//FF	记录	后台记录告警信息

	void alarmDeal(int code_level,QString tip_content);
	void ChangWidgetsStartStatus();
	//virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	//virtual bool eventFilter(QObject *, QEvent *);
};

#endif //MAIN_WIDGET_H
