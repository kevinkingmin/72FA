#include "SystemSetDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../../Include/Comm/singleton.h"
#include "../../Include/Model/baseSet/SystemSetModel.h"

SystemSetDao::SystemSetDao()
{
}

SystemSetDao::~SystemSetDao()
{
}

void SystemSetDao::queryBindValue(QSqlQuery &query, SystemSetModel& model)
{
    query.bindValue(":id",model.getId());
    query.bindValue(":saveSet",model.getSaveSet());
    query.bindValue(":saveDes",model.getSaveDes());
}

SystemSetDao *SystemSetDao::instance()
{
    return Singleton<SystemSetDao>::instance();
}

bool SystemSetDao::updateModel(SystemSetModel& model)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    query.prepare("update tsystemset set saveSet=:saveSet,saveDes=:saveDes where id=:id");
    queryBindValue(query, model);
    if(!query.exec()) return false;
    return true;
}

bool SystemSetDao::getModel(int id, SystemSetModel& out)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    query.prepare("Select * from tsystemset where id=? LIMIT 1");
    query.addBindValue(id);
    if(!query.exec()) return false;
    if (query.next())
    {
        out.setId(query.value("id").toString().toUInt());
        out.setSaveDes(query.value("saveDes").toString());
        out.setSaveSet(query.value("saveSet").toInt());
        out.setRemark(query.value("remark").toString());
    }
    return true;
}

bool SystemSetDao::getPicturePathRoot(QString& out)
{
    SystemSetModel systemSetting;
    if(!getModel(3, systemSetting)) return false;
    out = systemSetting.getSaveDes();
    return true;
}

QVector<SystemSetModel> SystemSetDao::getAllRows()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return {};
    query.prepare("SELECT id,saveSet,saveDes,remark FROM tsystemset");
    if(!query.exec()) return{};
    QVector<SystemSetModel> systemSetItemVect;
    uint id=0;
    while (query.next())
    {
        SystemSetModel item;
        id=query.value("id").toUInt();
        item.setId(id);
        item.setSaveSet(query.value("saveSet").toInt());
        item.setSaveDes(query.value("saveDes").toString());
        item.setRemark(query.value("remark").toString());
        systemSetItemVect.push_back(item);
    }
    return systemSetItemVect;
}
