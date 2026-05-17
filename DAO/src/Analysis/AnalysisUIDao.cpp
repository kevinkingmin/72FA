#include "AnalysisUIDao.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QDate>
#include <QVector>
#include <QMap>
#include "../Include/Comm/singleton.h"
#include <QTextCodec>
#include "../Include/Utilities/log.h"
#include "../Include/Model/baseSet/ProcessParaModel.h"
#include "../Include/DAO/baseSet/JudgeDao.h"

#pragma execution_character_set("utf-8")
AnalysisUIDao::AnalysisUIDao()
{
}

AnalysisUIDao::~AnalysisUIDao()
{
}

AnalysisUIDao *AnalysisUIDao::instance()
{
    return  Singleton<AnalysisUIDao>::instance();
}

bool AnalysisUIDao::UpdateSystemDes(QString strID, QString strsaveDes)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        return false;
    }
    QString strSql;
    strSql = "update tsystemset set saveDes = '";
    strSql += strsaveDes;
    strSql += "' where id = ";
    strSql += strID;
    bool bResult = query.exec(strSql);
    return bResult;
}

bool AnalysisUIDao::UpdateSystemSet(QString strID,QString strsaveDes)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }
    QString strSql;
    if (strID == "4" || strID == "3" || strID == "6" || strID=="20010")
    {
        strSql = "update tsystemset set saveDes = '";
    }
    else
    {
        strSql = "update tsystemset set saveSet = '";
    }
    strSql += strsaveDes;
    strSql += "' where id = ";
    strSql += strID;
    bool bResult = query.exec(strSql);
    return bResult;
}

bool AnalysisUIDao::UpdateSystemSetId5(
    QString strID,
    QString strsaveDes)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        return false;
    }
    QString strSql;
    strSql =
        "update tsystemset set saveDes = '";
    strSql += strsaveDes + "',saveSet=(select ID from t_testpapercompany where Name='"+ strsaveDes +"')";
    strSql += " where id = ";
    strSql += strID;
    bool bResult = query.exec(strSql);
    return bResult;
}

bool AnalysisUIDao::InsertSystemSet(
    QString strID,
    QString strsaveDes)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }
    QString strSql;
    strSql =
        "insert into tsystemset (id,saveDes ) values (";
    strSql += strID;
    strSql += ",'";
    strSql += strsaveDes;
    strSql += "')";
    bool bResult = query.exec(strSql);
    return bResult;
}

int AnalysisUIDao::SelectLisUseOrNot(bool *bResult)
{
    int nLisOpen;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return 0;
    }
    *bResult = query.exec("select * from tsystemset where id = 70 ");
    if (*bResult == false)
        return 0;
    if (query.next())
    {
        nLisOpen = query.value("saveDes").toInt();
    }
    else
    {
        *bResult = false;
        return 0;
    }
    return nLisOpen;
}

int AnalysisUIDao::SelectAstmOrHl7(bool *bResult)
{
    int nAstmOrHl7;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return 0;
    }

    *bResult = query.exec("select * from tsystemset where id = 71 ");
    if (*bResult == false)
        return 0;

    if (query.next())
    {
        nAstmOrHl7 = query.value("saveDes").toInt();
    }
    else
    {
        *bResult = false;
        return 0;
    }


    return nAstmOrHl7;
}



QSqlQuery AnalysisUIDao::SelectLisInfos(bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from tsystemset where id IN (70,71,72,73,74) ";
    *bResult = query.exec(strSql);
    return query;
}



QString AnalysisUIDao::SelectLisIPAdress(bool *bResult)
{
    QString strIPAdress;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return "";
    }

    *bResult = query.exec("select * from tsystemset where id = 72 ");
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

QString AnalysisUIDao::SelectTestReportsRootPath(bool *bResult)
{
    QString strIPAdress;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
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

QString AnalysisUIDao::SelectTestPicturesRootPath(bool *bResult)
{
    QString strIPAdress;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
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

QString AnalysisUIDao::SelectPaperInfo(bool *bResult)
{
    QString value;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }
    *bResult = query.exec("select * from tsystemset where id = 5");
    if (*bResult == false)
        return "";
    if (query.next())
    {
        value = query.value("saveDes").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return value;
}

QString AnalysisUIDao::SelectSaveSetById(bool *bResult, int id)
{
    QString strValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }
    QString sql = QString("select * from tsystemset where id =%1").arg(id);
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strValue = query.value("saveSet").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strValue;

}

QString AnalysisUIDao::SelectMaintenanceFinishTime(bool *bResult, int id)
{
    QString strValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }
    QString sql = QString("select * from tsystemset where id =%1").arg(id);
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strValue = query.value("saveDes").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strValue;
}

