#include "DiagnosisModel.h"

DiagnosisModel::DiagnosisModel():
    _ID(0)
  , _StrDiagnosis("")
  , _shortKey("")
  , _remark("")
{
}

uint DiagnosisModel::getID() const
{
    return _ID;
}

void DiagnosisModel::setID(const uint &ID)
{
    _ID = ID;
}

QString DiagnosisModel::getStrDiagnosis() const
{
    return _StrDiagnosis;
}

void DiagnosisModel::setStrDiagnosis(const QString &StrDiagnosis)
{
    _StrDiagnosis = StrDiagnosis;
}

QString DiagnosisModel::getShortKey() const
{
    return _shortKey;
}

void DiagnosisModel::setShortKey(const QString &shortKey)
{
    _shortKey = shortKey;
}

QString DiagnosisModel::getRemark() const
{
    return _remark;
}

void DiagnosisModel::setRemark(const QString &remark)
{
    _remark = remark;
}
