#include "AddReagent.h"
#include <QMessageBox>
#include "../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/DAO/reagent/ReagentDao.h"
#include "../Include/DAO/baseSet/TestPaperDao.h"
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
    //ui.lineEdit_ReagentName->setProperty("preserveTrailingSpaces", true);  // 设置保留尾部输入空格
    ui.label_SpecificReagent->setText(GlobalData::LoadLanguageInfo("K1841")); // 专用试剂
    ui.label_ReagentName->setText(GlobalData::LoadLanguageInfo("K1136")); // 试剂名称
    ui.label_PaperName->setText(GlobalData::LoadLanguageInfo("K1145")); // 关联膜条
    ui.label_IsNoDrip->setText(GlobalData::LoadLanguageInfo("K1142")); // 防挂滴
    ui.label_IsSkimp->setText(GlobalData::LoadLanguageInfo("K1143")); // 试剂回流
    ui.label_pumpNo->setText(GlobalData::LoadLanguageInfo("K1514")); // 泵号

    ui.label_Company->setText(GlobalData::LoadLanguageInfo("K1761")); // 关联厂家
    ui.label_SmallWash->setText(GlobalData::LoadLanguageInfo("K1139")); // 大充灌量
    ui.label_BigWash->setText(GlobalData::LoadLanguageInfo("K1138")); // 小充灌量

    ui.pushButton_Save->setText(GlobalData::LoadLanguageInfo("K1141")); // 保存
    ui.pushButton_Cancel->setText(GlobalData::LoadLanguageInfo("K1134")); // 取消
    ui.comboBox_ReagentName->setEditable(true); // 设置为可编辑

    for(int i = 1; i < 10; i++)
    {
        ui.comboBox_pumpNo->addItem(QString::number(i) ,i);
    }
    // 设置第二行
    QWidget *row2Container = new QWidget;
    QHBoxLayout *row2Layout = new QHBoxLayout;
    ui.label_PaperName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    ui.comboBox_PaperName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    row2Container->setContentsMargins(0, 0, 0, 0);
    row2Layout->setContentsMargins(0, 0, 0, 0);
    row2Layout->addWidget(ui.label_PaperName);
    row2Layout->addWidget(ui.comboBox_PaperName);
    row2Container->setLayout(row2Layout);
    ui.gridLayout->addWidget(row2Container, 1, 0, 1, 2);
    row2Container->hide();

    connect(ui.checkBox_IsSpecificReagent, &QCheckBox::toggled, this, [=](bool checked) {
        qDebug()<<"checkBox_IsSpecificReagent"<<checked;
        ui.comboBox_PaperName->clear();
        ui.comboBox_ReagentName->clear();
        if (checked) // 选中专用试剂
        {
            // 设置关联膜条下拉框
            QVector<TestPaperModel> paperVect = TestPaperDao::instance()->getCompanyPapers(m_strCompany_ID);
            for(TestPaperModel& paper : paperVect)
            {
                ui.comboBox_PaperName->addItem(paper.getPaperName(), paper.getId());
            }
            // 设置专用试剂下拉框
            QVector<ReagentModel> reagentVect = ReagentDao::instance()->selectReagent(m_strCompany_ID.toInt());
            QSet<QString> reagentNameSet = {};
            for(ReagentModel& reagent : reagentVect)
            {
                if(reagent.getReagentType() == 0) continue; // 忽略通用试剂
                if(reagentNameSet.contains(reagent.getReagentName())) continue; // 已经包含忽略
                reagentNameSet.insert(reagent.getReagentName());
                ui.comboBox_ReagentName->addItem(reagent.getReagentName(), reagent.getReagentName());
            }

            if(m_bModify) // 修改
            {
                // 设置膜条
                int paperIndex = ui.comboBox_PaperName->findData(_reagent.getPaperId());
                ui.comboBox_PaperName->setCurrentIndex(paperIndex);
                // 设置试剂
                int reagentIndex = ui.comboBox_ReagentName->findText(_reagent.getReagentName());
                if(reagentIndex != -1)
                {
                    ui.comboBox_ReagentName->setCurrentIndex(reagentIndex); // 设置试剂名称
                }else
                {
                    ui.comboBox_ReagentName->setEditText(_reagent.getReagentName()); // 设置试剂名称
                }
            }else
            {
                ui.comboBox_PaperName->setCurrentIndex(-1); // 默认不选中
            }
            row2Container->show();
        } else
        {
            row2Container->hide();
            ui.comboBox_ReagentName->setEditText(_reagent.getReagentName()); // 设置试剂名称
        }
    });
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
    ui.checkBox_IsSpecificReagent->setChecked(_reagent.getReagentType() == 1); // 设置专用试剂的选中状态
    ui.comboBox_ReagentName->setEditText(reagent_name);
    ui.comboBox_pumpNo->setCurrentText(QString::number(_reagent.getPumpNo()));

    int nValue = _reagent.getIsNoDrip();
    ui.checkBox_IsNoDrip->setChecked(nValue == 1);
    nValue = _reagent.getIsSkimp();
    ui.checkBox_IsSkimp->setChecked(nValue == 1);
    ui.lineEdit_big_wash->setText(big_wash_sz);
    ui.lineEdit_small_wash->setText(small_wash_sz);
    ui.checkBox_IsSkimp->setEnabled(true);
    ui.checkBox_IsNoDrip->setEnabled(true);
}

