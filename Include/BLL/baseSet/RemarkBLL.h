#ifndef REMARKBLL_H
#define REMARKBLL_H
#include "../bll.h"
#include <QSharedPointer>
#include <QVector>

class RemarkModel;

class BLLSHARED_EXPORT RemarkBLL
{
public:
    RemarkBLL();
    using ptrModel=QSharedPointer<RemarkModel>;

    QVector<ptrModel>getAllRows();
    QVector<ptrModel> getRowsByIds(QVector<uint>ids);
    ptrModel getRowById(uint id);
    int updateByModel(ptrModel pm);
    bool deleteById(uint id);
    int insertModel(ptrModel pm);
};

#endif // REMARKBLL_H
