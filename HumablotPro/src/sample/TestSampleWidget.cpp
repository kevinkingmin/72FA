#include "TestSampleWidget.h"
#include "ui_TestSampleWidget.h"
#include <QProgressBar>
#include "subDialog/SelectProcessDialog.h"
#include "subDialog/PrepareReagentDialog.h"
#include "src/comm/CustomLabel.h"
#include "src/comm/CustomerPumpStateLable.h"
#include <QDateTime>
#include <QStyle>
#include <QMessageBox>
#include <QTimer>
#include <QButtonGroup>
#include <QVariant>
#include <QSqlQuery>
#include "src/comm/ObjectTr.h"
#include "src/comm/CustomButton.h"
#include "../sample/model/AddSampleVModel.h"
#include "../Instrument/src/Instrument.h"
#include "../Model/src/baseSet/InstrumentStateModel.h"
#include "../DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Utilities/log.h"
#include "../BLL/src/baseSet/TestPaperBLL.h"
#include "../BLL/src/sample/SampleBLL.h"
#include "../Analysis/analysis.h"
#include <QDesktopWidget>
#include <QtXml>
#include <QFileDialog>
#include "src/comm/Global.h"
#include "src/main/subDialog/MyMessageBox.h"
#include <QDir>
#include <qdebug.h>
#include <QThread>
#include <QFileInfo>
#include <qdebug.h>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QtXml>
#include <QFileDialog>
#include "../Model/sample/SampleTestModel.h"
#include "../Model/baseSet/TestPaperModel.h"
#include <QtConcurrent/QtConcurrent>
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#define PROPERTY "lbl"
QString TestSampleWidget::_imgPath(":/images/indicate/");
QString TestSampleWidget::_readyFileName("indicateSelect.png");
QString TestSampleWidget::_delayFileName("indicateRed.png");
QString TestSampleWidget::_emptyFileName("indicateSkip.png");
QString TestSampleWidget::_usedFileName("indicateSelect.png");
TestSampleWidget::TestSampleWidget(PrepareReagentDialog * dialog, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestSampleWidget)
  , m_listTest{}
  , m_selectPDialog(nullptr)
  , _timer(nullptr)
  , _lblPaperVect{}
  , _lblPumpVect{}
  , _sampleTestTpVect{}
  , _pReagentDialog(dialog)
  , _btnGroup{ nullptr }
  , _isNewTest{ true }
  , _instrument{ Instrument::instance() }
  , _instrState(InstrumentStateModel::instance())
  , _currentGroupId(0)
  , _stepRunTimeMap{}
  ,_stepName("")
{
    ui->setupUi(this);
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
    initUI();
    //m_run_paper_pos_thread = new RunPaperPosThread();
    //connect(this, SIGNAL(preper_save(TestSampleWidget *)), m_run_paper_pos_thread, SLOT(getaddress(TestSampleWidget *)));//链接信号和槽
    //connect(m_run_paper_pos_thread, SIGNAL(UpdateSignal(int)),this, SLOT(UpdateSlot(int)));
    //connect(_instrument, &Instrument::sglAlarmInfo, this, &TestSampleWidget::slotAlarmInfo);
    //connect(_instrument, &Instrument::sglHandleStepDetail, this, &TestSampleWidget::slotHandleStepDetail);
    //connect(_instrument, &Instrument::sglIsStepSuc, this, &TestSampleWidget::slotIsStepSuc);
    connect(_instrument, &Instrument::sglDetectionStartResult, this, &TestSampleWidget::slotDetectionStartResult,Qt::QueuedConnection);
    connect(_instrument, &Instrument::sglDetectionPauseResult, this, &TestSampleWidget::slotDetectionPauseResult);
    connect(_instrument, &Instrument::sglDetectionContinueResult,this, &TestSampleWidget::slotDetectionContinueResult);
    connect(_instrument, &Instrument::sglDetectionStopResult,this, &TestSampleWidget::slotDetectionStopResult);
    connect(this, &TestSampleWidget::testFinish,this,&TestSampleWidget::slotTestFinish,Qt::QueuedConnection);

    ui->lblStep->setVisible(false);
    ui->subStepsWidget->setVisible(false);

    ui->label_9->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1093"));
    ui->label_3->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1094"));
    ui->label_5->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1095"));
    ui->label_2->setText("<b style=\"font-size:18px;font-weight:bold;color:gray;\">" + GlobalData::LoadLanguageInfo(g_language_type, "K1096") + "：</b>");
}

void TestSampleWidget::setProgressDialog(ProgressDialog *progressDialog){
    this->m_progressDialog = progressDialog;
}

void TestSampleWidget::slotUpdateTime(){
    QTime current=QTime::currentTime();
    int t = this->startTime.msecsTo(current);
    QTime showTime(0,0,0,0);
    showTime=showTime.addMSecs(t);
    ui->lblSolutionEnd->setText(showTime.toString("HH:mm:ss"));
    if (_instrState->getMachineState().state == _instrState->enumPause)
    {
        t = this->pauseTime.msecsTo(current);
        QTime showTime(0,0,0,0);
        showTime=showTime.addMSecs(t);
        ui->lblPause->setText(showTime.toString("HH:mm:ss"));
        return;
    }

//    t = this->stepTime.msecsTo(current);
//    showTime = stepTimeTotal.addMSecs(-t);
//    if(showTime.toString("HH:mm:ss")<stepTimeTotal.toString("HH:mm:ss")){
//        ui->lblPlainEnd->setText(showTime.toString("HH:mm:ss"));
//    }
}
void TestSampleWidget::slotTestFinish(){
    ui->lblPlainEnd->setText("00:00:00:00");
	_instrState->setMachineState(InstrumentStateModel::enumStandby);
    MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1424"),MyMessageBox::Ok, GlobalData::LoadLanguageInfo("K1181"), "");
}

void  TestSampleWidget::slotDetectionStartResult(QString messageType, QString sample,QString slot,QString step,QString code,QString time){
	QMutexLocker lock(&_lock);
	if(messageType=="1"){//开始
        ui->progressBar->setRange(0, 0);
        ui->progressBar->setVisible(true);
        if(_timer==nullptr){
            _timer=new QTimer;
        }
        startTime = QTime::currentTime();
        ui->lblSolutionEnd->setText("00:00:00:00");
        connect(_timer,SIGNAL(timeout()),this,SLOT(slotUpdateTime()));
        _timer->start(1000);
    }else if(messageType=="2"){//结果
        ui->progressBar->setVisible(false);
		if (_timer != nullptr)
			_timer->stop();
        //QString result = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1029");
        if(code!="0"){
            QString result= GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code);
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), result,MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
            return;
        }
		if (!createDir())
		{
			_instrState->setMachineState(_instrState->enumError);
			return;
		}
        //处理照片
        QtConcurrent::run([this, messageType]()
		{
            // 这里是线程要执行的任务
			Analysis m_analysis;
            auto dao = AnalysisUIDao::instance();
            auto pm{ SystemSetBLL().getRowById(9994) };
            bool isUploadLis{ pm.isNull() ? false : pm->getSaveSet() > 0 };
            for(auto test:m_listTest)
            {
                bool ret = m_analysis.AnalysisMothed(test->getTestId(), test->getPaperId(), test->getTestId(),test->getSolutionName(),test->getPatientName());
                if(ret & isUploadLis)
                {
                    QString send_sz=dao->createLISData(test->getTestId()); 
                    if(send_sz.isEmpty())
                    {
                        eLog("create LIS data failed,testId:{}",test->getTestId().toStdString());
                        continue;
                    }
                    m_tcpClient->sendData(send_sz);
                }
            }
            //检测完成，弹窗提示
            _instrState->setMachineState(InstrumentStateModel::enumStandby);
            emit testFinish();
		});
    }else if(messageType=="3"){//阶段信息
        QString result = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1029");
        QDateTime timeNow = QDateTime::currentDateTime();
        if(sample.isNull()||sample.isEmpty()){
            ui->textBrowser_2->append(tr("[%1] 步骤：%2, 结果：%3")
                                      .arg(timeNow.toString("yyyy-MM-dd hh:mm:ss"))
                                      .arg(step).arg(result));
        }else{
            ui->textBrowser_2->append(tr("[%1] 样本：%2, 槽位：%3, 步骤：%4, 结果：%5")
                                      .arg(timeNow.toString("yyyy-MM-dd hh:mm:ss"))
                                      .arg(sample)
                                      .arg(slot)
                                      .arg(step)
                                      .arg(result));
        }
    }else if(messageType=="5"){//阶段信息
        QString result = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1030");
        QDateTime timeNow = QDateTime::currentDateTime();
        if(sample.isNull()||sample.isEmpty()){
            ui->textBrowser_2->append(tr("[%1] 步骤：%2, 结果：%3")
                                      .arg(timeNow.toString("yyyy-MM-dd hh:mm:ss"))
                                      .arg(step).arg(result));
        }else{
            ui->textBrowser_2->append(tr("[%1] 样本：%2, 槽位：%3, 步骤：%4, 结果：%5")
                                      .arg(timeNow.toString("yyyy-MM-dd hh:mm:ss"))
                                      .arg(sample)
                                      .arg(slot)
                                      .arg(step)
                                      .arg(result));
        }
    }
    else if(messageType=="4"){//时间更新
        ui->lblPlainEnd->setText(time);
        stepTime = QTime::currentTime();
        stepTimeTotal = QTime::fromString(time, "HH:mm:ss");
    }
}

