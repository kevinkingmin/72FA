#ifndef SAMPLETESTMODEL_H
#define SAMPLETESTMODEL_H
#include "../Model.h"
#include <QString>
#include <QVector>

class MODELSHARED_EXPORT SampleTestModel
{
public:
    struct TestResultSct
    {
        int    itemId;
        int    orderNo;
        int    position;//项目所在模条的物理位置，像素位置
        double testGrayValue;
        double manuGrayValue;
        TestResultSct():
            itemId(0)
          ,orderNo(0)
          ,position(0)
          ,testGrayValue(0)
          ,manuGrayValue(0)
        {}
    };
    SampleTestModel();

    quint64 getId() const;
    void setId(const quint64 &Id);

	QString getSolutionName() const;
	void setSolutionName(QString solutionNam);

	QString getManageName() const;
	void setManageName(QString manageName);


    quint64 getSampleId() const;
    void setSampleId(const quint64 &sampleId);


    int getPaperId() const;
    void setPaperId(int paperId);

    int getSlotPos() const;
    void setSlotPos(int slotPos);


	//double _coefficient;
	//double _testGrayValue;
	//QString _testResult;

	//qint64 _testTime;
	//int _runStatus;

	//bool _isDelete;
	//QString _remark;
	//QString articleNo;

	QString getProjectName() const;
	void setProjectName(QString projectName);

    double getCutGrayValue() const;
    void setCutGrayValue(double cutGrayValue);

	double getCoefficient() const;
	void setCoefficient(double coefficient);

	double getTestGrayValue() const;
	void setTestGrayValue(double testGrayValue);

	QString getTestResult() const;
	void setTestResult(QString testResult);


    qint64 getTestTime() const;
    void setTestTime(const qint64 &testTime);

	int getRunStatus() const;
	void setRunStatus(int runStatus);

    bool getIsDelete() const;
    void setIsDelete(bool isDelete);

    QString getRemark() const;
    void setRemark(const QString &remark);

	QString getArticleNo() const;
	void setArticleNo(QString articleNo);

	QString getTestId() const;
	void setTestId(QString testId);


	int getSamplePos() const;
	void setSamplePos(int samplePos);

    //QVector<TestResultSct> getResultVect() const;
    //void setResultVect(QString strResult);
    //void setResultVect(QVector<TestResultSct> vect);

    QString vectToStr(QVector<TestResultSct> vect);
    QVector<TestResultSct> strToVect(const QString &resultStr);
private:
    quint64 _Id;
	QString _testId;
	QString _solutionName;
	QString _manageName;
    quint64 _sampleId;
    int _paperId;
    int _slotPos;
	int _samplePos;
	QString _projectName;
    double _cutGrayValue;
	double _coefficient;
	double _testGrayValue;
	QString _testResult;
    qint64 _testTime;
	int _runStatus;
    bool _isDelete;
    QString _remark;
	QString _articleNo;
    QVector<TestResultSct> _resultVect;
};

#endif // SAMPLETESTMODEL_H
