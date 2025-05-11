#pragma once

#include <QWidget>
#include <QDialog>
#include "ui_ProcessParaWidgets.h"

class ProcessParaWidgets : public QDialog
{
	Q_OBJECT

public:
	ProcessParaWidgets(QWidget *parent = nullptr);
	~ProcessParaWidgets();

private:
	Ui::ProcessParaWidgetsClass ui;
public:
	QString g_language_type;
};