void  TestSampleWidget::slotDetectionPauseResult(QString code){
    if(code=="0"){
        _instrState->setMachineState(InstrumentStateModel::enumPause);
        ui->lblPause->setText("00:00:00:00");
        pauseTime = QTime::currentTime();
    }else{
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }
}

void  TestSampleWidget::slotDetectionContinueResult(QString code){
    if(code=="0"){
        ui->lblPause->setText("00:00:00:00");
        _instrState->setMachineState(InstrumentStateModel::enumRuning);
    }else{
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }
}

void  TestSampleWidget::slotDetectionStopResult(QString code){
    if(code=="0"){
        _instrState->setMachineState(InstrumentStateModel::enumStandby);
        ui->progressBar->setVisible(false);
        ui->progressBar->reset();
        _timer->stop();
        m_progressDialog->done(1);
        emit testStop();
        //m_sampleWidget->ReturnSampleEdit();
    }else{
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }
}

void TestSampleWidget::slotIsStepSuc(int ret) {
    if (ret >= 0)
    {
        if (m_test_result_flage)
        {
            auto state = _instrState->getMachineState();
            if (state.state == _instrState->enumError)
            {
                return;
            }

            if (m_i_init_number == 1)
            {
                QVector<uchar>motorVect;
                motorVect.push_back(0x02);
                motorVect.push_back(0x03);
                motorVect.push_back(0x04);
                motorVect.push_back(0x05);
                motorVect.push_back(0x01);
                //_instrument->motorsInitialize(motorVect, 60000);
            }
            m_i_init_number++;
            if (m_i_init_number == 3)
            {
                m_test_result_flage = FALSE;
                m_i_init_number = 0;

                /*if (Global::g_stop_flage == 0)
                {
                    MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1424"),MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
                    ui->btnSet->setEnabled(false);
                }
                else
                {
                    MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1425"),MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
                    ui->btnSet->setEnabled(false);
                }*/

                mPause_time = 0;
                ui->lblPause->setText(traslationSecondToString(mPause_time));

            }
        }
    }
    else
    {

    }
}

