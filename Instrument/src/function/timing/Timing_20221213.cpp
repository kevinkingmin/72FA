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
#include "../Include/BLL/baseSet/ProcessParaBLL.h"
#include "../Include/Model/baseSet/ProcessParaModel.h"


#define TIMING_REAGENT_COVER_MONITOR 0
#define PER_SLOT_COUNT 24
#define ACT_PAUSE_DES "动作重启或结束:{}"

Timing::Timing() :Function()
  , _components(Components::instance())
  , _currentGroupId(0)
  ,_groupMap{}
  ,_actModel(ActionModel::instance())
  ,_stepIndex(0)
  ,_needFillPump{}
{
}

Timing::~Timing()
{
}

void Timing::addSeqDiagramToMap(QVector<ptrTest> sampleTests, QMap<int, QString>&groupMap)
{
    if(sampleTests.isEmpty())
        return;
    resetVariable();
    _actModel->setTestParasMap(sampleTests);
	setGroupMap(groupMap);
	start();
}

void Timing::resetVariable()
{
	_isThreadStop = false;
	QMap<int, QString>groupMap;
	_groupMap.swap(groupMap);
    ActionModel::instance()->resetField();
}

int Timing::start()
{
    if(_groupMap.isEmpty())
        return 0;
    stop();
    _thread = new std::thread([this]()
    {
NEXT:
        {
            InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumRuning);
            _actModel->setIsRestart(false);//在此设置重启标识，因为如果是重启则需要走这一步。
            QMutexLocker locker(&_lock);
            if(!_groupMap.isEmpty())
            {
                _currentGroupId=_groupMap.firstKey();
                emit sglCurrentGroupId(_currentGroupId,-1);
            }
            else
            {
                InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumStandby);
                return 0;
            }
        }
        QTime timer;
        int ret =0;
        while (true)
        {
            timer.start();
            if(_currentGroupId<=0)
                break;

            switch (_currentGroupId)
            {
            case 1:
            {
                ret = wettingGroup();
                break;
            }
            case 2:
            {
                ret = addSampleGroup();
                break;
            }
            case 3:
            {
                ret = washingGroup();
                break;
            }
            case 4:
            {
                ret = addReagentGroup();
                break;
            }
            case 5:
            {
                ret = washing_2_Group();
                break;
            }
            case 6:
            {
                ret = addSubStrateGroup();
                break;
            }
            case 7:
            {
                ret = addWaterGroup();
                break;
            }
            case 8:
            {
                ret = addStopLiquidGroup();
                break;
            }
            case 9:
            {
                ret = dryPaperGroup();
                break;
            }
            default:
            {
                assert(false);
                ret = -1;
                eLog("_currentGroupId:{}",_currentGroupId);
            }
            }

            if (_isThreadStop || ret < 0)
            {
                InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumError);
                eLog("程序被终止_terminationThread:{}", _isThreadStop);
                break;
            }

            if(_actModel->getIsRestart())
            {
                goto NEXT;
            }

            {
                QMutexLocker locker(&_lock);
                _groupMap.remove(_currentGroupId);

                if(!_groupMap.isEmpty())
                {
                    _currentGroupId=_groupMap.firstKey();
                    emit sglCurrentGroupId(_currentGroupId,timer.elapsed());
                }
                else
                {
                    InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumStandby);

                    _components->getBuzzle()->setBuzzleOnOff(Buzzle::STATE_ALARM1);
                    for(int i=0;i<5;i++)
                        QSLEEP(1000);
                    _components->getBuzzle()->setBuzzleOnOff(Buzzle::STATE_OFF);

                    break;
                }
            }
        }
        _components->getTemperature()->dstTemperatureControl(Temperature::TEMPERATURE_BED, false, 0);
        return 0;
	});
    return 0;
}

int Timing::wettingGroup()
{
    emit sglHandleStep(tr("润湿"));
    _subStepDesc=tr("--蠕动泵加液");
    int ret = drainageAndAddLiquid(1,1);
    if(ret != 0)
        return ret;
    _subStepDesc=tr("--摇床震荡孵育");
    ret = rockBedWork(1,2);
    return ret;
}

int Timing::addSampleGroup()
{
    emit sglHandleStep(tr("加样本"));
    _subStepDesc=tr("--排废液及蠕动泵加液");
    int ret=drainageAndAddLiquid(2,1);
    if(ret!=0)
        return ret;
    _subStepDesc=tr("--回流");
    ret=backFlow(2,2);
    if(ret!=0)
        return ret;
    _subStepDesc=tr("--样本臂移液");
    ret=sampleArmWork(2,3);
    if(ret!=0)
        return ret;
    _subStepDesc=tr("--摇床震荡孵育");
    ret=rockBedWork(2,4);
    return ret;
}

