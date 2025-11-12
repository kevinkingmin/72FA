#pragma once

#include <QDialog>
#include "ui_AddReagent.h"
#include <QSqlQuery>
#include "../Include/Model/reagent/ReagentModel.h"

class AddReagent : public QDialog
{
	Q_OBJECT

public:
    AddReagent(QWidget *parent = Q_NULLPTR);
	~AddReagent();
private slots:
    void on_pushButton_Save_clicked();
    void on_pushButton_Cancel_clicked();

public:
    void setCompanyName(const QString &companyName);
    void Set_UI();
public:
    QString m_strCompany_ID;
    bool m_bModify = false;
    QString m_strReagent_ID;
//    QString m_language_code;
//    QString m_reagent_name1; //= "";
private:
    Ui::AddReagent ui;
    QString m_companyName;
    ReagentModel _reagent;

};
