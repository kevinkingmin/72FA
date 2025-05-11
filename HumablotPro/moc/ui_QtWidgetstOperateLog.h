/********************************************************************************
** Form generated from reading UI file 'QtWidgetstOperateLog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSTOPERATELOG_H
#define UI_QTWIDGETSTOPERATELOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetstOperateLogClass
{
public:
    QLabel *label_2;
    QLabel *label;
    QTableWidget *tableWidgetOperateLog;
    QTableWidget *tableWidgetOperateLog_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QDateEdit *dateEdit;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QDateEdit *dateEdit_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButtonQuery;

    void setupUi(QWidget *QtWidgetstOperateLogClass)
    {
        if (QtWidgetstOperateLogClass->objectName().isEmpty())
            QtWidgetstOperateLogClass->setObjectName(QString::fromUtf8("QtWidgetstOperateLogClass"));
        QtWidgetstOperateLogClass->resize(1876, 865);
        label_2 = new QLabel(QtWidgetstOperateLogClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 270, 71, 16));
        label = new QLabel(QtWidgetstOperateLogClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 131, 16));
        tableWidgetOperateLog = new QTableWidget(QtWidgetstOperateLogClass);
        if (tableWidgetOperateLog->columnCount() < 5)
            tableWidgetOperateLog->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetOperateLog->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetOperateLog->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetOperateLog->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetOperateLog->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetOperateLog->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetOperateLog->setObjectName(QString::fromUtf8("tableWidgetOperateLog"));
        tableWidgetOperateLog->setGeometry(QRect(11, 40, 1851, 221));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(12);
        tableWidgetOperateLog->setFont(font);
        tableWidgetOperateLog_2 = new QTableWidget(QtWidgetstOperateLogClass);
        if (tableWidgetOperateLog_2->columnCount() < 5)
            tableWidgetOperateLog_2->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetOperateLog_2->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetOperateLog_2->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetOperateLog_2->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetOperateLog_2->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetOperateLog_2->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        tableWidgetOperateLog_2->setObjectName(QString::fromUtf8("tableWidgetOperateLog_2"));
        tableWidgetOperateLog_2->setGeometry(QRect(10, 290, 1851, 491));
        tableWidgetOperateLog_2->setFont(font);
        layoutWidget = new QWidget(QtWidgetstOperateLogClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(1070, 10, 661, 25));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        dateEdit = new QDateEdit(layoutWidget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setDateTime(QDateTime(QDate(2023, 1, 1), QTime(0, 0, 0)));
        dateEdit->setCalendarPopup(true);

        gridLayout->addWidget(dateEdit, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 3, 1, 1);

        dateEdit_2 = new QDateEdit(layoutWidget);
        dateEdit_2->setObjectName(QString::fromUtf8("dateEdit_2"));
        dateEdit_2->setDateTime(QDateTime(QDate(2023, 2, 27), QTime(0, 0, 0)));
        dateEdit_2->setCalendarPopup(true);

        gridLayout->addWidget(dateEdit_2, 0, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 5, 1, 1);

        pushButtonQuery = new QPushButton(layoutWidget);
        pushButtonQuery->setObjectName(QString::fromUtf8("pushButtonQuery"));

        gridLayout->addWidget(pushButtonQuery, 0, 6, 1, 1);


        retranslateUi(QtWidgetstOperateLogClass);

        QMetaObject::connectSlotsByName(QtWidgetstOperateLogClass);
    } // setupUi

    void retranslateUi(QWidget *QtWidgetstOperateLogClass)
    {
        QtWidgetstOperateLogClass->setWindowTitle(QApplication::translate("QtWidgetstOperateLogClass", "QtWidgetstOperateLog", nullptr));
        label_2->setText(QApplication::translate("QtWidgetstOperateLogClass", "\350\277\220\350\241\214\346\227\245\345\277\227", nullptr));
        label->setText(QApplication::translate("QtWidgetstOperateLogClass", "\346\223\215\344\275\234\346\227\245\345\277\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetOperateLog->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QtWidgetstOperateLogClass", "\346\250\241\345\235\227\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetOperateLog->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QtWidgetstOperateLogClass", "\346\234\272\345\231\250\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetOperateLog->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QtWidgetstOperateLogClass", "\346\223\215\344\275\234\345\206\205\345\256\271", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetOperateLog->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QtWidgetstOperateLogClass", "\346\223\215\344\275\234\345\221\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetOperateLog->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("QtWidgetstOperateLogClass", "\346\223\215\344\275\234\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetOperateLog_2->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("QtWidgetstOperateLogClass", "\350\247\243\345\206\263\346\226\271\346\241\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetOperateLog_2->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("QtWidgetstOperateLogClass", "\346\234\272\345\231\250\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetOperateLog_2->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("QtWidgetstOperateLogClass", "\346\227\245\345\277\227\345\206\205\345\256\271", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetOperateLog_2->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QApplication::translate("QtWidgetstOperateLogClass", "\346\223\215\344\275\234\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetOperateLog_2->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QApplication::translate("QtWidgetstOperateLogClass", "\346\243\200\351\252\214\344\272\272", nullptr));
        label_3->setText(QApplication::translate("QtWidgetstOperateLogClass", "\345\274\200\345\247\213\346\227\266\351\227\264\357\274\232", nullptr));
        label_4->setText(QApplication::translate("QtWidgetstOperateLogClass", "\347\273\223\346\235\237\346\227\266\351\227\264\357\274\232", nullptr));
        pushButtonQuery->setText(QApplication::translate("QtWidgetstOperateLogClass", "\346\237\245\350\257\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetstOperateLogClass: public Ui_QtWidgetstOperateLogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSTOPERATELOG_H
