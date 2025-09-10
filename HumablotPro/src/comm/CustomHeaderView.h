#ifndef CUSTOMHEADERVIEW_H
#define CUSTOMHEADERVIEW_H
#include <QHeaderView>
#include <QPainter>

class CustomHeaderView:public QHeaderView
{
public:
    CustomHeaderView(int columnIndex,
                     Qt::Orientation orientation=Qt::Horizontal,
                     QWidget *parent = nullptr);
public:
    void setWidgetObject(QWidget* w);
    void setColumnIndex(int columnIndex);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
private:
    int           m_columnIndex;
    QWidget      *m_widget;
};

#endif // CUSTOMHEADERVIEW_H
