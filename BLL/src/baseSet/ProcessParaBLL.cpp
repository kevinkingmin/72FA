#include "ProcessParaBLL.h"
#include "../Include/DAO/baseSet/ProcessParaDao.h"

ProcessParaBLL::ProcessParaBLL()
    :_dao(ProcessParaDao::instance())
{
}

QVector<ProcessParaBLL::ptrModel> ProcessParaBLL::getAllRows()
{
    return _dao->getAllRows();
}

ProcessParaBLL::ptrModel ProcessParaBLL::getRowById(int id)
{
    auto vect = _dao->getAllRows();
    for(auto it:vect)
    {
        if(it->getId()==id)
            return it;
    }
    return nullptr;
}

QVector<ProcessParaBLL::ptrModel> ProcessParaBLL::getRowByActId(int companyId,int actId){
    QVector<ProcessParaBLL::ptrModel>outvect{};
    auto vect = _dao->getAllRows();
    for(auto it:vect)
    {
        if(it->getActId()==actId&&it->getCompanyId()==companyId){
            outvect.push_back(it);
        }
    }
    return outvect;
}

QVector<ProcessParaBLL::ptrModel> ProcessParaBLL::getModels(int groupId, int companyId)
{
    QVector<ProcessParaBLL::ptrModel>outvect{};
    auto vect = _dao->getAllRows();
    for(auto it:vect)
    {
        if(it->getCompanyId()==companyId && it->getGroupId()==groupId)
        {
            outvect.push_back(it);
        }
    }
    return outvect;
}

QMap<int, int> ProcessParaBLL::getReagentIdAndParaIds(QVector<int> pGroupIds, int companyId)
{
    QString reagentFlag="RID";
    QMap<int, int>reagentIdAndProcessParaIdMap;
    auto vect =_dao->getAllRows();

    for(auto pm:vect)
    {
        int group_id = pm->getGroupId();
        if(!pGroupIds.contains(group_id) || pm->getCompanyId()!=companyId)
            continue;
        auto vect=pm->getParas();
        for(auto it:vect)
        {
            if(it.paraName!=reagentFlag)
                continue;
            reagentIdAndProcessParaIdMap.insert(static_cast<int>(it.paraValue),pm->getId());
        }
    }
    return reagentIdAndProcessParaIdMap;
}

//得到孵育时间
QMap<int, int> ProcessParaBLL::getIncubationTime(QVector<int> pGroupIds)
{
    QString reagentFlag = "震荡孵育时间(s)";
    QMap<int, int>reagentIdAndProcessParaIdMap;
    auto vect = _dao->getAllRows();
    for (auto pm : vect)
    {
        if (!pGroupIds.contains(pm->getGroupId()))
            continue;
        auto vect = pm->getParas();
        for (auto it : vect)
        {
            if (it.paraName != reagentFlag)
                continue;
            reagentIdAndProcessParaIdMap.insert(static_cast<int>(it.paraValue), pm->getId());
        }
    }
    return reagentIdAndProcessParaIdMap;
}


