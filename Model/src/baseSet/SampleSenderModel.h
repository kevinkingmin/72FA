#ifndef SAMPLESENDERMODEL_H
#define SAMPLESENDERMODEL_H
#include <QString>
#include "../Model.h"

class MODELSHARED_EXPORT SampleSenderModel
{
public:
    SampleSenderModel();
    uint getID() const;
    void setID(const uint &ID);

    QString getSenderName() const;
    void setSenderName(const QString &senderName);

    QString getShortKey() const;
    void setShortKey(const QString &shortKey);

    QString getRemark() const;
    void setRemark(const QString &remark);

private:
    uint _ID;
    QString _senderName;
    QString _shortKey;
    QString _remark;
};

#endif // SAMPLESENDERMODEL_H
