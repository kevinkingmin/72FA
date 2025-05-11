#ifndef USERBLL_H
#define USERBLL_H
#include <QSharedPointer>
#include <QVector>
#include "../bll.h"
#include <set>

class UserModel;
class UserGroupModel;
class BLLSHARED_EXPORT UserBLL
{
public:
    UserBLL();
    using ptrUser=QSharedPointer<UserModel>;
    using ptrGroup=QSharedPointer<UserGroupModel>;

    struct UserStruct
    {
        ptrUser pUser;
        ptrGroup pGroup;
        UserStruct()
        {
            pUser=nullptr;
            pGroup=nullptr;
        }
    };

    QVector<UserStruct>getAllRows();
    UserStruct getRowById(uint id);
    UserStruct login(QString loginName,QString password);

    bool deleteById(uint id);
    int updateByModel(ptrUser pm);
    int insertModel(ptrUser pm);

private:
    const QString getMd5Str(const QString loginName,const QString password);
    ptrUser getUserById(const uint id);
private:
    const QString _privateKey;
};

#endif // USERBLL_H
