#include "PatientDialog.h"
#include "ui_PatientDialog.h"
#include <QListView>
#include <QMessageBox>
#include <QLineEdit>
#include "../Include/Model/baseSet/AgeUnitModel.h"
#include "../Include/Model/baseSet/DepartmentModel.h"
#include "../Include/Model/baseSet/SexModel.h"
#include "../Include/Model/baseSet/SampleSenderModel.h"
#include "../Include/Model/baseSet/BedNoModel.h"
#include "../Include/Model/baseSet/WardModel.h"
#include "../Include/Model/baseSet/RemarkModel.h"
#include "../Include/Model/baseSet/DiagnosisModel.h"
#include "../Include/BLL/baseSet/AgeUnitBLL.h"
#include "../Include/BLL/baseSet/DepartmentBLL.h"
#include "../Include/BLL/baseSet/SexBLL.h"
#include "../Include/BLL/sample/SampleBLL.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Utilities/log.h"
#include "src/comm/GlobalData.h"
#include "src/comm/ObjectTr.h"
#include <QCalendarWidget>
#include <QDebug>

PatientDialog::PatientDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::PatientDialog)
  , _regLISValid(QRegExp("^[^|]{0,30}$"))
  ,_preRemark("")
  ,_preDiagnosis("")
  ,_pkid(0)
{
    ui->setupUi(this);
    ui->cmbAgeUnitID->setView(new QListView(this));
    ui->cmbSexID->setView(new QListView(this));
    ui->cmbBloodType->setView(new QListView(this));
    ui->txtAge->setValidator(new QIntValidator(0,200,this));
    ui->txtAnamnesisNO->setValidator(&_regLISValid);
    ui->txtPatientName->setValidator(&_regLISValid);
    ui->cmbWardName->setValidator(&_regLISValid);
    ui->cmbBedNo->setValidator(&_regLISValid);
    ui->cmbDepartmentName->setValidator(&_regLISValid);
    ui->cmbSampleSender->setValidator(&_regLISValid);
}

PatientDialog::~PatientDialog()
{
    delete ui;
}

void PatientDialog::showEvent(QShowEvent * e)
{
    Q_UNUSED(e);
    centerDisplay();
    initUIControl();
	setUIData();
}

void PatientDialog::initUIControl()
{    
    ui->cmbAgeUnitID->clear();
    ui->cmbSexID->clear();
    ui->cmbBloodType->clear();
    for(auto it:AgeUnitBLL().getAllRows())
        ui->cmbAgeUnitID->addItem(it->getAgeName(),it->getID());
    auto sexMap=GlobalData::mapSexType();
    for(auto it=sexMap.begin();it!=sexMap.end();it++)
        ui->cmbSexID->addItem(it.value(),it.key());    
    auto bloodMap=GlobalData::mapSampleType();
    for(auto it=bloodMap.begin();it!=bloodMap.end();it++)
        ui->cmbBloodType->addItem(it.value(),it.key());

    ui->cmbDepartmentName->setText("");
    ui->cmbSampleSender->setText("");
    ui->cmbWardName->setText("");
    ui->cmbBedNo->setText("");
	ui->txtAge->setText("");
	ui->txtAnamnesisNO->setText("");
	ui->txtDiagnosis->setText("");
	ui->txtPatientName->setText("");
	ui->txtRemark->setText("");
	ui->txtTestDoctor->setText("");
	ui->txtVerifyDoctor->setText("");
	ui->dtSampleSendTime->setDateTime(QDateTime::currentDateTime());
}

