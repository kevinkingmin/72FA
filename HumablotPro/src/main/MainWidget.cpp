#include"MainWidget.h"
#include "ui_MainWidget.h"
#include <QMessageBox>
#include <string>
#include <QDateTime>
#include "src/Camera/Camera.h"
#include "src/comm/ObjectTr.h"
#include "src/utility/TestPaperManage.h"
#include "src/utility/ReagentManager.h"
#include "src/utility/TubeManage.h"
#include "src/utility/SystemSet.h"
#include "src/sample/SampleWidget.h"
#include "../Include/Instrument/Instrument.h"
#include "src/utility/ResultManage.h"
#include "src/utility/RulesSetting.h"
#include "src/Camera/TestResultDataManage.h" 
#include "src/Camera/TestResultDataAll.h"
#include "src/main/UserManageWidget.h"
#include "src/main/LisSettingWidgets.h"
#include "src/main/AlarmInfoWidgets.h"
#include "src/utility/QtWidgetstOperateLog.h"
#include "src/main/subDialog/ProgressDialog.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "src/utility/maintain/PumpCalibrateWidget.h"
#include "src/utility/maintain/WeekMaintenanceWidgets.h"
#include "src/utility/maintain/MonthMaintenanceWidgets.h"
#include "src/utility/maintain/NewPumpRunningWidgets.h"
#include "src/utility/maintain/PipeWashWidgets.h"
#include "src/utility/maintain/PipeRefluxWidgets.h"
#include "src/utility/maintain/PipeWashEmptyingWidgets.h"
#include "src/utility/maintain/PumpAutoCheckWidgets.h"
#include "src/utility/maintain/PumpManaCheckWidgets.h"
#include "src/utility/maintain/LiquidDetectionWidgets.h"
#include "src/utility/maintain/CameraCheckWidgets.h"
#include "src/utility/maintain/SystemLiquidPipeWashWidgets.h"
#include <QToolBar>
#include <QToolButton>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QtXml> 
#include <QFileDialog>
#include "src/sample/TestSampleWidget.h"
#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/Camera/CameraControl.h"
#include "src/utility/AboutUsWidgets.h"
#include "src/sample/subDialog/SelfCheckResultShowDialog.h" 
#include "src/sample/subDialog/ManualIncubationWidgets.h"
#include "src/utility/WelcomWidgets.h"
#include "../Include/Utilities/log.h"
#include "../Include/Analysis/analysis.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"



