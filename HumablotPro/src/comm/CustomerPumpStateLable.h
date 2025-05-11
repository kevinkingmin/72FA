#ifndef CUSTOMERPUMPSTATELABLE_H
#define CUSTOMERPUMPSTATELABLE_H
#include <QLabel>

class CustomerPumpStateLable:public QLabel
{
public:
    explicit CustomerPumpStateLable(QWidget *parent=nullptr);
    virtual ~CustomerPumpStateLable();
    void setPos(int pos);
    void setPixPath(const QString &pixPath);
    void setTimeStr(const QString &timeStr);
    void reset();

protected:
    void paintEvent(QPaintEvent *);
private:
    int _pos;
    QString _pixPath;
    QString _timeStr;
};

#endif // CUSTOMERPUMPSTATELABLE_H
