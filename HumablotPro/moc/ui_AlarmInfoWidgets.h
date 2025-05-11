/********************************************************************************
** Form generated from reading UI file 'AlarmInfoWidgets.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALARMINFOWIDGETS_H
#define UI_ALARMINFOWIDGETS_H

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

class Ui_AlarmInfoWidgets
{
public:
    QTableWidget *tableWidgetAlarmInfo;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *labelAlarmInfo;
    QSpacerItem *horizontalSpacer;
    QLabel *labelAlarmInfo_2;
    QDateEdit *dateEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *AlarmInfoWidgets)
    {
        if (AlarmInfoWidgets->objectName().isEmpty())
            AlarmInfoWidgets->setObjectName(QString::fromUtf8("AlarmInfoWidgets"));
        AlarmInfoWidgets->resize(1456, 712);
        tableWidgetAlarmInfo = new QTableWidget(AlarmInfoWidgets);
        if (tableWidgetAlarmInfo->columnCount() < 3)
            tableWidgetAlarmInfo->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetAlarmInfo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetAlarmInfo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetAlarmInfo->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetAlarmInfo->setObjectName(QString::fromUtf8("tableWidgetAlarmInfo"));
        tableWidgetAlarmInfo->setGeometry(QRect(20, 50, 1411, 631));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(12);
        tableWidgetAlarmInfo->setFont(font);
        widget = new QWidget(AlarmInfoWidgets);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(31, 20, 357, 25));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        labelAlarmInfo = new QLabel(widget);
        labelAlarmInfo->setObjectName(QString::fromUtf8("labelAlarmInfo"));
        labelAlarmInfo->setFont(font);

        gridLayout->addWidget(labelAlarmInfo, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        labelAlarmInfo_2 = new QLabel(widget);
        labelAlarmInfo_2->setObjectName(QString::fromUtf8("labelAlarmInfo_2"));
        labelAlarmInfo_2->setFont(font);

        gridLayout->addWidget(labelAlarmInfo_2, 0, 2, 1, 1);

        dateEdit = new QDateEdit(widget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setDateTime(QDateTime(QDate(2023, 2, 27), QTime(0, 0, 0)));
        dateEdit->setCalendarPopup(true);

        gridLayout->addWidget(dateEdit, 0, 3, 1, 1);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 4, 1, 1);


        retranslateUi(AlarmInfoWidgets);

        QMetaObject::connectSlotsByName(AlarmInfoWidgets);
    } // setupUi

    void retranslateUi(QWidget *AlarmInfoWidgets)
    {
        AlarmInfoWidgets->setWindowTitle(QApplication::translate("AlarmInfoWidgets", "AlarmInfoWidgets", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetAlarmInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("AlarmInfoWidgets", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetAlarmInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("AlarmInfoWidgets", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetAlarmInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("AlarmInfoWidgets", "\346\225\205\351\232\234\345\206\205\345\256\271", nullptr));
        labelAlarmInfo->setText(QApplication::translate("AlarmInfoWidgets", "\346\212\245\350\255\246\344\277\241\346\201\257", nullptr));
        labelAlarmInfo_2->setText(QApplication::translate("AlarmInfoWidgets", "\346\227\245\346\234\237\346\237\245\350\257\242", nullptr));
        pushButton->setText(QApplication::translate("AlarmInfoWidgets", "\346\237\245\350\257\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlarmInfoWidgets: public Ui_AlarmInfoWidgets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALARMINFOWIDGETS_H