MainWidget::MainWidget(QWidget *parent/*=0*/, int iFlage,QString userName)
    :QWidget(parent)
    , _ui(new Ui::MainWidget)
    , _timerId(0)
    , _currentCloseSteps(0)
    , _totalCloseSteps(0)
    , _twinkleFlag(false)
    , m_pMenuBar(new QMenuBar(this))
    ,m_pToolBar(new QToolBar(this))
    , m_sampleWidget(new SampleWidget(this))
    ,_InstrumentState(InstrumentStateModel::instance())
    ,_instr(Instrument::instance())
    ,_maintainStep(-1)
    ,m_progressDialog(new ProgressDialog(this))
    ,_maintainType(0)
    ,_pumpCalibrateWidget(new PumpCalibrateWidget())
    , _pipeWashWidgets(new PipeWashWidgets())
    , _pipeRefluxWidgets(new PipeRefluxWidgets())
    , _PipeWashEmptyingWidgets(new PipeWashEmptyingWidgets())
    , _pumpAutoCheckWidgets(new PumpAutoCheckWidgets())
    , _pumpManaCheckWidgets(new PumpManaCheckWidgets())
    , _liquidDetectionWidgets(new LiquidDetectionWidgets())
    , _mShowImageDialog(new ShowImageDialog(this))
    , _weekMaintenanceWidgets(new WeekMaintenanceWidgets)
    , _monthMaintenanceWidgets(new MonthMaintenanceWidgets)
    , _newPumpRunninInWidgets(new NewPumpRunningWidgets)
    , _cameraCheckWidgets(new CameraCheckWidgets)
    , _mSelfCheckResultShowDialog(new SelfCheckResultShowDialog)
    , _mSystemLiquidPipeWashWidgets(new SystemLiquidPipeWashWidgets)
    , _mManualIncubationWidgets(new ManualIncubationWidgets(this))
    , m_tcpClient(new TcpClient(this))
    , _mTestResultDataAll(new TestResultDataAll)
{
    _ui->setupUi(this);
    _userFlage = iFlage;
    mUserName = userName;

    auto dao = AnalysisUIDao::instance();
    bool bResult;
    g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
    GlobalData::setLanguageType(g_language_type);
    authorizedControl();
    initUI();
    _timerId = startTimer(1000);
    setWindowState(Qt::WindowMaximized);
    QString userType = "";

    switch (_userFlage)
    {
    case 1:
        userType = GlobalData::LoadLanguageInfo(g_language_type, "K1010");//"管理员";
        break;
    case 2:
        userType = GlobalData::LoadLanguageInfo(g_language_type, "K1011");//"工程师";
        break;
    case 3:
        userType = GlobalData::LoadLanguageInfo(g_language_type, "K1012");//"普通用户";
        break;
    default:
        break;
    }


    QString userName1 = ""+ userType +"：" + userName;
    _ui->lblUser->setText(userName1);
    m_sampleWidget->setProgressDialog(m_progressDialog);
    _pumpCalibrateWidget->setProgressDialog(m_progressDialog);
    _pumpAutoCheckWidgets->setProgressDialog(m_progressDialog);
    _pumpManaCheckWidgets->setProgressDialog(m_progressDialog);
    _weekMaintenanceWidgets->setProgressDialog(m_progressDialog);
    _monthMaintenanceWidgets->setProgressDialog(m_progressDialog);
    _pipeWashWidgets->setProgressDialog(m_progressDialog);
    _liquidDetectionWidgets->setProgressDialog(m_progressDialog);
    _newPumpRunninInWidgets->setProgressDialog(m_progressDialog);
    _pipeRefluxWidgets->setProgressDialog(m_progressDialog);
    _PipeWashEmptyingWidgets->setProgressDialog(m_progressDialog);
    _mSystemLiquidPipeWashWidgets->setProgressDialog(m_progressDialog);

    setWindowTitle("ReceiveMessage");
    connect(_instr, &Instrument::sglMaintainStep, this, &MainWidget::slotMaintainStep);
    connect(_instr, &Instrument::sglSelfCheckResult, this, &MainWidget::autoSelfCheckResult);
    connect(_instr, &Instrument::sglGetMachineCodeResult, this, &MainWidget::onMachineCode);
    connect(_instr, &Instrument::sglMonthMaintenResult, this, &MainWidget::MonthMaintenResult);
    connect(_instr, &Instrument::sglWeekMaintenResult, this, &MainWidget::WeekMaintenResult);
    connect(_instr, &Instrument::sglShutdownMaintenResult, this, &MainWidget::shutdownMaintenResult);
    connect(_instr, &Instrument::sglSystemPipWashResult, this, &MainWidget::systemPipWashResult);
    connect(_instr, &Instrument::sglPipWashResult, this, &MainWidget::pipWashResult);
    connect(_instr, &Instrument::sglPipFlowbackResult, this, &MainWidget::pipFlowbackResultResult);
    connect(_instr, &Instrument::sglOnTemperature, this, &MainWidget::slotMinitorTemperature);
    connect(_instr, &Instrument::sglLiquidState, this, &MainWidget::onLiquidState);
    connect(m_tcpClient, &TcpClient::connectStatus, this, &MainWidget::slotConnectStatus);

    auto ipPm{ SystemSetBLL().getRowById(9995) };
    QString ip = ipPm.isNull()?"": ipPm->getSaveDes();
    auto portPm{ SystemSetBLL().getRowById(9996) };
    int port = portPm.isNull()?0: portPm->getSaveDes().toInt();
    auto lisStartPm{ SystemSetBLL().getRowById(9993) };
    m_tcpClient->setServerAddress(ip, port);
    if (m_tcpClient->m_connectedState)
    {
        _ui->btnLisState->setStyleSheet("QPushButton {qproperty-icon: url(:/images/menu/lisgreen.png);}");
        _ui->btnLisState->setToolTip(GlobalData::LoadLanguageInfo("K1734"));

        // 实例化子线程并启动
        m_workerThread = new WorkerThread(m_tcpClient, this);
        m_workerThread->start();
        connect(m_workerThread, &WorkerThread::sendDataToServer, this, &MainWidget::sendDataToServer, Qt::QueuedConnection);
    }
    else
    {
        _ui->btnLisState->setStyleSheet("QPushButton {qproperty-icon: url(:/images/menu/lisred.png);}");
        _ui->btnLisState->setToolTip(GlobalData::LoadLanguageInfo("K1735"));
    }

    GlobalData::setTcpClient(m_tcpClient);
	GlobalData::reconnect();
    m_sampleWidget->setTcpClient(m_tcpClient);
    _mTestResultDataAll->setTcpClient(m_tcpClient);
    _ui->leftMenuWidget->setVisible(false);
    _ui->btnMonthMaintain->setVisible(false);
    _ui->btnSystemLiquid->setVisible(false);
    bResult = false;
    QString KVersion = GlobalData::LoadLanguageInfo(g_language_type, "KVersion");
    _ui->lbVersion->setText(KVersion);

    _ui->btnCloseBeep1->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1005"));
    _ui->pushButton_osk_open->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1006"));
    _ui->lbTemperature->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1007") + "__.__℃ ");

    _ui->btnRunState->setStyleSheet("border:none");
    _ui->btnWasteBottle->setStyleSheet("border:none");
    _ui->btnSystemLiquidStatus->setStyleSheet("border:none");
    _ui->btnSystemLiquid->setStyleSheet("border:none");

    _ui->btnRunState->resize(200, 200);
    _ui->btnWasteBottle->resize(200, 200);
    _ui->btnSystemLiquidStatus->resize(200, 200);
    _ui->btnSystemLiquid->resize(200, 200);
}
//1，废液报警 2，废液正常 3，系统液报警 4，系统液正常
void MainWidget::onLiquidState(QString state){
    if(state=="1"){
        _ui->btnWasteBottle->setToolTip(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f01"));
        _ui->btnWasteBottle->setStyleSheet("QPushButton{ qproperty-icon: url(:/images/menu/wasteBottleFull.png);}");
    }else if(state=="2"){
        _ui->btnWasteBottle->setToolTip(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f04"));
        _ui->btnWasteBottle->setStyleSheet("QPushButton{ qproperty-icon: url(:/images/menu/wasteBottle.png);}");
    }else if(state=="3"){
        _ui->btnSystemLiquidStatus->setToolTip(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f02"));
        _ui->btnSystemLiquidStatus->setStyleSheet("QPushButton {qproperty-icon: url(:/images/menu/systemLiquidStatusNoFull.png);}");
    }else if(state=="4"){
        _ui->btnSystemLiquidStatus->setToolTip(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f05"));
        _ui->btnSystemLiquidStatus->setStyleSheet("QPushButton {qproperty-icon: url(:/images/menu/systemLiquidStatusFull.png);}");
    }
}

void MainWidget::slotMaintainStep(int index, QString des)
{
    if (index == 11 && des != "HumaDX 72FA")
    {
        //1640失败
        mCheckInfoVector.push_back(GlobalData::LoadLanguageInfo(g_language_type, "K1640"));//"扫码失败");
    }
    else if (des == "HumaDX 72FA")
    {
        //1641成功
        mCheckInfoVector.push_back(GlobalData::LoadLanguageInfo(g_language_type, "K1641"));//"扫码成功");
    }
    else
    {
        mCheckInfoVector.push_back(des);
    }
}

void MainWidget::sendDataToServer(const QString &data)
{
    m_tcpClient->sendData(data);
}

void MainWidget::slotConnectStatus(bool status)
{
    if (status)
    {
        _ui->btnLisState->setStyleSheet("QPushButton {qproperty-icon: url(:/images/menu/lisgreen.png);}");
        _ui->btnLisState->setToolTip(GlobalData::LoadLanguageInfo("K1734"));
        m_tcpClient->m_connectedState = true;
    }
    else
    {
        _ui->btnLisState->setStyleSheet("QPushButton {qproperty-icon: url(:/images/menu/lisred.png);}");
        _ui->btnLisState->setToolTip(GlobalData::LoadLanguageInfo("K1735"));
        m_tcpClient->m_connectedState = false;
    }
}

void MainWidget::authorizedControl()
{

}

MainWidget::~MainWidget()
{
    if (nullptr != _ui)
        delete _ui;
    delete _pumpCalibrateWidget;
    _pumpCalibrateWidget = nullptr;
    delete _weekMaintenanceWidgets;
    _weekMaintenanceWidgets = nullptr;
    delete _monthMaintenanceWidgets;
    _monthMaintenanceWidgets = nullptr;
    delete _newPumpRunninInWidgets;
    _newPumpRunninInWidgets = nullptr;
    delete _cameraCheckWidgets;
    _cameraCheckWidgets = nullptr;
    delete _pipeWashWidgets;
    _pipeWashWidgets = nullptr;
    delete _pipeRefluxWidgets;
    _pipeRefluxWidgets = nullptr;
    delete _PipeWashEmptyingWidgets;
    _PipeWashEmptyingWidgets = nullptr;
    delete _pumpAutoCheckWidgets;
    _pumpAutoCheckWidgets = nullptr;
    delete _pumpManaCheckWidgets;
    _pumpManaCheckWidgets = nullptr;
    delete _liquidDetectionWidgets;
    _liquidDetectionWidgets = nullptr;
    delete _mSystemLiquidPipeWashWidgets;
    _mSystemLiquidPipeWashWidgets = nullptr;
    delete _mTestResultDataAll;
    _mTestResultDataAll = nullptr;
    killTimer(_timerId);
}

void MainWidget::killTimerLs(int timeId)
{

}

// 在YourClass中创建一个槽函数来响应选项卡切换信号
void MainWidget::onTabChanged(int index)
{
    // 在这里添加处理选项卡切换时的代码
    ChangWidgetsStartStatus();
}

void MainWidget::initMenuBar()
{
    _ui->tabWidget->setTabsClosable(true);
    connect(_ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));
    connect(_ui->tabWidget, &QTabWidget::currentChanged, this, &MainWidget::onTabChanged);
    m_pToolBar->setObjectName("toolbar_v");
    m_pToolBar->setMovable(false);
    //m_pToolBar->setIconSize(QSize(110, 40));
    _ui->HBMenuBar->addWidget(m_pToolBar);
    createBaseSetMenu();
    createMantanceMenu();
    createHistoryMenu();
    createEditMenu();
    createApplicationMenu();
    createApplicationHelp();
    if (g_language_type == "1")
    {
        QString basic_toolbar_styleString = "QToolBar QToolButton{"
                                            "color:rgb(0,255,255,255);"
                                            "border: none;"
                                            "font-size:20px;"
                                            "image: none;"
                                            "min-width:106px;"
                                            "min-height:54px;}"
                                            "#fileButton1{"
                                            "border-image: url(:/images/buttonIcon/btn_test_normal.png);}"
                                            "#fileButton1:hover{"
                                            "border-image:url(:/images/buttonIcon/btn_test_on.png);}"
                                            "#fileButton1:pressed{"
                                            "border-image:url(:/images/buttonIcon/btn_test_on.png);}"
                                            ""
                                            "#m_pToolBar{"
                                            "border: none;"
                                            "image:none;"
                                            "top:10px;"
                                            "background-color:rgb(151,151,151);}"
                                            "";
        add_styleString(basic_toolbar_styleString);
        QString basic_toolbar_styleString1 = "QToolBar QToolButton{"
                                             "color:rgb(0,255,255,255);"
                                             "border: none;"
                                             "font-size:20px;"
                                             "image: none;"
                                             "min-width:106px;"
                                             "min-height:54px;}"
                                             "#fileButton2{"
                                             "border-image: url(:/images/buttonIcon/reagent_normal.png);}"
                                             "#fileButton2:hover{"
                                             "border-image:url(:/images/buttonIcon/reagent_on.png);}"
                                             "#fileButton2:pressed{"
                                             "border-image:url(:/images/buttonIcon/reagent_on.png);}"
                                             ""
                                             "#m_pToolBar{"
                                             "border: none;"
                                             "image:none;"
                                             "top:10px;"
                                             "background-color:rgb(151,151,151);}"
                                             "";
        add_styleString(basic_toolbar_styleString1);
        QString basic_toolbar_styleString2 = "QToolBar QToolButton{"
                                             "color:rgb(0,255,255,255);"
                                             "border: none;"
                                             "font-size:20px;"
                                             "image: none;"
                                             "min-width:106px;"
                                             "min-height:54px;}"
                                             "#fileButton3{"
                                             "border-image: url(:/images/buttonIcon/btn_report_normal.png);}"
                                             "#fileButton3:hover{"
                                             "border-image:url(:/images/buttonIcon/btn_report_on.png);}"
                                             "#fileButton3:pressed{"
                                             "border-image:url(:/images/buttonIcon/btn_report_on.png);}"
                                             ""
                                             "#m_pToolBar{"
                                             "border: none;"
                                             "image:none;"
                                             "top:10px;"
                                             "background-color:rgb(151,151,151);}"
                                             "";
        add_styleString(basic_toolbar_styleString2);
        QString basic_toolbar_styleString3 = "QToolBar QToolButton{"
                                             "color:rgb(0,255,255,255);"
                                             "border: none;"
                                             "font-size:20px;"
                                             "image: none;"
                                             "min-width:106px;"
                                             "min-height:54px;}"
                                             "#fileButton4{"
                                             "border-image: url(:/images/buttonIcon/btn_set_normal.png);}"
                                             "#fileButton4:hover{"
                                             "border-image:url(:/images/buttonIcon/btn_set_on.png);}"
                                             "#fileButton4:pressed{"
                                             "border-image:url(:/images/buttonIcon/btn_set_on.png);}"
                                             ""
                                             "#m_pToolBar{"
                                             "border: none;"
                                             "image:none;"
                                             "top:10px;"
                                             "background-color:rgb(151,151,151);}"
                                             "";
        add_styleString(basic_toolbar_styleString3);
        QString basic_toolbar_styleString4 = "QToolBar QToolButton{"
                                             "color:rgb(0,255,255,255);"
                                             "border: none;"
                                             "font-size:20px;"
                                             "image: none;"
                                             "min-width:106px;"
                                             "min-height:54px;}"
                                             "#fileButton5{"
                                             "border-image: url(:/images/buttonIcon/btn_weihu_normal.png);}"
                                             "#fileButton5:hover{"
                                             "border-image:url(:/images/buttonIcon/btn_weihu_on.png);}"
                                             "#fileButton5:pressed{"
                                             "border-image:url(:/images/buttonIcon/btn_weihu_on.png);}"
                                             ""
                                             "#m_pToolBar{"
                                             "border: none;"
                                             "image:none;"
                                             "top:10px;"
                                             "background-color:rgb(151,151,151);}"
                                             "";
        add_styleString(basic_toolbar_styleString4);
        QString basic_toolbar_styleString5 = "QToolBar QToolButton{"
                                             "color:rgb(0,255,255,255);"
                                             "border: none;"
                                             "font-size:20px;"
                                             "image: none;"
                                             "min-width:106px;"
                                             "min-height:54px;}"
                                             "#fileButton6{"
                                             "border-image: url(:/images/buttonIcon/btn_help_normal.png);}"
                                             "#fileButton6:hover{"
                                             "border-image:url(:/images/buttonIcon/btn_help_on.png);}"
                                             "#fileButton6:pressed{"
                                             "border-image:url(:/images/buttonIcon/btn_help_on.png);}"
                                             ""
                                             "#m_pToolBar{"
                                             "border: none;"
                                             "image:none;"
                                             "top:10px;"
                                             "background-color:rgb(151,151,151);}"
                                             "";
        add_styleString(basic_toolbar_styleString5);
    }

    if (g_language_type == "2")
    {
        QString basic_toolbar_styleString = "QToolBar QToolButton{"
                                            "color:rgb(0,255,255,255);"
                                            "border: none;"
                                            "font-size:20px;"
                                            "image: none;"
                                            "min-width:106px;"
                                            "min-height:54px;}"
                                            "#fileButton1{"
                                            "border-image: url(:/images/buttonIcon/btn_test_normal_en.png);}"
                                            "#fileButton1:hover{"
                                            "border-image:url(:/images/buttonIcon/btn_test_on_en.png);}"
                                            "#fileButton1:pressed{"
                                            "border-image:url(:/images/buttonIcon/btn_test_on_en.png);}"
                                            ""
                                            "#m_pToolBar{"
                                            "border: none;"
                                            "image:none;"
                                            "top:10px;"
                                            "background-color:rgb(151,151,151);}"
                                            "";
        add_styleString(basic_toolbar_styleString);

        QString basic_toolbar_styleString1 = "QToolBar QToolButton{"
                                             "color:rgb(0,255,255,255);"
                                             "border: none;"
                                             "font-size:20px;"
                                             "image: none;"
                                             "min-width:106px;"
                                             "min-height:54px;}"
                                             "#fileButton2{"
                                             "border-image: url(:/images/buttonIcon/reagent_normal_en.png);}"
                                             "#fileButton2:hover{"
                                             "border-image:url(:/images/buttonIcon/reagent_on_en.png);}"
                                             "#fileButton2:pressed{"
                                             "border-image:url(:/images/buttonIcon/reagent_on_en.png);}"
                                             ""
                                             "#m_pToolBar{"
                                             "border: none;"
                                             "image:none;"
                                             "top:10px;"
                                             "background-color:rgb(151,151,151);}"
                                             "";
        add_styleString(basic_toolbar_styleString1);

        QString basic_toolbar_styleString2 = "QToolBar QToolButton{"
                                             "color:rgb(0,255,255,255);"
                                             "border: none;"
                                             "font-size:20px;"
                                             "image: none;"
                                             "min-width:106px;"
                                             "min-height:54px;}"
                                             "#fileButton3{"
                                             "border-image: url(:/images/buttonIcon/btn_report_normal_en.png);}"
                                             "#fileButton3:hover{"
                                             "border-image:url(:/images/buttonIcon/btn_report_on_en.png);}"
                                             "#fileButton3:pressed{"
                                             "border-image:url(:/images/buttonIcon/btn_report_on_en.png);}"
                                             ""
                                             "#m_pToolBar{"
                                             "border: none;"
                                             "image:none;"
                                             "top:10px;"
                                             "background-color:rgb(151,151,151);}"
                                             "";
        add_styleString(basic_toolbar_styleString2);

        QString basic_toolbar_styleString3 = "QToolBar QToolButton{"
                                             "color:rgb(0,255,255,255);"
                                             "border: none;"
                                             "font-size:20px;"
                                             "image: none;"
                                             "min-width:106px;"
                                             "min-height:54px;}"
                                             "#fileButton4{"
                                             "border-image: url(:/images/buttonIcon/btn_set_normal_en.png);}"
                                             "#fileButton4:hover{"
                                             "border-image:url(:/images/buttonIcon/btn_set_on_en.png);}"
                                             "#fileButton4:pressed{"
                                             "border-image:url(:/images/buttonIcon/btn_set_on_en.png);}"
                                             ""
                                             "#m_pToolBar{"
                                             "border: none;"
                                             "image:none;"
                                             "top:10px;"
                                             "background-color:rgb(151,151,151);}"
                                             "";
        add_styleString(basic_toolbar_styleString3);

        QString basic_toolbar_styleString4 = "QToolBar QToolButton{"
                                             "color:rgb(0,255,255,255);"
                                             "border: none;"
                                             "font-size:20px;"
                                             "image: none;"
                                             "min-width:106px;"
                                             "min-height:54px;}"
                                             "#fileButton5{"
                                             "border-image: url(:/images/buttonIcon/btn_weihu_normal_en.png);}"
                                             "#fileButton5:hover{"
                                             "border-image:url(:/images/buttonIcon/btn_weihu_on_en.png);}"
                                             "#fileButton5:pressed{"
                                             "border-image:url(:/images/buttonIcon/btn_weihu_on_en.png);}"
                                             ""
                                             "#m_pToolBar{"
                                             "border: none;"
                                             "image:none;"
                                             "top:10px;"
                                             "background-color:rgb(151,151,151);}"
                                             "";
        add_styleString(basic_toolbar_styleString4);

        QString basic_toolbar_styleString5 = "QToolBar QToolButton{"
                                             "color:rgb(0,255,255,255);"
                                             "border: none;"
                                             "font-size:20px;"
                                             "image: none;"
                                             "min-width:106px;"
                                             "min-height:54px;}"
                                             "#fileButton6{"
                                             "border-image: url(:/images/buttonIcon/btn_help_normal_en.png);}"
                                             "#fileButton6:hover{"
                                             "border-image:url(:/images/buttonIcon/btn_help_on_en.png);}"
                                             "#fileButton6:pressed{"
                                             "border-image:url(:/images/buttonIcon/btn_help_on_en.png);}"
                                             ""
                                             "#m_pToolBar{"
                                             "border: none;"
                                             "image:none;"
                                             "top:10px;"
                                             "background-color:rgb(151,151,151);}"
                                             "";
        add_styleString(basic_toolbar_styleString5);
    }

}

void MainWidget::add_styleString(QString partial_styleString) {
    globel_styleString += partial_styleString;
    this->setStyleSheet(globel_styleString);
}

int MainWidget::checkWidgetIndex(MainWidget::MENUITEMID id)
{
    _ui->stackedWidget->setCurrentIndex(STACK_PAGE_MENU);
    auto count=_ui->tabWidget->count();
    if(count==0)
        return -1;
    bool b=false;
    for(int i=0;i<count;i++)
    {
        auto tid=_ui->tabWidget->tabToolTip(i).toInt(&b);
        if(!b)
            return -1;
        if(tid==id)
        {
            return i;
        }
    }
    return -1;
}

void MainWidget::addTabWidget(QWidget *w, const QString &tabName, const MainWidget::MENUITEMID id)
{
    _ui->tabWidget->addTab(w,tabName);
    auto index=_ui->tabWidget->count()-1;
    _ui->tabWidget->setCurrentIndex(index);
    _ui->tabWidget->setTabToolTip(index,QString::number(id));

    if (index > 0)
    {
        for (int i = _ui->stackedWidget->count() - 1; i >= 0; i--)
        {
            QWidget* widget = _ui->tabWidget->widget(i);
            QString windowsTitle = widget->metaObject()->className();
            if (windowsTitle == "WelcomWidgets")
            {
                _ui->tabWidget->removeTab(0);
            }
        }
    }

    if (tabName == "欢迎界面"|| tabName == "欢迎界面en" || tabName == GlobalData::LoadLanguageInfo(g_language_type, "K1113"))
    {
        _ui->tabWidget->setTabEnabled(0, false);
        _ui->tabWidget->setStyleSheet("QTabBar::tab:disabled {width: 0; color: transparent;}");
        _ui->tabWidget->setTabsClosable(false);
    }
    else
    {
        _ui->tabWidget->setTabEnabled(0, true);
        _ui->tabWidget->setTabsClosable(true);
        _ui->tabWidget->setDocumentMode(false);
    }
}

void MainWidget::actionClick(MENUITEMID id, const QString &actName, QWidget *w)
{
    int index = checkWidgetIndex(id);
    if(index >= 0)
    {
        _ui->tabWidget->setCurrentIndex(index);
        return;
    }
    if(w==nullptr)
        w=new QWidget(this);
    addTabWidget(w,actName,id);
}

void MainWidget::createBaseSetMenu()
{
    QMenu* menu = new QMenu(STR_MAINMENU_SET,this);
    QAction* action=nullptr;
    _ui->stackedWidget->setCurrentIndex(STACK_PAGE_SAMPLE);
    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1014");
    action = new QAction(QIcon(":/images/menu/addNew.png"), sz, this);//STR_SAMPLE_MANAGE, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(on_btnSample_clicked()));
    fileButton1 = new QToolButton();
    //一定要设置ObjectName,否则没法用样式表
    fileButton1->setObjectName("fileButton1");
    fileButton1->setPopupMode(QToolButton::InstantPopup);
    fileButton1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    fileButton1->setMenu(menu);
    fileButton1->setStyleSheet("QToolButton::menu - indicator{ image:none; }");
    m_pToolBar->addWidget(fileButton1);

}

void MainWidget::createMantanceMenu()
{
    QMenu* menu = new QMenu(STR_MAINMENU_MANTANCE,this);
    QAction* action=nullptr;
    if (_userFlage == 1 || _userFlage == 2)
    {
        QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1015");
        action = new QAction(QIcon(":/images/menu/assayGroup16.png"), sz, this);//STR_MENU_MAGIC, this);
        menu->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(OnAction_MagicManage()));
    }
    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1016");
    action = new QAction(QIcon(":/images/menu/reagents16.png"), sz, this);//STR_MENU_REAGENT, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(OnAction_ReagentManager()));
    //m_pMenuBar->addMenu(menu);

    fileButton2 = new QToolButton();
    //fileButton2->setText(STR_MAINMENU_MANTANCE);
    fileButton2->setObjectName("fileButton2");
    fileButton2->setPopupMode(QToolButton::InstantPopup);
    fileButton2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    fileButton2->setMenu(menu);
    fileButton2->setStyleSheet("QToolButton::menu - indicator{ image:none; }");

    m_pToolBar->addWidget(fileButton2);
}

void MainWidget::createHistoryMenu()
{
    QMenu* menu = new QMenu(STR_MAINMENU_HISTORY,this);
    QAction* action=nullptr;

    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1017");
    action = new QAction(QIcon(":/images/buttonIcon/testRecord16.png"), sz, this);//STR_MENU_RESULTINFO, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(OnAction_ResultManage()));

    fileButton3 = new QToolButton();
    fileButton3->setObjectName("fileButton3");


    fileButton3->setObjectName("fileButton3");
    fileButton3->setPopupMode(QToolButton::InstantPopup);
    fileButton3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    fileButton3->setMenu(menu);
    fileButton3->setStyleSheet("QToolButton::menu - indicator{ image:none; }");

    m_pToolBar->addWidget(fileButton3);
}

void MainWidget::createEditMenu()
{
    QMenu* menu = new QMenu(STR_MAINMENU_EDIT,this);
    QAction* action=nullptr;

    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1018");
    action = new QAction(QIcon(":/images/buttonIcon/users32.png"), sz);//STR_MENU_APPLICATION_USERS, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(OnAction_applicationUsers()));

    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1019");
    action = new QAction(QIcon(":/images/buttonIcon/login16.png"), sz, this);//STR_MENU_APPLICATION_LOGIN, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(OnAction_applicationLogin()));

    if (_userFlage == 1 || _userFlage == 2)
    {
        sz = GlobalData::LoadLanguageInfo(g_language_type, "K1020");
        action = new QAction(QIcon(":/images/menu/systemSet16.png"), sz, this);//STR_MENU_SYSTEMSET, this);
        menu->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(OnAction_SystemSet()));

        sz = GlobalData::LoadLanguageInfo(g_language_type, "K1021");
        action = new QAction(QIcon(":/images/buttonIcon/users32.png"), sz, this);//STR_LIS_SETTING, this);
        menu->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(OnAction_LisSetting()));

        sz = GlobalData::LoadLanguageInfo(g_language_type, "K1022");
        action = new QAction(QIcon(":/images/menu/camer16.png"), sz, this);//STR_RULES_SETTING, this);
        menu->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(OnAction_RulesSetting()));
    }

    fileButton4 = new QToolButton();
    fileButton4->setObjectName("fileButton4");

    fileButton4->setPopupMode(QToolButton::InstantPopup);
    fileButton4->setMenu(menu);
    fileButton4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_pToolBar->addWidget(fileButton4);
}

