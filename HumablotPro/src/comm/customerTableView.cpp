#include "customerTableView.h"
#include <QMouseEvent>

CustomerTableView::CustomerTableView(QWidget *parent):QTableView (parent)
{

}

void CustomerTableView::mousePressEvent(QMouseEvent *event)
{
    int xPos = event->x();
    int yPos = event->y();
    QModelIndex idx = indexAt(QPoint(xPos, yPos));
    if(!idx.isValid( ))
    {
        emit signalBlankArea(event);
    }
    else
    {
        emit signalDataArea(event);
        if(event->button()==Qt::RightButton)
        {
            return;
        }
    }
    QTableView::mousePressEvent(event);
}
