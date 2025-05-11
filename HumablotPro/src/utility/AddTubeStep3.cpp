#include "AddTubeStep3.h"
#include "AddTubeStep4.h"
#include <QMessageBox>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

AddTubeStep3::AddTubeStep3(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_ShowModal, true);
}

AddTubeStep3::~AddTubeStep3()
{
}

void AddTubeStep3::Set_UI()
{
	bool bResult;
    auto dao = AnalysisUIDao::instance();


	QPixmap pixBig;
	pixBig.load(QCoreApplication::applicationDirPath() + "/res/tube3.png");  //图片路径
	ui.label_Picture->setScaledContents(true);//设置图片适应label
	int w1 = pixBig.width();
	int h1 = pixBig.height();
	ui.label_Picture->resize(w1, h1);
	ui.label_Picture->setPixmap(pixBig);

	QIcon btn_icon;

	btn_icon.addFile(QCoreApplication::applicationDirPath() + "/res/button_add_little.png");
	ui.button_add_little->setMaximumSize(75, 51);
	ui.button_add_little->setMinimumSize(75, 51);
	ui.button_add_little->setIcon(btn_icon);
	ui.button_add_little->setIconSize(QSize(75, 51));

	QIcon btn_icon1;
	btn_icon1.addFile(QCoreApplication::applicationDirPath() + "/res/button_add_more.png");
	ui.button_add_more->setMaximumSize(75, 51);
	ui.button_add_more->setMinimumSize(75, 51);
	ui.button_add_more->setIcon(btn_icon1);
	ui.button_add_more->setIconSize(QSize(75, 51));

	QIcon btn_icon2;
	btn_icon2.addFile(QCoreApplication::applicationDirPath() + "/res/button_minus_little.png");
	ui.button_minus_little->setMaximumSize(75, 51);
	ui.button_minus_little->setMinimumSize(75, 51);
	ui.button_minus_little->setIcon(btn_icon2);
	ui.button_minus_little->setIconSize(QSize(75, 51));

	QIcon btn_icon3;
	btn_icon3.addFile(QCoreApplication::applicationDirPath() + "/res/button_minus_more.png");
	ui.button_minus_more->setMaximumSize(75, 51);
	ui.button_minus_more->setMinimumSize(75, 51);
	ui.button_minus_more->setIcon(btn_icon3);
	ui.button_minus_more->setIconSize(QSize(75, 51));

	QIcon btn_icon4;
	btn_icon4.addFile(QCoreApplication::applicationDirPath() + "/res/button_1.png");
	ui.pushButton_1->setMaximumSize(75, 51);
	ui.pushButton_1->setMinimumSize(75, 51);
	ui.pushButton_1->setIcon(btn_icon4);
	ui.pushButton_1->setIconSize(QSize(75, 51));

	QIcon btn_icon5;
	btn_icon5.addFile(QCoreApplication::applicationDirPath() + "/res/button_2.png");
	ui.pushButton_2->setMaximumSize(75, 51);
	ui.pushButton_2->setMinimumSize(75, 51);
	ui.pushButton_2->setIcon(btn_icon5);
	ui.pushButton_2->setIconSize(QSize(75, 51));

	QIcon btn_icon6;
	btn_icon6.addFile(QCoreApplication::applicationDirPath() + "/res/button_3.png");
	ui.pushButton_3->setMaximumSize(75, 51);
	ui.pushButton_3->setMinimumSize(75, 51);
	ui.pushButton_3->setIcon(btn_icon6);
	ui.pushButton_3->setIconSize(QSize(75, 51));


}

void AddTubeStep3::on_pushButton_Back_clicked()
{
	this->close();

}

void AddTubeStep3::on_pushButton_Next_clicked()
{
	AddTubeStep4 *addTubeStep4 = new AddTubeStep4();
	connect(addTubeStep4, SIGNAL(SetCancel(bool)), this, SLOT(getCancelSignal(bool)));

	addTubeStep4->m_strTube_ID = m_strTube_ID;
	addTubeStep4->m_Name = m_Name;
	addTubeStep4->m_IsControl = m_IsControl;
	addTubeStep4->m_Inner = m_Inner;
	addTubeStep4->m_LiquidStartPos = m_LiquidStartPos;
	addTubeStep4->m_CupHeight = m_CupHeight;

	addTubeStep4->Set_UI();
	addTubeStep4->show();
}

void AddTubeStep3::on_pushButton_Cancel_clicked()
{
	this->close();
	emit SetCancel(true);
}


void AddTubeStep3::getCancelSignal(bool bFlag)
{
	this->close();
	emit SetCancel(true);
}
