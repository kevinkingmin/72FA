#ifndef SERIALPORTDRIVER_H
#define SERIALPORTDRIVER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QQueue>
#include <QMutex>
#include "serialportdriver_global.h"
#include <functional>
#include <QByteArray>

class QSerialPort;
class QThread;
class QByteArray;
class WritePort;
class QTimer;
class Timing;

template <class T>
class Singleton;
class SERIALPORTDRIVERSHARED_EXPORT SerialPortDriver:public QObject
{
    Q_OBJECT
private:
    SerialPortDriver(QObject *parent = nullptr);
    SerialPortDriver(SerialPortDriver &)=delete;
    SerialPortDriver(SerialPortDriver &&)=delete;
    SerialPortDriver &operator=(const SerialPortDriver&)=delete;
    SerialPortDriver &operator=(SerialPortDriver&&)=delete;    
    friend Singleton<SerialPortDriver>;
    friend Timing;
private:
    void enqueueData();
    QByteArray dequeueData();
private slots:
    void slotReadyData();  
    void slotReadyArrive();
    void slotReadyHandle();
signals:
    void sglWriteDataArrive();
public:
    ~SerialPortDriver();
    static SerialPortDriver *instance();
    void initPort(QString port="");  
    void initLog(const QString& path, int level);    
    QVector<QString> getPorts();
    bool isPortOpen();
    void writeData(QByteArray data);
    void setRecieveFun(const std::function<void (QByteArray &datas)> &recieveFun);
    void stop();
    bool open();
    std::function<void (QByteArray &datas)> getRecieveFun() const;

private:
    mutable QMutex _readLock;
    QThread *_thread;
    QSerialPort *_port;
    WritePort *_WritePort;
    std::function<void(QByteArray &datas)>_recieveFun;
    QQueue<QByteArray> _receiveDatas;
    /**
     * @brief _isReciveDataStart:表示接收数据的函数是否启动
     */
    bool _isReciveDataStart;

};

#endif // SERIALPORTDRIVER_H
