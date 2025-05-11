/********************************************************************************
** Form generated from reading UI file 'AddCompany.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCOMPANY_H
#define UI_ADDCOMPANY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddCompany
{
public:
    QLabel *label;
    QLineEdit *lineEdit_Name;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Cancel;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *AddCompany)
    {
        if (AddCompany->objectName().isEmpty())
            AddCompany->setObjectName(QString::fromUtf8("AddCompany"));
        AddCompany->resize(639, 299);
        label = new QLabel(AddCompany);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 150, 101, 21));
        lineEdit_Name = new QLineEdit(AddCompany);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));
        lineEdit_Name->setGeometry(QRect(170, 140, 411, 31));
        pushButton_Save = new QPushButton(AddCompany);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));
        pushButton_Save->setGeometry(QRect(490, 220, 75, 31));
        pushButton_Cancel = new QPushButton(AddCompany);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(370, 220, 75, 31));
        label_2 = new QLabel(AddCompany);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 30, 201, 31));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(AddCompany);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 60, 641, 16));

        retranslateUi(AddCompany);

        QMetaObject::connectSlotsByName(AddCompany);
    } // setupUi

    void retranslateUi(QWidget *AddCompany)
    {
        AddCompany->setWindowTitle(QApplication::translate("AddCompany", "AddCompany", nullptr));
        label->setText(QApplication::translate("AddCompany", "\345\205\254\345\217\270\345\220\215\347\247\260\357\274\232", nullptr));
        pushButton_Save->setText(QApplication::translate("AddCompany", "\344\277\235\345\255\230", nullptr));
        pushButton_Save->setProperty("btnStyle", QVariant(QApplication::translate("AddCompany", "normalBtnRed", nullptr)));
        pushButton_Cancel->setText(QApplication::translate("AddCompany", "\345\217\226\346\266\210", nullptr));
        pushButton_Cancel->setProperty("btnStyle", QVariant(QApplication::translate("AddCompany", "normalBtnGray", nullptr)));
        label_2->setText(QApplication::translate("AddCompany", "\346\267\273\345\212\240\350\206\234\346\235\241\345\216\202\345\256\266", nullptr));
        label_3->setText(QApplication::translate("AddCompany", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddCompany: public Ui_AddCompany {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCOMPANY_H
