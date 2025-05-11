#ifndef ITEMBLL_H
#define ITEMBLL_H
#include "../bll.h"
#include <QSharedPointer>
#include <QVector>
#include "../Include/Model/result/TestResultModel.h"
#include "../Include/Model/baseSet/ItemModel.h"
#include "../Include/DAO/baseSet/ItemDao.h"

class ItemModel;

class BLLSHARED_EXPORT ItemBll
{
public:
    ItemBll();
    using ptrModel=QSharedPointer<ItemModel>;
    QVector<ptrModel>getAllRows();
    QVector<ptrModel>getRowsByPaperId(const int paperId);
	QList<TestResultModel>getItemInfoList(int paper_id);
	QVector<ItemBll::ptrModel>Test();
    QVector<ptrModel> getRowsByIds(QVector<int>ids);
    ptrModel getRowById(int id);
    bool update(ItemModel &m);
};

#endif // ITEMBLL_H
