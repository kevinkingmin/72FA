#ifndef VALVE_H
#define VALVE_H
#include"Component.h"

class Valve:public Component
{
public:    
    explicit Valve(ValveAddress address,QObject *parent=nullptr);
    virtual~Valve();
public:
    int valveControl(const bool enable);
    ValveAddress getAddress() const;

private:
    ValveAddress _address;
};

#endif // VALVE_H
