#pragma once

#include <QWidget>
#include "ui_InitWidgets.h"

class InitWidgets : public QWidget
{
	Q_OBJECT

public:
	InitWidgets(QWidget *parent = Q_NULLPTR);
	~InitWidgets();


private:
	Ui::InitWidgets ui;
private slots:
	void on_pushButtonInit_clicked();
//signals:
//	void sglInitFinish();
};
