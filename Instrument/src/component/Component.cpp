#include "Component.h"
#include <QTime>
#include "src/local_log.h"
#include "src/cmd/Command.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

QMutex Component::_controlLock;
QMutex Component::_dataLock;

Component::Component(QObject *parent):QObject (parent)
  ,_InquireResponseFlag(FLAG_IDLE)
  ,_moveResponseFlag(FLAG_IDLE)
  ,_comResponseFlag(FLAG_IDLE)
  ,_state(STATE_NORMAL)
  ,_instrState(InstrumentStateModel::instance())
{
    memset(_sensorFlag,FLAG_UNKNOWN,sizeof (_sensorFlag));
}

Component::~Component()
{
}

int Component::flush_answer()
{
    Command cmd;
    if(cmd.generateSynchronizedActionCommand()<0)
        return -1;

    if(cmd.send()<0)
        return -2;
    return 0;
}

int Component::waitMachineAnswer(const int timeout)
{
    QTime time;
    time.start();
    while(true)
    {
        if(FLAG_IDLE==getInquireResponseFlag())
            return(0);
        int timeElapsed = time.elapsed();
        if(_instrState->getMachineState().state==InstrumentStateModel::enumError)
        {
            eLog("error state");
            return -1;
        }

        if(timeElapsed>timeout)
        {
            eLog("overtime，set time:{},wait time:{}",timeout,timeElapsed);
            return -3;
        }
        Sleep(20);
    }
}

int Component::waitMoveComplete(const int timeout)
{
    QTime time;
    time.start();
    while(true)
    {
        if(FLAG_IDLE==getMoveResponseFlag())
        {
            return 0;
        }
        int timeElapsed = time.elapsed();
        if(_instrState->getMachineState().state==InstrumentStateModel::enumError)
        {
            eLog("error state");
            return -1;
        }
        if(timeElapsed>=static_cast<int>(timeout))
        {            
            eLog("overtime，set time:{},wait time:{}",timeout,timeElapsed);
            return -3;
        }
        Sleep(20);
    }
}

int Component::waitCompoundCmdAnswer(const int timeout)
{
    QTime time;
    time.start();
    while(true)
    {
        if(FLAG_IDLE==getComResponseFlag())
        {
            return 0;
        }

        int timeElapsed = time.elapsed();

        if(_instrState->getMachineState().state==InstrumentStateModel::enumError)
        {
            eLog("error state");
            return -1;
        }

        if(timeElapsed>=static_cast<int>(timeout))
        {
            eLog("overtime，set time:{},wait time:{}",timeout,timeElapsed);
            return -3;
        }
        Sleep(20);
    }
}

Component::Flag Component::getMoveResponseFlag() const
{
    QMutexLocker locker(&_dataLock);
    return _moveResponseFlag;
}

void Component::setMoveResponseFlag(const Component::Flag flag)
{
    QMutexLocker locker(&_dataLock);
    _moveResponseFlag = flag;
}

Component::Flag Component::getInquireResponseFlag() const
{
    QMutexLocker locker(&_dataLock);
    return _InquireResponseFlag;
}

void Component::setInquireResponseFlag(const Flag &v)
{
    QMutexLocker locker(&_dataLock);
    _InquireResponseFlag = v;
}

Component::Flag Component::getComResponseFlag() const
{
    QMutexLocker locker(&_dataLock);
    return _comResponseFlag;
}

void Component::setComResponseFlag(const Flag &comResponseFlag)
{
    QMutexLocker locker(&_dataLock);
    _comResponseFlag = comResponseFlag;
}

void Component::setState(const Component::State state)
{
    _state=state;
}

Component::State Component::getState() const
{
    return _state;
}
