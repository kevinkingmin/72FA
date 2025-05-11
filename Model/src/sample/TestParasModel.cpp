#include "TestParasModel.h"

TestParasModel::TestParasModel()
    :_testId("")
    ,_sampleId("")
    ,_paperId(0)
    ,_cupType(0)
    ,_samplePos(0)
    ,_slotPos(0)
{
}

QString TestParasModel::getTestId() const
{
    return _testId;
}

void TestParasModel::setTestId(const QString &testId)
{
    _testId = testId;
}

QString TestParasModel::getSampleId() const
{
    return _sampleId;
}

void TestParasModel::setSampleId(const QString &sampleId)
{
    _sampleId = sampleId;
}

int TestParasModel::getPaperId() const
{
    return _paperId;
}

void TestParasModel::setPaperId(int paperId)
{
    _paperId = paperId;
}

int TestParasModel::getCupType() const
{
    return _cupType;
}

void TestParasModel::setCupType(int cupType)
{
    _cupType = cupType;
}

int TestParasModel::getSamplePos() const
{
    return _samplePos;
}

void TestParasModel::setSamplePos(int samplePos)
{
    _samplePos = samplePos;
}

int TestParasModel::getSlotPos() const
{
    return _slotPos;
}

void TestParasModel::setSlotPos(int slotPos)
{
    _slotPos = slotPos;
}