void TestSampleWidget::slotAlarmInfo1(QString alarm_info,QString code_type)
{
    SaveRunInfo(alarm_info);
    QDateTime time = QDateTime::currentDateTime();
    if (GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9009") == alarm_info)  //0x9009
    {
        QString str1 = QString("[%1] %2，%3").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9009")).arg(m_current_disk_position).arg(m_current_slot_position);
        ui->textBrowser_2->append(str1);
    }
    //else if ("样本臂吸样时样Z轴电机使能液位探测时右光电立即有效" == alarm_info) //0x9005
    else if (GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9005") == alarm_info) //0x9005
    {
        QString str1 = QString("[%1] %2，%3").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9005")).arg(m_current_disk_position).arg(m_current_slot_position);
        ui->textBrowser_2->append(str1);
    }
    //else if ("样本臂吸样时Z轴电机运动至吸液位置发生垂直碰撞" == alarm_info)  //0x9006
    else if (GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9006") == alarm_info)  //0x9006
    {
        QString str1 = QString("[%1] %2，%3").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9006")).arg(m_current_disk_position).arg(m_current_slot_position);
        ui->textBrowser_2->append(str1);
        //m_errorAddSampleMap1.insert(m_current_slot_position, str1);
    }
    //else if ("样本臂吐样时Z轴电机运动至吐样位置发生垂直碰撞" == alarm_info)  //0x901F
    else if (GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x901F") == alarm_info)  //0x901F
    {
        QString str1 = QString("[%1] %2，%3").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x901F")).arg(m_current_disk_position).arg(m_current_slot_position);
        ui->textBrowser_2->append(str1);
        //m_errorAddSampleMap1.insert(m_current_slot_position, str1);
    }
    //else if ("清洗针下降时垂直碰撞" == alarm_info) //0x9016
    else if (GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9016") ==alarm_info) //0x9016
    {
        QString str1 = QString("[%1] %2，%3").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9016")).arg(m_current_disk_position).arg(m_current_slot_position);
        ui->textBrowser_2->append(str1);
    }
    //else if ("蠕动泵校准时Z轴电机使能液位探测时右光电立即有效" == alarm_info) //0x9060
    else if (GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9060") ==alarm_info) //0x9060
    {
        QString str1 = QString("[%1] %2，%3").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x9060")).arg(m_current_disk_position).arg(m_current_slot_position);
        ui->textBrowser_2->append(str1);
    }
    //else if ("样本针开启液位探测后全程未检测到液位(样本位吸样)" == alarm_info)
    else if (GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f06") == alarm_info)
    {
        QString str1 = QString("[%1] %2，%3").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f06")).arg(m_current_disk_position).arg(m_current_slot_position);
        ui->textBrowser_2->append(str1);
        //_instrument->setBuzzleOnOff(0);
        //Global::g_stop_flage = 2;
        Sleep(150);
    }
    //else if ("样本针探测到液位后到达最大距离(样本位吸样)" == alarm_info)
    else if (GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f07") == alarm_info)
    {
        //QString str1 = QString("[%1] %2，%3").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg("样本针探测到液位后到达最大距离(样本位吸样)").arg(m_current_disk_position).arg(m_current_slot_position);
        QString str1 = QString("[%1] %2，%3").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f07")).arg(m_current_disk_position).arg(m_current_slot_position);
        ui->textBrowser_2->append(str1);
        //_instrument->setBuzzleOnOff(0);
        //Global::g_stop_flage = 2;
        Sleep(150);
    }

    //else if ("上盖打开" == alarm_info)
    else if (GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1342") == alarm_info)
    {
        QString str1 = QString("[%1] %2").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(alarm_info);
        ui->textBrowser_2->append(str1);

    }else{
        QString str1 = QString("[%1] %2").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(alarm_info).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1680"));//K1680"停止并完成检测！！！");
        ui->textBrowser_2->append(str1);
        //Global::g_stop_flage = 2;

        //停机，把线程也停掉
        if (_timer != nullptr)
        {
            if (code_type == "01")
            {
                _timer->stop();
                delete _timer;
                _timer = nullptr;
                //_instrument->machineStop();
            }
        }
        //m_run_paper_pos_thread->quit();
        //m_run_paper_pos_thread->m_run_flage1 = false;
        if (Global::g_run_or_maintenance_flage == 1)
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), alarm_info, MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        }

        if (Global::g_run_or_maintenance_flage == 0)
        {
            if (code_type == "01")
            {
                Sleep(200);
                //_instrument->lightControl(12, 0);
                Sleep(200);

                /*if (Global::g_stop_flage == 0)
                {
                    auto dao = AnalysisUIDao::instance();
                    bool bResult;
                    int is_camera_open = dao->SelectSaveSetById(&bResult, 20008).toInt();
                    if (is_camera_open)
                    {
                        ui->lblProgress->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1631"));
                    }
                    else
                    {
                        ui->lblProgress->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1424"));
                        ui->lblStep_2->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1632"));
                    }
                    ui->btnSet->setEnabled(false);
                }
                else
                {
                    ui->lblProgress->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1426"));//"运行错误！");
                }*/
                ui->progressBar->setVisible(false);
                MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1426"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            }
        }
    }
}

void TestSampleWidget::SaveRunInfo(QString run_info)
{
    QString solution_name = "";
    for (auto it : m_listTest)
    {
        solution_name = it->getSolutionName();
    }
    QString login_name = GlobalData::getLoginName1();
    _instrument = Instrument::instance();
    QString nMachineUID = "_instrument->get_machine_no()";
    QString m_strMachineUID = nMachineUID;

    m_strMachineUID = Global::g_machine_no;
    bool bResult;
    QString sql1_log = QString("insert into t_run_log(machine_UID,login_name,tip_info,solution_name)values('%1','%2','%3','%4')").arg(m_strMachineUID).arg(login_name).arg(run_info).arg(solution_name);
    auto dao = AnalysisUIDao::instance();
    dao->SelectRecord(&bResult, sql1_log);
}

void TestSampleWidget::slotHandleStepDetail(int stepId, int index, bool isSucess, const QString &stepName)
{
    QString run_info = QString("stepid:[%0]-index:[%1]-isSucess:[%2]-stepName:[%3]").arg(stepId).arg(index).arg(isSucess).arg(stepName);
    SaveRunInfo(run_info);
    QDateTime time = QDateTime::currentDateTime();
    QString str1 = QString("[%1] %2").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(stepName);
    QString str2 = QString("%2").arg(stepName);
    ShowAlarmInfo(str2);

}

//报警信息处理
void TestSampleWidget::slotAlarmInfo(int warnCode)
{
    QString str = "";
    switch (warnCode)
    {
    case 0x8f00:
        if (Global::g_OpenCoverStatus == 5)//在运行界面
            break;
        str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1342"));//"设备开盖");
        if (mOpenCoverAlarmTip == 1)
        {
            ui->lblSubContent->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1342"));//tr("上盖打开"));
            ShowAlarmInfo(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1342"));//tr("上盖打开"));

            auto state = _instrState->getMachineState();
            //if (state.state == InstrumentStateModel::enumRuning)
            //_instrument->setIsPause(true);
        }
        writeAlarmInfo(str, "alarmInfo.log");
        break;
    case 0x8f03:
        if (Global::g_OpenCoverStatus == 5)//在运行界面
            break;
        if (mOpenCoverAlarmTip == 1)
        {
            //0x8f03
            str = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f03"));//"设备未开盖");
            ui->lblSubContent->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f03"));//tr("上盖关闭"));
            ShowAlarmInfo(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "0x8f03"));//tr("上盖关闭"));
            //_instrument->setIsPause(false);
        }
        break;
    }
}

void TestSampleWidget::ShowAlarmInfo(QString sz)
{
    int test_count = m_listTest.count();
    QStringList list1 = sz.split(':');
    QString L1001 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L10011");
    int lfind_postion1 = list1.indexOf(L1001);//"开始");
    QString L1003 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L10031");
    int lfind_postion2 = list1.indexOf(L1003);//"完成");
    QString LLL_sz = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1085") + "--" + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1008") + "," + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L10091");
    int lfind_postion3 = list1.indexOf(LLL_sz);//"加样本--样本臂移液,吸样位");

    if (lfind_postion1 == 0 && lfind_postion3 == 1)
    {
        QDateTime time = QDateTime::currentDateTime();
        QString str1 = QString("[%1] %2").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(sz);
        m_current_slot_position = 1;
        if (list1.size() > 0)
        {
            QStringList list2 = list1[4].split(',');
            m_current_disk_position = list1.at(1) + list1.at(2) + list1.at(3)+ list2[0];
            m_current_slot_position = list1[5].toInt();
        }
    }


    if (lfind_postion2 == 0 && lfind_postion3 == 1)
    {
        QDateTime time = QDateTime::currentDateTime();
        QString str1 = QString("[%1] %2").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(sz);
        if (list1.size() == 7)
        {
            QStringList list4 = list1.at(2).split(';');
            m_current_disk_position = list1.at(4).split(',')[0];
            int slot_postion = list1.at(5).split(',')[0].toInt();
            m_current_slot_postion = (m_current_disk_position.toInt() - 1) * 24 + slot_postion;
            QString liquid_height1 = list1.at(3);
            QStringList list3 = list1.at(6).split(',');
            liquid_height1 = "";

            if (list3.size() > 0)
            {
                liquid_height1 = list3.at(0);
            }

            QString liquid_height2 = list3.at(1).mid(3);
            if (GlobalData::getLanguageType() == "2")
            {
                liquid_height2 = list3.at(1).mid(10);
            }

            if (liquid_height1 != "")
            {
                if (liquid_height1.toInt() == liquid_height2.toInt())
                {
                    time = QDateTime::currentDateTime();
                    QString tip = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1633");//"吸液量异常";
                    //
                    QString sz1 = m_current_disk_position;
                    QString sz2 = QString::number(slot_postion);
                    str1 = QString("[%1] %4,  %5 %2 %6 %3   ").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(sz1).arg(sz2).arg(tip).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1011")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1012"));
                    m_errorAddSampleMap.insert(m_current_slot_postion, str1);
                    ui->textBrowser_2->append(str1);
                }
            }
            if( (m_current_slot_postion == (m_start_slot_postion+ m_test_count1 -1) && m_errorAddSampleMap.count()>0) || (m_current_slot_postion == (m_start_slot_postion + m_test_count1 - 1) && m_errorAddSampleMap1.count() > 0))
            {
                QString tip_error = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1427")+ "\n";
                int a_i_n = 1;

                for (auto it = m_errorAddSampleMap.begin(); it != m_errorAddSampleMap.end(); ++it) {
                    tip_error +=QString("%1   ").arg(it.value()) ;
                    if (a_i_n % 2 == 0)
                    {
                        tip_error += "\n";
                    }
                    a_i_n++;
                }
                //_instrument->setBuzzleOnOff(0x02);
                //_instrument->setIsPause(true);
                mPause_flage = true;
                MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tip_error, MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                //_instrument->setBuzzleOnOff(0);
                QDateTime begin_time = QDateTime::currentDateTime();
                mToatal_time = mWetting_time + mAddSample_time + mWash_time + mAddEnzyme_time + mSecondary_wash_time + mAddSubstrate_time + mAddPureWater_time + mAddTerminationLiquid_time + mDry_time;
                mToatal_solution_time = mWetting_time_old + mAddSample_time_old + mWash_time_old + mAddEnzyme_time_old + mSecondary_wash_time_old + mAddSubstrate_time_old + mAddPureWater_time_old + mAddTerminationLiquid_time_old + mDry_time_old;
                mPause_total_time += mPause_time;
                QDateTime ss = QDateTime::currentDateTime().addSecs(+(mToatal_time + 0));
                QString currentTime = ss.toString("hh:mm:ss");
                mToatal_solution_time = mToatal_solution_time + mPause_total_time;
                ui->lblSolutionEnd->setText(traslationSecondToString(mToatal_solution_time));
                ui->lblPlainEnd->setText(currentTime);
                //_instrument->setIsPause(false);
                mPause_flage = false;
            }
        }
    }
}

void TestSampleWidget::writeAlarmInfo(QString sz, QString fileName)
{
    QString strExePath = QDir::currentPath();
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyyMMdd");//("yyyy-MM-dd hh:mm:ss");
    QString str1 = QString("[%1]    %2\r").arg(time.toString("yyyy-MM-dd hh:mm:ss.zzz")).arg(sz);
    QString filePath = QString("%1/log/%2/%3").arg(strExePath).arg(str).arg(fileName);
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    file.write(str1.toUtf8());
    file.close();
}

void TestSampleWidget::UpdateSlot(int num)
{
    m_i_init_number = 0;
    /*if (Global::g_stop_flage == 0)
    {
        auto dao = AnalysisUIDao::instance();
        bool bResult;
        int is_camera_open = dao->SelectSaveSetById(&bResult, 20008).toInt();
        if (is_camera_open)
        {
            ui->lblProgress->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1631"));//"检验完成，请到报告->报告查询，查看检验结果。");
        }
        else
        {
            ui->lblProgress->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1424"));//"检验完成");
            ui->lblStep_2->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1632"));//"结束");
        }
        ui->btnSet->setEnabled(false);
        Sleep(200);
        //_instrument->lightControl(12, 0);
        m_test_result_flage = true;
        m_i_init_number++;
    }
    else
    {
        ui->lblProgress->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1634"));
    }*/
    ui->progressBar->setVisible(false);
}

bool TestSampleWidget::SaveDataFromPic()
{
    return true;
}

void TestSampleWidget::setTcpClient(TcpClient *tcpClient)
{
    m_tcpClient = tcpClient;
}

TestSampleWidget::~TestSampleWidget()
{
    if (_timer != nullptr)
        delete _timer;
    delete ui;
}

void TestSampleWidget::setListTest(QVector<ptrTest> listTest)
{
    m_listTest.swap(listTest);
}

//创建膜条在膜条盘中的示意图
void TestSampleWidget::setPapersState()
{
    //clearLayOut(ui->hLayPaperPos);
    for (auto lbl : _lblPaperVect)
    {
        lbl->reset();
        auto it = searchPmByPos(lbl->getPos());
        if (it.isNull())
            continue;

        auto paper = TestPaperBLL().getRowById(it->getPaperId());
        if (paper.isNull())
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1428"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            //eLog("找不到对应的膜条,paperId:{}", it->getPaperId());
            continue;
        }
        lbl->setBgColor(paper->getBGRGB());
        lbl->setText(paper->getPaperName());
    }
}

void TestSampleWidget::setPumpLblState()
{
    if (_btnGroup == nullptr)
        return;
    auto btns = _btnGroup->buttons();
    auto fun = [btns](int id)->CustomButton *
    {
        for (auto it : btns)
        {
            auto btn = reinterpret_cast<CustomButton *>(it);
            if (btn->objectName().toInt() == id)
                return btn;
        }
        return nullptr;
    };

    QString fileStr = "";
    for (auto lbl : _lblPumpVect)
    {
        lbl->reset();
        auto id = lbl->objectName().toInt();
        auto btn = fun(id);

        auto propertyValue = btn->property(GlobalData::getPropertyName()).toInt();
        if (propertyValue == PumpPosState::enumDelay)
            fileStr = _imgPath + _delayFileName;
        else if (propertyValue == PumpPosState::enumEmpty)
            fileStr = _imgPath + _emptyFileName;
        else if (propertyValue == PumpPosState::enumFlush)
            fileStr = _imgPath + _usedFileName;
        else if (propertyValue == PumpPosState::enumReady)
            fileStr = _imgPath + _readyFileName;
        else
            fileStr = "";
        if (fileStr.isEmpty())
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1429"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            //eLog("生成指示图失败");
            return;
        }
        lbl->setProperty(PROPERTY, propertyValue);
        lbl->setPos(id + 1);
        lbl->setPixPath(fileStr);
        lbl->setTimeStr(btn->getTimeText());
    }
}

void TestSampleWidget::ClearTextBrowser()
{
    ui->textBrowser_2->setText("");//->clear();

    ui->lblPause->setText("___:___:___");
    ui->lblSolutionEnd->setText("___:___:___");
    ui->lblPlainEnd->setText("___:___:___");

    ui->lblSubTitle->setText("<b style=\"font-size:18px;font-weight:bold;color:gray;\">"+ GlobalData::LoadLanguageInfo(g_language_type, "K1088") +"：</b>");
    ui->textBrowser_2->setStyleSheet("color:rgb(163,0,0,200);font-size:20px;background:transparent; border-width:0; border-style:outset;");
    ui->btnSet->setEnabled(true);

    ui->lblProgress->setText("");
}

void TestSampleWidget::initUI()
{
    QString step = GlobalData::LoadLanguageInfo(g_language_type, "K1086");//"待测状态";
    ui->lblStep->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1087")+":<br/><b style=\"font-size:21px;font-weight:bold;color:gray;\">" + step + "</b>");//"步骤:<br/><b style=\"font-size:21px;font-weight:bold;color:gray;\">" + step + "</b>");
    ui->lblSubTitle->setText("<b style=\"font-size:18px;font-weight:bold;color:gray;\">" + GlobalData::LoadLanguageInfo(g_language_type, "K1088") + "：</b>");
    ui->lblSubContent->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1089"));//(tr("提示描述信息"));

    ui->textBrowser_2->setStyleSheet("background:transparent; border-width:0; border-style:outset;");

    ui->lblSubContent->setVisible(false);
    ui->btnSubBody->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1090"));//(tr("略去用盖子保护"));
    ui->progressBar->setFormat(GlobalData::LoadLanguageInfo(g_language_type, "K1090")+ ":" + QString::number(0, 'f', 2) + "%");//"当前进度:" + QString::number(0, 'f', 2) + "%");
    ui->progressBar->setVisible(false);
    ui->lblProgress->setText("......");
    //创建膜条标签
    createPapers();
    connect(ui->btnFlushWidget, SIGNAL(clicked()), this, SLOT(slotPumpFlush()), Qt::UniqueConnection);
    connect(_pReagentDialog, &PrepareReagentDialog::sglPumpStateChange, this, [this]() {
        setPumpLblState();
    });

    connect(_instrument,&Instrument::sglHandelStepName,this,[this](const QString &stempName){_stepName=stempName;});
    connect(_instrument, &Instrument::sglCurrentGroupIdChanged, this,&TestSampleWidget::slotCurrentGroupIdChanged, Qt::UniqueConnection);
}

TestSampleWidget::ptrTest TestSampleWidget::searchPmByPos(int pos)
{
    for (auto it : m_listTest)
    {
        if (it->getSlotPos() == pos)
            return it;
    }
    return nullptr;
}

void TestSampleWidget::createPumpLbl()
{
    if (_btnGroup == nullptr)
        return;
    auto lblCount = _btnGroup->buttons().count();
    for (int i = 0; i < lblCount; i++)
    {
        auto lbl = new CustomerPumpStateLable(this);
        lbl->setProperty(PROPERTY, PumpPosState::enumEmpty);
        lbl->setObjectName(QString::number(i));
        lbl->setPos(i + 1);
        _lblPumpVect.push_back(lbl);
        ui->hLaySteps->addWidget(lbl);
    }
}

void TestSampleWidget::createPapers()
{

    for (auto i = 1; i <= PAPERCOUNT; i++)
    {
        auto it = searchPmByPos(i);
        auto lbl = new CustomLabel(this);
        lbl->setProperty("lblStyle", "lblPaperStyle");
        lbl->setPos(i);
        _lblPaperVect.push_back(lbl);

        if (i>0 && i <= 36)
        {
            ui->hLayPaperPos->addWidget(lbl);
        }

        if (i > 36)
        {
            ui->hLayPaperPos1->addWidget(lbl);
        }
    }
}

void TestSampleWidget::clearLayOut(QHBoxLayout *layOut)
{
    QLayoutItem *child;
    while ((child = layOut->itemAt(0)) != nullptr)
    {
        layOut->removeItem(child);
        delete child->widget();
        delete child;
        child = nullptr;
    }
}

void TestSampleWidget::updateProgress(int maxValue)
{
    if (_timer != nullptr)
    {
        delete _timer;
        _timer = nullptr;
    }
    ui->progressBar->setTextVisible(false);
    _timer = new QTimer(this);
    _timer->setInterval(1000);
    ui->progressBar->setRange(0, maxValue);
    ui->progressBar->setVisible(true);
    connect(_timer, &QTimer::timeout, this, [this, maxValue]()
    {
        if (maxValue <= 0)//当最小值与最大值都为0时，则表示当前忙的状态
        {
            setProgressState();
        }
        else
        {
            ui->progressBar->setValue(1);
            int curValue = ui->progressBar->value();//可以
            curValue++;
            if (curValue >= maxValue + 1)
            {
                setProgressState();
                _timer->stop();
            }

            ui->progressBar->setFormat(GlobalData::LoadLanguageInfo(g_language_type, "K1582") + QString::number((curValue*1.0) / maxValue * 100.0, 'f', 2) + "%");
            ui->progressBar->setValue(curValue);
        }
    }, Qt::UniqueConnection);
    _timer->start();
    ui->progressBar->setTextVisible(true);
}

void TestSampleWidget::setProgressState()
{
    auto state = _instrState->getMachineState().state;
    switch (state)
    {
    case InstrumentStateModel::enumRuning:
    {
        if (Global::g_pause_flage == 1)
        {
            //K1580
            ui->lblProgress->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1580"));//"当前状态：暂停");
        }
        else
        {
            ui->lblProgress->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1581"));
        }
        break;
    }
    case InstrumentStateModel::enumPause:
    {
        ui->lblProgress->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1580"));//"当前状态：暂停");
        break;
    }
    case InstrumentStateModel::enumStandby:
    {
        /*if (Global::g_stop_flage == 1 || Global::g_stop_flage == 2)
        {
            //_instrument->lightControl(12, 0);
            //_instrument->setBuzzleOnOff(0);

            emit preper_save(this);//发送信号将指针传递给槽函数

            ui->lblProgress->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1452"));
            ui->lblStep_2->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1452"));
            ui->btnSet->setEnabled(false);//setVisible(false);
            ui->progressBar->setVisible(false);
            ui->btnSet->setEnabled(false);

            _timer->stop();
        }
        else
        {
            //_instrument->motorInitialize(0x05, 60000);
            Sleep(100);
            QString strExePath = QDir::currentPath();
            QDateTime time = QDateTime::currentDateTime();
            QString str = time.toString("yyyyMMdd");//("yyyy-MM-dd hh:mm:ss");
            QString str1 = QString("[%1]    %2\n").arg(time.toString("yyyy-MM-dd hh:mm:ss.zzz")).arg(GlobalData::LoadLanguageInfo(g_language_type, "K1635"));//"摇床初始化");
            QString filePath = QString("%1/log/%2/%3").arg(strExePath).arg(str).arg("摇床初始记录2.log");
            //filePath = QString("%1/log/%2/%3").arg("D:/linshi/Y72/project2022042901/project/camera_project_Qt_Release/camera_project_Qt/Bin").arg(str).arg(fileName);
            QFile file(filePath);
            file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
            file.write(str1.toUtf8());
            file.close();

            Sleep(6000);
            //open light
            //_instrument->setBuzzleOnOff(0);
            Sleep(500);

            //_instrument->lightControl(12, 1);
            //Sleep(500);

            emit preper_save(this);//发送信号将指针传递给槽函数

            auto dao = AnalysisUIDao::instance();
            bool bResult;
            int is_camera_open = dao->SelectSaveSetById(&bResult, 20008).toInt();
            if (is_camera_open)
            {
                //m_run_paper_pos_thread->start();//开始线程
                //K1583
                //ui->lblProgress->setText("正在进行判读，请勿打开设备上盖。");
                ui->lblProgress->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1583"));//"正在进行判读，请勿打开设备上盖。");
                ui->lblStep_2->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1584"));//"测读");
                ui->btnSet->setEnabled(false);//setVisible(false);
            }
            else
            {
                UpdateSlot(1);
            }
            _timer->stop();
        }*/

        break;
    }
    case InstrumentStateModel::enumError:
    {
        ui->lblProgress->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1584"));//"测试错误");
        ui->progressBar->setVisible(false);
        ShowAlarmInfo(GlobalData::LoadLanguageInfo(g_language_type, "K1584"));//tr("测试错误"));
        //写入错误表
        Global::g_pause_flage = 0;

        _timer->stop();
        break;
    }
    default:
    {
        QString info = QString("%2:{%1}").arg(state).arg(GlobalData::LoadLanguageInfo(g_language_type, "K1586"));
        ShowAlarmInfo(info);
    }
    }

    ui->lblStep->setVisible(false);
    ui->lblStep->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1087")+
                         "<br/>"
                         "<b style=\"font-size:21px;font-weight:bold;color:rgb(0,0,140,120);\">"
                         "" + _stepName + "</b>");
    ui->lblStep->setVisible(false);

    QDateTime time = QDateTime::currentDateTime();
    QString str1 = QString("%1").arg(time.toString("yyyy-MM-dd hh:mm:ss"));

    if (mStartTime == "")
    {
        mStartTime = str1;
    }

    if (mPause_flage)
    {
        mPause_time++;
        ui->lblPause->setText(traslationSecondToString(mPause_time));
    }
    else
    {
        mToatal_time += mPause_time;
        if (mPause_time != 0)
        {
            m_need_add_pause_time = mPause_time;
        }
        mPause_time = 0;
        //根据步骤显示时间
        ui->lblPause->setText(traslationSecondToString(mPause_time));
        TimeShow(_stepName, str1, "", "", "");
    }
}

bool TestSampleWidget::createDir()
{
	auto pathPm = SystemSetBLL().getRowById(3);
	auto rootPath = pathPm.isNull() ? "D:\\HumablotProFiles\\TestPictures" : pathPm->getSaveDes();
	QDir dir;
	auto mkFun = [dir](const QString &pathStr)
	{
		if (!dir.exists(pathStr))
		{
			if (!dir.mkpath(pathStr))
			{
				eLog("make dir failed,path:{}", pathStr.toStdString());
				return false;
			}
		}
		return true;
	};
	if(!mkFun(rootPath + "\\analysised"))
		return false;
	if (!mkFun(rootPath + "\\original"))
		return false;
	pathPm = SystemSetBLL().getRowById(4);
	QString reportPath= pathPm.isNull() ? "D:\\HumablotProFiles\\Reports" : pathPm->getSaveDes();
	if (!mkFun(reportPath))
		return false;
	return true;
}

QString TestSampleWidget::traslationSecondToString(int second)
{
    //将秒数转化为时分秒格式
    int H = second / (60 * 60);
    int M = (second - (H * 60 * 60)) / 60;
    int S = (second - (H * 60 * 60)) - M * 60;
    QString hour = QString::number(H);
    if (hour.length() == 1) hour = "0" + hour;
    QString min = QString::number(M);
    if (min.length() == 1) min = "0" + min;
    QString sec = QString::number(S);
    if (sec.length() == 1) sec = "0" + sec;
    QString qTime = hour + ":" + min + ":" + sec;
    return qTime;
}

void TestSampleWidget::TimeShow(QString step_name, QString total_time, QString step_time, QString solution_time, QString plain_time)
{

    if (step_name == GlobalData::LoadLanguageInfo(g_language_type, "K1599"))//"润湿")
    {
        m_current_step_id = 1;
        mWetting_time = selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1599")];
        mWetting_time--;
        if (mWetting_time < 0)
        {
            mWetting_time = 0;
        }

        selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1599")] = mWetting_time;
        //mWetting_time += m_need_add_pause_time;
        m_need_add_pause_time = 0;
        mWetting_time_new++;
        QMap<QString, int>::iterator iter = selectProcessMap_time.begin();
        while (iter != selectProcessMap_time.end())
        {
            if (iter.key() != GlobalData::LoadLanguageInfo(g_language_type, "K1599"))//"润湿")
            {
                QMap<QString, int>::iterator mi;
                mi = selectProcessMap_time.find(GlobalData::LoadLanguageInfo(g_language_type, "K1599"));//"润湿");
                if (mi != selectProcessMap_time.end())
                {
                    mi.value() = mWetting_time_new;
                }
            }
            iter++;
        }
    }

    if (step_name == GlobalData::LoadLanguageInfo(g_language_type, "K1600"))//"加样本")
    {
        m_current_step_id = 2;
        mAddSample_time = selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1600")];
        mAddSample_time--;
        if (mAddSample_time < 0)
        {
            mAddSample_time = 0;
        }
        selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1600")] = mAddSample_time;

        m_need_add_pause_time = 0;
        mAddSample_time_new++;
        if (mAddSample_time_new==1)
        {
            int tmp = mWetting_time_new - mWetting_time_old;
            mToatal_time = mToatal_time + mFloat_time + tmp;
            QDateTime time;
            time = QDateTime::fromString(mStartTime, "yyyy-MM-dd hh:mm:ss");
            QDateTime ss = time.addSecs(+(mToatal_time));
            QString currentTime = ss.toString("hh:mm:ss");
            //ui->lblSolutionEnd->setText(traslationSecondToString(mToatal_time));
            ui->lblPlainEnd->setText(currentTime);
        }
        QMap<QString, int>::iterator iter = selectProcessMap_time.begin();
        while (iter != selectProcessMap_time.end())
        {
            if (iter.key() != GlobalData::LoadLanguageInfo(g_language_type, "K1600"))//"加样本")
            {
                QMap<QString, int>::iterator mi;
                mi = selectProcessMap_time.find(GlobalData::LoadLanguageInfo(g_language_type, "K1600"));//"加样本");
                if (mi != selectProcessMap_time.end())
                {
                    mi.value() = mAddSample_time_new;
                }
            }
            iter++;
        }
    }

    if (step_name == GlobalData::LoadLanguageInfo(g_language_type, "K1616"))//"第一次清洗")
    {
        m_current_step_id = 3;
        mWash_time = selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1601")];

        mWash_time--;
        if (mWash_time < 0)
        {
            mWash_time = 0;
        }
        selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1601")] = mWash_time;
        //mWash_time += m_need_add_pause_time;
        m_need_add_pause_time = 0;
        mWash_time_new++;
        if (mWash_time_new == 1)
        {
            int tmp = mAddSample_time_new - mAddSample_time_old;
            mToatal_time = mToatal_time + mFloat_time + tmp;
            QDateTime time;
            time = QDateTime::fromString(mStartTime, "yyyy-MM-dd hh:mm:ss");
            QDateTime ss = time.addSecs(+(mToatal_time));
            QString currentTime = ss.toString("hh:mm:ss");
            //ui->lblSolutionEnd->setText(traslationSecondToString(mToatal_time));
            ui->lblPlainEnd->setText(currentTime);
        }
        QMap<QString, int>::iterator iter = selectProcessMap_time.begin();
        while (iter != selectProcessMap_time.end())
        {
            if (iter.key() != GlobalData::LoadLanguageInfo(g_language_type, "K1601"))//"清洗")
            {
                QMap<QString, int>::iterator mi;
                mi = selectProcessMap_time.find(GlobalData::LoadLanguageInfo(g_language_type, "K1601"));//"清洗");
                if (mi != selectProcessMap_time.end())
                {
                    mi.value() = mWash_time_new;
                }
            }
            iter++;
        }
    }

    if (step_name == GlobalData::LoadLanguageInfo(g_language_type, "K1602"))//"加酶")
    {
        m_current_step_id = 4;
        mAddEnzyme_time = selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1602")];

        mAddEnzyme_time--;
        if (mAddEnzyme_time < 0)
        {
            mAddEnzyme_time = 0;
        }

        selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1602")] = mAddEnzyme_time;
        //mAddEnzyme_time += m_need_add_pause_time;
        m_need_add_pause_time = 0;
        mAddEnzyme_time_new++;
        if (mAddEnzyme_time_new == 1)
        {
            int tmp = mWash_time_new - mWash_time_old;
            mToatal_time = mToatal_time + mFloat_time + tmp;
            QDateTime time;
            time = QDateTime::fromString(mStartTime, "yyyy-MM-dd hh:mm:ss");
            QDateTime ss = time.addSecs(+(mToatal_time));
            QString currentTime = ss.toString("hh:mm:ss");
            //ui->lblSolutionEnd->setText(traslationSecondToString(mToatal_time));
            ui->lblPlainEnd->setText(currentTime);
        }
        QMap<QString, int>::iterator iter = selectProcessMap_time.begin();
        while (iter != selectProcessMap_time.end())
        {
            if (iter.key() != GlobalData::LoadLanguageInfo(g_language_type, "K1602"))//"加酶")
            {
                QMap<QString, int>::iterator mi;
                mi = selectProcessMap_time.find(GlobalData::LoadLanguageInfo(g_language_type, "K1602"));//"加酶");
                if (mi != selectProcessMap_time.end())
                {
                    mi.value() = mAddEnzyme_time_new;
                }
            }
            iter++;
        }
    }

    if (step_name == GlobalData::LoadLanguageInfo(g_language_type, "L1088"))//"第二次清洗")
    {
        m_current_step_id = 5;
        mSecondary_wash_time = selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1603")];

        mSecondary_wash_time--;
        if (mSecondary_wash_time < 0)
        {
            mSecondary_wash_time = 0;
        }

        selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1603")] = mSecondary_wash_time;
        //mSecondary_wash_time += m_need_add_pause_time;
        m_need_add_pause_time = 0;
        mSecondary_wash_time_new++;
        if (mSecondary_wash_time_new == 1)
        {
            int tmp = mAddEnzyme_time_new - mAddEnzyme_time_old;
            mToatal_time = mToatal_time + mFloat_time + tmp;
            QDateTime time;
            time = QDateTime::fromString(mStartTime, "yyyy-MM-dd hh:mm:ss");
            QDateTime ss = time.addSecs(+(mToatal_time));
            QString currentTime = ss.toString("hh:mm:ss");
            //ui->lblSolutionEnd->setText(traslationSecondToString(mToatal_time));
            ui->lblPlainEnd->setText(currentTime);
        }
        QMap<QString, int>::iterator iter = selectProcessMap_time.begin();
        while (iter != selectProcessMap_time.end())
        {
            if (iter.key() != GlobalData::LoadLanguageInfo(g_language_type, "K1603"))//"二次清洗")
            {
                QMap<QString, int>::iterator mi;
                mi = selectProcessMap_time.find(GlobalData::LoadLanguageInfo(g_language_type, "K1603"));//"二次清洗");
                if (mi != selectProcessMap_time.end())
                {
                    mi.value() = mSecondary_wash_time_new;
                }
            }
            iter++;
        }
    }

    if (step_name == GlobalData::LoadLanguageInfo(g_language_type, "K1604"))//"加底物")
    {
        m_current_step_id = 6;
        mAddSubstrate_time = selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1604")];

        mAddSubstrate_time--;
        if (mAddSubstrate_time < 0)
        {
            mAddSubstrate_time = 0;
        }
        selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1604")] = mAddSubstrate_time;
        m_need_add_pause_time = 0;
        mAddSubstrate_time_new++;
        if (mAddSubstrate_time_new == 1)
        {
            int tmp = mSecondary_wash_time_new - mSecondary_wash_time_old;
            mToatal_time = mToatal_time + mFloat_time + tmp;
            QDateTime time;
            time = QDateTime::fromString(mStartTime, "yyyy-MM-dd hh:mm:ss");
            QDateTime ss = time.addSecs(+(mToatal_time));
            QString currentTime = ss.toString("hh:mm:ss");
            //ui->lblSolutionEnd->setText(traslationSecondToString(mToatal_time));
            ui->lblPlainEnd->setText(currentTime);
        }

        QMap<QString, int>::iterator iter = selectProcessMap_time.begin();
        while (iter != selectProcessMap_time.end())
        {
            if (iter.key() != GlobalData::LoadLanguageInfo(g_language_type, "K1604"))//"加底物")
            {
                QMap<QString, int>::iterator mi;
                mi = selectProcessMap_time.find(GlobalData::LoadLanguageInfo(g_language_type, "K1604"));//"加底物");
                if (mi != selectProcessMap_time.end())
                {
                    mi.value() = mAddSubstrate_time_new;
                }
            }
            iter++;
        }
    }

    if (step_name == GlobalData::LoadLanguageInfo(g_language_type, "K1605"))//"加蒸馏水")
    {
        m_current_step_id = 7;
        mAddPureWater_time = selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1605")];

        mAddPureWater_time--;
        if (mAddPureWater_time < 0)
        {
            mAddPureWater_time = 0;
        }

        selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1605")] = mAddPureWater_time;
        //mAddPureWater_time += m_need_add_pause_time;
        m_need_add_pause_time = 0;
        mAddPureWater_time_new++;
        if (mAddPureWater_time_new == 1)
        {
            int tmp = mAddSubstrate_time_new - mAddSubstrate_time_old;
            mToatal_time = mToatal_time + mFloat_time + tmp;
            QDateTime time;
            time = QDateTime::fromString(mStartTime, "yyyy-MM-dd hh:mm:ss");
            QDateTime ss = time.addSecs(+(mToatal_time));
            QString currentTime = ss.toString("hh:mm:ss");
            //ui->lblSolutionEnd->setText(traslationSecondToString(mToatal_time));
            ui->lblPlainEnd->setText(currentTime);
        }
        QMap<QString, int>::iterator iter = selectProcessMap_time.begin();
        while (iter != selectProcessMap_time.end())
        {
            if (iter.key() != GlobalData::LoadLanguageInfo(g_language_type, "K1605"))//"加蒸馏水")
            {
                QMap<QString, int>::iterator mi;
                mi = selectProcessMap_time.find(GlobalData::LoadLanguageInfo(g_language_type, "K1605"));//"加蒸馏水");
                if (mi != selectProcessMap_time.end())
                {
                    mi.value() = mAddPureWater_time_new;
                }
            }
            iter++;
        }
    }

    if (step_name == GlobalData::LoadLanguageInfo(g_language_type, "K1606"))//"加终止液")
    {
        m_current_step_id = 8;
        mAddTerminationLiquid_time = selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1606")];
        mAddTerminationLiquid_time--;
        if (mAddTerminationLiquid_time < 0)
        {
            mAddTerminationLiquid_time = 0;
        }
        selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1606")] = mAddTerminationLiquid_time;
        //mAddTerminationLiquid_time += m_need_add_pause_time;
        m_need_add_pause_time = 0;
        mAddTerminationLiquid_time_new++;
        if (mAddTerminationLiquid_time_new == 1)
        {
            int tmp = mAddPureWater_time_new - mAddPureWater_time_old;
            mToatal_time = mToatal_time + mFloat_time + tmp;
            QDateTime time;
            time = QDateTime::fromString(mStartTime, "yyyy-MM-dd hh:mm:ss");
            QDateTime ss = time.addSecs(+(mToatal_time));
            QString currentTime = ss.toString("hh:mm:ss");
            //ui->lblSolutionEnd->setText(traslationSecondToString(mToatal_time));
            ui->lblPlainEnd->setText(currentTime);
        }
        QMap<QString, int>::iterator iter = selectProcessMap_time.begin();
        while (iter != selectProcessMap_time.end())
        {
            if (iter.key() != GlobalData::LoadLanguageInfo(g_language_type, "K1606"))//"加终止液")
            {
                QMap<QString, int>::iterator mi;
                mi = selectProcessMap_time.find(GlobalData::LoadLanguageInfo(g_language_type, "K1606"));//"加终止液");
                if (mi != selectProcessMap_time.end())
                {
                    mi.value() = mAddTerminationLiquid_time_new;
                }
            }
            iter++;
        }
    }

    if (step_name == GlobalData::LoadLanguageInfo(g_language_type, "K1607"))//"干燥")
    {
        m_current_step_id = 9;
        mDry_time = selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1607")];
        mDry_time--;
        if (mDry_time < 0)
        {
            mDry_time = 0;
        }
        selectProcessMap_time_old[GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1607")] = mDry_time;
        //mDry_time += m_need_add_pause_time;
        m_need_add_pause_time = 0;
        mDry_time_new++;
        if (mDry_time_new == 1)
        {
            int tmp = mAddTerminationLiquid_time_new - mAddTerminationLiquid_time_old;
            mToatal_time = mToatal_time + mFloat_time + tmp;
            QDateTime time;
            time = QDateTime::fromString(mStartTime, "yyyy-MM-dd hh:mm:ss");
            QDateTime ss = time.addSecs(+(mToatal_time));
            QString currentTime = ss.toString("hh:mm:ss");
            //ui->lblSolutionEnd->setText(traslationSecondToString(mToatal_time));
            ui->lblPlainEnd->setText(currentTime);
        }

        QMap<QString, int>::iterator iter = selectProcessMap_time.begin();
        while (iter != selectProcessMap_time.end())
        {
            if (iter.key() != GlobalData::LoadLanguageInfo(g_language_type, "K1607"))//"干燥")
            {
                QMap<QString, int>::iterator mi;
                mi = selectProcessMap_time.find(GlobalData::LoadLanguageInfo(g_language_type, "K1607"));//"干燥");
                if (mi != selectProcessMap_time.end())
                {
                    mi.value() = mDry_time_new;
                }
            }
            iter++;
        }
    }

}


void TestSampleWidget::UpdateprogressBarStatus(QString tip,bool visible)
{
    ui->lblProgress->setText(tip);
}

void TestSampleWidget::setIsNewTest(bool isNewTest)
{
    _isNewTest = isNewTest;
}

void TestSampleWidget::setBtnGroup(QButtonGroup *btnGroup)
{
    _btnGroup = btnGroup;
}

void TestSampleWidget::setSelectPDialog(SelectProcessDialog *selectPDialog)
{
    m_selectPDialog = selectPDialog;
    connect(m_selectPDialog, &SelectProcessDialog::sglProcessChanged, _pReagentDialog, [this]() {
        _pReagentDialog->setSelectProcessDialog(m_selectPDialog);//用来改变_pReagentDialog中泵的状态
    });
}

void TestSampleWidget::setSampleTestTpVect(QVector<std::tuple<ptrSample, QVector<ptrTest>>>sampleTestTpVect)
{
    _sampleTestTpVect.swap(sampleTestTpVect);
}

void TestSampleWidget::SaveTestResult(QVector<std::tuple<ptrSample, QVector<ptrTest>>> sampleTestTpVect)
{
    if (sampleTestTpVect.isEmpty())
        return ;

    Analysis m_analysis;
    int i = 0;
    QList<QString> pic_file_path_list;
    for (auto tp : sampleTestTpVect)
    {
        auto testVect = std::get<1>(tp);
        bool run_status = true;
        for (auto it : testVect)
        {
            //todo
            uchar pos = it->getSlotPos();
            int paper_id = it->getPaperId();
            QString sample_id = it->getSampleId();
            QString id = it->getId();
            QString pic_file_name = it->getTestId();
            run_status =true;// Instrument::instance()->moveToPhotoPos(pos);
            Sleep(1000);
            //m_cameraControl.CreateOneImage(sample_id, paper_id, pic_file_name);
            pic_file_path_list.push_back(pic_file_name);
            m_analysis.AnalysisMothed(pic_file_name,paper_id, sample_id,"","");
        }
        i++;
    }
    MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1431"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
}

//设置暂停
void TestSampleWidget::on_btnPause_clicked()
{
    InstrumentStateModel::paraStrc state = _instrState->getMachineState();
    if(state.state!=InstrumentStateModel::enumRuning){
        return;
    }
    /*int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1260"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1432"), MyMessageBox::Ok | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if (ret != MyMessageBox::Ok)
    {
        return;
    }
    Global::g_pause_flage = 1;
    mPause_flage = true;*/
    int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1260"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1432"), MyMessageBox::Ok | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if (ret == MyMessageBox::Ok)
    {
        _instrument->testPause();
    }

}

void TestSampleWidget::deleteFilesInDirectory() {

    QString currentPath = QDir::currentPath();
    QString dataFolderPath = currentPath + QDir::separator() + "Data";
    QDir dataDir(dataFolderPath);
    if (dataDir.exists()) {
        dataDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
        QFileInfoList fileList = dataDir.entryInfoList();
        for (const QFileInfo &fileInfo : fileList) {
            QFile::remove(fileInfo.absoluteFilePath());
        }
    }
}

//开始检测流程
void TestSampleWidget::on_btnSet_clicked()
{
    if(m_listTest.size()==0){
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1380"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        //eLog("样本数据保存失败");
        return;
    }

    auto state = _instrState->getMachineState();
    //判断是否停止状态 如果是停止则发送继续的指令
    if(state.state==InstrumentStateModel::enumPause){
        int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1260"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K14321"), MyMessageBox::Ok | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
        if (ret == MyMessageBox::Ok)
        {
            _instrument->testContinue();
        }
        return;
    }
    if(state.state==InstrumentStateModel::enumRuning){
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1581"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }

    //删除目录下的文件
    deleteFilesInDirectory();

    //Global::g_stop_flage = 0;
    //SaveRunInfo("dddd3455666666");
    //查询上盖是否打开
    //return;
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    QString company_id_sz = dao->SelectSaveSetById(&bResult, 5);

    if (mOpenCoverAlarmTip != 2)
    {
        //_instrument->inquireSensorState();
    }


    /*if (!state.canRun)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1433"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }

    if (state.state == InstrumentStateModel::enumRuning)
    {
        //_instrument->setIsPause(true);
        //暂停开始计算
        mPause_flage = true;
    }*/
    //阶段选择
    if (Global::g_pause_flage != 1)
    {
        m_selectPDialog->exec();
        if (m_selectPDialog->getIsCloseBtn())
        {
            mPause_flage = false;
            //_instrument->setIsPause(false);
            return;
        }
    }

    mPause_flage = false;
    Global::g_pause_flage = 0;
    //把所有的样本信息插入到数据库
    //auto selectMap = m_selectPDialog->getSeletedPGMap();
    selectProcessMap = m_selectPDialog->getSeletedPGMap();
    QMap<int, QString>::iterator iter = selectProcessMap.begin();
    Global::g_run_or_maintenance_flage = 0;
    /*if (selectProcessMap.count() == 1 && iter.value()== GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1608"))//"拍照")//K1608
    {
        //如果当前未运行结束，那么返回
        if (state.state == InstrumentStateModel::enumRuning)
        {
            return;
        }

        bool b = SampleBLL().insertModel(_sampleTestTpVect);
        if (!b)
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1434"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            //eLog("样本数据保存失败");
            return;
        }

        _currentGroupId = 0;
        _isNewTest = false;
        m_errorAddSampleMap.clear();
        m_errorAddSampleMap1.clear();

        //_instrument->motorInitialize(0x05, 60000);

        Sleep(100);
        QString strExePath = QDir::currentPath();
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString("yyyyMMdd");//("yyyy-MM-dd hh:mm:ss");
        QString str1 = QString("[%1]    %2\n").arg(time.toString("yyyy-MM-dd hh:mm:ss.zzz")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1635"));//"摇床初始化");
        QString filePath = QString("%1/log/%2/%3").arg(strExePath).arg(str).arg("摇床初始记录1.log");
        //filePath = QString("%1/log/%2/%3").arg("D:/linshi/Y72/project2022042901/project/camera_project_Qt_Release/camera_project_Qt/Bin").arg(str).arg(fileName);
        QFile file(filePath);
        file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
        file.write(str1.toUtf8());
        file.close();
        //_instrument->lightControl(12, 1);
        Sleep(6000);
        //qDebug("测试完成，正在测读"); //
        //emit preper_save(this);//发送信号将指针传递给槽函数

        auto dao = AnalysisUIDao::instance();
        bool bResult;
        int is_camera_open = dao->SelectSaveSetById(&bResult, 20008).toInt();
        //如果不需要判读，改为
        if (is_camera_open)
        {
            //m_run_paper_pos_thread->start();//开始线程
            ui->lblProgress->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1583"));//"正在进行判读，请勿打开设备上盖。");
        }
        else
        {
            UpdateSlot(1);
        }


        return;
        //ui->btnSet->setEnabled(false);//setVisible(false);
        //ui->progressBar->setVisible(false);
        ////写入结果表
        //_timer->stop();
        //直接调用拍照并且goto Next;
        //goto Next;
    }*/

    //这里用时较久
    bool b = SampleBLL().insertModel(_sampleTestTpVect);
    if (!b)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1434"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        //eLog("样本数据保存失败");
        return;
    }
    _currentGroupId = 0;
    _isNewTest = false;
    //_instrument->testStart(m_listTest, selectMap);//启动测试


    QList<QString> testIds;
    for(auto i:m_listTest){
        testIds.append(i->getTestId());
    }
    _instrState->setMachineState(InstrumentStateModel::enumRuning);
    _instrument->testStart(testIds, selectProcessMap.keys().toVector().toList(),company_id_sz.toInt());//启动测试
    //qDeleteAll(m_errorAddSampleMap);
    m_errorAddSampleMap.clear();
    m_errorAddSampleMap1.clear();

}

