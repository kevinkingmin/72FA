/********************************************************************************
** Form generated from reading UI file 'PatientDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTDIALOG_H
#define UI_PATIENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatientDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_4;
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonClose;
    QFrame *line;
    QGridLayout *gridLayout;
    QLineEdit *txtAnamnesisNO;
    QLabel *label_12;
    QLabel *label_19;
    QLineEdit *txtTestDoctor;
    QLabel *label_9;
    QDateTimeEdit *dtSampleSendTime;
    QLabel *label_4;
    QLabel *label_13;
    QLineEdit *cmbBedNo;
    QLineEdit *cmbDepartmentName;
    QTextEdit *txtDiagnosis;
    QLabel *label_14;
    QLabel *label_15;
    QLineEdit *cmbSampleSender;
    QComboBox *cmbSexID;
    QLabel *label_20;
    QLineEdit *txtPatientName;
    QLineEdit *cmbWardName;
    QLabel *label_10;
    QLabel *label;
    QLabel *label_8;
    QLabel *label_11;
    QTextEdit *txtRemark;
    QHBoxLayout *horizontalLayout;
    QLineEdit *txtAge;
    QComboBox *cmbAgeUnitID;
    QLineEdit *txtVerifyDoctor;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_16;
    QLabel *label_6;
    QComboBox *cmbBloodType;
    QLabel *label_21;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnSave;
    QPushButton *btnClose;

    void setupUi(QDialog *PatientDialog)
    {
        if (PatientDialog->objectName().isEmpty())
            PatientDialog->setObjectName(QString::fromUtf8("PatientDialog"));
        PatientDialog->resize(658, 816);
        PatientDialog->setFocusPolicy(Qt::NoFocus);
        PatientDialog->setModal(false);
        layoutWidget = new QWidget(PatientDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(9, 9, 641, 798));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, -1, -1, 0);
        widgetTop = new QWidget(layoutWidget);
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


        verticalLayout_4->addWidget(widgetTop);

        line = new QFrame(layoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);


        verticalLayout->addLayout(verticalLayout_4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(10);
        gridLayout->setVerticalSpacing(5);
        gridLayout->setContentsMargins(60, 15, 42, -1);
        txtAnamnesisNO = new QLineEdit(layoutWidget);
        txtAnamnesisNO->setObjectName(QString::fromUtf8("txtAnamnesisNO"));
        txtAnamnesisNO->setMaxLength(20);
        txtAnamnesisNO->setProperty("showFull", QVariant(true));

        gridLayout->addWidget(txtAnamnesisNO, 0, 1, 1, 1);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label_12, 9, 0, 1, 1);

        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0)"));

        gridLayout->addWidget(label_19, 2, 3, 1, 1);

        txtTestDoctor = new QLineEdit(layoutWidget);
        txtTestDoctor->setObjectName(QString::fromUtf8("txtTestDoctor"));
        txtTestDoctor->setEnabled(true);

        gridLayout->addWidget(txtTestDoctor, 10, 1, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label_9, 6, 0, 1, 1);

        dtSampleSendTime = new QDateTimeEdit(layoutWidget);
        dtSampleSendTime->setObjectName(QString::fromUtf8("dtSampleSendTime"));
        dtSampleSendTime->setEnabled(false);
        dtSampleSendTime->setCalendarPopup(true);

        gridLayout->addWidget(dtSampleSendTime, 9, 1, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label_13, 10, 0, 1, 1);

        cmbBedNo = new QLineEdit(layoutWidget);
        cmbBedNo->setObjectName(QString::fromUtf8("cmbBedNo"));
        cmbBedNo->setMaxLength(48);
        cmbBedNo->setProperty("showFull", QVariant(true));

        gridLayout->addWidget(cmbBedNo, 6, 1, 1, 1);

        cmbDepartmentName = new QLineEdit(layoutWidget);
        cmbDepartmentName->setObjectName(QString::fromUtf8("cmbDepartmentName"));
        cmbDepartmentName->setMaxLength(48);
        cmbDepartmentName->setProperty("showFull", QVariant(true));

        gridLayout->addWidget(cmbDepartmentName, 7, 1, 1, 1);

        txtDiagnosis = new QTextEdit(layoutWidget);
        txtDiagnosis->setObjectName(QString::fromUtf8("txtDiagnosis"));
        txtDiagnosis->setMinimumSize(QSize(0, 60));
        txtDiagnosis->setMaximumSize(QSize(16777215, 60));
        txtDiagnosis->setProperty("showFull", QVariant(true));

        gridLayout->addWidget(txtDiagnosis, 12, 1, 1, 1);

        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label_14, 11, 0, 1, 1);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label_15, 12, 0, 1, 1);

        cmbSampleSender = new QLineEdit(layoutWidget);
        cmbSampleSender->setObjectName(QString::fromUtf8("cmbSampleSender"));
        cmbSampleSender->setMaxLength(48);
        cmbSampleSender->setProperty("showFull", QVariant(true));

        gridLayout->addWidget(cmbSampleSender, 8, 1, 1, 1);

        cmbSexID = new QComboBox(layoutWidget);
        cmbSexID->setObjectName(QString::fromUtf8("cmbSexID"));

        gridLayout->addWidget(cmbSexID, 2, 1, 1, 1);

        label_20 = new QLabel(layoutWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0)"));

        gridLayout->addWidget(label_20, 3, 3, 1, 1);

        txtPatientName = new QLineEdit(layoutWidget);
        txtPatientName->setObjectName(QString::fromUtf8("txtPatientName"));
        txtPatientName->setMaxLength(48);
        txtPatientName->setProperty("showFull", QVariant(true));

        gridLayout->addWidget(txtPatientName, 1, 1, 1, 1);

        cmbWardName = new QLineEdit(layoutWidget);
        cmbWardName->setObjectName(QString::fromUtf8("cmbWardName"));
        cmbWardName->setMaxLength(48);
        cmbWardName->setProperty("showFull", QVariant(true));

        gridLayout->addWidget(cmbWardName, 5, 1, 1, 1);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label_10, 7, 0, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label_8, 5, 0, 1, 1);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label_11, 8, 0, 1, 1);

        txtRemark = new QTextEdit(layoutWidget);
        txtRemark->setObjectName(QString::fromUtf8("txtRemark"));
        txtRemark->setMinimumSize(QSize(0, 60));
        txtRemark->setMaximumSize(QSize(16777215, 60));
        txtRemark->setProperty("showFull", QVariant(true));

        gridLayout->addWidget(txtRemark, 13, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        txtAge = new QLineEdit(layoutWidget);
        txtAge->setObjectName(QString::fromUtf8("txtAge"));

        horizontalLayout->addWidget(txtAge);

        cmbAgeUnitID = new QComboBox(layoutWidget);
        cmbAgeUnitID->setObjectName(QString::fromUtf8("cmbAgeUnitID"));

        horizontalLayout->addWidget(cmbAgeUnitID);


        gridLayout->addLayout(horizontalLayout, 3, 1, 1, 1);

        txtVerifyDoctor = new QLineEdit(layoutWidget);
        txtVerifyDoctor->setObjectName(QString::fromUtf8("txtVerifyDoctor"));
        txtVerifyDoctor->setEnabled(true);

        gridLayout->addWidget(txtVerifyDoctor, 11, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px;"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0)"));

        gridLayout->addWidget(label_17, 0, 3, 1, 1);

        label_18 = new QLabel(layoutWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0)"));

        gridLayout->addWidget(label_18, 1, 3, 1, 1);

        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label_16, 13, 0, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        cmbBloodType = new QComboBox(layoutWidget);
        cmbBloodType->setObjectName(QString::fromUtf8("cmbBloodType"));

        gridLayout->addWidget(cmbBloodType, 4, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        label_21 = new QLabel(layoutWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setStyleSheet(QString::fromUtf8("color:blue;\n"
"font-weight:bold;\n"
"font-size:14;\n"
""));
        label_21->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_21);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(20, 10, 15, 30);
        btnSave = new QPushButton(layoutWidget);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setMinimumSize(QSize(100, 35));
        btnSave->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(btnSave);

        btnClose = new QPushButton(layoutWidget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setMinimumSize(QSize(100, 35));
        btnClose->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout_3);

        QWidget::setTabOrder(txtAnamnesisNO, txtPatientName);
        QWidget::setTabOrder(txtPatientName, cmbSexID);
        QWidget::setTabOrder(cmbSexID, txtAge);
        QWidget::setTabOrder(txtAge, cmbAgeUnitID);
        QWidget::setTabOrder(cmbAgeUnitID, dtSampleSendTime);
        QWidget::setTabOrder(dtSampleSendTime, txtDiagnosis);
        QWidget::setTabOrder(txtDiagnosis, txtRemark);
        QWidget::setTabOrder(txtRemark, btnSave);
        QWidget::setTabOrder(btnSave, btnClose);
        QWidget::setTabOrder(btnClose, pushButtonClose);

        retranslateUi(PatientDialog);

        QMetaObject::connectSlotsByName(PatientDialog);
    } // setupUi

    void retranslateUi(QDialog *PatientDialog)
    {
        PatientDialog->setWindowTitle(QApplication::translate("PatientDialog", "\346\250\241\345\274\217", nullptr));
        PatientDialog->setProperty("dialogStyle", QVariant(QApplication::translate("PatientDialog", "BGStyle", nullptr)));
        label_2->setText(QApplication::translate("PatientDialog", "\347\227\205\344\272\272\344\277\241\346\201\257", nullptr));
        label_2->setProperty("lblStyle", QVariant(QApplication::translate("PatientDialog", "lblNormal", nullptr)));
        pushButtonClose->setText(QString());
        label_12->setText(QApplication::translate("PatientDialog", "\351\200\201\346\243\200\346\227\245\346\234\237", nullptr));
        label_12->setProperty("lblStyle", QVariant(QString()));
        label_19->setText(QString());
        label_9->setText(QApplication::translate("PatientDialog", "\345\272\212    \345\217\267", nullptr));
        label_9->setProperty("lblStyle", QVariant(QString()));
        dtSampleSendTime->setDisplayFormat(QApplication::translate("PatientDialog", "yyyy-MM-dd HH:mm", nullptr));
        dtSampleSendTime->setProperty("dtStyle", QVariant(QApplication::translate("PatientDialog", "dtNormalStyle", nullptr)));
        label_4->setText(QApplication::translate("PatientDialog", "\346\200\247    \345\210\253", nullptr));
        label_4->setProperty("lblStyle", QVariant(QString()));
        label_13->setText(QApplication::translate("PatientDialog", "\346\243\200\351\252\214\345\214\273\347\224\237", nullptr));
        label_13->setProperty("lblStyle", QVariant(QString()));
        label_14->setText(QApplication::translate("PatientDialog", "\345\256\241\346\240\270\345\214\273\347\224\237", nullptr));
        label_14->setProperty("lblStyle", QVariant(QString()));
        label_15->setText(QApplication::translate("PatientDialog", "\350\257\212    \346\226\255", nullptr));
        label_15->setProperty("lblStyle", QVariant(QString()));
        label_20->setText(QString());
        label_10->setText(QApplication::translate("PatientDialog", "\351\200\201\346\243\200\347\247\221\345\256\244", nullptr));
        label_10->setProperty("lblStyle", QVariant(QString()));
        label->setText(QApplication::translate("PatientDialog", "\347\227\205 \345\216\206 \345\217\267", nullptr));
        label->setProperty("lblStyle", QVariant(QString()));
        label_8->setText(QApplication::translate("PatientDialog", "\347\227\205    \345\214\272", nullptr));
        label_8->setProperty("lblStyle", QVariant(QString()));
        label_11->setText(QApplication::translate("PatientDialog", "\351\200\201\346\243\200\345\214\273\347\224\237", nullptr));
        label_11->setProperty("lblStyle", QVariant(QString()));
        label_5->setText(QApplication::translate("PatientDialog", "\345\271\264    \351\276\204", nullptr));
        label_5->setProperty("lblStyle", QVariant(QString()));
        label_3->setText(QApplication::translate("PatientDialog", "\345\247\223    \345\220\215", nullptr));
        label_3->setProperty("lblStyle", QVariant(QString()));
        label_17->setText(QString());
        label_18->setText(QString());
        label_16->setText(QApplication::translate("PatientDialog", "\345\244\207    \346\263\250", nullptr));
        label_16->setProperty("lblStyle", QVariant(QString()));
        label_6->setText(QApplication::translate("PatientDialog", "\346\240\267\346\234\254\347\261\273\345\236\213", nullptr));
        label_6->setProperty("lblStyle", QVariant(QString()));
        label_21->setText(QString());
        btnSave->setText(QApplication::translate("PatientDialog", "\344\277\235\345\255\230", nullptr));
        btnSave->setProperty("btnStyle", QVariant(QApplication::translate("PatientDialog", "normalBtn", nullptr)));
        btnClose->setText(QApplication::translate("PatientDialog", "\345\205\263\351\227\255", nullptr));
        btnClose->setProperty("btnStyle", QVariant(QApplication::translate("PatientDialog", "normalBtn", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class PatientDialog: public Ui_PatientDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTDIALOG_H
