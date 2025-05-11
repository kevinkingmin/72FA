#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include "loginform.h"
#include "mainWidget.h"
#include <QtConcurrent/QtConcurrent>
#include "src/types/HumaClia2000.h"
#include <QSettings>
#include "../Include/Instrument/Instrument.h"
#include "src/comm/GlobalData.h"
#include "../Camera/Camera.h"
#include "../Camera/TestResultDataAll.h"
#include "../utility/SystemSet.h"
#include "../utility/ReagentManager.h"
#include "../utility/TestPaperManage.h"
#include "../utility/TubeManage.h"
#include "../DAO/src/user/UserDao.h"
#include <QMenuBar>
#include <qt_windows.h>
#include <windowsx.h>  
#include <QSharedMemory>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../comm/Global.h"
#include <QDateTime>
#include "src/main/subDialog/MyMessageBox.h"
#include <QThread>

#include "CreateDump.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    //setWindowTitle(tr("HumaBlot 72FA"));
    setWindowTitle(tr("HumablotPro"));
    setWindowIcon(QIcon(":/favicon.ico"));
    setWindowIcon(QIcon(":/images/buttonIcon/icon.png"));

    auto dao = AnalysisUIDao::instance();
    bool bResult;
    QString g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
    GlobalData::setLanguageType(g_language_type);

    QString sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1609");
    QString sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1610");
    QString sz3 = GlobalData::LoadLanguageInfo(g_language_type, "K1611");
    //设置 杯类型
    GlobalData::setMapSampleCupType({
                                        {0, sz1},
                                        {1, sz2},
                                        {2, sz3}
                                    });

    sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1612");
    sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1613");

    GlobalData::setMapSexType({ { 0, sz1 },
                                { 1, sz2 } });

    showMaximized();
    initUi();

    CCreateDump::Instance()->DeclarDumpFile("dumpfile");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sltLogin(QString userid, QString password)
{

    int GroupID;
    QString userName;

    bool bResult = true;
    auto dao = UserDao::instance();

    QString sql = QString("select * from tuser where LoginName='%1' and uPassword='%2'").arg(userid).arg(password);
    QSqlQuery ResultQuery = dao->SelectRecord(&bResult,sql);

    if (ResultQuery.size() <= 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1590"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1591") , MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
        return;
    }

    while (ResultQuery.next())
    {
        GroupID = ResultQuery.value("GroupID").toInt();
        userName = ResultQuery.value("LoginName").toString();
    }
    GlobalData::setLoginName1(userName);
    GlobalData::setGroupId(QString("%1").arg(GroupID));


    _MainWidget = new MainWidget(this, GroupID, userName);
    ui->stackedWidget->insertWidget(HumaClia2000::WindowMain, _MainWidget);
    connect(_MainWidget, &MainWidget::sglLogout, this, &MainWindow::sltLogOut);
    connect(_MainWidget, &MainWidget::sglMini, this, &MainWindow::sltShowMinimized);
    connect(_MainWidget, &MainWidget::sglReActiveMainWindow, this, &MainWindow::sltReActiveMainWindow);
    connect(this, &MainWindow::sigUpdateTestResultData, _MainWidget, &MainWidget::sltUpdateTestResultDataListFromMainWindow);
    connect(this, &MainWindow::sglUpdateUpdateSampleWidgetUi1, _MainWidget, &MainWidget::slotUpdateSampleWidgetUi);

    ui->stackedWidget->setCurrentIndex(HumaClia2000::WindowMain);


    _instrument = Instrument::instance();
    _ptrInstrumentState = InstrumentStateModel::instance();
    auto exe_path = GlobalData::getExePath() + "/config/instrumentConfig.ini";
    QSettings config_set(exe_path, QSettings::IniFormat);
    _instrument->start_instrument();
   /* QtConcurrent::run([]() {
        // 这里是线程要执行的任务
        QThread::sleep(1);

    });*/
    // _MainWidget->setIndicateLight();

    _MainWidget->openWelcomeWidgets();

    connect(_instrument, &Instrument::sglIsStepSuc, this, &MainWindow::slotIsStepSuc);
    //_instrument->inquireMachineNo();


    mOpenSoftwareInitFlage = 1;
    _MainWidget->mOpenSoftwareInitFlage = 1;
    int nMachineUID = 0;

    nMachineUID = 1;

    QString m_strMachineUID = QString("%1").arg(nMachineUID, 2, 10, QChar('0'));

    m_strMachineUID = Global::g_machine_no;

    if (m_strMachineUID.length() > 12)
    {
        m_strMachineUID = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1669");
    }

    QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1661")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1666")).arg(userName);
    auto dao1 = AnalysisUIDao::instance();
    dao1->SelectRecord(&bResult, sql1_log);

    Global::g_userid = userName;

    bResult = false;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz");
    sql1_log = QString("insert into t_login_name_info(login_name,login_time)values('%0','%1')").arg(userName).arg(current_date);
    QString sql1_log_update = QString("update t_login_name_info set login_time='%0' where login_name='%1'").arg(current_date).arg(userName);
    QString check_login_name_sql = QString("select * from t_login_name_info where login_name='%0'").arg(userName);

    auto select_login_name_info = dao1->SelectRecord(&bResult, check_login_name_sql);
    QString  user_name = "";

    while (select_login_name_info.next())
    {
        user_name = select_login_name_info.value("login_name").toString();
    }

    if (bResult && user_name== userName)
    {
        bResult = false;
        dao1->SelectRecord(&bResult, sql1_log_update);
    }
    else
    {
        bResult = false;
        dao1->SelectRecord(&bResult, sql1_log);
    }

}

