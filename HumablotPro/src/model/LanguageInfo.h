#ifndef LANGUAGEINFO
#define LANGUAGEINFO
#include <iostream>//�ȼ���C�����е�#include<stdio.h>
#include <cstring>
#include <string.h>
//�������ֶ���C���Ե�stringͷ�ļ�
#include <string>//������C++ͷ�ļ�
#include <string.h>
#include <iostream>

#include <QCoreApplication>
#include <QTextStream>

using namespace std;

class LanguageInfo
{
public:
	LanguageInfo();
	~LanguageInfo();

	LanguageInfo(QString i, QString content);
	void show();
	bool operator==(const LanguageInfo &s);

	QString id;
	QString content;//[32];

private:

};

#endif //GETLANGUAGECLS
