#ifndef PROCESSDAO_H
#define PROCESSDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QVector>
#include "../Include/Model/baseSet/ProcessModel.h"

template<class T>
class Singleton;

class QSqlQuery;

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
    QVector<ProcessModel> getModelsFromSystemSet();
    bool getModel(const int processId, ProcessModel& out);
    bool insert(const int companyId, const QString& processName);
private:
};

#endif // PROCESSDAO_H