QSqlQuery AnalysisUIDao::SelectAll_tsystemset(bool *bResult, QString sql)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    //strSql = "select * from tsystemset where id IN (70,71,72,73,74) ";
    *bResult = query.exec(sql);
    return query;
}


//获取值
QString AnalysisUIDao::SelectTargetValue(bool *bResult, QString condition)
{
    QString strTargetValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }

    QString sql = "";
    sql = QString("select * from tsystemset where id ='%1'").arg(condition);
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strTargetValue = query.value("saveSet").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strTargetValue;
}

//获取密码
QString AnalysisUIDao::SelectTargePassword(bool *bResult, QString condition)
{
    QString strTargetValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }

    QString sql = "";
    sql = QString("select * from tuser where LoginName ='%1' and GroupID=3").arg(condition);
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strTargetValue = query.value("uPassword").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strTargetValue;
}



QString AnalysisUIDao::SelectTargetValueDes(bool *bResult, QString condition)
{
    QString strTargetValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }

    QString sql = "";
    sql = QString("select * from tsystemset where id ='%1'").arg(condition);
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strTargetValue = query.value("saveSet").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strTargetValue;
}

//查出所有测试结果日期
QVector<QString> AnalysisUIDao::SelectAllCreateDay(bool *bResult) {
    QVector<QString>_vect;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
        return _vect;
    QString sqlStr = QString("select createDay from tsample  GROUP BY createDay");
    if (!query.exec(sqlStr))
        return _vect;
    QVector<QString>tempVect;
    _vect.swap(tempVect);
    QString paras = "";
    while (query.next())
    {
        paras = query.value("createDay").toString();
        _vect.push_back(paras);
    }
    return _vect;
}

QString AnalysisUIDao::selectDataBaseVersion(bool *bResult)
{
    QString strTargetValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }

    QString sql = "";
    sql = QString("select * from t_sql_version ");
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strTargetValue = query.value("version_name").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strTargetValue;
}

