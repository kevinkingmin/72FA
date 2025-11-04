#pragma once

#include <QWidget>
#include "ui_SystemSet.h"

class ProcessParaWidgets;

class SystemSet : public QWidget
{
	Q_OBJECT
public:
	SystemSet(QWidget *parent = Q_NULLPTR);
	~SystemSet();
private:
	Ui::SystemSet ui;
signals:
    void sglProcessAction(const QString &companyName,const QString &companyId);
private slots:
	void on_pushButton_Save_clicked();
	void on_pushButton_Cancel_clicked();
	void on_pushButton_Test_clicked();
    void on_pushButtonPara_clicked();
    // 公司选择的信号槽
    void onCompanyComboBoxChanged(const QString &text);
};
