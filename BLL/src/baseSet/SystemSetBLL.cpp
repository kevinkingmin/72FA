#include "SystemSetBLL.h"
#include "../Include/DAO/baseSet/SystemSetDao.h"
#include "../Include/Model/baseSet/SystemSetModel.h"

SystemSetBLL::SystemSetBLL()
{
}

QVector<SystemSetBLL::ptrModel> SystemSetBLL::getAllRows()
{
    return toPtrVector(SystemSetDao::instance()->getAllRows());
}

QVector<SystemSetBLL::ptrModel> SystemSetBLL::getRowsByIds(QVector<uint> ids)
{
    QVector<SystemSetModel>outVect;
    auto vect=SystemSetDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(ids.contains(it.getId()))
        {
            outVect.push_back(it);
        }
    }
    return toPtrVector(outVect);
}

SystemSetBLL::ptrModel SystemSetBLL::getRowById(uint id)
{
    SystemSetModel setModel;
    bool result=SystemSetDao::instance()->getModel(static_cast<int>(id), setModel);
    if(!result)
    {
        return nullptr;
    }
    return QSharedPointer<SystemSetModel>::create(std::move(setModel));
}

int SystemSetBLL::updateByModel(SystemSetBLL::ptrModel pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getId()<=0)
        return -2;
    return SystemSetDao::instance()->updateModel(*pm)?1:-3;
}

QVector<SystemSetBLL::ptrModel> SystemSetBLL::toPtrVector(const QVector<SystemSetModel>& models)
{
    QVector<ptrModel> result;
    result.reserve(models.size());
    for (const auto& model : models)
    {
        result.append(QSharedPointer<SystemSetModel>::create(std::move(model)));
    }
    return result;
}
