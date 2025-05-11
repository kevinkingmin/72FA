#ifndef PROCESSSTEPDAO_H
#define PROCESSSTEPDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QVector>

template<class T>
class Singleton;

class QSqlQuery;
class ProcessStepModel;

class DAOSHARED_EXPORT ProcessStepDao
{
private:
    ProcessStepDao();
    ProcessStepDao(ProcessStepDao &)=delete;
    ProcessStepDao(ProcessStepDao &&)=delete;
    ProcessStepDao &operator=(const ProcessStepDao&)=delete;
    ProcessStepDao &operator=(ProcessStepDao&&)=delete;
    using ptrModel= QSharedPointer<ProcessStepModel>;
    friend Singleton<ProcessStepDao>;

    void getTable();
public:
    ~ProcessStepDao();
    static ProcessStepDao *instance();
    QVector<ptrModel> getAllRows();
    bool updateActTime(int id,int ms);
private:
    QVector<ptrModel>_vect;
};

#endif // SEXDAO_H
