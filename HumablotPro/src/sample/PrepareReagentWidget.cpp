#include "PrepareReagentWidget.h"
#include "ui_PrepareReagentWidget.h"
#include <QMessageBox>
#include "subDialog/SelectProcessDialog.h"
#include "src/comm/CustomButton.h"
#include "src/main/subDialog/ProgressDialog.h"
#include "../BLL/reagent/ReagentBLL.h"
#include "../Model/reagent/ReagentModel.h"
#include "../BLL/baseSet/ProcessParaBLL.h"
#include "../BLL/reagent/ProcessReagentBLL.h"
#include "../Model/reagent/ProcessReagentModel.h"
#include "../Model/sample/SampleTestModel.h"
#include "../Model/baseSet/CommonType.h"
#include "../Model/baseSet/InstrumentStateModel.h"
#include "../Instrument/Instrument.h"
#include "../Utilities/log.h"
#include "../DAO/Analysis/AnalysisUIDao.h"
#include "src/comm/Global.h"
#include <QApplication>
#include <QMessageBox>
#include <string>
#include <QDateTime>
#include "src/comm/CustomButton.h"
#include <QSettings>
#include "src/main/subDialog/MyMessageBox.h"

#define PUMPCOUNT 9
PrepareReagentWidget::PrepareReagentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrepareReagentWidget)
  ,_btnGroup(new QButtonGroup(this))
  ,_pixPath(":/images/buttonIcon/")
  ,m_selectPDialog(nullptr)
  ,_processReagentVect{}
  ,_emptyFile("rFlowBack128.png")
  ,_flushFile("irrigationIcon.png")
  ,_readyFile("rReady.png")
  ,_delayFile("rDelay.png")
  ,_instrument(Instrument::instance())
  , m_instrState(InstrumentStateModel::instance())
{
    ui->setupUi(this);
    _btnGroup->setExclusive(false);
    // emit ChangeBtnNextSignal(true);
    createPumpBtn();
    //ui->btnSmall->setVisible(false);
    //ui->btnBig->setVisible(false);
    //ui->horizontalLayout_4
    ui->pushButtonSmall->setVisible(false);
    ui->label_4->setVisible(false);
    ui->cb_all->setVisible(false);
    ui->btnDelay->hide();
    m_postion_map.clear();
    m_postion_map.insert(1, 0);
    m_postion_map.insert(2, 0);
    m_postion_map.insert(3, 0);
    m_postion_map.insert(4, 0);
    m_postion_map.insert(5, 0);
    m_postion_map.insert(6, 0);
    m_postion_map.insert(7, 0);
    m_postion_map.insert(8, 0);
    m_postion_map.insert(9, 0);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    g_language_type = dao->SelectTargetValueDes(&bResult, "20005");

    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1074");
    ui->label_14->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1081");
    ui->btnFill_2->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1076");
    ui->label_12->setText(sz);

    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1077");
    ui->lblHint->setText(sz);

    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1078");
    ui->btnWash->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1079");
    ui->btnFill->setText(sz);

    connect(_instrument, &Instrument::sglPrepareReagentResult,this, &PrepareReagentWidget::slotPrepareReagentResult);

}

void PrepareReagentWidget::onWidgetShow() {

}

PrepareReagentWidget::~PrepareReagentWidget()
{
    delete ui;
}

void PrepareReagentWidget::setSelectPDialog(SelectProcessDialog *selectPDialog)
{
    m_selectPDialog = selectPDialog;
}
//显示试剂总用量
void PrepareReagentWidget::ShowCountReagentDose(int reagentId,int index,int paper_id)
{
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    int test_count = m_listTest.size();
    int test_count1 = 0;
    int company_id = dao->SelectSaveSetById(&bResult, 5).toInt();

    std::map<int, int> countMap;
    for (const auto& obj : m_listTest) {
        countMap[obj->getPaperId()]++;
    }

    if (paper_id != 111)
    {
        auto it = countMap.find(paper_id);  // 在 map 中查找指定的键
        if (it != countMap.end()) {
            test_count1 = it->second;
        }
    }
    else
    {
        test_count1 = test_count;
    }
    int need_volumn = _instrument->getUnitReagentVolumn(company_id, reagentId);
    float need_volumn1 = 1;

    if (index < 4)
    {
        need_volumn1 = ((float)(test_count1 * need_volumn)) / 1000;
    }
    else
    {
        need_volumn1 = ((float)(test_count * need_volumn)) / 1000;
    }

    QString exe_path = QCoreApplication::applicationDirPath() + "/PrepareReagent.ini";
    QSettings config_set(exe_path, QSettings::IniFormat);
    //double dParameterValue;
    config_set.beginGroup("Add");
    //dParameterValue = config_set.value("PrepareReagent").toFloat();

    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1085");

    QString str = "";
    if (index == 0)
    {
        str = QString(sz+":\n\r%1(mL)").arg(need_volumn1 + config_set.value("PrepareReagent_1").toFloat());
        ui->label->setText(str);
    }
    if (index == 1)
    {
        str = QString(sz + " :\n\r%1(mL)").arg(need_volumn1 + config_set.value("PrepareReagent_2").toFloat());
        ui->label_2->setText(str);
    }
    if (index == 2)
    {
        str = QString(sz + ":\n\r%1(mL)").arg(need_volumn1 + config_set.value("PrepareReagent_3").toFloat());
        ui->label_3->setText(str);
    }
    if (index == 3)
    {
        str = QString(sz + ":\n\r%1(mL)").arg(need_volumn1 + config_set.value("PrepareReagent_4").toFloat());
        ui->label_5->setText(str);
    }
    if (index == 4)
    {
        str = QString(sz + ":\n\r%1(mL)").arg(need_volumn1 + config_set.value("PrepareReagent_5").toFloat());
        ui->label_6->setText(str);
    }
    if (index == 5)
    {
        str = QString(sz + "\n\r%1(mL)").arg(need_volumn1 + config_set.value("PrepareReagent_6").toFloat());
        ui->label_7->setText(str);
    }
    if (index == 6)
    {
        str = QString(sz + ":\n\r%1(mL)").arg(need_volumn1 + config_set.value("PrepareReagent_7").toFloat());
        ui->label_8->setText(str);
    }
    if (index == 7)
    {
        str = QString(sz + ":\n\r%1(mL)").arg(need_volumn1 + config_set.value("PrepareReagent_8").toFloat());
        ui->label_9->setText(str);
    }
    if (index == 8)
    {
        str = QString(sz + ":\n\r%1(mL)").arg(need_volumn1 + config_set.value("PrepareReagent_9").toFloat());
        ui->label_10->setText(str);
    }
}

