#include "InstrumentParasSetBLL.h"
#include "../Include/DAO/baseSet/InstrumentParasSetDao.h"
#include "../Include/Model/baseSet/InstrumentParasSetModel.h"

InstrumentParasSetBLL::InstrumentParasSetBLL():_dao(InstrumentParasSetDao::instance())
{
}

QVector<InstrumentParasSetModel> InstrumentParasSetBLL::getAllRows()
{
    return _dao->getAllRows();
}

QVector<InstrumentParasSetModel> InstrumentParasSetBLL::getRowsByIds(QVector<uint> ids)
{
    auto vect=_dao->getAllRows();
    QVector<InstrumentParasSetModel>outvect;
    for(auto it:vect)
    {
        if(ids.contains(it.getId()))
            outvect.push_back(it);
    }
    return outvect;
}

InstrumentParasSetModel InstrumentParasSetBLL::getRowById(uint id)
{
    auto vect=_dao->getAllRows();
    for(auto it:vect)
    {
        if(it.getId()==id)
            return it;
    }
    return InstrumentParasSetModel();
}

bool InstrumentParasSetBLL::updateByModel(InstrumentParasSetModel pm)
{
    if(pm.getId()<=0)
        return false;
    return _dao->updateModel(pm);
}
