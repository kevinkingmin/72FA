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
        double _reagentUl;
        // 对应蠕动泵是否回流
        bool _isBackFlow;
        // 回流体积
        double _backFlowUl;
        AddReagentStrt(const bool isDrainWaster,const double drainTime,
                       const QString& name, const double ul,  const bool isBackFlow, const double backFlowUl)
            :_isDrainWaster(isDrainWaster)
            ,_drainTime(drainTime)
            ,_reagentName(name)
            ,_reagentUl(ul)
            ,_isBackFlow(isBackFlow)
            ,_backFlowUl(backFlowUl)
        {}
    };

    // 摇床混匀
    struct BedShakingStrt
    {
        // 干燥时间
        double _shakeTime;
        // 摇床温度
        double _bedTemperature;
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
        // 风干等级
        double _bedTime;
        DryingStrt(const double dryTime, const int fanLevel, const double fanTime, const double bedTemperature, const double bedTime)
            :_dryTime(dryTime)
            ,_fanLevel(fanLevel)
            ,_fanTime(fanTime)
            ,_bedTemperature(bedTemperature)
            ,_bedTime(bedTime)
        {}
    };

    //加样本
    struct SamplingStrt
    {
        double _sampleUl;
        SamplingStrt(const double sampleUl)
            :_sampleUl(sampleUl)
        {}
    };

    // 排废液
    struct DrainingStrt
    {
        // 抽干时间
        double _drainTime;
        DrainingStrt(const double drainTime)
            :_drainTime(drainTime)
        {}
    };

    //暂停
    struct PausingStrt
    {
        // 向上位机发送的信息
        QString _notifyMessage;
        PausingStrt(const QString& notifyMessage)
            :_notifyMessage(notifyMessage)
        {}
    };

    ProcessParameterModel();
    int getId() const;
    void setId(int id);

    int getCompanyId() const;
    void setCompanyId(int companyId);

    int getActIndex() const;
    void setActIndex(int index);

    QString getActName() const;
    void setActName(const QString &actName);

    QString getActCode() const;
    void setActCode(const QString &actNameCode);

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

    void setParas(QString &str);

    bool parsingParas();

    QString toShowString();

private:
    bool strToAddReagent(AddReagentStrt& out, const QString &str);
    QString AddReagentToStr(const AddReagentStrt &strt);

    bool strToDraining(DrainingStrt& out, const QString &str);
    QString drainingToStr(const DrainingStrt &strt);


    bool strToPausing(PausingStrt& out, const QString &str);
    QString PausingToStr(PausingStrt &strt);


    bool strToSampling(SamplingStrt& out, const QString &str);
    QString SamplingToStr(const SamplingStrt &strt);


    bool strToBedShaking(BedShakingStrt& out, const QString &str);
    QString BedShakingToStr(const BedShakingStrt &strt);

    bool strToDrying(DryingStrt& out, const QString &str);
    QString dryingToStr(const DryingStrt &strt);

private:
    int _id;
    int _companyId;
    QString _actName;
    QString _actCode;
    QString _paras;
    bool _paramParseSuccess;

    AddReagentStrt _addReagentStrt;
    BedShakingStrt _bedShakingStrt;
    DrainingStrt _drainingStrt;
    PausingStrt _pausingStrt;
    SamplingStrt _samplingStrt;
    DryingStrt _dryingStrt;
};

#endif // PROCESSPARAMODEL_H
