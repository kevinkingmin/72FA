#include "SampleTestDao.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include <QDate>
#include "../Include/Utilities/log.h"
#include "../Include/Comm/singleton.h"
#include"../Include/BLL/baseSet/ItemBll.h"
#include "../Include/Model/sample/SampleTestModel.h"

SampleTestDao::SampleTestDao()
{
    _insertStr="insert into tsample_test"
               "(Id,solutionName,manageName,sampleId,paperId,slotPos,projectName,cutGrayValue,coefficient,testGrayValue,testResult,testTime,runStatus,isDelete,remark,articleNo)"
               "values"
               "(:Id,:solutionName,:manageName,:sampleId,:paperId,:slotPos,:projectName,:cutGrayValue,:coefficient,:testGrayValue,:testResult,:testTime,:runStatus,:isDelete,:remark,:articleNo)";

    _editStr="update tsample_test set "
             "sampleId=:sampleId,paperId=:paperId,slotPos=:slotPos,testResult=:testResult,"
             "cutGrayValue=:cutGrayValue,testTime=:testTime,isDelete=:isDelete,remark=:remark,articleNo=:articleNo"
             " where Id=:Id";
}

SampleTestDao::~SampleTestDao()
{

}

SampleTestDao *SampleTestDao::instance()
{
    return  Singleton<SampleTestDao>::instance();
}

///
void SampleTestDao::queryBindValue(QSqlQuery &query, SampleTestDao::ptrModel pm)
{
	//int paperid = pm->getPaperId();
	//QList<TestResultModel> project_info_list1 = ItemBll().getItemInfoList(paperid);

    query.bindValue(":Id",pm->getId());
	query.bindValue(":solutionName", pm->getSolutionName());
	query.bindValue(":manageName", pm->getManageName());
    query.bindValue(":sampleId",pm->getSampleId());
    query.bindValue(":paperId",pm->getPaperId());
    query.bindValue(":slotPos",pm->getSlotPos());
	query.bindValue(":projectName", pm->getProjectName());
    //QString testResult=SampleTestModel().vectToStr(pm->getResultVect());
	//testResult = "test";
    //query.bindValue(":testResult",pm->());
    query.bindValue(":cutGrayValue",pm->getCutGrayValue());
	query.bindValue(":coefficient", pm->getCoefficient());
	query.bindValue(":testGrayValue", pm->getTestGrayValue());
	query.bindValue(":testResult", pm->getTestResult());
	//query.bindValue(":testGrayValue", pm->get());
    query.bindValue(":testTime",pm->getTestTime());
	query.bindValue(":runStatus", pm->getRunStatus());
    query.bindValue(":isDelete",pm->getIsDelete());
    query.bindValue(":remark",pm->getRemark());
	query.bindValue(":articleNo", pm->getRemark());
}

void SampleTestDao::insertBindValue(QSqlQuery &query, SampleTestDao::ptrModel pm)
{
    //int paperid = pm->getPaperId();
    //QList<TestResultModel> project_info_list1 = ItemBll().getItemInfoList(paperid);

    query.bindValue(":Id",pm->getId());
    query.bindValue(":solutionName", pm->getSolutionName());
    query.bindValue(":manageName", pm->getManageName());
    query.bindValue(":sampleId",pm->getSampleId());
    query.bindValue(":paperId",pm->getPaperId());
    query.bindValue(":slotPos",pm->getSlotPos());
    query.bindValue(":projectName", pm->getProjectName());
    //QString testResult=SampleTestModel().vectToStr(pm->getResultVect());
    //testResult = "test";
    //query.bindValue(":testResult",pm->());
    query.bindValue(":cutGrayValue",pm->getCutGrayValue());
    query.bindValue(":coefficient", pm->getCoefficient());
    query.bindValue(":testGrayValue", pm->getTestGrayValue());
    query.bindValue(":testResult", pm->getTestResult());
    //query.bindValue(":testGrayValue", pm->get());
    query.bindValue(":testTime",pm->getTestTime());
    query.bindValue(":runStatus", pm->getRunStatus());
    query.bindValue(":isDelete",pm->getIsDelete());
    query.bindValue(":remark",pm->getRemark());
    query.bindValue(":articleNo", pm->getRemark());
}

void SampleTestDao::editBindValue(QSqlQuery &query, SampleTestDao::ptrModel pm)
{
    //int paperid = pm->getPaperId();
    //QList<TestResultModel> project_info_list1 = ItemBll().getItemInfoList(paperid);

    query.bindValue(":Id",pm->getId());
    query.bindValue(":solutionName", pm->getSolutionName());
    query.bindValue(":manageName", pm->getManageName());
    query.bindValue(":sampleId",pm->getSampleId());
    query.bindValue(":paperId",pm->getPaperId());
    query.bindValue(":slotPos",pm->getSlotPos());
    query.bindValue(":projectName", pm->getProjectName());
    //QString testResult=SampleTestModel().vectToStr(pm->getResultVect());
    //testResult = "test";
    //query.bindValue(":testResult",pm->());
    query.bindValue(":cutGrayValue",pm->getCutGrayValue());
    query.bindValue(":coefficient", pm->getCoefficient());
    query.bindValue(":testGrayValue", pm->getTestGrayValue());
    query.bindValue(":testResult", pm->getTestResult());
    //query.bindValue(":testGrayValue", pm->get());
    query.bindValue(":testTime",pm->getTestTime());
    query.bindValue(":runStatus", pm->getRunStatus());
    query.bindValue(":isDelete",pm->getIsDelete());
    query.bindValue(":remark",pm->getRemark());
    query.bindValue(":articleNo", pm->getRemark());
}

bool SampleTestDao::updateModel(SampleTestDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    query.prepare(_editStr);
    queryBindValue(query,pm);
    if(!query.exec())
    {
        eLog(query.lastError().text().toStdString());
        return false;
    }
    return true;
}

QString SampleTestDao::getMaxId()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return 0;
    QString seqnoStr="00000";

    QString dateStr= QDate::currentDate().toString("yyyyMMdd")+"000000"+seqnoStr;
    QString sqlStr="select max(ID) from tsample_test where ID>"+dateStr;
    if(!query.exec(sqlStr))
        return 0;
    if(!query.next())
    {
        return 0;
    }

    auto  id = query.value(0).toString();//query.value(0).toULongLong();

    if(id<=0)
    {
        QString dateStr=QDateTime::currentDateTime().toString("yyyyMMddHHmmss")+seqnoStr;
		return dateStr;//.toULongLong();
    }
    return id;
}
