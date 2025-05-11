#include "ProcessStepDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Model/baseSet/ProcessStepModel.h"
#include "../Include/Model/baseSet/CommonType.h"
#include "../Include/Comm/singleton.h"

ProcessStepDao::ProcessStepDao()
{    
}

ProcessStepDao::~ProcessStepDao()
{
}

ProcessStepDao *ProcessStepDao::instance()
{
    return Singleton<ProcessStepDao>::instance();
}

QVector<ProcessStepDao::ptrModel> ProcessStepDao::getAllRows()
{
    if(_vect.isEmpty())
        getTable();
    return _vect;
}

bool ProcessStepDao::updateActTime(int id, int ms)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;

    QString sqlStr="update tprocess_step set actTime="+QString::number(ms)+" where id="+QString::number(id);
    if(!query.exec(sqlStr))
        return false;

    for(auto &it:_vect)
    {
        if(it->getId()==id)
        {
            it->setActTime(ms);
            break;
        }
    }
    return true;
}

void ProcessStepDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;

    QString sqlStr="SELECT * FROM tprocess_step";
    if(!query.exec(sqlStr))
        return;
    QVector<ptrModel> tempVect;
    _vect.swap(tempVect);
    while (query.next())
    {
        ptrModel pm(new ProcessStepModel);
        pm->setId(query.value("id").toInt());
        pm->setTName(query.value("tName").toString());
        pm->setActTime(query.value("actTime").toInt());
        pm->setTemplateParas(std::move(query.value("templatePara").toString()));
        pm->setRemark(query.value("remark").toString());
        _vect.push_back(pm);
    }
}
