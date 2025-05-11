/********************************************************************************
** Form generated from reading UI file 'AddTubeStep3.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTUBESTEP3_H
#define UI_ADDTUBESTEP3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddTubeStep3
{
public:
    QPushButton *pushButton_Cancel;
    QPushButton *pushButton_Back;
    QPushButton *pushButton_Next;
    QLabel *label_Picture;
    QLabel *label_5;
    QPushButton *button_add_more;
    QPushButton *button_add_little;
    QPushButton *button_minus_little;
    QPushButton *pushButton_2;
    QPushButton *pushButton_1;
    QPushButton *button_minus_more;
    QPushButton *pushButton_3;

    void setupUi(QWidget *AddTubeStep3)
    {
        if (AddTubeStep3->objectName().isEmpty())
            AddTubeStep3->setObjectName(QString::fromUtf8("AddTubeStep3"));
        AddTubeStep3->resize(1115, 718);
        pushButton_Cancel = new QPushButton(AddTubeStep3);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(1010, 20, 75, 41));
        pushButton_Back = new QPushButton(AddTubeStep3);
        pushButton_Back->setObjectName(QString::fromUtf8("pushButton_Back"));
        pushButton_Back->setGeometry(QRect(30, 20, 75, 41));
        pushButton_Next = new QPushButton(AddTubeStep3);
        pushButton_Next->setObjectName(QString::fromUtf8("pushButton_Next"));
        pushButton_Next->setGeometry(QRect(910, 20, 75, 41));
        label_Picture = new QLabel(AddTubeStep3);
        label_Picture->setObjectName(QString::fromUtf8("label_Picture"));
        label_Picture->setGeometry(QRect(220, 150, 71, 241));
        label_5 = new QLabel(AddTubeStep3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(150, 20, 671, 41));
        QFont font;
        font.setPointSize(18);
        label_5->setFont(font);
        button_add_more = new QPushButton(AddTubeStep3);
        button_add_more->setObjectName(QString::fromUtf8("button_add_more"));
        button_add_more->setGeometry(QRect(460, 140, 75, 51));
        button_add_little = new QPushButton(AddTubeStep3);
        button_add_little->setObjectName(QString::fromUtf8("button_add_little"));
        button_add_little->setGeometry(QRect(460, 190, 75, 51));
        button_minus_little = new QPushButton(AddTubeStep3);
        button_minus_little->setObjectName(QString::fromUtf8("button_minus_little"));
        button_minus_little->setGeometry(QRect(460, 290, 75, 51));
        pushButton_2 = new QPushButton(AddTubeStep3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(540, 240, 75, 51));
        pushButton_1 = new QPushButton(AddTubeStep3);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setGeometry(QRect(380, 240, 75, 51));
        button_minus_more = new QPushButton(AddTubeStep3);
        button_minus_more->setObjectName(QString::fromUtf8("button_minus_more"));
        button_minus_more->setGeometry(QRect(460, 340, 75, 51));
        pushButton_3 = new QPushButton(AddTubeStep3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(540, 340, 75, 51));

        retranslateUi(AddTubeStep3);

        QMetaObject::connectSlotsByName(AddTubeStep3);
    } // setupUi

    void retranslateUi(QWidget *AddTubeStep3)
    {
        AddTubeStep3->setWindowTitle(QApplication::translate("AddTubeStep3", "AddTubeStep3", nullptr));
        pushButton_Cancel->setText(QApplication::translate("AddTubeStep3", "\345\217\226\346\266\210", nullptr));
        pushButton_Back->setText(QApplication::translate("AddTubeStep3", "\345\220\216\351\200\200", nullptr));
        pushButton_Next->setText(QApplication::translate("AddTubeStep3", "\344\270\213\344\270\200\346\255\245", nullptr));
        label_Picture->setText(QApplication::translate("AddTubeStep3", "TextLabel", nullptr));
        label_5->setText(QApplication::translate("AddTubeStep3", "\346\240\267\346\234\254\347\256\241\344\270\212\350\276\271\347\274\230", nullptr));
        button_add_more->setText(QString());
        button_add_little->setText(QString());
        button_minus_little->setText(QString());
        pushButton_2->setText(QString());
        pushButton_1->setText(QString());
        button_minus_more->setText(QString());
        pushButton_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AddTubeStep3: public Ui_AddTubeStep3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTUBESTEP3_H
