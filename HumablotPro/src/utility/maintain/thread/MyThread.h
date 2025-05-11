#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QDebug>
#include <QThread>

class Instrument;

class Mythread : public QThread  //必须继承与QObject
{
	Q_OBJECT
protected:
	void run() Q_DECL_OVERRIDE;  //线程任务
public:
	explicit Mythread(QObject *parent = nullptr);
	//必须是槽函数
public:
	bool m_flag = false;
	void ChangeFlage(bool flage);
	Instrument * _instr;

private slots:
	void StartSend(bool flage);

};

#endif // MYTHREAD_H