void PrepareReagentWidget::createPumpBtn()
{
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1080");

    auto empty="rFlowBack128.png";//表明泵没有被占用
    for (int i = 0; i < PUMPCOUNT; i++)
    {
        auto btn=new CustomButton(this);
        btn->setLblPixSize(128,64);
        btn->setPixPath(_pixPath+empty);

        btn->setUpText(QString::number(i + 1)+ sz);//".位置");
        btn->setObjectName(QString::number(i));
        btn->setReagentName("");
        btn->setCheckable(false);
        btn->setBtnId(i);
        btn->setProperty("btnStyle","btnReagentPosStyle");
        btn->setProperty(GlobalData::getPropertyName(),PumpPosState::enumEmpty);
        ui->hLayPump->addWidget(btn);
        connect(btn, &QPushButton::clicked, this, [=](bool checked){
            QPushButton *senderButton = qobject_cast<QPushButton *>(sender());
            if (senderButton) {
                qDebug() << "Button clicked!"<<senderButton->objectName();
                senderButton->setChecked(false);
                QList<uint8_t> pumpListMin;
                pumpListMin.append(static_cast<uint8_t>(senderButton->objectName().toUInt()+1));
                for(auto r:m_reagentVect){
                    if(static_cast<uint>(r->getPumpNo())  == senderButton->objectName().toUInt()){
                        _instrument->prepareReagent(pumpListMin,"min");
                        m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1715"));
                        m_progressDialog->exec();
                    }
                }
            }
        });
        _btnGroup->addButton(btn);
    }


    on_chk_1_toggled(false);
}

void PrepareReagentWidget::slot_btnGroupClicked(int i)
{
    int index = 0;
    index = i;
}


void PrepareReagentWidget::createPumpBtn2(QPushButton * pushButton, bool selected_status)
{
    auto empty = "irrigationIcon.png";
    QImage image(_pixPath + empty);
    QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pushButton->setIcon(QIcon(fitpixmap));
    pushButton->setProperty("btnStyle", "btnReagentPosStyle");
    pushButton->setProperty(GlobalData::getPropertyName(), PumpPosState::enumEmpty);
    pushButton->setIconSize(QSize(image.width(), image.height()));
    if (selected_status)
    {
        pushButton->setChecked(true);//->setCheckable(true);
    }
    else
    {
        pushButton->setChecked(false);
    }
}

void PrepareReagentWidget::changeIcon(const QString &fileName, PumpPosState state)
{
    QMap<int, ushort>map;
    map.clear();
    /*if (!InstrumentStateModel::instance()->getMachineState().canRun)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1411"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }*/

    for(auto &it:_btnGroup->buttons())
    {
        if(it->isChecked())
        {
            auto btn=reinterpret_cast<CustomButton*>(it);
            btn->setProperty(GlobalData::getPropertyName(),state);
            btn->setPixPath(_pixPath+fileName);
            btn->setChecked(false);
            auto pumpNo = btn->objectName().toInt();

            if (state == PumpPosState::enumDelay)
            {
                QVector<pReagent> reagentVect = GetReagentVect();
                QString volumn1;
                for (auto r : reagentVect)
                {
                    if (r->getPumpNo() == pumpNo)
                    {
                        volumn1.sprintf("%.2f ml", r->getFluidMeasure());
                    }
                }
                auto strVolumn = btn->getVolumn();
                auto volumn = static_cast<ushort>(volumn1.left(volumn1.length() - 2).toDouble() * 1000);
                map.insert(pumpNo, volumn);
                m_finish_map.insert(pumpNo, 1);
            }

            if (state == PumpPosState::enumReady)
            {
                m_finish_map.insert(pumpNo, 1);
                for (const auto& key : m_preview_wash_map.keys()) {
                    int key_value = key;
                    if (pumpNo == key_value)
                    {
                        m_preview_wash_map.remove(key_value);
                    }
                }
            }

            if (state == PumpPosState::enumDelay)
            {
                if (map.size() == 0)
                {
                    MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1413"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                    return;
                }
                if (map.isEmpty())
                {
                    MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1414"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                    return;
                }

                m_preview_wash_map = map;

                for (const auto& key : m_finish_map.keys()) {
                    int key_value = key;
                    m_finish_map.insert(key_value,1);
                }
            }
        }
    }
    emit sglPumpStateChanged();
    ui->cb_all->setChecked(false);
    int finish_count = 0;
    int key_value = 0;
    for (const auto& key : m_finish_map.keys()) {
        if (m_finish_map.value(key) == 1 || m_finish_map.value(key)>0)
        {
            finish_count++;
        }
        key_value = key;
        switch (key_value)
        {
        case 0:
            ui->chk_1->setChecked(false);
            break;
        case 1:
            ui->chk_2->setChecked(false);
            break;
        case 2:
            ui->chk_3->setChecked(false);
            break;
        case 3:
            ui->chk_4->setChecked(false);
            break;
        case 4:
            ui->chk_5->setChecked(false);
            break;
        case 5:
            ui->chk_6->setChecked(false);
            break;
        case 6:
            ui->chk_7->setChecked(false);
            break;
        case 7:
            ui->chk_8->setChecked(false);
            break;
        case 8:
            ui->chk_9->setChecked(false);
            break;
        default:
            break;
        }
    }
    //如果操作
    if (m_system_liquid_finish && finish_count == m_reagentVect.size())
    {
        //if (!m_paper_connect_reagent_flage)
        // {
        emit ChangeBtnNextSignal(true);
        // }
    }
    else
    {
        emit ChangeBtnNextSignal(false);
    }
    //emit ChangeBtnNextSignal(true);//测试阶段忽略灌注限制
}
void PrepareReagentWidget::getIncubation()
{
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    int company_id = dao->SelectSaveSetById(&bResult, 5).toInt();
    auto groupStepMap = m_selectPDialog->getSeletedPGMap();
    auto paperIds = getPaperIds();
    auto groupIds = groupStepMap.keys().toVector();//选中的所有时序
    QVector<int> v_group_ids;
    auto reagentIdAndParaIdMap = ProcessParaBLL().getReagentIdAndParaIds(v_group_ids,company_id);
}

