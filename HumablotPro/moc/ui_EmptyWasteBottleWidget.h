/********************************************************************************
** Form generated from reading UI file 'EmptyWasteBottleWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPTYWASTEBOTTLEWIDGET_H
#define UI_EMPTYWASTEBOTTLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmptyWasteBottleWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *vwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnPerfusionSystemLiquid;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *EmptyWasteBottleWidget)
    {
        if (EmptyWasteBottleWidget->objectName().isEmpty())
            EmptyWasteBottleWidget->setObjectName(QString::fromUtf8("EmptyWasteBottleWidget"));
        EmptyWasteBottleWidget->resize(844, 646);
        horizontalLayout = new QHBoxLayout(EmptyWasteBottleWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        vwidget = new QWidget(EmptyWasteBottleWidget);
        vwidget->setObjectName(QString::fromUtf8("vwidget"));
        verticalLayout = new QVBoxLayout(vwidget);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 30, -1, -1);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(15);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 40, -1, 10);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 18, -1, -1);
        btnPerfusionSystemLiquid = new QPushButton(vwidget);
        btnPerfusionSystemLiquid->setObjectName(QString::fromUtf8("btnPerfusionSystemLiquid"));

        horizontalLayout_2->addWidget(btnPerfusionSystemLiquid);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(verticalLayout_2);

        label = new QLabel(vwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font-size:48px;\n"
"font-weight:bold;"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(vwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/background/wasteBottle.png")));
        label_2->setScaledContents(false);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(vwidget);


        retranslateUi(EmptyWasteBottleWidget);

        QMetaObject::connectSlotsByName(EmptyWasteBottleWidget);
    } // setupUi

    void retranslateUi(QWidget *EmptyWasteBottleWidget)
    {
        EmptyWasteBottleWidget->setWindowTitle(QApplication::translate("EmptyWasteBottleWidget", "Form", nullptr));
        vwidget->setProperty("widgetStyle", QVariant(QApplication::translate("EmptyWasteBottleWidget", "BGStyle", nullptr)));
        btnPerfusionSystemLiquid->setText(QApplication::translate("EmptyWasteBottleWidget", "PushButton", nullptr));
        label->setText(QApplication::translate("EmptyWasteBottleWidget", "\346\270\205\347\251\272\345\272\237\346\266\262\347\223\266", nullptr));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EmptyWasteBottleWidget: public Ui_EmptyWasteBottleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPTYWASTEBOTTLEWIDGET_H
