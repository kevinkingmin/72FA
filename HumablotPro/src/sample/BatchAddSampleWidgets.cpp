#include "..\include\precomp\precompile.h"
#include "BatchAddSampleWidgets.h"
#include <QColor>
#include <QDateTime>
#include <QMessageBox>
#include <QMenu>
#include <QPushButton>
#include <QRadioButton>
#include <QSqlQuery>
#include <QMap>
#include <QStandardItemModel>
#include "../Include/Utilities/log.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/DAO/Analysis/AnalysisDao.h"
#include "AddSampleWidget.h"
#include "../Include/Model/sample/SampleTestModel.h"
#include "../Include/Model/sample/BatchAddSampleModel.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"

BatchAddSampleWidgets::BatchAddSampleWidgets(QWidget *parent)
	: QMainWindow(parent), _vModel(new AddSampleVModel(this))
{
	ui.setupUi(this);
	_vModel->updateData();
	ui.mainToolBar->setVisible(false);
	ui.menuBar->setVisible(false);
	ui.mainToolBar->setVisible(false);
	ui.statusBar->setVisible(false);

	auto dao = AnalysisUIDao::instance();
	bool bResult;
	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
	GlobalData::setLanguageType(g_language_type);

	ui.tvSampleSet->setColumnCount(5);
	QHeaderView* view = new QHeaderView(Qt::Horizontal);
	QStandardItemModel* model = new QStandardItemModel;
	QStringList labels;

	labels << GlobalData::LoadLanguageInfo(g_language_type, "K1553") << GlobalData::LoadLanguageInfo(g_language_type, "K1554") << GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1041") << GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1555") << GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1049");
	//labels << "编号" << "膜条类型" << "复孔" << "样本位置" << "样本编号";
	model->setHorizontalHeaderLabels(labels);
	view->setModel(model);
	ui.tvSampleSet->setHorizontalHeader(view);
	ui.centralWidget->setStyleSheet("background-color:#FFFFFFFF;");

	ui.centralWidget->setStyleSheet("background-color:#FFFFFFFF;");
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
	ui.tvSampleSet->setColumnWidth(2, 108);
	ui.tvSampleSet->setEditTriggers(QAbstractItemView::AllEditTriggers);
	ui.tvSampleSet->setSelectionBehavior(QAbstractItemView::SelectRows);
	//ui->tvSampleSet->setSelectionMode(QTableView::SingleSelection);
	ui.tvSampleSet->setSelectionMode(QTableView::SingleSelection);
	ui.tvSampleSet->horizontalHeader()->setStretchLastSection(true);
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui.tvSampleSet->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
	//QTableWidget.verticalHeader().setSectionResizeMode(QHeaderView::);
	ui.tvSampleSet->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	ui.tvSampleSet->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//ui.tvSampleSet->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);//开启多选
	//GetTestPaperInfo();
	ui.pushButtonUpdate->setVisible(false);

	ui.label_6 -> setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1556"));
	ui.label_7->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1598"));
	ui.label->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1596"));

	ui.label_2->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1558"));

	ui.label_3->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1559"));
	ui.checkBox->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1041"));
	ui.label_4->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1560"));
	ui.pushButtonAdd->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1561"));
	ui.label_5->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1562"));
	
	ui.pushButtonDeleteAll->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1563"));
	ui.pushButtonDelete->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1140"));
	ui.pushButtonOk->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1564"));
}

BatchAddSampleWidgets::~BatchAddSampleWidgets()
{}

