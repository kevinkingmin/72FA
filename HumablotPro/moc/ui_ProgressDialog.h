/********************************************************************************
** Form generated from reading UI file 'ProgressDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSDIALOG_H
#define UI_PROGRESSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_ProgressDialog
{
public:
    QGroupBox *groupBox;
    QLabel *lblHead;
    QLabel *label_2;
    QProgressBar *progressBar;

    void setupUi(QDialog *ProgressDialog)
    {
        if (ProgressDialog->objectName().isEmpty())
            ProgressDialog->setObjectName(QString::fromUtf8("ProgressDialog"));
        ProgressDialog->resize(982, 653);
        ProgressDialog->setModal(false);
        groupBox = new QGroupBox(ProgressDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(250, 150, 461, 291));
        lblHead = new QLabel(groupBox);
        lblHead->setObjectName(QString::fromUtf8("lblHead"));
        lblHead->setGeometry(QRect(40, 26, 381, 41));
        lblHead->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        lblHead->setFont(font);
        lblHead->setStyleSheet(QString::fromUtf8("color:blue;\n"
"font-weight:bold;"));
        lblHead->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 60, 461, 16));
        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(40, 170, 381, 10));
        progressBar->setMinimumSize(QSize(10, 10));
        progressBar->setMaximumSize(QSize(16777215, 10));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        retranslateUi(ProgressDialog);

        QMetaObject::connectSlotsByName(ProgressDialog);
    } // setupUi

    void retranslateUi(QDialog *ProgressDialog)
    {
        ProgressDialog->setWindowTitle(QString());
        ProgressDialog->setProperty("dialogStyle", QVariant(QString()));
        groupBox->setTitle(QString());
        lblHead->setText(QString());
        label_2->setText(QApplication::translate("ProgressDialog", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProgressDialog: public Ui_ProgressDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSDIALOG_H
