#include "StandaryCurveModel.h"
#include <QStringList>

StandaryCurveModel::StandaryCurveModel():
    _id(0)
   ,_type(0)
   ,_remark("")
   ,_dataGroup({})
{

}
int StandaryCurveModel::getCurveId() const
{
    return _id;
}

void StandaryCurveModel::setCurveId(int id)
{
    _id = id;
}

int StandaryCurveModel::getCurveType() const
{
    return _type;
}

void StandaryCurveModel::setCurveType(int type)
{
    _type = type;
}

// 备注
QString StandaryCurveModel::getCurveName() const
{
    return _curveName;
}

void StandaryCurveModel::setCurveName(const QString &name)
{
    _curveName = name;
}

// 备注
QString StandaryCurveModel::getRemark() const
{
    return _remark;
}

void StandaryCurveModel::setRemark(const QString &remark)
{
    _remark = remark;
}

QVector<double> StandaryCurveModel::getDataGroup()
{
    return _dataGroup;
}

void StandaryCurveModel::setDataGroup(QVector<double> dataGroup)
{
    _dataGroup = dataGroup;
}

bool StandaryCurveModel::setDataGroupStr(int type, QString& parameterStr)
{
    QVector<double> dataVect;
    QStringList strList = parameterStr.split(',');
    for (const QString &s : strList)
    {
        bool ok;
        double num = s.toDouble(&ok);
        if (ok)
        {
            dataVect.push_back(num);
        }else
        {
            return false;
        }
    }
    if((type == 0 && dataVect.count() == 2)||(type == 1 && dataVect.count()==4))
    {
         _dataGroup = dataVect;
         return true;
    }
    return false;
}

QString StandaryCurveModel::getDataGroupStr()
{
    QStringList strList;
    for (double v : _dataGroup)
    {
        strList << QString::number(v, 'g', 2);
    }
    return strList.join(",");
}
