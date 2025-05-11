#ifndef	WAVELOWTOPINFOMODEL_H
#define WAVELOWTOPINFOMODEL_H
#include <QString>
#include <QVector>

class  Wave_Low_Top_Info
{
public:
	int getWaveType() const;
	void setWaveType(int wave_type);
	int getSum() const;
	void setSum(int sum);
	QVector<int> getIndexVector() const;
	void setIndexVector(QVector<int> index_vector);

private:
	int _wave_type;               
	int _sum;      
	QVector<int> _index_vector;   
};

#endif 