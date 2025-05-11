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
    ptrModel getReagent_new(const int &rid, const int &paperId, const int companyId);
private:
    ReagentDao *_dao;
};

#endif // REAGENTBLL_H
