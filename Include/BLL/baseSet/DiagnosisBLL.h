#ifndef DIAGNOSISBLL_H
#define DIAGNOSISBLL_H
#include "../bll.h"
#include <QSharedPointer>
#include <QVector>

class DiagnosisModel;

class BLLSHARED_EXPORT DiagnosisBLL
{
public:
    DiagnosisBLL();
    using ptrModel=QSharedPointer<DiagnosisModel>;

    QVector<ptrModel>getAllRows();
    QVector<ptrModel> getRowsByIds(QVector<uint>ids);
    ptrModel getRowById(uint id);
    int updateByModel(ptrModel pm);
    bool deleteById(uint id);
    int insertModel(ptrModel pm);
};

#endif // DIAGNOSISBLL_H
