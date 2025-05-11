/********************************************************************************
** Form generated from reading UI file 'ProcessParaWidgets.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESSPARAWIDGETS_H
#define UI_PROCESSPARAWIDGETS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProcessParaWidgetsClass
{
public:
    QPushButton *pushButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *ProcessParaWidgetsClass)
    {
        if (ProcessParaWidgetsClass->objectName().isEmpty())
            ProcessParaWidgetsClass->setObjectName(QString::fromUtf8("ProcessParaWidgetsClass"));
        ProcessParaWidgetsClass->resize(1380, 652);
        pushButton = new QPushButton(ProcessParaWidgetsClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1230, 0, 131, 51));
        verticalLayoutWidget = new QWidget(ProcessParaWidgetsClass);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 440, 91, 31));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(ProcessParaWidgetsClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(130, 100, 181, 161));
        treeWidget = new QTreeWidget(ProcessParaWidgetsClass);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(340, 60, 961, 571));

        retranslateUi(ProcessParaWidgetsClass);

        QMetaObject::connectSlotsByName(ProcessParaWidgetsClass);
    } // setupUi

    void retranslateUi(QWidget *ProcessParaWidgetsClass)
    {
        ProcessParaWidgetsClass->setWindowTitle(QApplication::translate("ProcessParaWidgetsClass", "ProcessParaWidgets", nullptr));
        pushButton->setText(QApplication::translate("ProcessParaWidgetsClass", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProcessParaWidgetsClass: public Ui_ProcessParaWidgetsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESSPARAWIDGETS_H
