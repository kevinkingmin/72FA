#pragma once

#include <QObject>
#include <QVector>
#include <QSqlRecord>
#include "../dao.h"
#include "../Include/Model/result/JudgeRules.h"

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

	//using ptrModel = QSharedPointer<ProcessParaModel>;

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
	QString SelectControlThreshold(bool *bResult);
	//周、月维护完成时间
	QString SelectMaintenanceFinishTime(bool *bResult,int id);
	QString SelectCutOffThreshold(bool *bResult);
	bool InsertSystemSet(QString strID,QString strsaveDes);
	bool UpdateSystemSet(QString strID,QString strsaveDes);
	bool UpdateSystemDes(QString strID, QString strsaveDes);
	bool UpdateSystemSetId5(QString strID, QString strsaveDes);
	bool InsertCompany(QString strName);
    QSqlQuery SelectCompanys(bool *bResult);
	QSqlQuery SelectCompanysById(bool *bResult,int id);
	QSqlQuery SelectRulues(bool *bResult);
    QSqlQuery SelectTestPapers(QString strCompany_ID, bool *bResult);
	QString GetTestPaper_ID(QString strCompany_ID, QString strTestPaperName, bool *bResult);
    QSqlQuery SelectTestPaperIDs(QString strProjectName, bool *bResult);
    QSqlQuery SelectSamples(QString strProjectName, bool *bResult);

	//查询sample_test表中数据量
	QString SelectSampleTestTotalNumber(QString test_id);

	QMap<int, QString> SelectAllWord(bool *bResult);

	//结果数据表中总数量
	QString SelectTotalNumber(int paper_id, QString start_time, QString end_time);
	//取得最大,最小pkid号
	QString SelectMaxPkid(int paper_id,QString start_time,QString end_time);

	QString SelectMinPkid();

	//整理pkid
	QSqlQuery ReNewPkid(bool *bResult);

	QSqlQuery SelectSamplesByQuery(QString start_time, QString end_time, QString project_name, QString strProjectName, bool *bResult, int one_page_number, int page_index);


	QVector<QSqlRecord> SelectSamplesByTestId(QString test_Id);
	///得到膜条在判断中的位置。
	QSqlQuery SelectLeftRightPosition(QString test_Id, bool *bResult);
	
    QSqlQuery SelectSamples2(QString strProjectName, QString strTestPaper_ID, bool *bResult);
    QSqlQuery SelectTestPaper(QString strID, bool *bResult);
    QSqlQuery SelectTestPaperItems(QString strTestPaper_ID, bool *bResult);

	///试剂名是不是已经存在，存在返回1，不存在返回0; 
	///add_type = 0 为修改，1为追加。
	int SelectReagentName(QString reagent_name,int add_type ,int reagent_id);
    QSqlQuery SelectReagents(QString strCompany_ID, bool *bResult);
    QSqlQuery SelectReagent(QString strID, bool *bResult);
    QSqlQuery SelectTubes(bool *bResult);
    QSqlQuery SelectTube(QString strID, bool *bResult);
    QSqlQuery SelectTestData(QString testId,QString strSampleID,QString strTestPaper_ID, bool *bResult);
	QSqlQuery SelectAll_tsystemset(bool *bResult,QString sql);
	QSqlQuery SelectTestDataByTestId(QString testId,bool *bResult);
	QSqlQuery SelectResultInfo(bool *bResult);
	//查询记录
	QSqlQuery SelectRecord(bool *bResult,QString sql);
	///
	QString SelectSaveSetById(bool *bResult, int id);
	///最得试剂名称
	QString SelectReagentById(bool *bResult, int id);


	void UpdateRecord(bool *bResult, QString sql);

	bool UpdateSampleAnalysisState(
				QString strProjectName,
				QString strSampleID,
				QString strTestPaper_ID,
				QString strAnalysisState,
				QString strTestDateTime);
	bool InsertTestData(
		QString strProjectName,
		QString strSampleID,
		QString strTestPaper_ID,
		QString strItemName,
		QString strPosition,
		QString strGrayValue,
		QString strRatioToCut,
		QString strTestDateTime);
	bool UpdateTestData(QString testId,QString projectName,double testGrayValue);
	bool InsertReagent(
		QString strName,
		QString strCompany_ID,
		QString strTestPaper_ID,
		QString strIsNoDrip,
		QString strIsSkimp,
		QString strIsNeedPrepare,
		QString strPumpNo,
		QString big_wash,
		QString small_wash);

	bool InsertTube(
		QString Name,
		QString IsControl,
		QString Inner,
		QString LiquidStartPos,
		QString CupHeight);

	bool UpdateReagent(
		QString strReagent_ID,
		QString strName,
		QString strCompany_ID,
		QString strTestPaper_ID,
		QString strIsNoDrip,
		QString strIsSkimp,
		QString strIsNeedPrepare,
		QString strPumpNo,
		QString big_wash,
		QString small_wash);

	bool UpdateReagent1(
		QString strReagent_ID,
		QString strName,
		QString strCompany_ID,
		QString strTestPaper_ID,
		QString strIsNoDrip,
		QString strIsSkimp,
		QString strIsNeedPrepare,
		QString strPumpNo,
		QString big_wash,
		QString small_wash);

	bool UpdateTube(
		QString strTube_ID,
		QString Name,
		QString IsControl,
		QString Inner,
		QString LiquidStartPos,
		QString CupHeight);

	bool InsertTestPaper(
		QString strName,
		QString strCompany_ID,
		QString strTotalNumber,
		QString strItem_Number,
		QString strTestPaparLenght,
		QString strFuncPosition,
		QString strArticleNo,
		QString rect_Analysis_x,
		QString rect_Analysis_y,
		QString rect_Analysis_width,
		QString rect_Analysis_height,
		QString analysis_height_percentage,
		QString head_length,
		int isCutOff,
		QString cutoffPosition,
		QString cutoffValue,
		int left_judge_value,
		int sort_id,
		QString BGRGB,
		int funGrayValue,
		int isFun,
		QString wave_pix_width,
		QString wave_pix_width_max,
		QString wave_pix_width_min,
		QString background_values,
		QString zero_value_coefficient,
		QString bg_difference
		);

	bool UpdateTestPaper(
		QString strID,
		QString strName,
		QString strCompany_ID,
		QString strTotalNumber,
		QString strItem_Number,
		QString strTestPaparLenght,
		QString strFuncPosition,
		QString strArticleNo,
		QString rect_Analysis_x,
		QString rect_Analysis_y,
		QString rect_Analysis_width,
		QString rect_Analysis_height,
		QString analysis_height_percentage,
		QString head_length,
		int isCutOff,
		QString cutoffPosition,
		QString cutoffValue,
		int left_judge_value,
		int sort_id,
		QString BGRGB,
		int funGrayValue,
		int isFun,
		QString wave_pix_width,
		QString wave_pix_width_max,
		QString wave_pix_width_min,
		QString background_values,
		QString zero_value_coefficient,
		QString bg_difference
		);

		bool DeleteTestPaper(QString strID);
		bool NoDeleteTestPaper(QString strID);
		bool DeleteReagent(QString strID);
		bool DeleteTube(QString strTubeID);
		bool DeleteTestPaperItems(QString strTestPaper_ID);

		bool InsertTestPaperItem(
			int RulesId,
			QString strID,
			QString strIsNull,
			QString strName,
			QString strTestPaper_ID,
			QString position,
			QString strPositionNo);
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

		//
		QMap<int, QString> MGroupIdMap(bool *bResult, int company_id);

		QVector<ProcessParaModel> MProcessPara(bool *bResult, int company_id);
		
		QVector<QString> SelectAllCreateDay(bool *bResult);

		QString selectDataBaseVersion(bool *bResult);
		//UpdateTargetValue(bool *bResult, QString id, QString value);
        QString  createLISData(const QString &testId);
		int getPaperItemCountBySampleId(const int pkid);
		QSqlRecord getSampleByPkid(const int pkid,bool &ret);
		QString getItemCHName(const QString &itemName,const int paperId);
private:
        QMap<QString, QVector<JudgeRules>> getPaperJudgeRules(const int paperId);
        QMap<int, QVector<JudgeRules> > convertGrayRadio();
        std::tuple<QString, QString> getConvertPara(QVector<JudgeRules>&judgeRulesVect, const double &dRatioToCut, const int paperId);
private:
        QVector<int> m_paperIdVect;
		int m_count_i = 0;
};
