#ifndef DIAGNOSISDAO_H
#define DIAGNOSISDAO_H
#include "../dao.h"
#include <QVector>
#include <QMap>
#include <QSharedPointer>

template<class T>
class Singleton;

class DiagnosisModel;
class QSqlQuery;

class DAOSHARED_EXPORT DiagnosisDao
{
public:
    DiagnosisDao();
    DiagnosisDao(DiagnosisDao &)=delete;
    DiagnosisDao(DiagnosisDao &&)=delete;
    DiagnosisDao &operator=(const DiagnosisDao&)=delete;
    DiagnosisDao &operator=(DiagnosisDao&&)=delete;

    using ptrModel=QSharedPointer<DiagnosisModel>;
    friend Singleton<DiagnosisDao>;

    void getTable();
    void queryBindValue(QSqlQuery &query, ptrModel pm);
public:
    ~DiagnosisDao();
    static DiagnosisDao *instance();
    bool deleteById(uint id);
    bool updateModel(ptrModel pm);
    bool insertModel(ptrModel pm);
    QVector<ptrModel>getAllRows();
private:
    QMap<uint,ptrModel>_map;
};

#endif // DIAGNOSISDAO_H
