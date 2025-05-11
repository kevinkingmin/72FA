#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QDebug>
#include <QThread>

class Instrument;

class Mythread : public QThread  //����̳���QObject
{
	Q_OBJECT
protected:
	void run() Q_DECL_OVERRIDE;  //�߳�����
public:
	explicit Mythread(QObject *parent = nullptr);
	//�����ǲۺ���
public:
	bool m_flag = false;
	void ChangeFlage(bool flage);
	Instrument * _instr;

private slots:
	void StartSend(bool flage);

};

#endif // MYTHREAD_H
