#pragma once

#include <QDialog>
#include "ui_ShowAllPicWidgets.h"

class ShowAllPicWidgets : public QDialog
{
	Q_OBJECT

public:
	ShowAllPicWidgets(QWidget *parent = nullptr);
	~ShowAllPicWidgets();

private:
	Ui::ShowAllPicWidgetsClass ui;
public:
	void ShowPic(QString strPath);


};
