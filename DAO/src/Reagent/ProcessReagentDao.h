#ifndef PROCESSREAGENTDAO_H
#define PROCESSREAGENTDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QMap>

template<class A>
class Singleton;

class ProcessReagentModel;

class DAOSHARED_EXPORT ProcessReagentDao
{
private:
    ProcessReagentDao();
    ProcessReagentDao(ProcessReagentDao &)=delete;
    ProcessReagentDao(ProcessReagentDao &&)=delete;
    ProcessReagentDao &operator=(const ProcessReagentDao&)=delete;
    ProcessReagentDao &operator=(ProcessReagentDao&&)=delete;
    using ptrModel= QSharedPointer<ProcessReagentModel>;
    friend Singleton<ProcessReagentDao>;
public:
    ~ProcessReagentDao();
    static ProcessReagentDao *instance();
    QVector<ptrModel>getAllRows();
private:
    void getTable();
    //void queryBindValue(QSqlQuery &query, ptrModel pm);
private:
    QMap<int, ptrModel>_map;
};

#endif // PROCESSREAGENTDAO_H
