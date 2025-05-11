#ifndef REAGENTMODEL_H
#define REAGENTMODEL_H
#include <QString>
#include "../Model.h"

class MODELSHARED_EXPORT ReagentModel
{
public:
    ReagentModel();
    int getID() const;
    void setID(int ID);

    QString getReagentName() const;
    void setReagentName(const QString &reagentName);
    //PaperId
	int getPaperId() const;
	void setPaperId(int val);

	QString getSpentTime() const;
	void setSpentTime(const QString &spentTime);

    int getCompanyID() const;
    void setCompanyID(int companyID);

    bool getIsNoDrip() const;
    void setIsNoDrip(bool IsNoDrip);

    bool getIsSkimp() const;
    void setIsSkimp(bool IsSkimp);

    bool getIsNeedPrepare() const;
    void setIsNeedPrepare(bool IsNeedPrepare);

    int getPumpNo() const;
    void setPumpNo(int PumpNo);

	float getFluidMeasure() const;
	void setFluidMeasure(float fluidMeasure);

	float getFluidMeasureSmall() const;
	void setFluidMeasureSmall(float fluidMeasureSmall);

private:
    int _ID;
    QString _reagentName;
    int _paperId;
    int _companyID;
    bool _IsNoDrip;
    bool _IsSkimp;
    bool _IsNeedPrepare;
    int _PumpNo;
	QString _spentTime;
	///大充灌液量
	float _fluidMeasure;
	///小充灌液量
	float _fluidMeasureSmall;
};

#endif // REAGENTMODEL_H
