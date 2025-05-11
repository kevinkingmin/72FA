#include "Mythread.h"
#include <qdebug.h>
#include <QThread>
#include <QDateTime>
#include <QStyle>
#include <QMessageBox>
#include <QTimer>
#include <QProgressBar>
#include <QDateTime>
#include <QStyle>
#include <QMessageBox>
#include <QTimer>
#include <QButtonGroup>
#include <QVariant>
#include "../Include/Instrument/Instrument.h"

Mythread::Mythread(QObject *parent) : QThread(parent), _instr(Instrument::instance())
{

}

void Mythread::run()
{
	while (true)
	{
		while (m_flag)
		{
			int pos = 1;
            //_instr->moveToPhotoPos(pos);
			m_flag = false;
		}
		Sleep(1000);
	}
}

void Mythread::StartSend(bool flage)
{
	m_flag = true;
	//m_tsw = p;//此行代码就使得w有了内存，而且和主线程对象地址一样
}

void Mythread::ChangeFlage(bool flage)
{
	m_flag = true;
}

