#include "Sensor.h"
#include "ObjectInfo.h"
#include <QTime>
#include <QtMath>
#include "src/cmd/Command.h"
#include "src/local_log.h"

Sensor::Sensor(QObject *parent):Component(parent)
  ,_sensorData(0)
{
}

Sensor::~Sensor()
{
}


int Sensor::inquireSensor()
{
    Command cmd;
    if(cmd.generateInquireSensorsCommand())
        return -1;
    setInquireResponseFlag(FLAG_BUSY);
    if (cmd.send() < 0)
        return -2;
    if(waitMachineAnswer()<0)
        return -3;
    return 0;
}

void Sensor::setSensorData(const ushort data)
{
    QMutexLocker locker(&_dataLock);
    _sensorData=data;
}

Component::Flag Sensor::getSensorFlag(const SensorAddress address)
{
    QMutexLocker locker(&_dataLock);
    if(getInquireResponseFlag()!= FLAG_IDLE)
        return FLAG_UNKNOWN;

    if(_sensorData & int(qPow(2, address)))
        return FLAG_USED;
    else
        return FLAG_EMPTY;
}

ushort Sensor::getSensorData() const
{
    QMutexLocker locker(&_dataLock);
    return _sensorData;
}
