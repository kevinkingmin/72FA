#ifndef SAMPLESENDERDAO_H
#define SAMPLESENDERDAO_H
#include "../dao.h"
#include <QVector>
#include <QMap>
#include <QSharedPointer>
#include <QVariant>

template<class T>
class Singleton;

class SampleSenderModel;
class QSqlQuery;

class DAOSHARED_EXPORT SampleSenderDao
{
private:
    SampleSenderDao();
    SampleSenderDao(SampleSenderDao &)=delete;
    SampleSenderDao(SampleSenderDao &&)=delete;
    SampleSenderDao &operator=(const SampleSenderDao&)=delete;
    SampleSenderDao &operator=(SampleSenderDao&&)=delete;

    using prtModel=QSharedPointer<SampleSenderModel>;
    friend Singleton<SampleSenderDao>;
    void getTable();
    void queryBindValue(QSqlQuery &query, prtModel pm);

public:
    ~SampleSenderDao();
    static SampleSenderDao *instance();
    bool deleteById(uint id);
    bool updateModel(prtModel pm);
    bool insertModel(prtModel pm);
    QVector<prtModel>getAllRows();
private:
    QMap<uint,prtModel>_map;
};

#endif // SAMPLESENDERDAO_H
