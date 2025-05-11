#ifndef DEPARTMENTDAO_H
#define DEPARTMENTDAO_H
#include "../dao.h"
#include <QVector>
#include <QMap>
#include <QSharedPointer>

template<class T>
class Singleton;

class DepartmentModel;
class QSqlQuery;

class DAOSHARED_EXPORT DepartmentDao
{
private:
    DepartmentDao();
    DepartmentDao(DepartmentDao &)=delete;
    DepartmentDao(DepartmentDao &&)=delete;
    DepartmentDao &operator=(const DepartmentDao&)=delete;
    DepartmentDao &operator=(DepartmentDao&&)=delete;

    using ptrModel=QSharedPointer<DepartmentModel>;
    friend Singleton<DepartmentDao>;
    void getTable();
    void queryBindValue(QSqlQuery &query, ptrModel pm);
public:
    ~DepartmentDao();
    static DepartmentDao *instance();
    bool deleteById(uint id);
    bool updateModel(ptrModel pm);
    bool insertModel(ptrModel pm);
    QVector<ptrModel>getAllRows();
private:
    QMap<uint,ptrModel>_map;
};

#endif // DEPARTMENTDAO_H
