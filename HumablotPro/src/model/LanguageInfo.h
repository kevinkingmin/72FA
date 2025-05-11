#ifndef LANGUAGEINFO
#define LANGUAGEINFO
#include <iostream>//等价于C语言中的#include<stdio.h>
#include <cstring>
#include <string.h>
//以上两种都是C语言的string头文件
#include <string>//真正的C++头文件
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
