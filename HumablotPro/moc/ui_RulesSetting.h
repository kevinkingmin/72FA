/********************************************************************************
** Form generated from reading UI file 'RulesSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULESSETTING_H
#define UI_RULESSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RulesSetting
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QPushButton *btnRule;
    QPushButton *btnCurve;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QFrame *line;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tbRule;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnAddRule;
    QPushButton *btnDeleteRule;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *tbRuleItem;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnAddItem;
    QPushButton *btnSaveItem;
    QPushButton *btnDelete;
    QGridLayout *gridLayout;

    void setupUi(QWidget *RulesSetting)
    {
        if (RulesSetting->objectName().isEmpty())
            RulesSetting->setObjectName(QString::fromUtf8("RulesSetting"));
        RulesSetting->resize(1454, 798);
        layoutWidget = new QWidget(RulesSetting);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(460, 10, 821, 761));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(5, 5, 5, 5);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 25, 15, -1);
        btnRule = new QPushButton(layoutWidget);
        btnRule->setObjectName(QString::fromUtf8("btnRule"));
        btnRule->setCheckable(false);
        btnRule->setAutoExclusive(false);

        verticalLayout->addWidget(btnRule);

        btnCurve = new QPushButton(layoutWidget);
        btnCurve->setObjectName(QString::fromUtf8("btnCurve"));
        btnCurve->setCheckable(false);
        btnCurve->setAutoExclusive(false);

        verticalLayout->addWidget(btnCurve);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_5->addLayout(verticalLayout);

        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label);

        line = new QFrame(groupBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 10);
        tbRule = new QTableWidget(groupBox);
        if (tbRule->columnCount() < 2)
            tbRule->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbRule->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbRule->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tbRule->setObjectName(QString::fromUtf8("tbRule"));

        verticalLayout_2->addWidget(tbRule);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(15, 10, 15, -1);
        btnAddRule = new QPushButton(groupBox);
        btnAddRule->setObjectName(QString::fromUtf8("btnAddRule"));

        horizontalLayout_2->addWidget(btnAddRule);

        btnDeleteRule = new QPushButton(groupBox);
        btnDeleteRule->setObjectName(QString::fromUtf8("btnDeleteRule"));

        horizontalLayout_2->addWidget(btnDeleteRule);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, -1, -1, 10);
        tbRuleItem = new QTableWidget(groupBox);
        if (tbRuleItem->columnCount() < 4)
            tbRuleItem->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbRuleItem->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbRuleItem->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbRuleItem->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tbRuleItem->setHorizontalHeaderItem(3, __qtablewidgetitem5);
        tbRuleItem->setObjectName(QString::fromUtf8("tbRuleItem"));

        verticalLayout_3->addWidget(tbRuleItem);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(25, 10, 25, -1);
        btnAddItem = new QPushButton(groupBox);
        btnAddItem->setObjectName(QString::fromUtf8("btnAddItem"));

        horizontalLayout_3->addWidget(btnAddItem);

        btnSaveItem = new QPushButton(groupBox);
        btnSaveItem->setObjectName(QString::fromUtf8("btnSaveItem"));

        horizontalLayout_3->addWidget(btnSaveItem);

        btnDelete = new QPushButton(groupBox);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        horizontalLayout_3->addWidget(btnDelete);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_4->setStretch(1, 1);

        verticalLayout_4->addLayout(horizontalLayout_4);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        verticalLayout_4->addLayout(gridLayout);


        horizontalLayout_5->addWidget(groupBox);


        retranslateUi(RulesSetting);

        QMetaObject::connectSlotsByName(RulesSetting);
    } // setupUi

    void retranslateUi(QWidget *RulesSetting)
    {
        RulesSetting->setWindowTitle(QApplication::translate("RulesSetting", "RulesSetting", nullptr));
        btnRule->setText(QApplication::translate("RulesSetting", "\345\210\244\350\257\273\350\247\204\345\210\231", nullptr));
        btnRule->setProperty("btnStyle", QVariant(QApplication::translate("RulesSetting", "normalBtnpink", nullptr)));
        btnCurve->setText(QApplication::translate("RulesSetting", "\346\240\207\345\207\206\346\233\262\347\272\277", nullptr));
        btnCurve->setProperty("btnStyle", QVariant(QApplication::translate("RulesSetting", "normalBtnpink", nullptr)));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("RulesSetting", "\350\247\204\345\210\231\350\256\276\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tbRule->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("RulesSetting", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tbRule->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("RulesSetting", "id", nullptr));
        btnAddRule->setText(QApplication::translate("RulesSetting", "\346\226\260\345\242\236\350\247\204\345\210\231", nullptr));
        btnAddRule->setProperty("btnStyle", QVariant(QApplication::translate("RulesSetting", "normalBtnpink", nullptr)));
        btnDeleteRule->setText(QApplication::translate("RulesSetting", "\345\210\240\351\231\244\350\247\204\345\210\231", nullptr));
        btnDeleteRule->setProperty("btnStyle", QVariant(QApplication::translate("RulesSetting", "normalBtnpink", nullptr)));
        QTableWidgetItem *___qtablewidgetitem2 = tbRuleItem->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("RulesSetting", "No", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tbRuleItem->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("RulesSetting", "\347\201\260\345\272\246\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tbRuleItem->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("RulesSetting", "\346\230\276\347\244\272\347\254\246\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tbRuleItem->horizontalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("RulesSetting", "id", nullptr));
        btnAddItem->setText(QApplication::translate("RulesSetting", "\346\226\260\345\242\236", nullptr));
        btnAddItem->setProperty("btnStyle", QVariant(QApplication::translate("RulesSetting", "normalBtnpink", nullptr)));
        btnSaveItem->setText(QApplication::translate("RulesSetting", "\344\277\235\345\255\230", nullptr));
        btnSaveItem->setProperty("btnStyle", QVariant(QApplication::translate("RulesSetting", "normalBtnpink", nullptr)));
        btnDelete->setText(QApplication::translate("RulesSetting", "\345\210\240\351\231\244", nullptr));
        btnDelete->setProperty("btnStyle", QVariant(QApplication::translate("RulesSetting", "normalBtnpink", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class RulesSetting: public Ui_RulesSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULESSETTING_H
