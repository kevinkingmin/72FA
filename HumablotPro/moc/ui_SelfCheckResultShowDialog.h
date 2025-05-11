/********************************************************************************
** Form generated from reading UI file 'SelfCheckResultShowDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELFCHECKRESULTSHOWDIALOG_H
#define UI_SELFCHECKRESULTSHOWDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelfCheckResultShowDialogClass
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_12;

    void setupUi(QDialog *SelfCheckResultShowDialogClass)
    {
        if (SelfCheckResultShowDialogClass->objectName().isEmpty())
            SelfCheckResultShowDialogClass->setObjectName(QString::fromUtf8("SelfCheckResultShowDialogClass"));
        SelfCheckResultShowDialogClass->resize(1053, 411);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../favicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        SelfCheckResultShowDialogClass->setWindowIcon(icon);
        pushButton = new QPushButton(SelfCheckResultShowDialogClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(500, 340, 91, 31));
        label = new QLabel(SelfCheckResultShowDialogClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(320, 20, 431, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(24);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(SelfCheckResultShowDialogClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 60, 1051, 16));
        layoutWidget = new QWidget(SelfCheckResultShowDialogClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 120, 971, 181));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        checkBox = new QCheckBox(layoutWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setEnabled(false);

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        checkBox_2 = new QCheckBox(layoutWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setEnabled(false);

        gridLayout->addWidget(checkBox_2, 0, 1, 1, 1);

        checkBox_3 = new QCheckBox(layoutWidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setEnabled(false);

        gridLayout->addWidget(checkBox_3, 0, 2, 1, 1);

        checkBox_4 = new QCheckBox(layoutWidget);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setEnabled(false);

        gridLayout->addWidget(checkBox_4, 1, 0, 1, 1);

        checkBox_5 = new QCheckBox(layoutWidget);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setEnabled(false);

        gridLayout->addWidget(checkBox_5, 1, 1, 1, 1);

        checkBox_6 = new QCheckBox(layoutWidget);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setEnabled(false);

        gridLayout->addWidget(checkBox_6, 1, 2, 1, 1);

        checkBox_7 = new QCheckBox(layoutWidget);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setEnabled(false);

        gridLayout->addWidget(checkBox_7, 2, 0, 1, 1);

        checkBox_8 = new QCheckBox(layoutWidget);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setEnabled(false);

        gridLayout->addWidget(checkBox_8, 2, 1, 1, 1);

        checkBox_9 = new QCheckBox(layoutWidget);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
        checkBox_9->setEnabled(false);

        gridLayout->addWidget(checkBox_9, 2, 2, 1, 1);

        checkBox_10 = new QCheckBox(layoutWidget);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));
        checkBox_10->setEnabled(false);

        gridLayout->addWidget(checkBox_10, 3, 0, 1, 1);

        checkBox_11 = new QCheckBox(layoutWidget);
        checkBox_11->setObjectName(QString::fromUtf8("checkBox_11"));
        checkBox_11->setEnabled(false);

        gridLayout->addWidget(checkBox_11, 3, 1, 1, 1);

        checkBox_12 = new QCheckBox(layoutWidget);
        checkBox_12->setObjectName(QString::fromUtf8("checkBox_12"));
        checkBox_12->setEnabled(false);

        gridLayout->addWidget(checkBox_12, 3, 2, 1, 1);


        retranslateUi(SelfCheckResultShowDialogClass);

        QMetaObject::connectSlotsByName(SelfCheckResultShowDialogClass);
    } // setupUi

    void retranslateUi(QDialog *SelfCheckResultShowDialogClass)
    {
        SelfCheckResultShowDialogClass->setWindowTitle(QApplication::translate("SelfCheckResultShowDialogClass", "\350\207\252\346\243\200\347\273\223\346\236\234\346\230\276\347\244\272", nullptr));
        pushButton->setText(QApplication::translate("SelfCheckResultShowDialogClass", "\345\256\214\346\210\220 ", nullptr));
        pushButton->setProperty("btnStyle", QVariant(QApplication::translate("SelfCheckResultShowDialogClass", "normalBtnRed", nullptr)));
        label->setText(QApplication::translate("SelfCheckResultShowDialogClass", "\350\207\252\346\243\200\347\273\223\346\236\234\346\230\276\347\244\272", nullptr));
        label_2->setText(QApplication::translate("SelfCheckResultShowDialogClass", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200"
                        "\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
        checkBox->setText(QApplication::translate("SelfCheckResultShowDialogClass", "CheckBox", nullptr));
        checkBox_2->setText(QApplication::translate("SelfCheckResultShowDialogClass", "CheckBox", nullptr));
        checkBox_3->setText(QApplication::translate("SelfCheckResultShowDialogClass", "CheckBox", nullptr));
        checkBox_4->setText(QApplication::translate("SelfCheckResultShowDialogClass", "CheckBox", nullptr));
        checkBox_5->setText(QApplication::translate("SelfCheckResultShowDialogClass", "CheckBox", nullptr));
        checkBox_6->setText(QApplication::translate("SelfCheckResultShowDialogClass", "CheckBox", nullptr));
        checkBox_7->setText(QApplication::translate("SelfCheckResultShowDialogClass", "CheckBox", nullptr));
        checkBox_8->setText(QApplication::translate("SelfCheckResultShowDialogClass", "CheckBox", nullptr));
        checkBox_9->setText(QApplication::translate("SelfCheckResultShowDialogClass", "CheckBox", nullptr));
        checkBox_10->setText(QApplication::translate("SelfCheckResultShowDialogClass", "CheckBox", nullptr));
        checkBox_11->setText(QApplication::translate("SelfCheckResultShowDialogClass", "CheckBox", nullptr));
        checkBox_12->setText(QApplication::translate("SelfCheckResultShowDialogClass", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelfCheckResultShowDialogClass: public Ui_SelfCheckResultShowDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELFCHECKRESULTSHOWDIALOG_H
