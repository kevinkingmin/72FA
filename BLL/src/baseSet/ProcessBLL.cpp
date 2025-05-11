#include "ProcessBLL.h"
#include "../Include/DAO/baseSet/ProcessDao.h"
#include "../Include/Model/baseSet/ProcessModel.h"

ProcessBLL::ProcessBLL():_dao(ProcessDao::instance())
{

}

QVector<ProcessBLL::ptrModel> ProcessBLL::getAllRows()
{
    return _dao->getAllRows();
}

ProcessBLL::ptrModel ProcessBLL::getRowById(int id)
{
    auto vect = _dao->getAllRows();
    for(auto it : vect)
    {
        if(it->getId()==id)
            return it;
    }
    return nullptr;
}
