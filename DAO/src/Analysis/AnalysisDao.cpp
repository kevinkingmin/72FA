#include "AnalysisDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Comm/singleton.h"
#include <QDebug>

AnalysisDao::AnalysisDao()
{
}

AnalysisDao::~AnalysisDao()
{
}

AnalysisDao *AnalysisDao::instance()
{
    return Singleton<AnalysisDao>::instance();
}

QString AnalysisDao::SelectTestPicturesRootPath(bool *bResult)
{
    QString strIPAdress;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult=false;
        return "";
    }

    *bResult = query.exec("select * from tsystemset where id = 3 ");
    if (*bResult == false)
        return "";

    if (query.next())
    {
        strIPAdress = query.value("saveDes").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strIPAdress;
}

QString AnalysisDao::SelectTestReportsRootPath(bool *bResult)
{
    QString strIPAdress;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult=false;
        return "";
    }

    *bResult = query.exec("select * from tsystemset where id = 4 ");
    if (*bResult == false)
        return "";

    if (query.next())
    {
        strIPAdress = query.value("saveDes").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strIPAdress;
}

QString AnalysisDao::SelectSystemMMPixel(bool *bResult)
{
    QString des;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }
    QString sql = "";
    sql.sprintf("select * from tsystemset where id = %d ", 20006);
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        des = query.value("saveDes").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return des;
}
///
QString AnalysisDao::SelectSystemSetDes(bool *bResult, int id)
{
    QString des;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }
    QString sql = "";
    sql.sprintf("select * from tsystemset where id = %d ", id);
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        des = query.value("saveDes").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return des;
}
QString AnalysisDao::SelectControlThreshold(bool *bResult,int paper_id,int company_id)
{
    QString strControlThreshold;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult=false;
        return "";
    }
    QString sql = "";
    sql.sprintf("select * from t_testpaper where id = %d and CompanyID=%d",paper_id,company_id);
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strControlThreshold = query.value("FuncGrayThreshold").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strControlThreshold;
}

QString AnalysisDao::SelectCutOffThreshold(bool *bResult, int paper_id, int company_id)
{
    QString strCutOffThreshold;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult=false;
        return "";
    }
    QString sql = "";
    sql.sprintf("select * from t_testpaper where id = %d and CompanyID=%d", paper_id, company_id);
    *bResult = query.exec(sql);
    if (*bResult == false)
    {
        return "";
    }
    if (query.next())
    {
        strCutOffThreshold = query.value("CutoffGrayThreshold").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strCutOffThreshold;
}

QString AnalysisDao::SelectThresholdValue(bool *bResult, int paper_id, int company_id)
{
    QString backgroundValue;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult=false;
        return "";
    }
    QString sql = "";
    sql.sprintf("select * from t_testpaper where id = %d and CompanyID=%d", paper_id, company_id);
    *bResult = query.exec(sql);
    if (*bResult == false)
    {
        return "";
    }
    if (query.next())
    {
        backgroundValue = query.value("PaperBinarizationThreshold").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return backgroundValue;
}


QSqlQuery AnalysisDao::SelectTestPaper(QString strID, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult=false;
        return query;
    }
    QString strSql;
    strSql = "select * from t_TestPaper where ID = ";
    strSql += strID;
    *bResult = query.exec(strSql);
    return query;
}

QSqlQuery AnalysisDao::SelectTestPaperItems(QString strTestPaper_ID, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult=false;
        return query;
    }
    QString strSql;
    strSql = "select * from titem where TestPaperID = ";
    strSql += strTestPaper_ID;
    strSql += "  order BY PositionNo";
    *bResult = query.exec(strSql);
    return query;
}


QSqlQuery AnalysisDao::SelectSamples(QString sampleId, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult=false;
        return query;
    }
    QString strSql;
    strSql = "select distinct paperId,sampleNo from tsample where sampleNo = '";
    strSql += sampleId;
    strSql += "' order by sampleNo";
    *bResult = query.exec(strSql);
    return query;
}


QString AnalysisDao::SelectCampanyId(bool *bResult)
{
    QString value;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }
    *bResult = query.exec("select * from tsystemset where id = 5 ");
    if (*bResult == false)
        return "";
    if (query.next())
    {
        value = query.value("saveSet").toString();
    }
    else
    {
        *bResult = false;
        return "44444";
    }
    return value;
}

int AnalysisDao::GetTestBacthMax()
{
    bool *bResult;
    int value;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return 1;
    }
    *bResult = query.exec("SELECT MAX(test_batch) as test_batch_max from tsample ");
    if (*bResult == false)
        return 1;
    if (query.next())
    {
        value = query.value("test_batch_max").toInt();
    }
    else
    {
        *bResult = false;
        return 1;
    }
    return value;
}

