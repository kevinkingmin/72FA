#include "..\include\precomp\precompile.h"
#include "ManualIncubationWidgets.h"
#include "../Include/Instrument/Instrument.h"
#include <QMessageBox>
#include "src/main/subDialog/MyMessageBox.h"
#include "src/comm/GlobalData.h"

ManualIncubationWidgets::ManualIncubationWidgets(QWidget *parent)
    : BaseDialog(parent)
    ,
    ui(new Ui::ManualIncubationWidgetsClass) 
    , m_instr(Instrument::instance())
{
    setWindowModality(Qt::WindowModal);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background-color:#FFFFFFFF;");

    ui->setupUi(this);
    //setWindowOpacity(0.5);
    myTimer = new QTimer(this);//父亲：当前对象传递进去
    connect(myTimer, &QTimer::timeout, this, &ManualIncubationWidgets::doProcessTimeout);
    ui->progressBar->setStyleSheet(
        "QProgressBar{border:1px solid #FFFFFF;"
        "height:30;"
        "background:grey;"
        "text-align:right;"
        "color:rgb(255,255,255);"
        "border-radius:0px;}"
        "QProgressBar::chunk{"
        "border-radius:5px;"    // 斑马线圆角
        "border:1px solid black;" // 黑边，默认无边
        "background-color:white;"
        "width:8px;margin:0.5px;}" // 宽度和间距
    );



    //ui->progressBar->setStyleSheet("QProgressBar{text-align:center;background-color:#DDDDDD;border: 1px solid #ff0000;}"
    //	"QProgressBar::chunk{background-color:#05B8CC;}");

    //文字居中 text-align:center;
    //设置圆角 border-radius 这里要注意如果设置的圆角大于或等进度条高度的一半，圆角设置无效， 比如进度条的高度为10， 圆然设置为5px或以上就不会起作用
    //ui->progressBar->setStyleSheet("QProgressBar{text-align:center;background-color:#DDDDDD;border: 0px solid #DDDDDD;border-radius:5px;}"
    //	"QProgressBar::chunk{background-color:#05B8CC; border-radius: 5px;}");

    ////块显示
    //ui->progressBar_3->setStyleSheet("QProgressBar{text-align:center;background-color:#DDDDDD;border: 0px solid #DDDDDD;border-radius:5px;}"
    //	"QProgressBar::chunk{background-color:#05B8CC;border-radius:5px; width:8px;margin:0.5px;}");

    ////进度块渐变
    //ui->progressBar->setStyleSheet("QProgressBar{height:22px; text-align:center; font-size:14px; color:white; border-radius:6px; background:#FFFFFF;}"
    //	"QProgressBar::chunk{border-radius:11px;background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #99ffff,stop:1 #9900ff);}");





    //ui->groupBox_2->setStyleSheet(
    //	"QGroupBox{border:1px solid #FFFFFF;"
    //	"height:30;"
    //	"background:grey;"
    //	"text-align:right;"
    //	"color:rgb(255,255,255);"
    //	"border-radius:0px;}"
    //	"QProgressBar::chunk{"
    //	"border-radius:3px;"    // 斑马线圆角
    //	"border:1px solid black;" // 黑边，默认无边
    //	"background-color:white;"
    //	"width:8px;margin:0.5px;}" // 宽度和间距
    //);

    //ui->groupBox->setStyleSheet(
    //	"QGroupBox{border:1px solid #FFFFFF;"
    //	"height:30;"
    //	"background:grey;"
    //	"text-align:right;"
    //	"color:rgb(0,0,0);"
    //	"border-radius:0px;}"
    //	"QProgressBar::chunk{"
    //	"border-radius:5px;"    // 斑马线圆角
    //	"border:1px solid black;" // 黑边，默认无边
    //	"background-color:white;"
    //	"width:8px;margin:0.5px;}" // 宽度和间距
    //);

    //ui->groupBox->setStyleSheet(
    //	"QLabel{font - family: Microsoft YaHei;font - size: 14px;color: #FFFFFF;background - color: #FFFFFF;}"
    //);

    ui->label->setStyleSheet(
        "QLabel{font - family: Microsoft YaHei;font - size: 14px;color: #BDC8E2;background - color: #2E3648;}"
    );

    QString sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1034");
    ui->label_3->setText(sz1);
    sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1226");
    ui->label->setText(sz1);
    sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1207");
    ui->label_2->setText("5-240"+sz1);
    sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1227");
    ui->btnStartIncubation->setText(sz1);
    sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1228");
    ui->btnIncubationFinish->setText(sz1);
}

void ManualIncubationWidgets::on_btnStartIncubation_clicked()
{
    index = 0;
    mNeed_incubation_times = 0;
    //m_instr->rockBedWorking(3);
    QString need_incubation_times1 = ui->Incubation_time->text();

    if (need_incubation_times1.toInt() == 0)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1363"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
        return;
    }

    if (need_incubation_times1.toInt() <5 || need_incubation_times1.toInt() > 240)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1364"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
        return;
    }

    //Incubation_time

    if (need_incubation_times1 == "")
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1365"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
        return;
    }
    ui->progressBar->setValue(0);
    int need_incubation_times = need_incubation_times1.toInt() * 60;
    ui->progressBar->setRange(0, need_incubation_times);
    myTimer->start(1000);//1s倒计时1次
    ui->btnStartIncubation->setEnabled(false);
    m_instr->incubationByHand(static_cast<uint16_t>(need_incubation_times));
    mNeed_incubation_times = need_incubation_times;
}
void ManualIncubationWidgets::on_btnIncubationFinish_clicked()
{
    if (myTimer->isActive() == true)
    {
        myTimer->stop();
    }
    ui->btnStartIncubation->setEnabled(true);
    m_instr->incubationByHand(static_cast<uint16_t>(0));
    ui->progressBar->setValue(0);
    close();
}

ManualIncubationWidgets::~ManualIncubationWidgets()
{
    delete ui;
}

void ManualIncubationWidgets::doProcessTimeout() {
    index++;
    ui->progressBar->setValue(index);
    if (index == mNeed_incubation_times)
    {
        //m_instr->rockBedWorking(0);
        myTimer->stop();
        ui->btnStartIncubation->setEnabled(true);
        //m_instr->motorInitialize(0x05, 60000);
        //m_instr->setBuzzleOnOff(0x00);
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1366"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }

    if (mNeed_incubation_times - index == 15)
    {
        //m_instr->setBuzzleOnOff(0x03);
    }


    //if (index == 0) {
    //	myTimer->stop();//从10开始倒计时，到这里停止计时
    //	movie->start();//开始播放动画
    //	ui->label->show();
    //	ui->lcdNumber->hide();

    //	this->showFullScreen();//当前对象全屏显示
    //}
    //ui->lcdNumber->display(index);
    //qDebug() << index << endl;
}
