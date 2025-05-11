/********************************************************************************
** Form generated from reading UI file 'ResultDetail.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTDETAIL_H
#define UI_RESULTDETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResultDetail
{
public:

    void setupUi(QWidget *ResultDetail)
    {
        if (ResultDetail->objectName().isEmpty())
            ResultDetail->setObjectName(QString::fromUtf8("ResultDetail"));
        ResultDetail->resize(400, 300);

        retranslateUi(ResultDetail);

        QMetaObject::connectSlotsByName(ResultDetail);
    } // setupUi

    void retranslateUi(QWidget *ResultDetail)
    {
        ResultDetail->setWindowTitle(QApplication::translate("ResultDetail", "ResultDetail", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResultDetail: public Ui_ResultDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTDETAIL_H
