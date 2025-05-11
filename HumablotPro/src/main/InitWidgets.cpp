#include "..\include\precomp\precompile.h"
#include "InitWidgets.h"
#include <QMessageBox>
#include <string>
#include <QDateTime>
#include "../Include/Instrument/Instrument.h"

InitWidgets::InitWidgets(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

InitWidgets::~InitWidgets()
{
}
void InitWidgets::on_pushButtonInit_clicked()
{
	//Instrument::instance()->connect()
	auto ret = QMessageBox::information(this, tr("提示"), tr("确定是否要初始化"), tr("是"), tr("否"));
	if (ret != 0)
	{
		//emit sglInitFinish();
	}
	else
	{

	}
}
