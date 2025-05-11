#pragma once

#include <winnt.h>
#include <profileapi.h>

//ms级精确定时
class MyTimer
{
private:
	long long _freq;
	LARGE_INTEGER _begin;
	LARGE_INTEGER _end;
	long costTime; //花费的时间

public:
	MyTimer()
	{
		LARGE_INTEGER tmp;
		QueryPerformanceFrequency(&tmp);
		_freq = tmp.QuadPart;
		costTime = 0;
	}

	void start()
	{
		QueryPerformanceCounter(&_begin); // 获得初始值
	}

	long long timeElapsed()
	{
		QueryPerformanceCounter(&_end);
		costTime = (long long)((_end.QuadPart - _begin.QuadPart) * 1000000 / _freq);
		return costTime;
	}
};