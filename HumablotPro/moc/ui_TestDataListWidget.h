/********************************************************************************
** Form generated from reading UI file 'TestDataListWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTDATALISTWIDGET_H
#define UI_TESTDATALISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestDataListWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QWidget *vwidget;
    QVBoxLayout *verticalLayout;
    QWidget *hWRunInfo1;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QHBoxLayout *hLayPaperPos;
    QWidget *hWRunInfo122;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QHBoxLayout *hLayPaperPos1;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *TestDataListWidget)
    {
        if (TestDataListWidget->objectName().isEmpty())
            TestDataListWidget->setObjectName(QString::fromUtf8("TestDataListWidget"));
        TestDataListWidget->resize(1032, 662);
        verticalLayout_2 = new QVBoxLayout(TestDataListWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        vwidget = new QWidget(TestDataListWidget);
        vwidget->setObjectName(QString::fromUtf8("vwidget"));
        vwidget->setMinimumSize(QSize(1000, 0));
        verticalLayout = new QVBoxLayout(vwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 65, -1, 155);
        hWRunInfo1 = new QWidget(vwidget);
        hWRunInfo1->setObjectName(QString::fromUtf8("hWRunInfo1"));
        horizontalLayout = new QHBoxLayout(hWRunInfo1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(hWRunInfo1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(65, 0));
        label->setMaximumSize(QSize(65, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(36);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        hLayPaperPos = new QHBoxLayout();
        hLayPaperPos->setSpacing(6);
        hLayPaperPos->setObjectName(QString::fromUtf8("hLayPaperPos"));
        hLayPaperPos->setContentsMargins(0, 8, 15, 15);

        horizontalLayout->addLayout(hLayPaperPos);


        verticalLayout->addWidget(hWRunInfo1);

        hWRunInfo122 = new QWidget(vwidget);
        hWRunInfo122->setObjectName(QString::fromUtf8("hWRunInfo122"));
        horizontalLayout_2 = new QHBoxLayout(hWRunInfo122);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(hWRunInfo122);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(65, 0));
        label_2->setMaximumSize(QSize(65, 16777215));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        hLayPaperPos1 = new QHBoxLayout();
        hLayPaperPos1->setSpacing(6);
        hLayPaperPos1->setObjectName(QString::fromUtf8("hLayPaperPos1"));
        hLayPaperPos1->setContentsMargins(0, 8, 15, 15);

        horizontalLayout_2->addLayout(hLayPaperPos1);


        verticalLayout->addWidget(hWRunInfo122);


        horizontalLayout_3->addWidget(vwidget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(TestDataListWidget);

        QMetaObject::connectSlotsByName(TestDataListWidget);
    } // setupUi

    void retranslateUi(QWidget *TestDataListWidget)
    {
        TestDataListWidget->setWindowTitle(QApplication::translate("TestDataListWidget", "Form", nullptr));
        vwidget->setProperty("widgetStyle", QVariant(QApplication::translate("TestDataListWidget", "BGStyle", nullptr)));
        label->setText(QApplication::translate("TestDataListWidget", "\342\221\240", nullptr));
        label_2->setText(QApplication::translate("TestDataListWidget", "\342\221\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestDataListWidget: public Ui_TestDataListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDATALISTWIDGET_H
