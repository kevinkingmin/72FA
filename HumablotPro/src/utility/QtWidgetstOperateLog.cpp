#include "..\include\precomp\precompile.h"
#include "QtWidgetstOperateLog.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QtXml> //也可以include <QDomDocument>
#include <QFileDialog>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QLineEdit>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "../DAO/src/user/UserDao.h"
#include "src/comm/GlobalData.h"

QtWidgetstOperateLog::QtWidgetstOperateLog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QString sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1257");
	ui.label->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1151");
	ui.label_3->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1152");
	ui.label_4->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1154");
	ui.pushButtonQuery->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1258");
	ui.label_2->setText(sz1);


	//ui.tableWidgetOperateLog->
	//	ui.tableWidgetOperateLog_2->


	//K1250 | 模块名称 | 模块名称en
	//	K1251 | 机器序号 | 机器序号en
	//	K1252 | 操作内容 | 操作内容en
	//	K1253 | 操作员 | 操作员en
	//	K1254 | 操作时间 | 操作时间en


	QStringList headerString;
	QStringList headerString1;

	QString sz11 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1250");
	QString sz2 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1251");
	QString sz3 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1252");
	QString sz4 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1253");
	QString sz5 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1254");

	headerString << sz11 << sz2 << sz3 << sz4 << sz5;
	ui.tableWidgetOperateLog->setHorizontalHeaderLabels(headerString);

	//K1255 | 解决方案 | 解决方案en
	//	K1256 | 日志内容 | 日志内容en
	//	K1256 | 检验人 | 检验人en
	QString sz6 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1255");
	QString sz7 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1256");
	QString sz8 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1256");

	headerString1 << sz6 << sz2 << sz7<< sz5<< sz8;
	ui.tableWidgetOperateLog_2->setHorizontalHeaderLabels(headerString1);


	InitTableWidgetBorder();
	InitTableWidget("","");
	InitTableWidgetBorder1();
	InitTableWidget1("","");
}

QtWidgetstOperateLog::~QtWidgetstOperateLog()
{

}

void QtWidgetstOperateLog::InitTableWidget(QString start__time, QString end_time)
{
	int row = 0;
	bool bResult = true;
	auto dao = UserDao::instance();
	QString sql = "";
	if (start__time != "" && end_time != "")
	{
		sql = "select  * from t_operate_log where create_time>='" + start__time + " 00:00:00' and create_time<='" + end_time + " 23:59:59'  order by create_time DESC LIMIT 10000";
	}
	else
	{
		sql = "select  * from t_operate_log  order by create_time DESC LIMIT 10000";
	}
	QSqlQuery QueryList = dao->SelectRecord(&bResult, sql);
	while (QueryList.next())
	{
		QString alarmInfo = QueryList.value("model_name").toString();
		ui.tableWidgetOperateLog->insertRow(row);
		addContent(row, 0, alarmInfo);
		QString machine_id = QueryList.value("machine_id").toString();
		addContent(row, 1, machine_id);
		QString operate_content = QueryList.value("operate_content").toString();
		addContent(row, 2, operate_content);
		QString user_name = QueryList.value("user_name").toString();
		addContent(row, 3, user_name);
		QString create_time = QueryList.value("create_time").toString().replace(QString("T"), QString(" "));
		addContent(row, 4, create_time);
		row++;
	}
	//if (row > 0)
	//{
	//	//选中单元格 第一行：
	//	ui.tableWidgetOperateLog->setCurrentCell(0, 0, QItemSelectionModel::Select);
	//}
	//ui.tableWidgetOperateLog->resizeColumnToContents(2);
	//ui.tableWidgetOperateLog->horizontalHeader()->setStretchLastSection(true);
	//ui.tableWidgetOperateLog->setAlternatingRowColors(true); // 隔行变色
	//ui.tableWidgetOperateLog->setPalette(QPalette(Qt::gray)); // 设置隔行变色的颜色  gray灰色
	if (row > 0)
	{
		//选中单元格 第一行：
		//ui.tableWidgetOperateLog->setCurrentCell(0, 0, QItemSelectionModel::Select);
	}
	//ui.tableWidgetOperateLog->resizeColumnToContents(2);
	//ui.tableWidgetOperateLog->horizontalHeader()->setStretchLastSection(true);
	//ui.tableWidgetOperateLog->setAlternatingRowColors(true); // 隔行变色
	//ui.tableWidgetOperateLog->setPalette(QPalette(Qt::gray)); // 设置隔行变色的颜色  gray灰色

	//ui.tableWidgetOperateLog->setEditTriggers(QAbstractItemView::AllEditTriggers);
	//ui.tableWidgetOperateLog->setSelectionBehavior(QAbstractItemView::SelectRows);
	//ui.tableWidgetOperateLog->setSelectionMode(QTableView::SingleSelection);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
	//ui.tableWidgetOperateLog->setAlternatingRowColors(true);
}

