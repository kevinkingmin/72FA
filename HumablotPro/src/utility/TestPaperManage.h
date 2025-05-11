#pragma once

#include <QWidget>
#include "ui_TestPaperManage.h"
#include <QSqlQuery>

class Instrument;

class TestPaperManage : public QWidget
{
	Q_OBJECT

public:
	TestPaperManage(QWidget *parent = Q_NULLPTR);
	~TestPaperManage();
public:
	QString g_language_type = "";

private:
	Ui::TestPaperManage ui;
	QString m_strCompany_ID;
	QString m_strTestPaper_ID;
    QSqlQuery m_CompanyQuery;
    QSqlQuery m_TestPaperQuery;
	Instrument * _instr;
	QString m_strMachineUID;
	void InitCompanyTableWidget();
	void InitTestPaperTableWidget();
	void addCompanyContent(int row, int column, QString content);
	void addTestPaperContent(int row, int column, QString content);
private slots:
	void on_tableWidget_Company_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	void on_tableWidget_Company_cellClicked();
	void on_tableWidget_TestPaper_cellClicked();
	void on_Add_Company_Button_clicked();
	void on_Delete_Company_Button_clicked();
	void on_Add_Button_clicked();
	void on_Modify_Button_clicked();
	void on_Delete_Button_clicked();
	void on_Delete_Button_2_clicked();
	void on_Export_Button_clicked();
	void on_Inport_Button_clicked();
	void on_Up_Sort_Button_2_clicked();
	void on_Down_Sort_Button_3_clicked();
	
	void getRefreshTableWidgetFlag(bool bFlag);
	void getRefreshCompanyTableWidgetFlag(bool bFlag);
};
