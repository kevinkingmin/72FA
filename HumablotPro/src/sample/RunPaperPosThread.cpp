#include "..\Include\Precomp\precompile.h"
#include "ui_TestSampleWidget.h"
#include "RunPaperPosThread.h"
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
#include "../Include/Analysis/analysis.h"
#include "../Include/Model/sample/SampleTestModel.h"
#include "../sample/model/AddSampleVModel.h"
#include "../Include/BLL/sample/SampleBLL.h"
#include "../Include/Model/sample/SampleTestModel.h"
#include "../Include/BLL/baseSet/TestPaperBLL.h"
#include "../Include/BLL/baseSet/ItemBll.h"
#include "../Include/Model/baseSet/TestPaperModel.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/Utilities/log.h"
#include "../Include/Model/result/TestResultModel.h"
#include "../Include/Analysis/analysis.h"
#include "src/Camera/CameraControl.h"

void RunPaperPosThread::run()
{
	if (m_tsw->_sampleTestTpVect.isEmpty())
		return;
	CameraControl m_cameraControl(m_tsw);
   Instrument *_instrument = Instrument::instance();
	bool res = m_cameraControl.OpenCamera();
	if (res == false)
	{
		m_cameraControl.CloseCamera();
		m_cameraControl.OpenCamera();
		while (true)
		{
			m_cameraControl.CloseCamera();
			res = m_cameraControl.OpenCamera();
			if (res)
			{
				goto STARTDEALPIC;
			}
		}
		return;
	}
	STARTDEALPIC:
	Analysis m_analysis;
    //_instrument->lightControl(12, 1);
    Sleep(600000);
	int i = 0;
	QList<QString> pic_file_path_list;
    //for(int i=m_tsw->_sampleTestTpVect.size()-1;i>0;i--)
    for (auto tp : m_tsw->_sampleTestTpVect)
	{
		auto testVect = std::get<1>(tp);
		bool run_status = true;
		for (auto it : testVect)
		{          
			QString a = it->getArticleNo();
			//todo
			uchar pos = it->getSlotPos();
			int paper_id = it->getPaperId();
			QString test_id =  it->getTestId();//it->getSampleId();
			QString id = it->getId();
			QString pic_file_name = it->getTestId();
			QString solution_name = it->getSolutionName();
			QString patiant_name = it->getPatientName();
			while (m_run_flage1)
			{
                //run_status = Instrument::instance()->moveToPhotoPos(pos);
				Sleep(2800);
				if (run_status)
				{
					goto DEALPIC;
				}
			}
			DEALPIC:
			m_cameraControl.CreateOneImage(test_id, paper_id, pic_file_name);
			pic_file_path_list.push_back(pic_file_name);
			//todo
            m_analysis.AnalysisMothed(pic_file_name, paper_id, test_id, solution_name, patiant_name);
			i++;      
		}
	}
	number = i;
    //_instrument->lightControl(12, 0);
	m_cameraControl.CloseCamera();
	emit UpdateSignal(number);
	this->quit();
}


void RunPaperPosThread::getaddress(TestSampleWidget *p)
{
	m_tsw = p;
}
RunPaperPosThread::RunPaperPosThread()
{
}
