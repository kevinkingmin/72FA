/********************************************************************************
** Form generated from reading UI file 'RulesSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULESSETTING_H
#define UI_RULESSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RulesSetting
{
public:
    QGroupBox *groupBox;
    QTableWidget *tableWidget_Rule;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *Modify_Button;
    QPushButton *Add_Button;
    QLabel *label_2;
    QTableWidget *tableWidget_Rules;
    QLineEdit *lineEditGrayValue;
    QLabel *label_3;
    QLineEdit *lineEditGrayWord;
    QPushButton *Delete_Button;
    QLabel *label;
    QLabel *label_4;

    void setupUi(QWidget *RulesSetting)
    {
        if (RulesSetting->objectName().isEmpty())
            RulesSetting->setObjectName(QString::fromUtf8("RulesSetting"));
        RulesSetting->resize(1454, 798);
        groupBox = new QGroupBox(RulesSetting);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(570, 60, 681, 661));
        tableWidget_Rule = new QTableWidget(groupBox);
        if (tableWidget_Rule->columnCount() < 1)
            tableWidget_Rule->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_Rule->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget_Rule->setObjectName(QString::fromUtf8("tableWidget_Rule"));
        tableWidget_Rule->setGeometry(QRect(10, 100, 256, 541));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(292, 102, 373, 541));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Modify_Button = new QPushButton(layoutWidget);
        Modify_Button->setObjectName(QString::fromUtf8("Modify_Button"));

        gridLayout->addWidget(Modify_Button, 3, 1, 1, 1);

        Add_Button = new QPushButton(layoutWidget);
        Add_Button->setObjectName(QString::fromUtf8("Add_Button"));

        gridLayout->addWidget(Add_Button, 3, 0, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        tableWidget_Rules = new QTableWidget(layoutWidget);
        if (tableWidget_Rules->columnCount() < 3)
            tableWidget_Rules->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_Rules->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_Rules->setHorizontalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_Rules->setHorizontalHeaderItem(2, __qtablewidgetitem3);
        tableWidget_Rules->setObjectName(QString::fromUtf8("tableWidget_Rules"));

        gridLayout->addWidget(tableWidget_Rules, 0, 0, 1, 3);

        lineEditGrayValue = new QLineEdit(layoutWidget);
        lineEditGrayValue->setObjectName(QString::fromUtf8("lineEditGrayValue"));

        gridLayout->addWidget(lineEditGrayValue, 1, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEditGrayWord = new QLineEdit(layoutWidget);
        lineEditGrayWord->setObjectName(QString::fromUtf8("lineEditGrayWord"));

        gridLayout->addWidget(lineEditGrayWord, 2, 1, 1, 1);

        Delete_Button = new QPushButton(layoutWidget);
        Delete_Button->setObjectName(QString::fromUtf8("Delete_Button"));

        gridLayout->addWidget(Delete_Button, 3, 2, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 20, 201, 31));
        label->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 50, 681, 16));

        retranslateUi(RulesSetting);

        QMetaObject::connectSlotsByName(RulesSetting);
    } // setupUi

    void retranslateUi(QWidget *RulesSetting)
    {
        RulesSetting->setWindowTitle(QApplication::translate("RulesSetting", "RulesSetting", nullptr));
        groupBox->setTitle(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget_Rule->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("RulesSetting", "\345\220\215\347\247\260", nullptr));
        Modify_Button->setText(QApplication::translate("RulesSetting", "\344\277\256\346\224\271", nullptr));
        Modify_Button->setProperty("btnStyle", QVariant(QApplication::translate("RulesSetting", "normalBtnpink", nullptr)));
        Add_Button->setText(QApplication::translate("RulesSetting", "\350\277\275\345\212\240", nullptr));
        Add_Button->setProperty("btnStyle", QVariant(QApplication::translate("RulesSetting", "normalBtnpink", nullptr)));
        label_2->setText(QApplication::translate("RulesSetting", "\347\201\260\345\272\246\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_Rules->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("RulesSetting", "No", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_Rules->horizontalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("RulesSetting", "\347\201\260\345\272\246\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_Rules->horizontalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("RulesSetting", "\346\230\276\347\244\272\347\254\246\345\217\267", nullptr));
        label_3->setText(QApplication::translate("RulesSetting", "\346\230\276\347\244\272\345\255\227\347\254\246", nullptr));
        Delete_Button->setText(QApplication::translate("RulesSetting", "\345\210\240\351\231\244", nullptr));
        Delete_Button->setProperty("btnStyle", QVariant(QApplication::translate("RulesSetting", "normalBtnpink", nullptr)));
        label->setText(QApplication::translate("RulesSetting", "\350\247\204\345\210\231\350\256\276\347\275\256", nullptr));
        label_4->setText(QApplication::translate("RulesSetting", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RulesSetting: public Ui_RulesSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULESSETTING_H
