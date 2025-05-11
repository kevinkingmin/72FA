#include "..\include\precomp\precompile.h"
#include "AlarmInfoWidgets.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QtXml>
#include<QFileDialog>
#include "src/comm/GlobalData.h"
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

AlarmInfoWidgets::AlarmInfoWidgets(QWidget *parent,QString fileName)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.tableWidgetAlarmInfo->setRowCount(0);
	ui.dateEdit->setDisplayFormat("yyyyMMdd");
	ui.dateEdit->setDateTime(QDateTime::currentDateTime());

	InitTableWidgetBorder();
	QString start_time = ui.dateEdit->text();
	InitTableWidget(start_time);
	if (fileName == "")
	{
		fileName = "instrument.log";
	}
	mFileName = fileName;

	InitTableWidget(start_time);
}

AlarmInfoWidgets::~AlarmInfoWidgets()
{

}

void AlarmInfoWidgets::on_pushButton_clicked()
{
	QString start_time = ui.dateEdit->text();
	InitTableWidget(start_time);
}

void AlarmInfoWidgets::InitTableWidget(QString condition)
{
	QString strExePath = QDir::currentPath();
	QDateTime time = QDateTime::currentDateTime();
	QString str = "";
	if (condition == "")
	{
		str = time.toString("yyyyMMdd");//("yyyy-MM-dd hh:mm:ss");
	}
	else
	{
		str = condition;
	}

	QString filePath = QString("%1/log/%2/%3").arg(strExePath).arg(str).arg(mFileName);

	QFile file(filePath);
	if (!file.open(QIODevice::ReadWrite)) {
	}
	int row = 0;
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		QString str(line);
		QStringList strs = str.split("]");
		QString occurTime = "";
		QString alarmInfo = "";
		if (strs.length() > 0)
		{
			occurTime = strs.at(0);//strs[strs.length - 1];
			alarmInfo = QString("%1").arg(strs.at(strs.length() - 1));//strs[strs.length - 1];
		}
		ui.tableWidgetAlarmInfo->insertRow(row);
		addContent(row, 0, QString::number(row));
		addContent(row, 1, occurTime.mid(1,-1));
		alarmInfo = alarmInfo.simplified();;
		addContent(row, 2, alarmInfo);
		row++;
		//qDebug() << str;
	}
	if (row > 0)
	{

	}
	ui.tableWidgetAlarmInfo->resizeColumnToContents(2);
	ui.tableWidgetAlarmInfo->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidgetAlarmInfo->setAlternatingRowColors(true); // 
	ui.tableWidgetAlarmInfo->setPalette(QPalette(Qt::gray)); // 
}

void AlarmInfoWidgets::InitTableWidgetBorder()
{
	QHeaderView* headerView = ui.tableWidgetAlarmInfo->verticalHeader();
	headerView->setHidden(true);
	ui.tableWidgetAlarmInfo->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidgetAlarmInfo->setSelectionBehavior(QAbstractItemView::SelectRows); 
	ui.tableWidgetAlarmInfo->setSelectionMode(QAbstractItemView::SingleSelection); 
	ui.tableWidgetAlarmInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidgetAlarmInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidgetAlarmInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	ui.tableWidgetAlarmInfo->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	ui.tableWidgetAlarmInfo->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Custom);
}

void AlarmInfoWidgets::addContent(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	ui.tableWidgetAlarmInfo->setItem(row, column, item);
}