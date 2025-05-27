#include "SampleWidget.h"
#include "ui_SampleWidget.h"
#include <QMessageBox>
#include "AddSampleWidget.h"
#include "TestDataListWidget.h"
#include "IrrigationSystemLiquidWidget.h"
#include "TestSampleWidget.h"
#include "EmptyWasteBottleWidget.h"
#include "PrepareReagentWidget.h"
#include "subDialog/SelectProcessDialog.h"
#include "subDialog/PrepareReagentDialog.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/reagent/ProcessReagentModel.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include <QSqlQuery>
#include <QDesktopWidget>
#include "src/Camera/CameraControl.h"
#include <string>
#include <QDateTime>

#include <QDir>
#include <QTextStream>
#include <QFile>
#include "src/main/subDialog/MyMessageBox.h"

SampleWidget::SampleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SampleWidget)
  ,m_addSampleWidget(new AddSampleWidget(this))
  ,m_testDataListWidget(new TestDataListWidget(this))
  ,m_irrigateSLiquidWidget(new IrrigationSystemLiquidWidget(this))
  //,m_emptyWasteBottle(new EmptyWasteBottleWidget(this))
  ,m_prepareReagent(new PrepareReagentWidget(this))  
  ,m_selectPDialog(new SelectProcessDialog(this))
  ,m_prepareRDialog(new PrepareReagentDialog(m_prepareReagent,this))
  ,m_testSampleWidget(new TestSampleWidget(m_prepareRDialog,this))
  ,m_tcpClient(nullptr)
{
    ui->setupUi(this);
	QDesktopWidget *desktop = QApplication::desktop();
	QRect screen = desktop->screenGeometry();
	int screenWidth = screen.width();
	int screenHeight = screen.height();


	auto dao = AnalysisUIDao::instance();
    bool bResult;
	GlobalData::setLanguageType(dao->SelectTargetValueDes(&bResult, "20005"));
	ui->sampleTopWidget->setMinimumSize(QSize(screenWidth - 0, screenHeight - 0));
    m_testSampleWidget->setSelectPDialog(m_selectPDialog);
    m_testSampleWidget->setBtnGroup(m_prepareReagent->getBtnGroup());
    m_testSampleWidget->createPumpLbl();
    m_prepareReagent->setSelectPDialog(m_selectPDialog);
    initUi();
	dao = AnalysisUIDao::instance();
	QString sql_query = QString("select * from tsample where stateFlag=1 and stateFlag is not null ");
	auto countNumberQuery = dao->SelectRecord(&bResult, sql_query);
	int number = 0;

	while (countNumberQuery.next())
	{
		number++;
	}

	if (number > 0)
	{
		on_changebtnNextEnable(true);
	}
	else
	{
		on_changebtnNextEnable(false);
	}

    connect(m_prepareReagent, SIGNAL(ChangeBtnNextSignal(bool)), this, SLOT(on_changebtnNextEnable(bool)));
    connect(m_irrigateSLiquidWidget, SIGNAL(ChangeBtnNextSignal(bool)), this, SLOT(on_changebtnNextEnable(bool)));
    connect(m_addSampleWidget, SIGNAL(ChangeBtnNextSignal(bool)), this, SLOT(on_changebtnNextEnable(bool)));
    connect(m_addSampleWidget, SIGNAL(ChangeBtnSaveSignal(bool)), this, SLOT(on_changebtnSaveEnable(bool)));
	connect(this, &SampleWidget::sglAlarmInfo, m_testSampleWidget, &TestSampleWidget::slotAlarmInfo1);
    connect(m_testSampleWidget, &TestSampleWidget::testStop, this, &SampleWidget::ReturnSampleEdit);
	ui->btnIncubation->setVisible(false);
	ui->btnBatchAdd->setVisible(false);
	ui->btnDeleteAll->setVisible(false);
	ui->btnReQuestLisAll->setVisible(false);
	this->setWindowFlags(Qt::FramelessWindowHint);

	QString sz = GlobalData::LoadLanguageInfo("K1038");
	ui->btnSaveAdd->setText(sz);
	sz = GlobalData::LoadLanguageInfo("K1039");
	ui->btnDelete->setText(sz);
	sz = GlobalData::LoadLanguageInfo("K1040");
	ui->btnRequestLis->setText(sz);
	sz = GlobalData::LoadLanguageInfo("K1041");
	ui->btnReTest->setText(sz);
	sz = GlobalData::LoadLanguageInfo("K1046");
	ui->btnNext->setText(sz);
}