int Timing::washingGroup()
{
    emit sglHandleStep(tr("清洗"));
    _subStepDesc=tr("--第一次排废液及蠕动泵加液(共三次)");
    int ret = drainageAndAddLiquid(3,1);
    if(ret!=0)
        return ret;
    _subStepDesc=tr("--第一次摇床震荡孵育(共三次)");
    ret = rockBedWork(3,2);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--第二次排废液及蠕动泵加液(共三次)");
    ret = drainageAndAddLiquid(3,3);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--第二次摇床震荡孵育(共三次)");
    ret = rockBedWork(3,4);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--第三次排废液及蠕动泵加液(共三次)");
    ret = drainageAndAddLiquid(3,5);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--第三次摇床震荡孵育(共三次)");
    ret = rockBedWork(3,6);
    return ret;
}

int Timing::addReagentGroup()
{
    emit sglHandleStep(tr("加酶"));
    _subStepDesc=tr("--排废液及蠕动泵加液");
    int ret = drainageAndAddLiquid(4,1);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--回流");
    ret=backFlow(4,2);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--室温震荡孵育");
    ret = rockBedWork(4,3);
    return ret;
}

int Timing::washing_2_Group()
{
    emit sglHandleStep(tr("二次清洗"));
    _subStepDesc=tr("--第一次排废液及蠕动泵加液(共三次)");
    int ret = drainageAndAddLiquid(5,1);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--第一次摇床震荡孵育(共三次)");
    ret = rockBedWork(5,2);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--第二次排废液及蠕动泵加液(共三次)");
    ret = drainageAndAddLiquid(5,3);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--第二次摇床震荡孵育(共三次)");
    ret = rockBedWork(5,4);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--第三次排废液及蠕动泵加液(共三次)");
    ret = drainageAndAddLiquid(5,5);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--回流");
    ret=backFlow(5,6);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--第三次摇床震荡孵育(共三次)");
    ret = rockBedWork(5,7);
    if(ret!=0)
        return ret;

    return 0;
}

int Timing::addSubStrateGroup()
{
    emit sglHandleStep(tr("加底物"));
    _subStepDesc=tr("--排废液及蠕动泵加液");
    int ret = drainageAndAddLiquid(6,1);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--回流");
    ret=backFlow(6,2);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--摇床震荡孵育");
    ret = rockBedWork(6,3);
    return ret;
}

int Timing::addWaterGroup()
{
    emit sglHandleStep(tr("加蒸馏水"));
    _subStepDesc=tr("--排废液及加入蒸馏水");
    int ret = drainageAndAddLiquid(7,1);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--摇床震荡孵育");
    ret = rockBedWork(7,2);
    return ret;
}

int Timing::addStopLiquidGroup()
{
    emit sglHandleStep(tr("加终止液"));
    _subStepDesc=tr("--排废液及加入中止液STOP");
    int ret = drainageAndAddLiquid(8,1);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--回流");
    ret=backFlow(8,2);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--摇床震荡孵育");
    ret = rockBedWork(8,3);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--排废液");
    ret = drainageAndAddLiquid(8,4);
    return ret;
}

