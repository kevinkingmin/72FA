#ifndef REMARKMODEL_H
#define REMARKMODEL_H
#include"../Model.h"
#include<QString>

class MODELSHARED_EXPORT RemarkModel
{
public:
    RemarkModel();
    uint getID() const;
    void setID(const uint &ID);

    QString getStrRemark() const;
    void setStrRemark(const QString &strRemark);

    QString getShortKey() const;
    void setShortKey(const QString &shortKey);

    QString getRemarkRK() const;
    void setRemarkRK(const QString &RemarkRK);

private:
    uint _ID;
    QString _strRemark;
    QString _RemarkRK;
    QString _shortKey;
};

#endif // REMARKMODEL_H