void SampleWidget::slotAlarmInfo1(QString alarm_info,QString code_type)
{
	emit sglAlarmInfo(alarm_info,code_type);
}

void SampleWidget::ShowFunctionBtn(bool status)
{
	QString lbl_title = "";
	lbl_title = ui->lblTitle->text();

	QString sz = GlobalData::LoadLanguageInfo("K1037");
	if (lbl_title == sz)//"工作列表")
	{
		ui->btnDelete->setVisible(status);
		ui->btnSaveAdd->setVisible(status);
		ui->btnReQuestLisAll->setVisible(false);
		ui->btnRequestLis->setVisible(status);
		ui->btnDelete->setVisible(status);
	}
}

void SampleWidget::slotReFreshListUi()
{
	m_addSampleWidget->ShowTestInfoFromDatabase();
}

void SampleWidget::on_btnDelete_clicked()
{
	m_addSampleWidget->DeleteSample();
}

void SampleWidget::on_btnDeleteAll_clicked()
{
	m_addSampleWidget->DeleteAllSample();
}

void SampleWidget::on_btnBatchAdd_clicked()
{
	m_addSampleWidget->FromTestDataByBatchAdd("");
}

void SampleWidget::on_btnSaveAdd_clicked()
{
	m_addSampleWidget->SaveSampleListToDataBase();
}

void SampleWidget:: on_btnReQuestLisAll_clicked()
{
	m_addSampleWidget->FromLisByCondition("ddddddddddddddddddddddddd");
}

void SampleWidget:: on_btnRequestLis_clicked()
{
	m_addSampleWidget->FromLis();
}

void SampleWidget::on_btnIncubation_clicked()
{
	m_addSampleWidget->Incubation(3,300);
}

SampleWidget::~SampleWidget()
{
    delete ui;
}

void SampleWidget::initUi()
{
	QString sz = GlobalData::LoadLanguageInfo("K1037");
    ui->lblTitle->setText(sz);
    ui->btnPre->setVisible(false);
    ui->btnCancel->setVisible(false);
    ui->sampleStackPage->setCurrentIndex(STACK_ADD_SAMPLE);
    ui->sampleStackPage->insertWidget(STACK_ADD_SAMPLE,m_addSampleWidget);
    ui->sampleStackPage->insertWidget(STACK_TESTDATALIST,m_testDataListWidget);
    ui->sampleStackPage->insertWidget(STACK_PREPAREREAGENT,m_prepareReagent);
    ui->sampleStackPage->insertWidget(STACK_TESTSAMPLE,m_testSampleWidget);
}

void SampleWidget::stackIndexChange()
{
	ui->btnPre->setText(GlobalData::LoadLanguageInfo("K1047"));
    ui->btnPre->setVisible(true);
    ui->btnNext->setVisible(true);
    ui->btnCancel->setVisible(false);
    ui->btnReTest->setVisible(false);
    auto index=ui->sampleStackPage->currentIndex();
    if(index==STACK_ADD_SAMPLE)
    {
        ui->btnPre->setVisible(false);
        ui->btnCancel->setVisible(false);
        ui->btnReTest->setVisible(true);
		QString sz = GlobalData::LoadLanguageInfo("K1037");
		ui->lblTitle->setText(sz);//tr("工作列表"));
    }
    else if(index==STACK_TESTDATALIST)
    {        
        ui->lblTitle->setText(GlobalData::LoadLanguageInfo("K1070"));//tr("实验列表"));
    }
    else if(index==STACK_TESTSAMPLE)
    {
        ui->lblTitle->setText(GlobalData::LoadLanguageInfo("K1072"));//tr("测试运行"));
		ui->btnCancel->setVisible(false);
		//ui->btnCancel->setVisible(false);
		ui->btnPre->setVisible(false);
    }
    else if(index==STACK_PREPAREREAGENT)
    {
        ui->lblTitle->setText(GlobalData::LoadLanguageInfo("K1071")); //tr("试剂准备"));
    }
    if(index==STACK_END-1)
        ui->btnNext->setVisible(false);
}

