#include "AlarmDialog.h"
#include "ui_AlarmDialog.h"
#include <QMessageBox>
#include "src/comm/GlobalData.h"
#include "../Include/Instrument/Instrument.h"

AlarmDialog::AlarmDialog(QWidget *parent) :
    BaseDialog(parent),    
    ui(new Ui::AlarmDialog)
  ,m_ret(-1)
  ,m_confirmMsgText("")
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
    if(!m_confirmMsgText.isEmpty())
    {
        int ret=QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1260"),
                                         m_confirmMsgText,
                                         GlobalData::LoadLanguageInfo("K1181"),
                                         GlobalData::LoadLanguageInfo("K1134"));
        if(ret != 0)
            return;
    }
    m_confirmMsgText="";
    this->hide();
}

void AlarmDialog::on_buttonCancel_clicked()
{
    m_ret=1;
    Instrument::instance()->shutdownBee();
}

void AlarmDialog::initUi()
{
    ui->label_2->setText(GlobalData::LoadLanguageInfo("K1180"));
    ui->btnSave->setText(GlobalData::LoadLanguageInfo("K1181"));
    ui->buttonCancel->setText(GlobalData::LoadLanguageInfo("K1134"));
    ui->pushButtonClose->setVisible(false);
}

void AlarmDialog::setConfirmMsgText(const QString &confirmMsgText)
{
    m_confirmMsgText = confirmMsgText;
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

void AlarmDialog::setAlignCenter()
{
    this->setFixedSize(550,350);
    QFont font = ui->plainTextEdit->font();
    font.setPointSize(15);
    ui->plainTextEdit->setFont(font);
    auto document = ui->plainTextEdit->document();
    QTextOption option(Qt::AlignCenter);
    document->setDefaultTextOption(option);
}

void AlarmDialog::showEvent(QShowEvent *)
{
    centerDisplay();
}
