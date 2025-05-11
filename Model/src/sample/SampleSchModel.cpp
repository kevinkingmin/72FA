#include "SampleSchModel.h"

SampleSchModel::SampleSchModel():
    _SampleSeqno("")
  , _Barcode("")
  , _PatientName("")
  , _AnamnesisNO("")
  , _startDate(0)
  , _endDate(0)
{
}

QString SampleSchModel::SampleSeqno() const
{
    return _SampleSeqno;
}

void SampleSchModel::setSampleSeqno(const QString &SampleSeqno)
{
    _SampleSeqno = SampleSeqno;
}

QString SampleSchModel::Barcode() const
{
    return _Barcode;
}

void SampleSchModel::setBarcode(const QString &Barcode)
{
    _Barcode = Barcode;
}

QVector<ushort> SampleSchModel::vectSampleType() const
{
    return _vectSampleType;
}

void SampleSchModel::setVectSampleType(QVector<ushort> vectSampleType)
{
    _vectSampleType.swap(vectSampleType);
}


QVector<ushort> SampleSchModel::vectClinicType() const
{
    return _vectClinicType;
}

void SampleSchModel::setVectClinicType(QVector<ushort> vectClinicType)
{
    _vectClinicType.swap(vectClinicType);
}

QString SampleSchModel::PatientName() const
{
    return _PatientName;
}

void SampleSchModel::setPatientName(const QString &PatientName)
{
    _PatientName = PatientName;
}

QString SampleSchModel::AnamnesisNO() const
{
    return _AnamnesisNO;
}

void SampleSchModel::setAnamnesisNO(const QString &AnamnesisNO)
{
    _AnamnesisNO = AnamnesisNO;
}

qint64 SampleSchModel::startDate() const
{
    return _startDate;
}

void SampleSchModel::setStartDate(const qint64 &startDate)
{
    _startDate = startDate;
}

qint64 SampleSchModel::endDate() const
{
    return _endDate;
}

void SampleSchModel::setEndDate(const qint64 &endDate)
{
    _endDate = endDate;
}

