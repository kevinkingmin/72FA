#pragma once
//#include <QWidget>
#include <QMainWindow>
#include "ui_TestResultDataManage.h"
#include "../sample/TestResultDetailDialog.h"
//#include "../sample/"
#include "../sample/ShowTestResultDetail.h"

class TestResultDataManage : public QWidget
{
	Q_OBJECT

public:
	TestResultDataManage(QWidget *parent = Q_NULLPTR);
	~TestResultDataManage();
	QString m_test_project_name;
	void Show_UI_Data();

public slots:
	void slotUpdateStatus(QString a ,QString b);
signals:
	void sglUpdateStatus(QString a, QString b);
private:
	Ui::TestResultDataManage ui;
	//表格
	ShowTestResultDetail *mytable;
	//对话框
	TestResultDetailDialog *dialog;
	//初始化列表
	//void InitTableWidget();
	/*给项目列表单元格添加内容*/
	//void addContent(int row, int column, QString content, int nColor = 0);


};
