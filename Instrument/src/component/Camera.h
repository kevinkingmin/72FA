#ifndef CAMERA_H
#define CAMERA_H
#include"Component.h"
class Command;
class Camera:public Component
{
public:
    typedef enum
    {
        STATE_OFF=0x00,
        STATE_ON=0x01,
    }State;
    explicit Camera(QObject *parent=nullptr);
    virtual ~Camera();
    int calibrateCamera();
    int takePhotograph(const uchar pos);

};

#endif // CAMERA_H
