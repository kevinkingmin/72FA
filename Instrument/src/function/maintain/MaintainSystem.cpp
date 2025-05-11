#include "MaintainSystem.h"

#include "src/component/Components.h"
#include "src/component/Valve.h"
#include "src/component/MainController.h"
#include "src/component/Sensor.h"
#include "src/component/Motor.h"
#include "src/component/Scaner.h"
#include "src/component/Camera.h"
#include "src/component/SampleArm.h"
#include "src/component/Liquid.h"
#include "src/component/Light.h"
#include "src/component/Temperature.h"
#include "src/component/Buzzle.h"
#include "src/component/RockBed.h"
#include "src/cmd/Command.h"
#include "src/component/ObjectInfo.h"
#include "src/local_log.h"
#include "../Include/BLL/baseSet/InstrumentParasSetBLL.h"
#include "../Include/Model/baseSet/InstrumentParasSetModel.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "../Include/BLL/comm/GetLanguageClsBLL.h"
#include "../Include/SerialPortDriver/SerialPortDriver.h"
#include "../Instrument/src/Instrument.h"
#include <QTime>


MaintainSystem::MaintainSystem()
    :Function()
    , _components(Components::instance())
    , _mainType(eUnknown)
    , _pumpVect{}
{
}

MaintainSystem::~MaintainSystem()
{
    stop();
}

void MaintainSystem::maintain(eMaintainType type)
{
    _mainType=type;
    start();
}

void MaintainSystem::scanSampleBatchNo(QVector<int> posVect)
{
    stop();
    _thread = new std::thread([this,posVect]()
    {
        for(auto pos:posVect)
        {
            if (_isThreadStop)
                return ;
            if(pos<0 || pos>72)
            {
                eLog("pos error,pos:{}",pos);
                continue;
            }
            auto scan{_components->getScaner()};
            int ret{scan->scanSampleBarcode(static_cast<uchar>(pos))};
            if(actionsValid(ret, "Sample rack scanning failed,pos:"+QString::number(pos)) < 0)
                continue;

            auto sampleNo{scan->getSampleBarcode()};
            emit sglSampleBatchNo(pos,sampleNo);
        }
    });
}

int MaintainSystem::start()
{
    //stop();

    int ret=0;
    auto fun=[this](const QString &strResult,int ret)
    {
        if(ret>=0)
            emit sglRunResult(strResult+GetLanguageClsBLL::getlangValue("K1259"));
        else
            emit sglRunResult(strResult+GetLanguageClsBLL::getlangValue("L1002"));
    };

    switch (_mainType)
    {
    case eStartUpCheck://开机自检
    {
        InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumIniting);
        ret=startUpProcess();
        fun(GetLanguageClsBLL::getlangValue("K1023"),ret);
        break;
    }
    case eSystemLiquidIrrigate://系统液灌注
    {
        InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumRuning);
        ret = systemLiquidIrrigate();
        if(ret==0)
            InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumStandby);
        fun(GetLanguageClsBLL::getlangValue("L1081"),ret);
        break;
    }
    case eSystemLiquidWash:
    {
        InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumRuning);
        ret = systemLiquidWash();
        if(ret==0)
            InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumStandby);
        fun(GetLanguageClsBLL::getlangValue("L1082"),ret);
        break;
    }
    case ePrepareReagent:
    {
        InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumRuning);
        ret = prepareReagent();
        if(ret == 0)
            InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumStandby);
        fun(GetLanguageClsBLL::getlangValue("K1071"),ret);
        break;
    }
    case ePumpFill:
    {
        InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumRuning);
        ret = pumpFill();

        if(ret == 0)
            InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumStandby);
        break;
    }
    case eTubeSoak:
    {
        InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumRuning);
        ret = tubeSoak();
        if(ret == 0)
            InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumStandby);
        break;
    }
    case ePumpCalibrate:
    {
        InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumRuning);
        ret = pumpCalibrate();
        if(ret == 0)
            InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumStandby);
        break;
    }
    default:
    {
        assert(false);
        eLog("unknow type，type:{}",_mainType);
    }
    }
    return 0;
}

int MaintainSystem::init_instrument_environment()
{
    if (_isThreadStop)
        return -1;

    int err = _components->get_main_controller()->inquire_main_controller_version();
    if (actionsValid(err, "Failed to query the hardware and software version number of the main control board") < 0)
        return err;


    auto mchNo = _components->get_main_controller()->get_machine_no();
    auto hardwareVer = _components->get_main_controller()->get_hardware_version();
    auto softwareVer = _components->get_main_controller()->get_software_version();
    dLog("机器设备号:{};主控板硬件版本号:{};主控板软件版本号:{}", mchNo.toStdString(), hardwareVer, softwareVer);

    err = arouse_system();
    if (actionsValid(err, "Restoration of motor maintenance current failed") < 0)
        return err;

    return 0;
}


int MaintainSystem::inquire_main_controller_version()
{
    int err = _components->get_main_controller()->inquire_main_controller_version();
    if (actionsValid(err, "Failed to check the hardware and software versions of the main control board") < 0)
        return err;
    return 0;
}

void MaintainSystem::setReagentPosVolumnMap(const QMap<uchar, ushort> &reagentPosVolumnMap)
{
    _reagentPosVolumnMap = reagentPosVolumnMap;
}

int MaintainSystem::XYZAxisInit()
{
    int err =0;
    auto motor=_components->getMotorByAddress(Component::MOTOR_Z_AXIS);
    err = motor->motorInitialize();
    if (actionsValid(err, "Z-axis motor initialization failed") < 0)
        return err;
    motor=_components->getMotorByAddress(Component::MOTOR_Y_AXIS);
    err=motor->motorInitialize();
    if (actionsValid(err, "Y-axis motor initialization failed") < 0)
        return err;

    auto sampleArm{_components->getSampleArm()};
    err=sampleArm->inquireYMotorParas();
    if(actionsValid(err, "Failed to query Y-axis motor position")<0)
        return err;

    err=motor->motorMoveToAbsolutePos(false,true,sampleArm->getYMotorPara().needleWashPos);
    if(actionsValid(err, "Y-axis motor movement to cleaning position failed")<0)
        return err;

    motor=_components->getMotorByAddress(Component::MOTOR_X_AXIS);
    err=motor->motorInitialize();
    if (actionsValid(err, "X-axis motor initialization failed") < 0)
        return err;
    return err;
}
//开机自检
int MaintainSystem::startUpProcess()
{    
    //检测socket连通性
    Instrument::instance()->selfCheck();

    emit sglMaintainStep(1,GetLanguageClsBLL::getlangValue("L1041"));

    emit sglMaintainStep(2,GetLanguageClsBLL::getlangValue("L1044"));

    emit sglMaintainStep(3,GetLanguageClsBLL::getlangValue("L1047"));

    emit sglMaintainStep(4,GetLanguageClsBLL::getlangValue("L1050"));

    emit sglMaintainStep(5,GetLanguageClsBLL::getlangValue("L1052"));

    emit sglMaintainStep(6,GetLanguageClsBLL::getlangValue("L1054"));

    emit sglMaintainStep(7,GetLanguageClsBLL::getlangValue("L1056"));

    emit sglMaintainStep(8,GetLanguageClsBLL::getlangValue("L1058"));

    emit sglMaintainStep(9,GetLanguageClsBLL::getlangValue("L1060"));

    emit sglMaintainStep(10,GetLanguageClsBLL::getlangValue("L1062"));

    emit sglMaintainStep(11,"0");

    return 0;
}

int MaintainSystem::systemLiquidIrrigate()
{
    if (_isThreadStop)
        return -1;

    int err=XYZAxisInit();
    if(actionsValid(err, "XYZ motor initialization failed") < 0)
        return err;

    auto pm=SystemSetBLL().getRowById(20);
    ushort volumn=pm.isNull()?500:static_cast<ushort>(pm->getSaveSet());

    err = _components->getLiquid()->irrigationSystemLiquid(volumn);
    if (actionsValid(err, "System liquid flushing failure") < 0)
        return err;

    return 0;
}

int MaintainSystem::systemLiquidWash()
{
    if (_isThreadStop)
        return -1;

    int err=XYZAxisInit();
    if(actionsValid(err, "XYZ motor initialization failed") < 0)
        return err;

    auto pm=SystemSetBLL().getRowById(21);
    ushort volumn=pm.isNull()?500:static_cast<ushort>(pm->getSaveSet());

    err = _components->getLiquid()->washSystemLiquidWay(volumn);
    if (actionsValid(err, "System fluid cleaning failed") < 0)
        return err;

    return 0;
}

int MaintainSystem::prepareReagent()
{
    if (_isThreadStop)
        return -1;

    int err=XYZAxisInit();
    if(actionsValid(err, "XYZ motor initialization failed") < 0)
        return err;

    auto liquid=_components->getLiquid();
    for(auto it=_reagentPosVolumnMap.begin();it!=_reagentPosVolumnMap.end();it++)
    {
        err=liquid->pumpFlushIrrigation(it.key(),it.value());
        if(actionsValid(err, "Peristaltic pump filling failure") < 0)
            return err;
    }
    return 0;
}

int MaintainSystem::pumpFill()
{
    if (_isThreadStop)
    {
        sglMonthMaintain(-1);
        return -1;
    }

    int err=XYZAxisInit();
    if(actionsValid(err, "XYZ motor initialization failed") < 0)
    {
        sglMonthMaintain(err);
        return err;
    }

    auto liquid=_components->getLiquid();
    auto pm=SystemSetBLL().getRowById(22);
    auto v = pm.isNull()?300:pm->getSaveSet();
    for(auto pump:_pumpVect)
    {
        err=liquid->pumpFlushIrrigation(pump,static_cast<ushort>(v));
        if(actionsValid(err, "Peristaltic pump filling failure") < 0)
        {
            sglMonthMaintain(err);
            return err;
        }
    }
    sglMonthMaintain(0);
    return 0;
}

int MaintainSystem::tubeSoak()
{
    auto pm=SystemSetBLL().getRowById(24);
    int totalSecond=pm.isNull()?15*60*1000:pm->getSaveSet();
    int consumTime=0;
    while (totalSecond>consumTime)
    {
        QSLEEP(1000);
        consumTime+=1000;
    }
    sglMonthMaintain(0);
    return 0;
}

int MaintainSystem::pumpCalibrate()
{
    if (_isThreadStop)
    {
        sglMonthMaintain(-1);
        return -1;
    }

    int err=XYZAxisInit();
    if(actionsValid(err, "XYZ motor initialization failed") < 0)
    {
        sglMonthMaintain(err);
        return err;
    }
    auto liquid=_components->getLiquid();
    auto pm=SystemSetBLL().getRowById(25);
    auto v = pm.isNull()?100:pm->getSaveSet();
    for(auto pump:_pumpVect)
    {
        err=liquid->pumpCalibrate(pump,static_cast<ushort>(v));
        if(actionsValid(err, "Peristaltic pump calibration failed") < 0)
        {
            sglMonthMaintain(err);
            return err;
        }
        int fstSteps=0;
        int SndSteps=0;
        liquid->getCalibrateSteps(fstSteps,SndSteps);
        emit sglPumpCalibrateFinish(pump,fstSteps,SndSteps);
    }
    sglMonthMaintain(0);
    return 0;
}



void MaintainSystem::arouse_process()
{
    int err = arouse_system();
    if (actionsValid(err, "Maintain torque, brake release, temperature control failure") < 0)
        return;
   // InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumStandby);

}


int MaintainSystem::arouse_system()
{
    if (_isThreadStop)
        return -1;

    int err = all_motor_release_hold_moment(0);
    if (actionsValid(err, "Restoration of motor maintenance current failed") < 0)
        return err;

    err = up_down_motor_move_0_speed();
    if (actionsValid(err, "Motor failed to rotate at 0 speed") < 0)
        return err;


    err = closeAllValve();
    if (actionsValid(err, "Closing all valves operation failed!") < 0)
        return err;

    return 0;
}


int MaintainSystem::query_param()
{
    auto m = InstrumentParasSetBLL().getRowById(1);
    if (m.getId() <= 0 || m.getParas().isEmpty())
    {
        eLog("get reagent disc mix steps failed");
        return -99;
    }
    return 0;
}

int MaintainSystem::closeAllValve()
{
    //	int err = _components->get_Liquid_way()->systemValveControl(false);
    //	if (actionsValid(err, "Closing all valves operation failed!！") < 0)
    //		return err;
    return 0;
}


int MaintainSystem::initialze_mechanical_structure(const bool isCloseProcess)
{
    Q_UNUSED(isCloseProcess)
    if (_isThreadStop)
    {
        return -1;
    }
    int err = 0;
    if (actionsValid(err, "Lifting motor init failed") < 0)
        return err;
    return 0;
}


int MaintainSystem::initialze_liquid_way(bool isOpenProcess)
{
    unsigned char ch = 0;
    if (isOpenProcess)
        ch = 1;
    return 0;
}

int MaintainSystem::initialze_position()
{
    int err = 0;
    err = initialze_mechanical_structure();
    if (actionsValid(err, "Mechanical initialization failed!") < 0)
        return err;
    return 0;
}


int MaintainSystem::all_motor_release_hold_moment(const bool on_off_status)
{
    Q_UNUSED(on_off_status)
    //int err = 0;

    if (_isThreadStop)
        return -1;
    /*
    auto vect = MotorParameterBLL().getAllRows();
    Component::MotorAddress address;
    for (auto it : vect)
    {
//        if (it->getMotorAddress() == 40 || it->getMotorAddress() == 41 || it->getMotorAddress() == 43)
//            continue;
        QSLEEP(200);
        address = static_cast<Component::MotorAddress>(it->getMotorAddress() % 10 + it->getMotorAddress() / 10 * 16);
        //err = _components->get_component_with_motor_address(static_cast<unsigned short>(address))->motorRealseHoldMoment(address, on_off_status);
        if (actionsValid(err, it->getMotorName() + ",address:" + QString::number(address) + "，释放/保持力矩失败") < 0)
            return err;
    }
    */
    return 0;
}


int MaintainSystem::up_down_motor_move_0_speed()
{
    return 0;
}

int MaintainSystem::actionsValid(int err, QString errStr)
{
    if (err < 0)
    {
        eLog(errStr.toStdString());
        InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumError);
        return -2;
    }

    if (_isThreadStop)
    {
        eLog("program stop！！");
        InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumError);
        return -1;
    }
    return 0;
}

void MaintainSystem::setPumpVect(const QVector<uchar> &pumpVect)
{
    _pumpVect = pumpVect;
}




