#include "DepartmentBLL.h"
#include "../Include/DAO/baseSet/DepartmentDao.h"
#include "../Include/Model/baseSet/DepartmentModel.h"

DepartmentBLL::DepartmentBLL()
{

}

QVector<DepartmentBLL::ptrModel> DepartmentBLL::getAllRows()
{
    return DepartmentDao::instance()->getAllRows();
}

QVector<DepartmentBLL::ptrModel> DepartmentBLL::getRowsByIds(QVector<uint> ids)
{
    QVector<ptrModel>outVect;
    auto vect=DepartmentDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(ids.contains(it->getID()))
            outVect.push_back(it);
    }
    return outVect;
}

DepartmentBLL::ptrModel DepartmentBLL::getRowById(uint id)
{
    auto vect=DepartmentDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(it->getID()==id)
            return it;
    }
    return nullptr;
}

int DepartmentBLL::updateByModel(DepartmentBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getID()<=0 || pm->getDepartmentName().isEmpty())
        return -2;
    return DepartmentDao::instance()->updateModel(pm)?1:-3;
}

bool DepartmentBLL::deleteById(uint id)
{
    if(id<=0)
        return false;
    return DepartmentDao::instance()->deleteById(id);
}

int DepartmentBLL::insertModel(DepartmentBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getDepartmentName().isEmpty())
        return -2;
    return DepartmentDao::instance()->insertModel(pm)?1:-3;
}