int Timing::dryPaperGroup()
{
    emit sglHandleStep(tr("干燥"));
    _subStepDesc=tr("--摇床震荡及加热");
    int ret = dryPaper(9,1);
    if(ret!=0)
        return ret;

    _subStepDesc=tr("--摇床震荡及加热+风扇干燥");
    ret = dryPaper(9,2);
    return ret;
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

int Timing::bedMotorInitialize()
{
    auto bedMotor=_components->getMotorByAddress(Component::MOTOR_SHAKE_BED);
    if(bedMotor==nullptr)
        return -1;
    auto ret = bedMotor->motorInitialize();
    if(ret <0)
    {
        //assert(false);
        eLog("摇床电机初始化失败");
        return ret;
    }
    return 0;
}

int Timing::backFlow(int group, int index)
{
    auto liquid=_components->getLiquid();
    if(liquid==nullptr)
    {
        eLog("没有找到相关组件");
        return -1;
    }
    auto pm=ProcessParaBLL().getModel(group,index);
    if(pm.isNull())
    {
        eLog("没有配制相应参数，请先配制参数,");
        return -1;
    }

    int reagentId=0;
    ushort volumn=0;
    auto vect = pm->getParas();

    for(auto m:vect)
    {
        if(m.id==1)
            reagentId=static_cast<int>(m.paraValue);
        else if(m.id==2)
            volumn=static_cast<ushort>(m.paraValue);
    }
    QVector<uchar> pumpNoVect=getFlowBackPumps(reagentId);

    for(auto pumpNo:pumpNoVect)
    {
        auto ret=actPauseOrRestartOrStop(true);
        if(ret!=0)
        {
            iLog(ACT_PAUSE_DES,ret);
            return ret;
        }

        QString stepName{""};
        if(_groupMap.keys().contains(_currentGroupId))
        {
            stepName=_groupMap[_currentGroupId]+_subStepDesc+",泵号:"+QString::number(pumpNo);
            emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"开始:"+stepName);
        }

        ret=liquid->liquidBackFlow(pumpNo,volumn);
        if(ret<0)
        {
            eLog("回流操作失败,pumpNo:{},volume:{}",pumpNo,volumn);
            if(stepName.length()>0)
                emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName);
            return ret;
        }

        if(stepName.length()>0)
            emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"完成:"+stepName);
    }
    return 0;
}

int Timing::drainageAndAddLiquid(int group, int index)
{
    auto pBed=_components->getRockBed();
    if(pBed==nullptr || _actModel==nullptr)
    {
        assert(false);
        eLog("组件为null");
        return -1;
    }

    QMap<int,QVector<int>>posMap{{1,{}},{2,{}},{3,{}}};//初始化三个盘
    auto slotPosVect=_actModel->getTestParasMap().keys();//获取所有的盘号
    if(slotPosVect.isEmpty())
    {
        eLog("没有待测样本数据");
        return -2;
    }

    auto fun=[&posMap](int reactNO,int slotPos)
    {
        auto &vect=posMap[reactNO];
        vect.push_back(slotPos);
    };

    _stepIndex=index;
    for(auto slotPos:slotPosVect)//对应试剂盘位置
    {
        if(slotPos<=PER_SLOT_COUNT)
        {
            fun(1,slotPos);
        }
        else if(slotPos>PER_SLOT_COUNT && slotPos<=PER_SLOT_COUNT*2)
        {
            fun(2,slotPos-PER_SLOT_COUNT);
        }
        else if(slotPos>PER_SLOT_COUNT*2 && slotPos<=PER_SLOT_COUNT*3)
        {
            fun(3,slotPos-PER_SLOT_COUNT*2);
        }
    }

    auto pm=ProcessParaBLL().getModel(group,index);
    if(pm.isNull())
    {
        eLog("没有配制相应参数，请先配制参数,groupId:{},actIndex:{}",group,index);
        return -1;
    }
    int reagentId=0;
    int addVolumn=0;
    int wasteTime=0;
    auto vect=pm->getParas();
    for(auto it:vect)
    {
        if (it.id == 1)
            reagentId = static_cast<int>(it.paraValue);
        else if (it.id == 2)
            addVolumn = static_cast<int>(it.paraValue);
        else if (it.id == 3)
            wasteTime = static_cast<int>(it.paraValue * 1000);
        else
            assert(false);
    }

    int type=-1;
    if(addVolumn>0 && wasteTime>0)
        type=eAllAct;
    else if(addVolumn>0)
        type=eAdd;
    else if(wasteTime>0)
        type=eWaste;

    auto bedMotor=_components->getMotorByAddress(Component::MOTOR_SHAKE_BED);
    if(bedMotor==nullptr)
        return -1;
    auto ret = bedMotor->motorInitialize();
    if(ret <0)
    {
        //assert(false);
        eLog("摇床电机初始化失败");
        return ret;
    }
    dLog("name:{},pumpNo:{},volumn:{},time:{}",pm->getGroupName().toStdString(),reagentId,addVolumn,wasteTime);
    switch (type)
    {
    case eAdd:
    {
        ret = addLiquid(posMap,reagentId,pm->getId(),addVolumn);
        return ret;
    }
    case eWaste:
    {
        ret = dranLiquid(posMap,wasteTime);
        return ret;
    }
    case eAllAct:
    {
        ret = dranAndAdd(posMap,reagentId,pm->getId(),addVolumn,wasteTime);
        return ret;
    }
    default:
    {
        eLog("未知类型，type:{}",type);
        assert(false);
        return -1;
    }
    }
}

