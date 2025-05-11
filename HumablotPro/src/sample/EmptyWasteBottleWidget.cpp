#include "EmptyWasteBottleWidget.h"
#include "ui_EmptyWasteBottleWidget.h"
#include <QMessageBox>
#include <QTimer>
#include "src/main/subDialog/ProgressDialog.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/BLL/baseSet/InstrumentParasSetBLL.h"
#include "../Include/Model/baseSet/InstrumentParasSetModel.h"
#include "../Include/Model/baseSet/CommonType.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "src/comm/GlobalData.h"

EmptyWasteBottleWidget::EmptyWasteBottleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmptyWasteBottleWidget)
	, m_isPerfusionSystemLiquid(false)
	, m_instr(Instrument::instance())
	, m_instrState(InstrumentStateModel::instance())
	, m_progressDialog(new ProgressDialog(this))
{
    ui->setupUi(this);
	ui->btnPerfusionSystemLiquid->setVisible(false);
}

EmptyWasteBottleWidget::~EmptyWasteBottleWidget()
{
    delete ui;
}
void EmptyWasteBottleWidget::on_btnPerfusionSystemLiquid_clicked()
{
	return;
	auto state = m_instrState->getMachineState();
	if (!state.canRun)
	{
		//QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("��ǰ״̬���������У����Ƚ��г�ʼ������"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1411"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
//	m_instr->maintain(eSystemLiquidIrrigate);
	m_progressDialog->exec();
	state = m_instrState->getMachineState();

	if (state.state == InstrumentStateModel::enumStandby)
	{
		//ui->lblHint->setText(tr("��עϵͳҺ�壡<br/>״̬:<b style=\"color:blue;\">����ɹ�ע</b>"));
		//m_isIrrigate = true;
	}
	else
	{
		//ui->lblHint->setText(tr("��עϵͳҺ�壡<br/>״̬:<b style=\"color:red;\">��עʧ��</b>"));
		//m_isIrrigate = false;
	}
}
