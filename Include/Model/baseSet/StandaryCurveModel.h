#ifndef STANDARY_CURVE_MODEL_H
#define STANDARY_CURVE_MODEL_H
#include <QString>
#include <QVector>
#include "../Model.h"

class MODELSHARED_EXPORT StandaryCurveModel
{
public:
    StandaryCurveModel();

    int getCurveId() const;
    void setCurveId(int id);

    int getCurveType() const;
    void setCurveType(int type);

    QString getCurveName() const;
    void setCurveName(const QString &name);

    // 备注
    QString getRemark() const;
    void setRemark(const QString &remark);

    QVector<double> getDataGroup();
    void setDataGroup(QVector<double> dataGroup);

    bool setDataGroupStr(int type, QString& parameterStr);
    QString getDataGroupStr();

private:
    int _id;
    QString _curveName;
    int _type;
    QString _remark;
    QVector<double> _dataGroup;
};
#endif
