#ifndef PROCESSPARABLL_H
#define PROCESSPARABLL_H
#include <QSharedPointer>
#include <QVector>
#include <QSet>
#include "../bll.h"
#include "../Include/Model/baseSet/ProcessParameterModel.h"
#include "../Include/DAO/baseSet/ProcessParameterDao.h"

class ProcessParameterDao;

class BLLSHARED_EXPORT ProcessParaBLL
{
public:
    using ptrModel=QSharedPointer<ProcessParameterModel>;
    ProcessParaBLL();
    QVector<ptrModel>getAllRows(int processId);
    QMap<int, int> getIncubationTime(QVector<int> pGroupIds);
    QVector<ProcessParaBLL::ptrModel> toPtrVector(const QVector<ProcessParameterModel>& models);
    // 获取各试剂总体积单位毫升 返回key:试剂名称 value:对应试剂量
    QMap<QString, std::tuple<int, double>> getUnitReagentMl(const int processId);
    // 获取指定试剂的总量
    std::tuple<int, double> getUnitReagentMl(const int processId, const QString& reagentName);
	
private:
    ProcessParameterDao *_dao;
};

#endif // PROCESSPARABLL_H
