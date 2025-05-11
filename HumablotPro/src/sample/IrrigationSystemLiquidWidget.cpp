#include "IrrigationSystemLiquidWidget.h"
#include "ui_IrrigationSystemLiquidWidget.h"
#include <QMessageBox>
#include <QTimer>
#include "src/main/subDialog/ProgressDialog.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/BLL/baseSet/InstrumentParasSetBLL.h"
#include "../Include/Model/baseSet/InstrumentParasSetModel.h"
#include "../Include/Model/baseSet/CommonType.h"
#include "src/comm/Global.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "src/comm/GlobalData.h"

IrrigationSystemLiquidWidget::IrrigationSystemLiquidWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IrrigationSystemLiquidWidget)
  ,m_isIrrigate(false)
  ,m_instr(Instrument::instance())
  ,m_instrState(InstrumentStateModel::instance())
{
    ui->setupUi(this);
	//ui->btnFill->setVisible(false);
	//emit ChangeBtnNextSignal(false); //btn tmp
	m_jump_irrigate = 1;
}

IrrigationSystemLiquidWidget::~IrrigationSystemLiquidWidget()
{
    delete ui;
}

void IrrigationSystemLiquidWidget::on_btnIrrigate_clicked()
{
    return;   
}

bool IrrigationSystemLiquidWidget::getIsIrrigate() const
{
    return m_isIrrigate;
}

void IrrigationSystemLiquidWidget::showEvent(QShowEvent *)
{
	if (m_isIrrigate)
	{
		if (m_jump_irrigate == 2)
		{
			ui->lblHint->setText(tr("灌注系统液体！<br/>状态:<b style=\"color:blue;\">跳过灌注</b>"));
		}
		else
		{
			ui->lblHint->setText(tr("灌注系统液体！<br/>状态:<b style=\"color:blue;\">已完成灌注</b>"));
		}

		auto empty = ":/images/buttonIcon/rReady.png";
		QImage image(empty);
		//ui->pumpLB1_1->setPixmap(QPixmap::fromImage(image));
		QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		ui->btnIrrigate->setIcon(QIcon(fitpixmap));
		//ui->btnIrrigate->setProperty(GlobalData::getPropertyName(), PumpPosState::enumEmpty);
		ui->btnIrrigate->setIconSize(QSize(image.width(), image.height()));


		Global::g_SystemLiquidPerfusion = 1;
		emit ChangeBtnNextSignal(true);
	}
    else
    {
        ui->lblHint->setText(tr("灌注系统液体！<br/>状态:<b style=\"color:red;\">没有灌注</b>"));
		Global::g_SystemLiquidPerfusion = 0;
		//emit ChangeBtnNextSignal(false); //btn tmp
		//emit ChangeBtnNextSignal(true);
    }
}

void IrrigationSystemLiquidWidget::on_btnWash_clicked()
{
    auto state = m_instrState->getMachineState();
    if (!state.canRun)
    {
        //QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("当前状态不允许运行，请先进行初始化操作"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1411"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
        return;
    }
    //m_instr->maintain(eSystemLiquidWash);
	m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1615"));
    //m_progressDialog->setHead(tr("正在清洗,请稍候......"));
    m_progressDialog->exec();
    state = m_instrState->getMachineState();
    if(state.state==InstrumentStateModel::enumStandby)
    {
		auto empty = ":/images/buttonIcon/rReady.png";
		QImage image(empty);
		//ui->pumpLB1_1->setPixmap(QPixmap::fromImage(image));
		QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		ui->btnIrrigate->setIcon(QIcon(fitpixmap));
		//ui->btnIrrigate->setProperty(GlobalData::getPropertyName(), PumpPosState::enumEmpty);
		ui->btnIrrigate->setIconSize(QSize(image.width(), image.height()));

        ui->lblHint->setText(tr("灌注系统液体！<br/>状态:<b style=\"color:blue;\">已完成灌注</b>"));
        m_isIrrigate=true;
		Global::g_SystemLiquidPerfusion = 1;
		emit ChangeBtnNextSignal(true);
		ui->btnWash->setChecked(true);
    }
    else
    {
		auto empty = ":/images/buttonIcon/irrigationIcon.png";
		QImage image(empty);
		//ui->pumpLB1_1->setPixmap(QPixmap::fromImage(image));
		QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		ui->btnIrrigate->setIcon(QIcon(fitpixmap));
		//ui->btnIrrigate->setProperty(GlobalData::getPropertyName(), PumpPosState::enumEmpty);
		ui->btnIrrigate->setIconSize(QSize(image.width(), image.height()));
        ui->lblHint->setText(tr("灌注系统液体！<br/>状态:<b style=\"color:red;\">灌注失败</b>"));
        m_isIrrigate=false;
		m_jump_irrigate = 1;
		//emit ChangeBtnNextSignal(false); //btn tmp
		ui->btnWash->setChecked(false);
    }
}

void IrrigationSystemLiquidWidget::on_btnFill_clicked()
{
	m_isIrrigate = true;
	emit ChangeBtnNextSignal(true);
	m_jump_irrigate = 2;

	auto empty = ":/images/buttonIcon/rReady.png";
	QImage image(empty);
	//ui->pumpLB1_1->setPixmap(QPixmap::fromImage(image));
	QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ui->btnIrrigate->setIcon(QIcon(fitpixmap));
	//ui->btnIrrigate->setProperty(GlobalData::getPropertyName(), PumpPosState::enumEmpty);
	ui->btnIrrigate->setIconSize(QSize(image.width(), image.height()));
	ui->lblHint->setText(tr("灌注系统液体！<br/>状态:<b style=\"color:blue;\">跳过灌注</b>"));
  //  auto state = m_instrState->getMachineState();
  //  if (!state.canRun)
  //  {
  //      QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("当前状态不允许运行，请先进行初始化操作"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
  //      return;
  //  }
  //  m_instr->maintain(eSystemLiquidIrrigate);
  //  m_progressDialog->setHead(tr("正在冲灌,请稍候......"));
  //  m_progressDialog->exec();
  //  state = m_instrState->getMachineState();

  //  if(state.state==InstrumentStateModel::enumStandby)
  //  {
  //      ui->lblHint->setText(tr("灌注系统液体！<br/>状态:<b style=\"color:blue;\">已完成灌注</b>"));
  //      m_isIrrigate=true;
		//Global::g_SystemLiquidPerfusion = 1;
  //  }
  //  else
  //  {
  //      ui->lblHint->setText(tr("灌注系统液体！<br/>状态:<b style=\"color:red;\">灌注失败</b>"));
  //      m_isIrrigate=false;
  //  }
}

void IrrigationSystemLiquidWidget::setProgressDialog(ProgressDialog *progressDialog)
{
    m_progressDialog = progressDialog;
}