QString AnalysisUIDao::createLISData(const QString &testId, const int companyId, bool removeSpace)
{
    QString query_sql = QString("SELECT tsample.pkid,tsample.Id,tsample.testId,tsample.sampleNo,"
		                         "tsample.samplePos,tsample.paperId,tsample.paperPos,tsample.barcode,"
		                         "tsample.PatientName,tsample.SexID,tsample.Age,tsample.AgeUnitID,"
		                         "tsample.birthday,tsample.bloodType,tsample.AnamnesisNO,tsample.wardName,"
		                         "tsample.BedNo,tsample.departmentName,tsample.cupType,tsample.diagnosis,"
		                         "tsample.errorFlag,tsample.skipFlag,tsample.stateFlag,tsample.isDelete,"
		                         "tsample.testUser,tsample.intPreField,tsample.strPreField,tsample.articleNo,"
		                         "tsample.createDay,tsample.test_batch,tsample_test.pkid as tpkid,"
		                         "tsample_test.Id as tId,tsample_test.solutionName,tsample_test.manageName,"
		                         "tsample_test.sampleId,tsample_test.paperId,tsample_test.slotPos,"
		                         "tsample_test.projectName,tsample_test.cutGrayValue,tsample_test.coefficient,"
		                         "tsample_test.testGrayValue,tsample_test.testResult,tsample_test.testTime,"
		                         "tsample_test.runStatus,tsample_test.isDelete as tisDelete,tsample_test.remark as tremark,"
		                         "tsample_test.articleNo as tarticleNo,tsample_test.sendLisFlag,tsample_test.error_code "
		                         " FROM tsample ,tsample_test "
		                         "WHERE tsample.testId=tsample_test.Id and tsample_test.Id='%1'").arg(testId);
    bool bResult{ true };
    auto TestDataQuery = SelectRecord(&bResult, query_sql);
    QString send_sz = "";
    int iii_count = 0;
    int paperId(0);
    QString MSH = SelectTargetValueDes(&bResult, "9999");
    MSH=MSH.isEmpty()?"MSH |^ |||||":MSH;
    if(removeSpace)
        MSH.remove(' ');
    while (TestDataQuery.next())
    {
        QString id = TestDataQuery.value("sampleNo").toString();
        QString seqNo = TestDataQuery.value("barcode").toString();
        if (iii_count == 0)
        {
            if(removeSpace)
            {
                send_sz += QString("%1"+MSH+"%2||OUL^R22||P|2.5.1|||AL|AL||ASCII|||%3").arg(QChar(0x0B)).arg(id).arg(QChar(0x0D));
                send_sz += QString("PID|%1|%3|||||%1|0|||||||||||||||||||||||%2").arg(id).arg(QChar(0x0D)).arg(seqNo);//"PID | " + List[0].SampleNo + " |||||| " + List[0].SampleNo + " | 0 |||||||||||||||||||||||" + getstringforbyte(0x0D);
                send_sz += QString("OBR|4|%1|4|E - LAB ^ ES - 480|N|%1|%1|%3|||||||||||||||||||||||||||||||||||||||| %2").arg(id).arg(QChar(0x0D)).arg(testId);//"OBR | 4 | " + List[0].SampleNo + " | 4 | E - LAB ^ ES - 480 | N | " + List[0].SampleNo + " | " + List[0].SampleNo + " ||||||||| ||||  ||||||||||||||||||||||||||||" + getstringforbyte(0x0D);
            }
            else
            {
                send_sz += QString("%1"+MSH+" %2 || OUL ^ R22 |  | P | 2.5.1 ||| AL | AL || ASCII |||%3").arg(QChar(0x0B)).arg(id).arg(QChar(0x0D));
                send_sz += QString("PID | %1 |%3||||| %1 | 0 ||||||||||||||||||||||| %2").arg(id).arg(QChar(0x0D)).arg(seqNo);//"PID | " + List[0].SampleNo + " |||||| " + List[0].SampleNo + " | 0 |||||||||||||||||||||||" + getstringforbyte(0x0D);
                send_sz += QString("OBR | 4 | %1  | 4 | E - LAB ^ ES - 480 | N | %1 | %1  |%3|||||||| ||||  |||||||||||||||||||||||||||| %2").arg(id).arg(QChar(0x0D)).arg(testId);//"OBR | 4 | " + List[0].SampleNo + " | 4 | E - LAB ^ ES - 480 | N | " + List[0].SampleNo + " | " + List[0].SampleNo + " ||||||||| ||||  ||||||||||||||||||||||||||||" + getstringforbyte(0x0D);
            }
        }
		if (paperId != TestDataQuery.value("paperId").toInt())
		{
			paperId = TestDataQuery.value("paperId").toInt();
		}
        QString projectName = TestDataQuery.value("projectName").toString();
        QString cutGrayValue = convetItemCutValue(companyId, projectName,TestDataQuery.value("cutGrayValue").toDouble());
        int error_code = TestDataQuery.value("error_code").toInt();
        QString testTime = TestDataQuery.value("testTime").toString();
        QString testResult = TestDataQuery.value("testResult").toString();
        double testGrayValue = TestDataQuery.value("testGrayValue").toDouble();
        if(removeSpace)
            send_sz += QString("OBX||NM|%1||%2|F%3||%4|%5|||F|||BetchNo||Admin||HumaBlot 72FA|%6").arg(testTime).arg(projectName).arg(testResult).arg(testGrayValue).arg(cutGrayValue).arg(QChar(0x0D)); //"OBX|"+ ""+ "|NM|" + s.TestTime + "||" + s.ProjectName + "|F" + s.TestResult + "||" + s.TestGrayValue + " |||| F ||| 批号 || Admin || HumaBlot 72FA  | " + "" + "" + getstringforbyte(0x0D);
        else
           send_sz += QString("OBX | |NM|%1||%2|F%3||%4 |%5||| F ||| BetchNo || Admin || HumaBlot 72FA  | %6").arg(testTime).arg(projectName).arg(testResult).arg(testGrayValue).arg(cutGrayValue).arg(QChar(0x0D)); //"OBX | " + "" + "|NM|" + s.TestTime + "||" + s.ProjectName + "|F" + s.TestResult + "||" + s.TestGrayValue + " |||| F ||| 批号 || Admin || HumaBlot 72FA  | " + "" + "" + getstringforbyte(0x0D);
        iii_count++;
    }
	if (!send_sz.isEmpty())
	{
		query_sql = QString("update tsample_test set sendLisFlag=3 where Id = '%1' ").arg(testId);
		SelectRecord(&bResult, query_sql);
	}
    if (!bResult)
        return "";
    send_sz += QString("%1%2").arg(QChar(0x1C)).arg(QChar(0x0D));
    return send_sz;
}

