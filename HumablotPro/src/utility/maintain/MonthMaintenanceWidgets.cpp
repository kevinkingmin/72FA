#include "..\include\precomp\precompile.h"
#include "MonthMaintenanceWidgets.h"
#include <QMessageBox>
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "src/comm/CustomButton.h"
#include <QMessageBox> 
#include <string>
#include <QDateTime>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/ProgressDialog.h"
#include <QTimer>
#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "../Include/Utilities/log.h"

#define PUMPCOUNT 9

MonthMaintenanceWidgets::MonthMaintenanceWidgets(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::MonthMaintenanceWidgetsClass)
	, _InstrumentState(InstrumentStateModel::instance())
	, _instr(Instrument::instance())
	, _emptyFile("rFlowBack128.png")
	, _flushFile("irrigationIcon.png")
	, _btnGroup(new QButtonGroup(this))
	, _readyFile("rReady.png")
	, _delayFile("rDelay.png")
	, _pixPath(":/images/buttonIcon/")
{
	//ui.setupUi(this);
	ui->setupUi(this);
	_btnGroup->setExclusive(false);

	ui->groupBox_2->setVisible(false);
	ui->groupBox_3->setVisible(false);
	ui->groupBox_4->setVisible(false);
	ui->groupBox_5->setVisible(false);

	createPumpBtn(ui->pushButton_2, false);
	createPumpBtn(ui->pushButton_3, false);
	createPumpBtn(ui->pushButton_4, false);
	createPumpBtn(ui->pushButton_5, false);
	createPumpBtn(ui->pushButton_6, false);
	createPumpBtn(ui->pushButton_7, false);
	createPumpBtn(ui->pushButton_8, false);
	createPumpBtn(ui->pushButton_9, false);
	createPumpBtn(ui->pushButton_10, false);

	ui->cb_all->setVisible(false);

	ui->progressBar->setStyleSheet("QProgressBar {border: 1px solid grey; border-radius: 2px; background-color: #FFFFFF; text-align:center; font-size:15px}");
	connect(_instr, &Instrument::sglMonthMaintain, this, &MonthMaintenanceWidgets::slotMonthMaintain);
	connect(_instr, &Instrument::sglPumpCalibrateResult, this, &MonthMaintenanceWidgets::slotPumpCalibrateResult_Month);


	myTimer = new QTimer(this);

	//auto pm1 = SystemSetBLL().getRowById(9992);
	////int delay_time = (pm1.isNull() ? 200 : pm1->getSaveSet())/1000;
	//int delay_time = (pm1.isNull() ? 200 : pm1->getSaveSet()) ;
	//static int i = 15 * 60;
	//i = delay_time;
	//m_i = delay_time;

	auto dao = AnalysisUIDao::instance();
	bool bResult;
	QString save_set = dao->SelectSaveSetById(&bResult, 24);
	m_i = save_set.toInt()/1000;
	m_i_max = save_set.toInt()/1000;

	
	connect(myTimer, &QTimer::timeout, [=]() {
		//管路浸泡中......
		//QString tip = QString("管路浸泡中,剩余秒数：[%0]").arg(m_i);
		QString tip = QString("%1[%0]").arg(m_i).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1628"));
		m_progressDialog->setMaxValue(m_i_max);
		m_progressDialog->setHead(tip);
		_InstrumentState->setMachineState(InstrumentStateModel::enumMaintain);
		//m_progressDialog->exec();

		if (m_i == 10)
		{
            //_instr->setBuzzleOnOff(0x03);
		}

		if (m_i < 5)
		{
			_maintainStep = 2;
		}

		
		if (m_i < 3)
		{
            //_instr->setBuzzleOnOff(0x00);
			_maintainStep = 2;
            //_instr->setBuzzleOnOff(0x00);
			//myTimer->stop();
		}
		m_i--;
		if (m_i == 0)
		{
			dLog("3");
			myTimer->stop();

		}
		//ui->lcdNumber->display(i);
	});

	QString sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1221");
	ui->chk_1->setText("1" + sz1);
	ui->chk_2->setText("2" + sz1);
	ui->chk_3->setText("3" + sz1);
	ui->chk_4->setText("4" + sz1);
	ui->chk_5->setText("5" + sz1);
	ui->chk_6->setText("6" + sz1);
	ui->chk_7->setText("7" + sz1);
	ui->chk_8->setText("8" + sz1);
	ui->chk_9->setText("9" + sz1);

	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1220");
	ui->label_3->setText( sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1081");
	ui->btn_down_step_2->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1222");
	ui->btn_down_step->setText(sz1);

}

void MonthMaintenanceWidgets::updateUI()
{
	//auto pm1 = SystemSetBLL().getRowById(9992);
	//int delay_time = (pm1.isNull() ? 200 : pm1->getSaveSet()) / 1000;
	//static int i = 15 * 60;
	//i = delay_time;
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	QString save_set = dao->SelectSaveSetById(&bResult, 24);
	m_i = save_set.toInt();
	//update();
}


MonthMaintenanceWidgets::~MonthMaintenanceWidgets()
{

}

QVector<uchar> MonthMaintenanceWidgets::getCheckBtn()
{
	QVector<uchar> outVect;
	if (ui->chk_1->isChecked())
	{
		createPumpBtn(ui->pushButton_2, true);
		outVect.push_back(0);
	}
	else
	{
		createPumpBtn(ui->pushButton_2, false);
	}

	if (ui->chk_2->isChecked())
	{
		createPumpBtn(ui->pushButton_3, true);
		outVect.push_back(1);
	}
	else
	{
		createPumpBtn(ui->pushButton_3, false);
	}

	if (ui->chk_3->isChecked())
	{
		createPumpBtn(ui->pushButton_4, true);
		outVect.push_back(2);
	}
	else
	{
		createPumpBtn(ui->pushButton_4, false);
	}

	if (ui->chk_4->isChecked())
	{
		createPumpBtn(ui->pushButton_5, true);
		outVect.push_back(3);
	}
	else
	{
		createPumpBtn(ui->pushButton_5, false);
	}

	if (ui->chk_5->isChecked())
	{
		createPumpBtn(ui->pushButton_6, true);
		outVect.push_back(4);
	}
	else
	{
		createPumpBtn(ui->pushButton_6, false);
	}

	if (ui->chk_6->isChecked())
	{
		createPumpBtn(ui->pushButton_7, true);
		outVect.push_back(5);
	}
	else
	{
		createPumpBtn(ui->pushButton_7, false);
	}

	if (ui->chk_7->isChecked())
	{
		createPumpBtn(ui->pushButton_8, true);
		outVect.push_back(6);
	}
	else
	{
		createPumpBtn(ui->pushButton_8, false);
	}

	if (ui->chk_8->isChecked())
	{
		createPumpBtn(ui->pushButton_9, true);
		outVect.push_back(7);
	}
	else
	{
		createPumpBtn(ui->pushButton_9, false);
	}

	if (ui->chk_9->isChecked())
	{
		createPumpBtn(ui->pushButton_10, true);
		outVect.push_back(8);
	}
	else
	{
		createPumpBtn(ui->pushButton_10, false);
	}
	mOutVect = outVect;
	return outVect;
}

void MonthMaintenanceWidgets::on_chk_1_toggled(bool state) 
{
	getCheckBtn();
}

void MonthMaintenanceWidgets::on_chk_2_toggled(bool state)
{
	getCheckBtn();
}

void MonthMaintenanceWidgets::on_chk_3_toggled(bool state)
{
	getCheckBtn();
}

void MonthMaintenanceWidgets::on_chk_4_toggled(bool state)
{
	getCheckBtn();
}

void MonthMaintenanceWidgets::on_chk_5_toggled(bool state)
{
	getCheckBtn();
}

void MonthMaintenanceWidgets::on_chk_6_toggled(bool state)
{
	getCheckBtn();
}

void MonthMaintenanceWidgets::on_chk_7_toggled(bool state)
{
	getCheckBtn();
}

void MonthMaintenanceWidgets::on_chk_8_toggled(bool state)
{
	getCheckBtn();
}

void MonthMaintenanceWidgets::on_chk_9_toggled(bool state)
{
	getCheckBtn();
}
void MonthMaintenanceWidgets::on_cb_all_toggled(bool state)
{
	if (state)
	{
		ui->chk_1->setChecked(true);
		ui->chk_2->setChecked(true);
		ui->chk_3->setChecked(true);
		ui->chk_4->setChecked(true);
		ui->chk_5->setChecked(true);
		ui->chk_6->setChecked(true);
		ui->chk_7->setChecked(true);
		ui->chk_8->setChecked(true);
		ui->chk_9->setChecked(true);
	}
	else
	{
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
	}
	getCheckBtn();
}

void MonthMaintenanceWidgets::on_pushButton_clicked()
{
    auto state = _InstrumentState->getMachineState();
    if (state.state==_InstrumentState->enumRuning)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1581"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }

    MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1625"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");

	int type = 2;
	QString tip = "";
	if (1 == type)
	{
		//1624
		//tip = QString("%1").arg("开始月维护\n\n请先将将泵管头放到足量的系统液中，再点击【确认】按钮，开始周维护！");
		tip = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1624"));
	}

	if (2 == type)
	{
		//tip = QString("%1").arg("开始月维护\n\n请先将将泵管头放到足量的系统液中，再点击【确认】按钮，开始月维护！");
		tip = QString("%1").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1625"));
		//QDateTime time = QDateTime::currentDateTime();
		//QString str = time.toString("yyyy-MM-dd hh:mm:ss");
		//bool bResult = true;
		//auto dao = AnalysisUIDao::instance();
		//QString sql = QString("update tsystemset set saveDes='%1' where id=9992").arg(str);
		//dao->UpdateRecord(&bResult, sql);
	}

	auto ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tip, MyMessageBox::Ok| MyMessageBox::No,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
	if (ret != MyMessageBox::Ok)
		return;

	ui->textBrowser->setText("");
	ui->textBrowser->clear();

	//auto pm1 = SystemSetBLL().getRowById(24);
	//int delay_time = (pm1.isNull() ? 200 : pm1->getSaveSet()) / 1000;
	//m_i = delay_time;

	auto dao = AnalysisUIDao::instance();
	bool bResult;
	QString save_set = dao->SelectSaveSetById(&bResult, 24);
	m_i = save_set.toInt();

	Global::g_run_or_maintenance_flage = 1;

	mMonthMaintenance_run_flage = true;
	m_finish_flage = false;

	QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
    //_instr->setPumpVect(mOutVect);
//	_instr->maintain(ePumpFill);
    QList<uint8_t> pumpList;
    for(int pumpNum:mOutVect){
        pumpList.push_back(static_cast<uint8_t>(pumpNum+1));
    }
    _instr->monthlyMaintenance(pumpList);


	_maintainStep = 1;
	m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1629"));//"月维护进行中......");
	m_progressDialog->exec();
    //ui->btn_down_step->setEnabled(false);
}

