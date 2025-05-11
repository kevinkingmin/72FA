#ifndef SAMPLETESTBLL_H
#define SAMPLETESTBLL_H
#include "../bll.h"
#include <QVector>
#include <QSharedPointer>

class SampleTestModel;
class SampleTestDao;

class BLLSHARED_EXPORT SampleTestBLL
{
public:
    SampleTestBLL();
    using ptrTest=QSharedPointer<SampleTestModel>;
    QVector<ptrTest> getAllRows();
    ptrTest getRowById(QString id);
    QVector<ptrTest> getRowsBySampleId(QString sampleId);
    bool updateModel(ptrTest pm);
private:
    SampleTestDao *_dao;
};

#endif // SAMPLETESTBLL_H
