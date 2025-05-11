#ifndef SENSOR_H
#define SENSOR_H
#include"Component.h"

class Sensor:public Component
{
public:    
    explicit Sensor(QObject *parent=nullptr);
    virtual ~Sensor();
public:
    int inquireSensor();

    void setSensorData(const ushort data);
    Flag getSensorFlag(const SensorAddress address);
    ushort getSensorData() const;

private:
    ushort _sensorData;
};

#endif // LIQUIDWAY_H
