#include "TestPaperManage.h"
#include "AddCompany.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QtXml>
#include<QFileDialog>
#include "src/comm/GlobalData.h"
#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Instrument/Instrument.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "../comm/GlobalData.h"
#include "../Include/DAO/baseSet/CompanyDao.h"
#include "../Include/DAO/baseSet/ItemDao.h"
#include "../Include/DAO/baseSet/TestPaperDao.h"

TestPaperManage::TestPaperManage(QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_ShowModal, true);
	ui.setupUi(this);
	InitCompanyTableWidget();
	InitTestPaperTableWidget();
	_instr = Instrument::instance();
	//int nMachineUID = _instr->get_machine_no();
	//m_strMachineUID = QString("%1").arg(nMachineUID, 2, 10, QChar('0'));//.Format("%08d", nMachineUID);
	//
    ui.label->setText(GlobalData::LoadLanguageInfo("K1098")); // 膜条厂家选择
    ui.Inport_Button->setText(GlobalData::LoadLanguageInfo("K1106")); // 导入
    ui.Export_Button->setText(GlobalData::LoadLanguageInfo("K1107")); // 导出
    ui.Add_Button->setText(GlobalData::LoadLanguageInfo("K1108")); // 追加
    ui.Modify_Button->setText(GlobalData::LoadLanguageInfo("K1109")); //修改
    ui.Enable_Button->setText(GlobalData::LoadLanguageInfo("K1104")); // 启用
    ui.Disable_Button->setText(GlobalData::LoadLanguageInfo("K1105")); // 不启用
    ui.Delete_Button->setText(GlobalData::LoadLanguageInfo("K1140")); // 删除
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
    QString sz1 = GlobalData::LoadLanguageInfo("K1100");
    QString sz2 = GlobalData::LoadLanguageInfo("K1101");
    QString sz3 = GlobalData::LoadLanguageInfo("K1102");
    QString sz4 = GlobalData::LoadLanguageInfo("K1103");
	headerString << "NO"<<sz1<<sz2<<sz3<<sz4;
	ui.tableWidget_TestPaper->setHorizontalHeaderLabels(headerString);
    this->setWindowTitle(GlobalData::LoadLanguageInfo("K1015"));
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
    headerString << GlobalData::LoadLanguageInfo("K1099");
	ui.tableWidget_Company->setHorizontalHeaderLabels(headerString);
	QString itemName;
	//DB中取Testitems表数据
	bool bResult = true;
    auto dao = CompanyDao::instance();
	QString  loginName = GlobalData::getLoginName1();
	int company_id= Global::g_company_id;
    uint group_id = GlobalData::getGruopId();
    _companyModels.clear();
	//不是管理员,
	if (group_id == 3)
	{
        CompanyModel model;
        bResult = dao->getModel(company_id, model);
        _companyModels.push_back(model);
	}
	else
	{
        _companyModels = dao->getAllRows();
	}
	if (bResult == false)
	{
        QString sz = GlobalData::LoadLanguageInfo("K1111");
        QString sz1 = GlobalData::LoadLanguageInfo("K1110");
		MyMessageBox::warning(this, sz, sz1, MyMessageBox::Ok, "OK", "");
		return;
	}
	int row = 0;
    for (CompanyModel& m : _companyModels)
	{
        itemName = m.getName();
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
    intRow = intRow>=0 ? intRow:0;
    if (_companyModels.size() == 0)
		return;
    CompanyModel companyModel = _companyModels[intRow];
    m_strCompany_ID = QString::number(companyModel.getId());
	QString strValue;
    _selectPaperVect = TestPaperDao::instance()->getCompanyPapers(m_strCompany_ID);
    if (_selectPaperVect.size() == 0)
    {
		return;
	}
	int row = 0;
    QString sID = "0";
    for(TestPaperModel& paper : _selectPaperVect)
	{
		ui.tableWidget_TestPaper->insertRow(row);
		//ID
		sID = QString::number(row + 1);
		addTestPaperContent(row, 0, sID);
		//名称
        strValue = paper.getPaperName();
		addTestPaperContent(row, 1, strValue);
		//货号
        strValue = paper.getArticleNo();
		addTestPaperContent(row, 2, strValue);
        strValue = QString::number(paper.getPaperSortIdxOnUi());
		addTestPaperContent(row, 3, strValue);
        bool enable = !paper.isPaperHide();
        if (enable)
		{
            strValue = GlobalData::LoadLanguageInfo("K1104");//"启用";
		}
		else
		{
            strValue = GlobalData::LoadLanguageInfo("K1105");//"不启用";
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
	QList<QTableWidgetItem*>items = ui.tableWidget_TestPaper->selectedItems();
	int row = ui.tableWidget_TestPaper->row(items.at(0));//获取选中的行
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
    sql = QString("update t_testpaper set PaperSortIdxOnUi=%0 where PaperName = '%1'").arg(up_sort_id).arg(name);
	dao->UpdateRecord(&result,sql);
	result = false;
    sql1 = QString("update t_testpaper set PaperSortIdxOnUi=%0 where PaperName = '%1'").arg(sort_idx).arg(up_name1);
	dao->UpdateRecord(&result, sql1);
	on_tableWidget_Company_cellClicked();
}

void TestPaperManage::on_Down_Sort_Button_3_clicked()
{
	//ui.tableWidget_TestPaper->
	QList<QTableWidgetItem*>items = ui.tableWidget_TestPaper->selectedItems();
	int row = ui.tableWidget_TestPaper->row(items.at(0));//获取选中的行
	int total_row = ui.tableWidget_TestPaper->rowCount();
	auto dao = AnalysisUIDao::instance();
	int count = items.count();
	QTableWidgetItem *item = items.at(1);
	if (count < 2)
    {
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
		return;
	}
	QString down_name1 = "";
    QString down_sort_id = "";
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
    sql = QString("update t_testpaper set PaperSortIdxOnUi=%0 where PaperName = '%1'").arg(down_sort_id).arg(name);
    sql1 = QString("update t_testpaper set PaperSortIdxOnUi=%0 where PaperName = '%1'").arg(sort_idx.toInt()).arg(down_name1);

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
    if (_selectPaperVect.size() == 0 && _selectPaperVect.size()<intRow)
	{
		return;
	}
    _selectPaperModel = _selectPaperVect[intRow];
    _selectPaperId = QString::number(_selectPaperModel.getId());
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
        TestPaperDao* paperDao = TestPaperDao::instance();
        ItemDao* itemDao = ItemDao::instance();
        QVector<TestPaperModel> paperVec = paperDao->getCompanyPapers(m_strCompany_ID);
        for(TestPaperModel& paper : paperVec)
        {
            paperDao->deleteById(paper.getId());
            itemDao->deleteItems(paper.getId());
        }
        CompanyDao* companyDao = CompanyDao::instance();
        int companyId = m_strCompany_ID.toInt();
        //删除公司
        companyDao->deleteModel(companyId);
		InitCompanyTableWidget();
	}
}

void TestPaperManage::on_Add_Button_clicked()
{
	if (m_strCompany_ID.length() == 0)
    {
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1265"), MyMessageBox::Ok, "OK", "");
		return;
	}
    TestPaper testPaper(this);
    testPaper.Set_UI("", m_strCompany_ID, false);
    testPaper.exec();
}

void TestPaperManage::on_Modify_Button_clicked()
{
	if (m_strCompany_ID.length() == 0)
    {
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
		return;
	}
    if (_selectPaperId.length() == 0)
    {
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
		return;
    }
    TestPaper testPaper(this);
    testPaper.Set_UI(_selectPaperId,m_strCompany_ID, true);
    testPaper.exec();

	bool bResult;
	m_strMachineUID = Global::g_machine_no;
	QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1664")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1109")).arg(GlobalData::getLoginName1());
	auto dao = AnalysisUIDao::instance();
	dao->SelectRecord(&bResult, sql1_log);
}


