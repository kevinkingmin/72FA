/********************************************************************************
** Form generated from reading UI file 'PrepareReagentDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREPAREREAGENTDIALOG_H
#define UI_PREPAREREAGENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrepareReagentDialog
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_4;
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonClose;
    QWidget *vLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnSmall;
    QPushButton *btnBig;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnFlash;
    QPushButton *pushButtonSmall;
    QPushButton *btnReady;
    QPushButton *btnDelay;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *hLayPump;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnConfig;

    void setupUi(QDialog *PrepareReagentDialog)
    {
        if (PrepareReagentDialog->objectName().isEmpty())
            PrepareReagentDialog->setObjectName(QString::fromUtf8("PrepareReagentDialog"));
        PrepareReagentDialog->resize(988, 594);
        PrepareReagentDialog->setModal(false);
        horizontalLayout_5 = new QHBoxLayout(PrepareReagentDialog);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, -1, -1, -1);
        widgetTop = new QWidget(PrepareReagentDialog);
        widgetTop->setObjectName(QString::fromUtf8("widgetTop"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetTop->sizePolicy().hasHeightForWidth());
        widgetTop->setSizePolicy(sizePolicy);
        widgetTop->setMinimumSize(QSize(0, 30));
        widgetTop->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_6 = new QHBoxLayout(widgetTop);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(20, 0, 20, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(widgetTop);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pushButtonClose = new QPushButton(widgetTop);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setMinimumSize(QSize(26, 26));
        pushButtonClose->setMaximumSize(QSize(26, 26));

        horizontalLayout_4->addWidget(pushButtonClose);


        horizontalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout_4->addWidget(widgetTop);


        verticalLayout->addLayout(verticalLayout_4);

        vLayoutWidget = new QWidget(PrepareReagentDialog);
        vLayoutWidget->setObjectName(QString::fromUtf8("vLayoutWidget"));
        verticalLayout_2 = new QVBoxLayout(vLayoutWidget);
        verticalLayout_2->setSpacing(30);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 40, -1, 10);
        label_4 = new QLabel(vLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_6);

        btnSmall = new QPushButton(vLayoutWidget);
        btnSmall->setObjectName(QString::fromUtf8("btnSmall"));

        horizontalLayout_8->addWidget(btnSmall);

        btnBig = new QPushButton(vLayoutWidget);
        btnBig->setObjectName(QString::fromUtf8("btnBig"));

        horizontalLayout_8->addWidget(btnBig);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        btnFlash = new QPushButton(vLayoutWidget);
        btnFlash->setObjectName(QString::fromUtf8("btnFlash"));
        btnFlash->setMinimumSize(QSize(128, 128));

        horizontalLayout->addWidget(btnFlash);

        pushButtonSmall = new QPushButton(vLayoutWidget);
        pushButtonSmall->setObjectName(QString::fromUtf8("pushButtonSmall"));
        pushButtonSmall->setMinimumSize(QSize(128, 128));

        horizontalLayout->addWidget(pushButtonSmall);

        btnReady = new QPushButton(vLayoutWidget);
        btnReady->setObjectName(QString::fromUtf8("btnReady"));
        btnReady->setMinimumSize(QSize(128, 128));

        horizontalLayout->addWidget(btnReady);

        btnDelay = new QPushButton(vLayoutWidget);
        btnDelay->setObjectName(QString::fromUtf8("btnDelay"));
        btnDelay->setMinimumSize(QSize(128, 128));

        horizontalLayout->addWidget(btnDelay);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        hLayPump = new QHBoxLayout();
        hLayPump->setSpacing(2);
        hLayPump->setObjectName(QString::fromUtf8("hLayPump"));
        hLayPump->setContentsMargins(10, 10, 10, 10);

        horizontalLayout_2->addLayout(hLayPump);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout->addWidget(vLayoutWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(10, 20, 10, 10);
        btnConfig = new QPushButton(PrepareReagentDialog);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setMinimumSize(QSize(100, 35));
        btnConfig->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(btnConfig);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_5->addLayout(verticalLayout);

        QWidget::setTabOrder(btnConfig, pushButtonClose);

        retranslateUi(PrepareReagentDialog);

        QMetaObject::connectSlotsByName(PrepareReagentDialog);
    } // setupUi

    void retranslateUi(QDialog *PrepareReagentDialog)
    {
        PrepareReagentDialog->setWindowTitle(QApplication::translate("PrepareReagentDialog", "\350\206\234\345\274\217", nullptr));
        PrepareReagentDialog->setProperty("dialogStyle", QVariant(QApplication::translate("PrepareReagentDialog", "BGStyle", nullptr)));
        label_2->setText(QApplication::translate("PrepareReagentDialog", "\350\257\225\345\211\202\345\207\206\345\244\207", nullptr));
        label_2->setProperty("lblStyle", QVariant(QApplication::translate("PrepareReagentDialog", "lblNormal", nullptr)));
        pushButtonClose->setText(QString());
        vLayoutWidget->setProperty("widgetStyle", QVariant(QApplication::translate("PrepareReagentDialog", "BGStyle", nullptr)));
        label_4->setText(QApplication::translate("PrepareReagentDialog", "\345\210\206\351\205\215\346\210\226\345\273\266\350\277\237\357\274\214\346\257\217\344\270\252\345\267\262\347\224\250\350\257\225\345\211\202", nullptr));
        btnSmall->setText(QApplication::translate("PrepareReagentDialog", "\345\260\217", nullptr));
        btnBig->setText(QApplication::translate("PrepareReagentDialog", "\345\244\247", nullptr));
        btnFlash->setText(QString());
        btnFlash->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentDialog", "btnReagentStyle", nullptr)));
        pushButtonSmall->setText(QString());
        pushButtonSmall->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentDialog", "btnReagentStyle", nullptr)));
        btnReady->setText(QString());
        btnReady->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentDialog", "btnReagentStyle", nullptr)));
        btnDelay->setText(QString());
        btnDelay->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentDialog", "btnReagentStyle", nullptr)));
        btnConfig->setText(QApplication::translate("PrepareReagentDialog", "\347\241\256  \345\256\232", nullptr));
        btnConfig->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentDialog", "normalBtn", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class PrepareReagentDialog: public Ui_PrepareReagentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREPAREREAGENTDIALOG_H
