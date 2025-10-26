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

///取得试剂名称
QString AnalysisUIDao::SelectReagentById(bool *bResult, int id)
{
    QString strValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }
    QString sql = QString("select * from t_testpaper where ID =%1").arg(id);
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strValue = query.value("PaperName").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strValue;
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

QString AnalysisUIDao::SelectControlThreshold(bool *bResult)
{
    QString strControlThreshold;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return "";
    }

    *bResult = query.exec("select * from tsystemset where id = 1 ");
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strControlThreshold = query.value("saveDes").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strControlThreshold;
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
        strTargetValue = query.value("saveDes").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strTargetValue;
}

//
QMap<int, QString> AnalysisUIDao::MGroupIdMap(bool *bResult,int company_id) {
    QMap<int, QString> result_map;
    int map_index = 1;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return result_map;
    }

    QString sql = "";
    sql = QString("SELECT * FROM tprocess_para WHERE companyId=%1 GROUP BY groupId ").arg(company_id);
    *bResult = query.exec(sql);
    if (*bResult == false)
        return result_map;

    while (query.next())
    {
        result_map.insert(map_index,query.value("groupId").toString());
        map_index++;
    }
    return result_map;
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

//按顺序查询出来所有的符号
QMap<int, QString> AnalysisUIDao::SelectAllWord(bool *bResult) {
    QMap<int, QString> _wordMap;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
        return _wordMap;
    QString sqlStr = QString("select * from t_judge_rules");
    if (!query.exec(sqlStr))
        return _wordMap;
    QMap<int, QString> tempVect;
    _wordMap.swap(tempVect);
    int pkid = 0;
    QString paras = "";
    while (query.next())
    {
        pkid = query.value("pkid").toInt();
        paras = query.value("GrayWord").toString();
        _wordMap.insert(pkid, paras);
    }
    return _wordMap;
}

