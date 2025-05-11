/********************************************************************************
** Form generated from reading UI file 'TestResultDataManage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTRESULTDATAMANAGE_H
#define UI_TESTRESULTDATAMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestResultDataManage
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;

    void setupUi(QWidget *TestResultDataManage)
    {
        if (TestResultDataManage->objectName().isEmpty())
            TestResultDataManage->setObjectName(QString::fromUtf8("TestResultDataManage"));
        TestResultDataManage->resize(1890, 833);
        tabWidget = new QTabWidget(TestResultDataManage);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 20, 1851, 801));
        tabWidget->setTabPosition(QTabWidget::North);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(TestResultDataManage);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TestResultDataManage);
    } // setupUi

    void retranslateUi(QWidget *TestResultDataManage)
    {
        TestResultDataManage->setWindowTitle(QApplication::translate("TestResultDataManage", "TestResultDataManage", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("TestResultDataManage", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("TestResultDataManage", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestResultDataManage: public Ui_TestResultDataManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTRESULTDATAMANAGE_H
