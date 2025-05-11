#ifndef BEDNODAO_H
#define BEDNODAO_H
#include "../dao.h"
#include <QVector>
#include <QMap>
#include <QSharedPointer>

template<class T>
class Singleton;

class BedNoModel;
class QSqlQuery;

class DAOSHARED_EXPORT BedNoDao
{
private:
    BedNoDao();
    BedNoDao(BedNoDao &)=delete;
    BedNoDao(BedNoDao &&)=delete;
    BedNoDao &operator=(const BedNoDao&)=delete;
    BedNoDao &operator=(BedNoDao&&)=delete;

    using ptrModel=QSharedPointer<BedNoModel>;
    friend Singleton<BedNoDao>;

    void getTable();
    void queryBindValue(QSqlQuery &query, ptrModel pm);
public:
    ~BedNoDao();
    static BedNoDao *instance();
    bool deleteById(uint id);
    bool updateModel(ptrModel pm);
    bool insertModel(ptrModel pm);
    QVector<ptrModel>getAllRows();
private:
    QMap<uint,ptrModel>_map;
};

#endif // BEDNODAO_H
