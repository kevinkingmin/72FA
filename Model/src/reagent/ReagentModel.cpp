#include "ReagentModel.h"

ReagentModel::ReagentModel():
    _ID(0)
  ,_reagentName("")
  ,_paperId(0)
  ,_companyID(0)
  ,_IsNoDrip(false)
  ,_IsSkimp(false)
  ,_IsNeedPrepare(false)
  ,_spentTime("")
  ,_fluidMeasure(0)
  ,_fluidMeasureSmall(0)
  ,_PumpNo(-1)
{}

int ReagentModel::getID() const
{
    return _ID;
}

void ReagentModel::setID(int ID)
{
    _ID = ID;
}

QString ReagentModel::getReagentName() const
{
    return _reagentName;
}

void ReagentModel::setReagentName(const QString &reagentName)
{
    _reagentName = reagentName;
}

int ReagentModel::getPaperId() const
{
	return _paperId;
}

void ReagentModel::setPaperId(int val)
{
	_paperId = val;
}

int ReagentModel::getCompanyID() const
{
    return _companyID;
}

void ReagentModel::setCompanyID(int companyID)
{
    _companyID = companyID;
}

bool ReagentModel::getIsNoDrip() const
{
    return _IsNoDrip;
}

void ReagentModel::setIsNoDrip(bool IsNoDrip)
{
    _IsNoDrip = IsNoDrip;
}

bool ReagentModel::getIsSkimp() const
{
    return _IsSkimp;
}

void ReagentModel::setIsSkimp(bool IsSkimp)
{
    _IsSkimp = IsSkimp;
}

bool ReagentModel::getIsNeedPrepare() const
{
    return _IsNeedPrepare;
}

void ReagentModel::setIsNeedPrepare(bool IsNeedPrepare)
{
    _IsNeedPrepare = IsNeedPrepare;
}

int ReagentModel::getPumpNo() const
{
    return _PumpNo;
}

void ReagentModel::setPumpNo(int PumpNo)
{
    _PumpNo = PumpNo;
}
QString ReagentModel::getSpentTime() const
{
	return _spentTime;
}
void ReagentModel::setSpentTime(const QString &spentTime)
{
	_spentTime = spentTime;
}

float ReagentModel::getFluidMeasure() const
{
	return _fluidMeasure;
}
void ReagentModel::setFluidMeasure(float fluidMeasure)
{
	_fluidMeasure = fluidMeasure;
}

float ReagentModel::getFluidMeasureSmall() const
{
	return _fluidMeasureSmall;
}
void ReagentModel::setFluidMeasureSmall(float fluidMeasureSmall)
{
	_fluidMeasureSmall = fluidMeasureSmall;
}