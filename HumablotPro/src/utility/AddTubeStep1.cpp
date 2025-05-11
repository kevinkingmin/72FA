#include "AddTubeStep1.h"
#include "AddTubeStep2.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/comm/GlobalData.h"

AddTubeStep1::AddTubeStep1(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_ShowModal, true);

}

AddTubeStep1::~AddTubeStep1()
{
}

void AddTubeStep1::Set_UI()
{
	bool bResult;
    auto dao = AnalysisUIDao::instance();
	ui.pushButton_Back->setVisible(false);
	QPixmap pixBig;
	pixBig.load(QCoreApplication::applicationDirPath() + "/res/tube1.png");  //图片路径
	ui.label_Picture->setScaledContents(true);//设置图片适应label
	int w1 = pixBig.width();
	int h1 = pixBig.height();
	ui.label_Picture->resize(w1, h1);
	ui.label_Picture->setPixmap(pixBig);
	if (m_strTube_ID.length() == 0)
		return;
    QSqlQuery TubeQuery = dao->SelectTube(m_strTube_ID, &bResult);
	if (bResult == false)
	{
		QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "检索样本管数据失败！", QMessageBox::Ok);
		return;
	}
    if (TubeQuery.next())
	{
        ui.lineEdit_Name->setText(TubeQuery.value("Name").toString());

        int nValue = TubeQuery.value("IsControl").toInt();
		if (nValue == 1)
			ui.checkBox_Control->setChecked(true);
		else
			ui.checkBox_Control->setChecked(false);
        ui.lineEdit_Inner->setText(TubeQuery.value("Inner").toString());
        m_LiquidStartPos = TubeQuery.value("LiquidStartPos").toString();
        m_CupHeight = TubeQuery.value("CupHeight").toString();
	}
}

void AddTubeStep1::on_pushButton_Back_clicked()
{


}

void AddTubeStep1::on_pushButton_Next_clicked()
{
	if (ui.lineEdit_Name->text().trimmed().length() == 0)
	{
		QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请输入试管名称！", QMessageBox::Ok);
		return;
	}

	if (ui.lineEdit_Inner->text().trimmed().length() == 0)
	{
		QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请输入正确的试管内径！", QMessageBox::Ok);
		return;
	}

	if (ui.lineEdit_Inner->text().trimmed().toInt() == 0)
	{
		QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请输入正确的试管内径！", QMessageBox::Ok);
		return;
	}


	AddTubeStep2 *addTubeStep2 = new AddTubeStep2();
	connect(addTubeStep2, SIGNAL(SetCancel(bool)), this, SLOT(getCancelSignal(bool)));

	addTubeStep2->m_strTube_ID = m_strTube_ID;
	addTubeStep2->m_Name = ui.lineEdit_Name->text().trimmed();
	addTubeStep2->m_IsControl = QString::number(ui.checkBox_Control->isChecked());
	addTubeStep2->m_Inner = ui.lineEdit_Inner->text().trimmed();

	addTubeStep2->m_LiquidStartPos = m_LiquidStartPos;
	addTubeStep2->m_CupHeight = m_CupHeight;

	addTubeStep2->Set_UI();
	addTubeStep2->show();
}

void AddTubeStep1::on_pushButton_Cancel_clicked() 
{
	this->close();
}

void AddTubeStep1::getCancelSignal(bool bFlag)
{
	this->close();
}