void TestSampleWidget::slotPumpFlush()
{
    /*auto state = _instrState->getMachineState();
    if (!state.canRun)
    {
        QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("当前状态不允许启动测试"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
        return;
    }
    if (state.state == InstrumentStateModel::enumRuning)
        _instrument->setIsPause(true);*/
    //_instrument->setIsPause(true);
    if (_timer != nullptr)
    {
        _timer->stop();
    }
    _pReagentDialog->exec();
    //_instrument->setIsPause(false);

    if (_timer != nullptr)
    {
        _timer->start();
    }

}

void TestSampleWidget::slotLblClick(int pos)
{
    MyMessageBox::information(this, tr("hint"), QString::number(pos), MyMessageBox::Ok, tr("ok"),"");
}

void TestSampleWidget::on_btnSubBody_clicked()
{
    mOpenCoverAlarmTip = 2;
    //_instrument->setIsPause(false);
    Global::g_OpenCoverStatus = 5;//在运行界面
}

void TestSampleWidget::slotCurrentGroupIdChanged(int groupId,int realTime)
{
    //   if(realTime>0 && _currentGroupId>0)
    //   {
    //       _stepRunTimeMap.insert(_currentGroupId,realTime);//时间修正
    //   }
    //_currentGroupId = groupId;
    //QMap<int, int> stepRunTimeMap;
    //stepRunTimeMap = _instrument->getStepRunTime();
    //_stepRunTimeMap.swap(stepRunTimeMap);
    //auto it = _stepRunTimeMap.find(_currentGroupId);
    //if (it == _stepRunTimeMap.end())
    //{
    //	_instrState->setMachineState(InstrumentStateModel::enumError);
    //	eLog("没有找到相应的时序,id:{}", _currentGroupId);
    //	return;
    //}
    updateProgress(0);//不能确定时间，暂时为0
}

void TestSampleWidget::on_btnStop_clicked()
{
    auto state = _instrState->getMachineState();
    if (state.state!=InstrumentStateModel::enumRuning&&state.state!=InstrumentStateModel::enumPause)
    {
        // QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("当前状态不允许启动测试"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
        return;
    }

    int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1260"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1337"), MyMessageBox::Yes | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if (ret == MyMessageBox::Yes)
    {
        _instrument->testStop();
        ui->progressBar->setVisible(false);
        m_progressDialog->setHead( GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1713"));
        m_progressDialog->exec();
    }
    else
    {
        return;
    }
}
