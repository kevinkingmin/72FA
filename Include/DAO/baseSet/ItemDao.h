#ifndef ITEMDAO_H
#define ITEMDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QVector>
#include <QMap>
#include <QVariant>
#include "../Include/Comm/singleton.h"
#include "../Include/Model/baseSet/ItemModel.h"
#include "../Include/Model/result/TestResultModel.h"

template<class T>
class Singleton;
class ItemModel;
class QSqlQuery;
class DAOSHARED_EXPORT ItemDao
{
private:
    ItemDao();
    ItemDao(ItemDao &)=delete;
    ItemDao(ItemDao &&)=delete;
    ItemDao &operator=(const ItemDao&)=delete;
    ItemDao &operator=(ItemDao&&)=delete;

    friend Singleton<ItemDao>;
    void getTable();

public:
    ~ItemDao();
    static ItemDao *instance();
    QVector<ItemModel> selectItems(int paper_id);
    bool update(ItemModel &m);
    bool insert(ItemModel &m);
    bool deleteItems(int paper_id);
private:
};

#endif
