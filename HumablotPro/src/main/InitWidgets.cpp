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
	auto ret = QMessageBox::information(this, tr("��ʾ"), tr("ȷ���Ƿ�Ҫ��ʼ��"), tr("��"), tr("��"));
	if (ret != 0)
	{
		//emit sglInitFinish();
	}
	else
	{

	}
}
