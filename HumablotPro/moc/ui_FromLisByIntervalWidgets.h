/********************************************************************************
** Form generated from reading UI file 'FromLisByIntervalWidgets.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FROMLISBYINTERVALWIDGETS_H
#define UI_FROMLISBYINTERVALWIDGETS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FromLisByIntervalWidgets
{
public:
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QGridLayout *gridLayout;
    QPushButton *pushButtonOK;
    QLineEdit *lineEdit_End;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEditStart;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *FromLisByIntervalWidgets)
    {
        if (FromLisByIntervalWidgets->objectName().isEmpty())
            FromLisByIntervalWidgets->setObjectName(QString::fromUtf8("FromLisByIntervalWidgets"));
        FromLisByIntervalWidgets->resize(635, 225);
        widget = new QWidget(FromLisByIntervalWidgets);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 60, 546, 72));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);

        gridLayout_2->addWidget(label_3, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonOK = new QPushButton(widget);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));

        gridLayout->addWidget(pushButtonOK, 0, 5, 1, 1);

        lineEdit_End = new QLineEdit(widget);
        lineEdit_End->setObjectName(QString::fromUtf8("lineEdit_End"));

        gridLayout->addWidget(lineEdit_End, 0, 3, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEditStart = new QLineEdit(widget);
        lineEditStart->setObjectName(QString::fromUtf8("lineEditStart"));

        gridLayout->addWidget(lineEditStart, 0, 1, 1, 1);

        pushButtonCancel = new QPushButton(widget);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        gridLayout->addWidget(pushButtonCancel, 0, 6, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 0, 1, 1);


        retranslateUi(FromLisByIntervalWidgets);

        QMetaObject::connectSlotsByName(FromLisByIntervalWidgets);
    } // setupUi

    void retranslateUi(QWidget *FromLisByIntervalWidgets)
    {
        FromLisByIntervalWidgets->setWindowTitle(QApplication::translate("FromLisByIntervalWidgets", "FromLisByIntervalWidgets", nullptr));
        label_3->setText(QApplication::translate("FromLisByIntervalWidgets", "\350\257\267\351\200\211\346\213\251\345\220\257\345\247\213\346\227\266\351\227\264", nullptr));
        pushButtonOK->setText(QApplication::translate("FromLisByIntervalWidgets", "\347\241\256\345\256\232", nullptr));
        label_2->setText(QApplication::translate("FromLisByIntervalWidgets", "\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        label->setText(QApplication::translate("FromLisByIntervalWidgets", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        pushButtonCancel->setText(QApplication::translate("FromLisByIntervalWidgets", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FromLisByIntervalWidgets: public Ui_FromLisByIntervalWidgets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FROMLISBYINTERVALWIDGETS_H
