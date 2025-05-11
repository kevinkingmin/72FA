/********************************************************************************
** Form generated from reading UI file 'PrepareReagentWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREPAREREAGENTWIDGET_H
#define UI_PREPAREREAGENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrepareReagentWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QFrame *vLayoutFrame;
    QLabel *label_4;
    QPushButton *pushButtonSmall;
    QGroupBox *groupBox;
    QLabel *lblHint;
    QPushButton *btnIrrigate;
    QLabel *label_11;
    QLabel *label_12;
    QPushButton *btnWash;
    QPushButton *btnFill;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnFlash;
    QPushButton *btnReady;
    QPushButton *btnDelay;
    QSpacerItem *horizontalSpacer_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *hLayPump;
    QSpacerItem *horizontalSpacer;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *chk_1;
    QCheckBox *chk_2;
    QCheckBox *chk_3;
    QCheckBox *chk_4;
    QCheckBox *chk_5;
    QCheckBox *chk_6;
    QCheckBox *chk_7;
    QCheckBox *chk_8;
    QCheckBox *chk_9;
    QSpacerItem *horizontalSpacer_6;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_13;
    QLabel *label_14;
    QPushButton *btnFill_2;
    QCheckBox *cb_all;

    void setupUi(QWidget *PrepareReagentWidget)
    {
        if (PrepareReagentWidget->objectName().isEmpty())
            PrepareReagentWidget->setObjectName(QString::fromUtf8("PrepareReagentWidget"));
        PrepareReagentWidget->resize(1780, 718);
        verticalLayout_3 = new QVBoxLayout(PrepareReagentWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        vLayoutFrame = new QFrame(PrepareReagentWidget);
        vLayoutFrame->setObjectName(QString::fromUtf8("vLayoutFrame"));
        label_4 = new QLabel(vLayoutFrame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(480, 0, 1021, 20));
        label_4->setAlignment(Qt::AlignCenter);
        pushButtonSmall = new QPushButton(vLayoutFrame);
        pushButtonSmall->setObjectName(QString::fromUtf8("pushButtonSmall"));
        pushButtonSmall->setGeometry(QRect(0, -40, 128, 128));
        pushButtonSmall->setMinimumSize(QSize(128, 128));
        groupBox = new QGroupBox(vLayoutFrame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(1525, 50, 301, 591));
        lblHint = new QLabel(groupBox);
        lblHint->setObjectName(QString::fromUtf8("lblHint"));
        lblHint->setGeometry(QRect(20, 110, 261, 111));
        lblHint->setStyleSheet(QString::fromUtf8("font-size:24px;\n"
"font-weight:bold;"));
        lblHint->setAlignment(Qt::AlignCenter);
        btnIrrigate = new QPushButton(groupBox);
        btnIrrigate->setObjectName(QString::fromUtf8("btnIrrigate"));
        btnIrrigate->setEnabled(true);
        btnIrrigate->setGeometry(QRect(80, 230, 135, 135));
        btnIrrigate->setMinimumSize(QSize(135, 135));
        btnIrrigate->setMaximumSize(QSize(135, 16777215));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 60, 331, 20));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 30, 281, 41));
        label_12->setAlignment(Qt::AlignCenter);
        btnWash = new QPushButton(groupBox);
        btnWash->setObjectName(QString::fromUtf8("btnWash"));
        btnWash->setGeometry(QRect(40, 400, 231, 35));
        btnWash->setMinimumSize(QSize(0, 35));
        btnFill = new QPushButton(groupBox);
        btnFill->setObjectName(QString::fromUtf8("btnFill"));
        btnFill->setGeometry(QRect(40, 450, 231, 35));
        btnFill->setMinimumSize(QSize(0, 35));
        groupBox_2 = new QGroupBox(vLayoutFrame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(70, 50, 1451, 591));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 90, 1431, 71));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(1100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        btnFlash = new QPushButton(layoutWidget);
        btnFlash->setObjectName(QString::fromUtf8("btnFlash"));
        btnFlash->setMinimumSize(QSize(64, 64));

        horizontalLayout->addWidget(btnFlash);

        btnReady = new QPushButton(layoutWidget);
        btnReady->setObjectName(QString::fromUtf8("btnReady"));
        btnReady->setMinimumSize(QSize(64, 64));

        horizontalLayout->addWidget(btnReady);

        btnDelay = new QPushButton(layoutWidget);
        btnDelay->setObjectName(QString::fromUtf8("btnDelay"));
        btnDelay->setMinimumSize(QSize(64, 64));

        horizontalLayout->addWidget(btnDelay);

        horizontalSpacer_3 = new QSpacerItem(90, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 230, 1431, 251));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        hLayPump = new QHBoxLayout();
        hLayPump->setSpacing(2);
        hLayPump->setObjectName(QString::fromUtf8("hLayPump"));
        hLayPump->setContentsMargins(10, 10, 10, 10);

        horizontalLayout_2->addLayout(hLayPump);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        layoutWidget_2 = new QWidget(groupBox_2);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 480, 1431, 32));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(190, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        chk_1 = new QCheckBox(layoutWidget_2);
        chk_1->setObjectName(QString::fromUtf8("chk_1"));
        chk_1->setLayoutDirection(Qt::LeftToRight);
        chk_1->setChecked(false);

        horizontalLayout_4->addWidget(chk_1);

        chk_2 = new QCheckBox(layoutWidget_2);
        chk_2->setObjectName(QString::fromUtf8("chk_2"));
        chk_2->setChecked(false);

        horizontalLayout_4->addWidget(chk_2);

        chk_3 = new QCheckBox(layoutWidget_2);
        chk_3->setObjectName(QString::fromUtf8("chk_3"));

        horizontalLayout_4->addWidget(chk_3);

        chk_4 = new QCheckBox(layoutWidget_2);
        chk_4->setObjectName(QString::fromUtf8("chk_4"));

        horizontalLayout_4->addWidget(chk_4);

        chk_5 = new QCheckBox(layoutWidget_2);
        chk_5->setObjectName(QString::fromUtf8("chk_5"));

        horizontalLayout_4->addWidget(chk_5);

        chk_6 = new QCheckBox(layoutWidget_2);
        chk_6->setObjectName(QString::fromUtf8("chk_6"));

        horizontalLayout_4->addWidget(chk_6);

        chk_7 = new QCheckBox(layoutWidget_2);
        chk_7->setObjectName(QString::fromUtf8("chk_7"));

        horizontalLayout_4->addWidget(chk_7);

        chk_8 = new QCheckBox(layoutWidget_2);
        chk_8->setObjectName(QString::fromUtf8("chk_8"));

        horizontalLayout_4->addWidget(chk_8);

        chk_9 = new QCheckBox(layoutWidget_2);
        chk_9->setObjectName(QString::fromUtf8("chk_9"));

        horizontalLayout_4->addWidget(chk_9);

        horizontalSpacer_6 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        layoutWidget2 = new QWidget(groupBox_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 180, 1431, 51));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_8 = new QSpacerItem(210, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);

        label = new QLabel(layoutWidget2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label);

        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_2);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);

        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_3->addWidget(label_8);

        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_3->addWidget(label_9);

        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_3->addWidget(label_10);

        horizontalSpacer_9 = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(0, 60, 1451, 20));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(40, 30, 641, 41));
        btnFill_2 = new QPushButton(groupBox_2);
        btnFill_2->setObjectName(QString::fromUtf8("btnFill_2"));
        btnFill_2->setGeometry(QRect(680, 540, 101, 35));
        btnFill_2->setMinimumSize(QSize(0, 35));
        cb_all = new QCheckBox(vLayoutFrame);
        cb_all->setObjectName(QString::fromUtf8("cb_all"));
        cb_all->setGeometry(QRect(230, 30, 47, 16));

        verticalLayout_3->addWidget(vLayoutFrame);


        retranslateUi(PrepareReagentWidget);

        QMetaObject::connectSlotsByName(PrepareReagentWidget);
    } // setupUi

    void retranslateUi(QWidget *PrepareReagentWidget)
    {
        PrepareReagentWidget->setWindowTitle(QApplication::translate("PrepareReagentWidget", "Form", nullptr));
        label_4->setText(QApplication::translate("PrepareReagentWidget", "\345\210\206\351\205\215\346\210\226\345\273\266\350\277\237\357\274\214\346\257\217\344\270\252\345\267\262\347\224\250\350\257\225\345\211\202", nullptr));
        pushButtonSmall->setText(QString());
        pushButtonSmall->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentWidget", "btnReagentStyle", nullptr)));
        groupBox->setTitle(QString());
        lblHint->setText(QApplication::translate("PrepareReagentWidget", "\347\201\214\346\263\250\347\263\273\347\273\237\346\266\262\344\275\223\357\274\201", nullptr));
        btnIrrigate->setText(QString());
        btnIrrigate->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentWidget", "iconOnlyStyle", nullptr)));
        label_11->setText(QApplication::translate("PrepareReagentWidget", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
        label_12->setText(QApplication::translate("PrepareReagentWidget", "\347\263\273\347\273\237\346\266\262\347\201\214\346\263\250", nullptr));
        btnWash->setText(QApplication::translate("PrepareReagentWidget", "\347\263\273\347\273\237\346\266\262\347\256\241\350\267\257\345\205\205\347\201\214", nullptr));
        btnWash->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentWidget", "normalBtnRed", nullptr)));
        btnFill->setText(QApplication::translate("PrepareReagentWidget", "\350\267\263\350\277\207\345\205\205\347\201\214", nullptr));
        btnFill->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentWidget", "normalBtnGray", nullptr)));
        groupBox_2->setTitle(QString());
        btnFlash->setText(QString());
        btnFlash->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentWidget", "btnReagentStyle", nullptr)));
        btnReady->setText(QString());
        btnReady->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentWidget", "btnReagentStyle", nullptr)));
        btnDelay->setText(QString());
        btnDelay->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentWidget", "btnReagentStyle", nullptr)));
        chk_1->setText(QApplication::translate("PrepareReagentWidget", "1\344\275\215\347\275\256", nullptr));
        chk_2->setText(QApplication::translate("PrepareReagentWidget", "2\344\275\215\347\275\256", nullptr));
        chk_3->setText(QApplication::translate("PrepareReagentWidget", "3\344\275\215\347\275\256", nullptr));
        chk_4->setText(QApplication::translate("PrepareReagentWidget", "4\344\275\215\347\275\256", nullptr));
        chk_5->setText(QApplication::translate("PrepareReagentWidget", "5\344\275\215\347\275\256", nullptr));
        chk_6->setText(QApplication::translate("PrepareReagentWidget", "6\344\275\215\347\275\256", nullptr));
        chk_7->setText(QApplication::translate("PrepareReagentWidget", "7\344\275\215\347\275\256", nullptr));
        chk_8->setText(QApplication::translate("PrepareReagentWidget", "8\344\275\215\347\275\256", nullptr));
        chk_9->setText(QApplication::translate("PrepareReagentWidget", "9\344\275\215\347\275\256", nullptr));
        label->setText(QApplication::translate("PrepareReagentWidget", "\346\200\273\347\224\250\351\207\217\357\274\232", nullptr));
        label_2->setText(QApplication::translate("PrepareReagentWidget", "\346\200\273\347\224\250\351\207\217\357\274\232", nullptr));
        label_3->setText(QApplication::translate("PrepareReagentWidget", "\346\200\273\347\224\250\351\207\217\357\274\232", nullptr));
        label_5->setText(QApplication::translate("PrepareReagentWidget", "\346\200\273\347\224\250\351\207\217\357\274\232", nullptr));
        label_6->setText(QApplication::translate("PrepareReagentWidget", "\346\200\273\347\224\250\351\207\217\357\274\232", nullptr));
        label_7->setText(QApplication::translate("PrepareReagentWidget", "\346\200\273\347\224\250\351\207\217\357\274\232", nullptr));
        label_8->setText(QApplication::translate("PrepareReagentWidget", "\346\200\273\347\224\250\351\207\217\357\274\232", nullptr));
        label_9->setText(QApplication::translate("PrepareReagentWidget", "\346\200\273\347\224\250\351\207\217\357\274\232", nullptr));
        label_10->setText(QApplication::translate("PrepareReagentWidget", "\346\200\273\347\224\250\351\207\217\357\274\232", nullptr));
        label_13->setText(QApplication::translate("PrepareReagentWidget", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200"
                        "\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
        label_14->setText(QApplication::translate("PrepareReagentWidget", "\346\243\200\346\265\213\345\211\215\345\207\206\345\244\207", nullptr));
        btnFill_2->setText(QApplication::translate("PrepareReagentWidget", "\345\205\250\351\200\211", nullptr));
        btnFill_2->setProperty("btnStyle", QVariant(QApplication::translate("PrepareReagentWidget", "normalBtnpink", nullptr)));
        cb_all->setText(QApplication::translate("PrepareReagentWidget", "\345\205\250\351\200\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PrepareReagentWidget: public Ui_PrepareReagentWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREPAREREAGENTWIDGET_H
