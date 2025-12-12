#include "ItemDao.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
ItemDao::ItemDao()
{    
}

ItemDao::~ItemDao()
{
}

ItemDao *ItemDao::instance()
{
    return Singleton<ItemDao>::instance();
}

QVector<ItemModel> ItemDao::selectItems(int paper_id)
{
    QVector<ItemModel> itemVect;
	QSqlQuery query;
    if (DAO::createQuery(query) < 0) return itemVect;
    query.prepare("SELECT * FROM titem where TestPaperID=?");
    query.addBindValue(paper_id);
    if (!query.exec()) return itemVect;
	while (query.next())
	{
        ItemModel tr;
		tr.setID(query.value("ID").toInt());
		tr.setTestPaperID(query.value("TestPaperID").toInt());
        int itemType = query.value("itemType").toInt();
        tr.setItemName(itemType, query.value("itemName").toString());
        tr.setSegmentIndex(query.value("segmentIndex").toInt());
		tr.setPositionNo(query.value("PositionNo").toInt());
        tr.setPosition(query.value("position").toDouble());
        tr.setCurveId(query.value("curveId").toInt());
        tr.setRulesId(query.value("RulesId").toInt());
        tr.setResultOffset(query.value("resultOffset").toDouble());
        tr.setIsNull(query.value("IsNull").toInt() == 1 ? true : false);
        tr.setItemFullName(query.value("itemFullName").toString());
        itemVect.push_back(tr);
	}
    return itemVect;
}
// 更新数据
bool ItemDao::update(ItemModel &m)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;
    query.prepare("update titem set TestPaperID=?,itemName=?,itemType=?,segmentIndex=?,PositionNo=?,curveId=?,RulesId=?,resultOffset=?,position=?,IsNull=?,itemFullName=? where ID=?");
    query.addBindValue(m.getTestPaperID());
    query.addBindValue(m.getItemName());
    query.addBindValue(m.getItemType());
    query.addBindValue(m.getSegmentIndex());
    query.addBindValue(m.getPositionNo());
    query.addBindValue(m.getCurveId());
    query.addBindValue(m.getRulesId());
    query.addBindValue(m.getResultOffset());
    query.addBindValue(m.getPosition());
    query.addBindValue(m.getIsNull()?1:0);
    query.addBindValue(m.getItemFullName());
    query.addBindValue(m.getID());
    if(!query.exec())
    {
        QSqlError err = query.lastError();
        qDebug() << "SQL Insert FAILED!";
        qDebug() << "Error Code:" << err.number();
        qDebug() << "Error Msg:" << err.text();
        qDebug() << "Database Text:" << err.databaseText();
        qDebug() << "Driver Text:" << err.driverText();
        // （Qt 5.13+）可选：查看实际执行的语句（仅占位符，不展开值）
        qDebug() << "Executed Query (with ?):" << query.executedQuery();
        return false;
    }
    return true;
}
// 插入新数据
bool ItemDao::insert(ItemModel &m)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;
    query.prepare("INSERT INTO titem (TestPaperID,itemName,itemType,segmentIndex, PositionNo,curveId,RulesId,resultOffset,position,IsNull,itemFullName) VALUES (?,?,?,?,?,?,?,?,?,?,?)");
    query.addBindValue(m.getTestPaperID());
    query.addBindValue(m.getItemName());
    query.addBindValue(m.getItemType());
    query.addBindValue(m.getSegmentIndex());
    query.addBindValue(m.getPositionNo());
    query.addBindValue(m.getCurveId());
    query.addBindValue(m.getRulesId());
    query.addBindValue(m.getResultOffset());
    query.addBindValue(m.getPosition());
    query.addBindValue(m.getIsNull()?1:0);
    query.addBindValue(m.getItemFullName());
    if(!query.exec())
    {
        QSqlError err = query.lastError();
        qDebug() << "SQL Insert FAILED!";
        qDebug() << "Error Code:" << err.number();
        qDebug() << "Error Msg:" << err.text();
        qDebug() << "Database Text:" << err.databaseText();
        qDebug() << "Driver Text:" << err.driverText();
        // （Qt 5.13+）可选：查看实际执行的语句（仅占位符，不展开值）
        qDebug() << "Executed Query (with ?):" << query.executedQuery();
        return false;
    }
    // 获取刚插入记录的自增主键 ID
    QVariant lastId = query.lastInsertId();
    if (!lastId.isValid()) {
        return false;
    }
    // 将生成的 ID 设置回 model（假设你有 setId 方法）
    m.setID(lastId.toInt());
    return true;
}


bool ItemDao::deleteItems(int paper_id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;
    query.prepare("DELETE FROM titem WHERE TestPaperID = ?;");
    query.addBindValue(paper_id);
    return query.exec();
}

