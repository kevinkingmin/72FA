#include "RemarkBLL.h"
#include "../Include/DAO/baseSet/RemarkDao.h"
#include "../Include/Model/baseSet/RemarkModel.h"

RemarkBLL::RemarkBLL()
{

}

QVector<RemarkBLL::ptrModel> RemarkBLL::getAllRows()
{
    return RemarkDao::instance()->getAllRows();
}

QVector<RemarkBLL::ptrModel> RemarkBLL::getRowsByIds(QVector<uint> ids)
{
    QVector<ptrModel>outVect;
    auto vect=RemarkDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(ids.contains(it->getID()))
            outVect.push_back(it);
    }
    return outVect;

}

RemarkBLL::ptrModel RemarkBLL::getRowById(uint id)
{
    auto vect=RemarkDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(it->getID()==id)
            return it;
    }
    return nullptr;
}

int RemarkBLL::updateByModel(RemarkBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getID()<=0 || pm->getStrRemark().isEmpty() || pm->getShortKey().isEmpty())
        return -2;
    return RemarkDao::instance()->updateModel(pm)?1:-3;
}

bool RemarkBLL::deleteById(uint id)
{
    if(id<=0)
        return false;
    return RemarkDao::instance()->deleteById(id);
}

int RemarkBLL::insertModel(RemarkBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if( pm->getStrRemark().isEmpty() || pm->getShortKey().isEmpty())
        return -2;
    return RemarkDao::instance()->insertModel(pm)?1:-3;
}