void MainWindow::slotIsStepSuc(int ret)
{
    if (ret == 1)
    {
        bool bResult = true;
        //QString nMachineUID = _instrument->get_machine_no();//20220202001;//
        QString nMachineUID = "_instrument->get_machine_no()";
        QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1661")).arg(nMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1666")).arg(Global::g_userid);
        auto dao1 = AnalysisUIDao::instance();
        dao1->SelectRecord(&bResult, sql1_log);


        QString uid = "";
        uid = QString("%1").arg(nMachineUID);
        int uid_i = uid.mid(0, 4).toInt();
        char month_i = uid.mid(4, 2).toInt();
        char version_i = uid.mid(6, 2).toInt();;
        char factory_index = uid.mid(8, 3).toInt();
        Global::g_machine_no = uid;
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == this)
    {
        activateWindow();
    }
    QWidget::eventFilter(obj, ev);
    return true;
}

bool MainWindow::nativeEventFilter(const QByteArray & eventType, void * message, long * result)
{
    if (eventType == "windows_generic_MSG")
    {
        MSG *param = static_cast<MSG *>(message);
        switch (param->message)
        {
        case WM_COPYDATA:
        {
            COPYDATASTRUCT *cds = reinterpret_cast<COPYDATASTRUCT*>(param->lParam);
            QString content = "";
            content = QString("%1").arg(reinterpret_cast<char*>(cds->lpData));//.arg(cds->lpData).arg(cds->lpData);
            QString strMessage = QString::fromLocal8Bit(reinterpret_cast<char*>(cds->lpData), cds->cbData);
            if (strMessage == "发送完成")
            {
                //更新列表
                int finish = 0;
                emit sigUpdateTestResultData("sss", "aaaaa");
                MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1592"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                auto dao = AnalysisUIDao::instance();
                bool bResult = true;
                QString sql = QString("update tsample_test set sendLisFlag=3 where sendLisFlag =2 ");
                dao->SelectRecord(&bResult, sql);
            }

            if (strMessage == "实时膜式发送完成")
            {
                //更新列表
                int finish = 0;
                emit sigUpdateTestResultData("sss", "aaaaa");
                MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1592"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
                auto dao = AnalysisUIDao::instance();
                bool bResult = true;
                QString sql = QString("update tsample_test set sendLisFlag=3 where sendLisFlag =2 ");
                dao->SelectRecord(&bResult, sql);
            }

            if (strMessage != "")
            {
                QString msg = strMessage;
                emit sglUpdateUpdateSampleWidgetUi1();
            }

            *result = 1;
            return true;
        }
        }
        return QWidget::nativeEvent(eventType, message, result);
    }
    return QWidget::nativeEvent(eventType, message, result);
}

