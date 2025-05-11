#include "dao.h"
#include <QSqlQuery>
#include <QSqlError>
#include "../Include/Database/Database.h"
#include "../Include/Utilities/log.h"

int DAO::createQuery(QSqlQuery &query)
{
	auto dataBase = Database::databaseClone();
	if (!dataBase.isOpen())
	{
        eLog("数据库打开失败！！");
		return -2;
	}
    QSqlQuery q(dataBase);
	query = q;
    if(query.isActive() || query.isValid())
    {
        eLog("sqlError:{}--{}--{}",query.lastError().databaseText().toStdString(),
             query.lastError().text().toStdString(),
             query.lastError().driverText().toStdString());
        return -1;
    }
    return 0;
}
