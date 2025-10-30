#include "ItemDao.h"
#include <QSqlQuery>

ItemDao::ItemDao()
{    
}

//void ItemDao::getTable()
//{
//    QSqlQuery query;
//    if(DAO::createQuery(query)<0)
//        return;
//    QString sqlStr="SELECT * FROM titem";
//    if(!query.exec(sqlStr))
//        return;
//    QMap<int,ItemModel> tempMap;
//    _map.swap(tempMap);
//    while (query.next())
//    {
//        ItemModel item;
//        item.setID(query.value("ID").toInt());
//        item.setTestPaperID(query.value("TestPaperID").toInt());
//        item.setItemName(query.value("ItemName").toString());
//        item.setPositionNo(query.value("PositionNo").toInt());
//        item.setIsNull(query.value("IsNull").toInt()==0?false:true);
//        _map.insert(pm->getID(),pm);
//    }
//}


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
	QString sqlStr = "";
	if (paper_id == -1)
	{
		sqlStr = "SELECT * FROM titem";
	}
	else
	{
        sqlStr.sprintf("SELECT * FROM titem where IsNull=0 and TestPaperID=%d", paper_id);
	}
	if (!query.exec(sqlStr))
        return itemVect;
	while (query.next())
	{
        ItemModel tr;
		tr.setID(query.value("ID").toInt());
		tr.setTestPaperID(query.value("TestPaperID").toInt());
        tr.setItemName(query.value("itemName").toString());
		tr.setPositionNo(query.value("PositionNo").toInt());
        tr.setCurveId(query.value("curveId").toInt());
        tr.setRulesId(query.value("RulesId").toInt());
        tr.setResultOffset(query.value("resultOffset").toDouble());
		tr.setIsNull(query.value("IsNull").toInt() == 0 ? false : true);
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
    QString sqlStr=QString("update titem set TestPaperID=%1,itemName='%2',PositionNo=%3,curveId=%4,RulesId=%5,resultOffset=%6,position=%7,IsNull=%8,itemFullName='%9' where ID=%10")
            .arg(m.getTestPaperID())
            .arg(m.getItemName())
            .arg(m.getPositionNo())
            .arg(m.getCurveId())
            .arg(m.getRulesId())
            .arg(m.getResultOffset())
            .arg(m.getPosition())
            .arg(m.getIsNull()?1:0)
            .arg(m.getItemFullName())
            .arg(m.getID());
    return query.exec();
}
// 插入新数据
bool ItemDao::insert(ItemModel &m)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;
    QString sqlStr=QString("INSERT INTO titem (TestPaperID,'itemName',PositionNo,curveId,RulesId,resultOffset,position,IsNull,'itemFullName') VALUES (%1,%2,%3,%4,%5,%6,%7,%8,%9)")
            .arg(m.getTestPaperID())
            .arg(m.getItemName())
            .arg(m.getPositionNo())
            .arg(m.getCurveId())
            .arg(m.getRulesId())
            .arg(m.getResultOffset())
            .arg(m.getPosition())
            .arg(m.getIsNull()?1:0)
            .arg(m.getItemFullName());
    return query.exec();
}

