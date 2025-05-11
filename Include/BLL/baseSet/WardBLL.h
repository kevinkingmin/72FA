#ifndef WARDBLL_H
#define WARDBLL_H
#include "../bll.h"
#include <QSharedPointer>
#include <QVector>

class WardModel;

class BLLSHARED_EXPORT WardBLL
{
public:
    WardBLL();
    using ptrModel=QSharedPointer<WardModel>;

    QVector<ptrModel>getAllRows();
    QVector<ptrModel> getRowsByIds(QVector<uint>ids);
    ptrModel getRowById(uint id);
    int updateByModel(ptrModel pm);
    bool deleteById(uint id);
    int insertModel(ptrModel pm);
};

#endif // WARDBLL_H
