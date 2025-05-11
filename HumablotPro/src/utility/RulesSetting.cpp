#include "..\include\precomp\precompile.h"
#include "RulesSetting.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QtXml> //也可以include <QDomDocument>
#include<QFileDialog>
#include "src/comm/Global.h"
#include "src/comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Instrument/Instrument.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QLineEdit>
#include "src/main/subDialog/MyMessageBox.h"


RulesSetting::RulesSetting(QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_ShowModal, true);
	ui.setupUi(this);

	auto dao = AnalysisUIDao::instance();
	bool bResult;
	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");


	_instr = Instrument::instance();
    //QString nMachineUID = _instr->get_machine_no();
    QString nMachineUID = "_instr->get_machine_no()";
	m_strMachineUID = nMachineUID;// QString("%1").arg(nMachineUID, 2, 10, QChar('0'));//.Format("%08d", nMachineUID);
	InitRulesTableWidget();
	InitRuleValuesTableWidget();
	//QRegExpValidator validator(QRegExp("[0-9.]+"));  // 设置正则表达式匹配规则
	//ui.lineEditGrayValue->setValidator(&validator);  // 应用验证器
	QRegExpValidator* validator = new QRegExpValidator(QRegExp("[-+]?[0-9]*\\.?[0-9]+"), ui.lineEditGrayValue);
	ui.lineEditGrayValue->setValidator(validator);

	//QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1188");
	//ui.label->setText(sz);
	//sz = GlobalData::LoadLanguageInfo(g_language_type, "K1188");

	QStringList headerString;
	QStringList headerString1;
	QString sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1187");
	QString sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1215");
	QString sz3 = GlobalData::LoadLanguageInfo(g_language_type, "K1216");
	headerString << sz3;
	ui.tableWidget_Rule->setHorizontalHeaderLabels(headerString);
	
	headerString1 << "NO"<<sz1 << sz2;
	ui.tableWidget_Rules->setHorizontalHeaderLabels(headerString1);

	QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1188");
	ui.label_2->setText(sz1);
	sz = GlobalData::LoadLanguageInfo(g_language_type, "K1188");
	ui.label_3->setText(sz2);
	sz = GlobalData::LoadLanguageInfo(g_language_type, "K1108");
	ui.Add_Button->setText(sz);
	sz = GlobalData::LoadLanguageInfo(g_language_type, "K1109");
	ui.Modify_Button->setText(sz);
	sz = GlobalData::LoadLanguageInfo(g_language_type, "K1140");
	ui.Delete_Button->setText(sz);

	sz = GlobalData::LoadLanguageInfo(g_language_type, "K1022");
	//
	ui.label->setText(sz);

}

RulesSetting::~RulesSetting()
{
}

void RulesSetting::InitRuleValuesTableWidget()
{
	//不显示左边默认自带序列号
	QHeaderView* headerView = ui.tableWidget_Rules->verticalHeader();
	headerView->setHidden(true);

	//使行列头自适应宽度，最后一列将会填充空白部分
	ui.tableWidget_Rules->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_Rules->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	ui.tableWidget_Rules->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
	ui.tableWidget_Rules->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑
	ui.tableWidget_Rules->setSortingEnabled(false);

	//隔行变色
	ui.tableWidget_Rules->setAlternatingRowColors(true);
	//去掉网格线
	ui.tableWidget_Rules->setShowGrid(false);
}

void RulesSetting::InitRulesTableWidget()
{
	ui.tableWidget_Rule->setRowCount(0);
	//不显示左边默认自带序列号
	QHeaderView* headerView = ui.tableWidget_Rule->verticalHeader();
	headerView->setHidden(true);
	//使行列头自适应宽度，最后一列将会填充空白部分
	ui.tableWidget_Rule->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_Rule->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	ui.tableWidget_Rule->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
	ui.tableWidget_Rule->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑
	QString itemName;
	//DB中取Testitems表数据
	bool bResult = true;
	auto dao = AnalysisUIDao::instance();
	m_RuleNameQuery = dao->SelectRulues(&bResult);
	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1275"), MyMessageBox::Ok,"OK","");
		return;
	}
	int row = 0;
	while (m_RuleNameQuery.next())
	{
		itemName = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), m_RuleNameQuery.value("RuleName").toString());//m_RuleNameQuery.value("RuleName").toString();
		ui.tableWidget_Rule->insertRow(row);
		addRuleContent(row, 0, itemName);
		row++;
	}

	if (row > 0)
	{
		/*设置让某个单元格或某行选中*/
		//选中单元格 第一行：
		ui.tableWidget_Rule->setCurrentCell(0, 0, QItemSelectionModel::Select);
	}

	//隔行变色
	ui.tableWidget_Rule->setAlternatingRowColors(true);
	//去掉网格线
	ui.tableWidget_Rule->setShowGrid(false);
}

void RulesSetting::addRuleContent(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	ui.tableWidget_Rule->setItem(row, column, item);
}

