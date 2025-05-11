#include "ProcessStepBLL.h"
#include "../Include/DAO/baseSet/ProcessStepDao.h"
#include "../Include/Model/baseSet/ProcessStepModel.h"

ProcessStepBLL::ProcessStepBLL()
    :_dao(ProcessStepDao::instance())
{
}

QVector<ProcessStepBLL::ptrModel> ProcessStepBLL::getAllRows()
{
    return _dao->getAllRows();
}

ProcessStepBLL::ptrModel ProcessStepBLL::getRowById(int id)
{
    auto vect = _dao->getAllRows();
    for(auto it:vect)
    {
        if(it->getId()==id)
            return it;
    }
    return nullptr;
}

bool ProcessStepBLL::updateActTime(int id, int ms)
{
    return _dao->updateActTime(id,ms);
}
