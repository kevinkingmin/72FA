#include "startDialog.h"
#include "ui_startDialog.h"
#include <QMessageBox>
#include <QThread>
#include <QDebug>
#include "src/comm/GlobalData.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/BLL/sample/SampleBLL.h"
#include "../Include/Model/sample/SampleModel.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "../Include/Utilities/log.h"
#include <QDateTime>


StartDialog::StartDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
    initUi();    
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::initUi()
{
    _InstrumentState=InstrumentStateModel::instance();
    _instr = Instrument::instance();
    auto clinicMap=GlobalData::mapClinicType();
    int j=0;
    for(auto it=clinicMap.begin();it!=clinicMap.end();it++)
    {
        QPushButton *btn=new QPushButton(this);
        btn->setText(it.value());
        btn->setObjectName(QString::number(it.key()));
        btn->setProperty("btnStyle","selectBtn1");
        btn->setCheckable(true);
        ui->vBoxSampleType->addWidget(btn);
        _btnGroupClinicType.addButton(btn,j);
        if(j==0)
            btn->setChecked(true);
        j++;
    }
}

void StartDialog::on_pushButtonClose_clicked()
{
    this->hide();
}

void StartDialog::on_btnCancel_clicked()
{
    this->hide();
}

void StartDialog::on_btnReagentInfo_clicked()
{
    emit sglCurrentPage(1);
}

void StartDialog::on_btnCalibrate_clicked()
{
    emit sglCurrentPage(2);
}

void StartDialog::on_btnQC_clicked()
{
    emit sglCurrentPage(3);
}

void StartDialog::on_btnStatistics_clicked()
{
    emit sglCurrentPage(0);
}

void StartDialog::on_btnChangeSample_clicked()
{

}

void StartDialog::on_btnAddConsumable_clicked()
{

}

void StartDialog::on_btnStart_clicked()
{
    //QVector<CreateActParaModel>vect;
	int cout=1;
    //Instrument::instance()->testStart(vect);
	_InstrumentState->setMachineState(InstrumentStateModel::enumRuning);
	this->hide();
}
