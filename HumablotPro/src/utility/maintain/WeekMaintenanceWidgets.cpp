#include "..\include\precomp\precompile.h"
#include "WeekMaintenanceWidgets.h"
#include <QMessageBox>
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "src/main/subDialog/ProgressDialog.h" 

#include <QMessageBox>
#include <string>
#include <QDateTime>
#include "src/comm/CustomButton.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include <QTimer>

#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"

WeekMaintenanceWidgets::WeekMaintenanceWidgets(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::WeekMaintenanceWidgetsClass)
    , _InstrumentState(InstrumentStateModel::instance())
    , _instr(Instrument::instance())
    , _emptyFile("rFlowBack128.png")
    , _flushFile("irrigationIcon.png")
    , _btnGroup(new QButtonGroup(this))
    , _readyFile("rReady.png")
    , _delayFile("rDelay.png")
    , _pixPath(":/images/buttonIcon/")
{
    //ui.setupUi(this);
    ui->setupUi(this);
    _btnGroup->setExclusive(false);

    ui->groupBox_2->setVisible(false);
    ui->groupBox_3->setVisible(false);
    ui->groupBox_4->setVisible(false);
    ui->groupBox_5->setVisible(false);

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

    ui->progressBar->setStyleSheet("QProgressBar {border: 1px solid grey; border-radius: 2px; background-color: #FFFFFF; text-align:center; font-size:15px}");

    connect(_instr, &Instrument::sglMonthMaintain, this, &WeekMaintenanceWidgets::slotMonthMaintain);

    auto pm1 = SystemSetBLL().getRowById(24);
    //int delay_time = (pm1.isNull() ? 200 : pm1->getSaveSet()) / 1000;
    int delay_time = (pm1.isNull() ? 200 : pm1->getSaveSet()) ;

    int i = delay_time/1000;
    m_i = delay_time/1000;

    myTimer = new QTimer(this);

    connect(myTimer, &QTimer::timeout, [=]() {

        //管路浸泡中......
        QString tip = "";//QString("管路浸泡中,剩余秒数：[%0]").arg(m_i);
        tip = QString("%1[%0]").arg(m_i).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1628"));
        m_progressDialog->setHead(tip);

        if (m_i == 10)
        {
            //_instr->setBuzzleOnOff(0x03);
        }

        if (m_i < 2)
        {
            //_instr->setBuzzleOnOff(0x00);
        }
        m_i--;
        //ui->lcdNumber->display(i);
    });

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

    sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1220");
    ui->label_3->setText(sz1);
    sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1081");
    ui->btn_down_step_2->setText(sz1);
    sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1222");
    ui->btn_down_step->setText(sz1);
}

void WeekMaintenanceWidgets::updateUI()
{
    //auto pm1 = SystemSetBLL().getRowById(9991);
    //int delay_time = (pm1.isNull() ? 200 : pm1->getSaveSet()) / 1000;
    //static int i = 15 * 60;
    //i = delay_time;
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    QString save_set = dao->SelectSaveSetById(&bResult, 24);

    m_i = save_set.toInt()/1000;
    update();
}



WeekMaintenanceWidgets::~WeekMaintenanceWidgets()
{}

