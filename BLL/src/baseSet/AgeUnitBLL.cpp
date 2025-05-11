#include "AgeUnitBLL.h"
#include "../Include/DAO/baseSet/AgeUnitDao.h"
#include "../Include/Model/baseSet/AgeUnitModel.h"

AgeUnitBLL::AgeUnitBLL()
{

}

QVector<AgeUnitBLL::ptrModel> AgeUnitBLL::getAllRows()
{
    return AgeUnitDao::instance()->getAllRows();
}

QVector<AgeUnitBLL::ptrModel> AgeUnitBLL::getRowsByIds(QVector<uint> ids)
{
    auto vect=AgeUnitDao::instance()->getAllRows();
    QVector<ptrModel>outVect;
    for(auto it:vect)
    {
        if(ids.contains(it->getID()))
            outVect.push_back(it);
    }
    return outVect;
}
