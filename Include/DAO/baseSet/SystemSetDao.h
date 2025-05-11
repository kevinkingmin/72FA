#ifndef SYSTEMSETDAO_H
#define SYSTEMSETDAO_H
#include "../dao.h"
#include <QVector>
#include <QMap>
#include <QSharedPointer>

template<class T>
class Singleton;

class SystemSetModel;
class QSqlQuery;

class DAOSHARED_EXPORT SystemSetDao
{
public:
    SystemSetDao();
    SystemSetDao(SystemSetDao &)=delete;
    SystemSetDao(SystemSetDao &&)=delete;
    SystemSetDao &operator=(const SystemSetDao&)=delete;
    SystemSetDao &operator=(SystemSetDao&&)=delete;

    using ptrModel=QSharedPointer<SystemSetModel>;
    friend Singleton<SystemSetDao>;

    void getTable();
    void queryBindValue(QSqlQuery &query, ptrModel pm);
public:
    ~SystemSetDao();
    static SystemSetDao *instance();
    bool deleteById(uint id);
    bool updateModel(ptrModel pm);
    QVector<ptrModel>getAllRows();
private:
    QMap<uint,ptrModel>_map;
};

#endif // SYSTEMSETDAO_H
