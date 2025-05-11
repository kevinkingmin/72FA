#pragma once
#include <qthread.h>
#include "TestSampleWidget.h"
#pragma execution_character_set("utf-8")

class TestSampleWidget;
class RunPaperPosThread :public QThread
{
	Q_OBJECT
protected:
	void run() Q_DECL_OVERRIDE;  
public:
	RunPaperPosThread();
	TestSampleWidget *m_tsw;

private slots:
	void getaddress(TestSampleWidget *p);
public:
	bool m_run_flage1 = true;
private:
	int number;
signals:
	void UpdateSignal(int num);
public slots:

};
