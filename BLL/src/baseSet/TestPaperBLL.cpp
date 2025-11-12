#include "TestPaperBLL.h"
#include "../Include/DAO/baseSet/TestPaperDao.h"
#include "../Include/Model/baseSet/TestPaperModel.h"
#include <algorithm>
#include <vector>



TestPaperBLL::TestPaperBLL()
    :_dao(TestPaperDao::instance())
{
}

QVector<TestPaperModel> TestPaperBLL::getOnUsedRowsByCompanyId(int companyId)
{
    auto vect=_dao->getAllRows();
    QVector<TestPaperModel>outVect;
    for(auto it:vect)
    {
        if(it.getCompanyId()==companyId && !it.isPaperHide())
            outVect.push_back(it);
    }
    // 使用 lambda 表达式对属性进行排序
    std::sort(outVect.begin(), outVect.end(), [](TestPaperModel &a, TestPaperModel &b) {
        return a.getPaperSortIdxOnUi() < b.getPaperSortIdxOnUi();
    });
    return outVect;
}

QVector<TestPaperModel> TestPaperBLL::getEnablePaper(int processId)
{
    auto vect=_dao->getAllRows();
    QVector<TestPaperModel>outVect;
    for(auto it:vect)
    {
        if(it.getProcessId()==processId && !it.isPaperHide())
        {
            outVect.push_back(it);
        }
    }
    // 使用 lambda 表达式对属性进行排序
    std::sort(outVect.begin(), outVect.end(), [](TestPaperModel &a, TestPaperModel &b) {
        return a.getPaperSortIdxOnUi() < b.getPaperSortIdxOnUi();
    });
    return outVect;
}

QVector<TestPaperModel> TestPaperBLL::getAllRows()
{
    return _dao->getAllRows();
}

bool TestPaperBLL::getRowById(int id, TestPaperModel& out)
{
    auto vect=_dao->getAllRows();
    for(auto it:vect)
    {
        if(it.getId()==id)
        {
            out = std::move(it);
            return true;
        }
    }
    return false;
}
