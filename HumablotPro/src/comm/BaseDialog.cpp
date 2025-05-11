#include "BaseDialog.h"
#include <QDesktopWidget>
#include <QApplication>

BaseDialog::BaseDialog(QWidget *parent)
    :QDialog (parent)
{
    setWindowModality(Qt::WindowModal);
    this->setWindowFlags(Qt::Dialog |Qt::FramelessWindowHint);
}

BaseDialog::~BaseDialog()
{

}

void BaseDialog::mousePressEvent(QMouseEvent *event)
{
     QWidget*lbl = this->findChild<QWidget *>("widgetTop");
     if(!lbl)
         return;
    if (event->button() == Qt::LeftButton && lbl->frameGeometry().contains(event->globalPos() - this->frameGeometry().topLeft()))
    {
        _mPress = event->globalPos();
        _leftBtnClk = true;
    }
    event->ignore();
}

void BaseDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (_leftBtnClk)
    {
        _mMove = event->globalPos();
        this->move(this->pos() + _mMove - _mPress);
        _mPress = _mMove;
    }
    event->ignore();
}

void BaseDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        _leftBtnClk = false;
    }
    event->ignore();
}

void BaseDialog::centerDisplay()
{
    QDesktopWidget *desk=QApplication::desktop();
    int wd=desk->width();
    int ht=desk->height();
    move((wd-width())/2,(ht-height())/2);
}
