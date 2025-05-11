#ifndef	WAVELOWTOPINFOMODEL_H
#define WAVELOWTOPINFOMODEL_H
#include <QString>
#include <QVector>
#include "../Model.h"
class  MODELSHARED_EXPORT Wave_Low_Top_Info
{
public:
	//0�����أ�1ƽ�أ�2���½���
	int getWaveType() const;
	void setWaveType(int wave_type);
	//����
	int getSum() const;
	void setSum(int sum);
	//�����������±�
	QVector<int> getIndexVector() const;
	void setIndexVector(QVector<int> index_vector);

private:
	int _wave_type;                            //0�����أ�1ƽ�أ�2���½���
	int _sum;                                      //����
	QVector<int> _index_vector;      //�����������±�
};

#endif 