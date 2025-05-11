#include "ProcessReagentModel.h"

ProcessReagentModel::ProcessReagentModel()
    :_id(0)
    ,_processParaId(0)
    ,_paperId(0)
    ,_reagentId(0)
    ,_pumpNo(0)
	,_fluidMeasure(0)
{

}

int ProcessReagentModel::getId() const
{
    return _id;
}

void ProcessReagentModel::setId(int id)
{
    _id = id;
}

int ProcessReagentModel::getProcessParaId() const
{
    return _processParaId;
}

void ProcessReagentModel::setProcessParaId(int id)
{
    _processParaId = id;
}

int ProcessReagentModel::getPaperId() const
{
    return _paperId;
}

void ProcessReagentModel::setPaperId(int paperId)
{
    _paperId = paperId;
}

int ProcessReagentModel::getReagentId() const
{
    return _reagentId;
}

void ProcessReagentModel::setReagentId(int reagentId)
{
    _reagentId = reagentId;
}

int ProcessReagentModel::getPumpNo() const
{
    return _pumpNo;
}

void ProcessReagentModel::setPumpNo(int pumpNo)
{
    _pumpNo = pumpNo;
}

float ProcessReagentModel::getFluidMeasure() const
{
	return _fluidMeasure;
}
void ProcessReagentModel::setFluidMeasure(float fluidMeasure)
{
	_fluidMeasure = fluidMeasure;
}