void BatchAddSampleWidgets::GetTestPaperInfo()
{
	m_paper_name = "";
		/*
	因为 QHeaderView 也是属于 model/view 模式所以需要一个model来提供数据供 QHeaderView来显示
	*/

	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
	ui.tvSampleSet->setColumnWidth(2, 108);
	ui.tvSampleSet->setEditTriggers(QAbstractItemView::AllEditTriggers);
	ui.tvSampleSet->setSelectionBehavior(QAbstractItemView::SelectRows);
	//ui->tvSampleSet->setSelectionMode(QTableView::SingleSelection);
	ui.tvSampleSet->setSelectionMode(QTableView::SingleSelection);
	ui.tvSampleSet->horizontalHeader()->setStretchLastSection(true);
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui.tvSampleSet->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
	ui.tvSampleSet->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
	//QTableWidget.verticalHeader().setSectionResizeMode(QHeaderView::);
	ui.tvSampleSet->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	ui.tvSampleSet->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_added_paper_number = 0;
	//保证每次进来数据清空
	m_BatchSampleList.clear();
	QVector<QString> sql_list;
	QVector<QString> Id_list;
	//createSamplePos();
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	ui.tvSampleSet->clear();
	//ui.tvSampleSet->clear();
	int row_number = ui.tvSampleSet->rowCount();
	//for (size_t i = 0; i < row_number; i++)
	//{
	//	ui.tvSampleSet->removeRow(i);
	//}
	ui.tvSampleSet->model()->removeRows(0, row_number);//->removeRows(0, ui.tvSampleSet->rowCount());
	// 或者
	//while (ui->categoryTableWidget->rowCount() != 0) {
	//	ui->categoryTableWidget->removeRow(0);
	//}
	row_number = ui.tvSampleSet->rowCount();
	quint64 id = dao->getMaxSampleNo();
	//QString createDay = QDate::currentDate().toString("yyyyMMdd");
	QString id_sz = QString("%1").arg(id);

	//ui.lineEditSampleNo->setText(id_sz);
	ui.lineEditSampleNo->setText("1");
	int company_id = dao->SelectSaveSetById(&bResult, 5).toInt();
	QString createDay = QDate::currentDate().toString("yyyy-MM-dd");
	QString sql = "";
	QString sql_getSample = QString("select A.sampleNo from tsample A,t_testpaper B where A.paperId=B.ID and B.Company_ID='%2' and A.stateFlag=1 and A.createDay='%1' GROUP BY A.sampleNo  ORDER BY  A.pkid asc  ").arg(createDay).arg(company_id);
	//QString sql_getSample = QString("select sampleNo from tsample where stateFlag=1 and createDay='%1' GROUP BY sampleNo").arg(createDay);
	auto selectSampleList = dao->SelectRecord(&bResult, sql_getSample);
	for (int i = 0; i < 72; i++)
	{
		_vModel->_vect[i].sampleNo = "";
	}
	ui.gridLayout_3->removeWidget(this);
	//清空horizontalLayout布局内的所有元素
	QLayoutItem *child;
	while ((child = ui.gridLayout_3->takeAt(0)) != 0)
	{
		//setParent为NULL，防止删除之后界面不消失
		if (child->widget())
		{
			child->widget()->setParent(this);
			delete child->widget();//释放
		}
		delete child;
	}
	m_pButtonGroup = new QButtonGroup(this);
	// 设置互斥
	m_pButtonGroup->setExclusive(true);
	QVector<HeadStrc> headv = _vModel->getHeadVect();
	m_PaperinfoMap.clear();
	for (int i = 7; i < headv.size(); ++i)
	{
		int paper_id = headv[i].paperId;
		QString paper_name = headv[i].field;
		m_PaperinfoMap.insert(headv[i].paperId, headv[i].field);//.push_back(headv[i].paperId, headv[i].patientName);
		QRadioButton *pButton = new QRadioButton(this);
		// 设置文本
		pButton->setText(QString::fromLocal8Bit("%1").arg(paper_name));
		//ui.horizontalLayout->addWidget(pButton);
		ui.gridLayout_3->addWidget(pButton);
		m_pButtonGroup->addButton(pButton);
	}
	while (selectSampleList.next())
	{
		QString sampleNo1 = selectSampleList.value("sampleNo").toString();
		QString sql_query = QString("select COUNT(*) as number, paperId,sampleNo,PatientName,samplePos from tsample where stateFlag=1 and createDay='%1' and sampleNo='%2' GROUP BY paperId").arg(createDay).arg(sampleNo1);
		auto countNumberQuery = dao->SelectRecord(&bResult, sql_query);
		//select COUNT(*) as number, paperId,sampleNo,PatientName,samplePos from tsample where stateFlag=1 and createDay='2022-06-13' and sampleNo='aaa' GROUP BY paperId
		while (countNumberQuery.next())
		{
			SampleTestModel stm;
			int number = countNumberQuery.value("number").toInt();
			int samplePos = countNumberQuery.value("samplePos").toInt();
			int paperId = countNumberQuery.value("paperId").toInt();
			QString sampleNo = countNumberQuery.value("sampleNo").toString();
			QString PatientName = countNumberQuery.value("PatientName").toString();
			//_vModel->_vect[samplePos].test.setTestId(sampleNo);
			_vModel->_vect[samplePos].sampleNo = sampleNo;
			//_vModel->_vect[samplePos].samplePos = samplePos;//.setSamplePos(samplePos);
			//_vModel->_vect[samplePos].//.setPaperId(paperId);
			_vModel->_vect[samplePos].patientName = PatientName;//(PatientName);
			auto map = _vModel->_vect[samplePos].paperCheckedCountMap;//it.paperCheckedCountMap;
			int paper_id_new = GetPaperId1(paperId);
			std::tuple tp(true, number);
			_vModel->_vect[samplePos].paperCheckedCountMap.insert(paper_id_new, tp);
			QString paper_name = m_PaperinfoMap.value(paperId);
			BatchAddSampleModel basm;
			basm.setNo(samplePos);
			basm.setPaperName(paper_name);
			basm.setPaperNumber(number);
			basm.setSampleNo(sampleNo);
			m_BatchSampleList.append(basm);
			int rowCount = ui.tvSampleSet->rowCount();//ui.tvSampleSet->rowCount();
			QString id = QString("%1").arg(rowCount+1);
			ui.tvSampleSet->insertRow(rowCount);
			QTableWidgetItem * xitem1 = new QTableWidgetItem(id);
			xitem1->setTextAlignment(Qt::AlignCenter);
			QTableWidgetItem * xitem2 = new QTableWidgetItem(paper_name);
			xitem2->setTextAlignment(Qt::AlignCenter);
			QString sz_number = QString("%1").arg(number);
			QTableWidgetItem * xitem3 = new QTableWidgetItem(sz_number);
			xitem3->setTextAlignment(Qt::AlignCenter);
			QString show_str = QString("%1").arg(samplePos + 1);
			QTableWidgetItem * xitem4 = new QTableWidgetItem(show_str);
			xitem4->setTextAlignment(Qt::AlignCenter);
			show_str = QString("%1").arg(sampleNo);
			QTableWidgetItem * xitem5 = new QTableWidgetItem(show_str);
			xitem5->setTextAlignment(Qt::AlignCenter);
			ui.tvSampleSet->setItem(rowCount, 0, xitem1);
			ui.tvSampleSet->setItem(rowCount, 1, xitem2);
			ui.tvSampleSet->setItem(rowCount, 2, xitem3);
			ui.tvSampleSet->setItem(rowCount, 3, xitem4);
			ui.tvSampleSet->setItem(rowCount, 4, xitem5);
			ui.tvSampleSet->setRowHeight(rowCount, 20);
		}
	}

	// 连接信号槽
	connect(m_pButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton *button) {
		m_paper_name = button->text();
		/* ... */ });
}


