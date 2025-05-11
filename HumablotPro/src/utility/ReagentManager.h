#pragma once

#include <QWidget>
#include "ui_ReagentManager.h"
#include <QSqlQuery>

class Instrument;

class ReagentManager : public QWidget
{
	Q_OBJECT

public:
	ReagentManager(QWidget *parent = Q_NULLPTR);
	~ReagentManager();

private:
	Ui::ReagentManager ui;

	QString m_strCompany_ID;
	QString m_strReagent_ID;
    QSqlQuery m_CompanyQuery;
    QSqlQuery m_ReagentQuery;
	QString m_strMachineUID;
	Instrument * _instr;
	void InitCompanyTableWidget();
	void InitReagentTableWidget();

	void addCompanyContent(int row, int column, QString content);
	void addReagentContent(int row, int column, QString content);

private slots:
	void on_tableWidget_Company_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	void on_tableWidget_Company_cellClicked();
	void on_tableWidget_Reagent_cellClicked();

	void on_Add_Button_clicked();
	void on_Modify_Button_clicked();
	void on_Delete_Button_clicked();

	void getRefreshTableWidgetFlag(bool bFlag);
	void getRefreshCompanyTableWidgetFlag(bool bFlag);

public:
	QString g_language_type = "";

};
