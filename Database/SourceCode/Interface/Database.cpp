#include"Database.h"
#include"../Database/DatabaseFactory.h"
#include<QSqlDatabase>

Database::Database()
{

}

int Database::connectDatabase()
{
    return((DatabaseFactory::instance())->connect());
}

void Database::disconnectDatabase()
{
    return((DatabaseFactory::instance())->disconnect());
}

QSqlDatabase Database::databaseClone()
{
    return((DatabaseFactory::instance())->clone());
}

QSqlDatabase Database::databaseConnection()
{
    return((DatabaseFactory::instance())->connection());
}
