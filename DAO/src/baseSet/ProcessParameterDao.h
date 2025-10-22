#ifndef PROCESS_PARAMETER_DAO_H
#define PROCESS_PARAMETER_DAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QVector>
#include <QVariant>

template<class T>
class Singleton;
class ProcessParameterModel;
class QSqlQuery;

class DAOSHARED_EXPORT ProcessParameterDao
{
private:
    ProcessParameterDao();
    ProcessParameterDao(ProcessParameterDao &)=delete;
    ProcessParameterDao(ProcessParameterDao &&)=delete;
    ProcessParameterDao &operator=(const ProcessParameterDao&)=delete;
    ProcessParameterDao &operator=(ProcessParameterDao&&)=delete;
    friend Singleton<ProcessParameterDao>;
public:
    ~ProcessParameterDao();
    using ptrModel= QSharedPointer<ProcessParameterModel>;
    static ProcessParameterDao *instance();
    QVector<ProcessParameterModel> getAllRows(int processId);
    bool selectModel(int stepId, ProcessParameterModel& out);
    bool delectModel(int stepId);
    bool insert(ProcessParameterModel& model);
    bool update(int stepId, ProcessParameterModel& model);
private:
    //QVector<ptrModel>_vect;
};

#endif // PROCESSPARADAO_H
