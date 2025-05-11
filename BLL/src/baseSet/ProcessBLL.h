#ifndef PROCESSBLL_H
#define PROCESSBLL_H
#include "../bll.h"
#include <QSharedPointer>
class ProcessDao;
class ProcessModel;

class BLLSHARED_EXPORT ProcessBLL
{
public:
    using ptrModel=QSharedPointer<ProcessModel>;
    ProcessBLL();
    QVector<ptrModel>getAllRows();
    ptrModel getRowById(int id);
private:
    ProcessDao *_dao;
};

#endif // PROCESSBLL_H