void AddReagent::setCompanyName(const QString &companyName)
{
    m_companyName = companyName;
}

// 专用试剂点击事件
void AddReagent::onSpecificReagentToggled(bool checked)
{
    qDebug()<<"onSpecificReagentToggled"<<checked;
}


void AddReagent::on_pushButton_Save_clicked()
{
    QString strName = ui.comboBox_ReagentName->currentText().trimmed();
    if (strName.length() == 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1528"), MyMessageBox::Ok,"OK","");
        return ;
    }
    bool isNoDrip;
    bool isSkimp;
    isNoDrip = ui.checkBox_IsNoDrip->isChecked();
    isSkimp = ui.checkBox_IsSkimp->isChecked();
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
    int pumpNo = ui.comboBox_pumpNo->currentData().toInt();
    int paperId = ui.comboBox_PaperName->currentData().toInt();
    int reagentType = ui.checkBox_IsSpecificReagent->isChecked()?1:0;
    QVector<ReagentModel> reagentVect = ReagentDao::instance()->selectReagent(m_strCompany_ID.toInt());
    // 泵号校验
    if(reagentType == 0) // 通用试剂
    {
        for(ReagentModel& reagent : reagentVect)
        {
            if(reagent.getID() == _reagent.getID()) continue; // 忽略自己
            if(reagent.getPumpNo() == pumpNo)
            {
                MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1842"), MyMessageBox::Ok,"OK","");
                return;
            }
        }
    }else // 专用试剂
    {
        for(ReagentModel& reagent : reagentVect)
        {
            if(reagent.getID() == _reagent.getID()) continue; // 忽略自己
            if(reagent.getReagentType() == 0 && reagent.getPumpNo() == pumpNo)
            {
                MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1843"), MyMessageBox::Ok,"OK","");
                return;
            }
        }
    }
    _reagent.setPaperId(paperId);
    _reagent.setReagentType(reagentType);
    _reagent.setPumpNo(pumpNo);
    _reagent.setReagentName(strName);
    _reagent.setIsSkimp(isSkimp);
    _reagent.setCompanyID(m_strCompany_ID.toInt());
    _reagent.setIsNoDrip(isNoDrip);
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
    // TODO::WangZ
//    auto ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1278"), MyMessageBox::Ok|MyMessageBox::No, GlobalData::LoadLanguageInfo("K1181"), GlobalData::LoadLanguageInfo("K1134"));
//    if (ret == MyMessageBox::No)
//    {
        this->close();
//        return;
//    }
//    InstrumentStateModel *_InstrumentState(InstrumentStateModel::instance());
//    auto state = _InstrumentState->getMachineState();
//    if ((state.state == _InstrumentState->enumRuning) || (state.state == _InstrumentState->enumMaintain))
//    {
//        MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1711"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo("K1181"), "");
//        return;
//    }
//    Instrument::instance()->closeSocket();
//    QString program = QCoreApplication::applicationFilePath();
//    QStringList arguments = QCoreApplication::arguments();
//    QProcess::startDetached(program, arguments);
//    QCoreApplication::instance()->quit();
}

void AddReagent::on_pushButton_Cancel_clicked()
{
	this->close();
}