void QtWidgetstOperateLog::InitTableWidgetBorder()
{
	//不显示左边默认自带序列号
	QHeaderView* headerView = ui.tableWidgetOperateLog->verticalHeader();
	headerView->setHidden(true);
	//使行列头自适应宽度，最后一列将会填充空白部分
	//ui.tableWidgetOperateLog->horizontalHeader()->setStretchLastSection(true);
	//ui.tableWidgetOperateLog->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	//ui.tableWidgetOperateLog->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
	ui.tableWidgetOperateLog->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//ui.tableWidgetAlarmInfo->setSectionResizeMode(0, QHeaderView.ResizeToContents)
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
	//ui.tableWidgetOperateLog->setAlternatingRowColors(true);
	//> resizeColumnToContents(2);
	//ui.tableWidgetAlarmInfo->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	//ui.tableWidgetOperateLog->setSortingEnabled(false);

	//ui.tableWidgetOperateLog->resizeColumnToContents(2);
	//ui.tableWidgetOperateLog->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidgetOperateLog->setAlternatingRowColors(true); // 隔行变色
	ui.tableWidgetOperateLog->setPalette(QPalette(Qt::gray)); // 设置隔行变色的颜色  gray灰色
	//ui.tableWidgetOperateLog->setEditTriggers(QAbstractItemView::AllEditTriggers);
	//ui.tableWidgetOperateLog->setSelectionBehavior(QAbstractItemView::SelectRows);
	////ui->tvSampleSet->setSelectionMode(QTableView::SingleSelection);
	//ui.tableWidgetOperateLog->setSelectionMode(QTableView::SingleSelection);
	//ui.tableWidgetOperateLog_2->horizontalHeader()->setStretchLastSection(true);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
	//ui.tableWidgetOperateLog->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
	//ui.tableWidgetOperateLog->setAlternatingRowColors(true);
	//ui.tableWidgetOperateLog->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑
	ui.tableWidgetOperateLog->setColumnWidth(0, 380);
	ui.tableWidgetOperateLog->setColumnWidth(1, 453);
	ui.tableWidgetOperateLog->setColumnWidth(2, 453);
	ui.tableWidgetOperateLog->setColumnWidth(3, 340);
	ui.tableWidgetOperateLog->setColumnWidth(4, 200);

	//ui.tableWidgetOperateLog->setColumnWidth(5, 80);


}

void QtWidgetstOperateLog::addContent(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	ui.tableWidgetOperateLog->setItem(row, column, item);
}

