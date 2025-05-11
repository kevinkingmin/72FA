#include "ResultManage.h"
#include "AddTubeStep1.h"
#include <QMessageBox>
#include <QCheckBox>
#include <QCoreApplication>
#include <QtXml> //也可以include <QDomDocument>
#include<QFileDialog>
#include "src/comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"

ResultManage::ResultManage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_ShowModal, true);
	InitTableWidget();
}

ResultManage::~ResultManage()
{
}

void ResultManage::InitTableWidget() 
{
	ui.tableWidget->setRowCount(0);
	//不显示左边默认自带序列号
	QHeaderView* headerView = ui.tableWidget->verticalHeader();
	headerView->setHidden(true);
	//使行列头自适应宽度，最后一列将会填充空白部分
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑
	QString strValue;
	bool bResult = true;
    auto dao = AnalysisUIDao::instance();
	m_TubeQuery = dao->SelectResultInfo(&bResult);
	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1543"), MyMessageBox::Ok,"OK","");
		return;
	}
    if (m_TubeQuery.size() == 0)
	{
		return;
	}
	int row = 0;
    QString sID = "0";
	bool bNull = false;
    while (m_TubeQuery.next())
	{
		ui.tableWidget->insertRow(row);
		//名称
        strValue = m_TubeQuery.value("Id").toString();
		addContent(row, 0, strValue);
        strValue = m_TubeQuery.value("sampleNo").toString();
		addContent(row, 1, strValue);
		strValue = m_TubeQuery.value("samplePos").toString();
		addContent(row, 2, strValue);
		strValue = m_TubeQuery.value("bloodType").toString();
		addContent(row, 3, strValue);
		strValue = m_TubeQuery.value("PatientName").toString();
		addContent(row, 4, strValue);
		QString age_unit = m_TubeQuery.value("AgeUnitID").toString();
		QString age_unit1 = "";
		if (age_unit == "1")
		{
			age_unit1 = "岁";
		}
		else if (age_unit == "2")
		{
			age_unit1 = "月";
		}
		else if (age_unit == "3")
		{
			age_unit1 = "日";
		}
		else if (age_unit == "4")
		{
			age_unit1 = "小时";
		}
		strValue = m_TubeQuery.value("Age").toString()+""+ age_unit1;
		addContent(row, 5, strValue);
		strValue = m_TubeQuery.value("SexID").toString();
		addContent(row, 6, strValue);
		strValue = m_TubeQuery.value("paperId").toString();
		addContent(row, 7, strValue);
		strValue = m_TubeQuery.value("testTime").toString();
		addContent(row, 8, strValue);
		strValue = m_TubeQuery.value("stateFlag").toString();
		addContent(row, 9, strValue);
		row++;
	}
	if (row > 0)
	{
		/*设置让某个单元格或某行选中*/
		//选中单元格 第一行：
		ui.tableWidget->setCurrentCell(0, 0, QItemSelectionModel::Select);
	}
}


void ResultManage::addContent(int row, int column, QString content)
{
	//if (column == 1 )
	//{
	//	QCheckBox *checkBox_Item = new QCheckBox();
	//	if (content == "1")
	//		checkBox_Item->setChecked(true);
	//	else
	//		checkBox_Item->setChecked(false);
	//	ui.tableWidget->setCellWidget(row, column, (QWidget*)checkBox_Item);
	//}
	//else
	//{
	//	QTableWidgetItem *item = new QTableWidgetItem(content);
	//	ui.tableWidget->setItem(row, column, item);
	//}
	//状态 1=保存，2=测试，88=成功，-1=失败
	QString result_status = "";
	if (column == 9)
	{
		if (content == "1")
		{
			result_status = "保存";
		}
		if (content == "2")
		{
			result_status = "测试中";
		}
		if (content == "88")
		{
			result_status = "成功";
		}
		if (content == "-1")
		{
			result_status = "失败";
		}
		if (content == "0")
		{
			result_status = "未测试";
		}
		QTableWidgetItem *item = new QTableWidgetItem(result_status);
		ui.tableWidget->setItem(row, column, item);
	}
	else if (column == 3)
	{
		if (content == "1")
		{
			result_status = "血清";
		}
		if (content == "2")
		{
			result_status = "血浆";
		}
		if (content == "3")
		{
			result_status = "全血";
		}
		QTableWidgetItem *item = new QTableWidgetItem(result_status);
		ui.tableWidget->setItem(row, column, item);
	}
	else
	{
		QTableWidgetItem *item = new QTableWidgetItem(content);
		ui.tableWidget->setItem(row, column, item);
	}
}

void ResultManage::on_Add_Button_clicked()
{
	AddTubeStep1 *addTubeStep1 = new AddTubeStep1();
	connect(addTubeStep1, SIGNAL(SetRefresh(bool)), this, SLOT(getRefreshTableWidgetFlag(bool)));
	addTubeStep1->m_strTube_ID = "";
	addTubeStep1->Set_UI();
	addTubeStep1->show();
}

void ResultManage::on_Modify_Button_clicked() 
{
	AddTubeStep1 *addTubeStep1 = new AddTubeStep1();
	connect(addTubeStep1, SIGNAL(SetRefresh(bool)), this, SLOT(getRefreshTableWidgetFlag(bool)));
	int intRow = ui.tableWidget->currentRow();//获取选中的行
    if (m_TubeQuery.size() == 0)
		return;
    m_TubeQuery.seek(intRow);
    addTubeStep1->m_strTube_ID = m_TubeQuery.value("ID").toString();
	if (addTubeStep1->m_strTube_ID.length() == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1544"), MyMessageBox::Ok,"OK","");
		return;
	}
	addTubeStep1->Set_UI();
	addTubeStep1->show();
}

