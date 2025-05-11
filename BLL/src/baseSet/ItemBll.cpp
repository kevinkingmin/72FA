#include "ItemBll.h"


ItemBll::ItemBll()
{
}

QVector<ItemBll::ptrModel> ItemBll::getAllRows()
{
    return  ItemDao::instance()->getAllRows();
}

QVector<ItemBll::ptrModel> ItemBll::getRowsByPaperId(int paperId)
{
    QVector<ptrModel>outVect;
    auto vect = ItemDao::instance()->getAllRows();
    for(auto it : vect)
    {
        if(it->getTestPaperID()==paperId)
            outVect.push_back(it);
    }
    return outVect;
}

QList<TestResultModel> ItemBll::getItemInfoList(int paper_id)
{
	QList<TestResultModel> item_model_list;
	item_model_list = ItemDao::instance()->getAllRows_list(paper_id);
	//for (auto it : vect)
	//{
	//	//if (it.getTestPaperID == paper_id)
	//	//{
	//	//	ptrModel pm(new ptrModel);
	//	//	item_model_list.push_back(pm);
	//	//}
	//}
	return item_model_list;
}

QVector<ItemBll::ptrModel> ItemBll::Test()
{
	QVector<ptrModel>outVect;
	return outVect;
}
QVector<ItemBll::ptrModel> ItemBll::getRowsByIds(QVector<int> ids)
{
	auto vect = ItemDao::instance()->getAllRows();
	QVector<ptrModel>outVect;
	for (auto it : vect)
	{
		if (ids.contains(it->getID()))
			outVect.push_back(it);
	}
	return outVect;
}

ItemBll::ptrModel ItemBll::getRowById(int id)
{
	if (id <= 0)
		return nullptr;
	auto vect = ItemDao::instance()->getAllRows();
	for (auto it : vect)
	{
		if (it->getID() == id)
			return it;
	}
	return nullptr;
}

bool ItemBll::update(ItemModel &m)
{
    if(m.getID()<=0)
        return false;
    return ItemDao::instance()->update(m);
}
