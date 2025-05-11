#pragma once

#include <QWidget>
#include "ui_TubeManage.h"
#include <QSqlQuery>

class TubeManage : public QWidget
{
	Q_OBJECT

public:
	TubeManage(QWidget *parent = Q_NULLPTR);
	~TubeManage();

private:
	Ui::TubeManage ui;
    QSqlQuery m_TubeQuery;
	void InitTableWidget();
	void addContent(int row, int column, QString content);

private slots:
	void on_Add_Button_clicked();
	void on_Modify_Button_clicked();
	void on_Delete_Button_clicked();

	void on_Export_Button_clicked();
	void on_Inport_Button_clicked();

	void getRefreshTableWidgetFlag(bool bFlag);

};
