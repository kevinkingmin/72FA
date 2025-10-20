/********************************************************************************
** Form generated from reading UI file 'AlarmDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALARMDIALOG_H
#define UI_ALARMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlarmDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonClose;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSave;
    QPushButton *buttonCancel;

    void setupUi(QDialog *AlarmDialog)
    {
        if (AlarmDialog->objectName().isEmpty())
            AlarmDialog->setObjectName(QString::fromUtf8("AlarmDialog"));
        AlarmDialog->resize(887, 564);
        AlarmDialog->setModal(false);
        widget = new QWidget(AlarmDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 9, 871, 541));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widgetTop = new QWidget(widget);
        widgetTop->setObjectName(QString::fromUtf8("widgetTop"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetTop->sizePolicy().hasHeightForWidth());
        widgetTop->setSizePolicy(sizePolicy);
        widgetTop->setMinimumSize(QSize(0, 30));
        widgetTop->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_6 = new QHBoxLayout(widgetTop);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(20, 0, 20, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(widgetTop);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pushButtonClose = new QPushButton(widgetTop);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setMinimumSize(QSize(26, 26));
        pushButtonClose->setMaximumSize(QSize(26, 26));

        horizontalLayout_4->addWidget(pushButtonClose);


        horizontalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout->addWidget(widgetTop);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        plainTextEdit = new QPlainTextEdit(widget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setStyleSheet(QString::fromUtf8("border: 1px solid gray;"));
        plainTextEdit->setReadOnly(true);

        verticalLayout->addWidget(plainTextEdit);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnSave = new QPushButton(widget);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setMinimumSize(QSize(100, 35));
        btnSave->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(btnSave);

        buttonCancel = new QPushButton(widget);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setMinimumSize(QSize(100, 35));
        buttonCancel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(buttonCancel);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(verticalLayout_3);

        QWidget::setTabOrder(btnSave, pushButtonClose);

        retranslateUi(AlarmDialog);

        QMetaObject::connectSlotsByName(AlarmDialog);
    } // setupUi

    void retranslateUi(QDialog *AlarmDialog)
    {
        AlarmDialog->setWindowTitle(QApplication::translate("AlarmDialog", "\350\206\234\345\274\217", nullptr));
        AlarmDialog->setProperty("dialogStyle", QVariant(QApplication::translate("AlarmDialog", "BGStyle", nullptr)));
        label_2->setText(QApplication::translate("AlarmDialog", "\346\217\220\347\244\272", nullptr));
        label_2->setProperty("lblStyle", QVariant(QApplication::translate("AlarmDialog", "lblNormal", nullptr)));
        pushButtonClose->setText(QString());
        label->setText(QApplication::translate("AlarmDialog", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
        btnSave->setText(QApplication::translate("AlarmDialog", "\347\241\256\345\256\232", nullptr));
        btnSave->setProperty("btnStyle", QVariant(QApplication::translate("AlarmDialog", "normalBtn", nullptr)));
        buttonCancel->setText(QApplication::translate("AlarmDialog", "\345\217\226\346\266\210", nullptr));
        buttonCancel->setProperty("btnStyle", QVariant(QApplication::translate("AlarmDialog", "normalBtn", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class AlarmDialog: public Ui_AlarmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALARMDIALOG_H
