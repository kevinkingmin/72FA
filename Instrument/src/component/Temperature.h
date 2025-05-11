#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include"Component.h"
class InstrumentStateModel;
#define ABSOLUTEZERO -273.15f
class Temperature:public Component
{
public:
    struct PIDStruct
    {
        int paraP;
        int paraI;
        int paraD;
        PIDStruct()
            :paraP(0)
            ,paraI(0)
            ,paraD(0)
        {}
    };

    explicit Temperature(QObject *parent=nullptr);
    virtual ~Temperature();
public:
    int dstTemperatureControl(TemperatureAddress address, const bool enable,const float temperature);
    int writeTemperaturePIDPara(TemperatureAddress address,const int p,const int i,const int d);

    int inquireDSTTemperature();
    int inquireRealTimeTemperature();
    int inquirePIDPara(TemperatureAddress address);


    float getDSTTemperature() const;
    void setDSTTemperature(float DSTTemperature);

    float getRealTimeTemperature() const;
    void setRealTimeTemperature(float realTimeTemperature);

    void resetPIDPara(const TemperatureAddress address);
    void setPIDPara(const PIDStruct &PIDPara,const TemperatureAddress address);
    PIDStruct getPIDParaByAddress(const TemperatureAddress address);

private:
    float _DSTTemperature;
    float _realTimeTemperature;
    Flag _monitorFlag;

    PIDStruct _PIDPara[TEMP_COUNT];
    InstrumentStateModel *_instrState;
};

#endif // TEMPERATURE_H
