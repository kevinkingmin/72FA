#include "ItemDao.h"
#include <QSqlQuery>
//#include "../Include/Model/"


ItemDao::ItemDao()
    :_map{}
{    
}

void ItemDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT * FROM titem";
    if(!query.exec(sqlStr))
        return;
    QMap<int,ptrModel> tempMap;
    _map.swap(tempMap);
    while (query.next())
    {
        ptrModel pm(new ItemModel);
        pm->setID(query.value("ID").toInt());
        pm->setTestPaperID(query.value("TestPaperID").toInt());
        pm->setItemName(query.value("ItemName").toString());
        pm->setPositionNo(query.value("PositionNo").toInt());
        pm->setIsNull(query.value("IsNull").toInt()==0?false:true);
        _map.insert(pm->getID(),pm);
    }
}

void ItemDao::queryBindValue(QSqlQuery &query, ItemModel &m)
{
    query.bindValue(":ID",m.getID());
    query.bindValue(":TestPaperID",m.getTestPaperID());
    query.bindValue(":ItemName",m.getItemName());
    query.bindValue(":PositionNo",m.getPositionNo());
    query.bindValue(":IsNull",m.getIsNull()?1:0);
}

void ItemDao::equalToPoint(ItemDao::ptrModel pm, ItemModel &m)
{
    pm->setID(m.getID());
    pm->setTestPaperID(m.getTestPaperID());
    pm->setItemName(m.getItemName());
    pm->setPositionNo(m.getPositionNo());
    pm->setIsNull(m.getIsNull());
}

ItemDao::~ItemDao()
{
}

ItemDao *ItemDao::instance()
{
    return Singleton<ItemDao>::instance();
}

QVector<ItemDao::ptrModel> ItemDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    QVector<ptrModel> outVect;
    auto list = _map.values();
    for(auto it:list)
    {
        auto m=*it;
        ptrModel p(new ItemModel(std::move(m)));
        outVect.push_back(p);
    }
	TestResultModel tr;
    return outVect;
}

QList<TestResultModel> ItemDao::getAllRows_list(int paper_id)
{
	QList<TestResultModel> ptr_model_list;
	QSqlQuery query;
	if (DAO::createQuery(query) < 0)
		return ptr_model_list;
	QString sqlStr = "";
	if (paper_id == -1)
	{
		sqlStr = "SELECT * FROM titem";
	}
	else
	{
		sqlStr.sprintf("SELECT * FROM titem where IsNull=0 and TestPaperID=%d", paper_id); // = "SELECT * FROM titem where TestPaperID=" + paper_id;
	}
	if (!query.exec(sqlStr))
		return ptr_model_list;
	while (query.next())
	{
		TestResultModel tr;//= new TestResultModel();
		tr.setID(query.value("ID").toInt());
		tr.setTestPaperID(query.value("TestPaperID").toInt());
		tr.setItemName(query.value("ItemName").toString());
		tr.setPositionNo(query.value("PositionNo").toInt());
		tr.setIsNull(query.value("IsNull").toInt() == 0 ? false : true);
		//_map.insert(pm->getID(), pm);
		ptr_model_list.push_back(tr);
	}
	return ptr_model_list;
}

bool ItemDao::update(ItemModel &m)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return false;
    QString sqlStr="update titem set "
                "TestPaperID=:TestPaperID,itemName=:itemName,PositionNo=:PositionNo,IsNull=:IsNull"
                " where ID=:ID";
    query.prepare(sqlStr);
    queryBindValue(query,m);
    if(!query.exec())
        return false;
    else
    {
        if(_map.keys().contains(m.getID()))
        {
            ptrModel pm(new ItemModel);
            equalToPoint(pm, m);
            _map.insert(m.getID(),pm);
        }
        else
            getTable();
        return true;
    }
}