QVector<uchar> WeekMaintenanceWidgets::getCheckBtn()
{
    QVector<uchar> outVect;
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

void WeekMaintenanceWidgets::on_chk_1_toggled(bool state)
{
    getCheckBtn();
}

void WeekMaintenanceWidgets::on_chk_2_toggled(bool state)
{
    getCheckBtn();
}

void WeekMaintenanceWidgets::on_chk_3_toggled(bool state)
{
    getCheckBtn();
}

void WeekMaintenanceWidgets::on_chk_4_toggled(bool state)
{
    getCheckBtn();
}
void WeekMaintenanceWidgets::on_chk_5_toggled(bool state)
{
    getCheckBtn();
}
void WeekMaintenanceWidgets::on_chk_6_toggled(bool state)
{
    getCheckBtn();
}
void WeekMaintenanceWidgets::on_chk_7_toggled(bool state)
{
    getCheckBtn();
}
void WeekMaintenanceWidgets::on_chk_8_toggled(bool state)
{
    getCheckBtn();
}
void WeekMaintenanceWidgets::on_chk_9_toggled(bool state)
{
    getCheckBtn();
}
void WeekMaintenanceWidgets::on_cb_all_toggled(bool state)
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

//void WeekMaintenanceWidgets::on_pushButton_clicked()
//{
//	int vect_count = mOutVect.count();
//	if (mOutVect.count() == 0)
//	{
//
//	}
//	int a = 0;
//}
void WeekMaintenanceWidgets::on_pushButton_clicked()
{
    //ui->btn_down_step->setEnabled(false);
    //return;
    auto state = _InstrumentState->getMachineState();
    if (state.state==_InstrumentState->enumRuning)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1581"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }

    MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1624"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");

    /*auto state = _InstrumentState->getMachineState();
    if (!state.canRun)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1321"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }*/


    //auto pm1 = SystemSetBLL().getRowById(24);
    //int delay_time = (pm1.isNull() ? 200 : pm1->getSaveSet()) / 1000;
    //static int i = 15 * 60;
    //i = delay_time;
    //m_i = delay_time;
    //mWeekMaintenance_run_flage = true;
    //Global::g_run_or_maintenance_flage = 1;
    //QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
    //_instr->setPumpVect(mOutVect);
    //	_instr->maintain(ePumpFill);
    QList<uint8_t> pumpList;
    for(int pumpNum:mOutVect){
        pumpList.push_back(static_cast<uint8_t>(pumpNum+1));
    }
    _instr->weeklyMaintenance(pumpList);

    _maintainStep = 1;
    m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1626"));//"周维护进行中......");
    m_progressDialog->exec();
    //ui->btn_down_step->setEnabled(false);
}

void WeekMaintenanceWidgets::slotMonthMaintain(int result)
{
    if (mWeekMaintenance_run_flage)
    {
        switch (_maintainStep)
        {
        case 1://浸泡
        {
            if (result < 0)
            {
                MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1344"),MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
                ui->btn_down_step->setEnabled(true);
                //_instr->machineStop();
                return;
            }
            //			_instr->maintain(eTubeSoak);
            _maintainStep = 2;
            m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1627"));//"管路浸泡中......");

            //auto pm1 = SystemSetBLL().getRowById(24);
            //int delay_time = pm1.isNull() ? 200 : pm1->getSaveSet();

            auto dao = AnalysisUIDao::instance();
            bool bResult;
            QString save_set = dao->SelectSaveSetById(&bResult, 24);
            m_i = save_set.toInt()/1000;


            m_progressDialog->setMaxValue(m_i);
            m_progressDialog->exec();

            if (myTimer->isActive() == false)
            {
                myTimer->start(1000);
            }

            break;
        }
        case 2:
        {

            if (myTimer->isActive() == true)
            {
                myTimer->stop();
            }

            //_instr->setBuzzleOnOff(0x00);

            if (result < 0)
            {
                MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1523"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
                ui->btn_down_step->setEnabled(true);
                //_instr->machineStop();
                return;
            }


            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1345"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            //QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
            //_instr->setPumpVect(mOutVect);
            //			_instr->maintain(ePumpFill);
            _maintainStep = 3;
            //if (_maintainType == MENU_ID_MONTH_MANTAINCE)
            //	_maintainStep = 3;
            //else if (_maintainType == MENU_ID_WEEK_MANTAINCE)
            //	_maintainStep = 4;
            //        m_progressDialog->setHead("清水充灌......");
            //        m_progressDialog->exec();
            break;
        }
        case 3://蠕动泵校准
        {
            if (result < 0)
            {
                MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1346"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                ui->btn_down_step->setEnabled(true);
                //_instr->machineStop();
                return;
            }
            //QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
            //_instr->setPumpVect(pumpVect);
            //_instr->maintain(ePumpFill);
            _maintainStep = 4;
            //        m_progressDialog->setHead("蠕动泵校准......");
            //        m_progressDialog->exec();
            //break;
        }
        case 4://充灌排空
        {
            if (result < 0)
            {
                MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1347"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                ui->btn_down_step->setEnabled(true);
                //_instr->machineStop();
                return;
            }

            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1348"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
            //_instr->setPumpVect(mOutVect);
            //			_instr->maintain(ePumpFill);
            _maintainStep = 5;
            //        m_progressDialog->setHead("最后充灌......");
            //        m_progressDialog->exec();
            break;
        }
        case 5:
        {
            if (result < 0)
            {
                MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1443"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                ui->btn_down_step->setEnabled(true);
                //_instr->machineStop();
                return;
            }

            ui->btn_down_step->setEnabled(true);
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


            createPumpBtn(ui->pushButton_2, false);
            createPumpBtn(ui->pushButton_3, false);
            createPumpBtn(ui->pushButton_4, false);
            createPumpBtn(ui->pushButton_5, false);
            createPumpBtn(ui->pushButton_6, false);
            createPumpBtn(ui->pushButton_7, false);
            createPumpBtn(ui->pushButton_8, false);
            createPumpBtn(ui->pushButton_9, false);
            createPumpBtn(ui->pushButton_10, false);

            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1524"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
            mWeekMaintenance_run_flage = false;
            //QVector<uchar>pumpVect{ 0,1,2,3,4,5,6,7,8 };
            //_instr->setPumpVect(pumpVect);
            //_instr->maintain(ePumpFill);
        }
        }
    }


}


