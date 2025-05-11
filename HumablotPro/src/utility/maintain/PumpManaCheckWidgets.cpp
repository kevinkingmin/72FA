#include "..\include\precomp\precompile.h"
#include "PumpManaCheckWidgets.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "src/main/subDialog/ProgressDialog.h"
#include <QMessageBox>
#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"

PumpManaCheckWidgets::PumpManaCheckWidgets(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::PumpManaCheckWidgetsClass)
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

	auto pm = SystemSetBLL().getRowById(26);
	int stardMin = pm.isNull() ? 200 : pm->getSaveSet();
	QString stardMax = pm.isNull() ? "400" : pm->getSaveDes();

	QString str = QString("%1").arg(stardMin);
	ui->lineEdit->setText(str);
	ui->lineEdit_2->setText(stardMax);

	ui->cb_all->setVisible(false);

	connect(_instr, &Instrument::sglIsStepSuc, this, &PumpManaCheckWidgets::slotIsStepSuc);
	connect(_instr, &Instrument::sglPumpCalibrateResult, this, &PumpManaCheckWidgets::slotPumpCalibrateResult);
	/*
	connect(_instr, &Instrument::sglPumpCalibrateResult, this, [this](int pumpNo, int fstSteps, int SndSteps) {
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
		}
		else
		{
			result = tr("  校准失败");
			//void convertVolumeToStepsToMachine(const char motorAddress, int steps);
			_instr->convertVolumeToStepsToMachine((5 + 1), 100);//->convertVolumeToStepsToMachine(0x01, 1000);
		}
		ui->textBrowser->append(tr("泵号:") + p + tr("  第一次下降步数:") + f + tr("  第二次下降步数:") + s+ tr("  两次下降步数差:") + d + tr("  设置标准:") + strStardMin + "~"
			+ stardMax + result);
	});
	*/

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
	ui->label_8->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1081");
	ui->pushButton_13->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1241");
	ui->label_5->setText(sz1);
	//sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1242");
	//ui->pushButton_11->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1242");
	ui->pushButton_12->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1244");
	ui->label_3->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1245");
	ui->label_4->setText(sz1);
	
}

void PumpManaCheckWidgets::slotPumpCalibrateResult(int pumpNo, int fstSteps, int SndSteps)
{

	if (m_start_pump_manal_check)
	{
		QString p = QString::number(pumpNo + 1);
		QString f = QString::number(fstSteps);
		QString s = QString::number(SndSteps);
		int dint = abs(fstSteps - SndSteps);
		QString d = QString::number(dint);
		int stardMin = ui->lineEdit->text().toInt();//pm.isNull() ? 200 : pm->getSaveSet();
		QString stardMax = ui->lineEdit_2->text(); //pm.isNull() ? "400" : pm->getSaveDes();
		QString strStardMin = QString::number(stardMin);
		QString result = "";
		if (dint >= stardMin && dint <= stardMax.toInt())
		{
			result = tr("  校准成功");
		}
		else
		{
			result = tr("  校准失败");
			/**
			 * @brief convertVolumeToStepsToMachine:蠕动泵液体体积对应步数参数写入，信号sglIsStepSuc
			 * @param motorAddress:电机地址
			 * @param steps:步数
			 */
			 //void convertVolumeToStepsToMachine(const char motorAddress, int steps);
			//_instr->convertVolumeToStepsToMachine((pumpNo + 1), 100);//->convertVolumeToStepsToMachine(0x01, 1000);

			//auto vect = getCheckBtn();
			//if (vect.isEmpty())
			//{
			//	QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("请选择您要校准的泵！"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
			//	return;
			//}
			//_instr->setPumpVect(vect);
			//_instr->maintain(ePumpCalibrate);
			//m_progressDialog->setHead("正在进行泵校准......");
			//m_progressDialog->exec();
		}
		m_finish_pump_manal_check_number++;
		if (m_need_pump_manal_check_number == m_finish_pump_manal_check_number)
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
			m_start_pump_manal_check = false;
			MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1519"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		}

		ui->textBrowser->append(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1514") + p + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1515") + f + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1516") + s + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1517") + d + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1518") + strStardMin + "~"
			+ stardMax + result);
	}
}

