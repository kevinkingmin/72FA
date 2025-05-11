#include "SelectProcessDialog.h"
#include "ui_SelectProcessDialog.h"
#include <QMessageBox>
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/Instrument/Instrument.h"
#include "src/comm/Global.h"
#include "src/comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

SelectProcessDialog::SelectProcessDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::SelectProcessDialog)
  ,_StartPosReg(QRegExp("^[1-9]$|^[1-6][0-9]$|^7[0-2]$"))
  ,m_btnVect{}
  ,_isCloseBtn(false)
  ,_instrState(InstrumentStateModel::instance())
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background-color:#FFFFFFFF;");
    creatBtns();
    //请选择要执行的时序
    //GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180")
    ui->label_2->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1614"));
    ui->btnConfig->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
}

SelectProcessDialog::~SelectProcessDialog()
{
    delete ui;
}

void SelectProcessDialog::showEvent(QShowEvent *)
{
    centerDisplay();
    //creatBtns();
    if(_instrState->getMachineState().state==InstrumentStateModel::enumRuning||_instrState->getMachineState().state==InstrumentStateModel::enumPause)
    {
        updateBtnState();
    }
}

void SelectProcessDialog::creatBtns()
{
    QVector<QPushButton*>btnVect;
    m_btnVect.swap(btnVect);
    auto fun=[this](QString id,QString btnText)
    {
        auto btn = new QPushButton(this);
        btn->setObjectName(id);
        btn->setText(btnText);
        btn->setCheckable(true);
        btn->setChecked(true);
        btn->setProperty("btnStyle","selectBtn1");
        ui->vLayoutBtn->addWidget(btn);
        m_btnVect.push_back(btn);
        connect(btn, &QPushButton::clicked, this,
                [=]()
        {
            QString select_btn_txt = "";
            select_btn_txt = btn->text();
            int click_index = 0;
            bool btn_selected = btn->isChecked();
            for (auto it : m_btnVect)
            {
                it->setChecked(true);
            }
            //if (select_btn_txt == "润湿")
            if (select_btn_txt == GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1599"))
            {
                btn->setChecked(btn_selected);//btn_selected
            }
            else
            {
                for (auto it : m_btnVect)
                {
                    click_index++;
                    QString select_btn_txt1 = "";
                    select_btn_txt1 = it->text();
                    it->setChecked(false);
                    if (select_btn_txt1 == select_btn_txt)
                    {
                        it->setChecked(true);
                        break;
                        //it->setChecked(true);
                    }
                }
            }
        }
        );
    };

    //GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111")
    //   fun("1",tr("润湿"));
    //   fun("2",tr("加样本"));
    //   fun("3",tr("清洗"));
    //   fun("4",tr("加酶"));
    //   fun("5",tr("二次清洗"));
    //   fun("6",tr("加底物"));
    //   fun("7",tr("加蒸馏水"));
    //if (Global::g_company_id != 2)
    //{
    //	fun("8", tr("加终止液"));
    //}
    //fun("9",tr("干燥"));
    //fun("10", tr("拍照"));
    //SELECT * FROM tprocess_para WHERE companyId=4 GROUP BY groupId

    //auto map = Instrument::instance()->getGroupMap();
    bool bResult;
    auto dao1 = AnalysisUIDao::instance();
    int company_id = dao1->SelectSaveSetById(&bResult, 5).toInt();

    if(company_id==6){
        QMap<int, QString> result_map = dao1->MGroupIdMap(&bResult, company_id);
        QMap<int, QString>::const_iterator i = result_map.constBegin();
        while (i != result_map.constEnd()) {
            //qDebug() << "key: " << i.key();
            //qDebug() << "value: " << i.value();
            int value = i.value().toInt();
            switch (value)
            {
            case 1:
                fun("1", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1084"));
                break;
            case 2:
                fun("2", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1085"));
                break;
            case 3:
                fun("3", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1086"));
                break;
            case 4:
                fun("4", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1141"));
                break;
            case 5:
                fun("5", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1088"));
                break;
            case 6:
                fun("6", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1087"));
                break;
            case 7:
                fun("7", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1139"));
                break;
            case 8:
                fun("8", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1089"));
                break;
            case 9:
                fun("9", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1140"));
                break;
            case 10:
                fun("10", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "L1092"));
                break;
            default:
                break;
            }
            ++i;
        }

        //if (Global::g_company_id != 2)
        //{
        //	fun("8", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1606"));
        //}
        //fun("9", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1607"));
        auto dao = AnalysisUIDao::instance();
        //bool bResult;
        int is_camera_open = dao->SelectSaveSetById(&bResult, 20008).toInt();
        if (is_camera_open)
        {
            fun("11", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1608"));
        }
    }else{
        int company_id = dao1->SelectSaveSetById(&bResult, 5).toInt();
        QMap<int, QString> result_map = dao1->MGroupIdMap(&bResult, company_id);
        QMap<int, QString>::const_iterator i = result_map.constBegin();
        while (i != result_map.constEnd()) {
            //qDebug() << "key: " << i.key();
            //qDebug() << "value: " << i.value();
            int value = i.value().toInt();
            switch (value)
            {
            case 1:
                fun("1", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1599"));
                break;
            case 2:
                fun("2", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1600"));
                break;
            case 3:
                fun("3", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1601"));
                break;
            case 4:
                fun("4", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1602"));
                break;
            case 5:
                fun("5", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1603"));
                break;
            case 6:
                fun("6", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1604"));
                break;
            case 7:
                fun("7", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1605"));
                break;
            case 8:
                fun("8", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1606"));
                break;
            case 9:
                fun("9", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1607"));
                break;
            default:
                break;
            }
            ++i;
        }

        //if (Global::g_company_id != 2)
        //{
        //	fun("8", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1606"));
        //}
        //fun("9", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1607"));
        auto dao = AnalysisUIDao::instance();
        //bool bResult;
        int is_camera_open = dao->SelectSaveSetById(&bResult, 20008).toInt();
        if (is_camera_open)
        {
            fun("10", GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1608"));
        }
    }

}

void SelectProcessDialog::on_pushButtonClose_clicked()
{
    _isCloseBtn = true;
    hide();
}

void SelectProcessDialog::on_btnConfig_clicked()
{
    _isCloseBtn=false;
    emit sglProcessChanged();
    hide();
}

bool SelectProcessDialog::getIsCloseBtn() const
{
    return _isCloseBtn;
}

void SelectProcessDialog::updateBtnState()
{
    auto map=Instrument::instance()->getGroupMap();

    //map.insert(10, "拍照");
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    int is_camera_open = dao->SelectSaveSetById(&bResult, 20008).toInt();
    if (is_camera_open)
    {
        map.insert(10, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1608"));
    }



    auto keys=map.keys();
    for(auto it:m_btnVect)
    {
        it->setChecked(false);
        int id=it->objectName().toInt();
        if(keys.contains(id))
            it->setChecked(true);
    }
}

QMap<int,QString> SelectProcessDialog::getSeletedPGMap()
{
    QMap<int, QString>map;
    for(auto it:m_btnVect)
    {
        if(!it->isChecked())
            continue;
        int id=it->objectName().toInt();
        map.insert(id,it->text().simplified());
    }
    return map;
}

QMap<int,QString> SelectProcessDialog::getAllPGMap()
{
    QMap<int, QString>map;
    for(auto it:m_btnVect)
    {
        int id=it->objectName().toInt();
        map.insert(id,it->text().simplified());
    }
    return map;
}

void SelectProcessDialog::resetBtn()
{
    for(auto it:m_btnVect)
    {
        it->setChecked(true);
    }
}

