#include "SetFirstPaperPosDialog.h"
#include "ui_SetFirstPaperPosDialog.h"
#include <QMessageBox>
#include "src/main/subDialog/MyMessageBox.h"
#include "../../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

SetFirstPaperPosDialog::SetFirstPaperPosDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::SetFirstPaperPosDialog)
  ,_StartPosReg(QRegExp("^[1-9]$|^[1-6][0-9]$|^7[0-2]$"))
  ,_testId(0)
  ,_paperCount(0)
  ,_totalNum(0)
  ,_isCloseBtn(false)
{
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
    ui->setupUi(this);
    ui->txtStartPos->setValidator(&_StartPosReg);
	ui->txtStartSlot->setVisible(false);
	ui->txtStartPos->setVisible(false);
	QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1055");
	ui->label_2->setText(sz);
	sz = GlobalData::LoadLanguageInfo(g_language_type, "K1056");
	ui->label_5->setText(sz);
	sz = GlobalData::LoadLanguageInfo(g_language_type, "K1057");
	ui->label_6->setText(sz);
	sz = GlobalData::LoadLanguageInfo(g_language_type, "K1058");
	ui->btnConfig->setText(sz);
}

SetFirstPaperPosDialog::~SetFirstPaperPosDialog()
{
    delete ui;
}

void SetFirstPaperPosDialog::showEvent(QShowEvent *)
{
    centerDisplay();
}

void SetFirstPaperPosDialog::on_pushButtonClose_clicked()
{
    _isCloseBtn=true;
    hide();
}

void SetFirstPaperPosDialog::setTestId(const quint64 &testId)
{
    _testId = testId;
}

void SetFirstPaperPosDialog::on_btnConfig_clicked()
{
	//int ui->txtStartSlot->text()
	int slot_number = ui->txtStartSlot->text().toInt();
	int start_number = ui->txtStartPos->text().toInt();
	slot_number = ui->comboBox->currentText().toInt();
	start_number = ui->comboBox_2->currentText().toInt();
	if (1 <= slot_number && slot_number <= 3)
	{
	}
	else
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1367"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	if (ui->txtStartSlot->text().simplified().isEmpty())
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1368"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
    if(ui->txtStartPos->text().simplified().isEmpty())
    {
        MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1369"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    if(_paperCount+getStartPos()-1>_totalNum)
    {
        int suggestStartPos=_totalNum-_paperCount+1;
		QString hint = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1370") + QString::number(suggestStartPos) + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1371");
		MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"),hint,  MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
        return;
    }
    _isCloseBtn=false;
    hide();
}

int SetFirstPaperPosDialog::getStartPos()
{
	int slot_number = ui->txtStartSlot->text().toInt();
	int start_number = ui->txtStartPos->text().toInt();
	slot_number = ui->comboBox->currentText().toInt();
	start_number =ui->comboBox_2->currentText().toInt();
    int start_position = (slot_number - 1) * 36 + start_number;
	return start_position;
    //return ui->txtStartPos->text().toInt();
}

bool SetFirstPaperPosDialog::getIsCloseBtn() const
{
    return _isCloseBtn;
}

void SetFirstPaperPosDialog::setPaperCount(const int &paperCount, const int &totalNum)
{
    _paperCount = paperCount;
    _totalNum=totalNum;
}
