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
    QLineEdit *lineEdit_small_wash;
    QLabel *label_IsSkimp;
    QCheckBox *checkBox_IsSpecificReagent;
    QCheckBox *checkBox_IsSkimp;
    QLabel *label_SmallWash;
    QLabel *label_ReagentName;
    QCheckBox *checkBox_IsNoDrip;
    QLabel *label_PaperName;
    QComboBox *comboBox_PaperName;
    QLineEdit *txtCompany;
    QLabel *label_Company;
    QLabel *label_SpecificReagent;
    QLabel *label_IsNoDrip;
    QComboBox *comboBox_ReagentName;
    QLineEdit *lineEdit_big_wash;
    QLabel *label_BigWash;
    QLabel *label_pumpNo;
    QComboBox *comboBox_pumpNo;

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
        lineEdit_small_wash = new QLineEdit(gridLayoutWidget);
        lineEdit_small_wash->setObjectName(QString::fromUtf8("lineEdit_small_wash"));

        gridLayout->addWidget(lineEdit_small_wash, 8, 1, 1, 1);

        label_IsSkimp = new QLabel(gridLayoutWidget);
        label_IsSkimp->setObjectName(QString::fromUtf8("label_IsSkimp"));
        label_IsSkimp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_IsSkimp, 5, 0, 1, 1);

        checkBox_IsSpecificReagent = new QCheckBox(gridLayoutWidget);
        checkBox_IsSpecificReagent->setObjectName(QString::fromUtf8("checkBox_IsSpecificReagent"));

        gridLayout->addWidget(checkBox_IsSpecificReagent, 0, 1, 1, 1);

        checkBox_IsSkimp = new QCheckBox(gridLayoutWidget);
        checkBox_IsSkimp->setObjectName(QString::fromUtf8("checkBox_IsSkimp"));

        gridLayout->addWidget(checkBox_IsSkimp, 5, 1, 1, 1);

        label_SmallWash = new QLabel(gridLayoutWidget);
        label_SmallWash->setObjectName(QString::fromUtf8("label_SmallWash"));
        label_SmallWash->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_SmallWash, 8, 0, 1, 1);

        label_ReagentName = new QLabel(gridLayoutWidget);
        label_ReagentName->setObjectName(QString::fromUtf8("label_ReagentName"));
        label_ReagentName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_ReagentName, 2, 0, 1, 1);

        checkBox_IsNoDrip = new QCheckBox(gridLayoutWidget);
        checkBox_IsNoDrip->setObjectName(QString::fromUtf8("checkBox_IsNoDrip"));

        gridLayout->addWidget(checkBox_IsNoDrip, 4, 1, 1, 1);

        label_PaperName = new QLabel(gridLayoutWidget);
        label_PaperName->setObjectName(QString::fromUtf8("label_PaperName"));
        label_PaperName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_PaperName, 1, 0, 1, 1);

        comboBox_PaperName = new QComboBox(gridLayoutWidget);
        comboBox_PaperName->setObjectName(QString::fromUtf8("comboBox_PaperName"));

        gridLayout->addWidget(comboBox_PaperName, 1, 1, 1, 1);

        txtCompany = new QLineEdit(gridLayoutWidget);
        txtCompany->setObjectName(QString::fromUtf8("txtCompany"));
        txtCompany->setEnabled(false);

        gridLayout->addWidget(txtCompany, 6, 1, 1, 1);

        label_Company = new QLabel(gridLayoutWidget);
        label_Company->setObjectName(QString::fromUtf8("label_Company"));
        label_Company->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_Company, 6, 0, 1, 1);

        label_SpecificReagent = new QLabel(gridLayoutWidget);
        label_SpecificReagent->setObjectName(QString::fromUtf8("label_SpecificReagent"));
        label_SpecificReagent->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_SpecificReagent, 0, 0, 1, 1);

        label_IsNoDrip = new QLabel(gridLayoutWidget);
        label_IsNoDrip->setObjectName(QString::fromUtf8("label_IsNoDrip"));
        label_IsNoDrip->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_IsNoDrip, 4, 0, 1, 1);

        comboBox_ReagentName = new QComboBox(gridLayoutWidget);
        comboBox_ReagentName->setObjectName(QString::fromUtf8("comboBox_ReagentName"));

        gridLayout->addWidget(comboBox_ReagentName, 2, 1, 1, 1);

        lineEdit_big_wash = new QLineEdit(gridLayoutWidget);
        lineEdit_big_wash->setObjectName(QString::fromUtf8("lineEdit_big_wash"));

        gridLayout->addWidget(lineEdit_big_wash, 7, 1, 1, 1);

        label_BigWash = new QLabel(gridLayoutWidget);
        label_BigWash->setObjectName(QString::fromUtf8("label_BigWash"));
        label_BigWash->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_BigWash, 7, 0, 1, 1);

        label_pumpNo = new QLabel(gridLayoutWidget);
        label_pumpNo->setObjectName(QString::fromUtf8("label_pumpNo"));
        label_pumpNo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_pumpNo, 3, 0, 1, 1);

        comboBox_pumpNo = new QComboBox(gridLayoutWidget);
        comboBox_pumpNo->setObjectName(QString::fromUtf8("comboBox_pumpNo"));

        gridLayout->addWidget(comboBox_pumpNo, 3, 1, 1, 1);


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
        label_IsSkimp->setText(QApplication::translate("AddReagent", "\350\257\225\345\211\202\345\233\236\346\265\201\357\274\232", nullptr));
        checkBox_IsSpecificReagent->setText(QString());
        checkBox_IsSkimp->setText(QString());
        label_SmallWash->setText(QApplication::translate("AddReagent", "\345\260\217\345\205\205\347\201\214\351\207\217\357\274\232", nullptr));
        label_ReagentName->setText(QApplication::translate("AddReagent", "\350\257\225\345\211\202\345\220\215\347\247\260\357\274\232", nullptr));
        checkBox_IsNoDrip->setText(QString());
        label_PaperName->setText(QApplication::translate("AddReagent", "\345\205\263\350\201\224\350\206\234\346\235\241\357\274\232", nullptr));
        label_Company->setText(QApplication::translate("AddReagent", "\345\205\263\350\201\224\345\216\202\345\256\266\357\274\232", nullptr));
        label_SpecificReagent->setText(QApplication::translate("AddReagent", "\344\270\223\347\224\250\350\257\225\345\211\202\357\274\232", nullptr));
        label_IsNoDrip->setText(QApplication::translate("AddReagent", "\351\230\262\346\214\202\346\273\264\357\274\232", nullptr));
        label_BigWash->setText(QApplication::translate("AddReagent", "\345\244\247\345\205\205\347\201\214\351\207\217\357\274\232", nullptr));
        label_pumpNo->setText(QApplication::translate("AddReagent", "\346\263\265\345\217\267\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddReagent: public Ui_AddReagent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDREAGENT_H