void MainWidget::createApplicationMenu()
{
    QMenu* menu = new QMenu(STR_MAINMENU_APPLICATION,this);
    QAction* action=nullptr;

    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1023");
    action = new QAction(QIcon(":/images/buttonIcon/runSelfCheck16.png"), sz, this);//STR_MENU_SELF_CHECK, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(OnAction_selfRunCheck()));

    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1024");
    action = new QAction(QIcon(":/images/menu/systemSet16.png"), sz, this);//STR_MENU_SYSTEM_LIQUID_PIPE_WASH, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(OnAction_system_liquid_pipe_wash()));

    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1025");
    action = new QAction(QIcon(":/images/menu/systemSet16.png"), sz, this);//STR_MENU_PIPE_REFLUX, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(OnAction_pipe_reflux()));

    //液位探测
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1026");
    action = new QAction(QIcon(":/images/menu/systemSet16.png"), sz, this);//STR_MENU_NEW_PIPE_WASH, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(OnAction_pipe_wash()));

    if (_userFlage == 1 || _userFlage == 2)
    {
        /*sz = GlobalData::LoadLanguageInfo(g_language_type, "K1027");
        action = new QAction(QIcon(":/images/menu/systemSet16.png"), sz, this);//STR_MENU_NEW_PERISTALTIC_PUMP_AUTO_CHECK, this);
        menu->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(OnAction_pump_auto_check()));*/

        /*sz = GlobalData::LoadLanguageInfo(g_language_type, "K1028");
        action = new QAction(QIcon(":/images/menu/systemSet16.png"), sz, this);//STR_MENU_NEW_PERISTALTIC_PUMP_MANA_CHECK, this);
        menu->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(OnAction_pump_mana_check()));*/

        /*sz = GlobalData::LoadLanguageInfo(g_language_type, "K1029");
        action = new QAction(QIcon(":/images/menu/systemSet16.png"), sz, this);//STR_MENU_NEW_LIQUID_DETECTION, this);
        menu->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(OnAction_liquid_detection()));*/
    }

    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1030");
    action = new QAction(QIcon(":/images/menu/systemSet16.png"), sz, this);//STR_MENU_WEEK_MANTANCE, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(OnAction_week_mantace()));

    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1031");
    action = new QAction(QIcon(":/images/menu/systemSet16.png"), sz, this);//STR_MENU_MONTH_MANTANCE, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(OnAction_month_mantace()));

    if (_userFlage == 1|| _userFlage == 2)
    {

        /*sz = GlobalData::LoadLanguageInfo(g_language_type, "K1032");
        action = new QAction(QIcon(":/images/menu/systemSet16.png"), sz, this);//STR_MENU_CAMERA_CHECK, this);
        menu->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(OnActive_camera_check()));*/

        /* sz = GlobalData::LoadLanguageInfo(g_language_type, "K1033");
        action = new QAction(QIcon(":/images/menu/systemSet16.png"), sz, this);//STR_MENU_NEW_PUMP_RUNNING_IN, this);
        menu->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(OnActive_new_pump_running_in()));*/
    }

    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1034");
    action = new QAction(QIcon(":/images/buttonIcon/maintanceIcon16.png"), sz, this);//STR_MENU_MAN_INCUBAT, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(OnAction_ManIncubation()));

    fileButton5 = new QToolButton();

    fileButton5->setObjectName("fileButton5");
    fileButton5->setPopupMode(QToolButton::InstantPopup);

    fileButton5->setMenu(menu);
    fileButton5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_pToolBar->addWidget(fileButton5);
}

void MainWidget::createApplicationHelp()
{
    QMenu* menu = new QMenu(STR_MENU_HELP, this);
    QAction* action = nullptr;

    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1035");
    action = new QAction(QIcon(":/images/buttonIcon/aboutIcon16.png"), sz, this);// STR_MENU_APPLICATION_ABOUT, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(OnAction_applicationAbout()));

    if (_userFlage == 1 || _userFlage == 2)
    {
        sz = GlobalData::LoadLanguageInfo(g_language_type, "K1036");
        action = new QAction(QIcon(":/images/buttonIcon/aboutIcon16.png"), sz, this);//STR_MENU_HELP_OPERATELOG, this);
        menu->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(OnAction_OperatorLog()));
    }


    fileButton6 = new QToolButton();
    fileButton6->setObjectName("fileButton6");
    //fileButton6->setText(STR_MENU_HELP);
    //fileButton->setIcon(QIcon(":/images/buttonIcon/bangzhuyushuoming.png"));
    //fileButton->setIcon(QIcon(":/images/buttonIcon/anniu_normal.png"));
    fileButton6->setPopupMode(QToolButton::InstantPopup);
    fileButton6->setMenu(menu);
    fileButton6->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //fileButton->setStyleSheet("QToolButton{border: none; background: rgb(68, 69, 73); color: rgb(0, 160, 230);}");
    // 将 QToolButton 添加到 QToolBar 中
    m_pToolBar->addWidget(fileButton6);
}

