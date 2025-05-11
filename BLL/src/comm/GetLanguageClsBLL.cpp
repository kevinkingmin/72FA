#include "GetLanguageClsBLL.h"
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include "../baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"

int GetLanguageClsBLL::_languageType=0;
QMap<QString,QString> GetLanguageClsBLL::_languageMap{};
GetLanguageClsBLL::GetLanguageClsBLL()
{

}

QString GetLanguageClsBLL::getlangValue(const QString id)
{
    LoadLanguageInfoList();
    auto it{_languageMap.find(id)};
    if(it==_languageMap.end())
        return id;
    return it.value();
}

void GetLanguageClsBLL::LoadLanguageInfoList()
{//1为汉语，2为英文，3德语，4为法语，5为日语
    auto set=SystemSetBLL().getRowById(20005);
	QString des = set->getSaveDes();
    int iType(set.isNull()?1:des.toInt());
    if(iType==_languageType)
        return;

    _languageMap.clear();
    _languageType=iType;
    QString image_path = "";
    image_path = QCoreApplication::applicationDirPath() + "/Language.dat";
    QFile f(image_path);
    if (!f.exists() || !f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream txtInput(&f);
    QString lineStr="";
    int i = 0;
    while (!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        QString language_code = "";
        QString language_str= "";
        QStringList strList = lineStr.split('|');
        if (i <= 0)
        {
			i++;
            continue;
        }
        if(strList.length()<2 || strList.length()<=_languageType)
            continue;
        _languageMap.insert(strList[0],strList[_languageType]);
    }
}