QVector<ProcessParaModel> AnalysisUIDao::MProcessPara(bool *bResult, int company_id) {

    QVector<ProcessParaModel>_vect;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
        return _vect;
    QString sqlStr = QString("SELECT id,companyId,groupId,groupName,groupNameCode,stepName,stepNameCode,actIndex,actId,actName,actNameCode,isPopWindow,popWindowDes,popWindowDesCode,paras FROM tprocess_para where companyId=%1").arg(company_id);
    if (!query.exec(sqlStr))
        return _vect;
    QVector<ProcessParaModel>tempVect;
    _vect.swap(tempVect);
    QString paras = "";
    while (query.next())
    {
        ProcessParaModel pm;//= new ProcessParaModel();
        pm.setId(query.value("id").toInt());
        pm.setCompanyId(query.value("companyId").toInt());
        pm.setGroupId(query.value("groupId").toInt());
        pm.setGroupName(query.value("groupName").toString());
        pm.setGroupNameCode(query.value("groupNameCode").toString());
        pm.setStepName(query.value("stepName").toString());
        pm.setStepNameCode(query.value("stepNameCode").toString());
        pm.setActIndex(query.value("actIndex").toInt());
        pm.setActId(query.value("actId").toInt());
        pm.setActName(query.value("actName").toString());
        pm.setActNameCode(query.value("actNameCode").toString());
        pm.setIsPopWindow(query.value("isPopWindow").toInt() > 0);
        pm.setPopWindowDes(query.value("popWindowDes").toString());
        pm.setPopWindowDesCode(query.value("popWindowDesCode").toString());
        paras = query.value("paras").toString();
        pm.setParas(paras);
        _vect.push_back(pm);
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

QString AnalysisUIDao::createLISData(const QString &testId, const int companyId)
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
    QMap<QString, QVector<JudgeRules>>judgeRulesMap{};
    while (TestDataQuery.next())
    {
        QString id = TestDataQuery.value("sampleNo").toString();
        if (iii_count == 0)
        {
            send_sz += QString("%1"+MSH+" %2 || OUL ^ R22 |  | P | 2.5.1 ||| AL | AL || ASCII |||%3").arg(QChar(0x0B)).arg(id).arg(QChar(0x0D));
            send_sz += QString("PID | %1 |||||| %1 | 0 ||||||||||||||||||||||| %2").arg(id).arg(QChar(0x0D));//"PID | " + List[0].SampleNo + " |||||| " + List[0].SampleNo + " | 0 |||||||||||||||||||||||" + getstringforbyte(0x0D);
            send_sz += QString("OBR | 4 | %1  | 4 | E - LAB ^ ES - 480 | N | %1 | %1  ||||||||| ||||  |||||||||||||||||||||||||||| %2").arg(id).arg(QChar(0x0D));//"OBR | 4 | " + List[0].SampleNo + " | 4 | E - LAB ^ ES - 480 | N | " + List[0].SampleNo + " | " + List[0].SampleNo + " ||||||||| ||||  ||||||||||||||||||||||||||||" + getstringforbyte(0x0D);
        }
		if (paperId != TestDataQuery.value("paperId").toInt())
		{
			paperId = TestDataQuery.value("paperId").toInt();
			judgeRulesMap = getPaperJudgeRules(paperId);
		}
        QString projectName = TestDataQuery.value("projectName").toString();
        QString cutGrayValue = convetItemCutValue(companyId, projectName,TestDataQuery.value("cutGrayValue").toDouble());
        int error_code = TestDataQuery.value("error_code").toInt();
        QString testTime = TestDataQuery.value("testTime").toString();
        QString testResult = TestDataQuery.value("testResult").toString();
        double testGrayValue = TestDataQuery.value("testGrayValue").toDouble();
        send_sz += QString("OBX | |NM|%1||%2|F%3||%4 |%5||| F ||| BetchNo || Admin || HumaBlot 72FA  | %6").arg(testTime).arg(projectName).arg(testResult).arg(testGrayValue).arg(cutGrayValue).arg(QChar(0x0D)); //"OBX | " + "" + "|NM|" + s.TestTime + "||" + s.ProjectName + "|F" + s.TestResult + "||" + s.TestGrayValue + " |||| F ||| 批号 || Admin || HumaBlot 72FA  | " + "" + "" + getstringforbyte(0x0D);
        iii_count++;
    }
    query_sql = QString("update tsample_test set sendLisFlag=3 where Id = '%1' ").arg(testId);
    SelectRecord(&bResult, query_sql);
    if (send_sz.isEmpty() || !bResult)
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

QString AnalysisUIDao::getItemCHName(const QString &itemName, const int paperId)
{
	QSqlQuery query;
	if (DAO::createQuery(query) < 0)
		return "";
	QString sqlStr = QString("select * from titem where TestPaperID=%1 and itemName='%2'").arg(paperId).arg(itemName);
	if (!query.exec(sqlStr))
		return "";
	if (query.next())
	{
		if (query.value("chItemName").isNull())
			return "";
		return query.value("chItemName").toString();
	}
    return "";
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

QMap<QString, QVector<JudgeRules> > AnalysisUIDao::getPaperJudgeRules(const int paperId)
{
    QMap<QString, QVector<JudgeRules>>outMap{};
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
        return outMap;

    auto judgeRulesMap{convertGrayRadio()};
    QString strSql = "SELECT * FROM titem WHERE TestPaperID=" + QString::number(paperId);
    if(!query.exec(strSql))
        return outMap;

    while (query.next())
    {
        int RulesId{ query.value("RulesId").toInt() };
        auto it{ judgeRulesMap.find(RulesId) };
        if (it == judgeRulesMap.end())
            continue;
        outMap.insert(query.value("itemName").toString(), it.value());
    }
    return outMap;
}

QMap<int, QVector<JudgeRules> > AnalysisUIDao::convertGrayRadio()
{
    QMap<int,QVector<JudgeRules>>judgeMap{};
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
        return judgeMap;
    QString strSql("SELECT * FROM t_judge_rules order by RulesId,GrayValue asc;");
    if (!query.exec(strSql))
        return judgeMap;

    while (query.next())
    {
        JudgeRules m;
        m.setpkid(query.value("pkid").toInt());
        auto ruleId{query.value("RulesId").toInt()};
        m.setRulesId(ruleId);
        m.setGrayValue(query.value("GrayValue").toDouble());
        m.setGrayWord(query.value("GrayWord").toString());
        auto it{judgeMap.find(ruleId)};
        if(it!=judgeMap.end())
        {
            it.value().push_back(m);
            continue;
        }
        judgeMap.insert(ruleId,{m});
    }
    QVector<double>targetValues{4.99,10.0,40.0,70.0,100.0};
    for(auto it=judgeMap.begin();it!=judgeMap.end();it++)
    {
        auto &judgeVect{it.value()};
        if(judgeVect.size()!=5)
            continue;
        double preValue{0};
        double preTarget{0};
        int count{judgeVect.count()};
        for(int i=0;i<count;i++)
        {
            auto &m{judgeVect[i]};
            double grayDV{m.getGrayValue()-preValue};
            if (grayDV-0.00000006 <= 0)
            {
                eLog("grayDV is error!");
                continue;
            }
            double targetDV=targetValues[i]-preTarget;
            if (targetDV - 0.00000006 <= 0)
            {
                eLog("targetDV is error!");
                continue;
            }
            double coff{targetDV/grayDV};
            m.setConvertCoff(coff);//即转化系数
            m.setConvertAdd(preTarget);
            if(i<count-1)
            {
                preValue=m.getGrayValue()+0.00001;
                preTarget=targetValues[i]+0.01;
            }
            else
            {
                preValue=m.getGrayValue();
                preTarget=targetValues[i];
            }
        }
    }
    return judgeMap;
}

std::tuple<QString, QString> AnalysisUIDao::getConvertPara(QVector<JudgeRules> &judgeRulesVect, const double &dRatioToCut, const int paperId)
{
    std::sort(judgeRulesVect.begin(),judgeRulesVect.end(),[](JudgeRules &a,JudgeRules &b)
    {
        return b.getGrayValue()>a.getGrayValue();
    });

    int index{-1};
    for(int i=0;i<judgeRulesVect.count();i++)
    {
        auto grayValue{ judgeRulesVect.at(i).getGrayValue() };
        if(grayValue > dRatioToCut)
        {
            index=i;
            break;
        }
    }

    if (index < 0)
        return std::tuple<QString, QString>("", "");
    double preGrayValue(0);
    if (index > 0)
        preGrayValue = judgeRulesVect.at(index-1).getGrayValue()+0.00001;
    auto m(judgeRulesVect.at(index));
    QString strCovertRatioCut = QString::number(dRatioToCut,'f',5);
    if (m_paperIdVect.contains(paperId))
    {
        auto covertRatioCut = (dRatioToCut - preGrayValue) *m.getConvertCoff() + m.getConvertAdd();
        strCovertRatioCut = QString::number(covertRatioCut, 'f', 2);
    }
    //return std::tuple<QString, QString>(strCovertRatioCut, m.getDisplayWord());
    return std::tuple<QString, QString>(strCovertRatioCut, m.getGrayWord());
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


bool AnalysisUIDao::InsertTestPaper(TestPaperModel& paper)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }
    QString strSql;
    strSql =
        "insert into t_testpaper(CompanyID,PaperName,PaperType,TotalNumber,ItemNumber,"
        "PaperLenght,PaperHeight,PaperMmToPixel,IgnoreHeadLenght,TestBlockWidth,"
        "FuncFindDir,FuncPosition,FuncFindWidth,FuncGrayThreshold,IsBlackPointDetect,"
        "BlackPointDetectThreshold,IsCutOff,CutoffGrayThreshold,CutoffValue,PaperShowAngle,"
        "PaperBinarizationThreshold,PaperBackgroundValue,ItemFindWidth,ItemLineWidth,AnalysisPercentOfHeight,"
        "AnalysisPercentOfWidth,PaperColorOnUi,IsPaperHide,ArticleNo,PaperSortIdxOnUi"
        ") values ('";
    strSql += QString::number(paper.getCompanyId())+","+paper.getPaperName()+","+QString::number(paper.getPaperType())
            +","+ QString::number(paper.getTotalNumber())+","+QString::number(paper.getTestItemNumber());
    strSql += ","+QString::number(paper.getPaperLenght(),'f',2)+","+QString::number(paper.getPaperHeight(),'f',2)+","+QString::number(paper.getPaperMmToPixel(),'f',2)
          +","+QString::number(paper.getIgnoreHeadLenght(),'f',2)+","+QString::number(paper.getTestBlockWidth(),'f',2);
    strSql += ","+QString::number(paper.getFuncFindDir())+","+QString::number(paper.getFuncPosition(),'f',2)+ ","+QString::number(paper.getFuncFindWidth(),'f',2)
           +","+QString::number(paper.getFuncGrayThreshold(),'f',2)+","+QString::number(paper.getIsBlackPointDetect()?1:0);
    strSql += ","+QString::number(paper.getBlackPointDetectThreshold(),'f',2)+","+QString::number(paper.getIsCutOff()?1:0)+ ","+QString::number(paper.getCutOffThreshold(),'f',2)
            +","+QString::number(paper.getCutOffValue(),'f',2)+","+QString::number(paper.getPaperShowAngle());
    strSql += "',"+ QString::number(paper.getPaperBinarizationThreshold())+","+QString::number(paper.getPaperBackgroundValue(),'f',2)+","+ QString::number(paper.getItemFindWidth(),'f',2)
            +","+ QString::number(paper.getItemLineWidth(),'f',2)+","+QString::number(paper.getAnalysisPercentOfHeight());
    strSql += ","+QString::number(paper.getAnalysisPercentOfWidth())+","+paper.getPaperColorOnUi()+","+QString::number(paper.isPaperHide()?1:0)
            +","+paper.getArticleNo()+","+QString::number(paper.getPaperSortIdxOnUi());
    strSql += ")";
    bool bResult = query.exec(strSql);
    return bResult;
}


bool AnalysisUIDao::InsertReagent(
    QString strName,
    QString strCompany_ID,
    QString strTestPaper_ID,
    QString strIsNoDrip,
    QString strIsSkimp,
    QString strIsNeedPrepare,
    QString big_wash,
    QString small_wash)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }
    QString strSql;
    strSql =
        "insert into treagent (reagentName,CompanyID,TestPaperID,IsNoDrip,IsSkimp,IsNeedPrepare,fluidMeasureSmall,fluidMeasure) values ('";

    strSql += strName;
    strSql += "',";

    strSql += strCompany_ID;
    strSql += ",";

    strSql += strTestPaper_ID;
    strSql += ",";

    strSql += strIsNoDrip;
    strSql += ",";

    strSql += strIsSkimp;
    strSql += ",";

    strSql += strIsNeedPrepare;
    strSql += ",";

    strSql += small_wash;
    strSql += ",";

    strSql += big_wash;

    strSql += ")";

    bool bResult = query.exec(strSql);
    return bResult;

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

bool AnalysisUIDao::UpdateTestPaper(QString strID, TestPaperModel& paper)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }

    QString strSql;
    strSql = "update t_TestPaper set ";
    strSql+="CompanyID="+QString::number(paper.getCompanyId())+
            ",PaperName="+paper.getPaperName()+
            ",PaperType="+QString::number(paper.getPaperType())+
            ",TotalNumber="+QString::number(paper.getTotalNumber())+
            ",ItemNumber="+QString::number(paper.getTestItemNumber())+
            ",PaperLenght="+QString::number(paper.getPaperLenght(),'f',2)+
            ",PaperHeight="+QString::number(paper.getPaperHeight(),'f',2)+
            ",PaperMmToPixel="+QString::number(paper.getPaperMmToPixel(),'f',2)+
            ",IgnoreHeadLenght="+QString::number(paper.getIgnoreHeadLenght(),'f',2)+
            ",TestBlockWidth="+QString::number(paper.getTestBlockWidth(),'f',2)+
            ",FuncFindDir="+QString::number(paper.getFuncFindDir())+
            ",FuncPosition="+QString::number(paper.getFuncPosition(),'f',2) +
            ",FuncFindWidth="+QString::number(paper.getFuncFindWidth(),'f',2)+
            ",FuncGrayThreshold="+QString::number(paper.getFuncGrayThreshold(),'f',2)+
            ",IsBlackPointDetect="+QString::number(paper.getIsBlackPointDetect()?1:0)+
            ",BlackPointDetectThreshold="+QString::number(paper.getBlackPointDetectThreshold(),'f',2)+
            ",IsCutOff="+QString::number(paper.getIsCutOff()?1:0) +
            ",CutoffGrayThreshold="+QString::number(paper.getCutOffThreshold(),'f',2)+
            ",CutoffValue="+QString::number(paper.getCutOffValue(),'f',2)+
            ",PaperShowAngle="+QString::number(paper.getPaperShowAngle())+
            ",PaperBinarizationThreshold="+QString::number(paper.getPaperBinarizationThreshold())+
            ",PaperBackgroundValue="+QString::number(paper.getPaperBackgroundValue(),'f',2)+
            ",ItemFindWidth="+QString::number(paper.getItemFindWidth(),'f',2)+
            ",ItemLineWidth="+QString::number(paper.getItemLineWidth(),'f',2)+
            ",AnalysisPercentOfHeight="+QString::number(paper.getAnalysisPercentOfHeight())+
            ",AnalysisPercentOfWidth="+QString::number(paper.getAnalysisPercentOfWidth())+
            ",PaperColorOnUi="+paper.getPaperColorOnUi()+
            ",IsPaperHide="+QString::number(paper.isPaperHide()?1:0)+
            ",ArticleNo="+paper.getArticleNo()+
            ",PaperSortIdxOnUi="+QString::number(paper.getPaperSortIdxOnUi());

    strSql += " where ID = ";
    strSql += strID;
    bool bResult = query.exec(strSql);
    return bResult;
}


