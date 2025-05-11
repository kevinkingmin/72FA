#include "..\include\precomp\precompile.h"
#include "PumpAutoCheckWidgets.h"
#include <QMessageBox>
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "src/main/subDialog/ProgressDialog.h"
#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"

PumpAutoCheckWidgets::PumpAutoCheckWidgets(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::PumpAutoCheckWidgetsClass)
	, _InstrumentState(InstrumentStateModel::instance())
	, _instr(Instrument::instance())
	, _emptyFile("rFlowBack128.png")
	, _flushFile("irrigationIcon.png")
	, _readyFile("rReady.png")
	, _delayFile("rDelay.png")
	, _pixPath(":/images/buttonIcon/")
{
	ui->setupUi(this);
	createPumpBtn(ui->pushButton_2, false);
	createPumpBtn(ui->pushButton_3, false);
	createPumpBtn(ui->pushButton_4, false);
	createPumpBtn(ui->pushButton_5, false);
	createPumpBtn(ui->pushButton_6, false);
	createPumpBtn(ui->pushButton_7, false);
	createPumpBtn(ui->pushButton_8, false);
	createPumpBtn(ui->pushButton_9, false);
	createPumpBtn(ui->pushButton_10, false);
	ui->progressBar->setStyleSheet("QProgressBar {border: 1px solid grey; border-radius: 2px; background-color: #FFFFFF; text-align:center; font-size:15px}");
	ui->groupBox_2->setVisible(false);
	ui->cb_all->setVisible(false);
	connect(_instr, &Instrument::sglAutoPumpCalibrateResult, this, &PumpAutoCheckWidgets::slotIsStepSuc);
	connect(_instr, &Instrument::sglIsStepSuc, this, &PumpAutoCheckWidgets::slotIsStepSuc1);


	/*
	connect(_instr, &Instrument::sglPumpCalibrateResult, this, [this](int pumpNo, int fstSteps, int SndSteps) {

		if (m_start_pump_auto_check)
		{
			QString p = QString::number(pumpNo + 1);
			QString f = QString::number(fstSteps);
			QString s = QString::number(SndSteps);
			int dint = abs(fstSteps - SndSteps);
			QString d = QString::number(dint);
			//    auto pm=SystemSetBLL().getRowById(26);
			//    int stard=pm.isNull()?500:pm->getSaveSet();
			//    QString strStard=QString::number(stard);
			//    QString result="";
			//    if(stard>=dint)
			//        result=tr("  校准成功");
			//    else
			//        result=tr("  校准失败");

			//    ui->textBrowser->append(tr("泵号:")+p+tr("  第一次下降步数:")+f+tr("  第二次下降步数:")+s
			//                            +tr("  两次下降步数差:")+d+tr("  设置标准:")+strStard+result);
			//});

			auto pm = SystemSetBLL().getRowById(26);
			int stardMin = pm.isNull() ? 200 : pm->getSaveSet();
			QString stardMax = pm.isNull() ? "400" : pm->getSaveDes();
			QString strStardMin = QString::number(stardMin);
			QString result = "";

			if (dint >= stardMin && dint <= stardMax.toInt())
			{
				result = tr("  校准成功");
				//m_check_pump_status = false;
			}
			else
			{
				 //_instr->getWPumpVolumeToSteps(pumpNo, m_current_step);
				if (fstSteps - SndSteps > 0)
				{
					m_current_step -= 3;
				}
				else
				{
					m_current_step += 3;
				}
				//如果失败则发送
				//_instr->convertVolumeToStepsToMachine(pumpNo, m_current_step);
				m_check_pump_status = true;
				result = tr("  校准失败");
			}

			m_finish_pump_auto_check_number++;
			if (m_need_pump_auto_check_number == m_finish_pump_auto_check_number)
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
				ui->cb_all->setChecked(false);
				m_start_pump_auto_check = false;
				m_finish_pump_auto_check_number = 0;

				//if (m_check_pump_status)
				//{
				//	Global::g_run_or_maintenance_flage = 1;
				//	//调用接口去得到当前对应步数，是用减还是用加？
				//	//m_current_step = 100;
				//	_instr->setPumpVect(mOutVect);
				//	_instr->maintain(ePumpCalibrate);
				//	m_start_pump_auto_check = true;
				//	m_finish_pump_auto_check_number = 0;
				//	m_need_pump_auto_check_number = mOutVect.size();
				//	m_progressDialog->setHead("正在进行泵校准......");
				//	m_progressDialog->exec();
				//}
				QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("自动校准泵操作完成！"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
			}

			ui->textBrowser->append(tr("泵号:") + p + tr("  第一次下降步数:") + f + tr("  第二次下降步数:") + s
				+ tr("  两次下降步数差:") + d + tr("  设置标准:") + strStardMin + "~"
				+ stardMax + result);
		}
	});

	*/

	ui->chk_1->setEnabled(false);
	ui->chk_2->setEnabled(false);
	ui->chk_3->setEnabled(false);
	ui->chk_4->setEnabled(false);
	ui->chk_5->setEnabled(false);
	ui->chk_6->setEnabled(false);
	ui->chk_7->setEnabled(false);
	ui->chk_8->setEnabled(false);
	ui->chk_9->setEnabled(false);

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
	ui->label_3->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1081");
	ui->pushButton_13->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1241");
	ui->label_5->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1242");
	ui->pushButton_11->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1243");
	ui->pushButton_12->setText(sz1);

}

void PumpAutoCheckWidgets::on_pushButton_13_clicked() {
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
		ui->pushButton_13->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1637"));
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
		ui->pushButton_13->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1081"));//setText("全选");
		all_select_flage = false;
	}
	getCheckBtn();
}


void PumpAutoCheckWidgets::on_pushButton_12_clicked() {
	m_stop_liquid_detect = true;
}

void PumpAutoCheckWidgets::on_pushButton_11_clicked() {

	if (!_InstrumentState->enumStandby)
	{
		return;
	}

	//int ret = QMessageBox::question(this, "校准", "是否进行一下步校准？", "继续", "退出");
	//if (ret == 0)
	//{
	//	int a = 0;
	//}
	//return;
	ui->textBrowser->setText("");
	auto state = _InstrumentState->getMachineState();
	if (!state.canRun)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1321"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}
	//auto vect = getCheckBtn();
	if (mOutVect.isEmpty())
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1507"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}

	Global::g_run_or_maintenance_flage = 1;
	//调用接口去得到当前对应步数，是用减还是用加？
	//m_current_step = 100;
	//_instr->setPumpVect(mOutVect);
	//_instr->maintain(ePumpCalibrate);
	//void pumpCalibrate(const uchar pumpNo, const ushort volume, const bool isLightOn = true);
	//_instr->pumpCalibrate()

	m_need_pump_auto_check_number = mOutVect.size();
	//Global::g_run_or_maintenance_flage = 1;
    //_instr->pumpCalibrate(mOutVect[0], 500, true);
    QList<uint8_t> pumpList;
    for(int pumpNum:mOutVect){
        pumpList.push_back(static_cast<uint8_t>(pumpNum));
    }
    _instr->pumpAutoCalibrate(pumpList);
	m_stop_liquid_detect = false;
	m_start_pump_auto_check = true;
	m_finish_pump_auto_check_number = 0;

	m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1618"));//"正在进行泵校准......");
	m_progressDialog->exec();
    //_InstrumentState->setMachineState(_InstrumentState->enumStandby);
}

void PumpAutoCheckWidgets::slotIsStepSuc1(int ret) {
	if (ret >= 0)
	{
		//如果失败则发送
		if (m_start_pump_auto_check)
		{
			if (!m_check_pump_status)
			{
				if (m_current_step_flage)
				{
					m_current_step -= 3;
				}
				else
				{
					m_current_step += 3;
				}
				if (m_current_step > 130 || m_current_step < 30)
				{
					m_stop_liquid_detect = true;
					QString sz = QString("%2%1%3").arg(m_current_step).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"));
					MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), sz, MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
					m_check_pump_status = false;
				}

				if (!m_stop_liquid_detect)
				{
					QString sz = "";
					if (m_current_step_flage)
					{
						int tm_step = m_current_step + 3;
						sz = QString("%4%1%5%2%6%3").arg(m_current_pump_no + 1).arg(tm_step).arg(m_current_step).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1514")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1621")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1622"));
					}
					else
					{
						int tm_step = m_current_step -3;
						//sz = QString("泵号:%1,  50ul步数由:%2，改为:%3").arg(m_current_pump_no + 1).arg(tm_step).arg(m_current_step);
						sz = QString("%4%1%5%2%6%3").arg(m_current_pump_no + 1).arg(tm_step).arg(m_current_step).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1514")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1621")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1622"));
					}

					ui->textBrowser->append(sz + tr(" \r\n"));
					//int ret = QMessageBox::question(this, "校准", "校准选择", "继续", "退出");
					int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1510"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
					if (ret == MyMessageBox::Ok)
					{
                        //_instr->convertVolumeToStepsToMachine(m_current_pump_no, m_current_step);
						m_check_pump_status = true;
                        //_instr->pumpCalibrate(m_current_pump_no, 500, true);
					}
					else
					{
						m_stop_liquid_detect = true;
						m_check_pump_status = false;
					}
				}

			}
		}
	}
}

void PumpAutoCheckWidgets::slotIsStepSuc(int ret, int pumpNo, int fstSteps, int SndSteps) {

	if (ret >= 0)
	{
		if (m_start_pump_auto_check)
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
				//QString sz = QString("泵号:%1,  50ul对应步数:%2").arg(p).arg(m_current_step);
				//ui->textBrowser->append(sz + tr(" \r\n"));
				//result = tr("  校准成功");
				//result = QString("校准成功\r\n泵号:%1,  50ul对应步数:%2").arg(p).arg(m_current_step);
				result = QString("%3%1%4%2").arg(p).arg(m_current_step).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1619")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1620"));
				//m_check_pump_status = false;
				//如果成功继续下一个校准
				if (mOutVect.count() > 0)
				{
                    //_instr->pumpCalibrate(mOutVect[0], 500, true);
					mOutVect.removeAt(0);
				}
				m_finish_pump_auto_check_number++;
				m_stop_liquid_detect = true;
			}
			else
			{
                //_instr->getWPumpVolumeToSteps(pumpNo, m_current_step);
				if (fstSteps - SndSteps > stardMax.toInt())
				{
					//m_current_step -= 3;
					m_current_step_flage = true;
				}

				if (fstSteps - SndSteps < stardMin)
				{
					//m_current_step += 3;
					m_current_step_flage = false;
				}

				if (fstSteps - SndSteps ==0)
				{
					//未检测到液体
					m_stop_liquid_detect = true;
					m_check_pump_status = false;
					MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1511"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");

				}

				if (fstSteps - SndSteps < 0)
				{
					//液位探测失败
					m_stop_liquid_detect = true;
					m_check_pump_status = false;
					MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1512"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
				}

				//else
				//{
				//	m_current_step_flage = true;
				//	//m_current_step -= 3;
				//}
				m_current_pump_no = pumpNo;
				result = tr("  校准失败");
				m_check_pump_status = false;

				m_start_pump_auto_check = false;
			}

			if (m_need_pump_auto_check_number == m_finish_pump_auto_check_number)
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
				ui->cb_all->setChecked(false);
				m_start_pump_auto_check = false;
				m_check_pump_status = false;
				m_finish_pump_auto_check_number = 0;
				MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1513"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
			}

			ui->textBrowser->append(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1514") + p + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1515") + f + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1516") + s
				+ GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1517") + d + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1518") + strStardMin + "~"
				+ stardMax + result);
		}

	}
}

PumpAutoCheckWidgets::~PumpAutoCheckWidgets()
{}

QVector<uchar> PumpAutoCheckWidgets::getCheckBtn()
{
	QVector<uchar> outVect;
	mOutVect = outVect;
	return outVect;
}

void PumpAutoCheckWidgets::on_chk_1_toggled(bool state)
{
	//getCheckBtn();
}

void PumpAutoCheckWidgets::on_chk_2_toggled(bool state)
{
	//getCheckBtn();
}

void PumpAutoCheckWidgets::on_chk_3_toggled(bool state)
{
	//getCheckBtn();
}

