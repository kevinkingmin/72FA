#include "TestPaperManage.h"
#include "TestPaper.h"
#include "AddCompany.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QtXml> //也可以include <QDomDocument>
#include<QFileDialog>
#include "src/comm/GlobalData.h"
#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Instrument/Instrument.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

TestPaperManage::TestPaperManage(QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_ShowModal, true);
	ui.setupUi(this);

	auto dao = AnalysisUIDao::instance();
	bool bResult;

	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");

	InitCompanyTableWidget();
	InitTestPaperTableWidget();

	//ui.Add_Button->setVisible(false);
	_instr = Instrument::instance();

	//int nMachineUID = _instr->get_machine_no();
	//m_strMachineUID = QString("%1").arg(nMachineUID, 2, 10, QChar('0'));//.Format("%08d", nMachineUID);
	//
	ui.label->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1098"));
	ui.Inport_Button->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1106"));
	ui.Export_Button->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1107"));
	ui.Add_Button->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1108"));
	ui.Modify_Button->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1109"));
	ui.Delete_Button_2->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1104"));
	ui.Delete_Button->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1105"));
	//ui.tableWidget_TestPaper->hideColumn(3);
}

TestPaperManage::~TestPaperManage()
{
}

void TestPaperManage::InitTestPaperTableWidget()
{
	//不显示左边默认自带序列号
	QHeaderView* headerView = ui.tableWidget_TestPaper->verticalHeader();
	headerView->setHidden(true);
	//使行列头自适应宽度，最后一列将会填充空白部分
	ui.tableWidget_TestPaper->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_TestPaper->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	ui.tableWidget_TestPaper->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择模式，选择单行
	ui.tableWidget_TestPaper->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑
	ui.tableWidget_TestPaper->setSortingEnabled(false);
	//隔行变色
	ui.tableWidget_TestPaper->setAlternatingRowColors(true);
	//去掉网格线
	ui.tableWidget_TestPaper->setShowGrid(false);
	QStringList headerString;
	QString sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1100");
	QString sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1101");
	QString sz3 = GlobalData::LoadLanguageInfo(g_language_type, "K1102");
	QString sz4 = GlobalData::LoadLanguageInfo(g_language_type, "K1103");
	headerString << "NO"<<sz1<<sz2<<sz3<<sz4;
	ui.tableWidget_TestPaper->setHorizontalHeaderLabels(headerString);
	this->setWindowTitle(GlobalData::LoadLanguageInfo(g_language_type, "K1015"));
}

void TestPaperManage::InitCompanyTableWidget()
{
	ui.tableWidget_Company->setRowCount(0);
	//不显示左边默认自带序列号
	QHeaderView* headerView = ui.tableWidget_Company->verticalHeader();
	headerView->setHidden(true);
	//使行列头自适应宽度，最后一列将会填充空白部分
	ui.tableWidget_Company->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_Company->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	ui.tableWidget_Company->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择模式，选择单行
	ui.tableWidget_Company->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑
	//隔行变色
	ui.tableWidget_Company->setAlternatingRowColors(true);
	//去掉网格线
	ui.tableWidget_Company->setShowGrid(false);
	QStringList headerString;
	headerString << GlobalData::LoadLanguageInfo(g_language_type, "K1099");
	ui.tableWidget_Company->setHorizontalHeaderLabels(headerString);
	QString itemName;
	//DB中取Testitems表数据
	bool bResult = true;
    auto dao = AnalysisUIDao::instance();
	QString  loginName = GlobalData::getLoginName1();
	int company_id= Global::g_company_id;
	int group_id = GlobalData::getGruopId();
	//不是管理员,
	if (group_id == 3)
	{
		m_CompanyQuery = dao->SelectCompanysById(&bResult, company_id);
	}
	else
	{
		m_CompanyQuery = dao->SelectCompanys(&bResult);
	}
	if (bResult == false)
	{
		QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1111");
		QString sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1110");
		MyMessageBox::warning(this, sz, sz1, MyMessageBox::Ok, "OK", "");
		//MyMessageBox::warning(this, "错误", "检索测试膜条厂家失败！", MyMessageBox::Ok,"OK","");
		return;
	}
	int row = 0;
    while (m_CompanyQuery.next())
	{
        itemName = m_CompanyQuery.value("Name").toString();
		ui.tableWidget_Company->insertRow(row);
		addCompanyContent(row, 0, itemName);
		row++;
	}
	if (row > 0)
	{
		/*设置让某个单元格或某行选中*/
		//选中单元格 第一行：
		ui.tableWidget_Company->setCurrentCell(0, 0, QItemSelectionModel::Select);
	}
}