void MainWidget::maintainStart(int type)
{
    auto state = _InstrumentState->getMachineState();
    if (!state.canRun)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1321"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");// GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
        return;
    }

    QString tip = "";
    if (1 == type)
    {
        tip = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1322"));//"开始周维护\n\n请先将将泵管头放到足量的系统液中，再点击【确认】按钮进行下一步！");
    }
    if (2 == type)
    {
        tip = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1323"));//"开始月维护\n\n请先将将泵管头放到足量的系统液中，再点击【确认】按钮进行下一步！");
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString("yyyy-MM-dd hh:mm:ss");
        bool bResult = true;
        auto dao = AnalysisUIDao::instance();
        QString sql = QString("update tsystemset set saveDes='%1' where id=9992").arg(str);
        dao->UpdateRecord(&bResult, sql);
    }

    //auto ret = QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tip, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), tr("取消"));
    auto ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tip, MyMessageBox::Ok | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));//GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), tr("取消"));
    //int ret = MyMessageBox::question(this, "\n提示\n", "\n数据上传LIS完成！", MyMessageBox::Save | MyMessageBox::No);

    if(ret!= MyMessageBox::Ok)
        return;
    QVector<uchar>pumpVect{0,1,2,3,4,5,6,7,8};
    //_instr->setPumpVect(pumpVect);
    //_instr->maintain(ePumpFill);
    _maintainStep=1;
}

void MainWidget::autoSelfCheck()
{
    //状态不符合则不进行初始化
    /*auto state = _InstrumentState->getMachineState();
    if(state.state==InstrumentStateModel::enumIniting||state.state==InstrumentStateModel::enumRuning){
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1334"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }*/

    //_InstrumentState->setMachineState(InstrumentStateModel::enumIniting);
    //通信异常 如果返回通信异常则弹此弹窗
    //MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1324"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1325"));//"自检进行中......");
    m_progressDialog->setMaxValue(1 * 35 * 1500);
    m_progressDialog->exec();
    mOpenSoftwareInitFlage = 2;
    //_InstrumentState->setMachineState(enumState::enumStandby);
}

void MainWidget::autoSelfCheckResult(QString code){
    qDebug()<<"autoSelfCheckResult down";
    m_progressDialog->done(1);
    if(code=="0"){
        _mSelfCheckResultShowDialog->show();
        _InstrumentState->setMachineState(enumState::enumStandby);
    }else{
        QString result =GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code);
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), result, MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        _InstrumentState->setMachineState(enumState::enumError);
    }
}

void MainWidget::shutdownMaintenResult(QString code){
    qDebug()<<"autoSelfCheckResult down："<<code;
    if(code=="0"){
        _InstrumentState->setMachineState(enumState::enumStandby);
        m_progressDialog->done(1);
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "关机维护已完成" , MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }else if(code=="K1345"||code=="K1348"||code=="K1501"||code=="K1502"){
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        _instr->testContinue();
    }else{
        _InstrumentState->setMachineState(enumState::enumError);
        m_progressDialog->done(1);
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }
}

void MainWidget::MonthMaintenResult(QString code){
    qDebug()<<"autoSelfCheckResult down";
    if(code=="0"){
        m_progressDialog->done(1);
        _InstrumentState->setMachineState(_InstrumentState->enumStandby);
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"),GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1446"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }else if(code=="K1345"||code=="K1348"){
        m_progressDialog->setShowTime(0);
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        _instr->testContinue();
    }else{
        m_progressDialog->done(1);
        _InstrumentState->setMachineState(_InstrumentState->enumError);
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }
}

void MainWidget::WeekMaintenResult(QString code){
    qDebug()<<"autoSelfCheckResult down";
    if(code=="0"){
        _InstrumentState->setMachineState(_InstrumentState->enumStandby);
        m_progressDialog->done(1);
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1524"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }else if(code=="K1345"||code=="K1348"){
        m_progressDialog->setShowTime(0);
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        _instr->testContinue();
    }else{
        m_progressDialog->done(1);
        _InstrumentState->setMachineState(_InstrumentState->enumError);
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }
}
void MainWidget::systemPipWashResult(QString code){
    if(code=="0"){
        m_progressDialog->done(1);
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1024")+ GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(),"K1685"), MyMessageBox::Ok,  GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
    }else{
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }
}

void MainWidget::pipWashResult(QString code){
    if(code=="0"){
        m_progressDialog->done(1);
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1506"), MyMessageBox::Ok, "OK", "");
    }else{
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }
}

void MainWidget::pipFlowbackResultResult(QString code){
    if(code=="0"){
        _InstrumentState->setMachineState(_InstrumentState->enumStandby);
        m_progressDialog->done(1);
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1500"), MyMessageBox::Ok, "OK", "");
    }else{
        _InstrumentState->setMachineState(_InstrumentState->enumError);
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }
}



void  MainWidget::onMachineCode(QString code){
    qDebug()<<"machine code:"<<code;
    Instrument::instance()->selfCheck();
    autoSelfCheck();
}

void MainWidget::slotGetSampleBarCode(QString barCode)
{
    if ("4444" == barCode)
    {
    }
}

void MainWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == _timerId)
    {
        QString strDateTime = GlobalData::LoadLanguageInfo(g_language_type, "K1008");
        strDateTime += QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        _ui->lblDateTime->setText(strDateTime);
        setIndicateLight();
    }
}

void MainWidget::slotLeavePage(int index)
{
    Q_UNUSED(index);
}

void MainWidget::sltUpdateTestResultDataListFromMainWindow(QString a, QString b)
{
    QString c = a;
    emit sglUpdateTestResultMainWidget(a, b);
}

void MainWidget::slotUpdateSampleWidgetUi()
{
    emit sglRefresh_SampleWidget();
}


void MainWidget::initUI()
{
    _ui->pBtnAbout->setVisible(false);
    _ui->stackedWidget->insertWidget(STACK_PAGE_SAMPLE,m_sampleWidget);
    _ui->stackedWidget->setCurrentIndex(STACK_PAGE_SAMPLE);

    connect(_instr,&Instrument::sglMaintainInfor,this,[this](const QString &strResult){
        //if ("开机自检执行成功" == strResult)
        QString sz_check_self_result = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1023") + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1259");
        if (sz_check_self_result != strResult){
            //QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), strResult, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
            if (mCheckInfoVector.size() > 0)
            {
                QString error_content = "";
                error_content = QString("%1%2").arg(mCheckInfoVector[mCheckInfoVector.size()-1]).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1679"));
                if (error_content == GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1679"))
                {
                    MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), strResult, MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
                }
                else
                {
                    MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), error_content, MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
                }
            }
            else
            {
                MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), strResult, MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
            }

            //_InstrumentState->setMachineState(enumState::enumError);
        }
    });

    connect(_instr, &Instrument::sglAlarmInfo, this, &MainWidget::slotAlarmInfo);
    connect(_instr, &Instrument::sglMinitorTemperature, this, &MainWidget::slotMinitorTemperature);
    connect(_instr, &Instrument::sglMinitorSensorState, this, &MainWidget::slotMinitorSensorState);

    connect(this, &MainWidget::sglRefresh_SampleWidget, m_sampleWidget, &SampleWidget::slotReFreshListUi);

    connect(this, &MainWidget::sglAlarmInfo_SampleWidget, m_sampleWidget, &SampleWidget::slotAlarmInfo1);

    initMenuBar();

    //1 //设置无边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    //connect(MainWindow, &MainWindow::sglUpdateTestResultMainWidget, this, &MainWidget::sltUpdateTestResultDataListFromMainWindow);
}

void MainWidget::setIndicateLight()
{
    bool bResult = true;
    auto dao = AnalysisUIDao::instance();
    QString weekMaintenance = dao->SelectMaintenanceFinishTime(&bResult, 9991);
    QString monthMaintenance = dao->SelectMaintenanceFinishTime(&bResult, 9992);
    QDateTime time1;
    QDateTime time2;
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyyMMdd");//("yyyy-MM-dd hh:mm:ss");
    time1 = QDateTime::fromString(weekMaintenance, "yyyy-MM-dd hh:mm:ss");
    time2 = QDateTime::fromString(monthMaintenance, "yyyy-MM-dd hh:mm:ss");
    int days1 = time1.daysTo(time);
    int days2 = time2.daysTo(time);
    if (days2 > 30)
    {
        _ui->btnMonthMaintain->setStyleSheet("QPushButton {qproperty-icon: url(:/images/menu/monthMaintain.png);}");
    }
    else
    {
        _ui->btnMonthMaintain->setStyleSheet("QPushButton {qproperty-icon: url(:/images/buttonIcon/maintanceIcon16.png);}");
    }
    //1为已经完成灌注，0为未灌注
    if (Global::g_SystemLiquidPerfusion == 1)
    {
        _ui->btnSystemLiquid->setStyleSheet("QPushButton {qproperty-icon: url(:/images/menu/btnSystem.png);}");
        _ui->btnSystemLiquid->setToolTip("系统液已完成灌注");
    }
    else
    {
        _ui->btnSystemLiquid->setStyleSheet("QPushButton {qproperty-icon: url(:/images/menu/btnSystemLack.png);}");
        _ui->btnSystemLiquid->setToolTip("系统液未完成灌注");
    }
    style()->unpolish(_ui->btnRunState);
    auto m = _InstrumentState->getMachineState();

    QString save_set1 = dao->SelectSaveSetById(&bResult, 20001);

	if (m.state == enumState::enumUnKnown)
	{
		_ui->btnRunState->setProperty("btnStyle", "stateErrorStyle");
		_ui->btnRunState->setToolTip(GlobalData::LoadLanguageInfo(g_language_type, "K1059"));
		_ui->label_3->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1059"));
		style()->polish(_ui->btnRunState);
		return;
	}
    int state = m.state;
    switch (state)
    {
    case enumState::enumUnConn:
    {
        _ui->btnRunState->setProperty("btnStyle","stateErrorStyle");
        _ui->btnRunState->setToolTip(GlobalData::LoadLanguageInfo(g_language_type, "K1059"));//tr("串口联接失败"));
        _ui->label_3->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1059"));//"串口联接失败");
        break;
    }
    case enumState::enumConn:
    {
        _ui->btnRunState->setProperty("btnStyle","stateConnectStyle");
        _ui->btnRunState->setToolTip(GlobalData::LoadLanguageInfo(g_language_type, "K1060"));//tr("设备联接成功"));
        _ui->label_3->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1060"));//"设备联接成功");
        break; 
    }
    case enumState::enumStandby:
    {
        _ui->btnRunState->setProperty("btnStyle","stateConnectStyle");
        _ui->btnRunState->setToolTip(GlobalData::LoadLanguageInfo(g_language_type, "K1061"));//tr("设备就绪状态"));
        _ui->label_3->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1061"));//"设备就绪状态");
        break;
    }
    case enumState::enumRuning:
    {
        if (_twinkleFlag)
        {
            _ui->btnRunState->setProperty("btnStyle","stateConnectStyle");
        }
        else
        {
            _ui->btnRunState->setProperty("btnStyle","stateIntermediateStyle");
        }
        _twinkleFlag = !_twinkleFlag;
        _ui->btnRunState->setToolTip(GlobalData::LoadLanguageInfo(g_language_type, "K1062"));//tr("设备运行状态"));
        _ui->label_3->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1062"));//"设备运行状态");
        break;
    }
    case enumState::enumCloseSoft:
    case enumState::enumIniting:
    {
        if (_twinkleFlag)
        {
            _ui->btnRunState->setProperty("btnStyle","stateConnectStyle");
        }
        else
        {
            _ui->btnRunState->setProperty("btnStyle","stateIntermediateStyle");
        }
        _twinkleFlag = !_twinkleFlag;
        _ui->btnRunState->setToolTip(GlobalData::LoadLanguageInfo(g_language_type, "K1063"));//tr("设备初始化状态"));
        _ui->label_3->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1063"));//"设备初始化状态");
        break;
    }
    case enumState::enumError:
    {
        _ui->btnRunState->setProperty("btnStyle","stateErrorStyle");
        _ui->btnRunState->setToolTip(GlobalData::LoadLanguageInfo(g_language_type, "K1064"));//tr("设备运行错误状态"));
        _ui->label_3->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1064"));//"设备运行错误状态");
        break;
    }
    }
    style()->polish(_ui->btnRunState);

}

