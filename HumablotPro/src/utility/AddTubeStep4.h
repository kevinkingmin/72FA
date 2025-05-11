#pragma once

#include <QWidget>
#include "ui_AddTubeStep4.h"

class AddTubeStep4 : public QWidget
{
	Q_OBJECT

public:
	AddTubeStep4(QWidget *parent = Q_NULLPTR);
	~AddTubeStep4();


	QString m_strTube_ID;
	QString m_Name;
	QString m_IsControl;
	QString m_Inner;
	QString m_LiquidStartPos;
	QString m_CupHeight;

	void Set_UI();

private:
	Ui::AddTubeStep4 ui;

private slots:
	void on_pushButton_Back_clicked();
	void on_pushButton_Save_clicked();
	void on_pushButton_Cancel_clicked();

signals:
	void SetCancel(bool bFlag);
};
