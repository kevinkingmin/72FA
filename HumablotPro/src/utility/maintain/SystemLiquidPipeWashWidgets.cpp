#include "..\include\precomp\precompile.h"
#include "SystemLiquidPipeWashWidgets.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "src/main/subDialog/ProgressDialog.h"
#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

#include "src/main/subDialog/MyMessageBox.h"

SystemLiquidPipeWashWidgets::SystemLiquidPipeWashWidgets(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::SystemLiquidPipeWashWidgetsClass)
    , _InstrumentState(InstrumentStateModel::instance())
    , _instr(Instrument::instance())
    , _emptyFile("rFlowBack128.png")
    , _flushFile("irrigationIcon.png")
    , _readyFile("rReady.png")
    , _delayFile("rDelay.png")
    , _pixPath(":/images/buttonIcon/")
{
    ui->setupUi(this);

    auto dao = AnalysisUIDao::instance();
    bool bResult;
    g_language_type = dao->SelectTargetValueDes(&bResult, "20005");

    createPumpBtn(ui->pushButton_2, false);
    createPumpBtn(ui->pushButton_3, false);
    createPumpBtn(ui->pushButton_4, false);
    createPumpBtn(ui->pushButton_5, false);
    createPumpBtn(ui->pushButton_6, false);
    createPumpBtn(ui->pushButton_7, false);
    createPumpBtn(ui->pushButton_8, false);
    createPumpBtn(ui->pushButton_9, false);
    createPumpBtn(ui->pushButton_10, false);
    myTimer = new QTimer(this);//父亲：当前对象传递进去
    connect(myTimer, &QTimer::timeout, this, &SystemLiquidPipeWashWidgets::doProcessTimeout);
    connect(_instr, &Instrument::sglIsStepSuc, this, &SystemLiquidPipeWashWidgets::slotIsStepSuc);
    ui->groupBox->setVisible(false);
    QRegExpValidator* validator6 = new QRegExpValidator(QRegExp("^\\d*$"), ui->lineEdit);
    ui->lineEdit->setValidator(validator6);
    //ui->progressBar->setStyleSheet("QProgressBar {border: 1px solid grey; border-radius: 2px; background-color: #FFFFFF; text-align:center; font-size:15px}");
    //ui->progressBar->setVisible(false);
    //auto dao = AnalysisUIDao::instance();
    //bool bResult;
    QString save_set = dao->SelectSaveSetById(&bResult, 21);
    //将泵管头放到足量的纯水中
    //m_vol = save_set.toInt();//ui->edit_time->text().toInt();
    save_set = QString("%1").arg(save_set.toInt() / 1000);
    ui->lineEdit->setText(save_set);
    ui->label_3->setText(save_set);
    ui->lineEdit->setEnabled(false);

    ui->pushButton_11->setVisible(false);  //->setEnabled(false);

    auto empty = ":/images/buttonIcon/irrigationIcon.png";
    QImage image(empty);
    //ui->pumpLB1_1->setPixmap(QPixmap::fromImage(image));
    QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->pushButton_12->setIcon(QIcon(fitpixmap));
    //ui->btnIrrigate->setProperty(GlobalData::getPropertyName(), PumpPosState::enumEmpty);
    ui->pushButton_12->setIconSize(QSize(image.width(), image.height()));
    ui->lineEdit->setVisible(false);

    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1217");
    ui->label_4->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1218");
    ui->label->setText(sz);


    QString sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1221");
    ui->chk_1->setText("1" + sz1);
    ui->chk_2->setText("2" + sz1);
    ui->chk_3->setText("3" + sz1);
    ui->chk_4->setText("4" + sz1);
    ui->chk_5->setText("5" + sz1);
    ui->chk_6->setText("6" + sz1);
    ui->chk_7->setText("7" + sz1);
    ui->chk_8->setText("8" + sz1);
    ui->chk_9->setText("9" + sz1);

}

void SystemLiquidPipeWashWidgets::updateUI()
{
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    QString save_set = dao->SelectSaveSetById(&bResult, 21);
    save_set = QString("%1").arg(save_set.toInt() / 1000);
    ui->lineEdit->setText(save_set);
    ui->label_3->setText(save_set);
    ui->lineEdit->setEnabled(false);
    update();
}

SystemLiquidPipeWashWidgets::~SystemLiquidPipeWashWidgets()
{}