void MonthMaintenanceWidgets::slotPumpCalibrateResult_Month(int pumpNo, int fstSteps, int SndSteps)
{
	if (mMonthMaintenance_run_flage)
	{
		QString p = QString::number(pumpNo + 1);
		QString f = QString::number(fstSteps);
		QString s = QString::number(SndSteps);
		int dint = abs(fstSteps - SndSteps);
		QString d = QString::number(dint);

		auto pm = SystemSetBLL().getRowById(26);
		int stardMin = pm.isNull() ? 200 : pm->getSaveSet();
		QString stardMax = pm.isNull() ? "400" : pm->getSaveDes();

		QString strStardMin = QString::number(stardMin);
		QString result = "";
		if (dint >= stardMin && dint <= stardMax.toInt())
		{
			result = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1642");//"  校准成功");
		}
		else
		{
			result = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1643");//tr("  校准失败");

		}
		//m_finish_pump_manal_check_number++;
		//if (m_need_pump_manal_check_number == m_finish_pump_manal_check_number)
		//{
		//	ui->chk_1->setChecked(false);
		//	ui->chk_2->setChecked(false);
		//	ui->chk_3->setChecked(false);
		//	ui->chk_4->setChecked(false);
		//	ui->chk_5->setChecked(false);
		//	ui->chk_6->setChecked(false);
		//	ui->chk_7->setChecked(false);
		//	ui->chk_8->setChecked(false);
		//	ui->chk_9->setChecked(false);
		//	ui->cb_all->setChecked(false);
		//	m_start_pump_manal_check = false;
		//	QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("手动校准泵操作完成！"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
		//}
		//ui->textBrowser->append(tr("泵号:") + p + tr("  第一次下降步数:") + f + tr("  第二次下降步数:") + s + tr("  两次下降步数差:") + d + tr("  设置标准:") + strStardMin + "~"+ stardMax + result);
		ui->textBrowser->append(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1000") + p + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1515") + f + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1516") + s + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1517")  + d + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1518")  + strStardMin + "~" + stardMax + result);
	}
}



