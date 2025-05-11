#ifndef WARDMODEL_H
#define WARDMODEL_H
#include"../Model.h"
#include<QString>

class MODELSHARED_EXPORT WardModel
{
public:
    WardModel();
    uint getID() const;
    void setID(const uint &ID);

    QString getWardName() const;
    void setWardName(const QString &wardName);

    QString getShortKey() const;
    void setShortKey(const QString &shortKey);

    QString getRemark() const;
    void setRemark(const QString &remark);

private:
    uint _ID;
    QString _wardName;
    QString _shortKey;
    QString _remark;
};

#endif // WARDMODEL_H
