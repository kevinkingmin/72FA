#ifndef STANDARD_CURVE_DAO_H
#define STANDARD_CURVE_DAO_H
#include "../dao.h"
#include <QVector>
#include "../Include/Model/baseSet/StandaryCurveModel.h"

template<class T>
class Singleton;

class QSqlQuery;

class DAOSHARED_EXPORT StandardCurveDao
{
private:
    StandardCurveDao();
    StandardCurveDao(StandardCurveDao &)=delete;
    StandardCurveDao(StandardCurveDao &&)=delete;
    StandardCurveDao &operator=(const StandardCurveDao&)=delete;
    StandardCurveDao &operator=(StandardCurveDao&&)=delete;
    friend Singleton<StandardCurveDao>;
public:
    ~StandardCurveDao();
    static StandardCurveDao *instance();
    QVector<StandaryCurveModel> getAllRows();
    QVector<QString> getAllNames();
    bool getModel(const int ruleId, StandaryCurveModel& out);
    bool insert(StandaryCurveModel& model);
    bool update(StandaryCurveModel &m);
    bool deleteModel(int id);
private:
};

#endif