void PrepareReagentWidget::on_btnWash_clicked()
{
    auto state = m_instrState->getMachineState();
    /*if (!state.canRun)
    {
        //QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("当前状态不允许运行，请先进行初始化操作"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1411"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
        return;
    }*/

    m_system_liquid_finish = true;
    Global::g_run_or_maintenance_flage = 1;
    //系统液灌注
    //_instrument->maintain(eSystemLiquidWash);
    pumpList.clear();
    pumpList.append(10);
    _instrument->prepareReagent(pumpList,"max");
    m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1718"));//tr("正在清洗,请稍候......"));
    m_progressDialog->exec();
    /*state = m_instrState->getMachineState();
    if (state.state == InstrumentStateModel::enumStandby)
    {
        auto empty = ":/images/buttonIcon/rReady.png";
        QImage image(empty);
        QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->btnIrrigate->setIcon(QIcon(fitpixmap));
        ui->btnIrrigate->setIconSize(QSize(image.width(), image.height()));
        QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1082");
        ui->lblHint->setText(sz);
        m_isIrrigate = true;
        Global::g_SystemLiquidPerfusion = 1;
        int finish_count = 0;
        for (const auto& key : m_finish_map.keys()) {
            if (m_finish_map.value(key) == 1 || m_finish_map.value(key) > 0)
            {
                finish_count++;
            }
        }
        if (m_system_liquid_finish && finish_count == m_reagentVect.size())
        {
            if (!m_paper_connect_reagent_flage)
            {
                emit ChangeBtnNextSignal(true);
            }
        }
        else
        {
            emit ChangeBtnNextSignal(false);
        }
        emit ChangeBtnNextSignal(true);//测试阶段忽略灌注限制
        ui->btnWash->setChecked(true);
    }
    else
    {
        auto empty = ":/images/buttonIcon/irrigationIcon.png";
        QImage image(empty);
        QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->btnIrrigate->setIcon(QIcon(fitpixmap));
        ui->btnIrrigate->setIconSize(QSize(image.width(), image.height()));
        QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1083");
        ui->lblHint->setText(sz);
        m_isIrrigate = false;
        m_jump_irrigate = 1;
        ui->btnWash->setChecked(false);
    }*/
}

void PrepareReagentWidget::on_btnFill_2_clicked()
{
    if (!all_select_flage)
    {
        auto btns = _btnGroup->buttons();
        int index = 0;

        for (auto &it : btns)
        {
            auto btn = reinterpret_cast<CustomButton*>(it);
            auto pumpNo = btn->objectName().toInt();
            for (auto r : m_reagentVect)
            {
                if (r->getPumpNo() == pumpNo)
                {
                    if (index == 0)
                    {
                        ui->chk_1->setChecked(true);
                    }
                    if (index == 1)
                    {
                        ui->chk_2->setChecked(true);
                    }
                    if (index == 2)
                    {
                        ui->chk_3->setChecked(true);
                    }
                    if (index == 3)
                    {
                        ui->chk_4->setChecked(true);
                    }
                    if (index == 4)
                    {
                        ui->chk_5->setChecked(true);
                    }
                    if (index == 5)
                    {
                        ui->chk_6->setChecked(true);
                    }
                    if (index == 6)
                    {
                        ui->chk_7->setChecked(true);
                    }
                    if (index == 7)
                    {
                        ui->chk_8->setChecked(true);
                    }
                    if (index == 8)
                    {
                        ui->chk_9->setChecked(true);
                    }
                    break;
                }
            }
            index++;
        }
        all_select_flage = true;
        ui->btnFill_2->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1637"));//"取消全选");
    }
    else
    {
        ui->chk_1->setChecked(false);
        ui->chk_2->setChecked(false);
        ui->chk_3->setChecked(false);
        ui->chk_4->setChecked(false);
        ui->chk_5->setChecked(false);
        ui->chk_6->setChecked(false);
        ui->chk_7->setChecked(false);
        ui->chk_8->setChecked(false);
        ui->chk_9->setChecked(false);

        all_select_flage = false;
        ui->btnFill_2->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1081"));//"全选");
    }
    getCheckBtn();
}


