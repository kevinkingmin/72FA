//#ifndef GETLANGUAGECLS
//#define GETLANGUAGECLS
#include <list>
#include "LanguageInfo.h"
#include <string>//真正的C++头文件
#include <string.h>
#include <iostream>
using namespace std;

class GetLanguageCls
{
public:
	GetLanguageCls();
	~GetLanguageCls();

public:

	list<LanguageInfo> g_languageInfo_list;      //创建链表对象
public:
	QString GetLanguagInfo(QString id);
	///1为汉语，2为英文，3德语，4为法语，5为日语
	void LoadLanguageInfoList(int language_type);
private:

};

//#endif //GETLANGUAGECLS
