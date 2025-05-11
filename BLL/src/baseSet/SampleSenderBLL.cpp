#include "SampleSenderBLL.h"
#include "../Include/Model/baseSet/SampleSenderModel.h"
#include "../Include/DAO/baseSet/SampleSenderDao.h"

SampleSenderBLL::SampleSenderBLL()
{
}

QVector<SampleSenderBLL::ptrModel> SampleSenderBLL::getAllRows()
{
    return SampleSenderDao::instance()->getAllRows();
}

QVector<SampleSenderBLL::ptrModel> SampleSenderBLL::getRowsByIds(QVector<uint> ids)
{
    QVector<ptrModel>outVect;
    auto vect=SampleSenderDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(ids.contains(it->getID()))
            outVect.push_back(it);
    }
    return outVect;
}

int SampleSenderBLL::updateByModel(SampleSenderBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getID()<=0 || pm->getSenderName().isEmpty() || pm->getShortKey().isEmpty())
        return -2;
    return SampleSenderDao::instance()->updateModel(pm)?1:-3;
}

bool SampleSenderBLL::deleteById(uint id)
{
    if(id<=0)
        return false;
    return SampleSenderDao::instance()->deleteById(id);
}

int SampleSenderBLL::insertModel(SampleSenderBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getSenderName().isEmpty() || pm->getShortKey().isEmpty())
        return -2;
    return SampleSenderDao::instance()->insertModel(pm)?1:-3;
}
