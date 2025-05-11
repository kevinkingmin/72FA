#include "..\include\precomp\precompile.h"
#include "NewPumpRunningWidgets.h"
#include <QStyleFactory>
#include "src/main/subDialog/ProgressDialog.h"
#include "../Include/Model/Model.h"

#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"

NewPumpRunningWidgets::NewPumpRunningWidgets(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::NewPumpRunningWidgetsClass)
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
	connect(myTimer, &QTimer::timeout, this, &NewPumpRunningWidgets::doProcessTimeout);
	connect(_instr, &Instrument::sglIsStepSuc, this, &NewPumpRunningWidgets::slotIsStepSuc);

	ui->pushButton_11->setVisible(true);
	ui->cb_all->setVisible(false);


	//QApplication::setStyle(QStyleFactory::create("Fusion"));
	//sglIsStepSuc
	ui->progressBar->setStyleSheet("QProgressBar {border: 1px solid grey; border-radius: 2px; background-color: #FFFFFF; text-align:center; font-size:15px}");
	//ui->radioButton_3->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
	//	"QRadioButton::indicator:checked {background-color:green;}"
	//	"QRadioButton::indicator:unchecked {background-color:red;}"
	//);

	//ui->radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
	//	"QRadioButton::indicator:checked {background-color:green;}"
	//	"QRadioButton::indicator:unchecked {background-color:red;}"
	//);

	//ui->radioButton_2->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
	//	"QRadioButton::indicator:checked {background-color:green;}"
	//	"QRadioButton::indicator:unchecked {background-color:red;}"
	//);

	//ui->cb_all->setVisible(false);

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
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1223");
	ui->label_5->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1224");
	ui->label->setText(sz1);

	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1207");
	ui->label_2->setText(sz1+"1-100");
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1225");
	ui->pushButton_11->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1222");
	ui->pushButton->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1081");
	ui->pushButton_12->setText(sz1);
	

}

void NewPumpRunningWidgets::slotIsStepSuc(int ret) {
	if (ret>=0)
	{
		if (m_start_NewPumpRunningWidgets)
		{
			QVector<int> motor_speed_vect;
			QVector<MotorSpeedPara> paras_vector;
			if (IsStepSuc_flag)
			{

				auto state = _InstrumentState->getMachineState();
				if (state.state == enumState::enumError)
				{
					return;
				}



                //motor_speed_vect = _instr->getMotorSpeed(mOutVect);
				IsStepSuc_flag = false;

				for (size_t i = 0; i < mOutVect.length(); i++)
				{
					MotorSpeedPara msp;
					msp.direction = 1;
					msp.motorAddress = mOutVect[i];
					msp.photoelectricEnable = false;
					msp.speed = motor_speed_vect[i];
					paras_vector.append(msp);
				}
			}
			//
			/**
			 * @brief motorMoveConstSpeed:电机固定速度转动
			 * @param motorAddress:电机地址
			 * @param photoelectricEnable:false=不使能,true=使能
			 * @param direction:false=左转,1=右转
			 * @param speed:旋转速度，一般取inquireMotorSpeed对应电机速度。
			 * @return <0失败，>=0成功。
			 */
			if (M_need_to_run)
			{
				//_InstrumentState->setMachineState(enumState::enumMaintain);
                //_instr->motorMoveConstSpeed(paras_vector);
				M_need_to_run = false;
			}
		}
	}
	else
	{
		IsStepSuc_flag = false;
	}
}

NewPumpRunningWidgets::~NewPumpRunningWidgets()
{}

QVector<uchar> NewPumpRunningWidgets::getCheckBtn()
{
	QVector<uchar> outVect;
	if (ui->chk_1->isChecked())
	{
		createPumpBtn(ui->pushButton_2, true);
		outVect.push_back(0x06);
	}
	else
	{
		createPumpBtn(ui->pushButton_2, false);
	}

	if (ui->chk_2->isChecked())
	{
		createPumpBtn(ui->pushButton_3, true);
		outVect.push_back(0x07);
	}
	else
	{
		createPumpBtn(ui->pushButton_3, false);
	}

	if (ui->chk_3->isChecked())
	{
		createPumpBtn(ui->pushButton_4, true);
		outVect.push_back(0x08);
	}
	else
	{
		createPumpBtn(ui->pushButton_4, false);
	}

	if (ui->chk_4->isChecked())
	{
		createPumpBtn(ui->pushButton_5, true);
		outVect.push_back(0x09);
	}
	else
	{
		createPumpBtn(ui->pushButton_5, false);
	}

	if (ui->chk_5->isChecked())
	{
		createPumpBtn(ui->pushButton_6, true);
		outVect.push_back(0x0A);
	}
	else
	{
		createPumpBtn(ui->pushButton_6, false);
	}

	if (ui->chk_6->isChecked())
	{
		createPumpBtn(ui->pushButton_7, true);
		outVect.push_back(0x0B);
	}
	else
	{
		createPumpBtn(ui->pushButton_7, false);
	}

	if (ui->chk_7->isChecked())
	{
		createPumpBtn(ui->pushButton_8, true);
		outVect.push_back(0x0C);
	}
	else
	{
		createPumpBtn(ui->pushButton_8, false);
	}

	if (ui->chk_8->isChecked())
	{
		createPumpBtn(ui->pushButton_9, true);
		outVect.push_back(0x0D);
	}
	else
	{
		createPumpBtn(ui->pushButton_9, false);
	}

	if (ui->chk_9->isChecked())
	{
		createPumpBtn(ui->pushButton_10, true);
		outVect.push_back(0x0E);
	}
	else
	{
		createPumpBtn(ui->pushButton_10, false);
	}
	mOutVect = outVect;
	return outVect;
}

