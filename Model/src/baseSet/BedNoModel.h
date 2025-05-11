#ifndef BEDNOMODEL_H
#define BEDNOMODEL_H
#include"../Model.h"
#include<QString>

class MODELSHARED_EXPORT BedNoModel
{
public:
    BedNoModel();
    uint getID() const;
    void setID(const uint &ID);

    QString getBedNoName() const;
    void setBedNoName(const QString &BedNoName);

    QString getShortKey() const;
    void setShortKey(const QString &shortKey);

    QString getRemark() const;
    void setRemark(const QString &remark);

private:
    uint _ID;
    QString _BedNoName;
    QString _shortKey;
    QString _remark;
};

#endif // BEDNOMODEL_H
