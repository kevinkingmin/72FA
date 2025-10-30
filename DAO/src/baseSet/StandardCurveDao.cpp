#include "StandardCurveDao.h"
#include <QSqlQuery>
#include <QVariant>
#include <QMap>
#include <QDebug>
#include "../Include/Model/baseSet/StandaryCurveModel.h"
#include "../Include/Comm/singleton.h"

StandardCurveDao::StandardCurveDao()
{    
}

StandardCurveDao::~StandardCurveDao()
{
}

StandardCurveDao *StandardCurveDao::instance()
{
    return Singleton<StandardCurveDao>::instance();
}

// 获取所有行
QVector<StandaryCurveModel> StandardCurveDao::getAllRows()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return {};

    QString sqlStr="SELECT * FROM standard_curve";
    if(!query.exec(sqlStr)) return {};
    QVector<StandaryCurveModel> tempVect;
    while (query.next())
    {
        StandaryCurveModel model;
        model.setCurveId(query.value("CurveId").toInt());
        model.setCurveName(query.value("curveName").toString());
        model.setCurveType(query.value("CurveType").toInt());
        model.setRemark(query.value("Remark").toString());
        QString parameterStr = query.value("DataGroup1").toString();
        model.setDataGroupStr(model.getCurveId(), parameterStr);
        tempVect.push_back(model);
    }
    return tempVect;
}


// 获取名称
QVector<QString> StandardCurveDao::getAllNames()
{
    QVector<StandaryCurveModel> curves = getAllRows();
    QVector<QString> names;
    for(StandaryCurveModel& curve : curves)
    {
        names.push_back(curve.getCurveName());
    }
    return names;
}

// 根据id获取对象
bool StandardCurveDao::getModel(const int curveId, StandaryCurveModel& out)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr = QString("SELECT * FROM standard_curve WHERE CurveId = %1 LIMIT 1").arg(curveId);
    if(!query.exec(sqlStr)) return false;
    if (query.next())
    {
        out.setCurveId(query.value("CurveId").toInt());
        out.setCurveName(query.value("curveName").toString());
        out.setCurveType(query.value("CurveType").toInt());
        out.setRemark(query.value("Remark").toString());
        QString parameterStr = query.value("DataGroup1").toString();
        out.setDataGroupStr(out.getCurveType(), parameterStr);
    }
    return true;
}

// 插入新数据
bool StandardCurveDao::insert(StandaryCurveModel& model)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;

    query.prepare("INSERT INTO standard_curve (curveName, CurveType, Remark, DataGroup1) VALUES (?, ?, ?, ?)");
    query.addBindValue(model.getCurveName());
    query.addBindValue(model.getCurveType());
    query.addBindValue(model.getRemark());
    query.addBindValue(model.getDataGroupStr());
    if(!query.exec()) return false;
    // 获取刚插入记录的自增主键 ID
    QVariant lastId = query.lastInsertId();
    if (!lastId.isValid()) {
        return false;
    }
    model.setCurveId(lastId.toInt());
    return true;
}

// 更新数据
bool StandardCurveDao::update(StandaryCurveModel &m)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;
    query.prepare("UPDATE standard_curve SET curveName = ?, CurveType = ?, Remark = ?, DataGroup1 = ? WHERE CurveId = ?");
    query.addBindValue(m.getCurveName());
    query.addBindValue(m.getCurveType());
    query.addBindValue(m.getRemark());
    query.addBindValue(m.getDataGroupStr());
    query.addBindValue(m.getCurveId());

    if (!query.exec())
    {
        qDebug() << "SQL Query:" << query.executedQuery();
        return false;
    }

    return true;
}

// 删除数据
bool StandardCurveDao::deleteModel(int id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;
    query.prepare("DELETE FROM standard_curve WHERE CurveId = ?");
    query.addBindValue(id);

    if (!query.exec())
    {
        qDebug() << "SQL Query:" << query.executedQuery();
        return false;
    }

    return true;
}
