#ifndef PROCESSPARABLL_H
#define PROCESSPARABLL_H
#include <QSharedPointer>
#include <QVector>
#include "../bll.h"
#include "../include/Model/baseSet/ProcessParaModel.h"

class ProcessParaDao;

class BLLSHARED_EXPORT ProcessParaBLL
{
public:
    using ptrModel=QSharedPointer<ProcessParaModel>;
    using ParaStrt=ProcessParaModel::ParaStrt;
    ProcessParaBLL();
    QVector<ptrModel>getAllRows();
    ptrModel getRowById(int id);
    QVector<ptrModel> getRowByActId(int companyId,int actId);
    QVector<ptrModel> getModels(int groupId,int companyId);
    QMap<int,int> getReagentIdAndParaIds(QVector<int> pGroupIds,int companyId);
	QMap<int, int> getIncubationTime(QVector<int> pGroupIds);
	
private:
    ProcessParaDao *_dao;
};

#endif // PROCESSPARABLL_H
