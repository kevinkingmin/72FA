#ifndef REMARKDAO_H
#define REMARKDAO_H
#include "../dao.h"
#include <QVector>
#include <QMap>
#include <QSharedPointer>

template<class T>
class Singleton;

class RemarkModel;
class QSqlQuery;

class DAOSHARED_EXPORT RemarkDao
{
public:
    RemarkDao();
    RemarkDao(RemarkDao &)=delete;
    RemarkDao(RemarkDao &&)=delete;
    RemarkDao &operator=(const RemarkDao&)=delete;
    RemarkDao &operator=(RemarkDao&&)=delete;

    using ptrModel=QSharedPointer<RemarkModel>;
    friend Singleton<RemarkDao>;

    void getTable();
    void queryBindValue(QSqlQuery &query, ptrModel pm);
public:
    ~RemarkDao();
    static RemarkDao *instance();
    bool deleteById(uint id);
    bool updateModel(ptrModel pm);
    bool insertModel(ptrModel pm);
    QVector<ptrModel>getAllRows();
private:
    QMap<uint,ptrModel>_map;
};

#endif // REMARKDAO_H