bool AnalysisUIDao::QueryTestPaper(QString paper_id, TestPaperModel& paper)
{
    bool bResult{false};
    auto TestPaperQuery = SelectTestPaper(paper_id, &bResult);
    if (bResult == false)
    {
        return false;
    }
    if (TestPaperQuery.next())
    {
        paper.setCompanyId(TestPaperQuery.value("CompanyID").toInt());
        paper.setPaperName(TestPaperQuery.value("PaperName").toString());
        paper.setPaperType(TestPaperQuery.value("PaperType").toInt());
        paper.setTotalNumber(TestPaperQuery.value("TotalNumber").toInt());
        paper.setTestItemNumber(TestPaperQuery.value("ItemNumber").toInt());
        paper.setTotalLenght(TestPaperQuery.value("PaperLenght").toDouble());
        paper.setPaperHeight(TestPaperQuery.value("PaperHeight").toDouble());
        paper.setPaperMmToPixel(TestPaperQuery.value("PaperMmToPixel").toDouble());
        paper.setIgnoreHeadLenght(TestPaperQuery.value("IgnoreHeadLenght").toDouble());
        paper.setTestBlockWidth(TestPaperQuery.value("TestBlockWidth").toDouble());
        paper.setFuncFindDir(TestPaperQuery.value("FuncFindDir").toInt());
        paper.setFuncPosition(TestPaperQuery.value("FuncPosition").toDouble());
        paper.setFuncFindWidth(TestPaperQuery.value("FuncFindWidth").toDouble());
        paper.setFuncGrayThreshold(TestPaperQuery.value("FuncGrayThreshold").toDouble());
        paper.setIsBlackPointDetect(TestPaperQuery.value("IsBlackPointDetect").toInt() == 1);
        paper.setBlackPointDetectThreshold(TestPaperQuery.value("BlackPointDetectThreshold").toDouble());
        paper.setIsCutOff(TestPaperQuery.value("IsCutOff").toInt());
        paper.setCutOffPosition(TestPaperQuery.value("CutoffPosition").toDouble());
        paper.setCutOffValue(TestPaperQuery.value("CutoffValue").toDouble());
        paper.setCutOffThreshold(TestPaperQuery.value("CutOffThreshold").toDouble());
        paper.setPaperShowAngle(TestPaperQuery.value("PaperShowAngle").toInt());
        paper.setPaperBinarizationThreshold(TestPaperQuery.value("PaperBinarizationThreshold").toInt());
        paper.setPaperBackgroundValue(TestPaperQuery.value("PaperBackgroundValue").toDouble());
        paper.setItemFindWidth(TestPaperQuery.value("ItemFindWidth").toDouble());
        paper.setItemLineWidth(TestPaperQuery.value("ItemLineWidth").toDouble());
        paper.setAnalysisPercentOfWidth(TestPaperQuery.value("AnalysisPercentOfWidth").toInt());
        paper.setAnalysisPercentOfHeight(TestPaperQuery.value("AnalysisPercentOfHeight").toInt());
        paper.setPaperColorOnUi(TestPaperQuery.value("PaperColorOnUi").toString());
        paper.setPaperHide(TestPaperQuery.value("IsPaperHide").toInt() == 1);
        paper.setArticleNo(TestPaperQuery.value("ArticleNo").toString());
        paper.setPaperSortIdxOnUi(TestPaperQuery.value("PaperSortIdxOnUi").toInt());
    }
    return true;
}

