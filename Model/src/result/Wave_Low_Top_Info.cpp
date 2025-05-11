#include "Wave_Low_Top_Info.h"

int Wave_Low_Top_Info::getWaveType() const
{
	return _wave_type;
}
void Wave_Low_Top_Info::setWaveType(int wave_type)
{
	_wave_type = wave_type;
}

int Wave_Low_Top_Info::getSum() const
{
	return _sum;
}
void Wave_Low_Top_Info::setSum(int sum)
{
	_sum = sum;
}


QVector<int> Wave_Low_Top_Info::getIndexVector() const
{
	return _index_vector ;
}
void Wave_Low_Top_Info::setIndexVector(QVector<int> index_vector)
{
	_index_vector = index_vector;
}