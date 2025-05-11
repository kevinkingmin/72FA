#include "AddTubeStep2.h"
#include "AddTubeStep3.h"
#include <QMessageBox>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

AddTubeStep2::AddTubeStep2(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_ShowModal, true);
}

AddTubeStep2::~AddTubeStep2()
{
}

void AddTubeStep2::Set_UI()
{
	bool bResult;
    auto dao = AnalysisUIDao::instance();

	QPixmap pixBig;
	pixBig.load(QCoreApplication::applicationDirPath() + "/res/tube2.png");  //图片路径
	ui.label_Picture->setScaledContents(true);//设置图片适应label
	int w1 = pixBig.width();
	int h1 = pixBig.height();
	ui.label_Picture->resize(w1, h1);
	ui.label_Picture->setPixmap(pixBig);
}

void AddTubeStep2::on_pushButton_Back_clicked()
{
	this->close();

}

void AddTubeStep2::on_pushButton_Next_clicked()
{
	AddTubeStep3 *addTubeStep3 = new AddTubeStep3();
	connect(addTubeStep3, SIGNAL(SetCancel(bool)), this, SLOT(getCancelSignal(bool)));

	addTubeStep3->m_strTube_ID = m_strTube_ID;
	addTubeStep3->m_Name = m_Name;
	addTubeStep3->m_IsControl = m_IsControl;
	addTubeStep3->m_Inner = m_Inner;
	addTubeStep3->m_LiquidStartPos = m_LiquidStartPos;
	addTubeStep3->m_CupHeight = m_CupHeight;


	addTubeStep3->Set_UI();
	addTubeStep3->show();
}

void AddTubeStep2::on_pushButton_Cancel_clicked()
{
	this->close();
	emit SetCancel(true);
}


void AddTubeStep2::getCancelSignal(bool bFlag)
{
	this->close();
	emit SetCancel(true);
}
