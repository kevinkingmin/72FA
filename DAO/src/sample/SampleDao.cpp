#include "SampleDao.h"
#include "SampleTestDao.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include <QDate>
#include "../Include/Utilities/log.h"
#include "../Include/Comm/singleton.h"
#include "../Include/Model/sample/SampleModel.h"
#include "../Include/Model/sample/SampleTestModel.h"
#include "../Include/BLL/baseSet/ItemBll.h"
#include "../Include/Model/result/TestResultModel.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/DAO/Analysis/AnalysisDao.h"

SampleDao::SampleDao()
    :_testDao(SampleTestDao::instance())
{
    _editStr="update tsample set "
             "paperPos=:paperPos,testId=:testId,sampleNo=:sampleNo,paperId=:paperId,barcode=:barcode,PatientName=:PatientName,SexID=:SexID,Age=:Age,AgeUnitID=:AgeUnitID,birthday=:birthday,bloodType=:bloodType,AnamnesisNO=:AnamnesisNO,wardName=:wardName,BedNo=:BedNo,departmentName=:departmentName,cupType=:cupType,samplePos=:samplePos,diagnosis=:diagnosis,errorFlag=:errorFlag,skipFlag=:skipFlag,stateFlag=:stateFlag,isDelete=:isDelete,testTime=:testTime,testUser=:testUser,intPreField=:intPreField,strPreField=:strPreField,test_batch=:test_batch "
             " where Id=:Id";
    _insertStr="insert into tsample(paperPos,testId,Id,sampleNo,paperId,barcode,PatientName,SexID,Age,AgeUnitID,birthday,bloodType,AnamnesisNO,wardName,BedNo,departmentName,cupType,samplePos,diagnosis,errorFlag,skipFlag,stateFlag,isDelete,testTime,testUser,intPreField,strPreField,test_batch) values(:paperPos,:testId,:Id,:sampleNo,:paperId,:barcode,:PatientName,:SexID,:Age,:AgeUnitID,:birthday,:bloodType,:AnamnesisNO,:wardName,:BedNo,:departmentName,:cupType,:samplePos,:diagnosis,:errorFlag,:skipFlag,:stateFlag,:isDelete,:testTime,:testUser,:intPreField,:strPreField,:test_batch)";
}

SampleDao::~SampleDao()
{
}

/*void SampleDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT * FROM tsample where isDelete=0";
    if(!query.exec(sqlStr))
        return;
    QMap<QString, ptrModel>tempMap;
    _map.swap(tempMap);
    while (query.next())
    {
        ptrModel pm(new SampleModel);
        pm->setId(query.value("Id").toString());
		pm->setTestId(query.value("testId").toString());
        pm->setSampleNo(query.value("sampleNo").toString());
		pm->setPaperId(query.value("paperId").toInt());
        pm->setBarcode(query.value("barcode").toString());
        pm->setPatientName(query.value("PatientName").toString());
        pm->setSexID(query.value("SexID").toInt());
        pm->setAge(query.value("Age").toInt());
        pm->setAgeUnitID(query.value("AgeUnitID").toInt());
        pm->setBirthday(query.value("birthday").toLongLong());
        pm->setBloodType(query.value("bloodType").toString());
        pm->setAnamnesisNO(query.value("AnamnesisNO").toString());
        pm->setWardName(query.value("wardName").toString());
        pm->setBedNo(query.value("BedNo").toString());
        pm->setDepartmentName(query.value("departmentName").toString());
        pm->setCupType(query.value("cupType").toInt());
		//QString paper_pos = query.value("paperPos").toInt();
		//int paper_pos_i = paper_pos.toInt();
  //      pm->setSamplePos(paper_pos);
        pm->setDiagnosis(query.value("diagnosis").toString());
        pm->setErrorFlag(query.value("errorFlag").toString());
        pm->setSkipFlag(query.value("skipFlag").toString());
        pm->setStateFlag(query.value("stateFlag").toInt());
        pm->setIsDelete(query.value("isDelete").toInt()==0?false:true);
        pm->setTestTime(query.value("testTime").toLongLong());
        pm->setTestUser(query.value("testUser").toString());
        pm->setIntPreField(query.value("intPreField").toInt());
        pm->setStrPreField(query.value("strPreField").toString());
        _map.insert(pm->getId(),pm);
    }
}*/

