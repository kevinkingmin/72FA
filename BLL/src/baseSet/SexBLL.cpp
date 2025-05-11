#include "SexBLL.h"
#include "../Include/DAO/baseSet/SexDao.h"
#include "../Include/Model/baseSet/SexModel.h"

SexBLL::SexBLL()
{
}

QVector<SexBLL::ptrModel> SexBLL::getAllRows()
{
    return SexDao::instance()->getAllRows();
}

QVector<SexBLL::ptrModel> SexBLL::getRowsByIds(QVector<uint> ids)
{
    QVector<ptrModel>outVect;
    auto vect=SexDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(ids.contains(it->getID()))
            outVect.push_back(it);
    }
    return outVect;
}
