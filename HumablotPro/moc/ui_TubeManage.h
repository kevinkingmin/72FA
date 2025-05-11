/********************************************************************************
** Form generated from reading UI file 'TubeManage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TUBEMANAGE_H
#define UI_TUBEMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TubeManage
{
public:
    QTableWidget *tableWidget;
    QPushButton *Add_Button;
    QPushButton *Modify_Button;
    QPushButton *Delete_Button;
    QPushButton *Inport_Button;
    QPushButton *Export_Button;

    void setupUi(QWidget *TubeManage)
    {
        if (TubeManage->objectName().isEmpty())
            TubeManage->setObjectName(QString::fromUtf8("TubeManage"));
        TubeManage->resize(1102, 675);
        tableWidget = new QTableWidget(TubeManage);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(50, 60, 1001, 501));
        Add_Button = new QPushButton(TubeManage);
        Add_Button->setObjectName(QString::fromUtf8("Add_Button"));
        Add_Button->setGeometry(QRect(680, 600, 75, 31));
        Modify_Button = new QPushButton(TubeManage);
        Modify_Button->setObjectName(QString::fromUtf8("Modify_Button"));
        Modify_Button->setGeometry(QRect(830, 600, 75, 31));
        Delete_Button = new QPushButton(TubeManage);
        Delete_Button->setObjectName(QString::fromUtf8("Delete_Button"));
        Delete_Button->setGeometry(QRect(970, 600, 75, 31));
        Inport_Button = new QPushButton(TubeManage);
        Inport_Button->setObjectName(QString::fromUtf8("Inport_Button"));
        Inport_Button->setGeometry(QRect(390, 600, 75, 31));
        Export_Button = new QPushButton(TubeManage);
        Export_Button->setObjectName(QString::fromUtf8("Export_Button"));
        Export_Button->setGeometry(QRect(530, 600, 75, 31));

        retranslateUi(TubeManage);

        QMetaObject::connectSlotsByName(TubeManage);
    } // setupUi

    void retranslateUi(QWidget *TubeManage)
    {
        TubeManage->setWindowTitle(QApplication::translate("TubeManage", "TubeManage", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TubeManage", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("TubeManage", "\346\230\257\345\220\246\350\264\250\346\216\247\347\256\241", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("TubeManage", "\350\257\225\347\256\241\345\206\205\345\276\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("TubeManage", "\350\257\225\347\256\241\351\253\230\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("TubeManage", "\346\266\262\344\275\215\351\253\230\345\272\246", nullptr));
        Add_Button->setText(QApplication::translate("TubeManage", "\350\277\275\345\212\240", nullptr));
        Modify_Button->setText(QApplication::translate("TubeManage", "\344\277\256\346\255\243", nullptr));
        Delete_Button->setText(QApplication::translate("TubeManage", "\345\210\240\351\231\244", nullptr));
        Inport_Button->setText(QApplication::translate("TubeManage", "\345\257\274\345\205\245", nullptr));
        Export_Button->setText(QApplication::translate("TubeManage", "\345\257\274\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TubeManage: public Ui_TubeManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TUBEMANAGE_H
