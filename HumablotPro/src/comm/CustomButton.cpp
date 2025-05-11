#include "CustomButton.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QVariant>
#define MARGINSIZE 8
#define SPACE  3
#define LABELHEIGHT 21
#define FONTSIZE 13

CustomButton::CustomButton(QWidget *parent):QPushButton (parent)
  ,_upText("")
  ,_reagentName("")
  ,_timeText("")
  ,_pixPath("")
	,_btn_id(0)
  ,_lblUp(new QLabel(this))
  ,_lblPix(new QLabel(this))
  ,_lblReagent(new QLabel(this))
  ,_lblVolumn(new QLabel(this))
  ,_lblTime(new QLabel(this))
	, _lblSpace(new QLabel(this))
  ,m_vLay(new QVBoxLayout(this))
{
    this->setStyleSheet("*{font:"+QString::number(FONTSIZE)+"pt;font-family:Calibri,黑体,simsun;}");
}

CustomButton::~CustomButton()
{
}

void CustomButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    setText("");

    _lblUp->setText(_upText);
    _lblReagent->setText(_reagentName);
    _lblVolumn->setText(_volumn);
    _lblTime->setText(_timeText);
	_lblSpace->setText("");

    auto pix=QPixmap(_pixPath);
    pix=pix.scaled(_lblPix->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //_lblPix->setScaledContents(true);

    _lblPix->setPixmap(pix);
    _lblUp->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _lblReagent->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _lblVolumn->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _lblTime->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _lblPix->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_vLay->addWidget(_lblUp);
    m_vLay->addWidget(_lblPix);

	m_vLay->addWidget(_lblSpace);
	m_vLay->addWidget(_lblSpace);
    m_vLay->addWidget(_lblReagent);
    m_vLay->addWidget(_lblVolumn);
    m_vLay->addWidget(_lblTime);
    m_vLay->setSpacing(SPACE);
    m_vLay->setMargin(MARGINSIZE);
    auto chCount=getChineseCount(_lblReagent->text());
    int enCount=_lblReagent->text().length()-chCount;
    int minWidth= enCount*(FONTSIZE) + chCount*(2*(FONTSIZE-2));

    if(minWidth < pix.width())
        minWidth=pix.width();

    minWidth=minWidth<96?96:minWidth;

	//应要求，改为宽一致 linshi 2024-01-02;
	minWidth = 160;


    _lblPix->setFixedSize(minWidth-MARGINSIZE*2,_lblPix->height());
    auto minHeight=_lblPix->height()+LABELHEIGHT*6+MARGINSIZE*2+SPACE*6;

    this->setMinimumHeight(minHeight);
    this->setMinimumWidth(minWidth);
    this->adjustSize();
    this->setLayout(m_vLay);
}

int CustomButton::getChineseCount(const QString &str)
{
    int chCount=0;
    int nCount = str.count();
    for(int i = 0 ; i < nCount ; i++)
    {
        QChar cha = str.at(i);
        ushort uni = cha.unicode();
        if(uni >= 0x4E00 && uni <= 0x9FA5)
        {
            chCount++;
        }
    }
    return chCount;
}

void CustomButton::setUpText(const QString &upText)
{
    _upText = upText;
}

void CustomButton::setBtnId(int id)
{
	_btn_id = id;
}

void CustomButton::setReagentName(const QString &reagentName)
{
    _reagentName = reagentName;
}

QString CustomButton::getReagentName()
{
	return _reagentName;
}

int CustomButton::getBtnId()
{
	return _btn_id;
}

void CustomButton::setVolumn(const QString &volumn)
{
    _volumn = volumn;
}

QString CustomButton::getVolumn() const
{
    return _volumn;
}

void CustomButton::setTimeText(const QString &timeText)
{
    _timeText = timeText;
}

QString CustomButton::getTimeText()
{
    return _timeText;
}

void CustomButton::setPixPath(const QString &pixPath)
{
    _pixPath = pixPath;
}

void CustomButton::setLblPixSize(int width, int height)
{
    _lblPix->setFixedWidth(width);
    _lblPix->setFixedHeight(height);
}

void CustomButton::reset(const QString &pixPath)
{
    //_upText="";
    _reagentName="";
    _volumn="";
    _timeText="";
    _pixPath=pixPath;
    setCheckable(false);
}




