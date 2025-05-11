#include "..\Include\Precomp\precompile.h"
#include "FromLisByIntervalWidgets.h"

#include <QMessageBox>
#include <QIntValidator>
#include "src/comm/GlobalData.h"

FromLisByIntervalWidgets::FromLisByIntervalWidgets(QWidget *parent)
	: BaseDialog(parent),
	ui(new Ui::FromLisByIntervalWidgets)
{
	//ui.setupUi(this);
	ui->setupUi(this);
	ui->lineEditStart->setText("2022-06-14");
	ui->lineEdit_End->setText("2022-06-14");
	//ui->lineEdit_End->t
}

//FromLisByIntervalWidgets::FromLisByIntervalWidgets(QWidget *parent) :
//	BaseDialog(parent),
//	ui(new Ui::RepeatSetDialog)
//	, _sampleNo("")
//	, m_data(nullptr)
//	, _posAndCountMap{}
//{
//	ui->setupUi(this);
//	initUi();
//}

void FromLisByIntervalWidgets::on_pushButtonOK_clicked()
{
	//lineEditStart
		//lineEdit_End
	QString start = ui->lineEditStart->text();//.Text();
	QString end = ui->lineEdit_End->text();// Text();
	emit sglQueryCondition(start,end);
	this->hide();
}

void FromLisByIntervalWidgets::on_pushButtonCancel_clicked()
{
	this->hide();
}

FromLisByIntervalWidgets::~FromLisByIntervalWidgets()
{
	delete ui;
}
