/********************************************************************************
** Form generated from reading UI file 'InitWidgets.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITWIDGETS_H
#define UI_INITWIDGETS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InitWidgets
{
public:
    QPushButton *pushButtonInit;

    void setupUi(QWidget *InitWidgets)
    {
        if (InitWidgets->objectName().isEmpty())
            InitWidgets->setObjectName(QString::fromUtf8("InitWidgets"));
        InitWidgets->resize(1050, 544);
        pushButtonInit = new QPushButton(InitWidgets);
        pushButtonInit->setObjectName(QString::fromUtf8("pushButtonInit"));
        pushButtonInit->setGeometry(QRect(430, 270, 181, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(12);
        pushButtonInit->setFont(font);

        retranslateUi(InitWidgets);

        QMetaObject::connectSlotsByName(InitWidgets);
    } // setupUi

    void retranslateUi(QWidget *InitWidgets)
    {
        InitWidgets->setWindowTitle(QApplication::translate("InitWidgets", "InitWidgets", nullptr));
        pushButtonInit->setText(QApplication::translate("InitWidgets", "\346\250\241\346\213\237\345\210\235\345\247\213\345\214\226\345\256\214\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InitWidgets: public Ui_InitWidgets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITWIDGETS_H
