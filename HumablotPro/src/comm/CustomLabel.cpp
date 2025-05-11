#include "CustomLabel.h"
#include <QPainter>
#include <QStylePainter>
#include "GlobalData.h"

#define LBLWIDTH 22
#define LBLHEIGHT 180
CustomLabel::CustomLabel(QWidget *parent):QLabel (parent)
  ,_bgColor("#D3D3D3")
  ,_pos(0)
{
    clear();
}

CustomLabel::~CustomLabel()
{    
}


void CustomLabel::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);
    QFont font = painter.font();
    font.setPixelSize(19);
    font.setFamily("simsun");
    font.setWeight(64);
    QPalette palette;
    if(_pos<=24)
    {
        palette.setColor(QPalette::Background, QColor(FIRSTPAPERRACK));
    }
    else if(_pos<=48)
    {
        palette.setColor(QPalette::Background, QColor(SECONDPAPERRACK));
    }
    else
    {
        palette.setColor(QPalette::Background, QColor(THIRDPAPERRACK));
    }

    setAutoFillBackground(true);
    setPalette(palette);
    this->setMinimumWidth(LBLWIDTH);

	if (_pos <= 36)
	{
		//QBrush brush;
		//brush.setColor(Qt::gray);
		//brush.setStyle(Qt::BDiagPattern);
		//painter.setBrush(brush);
		//// 画矩形；
		//painter.drawRect(0, 0, 100, 500);
	}
	else
	{
		//创建画刷
		//QBrush brush;
		//brush.setColor(Qt::black);
		//brush.setStyle(Qt::FDiagPattern);
		//painter.setBrush(brush);
		//// 画矩形；
		//painter.drawRect(0, 0, 100, 500);
	}
    this->setMaximumWidth(LBLWIDTH+3);
    this->setMinimumHeight(LBLHEIGHT);
    painter.setFont(font);
	QRect numRect(0, 0, LBLWIDTH, LBLWIDTH);

	QColor color("#F67D52");
	if (underMouse()) 
	{
		painter.fillRect(numRect, color); // 绘制白色背景
	}
	if (_pos <= 36)
	{
		painter.drawText(numRect, Qt::AlignCenter, QString::number(_pos));
	}
	else
	{
		painter.drawText(numRect, Qt::AlignCenter, QString::number(_pos - 36));
	}
    QPixmap pix(height(),height());
    QPainter p(&pix);
    pix.fill(QColor(_bgColor));
	p.translate(2, pix.height() - LBLWIDTH - 8);
	p.rotate(-90);
    p.setFont(font);
	p.drawText(pix.rect(), text());
    painter.drawPixmap(0,LBLWIDTH,pix);
}

void CustomLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    emit clicked(_pos);
}

int CustomLabel::getPos() const
{
    return _pos;
}

void CustomLabel::reset()
{
    _bgColor="#D3D3D3";
    setText("");
}

void CustomLabel::setBgColor(const QString &bgColor)
{
    _bgColor = bgColor;
}

void CustomLabel::setPos(int pos)
{
    _pos=pos;
}



