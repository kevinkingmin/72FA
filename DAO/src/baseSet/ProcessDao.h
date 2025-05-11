#ifndef PROCESSDAO_H
#define PROCESSDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QVector>

template<class T>
class Singleton;

class QSqlQuery;
class ProcessModel;

class DAOSHARED_EXPORT ProcessDao
{
private:
    ProcessDao();
    ProcessDao(ProcessDao &)=delete;
    ProcessDao(ProcessDao &&)=delete;
    ProcessDao &operator=(const ProcessDao&)=delete;
    ProcessDao &operator=(ProcessDao&&)=delete;
    using ptrModel= QSharedPointer<ProcessModel>;
    friend Singleton<ProcessDao>;

    void getTable();
public:
    ~ProcessDao();
    static ProcessDao *instance();
    QVector<ptrModel> getAllRows();
private:
    QVector<ptrModel>_vect;
};

#endif // PROCESSDAO_H
