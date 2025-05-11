#include "..\Include\Precomp\precompile.h"
#include "BatchAddSampleModel.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>

BatchAddSampleModel::BatchAddSampleModel()
	: _paperName("")
	, _sampleNo("1")
	, _paperNumber(1)
	, _no(1)
{
}
QString BatchAddSampleModel::getPaperName() const
{
	return _paperName;
}

void BatchAddSampleModel::setPaperName(const QString &paperName)
{
	_paperName = paperName;
}

QString BatchAddSampleModel::getSampleNo() const
{
	return _sampleNo;
}

void BatchAddSampleModel::setSampleNo(QString samplePos)
{
	_sampleNo = samplePos;
}

int BatchAddSampleModel::getNo() const
{
	return _no;
}

void BatchAddSampleModel::setNo(int no)
{
	_no = no;
}



int BatchAddSampleModel::getPaperNumber()
{
	return _paperNumber;
}

void BatchAddSampleModel::setPaperNumber(int number)
{
	_paperNumber = number;
}
