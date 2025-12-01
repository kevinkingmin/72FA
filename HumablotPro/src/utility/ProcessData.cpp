#include "ProcessData.h"
#include <QMessageBox>
#include "../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include <QListView>
#include <QSet>
#include "../Include/DAO/baseSet/ProcessDao.h"
#include "../Include/DAO/baseSet/ProcessParameterDao.h"
#include "../Include/DAO/reagent/ReagentDao.h"
#include "../Include/Model/reagent/ReagentModel.h"
#include "../Include/Model/baseSet/ProcessModel.h"
#include "../Include/Model/baseSet/ProcessParameterModel.h"

ProcessData::ProcessData(QWidget *parent)
    : QDialog(parent)
    ,m_bModify(false)
    ,_doubleReg("^(0\\.0[1-9]|0\\.[1-9]\\d|[1-9]\\d?(\\.\\d{0,2})?)$")
    ,_actTypeVect{}
{
	ui.setupUi(this);
    setWindowFlags((windowFlags() & ~(Qt::WindowContextHelpButtonHint|Qt::WindowCloseButtonHint)));
    setFixedSize(width(), height());
    ui.pushButton_Save->setText(GlobalData::LoadLanguageInfo("K1141"));
    ui.pushButton_Cancel->setText(GlobalData::LoadLanguageInfo("K1134"));
    _actTypeVect.push_back(GlobalData::LoadLanguageInfo("K1771"));//加试剂
    _actTypeVect.push_back(GlobalData::LoadLanguageInfo("K1600"));//加样本
    _actTypeVect.push_back(GlobalData::LoadLanguageInfo("K1826"));//排废液
    _actTypeVect.push_back(GlobalData::LoadLanguageInfo("K1827"));//暂停
    _actTypeVect.push_back(GlobalData::LoadLanguageInfo("K1828"));//孵育
    _actTypeVect.push_back(GlobalData::LoadLanguageInfo("K1607"));//干燥
    _actTypeVect.push_back(GlobalData::LoadLanguageInfo("K1229"));//拍照


    ui.cmbStepType->clear();
    for(auto it:_actTypeVect)
    {
        ui.cmbStepType->addItem(it);
    }
    ui.cmbStepType->setView(new QListView(this));
    ui.cmbStepGroup->setEditable(true);
    ui.lblStepType->setText(GlobalData::LoadLanguageInfo("K2022"));
    ui.lblStepGroup->setText(GlobalData::LoadLanguageInfo("K2023"));
}

ProcessData::~ProcessData()
{
}