bool AnalysisUIDao::UpdateReagent(
    QString strReagent_ID,
    QString strName,
    QString strCompany_ID,
    QString strTestPaper_ID,
    QString strIsNoDrip,
    QString strIsSkimp,
    QString strIsNeedPrepare,
    QString big_wash,
    QString small_wash)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }

    QString strSql;
    strSql =
        "update treagent set reagentName = '";
    strSql += strName;
    strSql += "',";

    strSql += "CompanyID = ";
    strSql += strCompany_ID;
    strSql += ",";

    strSql += "TestPaperID = ";
    strSql += strTestPaper_ID;
    strSql += ",";

    strSql += "IsNoDrip = ";
    strSql += strIsNoDrip;
    strSql += ",";

    strSql += "IsSkimp = ";
    strSql += strIsSkimp;
    strSql += ",";

    strSql += "IsNeedPrepare = ";
    strSql += strIsNeedPrepare;
    strSql += ",";

    strSql += "fluidMeasure = ";
    strSql += big_wash;
    strSql += ",";

    strSql += "fluidMeasureSmall = ";
    strSql += small_wash;

    strSql += " where ID = ";
    strSql += strReagent_ID;

    QString strSql1_update = "update treagent set ";
    strSql1_update += "fluidMeasure = ";
    strSql1_update += big_wash;
    strSql1_update += ",";
    strSql1_update += "fluidMeasureSmall = ";
    strSql1_update += small_wash;
    strSql1_update += " where TestPaperID =111 and CompanyID = ";
    strSql1_update += strCompany_ID;
    strSql1_update += " and ID = ";
    strSql1_update += strReagent_ID;

    bool bResult = query.exec(strSql);
    bResult = query.exec(strSql1_update);
    return bResult;
}

