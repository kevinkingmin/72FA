#ifndef ITEMBLL_H
#define ITEMBLL_H
#include "../bll.h"
#include <QSharedPointer>
#include <QVector>
#include "../Include/Model/baseSet/ItemModel.h"
#include "../Include/DAO/baseSet/ItemDao.h"

class ItemModel;

class BLLSHARED_EXPORT ItemBll
{
public:
    ItemBll();
    QVector<ItemModel>getRowsByPaperId(const int paperId);
};

#endif
