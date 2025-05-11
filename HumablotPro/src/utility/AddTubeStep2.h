#pragma once

#include <QWidget>
#include "ui_AddTubeStep2.h"

class AddTubeStep2 : public QWidget
{
	Q_OBJECT

public:
	AddTubeStep2(QWidget *parent = Q_NULLPTR);
	~AddTubeStep2();

	QString m_strTube_ID;
	QString m_Name;
	QString m_IsControl;
	QString m_Inner;
	QString m_LiquidStartPos;
	QString m_CupHeight;

	void Set_UI();

private:
	Ui::AddTubeStep2 ui;

private slots:
	void getCancelSignal(bool bFlag);
	void on_pushButton_Back_clicked();
	void on_pushButton_Next_clicked();
	void on_pushButton_Cancel_clicked();

signals:
	void SetCancel(bool bFlag);
};