bool AnalysisUIDao::UpdateReagent1(
    QString strReagent_ID,
    QString strName,
    QString strCompany_ID,
    QString strTestPaper_ID,
    QString strIsNoDrip,
    QString strIsSkimp,
    QString strIsNeedPrepare,
    QString big_wash,
    QString small_wash)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        return false;
    }

    QString strSql;
    strSql =
        "update treagent set reagentName = '";
    strSql += strName;
    strSql += "',";

    strSql += "CompanyID = ";
    strSql += strCompany_ID;
    strSql += ",";

    strSql += "TestPaperID = ";
    strSql += strTestPaper_ID;
    strSql += ",";

    strSql += "IsNoDrip = ";
    strSql += strIsNoDrip;
    strSql += ",";

    strSql += "IsSkimp = ";
    strSql += strIsSkimp;
    strSql += ",";

    strSql += "IsNeedPrepare = ";
    strSql += strIsNeedPrepare;
    strSql += ",";

    strSql += "fluidMeasure = ";
    strSql += big_wash;
    strSql += ",";

    strSql += "fluidMeasureSmall = ";
    strSql += small_wash;

    strSql += " where ID = ";
    strSql += strReagent_ID;

    QString strSql1_update = "update treagent set ";
    strSql1_update += "fluidMeasure = ";
    strSql1_update += big_wash;
    strSql1_update += ",";
    strSql1_update += "fluidMeasureSmall = ";
    strSql1_update += small_wash;
    strSql1_update += " where TestPaperID =111 and CompanyID = ";
    strSql1_update += strCompany_ID;
    strSql1_update += " and ID = ";
    strSql1_update += strReagent_ID;

    bool bResult = query.exec(strSql);
    bResult = query.exec(strSql1_update);
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

