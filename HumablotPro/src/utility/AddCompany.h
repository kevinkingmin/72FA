#pragma once

#include <QWidget>
#include "ui_AddCompany.h"

class AddCompany : public QWidget
{
	Q_OBJECT

public:
	AddCompany(QWidget *parent = Q_NULLPTR);
	~AddCompany();

private:
	Ui::AddCompany ui;

	bool Save_Company();

private slots:
	void on_pushButton_Save_clicked();
	void on_pushButton_Cancel_clicked();


signals:
	void SetRefresh(bool bFlag);

};
