#ifndef KEYBOARDFORMNUM_H
#define KEYBOARDFORMNUM_H

#include <QDialog>

class QLabel;
class QVBoxLayout;

class KeyboardFormNum : public QDialog
{
    Q_OBJECT
public:
    explicit KeyboardFormNum(QWidget *parent = 0);
    ~KeyboardFormNum(){}

signals:
    void sendKeyToFocusItem(const QString &keyText);

public slots:
    void numClicked();
    void setText(QString str);
    void backSpace();
    void changeStyle();

private:
    QWidget *m_btnFrm;              // 按键面板
    QLabel *m_labPyText;            // 显示拼音

    QVBoxLayout *m_mainLayout;

    enum InputMode{ImEn, ImCn, ImNum};
    InputMode m_inputMode;
};
#endif // KEYBOARDFORMNUM_H