void PrepareReagentWidget::on_btnFill_clicked()
{
    m_isIrrigate = true;
    m_system_liquid_finish = true;
    m_jump_irrigate = 2;
    auto empty = ":/images/buttonIcon/rReady.png";
    QImage image(empty);
    QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->btnIrrigate->setIcon(QIcon(fitpixmap));
    ui->btnIrrigate->setIconSize(QSize(image.width(), image.height()));
    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1084");
    ui->lblHint->setText(sz);
    int finish_count = 0;
    for (const auto& key : m_finish_map.keys()) {
        if (m_finish_map.value(key) == 1 || m_finish_map.value(key) > 0)
        {
            finish_count++;
        }
    }
    if (m_system_liquid_finish && finish_count == m_reagentVect.size())
    {
        //if (!m_paper_connect_reagent_flage)
        // {
        emit ChangeBtnNextSignal(true);
        //}
    }
    // emit ChangeBtnNextSignal(true);//测试阶段忽略灌注限制
}

QVector<PrepareReagentWidget::pReagent> PrepareReagentWidget::GetReagentVect() {
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    int company_id = dao->SelectSaveSetById(&bResult, 5).toInt();
    auto groupStepMap = m_selectPDialog->getSeletedPGMap();
    auto paperIds = getPaperIds();
    auto groupIds = groupStepMap.keys().toVector();//选中的所有时序
    auto reagentIdAndParaIdMap = ProcessParaBLL().getReagentIdAndParaIds(groupIds, company_id);
    QVector<ProcessReagentModel>processReagentVect;
    _processReagentVect.swap(processReagentVect);
    QVector<pReagent>reagentVect;
    QVector<int> usedPosVect;

    for (auto it = reagentIdAndParaIdMap.begin(); it != reagentIdAndParaIdMap.end(); it++)
    {
        if (it.key() == -1||it.key() == -2)
        {
            for (auto paperId : paperIds)
            {
                int para_value = it.key();
                int paper_id = paperId;
                int processParaId = it.value();
                auto r = ReagentBLL().getReagent_new(para_value, paperId, company_id);
                if (r.isNull())
                {
                    MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1415"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                    return reagentVect;
                }
                if (r->getPumpNo() >= 0)
                    usedPosVect.push_back(r->getPumpNo());
                reagentVect.push_back(r);
                if (m_flushing_type == 1)
                {
                    r->setFluidMeasure(r->getFluidMeasureSmall());
                }
                auto m = getProcessReagentModel(0, r, it.value(), paperId);
                _processReagentVect.push_back(m);
            }
        }
        else
        {

            auto r = ReagentBLL().getReagent(it.key(), 0, company_id);
            if (r.isNull())
            {
                MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1415"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                return reagentVect;
            }

            if (m_flushing_type == 1)
            {
                r->setFluidMeasure(r->getFluidMeasureSmall());
            }

            if (r->getPumpNo() >= 0)
                usedPosVect.push_back(r->getPumpNo());
            reagentVect.push_back(r);

            auto m = getProcessReagentModel(0, r, it.value(), 0);
            _processReagentVect.push_back(m);
        }
    }

    QVector<int> pumpNumberMap;
    int i = 0;
    int j = reagentVect.count() - paperIds.count();
    for (int i = 0; i < paperIds.count(); i++)
    {
        int paperId = paperIds[i];
        for (auto it = reagentVect.begin(); it < reagentVect.end(); it++)
        {
        }
    }

    if ((pumpNumberMap.count() + j) > PUMPCOUNT)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1416"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return reagentVect;
    }

    if (!setReagentWithPump(usedPosVect, reagentVect))
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1417"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return reagentVect;
    }
    return reagentVect;
}