int Timing::dryPaper(int group, int index)
{
    auto temprate=_components->getTemperature();
    auto fan=_components->getFan();
    auto rockBed=_components->getRockBed();
    auto xMotor=_components->getMotorByAddress(Component::MOTOR_X_AXIS);

    if(temprate==nullptr || fan==nullptr || rockBed==nullptr || xMotor==nullptr)
    {
        eLog("当前对象为NULL");
        return -1;
    }
    auto pm=ProcessParaBLL().getModel(group,index);
    if(pm==nullptr)
    {
        eLog("获取参数失败,groupId:{},index:{}",group,index);
        return -1;
    }

    auto vect=pm->getParas();
    int waitTime=0;//ms
    int tIsOn=0;
    float tempValue=0;
    uchar speedType=0;
    uchar bedSpeed=2;
    DWORD fanTime=2000;
    bool xMotorIsNeedInit=false;

    for(auto it:vect)
    {
        if(it.id==1)
            waitTime=static_cast<int>(it.paraValue*1000);
        if(it.id==2)
            tIsOn=static_cast<int>(it.paraValue);
        else if(it.id==3)
            tempValue=static_cast<float>(it.paraValue);
        else if(it.id==4)
            speedType=static_cast<uchar>(it.paraValue);//fanV=0时表示风扇停止
        else if(it.id==5)
            bedSpeed=static_cast<uchar>(it.paraValue);
        else if(it.id==6)
            fanTime=static_cast<DWORD>(it.paraValue*1000);
        else if(it.id==7)
            xMotorIsNeedInit=static_cast<int>(it.paraValue)==0?false:true;
    }

    int ret=temprate->dstTemperatureControl(Temperature::TEMPERATURE_BED,tIsOn,tempValue);
    if(ret<0)
    {
        temprate->dstTemperatureControl(Temperature::TEMPERATURE_BED,false,0);
        eLog("控制温度失败,温度:{}",tempValue);
        return -1;
    }

    QString stepName{""};
    if(_groupMap.keys().contains(_currentGroupId))
    {
        stepName=_groupMap[_currentGroupId]+_subStepDesc;
        emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"开始:"+stepName);
    }

    ret=rockBed->rockBedWorking(bedSpeed);
    if(ret<0)
    {
        rockBed->rockBedWorking(0);
        eLog("摇床工作失败！");
        if(stepName.length()>0)
            emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName+",摇床工作失败！");

        return -1;
    }

    QVector<Component::ValveAddress>fanVect{Component::VALVE_FANA,
                Component::VALVE_FANB,
                Component::VALVE_FANC};//20221109加，打开后面的几个风扇

    for(auto fan:fanVect)
    {
        auto ret = _components->getValveByAddress(fan)->valveControl(true);
        if(ret<0)
        {
            eLog("open fan failed,fan:",fan);
            return -1;
        }
    }

    auto stopFun=[temprate,fan,rockBed](bool isPause)
    {
        if (!isPause)//不是暂停，是直接停止
            temprate->dstTemperatureControl(Temperature::TEMPERATURE_BED, false, 0);
        fan->fanWork(0,0);
        rockBed->rockBedWorking(0);
    };

    auto stopFan=[fanVect,this]()
    {
        for(auto fan:fanVect)
        {
            //20221109加，关闭后面的几个风扇
            auto ret = _components->getValveByAddress(fan)->valveControl(false);
            if(ret<0)
            {
                eLog("close fan failed,fan:",fan);
            }
        }
    };

    //获取所有的模条信息
    auto posVect=_actModel->getTestParasMap().keys();
    QTime time;
    time.start();
    bool isPause = false;
    while (waitTime>time.elapsed())
    {
        //风扇动作
        for(auto pos:posVect)
        {
            if(waitTime<=time.elapsed())
            {
                break;
            }
            if(pos<0 || pos > 72)
            {
                eLog("当前位置错误,pos:{}",pos);
                return -1;
            }

            while (_actModel->getIsPause())
            {
                if (!isPause)
                    stopFun(true);//不停止加热。
                isPause = true;
                QSLEEP(1000);
            }

            if (isPause)
            {
                ret = rockBed->rockBedWorking(bedSpeed);
                if (ret < 0)
                {
                    rockBed->rockBedWorking(0);
                    eLog("摇床工作失败！");
                    if(stepName.length()>0)
                        emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName+",摇床工作失败！");

                    stopFun(false);
                    stopFan();
                    return ret;
                }
                isPause = false;
            }

            ret=actPauseOrRestartOrStop(false);
            if(ret!=0)
            {
                iLog(ACT_PAUSE_DES,ret);
                stopFun(false);
                stopFan();
                return ret;
            }

            ret=fan->fanWork(speedType,static_cast<uchar>(pos));
            if(ret<0)
            {
                stopFun(false);
                stopFan();
                eLog("风扇工作失败,speed:{},pos:{}",speedType,pos);
                if(stepName.length()>0)
                    emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName+",风扇工作失败！");
                return ret;
            }
            QSLEEP(fanTime);
        }
        QSLEEP(200);
    }
    stopFun(false);
    if(stepName.length()>0)
        emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"完成:"+stepName);

    stopFan();

    if(!xMotorIsNeedInit)
        return 0;

    ret=xMotor->motorInitialize();
    return ret;
}