int AnalysisUIDao::getPaperItemCountBySampleId(const int pkid)
{
	QSqlQuery query;
	if (DAO::createQuery(query) < 0)
		return 0;
	QString sqlStr("SELECT COUNT(*) FROM titem WHERE TestPaperID=(SELECT paperId FROM tsample WHERE pkid=" + QString::number(pkid) + ")");
	if (!query.exec(sqlStr))
		return 0;
	while (query.next())
		return query.value(0).toInt();
	return 0;
}

QSqlRecord AnalysisUIDao::getSampleByPkid(const int pkid, bool &ret)
{
	QSqlQuery query;
	ret = false;
	if (DAO::createQuery(query) < 0)
		return QSqlRecord();
	QString sqlStr = QString("select * from tsample where pkid=%1").arg(pkid);
	if(!query.exec(sqlStr))
		return QSqlRecord();
	if(!query.next())
		return QSqlRecord();
	ret = true;
	return query.record();
}

bool AnalysisUIDao::updateTestResult(const QVector<QVector<QString> > &testResult)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
        return false;
    QString sqlStr="";
    for(auto result:testResult)
    {
		bool sus = true;
		result.at(1).toDouble(&sus);
		if (!sus)
			continue;
		result.at(3).toDouble(&sus);
		if (!sus)
			continue;
        sqlStr+="UPDATE tsample_test set cutGrayValue="+result.at(1)+",testGrayValue="+result.at(3)+",testResult='"+result.at(2)+"' WHERE pkid="+result.at(0)+";";
    }
    return query.exec(sqlStr);
}

QString AnalysisUIDao::convetItemCutValue(const int companyId, const QString & itemName, const double &cutValue)
{
	QString outValue = QString("%1").arg(cutValue);
	if (companyId == 6 && itemName == "Total IgE")
	{
		if (cutValue >= 100)
			outValue = "≥100";
		else
			outValue = "＜100";
	}
	return outValue;
}

///通过膜条类型来读取耗时时间
QString AnalysisUIDao::SelectTargetValueDesByType(bool *bResult, QString condition,int type)
{
    QString strTargetValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }

    QString sql = "";
    sql = QString("select * from t_step_times where id ='%1' and type=%2").arg(condition).arg(type);
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strTargetValue = query.value("saveDes").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strTargetValue;
}

QString AnalysisUIDao::SelectIncubationTime(bool *bResult, QString condition, QString condition1)
{
    QString strTargetValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }

    QString sql = "";
    sql = QString("select * from tstep_incubation_time where step_name ='%1' and company_id='%2'").arg(condition).arg(condition1);
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strTargetValue = query.value("step_incubation_time").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strTargetValue;
}

//修改值
void AnalysisUIDao::UpdateTargetValue(bool *bResult, QString id, QString value)
{
    QString strTargetValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
    }
    *bResult = query.exec("update tsystemset set saveDes='" + value + "'  where id ='" + id + "'");
}

QString AnalysisUIDao::SelectCutOffThreshold(bool *bResult)
{
    QString strCutOffThreshold;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return "";
    }
    *bResult = query.exec("select * from tsystemset where id = 2 ");
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strCutOffThreshold = query.value("saveDes").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strCutOffThreshold;
}

