//#ifndef GETLANGUAGECLS
//#define GETLANGUAGECLS
#include <list>
#include "LanguageInfo.h"
#include <string>//������C++ͷ�ļ�
#include <string.h>
#include <iostream>
using namespace std;

class GetLanguageCls
{
public:
	GetLanguageCls();
	~GetLanguageCls();

public:

	list<LanguageInfo> g_languageInfo_list;      //�����������
public:
	QString GetLanguagInfo(QString id);
	///1Ϊ���2ΪӢ�ģ�3���4Ϊ���5Ϊ����
	void LoadLanguageInfoList(int language_type);
private:

};

//#endif //GETLANGUAGECLS
