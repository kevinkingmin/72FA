#include "UtilityWidget.h"
#include "ui_UtilityWidget.h"
#include "maintain/MaintainCmdWidget.h"

UtilityWidget::UtilityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UtilityWidget)
{
    ui->setupUi(this);
    initUi();
}

UtilityWidget::~UtilityWidget()
{
    delete ui;
}

void UtilityWidget::setMaintainShow()
{
    ui->btnMaintain->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tabMantain->setCurrentIndex(0);
    ui->tabMantain->show();
}

void UtilityWidget::initUi()
{
    _MaintainCmdWidget=new MaintainCmdWidget(this);

    ui->btnMaintain->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tabMantain->addTab(_MaintainCmdWidget,"维护指令");
    ui->tabMantain->addTab(new QWidget(this),"维护列表");


	_SystemSet = new SystemSet(this);
    ui->tabSystemSet->addTab(_SystemSet,"系统参数");

	_TestPaperManage = new TestPaperManage(this);
	ui->tabItemSet->addTab(_TestPaperManage, "膜条管理");

	_ReagentManager = new ReagentManager(this);
	ui->tabItemSet->addTab(_ReagentManager, "试剂管理");

	_TubeManage = new TubeManage(this);
	ui->tabItemSet->addTab(_TubeManage, "样本管管理");
	//ui->tabItemSet->addTab(_TubeManage, "报告管理");

	_ResultManage = new ResultManage(this);
	ui->tabItemSet->addTab(_ResultManage, "报告管理");

}

void UtilityWidget::on_btnMaintain_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tabMantain->show();
}

void UtilityWidget::on_btnSystemSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tabSystemSet->show();
}

void UtilityWidget::on_btnItemSet_clicked()
{
	ui->stackedWidget->setCurrentIndex(2);
	ui->tabSystemSet->show();
}
