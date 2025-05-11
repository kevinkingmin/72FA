/********************************************************************************
** Form generated from reading UI file 'TestResultDataOneType.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTRESULTDATAONETYPE_H
#define UI_TESTRESULTDATAONETYPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestResultDataOneType
{
public:
    QTableWidget *tableWidget_H;
    QTableWidget *tableWidget_Data;

    void setupUi(QWidget *TestResultDataOneType)
    {
        if (TestResultDataOneType->objectName().isEmpty())
            TestResultDataOneType->setObjectName(QString::fromUtf8("TestResultDataOneType"));
        tableWidget_H = new QTableWidget(TestResultDataOneType);
        if (tableWidget_H->columnCount() < 6)
            tableWidget_H->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_H->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_H->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_H->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_H->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_H->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_H->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget_H->setObjectName(QString::fromUtf8("tableWidget_H"));
        tableWidget_H->setGeometry(QRect(20, 20, 1791, 141));
        tableWidget_Data = new QTableWidget(TestResultDataOneType);
        if (tableWidget_Data->columnCount() < 6)
            tableWidget_Data->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_Data->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_Data->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_Data->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_Data->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_Data->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_Data->setHorizontalHeaderItem(5, __qtablewidgetitem11);
        tableWidget_Data->setObjectName(QString::fromUtf8("tableWidget_Data"));
        tableWidget_Data->setGeometry(QRect(20, 160, 1791, 651));

        retranslateUi(TestResultDataOneType);

        QMetaObject::connectSlotsByName(TestResultDataOneType);
    } // setupUi

    void retranslateUi(QWidget *TestResultDataOneType)
    {
        TestResultDataOneType->setWindowTitle(QApplication::translate("TestResultDataOneType", "TestResultDataOneType", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestResultDataOneType: public Ui_TestResultDataOneType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTRESULTDATAONETYPE_H
