/********************************************************************************
** Form generated from reading UI file 'ManualIncubationWidgets.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALINCUBATIONWIDGETS_H
#define UI_MANUALINCUBATIONWIDGETS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManualIncubationWidgetsClass
{
public:
    QGroupBox *groupBox_3;
    QPushButton *btnIncubationFinish;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *Incubation_time;
    QPushButton *btnStartIncubation;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_4;
    QProgressBar *progressBar;
    QLabel *label_3;
    QLabel *label_6;

    void setupUi(QDialog *ManualIncubationWidgetsClass)
    {
        if (ManualIncubationWidgetsClass->objectName().isEmpty())
            ManualIncubationWidgetsClass->setObjectName(QString::fromUtf8("ManualIncubationWidgetsClass"));
        ManualIncubationWidgetsClass->resize(865, 563);
        groupBox_3 = new QGroupBox(ManualIncubationWidgetsClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(120, 120, 641, 331));
        btnIncubationFinish = new QPushButton(groupBox_3);
        btnIncubationFinish->setObjectName(QString::fromUtf8("btnIncubationFinish"));
        btnIncubationFinish->setGeometry(QRect(270, 260, 121, 41));
        layoutWidget = new QWidget(groupBox_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(80, 120, 491, 71));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Incubation_time = new QLineEdit(layoutWidget);
        Incubation_time->setObjectName(QString::fromUtf8("Incubation_time"));

        gridLayout->addWidget(Incubation_time, 0, 2, 1, 1);

        btnStartIncubation = new QPushButton(layoutWidget);
        btnStartIncubation->setObjectName(QString::fromUtf8("btnStartIncubation"));

        gridLayout->addWidget(btnStartIncubation, 0, 4, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 5, 1, 1);

        progressBar = new QProgressBar(groupBox_3);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(20, 220, 589, 10));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(253, 40, 131, 31));
        label_3->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 70, 641, 20));

        retranslateUi(ManualIncubationWidgetsClass);

        QMetaObject::connectSlotsByName(ManualIncubationWidgetsClass);
    } // setupUi

    void retranslateUi(QDialog *ManualIncubationWidgetsClass)
    {
        ManualIncubationWidgetsClass->setWindowTitle(QApplication::translate("ManualIncubationWidgetsClass", "ManualIncubationWidgets", nullptr));
        groupBox_3->setTitle(QString());
        btnIncubationFinish->setText(QApplication::translate("ManualIncubationWidgetsClass", "\345\201\234\346\255\242\345\271\266\345\205\263\351\227\255", nullptr));
        btnIncubationFinish->setProperty("btnStyle", QVariant(QApplication::translate("ManualIncubationWidgetsClass", "normalBtnGray", nullptr)));
        Incubation_time->setText(QApplication::translate("ManualIncubationWidgetsClass", "100", nullptr));
        btnStartIncubation->setText(QApplication::translate("ManualIncubationWidgetsClass", "\345\274\200\345\247\213\345\255\265\350\202\262", nullptr));
        btnStartIncubation->setProperty("btnStyle", QVariant(QApplication::translate("ManualIncubationWidgetsClass", "normalBtnRed", nullptr)));
        label->setText(QApplication::translate("ManualIncubationWidgetsClass", "\345\255\265\350\202\262\346\227\266\351\227\264\357\274\232", nullptr));
        label_2->setText(QApplication::translate("ManualIncubationWidgetsClass", "5-240\345\210\206\351\222\237", nullptr));
        label_3->setText(QApplication::translate("ManualIncubationWidgetsClass", "\346\211\213\345\212\250\345\255\265\350\202\262", nullptr));
        label_6->setText(QApplication::translate("ManualIncubationWidgetsClass", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200"
                        "\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManualIncubationWidgetsClass: public Ui_ManualIncubationWidgetsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALINCUBATIONWIDGETS_H
