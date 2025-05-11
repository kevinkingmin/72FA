#include "JudgeRules.h"
JudgeRules::JudgeRules()
    :_pkid(0)
    ,_RulesId(0)
    ,_GrayValue(0)
    ,_GrayWord("")
    ,_convertCoff(0)
    ,_convertAdd(0)
{

}

int JudgeRules::getpkid() const
{
	return _pkid;
}
void JudgeRules::setpkid(int pkid)
{
	_pkid = pkid;
}
int JudgeRules::getRulesId() const
{
	return _RulesId;
}
void JudgeRules::setRulesId(int rulesId)
{
	_RulesId = rulesId;
}

double JudgeRules::getGrayValue() const
{
	return _GrayValue;
}
void JudgeRules::setGrayValue(double GrayValue)
{
	_GrayValue = GrayValue;
}

QString JudgeRules::getGrayWord() const
{
	return _GrayWord;
}
void JudgeRules::setGrayWord(QString GrayWord)
{
	_GrayWord = GrayWord;
}

double JudgeRules::getConvertCoff() const
{
    return _convertCoff;
}

void JudgeRules::setConvertCoff(double convertCoff)
{
    _convertCoff = convertCoff;
}

double JudgeRules::getConvertAdd() const
{
    return _convertAdd;
}

void JudgeRules::setConvertAdd(double convertAdd)
{
    _convertAdd = convertAdd;
}
