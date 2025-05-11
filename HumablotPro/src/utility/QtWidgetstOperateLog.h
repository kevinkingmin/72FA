#pragma once

#include <QWidget>
#include "ui_QtWidgetstOperateLog.h"

class QtWidgetstOperateLog : public QWidget
{
	Q_OBJECT

public:
	QtWidgetstOperateLog(QWidget *parent = nullptr);
	~QtWidgetstOperateLog();

private:
	Ui::QtWidgetstOperateLogClass ui;

	void InitTableWidget(QString start__time,QString end_time);
	void InitTableWidgetBorder();
	void addContent(int row, int column, QString content);

	void InitTableWidget1(QString start__time, QString end_time);
	void InitTableWidgetBorder1();
	void addContent1(int row, int column, QString content);
private slots:
	void on_pushButtonQuery_clicked();
};