void SampleWidget::setTcpClient(TcpClient *tcpClient)
{
    m_tcpClient = tcpClient;
    m_addSampleWidget->setTcpClient(tcpClient);
    m_testSampleWidget->setTcpClient(tcpClient);
}

void SampleWidget::on_btnPre_clicked()
{

    auto index=ui->sampleStackPage->currentIndex();
    auto preIndex=(index-1)<0?0:(index-1);
    ui->sampleStackPage->setCurrentIndex(preIndex);
    stackIndexChange();
	on_changebtnNextEnable(true);
	ShowFunctionBtn(true);
}

void SampleWidget::on_changebtnNextEnable(bool flage)
{
	ui->btnNext->setEnabled(flage);
}

void SampleWidget::on_changebtnSaveEnable(bool flage)
{
	ui->btnSaveAdd->setEnabled(flage);
}

void SampleWidget::on_btnNext_clicked()
{
    auto count=ui->sampleStackPage->count();
    auto index=ui->sampleStackPage->currentIndex();
    if(index==STACK_ADD_SAMPLE)
    {
        if(!m_addSampleWidget->nextAction())//添加样本 点击
            return;
        m_testDataListWidget->setPapersState(m_addSampleWidget->getListTestData());
        m_testSampleWidget->setIsNewTest(true);
		ShowFunctionBtn(false);
    }
    else if(index==STACK_TESTDATALIST)//跳转到  检测前液体灌注页面
    {
        m_testSampleWidget->setListTest(m_addSampleWidget->getListTestData());
        m_testSampleWidget->setSampleTestTpVect(m_addSampleWidget->getSampleTestTpVect());
        m_prepareReagent->setListTest(m_addSampleWidget->getListTestData());
        m_testSampleWidget->setPapersState();

		m_prepareReagent->m_preview_wash_map.clear();
		m_prepareReagent->m_finish_map.clear();
		m_prepareReagent->m_system_liquid_finish = false;
		m_prepareReagent->m_paper_connect_reagent_flage = false;
    }
    else if(index == STACK_PREPAREREAGENT)
    {
        Instrument::instance()->setProcessReagentVect(m_prepareReagent->getProcessReagentVect());
        m_testSampleWidget->setPumpLblState();


		m_testSampleWidget->mWetting_time = 0;
		m_testSampleWidget->mAddSample_time = 0;
		m_testSampleWidget->mWash_time = 0;
		m_testSampleWidget->mAddEnzyme_time = 0;
		m_testSampleWidget->mSecondary_wash_time = 0;
		m_testSampleWidget->mAddSubstrate_time = 0;
		m_testSampleWidget->mAddPureWater_time = 0;
		m_testSampleWidget->mAddTerminationLiquid_time = 0;
		m_testSampleWidget->mDry_time = 0;

		m_testSampleWidget->mWetting_time_old = 0;
		m_testSampleWidget->mAddSample_time_old = 0;
		m_testSampleWidget->mWash_time_old = 0;
		m_testSampleWidget->mAddEnzyme_time_old = 0;
		m_testSampleWidget->mSecondary_wash_time_old = 0;
		m_testSampleWidget->mAddSubstrate_time_old = 0;
		m_testSampleWidget->mAddPureWater_time_old = 0;
		m_testSampleWidget->mAddTerminationLiquid_time_old = 0;
		m_testSampleWidget->mDry_time_old = 0;
		m_testSampleWidget->mPause_total_time = 0;
		m_testSampleWidget->m_current_step_id = 0;
		m_testSampleWidget->m_need_add_pause_time = 0;
		m_testSampleWidget->mPause_total_time = 0;
		m_testSampleWidget->mToatal_time = 0;
		m_testSampleWidget->mToatal_solution_time = 0;
		m_testSampleWidget->m_preview_wash_flage = 0;
		m_testSampleWidget->m_Enzyme_number = 1;
		m_testSampleWidget->m_i_n = 1;
		if (m_prepareReagent->m_preview_wash_map.size() > 0)
		{
			m_testSampleWidget->m_preview_wash_flage = 1;
            //Instrument::instance()->setNeedFillPump(m_prepareReagent->m_preview_wash_map);
			QString strExePath = QDir::currentPath();
			QDateTime time = QDateTime::currentDateTime();
			QString str = time.toString("yyyyMMdd");//("yyyy-MM-dd hh:mm:ss");
			QString str222 = time.toString("yyyy-MM-dd hh:mm:ss");
			QString filePath = QString("%1/log/%2/%3").arg(strExePath).arg(str).arg("delay_time_log.txt");

			QMap<int, ushort>::const_iterator it;
			for (it = m_prepareReagent->m_preview_wash_map.constBegin(); it != m_prepareReagent->m_preview_wash_map.constEnd(); ++it) {
				QString str1 = QString("%1:%2\r\n").arg(str222).arg(it.key());
				QFile file(QApplication::applicationDirPath() + "/delay_time_log.txt");
				if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
					QTextStream out(&file);
					out << str1;
					file.close();
				}
			}
		}
		else
		{
			//m_preview_wash_flage = 0; 无延时充灌
			m_testSampleWidget->m_preview_wash_flage = 0;
		}

		m_testSampleWidget->m_Enzyme_number = m_prepareReagent->m_Enzyme_number;
		m_prepareReagent->m_Enzyme_number = 1;
    }
    else if(index==STACK_TESTSAMPLE)
    {

    }
    auto nextIndex=((index+1)<=count-1)?(index+1):count-1;
    ui->sampleStackPage->setCurrentIndex(nextIndex);
	m_testSampleWidget->ClearTextBrowser();
	m_testSampleWidget->mPause_total_time = 0;
    stackIndexChange();
}

