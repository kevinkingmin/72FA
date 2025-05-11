#ifndef SIGNALANDSLOTHANDLE_H
#define SIGNALANDSLOTHANDLE_H
#include "instrument_global.h"
#include <QObject>
#include <QDateTime>

template <class T>
class Singleton;
class Components;
class TestResultModel;

class INSTRUMENTSHARED_EXPORT SignalAndSlotHandle:public QObject
{
    Q_OBJECT
private:
    SignalAndSlotHandle(QObject *parenent=nullptr);
    SignalAndSlotHandle(SignalAndSlotHandle &)=delete;
    SignalAndSlotHandle(SignalAndSlotHandle &&)=delete;
    SignalAndSlotHandle &operator=(const SignalAndSlotHandle&)=delete;
    SignalAndSlotHandle &operator=(SignalAndSlotHandle&&)=delete;
    friend Singleton<SignalAndSlotHandle>;
public:
    virtual ~SignalAndSlotHandle();
    static SignalAndSlotHandle*instance();

signals:
	void sglCloseProcessComplete(bool isSuccess);
public slots:
	void slotCloseProcessFinish(bool isSuccess);
private:
    Components *_Components;
};

#endif // SIGNALANDSLOTHANDLE_H
