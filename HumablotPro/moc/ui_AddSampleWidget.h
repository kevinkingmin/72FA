/********************************************************************************
** Form generated from reading UI file 'AddSampleWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSAMPLEWIDGET_H
#define UI_ADDSAMPLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddSampleWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *vwidget;
    QVBoxLayout *verticalLayout;
    QWidget *verticalWidget;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gdLSamplePos;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QTableView *tvSampleSet;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit;
    QPushButton *btnBCR;
    QLineEdit *lineEdit_3;
    QPushButton *btnBatchAdd;
    QLabel *label_2;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *AddSampleWidget)
    {
        if (AddSampleWidget->objectName().isEmpty())
            AddSampleWidget->setObjectName(QString::fromUtf8("AddSampleWidget"));
        AddSampleWidget->resize(1024, 400);
        verticalLayout_2 = new QVBoxLayout(AddSampleWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        vwidget = new QWidget(AddSampleWidget);
        vwidget->setObjectName(QString::fromUtf8("vwidget"));
        verticalLayout = new QVBoxLayout(vwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalWidget = new QWidget(vwidget);
        verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
        gridLayout_2 = new QGridLayout(verticalWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(18, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 10, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(18, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 7, 1, 1);

        widget = new QWidget(verticalWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gdLSamplePos = new QGridLayout();
        gdLSamplePos->setSpacing(1);
        gdLSamplePos->setObjectName(QString::fromUtf8("gdLSamplePos"));
        gdLSamplePos->setContentsMargins(2, 2, 2, 2);

        horizontalLayout->addLayout(gdLSamplePos);


        gridLayout_2->addWidget(widget, 0, 8, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(18, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 4, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(18, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 0, 5, 1, 1);

        tvSampleSet = new QTableView(verticalWidget);
        tvSampleSet->setObjectName(QString::fromUtf8("tvSampleSet"));

        gridLayout_2->addWidget(tvSampleSet, 1, 0, 1, 14);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(verticalWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        lineEdit_4 = new QLineEdit(verticalWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 1, 4, 1, 1);

        lineEdit = new QLineEdit(verticalWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lineEdit, 0, 1, 1, 4);

        btnBCR = new QPushButton(verticalWidget);
        btnBCR->setObjectName(QString::fromUtf8("btnBCR"));

        gridLayout->addWidget(btnBCR, 1, 6, 1, 1);

        lineEdit_3 = new QLineEdit(verticalWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 1, 1, 1, 1);

        btnBatchAdd = new QPushButton(verticalWidget);
        btnBatchAdd->setObjectName(QString::fromUtf8("btnBatchAdd"));

        gridLayout->addWidget(btnBatchAdd, 0, 6, 1, 1);

        label_2 = new QLabel(verticalWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_6 = new QLabel(verticalWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 2, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_13, 0, 5, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_14, 1, 5, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(17, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 11, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(17, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 0, 13, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(18, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 6, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(17, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_11, 0, 9, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_12, 0, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(72, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 3, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(17, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 0, 12, 1, 1);

        verticalSpacer = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);


        verticalLayout->addWidget(verticalWidget);


        verticalLayout_2->addWidget(vwidget);


        retranslateUi(AddSampleWidget);

        QMetaObject::connectSlotsByName(AddSampleWidget);
    } // setupUi

    void retranslateUi(QWidget *AddSampleWidget)
    {
        AddSampleWidget->setWindowTitle(QApplication::translate("AddSampleWidget", "Form", nullptr));
        vwidget->setProperty("widgetStyle", QVariant(QApplication::translate("AddSampleWidget", "BGStyle", nullptr)));
        verticalWidget->setProperty("widgetStyle", QVariant(QApplication::translate("AddSampleWidget", "BGStyle", nullptr)));
        label_5->setText(QApplication::translate("AddSampleWidget", "\346\211\253\347\240\201\344\275\215\347\275\256\357\274\232", nullptr));
        lineEdit->setText(QApplication::translate("AddSampleWidget", "solutionName", nullptr));
        lineEdit->setProperty("btnStyle", QVariant(QApplication::translate("AddSampleWidget", "lineEditUserName", nullptr)));
        btnBCR->setText(QApplication::translate("AddSampleWidget", "Scan", nullptr));
        btnBCR->setProperty("btnStyle", QVariant(QApplication::translate("AddSampleWidget", "normalBtnRed", nullptr)));
        btnBatchAdd->setText(QApplication::translate("AddSampleWidget", "\346\211\271\351\207\217\346\267\273\345\212\240", nullptr));
        btnBatchAdd->setProperty("btnStyle", QVariant(QApplication::translate("AddSampleWidget", "normalBtnRed", nullptr)));
        label_2->setText(QApplication::translate("AddSampleWidget", "\345\216\202\345\256\266\345\220\215\347\247\260\357\274\232", nullptr));
        label_6->setText(QApplication::translate("AddSampleWidget", "\342\200\224\342\200\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddSampleWidget: public Ui_AddSampleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSAMPLEWIDGET_H