void RulesSetting::on_tableWidget_Rule_cellClicked()
{
	//清空列表
	ui.tableWidget_Rules->setRowCount(0);
	int intRow = ui.tableWidget_Rule->currentRow();//获取选中的行
	if (m_RuleNameQuery.size() == 0)
		return;
	m_RuleNameQuery.seek(intRow);
	m_strRule_ID = m_RuleNameQuery.value("pkid").toInt();
	ShowTableWidget_Rules();
}
void RulesSetting::ShowTableWidget_Rules()
{
	//清空列表
	ui.tableWidget_Rules->setRowCount(0);
	QString strValue;
	bool bResult = true;
	auto dao = AnalysisUIDao::instance();
	QString sql = "";
	sql.sprintf("select * from t_judge_rules where RulesId =%d order by GrayValue asc", m_strRule_ID);
	m_RuleValuesQuery = dao->SelectRecord(&bResult, sql);
	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1263"), MyMessageBox::Ok,"OK","");
		return;
	}
	if (m_RuleValuesQuery.size() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "数据库表中缺少测试膜条数据！", QMessageBox::Ok);
		return;
	}
	int row = 0;
	QString sID = "0";
	while (m_RuleValuesQuery.next())
	{
		ui.tableWidget_Rules->insertRow(row);
		//ID
		sID = QString::number(row + 1);
		addRulesContent(row, 0, sID);
		//名称
		strValue = m_RuleValuesQuery.value("GrayValue").toString();
		addRulesContent(row, 1, strValue);
		//货号
		strValue = m_RuleValuesQuery.value("GrayWord").toString();
		addRulesContent(row, 2, strValue);
		row++;
	}
	if (row > 0)
	{
		/*设置让某个单元格或某行选中*/
		//选中单元格 第一行：
		ui.tableWidget_Rules->setCurrentCell(0, 0, QItemSelectionModel::Select);
        on_tableWidget_Rules_cellClicked();
	}
}
void RulesSetting::addRulesContent(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	ui.tableWidget_Rules->setItem(row, column, item);
}

