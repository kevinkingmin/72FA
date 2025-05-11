#ifndef FUNCTION_H
#define FUNCTION_H
#include <QThread>
#include<QObject>
#include <QMutex>

#ifdef Q_OS_LINUX
#define SLEEPHEAD <unistd.h>
#define QSLEEP(ms) sleep(ms)
#endif

#ifdef Q_OS_WIN
#define SLEEPHEAD <qt_windows.h>
#define QSLEEP(ms) Sleep(ms)
#endif
#include SLEEPHEAD

class Function:public QObject
{
	Q_OBJECT
public:
    Function();
    virtual ~Function();
    Function(const Function &)=delete;
    Function &operator=(const Function &)=delete;
    static void setIsThreadStop(bool isThreadStop);
    virtual void stop();
protected:
    virtual int start()=0;
protected:
    std::thread *_thread;
    static bool _isThreadStop;
    static QMutex _lock;
};

#endif // FUNCTION_H