void TestPaperManage::enablePaper(bool enable)
{
    if (m_strCompany_ID.length() == 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
        return;
    }
    if (_selectPaperId.length() == 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
        return;
    }
    bool bResult;
    bResult = TestPaperDao::instance()->enableAndUpdate(_selectPaperId.toInt(), enable);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1268"), MyMessageBox::Ok, "OK", "");
        return;
    }
    on_tableWidget_Company_cellClicked();
    m_strMachineUID = Global::g_machine_no;
    QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1664")).arg(m_strMachineUID).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1140")).arg(GlobalData::getLoginName1());
    auto dao1 = AnalysisUIDao::instance();
    dao1->SelectRecord(&bResult, sql1_log);
}

// 膜条删除
void TestPaperManage::on_Delete_Button_clicked()
{
    if (_selectPaperId.length() == 0)
    {
        QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180"),GlobalData::LoadLanguageInfo("K1407"),GlobalData::LoadLanguageInfo("K1181"));
        return;
    }
    auto ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1259"), GlobalData::LoadLanguageInfo("K1713"), MyMessageBox::Ok| MyMessageBox::No,tr("YES"), tr("NO"));
    if (ret == MyMessageBox::No)
    {
        return;
    }
    bool bResult;
    // 删除膜条
    bResult = TestPaperDao::instance()->deleteById(_selectPaperId.toInt());
    // 删除对应项目
    ItemDao::instance()->deleteItems(_selectPaperId.toInt());
    _selectPaperId = "";
    on_tableWidget_Company_cellClicked();
}

