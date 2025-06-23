/********************************************************************************
** Form generated from reading UI file 'TestResultDataAll.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTRESULTDATAALL_H
#define UI_TESTRESULTDATAALL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestResultDataAll
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *pushButtonQuery;
    QDateEdit *dateEdit_2;
    QPushButton *pushButtonPdf;
    QPushButton *pushButtonPrint;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pushButtonSelectAll;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_3;
    QPushButton *pushButtonPdfAll;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButtonPrintA;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QDateEdit *dateEdit;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButtonUpdateToLis;
    QPushButton *btnSampleInfo;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *comboBoxPaperID;
    QPushButton *btnAnalyze;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelCount;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_5;
    QLineEdit *lineEditRowsPerPage;
    QPushButton *pushButtonPageNumberSet;
    QPushButton *pushButtonTopPage;
    QPushButton *pushButtonNextPage;
    QLabel *label_4;
    QLineEdit *lineEditPageIndex;
    QLabel *label_6;
    QPushButton *pushButtonJumpPage;

    void setupUi(QWidget *TestResultDataAll)
    {
        if (TestResultDataAll->objectName().isEmpty())
            TestResultDataAll->setObjectName(QString::fromUtf8("TestResultDataAll"));
        TestResultDataAll->resize(1514, 794);
        verticalLayout_2 = new QVBoxLayout(TestResultDataAll);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonQuery = new QPushButton(TestResultDataAll);
        pushButtonQuery->setObjectName(QString::fromUtf8("pushButtonQuery"));

        gridLayout->addWidget(pushButtonQuery, 0, 23, 1, 1);

        dateEdit_2 = new QDateEdit(TestResultDataAll);
        dateEdit_2->setObjectName(QString::fromUtf8("dateEdit_2"));
        dateEdit_2->setDateTime(QDateTime(QDate(2022, 12, 19), QTime(0, 0, 0)));
        dateEdit_2->setCalendarPopup(true);

        gridLayout->addWidget(dateEdit_2, 0, 18, 1, 1);

        pushButtonPdf = new QPushButton(TestResultDataAll);
        pushButtonPdf->setObjectName(QString::fromUtf8("pushButtonPdf"));

        gridLayout->addWidget(pushButtonPdf, 0, 10, 1, 1);

        pushButtonPrint = new QPushButton(TestResultDataAll);
        pushButtonPrint->setObjectName(QString::fromUtf8("pushButtonPrint"));

        gridLayout->addWidget(pushButtonPrint, 0, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 7, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_11, 0, 3, 1, 1);

        pushButtonSelectAll = new QPushButton(TestResultDataAll);
        pushButtonSelectAll->setObjectName(QString::fromUtf8("pushButtonSelectAll"));

        gridLayout->addWidget(pushButtonSelectAll, 0, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 0, 5, 1, 1);

        label_3 = new QLabel(TestResultDataAll);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 20, 1, 1);

        pushButtonPdfAll = new QPushButton(TestResultDataAll);
        pushButtonPdfAll->setObjectName(QString::fromUtf8("pushButtonPdfAll"));

        gridLayout->addWidget(pushButtonPdfAll, 0, 12, 1, 1);

        label_2 = new QLabel(TestResultDataAll);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 17, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 19, 1, 1);

        pushButtonPrintA = new QPushButton(TestResultDataAll);
        pushButtonPrintA->setObjectName(QString::fromUtf8("pushButtonPrintA"));

        gridLayout->addWidget(pushButtonPrintA, 0, 8, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 9, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 16, 1, 1);

        dateEdit = new QDateEdit(TestResultDataAll);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setDateTime(QDateTime(QDate(2023, 1, 1), QTime(0, 0, 0)));
        dateEdit->setCalendarPopup(true);

        gridLayout->addWidget(dateEdit, 0, 15, 1, 1);

        pushButton = new QPushButton(TestResultDataAll);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 24, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 0, 11, 1, 1);

        pushButtonUpdateToLis = new QPushButton(TestResultDataAll);
        pushButtonUpdateToLis->setObjectName(QString::fromUtf8("pushButtonUpdateToLis"));

        gridLayout->addWidget(pushButtonUpdateToLis, 0, 2, 1, 1);

        btnSampleInfo = new QPushButton(TestResultDataAll);
        btnSampleInfo->setObjectName(QString::fromUtf8("btnSampleInfo"));

        gridLayout->addWidget(btnSampleInfo, 0, 4, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_10, 0, 25, 1, 1);

        label = new QLabel(TestResultDataAll);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 14, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 22, 1, 1);

        comboBoxPaperID = new QComboBox(TestResultDataAll);
        comboBoxPaperID->setObjectName(QString::fromUtf8("comboBoxPaperID"));

        gridLayout->addWidget(comboBoxPaperID, 0, 21, 1, 1);

        btnAnalyze = new QPushButton(TestResultDataAll);
        btnAnalyze->setObjectName(QString::fromUtf8("btnAnalyze"));

        gridLayout->addWidget(btnAnalyze, 0, 13, 1, 1);


        verticalLayout->addLayout(gridLayout);

        tableWidget = new QTableWidget(TestResultDataAll);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
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
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelCount = new QLabel(TestResultDataAll);
        labelCount->setObjectName(QString::fromUtf8("labelCount"));

        horizontalLayout->addWidget(labelCount);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);

        label_5 = new QLabel(TestResultDataAll);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        lineEditRowsPerPage = new QLineEdit(TestResultDataAll);
        lineEditRowsPerPage->setObjectName(QString::fromUtf8("lineEditRowsPerPage"));
        lineEditRowsPerPage->setMinimumSize(QSize(60, 0));
        lineEditRowsPerPage->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(lineEditRowsPerPage);

        pushButtonPageNumberSet = new QPushButton(TestResultDataAll);
        pushButtonPageNumberSet->setObjectName(QString::fromUtf8("pushButtonPageNumberSet"));

        horizontalLayout->addWidget(pushButtonPageNumberSet);

        pushButtonTopPage = new QPushButton(TestResultDataAll);
        pushButtonTopPage->setObjectName(QString::fromUtf8("pushButtonTopPage"));

        horizontalLayout->addWidget(pushButtonTopPage);

        pushButtonNextPage = new QPushButton(TestResultDataAll);
        pushButtonNextPage->setObjectName(QString::fromUtf8("pushButtonNextPage"));

        horizontalLayout->addWidget(pushButtonNextPage);

        label_4 = new QLabel(TestResultDataAll);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        lineEditPageIndex = new QLineEdit(TestResultDataAll);
        lineEditPageIndex->setObjectName(QString::fromUtf8("lineEditPageIndex"));
        lineEditPageIndex->setMinimumSize(QSize(60, 0));
        lineEditPageIndex->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(lineEditPageIndex);

        label_6 = new QLabel(TestResultDataAll);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        pushButtonJumpPage = new QPushButton(TestResultDataAll);
        pushButtonJumpPage->setObjectName(QString::fromUtf8("pushButtonJumpPage"));

        horizontalLayout->addWidget(pushButtonJumpPage);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(TestResultDataAll);

        QMetaObject::connectSlotsByName(TestResultDataAll);
    } // setupUi

    void retranslateUi(QWidget *TestResultDataAll)
    {
        TestResultDataAll->setWindowTitle(QApplication::translate("TestResultDataAll", "TestResultDataAll", nullptr));
        pushButtonQuery->setText(QApplication::translate("TestResultDataAll", "\346\237\245\350\257\242", nullptr));
        pushButtonQuery->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnRed", nullptr)));
        pushButtonPdf->setText(QApplication::translate("TestResultDataAll", "\345\215\225\351\241\265\344\277\235\345\255\230PDF", nullptr));
        pushButtonPdf->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnpink", nullptr)));
        pushButtonPrint->setText(QApplication::translate("TestResultDataAll", "\346\246\202\350\277\260\346\212\245\345\221\212\346\211\223\345\215\260", nullptr));
        pushButtonPrint->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnpink", nullptr)));
        pushButtonSelectAll->setText(QApplication::translate("TestResultDataAll", "\345\205\250\351\200\211", nullptr));
        pushButtonSelectAll->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnpink", nullptr)));
        label_3->setText(QApplication::translate("TestResultDataAll", "\350\206\234\346\235\241\351\200\211\346\213\251", nullptr));
        pushButtonPdfAll->setText(QApplication::translate("TestResultDataAll", "\346\246\202\350\277\260\344\277\235\345\255\230PDF", nullptr));
        pushButtonPdfAll->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnpink", nullptr)));
        label_2->setText(QApplication::translate("TestResultDataAll", "\347\273\223\346\235\237\346\227\266\351\227\264\357\274\232", nullptr));
        pushButtonPrintA->setText(QApplication::translate("TestResultDataAll", "\345\215\225\351\241\265\346\212\245\345\221\212\346\211\223\345\215\260", nullptr));
        pushButtonPrintA->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnpink", nullptr)));
        pushButton->setText(QApplication::translate("TestResultDataAll", "\345\275\223\345\244\251\346\243\200\346\265\213\347\273\223\346\236\234\346\237\245\350\257\242", nullptr));
        pushButton->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnRed", nullptr)));
        pushButtonUpdateToLis->setText(QApplication::translate("TestResultDataAll", "\344\274\240\350\276\223", nullptr));
        pushButtonUpdateToLis->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnpink", nullptr)));
        btnSampleInfo->setText(QApplication::translate("TestResultDataAll", "\346\240\267\346\234\254\344\277\241\346\201\257", nullptr));
        btnSampleInfo->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnpink", nullptr)));
        label->setText(QApplication::translate("TestResultDataAll", "\345\274\200\345\247\213\346\227\266\351\227\264\357\274\232", nullptr));
        btnAnalyze->setText(QApplication::translate("TestResultDataAll", "\350\247\243\346\236\220", nullptr));
        btnAnalyze->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnpink", nullptr)));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TestResultDataAll", "\346\230\257\345\220\246\351\200\211\344\270\255", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("TestResultDataAll", "\346\265\213\350\257\225\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("TestResultDataAll", "\346\240\267\346\234\254\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("TestResultDataAll", "\346\243\200\346\265\213\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("TestResultDataAll", "\345\255\220\346\243\200\346\265\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("TestResultDataAll", "\345\233\276\345\203\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("TestResultDataAll", "LIS\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("TestResultDataAll", "\345\210\244\350\257\273\347\273\223\346\236\234", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("TestResultDataAll", "pkid", nullptr));
        labelCount->setText(QApplication::translate("TestResultDataAll", "\347\273\237\350\256\241\357\274\232", nullptr));
        label_5->setText(QApplication::translate("TestResultDataAll", "\346\257\217\351\241\265\350\241\214\346\225\260\357\274\232", nullptr));
        lineEditRowsPerPage->setText(QApplication::translate("TestResultDataAll", "24", nullptr));
        pushButtonPageNumberSet->setText(QApplication::translate("TestResultDataAll", "\350\256\276\345\256\232", nullptr));
        pushButtonPageNumberSet->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnpink", nullptr)));
        pushButtonTopPage->setText(QApplication::translate("TestResultDataAll", "\344\270\212\344\270\200\351\241\265", nullptr));
        pushButtonTopPage->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnpink", nullptr)));
        pushButtonNextPage->setText(QApplication::translate("TestResultDataAll", "\344\270\213\344\270\200\351\241\265", nullptr));
        pushButtonNextPage->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnpink", nullptr)));
        label_4->setText(QApplication::translate("TestResultDataAll", "\350\267\263\350\275\254\345\210\260\357\274\232", nullptr));
        lineEditPageIndex->setText(QApplication::translate("TestResultDataAll", "1", nullptr));
        label_6->setText(QApplication::translate("TestResultDataAll", "\351\241\265", nullptr));
        pushButtonJumpPage->setText(QApplication::translate("TestResultDataAll", "go", nullptr));
        pushButtonJumpPage->setProperty("btnStyle", QVariant(QApplication::translate("TestResultDataAll", "normalBtnpink", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class TestResultDataAll: public Ui_TestResultDataAll {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTRESULTDATAALL_H
