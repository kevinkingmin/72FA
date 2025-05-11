#ifndef AGEUNITMODEL_H
#define AGEUNITMODEL_H
#include <QString>
#include "../Model.h"

class MODELSHARED_EXPORT AgeUnitModel
{
public:
    AgeUnitModel();

    uint getID() const;
    void setID(const uint &ID);

    QString getAgeName() const;
    void setAgeName(const QString &AgeName);

    uint getOrderNo() const;
    void setOrderNo(const uint &orderNo);

private:
    uint _ID;
    QString _AgeName;
    uint _orderNo;
};

#endif // AGEUNITMODEL_H
