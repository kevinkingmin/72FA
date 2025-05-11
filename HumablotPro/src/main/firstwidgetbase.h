#ifndef FIRSTWIDGETBASE_H
#define FIRSTWIDGETBASE_H

#include <QWidget>

class FirstWidgetBase : public QWidget
{
    Q_OBJECT
public:
    explicit FirstWidgetBase(QWidget *parent = nullptr);
    virtual ~FirstWidgetBase();
signals:

public slots:
};

#endif // FIRSTWIDGETBASE_H
