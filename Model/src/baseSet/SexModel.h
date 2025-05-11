#ifndef SEXMODEL_H
#define SEXMODEL_H
#include <QString>
#include "../Model.h"

class MODELSHARED_EXPORT SexModel
{
public:
    SexModel();

    uint getID() const;
    void setID(const uint &ID);

    QString getSexName() const;
    void setSexName(const QString &SexName);

    uint getOrderNo() const;
    void setOrderNo(const uint &orderNo);

private:
    uint _ID;
    QString _SexName;
    uint _orderNo;
};
#endif // SEXMODEL_H
