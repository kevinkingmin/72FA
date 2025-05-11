/********************************************************************************
** Form generated from reading UI file 'PumpCalibrateWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUMPCALIBRATEWIDGET_H
#define UI_PUMPCALIBRATEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PumpCalibrateWidget
{
public:
    QLabel *label;
    QTextBrowser *textBrowser;
    QPushButton *btnStart;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *chk_1;
    QCheckBox *chk_2;
    QCheckBox *chk_3;
    QCheckBox *chk_4;
    QCheckBox *chk_5;
    QCheckBox *chk_6;
    QCheckBox *chk_7;
    QCheckBox *chk_8;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *PumpCalibrateWidget)
    {
        if (PumpCalibrateWidget->objectName().isEmpty())
            PumpCalibrateWidget->setObjectName(QString::fromUtf8("PumpCalibrateWidget"));
        PumpCalibrateWidget->resize(1205, 739);
        label = new QLabel(PumpCalibrateWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 300, 54, 16));
        textBrowser = new QTextBrowser(PumpCalibrateWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(200, 340, 681, 192));
        btnStart = new QPushButton(PumpCalibrateWidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(190, 630, 75, 40));
        btnStart->setMinimumSize(QSize(0, 40));
        widget = new QWidget(PumpCalibrateWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(200, 160, 688, 112));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 40, -1, 50);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        chk_1 = new QCheckBox(widget);
        chk_1->setObjectName(QString::fromUtf8("chk_1"));
        chk_1->setChecked(false);

        horizontalLayout->addWidget(chk_1);

        chk_2 = new QCheckBox(widget);
        chk_2->setObjectName(QString::fromUtf8("chk_2"));
        chk_2->setChecked(false);

        horizontalLayout->addWidget(chk_2);

        chk_3 = new QCheckBox(widget);
        chk_3->setObjectName(QString::fromUtf8("chk_3"));

        horizontalLayout->addWidget(chk_3);

        chk_4 = new QCheckBox(widget);
        chk_4->setObjectName(QString::fromUtf8("chk_4"));

        horizontalLayout->addWidget(chk_4);

        chk_5 = new QCheckBox(widget);
        chk_5->setObjectName(QString::fromUtf8("chk_5"));

        horizontalLayout->addWidget(chk_5);

        chk_6 = new QCheckBox(widget);
        chk_6->setObjectName(QString::fromUtf8("chk_6"));

        horizontalLayout->addWidget(chk_6);

        chk_7 = new QCheckBox(widget);
        chk_7->setObjectName(QString::fromUtf8("chk_7"));

        horizontalLayout->addWidget(chk_7);

        chk_8 = new QCheckBox(widget);
        chk_8->setObjectName(QString::fromUtf8("chk_8"));

        horizontalLayout->addWidget(chk_8);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(PumpCalibrateWidget);

        QMetaObject::connectSlotsByName(PumpCalibrateWidget);
    } // setupUi

    void retranslateUi(QWidget *PumpCalibrateWidget)
    {
        PumpCalibrateWidget->setWindowTitle(QApplication::translate("PumpCalibrateWidget", "Form", nullptr));
        label->setText(QApplication::translate("PumpCalibrateWidget", "\346\240\241\345\207\206\347\273\223\346\236\234:", nullptr));
        btnStart->setText(QApplication::translate("PumpCalibrateWidget", "\345\274\200\345\247\213\346\240\241\345\207\206", nullptr));
        btnStart->setProperty("btnStyle", QVariant(QApplication::translate("PumpCalibrateWidget", "normalBtn", nullptr)));
        chk_1->setText(QApplication::translate("PumpCalibrateWidget", "1\345\217\267\346\263\265", nullptr));
        chk_2->setText(QApplication::translate("PumpCalibrateWidget", "2\345\217\267\346\263\265", nullptr));
        chk_3->setText(QApplication::translate("PumpCalibrateWidget", "3\345\217\267\346\263\265", nullptr));
        chk_4->setText(QApplication::translate("PumpCalibrateWidget", "4\345\217\267\346\263\265", nullptr));
        chk_5->setText(QApplication::translate("PumpCalibrateWidget", "5\345\217\267\346\263\265", nullptr));
        chk_6->setText(QApplication::translate("PumpCalibrateWidget", "6\345\217\267\346\263\265", nullptr));
        chk_7->setText(QApplication::translate("PumpCalibrateWidget", "7\345\217\267\346\263\265", nullptr));
        chk_8->setText(QApplication::translate("PumpCalibrateWidget", "8\345\217\267\346\263\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PumpCalibrateWidget: public Ui_PumpCalibrateWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUMPCALIBRATEWIDGET_H
