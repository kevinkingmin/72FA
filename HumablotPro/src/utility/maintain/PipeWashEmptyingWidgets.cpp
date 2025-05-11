#include "..\include\precomp\precompile.h"
#include "PipeWashEmptyingWidgets.h"

#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "src/main/subDialog/ProgressDialog.h"

#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"

PipeWashEmptyingWidgets::PipeWashEmptyingWidgets(QWidget *parent)
	: QMainWindow(parent)
,ui(new Ui::PipeWashEmptyingWidgetsClass)
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

	myTimer = new QTimer(this);//父亲：当前对象传递进去
	connect(myTimer, &QTimer::timeout, this, &PipeWashEmptyingWidgets::doProcessTimeout);
	connect(_instr, &Instrument::sglIsStepSuc, this, &PipeWashEmptyingWidgets::slotIsStepSuc);

	ui->cb_all->setVisible(false);
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	QString save_set = dao->SelectSaveSetById(&bResult, 20003);
	ui->label_2->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1220"));
	//label_2K1220
	//ui->progressBar->setStyleSheet("QProgressBar {border: 1px solid grey; border-radius: 2px; background-color: #FFFFFF; text-align:center; font-size:15px}");
	//ui->progressBar->setVisible(false);
}

PipeWashEmptyingWidgets::~PipeWashEmptyingWidgets()
{

}

QVector<int> PipeWashEmptyingWidgets::getCheckBtn()
{
	QVector<int> outVect;
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
	mOutVect1 = outVect;
	return outVect;
}

void PipeWashEmptyingWidgets::on_chk_1_toggled(bool state)
{
	getCheckBtn();
}

void PipeWashEmptyingWidgets::on_chk_2_toggled(bool state)
{
	getCheckBtn();
}

void PipeWashEmptyingWidgets::on_chk_3_toggled(bool state)
{
	getCheckBtn();
}

void PipeWashEmptyingWidgets::on_chk_4_toggled(bool state)
{
	getCheckBtn();
}
void PipeWashEmptyingWidgets::on_chk_5_toggled(bool state)
{
	getCheckBtn();
}
void PipeWashEmptyingWidgets::on_chk_6_toggled(bool state)
{
	getCheckBtn();
}
void PipeWashEmptyingWidgets::on_chk_7_toggled(bool state)
{
	getCheckBtn();
}
void PipeWashEmptyingWidgets::on_chk_8_toggled(bool state)
{
	getCheckBtn();
}
void PipeWashEmptyingWidgets::on_chk_9_toggled(bool state)
{
	getCheckBtn();
}

void PipeWashEmptyingWidgets::on_pushButton_2_clicked()
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

