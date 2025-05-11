/********************************************************************************
** Form generated from reading UI file 'ShowAllPicWidgets.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWALLPICWIDGETS_H
#define UI_SHOWALLPICWIDGETS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowAllPicWidgetsClass
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;

    void setupUi(QWidget *ShowAllPicWidgetsClass)
    {
        if (ShowAllPicWidgetsClass->objectName().isEmpty())
            ShowAllPicWidgetsClass->setObjectName(QString::fromUtf8("ShowAllPicWidgetsClass"));
        ShowAllPicWidgetsClass->resize(1157, 176);
        layoutWidget = new QWidget(ShowAllPicWidgetsClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 1141, 151));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);


        retranslateUi(ShowAllPicWidgetsClass);

        QMetaObject::connectSlotsByName(ShowAllPicWidgetsClass);
    } // setupUi

    void retranslateUi(QWidget *ShowAllPicWidgetsClass)
    {
        ShowAllPicWidgetsClass->setWindowTitle(QApplication::translate("ShowAllPicWidgetsClass", "ShowAllPicWidgets", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ShowAllPicWidgetsClass: public Ui_ShowAllPicWidgetsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWALLPICWIDGETS_H
