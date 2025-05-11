#include "LanguageInfo.h"
#include <iostream>
#include <list>



LanguageInfo::LanguageInfo()
{
}

LanguageInfo::LanguageInfo(QString i, QString content1)
{
	id = i;
	content = content1;
}

LanguageInfo::~LanguageInfo()
{
}

void LanguageInfo::show()
{
	//std::cout << "id : " << id << "     name : " << content << std::endl;
}

bool LanguageInfo::operator==(const LanguageInfo &s)
{
	if (this->id == s.id)
	{
		return true;
	}
	else
	{
		return false;
	}
}
