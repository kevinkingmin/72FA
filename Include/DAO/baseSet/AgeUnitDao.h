#ifndef AGEUNITDAO_H
#define AGEUNITDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QVector>
#include <QMap>

template <class T>
class Singleton;

class QSqlQuery;
class AgeUnitModel;
class DAOSHARED_EXPORT AgeUnitDao
{
private:
    AgeUnitDao();
    AgeUnitDao(AgeUnitDao &)=delete;
    AgeUnitDao(AgeUnitDao &&)=delete;
    AgeUnitDao &operator=(const AgeUnitDao&)=delete;
    AgeUnitDao &operator=(AgeUnitDao&&)=delete;

    friend Singleton<AgeUnitDao>;
    using ptrModel=QSharedPointer<AgeUnitModel>;

    void getTable();
public:
    ~AgeUnitDao();
    static AgeUnitDao *instance();
    QVector<ptrModel> getAllRows();

protected:
    QVector<ptrModel>_vect;
};

#endif // AGEUNITDAO_H
