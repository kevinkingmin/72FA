#pragma once

#include <QWidget>
#include "ui_ResultDetail.h"

class ResultDetail : public QWidget
{
	Q_OBJECT

public:
	ResultDetail(QWidget *parent = Q_NULLPTR);
	~ResultDetail();

private:
	Ui::ResultDetail ui;
};