int AnalysisUIDao::SelectLisPort(bool *bResult)
{
    int nLisPort;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return 0;
    }
    *bResult = query.exec("select * from tsystemset where id = 73 ");
    if (*bResult == false)
        return 0;
    if (query.next())
    {
        nLisPort = query.value("saveDes").toInt();
    }
    else
    {
        *bResult = false;
        return 0;
    }
    return nLisPort;
}

bool AnalysisUIDao::InsertTube(
    QString Name,
    QString IsControl,
    QString Inner,
    QString LiquidStartPos,
    QString CupHeight)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }


    QString strSql;
    strSql =
        "insert into ttube (Name1,IsControl,Inner1,LiquidStartPos,CupHeight) values ('";

    strSql += Name;
    strSql += "',";

    strSql += IsControl;
    strSql += ",";

    strSql += Inner;
    strSql += ",";

    strSql += LiquidStartPos;
    strSql += ",";

    strSql += CupHeight;
    strSql += ")";

    bool bResult = query.exec(strSql);
    return bResult;
}


bool AnalysisUIDao::UpdateSampleAnalysisState(
    QString strProjectName,
    QString strSampleID,
    QString strTestPaper_ID,
    QString strAnalysisState,
    QString strTestDateTime)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }


    QString strSql;
    strSql =
        "update wgm_Sample set AnalysisState = ";
    strSql += strAnalysisState;
    strSql += ",";

    strSql += "TestDateTime = '";
    strSql += strTestDateTime;

    strSql += "' where ProjectName = '";
    strSql += strProjectName;

    strSql += "' and SampleID = ";
    strSql += strSampleID;

    strSql += " and TestPaper_ID = ";
    strSql += strTestPaper_ID;

    bool bResult = query.exec(strSql);
    return bResult;
}

bool AnalysisUIDao::UpdateTube(
    QString strTube_ID,
    QString Name,
    QString IsControl,
    QString Inner,
    QString LiquidStartPos,
    QString CupHeight)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }


    QString strSql;
    strSql =
        "update wgm_Tube set Name = '";
    strSql += Name;
    strSql += "',";

    strSql += "IsControl = ";
    strSql += IsControl;
    strSql += ",";

    strSql += "Inner = ";
    strSql += Inner;
    strSql += ",";


    strSql += "LiquidStartPos = ";
    strSql += LiquidStartPos;
    strSql += ",";

    strSql += "CupHeight = ";
    strSql += CupHeight;

    strSql += " where ID = ";
    strSql += strTube_ID;



    bool bResult = query.exec(strSql);
    return bResult;
}

bool AnalysisUIDao::DeleteTube(QString strTubeID)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }


    QString strSql;
    strSql =
        "delete from wgm_Tube where ID = ";
    strSql += strTubeID;

    bool bResult = query.exec(strSql);
    return bResult;

}

#include <QDebug>

QSqlQuery AnalysisUIDao::SelectTubes(bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from ttube";
    strSql += " order by ID";
    *bResult = query.exec(strSql);
    return query;
}

quint64 AnalysisUIDao::getMaxId()
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
        return 0;
    QString seqnoStr = "00000";
    //2020090402021300001
    QString dateStr = QDate::currentDate().toString("yyyyMMdd") + "000000" + seqnoStr;
    QString sqlStr = "select max(ID) from tsample where ID>" + dateStr;
    if (!query.exec(sqlStr))
        return 0;
    if (!query.next())
    {
        return 0;
    }
    auto  id = query.value(0).toULongLong();
    if (id <= 0)
    {
        QString dateStr = QDateTime::currentDateTime().toString("yyyyMMddHHmmss") + seqnoStr;
        return dateStr.toULongLong();
    }
    return id;
}

//最大样本编号
quint64 AnalysisUIDao::getMaxSampleNo()
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
        return 0;
    QString seqnoStr = "00000";
    //2020090402021300001
    QString dateStr = QDate::currentDate().toString("yyyyMMdd");
    QString dateStr1 = QString("select max(sampleNo) from tsample WHERE createDay > '%1'").arg(QDate::currentDate().toString("yyyy-MM-dd"));//“select max(sampleNo) from tsample WHERE createDay > 2023-02-01”;
    QString sqlStr = dateStr1;//"select max(sampleNo) from tsample where ID>" + dateStr;
    if (!query.exec(sqlStr))
    {
        return dateStr.toULongLong();;
    }
    if (!query.next())
    {
        return dateStr.toULongLong();;
        //return 0;
    }
    auto  id = query.value(0).toULongLong();

    if (id <= 0)
    {
        QString dateStr = QDateTime::currentDateTime().toString("yyyyMMdd") ;
        return dateStr.toULongLong();
    }
    return id;
}


