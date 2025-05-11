#ifndef SCANER_H
#define SCANER_H
#include"Component.h"

class Scaner:public Component
{
public:
    explicit Scaner(QObject *parent=nullptr);
    virtual ~Scaner();
public:
    int scanerRead();
    int scanerSelfCheck();
    int scanSampleBarcode(const uchar pos);

    QString getReadCode() const;
    void setReadCode(const QString &readCode);

    QString getCheckCode() const;
    void setCheckCode(const QString &checkCode);

    QString getSampleBarcode() const;
    void setSampleBarcode(const QString &sampleBarcode);

private:
    QString _readCode;
    QString _checkCode;
    QString _sampleBarcode;
};

#endif // SCANER_H
