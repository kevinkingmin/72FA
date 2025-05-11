#include "ActionModel.h"
#include "src/local_log.h"
#include "../Include/Model/sample/SampleModel.h"
#include "../Include/Model/sample/SampleTestModel.h"
#include "../Include/BLL/sample/SampleBLL.h"
#include "../Include/Model/reagent/ProcessReagentModel.h"
#include "../Include/Comm/singleton.h"
#include "../Include/Model/baseSet/ProcessParaModel.h"
#include "../Include/BLL/baseSet/ProcessParaBLL.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/BLL/reagent/ReagentBLL.h"
#include "../Include/Model/reagent/ReagentModel.h"

QMutex ActionModel::_lock;
ActionModel::ActionModel():
    _testParasMap{}
  ,_stepRunTime{}
  ,_stepName("")
  ,_reagentPumpNOVect{}
{
}

ActionModel *ActionModel::instance()
{
    return  Singleton<ActionModel>::instance();
}

uint ActionModel::calAddLiquidMotorStep(double liquidVolumeInReactionTube, uint currentReagentVolumn)
{
	double liquidHeightInReactionTube = 0.0;
	if (currentReagentVolumn > 50)
	{
		liquidHeightInReactionTube = (liquidVolumeInReactionTube + currentReagentVolumn - 20.0) / (3.1415926*9.0);
	}
	else
	{
		if (liquidVolumeInReactionTube > 20)
		{
			liquidHeightInReactionTube = (liquidVolumeInReactionTube - 20) / (3.1415926*9.0);
		}
	}
	double liquidPulseInReactionTube = liquidHeightInReactionTube * 157.48;
	uint motorDownSteps = 0;
	if (liquidPulseInReactionTube >= 0.0)
	{
		motorDownSteps = static_cast<uint>(liquidPulseInReactionTube);
	}
    return motorDownSteps;
}

int ActionModel::getPaperIdFun(int slotPos)
{
    auto it=_testParasMap.find(slotPos);
    if(it==_testParasMap.end())
    {
        eLog("No samples were found at the corresponding location");
        return -1;
    }
    return it.value().getPaperId();
}

int ActionModel::getPumpNoFun_(int processParaId, int paperId, int reagentId)
{
    auto vect = getProcessReagentVect();
    for(auto it:vect)
    {
        if(reagentId>0)
        {
            if(it.getReagentId()==reagentId)
                return it.getPumpNo();
        }
        else
        {
            if(it.getPaperId()==paperId && it.getProcessParaId()==processParaId)
                return it.getPumpNo();
        }
    }
    return -1;
}

int ActionModel::getPumpNoFun_new(int reagentId, int paperId, int companyId)
{
   auto reagent{ ReagentBLL().getReagent_new(reagentId,paperId,companyId)};
   if(reagent.isNull())
       return -1;
   return reagent->getPumpNo();
}

void ActionModel::updateModel()
{
}

void ActionModel::resetField()
{
    QMap<int,TestParasModel> testParasMap{};
    _testParasMap.swap(testParasMap);
    QMap<int,int>stepRunTime{};
    _stepRunTime.swap(stepRunTime);
    QVector<int>processGroupIds;
    _stepName="";
}

QVector<uchar> ActionModel::getReagentPumpNOVect() const
{
    return _reagentPumpNOVect;
}

void ActionModel::setReagentPumpNOVect(const QVector<uchar> &reagentPumpNOVect)
{
    _reagentPumpNOVect = reagentPumpNOVect;
}

QVector<ProcessReagentModel> ActionModel::getProcessReagentVect() const
{
    return _processReagentVect;
}

void ActionModel::setProcessReagentVect(QVector<ProcessReagentModel> processReagentVect)
{
    _processReagentVect.swap(processReagentVect);
}

void ActionModel::setTestParasMap(const QVector<ptrTest> &tests)
{
    QMap<int,TestParasModel> tMap;
    for(auto test:tests)
    {
		if (test->getSamplePos() <= 0 || test->getSlotPos() <= 0)
		{
            eLog("not set sample pos and paper pos:testId:{},samplePos:{},slotPos:{}"
				,test->getTestId().toStdString(),test->getSamplePos(),test->getSlotPos());
			continue;
		}
		/*
        auto sm=SampleBLL().getRowById(test->getSampleId());
        if(sm.isNull() || sm->getSamplePos()<=0 || test->getSlotPos()<=0)
        {
            tMap.clear();
            eLog("");
            break;
        }
		*/
        TestParasModel p;
        p.setTestId(test->getId());
        p.setSampleId(test->getSampleId());
        p.setPaperId(test->getPaperId());
        p.setCupType(test->getCupType());
        p.setSamplePos(test->getSamplePos());
        p.setSlotPos(test->getSlotPos());
        tMap.insert(p.getSlotPos(),p);
    }
    _testParasMap.swap(tMap);
}

QMap<int, TestParasModel> ActionModel::getTestParasMap() const
{
    return _testParasMap;
}

QString ActionModel::getStepName() const
{
    return _stepName;
}

void ActionModel::setStepName(const QString &value)
{
    _stepName = value;
}

const QMap<int, int> &ActionModel::getStepRunTime()
{
    return _stepRunTime;
}



