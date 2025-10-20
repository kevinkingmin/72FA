/********************************************************************************
** Form generated from reading UI file 'ProcessData.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESSDATA_H
#define UI_PROCESSDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProcessData
{
public:
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Cancel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lblStepType;
    QComboBox *cmbStepType;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *ProcessData)
    {
        if (ProcessData->objectName().isEmpty())
            ProcessData->setObjectName(QString::fromUtf8("ProcessData"));
        ProcessData->resize(699, 510);
        ProcessData->setMinimumSize(QSize(0, 0));
        ProcessData->setMaximumSize(QSize(10000, 10000));
        pushButton_Save = new QPushButton(ProcessData);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));
        pushButton_Save->setGeometry(QRect(436, 440, 101, 31));
        pushButton_Cancel = new QPushButton(ProcessData);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(560, 440, 101, 31));
        layoutWidget = new QWidget(ProcessData);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 651, 401));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 15);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 15, -1, -1);
        lblStepType = new QLabel(layoutWidget);
        lblStepType->setObjectName(QString::fromUtf8("lblStepType"));
        lblStepType->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(lblStepType);

        cmbStepType = new QComboBox(layoutWidget);
        cmbStepType->setObjectName(QString::fromUtf8("cmbStepType"));
        cmbStepType->setMinimumSize(QSize(150, 0));

        horizontalLayout->addWidget(cmbStepType);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(15);
        gridLayout->setVerticalSpacing(25);
        gridLayout->setContentsMargins(30, 20, 30, -1);

        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout->setStretch(1, 1);

        retranslateUi(ProcessData);

        QMetaObject::connectSlotsByName(ProcessData);
    } // setupUi

    void retranslateUi(QDialog *ProcessData)
    {
        ProcessData->setWindowTitle(QApplication::translate("ProcessData", "processStep", nullptr));
        pushButton_Save->setText(QApplication::translate("ProcessData", "\344\277\235\345\255\230", nullptr));
        pushButton_Save->setProperty("btnStyle", QVariant(QApplication::translate("ProcessData", "normalBtnRed", nullptr)));
        pushButton_Cancel->setText(QApplication::translate("ProcessData", "\345\217\226\346\266\210", nullptr));
        pushButton_Cancel->setProperty("btnStyle", QVariant(QApplication::translate("ProcessData", "normalBtnGray", nullptr)));
        lblStepType->setText(QApplication::translate("ProcessData", "\351\200\211\346\213\251\346\226\260\345\242\236\346\255\245\351\252\244\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProcessData: public Ui_ProcessData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESSDATA_H