int Timing::rockBedWork(int group, int index)
{
    auto pm=ProcessParaBLL().getModel(group,index);
    if(pm==nullptr)
    {
        eLog("获取参数失败,groupId:{},index:{}",group,index);
        return -1;
    }

    auto bed = _components->getRockBed();
    auto xMotor=_components->getMotorByAddress(Component::MOTOR_X_AXIS);
    if(bed==nullptr || xMotor==nullptr)
    {
       return -1;
    }
    uchar speed=0;
    int waitTime=0;//ms
    auto vect = pm->getParas();
    for(auto it:vect)
    {
        if(it.id==1)
            speed = static_cast<uchar>(it.paraValue);
        else if(it.id==2)
            waitTime=static_cast<int>(it.paraValue*1000);
        else
            assert(false);
    }

    QString stepName{""};
    if(_groupMap.keys().contains(_currentGroupId))
    {
        stepName=_groupMap[_currentGroupId]+_subStepDesc;
        emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"开始:"+stepName);
    }

    auto ret = bed->rockBedWorking(speed);
    if(ret<0)
    {
        if(stepName.length()>0)
            emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName);

        return ret;
    }

    QTime timer;
    timer.start();
    bool isPause = false;
    int pauseTime=0;
    bool isInit=false;


    while (timer.elapsed()-pauseTime<waitTime)
    {
        while (_actModel->getIsPause())
        {
            if (!isPause)
            {
                bed->rockBedWorking(RockBed::BedStop);
                isPause = true;
            }
            pauseTime+=200;
            QSLEEP(200);
        }

        if (isPause)
        {
            ret = bed->rockBedWorking(speed);
            if (ret < 0)
            {
                if(stepName.length()>0)
                    emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName);

                return ret;
            }
            isPause = false;
        }

        ret=actPauseOrRestartOrStop(false);
        if(ret!=0)
        {
            iLog(ACT_PAUSE_DES,ret);
            auto r = bed->rockBedWorking(RockBed::BedStop);
            if (r < 0)
            {
                eLog("动作停止失败");
                if(stepName.length()>0)
                    emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName+",动作停止失败");
                return r;
            }

            if(stepName.length()>0)
                emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"完成:"+stepName);
            return ret;
        }

        if(!isInit)
        {
            ret=xMotor->motorInitialize();
            if(ret<0)
            {
                bed->rockBedWorking(RockBed::BedStop);
                eLog("x轴电机初始化失败");

                if(stepName.length()>0)
                    emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName+",x轴电机初始化失败");

                return ret;
            }
            isInit=true;
        }
        QSLEEP(200);
    }

    ret=bed->rockBedWorking(RockBed::BedStop);
    if(stepName.length()>0)
        emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"完成:"+stepName);
    return ret;
}