void PatientDialog::setUIData()
{
    bool suc=true;
    auto record=AnalysisUIDao::instance()->getSampleByPkid(_pkid,suc);
    if(!suc)
    {
        eLog("get record failed");
        return;
    }
    ui->txtAnamnesisNO->setText(record.value("AnamnesisNO").toString());
    ui->txtPatientName->setText(record.value("PatientName").toString());
    QString ageStr=record.value("Age").toInt()<=0?"":record.value("Age").toString();
    ui->txtAge->setText(ageStr);
    int index=ui->cmbAgeUnitID->findData(record.value("AgeUnitID").toInt());
    ui->cmbAgeUnitID->setCurrentIndex(index);
    index=ui->cmbSexID->findData(record.value("SexID").toInt());
    ui->cmbSexID->setCurrentIndex(index);
    ui->dtSampleSendTime->setDateTime(record.value("createDay").toDateTime());
    ui->txtTestDoctor->setText(record.value("testUser").toString());
    QString checkerName=(record.value("checkerName").isNull()||record.value("checkerName").toString().isNull())?"":record.value("checkerName").toString();
    ui->txtVerifyDoctor->setText(checkerName);
    ui->txtDiagnosis->setPlainText(record.value("diagnosis").toString());
    QString remark=record.value("remark").isNull()||record.value("remark").toString().isNull()?"":record.value("remark").toString();
    ui->txtRemark->setPlainText(remark);
    ui->cmbWardName->setText(record.value("wardName").toString());
    ui->cmbBedNo->setText(record.value("BedNo").toString());
    ui->cmbDepartmentName->setText(record.value("departmentName").toString());
    QString sampleSender=record.value("sampleSender").isNull()||record.value("sampleSender").toString().isNull()?"":record.value("sampleSender").toString();
    ui->cmbSampleSender->setText(sampleSender);
    int bloodType = record.value("bloodType").toInt()<=0?1:record.value("bloodType").toInt();
    index=ui->cmbBloodType->findData(bloodType);
    ui->cmbBloodType->setCurrentIndex(index);
}

void PatientDialog::getUIData()
{
    bool succ=true;
    QString sqlStr="update tsample as t1 left join tsample as t2 on t1.samplePos=t2.samplePos and t1.createDay=t2.createDay and t1.sampleNo=t2.sampleNo set ";
    sqlStr+="t1.AnamnesisNO='"+ui->txtAnamnesisNO->text()+"',";
    sqlStr+="t1.PatientName='"+ui->txtPatientName->text()+"',";
    sqlStr+="t1.Age='"+(ui->txtAge->text().simplified().isEmpty()?"0": ui->txtAge->text().simplified()) +"',";
    sqlStr+="t1.AgeUnitID='"+(ui->cmbAgeUnitID->currentData().toString().isEmpty()?"0": ui->cmbAgeUnitID->currentData().toString()) +"',";
    sqlStr+="t1.SexID='"+ui->cmbSexID->currentData().toString()+"',";
    sqlStr+="t1.bloodType='"+ui->cmbBloodType->currentData().toString()+"',";
    //sqlStr+="createDay='"+ui->dtSampleSendTime->text().simplified()+"',";
    sqlStr+="t1.testUser='"+ui->txtTestDoctor->text().simplified()+"',";
    sqlStr+="t1.checkerName='"+ui->txtVerifyDoctor->text().simplified()+"',";
    sqlStr+="t1.diagnosis='"+ui->txtDiagnosis->toPlainText().simplified()+"',";
    sqlStr+="t1.remark='"+ui->txtRemark->toPlainText().simplified()+"',";
    sqlStr+="t1.wardName='"+ui->cmbWardName->text().simplified()+"',";
    sqlStr+="t1.BedNo='"+ui->cmbBedNo->text().simplified()+"',";
    sqlStr+="t1.departmentName='"+ui->cmbDepartmentName->text().simplified()+"',";
    sqlStr+="t1.sampleSender='"+ui->cmbSampleSender->text().simplified()+"' ";
    sqlStr+="where t2.pkid="+QString::number(_pkid)+";";
    AnalysisUIDao::instance()-> UpdateRecord(&succ,sqlStr);
    if(!succ)
    {
        QMessageBox::information(this,tr("提示"),tr("保存失败"),tr("确定"));
        return;
    }
    this->close();
}

void PatientDialog::on_btnSave_clicked()
{
    getUIData();
}

void PatientDialog::on_pushButtonClose_clicked()
{
    this->close();
}

void PatientDialog::on_btnClose_clicked()
{
    this->close();
}

void PatientDialog::setPkid(int pkid)
{
    _pkid = pkid;
}
