#pragma once
#ifndef MANUALINCUBATIONWIDGETS_H
#define MANUALINCUBATIONWIDGETS_H
#include "src/comm/BaseDialog.h"

#include <QWidget>
#include "ui_ManualIncubationWidgets.h"
#include <QTimer>

class Instrument;

class ManualIncubationWidgets : public BaseDialog
{
	Q_OBJECT 

public:
	ManualIncubationWidgets(QWidget *parent = nullptr);
	~ManualIncubationWidgets();
private slots:
	void doProcessTimeout();

	void on_btnStartIncubation_clicked();
	void on_btnIncubationFinish_clicked();


public:
	Instrument *m_instr;
	QTimer *myTimer;//计时器，头文件include

	int index;//倒计时数字
	int mNeed_incubation_times;

private:
	Ui::ManualIncubationWidgetsClass *ui;
};
#endif 