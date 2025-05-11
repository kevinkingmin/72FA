#ifndef GETLANGUAGECLSBLL_H
#define GETLANGUAGECLSBLL_H
#include <QMap>
#include <QString>
#include "../bll.h"

class BLLSHARED_EXPORT  GetLanguageClsBLL
{
public:
    GetLanguageClsBLL();
public:
    static QString getlangValue(const QString id);

    //1为汉语，2为英文，3德语，4为法语，5为日语
    static void LoadLanguageInfoList();
private:
    static int _languageType;
    static QMap<QString,QString> _languageMap;
};

#endif // GETLANGUAGECLSBLL_H
