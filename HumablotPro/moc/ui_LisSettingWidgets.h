/********************************************************************************
** Form generated from reading UI file 'LisSettingWidgets.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISSETTINGWIDGETS_H
#define UI_LISSETTINGWIDGETS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LisSettingWidgets
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *vertical_1;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBoxStartLis;
    QCheckBox *checkBoxAutoConnete;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *lineEditIP;
    QLabel *label;
    QComboBox *comboBoxPorocolType;
    QLineEdit *lineEditPort;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonSave;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButtonSend_5;
    QPushButton *pushButtonSend_2;
    QPushButton *pushButtonSend_3;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButtonSend_4;
    QPushButton *pushButtonSend;
    QTextEdit *textEditDisplayWidget;

    void setupUi(QWidget *LisSettingWidgets)
    {
        if (LisSettingWidgets->objectName().isEmpty())
            LisSettingWidgets->setObjectName(QString::fromUtf8("LisSettingWidgets"));
        LisSettingWidgets->resize(1135, 665);
        verticalLayout_5 = new QVBoxLayout(LisSettingWidgets);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(50, 30, 50, 30);
        vertical_1 = new QGroupBox(LisSettingWidgets);
        vertical_1->setObjectName(QString::fromUtf8("vertical_1"));
        verticalLayout_2 = new QVBoxLayout(vertical_1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(9, 9, 9, 9);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        label_4 = new QLabel(vertical_1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        line = new QFrame(vertical_1);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(35);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 30, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBoxStartLis = new QCheckBox(vertical_1);
        checkBoxStartLis->setObjectName(QString::fromUtf8("checkBoxStartLis"));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font.setPointSize(12);
        checkBoxStartLis->setFont(font);
        checkBoxStartLis->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(checkBoxStartLis);

        checkBoxAutoConnete = new QCheckBox(vertical_1);
        checkBoxAutoConnete->setObjectName(QString::fromUtf8("checkBoxAutoConnete"));
        checkBoxAutoConnete->setFont(font);

        horizontalLayout->addWidget(checkBoxAutoConnete);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(20, 10, 20, 10);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        groupBox = new QGroupBox(vertical_1);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFont(font);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(20, 12, 20, 12);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEditIP = new QLineEdit(groupBox);
        lineEditIP->setObjectName(QString::fromUtf8("lineEditIP"));

        gridLayout->addWidget(lineEditIP, 1, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBoxPorocolType = new QComboBox(groupBox);
        comboBoxPorocolType->addItem(QString());
        comboBoxPorocolType->setObjectName(QString::fromUtf8("comboBoxPorocolType"));

        gridLayout->addWidget(comboBoxPorocolType, 2, 1, 1, 1);

        lineEditPort = new QLineEdit(groupBox);
        lineEditPort->setObjectName(QString::fromUtf8("lineEditPort"));

        gridLayout->addWidget(lineEditPort, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);


        horizontalLayout_3->addWidget(groupBox);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, 25, -1);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pushButtonSave = new QPushButton(vertical_1);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setFont(font);

        horizontalLayout_2->addWidget(pushButtonSave);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_4->addWidget(vertical_1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        horizontalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(20, 20, 55, 20);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(10, 5, 10, 5);
        label_6 = new QLabel(LisSettingWidgets);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        pushButtonSend_5 = new QPushButton(LisSettingWidgets);
        pushButtonSend_5->setObjectName(QString::fromUtf8("pushButtonSend_5"));
        pushButtonSend_5->setFont(font);

        horizontalLayout_4->addWidget(pushButtonSend_5);

        pushButtonSend_2 = new QPushButton(LisSettingWidgets);
        pushButtonSend_2->setObjectName(QString::fromUtf8("pushButtonSend_2"));
        pushButtonSend_2->setFont(font);

        horizontalLayout_4->addWidget(pushButtonSend_2);

        pushButtonSend_3 = new QPushButton(LisSettingWidgets);
        pushButtonSend_3->setObjectName(QString::fromUtf8("pushButtonSend_3"));
        pushButtonSend_3->setFont(font);

        horizontalLayout_4->addWidget(pushButtonSend_3);


        verticalLayout_3->addLayout(horizontalLayout_4);

        textEdit = new QTextEdit(LisSettingWidgets);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout_3->addWidget(textEdit);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(10, 5, 10, 5);
        label_7 = new QLabel(LisSettingWidgets);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_5->addWidget(label_7);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        pushButtonSend_4 = new QPushButton(LisSettingWidgets);
        pushButtonSend_4->setObjectName(QString::fromUtf8("pushButtonSend_4"));
        pushButtonSend_4->setFont(font);

        horizontalLayout_5->addWidget(pushButtonSend_4);

        pushButtonSend = new QPushButton(LisSettingWidgets);
        pushButtonSend->setObjectName(QString::fromUtf8("pushButtonSend"));
        pushButtonSend->setFont(font);

        horizontalLayout_5->addWidget(pushButtonSend);


        verticalLayout_3->addLayout(horizontalLayout_5);

        textEditDisplayWidget = new QTextEdit(LisSettingWidgets);
        textEditDisplayWidget->setObjectName(QString::fromUtf8("textEditDisplayWidget"));

        verticalLayout_3->addWidget(textEditDisplayWidget);


        horizontalLayout_6->addLayout(verticalLayout_3);

        horizontalLayout_6->setStretch(0, 2);
        horizontalLayout_6->setStretch(1, 3);

        verticalLayout_5->addLayout(horizontalLayout_6);


        retranslateUi(LisSettingWidgets);

        QMetaObject::connectSlotsByName(LisSettingWidgets);
    } // setupUi

    void retranslateUi(QWidget *LisSettingWidgets)
    {
        LisSettingWidgets->setWindowTitle(QApplication::translate("LisSettingWidgets", "LisSettingWidgets", nullptr));
        label_4->setText(QApplication::translate("LisSettingWidgets", "TextLabel", nullptr));
        checkBoxStartLis->setText(QApplication::translate("LisSettingWidgets", "\345\220\257\345\212\250LIS", nullptr));
        checkBoxAutoConnete->setText(QApplication::translate("LisSettingWidgets", "\345\256\236\346\227\266\346\250\241\345\274\217", nullptr));
        groupBox->setTitle(QString());
        label_3->setText(QApplication::translate("LisSettingWidgets", "\351\200\232\344\277\241\345\215\217\350\256\256\357\274\232", nullptr));
        lineEditIP->setText(QApplication::translate("LisSettingWidgets", "192.168.20.83", nullptr));
        label->setText(QApplication::translate("LisSettingWidgets", "\347\253\257    \345\217\243\357\274\232", nullptr));
        comboBoxPorocolType->setItemText(0, QApplication::translate("LisSettingWidgets", "HL7", nullptr));

        lineEditPort->setText(QApplication::translate("LisSettingWidgets", "9997", nullptr));
        label_2->setText(QApplication::translate("LisSettingWidgets", "IP \345\234\260 \345\235\200\357\274\232", nullptr));
        pushButtonSave->setText(QApplication::translate("LisSettingWidgets", "\344\277\235\345\255\230", nullptr));
        pushButtonSave->setProperty("btnStyle", QVariant(QApplication::translate("LisSettingWidgets", "normalBtnRed", nullptr)));
        label_6->setText(QApplication::translate("LisSettingWidgets", "\345\217\221\351\200\201\346\225\260\346\215\256", nullptr));
        pushButtonSend_5->setText(QApplication::translate("LisSettingWidgets", "\346\270\205\347\251\272", nullptr));
        pushButtonSend_5->setProperty("btnStyle", QVariant(QApplication::translate("LisSettingWidgets", "normalBtnRed", nullptr)));
        pushButtonSend_2->setText(QApplication::translate("LisSettingWidgets", "\346\265\213\350\257\225\347\273\223\346\236\234", nullptr));
        pushButtonSend_2->setProperty("btnStyle", QVariant(QApplication::translate("LisSettingWidgets", "normalBtnRed", nullptr)));
        pushButtonSend_3->setText(QApplication::translate("LisSettingWidgets", "\350\257\267\346\261\202\346\240\267\346\234\254", nullptr));
        pushButtonSend_3->setProperty("btnStyle", QVariant(QApplication::translate("LisSettingWidgets", "normalBtnRed", nullptr)));
        label_7->setText(QApplication::translate("LisSettingWidgets", "\346\216\245\346\224\266\346\225\260\346\215\256", nullptr));
        pushButtonSend_4->setText(QApplication::translate("LisSettingWidgets", "\346\270\205\347\251\272", nullptr));
        pushButtonSend_4->setProperty("btnStyle", QVariant(QApplication::translate("LisSettingWidgets", "normalBtnRed", nullptr)));
        pushButtonSend->setText(QApplication::translate("LisSettingWidgets", "\345\220\257\345\212\250", nullptr));
        pushButtonSend->setProperty("btnStyle", QVariant(QApplication::translate("LisSettingWidgets", "normalBtnRed", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class LisSettingWidgets: public Ui_LisSettingWidgets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISSETTINGWIDGETS_H
