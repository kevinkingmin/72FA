#ifndef USERMODEL_H
#define USERMODEL_H
#include <QString>
#include "../Model.h"

class MODELSHARED_EXPORT UserModel
{
public:
    UserModel();
    uint getID() const;
    void setID(const uint &ID);

    uint getGroupID() const;
    void setGroupID(const uint &GroupID);

    QString getLoginName() const;
    void setLoginName(const QString &LoginName);

    QString getUPassword() const;
    void setUPassword(const QString &uPassword);

    QString getShowName() const;
    void setShowName(const QString &showName);

    QString getAddUser() const;
    void setAddUser(const QString &addUser);

    quint64 getAddTime() const;
    void setAddTime(const quint64 &addTime);

    bool getIsDelete() const;
    void setIsDelete(bool isDelete);

private:
    uint _ID;
    uint _GroupID;
    QString _LoginName;
    QString _uPassword;
    QString _showName;
    QString _addUser;
    quint64 _addTime;
    bool _isDelete;
};

#endif // USERMODEL_H
