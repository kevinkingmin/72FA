#include "TestResultDataOneType.h"
#include "../Include/Analysis/analysis.h"
#include <QMessageBox>
#include <QFileInfo>
#include <QLabel>
#include <QSqlQuery>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "src/comm/GlobalData.h"

TestResultDataOneType::TestResultDataOneType(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.tableWidget_Data->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	ui.tableWidget_Data->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
	ui.tableWidget_Data->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(ui.tableWidget_Data, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(getItemDataSlot(int)));//表格双击事件



}

void TestResultDataOneType::getItemDataSlot(int row)
{
	QTableWidgetItem *username = new QTableWidgetItem;
	username = ui.tableWidget_Data->item(row, 0);
	mytable = new ShowTestResultDetail(this);//实例化表格
	QString testId = username->text();
	//dialog->testId = testId;
	dialog = new TestResultDetailDialog(testId,"",this);
	connect(dialog, SIGNAL(UpdateTestResultTableOneTypeSignal(QString)), this, SLOT(UpdateTestResultTableOneTypeSlot(QString)));
	//关联一个single
	dialog->show();//显示弹窗
	//ui->usernameLineEdit->setText(username->text());
}

//修改完成更新结果列表
void TestResultDataOneType::UpdateTestResultTableOneTypeSlot(QString testId)
{
	//update todo
	QString a = testId;
}

TestResultDataOneType::~TestResultDataOneType()
{
}

void TestResultDataOneType::Show_UI_Data() 
{
	InitTableWidget_Data();
	InitTableWidget_H();
}

