#include "PrepareReagentDialog.h"
#include "ui_PrepareReagentDialog.h"
#include "SelectProcessDialog.h"
#include <QMessageBox>
#include "src/comm/CustomButton.h"
#include "src/comm/GlobalData.h"
#include "../PrepareReagentWidget.h"
#include "../../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

PrepareReagentDialog::PrepareReagentDialog(PrepareReagentWidget *reagentWidget, QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::PrepareReagentDialog)
  ,_isCloseBtn(false)
  ,_reagentWidget(reagentWidget)
{
    ui->setupUi(this);
    connect(_reagentWidget,&PrepareReagentWidget::sglPumpStateChanged,this,[this](){
        emit sglPumpStateChange();
    });
	ui->btnSmall->setVisible(false);
	ui->btnBig->setVisible(false);

	//auto dao = AnalysisUIDao::instance();
	//bool bResult;
	//g_language_type = dao->SelectTargetValue(&bResult, "20005");

	//QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1074");
	//ui->label_14->setText("");
	
}

void PrepareReagentDialog::on_btnSmall_clicked()
{
	//m_flushing_type = 1;
	_reagentWidget->m_flushing_type = 1;
	//_reagentWidget->on_btnSmall_clicked();

	centerDisplay();
	auto btns = _reagentWidget->getBtnGroup()->buttons();
	for (auto btn : btns)
	{
		ui->hLayPump->addWidget(btn);
	}
	//updatePumpBtnByTest();
}

void PrepareReagentDialog::on_btnBig_clicked()
{
	_reagentWidget->m_flushing_type = 0;
	//_reagentWidget->on_btnBig_clicked();
	centerDisplay();
	auto btns = _reagentWidget->getBtnGroup()->buttons();
	for (auto btn : btns)
	{
		ui->hLayPump->addWidget(btn);
	}
	//_reagentWidget->on_btnBig_clicked();
	//updatePumpBtnByTest();
}


PrepareReagentDialog::~PrepareReagentDialog()
{
    delete ui;
}

void PrepareReagentDialog::showEvent(QShowEvent *)
{
    centerDisplay();    
    auto btns=_reagentWidget->getBtnGroup()->buttons();
    for(auto btn:btns)
    {
        ui->hLayPump->addWidget(btn);
    }

	auto empty = ":/images/buttonIcon/irrigationIconSmall.png";
	//auto empty = ":/images/buttonIcon/q555.png";
	QImage image(empty);
	//ui->pumpLB1_1->setPixmap(QPixmap::fromImage(image));
	QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ui->pushButtonSmall->setIcon(QIcon(fitpixmap));
}

void PrepareReagentDialog::setSelectProcessDialog(SelectProcessDialog *widget)
{


    _reagentWidget->setSelectPDialog(widget);
    _reagentWidget->updatePumpBtnByTest();

}

void PrepareReagentDialog::on_pushButtonClose_clicked()
{
    _isCloseBtn=true;
    hide();
}

void PrepareReagentDialog::on_btnConfig_clicked()
{
    _isCloseBtn=false;
    hide();
}

bool PrepareReagentDialog::getIsCloseBtn() const
{
    return _isCloseBtn;
}

void PrepareReagentDialog::on_pushButtonSmall_clicked()
{
	_reagentWidget->m_flushing_type = 1;
	//_reagentWidget->on_btnSmall_clicked();

	centerDisplay();
	auto btns = _reagentWidget->getBtnGroup()->buttons();
	for (auto btn : btns)
	{
		ui->hLayPump->addWidget(btn);
	}
	_reagentWidget->changeIcon(_reagentWidget->_flushFile, PumpPosState::enumFlush);
}

void PrepareReagentDialog::on_btnFlash_clicked()
{
	_reagentWidget->m_flushing_type = 0;
//	_reagentWidget->on_btnBig_clicked();
	centerDisplay();
	auto btns = _reagentWidget->getBtnGroup()->buttons();
	for (auto btn : btns)
	{
		ui->hLayPump->addWidget(btn);
	}
     _reagentWidget->changeIcon(_reagentWidget->_flushFile,PumpPosState::enumFlush);
}

void PrepareReagentDialog::on_btnReady_clicked()
{
    _reagentWidget->changeIcon(_reagentWidget->_readyFile,PumpPosState::enumReady);
}

void PrepareReagentDialog::on_btnDelay_clicked()
{
    _reagentWidget->changeIcon(_reagentWidget->_delayFile,PumpPosState::enumDelay);
}
