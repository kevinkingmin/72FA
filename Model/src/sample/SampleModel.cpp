#include "SampleModel.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>

SampleModel::SampleModel():
    _pkid(0)
  ,_Id("")
  ,_sampleNo("1")
  ,_barcode("")
  ,_PatientName("")
  ,_SexID(0)
  ,_Age(0)
  ,_AgeUnitID(0)
  ,_birthday(0)
  ,_bloodType("")
  ,_AnamnesisNO("")
  ,_wardName("")
  ,_BedNo("")
  ,_departmentName("")
  ,_cupType(-1)
  ,_samplePos(0)
  ,_diagnosis("")
  ,_errorFlag("")
  ,_skipFlag("")
  ,_stateFlag(0)
  ,_isDelete(0)
  ,_testTime(0)
  ,_testUser("")
  ,_intPreField(-1)
  ,_strPreField("")
  , _articleNo("")
  , _paperId(0)
  ,_testId("")
  ,_paperPos(0)
  ,_test_batch(1)
  ,_remark("")
  ,_checkerName("")
{
}

QString SampleModel::getId() const
{
    return _Id;
}

void SampleModel::setId(const QString &Id)
{
    _Id = Id;
}

QString SampleModel::getSampleNo() const
{
    return _sampleNo;
}

void SampleModel::setSampleNo(const QString &sampleNo)
{
    _sampleNo = sampleNo;
}

QString SampleModel::getBarcode() const
{
    return _barcode;
}

void SampleModel::setBarcode(const QString &barcode)
{
    _barcode = barcode;
}

QString SampleModel::getPatientName() const
{
    return _PatientName;
}

void SampleModel::setPatientName(const QString &PatientName)
{
    _PatientName = PatientName;
}

int SampleModel::getSexID() const
{
    return _SexID;
}

void SampleModel::setSexID(int SexID)
{
    _SexID = SexID;
}

int SampleModel::getAge() const
{
    return _Age;
}

void SampleModel::setAge(int Age)
{
    _Age = Age;
}

int SampleModel::getAgeUnitID() const
{
    return _AgeUnitID;
}

void SampleModel::setAgeUnitID(int AgeUnitID)
{
    _AgeUnitID = AgeUnitID;
}

qint64 SampleModel::getBirthday() const
{
    return _birthday;
}

void SampleModel::setBirthday(const qint64 &birthday)
{
    _birthday = birthday;
}

QString SampleModel::getBloodType() const
{
    return _bloodType;
}

void SampleModel::setBloodType(const QString &bloodType)
{
    _bloodType = bloodType;
}

QString SampleModel::getAnamnesisNO() const
{
    return _AnamnesisNO;
}

void SampleModel::setAnamnesisNO(const QString &AnamnesisNO)
{
    _AnamnesisNO = AnamnesisNO;
}

QString SampleModel::getWardName() const
{
    return _wardName;
}

void SampleModel::setWardName(const QString &wardName)
{
    _wardName = wardName;
}

QString SampleModel::getBedNo() const
{
    return _BedNo;
}

void SampleModel::setBedNo(const QString &BedNo)
{
    _BedNo = BedNo;
}

QString SampleModel::getDepartmentName() const
{
    return _departmentName;
}

void SampleModel::setDepartmentName(const QString &departmentName)
{
    _departmentName = departmentName;
}

int SampleModel::getCupType() const
{
    return _cupType;
}

void SampleModel::setCupType(int cupType)
{
    _cupType = cupType;
}

int SampleModel::getSamplePos() const
{
    return _samplePos;
}

void SampleModel::setSamplePos(int samplePos)
{
    _samplePos = samplePos;
}

QString SampleModel::getDiagnosis() const
{
    return _diagnosis;
}

void SampleModel::setDiagnosis(const QString &diagnosis)
{
    _diagnosis = diagnosis;
}

QString SampleModel::getErrorFlag() const
{
    return _errorFlag;
}

void SampleModel::setErrorFlag(const QString &errorFlag)
{
    _errorFlag = errorFlag;
}

QString SampleModel::getSkipFlag() const
{
    return _skipFlag;
}

void SampleModel::setSkipFlag(const QString &skipFlag)
{
    _skipFlag = skipFlag;
}

int SampleModel::getStateFlag() const
{
    return _stateFlag;
}

void SampleModel::setStateFlag(int stateFlag)
{
    _stateFlag = stateFlag;
}

int SampleModel::getTestBatch() const
{
	return _test_batch;
}

void SampleModel::setTestBatch(int test_batsh)
{
	_test_batch = test_batsh;
}

bool SampleModel::getIsDelete() const
{
    return _isDelete;
}

void SampleModel::setIsDelete(bool isDelete)
{
    _isDelete = isDelete;
}

qint64 SampleModel::getTestTime() const
{
    return _testTime;
}

void SampleModel::setTestTime(const qint64 &testTime)
{
    _testTime = testTime;
}

QString SampleModel::getTestUser() const
{
    return _testUser;
}

void SampleModel::setTestUser(const QString &testUser)
{
    _testUser = testUser;
}

int SampleModel::getIntPreField() const
{
    return _intPreField;
}

void SampleModel::setIntPreField(int intPreField)
{
    _intPreField = intPreField;
}

QString SampleModel::getStrPreField() const
{
    return _strPreField;
}

void SampleModel::setStrPreField(const QString &strPreField)
{
    _strPreField = strPreField;
}

void SampleModel::setArticleNo(const QString & articleNo)
{
	_articleNo = articleNo;
}

QString SampleModel::getArticleNo() const
{
	return _articleNo;
}

void SampleModel::setPaperId(int paper_id)
{
	_paperId = paper_id;
}

int SampleModel::getPaperId() const
{
	return _paperId;
}

void SampleModel::setPaperPos(int paper_pos)
{
	_paperPos = paper_pos;
}

int SampleModel::getPaperPos() const
{
	return _paperPos;
}

void SampleModel::setTestId(QString testId)
{
	_testId = testId;
}

QString SampleModel::getTestId() const
{
	return _testId;
}


bool SampleModel::operator==(SampleModel &it) const
{
    if(
            _pkid           == it._pkid           &&
            _Id             == it._Id             &&
            _sampleNo       == it._sampleNo       &&
            _PatientName    == it._PatientName    &&
            _SexID          == it._SexID          &&
            _Age            == it._Age            &&
            _AgeUnitID      == it._AgeUnitID      &&
            _birthday       == it._birthday       &&
            _bloodType      == it._bloodType      &&
            _AnamnesisNO    == it._AnamnesisNO    &&
            _wardName       == it._wardName       &&
            _BedNo          == it._BedNo          &&
            _departmentName == it._departmentName &&
            _cupType        == it._cupType        &&
            _samplePos      == it._samplePos      &&
			_articleNo      == it._articleNo      &&
		    _testId         == it._testId         &&
		    _paperId        == it._paperId        &&
		    _paperPos       == it._paperPos       &&
            _diagnosis      == it._diagnosis
            )
    {
        return true;
    }
    return false;
}

QString SampleModel::getRemark() const
{
    return _remark;
}

void SampleModel::setRemark(const QString &remark)
{
    _remark = remark;
}

QString SampleModel::getCheckerName() const
{
    return _checkerName;
}

void SampleModel::setCheckerName(const QString &checkerName)
{
    _checkerName = checkerName;
}

int SampleModel::getPkid() const
{
    return _pkid;
}

void SampleModel::setPkid(int pkid)
{
    _pkid = pkid;
}

