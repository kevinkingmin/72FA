#include "Valve.h"
#include "ObjectInfo.h"
#include <QTime>
#include "src/cmd/Command.h"
#include "src/local_log.h"

Valve::Valve(ValveAddress address, QObject *parent)
    :Component(parent)
  ,_address(address)
{    
}

Valve::~Valve()
{
}


int Valve::valveControl(const bool enable)
{
    Command cmd;
    uchar able=enable?1:0;
    if(cmd.generateSingleValveActionCommand(_address,able)<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitMachineAnswer()<0)
        return -3;
    return 0;
}

Valve::ValveAddress Valve::getAddress() const
{
    return _address;
}