void RulesSetting::on_tableWidget_Rules_cellClicked()
{
	int intRow = ui.tableWidget_Rules->currentRow();//获取选中的行
	if (m_RuleValuesQuery.size() == 0)
		return;
	m_RuleValuesQuery.seek(intRow);
	m_strRuleValues_ID = m_RuleValuesQuery.value("pkid").toString();
	GrayValue = m_RuleValuesQuery.value("GrayValue").toString();
	GrayWord = m_RuleValuesQuery.value("GrayWord").toString();
	ui.lineEditGrayValue->setText(GrayValue);
	ui.lineEditGrayWord->setText(GrayWord);
		//ui.lineEditGrayWord
}
void RulesSetting::on_Add_Button_clicked()
{
	//int cols = ui.tableWidget_Rules->columnCount();
	//int rows = ui.tableWidget_Rules->rowCount();
	//ui.tableWidget_Rules->insertRow(rows);
	//for (int i = 0; i < cols; i++)
	//{
	//	ui.tableWidget_Rules->setItem(rows, i, new QTableWidgetItem("new" + QString::number(rows)));
	//}
	//ui.tableWidget_Rules->selectRow(rows);

	//int nMachineUID = Instrument::instance()->get_components()->get_reagentmodule()->GetMachineUID();
	//CString strMachineUID;
	//strMachineUID.Format("%08d", nMachineUID);
	//strMachineUID = _T("HumablotPro") + strMachineUID + _T(" : ");
	//CString strLog = strMachineUID + text;

	QString grayValue = ui.lineEditGrayValue->text();
	QString grayWord = ui.lineEditGrayWord->text();


	if (m_strRule_ID == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1293"), MyMessageBox::Ok,"OK","");
		return;
	}


	if (grayValue == "")
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1298"), MyMessageBox::Ok,"OK","");
		ui.lineEditGrayValue->setFocus();
		return;
	}

	if (grayWord == "")
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1297"), MyMessageBox::Ok,"OK","");
		ui.lineEditGrayWord->setFocus();
		return;
	}

	if (grayWord.length() == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1297"), MyMessageBox::Ok,"OK","");
		ui.lineEditGrayWord->setFocus();
		return;
	}

	auto dao = AnalysisUIDao::instance();

	bool bResult = true;
	QString sql_select = QString("select * from  t_judge_rules where RulesId=%1 and GrayValue=%2 and GrayWord='%3'").arg(m_strRule_ID).arg(grayValue).arg(grayWord);

	QSqlQuery select_gray_value = dao->SelectRecord(&bResult, sql_select);

	while (select_gray_value.next())
	{
		QString strValue = select_gray_value.value("GrayValue").toString();
		QString strValue1 = select_gray_value.value("GrayWord").toString();
		if (strValue == grayValue)
		{
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1303") ,MyMessageBox::Ok,"OK","");
			return;
		}
		if (strValue1 == grayWord)
		{
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1302"), MyMessageBox::Ok,"OK","");
			return;
		}
	}

	QString select_sql = QString("select * from t_judge_rules where GrayWord='%1' and RulesId=%2").arg(grayWord).arg(m_strRule_ID);

	QSqlQuery ResultQuery = dao->SelectRecord(&bResult, select_sql);
	int size = ResultQuery.size();

	if (size > 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1295"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}

	m_strMachineUID = Global::g_machine_no;

	QString sql1 = QString("insert into t_judge_rules(RulesId,GrayValue,GrayWord)values(%1,%2,'%3')").arg(m_strRule_ID).arg(grayValue).arg(grayWord);

	QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1658")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1660")).arg(GlobalData::getLoginName1());

	dao->SelectRecord(&bResult, sql1_log);
	m_RuleValuesQuery = dao->SelectRecord(&bResult, sql1);
	if (!bResult)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1301"), MyMessageBox::Ok,"OK","");
		return;
	}
	else
	{
		//刷新界面
		ShowTableWidget_Rules();
	}
}
void RulesSetting::on_Modify_Button_clicked()
{

	if (m_strRuleValues_ID == "")
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1300"), MyMessageBox::Ok,"OK","");
		return;
	}
	//m_strRuleValues_ID
	int ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1299"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
	if (ret== MyMessageBox::No)
	{
		return;
	}

	if (m_strRule_ID == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1293"), MyMessageBox::Ok,"OK","");
		return;
	}



	QString grayValue = ui.lineEditGrayValue->text();
	QString grayWord = ui.lineEditGrayWord->text();

	if (grayValue == "")
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1298"), MyMessageBox::Ok,"OK","");
		ui.lineEditGrayValue->setFocus();
		return;
	}

	if (grayWord == "")
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1297"), MyMessageBox::Ok,"OK","");
		ui.lineEditGrayWord->setFocus();
		return;
	}

	int word_length = grayWord.trimmed().length();

	if (word_length == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1297"), MyMessageBox::Ok,"OK","");
		ui.lineEditGrayWord->setFocus();
		return;
	}

	m_strMachineUID = Global::g_machine_no;

	bool bResult = true;
	QString sql = "";
	sql.sprintf("update t_judge_rules set GrayValue=%f,GrayWord='%s' where pkid =%d ", grayValue.toDouble(), grayWord, m_strRuleValues_ID.toInt());
	QString sql1 = QString("update t_judge_rules set GrayValue=%1,GrayWord='%2' where pkid =%3 ").arg(grayValue).arg(grayWord).arg(m_strRuleValues_ID);
	QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1658")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1668")).arg(GlobalData::getLoginName1());
	
	QString select_sql = QString("select * from t_judge_rules where GrayWord='%1' and RulesId=%2").arg(grayWord).arg(m_strRule_ID);

	QString select_sql_grayValue = QString("select * from t_judge_rules where GrayValue=%1 and RulesId=%2").arg(grayValue).arg(m_strRule_ID);

	auto dao = AnalysisUIDao::instance();

	QSqlQuery ResultQuery_grayValue = dao->SelectRecord(&bResult, select_sql_grayValue);
	int size_grayValue = ResultQuery_grayValue.size();
	if (size_grayValue > 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1296"), MyMessageBox::Ok, "OK","");
		return;
	}

	QSqlQuery ResultQuery = dao->SelectRecord(&bResult, select_sql);
	int size = ResultQuery.size();
	if (size > 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1295"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}

	dao->SelectRecord(&bResult, sql1_log);
	m_RuleValuesQuery = dao->SelectRecord(&bResult, sql1);
	if (!bResult)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1294"), MyMessageBox::Ok,"OK","");
		return;
	}
	else
	{
		//刷新界面
		ShowTableWidget_Rules();
	}
}
void RulesSetting::on_Delete_Button_clicked()
{
	if (m_strRuleValues_ID == "")
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1293"), MyMessageBox::Ok,"OK","");
		return;
	}
	//m_strRuleValues_ID
	int ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1292"), MyMessageBox::Ok| MyMessageBox::No,"YES", "NO");
	if (ret== MyMessageBox::No)
	{
		return;
	}

	m_strMachineUID = Global::g_machine_no;

	bool bResult = true;
	QString sql = "";
	sql.sprintf("delete from t_judge_rules where pkid =%d ", m_strRuleValues_ID.toInt());
	QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1658")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1662")).arg(GlobalData::getLoginName1());
	auto dao = AnalysisUIDao::instance();
	dao->SelectRecord(&bResult, sql1_log);
	m_RuleValuesQuery = dao->SelectRecord(&bResult, sql);
	if (!bResult)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1291"), MyMessageBox::Ok,"OK","");
		return;
	}
	else
	{
		//刷新界面
		ShowTableWidget_Rules();
	}
}
