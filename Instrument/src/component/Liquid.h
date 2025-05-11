#ifndef LIQUID_H
#define LIQUID_H
#include <QMap>
#include"Component.h"
class Command;

class Liquid:public Component
{
    typedef enum
    {
           L_COMBINDA=00,
           L_COMBINDB=01,
           L_COMBINDC=02,
           L_COMBINDD=03,
           L_DILUENT=04,
           L_SUBSTRATE=05,
           L_STOPLIQUID=06,
           L_DISTILEWATER=07,
           L_WASHWATER=8,
           L_SYSTEMLIQUID=9,
    }ELiquidType;
public:
    explicit Liquid(QObject *parent=nullptr);
    ~Liquid();

public:
    int liquidBackFlow(const uchar flowType,const ushort flowVolumn,const bool isLightOn=false);
    int pumpCalibrate(const uchar pumpNo, const ushort volume,const bool isLightOn=false);
    int pumpFlushIrrigation(const uchar flushType,const ushort flushVolumn,const bool isLightOn=false);
    int discardWasteAndSpitByPump(const uchar reactNO,
                                  const uchar spitPos,
                                  const ushort discardWasteTime,
                                  const uchar spitType,
                                  const ushort spitVolumn,
                                  const bool isLightOn=false);

    int irrigationSystemLiquid(const ushort volumn,const bool isLightOn=false);
    int washSystemLiquidWay(const ushort volumn);

    int write50ulToStepsToMachine(const uchar pumpNo,int steps);

    int inquirePeristalticPumpStepsFrom50ul(const uchar pumpNo);

    void setCalibrateSteps(int fstSteps,int SndSteps);
    void getCalibrateSteps(int &fstSteps,int &SndSteps);

    int get50ulSteps() const;
    void set50ulSteps(int value);
private:
    int liquidLightControl(const uchar lType, const uchar state);
private:
    int _calibrateFstSteps;
    int _calibrateSndSteps;
    int _50ulSteps;
    static QMap<ELiquidType,LightAddress>_LTypeLightMap;
};

#endif // LIQUID_H