void MainWidget::on_pBtnLogout_clicked()
{
    int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1326"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1327"), MyMessageBox::Yes | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if (ret == MyMessageBox::Yes)
    {
        emit sglLogout();
    }
}

void MainWidget::on_pBtnMini_clicked()
{
    emit sglMini();
}

void MainWidget::on_pBtnAbout_clicked()
{

}

void MainWidget::on_pBtnExit_clicked()
{
    //int ret = MyMessageBox::question(this, STR_SHUT_DOWN, STR_SHUT_DOWN_CONFIRM, MyMessageBox::Yes | MyMessageBox::No, STR_OK, STR_CANCEL);
    int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1328"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1329"), MyMessageBox::Yes | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if (ret == MyMessageBox::Yes)
    {
    }
}

void MainWidget::slotSoftClose(bool isSuccess)
{
    if (!isSuccess)
    {
        //auto ret = QMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "关机流程执行失败，是否继续关机！！", "是", "否");
        auto ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), MyMessageBox::Yes | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
        if (!ret)
        {
            qApp->quit();
        }
    }
    else
        qApp->quit();
}

void MainWidget::on_pBtnClose_clicked()
{
    QMessageBox messageBox;
    messageBox.setWindowTitle(GlobalData::LoadLanguageInfo(g_language_type, "K1003"));//"退出");
    messageBox.setText(GlobalData::LoadLanguageInfo(g_language_type, "K1578"));//"软件退出提示.");
    messageBox.setIconPixmap(QPixmap(":/images/buttonIcon/icon.png"));

    QPushButton *yesButton = messageBox.addButton(GlobalData::LoadLanguageInfo(g_language_type, "K1332"), QMessageBox::YesRole);
    QPushButton *noButton = messageBox.addButton(GlobalData::LoadLanguageInfo(g_language_type, "K1333"), QMessageBox::NoRole);
    QPushButton *cancelButton = messageBox.addButton(GlobalData::LoadLanguageInfo(g_language_type, "K1579"), QMessageBox::RejectRole);
    messageBox.setDefaultButton(cancelButton);
    messageBox.exec();

    if (messageBox.clickedButton() == yesButton) {
        // 用户点击了 "Yes" 按钮
        //qDebug() << "User clicked Yes";

        //actionClick(MENU_ID_APPLICATION_PIPEWASHEMPTY, STR_MENU_PIPE_WASH_EMPTY, _PipeWashEmptyingWidgets);
        actionClick(MENU_ID_APPLICATION_PIPEWASHEMPTY, GlobalData::LoadLanguageInfo(g_language_type, "K1332"), _PipeWashEmptyingWidgets);
    }
    else if (messageBox.clickedButton() == noButton) {
        /*_instr->setBuzzleOnOff(0x00);
                Sleep(150);
                _instr->valveControl(1, 0x00);
                Sleep(150);
                _instr->valveControl(2, 0x00);
                Sleep(150);
                _instr->valveControl(3, 0x00);
                Sleep(150);
                _instr->valveControl(11, 0x00);
                Sleep(150);
                _instr->valveControl(12, 0x00);
                Sleep(150);
                _instr->valveControl(13, 0x00);
                Sleep(150);
                _instr->valveControl(14, 0x00);
                Sleep(150);*/
        QVector<uchar> motorAddressVect;

        motorAddressVect.insert(0, 0x01);
        motorAddressVect.insert(1, 0x02);
        motorAddressVect.insert(2, 0x03);
        motorAddressVect.insert(3, 0x04);
        motorAddressVect.insert(4, 0x05);
        motorAddressVect.insert(5, 0x06);
        motorAddressVect.insert(6, 0x07);
        motorAddressVect.insert(7, 0x08);
        motorAddressVect.insert(8, 0x09);
        motorAddressVect.insert(9, 0x0A);
        motorAddressVect.insert(10, 0x0B);
        motorAddressVect.insert(11, 0x0C);
        motorAddressVect.insert(12, 0x0D);
        motorAddressVect.insert(13, 0x0E);
        motorAddressVect.insert(14, 0x0F);

        /*_instr->motorStop(motorAddressVect);
                Sleep(200);

                _instr->lightControl(0x00, 0x00);
                Sleep(150);
                _instr->lightControl(0x01, 0x00);
                Sleep(150);
                _instr->lightControl(0x02, 0x00);
                Sleep(150);
                _instr->lightControl(0x03, 0x00);
                Sleep(150);
                _instr->lightControl(0x04, 0x00);
                Sleep(150);
                _instr->lightControl(0x05, 0x00);
                Sleep(150);
                _instr->lightControl(0x06, 0x00);
                Sleep(150);
                _instr->lightControl(0x07, 0x00);
                Sleep(150);
                _instr->lightControl(0x08, 0x00);
                Sleep(150);
                _instr->lightControl(0x09, 0x00);
                Sleep(150);
                _instr->lightControl(0x0A, 0x00);
                Sleep(150);
                _instr->lightControl(0x0B, 0x00);
                Sleep(150);
                _instr->lightControl(0x0C, 0x00);
                Sleep(150);
                //_instr->lightControl(0x13, 0x00);
                //Sleep(150);
                _instr->fanControl(0x00, 0x00);
                Sleep(150);*/
        _instr->closeSocket();
        qApp->exit(0);
    }
    else if (messageBox.clickedButton() == cancelButton) {
        // 用户点击了 "Cancel" 按钮或关闭对话框
        //qDebug() << "User clicked Cancel or closed the dialog";
        //a = 40;
    }
    return;
    //int ret = QMessageBox::question(this, STR_SHUT_DOWN, STR_SHUT_DOWN_CONFIRM, STR_OK, STR_CANCEL);
    int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1328"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1331"), MyMessageBox::Yes | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1332"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1333"));
    if (ret == MyMessageBox::Yes)
    {
        actionClick(MENU_ID_APPLICATION_PIPEWASHEMPTY, STR_MENU_PIPE_WASH_EMPTY, _PipeWashEmptyingWidgets);
    }
    else
    {
        Sleep(150);
        /*_instr->setBuzzleOnOff(0x00);
                Sleep(150);
                _instr->valveControl(1, 0x00);
                Sleep(150);
                _instr->valveControl(2, 0x00);
                Sleep(150);
                _instr->valveControl(3, 0x00);
                Sleep(150);
                _instr->valveControl(11, 0x00);
                Sleep(150);
                _instr->valveControl(12, 0x00);
                Sleep(150);
                _instr->valveControl(13, 0x00);
                Sleep(150);
                _instr->valveControl(14, 0x00);*/
        Sleep(150);
        QVector<uchar> motorAddressVect;

        motorAddressVect.insert(0, 0x01);
        motorAddressVect.insert(1, 0x02);
        motorAddressVect.insert(2, 0x03);
        motorAddressVect.insert(3, 0x04);
        motorAddressVect.insert(4, 0x05);
        motorAddressVect.insert(5, 0x06);
        motorAddressVect.insert(6, 0x07);
        motorAddressVect.insert(7, 0x08);
        motorAddressVect.insert(8, 0x09);
        motorAddressVect.insert(9, 0x0A);
        motorAddressVect.insert(10, 0x0B);
        motorAddressVect.insert(11, 0x0C);
        motorAddressVect.insert(12, 0x0D);
        motorAddressVect.insert(12, 0x0E);
        motorAddressVect.insert(12, 0x0F);
        /*_instr->motorStop(motorAddressVect);
                Sleep(200);

                _instr->lightControl(0x00,0x00);
                Sleep(150);
                _instr->lightControl(0x01, 0x00);
                Sleep(150);
                _instr->lightControl(0x02, 0x00);
                Sleep(150);
                _instr->lightControl(0x03, 0x00);
                Sleep(150);
                _instr->lightControl(0x04, 0x00);
                Sleep(150);
                _instr->lightControl(0x05, 0x00);
                Sleep(150);
                _instr->lightControl(0x06, 0x00);
                Sleep(150);
                _instr->lightControl(0x07, 0x00);
                Sleep(150);
                _instr->lightControl(0x08, 0x00);
                Sleep(150);
                _instr->lightControl(0x09, 0x00);
                Sleep(150);
                _instr->lightControl(0x0A, 0x00);
                Sleep(150);
                _instr->lightControl(0x0B, 0x00);
                Sleep(150);
                _instr->lightControl(0x0C, 0x00);
                Sleep(150);
                _instr->fanControl(0x00, 0x00);
                Sleep(150);*/
        //_instr->controlHeat(22, false);
        qApp->quit();
    }
}

void MainWidget::on_btnSystemLiquidStatus_clicked()
{

}

void MainWidget::on_btnWasteBottle_clicked()
{

}


void MainWidget::on_btnRunState_clicked()
{

}

/*void MainWidget::on_btnInit_clicked()
{
    //Global::g_OpenCoverStatus = 2;
    if (Global::g_OpenCoverStatus != 5)
    {
        //_instr->inquireSensorState();
        mActiveQuery = 2;
    }
    //return;
    auto m = _InstrumentState->getMachineState();
    if(!m.canInit)
    {
        MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1334"), MyMessageBox::Yes, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    auto ret= MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1335"), MyMessageBox::Yes | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if(ret != 0)
        return;
    //_instr->maintain(eStartUpCheck);
    //清空内容清空内存
    QVector<QString> pNullVector;  //局部变量
    mCheckInfoVector.clear();
    mCheckInfoVector.swap(pNullVector);

    mOpenSoftwareInitFlage = 1;
    autoSelfCheck();
}*/

void MainWidget::on_btnReturnMain_clicked()
{
    auto state = _InstrumentState->getMachineState();
    if (state.state != enumState::enumStandby)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1581"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }

    int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1260"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1336"), MyMessageBox::Yes | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if (ret != MyMessageBox::Yes)
    {
        return;
    }
    m_sampleWidget->ReturnSampleEdit();
}

