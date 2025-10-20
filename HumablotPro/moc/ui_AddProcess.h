/********************************************************************************
** Form generated from reading UI file 'AddProcess.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPROCESS_H
#define UI_ADDPROCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddProcess
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QLineEdit *lineEdit_Name;
    QSpacerItem *horizontalSpacer_4;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Cancel;
    QSpacerItem *horizontalSpacer_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QFrame *line;

    void setupUi(QDialog *AddProcess)
    {
        if (AddProcess->objectName().isEmpty())
            AddProcess->setObjectName(QString::fromUtf8("AddProcess"));
        AddProcess->resize(588, 338);
        AddProcess->setMinimumSize(QSize(0, 0));
        AddProcess->setMaximumSize(QSize(100000, 100000));
        horizontalLayoutWidget = new QWidget(AddProcess);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 59, 571, 91));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        lineEdit_Name = new QLineEdit(horizontalLayoutWidget);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));
        lineEdit_Name->setMinimumSize(QSize(255, 0));

        horizontalLayout->addWidget(lineEdit_Name);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        horizontalLayoutWidget_2 = new QWidget(AddProcess);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 150, 571, 80));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_Save = new QPushButton(horizontalLayoutWidget_2);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));

        horizontalLayout_2->addWidget(pushButton_Save);

        pushButton_Cancel = new QPushButton(horizontalLayoutWidget_2);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));

        horizontalLayout_2->addWidget(pushButton_Cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayoutWidget = new QWidget(AddProcess);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 20, 571, 31));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        retranslateUi(AddProcess);

        QMetaObject::connectSlotsByName(AddProcess);
    } // setupUi

    void retranslateUi(QDialog *AddProcess)
    {
        AddProcess->setWindowTitle(QApplication::translate("AddProcess", "AddProcessName", nullptr));
        label->setText(QApplication::translate("AddProcess", "\346\265\201\347\250\213\345\220\215\347\247\260\357\274\232", nullptr));
        pushButton_Save->setText(QApplication::translate("AddProcess", "\344\277\235\345\255\230", nullptr));
        pushButton_Save->setProperty("btnStyle", QVariant(QApplication::translate("AddProcess", "normalBtnRed", nullptr)));
        pushButton_Cancel->setText(QApplication::translate("AddProcess", "\345\217\226\346\266\210", nullptr));
        pushButton_Cancel->setProperty("btnStyle", QVariant(QApplication::translate("AddProcess", "normalBtnGray", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class AddProcess: public Ui_AddProcess {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPROCESS_H
