#ifndef REAGENTBLL_H
#define REAGENTBLL_H
#include<QVector>
#include<QSharedPointer>
#include "../bll.h"

class ReagentDao;
class ReagentModel;
class TestParasModel;
class BLLSHARED_EXPORT ReagentBLL
{
public:
    using ptrModel=QSharedPointer<ReagentModel>;
    ReagentBLL();

    bool deleteById(int id);
    bool editModel(ptrModel pm);
    QVector<ptrModel>getAllRows();
    ptrModel getRowById(int id);
    //ptrModel getReagent(const int &rid, const int &paperId, const int &processParaId);
    ptrModel getReagent(const int &rid, const int &paperId, const int companyId);
    QVector<ptrModel> getReagent(const QSet<QString>& reagentNameVect);
    QVector<ptrModel> getReagent(const int companyId, const QSet<int>& pumpNoSet);
    QVector<ptrModel> getReagent(const int companyId, const QSet<int>& pumpNoSet, QSet<int>& paperIdVect);
    ptrModel getReagent(const QString& reagentName);
    ptrModel getReagent(const int& rid);
private:
    ReagentDao *_dao;
};

#endif // REAGENTBLL_H
