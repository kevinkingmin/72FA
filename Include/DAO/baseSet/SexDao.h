#ifndef SEXDAO_H
#define SEXDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QVector>

template<class T>
class Singleton;

class QSqlQuery;
class SexModel;

class DAOSHARED_EXPORT SexDao
{
private:
    SexDao();
    SexDao(SexDao &)=delete;
    SexDao(SexDao &&)=delete;
    SexDao &operator=(const SexDao&)=delete;
    SexDao &operator=(SexDao&&)=delete;
    using ptrModel= QSharedPointer<SexModel>;
    friend Singleton<SexDao>;

    void getTable();
public:
    ~SexDao();
    static SexDao *instance();
    QVector<ptrModel> getAllRows();
private:
    QVector<ptrModel>_vect;
};

#endif // SEXDAO_H
