#ifndef SAMPLEARM_H
#define SAMPLEARM_H
#include"Component.h"

class SampleArm:public Component
{
public:
    struct NeedleBlockPara
    {
        ushort minValue;
        ushort maxValue;
        NeedleBlockPara()
            :minValue(0)
            ,maxValue(0)
        {}
    };

    enum CupType{
        eStandardCup=0,
        eBloodCup=1,
        eMicrCup=2,
    };

    struct XMotorPara
    {
        int cupSpace;
        int rackSSpace;
        int rackLSpace;
        int rackPos;
        int rectSlotSpace;
        int rectDiscSpace;
        int sNeedleSpitXPos;
        int suckLiquidPos;
        int photographPos;
        int scanerXPos;
        int scanerChangePos;
        int cameraCalibratePos;
        int liquidDetectCalibratePos;
        int scanerSelfCheckPos;
        int scanerXPos2nd;

        XMotorPara()
            :cupSpace(0)
            ,rackSSpace(0)
            ,rackLSpace(0)
            ,rackPos(0)
            ,rectSlotSpace(0)
            ,rectDiscSpace(0)
            ,sNeedleSpitXPos(0)
            ,suckLiquidPos(0)
            ,photographPos(0)
            ,scanerXPos(0)
            ,scanerChangePos(0)
            ,cameraCalibratePos(0)
            ,liquidDetectCalibratePos(0)
            ,scanerSelfCheckPos(0)
            ,scanerXPos2nd(0)
        {}
    };

    struct YMotorPara
    {
        int fstRackPos;
        int scdRackPos;
        int needleWashPos;
        int startDrawWastePos;
        int spitYPos;
        int startWasteSlotPos;
        YMotorPara()
            :fstRackPos(0)
            ,scdRackPos(0)
            ,needleWashPos(0)
            ,startDrawWastePos(0)
            ,spitYPos(0)
            ,startWasteSlotPos(0)
        {}
    };

    struct ZMotorPara
    {
        int washHeight;
        int standartCupHeight;
        int bloodingCupHeight;
        int microCupHeight;
        int startDetectLevelHeight;
        int spitHeight;
        int detectLevel2ndDescendHeight;
        int wasteSlotHeight;
        ZMotorPara()
            :washHeight(0)
            ,standartCupHeight(0)
            ,bloodingCupHeight(0)
            ,microCupHeight(0)
            ,startDetectLevelHeight(0)
            ,spitHeight(0)
            ,detectLevel2ndDescendHeight(0)
            ,wasteSlotHeight(0)
        {}
    };

    explicit SampleArm(QObject *parent=nullptr);
    virtual ~SampleArm();
public:
    int suck(const ushort volum,const bool sensorEnable,const uchar cupType,const uchar suckPos);
    int spit(const ushort volum,const bool sensorEnable,const uchar spitPos);
    int suckAndSpit(const ushort volum,const uchar sensorEnable,const uchar cupType,const uchar suckPos,const uchar spitPos);
    int wash(const ushort innerTime,const ushort outerTime,const ushort wasteTime);

    int inquireSamplePlungerPumpStepsFrom1uL();

    int inquireSampleNeedleAirColumnValue();

    int inquireBlockNeedleRValue();

    int inquireXMotorParas();

    int inquireYMotorParas();

    int inquireZMotorParas();


    int controlDetectLevelEnable(const bool &isEnable);

    int writeBlockNeedleRValue(const NeedleBlockPara &para);

    int writeXMotorParas(const XMotorPara &para);

    int writeYMotorParas(const YMotorPara &para);

    int writeZMotorParas(const ZMotorPara &para);

    int write1ulToStepsToSamplePlungerPumps(const int &steps);

    int writeSampleNeedleAirColumnValue(const ushort &volumn);

    int getStepsFrom1ul() const;
    void setStepsFrom1ul(int stepsFrom1ul);

    ushort getNeedleAirColumn() const;
    void setNeedleAirColumn(const ushort &needleAirColumn);

    NeedleBlockPara getBlockPara() const;
    void setBlockPara(const NeedleBlockPara &blockPara);

    XMotorPara getXMotorPara() const;
    void setXMotorPara(const XMotorPara &xMotorPara);

    YMotorPara getYMotorPara() const;
    void setYMotorPara(const YMotorPara &yMotorPara);

    ZMotorPara getZMotorPara() const;
    void setZMotorPara(const ZMotorPara &zMotorPara);

    int getSampleSuckPos() const;
    void setSampleSuckPos(int sampleSuckPos);

    int getCupHeightByCupType(int cupType);
private:
    int _stepsFrom1ul;
    ushort _needleAirColumn;
    NeedleBlockPara _blockPara;
    XMotorPara _xMotorPara;
    YMotorPara _yMotorPara;
    ZMotorPara _zMotorPara;
    int _sampleSuckPos;
};

#endif // SAMPLEARM_H
