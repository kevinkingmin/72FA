#ifndef BEDNOBLL_H
#define BEDNOBLL_H
#include "../bll.h"
#include <QSharedPointer>
#include <QVector>

class BedNoModel;

class BLLSHARED_EXPORT BedNoBLL
{
public:
    BedNoBLL();
    using ptrModel=QSharedPointer<BedNoModel>;

    QVector<ptrModel>getAllRows();
    QVector<ptrModel> getRowsByIds(QVector<uint>ids);
    ptrModel getRowById(uint id);
    int updateByModel(ptrModel pm);
    bool deleteById(uint id);
    int insertModel(ptrModel pm);
};

#endif // BEDNOBLL_H
