#include "AddProcess.h"
#include <QMessageBox>
#include "../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include <QProcess>
#include <QListView>
#include "src/main/subDialog/MyMessageBox.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

AddProcess::AddProcess(QWidget *parent)
    : QDialog(parent)
    ,m_companyName("")
    ,m_strCompany_ID("")
    ,m_bModify(false)
{
	ui.setupUi(this);
    setWindowFlags((windowFlags() & ~(Qt::WindowContextHelpButtonHint)));
    setFixedSize(width(), height());
    ui.label->setText(GlobalData::LoadLanguageInfo("K1769")+": ");
    ui.pushButton_Save->setText(GlobalData::LoadLanguageInfo("K1141"));
    ui.pushButton_Cancel->setText(GlobalData::LoadLanguageInfo("K1134"));
}

AddProcess::~AddProcess()
{
}

void AddProcess::setStrCompany_ID(const QString &strCompany_ID)
{
    m_strCompany_ID = strCompany_ID;
}

void AddProcess::setCompanyName(const QString &companyName)
{
    m_companyName = companyName;
}

//调用接口,保存流程名称
void AddProcess::on_pushButton_Save_clicked()
{
    //ui.lineEdit_Name->text();//流程名称
    //m_strCompany_ID//公司id
}

void AddProcess::on_pushButton_Cancel_clicked()
{
	this->close();
}