void PrepareReagentWidget::CloseAllLight()
{
    /*_instrument->lightControl(0x02, 0);
    Sleep(150);
    _instrument->lightControl(0x03, 0);
    Sleep(150);
    _instrument->lightControl(0x04, 0);
    Sleep(150);
    _instrument->lightControl(0x05, 0);
    Sleep(150);
    _instrument->lightControl(0x06, 0);
    Sleep(150);
    _instrument->lightControl(0x07, 0);
    Sleep(150);
    _instrument->lightControl(0x08, 0);
    Sleep(150);
    _instrument->lightControl(0x09, 0);
    Sleep(150);
    _instrument->lightControl(0x0A, 0);
    Sleep(150);*/
}
//重新刷新泵得显示
void PrepareReagentWidget::updatePumpBtnByTest()
{ 
    all_select_flage = false;
    ui->btnFill_2->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1081"));//"全选");
    ui->label_4->setVisible(false);
    ui->groupBox_2->setVisible(true);
    ui->groupBox->setVisible(true);
    m_reagentVect.clear();
    QString str = "";
    str = QString("").arg("");
    ui->label->setText(str);
    str = QString("").arg("");
    ui->label_2->setText(str);
    str = QString("").arg("");
    ui->label_3->setText(str);
    str = QString("").arg("");
    ui->label_5->setText(str);
    str = QString("").arg("");
    ui->label_6->setText(str);
    str = QString("").arg("");
    ui->label_7->setText(str);
    str = QString("").arg("");
    ui->label_8->setText(str);
    str = QString("").arg("");
    ui->label_9->setText(str);
    str = QString("").arg("");
    ui->label_10->setText(str);
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    int company_id = dao->SelectSaveSetById(&bResult, 5).toInt();
    auto groupStepMap=m_selectPDialog->getSeletedPGMap();
    auto paperIds=getPaperIds();
    QVector<int> groupIds=groupStepMap.keys().toVector();//选中的所有时序

    auto reagentIdAndParaIdMap = ProcessParaBLL().getReagentIdAndParaIds(groupIds,company_id);
    if (reagentIdAndParaIdMap.size() == 0)
    {
        //MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "K1674该厂家膜条未添加实验流程，请联系技术支持人员。", MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
        if (groupIds.count() == 10)
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1674"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
            return;
        }
    }
    QVector<ProcessReagentModel> processReagentVect;
    _processReagentVect.swap(processReagentVect);
    QVector<pReagent>reagentVect;
    QVector<int> usedPosVect;
    for(auto it=reagentIdAndParaIdMap.begin();it!=reagentIdAndParaIdMap.end();it++)
    {
        if(it.key()==-1||it.key()==-2)
        {
            for(auto paperId:paperIds)
            {
                int para_value = it.key();
                int paper_id = paperId;
                QString reagent_name = dao->SelectReagentById(&bResult, paper_id);
                int processParaId = it.value();
                auto r=ReagentBLL().getReagent_new(para_value,paperId, company_id);
                if(r.isNull())
                {
                    QString sz = QString("%2 %1 %3").arg(reagent_name).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1418")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1419"));
                    MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), sz, MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                    m_paper_connect_reagent_flage = true;
                    return;
                }
                if(r->getPumpNo()>=0)
                    usedPosVect.push_back(r->getPumpNo());
                reagentVect.push_back(r);

                if (m_flushing_type == 1)
                {
                    r->setFluidMeasure(r->getFluidMeasureSmall());
                }
                auto m=getProcessReagentModel(0,r,it.value(),paperId);
                _processReagentVect.push_back(m);
            }
        }
        else
        {

            auto r=ReagentBLL().getReagent(it.key(),0, company_id);
            if(r.isNull())
            {
                MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"),GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1415"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                return;
            }
            if (m_flushing_type == 1)
            {
                r->setFluidMeasure(r->getFluidMeasureSmall());
            }
            if(r->getPumpNo()>=0)
                usedPosVect.push_back(r->getPumpNo());
            reagentVect.push_back(r);

            auto m=getProcessReagentModel(0,r,it.value(),0);
            _processReagentVect.push_back(m);
        }
    }
    QVector<int> pumpNumberMap;

    int i = 0;
    int j = reagentVect.count() - paperIds.count();

    for (auto it = reagentVect.begin();it< reagentVect.end();it++)
    {
        if (i < paperIds.count()) {
            int pumpNo = it->data()->getPumpNo();
            if (pumpNumberMap.indexOf(pumpNo))
            {
                pumpNumberMap.push_back(pumpNo);
            }
        }
        i++;
    }

    QString pump_sz = "";
    for (int i = 0; i < pumpNumberMap.count(); i++)
    {
        int iPumpNo = pumpNumberMap[i];
        int iPumpNumber = 0;
        int kk = 0;
        for (auto it = reagentVect.begin(); it < reagentVect.end(); it++)
        {
            if (kk < paperIds.count()) {
                if (it->data()->getPumpNo() == iPumpNo)
                {
                    iPumpNumber++;
                    pump_sz += QString("%3：%1  %4 %2\r\n").arg(it->data()->getReagentName()).arg(iPumpNo+1).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1136")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1514"));
                }
            }
            kk++;
        }

        if (iPumpNumber > 1)
        {
            ui->groupBox_2->setVisible(false);
            ui->groupBox->setVisible(false);
            ui->label_4->setVisible(true);
            ui->label_4->move(500,330);
            QString tip1 = "";
            tip1 = QString("%2\r\n%1").arg(pump_sz).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1420"));
            ui->label_4->setText(tip1);
            QString tip = "";
            tip = QString("%2\r\n%1").arg(pump_sz).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1421"));
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tip, MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            emit ChangeBtnNextSignal(false); //btn tmp
            // emit ChangeBtnNextSignal(true);//测试阶段忽略灌注限制
            return;
        }
    }

    m_Enzyme_number = pumpNumberMap.count();

    if ((pumpNumberMap.count() + j) > PUMPCOUNT)
    {
        MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1416"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    if(!setReagentWithPump(usedPosVect,reagentVect))
    {
        MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1417"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    updateBtnByReagents(reagentVect);
    m_reagentVect = reagentVect;
    on_chk_1_toggled(false);
}

QVector<int> PrepareReagentWidget::getPaperIds()
{
    QVector<int>paperIds{};
    for(auto it:m_listTest)
    {
        if(!paperIds.contains(it->getPaperId()))
            paperIds.push_back(it->getPaperId());
    }
    return paperIds;
}

bool PrepareReagentWidget::setReagentWithPump(QVector<int>usedPos,QVector<pReagent>&regentVect)
{
    QVector<int>freePos;
    for(int i=0;i<PUMPCOUNT;i++)
    {
        if(!usedPos.contains(i))
            freePos.push_back(i);
    }

    int j=0;
    for(auto &it:regentVect)
    {
        if(it->getPumpNo()<0)
        {
            if(j>freePos.count()-1)
            {
                return false;
            }
            it->setPumpNo(freePos[j]);
            for(auto & r:_processReagentVect)
            {
                if(r.getReagentId()==it->getID())
                    r.setPumpNo(freePos[j]);
            }
            j++;
        }
    }
    return true;
}

ProcessReagentModel PrepareReagentWidget::getProcessReagentModel(int id, pReagent r,int processParaId,int paperId)
{
    ProcessReagentModel m;
    m.setId(id);
    m.setPumpNo(r->getPumpNo());
    m.setPaperId(paperId);
    m.setReagentId(r->getID());
    if (m_flushing_type == 0)
    {
        m.setFluidMeasure(r->getFluidMeasure());
    }
    else
    {
        m.setFluidMeasure(r->getFluidMeasureSmall());
    }

    m.setProcessParaId(processParaId);
    return m;
}

void PrepareReagentWidget::updateBtnByReagents(const QVector<pReagent> &reagentVect)
{
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    int company_id = dao->SelectSaveSetById(&bResult, 5).toInt();
    auto btns=_btnGroup->buttons();
    int index = 0;
    for(auto &it:btns)
    {
        auto btn=reinterpret_cast<CustomButton*>(it);
        btn->reset(_pixPath+_emptyFile);
        btn->setProperty(GlobalData::getPropertyName(),PumpPosState::enumEmpty);
        btn->setLblPixSize(128, 64);
        auto pumpNo=btn->objectName().toInt();
        for(auto r:reagentVect)
        {
            if (r->getPumpNo() == pumpNo)
            {
                int id = r->getID();
                int paper_id = r->getPaperId();
                ShowCountReagentDose(id, index, paper_id);
                btn->setCheckable(true);
                btn->setProperty(GlobalData::getPropertyName(),PumpPosState::enumFlush);
                btn->setPixPath(_pixPath+_flushFile);
                QString reagent_name = r->getReagentName();
                QString reagent_id =QString::number( r->getPaperId());
                int length = 15;
                if (id > 4 && id < 11)
                {
                    QString reagent_name1 = GlobalData::LoadLanguageInfo(g_language_type, reagent_name);
                    if (reagent_name1.length() > length)
                    {
                        reagent_name1 = QString("%1\n%2").arg(reagent_name1.mid(0, length)).arg(reagent_name1.mid(length));
                    }
                    btn->setReagentName(reagent_name1);//reagent_name);
                }
                else
                {
                    QString reagent_name1 = reagent_name;
                    if (reagent_name1.length() > length)
                    {
                        reagent_name1 = QString("%1\n%2").arg(reagent_name1.mid(0, length)).arg(reagent_name1.mid(length));
                    }
                    btn->setReagentName(reagent_name1);//reagent_name);
                }

                QString volumn;
                qDebug()<<"pumpNo:"<<pumpNo;
                QString exe_path = QCoreApplication::applicationDirPath() + "/PrepareReagent.ini";
                QSettings config_set(exe_path, QSettings::IniFormat);
                config_set.beginGroup("Add");
                volumn.sprintf("%.2f ml ", config_set.value("PrepareReagent_"+QString::number(pumpNo+1)).toFloat());
                btn->setVolumn(volumn);
                break;
            }
        }
        ui->hLayPump->addWidget(btn);
        index++;
    }
    auto empty = ":/images/buttonIcon/irrigationIconSmall.png";
    QImage image(empty);
    QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->pushButtonSmall->setIcon(QIcon(fitpixmap));
}

void PrepareReagentWidget::setProgressDialog(ProgressDialog *progressDialog)
{
    m_progressDialog = progressDialog;
}

QButtonGroup *PrepareReagentWidget::getBtnGroup() const
{
    return _btnGroup;
}

QVector<ProcessReagentModel> PrepareReagentWidget::getProcessReagentVect() const
{
    return _processReagentVect;
}

void PrepareReagentWidget::setListTest(const QVector<ptrTest> &listTest)
{
    m_listTest = listTest;
}

void PrepareReagentWidget::move_chk_position()
{
    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1080");

    update();
    int add_x = -32;
    auto btns = _btnGroup->buttons();
    int index = 0;
    for (auto &it : btns)
    {
        auto btn = reinterpret_cast<CustomButton*>(it);
        btn->setLblPixSize(128, 64);
        auto pumpNo = btn->objectName().toInt();
        int btn_width = btn->width();
        int btn_x = btn->x() + btn_width/2;
        if (index == 0)
        {
            ui->chk_1->setText(sz + "1");
            ui->chk_1->move(btn_x + add_x, ui->chk_1->y());
            ui->label->move(btn_x + add_x, ui->label->y());

            ui->chk_1->resize(100, 30);
            update();
        }
        if (index == 1)
        {
            ui->chk_2->setText(sz + "2");
            ui->chk_2->move(btn_x + add_x, ui->chk_2->y());
            ui->label_2->move(btn_x + add_x, ui->label_2->y());
            ui->chk_2->resize(200, 30);
            update();
        }
        if (index == 2)
        {
            ui->chk_3->setText(sz + "3");
            ui->chk_3->move(btn_x + add_x, ui->chk_3->y());
            ui->label_3->move(btn_x + add_x, ui->label_3->y());
            ui->chk_3->resize(100, 30);
            update();
        }
        if (index == 3)
        {
            ui->chk_4->setText(sz + "4");
            ui->chk_4->move(btn_x + add_x, ui->chk_4->y());
            ui->label_5->move(btn_x + add_x, ui->label_5->y());
            ui->chk_4->resize(100, 30);
            update();
        }
        if (index == 4)
        {
            ui->chk_5->setText(sz + "5");
            ui->chk_5->move(btn_x + add_x, ui->chk_5->y());
            ui->label_6->move(btn_x + add_x, ui->label_6->y());
            ui->chk_5->resize(100, 30);
            update();
        }
        if (index == 5)
        {
            ui->chk_6->setText(sz + "6");
            ui->chk_6->move(btn_x + add_x, ui->chk_6->y());
            ui->label_7->move(btn_x + add_x, ui->label_7->y());
            ui->chk_6->resize(100, 30);
            update();
        }
        if (index == 6)
        {
            ui->chk_7->setText(sz + "7");
            ui->chk_7->move(btn_x + add_x, ui->chk_7->y());
            ui->label_8->move(btn_x + add_x, ui->label_8->y());
            ui->chk_7->resize(100, 30);
            update();
        }
        if (index == 7)
        {
            ui->chk_8->setText(sz + "8");
            ui->chk_8->move(btn_x + add_x, ui->chk_8->y());
            ui->label_9->move(btn_x + add_x, ui->label_9->y());
            ui->chk_8->resize(100, 30);
            update();
        }
        if (index == 8)
        {
            ui->chk_9->setText(sz + "9");
            ui->chk_9->move(btn_x + add_x, ui->chk_9->y());
            ui->label_10->move(btn_x + add_x, ui->label_10->y());
            ui->chk_9->resize(100, 30);
            update();
        }
        index++;
    }
    update();
}

void PrepareReagentWidget::showEvent(QShowEvent *e)
{
    Q_UNUSED(e);
    m_selectPDialog->resetBtn();
    on_cb_all_toggled(false);
    ui->cb_all->setChecked(false);
    CloseAllLight();
    auto empty = ":/images/buttonIcon/irrigationIcon.png";
    QImage image(empty);
    QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->btnIrrigate->setIcon(QIcon(fitpixmap));
    ui->btnIrrigate->setIconSize(QSize(image.width(), image.height()));
    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1077");
    ui->lblHint->setText(sz);
    updatePumpBtnByTest();
    emit ChangeBtnNextSignal(false);
    // emit ChangeBtnNextSignal(true);//测试阶段忽略灌注限制
    Sleep(200);
}

void PrepareReagentWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void PrepareReagentWidget::on_btnFlash_clicked()
{
    m_flushing_type = 0;
    QVector<pReagent> reagentVect = GetReagentVect();
    //auto state = InstrumentStateModel::instance()->getMachineState();
    /*if (!state.canRun)
    {
        //QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("当前状态不允许运行，请先进行初始化操作"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1411"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
        return;
    }*/

    QMap<uchar,ushort> map;
    for(auto it:_btnGroup->buttons())
    {
        auto btn=reinterpret_cast<CustomButton*>(it);
        if(btn->isChecked())
        {
            auto pumpNo = btn->objectName().toInt();
            QString volumn1;
            for (auto r : reagentVect)
            {
                if (r->getPumpNo() == pumpNo)
                {

                    volumn1.sprintf("%.2f ml", r->getFluidMeasure());
                }
            }

            //auto strVolumn=btn->getVolumn();
            //btn->setVolumn(volumn1);
            qDebug()<<"setVolumn"<<volumn1;
            auto volumn = static_cast<ushort>(volumn1.left(volumn1.length()-2).toDouble()*1000);

            map.insert(pumpNo, volumn);
            m_finish_map.insert(pumpNo, 0);

            for (const auto& key : m_preview_wash_map.keys()) {
                int key_value = key;
                if (pumpNo == key_value)
                {
                    m_preview_wash_map.remove(key_value);
                }
            }
        }
    }

    if(map.isEmpty())
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1412"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }

    for (auto it = m_finish_map.begin(); it != m_finish_map.end(); ++it) {

        for (auto it1 = map.begin(); it1 != map.end(); ++it1) {

            if (it.key() == it1.key())
            {
                it.value() = 1;
            }
        }
    }

    Global::g_run_or_maintenance_flage = 1;

    pumpList = map.keys();
    for(int i=0;i<pumpList.size();i++){
        pumpList[i]= pumpList[i]+1;
    }
    _instrument->prepareReagent(pumpList,"max");

    //_instrument->maintain(ePrepareReagent);

    m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1717"));
    m_progressDialog->exec();
    // if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumStandby)
    //     changeIcon(_readyFile,PumpPosState::enumReady);
    // else
    //     changeIcon(_flushFile,PumpPosState::enumFlush);
}

void PrepareReagentWidget::changeSystemLiquidIcon(){
    m_system_liquid_finish=true;
    auto empty = ":/images/buttonIcon/rReady.png";
    QImage image(empty);
    QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->btnIrrigate->setIcon(QIcon(fitpixmap));
    ui->btnIrrigate->setIconSize(QSize(image.width(), image.height()));
    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1082");
    ui->lblHint->setText(sz);
}

void PrepareReagentWidget::slotPrepareReagentResult(QString code){
    if(code=="0"){
        if(pumpList.size()==1&&pumpList[0]==10){
            changeSystemLiquidIcon();
        }else{
            changeIcon(_readyFile,PumpPosState::enumReady);
        }

        m_progressDialog->done(1);
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1716"), MyMessageBox::Ok, "OK", "");

        qDebug()<<"32423:"<<m_reagentVect.size();
        if (m_system_liquid_finish && m_finish_map.size() == m_reagentVect.size())
        {
            emit ChangeBtnNextSignal(true);
        }
    }else{
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), code), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }

}

