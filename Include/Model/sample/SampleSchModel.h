#ifndef SAMPLESCHMODEL_H
#define SAMPLESCHMODEL_H
#include "../Model.h"
#include <QString>
#include <QVector>

class MODELSHARED_EXPORT SampleSchModel
{
public:
    SampleSchModel();
    QString SampleSeqno() const;
    void setSampleSeqno(const QString &SampleSeqno);

    QString Barcode() const;
    void setBarcode(const QString &Barcode);

    QVector<ushort> vectSampleType() const;
    void setVectSampleType(QVector<ushort> vectSampleType);

    QVector<ushort> vectClinicType() const;
    void setVectClinicType(QVector<ushort> vectClinicType);

    QString PatientName() const;
    void setPatientName(const QString &PatientName);

    QString AnamnesisNO() const;
    void setAnamnesisNO(const QString &AnamnesisNO);

    qint64 startDate() const;
    void setStartDate(const qint64 &startDate);

    qint64 endDate() const;
    void setEndDate(const qint64 &endDate);
private:
    QString _SampleSeqno;
    QString _Barcode;
    QVector<ushort> _vectSampleType;
    QVector<ushort> _vectClinicType;
    QString _PatientName;
    QString _AnamnesisNO;
    qint64 _startDate;
    qint64 _endDate;
};

#endif // SAMPLESCHMODEL_H
