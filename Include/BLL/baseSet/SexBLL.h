#ifndef SEXBLL_H
#define SEXBLL_H
#include "../bll.h"
#include <QSharedPointer>
#include <QVector>


class SexModel;

class BLLSHARED_EXPORT SexBLL
{
public:
    SexBLL();
    using ptrModel=QSharedPointer<SexModel>;

    QVector<ptrModel>getAllRows();
    QVector<ptrModel> getRowsByIds(QVector<uint>ids);
};

#endif // SEXBLL_H