// 膜条禁用
void TestPaperManage::on_Disable_Button_clicked()
{
    enablePaper(false);
}

// 膜条启用
void TestPaperManage::on_Enable_Button_clicked()
{
    enablePaper(true);
}

// 膜条参数导入
void TestPaperManage::on_Inport_Button_clicked() 
{

    MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1263"), MyMessageBox::Ok, "OK", "");
//	if (m_strCompany_ID.length() == 0)
//    {
//		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1265"), MyMessageBox::Ok, "OK", "");
//		return;
//	}
//	QString path = GlobalData::getExePath();
//	QString fileName = QFileDialog::getOpenFileName(this,
//		tr("请选择要导入的xml文件！"),
//		path,
//		tr("(*xml)"));
//	if (fileName.length() == 0)
//		return;
//	//打开或创建文件
//	QFile file(fileName); //相对路径、绝对路径、资源路径都可以
//	if (!file.open(QFile::ReadOnly))
//		return;
//	QDomDocument doc;
//	if (!doc.setContent(&file))
//	{
//		file.close();
//		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "文件格式不正确!", QMessageBox::Ok);
//		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1273"), MyMessageBox::Ok, "OK", "");
//		return;
//	}
//	QDomElement root = doc.documentElement(); //返回根节点
//	QDomNode node = root.firstChild(); //获得第一个子节点

//    TestPaperModel testPaperModel;
//	bool bOverLoad = false;
//	while (!node.isNull())  //如果节点不空
//	{
//		if (node.isElement()) //如果节点是元素
//		{
//			QDomElement e = node.toElement();
//            auto tagName = e.tagName();
//            auto nodeValue =e.text();
//            if(tagName == "CompanyID")
//            {
//                testPaperModel.setCompanyId(nodeValue.toInt());
//            }
//            else if (tagName == "PaperName")
//			{
//                testPaperModel.setPaperName(nodeValue);
//			}
//            else if (tagName == "PaperType")
//            {
//                testPaperModel.setPaperType(nodeValue.toInt());
//            }
//            else if (tagName == "TotalNumber")
//			{
//                testPaperModel.setTotalNumber(nodeValue.toInt());
//			}
//            else if (tagName == "ItemNumber")
//			{
//                testPaperModel.setTestItemNumber(nodeValue.toInt());
//            }
//            else if (tagName == "TestPaperLenght")
//            {
//                testPaperModel.setPaperLenght(nodeValue.toDouble());
//            }
//            else if (tagName == "PaperHeight")
//            {
//                testPaperModel.setPaperHeight(nodeValue.toDouble());
//            }
//            else if (tagName == "PaperMmToPixel")
//			{
//                testPaperModel.setPaperMmToPixel(nodeValue.toDouble());
//			}
//            else if (tagName == "IgnoreHeadLenght")
//			{
//                testPaperModel.setPaperMmToPixel(nodeValue.toDouble());
//			}
//            else if (tagName == "TestBlockWidth")
//			{
//                testPaperModel.setTestBlockWidth(nodeValue.toDouble());
//			}
//            else if (tagName == "FuncFindDir")
//			{
//                testPaperModel.setFuncFindDir(nodeValue.toInt());
//			}
//            else if (tagName == "FuncPosition")
//			{
//                testPaperModel.setFuncPosition(nodeValue.toDouble());
//			}
//            else if (tagName == "FuncFindWidth")
//			{
//                testPaperModel.setFuncFindWidth(nodeValue.toDouble());
//			}
//            else if (tagName == "FuncGrayThreshold")
//			{
//                testPaperModel.setFuncGrayThreshold(nodeValue.toDouble());
//			}
//            else if (tagName == "IsBlackPointDetect")
//			{
//                testPaperModel.setIsBlackPointDetect(nodeValue.toInt() == 1);
//			}
//            else if (tagName == "BlackPointDetectThreshold")
//			{
//                testPaperModel.setBlackPointDetectThreshold(nodeValue.toDouble());
//			}
//            else if (tagName == "IsCutOff")
//			{
//                testPaperModel.setIsCutOff(nodeValue.toInt()==1);
//			}
//            else if (tagName == "CutoffGrayThreshold")
//			{
//                testPaperModel.setCutOffThreshold(nodeValue.toDouble());
//			}
//            else if (tagName == "CutoffPosition")
//			{
//                testPaperModel.setCutOffPosition(nodeValue.toDouble());
//			}
//            else if (tagName == "CutoffValue")
//			{
//                testPaperModel.setCutOffValue(nodeValue.toDouble());
//			}
//            else if (tagName == "PaperShowAngle")
//			{
//                testPaperModel.setPaperShowAngle(nodeValue.toInt());
//			}
//            else if (tagName == "PaperBinarizationThreshold")
//			{
//                testPaperModel.setPaperBinarizationThreshold(nodeValue.toInt());
//			}
//            else if (tagName == "PaperBackgroundValue")
//			{
//                testPaperModel.setPaperBackgroundValue(nodeValue.toDouble());
//			}
//            else if (tagName == "ItemFindWidth")
//			{
//                testPaperModel.setItemFindWidth(nodeValue.toDouble());
//			}
//            else if (tagName == "ItemLineWidth")
//			{
//                testPaperModel.setItemLineWidth(nodeValue.toDouble());
//			}
//            else if (tagName == "AnalysisPercentOfHeight")
//			{
//                testPaperModel.setAnalysisPercentOfHeight(nodeValue.toInt());
//			}
//            else if (tagName == "AnalysisPercentOfWidth")
//			{
//                testPaperModel.setAnalysisPercentOfWidth(nodeValue.toInt());
//			}
//            else if (tagName == "PaperColorOnUi")
//			{
//                testPaperModel.setPaperColorOnUi(nodeValue);
//			}
//            else if (tagName == "IsPaperHide")
//			{
//                testPaperModel.setPaperHide(nodeValue.toInt()==1);
//			}
//            else if (tagName == "ArticleNo")
//            {
//                testPaperModel.setArticleNo(nodeValue);
//			}
//            else if (tagName == "PaperSortIdxOnUi")
//            {
//                testPaperModel.setPaperSortIdxOnUi(nodeValue.toInt());
//            }
//		}
//		node = node.nextSibling();
//	}
//	file.close();
//    auto dao = AnalysisUIDao::instance();
//	bool bResult;
//    QString strTestPaper_ID = dao->GetTestPaper_ID(m_strCompany_ID, testPaperModel.getPaperName(), &bResult);
//	if (bResult == false)
//	{
//		//QMessageBox::warning(this, "错误", "检索膜条数据失败！", QMessageBox::Ok);
//		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1272"), MyMessageBox::Ok, "OK", "");
//		return;
//	}
//	if(strTestPaper_ID.length() >0)
//	{
//		int nRes = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1270"), MyMessageBox::Yes| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
//		if (nRes == MyMessageBox::Yes)
//			bOverLoad = true;
//		else
//			return;
//	}
//	if (bOverLoad == false)
//    {
//        return;
//	}
//	else
//    {
//        bResult = dao->UpdateTestPaper(strTestPaper_ID, testPaperModel);
//		if (bResult == false)
//		{
//			//QMessageBox::warning(this, "错误", "更新测试膜条数据失败！", QMessageBox::Ok);
//			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1169"), MyMessageBox::Ok, "OK", "");
//			return ;
//		}
//	}

    //TODO::WANGZ
//	int nTotalNumber = strTotalNumber.toInt();
//	QStringList itemNameList = strItemNameList.split(",");
//	QStringList itemPositionList = strItemPositionList.split(",");
//	QString strID,strPositionNo, strItemName, strIsNull,position;
//	for (int i = 0; i < nTotalNumber; i++)
//	{
//		strPositionNo = QString::number(i+1);
//		strItemName = itemNameList[i];
//		position = itemPositionList[i];
//		if (strItemName == "NULL")
//		{
//			strIsNull = "1";
//		}
//		else
//		{
//			strIsNull = "0";
//		}
//		if (strTestPaper_ID.length() == 1)
//		{
//			strID = "00" + strTestPaper_ID;
//		}
//		if (strTestPaper_ID.length() == 2)
//		{
//			strID = "0" + strTestPaper_ID;
//		}
//		if (strPositionNo.length() == 2)
//		{
//			strID += strPositionNo;
//		}
//		else
//		{
//			strID += ("0" + strPositionNo);
//		}
//		bResult = dao->InsertTestPaperItem(
//			RulesId,
//			strID,
//			strIsNull,
//			strItemName,
//			strTestPaper_ID,
//			position,
//			strPositionNo);
//		if (bResult == false)
//		{
//			//QMessageBox::warning(this, "错误", "追加测试膜条数据失败！", QMessageBox::Ok);
//			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1267"), MyMessageBox::Ok, "OK", "");
//			return ;
//		}
//	}

//	//QMessageBox::information(this, "成功", "导入膜条数据文件成功！", QMessageBox::Ok);
//	MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1259"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1266"), MyMessageBox::Ok, "OK", "");
//	on_tableWidget_Company_cellClicked();
}

