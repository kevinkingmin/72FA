//#include "..\Include\Precomp\precompile.h"
#include "HMessagebox.h"

HMessagebox::HMessagebox(QWidget *parent, MsgBoxType type, QString text) : QDialog(parent)
{
	initState();

	if (type == MsgBoxType_Info)
	{
		initInfo(text);
	}
	else if (type == MsgBoxType_Warn)
	{
		initWarn(text);
	}
	else
	{
		initError(text);
	}

}

void HMessagebox::initState()
{
	this->resize(240, 160);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

	this->setStyleSheet("background-color:rgb(46,47,48)");

	labPic = new QLabel(this);
	labNote = new QLabel(this);
	btnSure = new QPushButton("确认", this);
	btnCancle = new QPushButton("取消", this);

	connect(btnSure, &QPushButton::clicked, this, &HMessagebox::dealbtnSureClicked);
	connect(btnCancle, &QPushButton::clicked, this, &HMessagebox::dealbtnCancelClicked);
}

void HMessagebox::initWarn(const QString &text)
{
	int width = this->width();

	labPic->setStyleSheet("image:url(:/image/msg_question.png)");
	labPic->setGeometry(width*0.5 - 20, 10, 40, 40);

	labNote->setStyleSheet("color:white");
	labNote->setAlignment(Qt::AlignCenter);
	labNote->setGeometry(0, 70, width, 20);
	labNote->setText(text);

	btnSure->setGeometry(width*0.2 - 15, 110, 80, 30);
	btnSure->setStyleSheet("QPushButton{color:white; border-radius: 5px; background-color:rgb(43,34,45)}"
		"QPushButton:hover{background-color:blue}"
		"QPushButton:pressed{background-color:blue}");

	btnCancle->setGeometry(width*0.6, 110, 80, 30);
	btnCancle->setStyleSheet("QPushButton{color:white; border-radius: 5px; background-color:rgb(43,34,45)}"
		"QPushButton:hover{background-color:blue}"
		"QPushButton:pressed{background-color:blue}");

}

void HMessagebox::initError(const QString &text)
{
	int width = this->width();

	labPic->setStyleSheet("image:url(:/image/msg_error.png)");
	labPic->setGeometry(width*0.5 - 20, 10, 40, 40);

	labNote->setStyleSheet("color:white");
	labNote->setAlignment(Qt::AlignCenter);
	labNote->setGeometry(0, 70, width, 20);
	labNote->setText(text);

	btnSure->setGeometry(width*0.5 - 40, 110, 80, 30);
	btnSure->setStyleSheet("QPushButton{color:white; border-radius: 5px; background-color:rgb(43,34,45)}"
		"QPushButton:hover{background-color:blue}"
		"QPushButton:pressed{background-color:blue}");

	btnCancle->hide();
}

void HMessagebox::initInfo(const QString &text)
{
	int width = this->width();

	labPic->setStyleSheet("image:url(:/image/msg_info.png)");
	labPic->setGeometry(width*0.5 - 20, 10, 40, 40);

	labNote->setStyleSheet("color:white");
	labNote->setAlignment(Qt::AlignCenter);
	labNote->setGeometry(0, 70, width, 20);
	labNote->setText(text);

	btnSure->setGeometry(width*0.5 - 40, 110, 80, 30);
	btnSure->setStyleSheet("QPushButton{color:white; border-radius: 5px; background-color:rgb(43,34,45)}"
		"QPushButton:hover{background-color:blue}"
		"QPushButton:pressed{background-color:blue}");

	btnCancle->hide();
}

void HMessagebox::dealbtnSureClicked()
{
	this->accept();
}

void HMessagebox::dealbtnCancelClicked()
{
	this->reject();
}