QVector<int> SystemLiquidPipeWashWidgets::getCheckBtn()
{
    QVector<int> outVect;
    if (ui->chk_1->isChecked())
    {
        createPumpBtn(ui->pushButton_2, true);
        outVect.push_back(0);
    }
    else
    {
        createPumpBtn(ui->pushButton_2, false);
    }

    if (ui->chk_2->isChecked())
    {
        createPumpBtn(ui->pushButton_3, true);
        outVect.push_back(1);
    }
    else
    {
        createPumpBtn(ui->pushButton_3, false);
    }

    if (ui->chk_3->isChecked())
    {
        createPumpBtn(ui->pushButton_4, true);
        outVect.push_back(2);
    }
    else
    {
        createPumpBtn(ui->pushButton_4, false);
    }

    if (ui->chk_4->isChecked())
    {
        createPumpBtn(ui->pushButton_5, true);
        outVect.push_back(3);
    }
    else
    {
        createPumpBtn(ui->pushButton_5, false);
    }

    if (ui->chk_5->isChecked())
    {
        createPumpBtn(ui->pushButton_6, true);
        outVect.push_back(4);
    }
    else
    {
        createPumpBtn(ui->pushButton_6, false);
    }

    if (ui->chk_6->isChecked())
    {
        createPumpBtn(ui->pushButton_7, true);
        outVect.push_back(5);
    }
    else
    {
        createPumpBtn(ui->pushButton_7, false);
    }

    if (ui->chk_7->isChecked())
    {
        createPumpBtn(ui->pushButton_8, true);
        outVect.push_back(6);
    }
    else
    {
        createPumpBtn(ui->pushButton_8, false);
    }

    if (ui->chk_8->isChecked())
    {
        createPumpBtn(ui->pushButton_9, true);
        outVect.push_back(7);
    }
    else
    {
        createPumpBtn(ui->pushButton_9, false);
    }

    if (ui->chk_9->isChecked())
    {
        createPumpBtn(ui->pushButton_10, true);
        outVect.push_back(8);
    }
    else
    {
        createPumpBtn(ui->pushButton_10, false);
    }
    mOutVect = outVect;
    return outVect;
}

void SystemLiquidPipeWashWidgets::on_chk_1_toggled(bool state)
{
    getCheckBtn();
}

void SystemLiquidPipeWashWidgets::on_chk_2_toggled(bool state)
{
    getCheckBtn();
}

void SystemLiquidPipeWashWidgets::on_chk_3_toggled(bool state)
{
    getCheckBtn();
}

void SystemLiquidPipeWashWidgets::on_chk_4_toggled(bool state)
{
    getCheckBtn();
}
void SystemLiquidPipeWashWidgets::on_chk_5_toggled(bool state)
{
    getCheckBtn();
}
void SystemLiquidPipeWashWidgets::on_chk_6_toggled(bool state)
{
    getCheckBtn();
}
void SystemLiquidPipeWashWidgets::on_chk_7_toggled(bool state)
{
    getCheckBtn();
}
void SystemLiquidPipeWashWidgets::on_chk_8_toggled(bool state)
{
    getCheckBtn();
}
void SystemLiquidPipeWashWidgets::on_chk_9_toggled(bool state)
{
    getCheckBtn();
}

void SystemLiquidPipeWashWidgets::on_pushButton_2_clicked()
{
    if (ui->pushButton_2->isChecked())
    {
        ui->chk_1->setChecked(true);
        ui->pushButton_2->setChecked(true);
    }
    else
    {
        ui->chk_1->setChecked(false);
        ui->pushButton_2->setChecked(false);
    }
}

void SystemLiquidPipeWashWidgets::on_pushButton_3_clicked() {
    if (ui->pushButton_3->isChecked())
    {
        ui->chk_2->setChecked(true);
        ui->pushButton_3->setChecked(true);
    }
    else
    {
        ui->chk_2->setChecked(false);
        ui->pushButton_3->setChecked(false);
    }
}

void SystemLiquidPipeWashWidgets::on_pushButton_4_clicked() {
    if (ui->pushButton_4->isChecked())
    {
        ui->chk_3->setChecked(true);
        ui->pushButton_4->setChecked(true);
    }
    else
    {
        ui->chk_3->setChecked(false);
        ui->pushButton_4->setChecked(false);
    }
}

void SystemLiquidPipeWashWidgets::on_pushButton_5_clicked() {
    if (ui->pushButton_5->isChecked())
    {
        ui->chk_4->setChecked(true);
        ui->pushButton_5->setChecked(true);
    }
    else
    {
        ui->chk_4->setChecked(false);
        ui->pushButton_5->setChecked(false);
    }
}
void SystemLiquidPipeWashWidgets::on_pushButton_6_clicked() {

    if (ui->pushButton_6->isChecked())
    {
        ui->chk_5->setChecked(true);
        ui->pushButton_6->setChecked(true);
    }
    else
    {
        ui->chk_5->setChecked(false);
        ui->pushButton_6->setChecked(false);
    }
}
void SystemLiquidPipeWashWidgets::on_pushButton_7_clicked() {
    if (ui->pushButton_7->isChecked())
    {
        ui->chk_6->setChecked(true);
        ui->pushButton_7->setChecked(true);
    }
    else
    {
        ui->chk_6->setChecked(false);
        ui->pushButton_7->setChecked(false);
    }
}
void SystemLiquidPipeWashWidgets::on_pushButton_8_clicked() {
    if (ui->pushButton_8->isChecked())
    {
        ui->chk_7->setChecked(true);
        ui->pushButton_8->setChecked(true);

    }
    else
    {
        ui->chk_7->setChecked(false);
        ui->pushButton_8->setChecked(false);
    }
}
void SystemLiquidPipeWashWidgets::on_pushButton_9_clicked() {

    if (ui->pushButton_9->isChecked())
    {
        ui->chk_8->setChecked(true);
        ui->pushButton_9->setChecked(true);

    }
    else
    {
        ui->chk_8->setChecked(false);
        ui->pushButton_9->setChecked(false);
    }
}
void SystemLiquidPipeWashWidgets::on_pushButton_10_clicked() {

    if (ui->pushButton_10->isChecked())
    {
        ui->chk_9->setChecked(true);
        ui->pushButton_10->setChecked(true);

    }
    else
    {
        ui->chk_9->setChecked(false);
        ui->pushButton_10->setChecked(false);
    }
}

void SystemLiquidPipeWashWidgets::on_cb_all_toggled(bool state)
{
    if (state)
    {
        ui->chk_1->setChecked(true);
        ui->chk_2->setChecked(true);
        ui->chk_3->setChecked(true);
        ui->chk_4->setChecked(true);
        ui->chk_5->setChecked(true);
        ui->chk_6->setChecked(true);
        ui->chk_7->setChecked(true);
        ui->chk_8->setChecked(true);
        ui->chk_9->setChecked(true);
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

void SystemLiquidPipeWashWidgets::createPumpBtn(QPushButton *pushButton, bool selected_status)
{
    auto empty = "irrigationIcon.png";
    QImage image(_pixPath + empty);
    //ui->pumpLB1_1->setPixmap(QPixmap::fromImage(image));
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


void SystemLiquidPipeWashWidgets::on_pushButton_12_clicked() {
    auto state = _InstrumentState->getMachineState();
    if (state.state==_InstrumentState->enumRuning)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1581"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }

    m_start_system_liquid_pipe_wash = true;
    m_vol = ui->lineEdit->text().toInt();
    if (m_vol == 0)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1313"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    if (m_vol > 5 || m_vol < 1)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1313"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    Global::g_run_or_maintenance_flage = 1;
    //_instr->washSystemLiquidWay(m_vol * 1000);
    m_action_id = 14;
    _instr->systemPipWash(m_vol*1000);
    //_InstrumentState->setMachineState(_InstrumentState->enumRuning);
    m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"));
    m_progressDialog->exec();

}


void SystemLiquidPipeWashWidgets::on_pushButton_11_clicked() {
    m_start_system_liquid_pipe_wash = true;
    m_vol = ui->lineEdit->text().toInt();
    if (m_vol == 0)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1313"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }

    if (m_vol > 5 || m_vol < 1)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1313"), MyMessageBox::Ok| MyMessageBox::No,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }

    Global::g_run_or_maintenance_flage = 1;
    //_instr->pumpFlushIrrigation(mOutVect[0], m_vol, true);


    //_instr->irrigationSystemLiquid(m_vol*1000);
    //_instr->washSystemLiquidWay(m_vol * 1000);
    m_action_id = 14;
    //m_need_system_liquid_pipe_number = mOutVect.size();
    //mOutVect.removeAt(0);
    //_instr->maintain(eSystemLiquidWahs);
    //_InstrumentState->setMachineState(_InstrumentState->enumRuning);
    m_progressDialog->setHead("系统液充灌进行中......");
    m_progressDialog->exec();
}

void SystemLiquidPipeWashWidgets::slotIsStepSuc(int ret) {
    if (ret >= 0 && m_action_id == ret)
    {
        if (m_start_system_liquid_pipe_wash)
        {
            auto state = _InstrumentState->getMachineState();
            if (state.state == _InstrumentState->enumError)
            {
                return;
            }
            m_start_system_liquid_pipe_wash = false;
            m_finish_system_liquid_pipe_number = 0;
            m_need_system_liquid_pipe_number = 0;
            // _InstrumentState->setMachineState(_InstrumentState->enumStandby);
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1522"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        }
    }
    else
    {
    }
}

void SystemLiquidPipeWashWidgets::doProcessTimeout() {
    index++;
    //ui->progressBar->setValue(index);
    if (index == mNeed_times)
    {
        //_instr->rockBedWorking(0);
        myTimer->stop();
        ui->pushButton_11->setEnabled(true);
        //_instr->motorInitialize(0x05, 60000);
        //_instr->setBuzzleOnOff(0x00);
    }
    if (mNeed_times - index == 15)
    {
        //_instr->setBuzzleOnOff(0x03);
    }
}

void SystemLiquidPipeWashWidgets::setProgressDialog(ProgressDialog *progressDialog)
{
    m_progressDialog = progressDialog;
}
