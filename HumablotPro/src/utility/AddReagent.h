#pragma once

#include <QWidget>
#include "ui_AddReagent.h"
#include <QSqlQuery>

class AddReagent : public QWidget
{
	Q_OBJECT

public:
	AddReagent(QWidget *parent = Q_NULLPTR);
	~AddReagent();

	QString m_strCompany_ID;

	bool m_bModify = false;

	QString m_strReagent_ID;
	QString m_language_code;
	QString m_reagent_name1; //= "";

	void Set_UI();

private:
	Ui::AddReagent ui;

    QSqlQuery m_TestPaperQuery;

public:
	QString g_language_type = "";

private slots:
	void on_pushButton_Save_clicked();
	void on_pushButton_Cancel_clicked();

signals:
	void SetRefresh(bool bFlag);
};
