#include "TestResultDataManage.h"
#include "TestResultDataAll.h"
#include "TestResultDataOneType.h"
#include <qmessagebox.h>
#include <QSqlQuery>
#include <QMainWindow>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "src/comm/GlobalData.h"

TestResultDataManage::TestResultDataManage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_ShowModal, true);
}

TestResultDataManage::~TestResultDataManage()
{
}

void TestResultDataManage::slotUpdateStatus(QString a, QString b)
{
	emit sglUpdateStatus(a,b);
}

void TestResultDataManage::Show_UI_Data() 
{
	ui.tabWidget->setTabPosition(QTabWidget::South);
	ui.tabWidget->clear();
	TestResultDataAll *testResultDataAll = new TestResultDataAll();
	testResultDataAll->m_test_project_name = this->m_test_project_name;
	testResultDataAll->Show_UI_Data("");
	ui.tabWidget->addTab(testResultDataAll, "概述");


	connect(this, SIGNAL(sglUpdateStatus(QString, QString)), testResultDataAll, SLOT(sltUpdateTestResultDataList(QString, QString)));

	bool bResult = true;
    auto dao = AnalysisUIDao::instance();
    auto TestPaperListQuery = dao->SelectTestPaperIDs(m_test_project_name, &bResult);
	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1304"), MyMessageBox::Ok, "OK", "");
		return;
	}

    int nTestPaperTypeNumber = TestPaperListQuery.size();
	int nTestPaperID = 0;
	QString strTestPaperName;
	int index = 0;
 //   while (TestPaperListQuery.next())
	//{
	//	if (index == 0)
	//	{
	//		nTestPaperID = TestPaperListQuery.value("paperId").toInt();
	//		TestResultDataOneType *testResultDataOneType = new TestResultDataOneType();
	//		testResultDataOneType->m_test_project_name = this->m_test_project_name;
	//		testResultDataOneType->m_nTestPaperID = nTestPaperID;
	//		testResultDataOneType->Show_UI_Data();
	//		auto TestPaperQuery = dao->SelectTestPaper(QString::number(nTestPaperID), &bResult);
	//		if (bResult == false)
	//		{
	//			QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "检索测试膜条数据失败！", QMessageBox::Ok);
	//			return;
	//		}
	//		if (TestPaperQuery.next())
	//		{
	//			strTestPaperName = TestPaperQuery.value("PaperName").toString();
	//		}
	//		ui.tabWidget->addTab(testResultDataOneType, strTestPaperName);
	//	}
	//	index++;
	//}

}