int Timing::sampleArmWork(int group, int index)
{
    auto enablePm=InstrumentParasSetBLL().getRowById(2);
    bool suckEnable=true;
    bool spitEnable=true;
    auto vect=enablePm.getParas();
    for(auto it:vect)
    {
        if(it.id==1)
            suckEnable=it.para>0;
        else if(it.id==2)
            spitEnable=it.para>0;
    }

    _actModel->setStepName(tr("样本臂移液"));
    auto sampleArm=_components->getSampleArm();
    auto map=_actModel->getTestParasMap();

    if(sampleArm==nullptr || map.isEmpty())
    {
        eLog("sampleArm为null或没有查到需要检测的项目！");
        return -1;
    }

    auto washSet=InstrumentParasSetBLL().getRowById(1);
    if(washSet.getId()<=0)
    {
        eLog("样本臂没有配制清洗时间,id:{}",1);
        return -1;
    }

    auto timeVect=InstrumentParasSetBLL().getRowById(1).getParas();
    ushort inner=0;
    ushort outer=0;
    ushort waste=0;
    for(auto m:timeVect)
    {
        if(m.id==1)
            inner=static_cast<ushort>(m.para);
        else if(m.id==2)
            outer=static_cast<ushort>(m.para);
        else if(m.id==3)
            waste=static_cast<ushort>(m.para);
    }

    auto pm=ProcessParaBLL().getModel(group,index);
    if(pm.isNull())
    {
        assert(false);
        eLog("没有配制相应参数，请先配制参数,groupId:{},actIndex:{}",group,index);
        return -1;
    }
    ushort volum=0;
    auto paras=pm->getParas();
    for(auto p:paras)
    {
        if(p.id==1)
            volum=static_cast<ushort>(p.paraValue>=0?p.paraValue:0);
    }

    QTime timer;
    timer.start();
    for(auto it:map)
    {
        auto cupType=static_cast<uchar>(it.getCupType());
        auto suckPos=static_cast<uchar>(it.getSamplePos());
        auto ret=actPauseOrRestartOrStop(true);
        if(ret!=0)
        {
            assert(false);
            iLog(ACT_PAUSE_DES,ret);
            return ret;
        }

        ret = sampleArm->suck(volum,suckEnable,cupType,suckPos);
        if(ret<0)
        {
            assert(false);
            eLog("样本臂吸样失败，testId:{},volum:{},cupType:{},suckPos:{}",
                 it.getTestId().toStdString(),volum,cupType,suckPos);
            return ret;
        }

        auto slotpos=static_cast<uchar>(it.getSlotPos());
        QString stepName{""};
        if(_groupMap.keys().contains(_currentGroupId))
        {
            stepName=_groupMap[_currentGroupId]+_subStepDesc+",位置:"+QString::number(slotpos);
            emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"开始:"+stepName);
        }

        ret = sampleArm->spit(volum,spitEnable,slotpos);
        if(ret<0)
        {
            assert(false);
            eLog("样本臂吐样失败，testId:{},volum:{},slotpos:{}",
                 it.getTestId().toStdString(),volum,slotpos);

            if(stepName.length()>0)
                emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName);

            return ret;
        }
        ret=sampleArm->wash(inner,outer,waste);
        if(ret<0)
        {
            assert(false);
            eLog("样本臂清洗失败，testId:{},inner:{},outer:{},waste{}",
                 it.getTestId().toStdString(),inner,outer,waste);

            if(stepName.length()>0)
                emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName);
            return ret;
        }

        if(stepName.length()>0)
            emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"完成:"+stepName+",吸样下降步数:"+QString::number(sampleArm->getSampleSuckPos())
                                     +",杯高度:"+QString::number(sampleArm->getCupHeightByCupType(cupType)));

    }
    return 0;
}

QVector<uchar> Timing::getFlowBackPumps(int reagentId)
{
    if(reagentId>=0)
    {
        auto pumpNo=static_cast<uchar>(_actModel->getPumpNoFun(0,0,reagentId)) ;
        return {pumpNo};
    }
    else
    {
        return _actModel->getReagentPumpNOVect();
    }
}

int Timing::actPauseOrRestartOrStop(bool isWaitPause)
{
    while (isWaitPause && _actModel->getIsPause())//暂停
        QSLEEP(300);

    if(_actModel->getIsRestart())
        return 1;

    if (InstrumentStateModel::instance()->getMachineState().state == InstrumentStateModel::enumError)
        return -1;

    return 0;
}