void ProcessData::SetUI(bool modify)
{
    // 设置group下拉选项
    ui.cmbStepGroup->clear();
    QList<QString> actGroupVect = ProcessParameterDao::instance()->getActionGroupNameVect(_processId.toInt());
    for(auto it:actGroupVect)
    {
        ui.cmbStepGroup->addItem(it);
    }
    ui.cmbStepGroup->setView(new QListView(this));


    if(modify)
    {
        ProcessParameterModel model;
        ProcessParameterDao* dao = ProcessParameterDao::instance();
        dao->selectModel(_stepId.toInt(), model);
        // 解析数据
        model.parsingParas();
        QString actType = model.getActType();//调用接口,获取动作名称
        if(!_actTypeVect.contains(actType))
        {
            QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180"),
                                     GlobalData::LoadLanguageInfo("K1789")+":"+actType,
                                     GlobalData::LoadLanguageInfo("K1181"));
            return;
        }
        ui.cmbStepType->setCurrentText(actType);

        //调用接口,获取动作参数，请按界面顺序排列
        QVector<QString> txtDatas;
        QVector<QString> boxDatas;
        if(actType == GlobalData::LoadLanguageInfo("K1771"))
        {
            on_cmbStepType_currentIndexChanged(0);
            ProcessParameterModel::AddReagentStrt strt;
            model.getAddReagent(strt);
            txtDatas.push_back(QString::number(strt._reagentMl, 'f', 2));
            txtDatas.push_back(QString::number(strt._drainTime, 'f', 1));
            txtDatas.push_back(QString::number(strt._backFlowMl, 'f', 2));
            boxDatas.push_back(strt._reagentName);
            boxDatas.push_back(strt._isDrainWaster?GlobalData::LoadLanguageInfo("K1700"):GlobalData::LoadLanguageInfo("K1701"));
            boxDatas.push_back(strt._isBackFlow?GlobalData::LoadLanguageInfo("K1700"):GlobalData::LoadLanguageInfo("K1701"));
        }else if(actType == GlobalData::LoadLanguageInfo("K1600")) // 加样本
        {
            on_cmbStepType_currentIndexChanged(1);
            ProcessParameterModel::SamplingStrt strt;
            model.getSampling(strt);
            txtDatas.push_back(QString::number(strt._sampleUl));
            txtDatas.push_back(QString::number(strt._innerTime));
            txtDatas.push_back(QString::number(strt._outerTime));
            boxDatas.push_back(strt._isFilling?GlobalData::LoadLanguageInfo("K1700"):GlobalData::LoadLanguageInfo("K1701"));

        }else if(actType == GlobalData::LoadLanguageInfo("K1826"))
        {
            on_cmbStepType_currentIndexChanged(2);
            ProcessParameterModel::DrainingStrt strt;
            model.getDraining(strt);
            txtDatas.push_back(QString::number(strt._drainTime));
        }else if(actType == GlobalData::LoadLanguageInfo("K1827"))
        {
            on_cmbStepType_currentIndexChanged(3);
            ProcessParameterModel::PausingStrt strt;
            model.getPausing(strt);
            txtDatas.push_back(strt._notifyMessage);
        }else if(actType == GlobalData::LoadLanguageInfo("K1828"))
        {
            on_cmbStepType_currentIndexChanged(4);
            ProcessParameterModel::BedShakingStrt strt;
            model.getBedShaking(strt);
            txtDatas.push_back(QString::number(strt._shakeTime));
            txtDatas.push_back(QString::number(strt._bedTemperature));
        }else if(actType == GlobalData::LoadLanguageInfo("K1607"))
        {
            on_cmbStepType_currentIndexChanged(5);
            ProcessParameterModel::DryingStrt strt;
            model.getDrying(strt);
            txtDatas.push_back(QString::number(strt._dryTime));
            txtDatas.push_back(QString::number(strt._fanTime));
            txtDatas.push_back(QString::number(strt._bedTemperature));
            txtDatas.push_back(QString::number(strt._heatTime));
            boxDatas.push_back(QString::number(strt._fanLevel));
        }else if(actType == GlobalData::LoadLanguageInfo("K1607")) // 拍照
        {
            on_cmbStepType_currentIndexChanged(6);
        }

        if(_txtVect.count()>txtDatas.count()+boxDatas.count())
        {
            QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180"),
                                     GlobalData::LoadLanguageInfo("K1790"),
                                     GlobalData::LoadLanguageInfo("K1181"));
            return;
        }
        int stepGroupIndex = ui.cmbStepGroup->findText(model.getActName());
        if(stepGroupIndex == -1)
        {
            ui.cmbStepGroup->setEditText(model.getActName());
        }else
        {
            ui.cmbStepGroup->setCurrentIndex(stepGroupIndex);
        }
        int txtIdx = 0, boxIdx = 0;
        for(int i=0;i<_txtVect.count();i++)
        {
            auto obj=_txtVect.at(i);
            if(obj->objectName().contains("txt"))
            {
                auto *line{static_cast<QLineEdit *>(obj)};
                line->setText(txtDatas.at(txtIdx++));
            }
            else if(obj->objectName().contains("box"))
            {
                auto *box{static_cast<QComboBox *>(obj)};
                box->setCurrentText(boxDatas.at(boxIdx++));
            }
        }
    } else
    {
        on_cmbStepType_currentIndexChanged(0);
    }
}

void ProcessData::setBModify(bool bModify)
{
    m_bModify = bModify;
}

void ProcessData::setStepId(const QString &stepId)
{
    qDebug()<<"setStepId"<<stepId;
    _stepId = stepId;//动作id
}

void ProcessData::setProcessId(const QString &processId)
{
    qDebug()<<"processId"<<processId;
    _processId = processId;//流程id
}