void TestPaperManage::addCompanyContent(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	ui.tableWidget_Company->setItem(row, column, item);
}

void TestPaperManage::addTestPaperContent(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	ui.tableWidget_TestPaper->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
	ui.tableWidget_TestPaper->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
	ui.tableWidget_TestPaper->setItem(row, column, item);
	ui.tableWidget_TestPaper->item(row, column)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void TestPaperManage::on_tableWidget_Company_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	on_tableWidget_Company_cellClicked();
}
void TestPaperManage::on_tableWidget_Company_cellClicked()
{
	//清空列表
	ui.tableWidget_TestPaper->setRowCount(0);
	int intRow = ui.tableWidget_Company->currentRow();//获取选中的行
    if (m_CompanyQuery.size() == 0)
		return;
    m_CompanyQuery.seek(intRow);
    m_strCompany_ID = m_CompanyQuery.value("ID").toString();
	QString strValue;
	bool bResult = true;
    auto dao = AnalysisUIDao::instance();
	m_TestPaperQuery = dao->SelectTestPapers(m_strCompany_ID,&bResult);
	if (bResult == false)
	{
		//QMessageBox::warning(this, "错误", "检索测试膜条数据失败!", QMessageBox::Ok);
		return;
	}
    if (m_TestPaperQuery.size() == 0)
	{
		//QMessageBox::warning(this, "错误", "数据库表中缺少测试膜条数据！", QMessageBox::Ok);
		return;
	}
	int row = 0;
    QString sID = "0";
    while (m_TestPaperQuery.next())
	{
		ui.tableWidget_TestPaper->insertRow(row);
		//ID
		sID = QString::number(row + 1);
		addTestPaperContent(row, 0, sID);
		//名称
        strValue = m_TestPaperQuery.value("PaperName").toString();
		addTestPaperContent(row, 1, strValue);
		//货号
		strValue = m_TestPaperQuery.value("articleNo").toString();
		addTestPaperContent(row, 2, strValue);
		strValue = m_TestPaperQuery.value("sort_idx").toString();
		addTestPaperContent(row, 3, strValue);
		strValue = m_TestPaperQuery.value("isDelete").toString();
		if (strValue == "0")
		{
			strValue = GlobalData::LoadLanguageInfo(g_language_type, "K1104");//"启用";
		}
		else
		{
			strValue = GlobalData::LoadLanguageInfo(g_language_type, "K1105");//"不启用";
		}
		addTestPaperContent(row, 4, strValue);
		row++;
	}
	if (row > 0)
	{
		/*设置让某个单元格或某行选中*/
		//选中单元格 第一行：
		ui.tableWidget_TestPaper->setCurrentCell(0, 0, QItemSelectionModel::Select);
	}
}
void TestPaperManage::on_Up_Sort_Button_2_clicked()
{
	//ui.tableWidget_TestPaper->
	QList<QTableWidgetItem*>items = ui.tableWidget_TestPaper->selectedItems();
	int row = ui.tableWidget_TestPaper->row(items.at(0));//获取选中的行
	//if (row == 0)
	//{
	//	QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条!", QMessageBox::Ok);
	//	return;
	//}
	auto dao = AnalysisUIDao::instance();
	int count = items.count();
	if (count < 2)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok,"OK","");
		return;
	}
	QString up_name1 = "";
	QString up_sort_id = "";
	int total_row = ui.tableWidget_TestPaper->rowCount();
	if (row == 0)
	{
		QTableWidgetItem* item_name_up = ui.tableWidget_TestPaper->item(total_row - 1, 1);
		QTableWidgetItem* item_sort_id_up = ui.tableWidget_TestPaper->item(total_row - 1, 3);
		up_name1 = item_name_up->text();
		up_sort_id = item_sort_id_up->text();
	}
	else
	{
		//上一膜条名称及编号
		QTableWidgetItem* item_name_up = ui.tableWidget_TestPaper->item(row - 1, 1);
		QTableWidgetItem* item_sort_id_up = ui.tableWidget_TestPaper->item(row - 1, 3);
		up_name1 = item_name_up->text();
		up_sort_id = item_sort_id_up->text();
	}
	if (count < 2)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok,"OK","");
		return;
	}
	QTableWidgetItem *item = items.at(1);
	QString name = item->text();//获取内容
	QTableWidgetItem *item1 = items.at(3);
	QString sort_idx = item1->text();//获取内容
	QString sql = "";
	QString sql1 = "";
	bool result = false;
	sql = QString("update t_testpaper set sort_idx=%0 where PaperName = '%1'").arg(up_sort_id).arg(name);
	dao->UpdateRecord(&result,sql);
	result = false;
	sql1 = QString("update t_testpaper set sort_idx=%0 where PaperName = '%1'").arg(sort_idx).arg(up_name1);
	dao->UpdateRecord(&result, sql1);
	on_tableWidget_Company_cellClicked();
	//for (int i = 0; i < count; i++)
	//{
	//	int row = ui.tableWidget_TestPaper->row(items.at(i));//获取选中的行
	//	QTableWidgetItem *item = items.at(i);
	//	QString name = item->text();//获取内容
	//}
}