void SampleDao::queryBindValue(QSqlQuery &query, ptrModel pm)
{
    query.bindValue(":Id",pm->getId());
	query.bindValue(":testId", pm->getTestId());
	QString sample_no = pm->getSampleNo();
	query.bindValue(":sampleNo", sample_no);
	int sample_pos = pm->getSamplePos();
    query.bindValue(":samplePos", sample_pos);
	query.bindValue(":paperId", pm->getPaperId());
    query.bindValue(":barcode",pm->getBarcode());
    query.bindValue(":PatientName",pm->getPatientName());
    query.bindValue(":SexID",pm->getSexID());
    query.bindValue(":Age",pm->getAge());
    query.bindValue(":AgeUnitID",pm->getAgeUnitID());
    query.bindValue(":birthday",pm->getBirthday());
    query.bindValue(":bloodType",pm->getBloodType());
    query.bindValue(":AnamnesisNO",pm->getAnamnesisNO());
    query.bindValue(":wardName",pm->getWardName());
    query.bindValue(":BedNo",pm->getBedNo());
    query.bindValue(":departmentName",pm->getDepartmentName());
    query.bindValue(":cupType",pm->getCupType());
	int paper_pos = pm->getPaperPos();
    query.bindValue(":paperPos",paper_pos);
    query.bindValue(":diagnosis",pm->getDiagnosis());    
    query.bindValue(":errorFlag",pm->getErrorFlag());
    query.bindValue(":skipFlag",pm->getSkipFlag());
    query.bindValue(":stateFlag",pm->getStateFlag());
    query.bindValue(":isDelete",pm->getIsDelete()?1:0);
    query.bindValue(":testTime",pm->getTestTime());
    query.bindValue(":testUser",pm->getTestUser());
    query.bindValue(":intPreField", pm->getIntPreField());
    query.bindValue(":strPreField",pm->getStrPreField());
	query.bindValue(":test_batch", pm->getTestBatch());
}

SampleDao *SampleDao::instance()
{
    return Singleton<SampleDao>::instance();
}

bool SampleDao::deleteHardByIds(QVector<QString> ids)
{
    if(ids.isEmpty())
        return true;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    if(!query.exec("BEGIN"))
    {
        return false;
    }
    QString sqlStr="";
    for(auto id:ids)
    {
		sqlStr = QString("delete from tsample where ID=%1").arg(id);// +QString::number(id);
        if(!query.exec(sqlStr))
        {
            query.exec("ROLLBACK");
            return false;
        }
		sqlStr = QString("delete from tsample_test where sampleId=%1").arg(id);//+QString::number(id);
        if(!query.exec(sqlStr))
        {
            query.exec("ROLLBACK");
            return false;
        }
    }

    if(!query.exec("COMMIT"))
    {
        query.exec("ROLLBACK");
        return false;
    }
    return true;
}

bool SampleDao::updateModel(ptrModel pm)
{
    if(pm.isNull())
        return false;
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    query.prepare(_editStr);
    queryBindValue(query,pm);
    if(!query.exec())
        return false;
    return true;
}

bool SampleDao::updateModel(QVector<ptrModel> vect)
{
	QSqlQuery query;
	if (DAO::createQuery(query) < 0)
		return false;
	if (!query.exec("BEGIN"))
	{
		return false;
	}
    query.prepare(_editStr);
    for (auto pm : vect)
	{
        queryBindValue(query, pm);
		if (!query.exec())
		{
			query.exec("ROLLBACK");
			return false;
		}
	}

	if (!query.exec("COMMIT"))
	{
		query.exec("ROLLBACK");
		return false;
	}
    return true;
}


