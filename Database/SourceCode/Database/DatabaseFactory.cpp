#include"DatabaseFactory.h"
#include<QMutex>
#include<QString>
#include<QSqlDatabase>
#include<QMutexLocker>
#include<QThread>
#include<QDateTime>
#include<QSqlError>
#include<QException>
#include<QCoreApplication>
#include<QSettings>
#include <QDebug>
#include "../Include/Comm/singleton.h"

#if defined(Q_OS_WIN32)||defined(Q_OS_WIN64)
#include<qt_windows.h>
#else
#include<pthread.h>
#endif

DatabaseFactory::~DatabaseFactory(){
    disconnect();
    if(nullptr!=_lock)
        delete _lock;

    if(nullptr!=_database)
        delete _database;
}

DatabaseFactory *DatabaseFactory::instance()
{
    return(Singleton<DatabaseFactory>::instance());
}

int DatabaseFactory::connect()
{
    QMutexLocker locker(_lock);
#if defined(Q_OS_WIN32)||defined(Q_OS_WIN64)
    const QString connName(QString().number(GetCurrentThreadId()));
#else
    const QString connName(QString().number(pthread_self()));
#endif
    (*_database)=QSqlDatabase::addDatabase("QMYSQL", connName);
    _database->setHostName("localhost");
    //_database->setHostName("192.168.0.187");
    _database->setPort(3306);
    _database->setDatabaseName("HumaBlotPro");//HumaBlotPro_dxp
    _database->setUserName("root");
    _database->setPassword("123456");// TaiWen_666666_$
	try
	{
		if (!_database->open())
		{
            QSqlError error = _database->lastError();
            QString content = error.text();
            qDebug()<<content<<endl;
			return(-1);
		}
	}
	catch (QSqlError &e)
	{
		throw(e);
	}
    return(0);
}

void DatabaseFactory::disconnect(){
    QMutexLocker locker(_lock);
    if(_database->isOpen())
        _database->close();
}

QSqlDatabase DatabaseFactory::clone()
{
#if defined(Q_OS_WIN32)||defined(Q_OS_WIN64)
    const QString connName(QString().number(GetCurrentThreadId()));
#else
    const QString connName(QString().number(pthread_self()));
#endif
    if(QSqlDatabase::contains(connName))
    {
        return(QSqlDatabase::database(connName));
    }
    else
    {
        QMutexLocker locker(_lock);
        QSqlDatabase database=QSqlDatabase::cloneDatabase(*_database,connName);

        if(!database.open())
            return(QSqlDatabase());
        else
            return(database);
    }
}

QSqlDatabase DatabaseFactory::connection()
{
#if defined(Q_OS_WIN32)||defined(Q_OS_WIN64)
    const QString connName(QString().number(GetCurrentThreadId()));
#else
    const QString connName(QString().number(pthread_self()));
#endif
    return(QSqlDatabase::database(connName));
}

DatabaseFactory::DatabaseFactory()
    :_lock(new QMutex)
    ,_database(new QSqlDatabase)
{
    Q_ASSERT(nullptr!=_lock);
    Q_ASSERT(nullptr!=_database);
    auto exe_path = QCoreApplication::applicationDirPath()+"/config/instrumentConfig.ini";
    QSettings config_set(exe_path, QSettings::IniFormat);
    _conn = config_set.value("dataBaseConn/Conn", "localhost").toString();
}
