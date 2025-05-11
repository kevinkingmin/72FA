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

    using ptrModel= QSharedPointer<ItemModel>;
    friend Singleton<ItemDao>;
    void queryBindValue(QSqlQuery &query, ItemModel &m);
    void equalToPoint(ptrModel pm, ItemModel &m);
    void getTable();

public:
    ~ItemDao();
    static ItemDao *instance();
    QVector<ptrModel> getAllRows();
	QList<TestResultModel> getAllRows_list(int paper_id);
    bool update(ItemModel &m);
private:
    QMap<int,ptrModel> _map;
};

#endif // ITEMDAO_H
