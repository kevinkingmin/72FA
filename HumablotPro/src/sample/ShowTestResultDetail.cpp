#include "..\include\precomp\precompile.h"
#include "ShowTestResultDetail.h"
//引入表头视图
#include <QHeaderView>
#include <QPushButton>

ShowTestResultDetail::ShowTestResultDetail(QWidget *parent)
	: QTableWidget(parent)
{
	setColumnCount(9);//设置列数
	setRowCount(10);//设置行数
	//表头
	setHorizontalHeaderLabels(QStringList() << "编号" << "姓名" << "年龄"<< "受教育程度" << "民族"<< "专业" << "职称" << "部门" << "职务");
	//表头单元格背景色和字体
	setStyleSheet(QString("QTableWidget QHeaderView::section{background:#2a9ee4;font-weight:bold;}"));
	horizontalHeader()->setStretchLastSection(true);//设置表格的列随窗口拉伸
	verticalHeader()->hide();//隐藏竖直表头
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //表格列宽自适应
	setSelectionBehavior(QAbstractItemView::SelectRows);//单击选择类型为行
	setEditTriggers(QAbstractItemView::NoEditTriggers);//禁用表格双击修改
}

ShowTestResultDetail::~ShowTestResultDetail()
{
}
