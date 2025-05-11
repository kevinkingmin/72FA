#include "PumpCalibrateWidget.h"
#include "ui_PumpCalibrateWidget.h"
#include <QMessageBox>
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "src/main/subDialog/ProgressDialog.h"
#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"

#include "src/comm/GlobalData.h"
PumpCalibrateWidget::PumpCalibrateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PumpCalibrateWidget)
  ,_InstrumentState(InstrumentStateModel::instance())
  ,_instr(Instrument::instance())
{
    ui->setupUi(this);
 //   connect(_instr,&Instrument::sglPumpCalibrateResult,this,[this](int pumpNo, int fstSteps, int SndSteps){
 //       QString p=QString::number(pumpNo+1);
 //       QString f=QString::number(fstSteps);
 //       QString s=QString::number(SndSteps);
 //       int dint=abs(fstSteps-SndSteps);
 //       QString d=QString::number(dint);

	//	auto pm = SystemSetBLL().getRowById(26);
	//	int stardMin = pm.isNull() ? 200 : pm->getSaveSet();
	//	QString stardMax = pm.isNull() ? "400" : pm->getSaveDes();
	//	QString strStardMin = QString::number(stardMin);
	//	QString result = "";
	//	if (dint >= stardMin && dint <= stardMax.toInt())
	//		result = tr("  校准成功");
	//	else
	//		result = tr("  校准失败");

	//	ui->textBrowser->append(tr("泵号:") + p + tr("  第一次下降步数:") + f + tr("  第二次下降步数:") + s
	//		+ tr("  两次下降步数差:") + d + tr("  设置标准:") + strStardMin + "~"
	//		+ stardMax + result);
	//});
	QString sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1221");
	ui->chk_1->setText("1" + sz1);
	ui->chk_2->setText("2" + sz1);
	ui->chk_3->setText("3" + sz1);
	ui->chk_4->setText("4" + sz1);
	ui->chk_5->setText("5" + sz1);
	ui->chk_6->setText("6" + sz1);
	ui->chk_7->setText("7" + sz1);
	ui->chk_8->setText("8" + sz1);

}

PumpCalibrateWidget::~PumpCalibrateWidget()
{
    delete ui;
}

void PumpCalibrateWidget::on_btnStart_clicked()
{
    ui->textBrowser->setText("");
    auto state = _InstrumentState->getMachineState();
    if (!state.canRun)
    {
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1321") ,MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    auto vect=getCheckBtn();
    if(vect.isEmpty())
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1507"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }


	Global::g_run_or_maintenance_flage = 1;


    //_instr->setPumpVect(vect);
    //_instr->maintain(ePumpCalibrate);
    m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1618"));//"正在进行泵校准......");
    m_progressDialog->exec();
}

QVector<uchar> PumpCalibrateWidget::getCheckBtn()
{
    QVector<uchar>outVect;
    if(ui->chk_1->isChecked())
        outVect.push_back(0);
    if(ui->chk_2->isChecked())
        outVect.push_back(1);
    if(ui->chk_3->isChecked())
        outVect.push_back(2);
    if(ui->chk_4->isChecked())
        outVect.push_back(3);
    if(ui->chk_5->isChecked())
        outVect.push_back(4);
    if(ui->chk_6->isChecked())
        outVect.push_back(5);
    if(ui->chk_7->isChecked())
        outVect.push_back(6);
    if(ui->chk_8->isChecked())
        outVect.push_back(7);
    return outVect;
}

void PumpCalibrateWidget::setProgressDialog(ProgressDialog *progressDialog)
{
    m_progressDialog = progressDialog;
}
void PumpCalibrateWidget::on_checkBox_all_3_toggled(bool state)
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
	}
	getCheckBtn();
}