// 禁用膜条
bool AnalysisUIDao::DeleteTestPaper(QString strID)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }


    QString strSql;
    strSql ="update t_TestPaper set IsPaperHide=1 where ID = ";
    strSql += strID;

    bool bResult = query.exec(strSql);
    return bResult;

}

// 启用膜条
bool AnalysisUIDao::NoDeleteTestPaper(QString strID)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        return false;
    }

    QString strSql;
    strSql = "update t_TestPaper set IsPaperHide=0 where ID = ";
    strSql += strID;

    bool bResult = query.exec(strSql);
    return bResult;

}

bool AnalysisUIDao::DeleteReagent(QString strID)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }


    QString strSql;
    strSql =
        "delete from treagent where ID = ";
    strSql += strID;

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

bool AnalysisUIDao::DeleteTestPaperItems(QString strTestPaper_ID)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }


    QString strSql;
    strSql =
        "delete from titem where TestPaperID = ";
    strSql += strTestPaper_ID;

    bool bResult = query.exec(strSql);
    return bResult;

}


bool AnalysisUIDao::InsertTestPaperItem(
    int RulesId,
    QString strID,
    QString strIsNull,
    QString strName,
    QString strTestPaper_ID,
    QString position,
    QString strPositionNo)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        return false;
    }

    QString strSql;
    strSql =
        "insert into titem (IsNull,itemName,TestPaperID,RulesId,position,PositionNo) values (";
    strSql += strIsNull;
    strSql += ",'";

    strSql += strName;
    strSql += "',";

    strSql += strTestPaper_ID;
    strSql += ",";

    strSql += QString::number(RulesId);
    strSql += ",";

    strSql += position;
    strSql += ",";

    strSql += strPositionNo;
    strSql += ")";

    bool bResult = query.exec(strSql);
    return bResult;

}
QSqlQuery AnalysisUIDao::SelectRulues(bool *bResult)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from t_judge_rules_name order by pkid";
    *bResult = query.exec(strSql);
    return query;
}


