#include "ReagentDao.h"
#include <QVector>
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Model/reagent/ReagentModel.h"
#include "../Include/Comm/singleton.h"
#include "../Include/Utilities/log.h"

ReagentDao::ReagentDao()
{
}

ReagentDao::~ReagentDao()
{
}

ReagentDao *ReagentDao::instance()
{
    return Singleton<ReagentDao>::instance();
}

bool ReagentDao::deleteById(int id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="delete from treagent where ID="+QString::number(id);
    if(!query.exec(sqlStr))
        return false;
    if(_map.keys().contains(id))
        _map.remove(id);
    else
        getTable();
    return true;
}

bool ReagentDao::updateModel(ReagentDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="update treagent set reagentName=:reagentName,TestPaperID=:TestPaperID,"
                   "companyID=:companyID,IsNoDrip=:IsNoDrip,IsSkimp=:IsSkimp,"
                   "IsNeedPrepare=:IsNeedPrepare,PumpNo=:PumpNo"
                   " where ID=:ID";
    query.prepare(sqlStr);
    queryBindValue(query,pm);
    if(!query.exec())
        return false;
    if(_map.keys().contains(pm->getID()))
        _map.insert(pm->getID(),pm);
    else
        getTable();
    return true;
}

bool ReagentDao::insertModel(ReagentDao::ptrModel pm)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="insert into treagent(reagentName,TestPaperID,companyID,IsNoDrip,IsSkimp,IsNeedPrepare,PumpNo)"
                   "values"
                   "(:reagentName,:TestPaperID,:companyID,:IsNoDrip,:IsSkimp,:IsNeedPrepare,:PumpNo)";
    query.prepare(sqlStr);
    queryBindValue(query,pm);
    if(!query.exec())
        return false;
    int id=query.lastInsertId().toInt();
    pm->setID(id);
    if(_map.isEmpty() || id<=0)
        getTable();
    else
        _map.insert(id,pm);
    return true;
}

QVector<ReagentDao::ptrModel> ReagentDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    QVector<ptrModel> outVect;
    auto list = _map.values();
    for(auto it:list)
    {
        auto m=*it;
        ptrModel p(new ReagentModel(std::move(m)));
        outVect.push_back(p);
    }
    return outVect;
}

void ReagentDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT * FROM treagent";
    if(!query.exec(sqlStr))
        return;
    QMap<int,ptrModel>tempMap;
    _map.swap(tempMap);
    int id=0;
    while (query.next())
    {
        ptrModel pm(new ReagentModel);
        id=query.value("ID").toInt();
        pm->setID(id);
		pm->setPaperId(query.value("TestPaperID").toInt());
        pm->setReagentName(query.value("reagentName").toString());
        pm->setCompanyID(query.value("companyID").toInt());
        pm->setIsNoDrip(query.value("IsNoDrip").toInt()==0?false:true);
        pm->setIsSkimp(query.value("IsSkimp").toInt()==0?false:true);
        pm->setIsNeedPrepare(query.value("IsNeedPrepare").toInt()==0?false:true);
        pm->setPumpNo(query.value("PumpNo").toInt());
		float fluid_measure = query.value("fluidMeasure").toFloat();
		float fluid_measure_small = query.value("fluidMeasureSmall").toFloat();
		QString spent_time = query.value("spentTime").toString();
		pm->setFluidMeasure(fluid_measure);
		pm->setFluidMeasureSmall(fluid_measure_small);
		pm->setSpentTime(spent_time);
        _map.insert(id,pm);
    }
}

void ReagentDao::queryBindValue(QSqlQuery &query, ReagentDao::ptrModel pm)
{
    query.bindValue(":ID",pm->getID());
	query.bindValue(":TestPaperID", pm->getPaperId());
    query.bindValue(":reagentName",pm->getReagentName());
    query.bindValue(":companyID",pm->getCompanyID());
    query.bindValue(":IsNoDrip",pm->getIsNoDrip()?1:0);
    query.bindValue(":IsSkimp",pm->getIsSkimp()?1:0);
    query.bindValue(":IsNeedPrepare",pm->getIsNeedPrepare()?1:0);
    query.bindValue(":PumpNo",pm->getPumpNo());
}
