#ifndef COMMONTYPE_H
#define COMMONTYPE_H
#include "../Model.h"

typedef enum
{
    eUnknown=0,//未知流程
    eStartUpCheck=1,//开机自检
    eSystemLiquidIrrigate=2,//系统液充灌
    eSystemLiquidWash=3,//系统液清洗
    ePrepareReagent=4,//试剂准备流程
    ePumpFill=5,//泵充灌
    eTubeSoak=6,//管路浸泡
    ePumpCalibrate=7,//泵校准
}eMaintainType;

enum eAddType
{//0=忽略，1=只加，2=只排，3=吸吐
    eIgnore=0,
    eAdd=1,
    eWaste=2,
    eAllAct=3
};

enum eCupType
{
    eStandardCup=0,//标准杯
    eBloodCup=1,//采血管
    eMicroCup=2,//微量杯
};

enum eLiquidType
{
    eUnknow=-1,//未知物
    eCombineA=0,//结合物液A
    eCombineB=1,//结合物液B
    eCombineC=2,//结合物液C
    eCombineD=3,//结合物液D
    eDiluent=4,//稀释缓冲液
    eSubstrate=5,//底物
    eStopLiquid=6,//终止液
    eDistilledWater=7,//蒸馏水
    eWashLiquid=8,//洗涤缓冲液
    eSystemLiquid=9,//系统液
};

enum eSubIdType
{
    eUndetermined=-1,//未知类型
};

#endif // COMMONTYPE_H
