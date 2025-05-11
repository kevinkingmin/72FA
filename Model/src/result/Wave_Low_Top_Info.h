#ifndef	WAVELOWTOPINFOMODEL_H
#define WAVELOWTOPINFOMODEL_H
#include <QString>
#include <QVector>
#include "../Model.h"
class  MODELSHARED_EXPORT Wave_Low_Top_Info
{
public:
	//0上升沿，1平沿，2，下降沿
	int getWaveType() const;
	void setWaveType(int wave_type);
	//数量
	int getSum() const;
	void setSum(int sum);
	//满足条件的下标
	QVector<int> getIndexVector() const;
	void setIndexVector(QVector<int> index_vector);

private:
	int _wave_type;                            //0上升沿，1平沿，2，下降沿
	int _sum;                                      //数量
	QVector<int> _index_vector;      //满足条件的下标
};

#endif 