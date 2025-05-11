#include "..\include\precomp\precompile.h"
#include "PipeRefluxWidgets.h"

#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "src/main/subDialog/ProgressDialog.h"
#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"


PipeRefluxWidgets::PipeRefluxWidgets(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::PipeRefluxWidgetsClass)
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

    ui->cb_all->setVisible(false);

    myTimer = new QTimer(this);//父亲：当前对象传递进去
    connect(myTimer, &QTimer::timeout, this, &PipeRefluxWidgets::doProcessTimeout);
    connect(_instr, &Instrument::sglIsStepSuc, this, &PipeRefluxWidgets::slotIsStepSuc);


    QString sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1220");
    ui->label->setText(sz1);
    sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1081");
    ui->pushButton_12->setText(sz1);

    sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1221");
    ui->chk_1->setText("1"+sz1);
    ui->chk_2->setText("2" + sz1);
    ui->chk_3->setText("3" + sz1);
    ui->chk_4->setText("4" + sz1);
    ui->chk_5->setText("5" + sz1);
    ui->chk_6->setText("6" + sz1);
    ui->chk_7->setText("7" + sz1);
    ui->chk_8->setText("8" + sz1);
    ui->chk_9->setText("9" + sz1);

    sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1222");
    ui->pushButton_11->setText(sz1);
    //ui->progressBar->setStyleSheet("QProgressBar {border: 1px solid grey; border-radius: 2px; background-color: #FFFFFF; text-align:center; font-size:15px}");
    //ui->progressBar->setVisible(false);
}

void PipeRefluxWidgets::updateUI()
{
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    QString save_set = dao->SelectSaveSetById(&bResult, 20004);
    //将泵管头放到足量的纯水中
    //m_vol = save_set.toInt();//ui->edit_time->text().toInt();
    m_vol = save_set.toInt();//ui->edit_time->text().toInt();
    update();
}


QVector<int> PipeRefluxWidgets::getCheckBtn()
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

void PipeRefluxWidgets::on_chk_1_toggled(bool state)
{
    getCheckBtn();
}

void PipeRefluxWidgets::on_chk_2_toggled(bool state)
{
    getCheckBtn();
}

void PipeRefluxWidgets::on_chk_3_toggled(bool state)
{
    getCheckBtn();
}

void PipeRefluxWidgets::on_chk_4_toggled(bool state)
{
    getCheckBtn();
}
void PipeRefluxWidgets::on_chk_5_toggled(bool state)
{
    getCheckBtn();
}
void PipeRefluxWidgets::on_chk_6_toggled(bool state)
{
    getCheckBtn();
}
void PipeRefluxWidgets::on_chk_7_toggled(bool state)
{
    getCheckBtn();
}
void PipeRefluxWidgets::on_chk_8_toggled(bool state)
{
    getCheckBtn();
}
void PipeRefluxWidgets::on_chk_9_toggled(bool state)
{
    getCheckBtn();
}

void PipeRefluxWidgets::on_pushButton_2_clicked()
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

void PipeRefluxWidgets::on_pushButton_3_clicked() {
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

void PipeRefluxWidgets::on_pushButton_4_clicked() {
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

void PipeRefluxWidgets::on_pushButton_5_clicked() {
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
void PipeRefluxWidgets::on_pushButton_6_clicked() {

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
void PipeRefluxWidgets::on_pushButton_7_clicked() {
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
void PipeRefluxWidgets::on_pushButton_8_clicked() {
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
void PipeRefluxWidgets::on_pushButton_9_clicked() {

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
void PipeRefluxWidgets::on_pushButton_10_clicked() {

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


void PipeRefluxWidgets::on_cb_all_toggled(bool state)
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
void PipeRefluxWidgets::createPumpBtn(QPushButton *pushButton, bool selected_status)
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

void PipeRefluxWidgets::on_pushButton_12_clicked() {

    if (!all_select_flage)
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
        all_select_flage = true;
        ui->pushButton_12->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1637"));
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
        ui->pushButton_12->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1081"));//setText("全选");
        all_select_flage = false;
    }
    getCheckBtn();
}

void PipeRefluxWidgets::on_pushButton_11_clicked() {

    auto state = _InstrumentState->getMachineState();
    if (state.state==_InstrumentState->enumRuning)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1581"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    //index = 0;
    //mNeed_times = 0;
    ////m_instr->rockBedWorking(3);
    //QString need_i_times1 = ui->edit_time->text();
    //if (need_i_times1 == "")
    //{
    //	QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("请输入孵育时间！"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
    //	return;
    //}
    //ui->progressBar->setValue(0);
    //int need_in_times = need_i_times1.toInt();
    //ui->progressBar->setRange(0, need_in_times);
    //myTimer->start(1000);//1s倒计时1次
    //ui->pushButton_11->setEnabled(false);
    //mNeed_times = need_in_times;
    if (mOutVect.count() == 0)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1220"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    int ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1449"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if (ret == MyMessageBox::Ok)
    {
        //将泵管头放到足量的纯水中
        //m_progressDialog->setHead("管路回流进行中......");
        //m_progressDialog->exec();
        Global::g_run_or_maintenance_flage = 1;
        m_start_PipeRefluxWidgets = true;
        auto dao = AnalysisUIDao::instance();
        bool bResult;
        QString save_set = dao->SelectSaveSetById(&bResult, 20004);
        m_vol = save_set.toInt();//ui->edit_time->text().toInt();
        //_instr->liquidBackFlow(mOutVect[0], m_vol, true);
        m_need_wash_number = mOutVect.size();
        QList<uint8_t> pumpList;
        for(int pumpNum:mOutVect){
            pumpList.push_back(static_cast<uint8_t>(pumpNum+1));
        }
        _instr->pipFlowback(pumpList,m_vol);
        _InstrumentState->setMachineState(_InstrumentState->enumRuning);
        m_progressDialog->setHead("管路回流进行中......");
        m_progressDialog->exec();
        //_instr->maintain(eSystemLiquidWahs);
        //m_progressDialog->setHead("管路回流进行中......");
        //m_progressDialog->exec();
    }
    else
    {
        return;
    }

}

void PipeRefluxWidgets::slotIsStepSuc(int ret) {

    if (ret >= 0)
    {

        if (m_start_PipeRefluxWidgets)
        {

            if (mOutVect.count() > 0)
            {
                //_instr->liquidBackFlow(mOutVect[0], m_vol, false);
                mOutVect.removeAt(0);
            }

            auto state = _InstrumentState->getMachineState();
            if (state.state == _InstrumentState->enumError)
            {
                return;
            }
            m_finish_wash_number++;
            if (m_need_wash_number == m_finish_wash_number)
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
                ui->cb_all->setChecked(false);

                m_start_PipeRefluxWidgets = false;
                m_finish_wash_number = 0;
                m_need_wash_number = 0;
                //m_progressDialog->setMaxValue(100000);
                //m_progressDialog->close();
                //_instr->maintain(eSystemLiquidWahs);
                _InstrumentState->setMachineState(_InstrumentState->enumStandby);
                MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1500"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            }
        }
    }
    else
    {
    }
}

void PipeRefluxWidgets::doProcessTimeout() {
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

void PipeRefluxWidgets::setProgressDialog(ProgressDialog *progressDialog)
{
    m_progressDialog = progressDialog;
}




PipeRefluxWidgets::~PipeRefluxWidgets()
{}
