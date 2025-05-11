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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddReagent
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_Name;
    QCheckBox *checkBox_IsNoDrip;
    QCheckBox *checkBox_IsSkimp;
    QCheckBox *checkBox_IsNeedPrepare;
    QLineEdit *lineEdit_PumpNo;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Cancel;
    QLabel *label_6;
    QComboBox *comboBox_TestPaper;
    QLabel *label_7;
    QLineEdit *lineEdit_big_wash;
    QLabel *label_8;
    QLineEdit *lineEdit_small_wash;

    void setupUi(QWidget *AddReagent)
    {
        if (AddReagent->objectName().isEmpty())
            AddReagent->setObjectName(QString::fromUtf8("AddReagent"));
        AddReagent->resize(588, 557);
        label = new QLabel(AddReagent);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 51, 121, 31));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(AddReagent);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 101, 121, 31));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(AddReagent);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 151, 121, 31));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(AddReagent);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 201, 121, 31));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(AddReagent);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 251, 121, 31));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_Name = new QLineEdit(AddReagent);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));
        lineEdit_Name->setGeometry(QRect(180, 50, 311, 31));
        checkBox_IsNoDrip = new QCheckBox(AddReagent);
        checkBox_IsNoDrip->setObjectName(QString::fromUtf8("checkBox_IsNoDrip"));
        checkBox_IsNoDrip->setGeometry(QRect(180, 111, 71, 16));
        checkBox_IsSkimp = new QCheckBox(AddReagent);
        checkBox_IsSkimp->setObjectName(QString::fromUtf8("checkBox_IsSkimp"));
        checkBox_IsSkimp->setGeometry(QRect(180, 161, 71, 16));
        checkBox_IsNeedPrepare = new QCheckBox(AddReagent);
        checkBox_IsNeedPrepare->setObjectName(QString::fromUtf8("checkBox_IsNeedPrepare"));
        checkBox_IsNeedPrepare->setGeometry(QRect(180, 211, 71, 16));
        lineEdit_PumpNo = new QLineEdit(AddReagent);
        lineEdit_PumpNo->setObjectName(QString::fromUtf8("lineEdit_PumpNo"));
        lineEdit_PumpNo->setGeometry(QRect(180, 250, 311, 31));
        pushButton_Save = new QPushButton(AddReagent);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));
        pushButton_Save->setGeometry(QRect(270, 490, 75, 31));
        pushButton_Cancel = new QPushButton(AddReagent);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(420, 490, 75, 31));
        label_6 = new QLabel(AddReagent);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 310, 121, 31));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_TestPaper = new QComboBox(AddReagent);
        comboBox_TestPaper->setObjectName(QString::fromUtf8("comboBox_TestPaper"));
        comboBox_TestPaper->setGeometry(QRect(180, 310, 311, 31));
        label_7 = new QLabel(AddReagent);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 370, 121, 31));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_big_wash = new QLineEdit(AddReagent);
        lineEdit_big_wash->setObjectName(QString::fromUtf8("lineEdit_big_wash"));
        lineEdit_big_wash->setGeometry(QRect(180, 370, 311, 31));
        label_8 = new QLabel(AddReagent);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 430, 121, 31));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_small_wash = new QLineEdit(AddReagent);
        lineEdit_small_wash->setObjectName(QString::fromUtf8("lineEdit_small_wash"));
        lineEdit_small_wash->setGeometry(QRect(180, 430, 311, 31));

        retranslateUi(AddReagent);

        QMetaObject::connectSlotsByName(AddReagent);
    } // setupUi

    void retranslateUi(QWidget *AddReagent)
    {
        AddReagent->setWindowTitle(QApplication::translate("AddReagent", "AddReagent", nullptr));
        label->setText(QApplication::translate("AddReagent", "\350\257\225\345\211\202\345\220\215\347\247\260\357\274\232", nullptr));
        label_2->setText(QApplication::translate("AddReagent", "\351\230\262\346\214\202\346\273\264\357\274\232", nullptr));
        label_3->setText(QApplication::translate("AddReagent", "\350\257\225\345\211\202\345\233\236\346\265\201\357\274\232", nullptr));
        label_4->setText(QApplication::translate("AddReagent", "\350\277\220\350\241\214\345\211\215\347\201\214\350\243\205\357\274\232", nullptr));
        label_5->setText(QApplication::translate("AddReagent", "\346\263\265\347\232\204\345\210\206\351\205\215\357\274\232", nullptr));
        checkBox_IsNoDrip->setText(QString());
        checkBox_IsSkimp->setText(QString());
        checkBox_IsNeedPrepare->setText(QString());
        pushButton_Save->setText(QApplication::translate("AddReagent", "\344\277\235\345\255\230", nullptr));
        pushButton_Save->setProperty("btnStyle", QVariant(QApplication::translate("AddReagent", "normalBtnRed", nullptr)));
        pushButton_Cancel->setText(QApplication::translate("AddReagent", "\345\217\226\346\266\210", nullptr));
        pushButton_Cancel->setProperty("btnStyle", QVariant(QApplication::translate("AddReagent", "normalBtnGray", nullptr)));
        label_6->setText(QApplication::translate("AddReagent", "\345\205\263\350\201\224\350\206\234\346\235\241\357\274\232", nullptr));
        label_7->setText(QApplication::translate("AddReagent", "\345\244\247\345\205\205\347\201\214\351\207\217\357\274\232", nullptr));
        label_8->setText(QApplication::translate("AddReagent", "\345\260\217\345\205\205\347\201\214\351\207\217\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddReagent: public Ui_AddReagent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDREAGENT_H
