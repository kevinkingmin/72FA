#pragma once

#include <QWidget>
#include "ui_RulesSetting.h"
#include <QSqlQuery>
#include <QSqlTableModel>

class Instrument;

class RulesSetting : public QWidget
{
	Q_OBJECT

public:
	RulesSetting(QWidget *parent = Q_NULLPTR);
	~RulesSetting();
	void ShowTableWidget_Rules();
private slots:
	//void on_tableWidget_Company_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	void on_tableWidget_Rule_cellClicked();
	void on_tableWidget_Rules_cellClicked();
	void on_Add_Button_clicked();
	void on_Modify_Button_clicked();
	void on_Delete_Button_clicked();

private:
	Ui::RulesSetting ui;
	int m_strRule_ID;
	QString m_strMachineUID;
	int pkid;
	QString m_strRuleValues_ID;
	QString GrayValue;
	QString GrayWord;
	QSqlQuery m_RuleNameQuery;
	QSqlQuery m_RuleValuesQuery;

	Instrument * _instr;
	void InitRulesTableWidget();
	void InitRuleValuesTableWidget();
	void addRuleContent(int row, int column, QString content);
	void addRulesContent(int row, int column, QString content);
public:
	QString g_language_type = "";

};
