/********************************************************************************
** Form generated from reading UI file 'MainWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *horizontalWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QWidget *hStatusLayout;
    QHBoxLayout *hLayTitle;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_4;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *pBtnLogout;
    QPushButton *pBtnMini;
    QPushButton *pBtnClose;
    QPushButton *pBtnAbout;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *HBMenuBar;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnLisState;
    QPushButton *btnSystemLiquidStatus;
    QPushButton *btnWasteBottle;
    QPushButton *btnRunState;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_6;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_6;
    QWidget *leftMenuWidget;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnSample;
    QPushButton *btnInit;
    QPushButton *btnStop;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget;
    QSpacerItem *verticalSpacer_3;
    QWidget *statusbarWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_osk_open;
    QLabel *lblUser;
    QPushButton *btnCloseBeep1;
    QLabel *lbVersion;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *btnSystemLiquid;
    QLabel *lbTemperature;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *btnMonthMaintain;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lblDateTime;
    QWidget *verticalWidget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *horizontalWidget_21;
    QHBoxLayout *horizontalLayout_4;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(1151, 700);
        MainWidget->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setPointSize(11);
        MainWidget->setFont(font);
        MainWidget->setAcceptDrops(false);
        MainWidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(MainWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalWidget_2 = new QWidget(MainWidget);
        horizontalWidget_2->setObjectName(QString::fromUtf8("horizontalWidget_2"));
        horizontalWidget_2->setMinimumSize(QSize(8, 0));
        horizontalWidget_2->setMaximumSize(QSize(8, 16777215));
        horizontalWidget_2->setStyleSheet(QString::fromUtf8("background-color:#F0F0F0;"));
        horizontalLayout_3 = new QHBoxLayout(horizontalWidget_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        horizontalLayout_2->addWidget(horizontalWidget_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        hStatusLayout = new QWidget(MainWidget);
        hStatusLayout->setObjectName(QString::fromUtf8("hStatusLayout"));
        hLayTitle = new QHBoxLayout(hStatusLayout);
        hLayTitle->setSpacing(10);
        hLayTitle->setContentsMargins(11, 11, 11, 11);
        hLayTitle->setObjectName(QString::fromUtf8("hLayTitle"));
        hLayTitle->setContentsMargins(0, 0, 15, 0);
        label_5 = new QLabel(hStatusLayout);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        hLayTitle->addWidget(label_5);

        label = new QLabel(hStatusLayout);
        label->setObjectName(QString::fromUtf8("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/buttonIcon/LOGOlogo.png")));

        hLayTitle->addWidget(label);

        label_4 = new QLabel(hStatusLayout);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/images/buttonIcon/icon.png")));

        hLayTitle->addWidget(label_4);

        titleLabel = new QLabel(hStatusLayout);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setMinimumSize(QSize(0, 32));
        titleLabel->setFont(font);

        hLayTitle->addWidget(titleLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hLayTitle->addItem(horizontalSpacer);

        pBtnLogout = new QPushButton(hStatusLayout);
        pBtnLogout->setObjectName(QString::fromUtf8("pBtnLogout"));
        pBtnLogout->setMaximumSize(QSize(32, 32));
        pBtnLogout->setFont(font);

        hLayTitle->addWidget(pBtnLogout);

        pBtnMini = new QPushButton(hStatusLayout);
        pBtnMini->setObjectName(QString::fromUtf8("pBtnMini"));
        pBtnMini->setMaximumSize(QSize(32, 32));
        pBtnMini->setFont(font);

        hLayTitle->addWidget(pBtnMini);

        pBtnClose = new QPushButton(hStatusLayout);
        pBtnClose->setObjectName(QString::fromUtf8("pBtnClose"));
        pBtnClose->setMaximumSize(QSize(32, 32));
        pBtnClose->setFont(font);

        hLayTitle->addWidget(pBtnClose);

        pBtnAbout = new QPushButton(hStatusLayout);
        pBtnAbout->setObjectName(QString::fromUtf8("pBtnAbout"));
        pBtnAbout->setMaximumSize(QSize(32, 32));
        pBtnAbout->setFont(font);

        hLayTitle->addWidget(pBtnAbout);


        verticalLayout->addWidget(hStatusLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        HBMenuBar = new QHBoxLayout();
        HBMenuBar->setSpacing(6);
        HBMenuBar->setObjectName(QString::fromUtf8("HBMenuBar"));
        HBMenuBar->setContentsMargins(20, 10, -1, 0);
        verticalSpacer_2 = new QSpacerItem(13, 68, QSizePolicy::Minimum, QSizePolicy::Fixed);

        HBMenuBar->addItem(verticalSpacer_2);


        horizontalLayout_7->addLayout(HBMenuBar);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        btnLisState = new QPushButton(MainWidget);
        btnLisState->setObjectName(QString::fromUtf8("btnLisState"));
        btnLisState->setEnabled(true);
        btnLisState->setMinimumSize(QSize(0, 0));
        btnLisState->setIconSize(QSize(32, 32));

        horizontalLayout_7->addWidget(btnLisState);

        btnSystemLiquidStatus = new QPushButton(MainWidget);
        btnSystemLiquidStatus->setObjectName(QString::fromUtf8("btnSystemLiquidStatus"));
        btnSystemLiquidStatus->setEnabled(true);
        btnSystemLiquidStatus->setMinimumSize(QSize(0, 0));
        btnSystemLiquidStatus->setIconSize(QSize(32, 32));

        horizontalLayout_7->addWidget(btnSystemLiquidStatus);

        btnWasteBottle = new QPushButton(MainWidget);
        btnWasteBottle->setObjectName(QString::fromUtf8("btnWasteBottle"));
        btnWasteBottle->setEnabled(true);
        btnWasteBottle->setMinimumSize(QSize(0, 0));
        btnWasteBottle->setIconSize(QSize(32, 32));

        horizontalLayout_7->addWidget(btnWasteBottle);

        btnRunState = new QPushButton(MainWidget);
        btnRunState->setObjectName(QString::fromUtf8("btnRunState"));
        btnRunState->setEnabled(true);
        btnRunState->setMinimumSize(QSize(0, 0));
        btnRunState->setMaximumSize(QSize(16777215, 16777215));
        btnRunState->setIconSize(QSize(32, 32));

        horizontalLayout_7->addWidget(btnRunState);

        label_3 = new QLabel(MainWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_7->addWidget(label_3);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_7);

        line_4 = new QFrame(MainWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShadow(QFrame::Plain);
        line_4->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line_4);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));

        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 1);
        leftMenuWidget = new QWidget(MainWidget);
        leftMenuWidget->setObjectName(QString::fromUtf8("leftMenuWidget"));
        verticalLayout_3 = new QVBoxLayout(leftMenuWidget);
        verticalLayout_3->setSpacing(12);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(5, 10, 2, -1);
        btnSample = new QPushButton(leftMenuWidget);
        btnSample->setObjectName(QString::fromUtf8("btnSample"));
        btnSample->setIconSize(QSize(32, 32));

        verticalLayout_3->addWidget(btnSample);

        btnInit = new QPushButton(leftMenuWidget);
        btnInit->setObjectName(QString::fromUtf8("btnInit"));
        btnInit->setIconSize(QSize(32, 32));

        verticalLayout_3->addWidget(btnInit);

        btnStop = new QPushButton(leftMenuWidget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setIconSize(QSize(32, 32));

        verticalLayout_3->addWidget(btnStop);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_6->addWidget(leftMenuWidget);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, 3, 0, -1);
        stackedWidget = new QStackedWidget(MainWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_6 = new QVBoxLayout(page_2);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(page_2);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_6->addWidget(tabWidget);

        stackedWidget->addWidget(page_2);

        verticalLayout_4->addWidget(stackedWidget);

        verticalSpacer_3 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_3);


        horizontalLayout_6->addLayout(verticalLayout_4);


        verticalLayout->addLayout(horizontalLayout_6);

        statusbarWidget = new QWidget(MainWidget);
        statusbarWidget->setObjectName(QString::fromUtf8("statusbarWidget"));
        statusbarWidget->setMinimumSize(QSize(0, 35));
        gridLayout = new QGridLayout(statusbarWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, 0);
        pushButton_osk_open = new QPushButton(statusbarWidget);
        pushButton_osk_open->setObjectName(QString::fromUtf8("pushButton_osk_open"));
        pushButton_osk_open->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(pushButton_osk_open, 0, 9, 1, 1);

        lblUser = new QLabel(statusbarWidget);
        lblUser->setObjectName(QString::fromUtf8("lblUser"));
        lblUser->setFont(font);
        lblUser->setLineWidth(1);
        lblUser->setMidLineWidth(0);
        lblUser->setWordWrap(false);
        lblUser->setIndent(-1);

        gridLayout->addWidget(lblUser, 0, 12, 1, 1);

        btnCloseBeep1 = new QPushButton(statusbarWidget);
        btnCloseBeep1->setObjectName(QString::fromUtf8("btnCloseBeep1"));

        gridLayout->addWidget(btnCloseBeep1, 0, 7, 1, 1);

        lbVersion = new QLabel(statusbarWidget);
        lbVersion->setObjectName(QString::fromUtf8("lbVersion"));
        lbVersion->setFont(font);

        gridLayout->addWidget(lbVersion, 0, 5, 1, 1);

        label_2 = new QLabel(statusbarWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(40, 0));

        gridLayout->addWidget(label_2, 0, 13, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 0, 8, 1, 1);

        btnSystemLiquid = new QPushButton(statusbarWidget);
        btnSystemLiquid->setObjectName(QString::fromUtf8("btnSystemLiquid"));
        btnSystemLiquid->setEnabled(true);
        btnSystemLiquid->setMinimumSize(QSize(0, 0));
        btnSystemLiquid->setIconSize(QSize(32, 32));

        gridLayout->addWidget(btnSystemLiquid, 0, 1, 1, 1);

        lbTemperature = new QLabel(statusbarWidget);
        lbTemperature->setObjectName(QString::fromUtf8("lbTemperature"));
        lbTemperature->setFont(font);

        gridLayout->addWidget(lbTemperature, 0, 11, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_10, 0, 10, 1, 1);

        btnMonthMaintain = new QPushButton(statusbarWidget);
        btnMonthMaintain->setObjectName(QString::fromUtf8("btnMonthMaintain"));
        btnMonthMaintain->setMinimumSize(QSize(0, 0));
        btnMonthMaintain->setMaximumSize(QSize(16777215, 16777215));
        btnMonthMaintain->setIconSize(QSize(32, 32));

        gridLayout->addWidget(btnMonthMaintain, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(44, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 6, 1, 1);

        lblDateTime = new QLabel(statusbarWidget);
        lblDateTime->setObjectName(QString::fromUtf8("lblDateTime"));
        lblDateTime->setFont(font);

        gridLayout->addWidget(lblDateTime, 0, 14, 1, 1);


        verticalLayout->addWidget(statusbarWidget);

        verticalWidget_2 = new QWidget(MainWidget);
        verticalWidget_2->setObjectName(QString::fromUtf8("verticalWidget_2"));
        verticalWidget_2->setMinimumSize(QSize(0, 8));
        verticalWidget_2->setMaximumSize(QSize(16777215, 8));
        verticalWidget_2->setStyleSheet(QString::fromUtf8("background-color:#F0F0F0;"));
        verticalLayout_2 = new QVBoxLayout(verticalWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        verticalLayout->addWidget(verticalWidget_2);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalWidget_21 = new QWidget(MainWidget);
        horizontalWidget_21->setObjectName(QString::fromUtf8("horizontalWidget_21"));
        horizontalWidget_21->setMinimumSize(QSize(8, 0));
        horizontalWidget_21->setMaximumSize(QSize(8, 16777215));
        horizontalWidget_21->setStyleSheet(QString::fromUtf8("background-color:#F0F0F0;"));
        horizontalLayout_4 = new QHBoxLayout(horizontalWidget_21);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));

        horizontalLayout_2->addWidget(horizontalWidget_21);


        retranslateUi(MainWidget);

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "Axceed 260", nullptr));
        label_5->setText(QString());
        label->setText(QString());
        label_4->setText(QString());
        titleLabel->setText(QApplication::translate("MainWidget", "HumaBlot 72FA", nullptr));
        pBtnLogout->setText(QString());
        pBtnLogout->setProperty("pBtnStyle", QVariant(QApplication::translate("MainWidget", "statusBtnStyle", nullptr)));
        pBtnMini->setText(QString());
        pBtnMini->setProperty("pBtnStyle", QVariant(QApplication::translate("MainWidget", "statusBtnStyle", nullptr)));
        pBtnClose->setText(QString());
        pBtnClose->setProperty("pBtnStyle", QVariant(QApplication::translate("MainWidget", "statusBtnStyle", nullptr)));
        pBtnAbout->setText(QString());
        pBtnAbout->setProperty("pBtnStyle", QVariant(QApplication::translate("MainWidget", "statusBtnStyle", nullptr)));
#ifndef QT_NO_TOOLTIP
        btnLisState->setToolTip(QApplication::translate("MainWidget", "\347\263\273\347\273\237\346\272\266\346\266\262\350\266\263\345\244\237", nullptr));
#endif // QT_NO_TOOLTIP
        btnLisState->setText(QString());
        btnLisState->setProperty("btnStyle", QVariant(QApplication::translate("MainWidget", "LisStateConnectStyle", nullptr)));
#ifndef QT_NO_TOOLTIP
        btnSystemLiquidStatus->setToolTip(QApplication::translate("MainWidget", "\347\263\273\347\273\237\346\272\266\346\266\262\350\266\263\345\244\237", nullptr));
#endif // QT_NO_TOOLTIP
        btnSystemLiquidStatus->setText(QString());
        btnSystemLiquidStatus->setProperty("btnStyle", QVariant(QApplication::translate("MainWidget", "systemLiquidStatusFull", nullptr)));
#ifndef QT_NO_TOOLTIP
        btnWasteBottle->setToolTip(QApplication::translate("MainWidget", "\345\272\237\346\266\262\347\223\266\347\212\266\346\200\201", nullptr));
#endif // QT_NO_TOOLTIP
        btnWasteBottle->setText(QString());
        btnWasteBottle->setProperty("btnStyle", QVariant(QApplication::translate("MainWidget", "wasteBottleStyle", nullptr)));
        btnRunState->setText(QString());
        btnRunState->setProperty("btnStyle", QVariant(QApplication::translate("MainWidget", "stateConnectStyle", nullptr)));
        label_3->setText(QApplication::translate("MainWidget", "\350\277\220\350\241\214\347\212\266\346\200\201", nullptr));
#ifndef QT_NO_TOOLTIP
        btnSample->setToolTip(QApplication::translate("MainWidget", "\346\267\273\345\212\240\346\240\267\346\234\254\344\277\241\346\201\257", nullptr));
#endif // QT_NO_TOOLTIP
        btnSample->setText(QString());
        btnSample->setProperty("btnStyle", QVariant(QApplication::translate("MainWidget", "iconOnlyStyle", nullptr)));
#ifndef QT_NO_TOOLTIP
        btnInit->setToolTip(QApplication::translate("MainWidget", "\345\210\235\345\247\213\345\214\226", nullptr));
#endif // QT_NO_TOOLTIP
        btnInit->setText(QString());
        btnInit->setProperty("btnStyle", QVariant(QApplication::translate("MainWidget", "iconOnlyStyle", nullptr)));
#ifndef QT_NO_TOOLTIP
        btnStop->setToolTip(QApplication::translate("MainWidget", "\345\201\234\346\255\242", nullptr));
#endif // QT_NO_TOOLTIP
        btnStop->setText(QString());
        btnStop->setProperty("btnStyle", QVariant(QApplication::translate("MainWidget", "iconOnlyStyle", nullptr)));
        pushButton_osk_open->setText(QApplication::translate("MainWidget", "      \346\211\223\345\274\200\351\224\256\347\233\230", nullptr));
        pushButton_osk_open->setProperty("btnStyle", QVariant(QApplication::translate("MainWidget", "OpenKeyBoardStyle", nullptr)));
        lblUser->setText(QApplication::translate("MainWidget", "\347\224\250\346\210\267\357\274\232 Admin", nullptr));
        lblUser->setProperty("lblStyle", QVariant(QApplication::translate("MainWidget", "lblStatus", nullptr)));
        btnCloseBeep1->setText(QApplication::translate("MainWidget", "     \345\205\263\351\227\255\350\234\202\351\270\243\345\231\250", nullptr));
        btnCloseBeep1->setProperty("btnStyle", QVariant(QApplication::translate("MainWidget", "CloseBeepStyle", nullptr)));
        lbVersion->setText(QApplication::translate("MainWidget", "\350\275\257\344\273\266\347\211\210\346\234\254\357\274\232 V1.0.0.0 @2023-04-24 09:03", nullptr));
        lbVersion->setProperty("lblStyle", QVariant(QApplication::translate("MainWidget", "lblStatus", nullptr)));
        label_2->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnSystemLiquid->setToolTip(QApplication::translate("MainWidget", "\347\263\273\347\273\237\346\266\262\346\230\257\345\220\246\347\201\214\346\263\250", nullptr));
#endif // QT_NO_TOOLTIP
        btnSystemLiquid->setText(QString());
        btnSystemLiquid->setProperty("btnStyle", QVariant(QApplication::translate("MainWidget", "systemLiquidStyle", nullptr)));
        lbTemperature->setText(QApplication::translate("MainWidget", "\345\255\265\350\202\262\347\233\230\357\274\232__.__\342\204\203 ", nullptr));
        lbTemperature->setProperty("lblStyle", QVariant(QApplication::translate("MainWidget", "lblStatus", nullptr)));
#ifndef QT_NO_TOOLTIP
        btnMonthMaintain->setToolTip(QApplication::translate("MainWidget", "\346\234\210\347\273\264\346\212\244", nullptr));
#endif // QT_NO_TOOLTIP
        btnMonthMaintain->setText(QString());
        btnMonthMaintain->setProperty("btnStyle", QVariant(QApplication::translate("MainWidget", "iconOnlyStyle", nullptr)));
        lblDateTime->setText(QApplication::translate("MainWidget", "\346\227\245\346\234\237\346\227\266\351\227\264\357\274\2322017-01-13 14:55:56", nullptr));
        lblDateTime->setProperty("lblStyle", QVariant(QApplication::translate("MainWidget", "lblStatus", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
