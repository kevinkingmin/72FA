#ifndef TESTPARASMODEL_H
#define TESTPARASMODEL_H
#include "../Model.h"
#include <QObject>

class MODELSHARED_EXPORT TestParasModel
{
public:
    TestParasModel();
	QString getTestId() const;
    void setTestId(const QString &testId);

	QString getSampleId() const;
    void setSampleId(const QString &sampleId);

    int getPaperId() const;
    void setPaperId(int paperId);

    int getCupType() const;
    void setCupType(int cupType);

    int getSamplePos() const;
    void setSamplePos(int samplePos);

    int getSlotPos() const;
    void setSlotPos(int slotPos);

private:
	QString _testId;
	QString _sampleId;
    int _paperId;
    int _cupType;
    int _samplePos;
    int _slotPos;
};

#endif // TESTPARASMODEL_H
