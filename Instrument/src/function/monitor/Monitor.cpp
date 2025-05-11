#include "Monitor.h"
#include "src/component/Components.h"
#include "src/component/Valve.h"
#include "src/component/Temperature.h"
#include "src/SignalAndSlotHandle.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "src/local_log.h"
#include <QThread>

Monitor::Monitor():Function ()
  , _monitorThread(nullptr)
  ,_stopping_flag(false)
  ,_components(Components::instance())
	,_SignalAndSlotHandle(SignalAndSlotHandle::instance())
{
}

Monitor::~Monitor()
{
    if (_monitorThread != nullptr)
	{
        if (_monitorThread->joinable())
            _monitorThread->join();
        delete _monitorThread;
        _monitorThread = nullptr;
	}
}


int Monitor::start()
{
    stop();
    _monitorThread = new std::thread([this]()
    {
        monitor();
    });
    return 0;
}

void Monitor::stop()
{
    if(nullptr!= _monitorThread)
    {
        _stopping_flag=true;
        _monitorThread->join();
        delete _monitorThread;
        _monitorThread = nullptr;
    }
    _stopping_flag=false;
}

void Monitor::monitor()
{
    while(true)
    {
        if(_stopping_flag)
            return;
        auto state{InstrumentStateModel::instance()->getMachineState().state};
        if(state==InstrumentStateModel::enumUnConn
                ||state==InstrumentStateModel::enumConn
                ||state==InstrumentStateModel::enumUnInit
                //20240514
                //||state==InstrumentStateModel::enumStandby
                //||state==InstrumentStateModel::enumError
                )
        {
            Sleep(4000);
            continue;
        }

        if(_components->getTemperature()->inquireRealTimeTemperature()<0)
        {
            dLog("inquire temperature！！");
        }

        if(_stopping_flag)
            return;

		QSLEEP(MONITOR_INTERVAL);

        if(_stopping_flag)
            return;
		emit sglMonitor();
    }
}
