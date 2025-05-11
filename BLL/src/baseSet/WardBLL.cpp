#include "WardBLL.h"
#include "../Include/DAO/baseSet/WardDao.h"
#include "../Include/Model/baseSet/WardModel.h"

WardBLL::WardBLL()
{

}

QVector<WardBLL::ptrModel> WardBLL::getAllRows()
{
    return WardDao::instance()->getAllRows();
}

QVector<WardBLL::ptrModel> WardBLL::getRowsByIds(QVector<uint> ids)
{
    QVector<ptrModel>outVect;
    auto vect=WardDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(ids.contains(it->getID()))
            outVect.push_back(it);
    }
    return outVect;
}

WardBLL::ptrModel WardBLL::getRowById(uint id)
{
    auto vect=WardDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(it->getID()==id)
            return it;
    }
    return nullptr;
}

int WardBLL::updateByModel(WardBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getID()<=0 || pm->getWardName().isEmpty() || pm->getShortKey().isEmpty())
        return -2;
    return WardDao::instance()->updateModel(pm)?1:-3;
}

bool WardBLL::deleteById(uint id)
{
    if(id<=0)
        return false;
    return WardDao::instance()->deleteById(id);
}

int WardBLL::insertModel(WardBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getWardName().isEmpty() || pm->getShortKey().isEmpty())
        return -2;
    return WardDao::instance()->insertModel(pm)?1:-3;
}
