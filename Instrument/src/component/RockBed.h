#ifndef ROCKBED_H
#define ROCKBED_H
#include"Component.h"

class RockBed:public Component
{
public:
    typedef enum
    {
        BedStop=0,
        BedLSpeed=1,
        BedMSpeed=2,
        BedHSpeed=3
    }BedWorkType;

    struct SpeedStruct
    {
        ushort lSpeed;
        ushort mSpeed;
        ushort hSpeed;
        SpeedStruct()
            :lSpeed(0)
            ,mSpeed(0)
            ,hSpeed(0)
        {}
    };

    RockBed(QObject *parent=nullptr);
    virtual ~RockBed();
public:
    int rockBedWorking(uchar speed);
    int writeSpeedToBed(const SpeedStruct &para);
    int writeCameraPosToBed(const int pos);
    int writeDryPaperPosToBed(const int pos);
    int inquireBedSpeed();
    int inquireBedPos();

    SpeedStruct getSpeedPara() const;
    void setSpeedPara(const SpeedStruct &speedPara);

    int getCameraPos() const;
    void setCameraPos(const int cameraPos);


private:
    SpeedStruct _speedPara;
    int _cameraPos;
};

#endif // ROCKBED_H
