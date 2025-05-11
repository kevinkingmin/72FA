#include "MaintainCmdWidget.h"
#include "ui_MaintainCmdWidget.h"
#include <QMessageBox>
#include "../Include/Instrument/Instrument.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "src/comm/GlobalData.h"

MaintainCmdWidget::MaintainCmdWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaintainCmdWidget)
{
    ui->setupUi(this);
    initUI();
}

MaintainCmdWidget::~MaintainCmdWidget()
{
    delete ui;
}

void MaintainCmdWidget::initUI()
{
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(false);
    _Instrument=Instrument::instance();
    _InstrumentState=InstrumentStateModel::instance();
}

void MaintainCmdWidget::on_btnRunInit_clicked()
{
    auto ret = MyMessageBox::question(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1440"), MyMessageBox::Yes| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if(ret== MyMessageBox::Yes)
    {
        //Instrument::instance()->maintain(eStartUpCheck);
        _InstrumentState->setMachineState(enumState::enumIniting);
    }
}

void MaintainCmdWidget::on_btnCloseInit_clicked()
{
    auto ret = MyMessageBox::question(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1441"), MyMessageBox::Yes | MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if(ret!= MyMessageBox::No)
        return;
}

void MaintainCmdWidget::on_btnSysteReset_clicked()
{

}

void MaintainCmdWidget::on_btnStartWash_clicked()
{

}

void MaintainCmdWidget::on_btnWeekWash_clicked()
{

}

void MaintainCmdWidget::on_btnEmpty_clicked()
{

}

void MaintainCmdWidget::on_btnFlush_clicked()
{

}

void MaintainCmdWidget::on_btnCloseWash_clicked()
{

}

void MaintainCmdWidget::on_btnClose_clicked()
{

}

void MaintainCmdWidget::on_btnDormant_clicked()
{

}

void MaintainCmdWidget::on_btnRouse_clicked()
{

}

void MaintainCmdWidget::on_btnPoolFlush_clicked()
{

}