void PrepareReagentWidget::on_pushButtonSmall_clicked()
{

    m_flushing_type = 1;
    QVector<pReagent> reagentVect = GetReagentVect();
    // auto state = InstrumentStateModel::instance()->getMachineState();
    /* if (!state.canRun)
    {
        //QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("当前状态不允许运行，请先进行初始化操作"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1411"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
        return;
    }*/

    QMap<uchar, ushort>map;
    for (auto it : _btnGroup->buttons())
    {
        auto btn = reinterpret_cast<CustomButton*>(it);

        if (btn->isChecked())
        {
            auto pumpNo = btn->objectName().toInt();
            QString volumn1;
            for (auto r : reagentVect)
            {
                if (r->getPumpNo() == pumpNo)
                {

                    volumn1.sprintf("%.2f ml", r->getFluidMeasureSmall());
                }
            }

            auto strVolumn = btn->getVolumn();
            btn->setVolumn(volumn1);
            auto volumn = static_cast<ushort>(volumn1.left(volumn1.length() - 2).toDouble() * 1000);

            map.insert(pumpNo, volumn);
        }
    }

    if (map.isEmpty())
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1422"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    Global::g_run_or_maintenance_flage = 1;
    _instrument->setReagentPosVolumnMap(map);
    //	_instrument->maintain(ePrepareReagent);
    m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1636"));//tr("试剂准备中,请稍候......"));
    m_progressDialog->exec();
    if (InstrumentStateModel::instance()->getMachineState().state == InstrumentStateModel::enumStandby)
        changeIcon(_readyFile, PumpPosState::enumReady);
    else
        changeIcon(_flushFile, PumpPosState::enumFlush);
}

