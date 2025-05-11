#pragma once

#include <QWidget>
#include "ui_TestResultDataOneType.h"
#include "../sample/TestResultDetailDialog.h"
#include "../sample/ShowTestResultDetail.h"

class TestResultDataOneType : public QWidget
{
	Q_OBJECT

public:
	TestResultDataOneType(QWidget *parent = Q_NULLPTR);
	~TestResultDataOneType();

	QString m_test_project_name;

	int m_nTestPaperID;

	void Show_UI_Data();

	int pic_width = 850;
	int pic_height = 50;

private:
	Ui::TestResultDataOneType ui;

	int m_nImageColumnWidth = 0;
	int m_nLargerColumnWidth = 0;

	void InitTableWidget_H();

	void InitTableWidget_Data();

	/*给项目列表单元格添加内容*/
	void addContent_H(int row, int column, QString content, int nColor = 0);

	void addContent_Data(int row, int column, QString content, int nColor = 0);

	//表格
	ShowTestResultDetail *mytable;
	//对话框
	TestResultDetailDialog *dialog;
private slots:
	void on_tableWidget_Data_cellClicked(int row, int column); 
	void getItemDataSlot(int row);
	//更新TestResult table
	void UpdateTestResultTableOneTypeSlot(QString testId);
};
