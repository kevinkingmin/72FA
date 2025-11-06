#include "SystemSetModel.h"

SystemSetModel::SystemSetModel():
    _id(0)
  , _saveSet(-100)
  , _saveDes("")
  , _remark("")
{
}

uint SystemSetModel::getId() const
{
    return _id;
}

void SystemSetModel::setId(const uint &id)
{
    _id = id;
}

int SystemSetModel::getSaveSet() const
{
    return static_cast<int>(_saveSet);
}

double SystemSetModel::getSaveSetDou() const
{
    return _saveSet;
}

void SystemSetModel::setSaveSet(double saveSet)
{
    _saveSet = saveSet;
}

QString SystemSetModel::getSaveDes() const
{
    return _saveDes;
}

void SystemSetModel::setSaveDes(const QString &saveDes)
{
    _saveDes = saveDes;
}

QString SystemSetModel::getRemark() const
{
    return _remark;
}

void SystemSetModel::setRemark(const QString &remark)
{
    _remark = remark;
}
