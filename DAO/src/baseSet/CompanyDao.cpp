#include "CompanyDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Model/baseSet/CompanyModel.h"
#include "../Include/Comm/singleton.h"

CompanyDao::CompanyDao()
{    
}

CompanyDao::~CompanyDao()
{
}

CompanyDao *CompanyDao::instance()
{
    return Singleton<CompanyDao>::instance();
}

QVector<CompanyModel> CompanyDao::getAllRows()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return {};

    QString sqlStr="SELECT * FROM t_testpapercompany order by ID";
    if(!query.exec(sqlStr)) return {};
    QVector<CompanyModel> tempVect;
    while (query.next())
    {
        CompanyModel model;
        model.setId(query.value("ID").toInt());
        model.setName(query.value("Name").toString());
        tempVect.push_back(model);
    }
    return tempVect;
}
bool CompanyDao::getModel(const int Id, CompanyModel& out)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr = QString("SELECT * FROM t_testpapercompany WHERE id = %1").arg(Id);
    if(!query.exec(sqlStr)) return false;
    if (query.next())
    {
        out.setId(query.value("ID").toInt());
        out.setName(query.value("Name").toString());
    }
    return true;
}
bool CompanyDao::insertModel(const CompanyModel& model)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;

    QString sqlStr = QString("INSERT INTO t_testpapercompany (ID, Name) VALUES (%1, '%2')").arg(model.getId()).arg(model.getName());
    if(!query.exec(sqlStr)) return false;
    return true;
}
bool CompanyDao::deleteModel(const int id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;

    QString sqlStr = QString("DELETE FROM t_testpapercompany WHERE id = %1").arg(id);
    if(!query.exec(sqlStr)) return false;
    return true;
}