void MonthMaintenanceWidgets::slotMonthMaintain(int result)
{
	dLog("1");
	if (mMonthMaintenance_run_flage)
	{
		switch (_maintainStep)
		{
		case 1://浸泡
		{
			if (result < 0)
			{
				ui->btn_down_step->setEnabled(true);
				MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1442"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                //_instr->machineStop();
				return;
			}

			if (!m_finish_flage)
			{
//				_instr->maintain(eTubeSoak);
				//_maintainStep = 2;
				m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1627"));//"管路浸泡中......");
				//auto pm1 = SystemSetBLL().getRowById(24);
				//int delay_time = pm1.isNull() ? 200 : pm1->getSaveSet();
				auto dao = AnalysisUIDao::instance();
				bool bResult;
				QString save_set = dao->SelectSaveSetById(&bResult, 24);
				m_i_max = save_set.toInt()/1000;
				m_i = save_set.toInt()/1000;
				m_progressDialog->setMaxValue(m_i_max);
				//m_progressDialog->setMaxValue(15 * 60 * 1000);

				m_progressDialog->exec();
				//_instr->setBuzzleOnOff(0x00);
				if (myTimer->isActive() == false)
				{
					myTimer->start(1000);
				}
				m_finish_flage = true;
				_InstrumentState->setMachineState(InstrumentStateModel::enumMaintain);
			}
			break;
		}
		case 2:
		{
			dLog("2");
			if (myTimer->isActive() == true)
			{
				myTimer->stop();
			}
            //_instr->setBuzzleOnOff(0x00);
            //_instr->setBuzzleOnOff(0x00);
			if (result < 0)
			{
				MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1442"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
				ui->btn_down_step->setEnabled(true);
                //_instr->machineStop();
				return;
			}

			MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1345"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
			QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
            //_instr->setPumpVect(mOutVect);
//			_instr->maintain(ePumpFill);
			_maintainStep = 3;
			//if (_maintainType == MENU_ID_MONTH_MANTAINCE)
			//	_maintainStep = 3;
			//else if (_maintainType == MENU_ID_WEEK_MANTAINCE)
			//	_maintainStep = 4;
			        //m_progressDialog->setHead("清水充灌......");
			        //m_progressDialog->exec();
					//_InstrumentState->setMachineState(InstrumentStateModel::enumMaintain);
			break;
		}
		case 3://蠕动泵校准
		{
			if (result < 0)
			{
				MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1443"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
				ui->btn_down_step->setEnabled(true);
                //_instr->machineStop();
				return;
			}
			//QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
            //_instr->setPumpVect(mOutVect);
//			_instr->maintain(ePumpCalibrate);
			_maintainStep = 4;
			        //m_progressDialog->setHead("蠕动泵校准......");
			        //m_progressDialog->exec();
					//_InstrumentState->setMachineState(InstrumentStateModel::enumMaintain);
			break;
		}
		case 4://充灌排空
		{
			if (result < 0)
			{
				MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1444"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
				ui->btn_down_step->setEnabled(true);
                //_instr->machineStop();
				return;
			}

			MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1445"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
			QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
            //_instr->setPumpVect(mOutVect);
//			_instr->maintain(ePumpFill);
			_maintainStep = 5;
			        //m_progressDialog->setHead("最后充灌......");
			        //m_progressDialog->exec();
					//_InstrumentState->setMachineState(InstrumentStateModel::enumMaintain);
			break;
		}
		case 5:
		{
			if (result < 0)
			{
				MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1346"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");

                //_instr->machineStop();
				return;
			}
			//QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
			//_instr->setPumpVect(pumpVect);
			//_instr->maintain(ePumpFill);
			MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1446"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");

			ui->btn_down_step->setEnabled(true);

			ui->chk_1->setChecked(false);
			ui->chk_2->setChecked(false);
			ui->chk_3->setChecked(false);
			ui->chk_4->setChecked(false);
			ui->chk_5->setChecked(false);
			ui->chk_6->setChecked(false);
			ui->chk_7->setChecked(false);
			ui->chk_8->setChecked(false);
			ui->chk_9->setChecked(false);
			ui->cb_all->setChecked(false);


			createPumpBtn(ui->pushButton_2, false);
			createPumpBtn(ui->pushButton_3, false);
			createPumpBtn(ui->pushButton_4, false);
			createPumpBtn(ui->pushButton_5, false);
			createPumpBtn(ui->pushButton_6, false);
			createPumpBtn(ui->pushButton_7, false);
			createPumpBtn(ui->pushButton_8, false);
			createPumpBtn(ui->pushButton_9, false);
			createPumpBtn(ui->pushButton_10, false);
			mMonthMaintenance_run_flage = false;

            //_InstrumentState->setMachineState(InstrumentStateModel::enumStandby);

		}
		}
	}
	
}


