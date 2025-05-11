#ifndef AGEUNITBLL_H
#define AGEUNITBLL_H
#include "../bll.h"
#include <QSharedPointer>
#include <QVector>


class AgeUnitModel;
class BLLSHARED_EXPORT AgeUnitBLL
{
public:
    AgeUnitBLL();
    using ptrModel=QSharedPointer<AgeUnitModel>;

    QVector<ptrModel>getAllRows();
    QVector<ptrModel> getRowsByIds(QVector<uint>ids);
};

#endif // AGEUNITBLL_H
