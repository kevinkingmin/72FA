/********************************************************************************
** Form generated from reading UI file 'MaintainCmdWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINTAINCMDWIDGET_H
#define UI_MAINTAINCMDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MaintainCmdWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout;
    QWidget *horizontalWidget;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnRunInit;
    QPushButton *btnCloseInit;
    QPushButton *btnSysteReset;
    QPushButton *btnStartWash;
    QPushButton *btnWeekWash;
    QPushButton *btnEmpty;
    QPushButton *btnFlush;
    QPushButton *btnCloseWash;
    QPushButton *btnClose;
    QPushButton *btnDormant;
    QPushButton *btnRouse;
    QPushButton *btnPoolFlush;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QProgressBar *progressBar;

    void setupUi(QWidget *MaintainCmdWidget)
    {
        if (MaintainCmdWidget->objectName().isEmpty())
            MaintainCmdWidget->setObjectName(QString::fromUtf8("MaintainCmdWidget"));
        MaintainCmdWidget->resize(704, 678);
        verticalLayout_2 = new QVBoxLayout(MaintainCmdWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalWidget = new QWidget(MaintainCmdWidget);
        verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
        verticalLayout = new QVBoxLayout(verticalWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(15, 15, 15, 15);
        horizontalWidget = new QWidget(verticalWidget);
        horizontalWidget->setObjectName(QString::fromUtf8("horizontalWidget"));
        verticalLayout_5 = new QVBoxLayout(horizontalWidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(150, 10, -1, -1);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        btnRunInit = new QPushButton(horizontalWidget);
        btnRunInit->setObjectName(QString::fromUtf8("btnRunInit"));
        btnRunInit->setMinimumSize(QSize(200, 40));
        btnRunInit->setCheckable(true);
        btnRunInit->setAutoExclusive(true);

        verticalLayout_3->addWidget(btnRunInit);

        btnCloseInit = new QPushButton(horizontalWidget);
        btnCloseInit->setObjectName(QString::fromUtf8("btnCloseInit"));
        btnCloseInit->setMinimumSize(QSize(200, 40));
        btnCloseInit->setCheckable(true);
        btnCloseInit->setAutoExclusive(true);

        verticalLayout_3->addWidget(btnCloseInit);

        btnSysteReset = new QPushButton(horizontalWidget);
        btnSysteReset->setObjectName(QString::fromUtf8("btnSysteReset"));
        btnSysteReset->setMinimumSize(QSize(200, 40));
        btnSysteReset->setCheckable(true);
        btnSysteReset->setAutoExclusive(true);

        verticalLayout_3->addWidget(btnSysteReset);

        btnStartWash = new QPushButton(horizontalWidget);
        btnStartWash->setObjectName(QString::fromUtf8("btnStartWash"));
        btnStartWash->setMinimumSize(QSize(200, 40));
        btnStartWash->setCheckable(true);
        btnStartWash->setAutoExclusive(true);

        verticalLayout_3->addWidget(btnStartWash);

        btnWeekWash = new QPushButton(horizontalWidget);
        btnWeekWash->setObjectName(QString::fromUtf8("btnWeekWash"));
        btnWeekWash->setMinimumSize(QSize(200, 40));
        btnWeekWash->setCheckable(true);
        btnWeekWash->setAutoExclusive(true);

        verticalLayout_3->addWidget(btnWeekWash);

        btnEmpty = new QPushButton(horizontalWidget);
        btnEmpty->setObjectName(QString::fromUtf8("btnEmpty"));
        btnEmpty->setMinimumSize(QSize(200, 40));
        btnEmpty->setCheckable(true);
        btnEmpty->setAutoExclusive(true);

        verticalLayout_3->addWidget(btnEmpty);

        btnFlush = new QPushButton(horizontalWidget);
        btnFlush->setObjectName(QString::fromUtf8("btnFlush"));
        btnFlush->setMinimumSize(QSize(200, 40));
        btnFlush->setCheckable(true);
        btnFlush->setAutoExclusive(true);

        verticalLayout_3->addWidget(btnFlush);

        btnCloseWash = new QPushButton(horizontalWidget);
        btnCloseWash->setObjectName(QString::fromUtf8("btnCloseWash"));
        btnCloseWash->setMinimumSize(QSize(200, 40));
        btnCloseWash->setCheckable(true);
        btnCloseWash->setAutoExclusive(true);

        verticalLayout_3->addWidget(btnCloseWash);

        btnClose = new QPushButton(horizontalWidget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setMinimumSize(QSize(200, 40));
        btnClose->setCheckable(true);
        btnClose->setAutoExclusive(true);

        verticalLayout_3->addWidget(btnClose);

        btnDormant = new QPushButton(horizontalWidget);
        btnDormant->setObjectName(QString::fromUtf8("btnDormant"));
        btnDormant->setMinimumSize(QSize(200, 40));
        btnDormant->setCheckable(true);
        btnDormant->setAutoExclusive(true);

        verticalLayout_3->addWidget(btnDormant);

        btnRouse = new QPushButton(horizontalWidget);
        btnRouse->setObjectName(QString::fromUtf8("btnRouse"));
        btnRouse->setMinimumSize(QSize(200, 40));
        btnRouse->setCheckable(true);
        btnRouse->setAutoExclusive(true);

        verticalLayout_3->addWidget(btnRouse);

        btnPoolFlush = new QPushButton(horizontalWidget);
        btnPoolFlush->setObjectName(QString::fromUtf8("btnPoolFlush"));
        btnPoolFlush->setMinimumSize(QSize(200, 40));
        btnPoolFlush->setCheckable(true);
        btnPoolFlush->setAutoExclusive(true);

        verticalLayout_3->addWidget(btnPoolFlush);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_5->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(140, 10, 20, 20);
        progressBar = new QProgressBar(horizontalWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(0, 10));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        progressBar->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(progressBar);


        verticalLayout_5->addLayout(verticalLayout_4);


        verticalLayout->addWidget(horizontalWidget);


        verticalLayout_2->addWidget(verticalWidget);


        retranslateUi(MaintainCmdWidget);

        QMetaObject::connectSlotsByName(MaintainCmdWidget);
    } // setupUi

    void retranslateUi(QWidget *MaintainCmdWidget)
    {
        MaintainCmdWidget->setWindowTitle(QApplication::translate("MaintainCmdWidget", "Form", nullptr));
        verticalWidget->setProperty("widgetStyle", QVariant(QApplication::translate("MaintainCmdWidget", "BGStyle", nullptr)));
        horizontalWidget->setProperty("widgetStyle", QVariant(QApplication::translate("MaintainCmdWidget", "BGStyle", nullptr)));
        btnRunInit->setText(QApplication::translate("MaintainCmdWidget", "\344\270\200\351\224\256\345\274\200\346\234\272", nullptr));
        btnRunInit->setProperty("btnStyle", QVariant(QApplication::translate("MaintainCmdWidget", "normalBtn", nullptr)));
        btnCloseInit->setText(QApplication::translate("MaintainCmdWidget", "\344\270\200\351\224\256\345\205\263\346\234\272", nullptr));
        btnCloseInit->setProperty("btnStyle", QVariant(QApplication::translate("MaintainCmdWidget", "normalBtn", nullptr)));
        btnSysteReset->setText(QApplication::translate("MaintainCmdWidget", "\347\263\273\347\273\237\345\244\215\344\275\215", nullptr));
        btnSysteReset->setProperty("btnStyle", QVariant(QApplication::translate("MaintainCmdWidget", "normalBtn", nullptr)));
        btnStartWash->setText(QApplication::translate("MaintainCmdWidget", "\345\274\200\346\234\272\346\270\205\346\264\227", nullptr));
        btnStartWash->setProperty("btnStyle", QVariant(QApplication::translate("MaintainCmdWidget", "normalBtn", nullptr)));
        btnWeekWash->setText(QApplication::translate("MaintainCmdWidget", "\345\221\250\347\273\264\346\212\244\357\274\210\345\274\272\345\212\233\346\270\205\346\264\227\357\274\211", nullptr));
        btnWeekWash->setProperty("btnStyle", QVariant(QApplication::translate("MaintainCmdWidget", "normalBtn", nullptr)));
        btnEmpty->setText(QApplication::translate("MaintainCmdWidget", "\344\270\200\351\224\256\346\216\222\347\251\272", nullptr));
        btnEmpty->setProperty("btnStyle", QVariant(QApplication::translate("MaintainCmdWidget", "normalBtn", nullptr)));
        btnFlush->setText(QApplication::translate("MaintainCmdWidget", "\344\270\200\351\224\256\345\205\205\347\201\214", nullptr));
        btnFlush->setProperty("btnStyle", QVariant(QApplication::translate("MaintainCmdWidget", "normalBtn", nullptr)));
        btnCloseWash->setText(QApplication::translate("MaintainCmdWidget", "\345\205\263\346\234\272\346\270\205\346\264\227", nullptr));
        btnCloseWash->setProperty("btnStyle", QVariant(QApplication::translate("MaintainCmdWidget", "normalBtn", nullptr)));
        btnClose->setText(QApplication::translate("MaintainCmdWidget", "\345\205\263\346\234\272", nullptr));
        btnClose->setProperty("btnStyle", QVariant(QApplication::translate("MaintainCmdWidget", "normalBtn", nullptr)));
        btnDormant->setText(QApplication::translate("MaintainCmdWidget", "\344\274\221\347\234\240", nullptr));
        btnDormant->setProperty("btnStyle", QVariant(QApplication::translate("MaintainCmdWidget", "normalBtn", nullptr)));
        btnRouse->setText(QApplication::translate("MaintainCmdWidget", "\345\224\244\351\206\222", nullptr));
        btnRouse->setProperty("btnStyle", QVariant(QApplication::translate("MaintainCmdWidget", "normalBtn", nullptr)));
        btnPoolFlush->setText(QApplication::translate("MaintainCmdWidget", "\347\274\223\345\206\262\346\261\240\345\205\205\347\201\214", nullptr));
        btnPoolFlush->setProperty("btnStyle", QVariant(QApplication::translate("MaintainCmdWidget", "normalBtn", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class MaintainCmdWidget: public Ui_MaintainCmdWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINTAINCMDWIDGET_H