void TestPaperManage::on_Export_Button_clicked()
{
    MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1263"), MyMessageBox::Ok, "OK", "");
//	if (m_strCompany_ID.length() == 0)
//	{
//		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条厂家!", QMessageBox::Ok);
//		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1265"), MyMessageBox::Ok, "OK", "");
//		return;
//	}
//    if (_selectPaperId.length() == 0)
//	{
//		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请先选择膜条!", QMessageBox::Ok);
//		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1264"), MyMessageBox::Ok, "OK", "");
//		return;
//	}
//	int intRow = ui.tableWidget_TestPaper->currentRow();//获取选中的行
//	if (m_TestPaperQuery.size() == 0)
//	{
//		return;
//	}
//    m_TestPaperQuery.seek(intRow);
//    m_strTestPaper_ID = m_TestPaperQuery.value("ID").toString();
//	bool bResult;
//    auto dao = AnalysisUIDao::instance();
//	QString path = GlobalData::getExePath() ;
//	//getOpenFileName
//	QString fileName = QFileDialog::getSaveFileName(this,tr("请输入文件名！"),path,tr("(*xml)"));
//	if (fileName.length() == 0)
//	{
//		return;
//	}
//	fileName += tr(".xml");
//	//打开或创建文件
//	QFile file(fileName); //相对路径、绝对路径、资源路径都可以
//	if (!file.open(QFile::WriteOnly | QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
//	{
//		return;
//	}
//	QDomDocument doc;
//	//写入xml头部
//	QDomProcessingInstruction instruction; //添加处理命令
//	instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
//	doc.appendChild(instruction);
//	//添加根节点
//	QDomElement root = doc.createElement("TestPaper");
//	doc.appendChild(root);
//    TestPaperModel testPaperModel;
//    bResult = dao->QueryTestPaper(m_strTestPaper_ID, testPaperModel);
//	if (bResult == false)
//	{
//		//QMessageBox::warning(this, "错误", "检索测试膜条数据失败！", QMessageBox::Ok);
//		//MyMessageBox::warning(this, "错误", "检索测试膜条数据失败！", MyMessageBox::Ok, "OK", "");
//		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "1263"), MyMessageBox::Ok, "OK", "");
//		return;
//	}
//	QDomElement element;
//	QDomText text;
////    if (TestPaperQuery.next())
////	{
//        element = doc.createElement("CompanyID");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);
//		//articleNo
//		element = doc.createElement("articleNo");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("TotalNumber");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("Item_Number");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("Null_Number");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("TestPaparLenght");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("rect_Analysis.x");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("rect_Analysis.y");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("rect_Analysis.width");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("rect_Analysis.height");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("analysis_height_percentage");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("head_length");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("FuncPosition");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("TestAeaLenght");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("cutoffValue");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);


//		element = doc.createElement("cutoffPosition");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("isCutOff");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("isFun");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("funGrayValue");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);


//		element = doc.createElement("left_judge_value");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);


//		element = doc.createElement("wave_pix_width");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("wave_pix_width_max");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("wave_pix_width_min");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("background_values");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("zero_value_coefficient");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//		element = doc.createElement("bg_difference");
//        text = doc.createTextNode(QString::number(testPaperModel.getCompanyId()));
//		element.appendChild(text);
//		root.appendChild(element);

//	}
//    auto TestPaperItemQuery = dao->SelectTestPaperItems(m_strTestPaper_ID, &bResult);
//	if (bResult == false)
//	{
//		//QMessageBox::warning(this, "错误", "检索测试膜条数据失败！", QMessageBox::Ok);
//		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "1263"), MyMessageBox::Ok, "OK", "");
//		//K1263
//		return;
//	}
//	QString strItemNameList;
//	QString strItemPositionList;
//    while (TestPaperItemQuery.next())
//	{
//        int nIsNull = TestPaperItemQuery.value("IsNull").toInt();
//		if (nIsNull == 1)
//		{
//			strItemNameList += "NULL";
//			strItemPositionList += "0";
//		}
//		else
//		{
//            strItemNameList += TestPaperItemQuery.value("itemName").toString();
//			strItemPositionList += TestPaperItemQuery.value("position").toString();
		
//		}
//		strItemNameList += ",";
//		strItemPositionList += ",";
//	}
//	//添加名字
//	strItemNameList = strItemNameList.left(strItemNameList.length() - 1);
//	element = doc.createElement("ItemNameList");
//	text = doc.createTextNode(strItemNameList);
//	element.appendChild(text);
//	root.appendChild(element);
//	//添加位置
//	strItemPositionList = strItemPositionList.left(strItemPositionList.length() - 1);
//	element = doc.createElement("ItemPositionList");
//	text = doc.createTextNode(strItemPositionList);
//	element.appendChild(text);
//	root.appendChild(element);
//	//输出到文件
//	QTextStream out_stream(&file);
//	doc.save(out_stream, 4); //缩进4格
//	file.close();
//	//QMessageBox::information(this, "成功", "导出膜条数据文件成功！", QMessageBox::Ok);
//	MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1259"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1262"), MyMessageBox::Ok,"OK","");
//	//K1262
}


