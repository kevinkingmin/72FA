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
	//定时器第一种方式
	//启动定时器   每隔1s调用一下timerEvent函数
	//id1 = startTimer(1000); //参数1  间隔  单位 毫秒
	////定时器第二种方式
	//QTimer * timer = new QTimer(this);
	////启动定时器
	//timer->start(1000);
	//connect(timer, &QTimer::timeout, [=]() {
	//	static int num = 1;
	//	num++;
	//	//关闭窗口
	//	if (num == 10)
	//	{
	//		//timer->stop();
	//		//this->close();//close();
	//	}
	//	//label4 每隔0.5秒+1
	//});



	//ui.label->setText("追  求  诊  断  之  臻\r\nMake Diagnostics Better");
	//ui.label->setStyleSheet("QLabel{"
	//	"background-image:url(:/images/background/welcome_bj1.png);"
	//	"background-position:top right;"
	//	"background-origin:content;"
	//	"background-repeat:none;"
	//	"font:bold 30pt;"
	//	"font-family:宋体;"
	//	"font: normal 34px 宋体;"
	//	"color: rgb(0, 0, 0, 190);"
	//	"}");

	//:/images/background/welcome_bj1.png

	ui.label->setText("Make  Diagnostics  Better");
	ui.label->setStyleSheet("QLabel{"
	"background-position:top right;"
	"background-origin:content;"
	"background-repeat:none;"
	"font:bold 5pt;"
	"font-family:黑体;"
	"font: normal 27px 黑体;"
	"color: rgb(11 11, 11, 190);"
	"}");


	ui.label_2->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1013"));// "追求诊断之臻");

	ui.label_2->setStyleSheet("QLabel{"
		"background-position:top right;"
		"background-origin:content;"
		"background-repeat:none;"
		"font:bold 45pt;"
		"font-family:楷体;"
		"font: normal 60px 楷体;"
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
//		//label2 每隔1秒+1
//		//ui->label_2->setText(QString::number(num++));
//	}
//}
