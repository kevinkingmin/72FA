#include "ProcessParaBLL.h"
#include "QDebug"
#include "../Include/Model/reagent/ReagentModel.h"
#include "../Include/DAO/reagent/ReagentDao.h"
#include "../Include/Model/baseSet/ProcessModel.h"
#include "../Include/DAO/baseSet/ProcessDao.h"

ProcessParaBLL::ProcessParaBLL()
    :_dao(ProcessParameterDao::instance())
{
}

QVector<ProcessParaBLL::ptrModel> ProcessParaBLL::getAllRows(int processId)
{
    return toPtrVector(_dao->getAllRows(processId));
}

//得到孵育时间
QMap<int, int> ProcessParaBLL::getIncubationTime(QVector<int> pGroupIds)
{
    QString reagentFlag = "震荡孵育时间(s)";
    QMap<int, int>reagentIdAndProcessParaIdMap;
//    auto vect = _dao->getAllRows();
//    for (auto pm : vect)
//    {
//        if (!pGroupIds.contains(pm->getGroupId()))
//            continue;
//        auto vect = pm->getParas();
//        for (auto it : vect)
//        {
//            if (it.paraName != reagentFlag)
//                continue;
//            reagentIdAndProcessParaIdMap.insert(static_cast<int>(it.paraValue), pm->getId());
//        }
//    }
    return reagentIdAndProcessParaIdMap;
}

// 根据配置的流程, 获取泵号试剂名称与体积的QMap
QMap<int, std::tuple<QString, double>> ProcessParaBLL::getUnitReagentMl(const int processId, QSet<int> paperIdVect)
{
    QMap<int, std::tuple<QString, double>> rtnMap;
    QVector<ProcessParameterModel> processModelVect = _dao->selectModel(processId, ProcessParameterModel::ADD_REAGENT_CODE);
    ProcessModel process;
    if(!ProcessDao::instance()->getModel(processId, process)) return {};
    int companyId = process.getCompanyId();
    QVector<ReagentModel> reagentVect = ReagentDao::instance()->selectReagent(companyId);
    for (ProcessParameterModel& model : processModelVect)
    {
        ProcessParameterModel::AddReagentStrt strt;
        if (model.getAddReagent(strt))
        {
            for(ReagentModel& reagent : reagentVect)
            {
                if(strt._reagentName != reagent.getReagentName()) continue;
                 // 通用试剂直接获取泵号 专用试剂根据膜条重新匹配
                if(reagent.getReagentType() == 0 || (reagent.getReagentType() == 1 && paperIdVect.contains(reagent.getPaperId())))
                {
                    auto it = rtnMap.find(reagent.getPumpNo());
                    if (it != rtnMap.end())
                    {
                        std::get<1>(it.value()) += strt._reagentMl;
                    }
                    else
                    {
                        rtnMap[reagent.getPumpNo()] = {strt._reagentName, strt._reagentMl};
                    }
                }
            }
        }
    }
    return rtnMap;
}

std::tuple<int, double> ProcessParaBLL::getUnitReagentMl(const int processId, const int paperId, const QString& reagentName)
{
    QSet<int> paperIdVect = {paperId};
    QMap<int, std::tuple<QString, double>> reagentNameVolMap = getUnitReagentMl(processId, paperIdVect);
    for (int key : reagentNameVolMap.keys())
    {
        std::tuple<QString, double>& pumpVolumePair = reagentNameVolMap[key];
        QString name = std::get<0>(pumpVolumePair);
        if(name == reagentName)
        {
            return std::make_tuple(key, std::get<1>(pumpVolumePair));
        }
    }
    return std::make_tuple(1, 0);
}

QVector<ProcessParaBLL::ptrModel> ProcessParaBLL::toPtrVector(const QVector<ProcessParameterModel>& models)
{
    QVector<ptrModel> result;
    result.reserve(models.size());
    for (const auto& model : models)
    {
        result.append(QSharedPointer<ProcessParameterModel>::create(std::move(model)));
    }
    return result;
}

