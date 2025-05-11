/********************************************************************************
** Form generated from reading UI file 'TestPaperManage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTPAPERMANAGE_H
#define UI_TESTPAPERMANAGE_H

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

class Ui_TestPaperManage
{
public:
    QLabel *label;
    QTableWidget *tableWidget_Company;
    QTableWidget *tableWidget_TestPaper;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *Add_Button;
    QPushButton *Modify_Button;
    QPushButton *Delete_Button;
    QSpacerItem *horizontalSpacer;
    QPushButton *Inport_Button;
    QPushButton *Delete_Button_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *Export_Button;
    QSpacerItem *horizontalSpacer_7;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QPushButton *Down_Sort_Button_3;
    QPushButton *Up_Sort_Button_2;
    QPushButton *Add_Company_Button;
    QPushButton *Delete_Company_Button;

    void setupUi(QWidget *TestPaperManage)
    {
        if (TestPaperManage->objectName().isEmpty())
            TestPaperManage->setObjectName(QString::fromUtf8("TestPaperManage"));
        TestPaperManage->resize(1523, 722);
        label = new QLabel(TestPaperManage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 20, 281, 31));
        tableWidget_Company = new QTableWidget(TestPaperManage);
        if (tableWidget_Company->columnCount() < 1)
            tableWidget_Company->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_Company->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget_Company->setObjectName(QString::fromUtf8("tableWidget_Company"));
        tableWidget_Company->setGeometry(QRect(70, 60, 256, 541));
        tableWidget_TestPaper = new QTableWidget(TestPaperManage);
        if (tableWidget_TestPaper->columnCount() < 5)
            tableWidget_TestPaper->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_TestPaper->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_TestPaper->setHorizontalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_TestPaper->setHorizontalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_TestPaper->setHorizontalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_TestPaper->setHorizontalHeaderItem(4, __qtablewidgetitem5);
        tableWidget_TestPaper->setObjectName(QString::fromUtf8("tableWidget_TestPaper"));
        tableWidget_TestPaper->setGeometry(QRect(360, 60, 1141, 541));
        layoutWidget = new QWidget(TestPaperManage);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(480, 620, 821, 51));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        Add_Button = new QPushButton(layoutWidget);
        Add_Button->setObjectName(QString::fromUtf8("Add_Button"));

        gridLayout->addWidget(Add_Button, 0, 4, 1, 1);

        Modify_Button = new QPushButton(layoutWidget);
        Modify_Button->setObjectName(QString::fromUtf8("Modify_Button"));

        gridLayout->addWidget(Modify_Button, 0, 6, 1, 1);

        Delete_Button = new QPushButton(layoutWidget);
        Delete_Button->setObjectName(QString::fromUtf8("Delete_Button"));

        gridLayout->addWidget(Delete_Button, 0, 8, 1, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        Inport_Button = new QPushButton(layoutWidget);
        Inport_Button->setObjectName(QString::fromUtf8("Inport_Button"));

        gridLayout->addWidget(Inport_Button, 0, 0, 1, 1);

        Delete_Button_2 = new QPushButton(layoutWidget);
        Delete_Button_2->setObjectName(QString::fromUtf8("Delete_Button_2"));

        gridLayout->addWidget(Delete_Button_2, 0, 10, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 5, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 7, 1, 1);

        Export_Button = new QPushButton(layoutWidget);
        Export_Button->setObjectName(QString::fromUtf8("Export_Button"));

        gridLayout->addWidget(Export_Button, 0, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 0, 9, 1, 1);

        layoutWidget1 = new QWidget(TestPaperManage);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(1270, 670, 21, 21));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        Down_Sort_Button_3 = new QPushButton(TestPaperManage);
        Down_Sort_Button_3->setObjectName(QString::fromUtf8("Down_Sort_Button_3"));
        Down_Sort_Button_3->setGeometry(QRect(430, 630, 31, 31));
        Up_Sort_Button_2 = new QPushButton(TestPaperManage);
        Up_Sort_Button_2->setObjectName(QString::fromUtf8("Up_Sort_Button_2"));
        Up_Sort_Button_2->setGeometry(QRect(370, 630, 31, 31));
        Add_Company_Button = new QPushButton(TestPaperManage);
        Add_Company_Button->setObjectName(QString::fromUtf8("Add_Company_Button"));
        Add_Company_Button->setGeometry(QRect(230, 625, 40, 40));
        Delete_Company_Button = new QPushButton(TestPaperManage);
        Delete_Company_Button->setObjectName(QString::fromUtf8("Delete_Company_Button"));
        Delete_Company_Button->setGeometry(QRect(290, 630, 31, 31));

        retranslateUi(TestPaperManage);

        QMetaObject::connectSlotsByName(TestPaperManage);
    } // setupUi

    void retranslateUi(QWidget *TestPaperManage)
    {
        TestPaperManage->setWindowTitle(QApplication::translate("TestPaperManage", "TestPaperManage", nullptr));
        label->setText(QApplication::translate("TestPaperManage", "\350\206\234\346\235\241\345\216\202\345\256\266\351\200\211\346\213\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_Company->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TestPaperManage", "\345\205\254\345\217\270\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_TestPaper->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("TestPaperManage", "No", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_TestPaper->horizontalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("TestPaperManage", "\350\206\234\346\235\241\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_TestPaper->horizontalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("TestPaperManage", "\350\264\247\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_TestPaper->horizontalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("TestPaperManage", "\346\216\222\345\272\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_TestPaper->horizontalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("TestPaperManage", "\346\230\257\345\220\246\345\220\257\347\224\250", nullptr));
        Add_Button->setText(QApplication::translate("TestPaperManage", "\350\277\275\345\212\240", nullptr));
        Add_Button->setProperty("btnStyle", QVariant(QApplication::translate("TestPaperManage", "normalBtnpink", nullptr)));
        Modify_Button->setText(QApplication::translate("TestPaperManage", "\344\277\256\346\224\271", nullptr));
        Modify_Button->setProperty("btnStyle", QVariant(QApplication::translate("TestPaperManage", "normalBtnpink", nullptr)));
        Delete_Button->setText(QApplication::translate("TestPaperManage", "\344\270\215\345\220\257\347\224\250", nullptr));
        Delete_Button->setProperty("btnStyle", QVariant(QApplication::translate("TestPaperManage", "normalBtnpink", nullptr)));
        Inport_Button->setText(QApplication::translate("TestPaperManage", "\345\257\274\345\205\245", nullptr));
        Inport_Button->setProperty("btnStyle", QVariant(QApplication::translate("TestPaperManage", "normalBtnpink", nullptr)));
        Delete_Button_2->setText(QApplication::translate("TestPaperManage", "\345\220\257\347\224\250", nullptr));
        Delete_Button_2->setProperty("btnStyle", QVariant(QApplication::translate("TestPaperManage", "normalBtnpink", nullptr)));
        Export_Button->setText(QApplication::translate("TestPaperManage", "\345\257\274\345\207\272", nullptr));
        Export_Button->setProperty("btnStyle", QVariant(QApplication::translate("TestPaperManage", "normalBtnpink", nullptr)));
        Down_Sort_Button_3->setText(QString());
        Down_Sort_Button_3->setProperty("btnStyle", QVariant(QApplication::translate("TestPaperManage", "normalBtnxia", nullptr)));
        Up_Sort_Button_2->setText(QString());
        Up_Sort_Button_2->setProperty("btnStyle", QVariant(QApplication::translate("TestPaperManage", "normalBtnshang", nullptr)));
        Add_Company_Button->setText(QString());
        Add_Company_Button->setProperty("btnStyle", QVariant(QApplication::translate("TestPaperManage", "normalBtnadd", nullptr)));
        Delete_Company_Button->setText(QString());
        Delete_Company_Button->setProperty("btnStyle", QVariant(QApplication::translate("TestPaperManage", "normalBtnshanc", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class TestPaperManage: public Ui_TestPaperManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTPAPERMANAGE_H
