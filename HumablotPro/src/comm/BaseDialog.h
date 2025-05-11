#ifndef BASEDIALOG_H
#define BASEDIALOG_H
#include <QDialog>
#include <QMouseEvent>
#include <QPoint>
class BaseDialog:public QDialog
{
    Q_OBJECT
public:
    BaseDialog(QWidget *parent = nullptr);
    virtual~BaseDialog()override;

protected:
    virtual void mousePressEvent(QMouseEvent* event)override;
    virtual void mouseMoveEvent(QMouseEvent* event)override;
    virtual void mouseReleaseEvent(QMouseEvent* event)override;
    virtual void centerDisplay();
private:
    QPoint _mPress;
    QPoint _mMove;
    bool _leftBtnClk = false;
};

#endif // BASEDIALOG_H
