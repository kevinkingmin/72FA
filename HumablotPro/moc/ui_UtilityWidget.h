/********************************************************************************
** Form generated from reading UI file 'UtilityWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UTILITYWIDGET_H
#define UI_UTILITYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UtilityWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QGroupBox *verticalGroupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *btnMaintain;
    QPushButton *btnSystemSet;
    QPushButton *btnItemSet;
    QPushButton *btnState;
    QPushButton *btnASSetting;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *pageMantain;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabMantain;
    QWidget *pageSystemSet;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabSystemSet;
    QWidget *pageItemSet;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabItemSet;
    QWidget *pageState;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabState;
    QWidget *pageASSetting;
    QVBoxLayout *verticalLayout_7;
    QTabWidget *tabASSetting;

    void setupUi(QWidget *UtilityWidget)
    {
        if (UtilityWidget->objectName().isEmpty())
            UtilityWidget->setObjectName(QString::fromUtf8("UtilityWidget"));
        UtilityWidget->resize(839, 603);
        verticalLayout_2 = new QVBoxLayout(UtilityWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalGroupBox = new QGroupBox(UtilityWidget);
        verticalGroupBox->setObjectName(QString::fromUtf8("verticalGroupBox"));
        verticalLayout = new QVBoxLayout(verticalGroupBox);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(15, 30, 15, 10);
        btnMaintain = new QPushButton(verticalGroupBox);
        btnMaintain->setObjectName(QString::fromUtf8("btnMaintain"));
        btnMaintain->setMinimumSize(QSize(120, 40));
        btnMaintain->setCheckable(true);
        btnMaintain->setAutoExclusive(true);

        verticalLayout->addWidget(btnMaintain);

        btnSystemSet = new QPushButton(verticalGroupBox);
        btnSystemSet->setObjectName(QString::fromUtf8("btnSystemSet"));
        btnSystemSet->setMinimumSize(QSize(120, 40));
        btnSystemSet->setCheckable(true);
        btnSystemSet->setAutoExclusive(true);

        verticalLayout->addWidget(btnSystemSet);

        btnItemSet = new QPushButton(verticalGroupBox);
        btnItemSet->setObjectName(QString::fromUtf8("btnItemSet"));
        btnItemSet->setMinimumSize(QSize(120, 40));
        btnItemSet->setCheckable(true);
        btnItemSet->setAutoExclusive(true);

        verticalLayout->addWidget(btnItemSet);

        btnState = new QPushButton(verticalGroupBox);
        btnState->setObjectName(QString::fromUtf8("btnState"));
        btnState->setMinimumSize(QSize(120, 40));
        btnState->setCheckable(true);
        btnState->setAutoExclusive(true);

        verticalLayout->addWidget(btnState);

        btnASSetting = new QPushButton(verticalGroupBox);
        btnASSetting->setObjectName(QString::fromUtf8("btnASSetting"));
        btnASSetting->setMinimumSize(QSize(120, 40));
        btnASSetting->setCheckable(true);
        btnASSetting->setAutoExclusive(true);

        verticalLayout->addWidget(btnASSetting);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(verticalGroupBox);

        stackedWidget = new QStackedWidget(UtilityWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        pageMantain = new QWidget();
        pageMantain->setObjectName(QString::fromUtf8("pageMantain"));
        verticalLayout_3 = new QVBoxLayout(pageMantain);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabMantain = new QTabWidget(pageMantain);
        tabMantain->setObjectName(QString::fromUtf8("tabMantain"));

        verticalLayout_3->addWidget(tabMantain);

        stackedWidget->addWidget(pageMantain);
        pageSystemSet = new QWidget();
        pageSystemSet->setObjectName(QString::fromUtf8("pageSystemSet"));
        verticalLayout_4 = new QVBoxLayout(pageSystemSet);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tabSystemSet = new QTabWidget(pageSystemSet);
        tabSystemSet->setObjectName(QString::fromUtf8("tabSystemSet"));

        verticalLayout_4->addWidget(tabSystemSet);

        stackedWidget->addWidget(pageSystemSet);
        pageItemSet = new QWidget();
        pageItemSet->setObjectName(QString::fromUtf8("pageItemSet"));
        verticalLayout_5 = new QVBoxLayout(pageItemSet);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        tabItemSet = new QTabWidget(pageItemSet);
        tabItemSet->setObjectName(QString::fromUtf8("tabItemSet"));

        verticalLayout_5->addWidget(tabItemSet);

        stackedWidget->addWidget(pageItemSet);
        pageState = new QWidget();
        pageState->setObjectName(QString::fromUtf8("pageState"));
        verticalLayout_6 = new QVBoxLayout(pageState);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        tabState = new QTabWidget(pageState);
        tabState->setObjectName(QString::fromUtf8("tabState"));

        verticalLayout_6->addWidget(tabState);

        stackedWidget->addWidget(pageState);
        pageASSetting = new QWidget();
        pageASSetting->setObjectName(QString::fromUtf8("pageASSetting"));
        verticalLayout_7 = new QVBoxLayout(pageASSetting);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        tabASSetting = new QTabWidget(pageASSetting);
        tabASSetting->setObjectName(QString::fromUtf8("tabASSetting"));

        verticalLayout_7->addWidget(tabASSetting);

        stackedWidget->addWidget(pageASSetting);

        horizontalLayout->addWidget(stackedWidget);

        horizontalLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(UtilityWidget);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(UtilityWidget);
    } // setupUi

    void retranslateUi(QWidget *UtilityWidget)
    {
        UtilityWidget->setWindowTitle(QApplication::translate("UtilityWidget", "Form", nullptr));
        btnMaintain->setText(QApplication::translate("UtilityWidget", "\347\263\273\347\273\237\347\273\264\346\212\244", nullptr));
        btnMaintain->setProperty("btnStyle", QVariant(QApplication::translate("UtilityWidget", "normalBtn", nullptr)));
        btnSystemSet->setText(QApplication::translate("UtilityWidget", "\347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        btnSystemSet->setProperty("btnStyle", QVariant(QApplication::translate("UtilityWidget", "normalBtn", nullptr)));
        btnItemSet->setText(QApplication::translate("UtilityWidget", "\351\241\271\347\233\256\350\256\276\347\275\256", nullptr));
        btnItemSet->setProperty("btnStyle", QVariant(QApplication::translate("UtilityWidget", "normalBtn", nullptr)));
        btnState->setText(QApplication::translate("UtilityWidget", "\347\212\266\346\200\201", nullptr));
        btnState->setProperty("btnStyle", QVariant(QApplication::translate("UtilityWidget", "normalBtn", nullptr)));
        btnASSetting->setText(QApplication::translate("UtilityWidget", "\350\276\205\345\212\251\350\256\276\347\275\256", nullptr));
        btnASSetting->setProperty("btnStyle", QVariant(QApplication::translate("UtilityWidget", "normalBtn", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class UtilityWidget: public Ui_UtilityWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UTILITYWIDGET_H
