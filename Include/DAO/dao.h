#ifndef DAO_H
#define DAO_H

#include <QtCore/qglobal.h>
class QSqlQuery;

#if defined(DAO_LIBRARY)
#  define DAOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DAOSHARED_EXPORT Q_DECL_IMPORT
#endif
class DAO
{
public:
    static int createQuery(QSqlQuery &query);
};

#endif // DAO_H
