#include "Timing.h"
#include <QTime>
#include "ActionModel.h"
#include "src/component/Components.h"
#include "src/component/Buzzle.h"
#include "src/component/Liquid.h"
#include "src/component/RockBed.h"
#include "src/component/Motor.h"
#include "src/component/Fan.h"
#include "src/component/Temperature.h"
#include "src/component/SampleArm.h"
#include "src/component/Valve.h"
#include "src/local_log.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/Model/baseSet/CommonType.h"
#include "../Include/Model/sample/SampleModel.h"
#include "../Include/Model/reagent/ReagentModel.h"
#include "../Include/BLL/reagent/ReagentBLL.h"
#include "../Include/BLL/reagent/ProcessReagentBLL.h"
#include "../Include/Model/reagent/ProcessReagentModel.h"
#include "../Include/Model/baseSet/InstrumentParasSetModel.h"
#include "../Include/BLL/baseSet/InstrumentParasSetBLL.h"
#include "../Include/Model/baseSet/ProcessParaModel.h"
#include "../Include/BLL/baseSet/ProcessParaBLL.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "../Include/BLL/comm/GetLanguageClsBLL.h"
#include <iostream>
#include <QDebug>

#define TIMING_REAGENT_COVER_MONITOR 0
#define PER_SLOT_COUNT 24
#define ACT_PAUSE_DES "动作重启或结束:{}"
//#define XUNWU

Timing::Timing() :Function()
  , _currentGroupId(0)
  , _groupMap{}
  , _companyId(0)
  , _actModel(ActionModel::instance())
  , _stepIndex(0)
  , _needFillPump{}
  , _processId{0}
  , _pauseTime{0}
{
}

Timing::~Timing()
{
}



void Timing::resetVariable()
{
	_isThreadStop = false;
    QMap<int, QString>groupMap{};
	_groupMap.swap(groupMap);
    _companyId=0;
    ActionModel::instance()->resetField();
    _pauseTime=0;
}

bool Timing::groupMapIsChanged(const QMap<int, QString> &groupMap)
{
    if(_groupMap.count()!=groupMap.count())
        return false;

    auto gKeys=_groupMap.keys();
    auto tKeys=groupMap.keys();
    for(auto k:gKeys)
    {
        if(!tKeys.contains(k))
            return false;
    }
    return true;
}

/*int Timing::popWindow(const QSharedPointer<ProcessParaModel> pm)
{
    if(pm->getIsPopWindow())
    {
        bool isPaused{false};
        //_components->setIsPause(true);
        emit sglPopWindow(pm->getPopWindowDes());
        auto ret{actPauseOrRestartOrStop(eUnknownId,isPaused)};
        if(ret!=0)
        {
            iLog(ACT_PAUSE_DES,ret);
            return ret;
        }
    }
    return 0;
}*/

QString Timing::language(const QString id)
{
    return GetLanguageClsBLL::getlangValue(id);
}

void Timing::setNeedFillPump(const QMap<int, ushort> &needFillPump)
{
    _needFillPump = needFillPump;

    QString logStr("");
    for(auto it=_needFillPump.begin();it!=_needFillPump.end();it++)
        logStr+="  pumpNo:"+ QString::number(it.key())+"  volumn:"+QString::number(it.value());

    dLog(logStr.toStdString());
}

const QMap<int, QString> &Timing::getGroupMap()
{
    QMutexLocker locker(&_lock);
    return _groupMap;
}

void Timing::setGroupMap(QMap<int, QString> &groupMap, const int companyId)
{
    QMutexLocker locker(&_lock);
    auto keys=groupMap.keys();
    dLog("reId:{},currentId:{}",keys.first(),_currentGroupId);
    if (keys.isEmpty() || _currentGroupId != keys.first())
    {
        dLog("restart test");
        //_components->setIsRestart(true);
    }

    if(_companyId!=0 && companyId!=_companyId)
        eLog("_companyId:{},companyId:{}",_companyId,companyId);

    if(companyId<=0)
        eLog("companyId is error,companyId:{}",companyId);

    _companyId=companyId;
    _groupMap.swap(groupMap);
}

void Timing::setProcessReagentVect(QVector<ProcessReagentModel> processReagentVect)
{
    //_actModel->setProcessReagentVect(processReagentVect);
}