void ResultManage::on_Delete_Button_clicked()
{
	int intRow = ui.tableWidget->currentRow();//获取选中的行
    if (m_TubeQuery.size() == 0)
		return;

    m_TubeQuery.seek(intRow);
    QString strTube_ID = m_TubeQuery.value("ID").toString();
	if (strTube_ID.length() == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1544"), MyMessageBox::Ok,"OK","");
		return;
	}
    auto dao = AnalysisUIDao::instance();
	bool bResult;
	bResult = dao->DeleteTube(strTube_ID);
	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1545"), MyMessageBox::Ok,"OK","");
		return;
	}
	InitTableWidget();
}

void ResultManage::getRefreshTableWidgetFlag(bool bFlag)
{
    if (bFlag == true)
	{
		InitTableWidget();
	}
}

void ResultManage::on_Export_Button_clicked()
{
	int intRow = ui.tableWidget->currentRow();//获取选中的行
    if (m_TubeQuery.size() == 0)
		return;

    m_TubeQuery.seek(intRow);
    QString strTube_ID = m_TubeQuery.value("ID").toString();
	bool bResult;
    auto dao = AnalysisUIDao::instance();
	QString path = GlobalData::getExePath();
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("请输入文件名！"),
		path,
		tr("(*xml)"));

	if (fileName.length() == 0)
		return;

	fileName += tr(".xml");
	//打开或创建文件
	QFile file(fileName); //相对路径、绝对路径、资源路径都可以
	if (!file.open(QFile::WriteOnly | QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
		return;

	QDomDocument doc;
	//写入xml头部
	QDomProcessingInstruction instruction; //添加处理命令
	instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
	doc.appendChild(instruction);
	//添加根节点
	QDomElement root = doc.createElement("Tube");
	doc.appendChild(root);
	QDomElement element;
	QDomText text;
	element = doc.createElement("Name");
    text = doc.createTextNode(m_TubeQuery.value("Name").toString());
	element.appendChild(text);
	root.appendChild(element);

	element = doc.createElement("IsControl");
    text = doc.createTextNode(m_TubeQuery.value("IsControl").toString());
	element.appendChild(text);
	root.appendChild(element);

	element = doc.createElement("Inner");
    text = doc.createTextNode(m_TubeQuery.value("Inner").toString());
	element.appendChild(text);
	root.appendChild(element);

	element = doc.createElement("CupHeight");
    text = doc.createTextNode(m_TubeQuery.value("CupHeight").toString());
	element.appendChild(text);
	root.appendChild(element);

	element = doc.createElement("LiquidStartPos");
    text = doc.createTextNode(m_TubeQuery.value("LiquidStartPos").toString());
	element.appendChild(text);
	root.appendChild(element);
	//输出到文件
	QTextStream out_stream(&file);
	doc.save(out_stream, 4); //缩进4格
	file.close();
	MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1259"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1546"), MyMessageBox::Ok,"OK","");
}


void ResultManage::on_Inport_Button_clicked()
{
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
		return;
	}
	QDomElement root = doc.documentElement(); //返回根节点
	QDomNode node = root.firstChild(); //获得第一个子节点
	QString tagName;
	QString nodeValue;

	QString  strName;
	QString strIsControl;
	QString strInner;
	QString strCupHeight;
	QString strLiquidStartPos;
	bool bOverLoad = false;
	while (!node.isNull())  //如果节点不空
	{
		if (node.isElement()) //如果节点是元素
		{
			QDomElement e = node.toElement();
			tagName = e.tagName();
			nodeValue = e.text();

			if (tagName == "Name")
			{
				strName = nodeValue;
			}

			if (tagName == "IsControl")
			{
				strIsControl = nodeValue;
			}

			if (tagName == "Inner")
			{
				strInner = nodeValue;
			}

			if (tagName == "LiquidStartPos")
			{
				strLiquidStartPos = nodeValue;
			}

			if (tagName == "CupHeight")
			{
				strCupHeight = nodeValue;
			}

		}
		node = node.nextSibling();
	}

	file.close();
	QString strTube_ID;
    int nSize= m_TubeQuery.size();
	for (int i = 0; i < nSize; i++)
	{
        if (strName == m_TubeQuery.value("Name").toString())
		{
            strTube_ID = m_TubeQuery.value("ID").toString();
			break;
		}
	}
	if (strTube_ID.length() > 0)
	{
		int nRes = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1270"), MyMessageBox::Yes|MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
		if (nRes == MyMessageBox::Yes)
			bOverLoad = true;
		else
			return;
	}

    auto dao = AnalysisUIDao::instance();
	bool bResult;
	if (bOverLoad == false)
	{
		bResult = dao->InsertTube(
			strName,
			strIsControl,
			strInner,
			strLiquidStartPos,
			strCupHeight);

		if (bResult == false)
		{
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1547"), MyMessageBox::Ok,"OK","");
			return;
		}
	}
	else
	{
		bResult = dao->UpdateTube(
			strTube_ID,
			strName,
			strIsControl,
			strInner, 
			strLiquidStartPos,
			strCupHeight);

		if (bResult == false)
		{
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1548"), MyMessageBox::Ok,"OK","");
			return;
		}
	}
	MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1259"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1549"), MyMessageBox::Ok,"OK","");
	InitTableWidget();
}
