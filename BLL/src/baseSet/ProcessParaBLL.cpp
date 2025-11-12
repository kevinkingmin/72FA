#include "ProcessParaBLL.h"

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

// 获取试剂名称与体积的QMap
QMap<QString, std::tuple<int, double>> ProcessParaBLL::getUnitReagentMl(const int processId)
{
    QMap<QString, std::tuple<int, double>> rtnMap;
    QVector<ProcessParameterModel> processModelVect = _dao->selectModel(processId, ProcessParameterModel::ADD_REAGENT_CODE);

    for (ProcessParameterModel& model : processModelVect)
    {
        ProcessParameterModel::AddReagentStrt strt;
        if (model.getAddReagent(strt))
        {
            auto it = rtnMap.find(strt._reagentName);
            if (it != rtnMap.end())
            {
                std::get<1>(it.value()) += strt._reagentMl;
            }
            else
            {
                rtnMap[strt._reagentName] = {strt._pumpNo, strt._reagentMl};
            }
        }
    }
    return rtnMap;
}

std::tuple<int, double> ProcessParaBLL::getUnitReagentMl(const int processId, const QString& reagentName)
{
    QMap<QString, std::tuple<int, double>> reagentNameVolMap = getUnitReagentMl(processId);
    return reagentNameVolMap[reagentName];
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

