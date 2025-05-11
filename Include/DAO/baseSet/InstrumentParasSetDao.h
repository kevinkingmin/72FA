#ifndef INSTRUMENTPARASSETDAO_H
#define INSTRUMENTPARASSETDAO_H
#include "../dao.h"
#include <QSharedPointer>
#include <QVector>
#include <QMap>

template <class T>
class Singleton;

class QSqlQuery;
class InstrumentParasSetModel;

class DAOSHARED_EXPORT InstrumentParasSetDao
{
private:
    InstrumentParasSetDao();
    InstrumentParasSetDao(InstrumentParasSetDao &)=delete;
    InstrumentParasSetDao(InstrumentParasSetDao &&)=delete;
    InstrumentParasSetDao &operator=(const InstrumentParasSetDao&)=delete;
    InstrumentParasSetDao &operator=(InstrumentParasSetDao&&)=delete;

    friend Singleton<InstrumentParasSetDao>;
    void getTable();
public:
    ~InstrumentParasSetDao();
    static InstrumentParasSetDao *instance();
    bool updateModel(InstrumentParasSetModel m);
    QVector<InstrumentParasSetModel>getAllRows();
private:
    QMap<uint,InstrumentParasSetModel>_map;
};

#endif // INSTRUMENTPARASSETDAO_H
