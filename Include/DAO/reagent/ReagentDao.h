#ifndef REAGENTDAO_H
#define REAGENTDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QMap>

template<class A>
class Singleton;

class ReagentModel;
class DAOSHARED_EXPORT ReagentDao
{
private:
    ReagentDao();
    ReagentDao(ReagentDao &)=delete;
    ReagentDao(ReagentDao &&)=delete;
    ReagentDao &operator=(const ReagentDao&)=delete;
    ReagentDao &operator=(ReagentDao&&)=delete;
    using ptrModel= QSharedPointer<ReagentModel>;
    friend Singleton<ReagentDao>;
public:
    ~ReagentDao();
    static ReagentDao *instance();
    bool deleteById(int id);
    bool updateModel(ptrModel pm);
    bool insertModel(ptrModel pm);
    QVector<ptrModel>getAllRows();
private:
    void getTable();
    void queryBindValue(QSqlQuery &query, ptrModel pm);
private:
    QMap<int, ptrModel>_map;
};

#endif // REAGENTDAO_H
