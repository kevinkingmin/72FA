#include "SampleTestBLL.h"
#include "../Include/Model/sample/SampleTestModel.h"
#include "../Include/DAO/sample/SampleTestDao.h"

SampleTestBLL::SampleTestBLL()
    :_dao(SampleTestDao::instance())
{

}

QVector<SampleTestBLL::ptrTest> SampleTestBLL::getAllRows()
{
    return _dao->getAllRows();
}

SampleTestBLL::ptrTest SampleTestBLL::getRowById(QString id)
{
    auto vect = _dao->getAllRows();
    if(vect.isEmpty())
        return nullptr;
    for(auto it:vect)
    {
        if(it->getId()==id)
            return it;
    }
    return nullptr;
}

QVector<SampleTestBLL::ptrTest> SampleTestBLL::getRowsBySampleId(QString sampleId)
{
    QVector<ptrTest>outVect;
    auto vect = _dao->getAllRows();
    for(auto it:vect)
    {
        if(it->getSampleId()==sampleId)
            outVect.push_back(it);
    }
    return outVect;
}

bool SampleTestBLL::updateModel(SampleTestBLL::ptrTest pm)
{
    if(pm.isNull())
        return false;
    return _dao->updateModel(pm);
}