void PipeWashEmptyingWidgets::on_pushButton_3_clicked() {
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

void PipeWashEmptyingWidgets::on_pushButton_4_clicked() {
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

void PipeWashEmptyingWidgets::on_pushButton_5_clicked() {
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
void PipeWashEmptyingWidgets::on_pushButton_6_clicked() {

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
void PipeWashEmptyingWidgets::on_pushButton_7_clicked() {
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

void PipeWashEmptyingWidgets::on_pushButton_8_clicked() {
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
void PipeWashEmptyingWidgets::on_pushButton_9_clicked() {

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
void PipeWashEmptyingWidgets::on_pushButton_10_clicked() {

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

void PipeWashEmptyingWidgets::on_cb_all_toggled(bool state)
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

void PipeWashEmptyingWidgets::createPumpBtn(QPushButton *pushButton, bool selected_status)
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
void PipeWashEmptyingWidgets::on_pushButton_12_clicked() {

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
		ui->pushButton_12->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1637"));
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
		ui->pushButton_12->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1081"));//setText("全选");
		all_select_flage = false;
	}
	getCheckBtn();
}

void PipeWashEmptyingWidgets::on_pushButton_11_clicked() {

    /*auto state = _InstrumentState->getMachineState();
	if (!(state.state == _InstrumentState->enumStandby))
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
    }*/

    QList<uint8_t> pumpList;
    for(auto num:mOutVect){
        pumpList.push_back(static_cast<uint8_t>(num+1));
    }
    _instr->shutdownMaintenance(pumpList);
    m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1332"));
    m_progressDialog->exec();
    return;

	//if (!_InstrumentState->enumStandby)
	//{
	//	return;
	//}
	m_step_number = 0;
	if (mOutVect.count() == 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1220"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	QString save_set = dao->SelectSaveSetById(&bResult, 20003);
	int ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1345"), MyMessageBox::Ok | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
	if (ret == MyMessageBox::Ok)
	{
		Global::g_run_or_maintenance_flage = 1;
		auto dao = AnalysisUIDao::instance();
		bool bResult;
		QString save_set = dao->SelectSaveSetById(&bResult, 20003);
		m_start_pile_wash = true;
		//将泵管头放到足量的纯水中
		m_vol = save_set.toInt();//ui->edit_time->text().toInt();
        //_instr->pumpFlushIrrigation(mOutVect[0], m_vol, true);
		m_need_wash_number = mOutVect.size();
		mOutVect.removeAt(0);
		_InstrumentState->setMachineState(_InstrumentState->enumRuning);
		//K1645
		m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1645"));//"关机维护进行中，蠕动泵纯水清洗.");
		m_progressDialog->exec();
	}
	else
	{
		return;
	}

	ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1348"), MyMessageBox::Ok| MyMessageBox::No,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
	if (ret == MyMessageBox::Ok)
	{
		m_start_pile_wash = true;
		//将泵管头放到足量的纯水中
		auto dao = AnalysisUIDao::instance();
		bool bResult;
		QString save_set = dao->SelectSaveSetById(&bResult, 20003);
		m_vol = save_set.toInt();//ui->edit_time->text().toInt();
        //_instr->pumpFlushIrrigation(mOutVect1[0], m_vol, true);
		m_need_wash_number = mOutVect1.size();
		mOutVect1.removeAt(0);

		_InstrumentState->setMachineState(_InstrumentState->enumRuning);
		m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1646"));///"关机维护进行中，蠕动泵管路排空.");
		m_progressDialog->exec();
	}
	else
	{
		return;
	}


	ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1501"), MyMessageBox::Ok | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));//QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("将系统液管头放到足量的纯水中！"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), tr("取消"));
	if (ret == MyMessageBox::Ok)
	{
		m_start_pile_wash2 = true;
		//将泵管头放到足量的纯水中
		auto dao = AnalysisUIDao::instance();
		bool bResult;
		QString save_set = dao->SelectSaveSetById(&bResult, 20003);
		m_vol = save_set.toInt();//ui->edit_time->text().toInt();
        //_instr->washSystemLiquidWay(m_vol);
		_InstrumentState->setMachineState(_InstrumentState->enumRuning);
		m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1647"));//"关机维护进行中，系统液管路清洗.");
		m_progressDialog->exec();
	}
	else
	{
		return;
	}

	ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1502"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
	if (ret == MyMessageBox::Ok)
	{
		m_start_pile_wash3 = true;
		//将泵管头放到足量的纯水中
		auto dao = AnalysisUIDao::instance();
		bool bResult;
		QString save_set = dao->SelectSaveSetById(&bResult, 20003);
		m_vol = save_set.toInt();//ui->edit_time->text().toInt();
        //_instr->washSystemLiquidWay(m_vol);
		_InstrumentState->setMachineState(_InstrumentState->enumRuning);
		m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1648"));///setHead("关机维护进行中，系统液管路排空.");
		m_progressDialog->exec();
	}
	else
	{
		return;
	}

	//

	//m_start_pile_wash = true;
	//m_vol = ui->edit_time->text().toInt();
	//_instr->pumpFlushIrrigation(mOutVect[0], m_vol, true);
	//m_need_wash_number = mOutVect.size();
	//mOutVect.removeAt(0);
	//_instr->maintain(eSystemLiquidWahs);
	//m_progressDialog->setHead("管路排空进行中......");
	//m_progressDialog->exec();

	/**
	 * @brief inquireMotorSpeed:获取电机速度
	 * @param motorAddress:电机号
	 * @return <0获取速度失败，>0获取成功。
	 */
	 //uint speed = _instr->inquireMotorSpeed(0x06);

	 /**
	  * @brief motorMoveConstSpeed:电机固定速度转动
	  * @param motorAddress:电机地址
	  * @param photoelectricEnable:false=不使能,true=使能
	  * @param direction:false=左转,1=右转
	  * @param speed:旋转速度，一般取inquireMotorSpeed对应电机速度。
	  * @return <0失败，>=0成功。
	  */
	  //_instr->motorMoveConstSpeed(0x06, true, 1, 100);

}

void PipeWashEmptyingWidgets::slotIsStepSuc(int ret) {
	if (ret >= 0)
	{
		if (m_start_pile_wash2)
		{
			m_start_pile_wash2 = false;
			_InstrumentState->setMachineState(_InstrumentState->enumStandby);
		}

		auto state = _InstrumentState->getMachineState();
		if (state.state == _InstrumentState->enumError)
		{
			return;
		}

		if (m_start_pile_wash3)
		{
			m_start_pile_wash3 = false;
			_InstrumentState->setMachineState(_InstrumentState->enumStandby);
			MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1503"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		}

		if (mOutVect.count() > 0)
		{
            //_instr->pumpFlushIrrigation(mOutVect[0], m_vol, true);
			mOutVect.removeAt(0);
		}

		if (m_start_pile_wash1)
		{
			if (mOutVect1.count() > 0)
			{
                //_instr->pumpFlushIrrigation(mOutVect1[0], m_vol, true);
				mOutVect1.removeAt(0);
			}
		}

		if (m_start_pile_wash)
		{
			m_finish_wash_number++;
			if (m_need_wash_number == m_finish_wash_number)
			{
				//第二次充灌标识改为
				m_start_pile_wash1 = true;
				_InstrumentState->setMachineState(_InstrumentState->enumStandby);
				MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1504"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
			}
			if (m_need_wash_number * 2 == m_finish_wash_number)
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

				m_start_pile_wash = false;
				m_start_pile_wash1 = false;
				m_finish_wash_number = 0;
				m_need_wash_number = 0;
				//m_progressDialog->setMaxValue(100000);
				//m_progressDialog->close();
				//_instr->maintain(eSystemLiquidWahs);
				_InstrumentState->setMachineState(_InstrumentState->enumStandby);
				MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1505"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
			}
		}

	}
	else
	{

	}
}

void PipeWashEmptyingWidgets::doProcessTimeout() {
	index++;
	//ui->progressBar->setValue(index);
	if (index == mNeed_times)
	{
        //_instr->rockBedWorking(0);
		myTimer->stop();
		ui->pushButton_11->setEnabled(true);
        //_instr->motorInitialize(0x05, 60000);
        //_instr->setBuzzleOnOff(0x00);
	}
	if (mNeed_times - index == 15)
	{
        //_instr->setBuzzleOnOff(0x03);
	}
}

void PipeWashEmptyingWidgets::setProgressDialog(ProgressDialog *progressDialog)
{
	m_progressDialog = progressDialog;
}
