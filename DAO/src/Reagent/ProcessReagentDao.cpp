#include "ProcessReagentDao.h"
#include <QVector>
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Model/reagent/ProcessReagentModel.h"
#include "../Include/Comm/singleton.h"
#include "../Include/Utilities/log.h"

ProcessReagentDao::ProcessReagentDao()
{

}

ProcessReagentDao::~ProcessReagentDao()
{

}

ProcessReagentDao *ProcessReagentDao::instance()
{
    return Singleton<ProcessReagentDao>::instance();
}

QVector<ProcessReagentDao::ptrModel> ProcessReagentDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    QVector<ptrModel> outVect;
    auto list = _map.values();
    for(auto it:list)
    {
        auto m=*it;
        ptrModel p(new ProcessReagentModel(std::move(m)));
        outVect.push_back(p);
    }
    return outVect;
}

void ProcessReagentDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT * FROM tprocess_reagent";
    if(!query.exec(sqlStr))
        return;
    QMap<int,ptrModel>tempMap;
    _map.swap(tempMap);
    int id=0;
    while (query.next())
    {
        ptrModel pm(new ProcessReagentModel);
        id=query.value("id").toInt();
        pm->setId(id);
        pm->setProcessParaId(query.value("processParaId").toInt());
        pm->setPaperId(query.value("paperId").toInt());
        pm->setReagentId(query.value("reagentId").toInt());
        _map.insert(id,pm);
    }
}
