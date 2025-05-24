#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H
#include "../Model.h"
#include <QString>
#include <QVector>
#include <QStringList>
#include <QMap>

class MODELSHARED_EXPORT SampleModel
{
public:

    SampleModel();
	QString getId() const;
    void setId(const QString &Id);
    QString getSampleNo() const;
    void setSampleNo(const QString &sampleNo);
    QString getBarcode() const;
    void setBarcode(const QString &barcode);
    QString getPatientName() const;
    void setPatientName(const QString &PatientName);
    int getSexID() const;
    void setSexID(int SexID);
    int getAge() const;
    void setAge(int Age);
    int getAgeUnitID() const;
    void setAgeUnitID(int AgeUnitID);
    qint64 getBirthday() const;
    void setBirthday(const qint64 &birthday);
    QString getBloodType() const;
    void setBloodType(const QString &bloodType);
    QString getAnamnesisNO() const;
    void setAnamnesisNO(const QString &AnamnesisNO);
    QString getWardName() const;
    void setWardName(const QString &wardName);
    QString getBedNo() const;
    void setBedNo(const QString &BedNo);
    QString getDepartmentName() const;
    void setDepartmentName(const QString &departmentName);
    int getCupType() const;
    void setCupType(int cupType);
    int getSamplePos() const;
    void setSamplePos(int samplePos);
    QString getDiagnosis() const;
    void setDiagnosis(const QString &diagnosis);
    QString getErrorFlag() const;
    void setErrorFlag(const QString &errorFlag);
    QString getSkipFlag() const;
    void setSkipFlag(const QString &skipFlag);
    int getStateFlag() const;
    void setStateFlag(int stateFlag);

	int getTestBatch() const;
	void setTestBatch(int test_batsh);

    bool getIsDelete() const;
    void setIsDelete(bool isDelete);
    qint64 getTestTime() const;
    void setTestTime(const qint64 &testTime);
    QString getTestUser() const;
    void setTestUser(const QString &testUser);
    int getIntPreField() const;
    void setIntPreField(int intPreField);
    QString getStrPreField() const;
    void setStrPreField(const QString &strPreField);
	QString getArticleNo() const;
	void setArticleNo(const QString &articleNo);
	QString getTestId() const;
	void setTestId(QString testId);
	int getPaperId() const;
	void setPaperId(int paper_id);
	int getPaperPos() const;
	void setPaperPos(int paper_pos);
    bool operator==(SampleModel &it)const;
    QString getRemark() const;
    void setRemark(const QString &remark);

    QString getCheckerName() const;
    void setCheckerName(const QString &checkerName);

    int getPkid() const;
    void setPkid(int pkid);

private:
    int        _pkid;
    QString    _Id;
    QString    _testId;
    QString    _sampleNo;
    QString    _barcode;
    QString    _PatientName;
    int        _SexID;
    int        _Age;
    int        _AgeUnitID;
    qint64     _birthday;
    QString    _bloodType;
    QString    _AnamnesisNO;
    QString    _wardName;
    QString    _BedNo;
    QString    _departmentName;
    int        _cupType;
    int        _samplePos;
    QString    _diagnosis;
    QString    _errorFlag;
    QString    _skipFlag;
    int        _stateFlag;
    int        _test_batch;
    bool       _isDelete;
    qint64     _testTime;
    QString    _testUser;
    int        _intPreField;
    QString    _strPreField;
	QString    _articleNo;
	int        _paperId;
	int        _paperPos;
    QString    _remark;
    QString    _checkerName;
};

#endif // SAMPLEMODEL_H
