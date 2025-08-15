/********************************************************************************
** Form generated from reading UI file 'AddReagent.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDREAGENT_H
#define UI_ADDREAGENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddReagent
{
public:
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Cancel;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *lineEdit_big_wash;
    QCheckBox *checkBox_IsNeedPrepare;
    QLabel *label_5;
    QLineEdit *lineEdit_Name;
    QLineEdit *lineEdit_PumpNo;
    QLabel *label_6;
    QCheckBox *checkBox_IsSkimp;
    QLabel *label;
    QCheckBox *checkBox_IsNoDrip;
    QLabel *label_4;
    QLabel *label_8;
    QLineEdit *lineEdit_small_wash;
    QLineEdit *txtCompany;

    void setupUi(QDialog *AddReagent)
    {
        if (AddReagent->objectName().isEmpty())
            AddReagent->setObjectName(QString::fromUtf8("AddReagent"));
        AddReagent->resize(588, 581);
        AddReagent->setMinimumSize(QSize(588, 581));
        AddReagent->setMaximumSize(QSize(588, 581));
        pushButton_Save = new QPushButton(AddReagent);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));
        pushButton_Save->setGeometry(QRect(306, 510, 101, 31));
        pushButton_Cancel = new QPushButton(AddReagent);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(430, 510, 101, 31));
        gridLayoutWidget = new QWidget(AddReagent);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(29, 9, 511, 471));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(35);
        gridLayout->setContentsMargins(30, 0, 55, 0);
        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_big_wash = new QLineEdit(gridLayoutWidget);
        lineEdit_big_wash->setObjectName(QString::fromUtf8("lineEdit_big_wash"));

        gridLayout->addWidget(lineEdit_big_wash, 6, 1, 1, 1);

        checkBox_IsNeedPrepare = new QCheckBox(gridLayoutWidget);
        checkBox_IsNeedPrepare->setObjectName(QString::fromUtf8("checkBox_IsNeedPrepare"));

        gridLayout->addWidget(checkBox_IsNeedPrepare, 3, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        lineEdit_Name = new QLineEdit(gridLayoutWidget);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));

        gridLayout->addWidget(lineEdit_Name, 0, 1, 1, 1);

        lineEdit_PumpNo = new QLineEdit(gridLayoutWidget);
        lineEdit_PumpNo->setObjectName(QString::fromUtf8("lineEdit_PumpNo"));

        gridLayout->addWidget(lineEdit_PumpNo, 4, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        checkBox_IsSkimp = new QCheckBox(gridLayoutWidget);
        checkBox_IsSkimp->setObjectName(QString::fromUtf8("checkBox_IsSkimp"));

        gridLayout->addWidget(checkBox_IsSkimp, 2, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        checkBox_IsNoDrip = new QCheckBox(gridLayoutWidget);
        checkBox_IsNoDrip->setObjectName(QString::fromUtf8("checkBox_IsNoDrip"));

        gridLayout->addWidget(checkBox_IsNoDrip, 1, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 7, 0, 1, 1);

        lineEdit_small_wash = new QLineEdit(gridLayoutWidget);
        lineEdit_small_wash->setObjectName(QString::fromUtf8("lineEdit_small_wash"));

        gridLayout->addWidget(lineEdit_small_wash, 7, 1, 1, 1);

        txtCompany = new QLineEdit(gridLayoutWidget);
        txtCompany->setObjectName(QString::fromUtf8("txtCompany"));
        txtCompany->setEnabled(false);

        gridLayout->addWidget(txtCompany, 5, 1, 1, 1);


        retranslateUi(AddReagent);

        QMetaObject::connectSlotsByName(AddReagent);
    } // setupUi

    void retranslateUi(QDialog *AddReagent)
    {
        AddReagent->setWindowTitle(QApplication::translate("AddReagent", "AddReagent", nullptr));
        pushButton_Save->setText(QApplication::translate("AddReagent", "\344\277\235\345\255\230", nullptr));
        pushButton_Save->setProperty("btnStyle", QVariant(QApplication::translate("AddReagent", "normalBtnRed", nullptr)));
        pushButton_Cancel->setText(QApplication::translate("AddReagent", "\345\217\226\346\266\210", nullptr));
        pushButton_Cancel->setProperty("btnStyle", QVariant(QApplication::translate("AddReagent", "normalBtnGray", nullptr)));
        label_7->setText(QApplication::translate("AddReagent", "\345\244\247\345\205\205\347\201\214\351\207\217\357\274\232", nullptr));
        label_3->setText(QApplication::translate("AddReagent", "\350\257\225\345\211\202\345\233\236\346\265\201\357\274\232", nullptr));
        label_2->setText(QApplication::translate("AddReagent", "\351\230\262\346\214\202\346\273\264\357\274\232", nullptr));
        checkBox_IsNeedPrepare->setText(QString());
        label_5->setText(QApplication::translate("AddReagent", "\346\263\265\347\232\204\345\210\206\351\205\215\357\274\232", nullptr));
        label_6->setText(QApplication::translate("AddReagent", "\345\205\263\350\201\224\345\216\202\345\256\266\357\274\232", nullptr));
        checkBox_IsSkimp->setText(QString());
        label->setText(QApplication::translate("AddReagent", "\350\257\225\345\211\202\345\220\215\347\247\260\357\274\232", nullptr));
        checkBox_IsNoDrip->setText(QString());
        label_4->setText(QApplication::translate("AddReagent", "\350\277\220\350\241\214\345\211\215\347\201\214\350\243\205\357\274\232", nullptr));
        label_8->setText(QApplication::translate("AddReagent", "\345\260\217\345\205\205\347\201\214\351\207\217\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddReagent: public Ui_AddReagent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDREAGENT_H
