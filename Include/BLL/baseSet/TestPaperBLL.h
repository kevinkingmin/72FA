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
    //using ptrModel=QSharedPointer<TestPaperModel>;
    TestPaperBLL();
    QVector<TestPaperModel> getOnUsedRowsByCompanyId(int companyId);
    QVector<TestPaperModel> getAllRows();
    bool getRowById(int id, TestPaperModel& out);

private:
    TestPaperDao *_dao;
};

#endif // TESTPAPERBLL_H