//void MonthMaintenanceWidgets::on_btn_up_step_clicked()
//{
//	int a = 0;
//}


void MonthMaintenanceWidgets::on_btn_down_step_2_clicked()
{
	if (!all_select_flage)
	{
		ui->chk_1->setChecked(true);
		ui->chk_2->setChecked(true);
		ui->chk_3->setChecked(true);
		ui->chk_4->setChecked(true);
		ui->chk_5->setChecked(true);
		ui->chk_6->setChecked(true);
		ui->chk_7->setChecked(true);
		ui->chk_8->setChecked(true);
		ui->chk_9->setChecked(true);
		all_select_flage = true;
		ui->btn_down_step_2->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1637"));
	}
	else
	{
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->btn_down_step_2->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1081"));//setText("全选");
		all_select_flage = false;
	}
	getCheckBtn();
}

void MonthMaintenanceWidgets::on_btn_down_step_clicked()
{
	if (!_InstrumentState->enumStandby)
	{
		return;
	}

	int vect_count = mOutVect.count();
	if (vect_count == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1220"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}
	on_pushButton_clicked();

	//int a = 0;
	//step_index++;
	//if (step_index == 1)
	//{
	//	ui->groupBox_2->setVisible(true);
	//}
	//if (step_index == 2)
	//{
	//	ui->groupBox_2->setVisible(true);
	//	ui->groupBox_3->setVisible(true);
	//}
	//if (step_index == 3)
	//{
	//	ui->groupBox_2->setVisible(true);
	//	ui->groupBox_3->setVisible(true);
	//	//ui->groupBox_4->setVisible(true);
	//}
	//if (step_index == 4)
	//{
	//	ui->groupBox_2->setVisible(true);
	//	ui->groupBox_3->setVisible(true);
	//	//ui->groupBox_4->setVisible(true);
	//	ui->groupBox_5->setVisible(true);
	//}

}
void MonthMaintenanceWidgets::HideGroupBox()
{
	ui->groupBox_2->setVisible(false);
	ui->groupBox_3->setVisible(false);
	ui->groupBox_4->setVisible(false);
	ui->groupBox_5->setVisible(false);

	createPumpBtn(ui->pushButton_2, false);
	createPumpBtn(ui->pushButton_3, false);
	createPumpBtn(ui->pushButton_4, false);
	createPumpBtn(ui->pushButton_5, false);
	createPumpBtn(ui->pushButton_6, false);
	createPumpBtn(ui->pushButton_7, false);
	createPumpBtn(ui->pushButton_8, false);
	createPumpBtn(ui->pushButton_9, false);
	createPumpBtn(ui->pushButton_10, false);

	ui->chk_1->setChecked(false);
	ui->chk_2->setChecked(false);
	ui->chk_3->setChecked(false);
	ui->chk_4->setChecked(false);
	ui->chk_5->setChecked(false);
	ui->chk_6->setChecked(false);
	ui->chk_7->setChecked(false);
	ui->chk_8->setChecked(false);
	ui->chk_9->setChecked(false);
	ui->cb_all->setChecked(false);
}


void MonthMaintenanceWidgets::setCenterImageColor(QImage &image, QColor &color)
{
	image = image.convertToFormat(QImage::Format_RGBA8888_Premultiplied, Qt::NoFormatConversion);
	int bmpWidth = image.width();
	int bmpHeight = image.height();
	for (int i = 0; i < bmpWidth; ++i) {
		for (int j = 0; j < bmpHeight; ++j) {
			//将灰色(0~255)全部替换成设定的颜色，全透明的不替换
			QColor tempColor = image.pixelColor(i, j);
			if (tempColor.alpha() != 0) {
				color.setAlpha(tempColor.alpha());
				image.setPixelColor(i, j, color);
			}
		}
	}
}


void MonthMaintenanceWidgets::createPumpBtn(QPushButton *pushButton,bool selected_status)
{
	auto empty = "irrigationIcon.png";
	QImage image(_pixPath + empty);
	//ui->pumpLB1_1->setPixmap(QPixmap::fromImage(image));
	QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	pushButton->setIcon(QIcon(fitpixmap));
	pushButton->setProperty("btnStyle", "btnReagentPosStyle");
	pushButton->setProperty(GlobalData::getPropertyName(), PumpPosState::enumEmpty);
	pushButton->setIconSize(QSize(image.width(), image.height()));

	if (selected_status)
	{
		pushButton->setChecked(true);//->setCheckable(true);
	}
	else
	{
		pushButton->setChecked(false);
	}
}

void MonthMaintenanceWidgets::changeIcon(const QString &fileName, PumpPosState state)
{
	for (auto &it : _btnGroup->buttons())
	{
		if (it->isChecked())
		{
			auto btn = reinterpret_cast<CustomButton*>(it);
			btn->setProperty(GlobalData::getPropertyName(), state);
			btn->setPixPath(_pixPath + fileName);
			btn->setChecked(false);
		}
	}
	emit sglPumpStateChanged();
}


QButtonGroup *MonthMaintenanceWidgets::getBtnGroup() const
{
	return _btnGroup;
}

void MonthMaintenanceWidgets::on_btnFlash_clicked()
{
	if (InstrumentStateModel::instance()->getMachineState().state == InstrumentStateModel::enumStandby)
		changeIcon(_readyFile, PumpPosState::enumReady);
	else
		changeIcon(_flushFile, PumpPosState::enumFlush);
}

void MonthMaintenanceWidgets::on_btnReady_clicked()
{
	changeIcon(_readyFile, PumpPosState::enumReady);
}

void MonthMaintenanceWidgets::on_btnDelay_clicked()
{
	changeIcon(_delayFile, PumpPosState::enumDelay);
}

void MonthMaintenanceWidgets::on_pushButton_2_clicked()
{
	if (ui->pushButton_2->isChecked())
	{
		ui->chk_1->setChecked(true);
		ui->pushButton_2->setChecked(true);

	}
	else
	{
		ui->chk_1->setChecked(false);
		ui->pushButton_2->setChecked(false);
	}
}

void MonthMaintenanceWidgets::on_pushButton_3_clicked() {
	if (ui->pushButton_3->isChecked())
	{
		ui->chk_2->setChecked(true);
		ui->pushButton_3->setChecked(true);

	}
	else
	{
		ui->chk_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
	}
}

void MonthMaintenanceWidgets::on_pushButton_4_clicked() {
	if (ui->pushButton_4->isChecked())
	{
		ui->chk_3->setChecked(true);
		ui->pushButton_4->setChecked(true);

	}
	else
	{
		ui->chk_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
	}
}

void MonthMaintenanceWidgets::on_pushButton_5_clicked() {
	if (ui->pushButton_5->isChecked())
	{
		ui->chk_4->setChecked(true);
		ui->pushButton_5->setChecked(true);

	}
	else
	{
		ui->chk_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
	}
}
void MonthMaintenanceWidgets::on_pushButton_6_clicked() {

	if (ui->pushButton_6->isChecked())
	{
		ui->chk_5->setChecked(true);
		ui->pushButton_6->setChecked(true);

	}
	else
	{
		ui->chk_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
	}
}
void MonthMaintenanceWidgets::on_pushButton_7_clicked() {
	if (ui->pushButton_7->isChecked())
	{
		ui->chk_6->setChecked(true);
		ui->pushButton_7->setChecked(true);

	}
	else
	{
		ui->chk_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
	}
}
void MonthMaintenanceWidgets::on_pushButton_8_clicked() {
	if (ui->pushButton_8->isChecked())
	{
		ui->chk_7->setChecked(true);
		ui->pushButton_8->setChecked(true);

	}
	else
	{
		ui->chk_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
	}
}
void MonthMaintenanceWidgets::on_pushButton_9_clicked() {

	if (ui->pushButton_9->isChecked())
	{
		ui->chk_8->setChecked(true);
		ui->pushButton_9->setChecked(true);

	}
	else
	{
		ui->chk_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
	}
}
void MonthMaintenanceWidgets::on_pushButton_10_clicked() {

	if (ui->pushButton_10->isChecked())
	{
		ui->chk_9->setChecked(true);
		ui->pushButton_10->setChecked(true);

	}
	else
	{
		ui->chk_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
	}
}

void MonthMaintenanceWidgets::setProgressDialog(ProgressDialog *progressDialog)
{
	m_progressDialog = progressDialog;
}