void PrepareReagentWidget::on_btnReady_clicked()
{
    changeIcon(_readyFile,PumpPosState::enumReady);
}

void PrepareReagentWidget::on_btnDelay_clicked()
{
    m_flushing_type = 0;
    changeIcon(_delayFile,PumpPosState::enumDelay);
}

void PrepareReagentWidget::paintEvent(QPaintEvent *event)
{

    QWidget::paintEvent(event);
    move_chk_position();
}

void PrepareReagentWidget::on_chk_1_toggled(bool state)
{
    getCheckBtn();
}

void PrepareReagentWidget::on_chk_2_toggled(bool state)
{
    getCheckBtn();
}

void PrepareReagentWidget::on_chk_3_toggled(bool state)
{
    getCheckBtn();
}

void PrepareReagentWidget::on_chk_4_toggled(bool state)
{
    getCheckBtn();
}
void PrepareReagentWidget::on_chk_5_toggled(bool state)
{
    getCheckBtn();
}
void PrepareReagentWidget::on_chk_6_toggled(bool state)
{
    getCheckBtn();
}
void PrepareReagentWidget::on_chk_7_toggled(bool state)
{
    getCheckBtn();
}
void PrepareReagentWidget::on_chk_8_toggled(bool state)
{
    getCheckBtn();
}
void PrepareReagentWidget::on_chk_9_toggled(bool state)
{
    getCheckBtn();
}

