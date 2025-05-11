/********************************************************************************
** Form generated from reading UI file 'RepeatSetDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPEATSETDIALOG_H
#define UI_REPEATSETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RepeatSetDialog
{
public:
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonClose;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *lblSampleNo;
    QTableView *ItemTable;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnSave;
    QPushButton *buttonCancel;
    QLabel *label;

    void setupUi(QDialog *RepeatSetDialog)
    {
        if (RepeatSetDialog->objectName().isEmpty())
            RepeatSetDialog->setObjectName(QString::fromUtf8("RepeatSetDialog"));
        RepeatSetDialog->resize(550, 475);
        RepeatSetDialog->setModal(false);
        widgetTop = new QWidget(RepeatSetDialog);
        widgetTop->setObjectName(QString::fromUtf8("widgetTop"));
        widgetTop->setGeometry(QRect(6, 10, 540, 30));
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

        widget = new QWidget(RepeatSetDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 60, 531, 411));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, 2, 10, 10);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(12);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 5, -1, 5);
        lblSampleNo = new QLabel(widget);
        lblSampleNo->setObjectName(QString::fromUtf8("lblSampleNo"));

        horizontalLayout->addWidget(lblSampleNo);


        verticalLayout_3->addLayout(horizontalLayout);

        ItemTable = new QTableView(widget);
        ItemTable->setObjectName(QString::fromUtf8("ItemTable"));

        verticalLayout_3->addWidget(ItemTable);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
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

        label = new QLabel(RepeatSetDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1, 39, 548, 16));
        QWidget::setTabOrder(btnSave, pushButtonClose);

        retranslateUi(RepeatSetDialog);

        QMetaObject::connectSlotsByName(RepeatSetDialog);
    } // setupUi

    void retranslateUi(QDialog *RepeatSetDialog)
    {
        RepeatSetDialog->setWindowTitle(QApplication::translate("RepeatSetDialog", "\350\206\234\345\274\217", nullptr));
        RepeatSetDialog->setProperty("dialogStyle", QVariant(QApplication::translate("RepeatSetDialog", "BGStyle", nullptr)));
        label_2->setText(QApplication::translate("RepeatSetDialog", "\345\244\215\345\255\224\350\256\276\347\275\256", nullptr));
        label_2->setProperty("lblStyle", QVariant(QApplication::translate("RepeatSetDialog", "lblNormal", nullptr)));
        pushButtonClose->setText(QString());
        lblSampleNo->setText(QApplication::translate("RepeatSetDialog", "\346\240\267\346\234\254\347\274\226\345\217\267:", nullptr));
        btnSave->setText(QApplication::translate("RepeatSetDialog", "\345\256\214\346\210\220", nullptr));
        btnSave->setProperty("btnStyle", QVariant(QApplication::translate("RepeatSetDialog", "normalBtn", nullptr)));
        buttonCancel->setText(QApplication::translate("RepeatSetDialog", "\345\217\226\346\266\210", nullptr));
        buttonCancel->setProperty("btnStyle", QVariant(QApplication::translate("RepeatSetDialog", "normalBtn", nullptr)));
        label->setText(QApplication::translate("RepeatSetDialog", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RepeatSetDialog: public Ui_RepeatSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPEATSETDIALOG_H