bool SampleDao::insertModel(QVector<std::tuple<ptrModel ,QVector<ptrTest>>>tps)
{
    quint64 id=getMaxId();
	id += 1;
	auto testId = _testDao->getMaxId();

	auto dao1 = AnalysisDao::instance();
	int test_batch_max = dao1->GetTestBacthMax();
	test_batch_max += 1;

    if(id<=0 || testId<=0)
        return false;

    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    if (!query.exec("BEGIN"))
    {
        return false;
    }
	int i = 0;
    for(auto tp:tps)
    {
        auto pSample = std::get<0>(tp);
        auto testVect = std::get<1>(tp);
		//一个样本对应多个膜条的情况
		if (testVect.count() > 1)
		{
			for (auto &it : testVect)
			{
				QString id_1 = "";
				id_1 = QString("%1").arg(id);
				//pSample->setId(id + i);
				pSample->setId(id_1);
				//pSample->setId(id + i);
				int paper_id = 0;
				QString test_id = "";
				int paper_pos = 0;
				int sample_pos = 0;

				paper_id = it->getPaperId();
				test_id = it->getTestId();
				paper_pos = it->getSlotPos();
				sample_pos = it->getSamplePos();//it->getSampleId();

				pSample->setPaperId(paper_id);
				pSample->setTestId(test_id);
				pSample->setPaperPos(paper_pos);
				pSample->setSamplePos(sample_pos);
				pSample->setTestBatch(test_batch_max);

				query.prepare(_insertStr);
				queryBindValue(query, pSample);
				QString createDay = QDate::currentDate().toString("yyyy-MM-dd");
				//在插入前先删除掉原有记录。
				QString sql_delete = QString("delete from tsample where sampleNo='%1' and createDay='%2' and samplePos=%3 and stateFlag=1  and testId is NULL").arg(pSample->getSampleNo()).arg(createDay).arg(sample_pos-1);
				bool bResult;
				auto dao = AnalysisUIDao::instance();
				dao->SelectRecord(&bResult, sql_delete);

				//如果插入失败回滚
				if (!query.exec())
				{
					query.exec("ROLLBACK");
					eLog(query.lastError().text().toStdString());
					return false;
				}
				i++;
				id++;
			}
		}
		else //就是一个样本对应一个膜条的情况
		{
			//pSample->setId(id + i);
			//int paper_id = 0;
			//QString test_id = "";
			QString id_1 = "";
			id_1 = QString("%1").arg(id);
			//pSample->setId(id + i);
			pSample->setId(id_1);
			int paper_id = 0;
			QString test_id = "";
			int paper_pos = 0;
			int sample_pos = 0;
			for (auto &it : testVect)
			{
				//paper_id = it->getPaperId();
				//test_id = it->getTestId();
				paper_id = it->getPaperId();
				test_id = it->getTestId();
				paper_pos = it->getSlotPos();
				sample_pos = it->getSamplePos();//it->getSampleId();
			}
			pSample->setPaperId(paper_id);
			pSample->setTestId(test_id);
			pSample->setPaperPos(paper_pos);
			pSample->setSamplePos(sample_pos);
			//测试中
			pSample->setStateFlag(2);
			pSample->setTestBatch(test_batch_max);
			//pSample->setPaperId(paper_id);
			//pSample->setTestId(test_id);


			QString createDay = QDate::currentDate().toString("yyyy-MM-dd");
			//在插入前先删除掉原有记录。
			QString sql_delete = QString("delete from tsample where sampleNo='%1' and createDay='%2' and samplePos=%3 and stateFlag=1  and testId is NULL").arg(pSample->getSampleNo()).arg(createDay).arg(sample_pos-1);
			bool bResult;
			auto dao = AnalysisUIDao::instance();
			dao->SelectRecord(&bResult, sql_delete);

			query.prepare(_insertStr);
			queryBindValue(query, pSample);
			if (!query.exec())
			{
				query.exec("ROLLBACK");
				eLog(query.lastError().text().toStdString());
				return false;
			}
			i++;
			id++;
		}
    }

    if (!query.exec("COMMIT"))
    {
        query.exec("ROLLBACK");
        return false;
    }
    return true;
}

quint64 SampleDao::getMaxId()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return 0;
    QString seqnoStr="00000";
    //2020090402021300001
    QString dateStr= QDate::currentDate().toString("yyyyMMdd")+"000000"+seqnoStr;
    QString sqlStr="select max(ID) from tsample where ID>"+dateStr;
    if(!query.exec(sqlStr))
        return 0;
    if(!query.next())
    {
        return 0;
    }
    auto  id = query.value(0).toULongLong();
    if(id<=0)
    {
        QString dateStr=QDateTime::currentDateTime().toString("yyyyMMddHHmmss")+seqnoStr;
        return dateStr.toULongLong();
    }
    return id;
}


QList<SampleModel> SampleDao::getSampleList(QString query_condition)
{
	QList<SampleModel> sample_model_list;
	QSqlQuery query;
	if (DAO::createQuery(query) < 0)
		return sample_model_list;
	QString sqlStr = "SELECT * FROM tsample " + query_condition;
	if (!query.exec(sqlStr))
		return sample_model_list;
	while (query.next())
	{
		SampleModel pm;// (new SampleModel);
		pm.setId(query.value("Id").toString());
		pm.setTestId(query.value("testId").toString());
		pm.setSampleNo(query.value("sampleNo").toString());
		pm.setPaperId(query.value("paperId").toInt());
		pm.setBarcode(query.value("barcode").toString());
		pm.setPatientName(query.value("PatientName").toString());
		pm.setSexID(query.value("SexID").toInt());
		pm.setAge(query.value("Age").toInt());
		pm.setAgeUnitID(query.value("AgeUnitID").toInt());
		pm.setBirthday(query.value("birthday").toLongLong());
		pm.setBloodType(query.value("bloodType").toString());
		pm.setAnamnesisNO(query.value("AnamnesisNO").toString());
		pm.setWardName(query.value("wardName").toString());
		pm.setBedNo(query.value("BedNo").toString());
		pm.setDepartmentName(query.value("departmentName").toString());
		pm.setCupType(query.value("cupType").toInt());
		pm.setSamplePos(query.value("samplePos").toInt());
		pm.setDiagnosis(query.value("diagnosis").toString());
		pm.setErrorFlag(query.value("errorFlag").toString());
		pm.setSkipFlag(query.value("skipFlag").toString());
		pm.setStateFlag(query.value("stateFlag").toInt());
		pm.setIsDelete(query.value("isDelete").toInt() == 0 ? false : true);
		pm.setTestTime(query.value("testTime").toLongLong());
		pm.setTestUser(query.value("testUser").toString());
		pm.setIntPreField(query.value("intPreField").toInt());
		pm.setStrPreField(query.value("strPreField").toString());
		sample_model_list.push_back(pm);
	}
	return sample_model_list;
}
