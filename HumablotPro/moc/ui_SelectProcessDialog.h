/********************************************************************************
** Form generated from reading UI file 'SelectProcessDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTPROCESSDIALOG_H
#define UI_SELECTPROCESSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectProcessDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *vLayoutBtn;
    QLabel *lblHint;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label888;
    QLabel *label_2;
    QPushButton *pushButtonClose;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btnConfig;
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout_6;

    void setupUi(QDialog *SelectProcessDialog)
    {
        if (SelectProcessDialog->objectName().isEmpty())
            SelectProcessDialog->setObjectName(QString::fromUtf8("SelectProcessDialog"));
        SelectProcessDialog->resize(486, 704);
        SelectProcessDialog->setModal(false);
        verticalLayout_2 = new QVBoxLayout(SelectProcessDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(SelectProcessDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 120, 441, 461));
        vLayoutBtn = new QVBoxLayout(layoutWidget);
        vLayoutBtn->setSpacing(12);
        vLayoutBtn->setObjectName(QString::fromUtf8("vLayoutBtn"));
        vLayoutBtn->setContentsMargins(120, 40, 120, 20);
        lblHint = new QLabel(groupBox);
        lblHint->setObjectName(QString::fromUtf8("lblHint"));
        lblHint->setGeometry(QRect(110, 660, 151, 31));
        lblHint->setMinimumSize(QSize(0, 30));
        lblHint->setStyleSheet(QString::fromUtf8("color:red;"));
        lblHint->setAlignment(Qt::AlignCenter);
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(80, 650, 31, 50));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(10, 20, 10, 30);
        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 640, 108, 41));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_4->addItem(verticalSpacer);

        horizontalSpacer_2 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        label888 = new QLabel(groupBox);
        label888->setObjectName(QString::fromUtf8("label888"));
        label888->setGeometry(QRect(20, 80, 441, 31));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 50, 281, 41));
        label_2->setStyleSheet(QString::fromUtf8(""));
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonClose = new QPushButton(groupBox);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(430, 60, 26, 26));
        pushButtonClose->setMinimumSize(QSize(26, 26));
        pushButtonClose->setMaximumSize(QSize(26, 26));
        layoutWidget3 = new QWidget(groupBox);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(310, 670, 41, 21));
        verticalLayout_4 = new QVBoxLayout(layoutWidget3);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        btnConfig = new QPushButton(groupBox);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(180, 600, 100, 35));
        btnConfig->setMinimumSize(QSize(100, 35));
        btnConfig->setMaximumSize(QSize(100, 16777215));
        widgetTop = new QWidget(groupBox);
        widgetTop->setObjectName(QString::fromUtf8("widgetTop"));
        widgetTop->setGeometry(QRect(180, 660, 59, 30));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetTop->sizePolicy().hasHeightForWidth());
        widgetTop->setSizePolicy(sizePolicy);
        widgetTop->setMinimumSize(QSize(0, 30));
        widgetTop->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_6 = new QHBoxLayout(widgetTop);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(20, 0, 20, 0);

        verticalLayout->addWidget(groupBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(SelectProcessDialog);

        QMetaObject::connectSlotsByName(SelectProcessDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectProcessDialog)
    {
        SelectProcessDialog->setWindowTitle(QApplication::translate("SelectProcessDialog", "\350\206\234\345\274\217", nullptr));
        SelectProcessDialog->setProperty("dialogStyle", QVariant(QApplication::translate("SelectProcessDialog", "BGStyle", nullptr)));
        groupBox->setTitle(QString());
        lblHint->setText(QString());
        label888->setText(QApplication::translate("SelectProcessDialog", "________________________________________________________________________________________________________________________________________", nullptr));
        label888->setProperty("lblStyle", QVariant(QApplication::translate("SelectProcessDialog", "lblNormal", nullptr)));
        label_2->setText(QApplication::translate("SelectProcessDialog", "\350\257\267\351\200\211\346\213\251\350\246\201\346\211\247\350\241\214\347\232\204\346\227\266\345\272\217", nullptr));
        label_2->setProperty("lblStyle", QVariant(QApplication::translate("SelectProcessDialog", "lblNormal", nullptr)));
        pushButtonClose->setText(QString());
        btnConfig->setText(QApplication::translate("SelectProcessDialog", "\347\241\256  \345\256\232", nullptr));
        btnConfig->setProperty("btnStyle", QVariant(QApplication::translate("SelectProcessDialog", "normalBtnRed", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class SelectProcessDialog: public Ui_SelectProcessDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTPROCESSDIALOG_H