//void MonthMaintenanceWidgets::on_btn_up_step_clicked()
//{
//	int a = 0;
//}

void WeekMaintenanceWidgets::on_btn_down_step_2_clicked()
{
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
        //K1637
        ui->btn_down_step_2->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1637"));//"取消全选");
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
        //K1081
        ui->btn_down_step_2->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1081"));//"全选");
        all_select_flage = false;
    }
    getCheckBtn();
}

void WeekMaintenanceWidgets::on_btn_down_step_clicked()
{
    if (!_InstrumentState->enumStandby)
    {
        return;
    }
    int vect_count = mOutVect.count();
    if (vect_count == 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1220"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    on_pushButton_clicked();
    //int a = 0;
    //step_index++;
    //if (step_index == 1)
    //{
    //	int ret = QMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("将泵管头放到足量的溶液中？"), tr("取消"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
    //	if (ret == QMessageBox::NoButton) {
    //		step_index = 0;
    //		return;
    //	}
    //	on_pushButton_clicked();
    //	step_index++;
    //	//ui->groupBox_2->setVisible(true);
    //}

    //if (step_index == 2)
    //{
    //	int ret = QMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("确认充灌？"), tr("取消"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
    //	if (ret == QMessageBox::NoButton) {
    //		step_index = 0;
    //		return;
    //	}
    //	step_index++;
    //	//ui->groupBox_2->setVisible(true);
    //	//ui->groupBox_3->setVisible(true);
    //}


    //if (step_index == 3)
    //{
    //	ui->groupBox_2->setVisible(true);
    //	ui->groupBox_3->setVisible(true);
    //	//ui->groupBox_4->setVisible(true);
    //}
    //if (step_index == 4)
    //{
    //	ui->groupBox_2->setVisible(true);
    //	ui->groupBox_3->setVisible(true);
    //	//ui->groupBox_4->setVisible(true);
    //	ui->groupBox_5->setVisible(true);
    //}

}
void WeekMaintenanceWidgets::HideGroupBox()
{
    ui->groupBox_2->setVisible(false);
    ui->groupBox_3->setVisible(false);
    ui->groupBox_4->setVisible(false);
    ui->groupBox_5->setVisible(false);

    createPumpBtn(ui->pushButton_2, false);
    createPumpBtn(ui->pushButton_3, false);
    createPumpBtn(ui->pushButton_4, false);
    createPumpBtn(ui->pushButton_5, false);
    createPumpBtn(ui->pushButton_6, false);
    createPumpBtn(ui->pushButton_7, false);
    createPumpBtn(ui->pushButton_8, false);
    createPumpBtn(ui->pushButton_9, false);
    createPumpBtn(ui->pushButton_10, false);

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
}


void WeekMaintenanceWidgets::setCenterImageColor(QImage &image, QColor &color)
{
    image = image.convertToFormat(QImage::Format_RGBA8888_Premultiplied, Qt::NoFormatConversion);
    int bmpWidth = image.width();
    int bmpHeight = image.height();
    for (int i = 0; i < bmpWidth; ++i) {
        for (int j = 0; j < bmpHeight; ++j) {
            //将灰色(0~255)全部替换成设定的颜色，全透明的不替换
            QColor tempColor = image.pixelColor(i, j);
            if (tempColor.alpha() != 0) {
                color.setAlpha(tempColor.alpha());
                image.setPixelColor(i, j, color);
            }
        }
    }
}


void WeekMaintenanceWidgets::createPumpBtn(QPushButton *pushButton, bool selected_status)
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

    //ui->pumpLB1_1->clear();
    //ui->pumpLB1_1->setPixmap(QPixmap::fromImage(image));
    //ui->pumpLB1_1->setScaledContents(true);

    //ui->pumpLB1_1->resize(image.width(), image.height());

    //auto empty = "rFlowBack128.png";//表明泵没有被占用
    //for (int i = 0; i < PUMPCOUNT; i++)
    //{
    //	auto btn = new CustomButton(this);
    //	btn->setLblPixSize(64, 64);
    //	btn->setPixPath(_pixPath + empty);
    //	btn->setUpText("泵" + QString::number(i + 1) );
    //	btn->setObjectName(QString::number(i));
    //	btn->setReagentName("");
    //	btn->setCheckable(false);
    //	btn->setProperty("btnStyle", "btnReagentPosStyle");
    //	btn->setProperty(GlobalData::getPropertyName(), PumpPosState::enumEmpty);
    //	ui->hLayPump->addWidget(btn);
    //	_btnGroup->addButton(btn);
    //}
}