void TestPaperManage::on_Down_Sort_Button_3_clicked()
{
	//ui.tableWidget_TestPaper->
	QList<QTableWidgetItem*>items = ui.tableWidget_TestPaper->selectedItems();
	int row = ui.tableWidget_TestPaper->row(items.at(0));//获取选中的行
	int total_row = ui.tableWidget_TestPaper->rowCount();
	//if (row == total_row-1)
	//{
	//	QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条!", QMessageBox::Ok);
	//	return;
	//}
	auto dao = AnalysisUIDao::instance();
	int count = items.count();
	QTableWidgetItem *item = items.at(1);
	if (count < 2)
	{
		//dQMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
		return;
	}
	QString down_name1 = "";
	QString down_sort_id = "";
	//int total_row = ui.tableWidget_TestPaper->rowCount();
	if (row == total_row-1)
	{
		QTableWidgetItem* item_name_up = ui.tableWidget_TestPaper->item(0, 1);
		QTableWidgetItem* item_sort_id_up = ui.tableWidget_TestPaper->item(0, 3);
		down_name1 = item_name_up->text();
		down_sort_id = item_sort_id_up->text();
	}
	else
	{
		//上一膜条名称及编号
		QTableWidgetItem* item_name_up = ui.tableWidget_TestPaper->item(row + 1, 1);
		QTableWidgetItem* item_sort_id_up = ui.tableWidget_TestPaper->item(row + 1, 3);
		down_name1 = item_name_up->text();
		down_sort_id = item_sort_id_up->text();
	}
	QString name = item->text();//获取内容
	QTableWidgetItem *item1 = items.at(3);
	QString sort_idx = item1->text();//获取内容
	QString sql = "";
	QString sql1 = "";
	sql = QString("update t_testpaper set sort_idx=%0 where PaperName = '%1'").arg(down_sort_id).arg(name);
	sql1 = QString("update t_testpaper set sort_idx=%0 where PaperName = '%1'").arg(sort_idx.toInt()).arg(down_name1);

	bool result = false;
	dao->UpdateRecord(&result, sql);
	result = false;
	dao->UpdateRecord(&result, sql1);
	on_tableWidget_Company_cellClicked();
	//for (int i = 0; i < count; i++)
	//{
	//	int row = ui.tableWidget_TestPaper->row(items.at(i));//获取选中的行
	//	QTableWidgetItem *item = items.at(i);
	//	QString name = item->text();//获取内容
	//}
}

void TestPaperManage::on_tableWidget_TestPaper_cellClicked()
{
	int intRow = ui.tableWidget_TestPaper->currentRow();//获取选中的行
	if (m_TestPaperQuery.size() == 0)
	{
		return;
	}
    m_TestPaperQuery.seek(intRow);
    m_strTestPaper_ID = m_TestPaperQuery.value("ID").toString();
}

void TestPaperManage::getRefreshTableWidgetFlag(bool bFlag)
{
    if (bFlag == true)
	{
		on_tableWidget_Company_cellClicked();
	}
}

void TestPaperManage::getRefreshCompanyTableWidgetFlag(bool bFlag)
{
    if (bFlag == true)
	{
		InitCompanyTableWidget();
	}
}

void TestPaperManage::on_Add_Company_Button_clicked()
{
	AddCompany *addCompany = new AddCompany();
	connect(addCompany, SIGNAL(SetRefresh(bool)), this, SLOT(getRefreshCompanyTableWidgetFlag(bool)));
	//addCompany->m_strCompany_ID = m_strCompany_ID;
	//addCompany->m_bModify = false;
	addCompany->show();
	bool bResult;
	m_strMachineUID = Global::g_machine_no;
	QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1664")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1667")).arg(GlobalData::getLoginName1());
	auto dao = AnalysisUIDao::instance();
	dao->SelectRecord(&bResult, sql1_log);
}

