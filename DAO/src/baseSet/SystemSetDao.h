#ifndef SYSTEMSETDAO_H
#define SYSTEMSETDAO_H
#include "../dao.h"
#include <QVector>
#include <QMap>
#include <QSharedPointer>

template<class T>
class Singleton;

class SystemSetModel;
class QSqlQuery;

class DAOSHARED_EXPORT SystemSetDao
{
private:
    SystemSetDao();
    SystemSetDao(SystemSetDao &)=delete;
    SystemSetDao(SystemSetDao &&)=delete;
    SystemSetDao &operator=(const SystemSetDao&)=delete;
    SystemSetDao &operator=(SystemSetDao&&)=delete;

    friend Singleton<SystemSetDao>;

    void queryBindValue(QSqlQuery &query, SystemSetModel& model);
public:
    ~SystemSetDao();
    static SystemSetDao *instance();
    bool updateModel(SystemSetModel& model);
    bool getModel(int id, SystemSetModel& out);
    bool getPictureAnalysisDebug(SystemSetModel& out);
    bool getPictureAnalysisDebug();
    bool getPicturePathRoot(QString& out);
    // 送检者名称
    QString getSubmitter();
    // 检验者名称
    QString getTester();
    // 审核者名称
    QString getVerifier();

    QString getDefaultProcessName();
    int getProcessId();
    QVector<SystemSetModel>getAllRows();
private:
};

#endif
