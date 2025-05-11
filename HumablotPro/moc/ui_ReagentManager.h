/********************************************************************************
** Form generated from reading UI file 'ReagentManager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REAGENTMANAGER_H
#define UI_REAGENTMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReagentManager
{
public:
    QLabel *label;
    QTableWidget *tableWidget_Company;
    QTableWidget *tableWidget_Reagent;
    QWidget *widget;
    QGridLayout *gridLayout;
    QPushButton *Delete_Button;
    QPushButton *Add_Button;
    QSpacerItem *horizontalSpacer;
    QPushButton *Modify_Button;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ReagentManager)
    {
        if (ReagentManager->objectName().isEmpty())
            ReagentManager->setObjectName(QString::fromUtf8("ReagentManager"));
        ReagentManager->resize(1327, 741);
        label = new QLabel(ReagentManager);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 20, 281, 41));
        tableWidget_Company = new QTableWidget(ReagentManager);
        if (tableWidget_Company->columnCount() < 1)
            tableWidget_Company->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_Company->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget_Company->setObjectName(QString::fromUtf8("tableWidget_Company"));
        tableWidget_Company->setGeometry(QRect(40, 70, 231, 541));
        tableWidget_Reagent = new QTableWidget(ReagentManager);
        if (tableWidget_Reagent->columnCount() < 8)
            tableWidget_Reagent->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_Reagent->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_Reagent->setHorizontalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_Reagent->setHorizontalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_Reagent->setHorizontalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_Reagent->setHorizontalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_Reagent->setHorizontalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_Reagent->setHorizontalHeaderItem(6, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_Reagent->setHorizontalHeaderItem(7, __qtablewidgetitem8);
        tableWidget_Reagent->setObjectName(QString::fromUtf8("tableWidget_Reagent"));
        tableWidget_Reagent->setGeometry(QRect(310, 70, 971, 541));
        widget = new QWidget(ReagentManager);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(890, 620, 391, 51));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Delete_Button = new QPushButton(widget);
        Delete_Button->setObjectName(QString::fromUtf8("Delete_Button"));

        gridLayout->addWidget(Delete_Button, 0, 4, 1, 1);

        Add_Button = new QPushButton(widget);
        Add_Button->setObjectName(QString::fromUtf8("Add_Button"));

        gridLayout->addWidget(Add_Button, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        Modify_Button = new QPushButton(widget);
        Modify_Button->setObjectName(QString::fromUtf8("Modify_Button"));

        gridLayout->addWidget(Modify_Button, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);


        retranslateUi(ReagentManager);

        QMetaObject::connectSlotsByName(ReagentManager);
    } // setupUi

    void retranslateUi(QWidget *ReagentManager)
    {
        ReagentManager->setWindowTitle(QApplication::translate("ReagentManager", "ReagentManager", nullptr));
        label->setText(QApplication::translate("ReagentManager", "\350\257\225\345\211\202\345\216\202\345\256\266\351\200\211\346\213\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_Company->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ReagentManager", "\345\205\254\345\217\270\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_Reagent->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("ReagentManager", "\350\257\225\345\211\202\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_Reagent->horizontalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("ReagentManager", "\350\206\234\346\235\241\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_Reagent->horizontalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("ReagentManager", "\351\230\262\346\214\202\346\273\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_Reagent->horizontalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("ReagentManager", "\350\257\225\345\211\202\345\233\236\346\265\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_Reagent->horizontalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("ReagentManager", "\350\277\220\350\241\214\345\211\215\347\201\214\346\263\250", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_Reagent->horizontalHeaderItem(5);
        ___qtablewidgetitem6->setText(QApplication::translate("ReagentManager", "\346\263\265\347\232\204\345\210\206\351\205\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_Reagent->horizontalHeaderItem(6);
        ___qtablewidgetitem7->setText(QApplication::translate("ReagentManager", "\345\244\247\345\205\205\347\201\214\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_Reagent->horizontalHeaderItem(7);
        ___qtablewidgetitem8->setText(QApplication::translate("ReagentManager", "\345\260\217\345\205\205\347\201\214\351\207\217", nullptr));
        Delete_Button->setText(QApplication::translate("ReagentManager", "\345\210\240\351\231\244", nullptr));
        Delete_Button->setProperty("btnStyle", QVariant(QApplication::translate("ReagentManager", "normalBtnpink", nullptr)));
        Add_Button->setText(QApplication::translate("ReagentManager", "\350\277\275\345\212\240", nullptr));
        Add_Button->setProperty("btnStyle", QVariant(QApplication::translate("ReagentManager", "normalBtnpink", nullptr)));
        Modify_Button->setText(QApplication::translate("ReagentManager", "\344\277\256\346\255\243", nullptr));
        Modify_Button->setProperty("btnStyle", QVariant(QApplication::translate("ReagentManager", "normalBtnpink", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class ReagentManager: public Ui_ReagentManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REAGENTMANAGER_H