void TestResultDataOneType::InitTableWidget_H()
{
	//清空列表
	ui.tableWidget_H->setRowCount(0);
	ui.tableWidget_H->horizontalHeader()->hide();
	//不显示左边默认自带序列号
	QHeaderView* headerView = ui.tableWidget_H->verticalHeader();
	headerView->setHidden(true);
	////使行列头自适应宽度，最后一列将会填充空白部分
	ui.tableWidget_H->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_H->setSelectionMode(QAbstractItemView::NoSelection);
	ui.tableWidget_H->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑
	ui.tableWidget_H->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应行高
	ui.tableWidget_H->insertRow(0);
	addContent_H(0, 0, "测试编号");
	addContent_H(0, 1, "样本编号");
	addContent_H(0, 2, "检测类型");
	//addContent_H(0, 3, "子检测");
	addContent_H(0, 4, "");
	addContent_H(0, 5, "判读结果");

	//列表中显示图片
	QString strPath = QCoreApplication::applicationDirPath() + "\\res\\";
	QString strPathFileName = strPath + QString::number(m_nTestPaperID) + "_Header.png";
	QFileInfo fileInfo(strPathFileName);
	if (!fileInfo.isFile())
	{
	}
	QPixmap pixBig;
	pixBig.load(strPathFileName);
	int w1 = pic_width;//450;//pixBig.width();
	int h1 = pic_height;//50;// pixBig.height();


	QLabel *label1 = new QLabel;
	double dScale = (double)m_nImageColumnWidth / (double)w1;
	int nRowHeight = dScale * h1;
	QPixmap pix = pixBig.scaled(w1 * dScale, nRowHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.tableWidget_H->setColumnWidth(0, 150);
	int w = pic_width;//450;//pix.width();
	int h = pic_height;//50;// pix.height();
	int nColumnWidth = m_nImageColumnWidth;
	ui.tableWidget_H->setColumnWidth(3, m_nImageColumnWidth);
	ui.tableWidget_H->setColumnWidth(4, m_nLargerColumnWidth);
	label1->resize(nColumnWidth - 2, nRowHeight - 2);
	label1->setScaledContents(true);//设置图片适应label
	label1->setPixmap(pix);
	ui.tableWidget_H->setCellWidget(0, 3, label1);//显示label  



}


void TestResultDataOneType::InitTableWidget_Data()//初始化状态列表
{
	//清空列表
	ui.tableWidget_Data->setRowCount(0);
	ui.tableWidget_Data->horizontalHeader()->hide();
	////不显示左边默认自带序列号
	//QHeaderView* headerView = ui.tableWidget_Data->verticalHeader();
	//headerView->setHidden(true);
	////使行列头自适应宽度，最后一列将会填充空白部分
	ui.tableWidget_Data->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_Data->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	ui.tableWidget_Data->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
	ui.tableWidget_Data->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑

	QString strValue;
	QString strRel;
	QString strItemName;
	QString paper_name = "";
	double dRatioToCut;
	QString testResult = "";
	//DB中取Testitems表数据
	bool bResult = true;
    auto dao = AnalysisUIDao::instance();
	QString nSampleID = "";
	int paperId = 1;
	int nTestPaperID = 0;
	QString strPathFileName;
	QString pic_name;
	QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
	QString analysised_piture_path = "analysised";
	//以后加上公司ID
	//QString strPath = piture_root_str + "\\" + m_test_project_name + "\\" + analysised_piture_path;
	QString strPath = piture_root_str + "\\" + analysised_piture_path;
	int row = 0;
    auto SampleQuery = dao->SelectSamples2(m_test_project_name, QString::number(m_nTestPaperID), &bResult);
	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1304"), MyMessageBox::Ok, "OK", "");
		return;
	}
    while (SampleQuery.next())
	{
		ui.tableWidget_Data->insertRow(row);
        nSampleID = SampleQuery.value("sampleNo").toString();
		paper_name = SampleQuery.value("PaperName").toString();
        nTestPaperID = SampleQuery.value("paperId").toInt();
		pic_name = SampleQuery.value("testId").toString();

		ui.tableWidget_Data->setColumnWidth(0, 150);
		//测试编号
		addContent_Data(row, 0, pic_name);

		//样本编号
		//strValue = QString::number(nSampleID);
		strValue = nSampleID;
		addContent_Data(row, 1, strValue);
		//检测类型
        auto TestPaperQuery = dao->SelectTestPaper(QString::number(nTestPaperID), &bResult);
		if (bResult == false)
		{
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1263"), MyMessageBox::Ok, "OK", "");
			return;
		}
		strValue = "";
        if (TestPaperQuery.next())
		{
            strValue =TestPaperQuery.value("PaperName").toString();
		}
		addContent_Data(row, 2, strValue);
		//子检测
		//strValue = "子检测";
		//addContent_Data(row, 2, strValue);
		//列表中显示图片
		QFont font("Microsoft YaHei", 12);
		QFontMetrics fm(font);
		int pixelsHigh = fm.height();//字体高度
		int nRowHeight = pixelsHigh;//行高度
		QPixmap pixBig;
		//pixBig.load(strPath + "\\" + QString::number(nSampleID) + +"_" + QString::number(nTestPaperID) + ".png");  //图片路径
		pixBig.load(strPath + "\\" + pic_name + ".png");  //图片路径
		int w1 = pic_width;//450;//pixBig.width();
		int h1 = pic_height;//50;//pixBig.height();
		if (w1 == 0 && h1 == 0)
		{
			w1 = pic_width;//450;
			h1 = pic_height;//50;
		}
		QLabel *label1 = new QLabel;
		double dScale = (double)nRowHeight / (double)h1;
		QPixmap pix = pixBig.scaled(w1 * dScale, nRowHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		int w = pic_width;//pix.width();
		int h = pic_height;//pix.height();
		if (w == 0 || h == 0)
		{
			w = pic_width;//450;
			h = pic_height;//50;
			label1->setText("请确认膜条是否放置，或膜条已污染，查看后重新检测。");
			ui.tableWidget_Data->setCellWidget(row, 3, label1);//显示label
		}
		else
		{
			int nColumnWidth = w;
			if (row == 0)
			{
				ui.tableWidget_Data->setColumnWidth(3, nColumnWidth);
				m_nImageColumnWidth = nColumnWidth;
			}
			label1->resize(nColumnWidth - 2, nRowHeight - 2);
			label1->setScaledContents(true);//设置图片适应label
			label1->setPixmap(pix);
			ui.tableWidget_Data->setCellWidget(row, 3, label1);//显示label
		}
		QPixmap pixLarger;
		pixLarger.load(QCoreApplication::applicationDirPath() + "/res/Larger.png");  //图片路径
		int w2 = pixLarger.width();
		int h2 = pixLarger.height();
		QLabel *label2 = new QLabel;
		label2->resize(nRowHeight - 2, nRowHeight - 2);
		label2->setScaledContents(true);//设置图片适应label
		label2->setPixmap(pixLarger);
		ui.tableWidget_Data->setColumnWidth(4, nRowHeight);
		m_nLargerColumnWidth = nRowHeight;
		ui.tableWidget_Data->setCellWidget(row, 4, label2);//显示label 
		//QString strSampleID = QString::number(nSampleID);
		QString strSampleID = nSampleID;
		QString strTestPaper_ID = QString::number(nTestPaperID);
        auto TestDataQuery = dao->SelectTestData(
			pic_name,
			strSampleID,
			strTestPaper_ID,
			&bResult);
		if (bResult == false)
		{
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1174"), MyMessageBox::Ok,"OK","");
			return;
		}
		strRel = "";
        while (TestDataQuery.next())
		{
            //strItemName = TestDataQuery.value("ItemName").toString();
            //dRatioToCut = TestDataQuery.value("RatioToCut").toDouble();
			strItemName = TestDataQuery.value("projectName").toString();
			dRatioToCut = TestDataQuery.value("cutGrayValue").toDouble();
			testResult = TestDataQuery.value("testResult").toString();
			paperId = TestDataQuery.value("paperId").toInt();
			//旧的显示方式
			//if (dRatioToCut > 1 && strItemName != "FC" && strItemName != "Cut")
			//{
			//	strRel += strItemName;
			//	strRel += "(";
			//	strRel += QString::number((dRatioToCut - 1) * 100, 'f', 0);
			//	strRel += "%)  ";
			//}
			//新的显示方式
			//if (strItemName != "FC" && strItemName != "Cut")
			//{
			//	strRel += strItemName;
			//	strRel += "(";
			//	strRel += testResult;
			//	strRel += ")  ";
			//}
			if (strItemName != "FC" && strItemName != "Cut")
			{
				//根据strItemName查出项目判断规制RulesId，
				//select * from t_judge_rules where RulesId = (select RulesId from titem where itemName = 'Nucleosomes' and TestPaperID = 1)
				QString sql = "";
				//sql = "select * from t_judge_rules where RulesId = (select RulesId from titem where itemName = '" + strItemName + "' and TestPaperID=" + paperId + "";
				sql.sprintf("select * from t_judge_rules where RulesId = (select RulesId from titem where itemName = '%s' and TestPaperID =%d ) order by GrayValue asc", strItemName.toUtf8().data(), paperId);
				auto JudgeRulesQuery = dao->SelectRecord(&bResult, sql);
				QMap<double, QString> mapJudgeRules;
				testResult = "";
				while (JudgeRulesQuery.next())
				{
					double grayValue = JudgeRulesQuery.value("GrayValue").toDouble();
					QString grayWord = JudgeRulesQuery.value("GrayWord").toString();
					mapJudgeRules.insert(grayValue, grayWord);
				}
				QList<double> key_list;
				QList<QString> value_list;
				QMap<double, QString>::Iterator it = mapJudgeRules.begin();
				//while (it != mapJudgeRules.end())
				//{
				//	key_list.push_back(it.key());
				//	value_list.push_back(it.value());
				//	it++;
				//}
				int tmp_i = 0;
				while (it != mapJudgeRules.end())
				{
					if (tmp_i == 0)
					{
						key_list.push_back(-1000);
						value_list.push_back(it.value());
					}
					key_list.push_back(it.key());
					value_list.push_back(it.value());

					if (tmp_i == (mapJudgeRules.count()-1))
					{
						key_list.push_back(2000);
						value_list.push_back(it.value());
					}

					tmp_i++;

					it++;
				}

				int key_count = key_list.count();
				//找出下标，从而找出key对应的value
				int find_index = 0;
				for (int i = 0; i < key_count; )
				{
					double min = key_list[0];;
					double max = 1000;
					if (i > 0)
					{
						min = key_list[i - 1];
						max = key_list[i];

						if (dRatioToCut > min && dRatioToCut <= max)
						{
							find_index = i;
						}
					}
					/*
					double min = key_list[0];;
					double max = 1000;
					if (i == 0)
					{
						min = key_list[i];
						if (dRatioToCut <= min)
						{
							find_index = i;
						}
					}
					else if (i == key_count - 1)
					{
						max = key_list[i];
						if (dRatioToCut > max)
						{
							find_index = i;
						}
					}
					else
					{
						min = key_list[i - 1];
						max = key_list[i];
						if (dRatioToCut > min && dRatioToCut <= max)
						{
							find_index = i;
						}
					}
					if (i > 0)
					{
						min = key_list[i - 1];
						max = key_list[i];
						if (dRatioToCut > min && dRatioToCut <= max)
						{
							find_index = i - 1;
						}
					}
					*/

					i++;
				}
				if (value_list.count() > 0)
				{
					testResult = value_list[find_index];//mapJudgeRules.find(find_index).value();//.key();
				}
				strRel += strItemName;
				strRel += "(";
				strRel += testResult;
				strRel += ")  ";
			}

		}
		strValue = strRel;
		if ( strRel == "")
		{
			strValue = "无结果！";
		}
		//ui.tableWidget_Data->setColumnWidth(5, nColumnWidth * 3);
		addContent_Data(row, 5, strValue);
		row++;
	}
	if (row > 0)
	{
		/*设置让某个单元格或某行选中*/
		//选中单元格 第一行：
		//ui.tableWidget_Data->setCurrentCell(0, 0, QItemSelectionModel::Select);
	}
}

void TestResultDataOneType::addContent_H(int row, int column, QString content, int nColor) 
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	item->setBackground(QBrush(QColor(46, 140, 210)));
	//字体设置为白色
	item->setForeground(QBrush(QColor(255, 255, 255)));
	item->setTextAlignment(Qt::AlignCenter);
	////字体设置为黑色
	//if (nColor == 0)
	//	item->setForeground(QBrush(QColor(0, 0, 0)));

	////黄绿色
	//if (nColor == 1)
	//	item->setForeground(QBrush(QColor(128, 128, 0)));

	////红色
	//if (nColor == 2)
	//	item->setForeground(QBrush(QColor(255, 0, 0)));

	////绿色
	//if (nColor == 3)
	//	item->setForeground(QBrush(QColor(0, 255, 0)));

	ui.tableWidget_H->setItem(row, column, item);
}

void TestResultDataOneType::addContent_Data(int row, int column, QString content, int nColor) 
{
	QTableWidgetItem *item = new QTableWidgetItem(content);

	item->setToolTip(content);

	//字体设置为黑色
	if (nColor == 0)
		item->setForeground(QBrush(QColor(0, 0, 0)));

	//黄绿色
	if (nColor == 1)
		item->setForeground(QBrush(QColor(128, 128, 0)));

	//红色
	if (nColor == 2)
		item->setForeground(QBrush(QColor(255, 0, 0)));

	//绿色
	if (nColor == 3)
		item->setForeground(QBrush(QColor(0, 255, 0)));

	ui.tableWidget_Data->setItem(row, column, item);
}

void TestResultDataOneType::on_tableWidget_Data_cellClicked(int row, int column) 
{
}

