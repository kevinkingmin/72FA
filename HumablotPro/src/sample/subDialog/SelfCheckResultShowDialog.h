#pragma once

#include <QDialog>
#include "ui_SelfCheckResultShowDialog.h"

class SelfCheckResultShowDialog : public QDialog
{
	Q_OBJECT

public:
	SelfCheckResultShowDialog(QWidget *parent = nullptr);
	~SelfCheckResultShowDialog();
    void ShowSelfCheckInfo();
public slots:
	void on_pushButton_clicked();
public:
	QString g_language_type = "";

private:
	Ui::SelfCheckResultShowDialogClass ui;
};
