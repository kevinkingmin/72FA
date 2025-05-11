#ifndef SAMPLEDAO_H
#define SAMPLEDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QMap>
#include <QVector>


template<class T>
class Singleton;

class QSqlQuery;
class SampleModel;
class SampleTestDao;
class SampleTestModel;

class DAOSHARED_EXPORT SampleDao
{
private:
    SampleDao();
    SampleDao(SampleDao &)=delete;
    SampleDao(SampleDao &&)=delete;
    SampleDao &operator=(const SampleDao&)=delete;
    SampleDao &operator=(SampleDao&&)=delete;
    using ptrModel=QSharedPointer<SampleModel>;
    using ptrTest=QSharedPointer<SampleTestModel>;
    friend Singleton<SampleDao>;
    //void getTable();
    void queryBindValue(QSqlQuery &query, ptrModel pm);
public:
    ~SampleDao();
    static SampleDao *instance();
    //硬删除，没有测试结果的
    bool deleteHardByIds(QVector<QString> ids);
    //只有未完成的样本才可以进行修改
    bool updateModel(ptrModel pm);
    bool updateModel(QVector<ptrModel>vect);

    bool insertModel(QVector<std::tuple<ptrModel ,QVector<ptrTest>>>tps);
	QList<SampleModel> getSampleList(QString query_condition);

    quint64 getMaxId();
private:
    //QMap<QString, ptrModel>_map;
    QString _editStr;
    QString _insertStr;
    SampleTestDao *_testDao;
};

#endif // SAMPLEDAO_H
