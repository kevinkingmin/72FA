#ifndef BATCHADDSAMPLETMODEL_H
#define BATCHADDSAMPLETMODEL_H
#include "../Model.h"
#include <QString>
#include <QVector>
#include <qmap.h>

class MODELSHARED_EXPORT  BatchAddSampleModel
{
public:
	BatchAddSampleModel();
	//样本号对应膜条数量
	QMap<int, int> _sample_id_paper_number_map;
	QString getPaperName() const;
	void setPaperName(const QString &Id);
	QString getSampleNo() const;
	void setSampleNo(QString samplePos);

	int getPaperNumber();
	void setPaperNumber(int number);

	int getNo() const;
	void setNo(int no);



private:
	//样本编号
	QString _sampleNo;
	QString _paperName;
	//样本对应膜条数量，部分样本会有复孔情况
	int _paperNumber;
	//编号
	int _no;

};
#endif // BATCHADDSAMPLETMODEL_H
