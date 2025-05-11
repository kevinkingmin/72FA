#include "AddCompany.h"
#include <QMessageBox>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "src/comm/GlobalData.h"

AddCompany::AddCompany(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_ShowModal, true);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	ui.label->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1099"));
	ui.pushButton_Cancel->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
	ui.pushButton_Save->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1141"));
	ui.label_2->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1589"));
	
	//
}

AddCompany::~AddCompany()
{
}

void AddCompany::on_pushButton_Cancel_clicked()
{
	this->close();

}

void AddCompany::on_pushButton_Save_clicked()
{

	if (Save_Company() == false)
		return;

	emit SetRefresh(true);

	this->close();

}

bool AddCompany::Save_Company() 
{
	QString strName = ui.lineEdit_Name->text();
	if(strName.length() == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1525"), MyMessageBox::Ok,"OK","");
		return false;
	}
    auto dao = AnalysisUIDao::instance();
	bool bResult;
	bResult = dao->InsertCompany(strName);
	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1526"), MyMessageBox::Ok,"OK","");
		return false;
	}
	return true;
}
