#include "GetLanguageCls.h"
#include <QObject>
#include <QDateTime>
#include <QSettings>
#include <QMessageBox>
#include <QMutex>
#include <QDir>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QTextStream>



GetLanguageCls::GetLanguageCls()
{

}

void GetLanguageCls::LoadLanguageInfoList(int language_type)
{
	QString image_path = "";
	image_path = QCoreApplication::applicationDirPath() + "/Language.dat";
	QFile f(image_path);
	 if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
	 {
		 //qDebug() << ("打开文件失败");
	 }
	 QTextStream txtInput(&f);
	 QString lineStr;
	 int i = 0;
	 while (!txtInput.atEnd())
	 {
		 lineStr = txtInput.readLine();
		 QString language_code = "";
		 QString language_str= "";
		 QStringList strList = lineStr.split('|');
		 if (i > 0)
		 {
			 if (strList.length() > 2)
			 {
				 language_code = QString("%1").arg(strList[0]);
				 if (language_type == 1)
				 {
					 language_str = QString("%1").arg(strList[1]);
				 }
				 if (language_type == 2)
				 {
					 language_str = QString("%1").arg(strList[2]);
				 }
				 if (language_type == 3)
				 {
					 language_str = QString("%1").arg(strList[3]);
				 }
				 if (language_type == 4)
				 {
					 language_str = QString("%1").arg(strList[4]);
				 }
				 if (language_type == 5)
				 {
					 language_str = QString("%1").arg(strList[5]);
				 }
			 }

			 if (language_code != "" && language_str != "")
			 {
				 LanguageInfo s1(language_code, language_str);
				 g_languageInfo_list.push_back(s1);
			 }
		 }
		 i++;
	 }
	 f.close();
}

QString GetLanguageCls::GetLanguagInfo(QString id)
{
	QString info = "";
	for (std::list<LanguageInfo>::iterator it = g_languageInfo_list.begin(); it != g_languageInfo_list.end(); it++)
	{
		if (it->id == id)
		{
			info = it->content;
			return info;
			break;
		}
	}
	return info;
}


GetLanguageCls::~GetLanguageCls()
{

}