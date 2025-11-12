#include "AddReagent.h"
#include <QMessageBox>
#include "../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/DAO/reagent/ReagentDao.h"
#include <QProcess>
#include <QListView>
#include "src/main/subDialog/MyMessageBox.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

AddReagent::AddReagent(QWidget *parent)
    : QDialog(parent)
    ,m_strCompany_ID("")
    ,m_strReagent_ID("")
    ,m_companyName("")
{
	ui.setupUi(this);
    setWindowFlags((windowFlags() & ~(Qt::WindowContextHelpButtonHint)));
    setFixedSize(width(), height());
	QDoubleValidator* validator6 = new QDoubleValidator(0.0, 0.0, 2, ui.lineEdit_big_wash);
    ui.lineEdit_big_wash->setValidator(validator6);
	QDoubleValidator* validator7 = new QDoubleValidator(0.0, 0.0, 2, ui.lineEdit_small_wash);	
	ui.lineEdit_small_wash->setValidator(validator7);
	ui.lineEdit_Name->setProperty("preserveTrailingSpaces", true);  // 设置保留尾部输入空格
    ui.label->setText(GlobalData::LoadLanguageInfo("K1136")); // 试剂名称
    ui.label_2->setText(GlobalData::LoadLanguageInfo("K1142")); // 防挂滴
    ui.label_3->setText(GlobalData::LoadLanguageInfo("K1143")); // 试剂回流
    ui.label_4->setText(GlobalData::LoadLanguageInfo("K1144")); // 运行前灌装

    ui.label_6->setText(GlobalData::LoadLanguageInfo("K1761")); // 关联厂家
    ui.label_7->setText(GlobalData::LoadLanguageInfo("K1138")); // 大充灌量
    ui.label_8->setText(GlobalData::LoadLanguageInfo("K1139")); // 小充灌量

    ui.pushButton_Save->setText(GlobalData::LoadLanguageInfo("K1141")); // 保存
    ui.pushButton_Cancel->setText(GlobalData::LoadLanguageInfo("K1134")); // 取消
}

AddReagent::~AddReagent()
{
}

void AddReagent::Set_UI()
{
    ui.txtCompany->setText(m_companyName);
    bool bResult;
    if (!m_bModify)
    {
        _reagent = ReagentModel();
        return;
    }
    bResult=ReagentDao::instance()->selectReagentById(m_strReagent_ID.toInt(), _reagent);
	if (bResult == false)
	{
        _reagent = ReagentModel();
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1527"), MyMessageBox::Ok,"OK","");
		return;
    }
    m_strCompany_ID = QString::number(_reagent.getCompanyID());
    QString reagent_name = _reagent.getReagentName();
    QString small_wash_sz = QString::number(static_cast<double>(_reagent.getFluidMeasureSmall()), 'f', 2);
    QString big_wash_sz = QString::number(static_cast<double>(_reagent.getFluidMeasure()), 'f', 2);
    ui.lineEdit_Name->setText(reagent_name);

    int nValue = _reagent.getIsNoDrip();
    ui.checkBox_IsNoDrip->setChecked(nValue == 1);
    nValue = _reagent.getIsSkimp();
    ui.checkBox_IsSkimp->setChecked(nValue == 1);
    nValue = _reagent.getIsNeedPrepare();
    ui.checkBox_IsNeedPrepare->setChecked(nValue == 1);
    ui.lineEdit_big_wash->setText(big_wash_sz);
    ui.lineEdit_small_wash->setText(small_wash_sz);

    ui.checkBox_IsNeedPrepare->setEnabled(true);
    ui.lineEdit_Name->setEnabled(true);
    ui.checkBox_IsSkimp->setEnabled(true);
    ui.checkBox_IsNoDrip->setEnabled(true);
}

void AddReagent::setCompanyName(const QString &companyName)
{
    m_companyName = companyName;
}


void AddReagent::on_pushButton_Save_clicked()
{
    QString strName = ui.lineEdit_Name->text().trimmed();
	if (strName.length() == 0)
	{
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1528"), MyMessageBox::Ok,"OK","");
		return ;
	}
    bool isNoDrip;
    bool isSkimp;
    bool isNeedPrepare;
    isNoDrip = ui.checkBox_IsNoDrip->isChecked();
    isSkimp = ui.checkBox_IsSkimp->isChecked();
    isNeedPrepare = ui.checkBox_IsNeedPrepare->isChecked();
    bool bResult;
    float big_wash = ui.lineEdit_big_wash->text().simplified().toFloat();
    if (big_wash <= 0)
	{
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1532"), MyMessageBox::Ok,"OK","");
		return;
	}
    float small_wash = ui.lineEdit_small_wash->text().simplified().toFloat();
    if (small_wash <= 0)
	{
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1533"), MyMessageBox::Ok,"OK","");
		return;
	}

	if (small_wash > big_wash)
	{
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1534"), MyMessageBox::Ok,"OK","");
		return;
	}

    _reagent.setReagentName(strName);
    _reagent.setIsSkimp(isSkimp);
    _reagent.setCompanyID(m_strCompany_ID.toInt());
    _reagent.setIsNoDrip(isNoDrip);
    _reagent.setIsNeedPrepare(isNeedPrepare);
    _reagent.setFluidMeasure(big_wash);
    _reagent.setFluidMeasureSmall(small_wash);
    if (!m_bModify)
    {
        bResult = ReagentDao::instance()->insertModel(_reagent);
        if (bResult == false)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1536"), MyMessageBox::Ok, "OK", "");
            return;
        }
	}
	else
	{
        bResult = ReagentDao::instance()->updateModel(_reagent);
        if (bResult == false)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1537"), MyMessageBox::Ok, "OK", "");
            return;
        }
    }
    auto ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1278"), MyMessageBox::Ok|MyMessageBox::No, GlobalData::LoadLanguageInfo("K1181"), GlobalData::LoadLanguageInfo("K1134"));
	if (ret == MyMessageBox::No)
	{
        this->close();
        return;
	}
    InstrumentStateModel *_InstrumentState(InstrumentStateModel::instance());
    auto state = _InstrumentState->getMachineState();
    if ((state.state == _InstrumentState->enumRuning) || (state.state == _InstrumentState->enumMaintain))
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1711"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo("K1181"), "");
        return;
    }
    Instrument::instance()->closeSocket();
    QString program = QCoreApplication::applicationFilePath();
    QStringList arguments = QCoreApplication::arguments();
    QProcess::startDetached(program, arguments);
    QCoreApplication::instance()->quit();
}

void AddReagent::on_pushButton_Cancel_clicked()
{
	this->close();
}
