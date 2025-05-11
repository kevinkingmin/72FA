#ifndef BUZZLE_H
#define BUZZLE_H
#include"Component.h"
class Command;
class Buzzle:public Component
{
public:
    typedef enum
    {
        STATE_OFF=0x00,
        STATE_ON=0x01,
        STATE_ALARM1=0x02,
        STATE_ALARM2=0x03
    }State;

    Buzzle(QObject *parent=nullptr);
    virtual ~Buzzle();
    int setBuzzleOnOff(const State state);
};

#endif // BUZZLE_H
