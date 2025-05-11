#ifndef SAMPLESENDERBLL_H
#define SAMPLESENDERBLL_H
#include "../bll.h"
#include <QSharedPointer>
#include <QVector>

class SampleSenderModel;

class BLLSHARED_EXPORT SampleSenderBLL
{
public:
    SampleSenderBLL();
    using ptrModel=QSharedPointer<SampleSenderModel>;

    QVector<ptrModel>getAllRows();
    QVector<ptrModel> getRowsByIds(QVector<uint>ids);
    int updateByModel(ptrModel pm);
    bool deleteById(uint id);
    int insertModel(ptrModel pm);
};

#endif // SAMPLESENDERBLL_H
