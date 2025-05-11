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
	//�����Ŷ�ӦĤ������
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
	//�������
	QString _sampleNo;
	QString _paperName;
	//������ӦĤ�������������������и������
	int _paperNumber;
	//���
	int _no;

};
#endif // BATCHADDSAMPLETMODEL_H
