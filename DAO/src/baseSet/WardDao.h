#ifndef WARDDAO_H
#define WARDDAO_H
#include "../dao.h"
#include <QVector>
#include <QMap>
#include <QSharedPointer>

template<class T>
class Singleton;

class WardModel;
class QSqlQuery;

class DAOSHARED_EXPORT WardDao
{
private:
    WardDao();
    WardDao(WardDao &)=delete;
    WardDao(WardDao &&)=delete;
    WardDao &operator=(const WardDao&)=delete;
    WardDao &operator=(WardDao&&)=delete;

    using ptrModel=QSharedPointer<WardModel>;
    friend Singleton<WardDao>;

    void getTable();
    void queryBindValue(QSqlQuery &query, ptrModel pm);
public:
    ~WardDao();
    static WardDao *instance();
    bool deleteById(uint id);
    bool updateModel(ptrModel pm);
    bool insertModel(ptrModel pm);
    QVector<ptrModel>getAllRows();
private:
    QMap<uint,ptrModel>_map;
};

#endif // WARDDAO_H
