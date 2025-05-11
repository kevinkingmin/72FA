#include "BedNoBLL.h"
#include "../Include/DAO/baseSet/BedNoDao.h"
#include "../Include/Model/baseSet/BedNoModel.h"

BedNoBLL::BedNoBLL()
{
}

QVector<BedNoBLL::ptrModel> BedNoBLL::getAllRows()
{
    return BedNoDao::instance()->getAllRows();
}

QVector<BedNoBLL::ptrModel> BedNoBLL::getRowsByIds(QVector<uint> ids)
{
    QVector<ptrModel>outVect;
    auto vect=BedNoDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(ids.contains(it->getID()))
            outVect.push_back(it);
    }
    return outVect;
}

BedNoBLL::ptrModel BedNoBLL::getRowById(uint id)
{
    auto vect=BedNoDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(it->getID()==id)
            return it;
    }
    return nullptr;
}

int BedNoBLL::updateByModel(BedNoBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getID()<=0 || pm->getBedNoName().isEmpty() || pm->getShortKey().isEmpty())
        return -2;
    return BedNoDao::instance()->updateModel(pm)?1:-3;
}

bool BedNoBLL::deleteById(uint id)
{
    if(id<=0)
        return false;
    return BedNoDao::instance()->deleteById(id);
}

int BedNoBLL::insertModel(BedNoBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getBedNoName().isEmpty() || pm->getShortKey().isEmpty())
        return -2;
    return BedNoDao::instance()->insertModel(pm)?1:-3;
}
