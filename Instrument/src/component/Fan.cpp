#include "Fan.h"
#include "ObjectInfo.h"
#include <QTime>
#include "src/cmd/Command.h"
#include "src/local_log.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

Fan::Fan(QObject *parent)
    :Component(parent)
{    
}

Fan::~Fan()
{
}

int Fan::fanWork(const uchar runType, const uchar pos)
{
    Command cmd;
    if(cmd.generateFanControlCommand(runType,pos)<0)
    {
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError && runType>0)
    {
        eLog("program stop");
        return -1;
    }
    if(cmd.send()<0)
    {
        return -2;
    }
    return waitCompoundCmdAnswer();
}

