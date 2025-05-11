#ifndef USERGROUPMODEL_H
#define USERGROUPMODEL_H
#include <QString>
#include "../Model.h"

class MODELSHARED_EXPORT UserGroupModel
{
public:
    UserGroupModel();
    uint getID() const;
    void setID(const uint &ID);
    QString getGroupName() const;
    void setGroupName(const QString &GroupName);
    bool getEnableAddOrDelete() const;
    void setEnableAddOrDelete(bool EnableAddOrDelete);
    bool getEnableChangePassword() const;
    void setEnableChangePassword(bool EnableChangePassword);

private:
    uint _ID;
    QString _GroupName;
    bool _EnableAddOrDelete;
    bool _EnableChangePassword;
};

#endif // USERGROUPMODEL_H