int Timing::dranAndAdd(QMap<int, QVector<int> > mapPos, int reagentId, int processParaId, int addVolum, int wasteTime)
{
    int ret=0;
    wasteTime=wasteTime>=0?wasteTime:0;
    ushort utime=static_cast<ushort>(wasteTime);
    auto liquid=_components->getLiquid();
    uchar reactNO=0;
    QMap<uchar,char> pumpPosMap;
    for(auto &vect:mapPos)//对每个盘进行遍历
    {
        reactNO++;
        if(vect.isEmpty())
            continue;

        int pumpNo=0;
        auto first=vect.first();
        auto last=vect.last();
        vect.push_back(last+1);//加样
        for(auto v:vect)
        {
            if(first!=v)//不是盘的首位置，则需要进行加样
            {
                auto slotPos=(reactNO-1)*PER_SLOT_COUNT+v-1;
                auto paperId=_actModel->getPaperIdFun(slotPos);
                pumpNo=_actModel->getPumpNoFun(processParaId,paperId,reagentId);

                if(reagentId<0)
                    pumpPosMap.insert(static_cast<uchar>(pumpNo),0);

                if(pumpNo<0)
                {
                    assert(false);
                    eLog("获取试剂类型失败，processParaId:{},paperId:{},reagentId:{}",processParaId,paperId,reagentId);
                    return -1;
                }

                auto pumps=_needFillPump.keys();
                if(pumps.contains(pumpNo))//表示这个泵没有冲灌
                {
                    emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"开始:冲灌,泵号:"+QString::number(pumpNo));
                    ret=liquid->pumpFlushIrrigation(static_cast<uchar>(pumpNo),_needFillPump[pumpNo]);
                    if(ret<0)
                    {
                        emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"失败:冲灌,泵号:"+QString::number(pumpNo));
                        return  -1;
                    }
                    _needFillPump.remove(pumpNo);
                    emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"完成:冲灌,泵号:"+QString::number(pumpNo));
                }
            }

            ret=actPauseOrRestartOrStop(true);
            if(ret!=0)
            {
                assert(false);
                iLog(ACT_PAUSE_DES,ret);
                return ret;
            }

            QString stepName{""};
            if(_groupMap.keys().contains(_currentGroupId))
            {
                stepName=_groupMap[_currentGroupId]+_subStepDesc+
                        ",反应盘:"+QString::number(reactNO)+",位置:"+QString::number(v);

                emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"开始:"+stepName);
            }

            auto volumn=static_cast<ushort>(addVolum>=0?addVolum:0);
            if(first==v)//只排不加
            {
                ret = liquid->discardWasteAndSpitByPump(reactNO,static_cast<uchar>(v),utime,0,0);
            }
            else if(last+1==v)//只加不排
            {
                ret = liquid->discardWasteAndSpitByPump(reactNO,
                                                     static_cast<uchar>(v),
                                                     0,
                                                     static_cast<uchar>(pumpNo),
                                                     volumn);
            }
            else //加排
            {
                ret = liquid->discardWasteAndSpitByPump(reactNO,
                                                        static_cast<uchar>(v),
                                                        utime,
                                                        static_cast<uchar>(pumpNo),
                                                        volumn);
            }

            if(ret<0)
            {
                assert(false);
                eLog("排废液及蠕动泵加液失败,reactPos:{},slotPos:{},utime:{},pumpNo:{},volumn:{}",
                     reactNO,v,utime,pumpNo,volumn);

                if(stepName.length()>0)
                    emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName);

                return ret;
            }

            if(stepName.length()>0)
                emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"完成:"+stepName);
        }
    }
    _actModel->setReagentPumpNOVect(pumpPosMap.keys().toVector());
    return ret;
}

int Timing::dranLiquid(QMap<int, QVector<int> > mapPos, int wasteTime)
{
    int ret=0;
    wasteTime=wasteTime>=0?wasteTime:0;
    ushort utime=static_cast<ushort>(wasteTime);

    auto liquid=_components->getLiquid();
    auto xMotor=_components->getMotorByAddress(Component::MOTOR_SHAKE_BED);
    if(liquid==nullptr || xMotor==nullptr)
    {
        assert(false);
        eLog("没有生成相关的实体");
        return -1;
    }

    uchar reactNO=0;
    for(auto &vect:mapPos)
    {
        reactNO++;
        if(vect.isEmpty())
            continue;

        for(auto v:vect)
        {
            ret=actPauseOrRestartOrStop(true);
            if(ret!=0)
            {
                assert(false);
                iLog(ACT_PAUSE_DES,ret);
                return ret;
            }
            QString stepName{""};
            if(_groupMap.keys().contains(_currentGroupId))
            {
                stepName=_groupMap[_currentGroupId]+_subStepDesc+
                        ",反应盘:"+QString::number(reactNO)+",位置:"+QString::number(v);

                emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"开始:"+stepName);
            }
            ret = liquid->discardWasteAndSpitByPump(reactNO,
                                                 static_cast<uchar>(v),
                                                 utime,
                                                 0,
                                                 0);
            if(ret<0)
            {
                assert(false);
                eLog("排废液失败,reactPos:{},slotPos:{},time:{}",reactNO,v,utime);
                if(stepName.length()>0)
                    emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName);
                return ret;
            }

            if(stepName.length()>0)
                emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"完成:"+stepName);
        }
    }

    ret=xMotor->motorInitialize();
    if(ret<0)
    {
        assert(false);
        eLog("x轴电机初始化失败");
        return ret;
    }

    return 0;
}

