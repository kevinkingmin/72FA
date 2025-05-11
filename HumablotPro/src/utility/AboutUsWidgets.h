#pragma once

#include <QWidget>
#include "ui_AboutUsWidgets.h"
class Instrument;
class AboutUsWidgets : public QWidget
{
	Q_OBJECT

public:
	AboutUsWidgets(QWidget *parent = nullptr);
	~AboutUsWidgets();
public slots:
	void slotIsStepSuc(int ret);
private:
	Ui::AboutUsWidgetsClass ui;
private:
	Instrument  *_instrument;
};
