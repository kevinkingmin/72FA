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
	//��д��ʱ�����¼�   �麯�� ������д������麯��
	//virtual void timerEvent(QTimerEvent *);
	//int id1; //��ʱ��1��Ψһ��ʾ

	QString g_language_type = "";

private:
	Ui::WelcomWidgetsClass ui;
};