void ProcessData::on_pushButton_Save_clicked()
{
    QVector<QString> txtVect;//输入框数据往数据库保存的数据，按界面顺序排列
    QVector<QString> boxVect;//选择框数据往数据库保存的数据，按界面顺序排列
    for(auto obj:_txtVect)
    {
        if(obj->objectName().contains("txt"))
        {
            auto *line{static_cast<QLineEdit *>(obj)};
            txtVect.push_back(line->text().simplified());
        }
        else if(obj->objectName().contains("box"))
        {
            auto *box{static_cast<QComboBox *>(obj)};
            boxVect.push_back(box->currentText().simplified());
        }
    }

    qDebug()<<"on_pushButton_Save_clicked"<<_currentSelectStep;
    ProcessParameterModel model;
    model.setActType(ui.cmbStepType->currentText());
    if(_currentSelectStep==0)
    {
        QString reagentName = boxVect[0];
        bool isDrainWaster = boxVect[1] == GlobalData::LoadLanguageInfo("K1700");
        bool isBackFlow = boxVect[2] == GlobalData::LoadLanguageInfo("K1700");
        double reagentMl =  txtVect[0].toDouble();
        reagentMl = reagentMl < 0.001 ? 0 : reagentMl;
        double drainTime = txtVect[1].toDouble();
        drainTime = drainTime < 0.01 ? 0 : drainTime;
        double backFlowMl = txtVect[2].toDouble();
        backFlowMl = backFlowMl < 0.001 ? 0 : backFlowMl;
        ProcessParameterModel::AddReagentStrt strt(isDrainWaster, drainTime, reagentName, reagentMl, isBackFlow, backFlowMl);
        model.setActCode(ProcessParameterModel::ADD_REAGENT_CODE);
        model.setActName(ui.cmbStepGroup->currentText());
        model.setProcessId(_processId.toInt());
        QString parasStr =model.AddReagentToStr(strt);
        model.setParas(parasStr);
        model.setAddReagent(strt);
    }else if(_currentSelectStep==1)
    {
        double sampleUl = txtVect[0].toDouble();
        int innerTime = txtVect[1].toInt();
        int outerTime = txtVect[2].toInt();
        bool isFilling = boxVect[0] == GlobalData::LoadLanguageInfo("K1700");
        qDebug()<<"innerTime"<<innerTime<<outerTime;
        ProcessParameterModel::SamplingStrt strt(sampleUl, isFilling, innerTime, outerTime);
        model.setActCode(ProcessParameterModel::SAMPLING_CODE);
        model.setActName(ui.cmbStepGroup->currentText());
        model.setProcessId(_processId.toInt());
        QString parasStr =model.SamplingToStr(strt);
        model.setParas(parasStr);
        model.setSampling(strt);
    }else if(_currentSelectStep==2)
    {
        int drainTime = txtVect[0].toInt();
        ProcessParameterModel::DrainingStrt strt(drainTime);
        model.setActCode(ProcessParameterModel::DRAINING_CODE);
        model.setActName(ui.cmbStepGroup->currentText());
        model.setProcessId(_processId.toInt());
        QString parasStr =model.drainingToStr(strt);
        model.setParas(parasStr);
        model.setDraining(strt);
    }else if(_currentSelectStep==3)
    {
        QString message = txtVect[0];
        ProcessParameterModel::PausingStrt strt(message);
        model.setActCode(ProcessParameterModel::PAUSING_CODE);
        model.setActName(ui.cmbStepGroup->currentText());
        model.setProcessId(_processId.toInt());
        QString parasStr =model.PausingToStr(strt);
        model.setParas(parasStr);
        model.setPausing(strt);
    }else if(_currentSelectStep==4)
    {
        int shakeTime = txtVect[0].toInt();
        double bedTemperature = txtVect[1].toDouble();
        ProcessParameterModel::BedShakingStrt strt(shakeTime, bedTemperature);
        model.setActCode(ProcessParameterModel::BED_SHAKING_CODE);
        model.setActName(ui.cmbStepGroup->currentText());
        model.setProcessId(_processId.toInt());
        QString parasStr =model.BedShakingToStr(strt);
        model.setParas(parasStr);
        model.setBedShaking(strt);
    }else if(_currentSelectStep==5)
    {
        int dryTime = txtVect[0].toInt();
        int fanTime = txtVect[1].toInt();
        double bedTemperature = txtVect[2].toDouble();
        int shakeTime = txtVect[3].toInt();

        int fanLevel = boxVect[0].toInt();

        ProcessParameterModel::DryingStrt strt(dryTime, fanLevel, fanTime, bedTemperature, shakeTime);
        model.setActCode(ProcessParameterModel::DRYING_CODE);
        model.setActName(ui.cmbStepGroup->currentText());
        model.setProcessId(_processId.toInt());
        QString parasStr =model.dryingToStr(strt);
        model.setParas(parasStr);
        model.setDrying(strt);
    }else if(_currentSelectStep==6) // 拍照
    {
        model.setActCode(ProcessParameterModel::TAKE_PHOTO_CODE);
        model.setActName(ui.cmbStepGroup->currentText());
        model.setProcessId(_processId.toInt());
    }

    ProcessParameterDao* dao = ProcessParameterDao::instance();
    if(m_bModify)
    {
        dao->update(_stepId.toInt(), model);
    }
    else
    {
        dao->insert(model);
    }
    this->hide();
}

