#ifndef PROCESSPARADAO_H
#define PROCESSPARADAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QVector>
#include <QVariant>

template<class T>
class Singleton;
class ProcessParaModel;
class QSqlQuery;

class DAOSHARED_EXPORT ProcessParaDao
{
private:
    ProcessParaDao();
    ProcessParaDao(ProcessParaDao &)=delete;
    ProcessParaDao(ProcessParaDao &&)=delete;
    ProcessParaDao &operator=(const ProcessParaDao&)=delete;
    ProcessParaDao &operator=(ProcessParaDao&&)=delete;

    using ptrModel= QSharedPointer<ProcessParaModel>;

    friend Singleton<ProcessParaDao>;
    void getTable();
public:
    ~ProcessParaDao();
    static ProcessParaDao *instance();
    QVector<ptrModel> getAllRows();
private:
    QVector<ptrModel>_vect;
};

#endif // PROCESSPARADAO_H
