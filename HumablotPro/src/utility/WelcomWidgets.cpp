#include "..\include\precomp\precompile.h"
#include "WelcomWidgets.h"
#include <QTimer>
#include "../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

WelcomWidgets::WelcomWidgets(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	auto dao = AnalysisUIDao::instance();
	bool bResult;
	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
	//��ʱ����һ�ַ�ʽ
	//������ʱ��   ÿ��1s����һ��timerEvent����
	//id1 = startTimer(1000); //����1  ���  ��λ ����
	////��ʱ���ڶ��ַ�ʽ
	//QTimer * timer = new QTimer(this);
	////������ʱ��
	//timer->start(1000);
	//connect(timer, &QTimer::timeout, [=]() {
	//	static int num = 1;
	//	num++;
	//	//�رմ���
	//	if (num == 10)
	//	{
	//		//timer->stop();
	//		//this->close();//close();
	//	}
	//	//label4 ÿ��0.5��+1
	//});



	//ui.label->setText("׷  ��  ��  ��  ֮  ��\r\nMake Diagnostics Better");
	//ui.label->setStyleSheet("QLabel{"
	//	"background-image:url(:/images/background/welcome_bj1.png);"
	//	"background-position:top right;"
	//	"background-origin:content;"
	//	"background-repeat:none;"
	//	"font:bold 30pt;"
	//	"font-family:����;"
	//	"font: normal 34px ����;"
	//	"color: rgb(0, 0, 0, 190);"
	//	"}");

	//:/images/background/welcome_bj1.png

	ui.label->setText("Make  Diagnostics  Better");
	ui.label->setStyleSheet("QLabel{"
	"background-position:top right;"
	"background-origin:content;"
	"background-repeat:none;"
	"font:bold 5pt;"
	"font-family:����;"
	"font: normal 27px ����;"
	"color: rgb(11 11, 11, 190);"
	"}");


	ui.label_2->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1013"));// "׷�����֮��");

	ui.label_2->setStyleSheet("QLabel{"
		"background-position:top right;"
		"background-origin:content;"
		"background-repeat:none;"
		"font:bold 45pt;"
		"font-family:����;"
		"font: normal 60px ����;"
		"color: rgb(11, 11, 11, 190);"
		"}");
	
}

WelcomWidgets::~WelcomWidgets()
{
	//delete ui;
}

//void WelcomWidgets::timerEvent(QTimerEvent * ev)
//{
//	if (ev->timerId() == id1)
//	{
//		static int num = 1;
//		//label2 ÿ��1��+1
//		//ui->label_2->setText(QString::number(num++));
//	}
//}
