#include "DiagnosisBLL.h"
#include "../Include/DAO/baseSet/DiagnosisDao.h"
#include "../Include/Model/baseSet/DiagnosisModel.h"

DiagnosisBLL::DiagnosisBLL()
{
}

QVector<DiagnosisBLL::ptrModel> DiagnosisBLL::getAllRows()
{
    return DiagnosisDao::instance()->getAllRows();
}

QVector<DiagnosisBLL::ptrModel> DiagnosisBLL::getRowsByIds(QVector<uint> ids)
{
    QVector<ptrModel>outVect;
    auto vect=DiagnosisDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(ids.contains(it->getID()))
            outVect.push_back(it);
    }
    return outVect;
}

DiagnosisBLL::ptrModel DiagnosisBLL::getRowById(uint id)
{
    auto vect=DiagnosisDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(it->getID()==id)
            return it;
    }
    return nullptr;
}

int DiagnosisBLL::updateByModel(DiagnosisBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getID()<=0 || pm->getStrDiagnosis().isEmpty() || pm->getShortKey().isEmpty())
        return -2;
    return DiagnosisDao::instance()->updateModel(pm)?1:-3;
}

bool DiagnosisBLL::deleteById(uint id)
{
    if(id<=0)
        return false;
    return DiagnosisDao::instance()->deleteById(id);
}

int DiagnosisBLL::insertModel(DiagnosisBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getStrDiagnosis().isEmpty() || pm->getShortKey().isEmpty())
        return -2;
    return DiagnosisDao::instance()->insertModel(pm)?1:-3;
}
