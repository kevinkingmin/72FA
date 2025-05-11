#pragma once

#include <QWidget>
#include "ui_AddTubeStep3.h"

class AddTubeStep3 : public QWidget
{
	Q_OBJECT

public:
	AddTubeStep3(QWidget *parent = Q_NULLPTR);
	~AddTubeStep3();


	QString m_strTube_ID;
	QString m_Name;
	QString m_IsControl;
	QString m_Inner;
	QString m_LiquidStartPos;
	QString m_CupHeight;

	void Set_UI();

private:
	Ui::AddTubeStep3 ui;

private slots:
	void getCancelSignal(bool bFlag);
	void on_pushButton_Back_clicked();
	void on_pushButton_Next_clicked();
	void on_pushButton_Cancel_clicked();

signals:
	void SetCancel(bool bFlag);
};