void MainWidget::on_pushButton_osk_open_clicked()
{
    if (m_open_key_word == 0)
    {
        PVOID OldValue;
        BOOL bRet = Wow64DisableWow64FsRedirection(&OldValue);
        QString csProcess = "C:\\Windows\\System32\\osk.exe";
        //QString csProcess = "C:\\Program Files\\Common Files\\microsoft shared\\ink\\TabTip.exe";
        QString params = "";
        ShellExecute(NULL, L"open", (LPCWSTR)csProcess.utf16(), (LPCWSTR)params.utf16(), NULL, SW_SHOWNORMAL);
        if (bRet)
        {
            Wow64RevertWow64FsRedirection(OldValue);
        }
        m_open_key_word = 1;
        //K1638
        _ui->pushButton_osk_open->setText("     " + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1638"));
    }
    else
    {
        HWND appWnd;
        appWnd = ::FindWindow(L"OSKMainClass", NULL);
        if (appWnd)
        {
            //::SendMessage(appWnd, WM_CLOSE, 0, 0);
            SendMessage(appWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
            qDebug() << "closeKeyboard succeed";
        }
        else
        {
            qDebug() << "closeKeyboard failed";
        }
        m_open_key_word = 0;
        //K1006 打开键盘
        _ui->pushButton_osk_open->setText("     "+ GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1006"));
    }
}

void MainWidget::on_btnCloseBeep1_clicked()
{
     // slz
    //  qDebug() << "close bee wz2";
    //  Analysis m_analysis;
    //  m_analysis.AnalysisMothed("202503140959581",29,"202503140959581", "solutionName","");
    //  iLog("wangzhen");


    _instr->shutdownBee();
    //OnAction_CloseBeep();
    // TODO::WangZ
//    qDebug() << "close bee wz";
//    QString folderPath = "C:/img/";
//    QDir dir(folderPath);
//    dir.setFilter(QDir::Files);
//    QFileInfoList fileInfoList = dir.entryInfoList();
//    foreach (QFileInfo fileInfo, fileInfoList)
//    {
//        QString fileFullName = fileInfo.fileName();
//        QString fileName = fileFullName.left(fileFullName.lastIndexOf('.'));
//        // 在这里处理获取到的图片名称
//        qDebug() << "图片名称：" << fileName;
//        // 开始图片分析
//        Analysis m_analysis;
//        int code = m_analysis.AnalysisMothed_wz(folderPath,fileName);
//        if(code == 0)
//        {
//            qDebug() << "success wz";
//        }else
//        {
//            qDebug() << "file wz " << code;
//        }
//    }

//    Analysis m_analysis;
//    int code = m_analysis.AnalysisMothed_wz("C:/img/","1");
//    if(code == 0)
//    {
//        qDebug() << "success wz";
//    }else
//    {
//        qDebug() << "file wz " << code;
//    }
//    Analysis m_analysis;
//    m_analysis.AnalysisMothed("202502141638021",929, "solutionName");
}

//处理窗口关闭
void MainWidget::removeSubTab(int index)
{
    /*if (_weekMaintenanceWidgets->mWeekMaintenance_run_flage)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1338"), MyMessageBox::Yes, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }

    if (_monthMaintenanceWidgets->mMonthMaintenance_run_flage)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1339"), MyMessageBox::Yes, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }*/

    int tabWidgetCount = _ui->tabWidget->count();
    _ui->tabWidget->removeTab(index);
    if(_ui->tabWidget->count()<=0)
        _ui->stackedWidget->setCurrentIndex(1);
    int stack_number = _ui->stackedWidget->count();

    this->activateWindow();
    //发送一个信号，使mainwindow重新成为setActivationWindow
    emit sglReActiveMainWindow();
}

void MainWidget::OnAction_SystemSet()
{
    //actionClick(MENU_ID_SYSTEMSET,STR_MENU_SYSTEMSET,new SystemSet(this));
    actionClick(MENU_ID_SYSTEMSET, GlobalData::LoadLanguageInfo("K1020"), new SystemSet(this));
}

void MainWidget::OnAction_MagicManage()
{
    //actionClick(MENU_ID_MAGIC,STR_MENU_MAGIC,new TestPaperManage(this));
    actionClick(MENU_ID_MAGIC, GlobalData::LoadLanguageInfo("K1015"), new TestPaperManage(this));
}

void MainWidget::OnAction_ReagentManager()
{
    //actionClick(MENU_ID_REAGENT,STR_MENU_REAGENT,new ReagentManager(this));
    actionClick(MENU_ID_REAGENT, GlobalData::LoadLanguageInfo(g_language_type, "K1016"), new ReagentManager(this));
}

void MainWidget::OnAction_TubeManage()
{
    actionClick(MENU_ID_SAMPLETUBE,STR_MENU_SAMPLETUBE,new TubeManage(this));
}

void MainWidget::OnAction_OperatorLog()
{
    QtWidgetstOperateLog * operate_log_w = new QtWidgetstOperateLog(this);
    int ax = 0;
    int ay = 0;
    ax = (QApplication::desktop()->width() - operate_log_w->width()) / 2;
    ay = (QApplication::desktop()->height() - operate_log_w->height()) / 2;
    operate_log_w->move(ax, ay);
    actionClick(MENU_ID_APPLICATION_OPERATELOG, GlobalData::LoadLanguageInfo("K1036"), operate_log_w);
}

void MainWidget::OnAction_ResultManage()
{
    _mTestResultDataAll->setProgressDialog(m_progressDialog);
    _mTestResultDataAll->m_test_project_name = "";
    _mTestResultDataAll->Show_UI_Data("");
    _mTestResultDataAll->set_print_doing(0);
    actionClick(MENU_ID_RESULTINFO, GlobalData::LoadLanguageInfo("K1017"), _mTestResultDataAll);
}

void MainWidget::OnAction_Camera()
{
    actionClick(MENU_ID_CAMERA,STR_MENU_CAMAR,new Camera(this));
}

void MainWidget::OnAction_RulesSetting()
{
    //actionClick(MENU_ID_RULESETTING, STR_RULES_SETTING, new RulesSetting(this));
    actionClick(MENU_ID_RULESETTING, GlobalData::LoadLanguageInfo(g_language_type, "K1022"), new RulesSetting(this));
}

void MainWidget::OnAction_systemLiquid()
{
    actionClick(MENU_ID_SYSTEMLIQUID,STR_MENU_SLIQUID,nullptr);
}

void MainWidget::OnAction_pump()
{
    //actionClick(MENU_ID_PUMP,STR_MENU_PUMP,nullptr);
}

void MainWidget::OnAction_pump_calibrate()
{
    actionClick(MENU_ID_PUMP_CALIBRATE,STR_MENU_PUMP_CALIBRATE,_pumpCalibrateWidget);
}

void MainWidget::OnAction_pipe_reflux()
{
    auto state = _InstrumentState->getMachineState();
    if (state.state != enumState::enumStandby)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    ChangWidgetsStartStatus();
    _pipeRefluxWidgets->updateUI();



    actionClick(MENU_ID_PIPE_REFLUX, GlobalData::LoadLanguageInfo(g_language_type, "K1219"), _pipeRefluxWidgets);
    //actionClick(MENU_ID_PIPE_REFLUX, STR_MENU_NEW_PIPE_FEFLUX, _pipeRefluxWidgets);
}

void MainWidget::OnAction_system_liquid_pipe_wash()
{
    auto state = _InstrumentState->getMachineState();
    if (state.state != enumState::enumStandby)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    ChangWidgetsStartStatus();
    _mSystemLiquidPipeWashWidgets->updateUI();

    actionClick(MENU_ID_SYSTEM_LIQUID_PIPE_WASH, GlobalData::LoadLanguageInfo(g_language_type, "K1217"), _mSystemLiquidPipeWashWidgets);
    //actionClick(MENU_ID_SYSTEM_LIQUID_PIPE_WASH, STR_MENU_SYSTEM_LIQUID_PIPE_WASH, _mSystemLiquidPipeWashWidgets);
}

void MainWidget::OnAction_pipe_wash()
{
    auto state = _InstrumentState->getMachineState();
    if (state.state != enumState::enumStandby)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    ChangWidgetsStartStatus();
    _pipeWashWidgets->updateUI();
    //actionClick(MENU_ID_PIPE_WASH, STR_MENU_NEW_PIPE_WASH, _pipeWashWidgets);
    actionClick(MENU_ID_PIPE_WASH, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1026"), _pipeWashWidgets);
}
void MainWidget::OnAction_pump_auto_check()
{
    /*auto state = _InstrumentState->getMachineState();
    if (state.state != enumState::enumStandby)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }*/
    ChangWidgetsStartStatus();
    actionClick(MENU_ID_PERISTALTIC_PUMP_AUTO_CHECK, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1027"), _pumpAutoCheckWidgets);
    //actionClick(MENU_ID_PERISTALTIC_PUMP_AUTO_CHECK, STR_MENU_NEW_PERISTALTIC_PUMP_AUTO_CHECK, _pumpAutoCheckWidgets);
}
void MainWidget::OnAction_pump_mana_check()
{
    /*auto state = _InstrumentState->getMachineState();
    if (state.state != enumState::enumStandby)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }*/
    ChangWidgetsStartStatus();
    actionClick(MENU_ID_PERISTALTIC_PUMP_MANA_CHECK, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1028"), _pumpManaCheckWidgets);
}
void MainWidget::OnAction_liquid_detection()
{
    /*auto state = _InstrumentState->getMachineState();
    if (state.state != enumState::enumStandby)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }*/
    ChangWidgetsStartStatus();
    actionClick(MENU_ID_LIQUID_DETECTION, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1029"), _liquidDetectionWidgets);
}

void MainWidget::OnAction_week_mantace()
{
    //_maintainType=MENU_ID_WEEK_MANTAINCE;
    //maintainStart(1);
    auto state = _InstrumentState->getMachineState();
    if (state.state != enumState::enumStandby)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    ChangWidgetsStartStatus();
    _weekMaintenanceWidgets->updateUI();
    actionClick(MENU_ID_WEEK_MANTAINCE, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1030"), _weekMaintenanceWidgets);
}

void MainWidget::OnAction_ManIncubation()//手动孵育
{
    //_maintainType=MENU_ID_WEEK_MANTAINCE;
    //maintainStart(1);
    //actionClick(MENU_ID_APPLICATION_MAN_INCUBAT, STR_MENU_MAN_INCUBAT, _mManualIncubationWidgets);
    auto state = _InstrumentState->getMachineState();
    if (state.state != enumState::enumStandby)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    ChangWidgetsStartStatus();
    _mManualIncubationWidgets->exec();
}

void MainWidget::OnAction_month_mantace()
{
    auto state = _InstrumentState->getMachineState();
    if (state.state != enumState::enumStandby)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    ChangWidgetsStartStatus();
    on_btnMonthMaintain_clicked();
}

void MainWidget::OnActive_camera_check()
{
    ChangWidgetsStartStatus();
    actionClick(MENU_ID_CAMERA_CHECK, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1032"), _cameraCheckWidgets);
}

//新泵磨合
void MainWidget::OnActive_new_pump_running_in()
{
    auto state = _InstrumentState->getMachineState();
    if (state.state != enumState::enumStandby)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    ChangWidgetsStartStatus();
    actionClick(MENU_ID_NEW_PUMP_RUNNING_IN, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1033"), _newPumpRunninInWidgets);
}

void MainWidget::ChangWidgetsStartStatus()
{
	if (_mSystemLiquidPipeWashWidgets != nullptr)
		_mSystemLiquidPipeWashWidgets->m_start_system_liquid_pipe_wash = false;
	if (_pipeRefluxWidgets != nullptr)
		_pipeRefluxWidgets->m_start_PipeRefluxWidgets = false;
	if (_pipeWashWidgets != nullptr)
		_pipeWashWidgets->m_start_pile_wash = false;
	if (_pumpAutoCheckWidgets != nullptr)
		_pumpAutoCheckWidgets->m_start_pump_auto_check = false;
	if (_pumpManaCheckWidgets != nullptr)
		_pumpManaCheckWidgets->m_start_pump_manal_check = false;
	if (_liquidDetectionWidgets != nullptr)
		_liquidDetectionWidgets->start_liquid_detection = false;
	if (_weekMaintenanceWidgets != nullptr)
		_weekMaintenanceWidgets->mWeekMaintenance_run_flage = false;
	if (_monthMaintenanceWidgets != nullptr)
		_monthMaintenanceWidgets->mMonthMaintenance_run_flage = false;
	if (_newPumpRunninInWidgets != nullptr)
		_newPumpRunninInWidgets->m_start_NewPumpRunningWidgets = false;
}

void MainWidget::on_btnMonthMaintain_clicked()
{
    //_maintainType = MENU_ID_MONTH_MANTAINCE;
    //maintainStart(2);
    ChangWidgetsStartStatus();
    _monthMaintenanceWidgets->HideGroupBox();
    _monthMaintenanceWidgets->step_index = 0;
    _monthMaintenanceWidgets->updateUI();
    actionClick(MENU_ID_MONTH_MANTAINCE, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1031"), _monthMaintenanceWidgets);
}

void MainWidget::OnAction_CloseBeep()
{
    //_instr->setBuzzleOnOff(0);
    Sleep(1000);
    //_instr->setBuzzleOnOff(0);
}

void MainWidget::OnAction_selfRunCheck()
{
    auto state = _InstrumentState->getMachineState();
    if (state.state==_InstrumentState->enumRuning)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }

    //QVector<QString> pNullVector;  //局部变量
    //mCheckInfoVector.clear();
    //mCheckInfoVector.swap(pNullVector);
    //mOpenSoftwareInitFlage = 1;
    //autoSelfCheck();
    Instrument::instance()->selfCheck();
    _InstrumentState->setMachineState(InstrumentStateModel::enumRuning);
    autoSelfCheck();
}

void MainWidget::OnAction_testRecord()
{
    //actionClick(MENU_ID_TESTRECORD,STR_MENU_TEST_RECORD,nullptr);
}

void MainWidget::OnAction_maintaceRecord()
{
    //actionClick(MENU_ID_MAINTANCERECORD,STR_MENU_MAINTANCE_RECORD,nullptr);
}

void MainWidget::OnAction_communicateRecord()
{
    //actionClick(MENU_ID_COMMUNICATERECORD,STR_MENU_COMMUNIT_RECORD,nullptr);
}

void MainWidget::OnAction_solutionRecord()
{
    //actionClick(MENU_ID_SOLUTIONRECORD,STR_MENU_SOLUTION_RECORD,nullptr);
}

void MainWidget::OnAction_editGroup()
{
    //actionClick(MENU_ID_EDITGROUP,STR_MENU_EDIT_GROUP,nullptr);
}

void MainWidget::OnAction_editTest()
{
    //actionClick(MENU_ID_EDITTEST,STR_MENU_EDIT_TEST,nullptr);
}

void MainWidget::OnAction_editReagent()
{
    //actionClick(MENU_ID_EDITREAGENT,STR_MENU_EDIT_REAGENT,nullptr);
}

void MainWidget::OnAction_editTupe()
{
    //actionClick(MENU_ID_EDITTUPE,STR_MENU_EDIT_TUPE,nullptr);
}

void MainWidget::OnAction_applicationLogin()
{
    //actionClick(MENU_ID_APPLICATION_LOGING,STR_MENU_APPLICATION_LOGIN,nullptr);
    emit sglLogout();
}

void MainWidget::OnAction_applicationPassword()
{
    actionClick(MENU_ID_APPLICATION_PASSWORD,STR_MENU_APPLICATION_PASSWORD,nullptr);
}

void MainWidget::OnAction_applicationUsers()
{
    UserManageWidget* user_manage_widget = new UserManageWidget(this,_userFlage, mUserName);
    actionClick(MENU_ID_APPLICATION_USERS, GlobalData::LoadLanguageInfo(g_language_type, "K1018"), user_manage_widget);
}

void MainWidget::OnAction_LisSetting()
{
    LisSettingWidgets* lisSetting = new LisSettingWidgets(this);
    lisSetting->setTcpClient(m_tcpClient);
    actionClick(MENU_ID_APPLICATION_LIS, GlobalData::LoadLanguageInfo(g_language_type, "K1209"), lisSetting);
}

void MainWidget::OnAction_applicationSet()
{
    //actionClick(MENU_ID_APPLICATION_SET,STR_MENU_APPLICATION_SET,nullptr);
}

void MainWidget::OnAction_applicationCardSet()
{
    //actionClick(MENU_ID_APPLICATION_CARDSET,STR_MENU_APPLICATION_CARDSET,nullptr);
}

void MainWidget::OnAction_applicationCodeAdd()
{
    //actionClick(MENU_ID_APPLICATION_CODEADD,STR_MENU_APPLICATION_CODEADD,nullptr);
}

void MainWidget::openWelcomeWidgets() {

    WelcomWidgets * welcome__w = new WelcomWidgets(this);
    int ax = 0;
    int ay = 0;
    ax = (QApplication::desktop()->width() - welcome__w->width()) / 2;
    ay = (QApplication::desktop()->height() - welcome__w->height()) / 2;
    welcome__w->move(ax, ay);
    //actionClick(MENU_ID_APPLICATION_OPERATELOG, STR_MENU_HELP_OPERATELOG, operate_log_w);
    //actionClick(MENU_ID_APPLICATION_WELCOME, STR_MENU_APPLICATION_WELCOME, welcome__w);
    actionClick(MENU_ID_APPLICATION_WELCOME, GlobalData::LoadLanguageInfo(g_language_type, "K1113"), welcome__w);
}

void MainWidget::OnAction_applicationAbout()
{
    AboutUsWidgets * about_us_w = new AboutUsWidgets(this);
    int ax = 0;
    int ay = 0;
    ax = (QApplication::desktop()->width() - about_us_w->width()) / 2;
    ay = (QApplication::desktop()->height() - about_us_w->height()) / 2;
    about_us_w->move(ax, ay);
    //actionClick(MENU_ID_APPLICATION_OPERATELOG, STR_MENU_HELP_OPERATELOG, operate_log_w);
    //actionClick(MENU_ID_APPLICATION_ABOUT,STR_MENU_APPLICATION_ABOUT, about_us_w);
    actionClick(MENU_ID_APPLICATION_ABOUT, GlobalData::LoadLanguageInfo(g_language_type, "K1035"), about_us_w);
}

void MainWidget::OnAction_applicationTechSupport()
{
    actionClick(MENU_ID_APPLICATION_TECHSUPPORT, STR_MENU_HELP_TECHSUPPORT, nullptr);
}

void MainWidget::OnAction_applicationHelpManual()
{
    actionClick(MENU_ID_APPLICATION_HELPMANUAL, STR_MENU_HELPMANUAL, nullptr);
}

void MainWidget::OnAction_applicationSoftwareInfo()
{
    actionClick(MENU_ID_APPLICATION_SOFTWAREINFO, STR_MENU_HELP_SOFTWAREINFO, nullptr);
}

void MainWidget::on_btnSample_clicked()
{
    _ui->stackedWidget->setCurrentIndex(STACK_PAGE_SAMPLE);
}

void MainWidget::stopInstrument()
{
    _InstrumentState->setMachineState(enumState::enumError);
    //_instr->machineStop();
}
void MainWidget::pauseInstrument()
{
    _InstrumentState->setMachineState(enumState::enumPause);
    //_instr->setIsPause(true);
}
void MainWidget::continueInstrument()
{
    //_instr->setIsPause(false);
}

void MainWidget::alarmDeal(int code_level,QString tip_content)
{

    QString tip_content1 = "";
    switch (code_level)
    {
    case 0x01:
        stopInstrument();
        tip_content1 = QString("%1-%2").arg(tip_content).arg(code_level);
        emit sglAlarmInfo_SampleWidget(tip_content1,"01");
        writeAlarmInfo(tip_content1, "alarmInfo.log");
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tip_content1, MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        break;
    case 0x02:
        stopInstrument();
        tip_content1 = QString("%1-%2").arg(tip_content).arg(code_level);
        emit sglAlarmInfo_SampleWidget(tip_content1,"02");
        writeAlarmInfo(tip_content1, "alarmInfo.log");
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tip_content1, MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        break;
    case 0xFD:
        tip_content1 = QString("%1").arg(tip_content);
        emit sglAlarmInfo_SampleWidget(tip_content1,"FD");
        writeAlarmInfo(tip_content1, "alarmInfo.log");
        //QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tip_content1, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
        break;
    case 0xFE:
        tip_content1 = QString("%1").arg(tip_content);
        emit sglAlarmInfo_SampleWidget(tip_content1,"FE");
        writeAlarmInfo(tip_content1, "alarmInfo.log");
        //QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tip_content1, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
        break;
    case 0xFF:
        tip_content1 = QString("%1").arg(tip_content);
        emit sglAlarmInfo_SampleWidget(tip_content1,"FF");
        writeAlarmInfo(tip_content1, "alarmInfo.log");
        break;
    default:
        break;
    }
}

//报警信息处理
void MainWidget::slotAlarmInfo(int warnCode)
{
    int ret = 0;
    QString str = "";
    switch (warnCode)
    {
    case 0x9000:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9000"));//"样本臂吸样时Z轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9001:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9001"));//.arg("样本臂吸样时X轴电机运动至吸样位时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9002:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9002"));//.arg("样本臂吸样时X轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9003:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9003"));//.arg("样本臂吸样时Y轴电机运动至吸样位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9004:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9004"));//.arg("样本臂吸样时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9005:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9005"));//.arg("样本臂吸样时样Z轴电机使能液位探测时右光电立即有效");
        alarmDeal(0xFD, str);
        break;
    case 0x9006:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9006"));//.arg("样本臂吸样时Z轴电机运动至吸液位置发生垂直碰撞");
        //emit sglAlarmInfo_SampleWidget(str);
        //pauseInstrument();
        //pauseInstrument();
        alarmDeal(0xFD, str);
        break;
    case 0x9007:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9007"));//.arg("样本臂吸样时Z轴电机运动至吸液位置复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0x9008:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9008"));//.arg("样本臂吸样时样本针柱塞泵吸样复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0x9009:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9009"));//.arg("样本臂吸样时样本针柱塞泵吸样堵针");
        //emit sglAlarmInfo_SampleWidget(str);
        //pauseInstrument();
        //emit sglAlarmInfo_SampleWidget(str);
        alarmDeal(0xFD, str);
        break;
    case 0x900D:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x900D"));//.arg("样本臂吸样前样本针内压力值与设置的环境压力值相差大于100");
        //emit sglAlarmInfo_SampleWidget(str);
        //pauseInstrument();
        //emit sglAlarmInfo_SampleWidget(str);
        alarmDeal(0xFE, str);
        break;
    case 0x900A:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x900A"));//.arg("样本臂吸样时Z轴电机第二次运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x900B:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x900B"));//.arg("样本臂吸样时Y轴电机运动至样本针清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x900C:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x900C"));//.arg("样本臂吸样时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9010:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9010"));//.arg("样本臂清洗时Z轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9011:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9011"));//.arg("样本臂清洗时Y轴电机运动至清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9012:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9012"));//.arg("样本臂清洗时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9013:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9013"));//.arg("样本臂清洗时Z轴电机运动至清洗位置复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0x9014:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9014"));//.arg("样本臂清洗时样本针柱塞泵运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9015:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9015"));//.arg("样本臂清洗时Z轴电机第二次运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9016:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9016"));//.arg("清洗针下降时垂直碰撞");
        alarmDeal(0xFD, str);
        break;
    case 0x9018:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9018"));//.arg("样本臂吐样时Z轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9019:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9019"));//.arg("样本臂吐样时X轴电机运动至吐样位时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x901A:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x901A"));//.arg("样本臂吐样时X轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x901B:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x901B"));//.arg("样本臂吐样时摇床电机运动至吸液位置复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0x901C:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x901C"));//.arg("样本臂吐样时Y轴电机运动至吐样位置时编码器差值超48步以上");
        break;
    case 0x901D:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x901D"));//.arg("样本臂吐样时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x901E:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x901E"));//.arg("样本臂吐样时Z轴电机使能液位探测时右光电立即有效");
        alarmDeal(0x02, str);
        break;
    case 0x901F:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x901F"));//.arg("样本臂吐样时Z轴电机运动至吐样位置发生垂直碰撞");
        alarmDeal(0xFD, str);
        break;
    case 0x9020:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9020"));//.arg("样本臂吐样时Z轴电机第二次运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9021:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9021"));//.arg("样本臂吐样时Y轴电机运动至样本针清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9022:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9022"));//.arg("样本臂吐样时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9028:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9028"));//.arg("样本条码扫描时Z轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9029:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9029"));//.arg("样本条码扫描时Y轴电机运动至清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x902A:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x902A"));//.arg("样本条码扫描时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x902B:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x902B"));//.arg("样本条码扫描时X轴电机运动至扫描位时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x902C:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x902C"));//.arg("样本条码扫描时X轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9030:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9030"));//.arg("相机校准时Z轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9031:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9031"));//.arg("相机校准时Y轴电机运动至样本针清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9032:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9032"));//.arg("相机校准时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9033:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9033"));//.arg("相机校准时X轴电机运动至相机校准位时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9034:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9034"));//.arg("相机校准时X轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9038:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9038"));//.arg("排废液及蠕动泵加液时Z轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9039:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9039"));//.arg("排废液及蠕动泵加液时Y轴电机运动至样本针清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x903A:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x903A"));//.arg("排废液及蠕动泵加液时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x903B:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x903B"));//.arg("排废液及蠕动泵加液时摇床电机运动至吸液位置复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0x903C:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x903C"));//.arg("排废液及蠕动泵加液时X轴电机运动至排液位时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x903D:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x903D"));//.arg("排废液及蠕动泵加液时X轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x903E:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x903E"));//.arg("排废液及蠕动泵加液时Y轴电机运动至废液槽触发抽废液位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x903F:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x903F"));//.arg("排废液及蠕动泵加液时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9040:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9040"));//.arg("排废液及蠕动泵加液时Y轴电机第二次运动至样本针清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9041:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9041"));//.arg("排废液及蠕动泵加液时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9048:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9048"));//.arg("蠕动泵充灌时Z轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9049:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9049"));//.arg("蠕动泵充灌时Y轴电机运动至样本针清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x904A:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x904A"));//.arg("蠕动泵充灌时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x904B:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x904B"));//.arg("蠕动泵充灌时X轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x904C:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x904C"));//.arg("蠕动泵充灌时Y轴电机运动至废液槽触发抽废液位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x904D:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x904D"));//.arg("蠕动泵充灌时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x904E:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x904E"));//.arg("蠕动泵充灌时Y轴电机第二次运动至样本针清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x904F:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x904F"));//.arg("蠕动泵充灌时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9050:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9050"));//.arg("扫码器自检时Z轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9051:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9051"));//.arg("扫码器自检时Y轴电机运动至清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9052:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9052"));//.arg("扫码器自检时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9053:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9053"));//.arg("扫码器自检时X轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9058:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9058"));//.arg("蠕动泵校准时Z轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9059:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9059"));//.arg("蠕动泵校准时X轴电机运动至复位位置复位光耦无效");
        //pauseInstrument();
        alarmDeal(0x02, str);
        break;
    case 0x905A:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x905A"));//.arg("蠕动泵校准时Y轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x905B:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x905B"));//.arg("蠕动泵校准时Y轴电机运动至废液槽触发抽废液位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x905C:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x905C"));//.arg("蠕动泵校准时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x905D:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x905D"));//.arg("蠕动泵校准时Y轴电机运动至样本针清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x905E:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x905E"));//.arg("蠕动泵校准时Y轴电机运动至样本针清洗位置补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x905F:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x905F"));//.arg("蠕动泵校准时Y轴电机第二次运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9060:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9060"));//.arg("蠕动泵校准时Z轴电机使能液位探测时右光电立即有效");
        alarmDeal(0xFD, str);
        break;
    case 0x9061:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9061"));//.arg("蠕动泵校准时Z轴电机运动至废液槽高度位置复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0x9062:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9062"));//.arg("蠕动泵校准时Z轴电机第二次运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9063:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9063"));//.arg("蠕动泵校准时Z轴电机第二次使能液位探测时右光电立即有效");
        alarmDeal(0x02, str);
        break;
    case 0x9064:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9064"));//.arg("蠕动泵校准时Z轴电机第二次运动至废液槽高度位置复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0x9065:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9065"));//.arg("蠕动泵校准时Z轴电机第三次运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9066:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9066"));//.arg("蠕动泵校准时Y轴电机第二次运动至废液槽触发抽废液位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9067:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9067"));//.arg("蠕动泵校准时Y轴电机第二次运动至废液槽触发抽废液位置补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9068:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9068"));//.arg("蠕动泵校准时Y轴电机第二次运动至样本针清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9069:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9069"));//.arg("蠕动泵校准时Y轴电机第二次运动至样本针清洗位置补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9070:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9070"));//.arg("膜条拍照时Z轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9071:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9071"));//.arg("膜条拍照时Y轴电机运动至清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9072:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9072"));//.arg("膜条拍照时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9073:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9073"));//.arg("膜条拍照时X轴电机运动至膜条拍照位时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9074:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9074"));//.arg("膜条拍照时X轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9075:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9075"));//.arg("膜条拍照时摇床电机运动至拍照位置复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0x9080:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9080"));//.arg("系统液充灌时Z轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9081:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9081"));//.arg("系统液充灌时Y轴电机运动至样本针清洗位置时编码器差值超48步以上");
        break;
    case 0x9082:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9082"));//.arg("系统液充灌时Y轴电机运动至样本针清洗位置补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9083:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9083"));//.arg("系统液充灌时 样本针柱塞泵电机初始化复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9084:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9084"));//.arg("系统液充灌时Z轴电机运动至清洗位一半高度时复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0x9088:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9088"));//.arg("系统液管路清洗时Z轴电机运动至复位位置复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x9089:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9089"));//.arg("系统液管路清洗时Y轴电机运动至样本针清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x908A:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x908A"));//.arg("系统液管路清洗时Y轴电机运动至样本针清洗位置补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x908B:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x908B"));//.arg("系统液管路清洗时 样本针柱塞泵电机初始化复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0x908C:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x908C"));//.arg("系统液管路清洗时Z轴电机运动至清洗位高度时复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0x9090:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9090"));//.arg("调速风扇工作时Y轴电机运动至清洗位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9091:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9091"));//.arg("调速风扇工作时Y轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
    case 0x9092:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9092"));//.arg("调速风扇工作时X轴电机运动至相机校准位 + 偏离槽距离位置时编码器差值超48步以上");
        alarmDeal(0xFF, str);
        break;
    case 0x9093:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9093"));//.arg("调速风扇工作时X轴电机补偿运动后编码器差值超48步以上");
        alarmDeal(0x02, str);
        break;
        //FF	0x9090	调速风扇工作时Y轴电机运动至清洗位置时编码器差值超48步以上
        //	02	0x9091	调速风扇工作时Y轴电机补偿运动后编码器差值超48步以上
        //	FF	0x9092	调速风扇工作时X轴电机运动至相机校准位 + 偏离槽距离位置时编码器差值超48步以上
        //	02	0x9093	调速风扇工作时X轴电机补偿运动后编码器差值超48步以上
    case 0xA001:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0xA001"));//.arg("X轴电机初始化时定速运动到复位位置时用时12s复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0xA101:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0xA101"));//.arg("X轴电机初始化时退出复位位置设定的步数时复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0xA002:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0xA002"));//.arg("Y轴电机初始化时定速运动到复位位置时用时12s复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0xA102:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0xA102"));//.arg("Y轴电机初始化时退出复位位置设定的步数时复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0xA003:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0xA003"));//.arg("Z轴电机初始化时定速运动到复位位置时用时12s复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0xA103:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0xA103"));//.arg("Z轴电机初始化时退出复位位置设定的步数时复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0xA004:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0xA004"));//.arg("样本柱塞泵电机初始化时定速运动到复位位置时用时12s复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0xA104:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0xA104"));//.arg("样本柱塞泵电机初始化时退出复位位置设定的步数时复位光耦有效");
        alarmDeal(0x02, str);
        break;
    case 0xA005:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0xA005"));//.arg("摇床电机初始化时定速运动到复位位置时用时12s复位光耦无效");
        alarmDeal(0x02, str);
        break;
    case 0xA105:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0xA105"));
        alarmDeal(0x02, str);
        break;
    case 0x8f01:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f04"));
        _ui->btnWasteBottle->setToolTip(str);
        _ui->btnWasteBottle->setStyleSheet("QPushButton{ qproperty-icon: url(:/images/menu/wasteBottle.png);}");
        update();
        //_instr->setBuzzleOnOff(0);
        Sleep(150);
        break;
    case 0x8f02:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f02"));
        _ui->btnSystemLiquidStatus->setToolTip(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f02"));
        _ui->btnSystemLiquidStatus->setStyleSheet("QPushButton {qproperty-icon: url(:/images/menu/systemLiquidStatusNoFull.png);}");
        update();
        writeAlarmInfo(str, "alarmInfo.log");
        break;
    case 0x8f04:
    {
        auto dao = AnalysisUIDao::instance();
        bool bResult;
        QString save_set = dao->SelectSaveSetById(&bResult, 20002);
        QString save_set1 = dao->SelectSaveSetById(&bResult, 20001);
        if (save_set == "1")
        {
            _ui->btnWasteBottle->setToolTip(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f01"));
            _ui->btnWasteBottle->setStyleSheet("QPushButton{ qproperty-icon: url(:/images/menu/wasteBottleFull.png);}");
            update();
            writeAlarmInfo(str, "alarmInfo.log");
            if (save_set1 == "1")
            {
                //_instr->setBuzzleOnOff(2);
            }
            else
            {
                //_instr->setBuzzleOnOff(0);
            }
        }
        break;
    }
    case 0x8f05:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f05"));
        _ui->btnSystemLiquidStatus->setToolTip(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f05"));
        _ui->btnSystemLiquidStatus->setStyleSheet("QPushButton {qproperty-icon: url(:/images/menu/systemLiquidStatusFull.png);}");
        break;
    case 0x8f06:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f06"));
        alarmDeal(0xFE, str);

        break;
    case 0x8f07:
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f07"));
        alarmDeal(0xFE, str);
        break;
    case 0x8f00:
        if (Global::g_OpenCoverStatus == 5)
            break;
        if (mActiveQuery == 3)
            break;
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1343"));
        //_instr->setIsPause(true);
        ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1342"), MyMessageBox::Ok| MyMessageBox::Cancel, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1341"),GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));

        emit sglAlarmInfo_SampleWidget(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1342"), "FE");
        if (ret == QMessageBox::NoButton) {
            mActiveQuery = 3;
            Global::g_OpenCoverStatus = 5;
        }
        else
        {
            mActiveQuery = 3;
            //_instr->setIsPause(false);
        }

        break;
    case 0x8f03:
        if (Global::g_OpenCoverStatus == 5)
            break;
        if (mActiveQuery == 3)
            break;
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f03"));
        //_instr->setIsPause(false);
        break;
    default:
        break;
    }
}

void MainWidget::writeAlarmInfo(QString sz,QString fileName)
{
    QString strExePath = QDir::currentPath();
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyyMMdd");//("yyyy-MM-dd hh:mm:ss");
    QString str1 = QString("[%1]    %2\n").arg(time.toString("yyyy-MM-dd hh:mm:ss.zzz")).arg(sz);
    QString filePath = QString("%1/log/%2/%3").arg(strExePath).arg(str).arg(fileName);
    //filePath = QString("%1/log/%2/%3").arg("D:/linshi/Y72/project2022042901/project/camera_project_Qt_Release/camera_project_Qt/Bin").arg(str).arg(fileName);
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    file.write(str1.toUtf8());
    file.close();
}
void MainWidget::inquireSensorStateMain()
{
    //如果主动查询完成，则返回
    if (mActiveQuery == 2)
        return;
    //_instr->inquireSensorState();
    mActiveQuery = 2;
}

void MainWidget::slotMinitorSensorState(ushort code, bool isSucess)
{

    int needCode = 0;
    if (code & 0b0000001 == 1)
    {
        //设备开盖传感器有效
        needCode = 0x8f00;
    }
    else
    {
        needCode = 0x8f03;
    }
    slotAlarmInfo(needCode);

}

void MainWidget::slotMinitorTemperature(float temperature)
{
    //temperature = 23.8;
    if (temperature < 15 || temperature >45)
    {
        _ui->lbTemperature->setStyleSheet("QLabel {  color : rgb(255, 219, 117);  }");
        QString str = "";
        str = QString("%1").arg(temperature);
        writeAlarmInfo(str, "temperature.log");
    }
    else
    {
        _ui->lbTemperature->setStyleSheet("QLabel {  color : rgb(122, 122, 122); }");
    }
    QString str = "";
    QString str2 = QString::number(temperature, 'f', 1);
    str = QString("%1：%2 ℃  ").arg(GlobalData::LoadLanguageInfo(g_language_type, "K1007")).arg(str2);
    _ui->lbTemperature->setText(str);
}

void MainWidget::slotMonthMaintain(int result)
{
    switch (_maintainStep)
    {
    case 1://浸泡
    {
        if (result < 0)
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1344"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            return;
        }
        //_instr->maintain(eTubeSoak);
        _maintainStep = 2;
        m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1627"));//"管路浸泡中......");
        m_progressDialog->setMaxValue(15 * 60 * 1000);
        m_progressDialog->exec();
        break;
    }
    case 2:
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1345"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
        //_instr->setPumpVect(pumpVect);
        //_instr->maintain(ePumpFill);
        if (_maintainType == MENU_ID_MONTH_MANTAINCE)
            _maintainStep = 3;
        else if (_maintainType == MENU_ID_WEEK_MANTAINCE)
            _maintainStep = 4;
        //        m_progressDialog->setHead("清水充灌......");
        //        m_progressDialog->exec();
        break;
    }
    case 3://蠕动泵校准
    {
        if (result < 0)
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1346"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            return;
        }
        QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
        //_instr->setPumpVect(pumpVect);
        //_instr->maintain(ePumpCalibrate);
        _maintainStep = 4;
        //        m_progressDialog->setHead("蠕动泵校准......");
        //        m_progressDialog->exec();
        break;
    }
    case 4://充灌排空
    {
        if (result < 0)
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1347"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            return;
        }
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1348"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
        //_instr->setPumpVect(pumpVect);
        //_instr->maintain(ePumpFill);
        //        m_progressDialog->setHead("最后充灌......");
        //        m_progressDialog->exec();
    }
    }
}
