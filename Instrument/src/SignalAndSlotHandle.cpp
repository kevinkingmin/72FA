#include "SignalAndSlotHandle.h"
#include "local_log.h"
#include "../Include/Comm/singleton.h"
#include "src/component/Components.h"
#include "src/component/Temperature.h"
#include "../Include/Model/sample/SampleModel.h"
#include "../Include/BLL/sample/SampleBLL.h"


SignalAndSlotHandle::SignalAndSlotHandle(QObject *parenent) :QObject(parenent)
, _Components(Components::instance())
{
}

SignalAndSlotHandle::~SignalAndSlotHandle()
{
}

SignalAndSlotHandle *SignalAndSlotHandle::instance()
{
	return Singleton<SignalAndSlotHandle>::instance();
}

void SignalAndSlotHandle::slotCloseProcessFinish(bool isSuccess)
{
	emit sglCloseProcessComplete(isSuccess);
}
