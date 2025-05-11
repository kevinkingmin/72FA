#pragma once

#include <QWidget>
#include "ui_LisSettingWidgets.h"
#include "../Include/TCPClient/TcpClient.h"
#include "WorkerThread.h"
class LisSettingWidgets : public QWidget
{
	Q_OBJECT

public:
	LisSettingWidgets(QWidget *parent = Q_NULLPTR);
	~LisSettingWidgets();

public:	
	void setTcpClient(TcpClient *tcpClient1);
private:
	Ui::LisSettingWidgets ui;
    TcpClient *m_tcpClient;
private slots:
	void on_pushButtonSave_clicked();
	void onSendClicked();
	void updateDisplay(const QString &data);
	void onConnectClicked();
	void slotConnectStatus(bool status);
	void on_pushButtonSend_clicked();

	void on_pushButtonSend_5_clicked();
	void on_pushButtonSend_2_clicked();
	void on_pushButtonSend_3_clicked();
	void on_pushButtonSend_4_clicked();
};