void ProcessData::on_pushButton_Cancel_clicked()
{
    this->hide();
}


void ProcessData::on_cmbStepType_currentIndexChanged(int index)
{
    ui.cmbStepGroup->setCurrentIndex(-1);
    _currentSelectStep = index;
    _txtVect.clear();
    ui.gridLayout->setContentsMargins(35,30,35,10);
    QLayoutItem *item(nullptr);
    while ((item = ui.gridLayout->takeAt(0)) != nullptr)
    {
        if(item->widget())
        {
            item->widget()->setParent(nullptr);
            delete item->widget();
        }
        delete item;
        item=nullptr;
    }

    auto createBox=[this](const QVector<ComboBoxData> &boxVect)
    {
        QComboBox *box=new QComboBox(this);
        box->setObjectName("box");
        for(auto it:boxVect)
            box->addItem(it.itemText,it.itemData);
        _txtVect.push_back(box);
        box->setView(new QListView(this));
        return box;
    };

    auto createEdit=[this](const QValidator * v=nullptr)
    {
        QLineEdit *edit=new QLineEdit(this);
        edit->setObjectName("txt");
        if(v!=nullptr)
            edit->setValidator(v);
        _txtVect.push_back(edit);
        return edit;
    };
    QVector<ComboBoxData>boxVect;
    if(index==0) // 加试剂
    {
        boxVect.clear();
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1772")+":",this),0,0,Qt::AlignRight);//选择试剂
        ReagentDao* dao = ReagentDao::instance();
        ProcessDao* processDao = ProcessDao::instance();
        ProcessModel processModel;
        qDebug()<<"_processId"<<_processId;
        processDao->getModel(_processId.toInt(), processModel);
        int companyId = processModel.getCompanyId();
        QVector<ReagentModel> reagentVect = dao->selectReagent(companyId);
        // 转为 QSet，自动去重
        QSet<QString> reagentNameSet = {};
        for(const ReagentModel& model : reagentVect)
        {
            if(reagentNameSet.contains(model.getReagentName())) continue;
            reagentNameSet.insert(model.getReagentName());
            boxVect.push_back(ComboBoxData(model.getReagentName(), model.getReagentName()));
        }
        ui.gridLayout->addWidget(createBox(boxVect),0,1,1,3);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1773")+":",this),1,0,Qt::AlignRight);// 试剂量
        ui.gridLayout->addWidget(createEdit(new QDoubleValidator(0,1000,2,this)),1,1,1,3);
        ui.gridLayout->addWidget(new QLabel("ml",this),1,4);

        boxVect.clear();
        boxVect.push_back(ComboBoxData(GlobalData::LoadLanguageInfo("K1700"),GlobalData::LoadLanguageInfo("K1700")));
        boxVect.push_back(ComboBoxData(GlobalData::LoadLanguageInfo("K1701"),GlobalData::LoadLanguageInfo("K1701")));
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1775")+":",this),2,0,Qt::AlignRight);// 是否排废液
        ui.gridLayout->addWidget(createBox(boxVect),2,1);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1774")+":",this),2,2,Qt::AlignRight); // 排废时间
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,1000,this)),2,3);
        ui.gridLayout->addWidget(new QLabel("s",this),2,4);


        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1143")+":",this),3,0,Qt::AlignRight);// 是否回流
        ui.gridLayout->addWidget(createBox(boxVect),3,1);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1829")+":",this),3,2,Qt::AlignRight); // 回流体积
        ui.gridLayout->addWidget(createEdit(new QDoubleValidator(0,5.0,2,this)),3,3);
        ui.gridLayout->addWidget(new QLabel("ml",this),3,4);
    }
    else if(index==1) // 加样本
    {
//        ui.gridLayout->setContentsMargins(30,100,30,0);
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1776")+":",this),0,0,Qt::AlignLeft);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,1000,this)),0,1,1,4);
        ui.gridLayout->addWidget(new QLabel("ul",this),0,5);

        boxVect.clear();
        boxVect.push_back(ComboBoxData(GlobalData::LoadLanguageInfo("K1700"),GlobalData::LoadLanguageInfo("K1700")));
        boxVect.push_back(ComboBoxData(GlobalData::LoadLanguageInfo("K1701"),GlobalData::LoadLanguageInfo("K1701")));
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1845")+":",this),1,0,1,2,Qt::AlignLeft);// 所有样本加完执行充盈
        ui.gridLayout->addWidget(createBox(boxVect),1,2);
        // 内冲
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1846"),this),2,0,Qt::AlignLeft);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,100,this)),2,1);
        ui.gridLayout->addWidget(new QLabel("s",this),2,2);
        // 外充
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1847"),this),2,3,Qt::AlignLeft);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,100,this)),2,4);
        ui.gridLayout->addWidget(new QLabel("s",this),2,5);
    }
    else if(index==2) // 排废液
    {
        ui.gridLayout->setContentsMargins(30,100,30,0);
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1831")+":",this),0,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,1000,this)),0,1);
        ui.gridLayout->addWidget(new QLabel("s",this),0,2);
    }
    else if(index==3) // 暂停
    {
        ui.gridLayout->setContentsMargins(30,100,30,0);
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1832")+":",this),0,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(nullptr),0,1);
    }
    else if(index==4) // 孵育
    {
        // 孵育时间
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1226")+":",this),0,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,1000,this)),0,1);
        ui.gridLayout->addWidget(new QLabel("min",this),0,2);

        // 孵育温度
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1778")+":",this),1,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QDoubleValidator(10.0,70.0,1,this)),1,1);
        ui.gridLayout->addWidget(new QLabel("℃",this),1,2);
    }
    else if(index==5) // 干燥
    {
        // 孵育总时间
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1781")+":",this),0,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,10000,this)),0,1,1,3);
        ui.gridLayout->addWidget(new QLabel("min",this),0,4);

        // 风扇转速
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1833")+":",this),1,0,Qt::AlignRight);
        boxVect.clear();
        for(int i=1;i<=5;i++)
        {
            boxVect.push_back(ComboBoxData(QString::number(i),QString::number(i)));
        }
        ui.gridLayout->addWidget(createBox(boxVect),1,1);
        // 风干时间
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1784")+":",this),1,2,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,10000,this)),1,3);
        ui.gridLayout->addWidget(new QLabel("min",this),1,4);

        // 温度
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1785")+":",this),2,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QDoubleValidator(10.0, 70.0, 1, this)),2,1);
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1786")+":",this),2,2);
        // 孵育时间
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,10000,this)),2,3);
        ui.gridLayout->addWidget(new QLabel("min",this),2,4);
    }
    else if(index==6) // 拍照
    {

    }

    // 设置默认数据
    for(auto obj:_txtVect)
    {
        if(obj->objectName().contains("txt"))
        {
            auto *line{static_cast<QLineEdit *>(obj)};
            line->setText("0");
        }else if(obj->objectName().contains("box"))
        {
            auto *box{static_cast<QComboBox *>(obj)};
            box->setCurrentIndex(-1);
        }
    }
}