void NewPumpRunningWidgets::on_chk_1_toggled(bool state)
{
	getCheckBtn();
	//if (state)
	//{
	//	getCheckBtn();
	//}
}

void NewPumpRunningWidgets::on_chk_2_toggled(bool state)
{
	//if (state)
	//{
	//	getCheckBtn();
	//}
	getCheckBtn();
}

void NewPumpRunningWidgets::on_chk_3_toggled(bool state)
{
	//if (state)
	//{
	//	getCheckBtn();
	//}
	getCheckBtn();
}

void NewPumpRunningWidgets::on_chk_4_toggled(bool state)
{
	//if (state)
	//{
	//	getCheckBtn();
	//}
	getCheckBtn();
}
void NewPumpRunningWidgets::on_chk_5_toggled(bool state)
{
	//if (state)
	//{
	//	getCheckBtn();
	//}
	getCheckBtn();
}
void NewPumpRunningWidgets::on_chk_6_toggled(bool state)
{
	//if (state)
	//{
	//	getCheckBtn();
	//}
	getCheckBtn();
}
void NewPumpRunningWidgets::on_chk_7_toggled(bool state)
{
	//if (state)
	//{
	//	getCheckBtn();
	//}
	getCheckBtn();
}
void NewPumpRunningWidgets::on_chk_8_toggled(bool state)
{
	//if (state)
	//{
	//	getCheckBtn();
	//}
	getCheckBtn();
}
void NewPumpRunningWidgets::on_chk_9_toggled(bool state)
{
	//if (state)
	//{
	//	getCheckBtn();
	//}
	getCheckBtn();
}

void NewPumpRunningWidgets::on_pushButton_2_clicked()
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

void NewPumpRunningWidgets::on_pushButton_3_clicked() {
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

void NewPumpRunningWidgets::on_pushButton_4_clicked() {
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

void NewPumpRunningWidgets::on_pushButton_5_clicked() {
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
void NewPumpRunningWidgets::on_pushButton_6_clicked() {

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
void NewPumpRunningWidgets::on_pushButton_7_clicked() {
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
void NewPumpRunningWidgets::on_pushButton_8_clicked() {
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
void NewPumpRunningWidgets::on_pushButton_9_clicked() {

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

void NewPumpRunningWidgets::on_pushButton_10_clicked() {

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

void NewPumpRunningWidgets::on_cb_all_toggled(bool state)
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

void NewPumpRunningWidgets::createPumpBtn(QPushButton *pushButton, bool selected_status)
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

void NewPumpRunningWidgets::on_pushButton_12_clicked() {
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



void NewPumpRunningWidgets::on_pushButton_11_clicked() {
	if (mOutVect.length()==0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1220"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}
	index = 0;
	mNeed_times = 0;
	ui->progressBar->setValue(0);
	myTimer->stop();
	ui->pushButton->setEnabled(true);
	//_instr->motorInitialize(0x05, 60000);
    //_instr->setBuzzleOnOff(0x00);
    //_instr->motorStop(mOutVect);
	m_start_NewPumpRunningWidgets = false;
	_InstrumentState->setMachineState(enumState::enumStandby);
}

void NewPumpRunningWidgets::on_pushButton_clicked() {


	auto state = _InstrumentState->getMachineState();
	if (!(state.state == _InstrumentState->enumStandby))
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}


	//if (mOutVect.count() != 1)
	//{
	//	QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("单次只能选择一个泵！"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
	//}
	if (mOutVect.length() == 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1220"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}
	index = 0;
	mNeed_times = 0;
	//m_instr->rockBedWorking(3);
	QString need_i_times1 = ui->edit_time->text();
	if (need_i_times1 == "")
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1447"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}

	//if (need_i_times1 == 0)
	//{
	//	QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("磨合时间输入异常！"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
	//	return;
	//}

	if (need_i_times1.toInt() > 100 || need_i_times1.toInt() <= 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1448"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		ui->edit_time->setFocus();
		return;
	}

	ui->progressBar->setValue(0);
	int need_in_times = need_i_times1.toInt();
	ui->progressBar->setRange(0, need_in_times*60);
	myTimer->start(1000);//1s倒计时1次
	ui->pushButton->setEnabled(false);
	//_instr->rockBedWorking(1);
	mNeed_times = need_in_times*60;

	/**
	 * @brief inquireMotorSpeed:获取电机速度
	 * @param motorAddress:电机号
	 * @return <0获取速度失败，>0获取成功。
	 */

	Global::g_run_or_maintenance_flage = 1;
    //_instr->inquireMotorSpeed(mOutVect);
	m_start_NewPumpRunningWidgets = true;
	IsStepSuc_flag = true;
	M_need_to_run = true;
	_InstrumentState->setMachineState(enumState::enumRuning);
	//m_progressDialog->setHead("新泵磨合进行中......");
	//m_progressDialog->exec();
}

void NewPumpRunningWidgets::doProcessTimeout() {
	index++;
	ui->progressBar->setValue(index);
	if (index == mNeed_times)
	{
		//_instr->rockBedWorking(0);
		myTimer->stop();
		ui->pushButton->setEnabled(true);
		//_instr->motorInitialize(0x05, 60000);
        //_instr->setBuzzleOnOff(0x00);
        //_instr->motorStop(mOutVect);
		//->setMachineState(enumState::enumStandby);
		//_InstrumentState->setMachineState(enumState::enumStandby);
		//_InstrumentState->setMachineState(enumState::enumStandby);
		_InstrumentState->setMachineState(enumState::enumStandby);
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
	if (mNeed_times - index == 15)
	{
        //_instr->setBuzzleOnOff(0x03);
	}
}

void NewPumpRunningWidgets::setProgressDialog(ProgressDialog *progressDialog)
{
	m_progressDialog = progressDialog;
}
