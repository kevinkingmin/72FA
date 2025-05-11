#include "ReagentManager.h"
#include "AddReagent.h"
#include <QMessageBox>
#include <QCheckBox>
#include <QSqlQuery>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Instrument/Instrument.h"
#include "../comm/Global.h"
#include "../comm/GlobalData.h"
#include <QProcess>
#include "src/main/subDialog/MyMessageBox.h"
#include <QDebug>

ReagentManager::ReagentManager(QWidget *parent): QWidget(parent)
{
	setAttribute(Qt::WA_ShowModal, true);
	ui.setupUi(this);
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
	_instr = Instrument::instance();
    QString nMachineUID = "_instr->get_machine_no()";
	m_strMachineUID = nMachineUID;//QString("%1").arg(nMachineUID, 2, 10, QChar('0'));//.Format("%08d", nMachineUID);
	InitCompanyTableWidget();
	InitReagentTableWidget();
	ui.label->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1135"));
	ui.Add_Button->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1108"));
	ui.Modify_Button->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1109"));
	ui.Delete_Button->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1140"));
}

ReagentManager::~ReagentManager()
{
}

void ReagentManager::InitReagentTableWidget()
{
	//不显示左边默认自带序列号
	QHeaderView* headerView = ui.tableWidget_Reagent->verticalHeader();
	headerView->setHidden(true);
	//使行列头自适应宽度，最后一列将会填充空白部分
	ui.tableWidget_Reagent->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_Reagent->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	ui.tableWidget_Reagent->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
	ui.tableWidget_Reagent->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑
	ui.tableWidget_Reagent->setSortingEnabled(false);
	//隔行变色
	ui.tableWidget_Reagent->setAlternatingRowColors(true);

	//去掉网格线
	ui.tableWidget_Reagent->setShowGrid(false);
	QStringList headerString;
	QString sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1136");
	QString sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1100");
	QString sz3 = GlobalData::LoadLanguageInfo(g_language_type, "K1137");
	QString sz4 = GlobalData::LoadLanguageInfo(g_language_type, "K1138");
	QString sz5 = GlobalData::LoadLanguageInfo(g_language_type, "K1139");
	headerString <<  sz1 << sz2 <<"" << "" << "" << sz3 << sz4 << sz5;
	ui.tableWidget_Reagent->setHorizontalHeaderLabels(headerString);
	//ui.tableWidget_Reagent->setAlternatingRowColors(true);
}

void ReagentManager::InitCompanyTableWidget()
{
	ui.tableWidget_Company->setRowCount(0);
	//不显示左边默认自带序列号
	QHeaderView* headerView = ui.tableWidget_Company->verticalHeader();
	headerView->setHidden(true);
	//使行列头自适应宽度，最后一列将会填充空白部分
	ui.tableWidget_Company->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_Company->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	ui.tableWidget_Company->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
	ui.tableWidget_Company->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑


	QStringList headerString;
	headerString << GlobalData::LoadLanguageInfo(g_language_type, "K1099");
	ui.tableWidget_Company->setHorizontalHeaderLabels(headerString);


	QString itemName;
	bool bResult = true;
    auto dao = AnalysisUIDao::instance();
	//m_CompanyQuery = dao->SelectCompanys(&bResult);
	QString  loginName = GlobalData::getLoginName1();
	int company_id = Global::g_company_id;
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
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1290"), MyMessageBox::Ok,"OK","");
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

	//隔行变色
	ui.tableWidget_Company->setAlternatingRowColors(true);
	//去掉网格线
	ui.tableWidget_Company->setShowGrid(false);
}


void ReagentManager::addCompanyContent(int row, int column, QString content)
{

	QTableWidgetItem *item = new QTableWidgetItem(content);

	ui.tableWidget_Company->setItem(row, column, item);

}

void ReagentManager::addReagentContent(int row, int column, QString content)
{
	if (column == 1)
	{
		ui.tableWidget_Reagent->resizeColumnsToContents();
	}

	if (column == 2 || column == 3 || column == 4)
	{
		QCheckBox *checkBox_Item = new QCheckBox();
		if(content == "1")
			checkBox_Item->setChecked(true);
		else
			checkBox_Item->setChecked(false);
		ui.tableWidget_Reagent->setCellWidget(row, column, (QWidget*)checkBox_Item);
	}
	else 
	{
		if (row == 1 || row == 2)
		{
			QTableWidgetItem *item = new QTableWidgetItem(content);
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			//ui.tableWidget_Reagent->horizontalHeader().setSectionResizeMode(QHeaderView.Stretch);
			//ui.tableWidget_Reagent->width = 200;
			ui.tableWidget_Reagent->setItem(row, column, item);
		}
		else
		{
			QTableWidgetItem *item = new QTableWidgetItem(content);
			ui.tableWidget_Reagent->setItem(row, column, item);
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
		ui.tableWidget_Reagent->horizontalHeader()->setStretchLastSection(true); //这个是关键
		//ui.tableWidget_Reagent->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		//ui.tableWidget_Reagent->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
		//ui.tableWidget_Reagent->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


	}
}

void ReagentManager::on_tableWidget_Company_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	on_tableWidget_Company_cellClicked();
}

