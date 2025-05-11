#ifndef DATABASE_H
#define DATABASE_H

#include<QtCore/qglobal.h>

class QSqlDatabase;

#if defined(DATABASE_LIBRARY)
#  define DATABASE_API Q_DECL_EXPORT
#else
#  define DATABASE_API Q_DECL_IMPORT
#endif

class DATABASE_API Database
{
public:
    Database();
    static int connectDatabase();
    static void disconnectDatabase();
    static QSqlDatabase databaseClone();
    static QSqlDatabase databaseConnection();
};
#endif//DATABASE_H
