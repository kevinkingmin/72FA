#include "MainController.h"
#include <QTime>
#include "src/cmd/Command.h"
#include "src/local_log.h"

MainController::MainController(QObject *parent):Component(parent)
  ,_hardware_version(0)
  ,_software_version(0)
  ,_machine_no("")
  ,_MCB_Version("")
{
}

MainController::~MainController()
{
}


int MainController::synchronizeLowerMachine()
{
    Command cmd;
    if(cmd.generateSynchronizedActionCommand()<0)
        return(-1);
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
        return -2;
    return waitMachineAnswer();
}


int MainController::inquire_main_controller_version()
{
    Command cmd;
    if(cmd.generate_inquire_maincontrol_version_command()<0)
        return(-1);
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
        return -2;
    return waitMachineAnswer();
}


int MainController::inquire_machine_no()
{
    Command cmd;
    if(cmd.generate_inquire_machine_no_command()<0)
        return -1;
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
        return -2;
    return waitMachineAnswer();
}


int MainController::mainControlParameterReset()
{
    Command cmd;
    if(cmd.generateMainControlParameterResetActionCommand()<0)
        return -1;

    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        eLog("error happen");
        return -2;
    }
    return waitMachineAnswer(10000);
}

int MainController::writeMachineNoToMachine(const uint &machineNo)
{
    Command cmd;
    if(cmd.generateMachineNoWriteActionCommand(machineNo)<0)
        return -1;
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
        return -2;

    return waitMachineAnswer();
}

int MainController::systemValveControl(bool enable)
{
    ushort cmdData;
    if(enable)
        cmdData = 0xFFFF;
    else
        cmdData = 0x00;

    Command cmd;
    if(cmd.generateAllValveActionControl(cmdData)<0)
        return(-1);
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitMachineAnswer()<0)
        return -3;
    return 0;
}


void MainController::set_main_controller_version(int hardware_version,int software_version)
{
    setInquireResponseFlag(FLAG_IDLE);
    _hardware_version=hardware_version;
    _software_version=software_version;
}


void MainController::set_machine_no(QString machine_no)
{
    _machine_no=machine_no;
}

QString MainController::get_MCB_Version() const
{
    return _MCB_Version;
}

void MainController::set_MCB_Version(const QString &MCB_Version)
{
    _MCB_Version = MCB_Version;
}

