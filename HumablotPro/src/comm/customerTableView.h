#ifndef CUSTOMERTABLEVIEW_H
#define CUSTOMERTABLEVIEW_H

#include <QTableView>

class CustomerTableView : public QTableView
{
    Q_OBJECT
public:
    CustomerTableView(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent * event) override;
signals:
    void signalBlankArea(QMouseEvent *event);
    void signalDataArea(QMouseEvent *event);
};

#endif // CUSTOMERTABLEVIEW_H
