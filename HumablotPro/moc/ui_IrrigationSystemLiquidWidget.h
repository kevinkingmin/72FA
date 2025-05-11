/********************************************************************************
** Form generated from reading UI file 'IrrigationSystemLiquidWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IRRIGATIONSYSTEMLIQUIDWIDGET_H
#define UI_IRRIGATIONSYSTEMLIQUIDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IrrigationSystemLiquidWidget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblHint;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnIrrigate;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnWash;
    QPushButton *btnFill;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *IrrigationSystemLiquidWidget)
    {
        if (IrrigationSystemLiquidWidget->objectName().isEmpty())
            IrrigationSystemLiquidWidget->setObjectName(QString::fromUtf8("IrrigationSystemLiquidWidget"));
        IrrigationSystemLiquidWidget->resize(737, 497);
        IrrigationSystemLiquidWidget->setStyleSheet(QString::fromUtf8(""));
        layoutWidget = new QWidget(IrrigationSystemLiquidWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 177, 368));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 40, 0, 10);
        lblHint = new QLabel(layoutWidget);
        lblHint->setObjectName(QString::fromUtf8("lblHint"));
        lblHint->setStyleSheet(QString::fromUtf8("font-size:24px;\n"
"font-weight:bold;"));
        lblHint->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblHint);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 18, -1, -1);
        btnIrrigate = new QPushButton(layoutWidget);
        btnIrrigate->setObjectName(QString::fromUtf8("btnIrrigate"));
        btnIrrigate->setEnabled(true);
        btnIrrigate->setMinimumSize(QSize(135, 135));
        btnIrrigate->setMaximumSize(QSize(135, 16777215));

        horizontalLayout_2->addWidget(btnIrrigate);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 10, -1, 10);
        btnWash = new QPushButton(layoutWidget);
        btnWash->setObjectName(QString::fromUtf8("btnWash"));
        btnWash->setMinimumSize(QSize(0, 35));

        horizontalLayout_3->addWidget(btnWash);

        btnFill = new QPushButton(layoutWidget);
        btnFill->setObjectName(QString::fromUtf8("btnFill"));
        btnFill->setMinimumSize(QSize(0, 35));

        horizontalLayout_3->addWidget(btnFill);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(IrrigationSystemLiquidWidget);

        QMetaObject::connectSlotsByName(IrrigationSystemLiquidWidget);
    } // setupUi

    void retranslateUi(QWidget *IrrigationSystemLiquidWidget)
    {
        IrrigationSystemLiquidWidget->setWindowTitle(QApplication::translate("IrrigationSystemLiquidWidget", "Form", nullptr));
        IrrigationSystemLiquidWidget->setProperty("btnStyle", QVariant(QApplication::translate("IrrigationSystemLiquidWidget", "lblHintStyle", nullptr)));
        lblHint->setText(QApplication::translate("IrrigationSystemLiquidWidget", "\347\201\214\346\263\250\347\263\273\347\273\237\346\266\262\344\275\223\357\274\201", nullptr));
        btnIrrigate->setText(QString());
        btnIrrigate->setProperty("btnStyle", QVariant(QApplication::translate("IrrigationSystemLiquidWidget", "iconOnlyStyle", nullptr)));
        btnWash->setText(QApplication::translate("IrrigationSystemLiquidWidget", "\347\263\273\347\273\237\346\266\262\347\256\241\350\267\257\345\205\205\347\201\214", nullptr));
        btnWash->setProperty("btnStyle", QVariant(QApplication::translate("IrrigationSystemLiquidWidget", "normalBtn", nullptr)));
        btnFill->setText(QApplication::translate("IrrigationSystemLiquidWidget", "\350\267\263\350\277\207\345\205\205\347\201\214", nullptr));
        btnFill->setProperty("btnStyle", QVariant(QApplication::translate("IrrigationSystemLiquidWidget", "normalBtn", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class IrrigationSystemLiquidWidget: public Ui_IrrigationSystemLiquidWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IRRIGATIONSYSTEMLIQUIDWIDGET_H
