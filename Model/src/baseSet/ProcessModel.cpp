#include "ProcessModel.h"

ProcessModel::ProcessModel():
     _id(0)
     ,_companyId(0)
     ,_processName("")
     ,_remark("")
{

}

int ProcessModel::getId() const
{
    return _id;
}

void ProcessModel::setId(int id)
{
    _id = id;
}


int ProcessModel::getCompanyId() const
{
    return _companyId;
}

void ProcessModel::setCompanyId(int companyId)
{
    _companyId = companyId;
}

QString ProcessModel::getProcessName() const
{
    return _processName;
}

void ProcessModel::setProcessName(const QString &processName)
{
    _processName = processName;
}

QString ProcessModel::getRemark() const
{
    return _remark;
}

void ProcessModel::setRemark(const QString &remark)
{
    _remark = remark;
}