QSqlQuery AnalysisUIDao::SelectRecord(bool *bResult, QString sql)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = sql;//"select * from tsample";
    //strSql += " order by Id";
    *bResult = query.exec(sql);
    return query;
}

void AnalysisUIDao::deleteRecord(bool *bResult, QString sql)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
    }
    QString strSql;
    strSql = sql;//"select * from tsample";
    //strSql += " order by Id";
    *bResult = query.exec(strSql);
}

void AnalysisUIDao::addRecord(bool *bResult, QString sql)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
    }
    QString strSql;
    strSql = sql;//"select * from tsample";
    //strSql += " order by Id";
    *bResult = query.exec(strSql);
}

void AnalysisUIDao::UpdateRecord(bool *bResult, QString sql)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
    }
    QString strSql;
    strSql = sql;//"select * from tsample";
    //strSql += " order by Id";
    *bResult = query.exec(strSql);
}


QSqlQuery AnalysisUIDao::SelectResultInfo(bool *bResult)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from tsample";
    strSql += " order by Id";
    *bResult = query.exec(strSql);
    return query;
}

QSqlQuery AnalysisUIDao::SelectTube(QString strID, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from ttube where ID = ";
    strSql += strID;
    *bResult = query.exec(strSql);
    return query;
}

QSqlQuery AnalysisUIDao::SelectTestData(
                        QString testId,
                        bool *bResult)
{
    QSqlQuery query;
    query.setForwardOnly(true);
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    query.prepare("select * from tsample_test where projectName<>'' and Id=?");
    query.addBindValue(testId);
    int total_number = SelectSampleTestTotalNumber(testId);
    if (total_number > 0)
    {
        *bResult = query.exec();
    }
    else
    {
        *bResult = false;
    }

    return query;
}

QSqlQuery  AnalysisUIDao::ReNewPkid(bool *bResult)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    //strSql = "select * from tsample_test where  projectName<>'' and  Id='" + testId + "'";
    strSql += "SET @auto_id = 0;";
    strSql += "UPDATE tsample SET pkid = (@auto_id := @auto_id + 1);";
    strSql += "ALTER TABLE tsample AUTO_INCREMENT = 1;";
    //strSql = "select * from tsample where ProjectName = '";
    //strSql += strProjectName;
    //strSql += "' and SampleID = ";
    //strSql += strSampleID;
    //strSql += " and TestPaper_ID = ";
    //strSql += strTestPaper_ID;
    *bResult = query.exec(strSql);
    return query;
}

QSqlQuery AnalysisUIDao::SelectTestDataByTestId(QString testId,bool *bResult)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select DISTINCT A.pkid, A.*, B.left_pix_position, B.right_pix_position, B.top, B.height from tsample_test A, tresult_left_right_pixp B where  A.projectName<>'' and  A.Id = '" + testId + "' and B.test_id = '" + testId + "' and A.projectName = B.projectName";
    *bResult = query.exec(strSql);
    return query;
}

bool UpdateTestData(QString testId, QString projectName, double testGrayValue)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        return false;
    }
    QString strSql;
    strSql = "update tsample_test set testGrayValue="
        + QString::number(testGrayValue, 'f', 4)
        + " where testId='" + testId + "' and projectName='" + projectName + "'";
    bool bResult = query.exec(strSql);
    return bResult;
}

QSqlQuery AnalysisUIDao::SelectTestPaper(QString strID, bool *bResult)
{
    QSqlQuery query;

    query.setForwardOnly(true);
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from t_TestPaper where ID = ";
    strSql += strID;
    *bResult = query.exec(strSql);
    return query;
}


QSqlQuery AnalysisUIDao::SelectTestPaperIDs(QString strProjectName, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select distinct paperId,paperName from tsample A,t_testpaper B where A.paperId=B.ID";
    *bResult = query.exec(strSql);
    return query;
}

