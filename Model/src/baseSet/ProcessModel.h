#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H
#include <QString>
#include "../Model.h"

class MODELSHARED_EXPORT ProcessModel
{
public:
    ProcessModel();

    int getId() const;
    void setId(int id);

    QString getPName() const;
    void setPName(const QString &pName);

    QString getRemark() const;
    void setRemark(const QString &remark);

    bool getIsDefault() const;
    void setIsDefault(bool isDefault);

    QString getAddUser() const;
    void setAddUser(const QString &addUser);

    qint64 getAddTime() const;
    void setAddTime(const qint64 &addTime);

private:
    int _id;
    QString _pName;
    QString _remark;
    bool _isDefault;
    QString _addUser;
    qint64 _addTime;
};
#endif // PROCESSMODEL_H