void PumpManaCheckWidgets::slotIsStepSuc(int ret)
{
	if (ret >= 0)
	{
		int a = 100;
	}
	else
	{
	}

}
void PumpManaCheckWidgets::on_pushButton_13_clicked() {

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
void PumpManaCheckWidgets::on_pushButton_12_clicked() {
	if (!_InstrumentState->enumStandby)
	{
		return;
	}
	ui->textBrowser->setText("");
	auto state = _InstrumentState->getMachineState();
	if (!state.canRun)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1321"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}
	auto vect = getCheckBtn();
	if (vect.isEmpty())
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1507"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}

	int stardMin = ui->lineEdit->text().toInt();//pm.isNull() ? 200 : pm->getSaveSet();
	QString stardMax = ui->lineEdit_2->text(); //pm.isNull() ? "400" : pm->getSaveDes();

	if (stardMin == 0 || stardMax.toInt() == 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1520"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}

	if (stardMin > stardMax.toInt())
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1289"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}


	Global::g_run_or_maintenance_flage = 1;

	//int set_value = ui->lineEdit->text().toInt();
	//for (size_t i = 0; i < vect.length(); i++)
	//{
	//	int pump_no = vect[i] + 1;
	//	_instr->convertVolumeToStepsToMachine(pump_no, set_value);//->convertVolumeToStepsToMachine(0x01, 1000);
	//}

    //_instr->setPumpVect(mOutVect);
//	_instr->maintain(ePumpCalibrate);
	m_finish_pump_manal_check_number = 0;
	m_start_pump_manal_check = true;
	m_need_pump_manal_check_number = mOutVect.size();
	m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1618"));//"正在进行泵校准......");
	m_progressDialog->exec();
	//ui->chk_1->setChecked(false);
	//ui->chk_2->setChecked(false);
	//ui->chk_3->setChecked(false);
	//ui->chk_4->setChecked(false);
	//ui->chk_5->setChecked(false);
	//ui->chk_6->setChecked(false);
	//ui->chk_7->setChecked(false);
	//ui->chk_8->setChecked(false);
	//ui->chk_9->setChecked(false);
	//ui->cb_all->setChecked(false);
}
void PumpManaCheckWidgets::setProgressDialog(ProgressDialog *progressDialog)
{
	m_progressDialog = progressDialog;
}

PumpManaCheckWidgets::~PumpManaCheckWidgets()
{}

QVector<uchar> PumpManaCheckWidgets::getCheckBtn()
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

void PumpManaCheckWidgets::on_chk_1_toggled(bool state)
{
	getCheckBtn();
}

void PumpManaCheckWidgets::on_chk_2_toggled(bool state)
{
	getCheckBtn();
}

void PumpManaCheckWidgets::on_chk_3_toggled(bool state)
{
	getCheckBtn();
}

void PumpManaCheckWidgets::on_chk_4_toggled(bool state)
{
	getCheckBtn();
}
void PumpManaCheckWidgets::on_chk_5_toggled(bool state)
{
	getCheckBtn();
}
void PumpManaCheckWidgets::on_chk_6_toggled(bool state)
{
	getCheckBtn();
}
void PumpManaCheckWidgets::on_chk_7_toggled(bool state)
{
	getCheckBtn();
}
void PumpManaCheckWidgets::on_chk_8_toggled(bool state)
{
	getCheckBtn();
}
void PumpManaCheckWidgets::on_chk_9_toggled(bool state)
{
	getCheckBtn();
}

void PumpManaCheckWidgets::on_pushButton_2_clicked()
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

void PumpManaCheckWidgets::on_pushButton_3_clicked() {
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

void PumpManaCheckWidgets::on_pushButton_4_clicked() {
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

void PumpManaCheckWidgets::on_pushButton_5_clicked() {
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
void PumpManaCheckWidgets::on_pushButton_6_clicked() {

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
void PumpManaCheckWidgets::on_pushButton_7_clicked() {
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
void PumpManaCheckWidgets::on_pushButton_8_clicked() {
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
void PumpManaCheckWidgets::on_pushButton_9_clicked() {

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
void PumpManaCheckWidgets::on_pushButton_10_clicked() {

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


void PumpManaCheckWidgets::on_cb_all_toggled(bool state)
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
void PumpManaCheckWidgets::createPumpBtn(QPushButton *pushButton, bool selected_status)
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
