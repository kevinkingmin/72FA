#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H
#include <QLabel>
#include <QColor>
class CustomLabel:public QLabel
{
    Q_OBJECT 
public:
    explicit CustomLabel(QWidget *parent=nullptr);
    virtual ~CustomLabel();
    void setBgColor(const QString &bgColor);

    void setPos(int pos);
    int getPos() const;
    void reset();

protected:
    void paintEvent(QPaintEvent *);
    virtual void mouseReleaseEvent(QMouseEvent * ev);
signals:
    void clicked(int);

private:
    QString _bgColor;
    int _pos;
};

#endif // CUSTOMLABEL_H
