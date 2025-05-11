#include "CustomerPumpStateLable.h"
#include <QStylePainter>
#include <QPixmap>

#define LBLWIDTH 36
#define LBLHEIGHT 62
CustomerPumpStateLable::CustomerPumpStateLable(QWidget *parent):QLabel (parent)
  ,_pos(0)
  ,_pixPath("")
  ,_timeStr("")
{

}

CustomerPumpStateLable::~CustomerPumpStateLable()
{

}

void CustomerPumpStateLable::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);
    this->setMinimumWidth(LBLWIDTH);
    this->setMaximumWidth(LBLWIDTH+3);

    this->setMinimumHeight(LBLHEIGHT);

    QFont font = painter.font();
    font.setPixelSize(17);
    font.setFamily("simsun");
    painter.setFont(font);
    QRect numRect(0,0,LBLWIDTH,21);
    painter.drawText(numRect,Qt::AlignCenter,QString::number(_pos));

    auto pix=QPixmap(_pixPath);
    QRect pixRect(LBLWIDTH/2-8,21,16,16);
    painter.drawPixmap(pixRect,pix);
    font.setPixelSize(13);
    painter.setFont(font);
    QRect timeRect(0,42,LBLWIDTH,20);
    painter.drawText(timeRect,Qt::AlignCenter,_timeStr);
}

void CustomerPumpStateLable::setTimeStr(const QString &timeStr)
{
    _timeStr = timeStr;
}

void CustomerPumpStateLable::reset()
{
    _pos=0;
    _pixPath="";
    _timeStr="";
}

void CustomerPumpStateLable::setPixPath(const QString &pixPath)
{
    _pixPath = pixPath;
}

void CustomerPumpStateLable::setPos(int pos)
{
    _pos = pos;
}