void SampleWidget::ReturnSampleEdit()
{
	auto index = ui->sampleStackPage->currentIndex();
	if (index == STACK_ADD_SAMPLE)
	{
		m_testSampleWidget->ClearTextBrowser();
		m_testSampleWidget->mPause_total_time = 0;
		m_addSampleWidget->cancelAction();
		//ShowFunctionBtn(true);
	}
	else if (index == STACK_TESTSAMPLE)
	{
		m_testSampleWidget->ClearTextBrowser();
		m_testSampleWidget->mPause_total_time = 0;
		auto state = InstrumentStateModel::instance()->getMachineState().state;
		if (state == InstrumentStateModel::enumRuning)
		{
			//auto ret = QMessageBox::information(this, tr("询问"), tr("是否要取消本次测试？？"), tr("是"), tr("否"));
			auto ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1260"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1423"), MyMessageBox::Ok | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
			if (ret != MyMessageBox::Ok)
				return;
            //Instrument::instance()->machineStop();
		}
		int stack_number = ui->sampleStackPage->count();
		m_addSampleWidget->cancelAction();
		ui->sampleStackPage->setCurrentIndex(STACK_ADD_SAMPLE);
	}
	stackIndexChange();
	on_changebtnNextEnable(false);
	ShowFunctionBtn(true);
	m_testSampleWidget->ClearTextBrowser();
	m_testSampleWidget->mPause_total_time = 0;
	m_addSampleWidget->ShowTestInfoFromDatabase();
}

void SampleWidget::on_btnCancel_clicked()
{
    auto index=ui->sampleStackPage->currentIndex();
    if(index==STACK_ADD_SAMPLE)
    {
        m_addSampleWidget->cancelAction();
    }
	else if (index == STACK_TESTSAMPLE)
	{
        auto state=InstrumentStateModel::instance()->getMachineState().state;
        if(state==InstrumentStateModel::enumRuning)
        {
            auto ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1260"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1423"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
            if(ret != MyMessageBox::Ok)
                return;
            //Instrument::instance()->machineStop();
        }
		int stack_number = ui->sampleStackPage->count();
		m_addSampleWidget->cancelAction();
		ui->sampleStackPage->setCurrentIndex(STACK_ADD_SAMPLE);
	}
	stackIndexChange();
	on_changebtnNextEnable(false);
	ShowFunctionBtn(true);
	m_testSampleWidget->ClearTextBrowser();
	m_testSampleWidget->mPause_total_time = 0;
	m_addSampleWidget->ShowTestInfoFromDatabase();
}


void SampleWidget::on_btnReTest_clicked()
{
    m_addSampleWidget->createRepeatTest();
}

void SampleWidget::setProgressDialog(ProgressDialog *progressDialog)
{
    m_irrigateSLiquidWidget->setProgressDialog(progressDialog);
    m_prepareReagent->setProgressDialog(progressDialog);
    m_addSampleWidget->setProgressDialog(progressDialog);
    m_testSampleWidget->setProgressDialog(progressDialog);
}
