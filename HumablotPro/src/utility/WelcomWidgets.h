#pragma once

#include <QWidget>
#include "ui_WelcomWidgets.h"

class WelcomWidgets : public QWidget
{
	Q_OBJECT

public:
	WelcomWidgets(QWidget *parent = nullptr);
	~WelcomWidgets();

public:
	//重写定时器的事件   虚函数 子类重写父类的虚函数
	//virtual void timerEvent(QTimerEvent *);
	//int id1; //定时器1的唯一标示

	QString g_language_type = "";

private:
	Ui::WelcomWidgetsClass ui;
};