void TestPaperManage::on_Delete_Company_Button_clicked()
{
	int intRow = ui.tableWidget_Company->currentRow();//获取选中的行
	if (intRow == 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1644"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	if (m_strCompany_ID.length() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条厂家!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1265"), MyMessageBox::Ok, "OK", "");
		return;
	}
	//t_testpapercompany
	bool bResult;
	m_strMachineUID = Global::g_machine_no;
	QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1665")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1667")).arg(GlobalData::getLoginName1());
	auto dao = AnalysisUIDao::instance();
	dao->SelectRecord(&bResult, sql1_log);
	int nRes = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1274"), MyMessageBox::Yes| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
	if (nRes == MyMessageBox::Yes)
	{
		//删除公司
		sql1_log = QString("delete from t_testpapercompany where ID='%1' ").arg(m_strCompany_ID);
		dao->SelectRecord(&bResult, sql1_log);
		InitCompanyTableWidget();
	}
	else
	{
	}
	//AddCompany *addCompany = new AddCompany();
	//connect(addCompany, SIGNAL(SetRefresh(bool)), this, SLOT(getRefreshCompanyTableWidgetFlag(bool)));
	////addCompany->m_strCompany_ID = m_strCompany_ID;
	////addCompany->m_bModify = false;
	//addCompany->show();
	//bool bResult;
	//QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg("膜条管理模块").arg(m_strMachineUID).arg("添加").arg("");
	//auto dao = AnalysisUIDao::instance();
	//dao->SelectRecord(&bResult, sql1_log);
}

void TestPaperManage::on_Add_Button_clicked()
{
	if (m_strCompany_ID.length() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条厂家!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1265"), MyMessageBox::Ok, "OK", "");
		return;
	}
	TestPaper *testPaper = new TestPaper();
	connect(testPaper, SIGNAL(SetRefresh(bool)), this, SLOT(getRefreshTableWidgetFlag(bool)));
	testPaper->m_strCompany_ID = m_strCompany_ID;
	testPaper->m_bModify = false;
	testPaper->show();
}

void TestPaperManage::on_Modify_Button_clicked()
{
	if (m_strCompany_ID.length() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
		return;
	}
	if (m_strTestPaper_ID.length() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
		return;
	}
	TestPaper *testPaper = new TestPaper();
	connect(testPaper, SIGNAL(SetRefresh(bool)), this, SLOT(getRefreshTableWidgetFlag(bool)));
	testPaper->m_strCompany_ID = m_strCompany_ID;
	testPaper->m_bModify = true;
	testPaper->m_strTestPaper_ID = m_strTestPaper_ID;
	testPaper->Set_UI();
	testPaper->show();
	bool bResult;
	m_strMachineUID = Global::g_machine_no;
	QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1664")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1109")).arg(GlobalData::getLoginName1());
	auto dao = AnalysisUIDao::instance();
	dao->SelectRecord(&bResult, sql1_log);
}

void TestPaperManage::on_Delete_Button_clicked()
{
	if (m_strCompany_ID.length() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
		return;
	}
	if (m_strTestPaper_ID.length() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
		return;
	}
	int intRow = ui.tableWidget_TestPaper->currentRow();//获取选中的行
    if (m_TestPaperQuery.size() == 0)
		return;
    m_TestPaperQuery.seek(intRow);
    m_strTestPaper_ID = m_TestPaperQuery.value("ID").toString();
    auto dao = AnalysisUIDao::instance();
	bool bResult;
	bResult = dao->DeleteTestPaper(m_strTestPaper_ID);
	if (bResult == false)
	{
		//QMessageBox::warning(this, "错误", "删除测试膜条数据失败!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1268"), MyMessageBox::Ok, "OK", "");
		return;
	}
	on_tableWidget_Company_cellClicked();
	m_strMachineUID = Global::g_machine_no;
	QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1664")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1140")).arg(GlobalData::getLoginName1());
	auto dao1 = AnalysisUIDao::instance();
	dao1->SelectRecord(&bResult, sql1_log);
}

