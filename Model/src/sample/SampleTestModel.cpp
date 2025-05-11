#include "SampleTestModel.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>

SampleTestModel::SampleTestModel()
    :_Id("")
	,_solutionName("")
	,_manageName("")
    ,_sampleId("")
	, _projectName("")
    ,_paperId(0)
	,_cutGrayValue(0)
	,_coefficient(0)
	,_testGrayValue(0)
	,_runStatus(1)
	,_testResult("")
	,_articleNo("")
    ,_paperPos(0)
    ,_testTime(0)
    ,_isDelete(false)
	,_cupType(0)
    ,_remark("")
{
}

QString SampleTestModel::getId() const
{
    return _Id;
}

void SampleTestModel::setId(const QString &Id)
{
    _Id = Id;
}

QString SampleTestModel::getSampleId() const
{
    return _sampleId;
}

void SampleTestModel::setSampleId(const QString &sampleId)
{
    _sampleId = sampleId;
}

int SampleTestModel::getPaperId() const
{
    return _paperId;
}

void SampleTestModel::setPaperId(int paperId)
{
    _paperId = paperId;
}

int SampleTestModel::getSlotPos() const
{
    return _paperPos;
}

void SampleTestModel::setSlotPos(int slotPos)
{
    _paperPos = slotPos;
}

int SampleTestModel::getSamplePos() const
{
	return _samplePos;
}

void SampleTestModel::setSamplePos(int samplePos)
{
	_samplePos = samplePos;
}

double SampleTestModel::getCutGrayValue() const
{
    return _cutGrayValue;
}

void SampleTestModel::setCutGrayValue(double cutGrayValue)
{
    _cutGrayValue = cutGrayValue;
}

qint64 SampleTestModel::getTestTime() const
{
    return _testTime;
}

void SampleTestModel::setTestTime(const qint64 &testTime)
{
    _testTime = testTime;
}

bool SampleTestModel::getIsDelete() const
{
    return _isDelete;
}

void SampleTestModel::setIsDelete(bool isDelete)
{
    _isDelete = isDelete;
}

QString SampleTestModel::getRemark() const
{
    return _remark;
}

void SampleTestModel::setRemark(const QString &remark)
{
    _remark = remark;
}

QString SampleTestModel::getSolutionName() const
{
	return _solutionName;
}
void SampleTestModel::setSolutionName(QString solutionName)
{
	_solutionName = solutionName;
}

QString SampleTestModel::getManageName() const
{
	return _manageName;
}
void SampleTestModel::setManageName(QString manageName)
{
	_manageName = manageName;
}

QString SampleTestModel::getProjectName() const
{
	return _projectName;
}
void SampleTestModel::setProjectName(QString projectName)
{
	_projectName = projectName;
}

double SampleTestModel::getCoefficient() const
{
	return _coefficient;
}

void SampleTestModel::setCoefficient(double coefficient)
{
	_coefficient = coefficient;
}

double SampleTestModel::getTestGrayValue() const
{
	return _testGrayValue;
}
void SampleTestModel::setTestGrayValue(double testGrayValue)
{
	_testGrayValue = testGrayValue;
}
//double SampleTestModel::getCutGrayValue() const
//{
//	return _cutGrayValue;
//}
//
//void SampleTestModel::setCutGrayValue(double cutGrayValue)
//{
//	_cutGrayValue = cutGrayValue;
//}

int SampleTestModel::getRunStatus() const
{
	return _runStatus;
}
void SampleTestModel::setRunStatus(int runStatus)
{
	_runStatus = runStatus;
}

QString SampleTestModel::getArticleNo() const
{
	return _articleNo;
}
void SampleTestModel::setArticleNo(QString articleNo)
{
	_articleNo = articleNo;
}

QString SampleTestModel::getPatientName() const
{
	return _patientName;
}
void SampleTestModel::setPatientName(QString patientName)
{
	_patientName = patientName;
}

QString SampleTestModel::getTestResult() const {
	return _testResult;
}
void SampleTestModel::setTestResult(QString testResult)
{
	_testResult = testResult;
}

QString SampleTestModel::getTestId() const {
	return _testId;
}
void SampleTestModel::setTestId(QString testId)
{
	_testId = testId;
}

int SampleTestModel::getCupType() const
{
	return _cupType;
}
void SampleTestModel::setCupType(int cup_type)
{
	_cupType = cup_type;
}

//QVector<SampleTestModel::TestResultSct> SampleTestModel::getResultVect() const
//{
//    return _resultVect;
//}
//
//void SampleTestModel::setResultVect(QString strResult)
//{
//    auto vect =strToVect(strResult);
//    _resultVect.swap(vect);
//}
//
//void SampleTestModel::setResultVect(QVector<SampleTestModel::TestResultSct> vect)
//{
//    _resultVect.swap(vect);
//}

QString SampleTestModel::vectToStr(QVector<TestResultSct> vect)
{
    if(vect.empty())return "";
    QJsonArray array;
    int i=0;
    for(auto it:vect)
    {
        QJsonObject obj;
        obj.insert("itemId",it.itemId);
        obj.insert("orderNo",it.orderNo);
        obj.insert("position",it.position);
        obj.insert("testGrayValue",it.testGrayValue);
        obj.insert("manuGrayValue",it.manuGrayValue);
        array.insert(i,obj);
        i++;
    }
    QJsonDocument doc;
    doc.setArray(array);
    QString jsonStr=doc.toJson(QJsonDocument::Compact);
    return jsonStr;
}

QVector<SampleTestModel::TestResultSct> SampleTestModel::strToVect(const QString &resultStr)
{
    QVector<TestResultSct>vect;
    if(resultStr.isNull() || resultStr.isEmpty())
        return vect;
    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(resultStr.toUtf8(), &parse_error);
    if (document.isNull() ||(parse_error.error != QJsonParseError::NoError))
        return vect;
    auto arr=document.array();
    for(auto it:arr)
    {
        TestResultSct m;
        m.itemId=it.toObject().value("itemId").toInt();
        m.orderNo=it.toObject().value("orderNo").toInt();
        m.position=it.toObject().value("position").toInt();
        m.testGrayValue=it.toObject().value("position").toDouble();
        m.manuGrayValue=it.toObject().value("manuGrayValue").toDouble();
        vect.push_back(m);
    }
    return vect;
}
