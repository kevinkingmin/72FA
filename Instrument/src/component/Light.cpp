#include "Light.h"
#include "ObjectInfo.h"
#include <QTime>
#include "src/cmd/Command.h"
#include "src/local_log.h"

Light::Light(LightAddress address, QObject *parent)
    :Component(parent)
  ,_address(address)
{    
}

Light::~Light()
{
}


int Light::lightControl(uchar state)
{
    Command cmd;
    if(cmd.generateIndicatorLightOnOffCommand(_address,state)<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    return waitMachineAnswer();
}

Light::LightAddress Light::address() const
{
    return _address;
}