int BatchAddSampleWidgets::GetPaperId1(int ii)
{
	int id = 0;
	auto head = _vModel->getHeadVect();
	for (auto it : head)
	{
		if (ii == it.paperId && it.id > 6)
		{
			id = it.id;
			break;
		}
	}
	return id;
}


int BatchAddSampleWidgets::GetPaperId(int ii)
{
	int paper_id = 0;
	auto head = _vModel->getHeadVect();
	for (auto it : head)
	{
		if (ii == it.id)
		{
			paper_id = it.paperId;
			break;
		}
	}
	return paper_id;
}


void BatchAddSampleWidgets::updatePage(dataStrc *data)
{
	//beginResetModel();
	m_data = data;
	//endResetModel();
}

void BatchAddSampleWidgets::on_pushButtonAdd_clicked()
{
	if (m_paper_name == "")
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1391"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	QString sample_no = ui.lineEditSampleNo->text();
	INT64 sample_no_i = 0;
	QRegExp regExp("^[A-Za-z0-9]+$");
	if (regExp.exactMatch(sample_no)) {
		// 匹配成功，字符串只包含字母和数字
		//qDebug() << "String only contains letters and numbers.";
	}
	else {
		// 匹配失败，字符串含有其它字符
		//qDebug() << "String contains characters other than letters and numbers.";
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1392"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	if (sample_no.length() > 20)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1393"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}

	QString sample_start_index = ui.lineEditSampleStartIndex->text();
	QString sample_end_index = ui.lineEditSampleEndIndex->text();
	int sample_start_index1 = ui.lineEditSampleStartIndex->text().toInt();
	int sample_end_index1 = ui.lineEditSampleEndIndex->text().toInt();

	if (sample_start_index1 == 0 )
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1394"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	if (sample_end_index1 == 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1395"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}

	if (sample_start_index1 > sample_end_index1)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1396"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	//需要膜条数量
	int need_paper_number = 0;
	//quint64 aaa = sample_no.toLongLong();//toInt();
	//quint64 sample_no_i = aaa + (sample_end_index1 - sample_start_index1);
	if (sample_start_index1 > 72 || sample_start_index1 < 1)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1397"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	if (sample_end_index1 > 72 || sample_end_index1<1)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1398"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	//QString paper_start_index = ui.lineEditPaperStartIndex->text();
	//是否复孔
	bool duplicate_hole = ui.checkBox->checkState();//->isCheckable();
	//复孔数量
	QString duplicate_number;
	duplicate_number = ui.lineEditPaperEndIndex->text();
	if (duplicate_number.toInt() == 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1399"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}
	if (duplicate_number.toInt() > 1 && !duplicate_hole)
	{
		int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1400"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
		if (ret == MyMessageBox::Ok) {
			ui.checkBox->setChecked(true);
			duplicate_hole = true;
		}else
		{
			ui.checkBox->setChecked(false);
			ui.lineEditPaperEndIndex->setText("1");
			//ui.checkBox->setCheckState(true);
		}
	}

	if (duplicate_hole)
	{
		duplicate_number = ui.lineEditPaperEndIndex->text();
	}
	else
	{
		duplicate_number = "1";
	}

	m_added_paper_number = 0;

	for (size_t i = 0; i < m_BatchSampleList.size(); i++)
	{
		m_added_paper_number += m_BatchSampleList[i].getPaperNumber();
	}

	need_paper_number = ((sample_end_index1 - sample_start_index1) + 1)*duplicate_number.toInt();

	if ((m_added_paper_number + need_paper_number) > 72)
	{
		QString str = QString("%3 %1，%4 %2 %5").arg(m_added_paper_number).arg((72- m_added_paper_number-1)<0?0: (72 - m_added_paper_number - 1)).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1401")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1402")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1403"));
		int max_number_tmp = ui.lineEditSampleEndIndex->text().toInt();
		int iii_tmp = max_number_tmp - (max_number_tmp - (72 - m_added_paper_number));
		ui.lineEditSampleEndIndex->setText(QString("%1").arg(sample_start_index1 + iii_tmp -1));
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), str, MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}

	QString paper_name = m_paper_name;//m_pButtonGroup->checkedButton.checkedButton
	int rowCount = ui.tvSampleSet->rowCount();//ui.tvSampleSet->rowCount();

	QString sample_middle = "0";
	if (sample_end_index > 10)
	{
		sample_middle = "00";
		sample_start_index = QString("%1%2").arg(sample_no).arg(sample_middle);
	}
	else
	{
		sample_middle = "000";
		sample_start_index = QString("%1%2").arg(sample_no).arg(sample_middle);

	}

	bool is_return = false;
	//int added_paper_number = 0;
	m_added_paper_number = 0;
	if (m_BatchSampleList.size() > 0)
	{
		for (size_t i = 0; i < m_BatchSampleList.size(); i++)
		{
			int sample_index = m_BatchSampleList[i].getNo();
			m_added_paper_number += m_BatchSampleList[i].getPaperNumber();
			if (sample_start_index1-1 == sample_index)
			{
				MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1404"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
				is_return = true;
				break;

			}
			if (sample_end_index1-1 == sample_index)
			{
				MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1404"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
				is_return = true;
				break;
			}
		}

		if ((m_BatchSampleList.size()+(sample_end_index1- sample_start_index1)) > 72)
		{
			//QString str = QString("合共样本位输入超72，已占用样本位：%1，还可以输入样本位：%2，请重新输入。").arg(m_added_paper_number).arg(72 - m_added_paper_number-1);
			//QMessageBox::information(NULL, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), str, "确定");
			//QMessageBox::information(NULL, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "合共样本输入超72，请重新输入", "确定");
			QString str = QString("%3%1，%4%2%5").arg(m_added_paper_number).arg(72 - m_added_paper_number - 1).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1401")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1402")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1403"));
			int max_number_tmp = ui.lineEditSampleEndIndex->text().toInt();
			int iii_tmp = max_number_tmp - (max_number_tmp - (72 - m_added_paper_number));
			ui.lineEditSampleEndIndex->setText(QString("%1").arg(sample_start_index1 + iii_tmp - 1));
			MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), str, MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
			return;
		}

		if (m_BatchSampleList.size() > 72 || m_added_paper_number >72)
		{
			MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1405"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
			return;
		}
	}

	if (is_return)
	{
		is_return = false;
		return;
	}

	if ((sample_end_index1) > 72)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1405"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}

	if (isPureNumber(sample_no))
	{
		sample_no_i = sample_no.toLongLong();//.toInt();
	}

	//BatchAddSampleModel
	for (size_t i = sample_start_index1; i < (sample_end_index1) + 1; i++)
	{
		BatchAddSampleModel basm;
		basm.setNo(i-1);
		basm.setPaperName(paper_name);
		basm.setPaperNumber(duplicate_number.toInt());

		QString sample_no_tmp = "";
		if (isPureNumber(sample_no))
		{
			sample_no_tmp = QString("%1").arg(sample_no_i);
			sample_no_i++;
		}
		else
		{
			QString sz = sample_no;
			int lastIndex = 0;
			for (int i = sz.length() - 1; i >= 0; i--) {
				if (!sz.at(i).isDigit()) {
					lastIndex = i;
					break;
				}
			}

			QString firstPart = sz.left(lastIndex + 1);
			QString secondPart = sz.mid(lastIndex + 1);
			int count = secondPart.lastIndexOf(QRegExp("[^0]"));

			if (count >= 0)
			{
				QString zerosBeforeOne = secondPart.left(count);
				if ((secondPart.toInt() + sample_no_i) >= 10)
				{
					zerosBeforeOne = zerosBeforeOne.left(zerosBeforeOne.length() - 1);
				}

				if ((secondPart.toInt() + sample_no_i) >= 100)
				{
					zerosBeforeOne = zerosBeforeOne.left(zerosBeforeOne.length() - 2);
				}
				sample_no_tmp = QString("%1%2%3").arg(firstPart).arg(zerosBeforeOne).arg(secondPart.toInt() + sample_no_i);
			}
			else
			{
				sample_no_tmp = QString("%1%2").arg(firstPart).arg(secondPart.toInt() + (sample_no_i+1));
			}
			sample_no_i++;
		}

		basm.setSampleNo(sample_no_tmp);
		//sample_id_paper_number_map.insert(i, duplicate_number.toInt());
		//sample_id_paper_number_map.ad
		//BatchAddSampleModel batch_add_sample_model;//= new BatchAddSampleModel;
		//batch_add_sample_model.setSampleNo(i);
		//batch_add_sample_model._sample_id_paper_number_map
		m_BatchSampleList.append(basm);
	}
	SaveSample();
	GetTestPaperInfo();
	//QString id = QString("%1").arg(rowCount);
	//ui.tvSampleSet->insertRow(rowCount);

	//QTableWidgetItem * xitem1 = new QTableWidgetItem(id);
	//xitem1->setTextAlignment(Qt::AlignCenter);

	//QTableWidgetItem * xitem2 = new QTableWidgetItem(paper_name);
	//xitem2->setTextAlignment(Qt::AlignCenter);

	//QTableWidgetItem * xitem3 = new QTableWidgetItem(duplicate_number);
	//xitem3->setTextAlignment(Qt::AlignCenter);

	//QString show_str = QString("%1%2").arg("").arg("");
	//QTableWidgetItem * xitem4 = new QTableWidgetItem(show_str);
	//xitem4->setTextAlignment(Qt::AlignCenter);

	//show_str = QString("%1%2").arg("").arg("");
	//QTableWidgetItem * xitem5 = new QTableWidgetItem(show_str);
	//xitem5->setTextAlignment(Qt::AlignCenter);

	//ui.tvSampleSet->setItem(rowCount, 0, xitem1);
	//ui.tvSampleSet->setItem(rowCount, 1, xitem2);
	//ui.tvSampleSet->setItem(rowCount, 2, xitem3);
	//ui.tvSampleSet->setItem(rowCount, 3, xitem4);
	//ui.tvSampleSet->setItem(rowCount, 4, xitem5);
	//ui.tvSampleSet->setRowHeight(rowCount, 20);

	//SampleTestModel stm;
	//stm.getArticleNo();

	//while (selectSampleList.next())
	//{
	//	QString sampleNo1 = selectSampleList.value("sampleNo").toString();
	//	QString sql_query = QString("select COUNT(*) as number, paperId,sampleNo,PatientName,samplePos from tsample where stateFlag=1 and createDay='%1' and sampleNo='%2' GROUP BY paperId").arg(createDay).arg(sampleNo1);
	//	auto countNumberQuery = dao->SelectRecord(&bResult, sql_query);
	//	//select COUNT(*) as number, paperId,sampleNo,PatientName,samplePos from tsample where stateFlag=1 and createDay='2022-06-13' and sampleNo='aaa' GROUP BY paperId
	//	while (countNumberQuery.next())
	//	{
	//		SampleTestModel stm;
	//		int number = countNumberQuery.value("number").toInt();
	//		int samplePos = countNumberQuery.value("samplePos").toInt();
	//		int paperId = countNumberQuery.value("paperId").toInt();
	//		QString sampleNo = countNumberQuery.value("sampleNo").toString();
	//		QString PatientName = countNumberQuery.value("PatientName").toString();

	//		_vModel->_vect[samplePos].sampleNo = sampleNo;
	//		_vModel->_vect[samplePos].patientName = PatientName;//(PatientName);
	//		auto map = _vModel->_vect[samplePos].paperCheckedCountMap;//it.paperCheckedCountMap;
	//		int paper_id_new = GetPaperId1(paperId);
	//		std::tuple tp(true, number);
	//		_vModel->_vect[samplePos].paperCheckedCountMap.insert(paper_id_new, tp);

	//	}
	//}
	//QTableWidget.verticalHeader().setSectionResizeMode(QHeaderView.Fixed)
	//ui.tvSampleSet->verticalHeader()->SectionResizeMode(QHeaderView::Stretch);
	//	ui.tvSampleSet->verticalHeader()->SectionResizeMode(0, QHeaderView::ResizeToContents)
	//ui.tvSampleSet->setItem(table_len, 0, new QTableWidgetItem(data::current_date.mid(0, 10)));
	//ui.tvSampleSet->setItem(table_len, 1, new QTableWidgetItem(data::current_date.mid(11, 17)));
}

