#ifndef SYSTEMSETBLL_H
#define SYSTEMSETBLL_H
#include "../bll.h"
#include <QSharedPointer>
#include <QVector>

class SystemSetModel;

class BLLSHARED_EXPORT SystemSetBLL
{
public:
    SystemSetBLL();
    using ptrModel=QSharedPointer<SystemSetModel>;

    QVector<ptrModel>getAllRows();
    QVector<ptrModel> getRowsByIds(QVector<uint>ids);
    ptrModel getRowById(uint id);
    int updateByModel(ptrModel pm);
};

#endif // SYSTEMSETBLL_H
