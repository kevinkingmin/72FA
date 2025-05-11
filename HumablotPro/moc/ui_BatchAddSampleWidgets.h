/********************************************************************************
** Form generated from reading UI file 'BatchAddSampleWidgets.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATCHADDSAMPLEWIDGETS_H
#define UI_BATCHADDSAMPLEWIDGETS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BatchAddSampleWidgetsClass
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tvSampleSet;
    QLabel *label_5;
    QPushButton *pushButtonOk;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButtonUpdate;
    QGroupBox *groupBox;
    QLineEdit *lineEditSampleEndIndex;
    QCheckBox *checkBox;
    QPushButton *pushButtonAdd;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEditSampleStartIndex;
    QLineEdit *lineEditSampleNo;
    QLineEdit *lineEditPaperEndIndex;
    QGroupBox *groupBox_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    QLabel *label_8;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonDeleteAll;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BatchAddSampleWidgetsClass)
    {
        if (BatchAddSampleWidgetsClass->objectName().isEmpty())
            BatchAddSampleWidgetsClass->setObjectName(QString::fromUtf8("BatchAddSampleWidgetsClass"));
        BatchAddSampleWidgetsClass->resize(1408, 692);
        centralWidget = new QWidget(BatchAddSampleWidgetsClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(950, 10, 31, 20));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tvSampleSet = new QTableWidget(centralWidget);
        if (tvSampleSet->columnCount() < 5)
            tvSampleSet->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tvSampleSet->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tvSampleSet->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tvSampleSet->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tvSampleSet->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tvSampleSet->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tvSampleSet->setObjectName(QString::fromUtf8("tvSampleSet"));
        tvSampleSet->setGeometry(QRect(560, 90, 821, 521));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tvSampleSet->sizePolicy().hasHeightForWidth());
        tvSampleSet->setSizePolicy(sizePolicy);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(560, 50, 241, 31));
        label_5->setLayoutDirection(Qt::LeftToRight);
        pushButtonOk = new QPushButton(centralWidget);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));
        pushButtonOk->setGeometry(QRect(1270, 30, 101, 41));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(700, 10, 211, 25));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButtonUpdate = new QPushButton(layoutWidget);
        pushButtonUpdate->setObjectName(QString::fromUtf8("pushButtonUpdate"));

        gridLayout_2->addWidget(pushButtonUpdate, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 350, 511, 261));
        lineEditSampleEndIndex = new QLineEdit(groupBox);
        lineEditSampleEndIndex->setObjectName(QString::fromUtf8("lineEditSampleEndIndex"));
        lineEditSampleEndIndex->setGeometry(QRect(160, 120, 161, 31));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(160, 158, 101, 31));
        checkBox->setChecked(false);
        pushButtonAdd = new QPushButton(groupBox);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
        pushButtonAdd->setGeometry(QRect(350, 174, 151, 41));
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 40, 131, 181));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 0, 0, 1, 1);

        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        lineEditSampleStartIndex = new QLineEdit(groupBox);
        lineEditSampleStartIndex->setObjectName(QString::fromUtf8("lineEditSampleStartIndex"));
        lineEditSampleStartIndex->setGeometry(QRect(160, 80, 161, 31));
        lineEditSampleNo = new QLineEdit(groupBox);
        lineEditSampleNo->setObjectName(QString::fromUtf8("lineEditSampleNo"));
        lineEditSampleNo->setGeometry(QRect(160, 40, 161, 31));
        lineEditPaperEndIndex = new QLineEdit(groupBox);
        lineEditPaperEndIndex->setObjectName(QString::fromUtf8("lineEditPaperEndIndex"));
        lineEditPaperEndIndex->setGeometry(QRect(160, 192, 161, 31));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 20, 511, 311));
        gridLayoutWidget = new QWidget(groupBox_2);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 80, 461, 221));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(180, 30, 161, 41));
        label_6->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(1, 60, 509, 16));
        pushButtonDelete = new QPushButton(centralWidget);
        pushButtonDelete->setObjectName(QString::fromUtf8("pushButtonDelete"));
        pushButtonDelete->setGeometry(QRect(1130, 30, 101, 41));
        pushButtonDeleteAll = new QPushButton(centralWidget);
        pushButtonDeleteAll->setObjectName(QString::fromUtf8("pushButtonDeleteAll"));
        pushButtonDeleteAll->setGeometry(QRect(990, 30, 101, 41));
        BatchAddSampleWidgetsClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BatchAddSampleWidgetsClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1408, 23));
        BatchAddSampleWidgetsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BatchAddSampleWidgetsClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        BatchAddSampleWidgetsClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BatchAddSampleWidgetsClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BatchAddSampleWidgetsClass->setStatusBar(statusBar);

        retranslateUi(BatchAddSampleWidgetsClass);

        QMetaObject::connectSlotsByName(BatchAddSampleWidgetsClass);
    } // setupUi

    void retranslateUi(QMainWindow *BatchAddSampleWidgetsClass)
    {
        BatchAddSampleWidgetsClass->setWindowTitle(QApplication::translate("BatchAddSampleWidgetsClass", "\346\211\271\351\207\217\346\267\273\345\212\240", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tvSampleSet->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tvSampleSet->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\350\206\234\346\235\241\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tvSampleSet->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\345\244\215\345\255\224\346\225\260\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tvSampleSet->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\345\274\200\345\247\213\346\240\267\346\234\254\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tvSampleSet->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\347\273\223\346\235\237\346\240\267\346\234\254\347\274\226\345\217\267", nullptr));
        label_5->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\346\240\267\346\234\254\345\210\227\350\241\250\357\274\232", nullptr));
        pushButtonOk->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\345\256\214\346\210\220", nullptr));
        pushButtonOk->setProperty("btnStyle", QVariant(QApplication::translate("BatchAddSampleWidgetsClass", "normalBtnRed", nullptr)));
        pushButtonUpdate->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\344\277\235\345\255\230", nullptr));
        groupBox->setTitle(QString());
        lineEditSampleEndIndex->setText(QApplication::translate("BatchAddSampleWidgetsClass", "1", nullptr));
        checkBox->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\345\244\215\345\255\224", nullptr));
        pushButtonAdd->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\346\211\271\351\207\217\346\267\273\345\212\240\345\271\266\344\277\235\345\255\230", nullptr));
        pushButtonAdd->setProperty("btnStyle", QVariant(QApplication::translate("BatchAddSampleWidgetsClass", "normalBtnRed", nullptr)));
        label_7->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\345\274\200\345\247\213\346\240\267\346\234\254\347\274\226\345\217\267\357\274\232", nullptr));
        label->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\345\274\200\345\247\213\346\240\267\346\234\254\344\275\215\347\275\256\357\274\232", nullptr));
        label_2->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\347\273\223\346\235\237\346\240\267\346\234\254\344\275\215\347\275\256\357\274\232", nullptr));
        label_3->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\346\230\257\345\220\246\345\244\215\345\255\224\357\274\232", nullptr));
        label_4->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\346\225\260\351\207\217\357\274\232", nullptr));
        lineEditSampleStartIndex->setText(QApplication::translate("BatchAddSampleWidgetsClass", "1", nullptr));
        lineEditSampleNo->setText(QApplication::translate("BatchAddSampleWidgetsClass", "20230215", nullptr));
        lineEditPaperEndIndex->setText(QApplication::translate("BatchAddSampleWidgetsClass", "1", nullptr));
        groupBox_2->setTitle(QString());
        label_6->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\350\206\234\346\235\241\347\261\273\345\236\213\351\200\211\346\213\251", nullptr));
        label_8->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
        pushButtonDelete->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\345\210\240\351\231\244", nullptr));
        pushButtonDelete->setProperty("btnStyle", QVariant(QApplication::translate("BatchAddSampleWidgetsClass", "normalBtnRed", nullptr)));
        pushButtonDeleteAll->setText(QApplication::translate("BatchAddSampleWidgetsClass", "\345\210\240\351\231\244\346\211\200\346\234\211", nullptr));
        pushButtonDeleteAll->setProperty("btnStyle", QVariant(QApplication::translate("BatchAddSampleWidgetsClass", "normalBtnRed", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class BatchAddSampleWidgetsClass: public Ui_BatchAddSampleWidgetsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATCHADDSAMPLEWIDGETS_H
