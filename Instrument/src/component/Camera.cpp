#include "Camera.h"
#include "src/cmd/Command.h"
#include "src/local_log.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include <QTime>

Camera::Camera(QObject *parent):Component(parent)
{
}

Camera::~Camera()
{
}


int Camera::calibrateCamera()
{
    Command cmd;
    if(cmd.generateCalibrateCameraCommand()<0)
        return -1;
    //QMutexLocker locker(&_controlLock);
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
        return -2;
    return waitCompoundCmdAnswer();
}

int Camera::takePhotograph(const uchar pos)
{
    Command cmd;
    if(cmd.generatePhotographCommand(pos)<0)
        return -1;
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
        return -2;
    return waitCompoundCmdAnswer();
}

