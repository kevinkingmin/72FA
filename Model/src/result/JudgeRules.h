#ifndef	JUDGERULESMODEL_H
#define JUDGERULESMODEL_H
#include <QString>
#include "../Model.h"
class MODELSHARED_EXPORT JudgeRules
{
public:
    JudgeRules();

	int getpkid() const;
	void setpkid(int pkid);

	int getRulesId() const;
	void setRulesId(int rulesId);

	double getGrayValue() const;
	void setGrayValue(double grayValue);

	QString getGrayWord() const;
	void setGrayWord(QString grayWord);

    double getConvertCoff() const;
    void setConvertCoff(double convertCoff);

    double getConvertAdd() const;
    void setConvertAdd(double convertAdd);

private:
    int     _pkid;
    int     _RulesId;
    double  _GrayValue;
	QString _GrayWord;
    double  _convertCoff;
    double  _convertAdd;
};
#endif 

