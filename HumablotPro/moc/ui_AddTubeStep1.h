/********************************************************************************
** Form generated from reading UI file 'AddTubeStep1.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTUBESTEP1_H
#define UI_ADDTUBESTEP1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddTubeStep1
{
public:
    QLabel *label_Picture;
    QPushButton *pushButton_Cancel;
    QCheckBox *checkBox_Control;
    QLabel *label;
    QLineEdit *lineEdit_Inner;
    QPushButton *pushButton_Next;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *lineEdit_Name;
    QLabel *label_5;
    QPushButton *pushButton_Back;

    void setupUi(QWidget *AddTubeStep1)
    {
        if (AddTubeStep1->objectName().isEmpty())
            AddTubeStep1->setObjectName(QString::fromUtf8("AddTubeStep1"));
        AddTubeStep1->resize(1119, 714);
        label_Picture = new QLabel(AddTubeStep1);
        label_Picture->setObjectName(QString::fromUtf8("label_Picture"));
        label_Picture->setGeometry(QRect(220, 150, 71, 241));
        pushButton_Cancel = new QPushButton(AddTubeStep1);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(1010, 20, 75, 41));
        checkBox_Control = new QCheckBox(AddTubeStep1);
        checkBox_Control->setObjectName(QString::fromUtf8("checkBox_Control"));
        checkBox_Control->setGeometry(QRect(470, 230, 101, 31));
        label = new QLabel(AddTubeStep1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(370, 160, 101, 31));
        lineEdit_Inner = new QLineEdit(AddTubeStep1);
        lineEdit_Inner->setObjectName(QString::fromUtf8("lineEdit_Inner"));
        lineEdit_Inner->setGeometry(QRect(460, 300, 113, 31));
        pushButton_Next = new QPushButton(AddTubeStep1);
        pushButton_Next->setObjectName(QString::fromUtf8("pushButton_Next"));
        pushButton_Next->setGeometry(QRect(910, 20, 75, 41));
        label_2 = new QLabel(AddTubeStep1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(370, 230, 101, 31));
        label_4 = new QLabel(AddTubeStep1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(590, 300, 101, 31));
        label_3 = new QLabel(AddTubeStep1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(370, 300, 101, 31));
        lineEdit_Name = new QLineEdit(AddTubeStep1);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));
        lineEdit_Name->setGeometry(QRect(460, 160, 113, 31));
        label_5 = new QLabel(AddTubeStep1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(150, 20, 671, 41));
        QFont font;
        font.setPointSize(18);
        label_5->setFont(font);
        pushButton_Back = new QPushButton(AddTubeStep1);
        pushButton_Back->setObjectName(QString::fromUtf8("pushButton_Back"));
        pushButton_Back->setGeometry(QRect(30, 20, 75, 41));

        retranslateUi(AddTubeStep1);

        QMetaObject::connectSlotsByName(AddTubeStep1);
    } // setupUi

    void retranslateUi(QWidget *AddTubeStep1)
    {
        AddTubeStep1->setWindowTitle(QApplication::translate("AddTubeStep1", "\346\240\267\346\234\254\347\256\241\350\256\276\347\275\256", nullptr));
        label_Picture->setText(QApplication::translate("AddTubeStep1", "TextLabel", nullptr));
        pushButton_Cancel->setText(QApplication::translate("AddTubeStep1", "\345\217\226\346\266\210", nullptr));
        checkBox_Control->setText(QString());
        label->setText(QApplication::translate("AddTubeStep1", "\345\220\215\347\247\260\357\274\232", nullptr));
        pushButton_Next->setText(QApplication::translate("AddTubeStep1", "\344\270\213\344\270\200\346\255\245", nullptr));
        label_2->setText(QApplication::translate("AddTubeStep1", "\350\264\250\346\216\247\347\256\241\357\274\232", nullptr));
        label_4->setText(QApplication::translate("AddTubeStep1", "mm", nullptr));
        label_3->setText(QApplication::translate("AddTubeStep1", "\350\257\225\347\256\241\345\206\205\345\276\204\357\274\232", nullptr));
        label_5->setText(QApplication::translate("AddTubeStep1", "\350\257\225\347\256\241\347\261\273\345\236\213", nullptr));
        pushButton_Back->setText(QApplication::translate("AddTubeStep1", "\345\220\216\351\200\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddTubeStep1: public Ui_AddTubeStep1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTUBESTEP1_H
