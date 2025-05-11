#include "Function.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "timing/ActionModel.h"

bool Function::_isThreadStop = false;
QMutex Function::_lock;
Function::Function() :QObject()
, _thread(nullptr)
{
}

Function::~Function()
{
	if (_thread != nullptr)
	{
		_isThreadStop = true;
		if (_thread->joinable())
			_thread->join();
		delete _thread;
	}
}

void Function::setIsThreadStop(bool isThreadStop)
{
	_isThreadStop = isThreadStop;
}

void Function::stop()
{
    InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumError);
    QSLEEP(600);
	if (nullptr != _thread)
	{
		if (_thread->joinable())
			_thread->join();

		delete _thread;
		_thread = nullptr;
        //InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumError);
	}
    InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumStandby);
	_isThreadStop = false;
}