bool BatchAddSampleWidgets::isPureNumber(const QString& str) {
	QRegularExpression regex("^\\d+$");  // 正则表达式匹配纯数字
	QRegularExpressionMatch match = regex.match(str);
	return match.hasMatch();
}

void BatchAddSampleWidgets::on_pushButtonDeleteAll_clicked()
{
	QString need_delete = "";
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	//int id = ui.tvSampleSet->item(i, 1)->text().toUInt();
	int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1406"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
	if (ret == MyMessageBox::Ok) {
		for (size_t j = 0; j < m_BatchSampleList.size(); j++)
		{
			ui.tvSampleSet->removeRow(j);
			QString sample_no = m_BatchSampleList[j].getSampleNo();
			need_delete += QString("%1,").arg(j);
			QString sql_delete = QString("delete from tsample where sampleNo='%1' and stateFlag=1").arg(sample_no);
			dao->SelectRecord(&bResult, sql_delete);
		}
	}
	else
	{
	}
	GetTestPaperInfo();
}

void BatchAddSampleWidgets::on_pushButtonDelete_clicked()
{
	// 获取当前选择的单元格列表
	QList<QTableWidgetItem *> items = ui.tvSampleSet->selectedItems();
	if (items.isEmpty()) {
		// 没有选择任何行
		MyMessageBox::information(NULL, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1407"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}
	else {
		// 至少选择了一行
	}
	int i = ui.tvSampleSet->currentRow();
	int size = m_BatchSampleList.size();
	int paper_number = ui.tvSampleSet->item(i, 2)->text().toUInt();
	int sample_start_id = ui.tvSampleSet->item(i, 3)->text().toUInt();
	int sample_end_id = ui.tvSampleSet->item(i, 4)->text().toUInt();
	int sample_space = sample_end_id;
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	QString createDay = QDate::currentDate().toString("yyyy-MM-dd");
	QString need_delete = "";
	//int id = ui.tvSampleSet->item(i, 1)->text().toUInt();
	int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1406"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
	if (ret == MyMessageBox::Ok) {
		QString sql_delete = QString("delete from tsample where sampleNo='%1'  and stateFlag=1").arg(sample_space);
		dao->SelectRecord(&bResult, sql_delete);
	}
	else
	{
	}
	GetTestPaperInfo();
}

void BatchAddSampleWidgets::on_pushButtonUpdate_clicked()
{
	//for (size_t j = 0; j < m_BatchSampleList.size(); j++)
	//{
	//}
	SaveSample();
}

void BatchAddSampleWidgets::on_pushButtonOk_clicked()
{
	//lineEditSampleNo
	QString sz = "67777777777777777777777";
	emit sglFromBatchSample(sz);
	this->close();
}

void BatchAddSampleWidgets::SaveSample()
{
	if (m_BatchSampleList.size()==0)
	{
		return;
	}
	QVector<QString> sql_list;
	//去插入的时候查询样本编号是不是存在样本表中
	QVector<QString> sample_list;
	QVector<QString> samplePos_list;
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	quint64 id = dao->getMaxId();
	QString createDay = QDate::currentDate().toString("yyyy-MM-dd");
	//删除当天，旧的，未检验的项目信息。
	int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1408"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1409"), MyMessageBox::Ok| MyMessageBox::No,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
	if (ret == MyMessageBox::Ok) {
		QString sql_delete = QString("delete from tsample where  createDay='%1' and stateFlag=1").arg(createDay);
		dao->SelectRecord(&bResult, sql_delete);
	}
	else
	{
		return;
	}

	auto dao1 = AnalysisDao::instance();
	int test_batch_max = dao1->GetTestBacthMax();
	test_batch_max = 1;

	for (size_t i = 0; i < m_BatchSampleList.size(); i++)
	{
		QString paper_name = m_BatchSampleList[i].getPaperName();
		int key = m_PaperinfoMap.key(paper_name);
		int paper_number = m_BatchSampleList[i].getPaperNumber();
		//m_BatchSampleList[i].getSampleNo().to
		//QString sampleNo = m_BatchSampleList[i].getSampleNo();//"";
		QString sampleNo = QString("%1").arg(m_BatchSampleList[i].getSampleNo());//m_BatchSampleList[i].getSampleNo();//"";
		QString samplePos = QString("%1").arg(m_BatchSampleList[i].getNo());//"";
		QString paper_id = QString("%1").arg(key);
		QString PatientName = "";
		QString SexID = "0";
		QString id = "0";
		QString Age = "0";
		for (int jj = 0; jj < paper_number; jj++)
		{
			QString sql = QString("insert tsample(sampleNo,samplePos,paperId,PatientName,SexID,Age,id,stateFlag,paperPos,createDay,test_batch)VALUES('%1',%2,%3,'%4',%5,%6,'%7',1,0,'%8',%9)").arg(sampleNo).arg(samplePos).arg(paper_id).arg(PatientName).arg(SexID).arg(Age).arg(sampleNo).arg(createDay).arg(test_batch_max);
			sql_list.append(sql);
			sample_list.append(sampleNo);
			samplePos_list.append(samplePos);
		}
	}

	QString sql = "";
	for (int iv = 0; iv < sql_list.size(); ++iv)
	{
		sql = sql_list.at(iv);
		QString sql_query = "";
		dao->addRecord(&bResult, sql);
		if (bResult)
		{
			//QMessageBox::information(NULL, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "保存成功", "确定");
			//tip += "保存成功";
		}
	}
	/*
	QVector<QString> Id_list;
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	quint64 id = dao->getMaxId();
	QString createDay = QDate::currentDate().toString("yyyy-MM-dd");
	//id += 1;
	auto vect = _vModel->getVect();
	auto head = _vModel->getHeadVect();
	QMap<SampleStrc, QVector<int>> tempMap;
	_samplePaperIdMap.swap(tempMap);
	int i = 0;
	QString tip = "";
	for (auto it : vect)
	{
		if (_vModel->_vect[i].sampleNo != "")
		{
			//if (it.sampleNo.simplified().isEmpty())
			//	continue;
			//m.samplePos = it.samplePos;
			//_vModel->_vect[i].sampleNo = "";
			//_vModel->_vect[i].cupType = 1;
			//_vModel->_vect[i].articleNo = "货号";
			//_vModel->_vect[i].age = 20;
			//_vModel->_vect[i].patientName = "张三";
			//QMap<int, std::tuple<bool, int>>paperCheckedCountMap1;
			QString sampleNo = _vModel->_vect[i].sampleNo;
			int samplePos = _vModel->_vect[i].samplePos - 1;
			//int paperId = _vModel->_vect[i].;
			QString PatientName = _vModel->_vect[i].patientName;
			int SexID = _vModel->_vect[i].sexID;
			int Age = _vModel->_vect[i].age;
			int paper_id = 0;
			auto map = _vModel->_vect[i].paperCheckedCountMap;
			int ii = 0;
			QString sql_delete = QString("delete from tsample where sampleNo='%1' and createDay='%2' and samplePos=%3 and stateFlag=1").arg(sampleNo).arg(createDay).arg(samplePos);
			dao->SelectRecord(&bResult, sql_delete);
			for (auto m = map.begin(); m != map.end(); m++)
			{
				int paper_id_tmp = m.key();
				auto isChecked = std::get<0>(m.value());
				int number = std::get<1>(m.value());
				for (size_t jj = 0; jj < number; jj++)
				{
					paper_id = GetPaperId(paper_id_tmp);
					if (isChecked)
					{
						QString sql = "";
						QString sql_query = QString("select * from tsample where sampleNo='%1' and createDay='%2' and samplePos=%3  and stateFlag=1").arg(sampleNo).arg(createDay).arg(samplePos);
						auto countNumberQuery = dao->SelectRecord(&bResult, sql_query);
						int number = 0;
						while (countNumberQuery.next())
						{
							QString id = countNumberQuery.value("Id").toString();
							Id_list.append(id);
							number++;
						}
						if (number > 0)
						{
							QString id11 = Id_list.at(ii);
							//生成修改sql
							sql = QString("update tsample set samplePos=%1,paperId=%2,PatientName='%3',SexID=%4,Age=%5,stateFlag=1,paperPos=0 where Id=%6 and samplePos=%1").arg(samplePos).arg(paper_id).arg(PatientName).arg(SexID).arg(Age).arg(id11);
							sql_list.append(sql);
						}
						else
						{
							id += 1;
							//生成添加sql
							sql = QString("insert tsample(sampleNo,samplePos,paperId,PatientName,SexID,Age,id,stateFlag,paperPos,createDay)VALUES('%1',%2,%3,'%4',%5,%6,%7,1,0,'%8')").arg(sampleNo).arg(samplePos).arg(paper_id).arg(PatientName).arg(SexID).arg(Age).arg(id).arg(createDay);
							sql_list.append(sql);
						}
						ii++;
					}
				}
			}
			//QVector<QString>::iterator iter;
			//for (iter = sql_list.begin(); iter != sql_list.end(); iter++) {
			//	QString sql = "";
			//	sql = *iter;
			//	dao->addRecord(&bResult, sql);
			//	if (bResult)
			//	{
			//		tip += "保存成功";
			//	}
			//}
			for (int iv = 0; iv < sql_list.size(); ++iv)
			{
				QString sql = "";
				sql = sql_list.at(iv);
				QString sql_query = "";
				dao->addRecord(&bResult, sql);
				if (bResult)
				{
					tip += "保存成功";
				}
			}
			sql_list.clear();
		}
		i++;
	}
	if (tip != "")
	{
		//emit ChangeBtnNextSignal(true);
		QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("保存成功"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
	}
	*/

}
//关闭事件
void BatchAddSampleWidgets::closeEvent(QCloseEvent *e) {
	int ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1410"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
	if (ret== MyMessageBox::Ok) {
		//关闭窗口
		//处理关闭窗口事件，接受事件，事件就不会往下再传递
		e->accept();
		m_added_paper_number = 0;
	}
	else {
		//不关闭窗口
		//忽略事件，事件继续给 父组件 传递
		e->ignore();
	}
}

