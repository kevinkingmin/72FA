#include "AlarmDialog.h"
#include "ui_AlarmDialog.h"
#include <QMessageBox>
#include "src/comm/GlobalData.h"

AlarmDialog::AlarmDialog(QWidget *parent) :
    BaseDialog(parent),    
    ui(new Ui::AlarmDialog)
  ,m_ret(-1)
{
    ui->setupUi(this);
    initUi();	
}


AlarmDialog::~AlarmDialog()
{
    delete ui;
}

void AlarmDialog::msgText(const QString &alarmStr, const bool showCancelBtn)
{
	ui->plainTextEdit->clear();
    if(showCancelBtn)
        ui->buttonCancel->setVisible(true);
    else
        ui->buttonCancel->setVisible(false);
    ui->plainTextEdit->appendPlainText(alarmStr);
}

void AlarmDialog::on_pushButtonClose_clicked()
{
    m_ret=1;
    this->hide();
}

void AlarmDialog::on_btnSave_clicked()
{
    m_ret=0;
    this->hide();
}

void AlarmDialog::on_buttonCancel_clicked()
{
    m_ret=1;
    this->hide();
}

void AlarmDialog::initUi()
{
    ui->label_2->setText(GlobalData::LoadLanguageInfo("K1180"));
    ui->btnSave->setText(GlobalData::LoadLanguageInfo("K1181"));
    ui->buttonCancel->setText(GlobalData::LoadLanguageInfo("K1134"));
}

int AlarmDialog::getRet() const
{
    return m_ret;
}

void AlarmDialog::setFstBtnTest(const QString &text)
{
    ui->btnSave->setText(text);
}

void AlarmDialog::setSndBtnTest(const QString &text)
{
    ui->buttonCancel->setText(text);
}


void AlarmDialog::showEvent(QShowEvent *)
{
    centerDisplay();
}
