#include "SystemSetBLL.h"
#include "../Include/DAO/baseSet/SystemSetDao.h"
#include "../Include/Model/baseSet/SystemSetModel.h"

SystemSetBLL::SystemSetBLL()
{
}

QVector<SystemSetBLL::ptrModel> SystemSetBLL::getAllRows()
{
    return SystemSetDao::instance()->getAllRows();
}

QVector<SystemSetBLL::ptrModel> SystemSetBLL::getRowsByIds(QVector<uint> ids)
{
    QVector<ptrModel>outVect;
    auto vect=SystemSetDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(ids.contains(it->getId()))
            outVect.push_back(it);
    }
    return outVect;
}

SystemSetBLL::ptrModel SystemSetBLL::getRowById(uint id)
{
    auto vect=SystemSetDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(it->getId()==id)
            return it;
    }
    return nullptr;
}

int SystemSetBLL::updateByModel(SystemSetBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getId()<=0)
        return -2;
    return SystemSetDao::instance()->updateModel(pm)?1:-3;
}