void MainWindow::shareMemery()
{
    QSharedMemory shareMem;         //1-实例化QSharedMemory类
    shareMem.setKey("TestMem");     //1-通过函数setKey()设置标志名;
    if (!shareMem.attach())          //
    {
        return;
    }
    char str[100];
    shareMem.lock();                //2- 调用lock()将共享内存上锁
    const char *source = (char*)shareMem.constData();
    char *dest = str;
    memcpy(dest, source, 100);      //3-对共享内存进行数据写入
    shareMem.unlock();              //4- 调用unlock()函数将共享内存解锁

}

void MainWindow::readSharedMemQt()
{
    QSharedMemory sharedMemory;
    sharedMemory.setKey("LisTool");
    QString tmpStr("");
    while (true)
    {
        char c;
        if (!sharedMemory.isAttached())
        {
            if (!sharedMemory.attach())
            {
                //qDebug() << sharedMemory.errorString();
            }
            else
            {
                sharedMemory.lock();
                QByteArray arr((char*)sharedMemory.data(), sharedMemory.size());
                tmpStr = arr;
                sharedMemory.unlock();
                sharedMemory.detach();
                Sleep(30);
            }
        }
        Sleep(1000);
    }
}


bool MainWindow::winEvent(MSG *message, long *result)
{
    if (message->message == WM_COPYDATA) {
        COPYDATASTRUCT * p = reinterpret_cast<COPYDATASTRUCT*>(message->lParam);
    }
    return MainWindow::winEvent(message, result);
}

void MainWindow::sltReActiveMainWindow()
{
    int stack_count = ui->stackedWidget->count();
    for (int i = ui->stackedWidget->count() - 1; i >= 0; i--)
    {
        QWidget* widget = ui->stackedWidget->widget(i);
        QString windowsTitle = widget->metaObject()->className();
        if (windowsTitle == "MainWidget")
        {
        }
    }
    ui->stackedWidget->setCurrentIndex(HumaClia2000::WindowMain);

    raise();
    activateWindow();
    show();

}

void MainWindow::sltLogOut()
{
    //K1595
    int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1595"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if (ret == MyMessageBox::Yes) {
        Instrument::instance()->closeSocket();
        int stack_count = ui->stackedWidget->count();
        for (int i = ui->stackedWidget->count() - 1; i >= 0; i--)
        {
            QWidget* widget = ui->stackedWidget->widget(i);
            // 这里使用GetWindowTextA而不是GetWindowTextW，应为GetWindowTextA使用LPSTR，而GetWindowTextW使用的则是LPWSTR
            QString windowsTitle = widget->metaObject()->className();
            //QString windowsTitle = widget->windowTitle();
            if (windowsTitle == "MainWidget")
            {
                _MainWidget->killTimerLs(1);
                ui->stackedWidget->removeWidget(widget);
                widget->deleteLater();
            }
            //ui->stackedWidget->removeWidget(widget);
            //widget->deleteLater();
        }
        ui->stackedWidget->setCurrentIndex(HumaClia2000::WindowLogIn);
    }
}

void MainWindow::sltShowMinimized()
{
    showMinimized();
}

void MainWindow::initUi()
{
    _LogInForm = new LogInForm(this);
    ui->stackedWidget->insertWidget(HumaClia2000::WindowLogIn,_LogInForm);
    ui->stackedWidget->setCurrentIndex(0);
    initSigAndSlt();
}

void MainWindow::initSigAndSlt()
{
    //SIGNAL(SigTest(QString))
    connect(_LogInForm, &LogInForm::sigLogIn,this,&MainWindow::sltLogin);
}
