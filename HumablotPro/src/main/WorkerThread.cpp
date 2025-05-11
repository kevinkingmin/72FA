#include "workerthread.h"
#include <QMetaObject>
#include <QThread>
//#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include <QMessageBox>
#include <string>
#include <QDateTime>
#include "src/Camera/Camera.h"
#include "src/comm/ObjectTr.h"
#include <QToolBar>
#include <QToolButton>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QtXml> //也可以include <QDomDocument>
#include <QFileDialog>
#include "src/sample/TestSampleWidget.h"
#include "src/comm/Global.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QDate>
#include <QVector>
#include <QMap>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"


WorkerThread::WorkerThread(TcpClient *tcpClient, QObject *parent) : QThread(parent), m_tcpClient(tcpClient) {
	m_tcpClient = tcpClient;
}

void WorkerThread::run()
{
	bool bResult;
	auto dao = AnalysisUIDao::instance();
	QString auto_update_lis_flage = dao->SelectTargetValueDes(&bResult, "9994");
	if (auto_update_lis_flage == "1")
	{
		QString testId = "";
		QString query_sql_testid = "";
		// 获取当前日期
		QDate currentDate = QDate::currentDate();
		// 格式化日期为 "yyyy-MM-dd"
		QString formattedDate = currentDate.toString("yyyy-MM-dd");
		query_sql_testid = QString(" SELECT DISTINCT tsample.testId as Id1 from tsample,tsample_test WHERE tsample.testId=tsample_test.Id  and tsample_test.sendLisFlag=1 and testTime>'%1'").arg(formattedDate);
		auto TestDataQuery_testid = dao->SelectRecord(&bResult, query_sql_testid);//SelectTestDataByTestId(testId, &bResult);
		while (TestDataQuery_testid.next())
		{
			testId = TestDataQuery_testid.value("Id1").toString();
			QString query_sql = "";
			query_sql = QString("SELECT * from tsample,tsample_test WHERE tsample.testId=tsample_test.Id and tsample_test.sendLisFlag=1 and tsample_test.Id='%1'").arg(testId);
			auto TestDataQuery = dao->SelectRecord(&bResult, query_sql);//SelectTestDataByTestId(testId, &bResult);
			QString send_sz = "";
			int iii_count = 0;
			while (TestDataQuery.next())
			{
				QString id = TestDataQuery.value("sampleNo").toString();
				if (iii_count == 0)
				{
					send_sz += QString("%1MSH |^ |||||MSH |^ |||||  %2 || OUL ^ R22 |  | P | 2.5.1 ||| AL | AL || ASCII |||%3").arg(QChar(0x0B)).arg(id).arg(QChar(0x0D));
					send_sz += QString("PID | %1 |||||| %1 | 0 ||||||||||||||||||||||| %2").arg(id).arg(QChar(0x0D));//"PID | " + List[0].SampleNo + " |||||| " + List[0].SampleNo + " | 0 |||||||||||||||||||||||" + getstringforbyte(0x0D);
					send_sz += QString("OBR | 4 | %1  | 4 | E - LAB ^ ES - 480 | N | %1 | %1  ||||||||| ||||  |||||||||||||||||||||||||||| %2").arg(id).arg(QChar(0x0D));//"OBR | 4 | " + List[0].SampleNo + " | 4 | E - LAB ^ ES - 480 | N | " + List[0].SampleNo + " | " + List[0].SampleNo + " ||||||||| ||||  ||||||||||||||||||||||||||||" + getstringforbyte(0x0D);
				}
				QString testTime = TestDataQuery.value("testTime").toString();
				QString testResult = TestDataQuery.value("testResult").toString();
				QString projectName = TestDataQuery.value("projectName").toString();
				double testGrayValue = TestDataQuery.value("testGrayValue").toDouble();
				send_sz += QString("OBX | |NM|%1||%2|F%3||%4 |||| F ||| BetchNo || Admin || HumaBlot 72FA  | %5").arg(testTime).arg(projectName).arg(testResult).arg(testGrayValue).arg(QChar(0x0D));; //"OBX | " + "" + "|NM|" + s.TestTime + "||" + s.ProjectName + "|F" + s.TestResult + "||" + s.TestGrayValue + " |||| F ||| 批号 || Admin || HumaBlot 72FA  | " + "" + "" + getstringforbyte(0x0D);
				iii_count++;
			}
			send_sz += QString("%1%2").arg(QChar(0x1C)).arg(QChar(0x0D));

			if (m_tcpClient->m_connectedState)
			{
				QString sql = QString("update tsample_test set sendLisFlag=2 where Id = '%1' ").arg(testId);
				dao->SelectRecord(&bResult, sql);
				emit sendDataToServer(send_sz);
			}
			else
			{
				//MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1736"), MyMessageBox::Ok, "OK", "");
				//return;
				////请连接LIS
			}
			QThread::sleep(1);
		}
	}


	// 在子线程中使用传入的 tcpClient 发送数据
	//QMetaObject::invokeMethod(m_tcpClient, "sendData", Qt::QueuedConnection, Q_ARG(QString, "耗时数据"));
}
