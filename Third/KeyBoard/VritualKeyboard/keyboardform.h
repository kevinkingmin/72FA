﻿#ifndef KEYBOARDFROM_H
#define KEYBOARDFROM_H

#include <QDialog>
#include "googlepinyin.h"

class QLineEdit;
class QLabel;
class QVBoxLayout;

class KeyboardForm : public QDialog
{
    Q_OBJECT
public:
    explicit KeyboardForm(QWidget *parent = 0);
    ~KeyboardForm(){}

signals:
    void sendKeyToFocusItem(const QString &keyText);

public slots:
    void letterClicked();
    void numClicked();
    void hanziClicked();
    void setText(QString str);
    void shiftClicked();
    void changeInputMode();
    void changeSymbol();
    void space();
    void enter();
    void backSpace();
    void prevPage();
    void nextPage();
    void changeStyle();
//protected:
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
private:
    void displayHanzi();
    void hideEvent(QHideEvent *);
private:
    QWidget *m_pyFrm;               // 拼音面板
    QWidget *m_btnFrm;              // 按键面板
    QLabel *m_labPyText;            // 显示拼音

    QString m_cachePinYin;          // 真实拼音缓存

    QList<QPushButton*> m_listHanzi;
    QList<QPushButton*> m_listCharsBtns; // A-Z Symbol

    QVBoxLayout *m_mainLayout;
    QPushButton *m_btnChange;
    QPushButton *m_btnShift;
    QPushButton *m_btnSymbol;
    QPushButton *m_btnSpace; // 显示切换输入法

    enum InputMode{ImEn, ImCn, ImNum};
    InputMode m_inputMode;
    bool m_shiftKey;
    int m_hanziPageCnt, m_curHanziPage;
    GooglePinyin m_pinyin;

    QPoint last;             //鼠标按下位置
};
#endif // KEYBOARDFROM_H
