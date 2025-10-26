#ifndef COMPANY_DAO_H
#define COMPANY_DAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QVector>

template<class T>
class Singleton;

class QSqlQuery;
class CompanyModel;

class DAOSHARED_EXPORT CompanyDao
{
private:
    CompanyDao();
    CompanyDao(CompanyDao &)=delete;
    CompanyDao(CompanyDao &&)=delete;
    CompanyDao &operator=(const CompanyDao&)=delete;
    CompanyDao &operator=(CompanyDao&&)=delete;
    friend Singleton<CompanyDao>;
public:
    ~CompanyDao();
    static CompanyDao *instance();
    QVector<CompanyModel> getAllRows();
    bool getModel(const int id, CompanyModel& out);
    bool insertModel(const CompanyModel& model);
    bool deleteModel(const int id);
private:
};

#endif // PROCESSDAO_H
