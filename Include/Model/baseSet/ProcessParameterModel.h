#ifndef PROCESS_PARAMETER_MODEL_H
#define PROCESS_PARAMETER_MODEL_H
#include <QString>
#include <QVector>
#include "../Model.h"

class MODELSHARED_EXPORT ProcessParameterModel
{
public:
    static const QString ADD_REAGENT_CODE;
    static const QString BED_SHAKING_CODE;
    static const QString DRYING_CODE;
    static const QString SAMPLING_CODE;
    static const QString DRAINING_CODE;
    static const QString PAUSING_CODE;
    static const QString TAKE_PHOTO_CODE;
    // 加试剂
    struct AddReagentStrt
    {
        // 是否同时抽干废液
        bool _isDrainWaster;
        // 抽干时间
        double _drainTime;
        // 试剂名
        QString _reagentName;
        // 试剂量
        double _reagentMl;
        // 对应蠕动泵是否回流
        bool _isBackFlow;
        // 回流体积
        double _backFlowMl;
        AddReagentStrt()
            :_isDrainWaster(false)
            ,_drainTime(0)
            ,_reagentName("")
            ,_reagentMl(1)
            ,_isBackFlow(false)
            ,_backFlowMl(0)
        {}
        AddReagentStrt(const bool isDrainWaster,const double drainTime, const QString& name,
                       const double ul,  const bool isBackFlow, const double backFlowMl)
            :_isDrainWaster(isDrainWaster)
            ,_drainTime(drainTime)
            ,_reagentName(name)
            ,_reagentMl(ul)
            ,_isBackFlow(isBackFlow)
            ,_backFlowMl(backFlowMl)
        {}
    };

    // 摇床混匀
    struct BedShakingStrt
    {
        // 干燥时间
        double _shakeTime;
        // 摇床温度
        double _bedTemperature;
        BedShakingStrt()
            :_shakeTime(0)
            ,_bedTemperature(0)
        {}
        BedShakingStrt(const double shakeTime, const double bedTemperature)
            :_shakeTime(shakeTime)
            ,_bedTemperature(bedTemperature)
        {}
    };

    // 干燥
    struct DryingStrt
    {
        // 干燥时间
        double _dryTime;
        // 风扇等级
        int _fanLevel;
        // 风扇时间
        double _fanTime;
        // 干燥温度
        double _bedTemperature;
        // 加热时间
        double _heatTime;
        DryingStrt()
            :_dryTime(0)
            ,_fanLevel(0)
            ,_fanTime(0)
            ,_bedTemperature(0)
            ,_heatTime(0)
        {}
        DryingStrt(const double dryTime, const int fanLevel, const double fanTime, const double bedTemperature, const double heatTime)
            :_dryTime(dryTime)
            ,_fanLevel(fanLevel)
            ,_fanTime(fanTime)
            ,_bedTemperature(bedTemperature)
            ,_heatTime(heatTime)
        {}
    };

    //加样本
    struct SamplingStrt
    {
        double _sampleUl;
        // 加完样本后是否做完全充盈
        bool _isFilling;
        // 内针充盈时间
        int _innerTime;
        // 外针充盈时间
        int _outerTime;
        SamplingStrt()
            :_sampleUl(0)
            ,_isFilling(false)
            ,_innerTime(3)
            ,_outerTime(3)
        {}
        SamplingStrt(const double sampleUl, const bool isFilling, const int& innerTime, const int& outerTime)
            :_sampleUl(sampleUl),_isFilling(isFilling), _innerTime(innerTime), _outerTime(outerTime)
        {}
    };

    // 排废液
    struct DrainingStrt
    {
        // 抽干时间
        double _drainTime;
        DrainingStrt()
            :_drainTime(0)
        {}
        DrainingStrt(const double drainTime)
            :_drainTime(drainTime)
        {}
    };

    //暂停
    struct PausingStrt
    {
        // 向上位机发送的信息
        QString _notifyMessage;
        PausingStrt()
            :_notifyMessage("")
        {}
        PausingStrt(const QString& notifyMessage)
            :_notifyMessage(notifyMessage)
        {}
    };

    ProcessParameterModel();
    int getId() const;
    void setId(int id);

    int getProcessId() const;
    void setProcessId(int companyId);

    QString getActType() const;
    void setActType(const QString &actName);

    QString getActName() const;
    void setActName(const QString &actName);

    QString getActCode() const;
    void setActCode(const QString &actNameCode);

    QString getParas();
    void setParas(QString &str);

    int getExecuteTime();
    void setExecuteTime(int executeTime);

    bool getAddReagent(AddReagentStrt &out);
    void setAddReagent(const AddReagentStrt &strt);

    bool getDraining(DrainingStrt &out);
    void setDraining(const DrainingStrt &strt);

    bool getPausing(PausingStrt &out);
    void setPausing(PausingStrt &strt);

    bool getSampling(SamplingStrt &out);
    void setSampling(const SamplingStrt &strt);

    bool getBedShaking(BedShakingStrt &out);
    void setBedShaking(const BedShakingStrt &strt);

    bool getDrying(DryingStrt &out);
    void setDrying(const DryingStrt &strt);

    bool parsingParas();

    QString toShowString();

    QString AddReagentToStr(const AddReagentStrt &strt);
    QString drainingToStr(const DrainingStrt &strt);
    QString PausingToStr(PausingStrt &strt);
    QString SamplingToStr(const SamplingStrt &strt);
    QString BedShakingToStr(const BedShakingStrt &strt);
    QString dryingToStr(const DryingStrt &strt);
private:
    bool strToAddReagent(AddReagentStrt& out, const QString &str);
    bool strToDraining(DrainingStrt& out, const QString &str);
    bool strToPausing(PausingStrt& out, const QString &str);
    bool strToSampling(SamplingStrt& out, const QString &str);
    bool strToBedShaking(BedShakingStrt& out, const QString &str);
    bool strToDrying(DryingStrt& out, const QString &str);

private:
    int _id;
    int _processId;
    QString _actType;
    QString _actName;
    QString _actCode;
    QString _paras;
    int _executeTime;
    bool _paramParseSuccess;

    AddReagentStrt _addReagentStrt;
    BedShakingStrt _bedShakingStrt;
    DrainingStrt _drainingStrt;
    PausingStrt _pausingStrt;
    SamplingStrt _samplingStrt;
    DryingStrt _dryingStrt;
};

#endif // PROCESSPARAMODEL_H
