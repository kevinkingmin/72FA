#pragma once

#include <QDialog>
#include "ui_AddProcess.h"
#include <QSqlQuery>

class AddProcess : public QDialog
{
	Q_OBJECT

public:
    AddProcess(QWidget *parent = Q_NULLPTR);
    ~AddProcess();
private slots:
    void on_pushButton_Save_clicked();
    void on_pushButton_Cancel_clicked();

public:
    void setStrCompany_ID(const QString &strCompany_ID);

private:
    Ui::AddProcess ui;
    QString m_strCompany_ID;
    bool m_bModify;
};