void WeekMaintenanceWidgets::changeIcon(const QString &fileName, PumpPosState state)
{
    for (auto &it : _btnGroup->buttons())
    {
        if (it->isChecked())
        {
            auto btn = reinterpret_cast<CustomButton*>(it);
            btn->setProperty(GlobalData::getPropertyName(), state);
            btn->setPixPath(_pixPath + fileName);
            btn->setChecked(false);
        }
    }
    emit sglPumpStateChanged();
}


QButtonGroup *WeekMaintenanceWidgets::getBtnGroup() const
{
    return _btnGroup;
}


void WeekMaintenanceWidgets::on_btnFlash_clicked()
{
    //auto state = InstrumentStateModel::instance()->getMachineState();
    //if (!state.canRun)
    //{
    //	QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("当前状态不允许运行，请先进行初始化操作"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
    //	return;
    //}
    //QMap<uchar, ushort>map;
    //for (auto it : _btnGroup->buttons())
    //{
    //	auto btn = reinterpret_cast<CustomButton*>(it);
    //	if (btn->isChecked())
    //	{
    //		auto pumpNo = static_cast<uchar>(btn->objectName().toInt());
    //		auto strVolumn = btn->getVolumn();
    //		auto volumn = static_cast<ushort>(strVolumn.left(strVolumn.length() - 2).toDouble() * 1000);
    //		map.insert(pumpNo, volumn);
    //	}
    //}
    //if (map.isEmpty())
    //{
    //	QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("请选择要进行试剂准备的位置！"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
    //	return;
    //}
    //_instrument->setReagentPosVolumnMap(map);
    //_instrument->maintain(ePrepareReagent);
    //m_progressDialog->setHead(tr("试剂准备中,请稍候......"));
    //m_progressDialog->exec();
    if (InstrumentStateModel::instance()->getMachineState().state == InstrumentStateModel::enumStandby)
        changeIcon(_readyFile, PumpPosState::enumReady);
    else
        changeIcon(_flushFile, PumpPosState::enumFlush);
}

void WeekMaintenanceWidgets::on_btnReady_clicked()
{
    changeIcon(_readyFile, PumpPosState::enumReady);
}

void WeekMaintenanceWidgets::on_btnDelay_clicked()
{
    changeIcon(_delayFile, PumpPosState::enumDelay);
}


void WeekMaintenanceWidgets::on_pushButton_2_clicked()
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

void WeekMaintenanceWidgets::on_pushButton_3_clicked() {
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

void WeekMaintenanceWidgets::on_pushButton_4_clicked() {
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

void WeekMaintenanceWidgets::on_pushButton_5_clicked() {
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
void WeekMaintenanceWidgets::on_pushButton_6_clicked() {

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
void WeekMaintenanceWidgets::on_pushButton_7_clicked() {
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
void WeekMaintenanceWidgets::on_pushButton_8_clicked() {
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
void WeekMaintenanceWidgets::on_pushButton_9_clicked() {

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
void WeekMaintenanceWidgets::on_pushButton_10_clicked() {

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

void WeekMaintenanceWidgets::setProgressDialog(ProgressDialog *progressDialog)
{
    m_progressDialog = progressDialog;
}


//void MonthMaintenanceWidgets::Onchk_2State()
//{
//
//}
//void MonthMaintenanceWidgets::Onchk_3State()
//{
//
//}
//
//void MonthMaintenanceWidgets::Onchk_4State()
//{
//
//}