//查询测试编号
QSqlQuery AnalysisDao::SelectTestIdFromSamples(QString testId, bool *bResult)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from tsample where testId = '";
    strSql += testId;
    strSql += "'";
    *bResult = query.exec(strSql);
    return query;
}

QSqlQuery AnalysisDao::SelectSamples2(QString strProjectName, QString strTestPaper_ID, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult=false;
        return query;
    }
    QString strSql;
    strSql = "select * from wgm_Sample where ProjectName = '";
    strSql += strProjectName;
    strSql += "' and TestPaper_ID = ";
    strSql += strTestPaper_ID;
    strSql += " order by SampleID";
    *bResult = query.exec(strSql);
    return query;
}

bool AnalysisDao::InsertOrUpdate_tresult_left_right_pixp(QString testId, int position_index, int left, int right, QString projectName, int top, int height)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0) {
        qWarning() << "Failed to create query";
        return false;
    }
    // 1. 先查询是否存在
    query.prepare("SELECT pkid FROM tresult_left_right_pixp WHERE test_id = :tid AND projectName = :tName LIMIT 1");
    query.bindValue(":tid", testId);
    query.bindValue(":tName", projectName);
    if(!query.exec()) {
        qWarning() << "Failed to create query1";
        return false;
    }

    if (!query.next()) { // 插入
        QString strSql = "INSERT INTO tresult_left_right_pixp "
                         "(test_id, left_pix_position, right_pix_position, position_index, top, height, projectName) "
                         "VALUES (:testId, :left, :right, :positionIndex, :top, :height, :projectName)";
        query.prepare(strSql);
        query.bindValue(":testId", testId);
        query.bindValue(":left", left);
        query.bindValue(":right", right);
        query.bindValue(":positionIndex", position_index);
        query.bindValue(":top", top);
        query.bindValue(":height", height);
        query.bindValue(":projectName", projectName);
        if(!query.exec()){
            qWarning() << "Failed to create query2";
            return false;
        }
    }else // 更新
    {
        QString strSql = "UPDATE tresult_left_right_pixp SET "
                         "left_pix_position = :left, "
                         "right_pix_position = :right, "
                         "top = :top, "
                         "height = :height, "
                         "position_index = :position_index "
                         "WHERE test_id = :testId AND projectName = :projectName";

        query.prepare(strSql);
        query.bindValue(":left", left);
        query.bindValue(":right", right);
        query.bindValue(":top", top);
        query.bindValue(":height", height);
        query.bindValue(":position_index", position_index);
        query.bindValue(":testId", testId);
        query.bindValue(":projectName", projectName);
        if(!query.exec()){
            qWarning() << "Failed to create query3";
            return false;
        }
    }
    return true;
}

bool AnalysisDao::InsertTestData(
                                 QString strSolutionName,
                                 QString id,
                                 QString paper_id,
                                 QString articleNo,
                                 QString manageName,
                                 QString strSampleID,
                                 QString strItemName,
                                 QString strPosition,
                                 QString strGrayValue,
                                 QString strRatioToCut,
                                 QString strDiagnosis,
                                 QString strTestDateTime, int error_code)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }
    QString strSql;
    strSql =
            "insert into tsample_test (solutionName,Id,sampleId,paperId,projectName,slotPos,testGrayValue,cutGrayValue,testResult,articleNo,manageName,testTime,error_code) values ('";
    strSql += strSolutionName;
    strSql += "','";
    strSql += id;
    strSql += "','";
    strSql += strSampleID;
    strSql += "','";
    strSql += paper_id;
    strSql += "','";
    strSql += strItemName;
    strSql += "',";
    strSql += strPosition;
    strSql += ",";
    strSql += strGrayValue;
    strSql += ",";
    strSql += strRatioToCut;
    strSql += ",'";
    strSql += strDiagnosis;
    strSql += "','";
    strSql += articleNo;
    strSql += "','";
    strSql += manageName;
    strSql += "','";
    strSql += strTestDateTime;
    strSql += "',";
    strSql += QString::number(error_code);
    strSql += ")";
    bool bResult = query.exec(strSql);
    return bResult;
}

bool AnalysisDao::UpdateSampleAnalysisState(QString& testId, QString& strAnalysisState)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }

    QString strSql;
    strSql =
            "update tSample set stateFlag = ";
    strSql += strAnalysisState;
    strSql += "  where testId = '";
    strSql += testId;
    strSql += "' ";
    bool bResult = query.exec(strSql);
    return bResult;
}

QSqlQuery AnalysisDao::SelectStandardCurveParameter(QString curveIdStr, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult=false;
        return query;
    }
    QString strSql;
    strSql = "select * from standard_curve where CurveId = ";
    strSql += curveIdStr;
    *bResult = query.exec(strSql);
    return query;
}
