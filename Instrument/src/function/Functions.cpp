#include "Functions.h"
#include "maintain/MaintainSystem.h"
#include "monitor/Monitor.h"
#include "timing/Timing.h"
#include "../Include/Comm/singleton.h"

Functions::Functions()
    :_monitor(new Monitor)
    ,_maintain(new MaintainSystem)
{
}

Functions::~Functions()
{
    delete _monitor;
    delete _maintain;
}

Functions *Functions::instance()
{
    return  Singleton<Functions>::instance();
}


Monitor *Functions::get_monitor()
{
    return dynamic_cast<Monitor*>(_monitor);
}

MaintainSystem *Functions::getMaintain()
{
    return dynamic_cast<MaintainSystem*>(_maintain);
}

Timing *Functions::getTimimg()
{
    return dynamic_cast<Timing *>(_timing);
}
