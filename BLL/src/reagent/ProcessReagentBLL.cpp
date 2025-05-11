#include "ProcessReagentBLL.h"
#include "../Include/DAO/reagent/ProcessReagentDao.h"
#include "../Include/Model/reagent/ProcessReagentModel.h"

ProcessReagentBLL::ProcessReagentBLL()
    :_dao(ProcessReagentDao::instance())
{

}

QVector<ProcessReagentBLL::ptrModel> ProcessReagentBLL::getAllRows()
{
    return _dao->getAllRows();
}

ProcessReagentBLL::ptrModel ProcessReagentBLL::getRowById(int id)
{
    auto vect = _dao->getAllRows();
    for(auto pm:vect)
    {
        if(pm->getId()==id)
            return pm;
    }
    return nullptr;
}

ProcessReagentBLL::ptrModel ProcessReagentBLL::getModel(int processParaId, int paperId)
{
    auto vect = _dao->getAllRows();
    for(auto pm:vect)
    {
        if(pm->getProcessParaId()==processParaId && pm->getPaperId()==paperId)
            return pm;
    }
    return nullptr;
}
