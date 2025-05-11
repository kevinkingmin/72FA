#ifndef SAMPLETESTDAO_H
#define SAMPLETESTDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QMap>
#include <QVector>
#include "../Include/Model/result/TestResultModel.h"

template<class T>
class Singleton;

class QSqlQuery;
class SampleTestModel;
class SampleDao;

class DAOSHARED_EXPORT SampleTestDao
{
private:
    SampleTestDao();
    SampleTestDao(SampleTestDao &)=delete;
    SampleTestDao(SampleTestDao &&)=delete;
    SampleTestDao &operator=(const SampleTestDao&)=delete;
    SampleTestDao &operator=(SampleTestDao&&)=delete;

    using ptrModel=QSharedPointer<SampleTestModel>;
    friend Singleton<SampleTestDao>;
    friend SampleDao;
    void queryBindValue(QSqlQuery &query, ptrModel pm);
    void insertBindValue(QSqlQuery &query, ptrModel pm);
    void editBindValue(QSqlQuery &query, ptrModel pm);
public:
    ~SampleTestDao();
    static SampleTestDao *instance();
    bool updateModel(ptrModel pm);
	QString getMaxId();
private:
    QMap<QString,ptrModel>_map;
    QString _insertStr;
    QString _editStr;
};

#endif // SAMPLETESTDAO_H
