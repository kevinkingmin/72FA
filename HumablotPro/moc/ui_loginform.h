/********************************************************************************
** Form generated from reading UI file 'loginform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogInForm
{
public:
    QGridLayout *gridLayout;
    QWidget *widgetLogInBackground;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_12;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_24;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_18;
    QLabel *labelTitleLogin;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_13;
    QLabel *labelTitle1Login;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer;
    QWidget *widgetLogIn;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QLabel *labelLogIn;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_22;
    QLabel *labelLogInUserName;
    QSpacerItem *horizontalSpacer_23;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QComboBox *comboBox_UserName;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_20;
    QLabel *labelLogInPasssord;
    QSpacerItem *horizontalSpacer_21;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *lineEditPassWord;
    QSpacerItem *horizontalSpacer_19;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pushButtonLogIn;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButtonLogOut;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_15;
    QLabel *labelVersionInfo;
    QSpacerItem *horizontalSpacer_16;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_14;
    QLabel *labelCampanyInfo;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *LogInForm)
    {
        if (LogInForm->objectName().isEmpty())
            LogInForm->setObjectName(QString::fromUtf8("LogInForm"));
        LogInForm->resize(1019, 736);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../favicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        LogInForm->setWindowIcon(icon);
        gridLayout = new QGridLayout(LogInForm);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widgetLogInBackground = new QWidget(LogInForm);
        widgetLogInBackground->setObjectName(QString::fromUtf8("widgetLogInBackground"));
        gridLayout_2 = new QGridLayout(widgetLogInBackground);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_12 = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_24 = new QSpacerItem(30, 40, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_24);

        label_2 = new QLabel(widgetLogInBackground);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(450, 60));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/buttonIcon/login_logo.png")));

        horizontalLayout_13->addWidget(label_2);


        verticalLayout_2->addLayout(horizontalLayout_13);

        verticalSpacer_8 = new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_18);

        labelTitleLogin = new QLabel(widgetLogInBackground);
        labelTitleLogin->setObjectName(QString::fromUtf8("labelTitleLogin"));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(20);
        labelTitleLogin->setFont(font);

        horizontalLayout_6->addWidget(labelTitleLogin);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_6);

        verticalSpacer_6 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_13);

        labelTitle1Login = new QLabel(widgetLogInBackground);
        labelTitle1Login->setObjectName(QString::fromUtf8("labelTitle1Login"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(12);
        labelTitle1Login->setFont(font1);

        horizontalLayout_7->addWidget(labelTitle1Login);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_7);

        verticalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_9);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_6 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        horizontalSpacer = new QSpacerItem(345, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        widgetLogIn = new QWidget(widgetLogInBackground);
        widgetLogIn->setObjectName(QString::fromUtf8("widgetLogIn"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetLogIn->sizePolicy().hasHeightForWidth());
        widgetLogIn->setSizePolicy(sizePolicy);
        widgetLogIn->setMinimumSize(QSize(100, 0));
        widgetLogIn->setFocusPolicy(Qt::NoFocus);
        widgetLogIn->setProperty("sizeHint", QVariant(QSize(237, 349)));
        widgetLogIn->setLayoutDirection(Qt::LeftToRight);
        widgetLogIn->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(widgetLogIn);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(15, 15, 15, 15);
        label_6 = new QLabel(widgetLogIn);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);

        labelLogIn = new QLabel(widgetLogIn);
        labelLogIn->setObjectName(QString::fromUtf8("labelLogIn"));
        labelLogIn->setFocusPolicy(Qt::NoFocus);
        labelLogIn->setStyleSheet(QString::fromUtf8(""));
        labelLogIn->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelLogIn);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_22 = new QSpacerItem(33, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_22);

        labelLogInUserName = new QLabel(widgetLogIn);
        labelLogInUserName->setObjectName(QString::fromUtf8("labelLogInUserName"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelLogInUserName->sizePolicy().hasHeightForWidth());
        labelLogInUserName->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(labelLogInUserName);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_23);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_9 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        comboBox_UserName = new QComboBox(widgetLogIn);
        comboBox_UserName->setObjectName(QString::fromUtf8("comboBox_UserName"));

        horizontalLayout_3->addWidget(comboBox_UserName);

        horizontalSpacer_10 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalSpacer_20 = new QSpacerItem(33, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_20);

        labelLogInPasssord = new QLabel(widgetLogIn);
        labelLogInPasssord->setObjectName(QString::fromUtf8("labelLogInPasssord"));
        sizePolicy1.setHeightForWidth(labelLogInPasssord->sizePolicy().hasHeightForWidth());
        labelLogInPasssord->setSizePolicy(sizePolicy1);

        horizontalLayout_12->addWidget(labelLogInPasssord);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_21);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_8 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        lineEditPassWord = new QLineEdit(widgetLogIn);
        lineEditPassWord->setObjectName(QString::fromUtf8("lineEditPassWord"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEditPassWord->sizePolicy().hasHeightForWidth());
        lineEditPassWord->setSizePolicy(sizePolicy2);
        lineEditPassWord->setContextMenuPolicy(Qt::NoContextMenu);
        lineEditPassWord->setMaxLength(12);
        lineEditPassWord->setEchoMode(QLineEdit::Password);
        lineEditPassWord->setAlignment(Qt::AlignCenter);
        lineEditPassWord->setProperty("showFull", QVariant(true));

        horizontalLayout_4->addWidget(lineEditPassWord);

        horizontalSpacer_19 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_19);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, 0, -1);
        horizontalSpacer_11 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_11);

        pushButtonLogIn = new QPushButton(widgetLogIn);
        pushButtonLogIn->setObjectName(QString::fromUtf8("pushButtonLogIn"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButtonLogIn->sizePolicy().hasHeightForWidth());
        pushButtonLogIn->setSizePolicy(sizePolicy3);
        pushButtonLogIn->setMaximumSize(QSize(16777215, 16777215));
        pushButtonLogIn->setFocusPolicy(Qt::StrongFocus);
        pushButtonLogIn->setContextMenuPolicy(Qt::NoContextMenu);
        pushButtonLogIn->setStyleSheet(QString::fromUtf8(""));
        pushButtonLogIn->setAutoDefault(false);
        pushButtonLogIn->setFlat(false);

        horizontalLayout_2->addWidget(pushButtonLogIn);

        horizontalSpacer_12 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_12);


        verticalLayout->addLayout(horizontalLayout_2);

        label_7 = new QLabel(widgetLogIn);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout->addWidget(label_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_7);

        pushButtonLogOut = new QPushButton(widgetLogIn);
        pushButtonLogOut->setObjectName(QString::fromUtf8("pushButtonLogOut"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButtonLogOut->sizePolicy().hasHeightForWidth());
        pushButtonLogOut->setSizePolicy(sizePolicy4);
        pushButtonLogOut->setContextMenuPolicy(Qt::NoContextMenu);

        horizontalLayout_9->addWidget(pushButtonLogOut);


        verticalLayout->addLayout(horizontalLayout_9);

        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(8, 2);

        horizontalLayout->addWidget(widgetLogIn);

        pushButton = new QPushButton(widgetLogInBackground);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(345, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalSpacer_5 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_10);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_7);

        verticalSpacer_2 = new QSpacerItem(20, 55, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_15);

        labelVersionInfo = new QLabel(widgetLogInBackground);
        labelVersionInfo->setObjectName(QString::fromUtf8("labelVersionInfo"));

        horizontalLayout_8->addWidget(labelVersionInfo);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_16);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_14);

        labelCampanyInfo = new QLabel(widgetLogInBackground);
        labelCampanyInfo->setObjectName(QString::fromUtf8("labelCampanyInfo"));

        horizontalLayout_5->addWidget(labelCampanyInfo);

        horizontalSpacer_17 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_17);


        verticalLayout_2->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout->addWidget(widgetLogInBackground, 0, 0, 1, 1);


        retranslateUi(LogInForm);

        pushButtonLogIn->setDefault(false);


        QMetaObject::connectSlotsByName(LogInForm);
    } // setupUi

    void retranslateUi(QWidget *LogInForm)
    {
        LogInForm->setWindowTitle(QApplication::translate("LogInForm", "Form", nullptr));
        label_2->setText(QString());
        labelTitleLogin->setText(QApplication::translate("LogInForm", "HumaBlot 72FA \345\205\250\350\207\252\345\212\250\345\205\215\347\226\253\345\215\260\350\277\271\344\273\252", nullptr));
        labelTitle1Login->setText(QApplication::translate("LogInForm", "Full-Automatic Immunoblotting Analyzer", nullptr));
        label_6->setText(QString());
        labelLogIn->setText(QApplication::translate("LogInForm", "\346\254\242\350\277\216\347\231\273\345\275\225", nullptr));
        labelLogInUserName->setText(QApplication::translate("LogInForm", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        labelLogInPasssord->setText(QApplication::translate("LogInForm", "\345\257\206  \347\240\201\357\274\232", nullptr));
        lineEditPassWord->setInputMask(QString());
        lineEditPassWord->setText(QString());
        pushButtonLogIn->setText(QApplication::translate("LogInForm", "\347\253\213\345\210\273\347\231\273\345\275\225", nullptr));
        label_7->setText(QString());
        pushButtonLogOut->setText(QApplication::translate("LogInForm", "   \351\200\200\345\207\272", nullptr));
        pushButton->setText(QApplication::translate("LogInForm", "PushButton", nullptr));
        labelVersionInfo->setText(QApplication::translate("LogInForm", "\347\211\210\346\234\254\357\274\232V1.0.0.2  @2023/07/31", nullptr));
        labelCampanyInfo->setText(QApplication::translate("LogInForm", "\345\214\227\344\272\254\350\203\241\346\233\274\346\231\272\351\200\240\347\247\221\346\212\200\346\234\211\351\231\220\350\264\243\344\273\273\345\205\254\345\217\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogInForm: public Ui_LogInForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