void PumpAutoCheckWidgets::on_chk_4_toggled(bool state)
{
	//getCheckBtn();
}
void PumpAutoCheckWidgets::on_chk_5_toggled(bool state)
{
	//getCheckBtn();
}
void PumpAutoCheckWidgets::on_chk_6_toggled(bool state)
{
	//getCheckBtn();
}
void PumpAutoCheckWidgets::on_chk_7_toggled(bool state)
{
	//getCheckBtn();
}
void PumpAutoCheckWidgets::on_chk_8_toggled(bool state)
{
	//getCheckBtn();
}
void PumpAutoCheckWidgets::on_chk_9_toggled(bool state)
{
	//getCheckBtn();
}

void PumpAutoCheckWidgets::on_pushButton_2_clicked()
{
	if (ui->pushButton_2->isChecked())
	{
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);


		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->chk_1->setChecked(true);
		ui->pushButton_2->setChecked(true);


		QVector<uchar> outVect;
		outVect.push_back(0);
		mOutVect = outVect;

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

		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);

	}
}

void PumpAutoCheckWidgets::on_pushButton_3_clicked() {
	if (ui->pushButton_3->isChecked())
	{
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->chk_2->setChecked(true);
		ui->pushButton_3->setChecked(true);
		QVector<uchar> outVect;
		outVect.push_back(1);
		mOutVect = outVect;

	}
	else
	{
		ui->chk_2->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
	}
}

void PumpAutoCheckWidgets::on_pushButton_4_clicked() {
	if (ui->pushButton_4->isChecked())
	{
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->chk_3->setChecked(true);
		ui->pushButton_4->setChecked(true);

		QVector<uchar> outVect;
		outVect.push_back(2);
		mOutVect = outVect;

	}
	else
	{
		ui->chk_3->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
	}
}

void PumpAutoCheckWidgets::on_pushButton_5_clicked() {
	if (ui->pushButton_5->isChecked())
	{
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->chk_4->setChecked(true);
		ui->pushButton_5->setChecked(true);

		QVector<uchar> outVect;
		outVect.push_back(3);
		mOutVect = outVect;

	}
	else
	{
		ui->chk_4->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
	}
}

void PumpAutoCheckWidgets::on_pushButton_6_clicked() {

	if (ui->pushButton_6->isChecked())
	{
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->chk_5->setChecked(true);
		ui->pushButton_6->setChecked(true);

		QVector<uchar> outVect;
		outVect.push_back(4);
		mOutVect = outVect;

	}
	else
	{
		ui->chk_5->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
	}
}

void PumpAutoCheckWidgets::on_pushButton_7_clicked() {
	if (ui->pushButton_7->isChecked())
	{
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->chk_6->setChecked(true);
		ui->pushButton_7->setChecked(true);

		QVector<uchar> outVect;
		outVect.push_back(5);
		mOutVect = outVect;

	}
	else
	{
		ui->chk_6->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
	}
}
void PumpAutoCheckWidgets::on_pushButton_8_clicked() {
	if (ui->pushButton_8->isChecked())
	{
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->chk_7->setChecked(true);
		ui->pushButton_8->setChecked(true);

		QVector<uchar> outVect;
		outVect.push_back(6);
		mOutVect = outVect;

	}
	else
	{
		ui->chk_7->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
	}
}

void PumpAutoCheckWidgets::setProgressDialog(ProgressDialog *progressDialog)
{
	m_progressDialog = progressDialog;
}

void PumpAutoCheckWidgets::on_pushButton_9_clicked() {

	if (ui->pushButton_9->isChecked())
	{
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->chk_8->setChecked(true);
		ui->pushButton_9->setChecked(true);

		QVector<uchar> outVect;
		outVect.push_back(7);
		mOutVect = outVect;

	}
	else
	{
		ui->chk_8->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
	}
}
void PumpAutoCheckWidgets::on_pushButton_10_clicked() {

	if (ui->pushButton_10->isChecked())
	{
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->chk_9->setChecked(true);
		ui->pushButton_10->setChecked(true);

		QVector<uchar> outVect;
		outVect.push_back(8);
		mOutVect = outVect;

	}
	else
	{
		ui->chk_9->setChecked(false);
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
		ui->pushButton_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
	}
}



void PumpAutoCheckWidgets::on_cb_all_toggled(bool state)
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
void PumpAutoCheckWidgets::createPumpBtn(QPushButton *pushButton, bool selected_status)
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
