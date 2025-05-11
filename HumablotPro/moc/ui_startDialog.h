/********************************************************************************
** Form generated from reading UI file 'startDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTDIALOG_H
#define UI_STARTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartDialog
{
public:
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_4;
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonClose;
    QGridLayout *gridLayout_3;
    QPushButton *btnQC;
    QPushButton *btnStatistics;
    QPushButton *btnReagentInfo;
    QLabel *label;
    QLineEdit *txtSeqNo;
    QGroupBox *verticalGroupBox_2;
    QVBoxLayout *verticalLayout_5;
    QPushButton *btnSelectCal;
    QPushButton *btnSelectQC;
    QPushButton *btnCalibrate;
    QGroupBox *gbSampleType;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *vBoxSampleType;
    QPushButton *btnChangeSample;
    QPushButton *btnAddConsumable;
    QPushButton *btnStart;
    QVBoxLayout *verticalLayout_6;
    QLabel *lblRemark;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnCancel;

    void setupUi(QDialog *StartDialog)
    {
        if (StartDialog->objectName().isEmpty())
            StartDialog->setObjectName(QString::fromUtf8("StartDialog"));
        StartDialog->resize(390, 452);
        StartDialog->setModal(false);
        verticalLayout_7 = new QVBoxLayout(StartDialog);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, -1, -1, -1);
        widgetTop = new QWidget(StartDialog);
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
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 12pt \"\345\256\213\344\275\223\";\n"
"font-weight:bolder;"));

        horizontalLayout_4->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pushButtonClose = new QPushButton(widgetTop);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setMinimumSize(QSize(26, 26));
        pushButtonClose->setMaximumSize(QSize(26, 26));

        horizontalLayout_4->addWidget(pushButtonClose);


        horizontalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout_4->addWidget(widgetTop);


        verticalLayout_7->addLayout(verticalLayout_4);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(50);
        gridLayout_3->setContentsMargins(50, 20, 50, -1);
        btnQC = new QPushButton(StartDialog);
        btnQC->setObjectName(QString::fromUtf8("btnQC"));
        btnQC->setMinimumSize(QSize(120, 30));

        gridLayout_3->addWidget(btnQC, 6, 0, 1, 1);

        btnStatistics = new QPushButton(StartDialog);
        btnStatistics->setObjectName(QString::fromUtf8("btnStatistics"));
        btnStatistics->setMinimumSize(QSize(120, 30));

        gridLayout_3->addWidget(btnStatistics, 7, 0, 1, 1);

        btnReagentInfo = new QPushButton(StartDialog);
        btnReagentInfo->setObjectName(QString::fromUtf8("btnReagentInfo"));
        btnReagentInfo->setMinimumSize(QSize(120, 30));

        gridLayout_3->addWidget(btnReagentInfo, 4, 0, 1, 1);

        label = new QLabel(StartDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setLayoutDirection(Qt::RightToLeft);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label, 2, 0, 1, 1);

        txtSeqNo = new QLineEdit(StartDialog);
        txtSeqNo->setObjectName(QString::fromUtf8("txtSeqNo"));
        txtSeqNo->setMinimumSize(QSize(0, 30));

        gridLayout_3->addWidget(txtSeqNo, 2, 1, 1, 1);

        verticalGroupBox_2 = new QGroupBox(StartDialog);
        verticalGroupBox_2->setObjectName(QString::fromUtf8("verticalGroupBox_2"));
        verticalLayout_5 = new QVBoxLayout(verticalGroupBox_2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(20, 20, 20, 10);
        btnSelectCal = new QPushButton(verticalGroupBox_2);
        btnSelectCal->setObjectName(QString::fromUtf8("btnSelectCal"));
        btnSelectCal->setMinimumSize(QSize(0, 30));
        btnSelectCal->setCheckable(true);

        verticalLayout_5->addWidget(btnSelectCal);

        btnSelectQC = new QPushButton(verticalGroupBox_2);
        btnSelectQC->setObjectName(QString::fromUtf8("btnSelectQC"));
        btnSelectQC->setMinimumSize(QSize(0, 30));
        btnSelectQC->setCheckable(true);

        verticalLayout_5->addWidget(btnSelectQC);


        gridLayout_3->addWidget(verticalGroupBox_2, 0, 1, 1, 1);

        btnCalibrate = new QPushButton(StartDialog);
        btnCalibrate->setObjectName(QString::fromUtf8("btnCalibrate"));
        btnCalibrate->setMinimumSize(QSize(120, 30));

        gridLayout_3->addWidget(btnCalibrate, 5, 0, 1, 1);

        gbSampleType = new QGroupBox(StartDialog);
        gbSampleType->setObjectName(QString::fromUtf8("gbSampleType"));
        verticalLayout = new QVBoxLayout(gbSampleType);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(20, 20, 20, 10);
        vBoxSampleType = new QVBoxLayout();
        vBoxSampleType->setObjectName(QString::fromUtf8("vBoxSampleType"));

        verticalLayout->addLayout(vBoxSampleType);


        gridLayout_3->addWidget(gbSampleType, 0, 0, 1, 1);

        btnChangeSample = new QPushButton(StartDialog);
        btnChangeSample->setObjectName(QString::fromUtf8("btnChangeSample"));
        btnChangeSample->setMinimumSize(QSize(120, 30));

        gridLayout_3->addWidget(btnChangeSample, 4, 1, 1, 1);

        btnAddConsumable = new QPushButton(StartDialog);
        btnAddConsumable->setObjectName(QString::fromUtf8("btnAddConsumable"));
        btnAddConsumable->setMinimumSize(QSize(120, 30));

        gridLayout_3->addWidget(btnAddConsumable, 5, 1, 1, 1);

        btnStart = new QPushButton(StartDialog);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setMinimumSize(QSize(120, 65));

        gridLayout_3->addWidget(btnStart, 6, 1, 2, 1);


        verticalLayout_7->addLayout(gridLayout_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        lblRemark = new QLabel(StartDialog);
        lblRemark->setObjectName(QString::fromUtf8("lblRemark"));

        verticalLayout_6->addWidget(lblRemark);


        verticalLayout_7->addLayout(verticalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(20, 10, 15, 30);
        btnCancel = new QPushButton(StartDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setMinimumSize(QSize(120, 35));
        btnCancel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(btnCancel);


        verticalLayout_7->addLayout(horizontalLayout_3);


        retranslateUi(StartDialog);

        QMetaObject::connectSlotsByName(StartDialog);
    } // setupUi

    void retranslateUi(QDialog *StartDialog)
    {
        StartDialog->setWindowTitle(QApplication::translate("StartDialog", "\350\206\234\345\274\217", nullptr));
        StartDialog->setProperty("dialogStyle", QVariant(QApplication::translate("StartDialog", "BGStyle", nullptr)));
        label_2->setText(QApplication::translate("StartDialog", "\346\265\213\350\257\225", nullptr));
        pushButtonClose->setText(QString());
        btnQC->setText(QApplication::translate("StartDialog", "\350\264\250\346\216\247\344\277\241\346\201\257", nullptr));
        btnQC->setProperty("btnStyle", QVariant(QApplication::translate("StartDialog", "normalBtn", nullptr)));
        btnStatistics->setText(QApplication::translate("StartDialog", "\346\240\267\346\234\254\344\277\241\346\201\257", nullptr));
        btnStatistics->setProperty("btnStyle", QVariant(QApplication::translate("StartDialog", "normalBtn", nullptr)));
        btnReagentInfo->setText(QApplication::translate("StartDialog", "\350\257\225\345\211\202\344\277\241\346\201\257", nullptr));
        btnReagentInfo->setProperty("btnStyle", QVariant(QApplication::translate("StartDialog", "normalBtn", nullptr)));
        label->setText(QApplication::translate("StartDialog", "\345\272\217\345\210\227\345\217\267:    ", nullptr));
        verticalGroupBox_2->setTitle(QApplication::translate("StartDialog", "\345\214\205\345\220\253\346\265\213\350\257\225", nullptr));
        btnSelectCal->setText(QApplication::translate("StartDialog", "\345\256\232\346\240\207", nullptr));
        btnSelectCal->setProperty("btnStyle", QVariant(QApplication::translate("StartDialog", "selectBtn", nullptr)));
        btnSelectQC->setText(QApplication::translate("StartDialog", "\350\264\250\346\216\247", nullptr));
        btnSelectQC->setProperty("btnStyle", QVariant(QApplication::translate("StartDialog", "selectBtn", nullptr)));
        btnCalibrate->setText(QApplication::translate("StartDialog", "\345\256\232\346\240\207\344\277\241\346\201\257", nullptr));
        btnCalibrate->setProperty("btnStyle", QVariant(QApplication::translate("StartDialog", "normalBtn", nullptr)));
        gbSampleType->setTitle(QApplication::translate("StartDialog", "\346\240\267\346\234\254\347\261\273\345\236\213", nullptr));
        btnChangeSample->setText(QApplication::translate("StartDialog", "\346\233\264\346\215\242\346\240\267\346\234\254\346\236\266", nullptr));
        btnChangeSample->setProperty("btnStyle", QVariant(QApplication::translate("StartDialog", "normalBtn", nullptr)));
        btnAddConsumable->setText(QApplication::translate("StartDialog", "\346\267\273\345\212\240\350\200\227\346\235\220", nullptr));
        btnAddConsumable->setProperty("btnStyle", QVariant(QApplication::translate("StartDialog", "normalBtn", nullptr)));
        btnStart->setText(QApplication::translate("StartDialog", "\345\274\200\345\247\213", nullptr));
        btnStart->setProperty("btnStyle", QVariant(QApplication::translate("StartDialog", "normalBtn", nullptr)));
        lblRemark->setText(QString());
        btnCancel->setText(QApplication::translate("StartDialog", "\345\217\226\346\266\210", nullptr));
        btnCancel->setProperty("btnStyle", QVariant(QApplication::translate("StartDialog", "normalBtn", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class StartDialog: public Ui_StartDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTDIALOG_H
