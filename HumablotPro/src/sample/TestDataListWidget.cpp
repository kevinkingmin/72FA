#include "TestDataListWidget.h"
#include "ui_TestDataListWidget.h"
#include <QMessageBox>
#include "model/TestDataListVModel.h"
#include "../Include/Model/sample/SampleModel.h"
#include "../Include/Model/sample/SampleTestModel.h"
#include "qstandarditemmodel.h"
#include <QMessageBox>
#include <QTimer>
#include <QButtonGroup>
#include <QVariant>
#include <QSqlQuery>
#include "src/comm/ObjectTr.h"
#include "src/comm/CustomButton.h"
#include "src/comm/CustomLabel1.h"
#include "../Include/BLL/sample/SampleBLL.h"
#include "../Include/Model/sample/SampleTestModel.h"
#include "../Include/BLL/baseSet/TestPaperBLL.h"
#include "../Include/BLL/baseSet/ItemBll.h"
#include "../Include/Model/baseSet/TestPaperModel.h"
#include "../Include/Utilities/log.h"
#include "src/main/subDialog/MyMessageBox.h"

TestDataListWidget::TestDataListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestDataListWidget)
  , m_listTest{}
  ,_lblPaperVect{}
{
    ui->setupUi(this);
    initUI();
}

TestDataListWidget::~TestDataListWidget()
{
    delete ui;
}

void TestDataListWidget::initUI()
{
	ui->label->setStyleSheet("background-color: rgba(233, 233, 233, 0); color: rgba(233, 233, 233, 190);font-size: 36px; ");
    ui->label_2->setStyleSheet("background-color: rgba(233, 233, 233, 0); color: rgba(233, 233, 233, 190);font-size: 36px; ");
}

void TestDataListWidget::createPapers()
{
	for (auto i = 1; i <= PAPERCOUNT; i++)
	{
		auto lbl = new CustomLabel1(this);
		lbl->setProperty("lblStyle", "lblPaperStyle");
		lbl->setPos(i);
		lbl->setText(" ");
		_lblPaperVect.push_back(lbl);
        if (i > 0 && i <= 36)
		{
            ui->hLayPaperPos->addWidget(lbl);
		}
        else if (i > 36)
		{
            ui->hLayPaperPos1->addWidget(lbl);
		}       
	}
}

void TestDataListWidget::setPapersState(QVector<ptrTest> listTestData)
{
    m_listTest=listTestData;
    if(_lblPaperVect.isEmpty())
        createPapers();
    for (auto lbl : _lblPaperVect)
    {
        lbl->reset();
        auto it = searchPmByPos(lbl->getPos());
        if (it.isNull())
            continue;

        auto paper = TestPaperBLL().getRowById(it->getPaperId());
        if (paper.isNull())
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1428"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            eLog("paper is null", it->getPaperId());
            continue;
        }
        QString sz = QString("%1:%2:%3").arg(it->getSamplePos()).arg(paper->getPaperName()).arg(it->getRemark());//sampleNo
        lbl->setBgColor(paper->getBGRGB());
        lbl->setText(sz);
    }
}


TestDataListWidget::ptrTest TestDataListWidget::searchPmByPos(int pos)
{
    for (auto it : m_listTest)
    {
        if (it->getSlotPos() == pos)
            return it;
    }
    return nullptr;
}