QSqlQuery AnalysisUIDao::SelectSamples(QString strProjectName, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from tsample A,t_testpaper B where A.paperId = B.ID and testId is not null order by A.pkid desc";
    *bResult = query.exec(strSql);
    return query;
}

QVector<QSqlRecord> AnalysisUIDao::SelectSamplesByTestId(QString test_Id)
{
    QSqlQuery query;
	QVector<QSqlRecord> outVect{};
    if (DAO::createQuery(query) < 0)
    {
		return outVect;
    }
	QString strSql = "select * from tsample_test where Id = " + test_Id + "";
	if (!query.exec(strSql))
		return outVect;
	while (query.next())
	{
		outVect.push_back(query.record());
	}
    return outVect;
}

QSqlQuery AnalysisUIDao::SelectLeftRightPosition(QString test_Id, bool *bResult)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return query;
    }

    QString strSql;
    strSql = "";
    strSql = "select * from tresult_left_right_pixp where test_id = '" + test_Id + "'";
    //strSql = "select * from wgm_Sample where ProjectName = '";
    //strSql += strProjectName;
    //strSql += "' order by SampleID";
    *bResult = query.exec(strSql);
    return query;
}

QSqlQuery AnalysisUIDao::SelectSamplesByQuery(QString start_time, QString end_time, QString project_name, QString strProjectName, bool *bResult,int one_page_number,int page_index)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "";
    query.setForwardOnly(true);
    if (project_name == "全部" || project_name == "全部all"|| project_name == "all" || project_name == "全部en" || project_name == "All" || project_name == "All " || project_name == " All ")
    {
        strSql = "select * from tsample A,t_testpaper B where A.paperId = B.ID   and A.createDay>='" + start_time + "' and A.createDay<'" + end_time + "'     ";
        m_count_i = SelectMaxPkid(0, start_time, end_time);
    }
    else
    {
        strSql = "select * from tsample A,t_testpaper B where A.paperId = B.ID   and B.ID='" + project_name + "'  and A.createDay>='" + start_time + "' and A.createDay<'" + end_time + "'    ";
        int project_name1 = project_name.toInt();
        m_count_i = SelectMaxPkid(project_name1, start_time, end_time);
    }

    int number_i = 0;
    number_i = one_page_number * (page_index-1);
    int page_size = 0;
    page_size = m_count_i - number_i;

    if (m_count_i <= one_page_number)
    {
        strSql = QString("%1    %3  LIMIT  %2 ,%4").arg(strSql).arg(0).arg("   ORDER BY createDay DESC , paperPos ASC   ").arg(one_page_number);
    }
    else
    {
        if (page_size <= 0)
        {
            if ((page_size)< one_page_number && page_size>0)
            {
                strSql = QString("%1    %3  LIMIT  %2 ,%4").arg(strSql).arg(one_page_number).arg("   ORDER BY createDay DESC , paperPos ASC   ").arg(page_size + one_page_number);
            }
            else if(page_size==0)
            {
                strSql = QString("%1    %3  LIMIT  %2 ,%4").arg(strSql).arg(0).arg("  ORDER BY createDay DESC , paperPos ASC    ").arg(one_page_number);
            }
            else
            {
                strSql = QString("%1    %3  LIMIT  %2 ,%4").arg(strSql).arg(one_page_number).arg("   ORDER BY createDay DESC , paperPos ASC   ").arg(page_size + one_page_number);
            }
        }
        else
        {
            if (page_size < one_page_number)
            {
                strSql = QString("%1    %3  LIMIT  %2 ,%4").arg(strSql).arg(one_page_number*(page_index - 1)).arg("  ORDER BY createDay DESC , paperPos ASC  ").arg(one_page_number);
            }
            else
            {
                if (page_index == 1)
                {
                    strSql = QString("%1    %3  LIMIT  %2 ,%4").arg(strSql).arg(0).arg("   ORDER BY createDay DESC , paperPos ASC  ").arg(one_page_number);
                }
                else
                {
                    strSql = QString("%1    %3  LIMIT  %2 ,%4").arg(strSql).arg(one_page_number*(page_index - 1)).arg(" ORDER BY createDay DESC , paperPos ASC ").arg(one_page_number);
                }
            }
        }
    }
    *bResult = query.exec(strSql);
    return query;
}

