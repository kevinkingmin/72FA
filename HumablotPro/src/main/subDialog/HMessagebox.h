//#pragma once
//class HMessagebox
//{
//};

#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QString>

enum MsgBoxType
{
	MsgBoxType_Warn = 0,
	MsgBoxType_Info = 1,
	MsgBoxType_Error = 2
};

// ����MessageBox  ���ܺ� windows�����Ķ����ظ� ����Լ��޸���������
class HMessagebox : public QDialog
{
	Q_OBJECT
public:
	explicit HMessagebox(QWidget *parent, MsgBoxType type, QString text);

	void initState();

	void initWarn(const QString &text);
	void initError(const QString &text);
	void initInfo(const QString &text);

signals:

public slots:
	void dealbtnSureClicked();
	void dealbtnCancelClicked();

private:
	QLabel *labPic;
	QLabel *labNote;
	QPushButton *btnSure;
	QPushButton *btnCancle;
};

#endif // MESSAGEBOX_H


