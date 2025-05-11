#ifndef LIGHT_H
#define LIGHT_H
#include"Component.h"

class Light:public Component
{
public:    
    explicit Light(LightAddress address,QObject *parent=nullptr);
    virtual ~Light();
public:
    int lightControl(uchar state);
    LightAddress address() const;

private:
    LightAddress _address;
};

#endif // LIGHT_H
