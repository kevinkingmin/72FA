/********************************************************************************
** Form generated from reading UI file 'WelcomWidgets.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMWIDGETS_H
#define UI_WELCOMWIDGETS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomWidgetsClass
{
public:
    QGridLayout *gridLayout;
    QWidget *widgetWelcome;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *WelcomWidgetsClass)
    {
        if (WelcomWidgetsClass->objectName().isEmpty())
            WelcomWidgetsClass->setObjectName(QString::fromUtf8("WelcomWidgetsClass"));
        WelcomWidgetsClass->resize(1940, 885);
        gridLayout = new QGridLayout(WelcomWidgetsClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widgetWelcome = new QWidget(WelcomWidgetsClass);
        widgetWelcome->setObjectName(QString::fromUtf8("widgetWelcome"));
        widgetWelcome->setAutoFillBackground(false);
        widgetWelcome->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(widgetWelcome);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 340, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        label_2 = new QLabel(widgetWelcome);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        label = new QLabel(widgetWelcome);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalSpacer_2 = new QSpacerItem(20, 340, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);


        verticalLayout->addLayout(verticalLayout_2);


        gridLayout->addWidget(widgetWelcome, 0, 0, 1, 1);


        retranslateUi(WelcomWidgetsClass);

        QMetaObject::connectSlotsByName(WelcomWidgetsClass);
    } // setupUi

    void retranslateUi(QWidget *WelcomWidgetsClass)
    {
        WelcomWidgetsClass->setWindowTitle(QApplication::translate("WelcomWidgetsClass", "WelcomWidgets", nullptr));
        label_2->setText(QApplication::translate("WelcomWidgetsClass", "TextLabel", nullptr));
        label->setText(QApplication::translate("WelcomWidgetsClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WelcomWidgetsClass: public Ui_WelcomWidgetsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMWIDGETS_H
