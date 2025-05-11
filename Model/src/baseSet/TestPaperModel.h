#ifndef TESTPAPERMODEL_H
#define TESTPAPERMODEL_H
#include <QObject>
#include "../Model.h"

class MODELSHARED_EXPORT TestPaperModel
{
public:
    TestPaperModel();

    int getID() const;
    void setID(int ID);

    QString getPaperName() const;
    void setPaperName(const QString &PaperName);

    int getCompanyId() const;
    void setCompanyId(int companyId);

    int getTotalNumber() const;
    void setTotalNumber(int TotalNumber);

    int getItemNumber() const;
    void setItemNumber(int itemNumber);

    int getTestPaparLenght() const;
    void setTestPaparLenght(int TestPaparLenght);

    int getFuncPosition() const;
    void setFuncPosition(int FuncPosition);

    int getTestAeaLenght() const;
    void setTestAeaLenght(int TestAeaLenght);

    int getUsageV() const;
    void setUsageV(int usageV);

	int getSort_idx() const;
	void setSort_idx(int sort_idx);

	QString getDefaultBGRGB() const;
	void setDefaultBGRGB(const QString &defaultBGRGB);

	QString getBGRGB() const;
	void setBGRGB(const QString &BGRGB);

	QString getArticleNo() const;
	void setArticleNo(const QString &articleNo);

	bool getIsDelete() const;
	void setIsDelete(bool isDelete);


private:
	int _ID;
	QString _PaperName;
	int _companyId;
	int _TotalNumber;
	int _itemNumber;
	int _TestPaparLenght;
	int _FuncPosition;
	int _TestAeaLenght;
	int _usageV;
	int _sort_idx;
	QString _defaultBGRGB;
	QString _BGRGB;
	bool _isDelete;
	QString _articleNo;
};

#endif // TESTPAPERMODEL_H
