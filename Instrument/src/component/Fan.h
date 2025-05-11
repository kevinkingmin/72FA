#ifndef FAN_H
#define FAN_H
#include"Component.h"

class Fan:public Component
{
public:
    Fan(QObject *parent=nullptr);
    virtual ~Fan();
public:
    int fanWork(const uchar runType,const uchar pos);
};

#endif // FAN_H
