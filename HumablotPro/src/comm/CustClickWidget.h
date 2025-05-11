#ifndef CUSTCLICKWIDGET_H
#define CUSTCLICKWIDGET_H

#include <QWidget>

class CustClickWidget:public QWidget
{
    Q_OBJECT
public:
    explicit CustClickWidget(QWidget *parent = nullptr);
    virtual ~CustClickWidget();

signals:
    void clicked();

protected:
    virtual void mouseReleaseEvent(QMouseEvent * ev);
};

#endif // CUSTCLICKWIDGET_H