int AnalysisUIDao::SelectSampleTestTotalNumber(QString test_id) {

    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        return 0;
    }
    query.prepare("select count(*) as total_number from tsample_test  where Id=?");
    query.addBindValue(test_id);
    if(!query.exec()) return 0;
    return query.next()?query.value("total_number").toInt():0;
}


QString  AnalysisUIDao::SelectTotalNumber(int paper_id, QString start_time, QString end_time) {

    //bool *bResult;
    //*bResult = false;
    QString strTargetValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        //*bResult = false;
        return "";
    }


    QString sql = "";
    if (paper_id == 0)
    {
        sql = QString("select count(*) as total_number from tsample where  createDay>='" + start_time + "' and createDay<'" + end_time + "'  and  (stateFlag=88 or stateFlag=81 or stateFlag=82 or stateFlag=83  or stateFlag=1  or stateFlag=2 or stateFlag=0)  ");
    }
    else
    {
        sql = QString("select count(*) as total_number from tsample  where  paperId=%1 and (stateFlag=88 or stateFlag=81 or stateFlag=82 or stateFlag=83 or stateFlag=1  or stateFlag=2 or stateFlag=0)  and  createDay>='" + start_time + "' and createDay<'" + end_time + "' ").arg(paper_id);
    }
    //sql = "select count(*) as total_number from tsample ";
    query.exec(sql);
    //if (*bResult == false)
    //	return "";
    if (query.next())
    {
        strTargetValue = query.value("total_number").toString();
    }
    else
    {
        //*bResult = false;
        return "";
    }
    return strTargetValue;
}

//取得最大,最小pkid号
int AnalysisUIDao::SelectMaxPkid(int paper_id, QString start_time, QString end_time)
{
    QString strTargetValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        return 0;
    }
    if (paper_id == 0)
    {
        query.prepare("select count(*) AS total_count from tsample where createDay>=? and createDay<?");
        query.addBindValue(start_time);
        query.addBindValue(end_time);
    }
    else
    {
        query.prepare("select count(*) AS total_count from tsample where paperId=? and  createDay>=? and createDay<?");
        query.addBindValue(paper_id);
        query.addBindValue(start_time);
        query.addBindValue(end_time);
    }

    if(!query.exec()) return 0;
    return query.next()?query.value("total_count").toInt():0;
}

QSqlQuery AnalysisUIDao::SelectSamples2(QString strProjectName, QString strTestPaper_ID, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from tsample A, t_testpaper B where A.paperId = B.ID and A.paperId = '"+ strTestPaper_ID +"' and A.testId is not null order by A.pkid desc";
    *bResult = query.exec(strSql);
    return query;
}

QSqlQuery AnalysisUIDao::SelectTestPaperItems(QString strTestPaper_ID, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from titem where TestPaperID = ";
    strSql += strTestPaper_ID;
    strSql += " order by ID";
    *bResult = query.exec(strSql);
    return query;
}

QString AnalysisUIDao::GetTestPaper_sort_max(QString strCompany_ID, QString strTestPaperName, bool *bResult)
{
    QString strID;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }
    QString strSql = "select MAX(PaperSortIdxOnUi)  as max_value from t_testpaper where CompanyID = ";
    strSql += strCompany_ID;
    *bResult = query.exec(strSql);
    if (*bResult == false)
    {
        return "";
    }
    if (query.next())
    {
        strID = query.value("max_value").toString();
    }
    else
    {
        strID = "";
    }
    return strID;
}


QString AnalysisUIDao::GetTestResultByTestId(QString test_id)
{

    QString result_sz;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        return "";
    }
    QString strSql = "SELECT * from tsample_test where Id='"+test_id+"'";
    //strSql += " and PaperName = '";
    //strSql += strTestPaperName;
    //strSql += "'";
    query.exec(strSql);
    QString projectName;
    QString testResult;
    QString sz;
    //U1-snRNP(+++)  SSA/Ro 60 kD(+++)  SSA/Ro 52 kD(+++)
    while (query.next())
    {
        projectName = query.value("projectName").toString();
        testResult = query.value("testResult").toString();
        sz = projectName + "(" + testResult + ")  ";
        result_sz += sz;
    }
    return result_sz;
}

