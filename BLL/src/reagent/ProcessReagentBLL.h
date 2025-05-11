#ifndef PROCESSREAGENTBLL_H
#define PROCESSREAGENTBLL_H
#include<QVector>
#include<QSharedPointer>
#include "../bll.h"

class ProcessReagentDao;
class ProcessReagentModel;

class BLLSHARED_EXPORT ProcessReagentBLL
{
public:
    using ptrModel=QSharedPointer<ProcessReagentModel>;
    ProcessReagentBLL();
    QVector<ptrModel>getAllRows();
    ptrModel getRowById(int id);
    ptrModel getModel(int processParaId,int paperId);
private:
    ProcessReagentDao *_dao;
};

#endif // PROCESSREAGENTBLL_H