void QtWidgetstOperateLog::InitTableWidget1(QString start__time, QString end_time)
{
	int row = 0;
	bool bResult = true;
	auto dao = UserDao::instance();
	QString sql = "";
	if (start__time != "" && end_time != "")
	{
		sql = "select  * from t_run_log  where create_time>='" + start__time + " 00:00:00' and create_time<='" + end_time + " 23:59:59'  order by create_time DESC LIMIT 10000";
	}
	else
	{
		sql = "select  * from t_run_log   order by create_time DESC LIMIT 10000";
	}
	QSqlQuery QueryList = dao->SelectRecord(&bResult, sql);
	while (QueryList.next())
	{
		QString alarmInfo = QueryList.value("solution_name").toString();
		ui.tableWidgetOperateLog_2->insertRow(row);
		addContent1(row, 0, alarmInfo);
		QString machine_id = QueryList.value("machine_UID").toString();
		addContent1(row, 1, machine_id);
		QString operate_content = QueryList.value("tip_info").toString();
		addContent1(row, 2, operate_content);
		QString create_time = QueryList.value("create_time").toString().replace(QString("T"), QString(" "));
		addContent1(row, 3, create_time);
		QString user_name = QueryList.value("login_name").toString();
		addContent1(row, 4, user_name);
		row++;
	}

	if (row == 0)
	{
		return;
	}

	if (row > 0)
	{
		//选中单元格 第一行：
		//ui.tableWidgetOperateLog_2->setCurrentCell(0, 0, QItemSelectionModel::Select);
	}
	ui.tableWidgetOperateLog_2->resizeColumnToContents(2);
	ui.tableWidgetOperateLog_2->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidgetOperateLog_2->setAlternatingRowColors(true); // 隔行变色
	ui.tableWidgetOperateLog_2->setPalette(QPalette(Qt::gray)); // 设置隔行变色的颜色  gray灰色

	ui.tableWidgetOperateLog_2->setEditTriggers(QAbstractItemView::AllEditTriggers);
	ui.tableWidgetOperateLog_2->setSelectionBehavior(QAbstractItemView::SelectRows);
	//ui->tvSampleSet->setSelectionMode(QTableView::SingleSelection);
	ui.tableWidgetOperateLog_2->setSelectionMode(QTableView::SingleSelection);
	//ui.tableWidgetOperateLog_2->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidgetOperateLog_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	ui.tableWidgetOperateLog_2->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	ui.tableWidgetOperateLog_2->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	ui.tableWidgetOperateLog_2->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
	ui.tableWidgetOperateLog_2->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
	ui.tableWidgetOperateLog_2->setAlternatingRowColors(true);
	ui.tableWidgetOperateLog_2->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑

}

void QtWidgetstOperateLog::InitTableWidgetBorder1()
{
	//不显示左边默认自带序列号
	QHeaderView* headerView = ui.tableWidgetOperateLog_2->verticalHeader();
	headerView->setHidden(true);
	//使行列头自适应宽度，最后一列将会填充空白部分
	ui.tableWidgetOperateLog_2->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidgetOperateLog_2->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	ui.tableWidgetOperateLog_2->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
	ui.tableWidgetOperateLog_2->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑
	ui.tableWidgetOperateLog_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//ui.tableWidgetAlarmInfo->setSectionResizeMode(0, QHeaderView.ResizeToContents)
	//ui.tableWidgetOperateLog_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	//ui.tableWidgetOperateLog_2->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	//ui.tableWidgetOperateLog_2->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Custom);


	//> resizeColumnToContents(2);
	//ui.tableWidgetAlarmInfo->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	//ui.tableWidgetAlarmInfo->setSortingEnabled(false);
}

void QtWidgetstOperateLog::addContent1(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	ui.tableWidgetOperateLog_2->setItem(row, column, item);
}

void QtWidgetstOperateLog::on_pushButtonQuery_clicked()
{

	//ui.tableWidgetOperateLog_2->clear();
	//ui.tableWidgetOperateLog->clear();

	while (ui.tableWidgetOperateLog_2->rowCount() != 0) {
		ui.tableWidgetOperateLog_2->removeRow(0);
	}

	while (ui.tableWidgetOperateLog->rowCount() != 0) {
		ui.tableWidgetOperateLog->removeRow(0);
	}

	//InitTableWidgetBorder();
	//InitTableWidgetBorder1();

	//Show_UI_Data();
	QString start_time = ui.dateEdit->text();
	QString end_time = ui.dateEdit_2->text();

	InitTableWidgetBorder();
	InitTableWidget(start_time, end_time);

	InitTableWidgetBorder1();
	InitTableWidget1(start_time, end_time);
}
