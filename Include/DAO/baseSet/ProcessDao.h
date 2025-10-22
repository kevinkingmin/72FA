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
    friend Singleton<ProcessDao>;
public:
    ~ProcessDao();
    static ProcessDao *instance();
    QVector<ProcessModel> getAllRows();
    QVector<ProcessModel> getModels(const int companyId);
    bool getModel(const int processId, ProcessModel& out);
    bool insert(const int companyId, const QString& processName);
private:
};

#endif // PROCESSDAO_H
