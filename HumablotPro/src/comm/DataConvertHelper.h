#ifndef DATACONVERTHELPER_H
#define DATACONVERTHELPER_H
#include <QByteArray>
#include <QString>

class DataConvertHelper
{
public:
    DataConvertHelper();

    static QString byteArrayToHexStr(const QByteArray &data);

    static QString byteArrayToAsciiStr(const QByteArray &data);

    static QByteArray asciiStrToByteArray(const QString &str);

    static QByteArray hexStrToByteArray(const QString &str);

    static QString byteArrayToHexStr(const QByteArray &data,bool b=false);


};

#endif // DATACONVERTHELPER_H