void ReagentManager::on_tableWidget_Company_cellClicked()
{
	//清空列表
	ui.tableWidget_Reagent->setRowCount(0);
	int intRow = ui.tableWidget_Company->currentRow();//获取选中的行
    if (m_CompanyQuery.size() == 0)
		return;

    m_CompanyQuery.seek(intRow);
    m_strCompany_ID = m_CompanyQuery.value("ID").toString();
    qDebug() << "m_strCompany_ID:"<<m_strCompany_ID;
	QString strValue;
	bool bResult = true;
    auto dao = AnalysisUIDao::instance();
	m_ReagentQuery = dao->SelectReagents(m_strCompany_ID, &bResult);

	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1263"), MyMessageBox::Ok,"OK","");
		return;
	}
    if (m_ReagentQuery.size() == 0)
	{
		return;
	}
	int row = 0;
	QString sID = 0;
	bool bNull = false;

    while (m_ReagentQuery.next())
	{
		ui.tableWidget_Reagent->insertRow(row);
		//名称
        strValue = m_ReagentQuery.value("reagentName").toString();

		QString test_paper_id = m_ReagentQuery.value("TestPaperID").toString();

		if (test_paper_id == "111")
		{
			addReagentContent(row, 0, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), strValue));//strValue);
		}
		else
		{
			addReagentContent(row, 0, strValue);
		}


        bNull = m_ReagentQuery.value("TestPaperID").isNull();
		if (bNull == true) 
		{
			addReagentContent(row, 1, "");
		}
		else 
		{
            strValue = m_ReagentQuery.value("TestPaperID").toString();
			if (strValue.length() > 0)
			{
                auto TestPaperQuery = dao->SelectTestPaper(strValue, &bResult);
                if (TestPaperQuery.next())
				{
                    strValue = TestPaperQuery.value("PaperName").toString();
				}
				else if (strValue == "111")
				{
					strValue = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1697");//"通用";
				}
			}
			addReagentContent(row, 1, strValue);
        }
        strValue = m_ReagentQuery.value("IsNoDrip").toString();
		addReagentContent(row, 2, strValue);
        strValue = m_ReagentQuery.value("IsSkimp").toString();
		addReagentContent(row, 3, strValue);
        strValue = m_ReagentQuery.value("IsNeedPrepare").toString();
		addReagentContent(row, 4, strValue);
        bNull = m_ReagentQuery.value("PumpNo").isNull();
		if (bNull == true)
		{
			addReagentContent(row, 5, "");
		}
		else 
		{
			int pump_no = m_ReagentQuery.value("PumpNo").toInt();
			if (pump_no != -1)
			{
				strValue = QString("%1").arg(pump_no + 1);//m_ReagentQuery.value("PumpNo").toString();
				addReagentContent(row, 5, strValue);
			}
			else
			{
				strValue = QString("%1").arg(pump_no);//m_ReagentQuery.value("PumpNo").toString();
				addReagentContent(row, 5, strValue);
			}
        }
		QString big_wash = m_ReagentQuery.value("fluidMeasure").toString();
		addReagentContent(row, 6, big_wash);
		QString small_wash  = m_ReagentQuery.value("fluidMeasureSmall").toString();
		addReagentContent(row, 7, small_wash);
		row++;
	}
	if (row > 0)
	{
		/*设置让某个单元格或某行选中*/
		//选中单元格 第一行：
		//ui.tableWidget_Reagent->setCurrentCell(0, 0, QItemSelectionModel::Select);
	}

	// 假设tableWidget是你的QTableWidget对象

// 自适应行高
	//tableWidget->resizeRowsToContents();

	// 自适应列宽
	//ui.tableWidget_Reagent->resizeColumnsToContents();

	ui.tableWidget_Reagent->hideColumn(2);
	ui.tableWidget_Reagent->hideColumn(3);
	ui.tableWidget_Reagent->hideColumn(4);

	ui.tableWidget_Reagent->setColumnWidth(1, 220);
	ui.tableWidget_Reagent->setColumnWidth(5, 150);
	ui.tableWidget_Reagent->setColumnWidth(6, 150);


	ui.tableWidget_Reagent->setColumnWidth(7, 100);
	// 自适应表格大小
	//ui.tableWidget_Reagent->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//ui.tableWidget_Reagent->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}

