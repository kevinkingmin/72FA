/********************************************************************************
** Form generated from reading UI file 'AddTubeStep4.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTUBESTEP4_H
#define UI_ADDTUBESTEP4_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddTubeStep4
{
public:
    QLabel *label_5;
    QPushButton *pushButton_Cancel;
    QPushButton *pushButton_Back;
    QLabel *label_Picture;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_3;
    QPushButton *pushButton_1;
    QPushButton *button_minus_little;
    QPushButton *button_add_more;
    QPushButton *button_minus_more;
    QPushButton *pushButton_2;
    QPushButton *button_add_little;

    void setupUi(QWidget *AddTubeStep4)
    {
        if (AddTubeStep4->objectName().isEmpty())
            AddTubeStep4->setObjectName(QString::fromUtf8("AddTubeStep4"));
        AddTubeStep4->resize(1096, 713);
        label_5 = new QLabel(AddTubeStep4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(140, 20, 671, 41));
        QFont font;
        font.setPointSize(18);
        label_5->setFont(font);
        pushButton_Cancel = new QPushButton(AddTubeStep4);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(1000, 20, 75, 41));
        pushButton_Back = new QPushButton(AddTubeStep4);
        pushButton_Back->setObjectName(QString::fromUtf8("pushButton_Back"));
        pushButton_Back->setGeometry(QRect(20, 20, 75, 41));
        label_Picture = new QLabel(AddTubeStep4);
        label_Picture->setObjectName(QString::fromUtf8("label_Picture"));
        label_Picture->setGeometry(QRect(210, 150, 71, 241));
        pushButton_Save = new QPushButton(AddTubeStep4);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));
        pushButton_Save->setGeometry(QRect(900, 20, 75, 41));
        pushButton_3 = new QPushButton(AddTubeStep4);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(550, 350, 75, 51));
        pushButton_1 = new QPushButton(AddTubeStep4);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setGeometry(QRect(390, 250, 75, 51));
        button_minus_little = new QPushButton(AddTubeStep4);
        button_minus_little->setObjectName(QString::fromUtf8("button_minus_little"));
        button_minus_little->setGeometry(QRect(470, 300, 75, 51));
        button_add_more = new QPushButton(AddTubeStep4);
        button_add_more->setObjectName(QString::fromUtf8("button_add_more"));
        button_add_more->setGeometry(QRect(470, 150, 75, 51));
        button_minus_more = new QPushButton(AddTubeStep4);
        button_minus_more->setObjectName(QString::fromUtf8("button_minus_more"));
        button_minus_more->setGeometry(QRect(470, 350, 75, 51));
        pushButton_2 = new QPushButton(AddTubeStep4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(550, 250, 75, 51));
        button_add_little = new QPushButton(AddTubeStep4);
        button_add_little->setObjectName(QString::fromUtf8("button_add_little"));
        button_add_little->setGeometry(QRect(470, 200, 75, 51));

        retranslateUi(AddTubeStep4);

        QMetaObject::connectSlotsByName(AddTubeStep4);
    } // setupUi

    void retranslateUi(QWidget *AddTubeStep4)
    {
        AddTubeStep4->setWindowTitle(QApplication::translate("AddTubeStep4", "AddTubeStep4", nullptr));
        label_5->setText(QApplication::translate("AddTubeStep4", "\346\240\267\346\234\254\347\256\241\344\270\213\350\276\271\347\274\230", nullptr));
        pushButton_Cancel->setText(QApplication::translate("AddTubeStep4", "\345\217\226\346\266\210", nullptr));
        pushButton_Back->setText(QApplication::translate("AddTubeStep4", "\345\220\216\351\200\200", nullptr));
        label_Picture->setText(QApplication::translate("AddTubeStep4", "TextLabel", nullptr));
        pushButton_Save->setText(QApplication::translate("AddTubeStep4", "\344\277\235\345\255\230", nullptr));
        pushButton_3->setText(QString());
        pushButton_1->setText(QString());
        button_minus_little->setText(QString());
        button_add_more->setText(QString());
        button_minus_more->setText(QString());
        pushButton_2->setText(QString());
        button_add_little->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AddTubeStep4: public Ui_AddTubeStep4 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTUBESTEP4_H
