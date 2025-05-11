#pragma once

#include <QDialog>
#include "ui_ShowImageDialog.h"

class ShowImageDialog : public QDialog
{
	Q_OBJECT

public:
	ShowImageDialog(QWidget *parent = nullptr);
	~ShowImageDialog();
	void ShowPicInfo();

public slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();

private:
	Ui::ShowImageDialogClass ui;
public:
	//0,1为拍照成功，2为失败
	int m_camera_check_status = 0;


};
