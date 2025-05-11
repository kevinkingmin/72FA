/********************************************************************************
** Form generated from reading UI file 'workAreaForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKAREAFORM_H
#define UI_WORKAREAFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WorkAreaForm
{
public:
    QGridLayout *gridLayout_5;
    QWidget *widgetToolButton;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QToolButton *btnChooseItem;
    QToolButton *btnReviewResult;
    QSpacerItem *horizontalSpacer_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_8;
    QPushButton *pushButton_6;
    QWidget *page_2;

    void setupUi(QWidget *WorkAreaForm)
    {
        if (WorkAreaForm->objectName().isEmpty())
            WorkAreaForm->setObjectName(QString::fromUtf8("WorkAreaForm"));
        WorkAreaForm->resize(851, 623);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WorkAreaForm->sizePolicy().hasHeightForWidth());
        WorkAreaForm->setSizePolicy(sizePolicy);
        WorkAreaForm->setStyleSheet(QString::fromUtf8(""));
        gridLayout_5 = new QGridLayout(WorkAreaForm);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        widgetToolButton = new QWidget(WorkAreaForm);
        widgetToolButton->setObjectName(QString::fromUtf8("widgetToolButton"));
        widgetToolButton->setMinimumSize(QSize(0, 40));
        widgetToolButton->setMaximumSize(QSize(16777215, 40));
        gridLayout = new QGridLayout(widgetToolButton);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 5, -1, -1);
        btnChooseItem = new QToolButton(widgetToolButton);
        btnChooseItem->setObjectName(QString::fromUtf8("btnChooseItem"));
        btnChooseItem->setMinimumSize(QSize(160, 35));
        btnChooseItem->setMaximumSize(QSize(160, 30));
        btnChooseItem->setCheckable(true);
        btnChooseItem->setAutoExclusive(true);
        btnChooseItem->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout->addWidget(btnChooseItem);

        btnReviewResult = new QToolButton(widgetToolButton);
        btnReviewResult->setObjectName(QString::fromUtf8("btnReviewResult"));
        btnReviewResult->setMinimumSize(QSize(160, 35));
        btnReviewResult->setMaximumSize(QSize(160, 30));
        btnReviewResult->setCheckable(true);
        btnReviewResult->setAutoExclusive(true);
        btnReviewResult->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout->addWidget(btnReviewResult);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(2, 6);

        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        gridLayout_5->addWidget(widgetToolButton, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(WorkAreaForm);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        horizontalLayoutWidget = new QWidget(page);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(60, 40, 481, 391));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setCheckable(true);
        pushButton_2->setAutoExclusive(true);

        verticalLayout_2->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(horizontalLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setCheckable(true);
        pushButton_4->setAutoExclusive(true);

        verticalLayout_2->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(horizontalLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setCheckable(true);
        pushButton_3->setAutoExclusive(true);

        verticalLayout_2->addWidget(pushButton_3);

        pushButton_5 = new QPushButton(horizontalLayoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setCheckable(true);
        pushButton_5->setAutoExclusive(true);

        verticalLayout_2->addWidget(pushButton_5);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setCheckable(true);
        pushButton->setAutoExclusive(true);

        verticalLayout_2->addWidget(pushButton);


        horizontalLayout_4->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_7 = new QPushButton(horizontalLayoutWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setCheckable(true);
        pushButton_7->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_7);

        pushButton_9 = new QPushButton(horizontalLayoutWidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setCheckable(true);
        pushButton_9->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_9);

        pushButton_10 = new QPushButton(horizontalLayoutWidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setCheckable(true);
        pushButton_10->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_10);

        pushButton_8 = new QPushButton(horizontalLayoutWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setCheckable(true);
        pushButton_8->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_8);

        pushButton_6 = new QPushButton(horizontalLayoutWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setCheckable(true);
        pushButton_6->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_6);


        horizontalLayout_4->addLayout(verticalLayout);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        gridLayout_5->addWidget(stackedWidget, 1, 0, 1, 1);


        retranslateUi(WorkAreaForm);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WorkAreaForm);
    } // setupUi

    void retranslateUi(QWidget *WorkAreaForm)
    {
        WorkAreaForm->setWindowTitle(QApplication::translate("WorkAreaForm", "Form", nullptr));
        btnChooseItem->setText(QApplication::translate("WorkAreaForm", "\351\241\271\347\233\256\351\200\211\346\213\251", nullptr));
        btnChooseItem->setProperty("buttonStyle", QVariant(QApplication::translate("WorkAreaForm", "Report", nullptr)));
        btnReviewResult->setText(QApplication::translate("WorkAreaForm", "\347\273\223\346\236\234\351\242\204\350\247\210", nullptr));
        btnReviewResult->setProperty("buttonStyle", QVariant(QApplication::translate("WorkAreaForm", "Report", nullptr)));
        pushButton_2->setText(QApplication::translate("WorkAreaForm", "PushButton", nullptr));
        pushButton_4->setText(QApplication::translate("WorkAreaForm", "PushButton", nullptr));
        pushButton_3->setText(QApplication::translate("WorkAreaForm", "PushButton", nullptr));
        pushButton_5->setText(QApplication::translate("WorkAreaForm", "PushButton", nullptr));
        pushButton->setText(QApplication::translate("WorkAreaForm", "PushButton", nullptr));
        pushButton_7->setText(QApplication::translate("WorkAreaForm", "PushButton", nullptr));
        pushButton_9->setText(QApplication::translate("WorkAreaForm", "PushButton", nullptr));
        pushButton_10->setText(QApplication::translate("WorkAreaForm", "PushButton", nullptr));
        pushButton_8->setText(QApplication::translate("WorkAreaForm", "PushButton", nullptr));
        pushButton_6->setText(QApplication::translate("WorkAreaForm", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WorkAreaForm: public Ui_WorkAreaForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKAREAFORM_H