void ReagentManager::on_tableWidget_Reagent_cellClicked()
{
	int intRow = ui.tableWidget_Reagent->currentRow();//获取选中的行

    if (m_ReagentQuery.size() == 0)
		return;

    m_ReagentQuery.seek(intRow);
    m_strReagent_ID = m_ReagentQuery.value("ID").toString();
}

void ReagentManager::getRefreshTableWidgetFlag(bool bFlag)
{
    if (bFlag == true)
	{
		on_tableWidget_Company_cellClicked();
	}

}

void ReagentManager::getRefreshCompanyTableWidgetFlag(bool bFlag)
{
    if (bFlag == true)
	{
		InitCompanyTableWidget();
	}
}

void ReagentManager::on_Add_Button_clicked()
{
	if (m_strCompany_ID.length() == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1538"), MyMessageBox::Ok,"OK","");
		return;
	}

	AddReagent *addReagent = new AddReagent();
	connect(addReagent, SIGNAL(SetRefresh(bool)), this, SLOT(getRefreshTableWidgetFlag(bool)));

	addReagent->m_strCompany_ID = m_strCompany_ID;
	addReagent->m_bModify = false;
	addReagent->Set_UI();
	addReagent->show();

	m_strMachineUID = Global::g_machine_no;

	bool bResult;
	QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1659")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1667")).arg(GlobalData::getLoginName1());
	auto dao = AnalysisUIDao::instance();
	dao->SelectRecord(&bResult, sql1_log);

}

void ReagentManager::on_Modify_Button_clicked()
{
	if (m_strCompany_ID.length() == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1539"), MyMessageBox::Ok,"OK","");
		return;
	}

	if (m_strReagent_ID.length() == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1539"), MyMessageBox::Ok,"OK","");
		return;
	}

	AddReagent *addReagent = new AddReagent();
	connect(addReagent, SIGNAL(SetRefresh(bool)), this, SLOT(getRefreshTableWidgetFlag(bool)));

	addReagent->m_strCompany_ID = m_strCompany_ID;
	addReagent->m_bModify = true;
	addReagent->m_strReagent_ID = m_strReagent_ID;

	addReagent->Set_UI();
	addReagent->show();

	m_strMachineUID = Global::g_machine_no;
	bool bResult;
	QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1659")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1109")).arg(GlobalData::getLoginName1());
	auto dao = AnalysisUIDao::instance();
	dao->SelectRecord(&bResult, sql1_log);

	//auto ret = QMessageBox::information(this, tr("成功"), tr("更新系统参数成功， 需重启软件后更改才生效。"), tr("是"), tr("否"));
	//if (ret != 0)
	//{

	//}
	//else
	//{
	//	qApp->quit();   // 或者   aApp->closeAllWindows();
	//	QProcess::startDetached(qApp->applicationFilePath(), QStringList());
	//}
}

void ReagentManager::on_Delete_Button_clicked()
{
	if (m_strCompany_ID.length() == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1539"), MyMessageBox::Ok,"OK","");
		return;
	}

	if (m_strReagent_ID.length() == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1539"), MyMessageBox::Ok,"OK","");
		return;
	}

	int ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1540"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
	if (ret != MyMessageBox::Ok)
	{
		return;
	}

	int intRow = ui.tableWidget_Reagent->currentRow();//获取选中的行
    if (m_ReagentQuery.size() == 0)
		return;

    m_ReagentQuery.seek(intRow);
    m_strReagent_ID = m_ReagentQuery.value("ID").toString();

	if (m_strReagent_ID == "5" || m_strReagent_ID == "6" || m_strReagent_ID == "7" || m_strReagent_ID == "8" || m_strReagent_ID == "9" || m_strReagent_ID == "10")
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1541"), MyMessageBox::Ok,"OK","");
		return;
	}


    auto dao = AnalysisUIDao::instance();
	bool bResult;
	bResult = dao->DeleteReagent(m_strReagent_ID);

	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1542"), MyMessageBox::Ok,"OK","");
		return;
	}
	m_strMachineUID = Global::g_machine_no;
	QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1659")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1140")).arg(GlobalData::getLoginName1());
	auto dao1 = AnalysisUIDao::instance();
	dao1->SelectRecord(&bResult, sql1_log);
	on_tableWidget_Company_cellClicked();
}
