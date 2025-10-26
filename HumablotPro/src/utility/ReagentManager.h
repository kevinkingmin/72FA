#pragma once

#include <QWidget>
#include "ui_ReagentManager.h"
#include <QSqlQuery>
#include "../Include/Model/baseSet/CompanyModel.h"

class Instrument;

class ReagentManager : public QWidget
{
	Q_OBJECT
public:
	ReagentManager(QWidget *parent = Q_NULLPTR);
	~ReagentManager();

private:
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
	void getRefreshCompanyTableWidgetFlag(bool bFlag);
private:
    Ui::ReagentManager ui;
    QString m_strCompany_ID;
    QString m_strReagent_ID;
    QVector<CompanyModel> _companyModels;
    QSqlQuery m_ReagentQuery;
    QString m_strMachineUID;
    Instrument * _instr;
    QString m_companyName;
};
