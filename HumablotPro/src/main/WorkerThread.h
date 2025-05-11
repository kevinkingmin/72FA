#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QObject>
#include "../Include/TCPClient/TCPClient.h"


class WorkerThread : public QThread {
	Q_OBJECT
public:
	explicit WorkerThread(TcpClient *tcpClient, QObject *parent = nullptr);
	void run() override;
signals:
	void sendDataToServer(QString str);
private:
	TcpClient *m_tcpClient;
};

#endif // WORKERTHREAD_H
