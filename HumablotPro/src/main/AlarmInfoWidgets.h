#pragma once

#include <QWidget>
#include "ui_AlarmInfoWidgets.h"

class AlarmInfoWidgets : public QWidget
{
	Q_OBJECT

public:
	AlarmInfoWidgets(QWidget *parent ,QString file_name);
	~AlarmInfoWidgets();
public slots:
	//pushButton
	void on_pushButton_clicked();

private:
	Ui::AlarmInfoWidgets ui;
	void InitTableWidget(QString condition);
	void InitTableWidgetBorder();
	void addContent(int row, int column, QString content);
public:
	QString mFileName;
};
