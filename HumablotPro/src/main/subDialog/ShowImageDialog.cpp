#include "..\include\precomp\precompile.h"
#include "ShowImageDialog.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

ShowImageDialog::ShowImageDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

ShowImageDialog::~ShowImageDialog()
{}

void ShowImageDialog::ShowPicInfo()
{
	bool bResult = true;
	auto dao = AnalysisUIDao::instance();
	QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
	QString original_piture_path = "original";
	//QString strPath = piture_root_str +"\\"+ test_file_name + "\\" + original_piture_path;
	//QString strPathFileName = strPath + "\\" + QString::number(nSampleID) + +"_" + QString::number(nTestPaperID) + ".png";
	QString strPath = piture_root_str + "\\" + original_piture_path;
	QString strPathFileName = strPath + "\\" + "test" + ".png";

	QImage image(strPathFileName);
	ui.label->setPixmap(QPixmap::fromImage(image));
	ui.label->setScaledContents(true);
	
	//ui->label->setPixmap(QPixmap::fromImage(image));
	//label->show();
	//ShowPicInfo();
}

void ShowImageDialog::on_pushButton_clicked()
{
	m_camera_check_status = 1;
	close();
}

void ShowImageDialog::on_pushButton_2_clicked()
{
	m_camera_check_status = 2;
	close();
}