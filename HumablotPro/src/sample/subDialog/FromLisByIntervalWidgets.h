#pragma once
#ifndef LISREQUESTDIALOG_H
#define LISREQUESTDIALOG_H
#include "src/comm/BaseDialog.h"

#include <QWidget>
#include "ui_FromLisByIntervalWidgets.h"
namespace Ui {
	class FromLisByIntervalWidgets;
}
class FromLisByIntervalWidgets : public BaseDialog
{
	Q_OBJECT

signals:
	//查询值改变 
	void QueryValueChange(QString confition);
	void sglQueryCondition(QString confition1, QString confition2);

public slots:
	void on_pushButtonOK_clicked();
	void on_pushButtonCancel_clicked();
public:
	FromLisByIntervalWidgets(QWidget *parent = Q_NULLPTR);
	~FromLisByIntervalWidgets();
	QString QueryInterval();

private:
	Ui::FromLisByIntervalWidgets *ui;

};
#endif // LISREQUESTDIALOG_H