void TestPaperManage::on_Delete_Button_2_clicked()
{
	if (m_strCompany_ID.length() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
		return;
	}
	if (m_strTestPaper_ID.length() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
		return;
	}
	int intRow = ui.tableWidget_TestPaper->currentRow();//获取选中的行
	if (m_TestPaperQuery.size() == 0)
		return;
	m_TestPaperQuery.seek(intRow);
	m_strTestPaper_ID = m_TestPaperQuery.value("ID").toString();
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	bResult = dao->NoDeleteTestPaper(m_strTestPaper_ID);
	if (bResult == false)
	{
		//QMessageBox::warning(this, "错误", "删除测试膜条数据失败!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1268"), MyMessageBox::Ok, "OK", "");
		return;
	}
	on_tableWidget_Company_cellClicked();
	m_strMachineUID = Global::g_machine_no;
	//QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg("膜条管理模块").arg(m_strMachineUID).arg("删除").arg(GlobalData::getLoginName1());
	QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1664")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1140")).arg(GlobalData::getLoginName1());
	auto dao1 = AnalysisUIDao::instance();
	dao1->SelectRecord(&bResult, sql1_log);
}


void TestPaperManage::on_Inport_Button_clicked() 
{
	if (m_strCompany_ID.length() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条厂家!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1265"), MyMessageBox::Ok, "OK", "");
		return;
	}
	QString path = GlobalData::getExePath();
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("请选择要导入的xml文件！"),
		path,
		tr("(*xml)"));
	if (fileName.length() == 0)
		return;
	//打开或创建文件
	QFile file(fileName); //相对路径、绝对路径、资源路径都可以
	if (!file.open(QFile::ReadOnly)) 
		return;
	QDomDocument doc;
	if (!doc.setContent(&file))
	{
		file.close();
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "文件格式不正确!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1273"), MyMessageBox::Ok, "OK", "");
		return;
	}
	QDomElement root = doc.documentElement(); //返回根节点
	QDomNode node = root.firstChild(); //获得第一个子节点
	QString tagName;
	QString nodeValue;
	QString  strName;
	QString  strTotalNumber;
	QString  strItem_Number;
	QString  strTestPaparLenght;
	QString  strFuncPosition;
	QString  strTestAeaLenght;
	QString rect_Analysis_x;
	QString rect_Analysis_y;
	QString rect_Analysis_width;
	QString rect_Analysis_height;
	QString analysis_height_percentage;
	QString head_length;
	QString  strItemNameList;
	QString strItemPositionList;
	QString  strTestPaper_ID;
	QString strArticleNo;
	int RulesId = 1;
	int isCutOff = 0;
	int isFun = 0;
	QString cutoffPosition;
	QString cutoffValue;
	QString left_judge_value;
	QString BGRGB;
	QString funGrayValue;

	QString wave_pix_width;// = ui.lineEdit_wave_pix_width->text();
	QString wave_pix_width_max;// = ui.lineEdit_wave_pix_width_max->text();
	QString wave_pix_width_min;// = ui.lineEdit_wave_pix_width_min->text();
	QString background_values;// = ui.lineEdit_background_values->text();
	QString zero_value_coefficient;// = ui.lineEdit_zero_value_coefficient->text();
	QString bg_difference;// = ui.lineEdit_bg_difference->text();



	bool bOverLoad = false;
	while (!node.isNull())  //如果节点不空
	{
		if (node.isElement()) //如果节点是元素
		{
			QDomElement e = node.toElement(); 
			tagName = e.tagName();
			nodeValue =e.text();
			if (tagName == "Name")
			{
				strName = nodeValue;
			}
			if (tagName == "TotalNumber")
			{
				strTotalNumber = nodeValue;
			}
			if (tagName == "Item_Number")
			{
				strItem_Number = nodeValue;
			}
			if (tagName == "TestPaparLenght")
			{
				strTestPaparLenght = nodeValue;
			}
			if (tagName == "FuncPosition")
			{
				strFuncPosition = nodeValue;
			}
			if (tagName == "TestAeaLenght")
			{
				strTestAeaLenght = nodeValue;
			}
			if (tagName == "rect_Analysis.x")
			{
				rect_Analysis_x = nodeValue;
			}
			if (tagName == "rect_Analysis.y")
			{
				rect_Analysis_y = nodeValue;
			}
			if (tagName == "rect_Analysis.width")
			{
				rect_Analysis_width = nodeValue;
			}
			if (tagName == "rect_Analysis.height")
			{
				rect_Analysis_height = nodeValue;
			}
			if (tagName == "analysis_height_percentage")
			{
				analysis_height_percentage = nodeValue;
			}
			if (tagName == "head_length")
			{
				head_length = nodeValue;
			}
			if (tagName == "articleNo")
			{
				strArticleNo = nodeValue;
			}
			if (tagName == "ItemNameList")
			{
				strItemNameList = nodeValue;
			}
			if (tagName == "ItemPositionList")
			{
				strItemPositionList = nodeValue;
			}
			if (tagName == "isCutOff")
			{
				isCutOff = nodeValue.toInt();
			}
			if (tagName == "isFun")
			{
				isFun = nodeValue.toInt();
			}
			if (tagName == "cutoffValue")
			{
				cutoffValue = nodeValue;//.toInt();
			}
			if (tagName == "cutoffPosition")
			{
				cutoffPosition = nodeValue;//.toInt();
			}
			if (tagName == "left_judge_value")
			{
				left_judge_value = nodeValue;//.toInt();
			}
			if (tagName == "BGRGB")
			{
				BGRGB = nodeValue;//.toInt();
			}

			if (tagName == "funGrayValue")
			{
				funGrayValue = nodeValue;//.toInt();
			}


			if (tagName == "wave_pix_width")
			{
				wave_pix_width = nodeValue;//.toInt();
			}
			if (tagName == "wave_pix_width_max")
			{
				wave_pix_width_max = nodeValue;//.toInt();
			}
			if (tagName == "wave_pix_width_min")
			{
				wave_pix_width_min = nodeValue;//.toInt();
			}
			if (tagName == "background_values")
			{
				background_values = nodeValue;//.toInt();
			}
			if (tagName == "zero_value_coefficient")
			{
				zero_value_coefficient = nodeValue;//.toInt();
			}
			if (tagName == "bg_difference")
			{
				bg_difference = nodeValue;//.toInt();
			}


		}
		node = node.nextSibling();
	}
	file.close();
    auto dao = AnalysisUIDao::instance();
	bool bResult;
	strTestPaper_ID = dao->GetTestPaper_ID(m_strCompany_ID, strName, &bResult);
	if (bResult == false)
	{
		//QMessageBox::warning(this, "错误", "检索膜条数据失败！", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1272"), MyMessageBox::Ok, "OK", "");
		return;
	}
	if(strTestPaper_ID.length() >0)
	{
		int nRes = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1270"), MyMessageBox::Yes| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
		if (nRes == MyMessageBox::Yes)
			bOverLoad = true;
		else
			return;
	}
	int left_judge_value_int = left_judge_value.toInt();
	QString max_sort_id = dao->GetTestPaper_sort_max(m_strCompany_ID, strName, &bResult);
	int sort_id = 0;
	sort_id = max_sort_id.toInt();
	sort_id += 1;
	if (bOverLoad == false)
	{
		bResult = dao->InsertTestPaper(
			strName,
			m_strCompany_ID,
			strTotalNumber,
			strItem_Number,
			strTestPaparLenght,
			strFuncPosition,
			strArticleNo,
			rect_Analysis_x,
			rect_Analysis_y,
			rect_Analysis_width,
			rect_Analysis_height,
			analysis_height_percentage,
			head_length,
			isCutOff,
			cutoffPosition,
			cutoffValue,
			left_judge_value_int,sort_id, BGRGB, funGrayValue.toInt(),isFun,
			wave_pix_width,
			wave_pix_width_max,
			wave_pix_width_min,
			background_values,
			zero_value_coefficient,
			bg_difference
		);
		if (bResult == false)
		{
			//QMessageBox::warning(this, "错误", "追加测试膜条数据失败！", QMessageBox::Ok);
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1267"), MyMessageBox::Ok, "OK", "");
			return ;
		}
	}
	else
	{
		bResult = dao->UpdateTestPaper(
			strTestPaper_ID,
			strName,
			m_strCompany_ID,
			strTotalNumber,
			strItem_Number,
			strTestPaparLenght,
			strFuncPosition,
			strArticleNo,
			rect_Analysis_x,
			rect_Analysis_y,
			rect_Analysis_width,
			rect_Analysis_height,
			analysis_height_percentage,
			head_length,
			isCutOff, 
			cutoffPosition,
			cutoffValue,
			left_judge_value_int,sort_id, BGRGB, funGrayValue.toInt(),isFun,
			wave_pix_width,
			wave_pix_width_max,
			wave_pix_width_min,
			background_values,
			zero_value_coefficient,
			bg_difference
		);
		if (bResult == false)
		{
			//QMessageBox::warning(this, "错误", "更新测试膜条数据失败！", QMessageBox::Ok);
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1169"), MyMessageBox::Ok, "OK", "");
			return ;
		}
	}
	if (bOverLoad == true)
	{
		bResult = dao->DeleteTestPaperItems(strTestPaper_ID);
		if (bResult == false)
		{
			//QMessageBox::warning(this, "错误", "删除测试膜条数据失败！", QMessageBox::Ok);
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1268"), MyMessageBox::Ok, "OK", "");
			return ;
		}
	}
	else
	{
		strTestPaper_ID = dao->GetTestPaper_ID(m_strCompany_ID, strName, &bResult);
	}
	int nTotalNumber = strTotalNumber.toInt();
	QStringList itemNameList = strItemNameList.split(",");
	QStringList itemPositionList = strItemPositionList.split(",");
	QString strID,strPositionNo, strItemName, strIsNull,position;
	for (int i = 0; i < nTotalNumber; i++)
	{
		strPositionNo = QString::number(i+1);
		strItemName = itemNameList[i];
		position = itemPositionList[i];
		if (strItemName == "NULL")
		{
			strIsNull = "1";
		}
		else 
		{
			strIsNull = "0";
		}
		if (strTestPaper_ID.length() == 1)
		{
			strID = "00" + strTestPaper_ID;
		}
		if (strTestPaper_ID.length() == 2)
		{
			strID = "0" + strTestPaper_ID;
		}
		if (strPositionNo.length() == 2)
		{
			strID += strPositionNo;
		}
		else
		{
			strID += ("0" + strPositionNo);
		}
		bResult = dao->InsertTestPaperItem(
			RulesId,
			strID,
			strIsNull,
			strItemName,
			strTestPaper_ID,
			position,
			strPositionNo);
		if (bResult == false)
		{
			//QMessageBox::warning(this, "错误", "追加测试膜条数据失败！", QMessageBox::Ok);
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1267"), MyMessageBox::Ok, "OK", "");
			return ;
		}
	}

	//QMessageBox::information(this, "成功", "导入膜条数据文件成功！", QMessageBox::Ok);
	MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1259"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1266"), MyMessageBox::Ok, "OK", "");
	on_tableWidget_Company_cellClicked();
}

void TestPaperManage::on_Export_Button_clicked()
{
	if (m_strCompany_ID.length() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条厂家!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1265"), MyMessageBox::Ok, "OK", "");
		return;
	}
	if (m_strTestPaper_ID.length() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条!", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
		return;
	}
	int intRow = ui.tableWidget_TestPaper->currentRow();//获取选中的行
	if (m_TestPaperQuery.size() == 0)
	{
		return;
	}
    m_TestPaperQuery.seek(intRow);
    m_strTestPaper_ID = m_TestPaperQuery.value("ID").toString();
	bool bResult;
    auto dao = AnalysisUIDao::instance();
	QString path = GlobalData::getExePath() ;
	//getOpenFileName
	QString fileName = QFileDialog::getSaveFileName(this,tr("请输入文件名！"),path,tr("(*xml)"));
	if (fileName.length() == 0)
	{
		return;
	}
	fileName += tr(".xml");
	//打开或创建文件
	QFile file(fileName); //相对路径、绝对路径、资源路径都可以
	if (!file.open(QFile::WriteOnly | QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
	{
		return;
	}
	QDomDocument doc;
	//写入xml头部
	QDomProcessingInstruction instruction; //添加处理命令
	instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
	doc.appendChild(instruction);
	//添加根节点
	QDomElement root = doc.createElement("TestPaper");
	doc.appendChild(root);
    QSqlQuery TestPaperQuery = dao->SelectTestPaper(m_strTestPaper_ID, &bResult);
	if (bResult == false)
	{
		//QMessageBox::warning(this, "错误", "检索测试膜条数据失败！", QMessageBox::Ok);
		//MyMessageBox::warning(this, "错误", "检索测试膜条数据失败！", MyMessageBox::Ok, "OK", "");
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "1263"), MyMessageBox::Ok, "OK", "");
		return;
	}
	QDomElement element;
	QDomText text;
    if (TestPaperQuery.next())
	{
		element = doc.createElement("Name");
        text = doc.createTextNode(TestPaperQuery.value("PaperName").toString());
		element.appendChild(text);
		root.appendChild(element);
		//articleNo
		element = doc.createElement("articleNo");
		text = doc.createTextNode(TestPaperQuery.value("articleNo").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("TotalNumber");
        text = doc.createTextNode(TestPaperQuery.value("TotalNumber").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("Item_Number");
        text = doc.createTextNode(TestPaperQuery.value("Item_Number").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("Null_Number");
        text = doc.createTextNode(TestPaperQuery.value("Null_Number").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("TestPaparLenght");
        text = doc.createTextNode(TestPaperQuery.value("TestPaparLenght").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("rect_Analysis.x");
		text = doc.createTextNode(TestPaperQuery.value("rect_Analysis.x").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("rect_Analysis.y");
		text = doc.createTextNode(TestPaperQuery.value("rect_Analysis.y").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("rect_Analysis.width");
		text = doc.createTextNode(TestPaperQuery.value("rect_Analysis.width").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("rect_Analysis.height");
		text = doc.createTextNode(TestPaperQuery.value("rect_Analysis.height").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("analysis_height_percentage");
		text = doc.createTextNode(TestPaperQuery.value("analysis_height_percentage").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("head_length");
		text = doc.createTextNode(TestPaperQuery.value("head_length").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("FuncPosition");
        text = doc.createTextNode(TestPaperQuery.value("FuncPosition").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("TestAeaLenght");
        text = doc.createTextNode(TestPaperQuery.value("TestAeaLenght").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("cutoffValue");
		text = doc.createTextNode(TestPaperQuery.value("cutoffValue").toString());
		element.appendChild(text);
		root.appendChild(element);


		element = doc.createElement("cutoffPosition");
		text = doc.createTextNode(TestPaperQuery.value("cutoffPosition").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("isCutOff");
		text = doc.createTextNode(TestPaperQuery.value("isCutOff").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("isFun");
		text = doc.createTextNode(TestPaperQuery.value("isFun").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("funGrayValue");
		text = doc.createTextNode(TestPaperQuery.value("funGrayValue").toString());
		element.appendChild(text);
		root.appendChild(element);


		element = doc.createElement("left_judge_value");
		text = doc.createTextNode(TestPaperQuery.value("left_judge_value").toString());
		element.appendChild(text);
		root.appendChild(element);


		element = doc.createElement("wave_pix_width");
		text = doc.createTextNode(TestPaperQuery.value("wave_pix_width").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("wave_pix_width_max");
		text = doc.createTextNode(TestPaperQuery.value("wave_pix_width_max").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("wave_pix_width_min");
		text = doc.createTextNode(TestPaperQuery.value("wave_pix_width_min").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("background_values");
		text = doc.createTextNode(TestPaperQuery.value("background_values").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("zero_value_coefficient");
		text = doc.createTextNode(TestPaperQuery.value("zero_value_coefficient").toString());
		element.appendChild(text);
		root.appendChild(element);

		element = doc.createElement("bg_difference");
		text = doc.createTextNode(TestPaperQuery.value("bg_difference").toString());
		element.appendChild(text);
		root.appendChild(element);

	}
    auto TestPaperItemQuery = dao->SelectTestPaperItems(m_strTestPaper_ID, &bResult);
	if (bResult == false)
	{
		//QMessageBox::warning(this, "错误", "检索测试膜条数据失败！", QMessageBox::Ok);
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "1263"), MyMessageBox::Ok, "OK", "");
		//K1263
		return;
	}
	QString strItemNameList;
	QString strItemPositionList;
    while (TestPaperItemQuery.next())
	{
        int nIsNull = TestPaperItemQuery.value("IsNull").toInt();
		if (nIsNull == 1)
		{
			strItemNameList += "NULL";
			strItemPositionList += "0";
		}
		else 
		{
            strItemNameList += TestPaperItemQuery.value("itemName").toString();
			strItemPositionList += TestPaperItemQuery.value("position").toString();
		
		}
		strItemNameList += ",";
		strItemPositionList += ",";
	}
	//添加名字
	strItemNameList = strItemNameList.left(strItemNameList.length() - 1);
	element = doc.createElement("ItemNameList");
	text = doc.createTextNode(strItemNameList);
	element.appendChild(text);
	root.appendChild(element);
	//添加位置
	strItemPositionList = strItemPositionList.left(strItemPositionList.length() - 1);
	element = doc.createElement("ItemPositionList");
	text = doc.createTextNode(strItemPositionList);
	element.appendChild(text);
	root.appendChild(element);
	//输出到文件
	QTextStream out_stream(&file);
	doc.save(out_stream, 4); //缩进4格
	file.close();
	//QMessageBox::information(this, "成功", "导出膜条数据文件成功！", QMessageBox::Ok);
	MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1259"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1262"), MyMessageBox::Ok,"OK","");
	//K1262
}


