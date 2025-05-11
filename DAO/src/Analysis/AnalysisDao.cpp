#include "AnalysisDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Comm/singleton.h"

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
	sql.sprintf("select * from t_testpaper where id = %d and Company_ID=%d",paper_id,company_id);
	*bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strControlThreshold = query.value("funGrayValue").toString();
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
	sql.sprintf("select * from t_testpaper where id = %d and Company_ID=%d", paper_id, company_id);
	*bResult = query.exec(sql);
    //*bResult = query.exec("select * from tsystemset where id = 2 ");
    if (*bResult == false)
    {
        return "";
    }
    if (query.next())
    {
        strCutOffThreshold = query.value("cutoffValue").toString();
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
    sql.sprintf("select * from t_testpaper where id = %d and Company_ID=%d", paper_id, company_id);
    *bResult = query.exec(sql);
    if (*bResult == false)
    {
        return "";
    }
    if (query.next())
    {
        backgroundValue = query.value("threshold_value").toString();
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

	
    //strSql += "  order by ID";
    strSql += "  order BY PositionNo";

    *bResult = query.exec(strSql);
    return query;
}

QSqlQuery AnalysisDao::SelectTestPaperIDs(QString strProjectName, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult=false;
        return query;
    }

    QString strSql;
    strSql = "select distinct(TestPaper_ID) as TestPaper_ID from wgm_Sample where ProjectName = '";
    strSql += strProjectName;
    strSql += "' order by TestPaper_ID";

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
    //strSql = "select * from wgm_Sample where ProjectName = '";
	strSql = "select distinct paperId,sampleNo from tsample where sampleNo = '";
	//select distinct paperId from tsample_test where sampleId = 1
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
	//strSql = "select * from wgm_Sample where ProjectName = '";
	strSql = "select * from tsample where testId = '";
	//select distinct paperId from tsample_test where sampleId = 1
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

bool AnalysisDao::Insert_tresult_left_right_pixp(QString testId, int position_index, int left, int right,QString projectName,int top, int height)
{
	QSqlQuery query;
	if (DAO::createQuery(query) < 0)
	{
		return false;
	}
	QString strSql;
	strSql =
		"insert into tresult_left_right_pixp (test_id,left_pix_position,right_pix_position,position_index,top,height,projectName) values ('";
	strSql += testId;
	strSql += "',";
	strSql += QString::number(left);
	strSql += ",";
	strSql += QString::number(right);
	strSql += ",";
	strSql += QString::number(position_index);
	strSql += ",";
	strSql += QString::number(top);
	strSql += ",";
	strSql += QString::number(height);
	strSql += ",'";
	strSql += projectName;
	strSql += "')";
	bool bResult = query.exec(strSql);
	return bResult;
}

QSqlQuery AnalysisDao::SelectTestData(QString strProjectName, QString strSampleID, QString strTestPaper_ID, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult=false;
        return query;
    }
    QString strSql;
    strSql = "select * from wgm_TestData where ProjectName = '";
    strSql += strProjectName;
    strSql += "' and SampleID = ";
    strSql += strSampleID;
    strSql += " and TestPaper_ID = ";
    strSql += strTestPaper_ID;
    *bResult = query.exec(strSql);
    return query;
}

bool AnalysisDao::InsertTestData(
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
                                 QString strTestDateTime, QString solution_name, QString patiant_name,int error_code)
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

bool AnalysisDao::UpdateSampleAnalysisState(QString sampleNo, QString testId, QString strTestPaper_ID, QString strAnalysisState, QString strTestDateTime)
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
    //strSql += ",";
    //strSql += "test_batch = ";
    //strSql += QString::number(test_batch_value);
    strSql += "  where testId = '";
    strSql += testId;
	strSql += "' ";// and SampleID = ";
    //strSql += strSampleID;
    //strSql += " and TestPaper_ID = ";+		strSql	update tSample set stateFlag = 81, where testId = '202206081117520' 	QString
    //strSql += strTestPaper_ID;
    bool bResult = query.exec(strSql);
    return bResult;
}
