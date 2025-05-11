#include "keyboardformnum.h"

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QFontDatabase>
#include <QApplication>
#include <QDebug>


const char *kbNumber_num = "123456789";
const int verSpace = 4;
const int horSpace = 4;
const int margins = 4;
const int btnHeight = (220 - verSpace*5)/5;
const int btnWidth = (600 - margins*2 - horSpace*10)/10.8+0.5;

KeyboardFormNum::KeyboardFormNum(QWidget *parent) : QDialog(parent),
    m_inputMode(ImNum)
{
    setWindowModality(Qt::WindowModal);
    setWindowFlags(windowFlags() | Qt::Tool |
                   Qt::FramelessWindowHint |
                   Qt::WindowStaysOnTopHint |
                   Qt::WindowDoesNotAcceptFocus);

    //图标字体
    int fontId = QFontDatabase::addApplicationFont(":/font/FontAwesome.otf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont icofont(fontName);
    icofont.setPixelSize(20);

    //按键字体
    QFont deffont("Courier");
    deffont.setPixelSize(18);

    QVBoxLayout *pyLayout = new QVBoxLayout;

    //数字
    QHBoxLayout *h1 = new QHBoxLayout;
    QHBoxLayout *h2 = new QHBoxLayout;
    QHBoxLayout *h3 = new QHBoxLayout;

    for (int j = 0; j < 3; j++)
    {
        QPushButton *btn = new QPushButton(QString(QLatin1Char(kbNumber_num[j])));
        btn->setFixedSize(btnWidth, btnHeight);
        btn->setFont(deffont);
        connect(btn, SIGNAL(clicked()), SLOT(numClicked()));
        h1->addWidget(btn);
    }
    for (int j = 3; j < 6; j++)
    {
        QPushButton *btn = new QPushButton(QString(QLatin1Char(kbNumber_num[j])));
        btn->setFixedSize(btnWidth, btnHeight);
        btn->setFont(deffont);
        connect(btn, SIGNAL(clicked()), SLOT(numClicked()));
        h2->addWidget(btn);
    }
    for (int j = 6; j < 9; j++)
    {
        QPushButton *btn = new QPushButton(QString(QLatin1Char(kbNumber_num[j])));
        btn->setFixedSize(btnWidth, btnHeight);
        btn->setFont(deffont);
        connect(btn, SIGNAL(clicked()), SLOT(numClicked()));
        h3->addWidget(btn);
    }
    pyLayout->addLayout(h3);
    pyLayout->addLayout(h2);
    pyLayout->addLayout(h1);

    QHBoxLayout *h5 = new QHBoxLayout;

    QPushButton *btnBack = new QPushButton();
    btnBack->setFont(icofont);
    btnBack->setText(QChar(0xf060));
    btnBack->setFixedSize(btnWidth, btnHeight);
    btnBack->setAutoRepeat(true);
    connect(btnBack, SIGNAL(clicked()), SLOT(backSpace()));

    QString letter(".0-");
    QPushButton* btn = new QPushButton(letter.at(0));
    btn->setFont(deffont);
    btn->setFixedSize(btnWidth, btnHeight);
    connect(btn, SIGNAL(clicked()), SLOT(numClicked()));

    QPushButton *zerobtn = new QPushButton(letter.at(1));
    zerobtn->setFont(deffont);
    zerobtn->setFixedSize(btnWidth, btnHeight);
    connect(zerobtn, SIGNAL(clicked()), SLOT(numClicked()));

    QPushButton *negativebtn = new QPushButton(letter.at(2));
    negativebtn->setFont(deffont);
    negativebtn->setFixedSize(btnWidth, btnHeight);
    connect(negativebtn, SIGNAL(clicked()), SLOT(numClicked()));

    QString text = QChar(0xf11c);
    text.append(QChar(0xf103));
    QPushButton *btnHide = new QPushButton(text);
    btnHide->setFont(icofont);
    btnHide->setFixedSize(btnWidth, btnHeight);
    connect(btnHide, SIGNAL(clicked()), SLOT(hide()));

    h5->addWidget(btn);
    h5->addWidget(zerobtn);
    h5->addWidget(negativebtn);

    QVBoxLayout *otherLayout = new QVBoxLayout;
    otherLayout->addWidget(btnBack);
    otherLayout->addWidget(btnHide);

    QVBoxLayout *boradLayout = new QVBoxLayout;

    boradLayout->addLayout(pyLayout);
    boradLayout->addLayout(h5);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(boradLayout);
    mainLayout->addLayout(otherLayout);
    // 键盘widget容器
    m_btnFrm = new QWidget();
    m_btnFrm->setLayout(mainLayout);

    // 主布局
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);
    m_mainLayout->addWidget(m_btnFrm);
    setLayout(m_mainLayout);

    changeStyle();
}

void KeyboardFormNum::numClicked()
{
    sendKeyToFocusItem(((QPushButton*)sender())->text());
}

void KeyboardFormNum::setText(QString str)
{
    m_labPyText->setVisible(str.size());
    m_labPyText->setText(str);
}

void KeyboardFormNum::backSpace()
{
    if (m_inputMode == ImNum)
    {
        sendKeyToFocusItem("\x7F");
    }
}

void KeyboardFormNum::changeStyle()
{
    setStyleSheet("QPushButton{border-image: url(:/images/btn2.png); "
                  "border-width: 5; "
                  "font: normal } "
                  "QPushButton:pressed{border-image: url(:/images/btn3.png); "
                  "border-width: 5;}");
    m_btnFrm->setStyleSheet("background:#D1D4DA;");
}

