#include "Buzzle.h"
#include "src/cmd/Command.h"
#include "src/local_log.h"
#include <QTime>

Buzzle::Buzzle(QObject *parent):Component(parent)
{
}

Buzzle::~Buzzle()
{
}


int Buzzle::setBuzzleOnOff(const Buzzle::State state)
{
    Command cmd;
    if(cmd.generateBuzzleOnOffCommand(static_cast<const unsigned char>(state))<0)
        return(-1);
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    return waitMachineAnswer();
}
