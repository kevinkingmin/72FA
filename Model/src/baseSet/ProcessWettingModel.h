#ifndef PROCESS_WETTING_MODEL_H
#define PROCESS_WETTING_MODEL_H
#include "../Model.h"
#include <QString>
#include <QVector>

// 润湿
class MODELSHARED_EXPORT ProcessWettingModel
{
public:
    ProcessWettingModel();
    struct paraStruct
    {
        QString reagentName;
        double reagentUl;
        double wettingTime;
        bool isDrainWaster;
        paraStruct(const QString& name, const double ul, const double time, const bool isDrain)
            :reagentName(name)
            ,reagentUl(ul)
            ,wettingTime(time)
            ,isDrainWaster(isDrain)
        {}
    };
public:

    uint getId() const;
    void setId(const uint &id);

    QVector<paraStruct> getParas() const;
    void setParas(QString &str);

    int getPreIntFileld1() const;
    void setPreIntFileld1(int preIntFileld1);

    QString getRemark() const;
    void setRemark(const QString &remark);

    QString vectToStr(QVector<paraStruct> vect);

private:
    QVector<paraStruct> strToVect(const QString &str);
private:
    uint _id;
    QVector<paraStruct>_paras;
    int _preIntFileld1;
    QString _remark;	
};

#endif // INSTRUMENTPARASSETMODEL_H
