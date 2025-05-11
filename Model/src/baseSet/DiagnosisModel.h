#ifndef DIAGNOSISMODEL_H
#define DIAGNOSISMODEL_H
#include"../Model.h"
#include<QString>

class MODELSHARED_EXPORT DiagnosisModel
{
public:
    DiagnosisModel();
    uint getID() const;
    void setID(const uint &ID);

    QString getStrDiagnosis() const;
    void setStrDiagnosis(const QString &StrDiagnosis);

    QString getShortKey() const;
    void setShortKey(const QString &shortKey);

    QString getRemark() const;
    void setRemark(const QString &remark);

private:
    uint _ID;
    QString _StrDiagnosis;
    QString _shortKey;
    QString _remark;
};

#endif // DIAGNOSISMODEL_H
