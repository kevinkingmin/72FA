#include "ProgressDialog.h"
#include "ui_ProgressDialog.h"
#include <QMessageBox>
#include <QTimer>
#include <QDesktopWidget>
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/Utilities/log.h"
#include <QBitmap>
#include <QPainter>
#include <QTime>


ProgressDialog::ProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
  ,_StartPosReg(QRegExp("^[1-9]$|^[1-6][0-9]$|^7[0-2]$"))
  ,_timer(nullptr)
  ,_instrState(InstrumentStateModel::instance())
  ,_maxValue(0)
  ,_showTime(0)
{
    setWindowModality(Qt::WindowModal);
    this->setWindowFlags(Qt::Dialog |Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background-color:#FFFFFFFF;");
    ui->setupUi(this);


	//ui->progressBar->setStyleSheet(
	//	"QProgressBar{border:1px solid #FF9955;"
	//	"height:30;"
	//	"background:#F3F3F3;"
	//	"text-align:right;"
	//	"color:#FF9955;"
	//	"border-radius:15px;}"
	//	"QProgressBar::chunk{"
	//	"border-radius:5px;"    // 斑马线圆角
	//	"border:1px solid black;" // 黑边，默认无边
	//	"background-color:#FF9955;"
	//	"width:8px;margin:0.5px;}" // 宽度和间距
	//	);

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


	ui->groupBox->setStyleSheet(
		"QGroupBox{border:1px solid #D1CFCE;"
		"height:130;"
		"background:#FFFFFF;"
		"text-align:right;"
		"color:rgb(255,255,255);"
		"border-radius:15px;}"
		"QProgressBar::chunk{"
		"border-radius:15px;"    // 斑马线圆角
		"border:1px solid black;" // 黑边，默认无边
		"background-color:white;"
		"width:8px;margin:0.5px;}" // 宽度和间距
	);

	//ui->lblHead->setStyleSheet(
	//"QLabel{font - family: Microsoft YaHei;font - size: 14px;background:red;}"
	//);
	//ui->label_2->setStyleSheet(
	//	"QLabel{font - family: Microsoft YaHei;font - size: 14px;background:red;}"
	//);
	ui->lblHead->setStyleSheet("background:transparent;}");
	ui->label_2->setStyleSheet("background:transparent;}");
}

ProgressDialog::~ProgressDialog()
{
    if (_timer != nullptr)
        delete _timer;
    delete ui;
}

void ProgressDialog::showEvent(QShowEvent *)
{
    QDesktopWidget *desk=QApplication::desktop();
    int wd=desk->width()+32+16;
    int ht=desk->height();
    move((wd-width())/2,(ht-height())/2);
    ui->progressBar->setValue(0);
    updateProgress(_maxValue);

	ui->lblHead->setStyleSheet("background:transparent;}");
	ui->label_2->setStyleSheet("background:transparent;}");
}

void ProgressDialog::hideEvent(QHideEvent *)
{
    _maxValue=0;
    _showTime=0;
	_timer->stop();
}

void ProgressDialog::updateProgress(int maxValue)
{
    if (_timer != nullptr)
    {
        delete _timer;
        _timer = nullptr;
    }
    _timer = new QTimer(this);
    _timer->setInterval(1000);
    ui->progressBar->setRange(0, maxValue);
    QTime time;
    time.start();
    connect(_timer, &QTimer::timeout, this, [this, maxValue,time]()
    {
        _showTime-=time.elapsed()/1000;
        if(_showTime>0)
            ui->lblHead->setText(ui->lblHead->text()+tr("(%1)").arg(_showTime));
        else
            _showTime=0;

        if (maxValue <= 0)
        {
            setProgressState();
        }
        else
        {
            int curValue = ui->progressBar->value();//可以
            curValue+=1000;
            ui->progressBar->setValue(curValue);
            //setProgressState();
            if (curValue >= maxValue + 1)
            {
                setProgressState();
                _timer->stop();
                //this->hide();
            }
            ui->progressBar->setFormat(tr("当前进度:") + QString::number((curValue*1.0) / maxValue * 100.0, 'f', 2) + "%");
            ui->progressBar->setValue(curValue);
        }
    }, Qt::UniqueConnection);

    _timer->start();
}

void ProgressDialog::setHead(const QString &str)
{
    ui->lblHead->setText(str);
}

void ProgressDialog::setProgressState()
{
    auto state = _instrState->getMachineState().state;
    switch (state)
    {
    case InstrumentStateModel::enumStandby:
    {
        _timer->stop();
        //hide();
        break;
    }
    case InstrumentStateModel::enumError:
    {
        _timer->stop();
        //hide();
        break;
    }
    default:
    {
        //assert(false);
        iLog("当前状态为:{}", state);
    }
    }
}

void ProgressDialog::setShowTime(int showTime)
{
    _showTime = showTime;
}

void ProgressDialog::setMaxValue(int maxValue)
{
    _maxValue = maxValue;
}

//void ProgressDialog::resizeEvent(QResizeEvent* e)
//{
//	QBitmap bmp(size());
//	bmp.fill();
//	QPainter p(&bmp);
//	p.setRenderHint(QPainter::Antialiasing);
//	//p.drawRoundedRect(bmp.rect(), 20, 20); //四个角都是圆弧 
//	//只要上边角圆弧 
//	int arcR = 10; //圆弧大小
//	QRect rect = this->rect().adjusted(0, 0, 0, 0);
//	QPainterPath path;
//	//逆时针 
//	path.moveTo(arcR, 0);
//	//左上角
//	path.arcTo(0, 0, arcR * 2, arcR * 2, 90.0f, 90.0f);
//	path.lineTo(0, rect.height() - arcR);
//	//左下角
//	path.arcTo(0, rect.height() - arcR * 2, arcR * 2, arcR * 2, 180.0f, 90.0f);
//	path.lineTo(rect.width(), rect.height());
//	//右下角
//	path.arcTo(rect.width() - arcR * 2, rect.height() - arcR * 2, arcR * 2, arcR * 2, 270.0f, 90.0f);
//	path.lineTo(rect.width(), arcR);
//	//右上角
//	path.arcTo(rect.width() - arcR * 2, 0, arcR * 2, arcR * 2, 0.0f, 90.0f);
//	path.lineTo(arcR, 0);
//	p.drawPath(path);
//	//此行代码必须添加，不然无法达到正常的显示
//	p.fillPath(path, QBrush(Qt::red));
//	setMask(bmp);
//
//	return QDialog::resizeEvent(e);
//}
