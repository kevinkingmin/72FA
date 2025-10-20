/********************************************************************************
** Form generated from reading UI file 'ProcessDataList.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESSDATALIST_H
#define UI_PROCESSDATALIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProcessDataList
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tbProcess;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnAddProcess;
    QPushButton *btnDeleteProcess;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *tbProcessSteps;
    QVBoxLayout *verticalLayout_2;
    QPushButton *Add_Button;
    QPushButton *Delete_Button;
    QPushButton *Modify_Button;
    QSpacerItem *verticalSpacer;
    QPushButton *back_Button;

    void setupUi(QWidget *ProcessDataList)
    {
        if (ProcessDataList->objectName().isEmpty())
            ProcessDataList->setObjectName(QString::fromUtf8("ProcessDataList"));
        ProcessDataList->resize(1616, 789);
        layoutWidget = new QWidget(ProcessDataList);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 1591, 761));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(200, 0, 20, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 25));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, 0, -1);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(10, -1, -1, 0);
        tbProcess = new QTableWidget(layoutWidget);
        if (tbProcess->columnCount() < 3)
            tbProcess->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbProcess->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbProcess->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbProcess->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tbProcess->setObjectName(QString::fromUtf8("tbProcess"));

        verticalLayout_4->addWidget(tbProcess);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(15);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(25, 0, 25, -1);
        btnAddProcess = new QPushButton(layoutWidget);
        btnAddProcess->setObjectName(QString::fromUtf8("btnAddProcess"));

        horizontalLayout_2->addWidget(btnAddProcess);

        btnDeleteProcess = new QPushButton(layoutWidget);
        btnDeleteProcess->setObjectName(QString::fromUtf8("btnDeleteProcess"));

        horizontalLayout_2->addWidget(btnDeleteProcess);


        verticalLayout_4->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(15, -1, 0, 36);
        tbProcessSteps = new QTableWidget(layoutWidget);
        if (tbProcessSteps->columnCount() < 3)
            tbProcessSteps->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbProcessSteps->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbProcessSteps->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tbProcessSteps->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tbProcessSteps->setObjectName(QString::fromUtf8("tbProcessSteps"));

        verticalLayout_5->addWidget(tbProcessSteps);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(15);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(10, 10, -1, 45);
        Add_Button = new QPushButton(layoutWidget);
        Add_Button->setObjectName(QString::fromUtf8("Add_Button"));

        verticalLayout_2->addWidget(Add_Button);

        Delete_Button = new QPushButton(layoutWidget);
        Delete_Button->setObjectName(QString::fromUtf8("Delete_Button"));

        verticalLayout_2->addWidget(Delete_Button);

        Modify_Button = new QPushButton(layoutWidget);
        Modify_Button->setObjectName(QString::fromUtf8("Modify_Button"));

        verticalLayout_2->addWidget(Modify_Button);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        back_Button = new QPushButton(layoutWidget);
        back_Button->setObjectName(QString::fromUtf8("back_Button"));

        verticalLayout_2->addWidget(back_Button);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ProcessDataList);

        QMetaObject::connectSlotsByName(ProcessDataList);
    } // setupUi

    void retranslateUi(QWidget *ProcessDataList)
    {
        ProcessDataList->setWindowTitle(QApplication::translate("ProcessDataList", "ProcessDataList", nullptr));
        label->setText(QApplication::translate("ProcessDataList", "\345\275\223\345\211\215\351\200\211\346\213\251\345\216\202\345\256\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tbProcess->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ProcessDataList", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tbProcess->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ProcessDataList", "\346\265\201\347\250\213\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tbProcess->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ProcessDataList", "id", nullptr));
        btnAddProcess->setText(QApplication::translate("ProcessDataList", "\346\226\260\345\242\236\346\265\201\347\250\213", nullptr));
        btnAddProcess->setProperty("btnStyle", QVariant(QApplication::translate("ProcessDataList", "normalBtnpink", nullptr)));
        btnDeleteProcess->setText(QApplication::translate("ProcessDataList", "\345\210\240\351\231\244\346\265\201\347\250\213", nullptr));
        btnDeleteProcess->setProperty("btnStyle", QVariant(QApplication::translate("ProcessDataList", "normalBtnpink", nullptr)));
        QTableWidgetItem *___qtablewidgetitem3 = tbProcessSteps->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("ProcessDataList", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tbProcessSteps->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("ProcessDataList", "\346\255\245\351\252\244\345\217\202\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tbProcessSteps->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("ProcessDataList", "id", nullptr));
        Add_Button->setText(QApplication::translate("ProcessDataList", "\346\226\260\345\242\236\346\255\245\351\252\244", nullptr));
        Add_Button->setProperty("btnStyle", QVariant(QApplication::translate("ProcessDataList", "normalBtnpink", nullptr)));
        Delete_Button->setText(QApplication::translate("ProcessDataList", "\345\210\240\351\231\244\346\255\245\351\252\244", nullptr));
        Delete_Button->setProperty("btnStyle", QVariant(QApplication::translate("ProcessDataList", "normalBtnpink", nullptr)));
        Modify_Button->setText(QApplication::translate("ProcessDataList", "\347\274\226\350\276\221\346\255\245\351\252\244", nullptr));
        Modify_Button->setProperty("btnStyle", QVariant(QApplication::translate("ProcessDataList", "normalBtnpink", nullptr)));
        back_Button->setText(QApplication::translate("ProcessDataList", "\350\277\224\345\233\236", nullptr));
        back_Button->setProperty("btnStyle", QVariant(QApplication::translate("ProcessDataList", "normalBtnpink", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class ProcessDataList: public Ui_ProcessDataList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESSDATALIST_H
