#ifndef USERGROUPDAO_H
#define USERGROUPDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QVector>

template<class T>
class Singleton;

class QSqlQuery;
class UserGroupModel;

class DAOSHARED_EXPORT UserGroupDao
{
private:
    UserGroupDao();
    UserGroupDao(UserGroupDao &)=delete;
    UserGroupDao(UserGroupDao &&)=delete;
    UserGroupDao &operator=(const UserGroupDao&)=delete;
    UserGroupDao &operator=(UserGroupDao&&)=delete;
    using ptrModel= QSharedPointer<UserGroupModel>;
    friend Singleton<UserGroupDao>;

    void getTable();
public:
    ~UserGroupDao();
    static UserGroupDao *instance();
    QVector<ptrModel> getAllRows();
private:
    QVector<ptrModel>_vect;
};

#endif // USERGROUPDAO_H
