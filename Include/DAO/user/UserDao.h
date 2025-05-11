#ifndef USERDAO_H
#define USERDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QMap>
#include <QVector>

template<class T>
class Singleton;

class QSqlQuery;
class UserModel;

class DAOSHARED_EXPORT UserDao
{
private:
    UserDao();
    UserDao(UserDao &)=delete;
    UserDao(UserDao &&)=delete;
    UserDao &operator=(const UserDao&)=delete;
    UserDao &operator=(UserDao&&)=delete;
    using ptrModel=QSharedPointer<UserModel>;

    friend Singleton<UserDao>;
    void getTable();
    void queryBindValue(QSqlQuery &query, ptrModel pm);
public:
    ~UserDao();
    static UserDao *instance();
    QVector<ptrModel> getAllRows();
    bool deleteById(uint id);
    bool updateModel(ptrModel pm);
    bool insertModel(ptrModel pm);
	QSqlQuery SelectRecord(bool *bResult, QString sql);
private:
    QMap<uint,ptrModel>_map;
};

#endif // USERDAO_H
