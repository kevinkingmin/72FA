#pragma once
#include <QWidget>
#include "ui_AddTubeStep1.h"
class AddTubeStep1 : public QWidget
{
	Q_OBJECT
public:
	AddTubeStep1(QWidget *parent = Q_NULLPTR);
	~AddTubeStep1();
	QString m_strTube_ID;
	QString m_LiquidStartPos;
	QString m_CupHeight;
	void Set_UI();
private:
	Ui::AddTubeStep1 ui;

private slots:
	void getCancelSignal(bool bFlag);
	void on_pushButton_Back_clicked();
	void on_pushButton_Next_clicked();
	void on_pushButton_Cancel_clicked();
signals:
	void SetRefresh(bool bFlag);
};
