/********************************************************************************
** Form generated from reading UI file 'SampleWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAMPLEWIDGET_H
#define UI_SAMPLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SampleWidget
{
public:
    QWidget *sampleTopWidget;
    QGridLayout *gridLayout_4;
    QWidget *widget;
    QGridLayout *gridLayout;
    QStackedWidget *sampleStackPage;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QPushButton *btnReTest;
    QPushButton *btnBatchAdd;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnReQuestLisAll;
    QPushButton *btnNext;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnSaveAdd;
    QLabel *lblSpace;
    QPushButton *btnPre;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnRequestLis;
    QPushButton *btnIncubation;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnDeleteAll;
    QPushButton *btnDelete;
    QLabel *lblTitle;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SampleWidget)
    {
        if (SampleWidget->objectName().isEmpty())
            SampleWidget->setObjectName(QString::fromUtf8("SampleWidget"));
        SampleWidget->resize(1005, 473);
        sampleTopWidget = new QWidget(SampleWidget);
        sampleTopWidget->setObjectName(QString::fromUtf8("sampleTopWidget"));
        sampleTopWidget->setEnabled(true);
        sampleTopWidget->setGeometry(QRect(0, 0, 901, 331));
        sampleTopWidget->setLayoutDirection(Qt::LeftToRight);
        sampleTopWidget->setAutoFillBackground(true);
        gridLayout_4 = new QGridLayout(sampleTopWidget);
        gridLayout_4->setSpacing(2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(2, 2, 6, 2);
        widget = new QWidget(sampleTopWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 6, 2);
        sampleStackPage = new QStackedWidget(widget);
        sampleStackPage->setObjectName(QString::fromUtf8("sampleStackPage"));

        gridLayout->addWidget(sampleStackPage, 0, 0, 1, 1);


        gridLayout_4->addWidget(widget, 1, 0, 1, 1);

        widget_2 = new QWidget(sampleTopWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(20, 3, 4, 2);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, -1, 8, -1);
        btnReTest = new QPushButton(widget_2);
        btnReTest->setObjectName(QString::fromUtf8("btnReTest"));
        btnReTest->setMinimumSize(QSize(20, 48));

        gridLayout_2->addWidget(btnReTest, 0, 14, 1, 1);

        btnBatchAdd = new QPushButton(widget_2);
        btnBatchAdd->setObjectName(QString::fromUtf8("btnBatchAdd"));
        btnBatchAdd->setMinimumSize(QSize(80, 48));

        gridLayout_2->addWidget(btnBatchAdd, 0, 5, 1, 1);

        btnCancel = new QPushButton(widget_2);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setMinimumSize(QSize(20, 48));

        gridLayout_2->addWidget(btnCancel, 0, 16, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 7, 1, 1);

        btnReQuestLisAll = new QPushButton(widget_2);
        btnReQuestLisAll->setObjectName(QString::fromUtf8("btnReQuestLisAll"));
        btnReQuestLisAll->setMinimumSize(QSize(20, 48));

        gridLayout_2->addWidget(btnReQuestLisAll, 0, 12, 1, 1);

        btnNext = new QPushButton(widget_2);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));
        btnNext->setMinimumSize(QSize(20, 48));

        gridLayout_2->addWidget(btnNext, 0, 18, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 10, 1, 1);

        btnSaveAdd = new QPushButton(widget_2);
        btnSaveAdd->setObjectName(QString::fromUtf8("btnSaveAdd"));
        btnSaveAdd->setMinimumSize(QSize(20, 48));

        gridLayout_2->addWidget(btnSaveAdd, 0, 6, 1, 1);

        lblSpace = new QLabel(widget_2);
        lblSpace->setObjectName(QString::fromUtf8("lblSpace"));
        lblSpace->setMinimumSize(QSize(20, 0));

        gridLayout_2->addWidget(lblSpace, 0, 2, 1, 1);

        btnPre = new QPushButton(widget_2);
        btnPre->setObjectName(QString::fromUtf8("btnPre"));
        btnPre->setMinimumSize(QSize(0, 48));

        gridLayout_2->addWidget(btnPre, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 4, 1, 1);

        btnRequestLis = new QPushButton(widget_2);
        btnRequestLis->setObjectName(QString::fromUtf8("btnRequestLis"));
        btnRequestLis->setMinimumSize(QSize(20, 48));

        gridLayout_2->addWidget(btnRequestLis, 0, 11, 1, 1);

        btnIncubation = new QPushButton(widget_2);
        btnIncubation->setObjectName(QString::fromUtf8("btnIncubation"));
        btnIncubation->setMinimumSize(QSize(20, 48));

        gridLayout_2->addWidget(btnIncubation, 0, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(120, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 17, 1, 1);

        btnDeleteAll = new QPushButton(widget_2);
        btnDeleteAll->setObjectName(QString::fromUtf8("btnDeleteAll"));
        btnDeleteAll->setMinimumSize(QSize(80, 48));

        gridLayout_2->addWidget(btnDeleteAll, 0, 8, 1, 1);

        btnDelete = new QPushButton(widget_2);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));
        btnDelete->setMinimumSize(QSize(20, 48));

        gridLayout_2->addWidget(btnDelete, 0, 9, 1, 1);

        lblTitle = new QLabel(widget_2);
        lblTitle->setObjectName(QString::fromUtf8("lblTitle"));
        lblTitle->setMinimumSize(QSize(10, 0));
        lblTitle->setStyleSheet(QString::fromUtf8("font-size:32px;\n"
"font-weight:bold;"));

        gridLayout_2->addWidget(lblTitle, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 13, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        gridLayout_4->addWidget(widget_2, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_4->addItem(verticalSpacer, 2, 0, 1, 1);


        retranslateUi(SampleWidget);

        sampleStackPage->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(SampleWidget);
    } // setupUi

    void retranslateUi(QWidget *SampleWidget)
    {
        SampleWidget->setWindowTitle(QApplication::translate("SampleWidget", "Form", nullptr));
        sampleTopWidget->setProperty("widgetStyle", QVariant(QApplication::translate("SampleWidget", "BGStyle", nullptr)));
        btnReTest->setText(QApplication::translate("SampleWidget", "      \345\244\215\345\255\224", nullptr));
        btnReTest->setProperty("btnStyle", QVariant(QApplication::translate("SampleWidget", "normalBtn_Mut_Hole", nullptr)));
        btnBatchAdd->setText(QApplication::translate("SampleWidget", "\346\211\271\351\207\217\346\267\273\345\212\240", nullptr));
        btnBatchAdd->setProperty("btnStyle", QVariant(QApplication::translate("SampleWidget", "normalBtn", nullptr)));
        btnCancel->setText(QApplication::translate("SampleWidget", "\350\277\224\345\233\236\346\240\267\346\234\254", nullptr));
        btnCancel->setProperty("btnStyle", QVariant(QApplication::translate("SampleWidget", "normalBtn", nullptr)));
        btnReQuestLisAll->setText(QApplication::translate("SampleWidget", " LIS\346\211\271\351\207\217\350\216\267\345\217\226", nullptr));
        btnReQuestLisAll->setProperty("btnStyle", QVariant(QApplication::translate("SampleWidget", "normalBtn", nullptr)));
        btnNext->setText(QApplication::translate("SampleWidget", "\344\270\213\344\270\200\346\255\245", nullptr));
        btnNext->setProperty("btnStyle", QVariant(QApplication::translate("SampleWidget", "normalBtnRed", nullptr)));
        btnSaveAdd->setText(QApplication::translate("SampleWidget", "      \344\277\235\345\255\230", nullptr));
        btnSaveAdd->setProperty("btnStyle", QVariant(QApplication::translate("SampleWidget", "normalBtn_Save", nullptr)));
        lblSpace->setText(QString());
        btnPre->setText(QApplication::translate("SampleWidget", "\344\270\212\344\270\200\346\255\245", nullptr));
        btnPre->setProperty("btnStyle", QVariant(QApplication::translate("SampleWidget", "normalBtnRed", nullptr)));
        btnRequestLis->setText(QApplication::translate("SampleWidget", "      LIS\350\216\267\345\217\226", nullptr));
        btnRequestLis->setProperty("btnStyle", QVariant(QApplication::translate("SampleWidget", "normalBtn_request_lis", nullptr)));
        btnIncubation->setText(QApplication::translate("SampleWidget", "\346\211\213\345\212\250\345\255\265\350\202\262", nullptr));
        btnIncubation->setProperty("btnStyle", QVariant(QApplication::translate("SampleWidget", "normalBtn", nullptr)));
        btnDeleteAll->setText(QApplication::translate("SampleWidget", "\345\210\240\351\231\244\346\211\200\346\234\211", nullptr));
        btnDeleteAll->setProperty("btnStyle", QVariant(QApplication::translate("SampleWidget", "normalBtn_Delete", nullptr)));
        btnDelete->setText(QApplication::translate("SampleWidget", "     \345\210\240\351\231\244", nullptr));
        btnDelete->setProperty("btnStyle", QVariant(QApplication::translate("SampleWidget", "normalBtn_Delete", nullptr)));
        lblTitle->setText(QApplication::translate("SampleWidget", "t", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SampleWidget: public Ui_SampleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAMPLEWIDGET_H
