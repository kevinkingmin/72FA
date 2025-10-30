#ifndef TESTPAPERDAO_H
#define TESTPAPERDAO_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "../dao.h"
template<class T>
class Singleton;

class TestPaperModel;
class QSqlQuery;
class DAOSHARED_EXPORT TestPaperDao
{
private:
    //using ptrModel=QSharedPointer<TestPaperModel>;
    TestPaperDao();
    TestPaperDao(TestPaperDao &)=delete;
    TestPaperDao(TestPaperDao &&)=delete;
    TestPaperDao &operator=(const TestPaperDao&)=delete;
    TestPaperDao &operator=(TestPaperDao&&)=delete;

    friend Singleton<TestPaperDao>;

    QVector<TestPaperModel> getModelFormQuery(QSqlQuery& query);
//    void getTable();
//    void queryBindValue(QSqlQuery &query, ptrModel pm);
public:
    ~TestPaperDao();
    static TestPaperDao *instance();
    bool deleteById(int id);
    QVector<TestPaperModel>getAllRows();
    QVector<QString> getAllNames();
    bool getModel(const int paperId, TestPaperModel& out);
    bool insert(TestPaperModel& model);
    bool update(TestPaperModel& model);
private:
    //QMap<int,ptrModel>_map;
};

#endif // TESTPAPERDAO_H
