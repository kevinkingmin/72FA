#include "CustomHeaderView.h"

CustomHeaderView::CustomHeaderView(int columnIndex, Qt::Orientation orientation, QWidget *parent)
    :QHeaderView(orientation, parent)
    ,m_columnIndex(columnIndex)
    ,m_widget(nullptr)
{
}

void CustomHeaderView::setWidgetObject(QWidget *w)
{
	m_widget = w;
	if (m_widget == nullptr)
		return;    
    m_widget->setParent(this);
}

void CustomHeaderView::paintSection(QPainter *painter,const QRect &rect,int logicalIndex) const
{
    if (logicalIndex == m_columnIndex)
    {
        if(m_widget==nullptr)
        {
            QHeaderView::paintSection(painter, rect, logicalIndex);
            return;
        }
        m_widget->setGeometry(rect);
    }
    else
    {
        QHeaderView::paintSection(painter, rect, logicalIndex);
    }
}

void CustomHeaderView::setColumnIndex(int columnIndex)
{
    m_columnIndex = columnIndex;
}

