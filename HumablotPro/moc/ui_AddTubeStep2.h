/********************************************************************************
** Form generated from reading UI file 'AddTubeStep2.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTUBESTEP2_H
#define UI_ADDTUBESTEP2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddTubeStep2
{
public:
    QPushButton *pushButton_Cancel;
    QPushButton *pushButton_Back;
    QPushButton *pushButton_Next;
    QLabel *label_Picture;
    QLabel *label_5;

    void setupUi(QWidget *AddTubeStep2)
    {
        if (AddTubeStep2->objectName().isEmpty())
            AddTubeStep2->setObjectName(QString::fromUtf8("AddTubeStep2"));
        AddTubeStep2->resize(1115, 723);
        pushButton_Cancel = new QPushButton(AddTubeStep2);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(1010, 20, 75, 41));
        pushButton_Back = new QPushButton(AddTubeStep2);
        pushButton_Back->setObjectName(QString::fromUtf8("pushButton_Back"));
        pushButton_Back->setGeometry(QRect(30, 20, 75, 41));
        pushButton_Next = new QPushButton(AddTubeStep2);
        pushButton_Next->setObjectName(QString::fromUtf8("pushButton_Next"));
        pushButton_Next->setGeometry(QRect(910, 20, 75, 41));
        label_Picture = new QLabel(AddTubeStep2);
        label_Picture->setObjectName(QString::fromUtf8("label_Picture"));
        label_Picture->setGeometry(QRect(40, 150, 1041, 261));
        label_5 = new QLabel(AddTubeStep2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(150, 20, 671, 41));
        QFont font;
        font.setPointSize(18);
        label_5->setFont(font);

        retranslateUi(AddTubeStep2);

        QMetaObject::connectSlotsByName(AddTubeStep2);
    } // setupUi

    void retranslateUi(QWidget *AddTubeStep2)
    {
        AddTubeStep2->setWindowTitle(QApplication::translate("AddTubeStep2", "AddTubeStep2", nullptr));
        pushButton_Cancel->setText(QApplication::translate("AddTubeStep2", "\345\217\226\346\266\210", nullptr));
        pushButton_Back->setText(QApplication::translate("AddTubeStep2", "\345\220\216\351\200\200", nullptr));
        pushButton_Next->setText(QApplication::translate("AddTubeStep2", "\344\270\213\344\270\200\346\255\245", nullptr));
        label_Picture->setText(QApplication::translate("AddTubeStep2", "TextLabel", nullptr));
        label_5->setText(QApplication::translate("AddTubeStep2", "\346\240\267\345\223\201\347\256\241\346\224\276\347\275\256\345\234\250\346\240\267\346\234\254\346\236\266\347\232\2041\345\217\267\344\275\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddTubeStep2: public Ui_AddTubeStep2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTUBESTEP2_H
