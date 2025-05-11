/********************************************************************************
** Form generated from reading UI file 'TestSampleWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTSAMPLEWIDGET_H
#define UI_TESTSAMPLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "src/comm/CustClickWidget.h"

QT_BEGIN_NAMESPACE

class Ui_TestSampleWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *twiget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnSubBody;
    QLabel *lblStep;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *lblPause;
    QLabel *lblPlainEnd;
    QLabel *lblSolutionEnd;
    QLabel *label_9;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnSet;
    QPushButton *btnPause;
    QPushButton *btnStop;
    QPushButton *btnReturnMain;
    QSpacerItem *horizontalSpacer_13;
    QWidget *subStepsWidget;
    QHBoxLayout *horizontalLayout_6;
    CustClickWidget *btnFlushWidget;
    QHBoxLayout *hLaySteps;
    QWidget *hWRunInfo1;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *hLayPaperPos;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *hLayPaperPos1;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_4;
    QWidget *verticalWidget_prograss_2;
    QHBoxLayout *verticalWidget_prograss;
    QWidget *verticalWidget_prograss33;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QLabel *lblProgress;
    QSpacerItem *horizontalSpacer_5;
    QLabel *lblSubContent;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *hLayProcess;
    QProgressBar *progressBar;
    QWidget *blockWiget;
    QVBoxLayout *verticalLayout_2;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout_5;
    QWidget *subBodyW;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QWidget *subTitleW;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_12;
    QLabel *lblSubTitle;
    QSpacerItem *horizontalSpacer_4;
    QTextBrowser *textBrowser_2;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *TestSampleWidget)
    {
        if (TestSampleWidget->objectName().isEmpty())
            TestSampleWidget->setObjectName(QString::fromUtf8("TestSampleWidget"));
        TestSampleWidget->resize(1319, 701);
        horizontalLayout = new QHBoxLayout(TestSampleWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        twiget = new QWidget(TestSampleWidget);
        twiget->setObjectName(QString::fromUtf8("twiget"));
        verticalLayout = new QVBoxLayout(twiget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 10, 3, 8);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(15, -1, 10, 5);
        btnSubBody = new QPushButton(twiget);
        btnSubBody->setObjectName(QString::fromUtf8("btnSubBody"));

        horizontalLayout_2->addWidget(btnSubBody);

        lblStep = new QLabel(twiget);
        lblStep->setObjectName(QString::fromUtf8("lblStep"));
        lblStep->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(lblStep);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(12);
        gridLayout->setVerticalSpacing(2);
        label_5 = new QLabel(twiget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(135, 0));
        label_5->setLayoutDirection(Qt::LeftToRight);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 0, 4, 1, 1);

        lblPause = new QLabel(twiget);
        lblPause->setObjectName(QString::fromUtf8("lblPause"));

        gridLayout->addWidget(lblPause, 0, 1, 1, 1);

        lblPlainEnd = new QLabel(twiget);
        lblPlainEnd->setObjectName(QString::fromUtf8("lblPlainEnd"));

        gridLayout->addWidget(lblPlainEnd, 0, 5, 1, 1);

        lblSolutionEnd = new QLabel(twiget);
        lblSolutionEnd->setObjectName(QString::fromUtf8("lblSolutionEnd"));

        gridLayout->addWidget(lblSolutionEnd, 0, 3, 1, 1);

        label_9 = new QLabel(twiget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setLayoutDirection(Qt::LeftToRight);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_9, 0, 0, 1, 1);

        label_3 = new QLabel(twiget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(135, 0));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 0, 2, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnSet = new QPushButton(twiget);
        btnSet->setObjectName(QString::fromUtf8("btnSet"));
        btnSet->setMinimumSize(QSize(64, 64));

        horizontalLayout_3->addWidget(btnSet);

        btnPause = new QPushButton(twiget);
        btnPause->setObjectName(QString::fromUtf8("btnPause"));
        btnPause->setMinimumSize(QSize(64, 64));

        horizontalLayout_3->addWidget(btnPause);

        btnStop = new QPushButton(twiget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setMinimumSize(QSize(64, 64));

        horizontalLayout_3->addWidget(btnStop);

        btnReturnMain = new QPushButton(twiget);
        btnReturnMain->setObjectName(QString::fromUtf8("btnReturnMain"));
        btnReturnMain->setMinimumSize(QSize(64, 64));

        horizontalLayout_3->addWidget(btnReturnMain);

        horizontalSpacer_13 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_13);

        subStepsWidget = new QWidget(twiget);
        subStepsWidget->setObjectName(QString::fromUtf8("subStepsWidget"));
        horizontalLayout_6 = new QHBoxLayout(subStepsWidget);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        btnFlushWidget = new CustClickWidget(subStepsWidget);
        btnFlushWidget->setObjectName(QString::fromUtf8("btnFlushWidget"));
        btnFlushWidget->setMinimumSize(QSize(0, 64));
        btnFlushWidget->setMaximumSize(QSize(16777215, 64));
        hLaySteps = new QHBoxLayout(btnFlushWidget);
        hLaySteps->setObjectName(QString::fromUtf8("hLaySteps"));
        hLaySteps->setContentsMargins(9, 0, 9, 0);

        horizontalLayout_6->addWidget(btnFlushWidget);


        horizontalLayout_3->addWidget(subStepsWidget);


        horizontalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(horizontalLayout_2);

        hWRunInfo1 = new QWidget(twiget);
        hWRunInfo1->setObjectName(QString::fromUtf8("hWRunInfo1"));
        horizontalLayout_12 = new QHBoxLayout(hWRunInfo1);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(20, 20, 20, 25);
        horizontalSpacer_7 = new QSpacerItem(20, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_7);

        hLayPaperPos = new QHBoxLayout();
        hLayPaperPos->setObjectName(QString::fromUtf8("hLayPaperPos"));
        hLayPaperPos->setContentsMargins(3, 4, 3, 5);

        horizontalLayout_12->addLayout(hLayPaperPos);

        horizontalSpacer_10 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_10);

        hLayPaperPos1 = new QHBoxLayout();
        hLayPaperPos1->setObjectName(QString::fromUtf8("hLayPaperPos1"));
        hLayPaperPos1->setContentsMargins(3, 4, 3, 5);

        horizontalLayout_12->addLayout(hLayPaperPos1);

        horizontalSpacer_8 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_8);


        verticalLayout->addWidget(hWRunInfo1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(9, 9, 9, 9);
        verticalWidget_prograss_2 = new QWidget(twiget);
        verticalWidget_prograss_2->setObjectName(QString::fromUtf8("verticalWidget_prograss_2"));
        verticalWidget_prograss = new QHBoxLayout(verticalWidget_prograss_2);
        verticalWidget_prograss->setObjectName(QString::fromUtf8("verticalWidget_prograss"));
        verticalWidget_prograss33 = new QWidget(verticalWidget_prograss_2);
        verticalWidget_prograss33->setObjectName(QString::fromUtf8("verticalWidget_prograss33"));
        verticalLayout_6 = new QVBoxLayout(verticalWidget_prograss33);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(6, -1, -1, -1);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(12);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(10, 5, -1, 0);
        label_2 = new QLabel(verticalWidget_prograss33);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("font-size:18px;"));

        horizontalLayout_8->addWidget(label_2);

        lblProgress = new QLabel(verticalWidget_prograss33);
        lblProgress->setObjectName(QString::fromUtf8("lblProgress"));
        lblProgress->setStyleSheet(QString::fromUtf8("font-size:18px;\n"
"font-weight:bold;\n"
"color:rgb(0,0,100,120);"));

        horizontalLayout_8->addWidget(lblProgress);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);

        lblSubContent = new QLabel(verticalWidget_prograss33);
        lblSubContent->setObjectName(QString::fromUtf8("lblSubContent"));
        lblSubContent->setMinimumSize(QSize(80, 0));

        horizontalLayout_8->addWidget(lblSubContent);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);


        verticalLayout_6->addLayout(horizontalLayout_8);

        hLayProcess = new QHBoxLayout();
        hLayProcess->setObjectName(QString::fromUtf8("hLayProcess"));
        hLayProcess->setContentsMargins(10, 0, 10, 8);
        progressBar = new QProgressBar(verticalWidget_prograss33);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(0, 0));
        progressBar->setMaximum(100);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextVisible(false);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        hLayProcess->addWidget(progressBar);


        verticalLayout_6->addLayout(hLayProcess);


        verticalWidget_prograss->addWidget(verticalWidget_prograss33);


        verticalLayout_4->addWidget(verticalWidget_prograss_2);


        verticalLayout->addLayout(verticalLayout_4);

        blockWiget = new QWidget(twiget);
        blockWiget->setObjectName(QString::fromUtf8("blockWiget"));
        verticalLayout_2 = new QVBoxLayout(blockWiget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(9, 9, 9, 9);
        verticalWidget = new QWidget(blockWiget);
        verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
        verticalLayout_5 = new QVBoxLayout(verticalWidget);
        verticalLayout_5->setSpacing(1);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(10, 1, 10, 1);

        verticalLayout_2->addWidget(verticalWidget);

        subBodyW = new QWidget(blockWiget);
        subBodyW->setObjectName(QString::fromUtf8("subBodyW"));
        horizontalLayout_5 = new QHBoxLayout(subBodyW);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, 10, 10, 10);
        subTitleW = new QWidget(subBodyW);
        subTitleW->setObjectName(QString::fromUtf8("subTitleW"));
        horizontalLayout_4 = new QHBoxLayout(subTitleW);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(10, 2, 2, 3);
        horizontalSpacer_12 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_12);

        lblSubTitle = new QLabel(subTitleW);
        lblSubTitle->setObjectName(QString::fromUtf8("lblSubTitle"));
        lblSubTitle->setMinimumSize(QSize(80, 0));
        lblSubTitle->setStyleSheet(QString::fromUtf8("color:white;"));

        horizontalLayout_4->addWidget(lblSubTitle);

        horizontalSpacer_4 = new QSpacerItem(40, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_3->addWidget(subTitleW);

        textBrowser_2 = new QTextBrowser(subBodyW);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));

        verticalLayout_3->addWidget(textBrowser_2);

        horizontalSpacer_14 = new QSpacerItem(40, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_14);


        horizontalLayout_5->addLayout(verticalLayout_3);


        verticalLayout_2->addWidget(subBodyW);


        verticalLayout->addWidget(blockWiget);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(twiget);


        retranslateUi(TestSampleWidget);

        QMetaObject::connectSlotsByName(TestSampleWidget);
    } // setupUi

    void retranslateUi(QWidget *TestSampleWidget)
    {
        TestSampleWidget->setWindowTitle(QApplication::translate("TestSampleWidget", "Form", nullptr));
        twiget->setProperty("widgetStyle", QVariant(QApplication::translate("TestSampleWidget", "BGStyle", nullptr)));
        btnSubBody->setText(QString());
        btnSubBody->setProperty("btnStyle", QVariant(QApplication::translate("TestSampleWidget", "normalBtn", nullptr)));
        lblStep->setText(QApplication::translate("TestSampleWidget", "\346\255\245\351\252\244", nullptr));
        label_5->setText(QApplication::translate("TestSampleWidget", "\351\242\204\346\234\237\345\256\214\346\210\220\346\227\266\351\227\264  ", nullptr));
        lblPause->setText(QApplication::translate("TestSampleWidget", "___:___:___", nullptr));
        lblPlainEnd->setText(QApplication::translate("TestSampleWidget", "___:___:___", nullptr));
        lblSolutionEnd->setText(QApplication::translate("TestSampleWidget", "___:___:___", nullptr));
        label_9->setText(QApplication::translate("TestSampleWidget", "\346\232\202\345\201\234\346\227\266\351\227\264  ", nullptr));
        label_3->setText(QApplication::translate("TestSampleWidget", "\346\200\273\350\256\241\347\224\250\346\227\266  ", nullptr));
        btnSet->setText(QString());
        btnSet->setProperty("btnStyle", QVariant(QApplication::translate("TestSampleWidget", "iconRunStyle", nullptr)));
        btnPause->setText(QString());
        btnPause->setProperty("btnStyle", QVariant(QApplication::translate("TestSampleWidget", "iconPauseStyle", nullptr)));
        btnStop->setText(QString());
        btnStop->setProperty("btnStyle", QVariant(QApplication::translate("TestSampleWidget", "iconStopStyle", nullptr)));
        btnReturnMain->setText(QString());
        btnReturnMain->setProperty("btnStyle", QVariant(QApplication::translate("TestSampleWidget", "iconReturnMainStyle", nullptr)));
        subStepsWidget->setProperty("widgetStyle", QVariant(QApplication::translate("TestSampleWidget", "BGStyle", nullptr)));
        label_2->setText(QApplication::translate("TestSampleWidget", "\347\212\266\346\200\201", nullptr));
        lblProgress->setText(QApplication::translate("TestSampleWidget", "\345\275\223\345\211\215\350\277\233\345\272\246\346\230\276\347\244\272(7/9)", nullptr));
        lblSubContent->setText(QString());
        progressBar->setFormat(QApplication::translate("TestSampleWidget", "%p%", nullptr));
        lblSubTitle->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TestSampleWidget: public Ui_TestSampleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTSAMPLEWIDGET_H
