#include "ProcessData.h"
#include <QMessageBox>
#include "../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include <QListView>

ProcessData::ProcessData(QWidget *parent)
    : QDialog(parent)
    ,m_bModify(false)
    ,_doubleReg("^(0\\.0[1-9]|0\\.[1-9]\\d|[1-9]\\d?(\\.\\d{0,2})?)$")
    ,_actNameVect{}
{
	ui.setupUi(this);
    setWindowFlags((windowFlags() & ~(Qt::WindowContextHelpButtonHint|Qt::WindowCloseButtonHint)));
    setFixedSize(width(), height());
    ui.pushButton_Save->setText(GlobalData::LoadLanguageInfo("K1141"));
    ui.pushButton_Cancel->setText(GlobalData::LoadLanguageInfo("K1134"));
    _actNameVect.push_back(GlobalData::LoadLanguageInfo("K1599"));
    _actNameVect.push_back(GlobalData::LoadLanguageInfo("K1600"));
    _actNameVect.push_back(GlobalData::LoadLanguageInfo("K1770"));
    _actNameVect.push_back(GlobalData::LoadLanguageInfo("K1601"));
    _actNameVect.push_back(GlobalData::LoadLanguageInfo("K1771"));
    _actNameVect.push_back(GlobalData::LoadLanguageInfo("K1607"));
    ui.cmbStepType->clear();
    for(auto it:_actNameVect)
        ui.cmbStepType->addItem(it);
    ui.cmbStepType->setView(new QListView(this));
}

ProcessData::~ProcessData()
{
}

void ProcessData::SetUI()
{
    QString actName;//调用接口,获取动作名称
    if(!_actNameVect.contains(actName))
    {
        QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180"),
                                 GlobalData::LoadLanguageInfo("K1789")+":"+actName,
                                 GlobalData::LoadLanguageInfo("K1181"));
        return;
    }
    ui.cmbStepType->setCurrentText(actName);
    QVector<QString> uiDatas;//调用接口,获取动作参数，请按界面顺序排列
    if(_txtVect.count()>uiDatas.count())
    {
        QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180"),
                                 GlobalData::LoadLanguageInfo("K1790"),
                                 GlobalData::LoadLanguageInfo("K1181"));
        return;
    }
    for(int i=0;i<_txtVect.count();i++)
    {
        auto obj=_txtVect.at(i);
        if(obj->objectName().contains("txt"))
        {
            auto *line{static_cast<QLineEdit *>(obj)};
            line->setText(uiDatas.at(i));
        }
        else if(obj->objectName().contains("box"))
        {
            auto *box{static_cast<QComboBox *>(obj)};
            box->setCurrentText(uiDatas.at(i));
        }
    }
}

void ProcessData::setBModify(bool bModify)
{
    m_bModify = bModify;
}

void ProcessData::setStepId(const QString &stepId)
{
    _stepId = stepId;//动作id
}

void ProcessData::setProcessId(const QString &processId)
{
    _processId = processId;//流程id
}

void ProcessData::on_pushButton_Save_clicked()
{
    QVector<QString>valueVect;//往数据库保存的数据，按界面顺序排列
    for(auto obj:_txtVect)
    {
        if(obj->objectName().contains("txt"))
        {
            auto *line{static_cast<QLineEdit *>(obj)};
            valueVect.push_back(line->text().simplified());
        }
        else if(obj->objectName().contains("box"))
        {
            auto *box{static_cast<QComboBox *>(obj)};
            valueVect.push_back(box->currentText().simplified());
        }
    }

    if(m_bModify)
    {
        //调用接口 修改
        //_processId
    }
    else
    {
        //调用接口 新增
        //_stepId
    }
}

void ProcessData::on_pushButton_Cancel_clicked()
{
    this->hide();
}


void ProcessData::on_cmbStepType_currentIndexChanged(int index)
{
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
    if(index==0)
    {
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1772")+":",this),0,0,Qt::AlignRight);
        //调用接口 boxVect= 试剂
        ui.gridLayout->addWidget(createBox(boxVect),0,1);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1773")+":",this),1,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,1000,this)),1,1);
        ui.gridLayout->addWidget(new QLabel("ul",this),1,2);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1774")+":",this),2,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,100000,this)),2,1);
        ui.gridLayout->addWidget(new QLabel("s",this),2,2);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1775")+":",this),3,0,Qt::AlignRight);
        boxVect.clear();
        boxVect.push_back(ComboBoxData(GlobalData::LoadLanguageInfo("K1700"),GlobalData::LoadLanguageInfo("K1700")));
        boxVect.push_back(ComboBoxData(GlobalData::LoadLanguageInfo("K1701"),GlobalData::LoadLanguageInfo("K1701")));
        ui.gridLayout->addWidget(createBox(boxVect),3,1);
    }
    else if(index==1)
    {
        ui.gridLayout->setContentsMargins(30,100,30,0);
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1776")+":",this),0,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,1000,this)),0,1);
        ui.gridLayout->addWidget(new QLabel("ul",this),0,2);
    }
    else if(index==2)
    {
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1777")+":",this),0,0,Qt::AlignRight);
        for(int i=1;i<=5;i++)
            boxVect.push_back(ComboBoxData(QString::number(i),QString::number(i)));
        ui.gridLayout->addWidget(createBox(boxVect),0,1);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1778")+":",this),1,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QRegExpValidator(_doubleReg, this)),1,1);
        ui.gridLayout->addWidget(new QLabel("℃",this),1,2);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1226")+":",this),2,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,100000,this)),2,1);
        ui.gridLayout->addWidget(new QLabel("s",this),2,2);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1775")+":",this),3,0,Qt::AlignRight);
        boxVect.clear();
        boxVect.push_back(ComboBoxData(GlobalData::LoadLanguageInfo("K1700"),GlobalData::LoadLanguageInfo("K1700")));
        boxVect.push_back(ComboBoxData(GlobalData::LoadLanguageInfo("K1701"),GlobalData::LoadLanguageInfo("K1701")));
        ui.gridLayout->addWidget(createBox(boxVect),3,1);
    }
    else if(index==3)
    {
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1772")+":",this),0,0,Qt::AlignRight);
        //调用接口 boxVect= 试剂
        ui.gridLayout->addWidget(createBox(boxVect),0,1);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1779")+":",this),1,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,9,this)),1,1);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1780")+":",this),2,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,1000,this)),2,1);
        ui.gridLayout->addWidget(new QLabel("s",this),2,2);
    }
    else if(index==4)
    {
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1772")+":",this),0,0,Qt::AlignRight);
        //调用接口 boxVect= 试剂
        ui.gridLayout->addWidget(createBox(boxVect),0,1);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1773")+":",this),1,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,10000,this)),1,1);
        ui.gridLayout->addWidget(new QLabel("ul",this),1,2);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1775")+":",this),2,0,Qt::AlignRight);
        boxVect.clear();
        boxVect.push_back(ComboBoxData(GlobalData::LoadLanguageInfo("K1700"),GlobalData::LoadLanguageInfo("K1700")));
        boxVect.push_back(ComboBoxData(GlobalData::LoadLanguageInfo("K1701"),GlobalData::LoadLanguageInfo("K1701")));
        ui.gridLayout->addWidget(createBox(boxVect),2,1);
    }
    else if(index==5)
    {
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1781")+":",this),0,0,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,10000,this)),0,1,1,3);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1782")+":",this),1,0,Qt::AlignRight);
        boxVect.push_back(ComboBoxData(GlobalData::LoadLanguageInfo("K1698"),GlobalData::LoadLanguageInfo("K1698")));
        boxVect.push_back(ComboBoxData(GlobalData::LoadLanguageInfo("K1699"),GlobalData::LoadLanguageInfo("K1699")));
        auto box=createBox(boxVect);
        box->setMinimumWidth(95);
        ui.gridLayout->addWidget(box,1,1);
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1783")+":",this),1,2,Qt::AlignRight);
        boxVect.clear();
        for(int i=1;i<=5;i++)
            boxVect.push_back(ComboBoxData(QString::number(i),QString::number(i)));
        ui.gridLayout->addWidget(createBox(boxVect),1,3);
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1784")+":",this),1,4);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,10000,this)),1,5);
        ui.gridLayout->addWidget(new QLabel("s",this),1,6);

        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1777")+":",this),2,0,Qt::AlignRight);
        boxVect.clear();
        for(int i=1;i<=5;i++)
            boxVect.push_back(ComboBoxData(QString::number(i),QString::number(i)));
        ui.gridLayout->addWidget(createBox(boxVect),2,1);
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1785")+":",this),2,2,Qt::AlignRight);
        ui.gridLayout->addWidget(createEdit(new QRegExpValidator(_doubleReg, this)),2,3);
        ui.gridLayout->addWidget(new QLabel(GlobalData::LoadLanguageInfo("K1786")+":",this),2,4);
        ui.gridLayout->addWidget(createEdit(new QIntValidator(0,10000,this)),2,5);
        ui.gridLayout->addWidget(new QLabel("s",this),2,6);
    }
}
