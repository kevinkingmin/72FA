#ifndef PROCESSSTEPBLL_H
#define PROCESSSTEPBLL_H
#include <QSharedPointer>
#include "../bll.h"

class ProcessStepModel;
class ProcessStepDao;

class BLLSHARED_EXPORT ProcessStepBLL
{
public:
    using ptrModel=QSharedPointer<ProcessStepModel>;
    ProcessStepBLL();
    QVector<ptrModel>getAllRows();
    ptrModel getRowById(int id);
    bool updateActTime(int id,int ms);
private:
    ProcessStepDao *_dao;
};

#endif // PROCESSSTEPBLL_H
