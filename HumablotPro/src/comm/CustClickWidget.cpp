#include "CustClickWidget.h"
#include <QVariant>

CustClickWidget::CustClickWidget(QWidget *parent):QWidget (parent)
{
}

CustClickWidget::~CustClickWidget()
{
}

void CustClickWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    emit clicked();
}