void PrepareReagentWidget::on_cb_all_toggled(bool state)
{
    if (state)
    {
        auto btns = _btnGroup->buttons();
        int index = 0;

        for (auto &it : btns)
        {
            auto btn = reinterpret_cast<CustomButton*>(it);

            auto pumpNo = btn->objectName().toInt();
            for (auto r : m_reagentVect)
            {
                if (r->getPumpNo() == pumpNo)
                {
                    if (index == 0)
                    {
                        ui->chk_1->setChecked(true);
                        ui->chk_1->setText("");
                    }
                    if (index == 1)
                    {
                        ui->chk_2->setChecked(true);
                    }
                    if (index == 2)
                    {
                        ui->chk_3->setChecked(true);
                    }
                    if (index == 3)
                    {
                        ui->chk_4->setChecked(true);
                    }
                    if (index == 4)
                    {
                        ui->chk_5->setChecked(true);
                    }
                    if (index == 5)
                    {
                        ui->chk_6->setChecked(true);
                    }
                    if (index == 6)
                    {
                        ui->chk_7->setChecked(true);
                    }
                    if (index == 7)
                    {
                        ui->chk_8->setChecked(true);
                    }
                    if (index == 8)
                    {
                        ui->chk_9->setChecked(true);
                    }
                    break;
                }
            }
            index++;
        }
    }
    else
    {
        ui->chk_1->setChecked(false);
        ui->chk_2->setChecked(false);
        ui->chk_3->setChecked(false);
        ui->chk_4->setChecked(false);
        ui->chk_5->setChecked(false);
        ui->chk_6->setChecked(false);
        ui->chk_7->setChecked(false);
        ui->chk_8->setChecked(false);
        ui->chk_9->setChecked(false);
    }
    getCheckBtn();
}

QVector<uchar> PrepareReagentWidget::getCheckBtn()
{
    QVector<uchar> outVect;
    if (ui->chk_1->isChecked())
    {
        outVect.push_back(0);
        m_postion_map[1] = 1;
    }
    else
    {
        m_postion_map[1] = 0;
    }

    if (ui->chk_2->isChecked())
    {
        outVect.push_back(1);
        m_postion_map[2] = 1;
    }
    else
    {
        m_postion_map[2] = 0;
    }

    if (ui->chk_3->isChecked())
    {
        m_postion_map[3] = 1;
        outVect.push_back(2);
    }
    else
    {
        m_postion_map[3] = 0;
    }

    if (ui->chk_4->isChecked())
    {
        m_postion_map[4] = 1;
        outVect.push_back(3);
    }
    else
    {
        m_postion_map[4] = 0;
    }

    if (ui->chk_5->isChecked())
    {
        m_postion_map[5] = 1;

        outVect.push_back(4);
    }
    else
    {
        m_postion_map[5] = 0;
    }

    if (ui->chk_6->isChecked())
    {
        m_postion_map[6] = 1;
        outVect.push_back(5);
    }
    else
    {
        m_postion_map[6] = 0;
    }

    if (ui->chk_7->isChecked())
    {
        m_postion_map[7] = 1;
        outVect.push_back(6);
    }
    else
    {
        m_postion_map[7] = 0;
    }

    if (ui->chk_8->isChecked())
    {
        m_postion_map[8] = 1;
        outVect.push_back(7);
    }
    else
    {
        m_postion_map[8] = 0;
    }

    if (ui->chk_9->isChecked())
    {
        m_postion_map[9] = 1;
        outVect.push_back(8);
    }
    else
    {
        m_postion_map[9] = 0;
    }

    mOutVect = outVect;
    auto btns = _btnGroup->buttons();
    int iii = 0;
    for (auto &it : btns)
    {
        auto btn = reinterpret_cast<CustomButton*>(it);
        QString reagent_name = btn->getReagentName();
        if (reagent_name != "")
        {
        }
        else
        {
        }
        int valuezx = m_postion_map[iii + 1];
        if (valuezx == 0)
        {
            btn->setChecked(false);
        }
        if (valuezx == 1)
        {
            btn->setChecked(true);
        }
        iii++;
    }
    return outVect;
}

