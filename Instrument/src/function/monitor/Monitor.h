#ifndef MONITOR_H
#define MONITOR_H
#include"../Function.h"
#include <QObject>
class Components;
class SignalAndSlotHandle;

class Monitor:public Function
{
	Q_OBJECT
public:
    Monitor();
    virtual ~Monitor();
    enum
    {
        MONITOR_INTERVAL=5000,
        THREAD_EXITING_TIMEOUT=30000,
    };
public:
    virtual int start();
    virtual void stop();
signals:
	void sglMonitor();
private:
    void monitor();
private:
    std::thread *_monitorThread;
    bool _stopping_flag;
    Components *_components;
	SignalAndSlotHandle *_SignalAndSlotHandle;
};

#endif // MONITOR_H
