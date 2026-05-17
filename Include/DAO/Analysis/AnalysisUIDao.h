#pragma once

#include <QObject>
#include <QVector>
#include <QSqlRecord>
#include "../dao.h"
#include "../Include/Model/result/JudgeRules.h"
#include "../Include/Model/baseSet/TestPaperModel.h"

template<class T>
class Singleton;
class QSqlQuery;
class ProcessParaModel;


class DAOSHARED_EXPORT AnalysisUIDao
{
private:
    AnalysisUIDao();
    AnalysisUIDao(AnalysisUIDao &)=delete;
    AnalysisUIDao(AnalysisUIDao &&)=delete;
    AnalysisUIDao &operator=(const AnalysisUIDao&)=delete;
    AnalysisUIDao &operator=(AnalysisUIDao&&)=delete;
    friend Singleton<AnalysisUIDao>;

public:
    ~AnalysisUIDao();
    static AnalysisUIDao *instance();

	int SelectLisUseOrNot(bool *bResult);
	int SelectAstmOrHl7(bool *bResult);
	QString SelectLisIPAdress(bool *bResult);
	int SelectLisPort(bool *bResult);
    QSqlQuery SelectLisInfos(bool *bResult);
	QString SelectTestPicturesRootPath(bool *bResult);
    QString SelectTestReportsRootPath(bool *bResult);
	//周、月维护完成时间
	QString SelectMaintenanceFinishTime(bool *bResult,int id);
	QString SelectCutOffThreshold(bool *bResult);
	bool InsertSystemSet(QString strID,QString strsaveDes);
	bool UpdateSystemSet(QString strID,QString strsaveDes);
	bool UpdateSystemDes(QString strID, QString strsaveDes);
    bool UpdateSystemSetId5(QString strID, QString strsaveDes);
    QSqlQuery SelectTestPaperIDs(QString strProjectName, bool *bResult);
    QSqlQuery SelectSamples(QString strProjectName, bool *bResult);
	//查询sample_test表中数据量
    int SelectSampleTestTotalNumber(QString test_id);
	//结果数据表中总数量
	QString SelectTotalNumber(int paper_id, QString start_time, QString end_time);
	//取得最大,最小pkid号
    int SelectMaxPkid(int paper_id,QString start_time,QString end_time);
	//整理pkid
	QSqlQuery ReNewPkid(bool *bResult);
	QSqlQuery SelectSamplesByQuery(QString start_time, QString end_time, QString project_name, QString strProjectName, bool *bResult, int one_page_number, int page_index);
	QVector<QSqlRecord> SelectSamplesByTestId(QString test_Id);
	///得到膜条在判断中的位置。
	QSqlQuery SelectLeftRightPosition(QString test_Id, bool *bResult);
    QSqlQuery SelectSamples2(QString strProjectName, QString strTestPaper_ID, bool *bResult);
    QSqlQuery SelectTestPaper(QString strID, bool *bResult);
    QSqlQuery SelectTestPaperItems(QString strTestPaper_ID, bool *bResult);
    QSqlQuery SelectTubes(bool *bResult);
    QSqlQuery SelectTube(QString strID, bool *bResult);
    QSqlQuery SelectTestData(QString testId, bool *bResult);
	QSqlQuery SelectAll_tsystemset(bool *bResult,QString sql);
	QSqlQuery SelectTestDataByTestId(QString testId,bool *bResult);
	QSqlQuery SelectResultInfo(bool *bResult);
	//查询记录
	QSqlQuery SelectRecord(bool *bResult,QString sql);
	///
    QString SelectSaveSetById(bool *bResult, int id);
	void UpdateRecord(bool *bResult, QString sql);
	bool UpdateSampleAnalysisState(
				QString strProjectName,
				QString strSampleID,
				QString strTestPaper_ID,
				QString strAnalysisState,
				QString strTestDateTime);
	bool UpdateTestData(QString testId,QString projectName,double testGrayValue);
	bool InsertTube(
		QString Name,
		QString IsControl,
		QString Inner,
		QString LiquidStartPos,
		QString CupHeight);
	bool UpdateTube(
		QString strTube_ID,
		QString Name,
		QString IsControl,
		QString Inner,
		QString LiquidStartPos,
		QString CupHeight);
        bool DeleteTube(QString strTubeID);
		QString SelectPaperInfo(bool *bResult);
		QString SelectTargetValue(bool *bResult, QString condition);
		QString SelectTargetValueDes(bool *bResult, QString condition);
		QString SelectTargePassword(bool *bResult, QString condition);
		QString SelectIncubationTime(bool *bResult, QString condition, QString condition1);
		void UpdateTargetValue(bool *bResult, QString id, QString value);
		quint64 getMaxId();
		quint64 getMaxSampleNo();
		void deleteRecord(bool *bResult, QString sql);
		void addRecord(bool *bResult, QString sql);
		QString GetTestPaper_sort_max(QString strCompany_ID, QString strTestPaperName, bool *bResult);
		QString GetTestResultByTestId(QString test_id);
		QString SelectTargetValueDesByType(bool *bResult, QString condition, int type);
		QVector<QString> SelectAllCreateDay(bool *bResult);
        QString selectDataBaseVersion(bool *bResult);
        QString  createLISData(const QString &testId, const int companyId,bool removeSpace);
		int getPaperItemCountBySampleId(const int pkid);
        QSqlRecord getSampleByPkid(const int pkid,bool &ret);
        bool updateTestResult(const QVector<QVector<QString>> &testResult);
		QString convetItemCutValue(const int companyId, const QString &itemName, const double &cutValue);
private:
private:
        QVector<int> m_paperIdVect;
		int m_count_i = 0;
};
