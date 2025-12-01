#include "SelectProcessDialog.h"
#include "ui_SelectProcessDialog.h"
#include <QMessageBox>
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/Model/baseSet/ProcessParameterModel.h"
#include "../Include/Instrument/Instrument.h"
#include "src/comm/Global.h"
#include "src/comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/DAO/baseSet/ProcessParameterDao.h"
#include "../Include/DAO/baseSet/SystemSetDao.h"

SelectProcessDialog::SelectProcessDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::SelectProcessDialog)
  ,_StartPosReg(QRegExp("^[1-9]$|^[1-6][0-9]$|^7[0-2]$"))
  ,m_btnVect{}
  ,_allProcessParameterVect{}
  ,_isCloseBtn(false)
  ,_instrState(InstrumentStateModel::instance())
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background-color:#FFFFFFFF;");
    creatBtns();
    //请选择要执行的时序
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

    bool bResult;
    SystemSetModel systemSetModel;
    bResult = SystemSetDao::instance()->getModel(6, systemSetModel);
    ProcessParameterDao* processDao = ProcessParameterDao::instance();
    int processId = systemSetModel.getSaveSet();
    _allProcessParameterVect = processDao->getAllRows(processId);
    QSet<QString> seen;  // 辅助去重
    bResult = SystemSetDao::instance()->getModel(20008, systemSetModel);
    int isCameraOpen = systemSetModel.getSaveSet()==1;
    for(ProcessParameterModel& processStep : _allProcessParameterVect)
    {
        if(seen.contains(processStep.getActName())) continue; // 过滤重复
        if(!isCameraOpen && processStep.getActCode() == ProcessParameterModel::TAKE_PHOTO_CODE) continue; // 根据配置项过滤拍照功能
        seen.insert(processStep.getActName());
        fun(QString::number(processStep.getId()), processStep.getActName());
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
        {
            it->setChecked(true);
        }
    }
}

QMap<int,QString> SelectProcessDialog::getSeletedPGMap()
{
    QMap<int, QString>map;
    int selectId = -1;
    for(auto it:m_btnVect)
    {
        if(!it->isChecked()) continue;
        selectId = it->objectName().toInt();
        break;
    }
    if(selectId == -1) return {};
    for(ProcessParameterModel& processStep : _allProcessParameterVect)
    {
        if(processStep.getId() >= selectId)
        {
            map[processStep.getId()] = processStep.getActName();
        }
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

