/********************************************************************************
** Form generated from reading UI file 'ShowImageDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWIMAGEDIALOG_H
#define UI_SHOWIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowImageDialogClass
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;

    void setupUi(QDialog *ShowImageDialogClass)
    {
        if (ShowImageDialogClass->objectName().isEmpty())
            ShowImageDialogClass->setObjectName(QString::fromUtf8("ShowImageDialogClass"));
        ShowImageDialogClass->resize(879, 133);
        pushButton = new QPushButton(ShowImageDialogClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(690, 97, 91, 31));
        pushButton_2 = new QPushButton(ShowImageDialogClass);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(780, 97, 91, 31));
        layoutWidget = new QWidget(ShowImageDialogClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 871, 81));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);


        retranslateUi(ShowImageDialogClass);

        QMetaObject::connectSlotsByName(ShowImageDialogClass);
    } // setupUi

    void retranslateUi(QDialog *ShowImageDialogClass)
    {
        ShowImageDialogClass->setWindowTitle(QApplication::translate("ShowImageDialogClass", "\346\213\215\347\205\247\346\265\213\350\257\225", nullptr));
        pushButton->setText(QApplication::translate("ShowImageDialogClass", "\346\213\215\347\205\247\346\210\220\345\212\237", nullptr));
        pushButton_2->setText(QApplication::translate("ShowImageDialogClass", "\346\213\215\347\205\247\345\244\261\350\264\245", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ShowImageDialogClass: public Ui_ShowImageDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWIMAGEDIALOG_H
