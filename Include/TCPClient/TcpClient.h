#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
#include <QTcpSocket>
#include "tcpclient_global.h"

class TCPCLIENTSHARED_EXPORT TcpClient : public QObject
{
	Q_OBJECT

public:
	explicit TcpClient(QObject *parent = nullptr);
	void setServerAddress(const QString &address, quint16 port);
	void sendData(const QString &data);
public:
	static TcpClient* getInstance() 
	{
		static TcpClient instance;
		return &instance;
	}

signals:
	void dataReceived(const QString &data);
	void connectStatus(bool status);

private slots:
	void onConnected();
	void onDisconnected();
	void onReadyRead();
public:
	void reconnect();
	void disconnectFromServer();
	private:
	QString GetCorrectUnicode(const QByteArray &data);
public:
	int m_connectedState = false;
private:
	QTcpSocket *tcpSocket;
	QString serverAddress;
	quint16 serverPort;
};

#endif // TCPCLIENT_H
