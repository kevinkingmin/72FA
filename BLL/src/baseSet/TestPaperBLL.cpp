#include "TestPaperBLL.h"
#include "../Include/DAO/baseSet/TestPaperDao.h"
#include "../Include/Model/baseSet/TestPaperModel.h"
#include <algorithm>
#include <vector>



TestPaperBLL::TestPaperBLL()
    :_dao(TestPaperDao::instance())
{
}

QVector<TestPaperBLL::ptrModel> TestPaperBLL::getRowsByCompanyId(int companyId)
{
    auto vect=_dao->getAllRows();
    QVector<ptrModel>outVect;
    for(auto it:vect)
    {
        if(it->getCompanyId()==companyId)
            outVect.push_back(it);
    }
    return outVect;
}

// 比较函数，用于按照对象的属性进行排序
bool TestPaperBLL::compareObjects1(const ptrModel &obj1, const ptrModel &obj2) {
	return obj1->getSort_idx() < obj2->getSort_idx(); // 这里假设您希望按照property属性升序排序
}

QVector<TestPaperBLL::ptrModel> TestPaperBLL::getOnUsedRowsByCompanyId(int companyId)
{
    auto vect=_dao->getAllRows();
    QVector<ptrModel>outVect;
    for(auto it:vect)
    {
        if(it->getCompanyId()==companyId && !it->getIsDelete())
            outVect.push_back(it);
    }
	// 使用 lambda 表达式对属性进行排序
	std::sort(outVect.begin(), outVect.end(), [](const ptrModel &a, const ptrModel &b) {
		return a->getSort_idx() < b->getSort_idx();
	});
    return outVect;
}

QVector<TestPaperBLL::ptrModel> TestPaperBLL::getAllRows()
{
    return _dao->getAllRows();
}

TestPaperBLL::ptrModel TestPaperBLL::getRowById(int id)
{
    auto vect=_dao->getAllRows();
    for(auto it:vect)
    {
        if(it->getID()==id)
            return it;
    }
    return nullptr;
}
