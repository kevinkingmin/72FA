#ifndef DATABASE_FACTORY_H
#define DATABASE_FACTORY_H
#include <QString>

template<typename T>
class Singleton;
class QMutex;
class QString;
class QSqlDatabase;


class DatabaseFactory{
public:
    ~DatabaseFactory();
public:
    static DatabaseFactory *instance();
public:
    int connect();
    void disconnect();
    QSqlDatabase clone();
    QSqlDatabase connection();
private:
    friend class Singleton<DatabaseFactory>;
private:
    DatabaseFactory();
private:
    QMutex *_lock;
    QSqlDatabase *_database;
    QString _conn;
};

#endif //DATABASE_FACTORY_H
