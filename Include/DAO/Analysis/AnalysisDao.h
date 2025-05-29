#ifndef ANALYSISDAO_H
#define ANALYSISDAO_H
#include "../dao.h"
#include <QVector>
#include <QMap>
#include <QSharedPointer>

template<class T>
class Singleton;
class QSqlQuery;

class DAOSHARED_EXPORT AnalysisDao
{
private:
    AnalysisDao();
    AnalysisDao(AnalysisDao &)=delete;
    AnalysisDao(AnalysisDao &&)=delete;
    AnalysisDao &operator=(const AnalysisDao&)=delete;
    AnalysisDao &operator=(AnalysisDao&&)=delete;
    friend Singleton<AnalysisDao>;

public:
    ~AnalysisDao();
    static AnalysisDao *instance();

    QString SelectTestPicturesRootPath(bool *bResult);
    QString SelectTestReportsRootPath(bool *bResult);

    QString AnalysisDao::SelectSystemMMPixel(bool *bResult);
    QString SelectSystemSetDes(bool *bResult, int id);

    QString SelectThresholdValue(bool *bResult, int paper_id, int company_id);
    QString SelectControlThreshold(bool *bResult,int paper_id,int company_id);
    QString SelectCutOffThreshold(bool *bResult, int paper_id, int company_id);
    QSqlQuery SelectTestPaper(QString strID, bool *bResult);
    QSqlQuery SelectTestPaperItems(QString strTestPaper_ID, bool *bResult);
    QSqlQuery SelectTestPaperIDs(QString sampleNo, bool *bResult);
    QSqlQuery SelectSamples(QString sampleNo, bool *bResult);
    QSqlQuery SelectSamples2(QString sampleNo, QString strTestPaper_ID, bool *bResult);
    QSqlQuery SelectTestData(QString sampleNo,QString strSampleID,QString strTestPaper_ID,bool *bResult);
    QSqlQuery SelectTestIdFromSamples(QString testId, bool *bResult);
    QString SelectCampanyId(bool *bResult);

    bool InsertTestData(
        QString strSolutionName,
        QString id,
        QString paper_id,
        QString articleNo,
        QString manageName,
        QString sampleNo,
        QString strSampleID,
        QString strTestPaper_ID,
        QString strItemName,
        QString strPosition,
        QString strGrayValue,
        QString strRatioToCut,
        QString strDiagnosis,
        QString strTestDateTime, QString solution_name, QString patiant_name,int error_code);

    bool UpdateSampleAnalysisState(
        QString sampleNo,
        QString strSampleID,
        QString strTestPaper_ID,
        QString strAnalysisState,
        QString strTestDateTime);

    //插入左右位置记录表中
    bool Insert_tresult_left_right_pixp(QString testId,int position_index, int left, int right,QString projectName, int top, int height);
    int GetTestBacthMax();
    QSqlQuery SelectStandardCurveParameter(QString curveIdStr, bool *bResult);
};

#endif // ANALYSISDAO_H