///
///
///试剂名是不是已经存在，存在返回1，不存在返回0;
int AnalysisUIDao::SelectReagentName(QString reagent_name,int add_type, int reagent_id)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
        return 0;
    //QString seqnoStr = "00000";
    //2020090402021300001
    //QString dateStr = QDate::currentDate().toString("yyyyMMdd") + "000000" + seqnoStr;
    QString sqlStr = QString("select reagentName,ID from treagent where reagentName='%1'").arg(reagent_name);
    if (!query.exec(sqlStr))
        return 0;
    if (!query.next())
    {
        return 0;
    }

    auto  name1 = query.value(0).toString();
    auto id = query.value(1).toInt();

    //1为追加，0为修改。
    if (add_type == 1)
    {
        if (name1 == reagent_name && name1 != "")
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (reagent_id == id)
        {
            return 0;
        }
        else
        {
            if (name1 != reagent_name && name1 != "")
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
}

#include <QDebug>
QSqlQuery AnalysisUIDao::SelectReagents(QString strCompany_ID, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from treagent A, t_testpaper B where  (A.TestPaperID = B.ID  and  A.CompanyID in( " + strCompany_ID + ",0))   or  (A.PumpNo in(-1,4,5,6,7,8) and A.CompanyID in(" + strCompany_ID + ",0)) ";
    strSql += "  GROUP BY reagentName ORDER BY  PaperSortIdxOnUi asc ";
    qDebug() << "strSql:"<<strSql;
    *bResult = query.exec(strSql);
    return query;
}

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

QSqlQuery AnalysisUIDao::SelectTestPapers(QString strCompany_ID, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from t_testpaper where CompanyID = ";
    strSql += strCompany_ID;
    strSql += " order by PaperSortIdxOnUi desc";
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
                        QString strSampleID,
                        QString strTestPaper_ID,
                        bool *bResult)
{
    QSqlQuery query;
    query.setForwardOnly(true);
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from tsample_test where  projectName<>'' and Id='"+ testId +"'";
    //strSql = "select * from tsample where ProjectName = '";
    //strSql += strProjectName;
    //strSql += "' and SampleID = ";
    //strSql += strSampleID;
    //strSql += " and TestPaper_ID = ";
    //strSql += strTestPaper_ID;
    int total_number = SelectSampleTestTotalNumber(testId).toInt();
    if (total_number > 0)
    {
        *bResult = query.exec(strSql);
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
    //strSql = "select * from tsample_test where  projectName<>'' and  Id='" + testId + "'";
    strSql = "select DISTINCT A.pkid, A.*, B.left_pix_position, B.right_pix_position, B.top, B.height from tsample_test A, tresult_left_right_pixp B where  A.projectName<>'' and  A.Id = '" + testId + "' and B.test_id = '" + testId + "' and A.projectName = B.projectName";
    //strSql = "select * from tsample where ProjectName = '";
    //strSql += strProjectName;
    //strSql += "' and SampleID = ";
    //strSql += strSampleID;
    //strSql += " and TestPaper_ID = ";
    //strSql += strTestPaper_ID;
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
    QString max_pkid = 0;//; SelectMaxPkid();
    if (project_name == "全部" || project_name == "全部all"|| project_name == "all" || project_name == "全部en" || project_name == "All" || project_name == "All " || project_name == " All ")
    {
        strSql = "select * from tsample A,t_testpaper B where  (A.stateFlag=88 or A.stateFlag=82 or A.stateFlag=81 or A.stateFlag=83 or A.stateFlag=1 or A.stateFlag=2 or A.stateFlag=0)  and A.paperId = B.ID   and A.createDay>='" + start_time + "' and A.createDay<'" + end_time + "'     ";
        max_pkid = SelectMaxPkid(0, start_time, end_time);
    }
    else
    {
        strSql = "select * from tsample A,t_testpaper B where   (A.stateFlag=88 or A.stateFlag=82 or A.stateFlag=81 or A.stateFlag=83 or A.stateFlag=1 or A.stateFlag=2 or A.stateFlag=0)  and A.paperId = B.ID   and B.ID='" + project_name + "'  and A.createDay>='" + start_time + "' and A.createDay<'" + end_time + "'    ";
        int project_name1 = project_name.toInt();
        max_pkid = SelectMaxPkid(project_name1, start_time, end_time);
    }

    int number_i = 0;
    number_i = one_page_number * (page_index-1);
    m_count_i = 0;
    m_count_i = max_pkid.toInt();
    int page_size = 0;
    page_size = m_count_i - number_i;

    if (max_pkid.toInt() <= one_page_number)
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

QString  AnalysisUIDao::SelectSampleTestTotalNumber(QString test_id) {

    QString strTargetValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        return "";
    }

    QString sql = "";
    sql = QString("select count(*) as total_number from tsample_test  where Id='%1'").arg(test_id);
     query.exec(sql);
    if (query.next())
    {
        strTargetValue = query.value("total_number").toString();
    }
    else
    {
        return "";
    }
    return strTargetValue;
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
QString  AnalysisUIDao::SelectMaxPkid(int paper_id, QString start_time, QString end_time)
{
    bool *bResult;
    QString strTargetValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }

    QString sql = "";
    if (paper_id == 0)
    {
        sql = QString("select count(*) AS max_pkid from tsample A,t_testpaper B where  (A.stateFlag=88 or A.stateFlag=81 or A.stateFlag=82 or A.stateFlag=83 or A.stateFlag=1 or A.stateFlag=2 or A.stateFlag=0)  and A.paperId = B.ID   and  createDay>='" + start_time + "' and createDay<'" + end_time + "'  ");
    }
    else
    {
        sql = QString("select count(*)  AS max_pkid from tsample   A,t_testpaper B where (A.stateFlag=88 or A.stateFlag=81 or A.stateFlag=82 or A.stateFlag=83 or A.stateFlag=1 or A.stateFlag=2 or A.stateFlag=0) and  A.paperId = B.ID   and   paperId=%1 and  createDay>='" + start_time + "' and createDay<'" + end_time + "' ").arg(paper_id);
    }

    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strTargetValue = query.value("max_pkid").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }

    return strTargetValue;
}

QString  AnalysisUIDao::SelectMinPkid()
{
    bool *bResult;
    QString strTargetValue;
    QSqlQuery query;
    if (DAO::createQuery(query) < 0)
    {
        *bResult = false;
        return "";
    }

    QString sql = "";
    sql = "select MIN(pkid) AS min_pkid from tsample ";
    *bResult = query.exec(sql);
    if (*bResult == false)
        return "";
    if (query.next())
    {
        strTargetValue = query.value("min_pkid").toString();
    }
    else
    {
        *bResult = false;
        return "";
    }
    return strTargetValue;
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

QSqlQuery AnalysisUIDao::SelectReagent(QString strID, bool *bResult)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return query;
    }
    QString strSql;
    strSql = "select * from treagent where ID = ";
    strSql += strID;
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

QString AnalysisUIDao::GetTestPaper_ID(QString strCompany_ID, QString strTestPaperName, bool *bResult)
{
    QString strID;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
    {
        *bResult = false;
        return "";
    }
    QString strSql = "select ID from t_testpaper where CompanyID = ";
    strSql += strCompany_ID;
    strSql += " and PaperName = '";
    strSql += strTestPaperName;
    strSql += "'";
    *bResult = query.exec(strSql);
    if (*bResult == false)
        return strID;
    if (query.next())
    {
        strID = query.value("ID").toString();
    }
    else
    {
        strID = "";
    }
    return strID;
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

