#pragma once

#include <winnt.h>
#include <profileapi.h>

//ms����ȷ��ʱ
class MyTimer
{
private:
	long long _freq;
	LARGE_INTEGER _begin;
	LARGE_INTEGER _end;
	long costTime; //���ѵ�ʱ��

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
		QueryPerformanceCounter(&_begin); // ��ó�ʼֵ
	}

	long long timeElapsed()
	{
		QueryPerformanceCounter(&_end);
		costTime = (long long)((_end.QuadPart - _begin.QuadPart) * 1000000 / _freq);
		return costTime;
	}
};