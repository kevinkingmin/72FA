#include "ReagentBLL.h"
#include "ProcessReagentBLL.h"
#include "../Include/Model/reagent/ReagentModel.h"
#include "../Include/Model/reagent/ProcessReagentModel.h"
#include "../Include/DAO/reagent/ReagentDao.h"
#include "../Include/Model/sample/TestParasModel.h"
#include "../Include/Utilities/log.h"

ReagentBLL::ReagentBLL()
    :_dao(ReagentDao::instance())
{
}

bool ReagentBLL::deleteById(int id)
{
    if(id<=0)
    {
        eLog("删除错误，id:{}",id);
        return false;
    }
    return _dao->deleteById(id);
}

bool ReagentBLL::editModel(ReagentBLL::ptrModel pm)
{
    if(pm.isNull())
    {
        eLog("编辑的对象不能为null");
        return false;
    }

    if(pm->getID()<=0)
    {
        if(pm->getPumpNo()<0)
        {
            eLog("没有指定泵类型，pumpNo:{}",pm->getPumpNo());
            return false;
        }

        auto vect = _dao->getAllRows();
        bool isExist=false;
        for(auto it:vect)
        {
            if(it->getPumpNo()==pm->getPumpNo())
            {
                pm->setID(it->getID());
                isExist=true;
                break;
            }
        }

        if(!isExist)
            return _dao->insertModel(pm);
    }
    return _dao->updateModel(pm);
}

QVector<ReagentBLL::ptrModel> ReagentBLL::getAllRows()
{
    return _dao->getAllRows();
}

ReagentBLL::ptrModel ReagentBLL::getRowById(int id)
{
    auto vect=_dao->getAllRows();
    for(auto it:vect)
    {
        if(it->getID()==id)
            return it;
    }
    return nullptr;
}
/*
ReagentBLL::ptrModel ReagentBLL::getReagent(const int &rid, const int &paperId, const int &processParaId)
{
    if(rid>=0)
    {
        auto reagent=getRowById(rid);
        if(reagent.isNull())
        {
            eLog("没有相关的试剂信息,reagentId:{}",rid);
            return nullptr;
        }
        return reagent;
    }
    //rid<0的情况
    auto processReagent=ProcessReagentBLL().getModel(processParaId,paperId);
    if(processReagent.isNull())
    {
        eLog("获取试剂信息失败,processParaId:{},paperId:{},slotPos:{}",processParaId,paperId,paperId);
        return nullptr;
    }
    auto reagentId=processReagent->getReagentId();
    auto reagent=ReagentBLL().getRowById(reagentId);
    if(reagent.isNull())
    {
        eLog("没有找到相应的试剂,reagentId:{}",reagentId);
        return nullptr;
    }
    return reagent;
}
*/
ReagentBLL::ptrModel ReagentBLL::getReagent(const int & rid, const int & paperId, const int companyId)
{
    if (rid >= 0)
    {
        auto reagent = getRowById(rid);
        if (reagent.isNull())
        {
            eLog("没有相关的试剂信息,reagentId:{}", rid);
            return nullptr;
        }
        return reagent;
    }

    auto vect{ _dao->getAllRows() };
    for (auto reagent : vect)
    {
        if (reagent->getPaperId() == paperId && companyId == reagent->getCompanyID())
            return reagent;
    }
    eLog("no reagent found,paperId:{},companyId:{}",paperId,companyId);
    return nullptr;
}

ReagentBLL::ptrModel ReagentBLL::getReagent_new(const int &rid, const int &paperId, const int companyId)
{
    if(paperId>=929){
        if (rid >= 0)
        {
            auto reagent = getRowById(rid);
            if (reagent.isNull())
            {
                eLog("没有相关的试剂信息,reagentId:{}", rid);
                return nullptr;
            }
            return reagent;
        }

        auto vect{ _dao->getAllRows() };
        for (auto reagent : vect)
        {
            if(rid==-2){
                int paper_id_set_value = reagent->getPaperId();
                int company_id_set_value = reagent->getCompanyID();
                if (paper_id_set_value == paperId && companyId == company_id_set_value&& reagent->getReagentName().contains("抗人IgE抗体液"))
                    return reagent;
            }else if(rid==-1){
                int paper_id_set_value = reagent->getPaperId();
                int company_id_set_value = reagent->getCompanyID();
                if (paper_id_set_value == paperId && companyId == company_id_set_value&& reagent->getReagentName().contains("酶结合物"))
                    return reagent;
            }
        }
        eLog("no reagent found,paperId:{},companyId:{}",paperId,companyId);
        return nullptr;
    }else{
        if (rid >= 0)
        {
            auto reagent = getRowById(rid);
            if (reagent.isNull())
            {
                eLog("没有相关的试剂信息,reagentId:{}", rid);
                return nullptr;
            }
            return reagent;
        }

        auto vect{ _dao->getAllRows() };
        for (auto reagent : vect)
        {
            if (reagent->getPaperId() == paperId && companyId == reagent->getCompanyID())
                return reagent;
        }
        eLog("no reagent found,paperId:{},companyId:{}",paperId,companyId);
        return nullptr;
    }

}