int Timing::addLiquid(QMap<int, QVector<int> > mapPos, int reagentId, int processParaId, int addVolum)
{
    int ret=0;
    auto liquid=_components->getLiquid();
    uchar reactNO=0;

    for(auto &vect:mapPos)//遍历每一个模条盘
    {
        reactNO++;
        if(vect.isEmpty())
            continue;

        int pumpNo=0;
        auto first=vect.first();
        auto last=vect.last();
        vect.push_back(last+1);//因为结构原因,机构移动到下一个位置时，才能给当前位置加样，所以需要虚增一个模条位
        for(auto v:vect)
        {
            if(first==v)//盘的第一个不加，必须移动到第二个位置才是给第一个加
                continue;
            auto slotPos=(reactNO-1)*PER_SLOT_COUNT+v-1;
            auto paperId=_actModel->getPaperIdFun(slotPos);
            pumpNo=_actModel->getPumpNoFun(processParaId,paperId,reagentId);
            if(pumpNo<0)
            {
                assert(false);
                eLog("获取试剂类型失败，processParaId:{},paperId:{}",processParaId,paperId);
                return -1;
            }

            auto pumps=_needFillPump.keys();
            if(pumps.contains(pumpNo))//表示这个泵没有冲灌
            {
                emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"开始:冲灌,泵号:"+QString::number(pumpNo));
                ret=liquid->pumpFlushIrrigation(static_cast<uchar>(pumpNo),_needFillPump[pumpNo]);
                if(ret<0)
                {
                    emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"失败:冲灌,泵号:"+QString::number(pumpNo));
                    return  -1;
                }
                _needFillPump.remove(pumpNo);
                emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"完成:冲灌,泵号:"+QString::number(pumpNo));
            }

            auto volumn=static_cast<ushort>(addVolum>=0?addVolum:0);
            ret=actPauseOrRestartOrStop(true);
            if(ret!=0)
            {
                assert(false);
                iLog(ACT_PAUSE_DES,ret);
                return ret;
            }

            QString stepName{""};
            if(_groupMap.keys().contains(_currentGroupId))
            {
                stepName=_groupMap[_currentGroupId]+_subStepDesc+
                        ",反应盘:"+QString::number(reactNO)+",位置:"+QString::number(v);

                emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"开始:"+stepName);
            }

            ret = liquid->discardWasteAndSpitByPump(reactNO,
                                                 static_cast<uchar>(v),
                                                 0,
                                                 static_cast<uchar>(pumpNo),
                                                 volumn);
            if(ret<0)
            {
                assert(false);
                eLog("排废液失败,reactPos:{},slotPos:{},reagentType:{},volumn:{}"
                     ,reactNO,v,pumpNo,volumn);

                if(stepName.length()>0)
                    emit sglHandleStepDetail(_currentGroupId,_stepIndex,false,"失败:"+stepName);
                return ret;
            }

            if(stepName.length()>0)
                emit sglHandleStepDetail(_currentGroupId,_stepIndex,true,"完成:"+stepName);
        }
    }
    return ret;
}

void Timing::setNeedFillPump(const QMap<int, ushort> &needFillPump)
{
    _needFillPump = needFillPump;

    QString logStr("");
    for(auto it=_needFillPump.begin();it!=_needFillPump.end();it++)
        logStr+="  泵号:"+ QString::number(it.key())+"  体积:"+QString::number(it.value());

    dLog(logStr.toStdString());
}

const QMap<int, QString> &Timing::getGroupMap()
{
    QMutexLocker locker(&_lock);
    return _groupMap;
}

void Timing::setGroupMap(QMap<int, QString> &groupMap)
{
    QMutexLocker locker(&_lock);
    auto keys=groupMap.keys();
    if (keys.isEmpty() || _currentGroupId != keys.first())
        _actModel->setIsRestart(true);

    _groupMap.swap(groupMap);
}

void Timing::setProcessReagentVect(QVector<ProcessReagentModel> processReagentVect)
{
    _actModel->setProcessReagentVect(processReagentVect);
}


