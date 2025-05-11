#ifndef TESTPAPERBLL_H
#define TESTPAPERBLL_H
#include "../bll.h"
#include <QSharedPointer>
#include <QVector>
class TestPaperModel;
class TestPaperDao;
class BLLSHARED_EXPORT TestPaperBLL
{
public:
    using ptrModel=QSharedPointer<TestPaperModel>;
    TestPaperBLL();

	bool compareObjects1(const ptrModel &obj1, const ptrModel &obj2);
    QVector<ptrModel> getRowsByCompanyId(int companyId);
    QVector<ptrModel> getOnUsedRowsByCompanyId(int companyId);
    QVector<ptrModel> getAllRows();
    ptrModel getRowById(int id);

private:
    TestPaperDao *_dao;
};

#endif // TESTPAPERBLL_H
