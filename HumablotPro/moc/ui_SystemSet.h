/********************************************************************************
** Form generated from reading UI file 'SystemSet.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMSET_H
#define UI_SYSTEMSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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

class Ui_SystemSet
{
public:
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_25;
    QLabel *label_55;
    QLabel *label_24;
    QLabel *label_17;
    QComboBox *comboBox_aspirate_sample;
    QLabel *label_36;
    QLabel *label_28;
    QLabel *label_11;
    QLabel *label_26;
    QLineEdit *lineEdit_month_finish_time;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEdit_month_filling_volume;
    QComboBox *comboBox_run_sequence;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_21;
    QLabel *label_12;
    QLineEdit *lineEdit_week_filling_volume;
    QLineEdit *lineEdit_system_wash_volume;
    QLabel *label_29;
    QLabel *label_15;
    QLineEdit *lineEdit_Weight;
    QLabel *label_56;
    QLineEdit *lineEdit_RootPathPicture;
    QLabel *label_7;
    QLabel *label_19;
    QLabel *label_18;
    QLabel *label_10;
    QLabel *label_27;
    QComboBox *comboBox_waste_liquid_tank_enable;
    QLabel *label_22;
    QComboBox *comboBox_CompanyList;
    QLabel *label_41;
    QComboBox *comboBox_vomit;
    QLabel *label_32;
    QLabel *label_34;
    QPushButton *pushButtonPara;
    QComboBox *comboBox_waste_liquid_tank_enable_2;
    QLineEdit *lineEdit_system_wash_volume_2;
    QLabel *label_30;
    QLineEdit *lineEdit_monthly_maintenance_pump_calibration;
    QLineEdit *lineEdit_week_finish_time;
    QLabel *label_13;
    QLabel *label_8;
    QComboBox *comboBox_picture_analysis_enable;
    QLabel *label_6;
    QLabel *label_14;
    QLineEdit *lineEdit_system_filling_volume;
    QLineEdit *lineEdit_RootPathReport;
    QLabel *label_5;
    QComboBox *comboBox_beep_enable;
    QLabel *label_3;
    QLabel *label_16;
    QLineEdit *txtReportTitle;
    QLabel *label_31;
    QComboBox *comboBox_language;
    QLineEdit *lineEdit_system_wash_volume_3;
    QLabel *label_23;
    QLabel *label_33;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Test;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Cancel;

    void setupUi(QWidget *SystemSet)
    {
        if (SystemSet->objectName().isEmpty())
            SystemSet->setObjectName(QString::fromUtf8("SystemSet"));
        SystemSet->resize(1705, 776);
        groupBox = new QGroupBox(SystemSet);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(50, 50, 1611, 681));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(15, 15, 15, 15);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_25 = new QLabel(groupBox);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_2->addWidget(label_25, 3, 3, 1, 1);

        label_55 = new QLabel(groupBox);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        label_55->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_55, 9, 5, 1, 1);

        label_24 = new QLabel(groupBox);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_2->addWidget(label_24, 2, 3, 1, 1);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_17, 1, 1, 1, 1);

        comboBox_aspirate_sample = new QComboBox(groupBox);
        comboBox_aspirate_sample->addItem(QString());
        comboBox_aspirate_sample->addItem(QString());
        comboBox_aspirate_sample->setObjectName(QString::fromUtf8("comboBox_aspirate_sample"));

        gridLayout_2->addWidget(comboBox_aspirate_sample, 4, 6, 1, 1);

        label_36 = new QLabel(groupBox);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setMinimumSize(QSize(120, 10));

        gridLayout_2->addWidget(label_36, 5, 8, 1, 1);

        label_28 = new QLabel(groupBox);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_28, 2, 5, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_11, 8, 1, 1, 1);

        label_26 = new QLabel(groupBox);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_2->addWidget(label_26, 4, 3, 1, 1);

        lineEdit_month_finish_time = new QLineEdit(groupBox);
        lineEdit_month_finish_time->setObjectName(QString::fromUtf8("lineEdit_month_finish_time"));

        gridLayout_2->addWidget(lineEdit_month_finish_time, 2, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 8, 9, 1, 1);

        lineEdit_month_filling_volume = new QLineEdit(groupBox);
        lineEdit_month_filling_volume->setObjectName(QString::fromUtf8("lineEdit_month_filling_volume"));

        gridLayout_2->addWidget(lineEdit_month_filling_volume, 3, 2, 1, 1);

        comboBox_run_sequence = new QComboBox(groupBox);
        comboBox_run_sequence->setObjectName(QString::fromUtf8("comboBox_run_sequence"));

        gridLayout_2->addWidget(comboBox_run_sequence, 3, 6, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_9, 4, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_21, 5, 1, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_12, 9, 1, 1, 1);

        lineEdit_week_filling_volume = new QLineEdit(groupBox);
        lineEdit_week_filling_volume->setObjectName(QString::fromUtf8("lineEdit_week_filling_volume"));

        gridLayout_2->addWidget(lineEdit_week_filling_volume, 4, 2, 1, 1);

        lineEdit_system_wash_volume = new QLineEdit(groupBox);
        lineEdit_system_wash_volume->setObjectName(QString::fromUtf8("lineEdit_system_wash_volume"));

        gridLayout_2->addWidget(lineEdit_system_wash_volume, 9, 2, 1, 1);

        label_29 = new QLabel(groupBox);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_29, 0, 1, 1, 1);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_15, 6, 1, 1, 1);

        lineEdit_Weight = new QLineEdit(groupBox);
        lineEdit_Weight->setObjectName(QString::fromUtf8("lineEdit_Weight"));

        gridLayout_2->addWidget(lineEdit_Weight, 9, 6, 1, 1);

        label_56 = new QLabel(groupBox);
        label_56->setObjectName(QString::fromUtf8("label_56"));
        label_56->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_56, 10, 5, 1, 1);

        lineEdit_RootPathPicture = new QLineEdit(groupBox);
        lineEdit_RootPathPicture->setObjectName(QString::fromUtf8("lineEdit_RootPathPicture"));

        gridLayout_2->addWidget(lineEdit_RootPathPicture, 1, 6, 1, 3);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_7, 6, 5, 1, 1);

        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setLayoutDirection(Qt::LeftToRight);
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_19, 8, 5, 1, 1);

        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_18, 7, 5, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_10, 5, 5, 1, 1);

        label_27 = new QLabel(groupBox);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_2->addWidget(label_27, 5, 3, 1, 1);

        comboBox_waste_liquid_tank_enable = new QComboBox(groupBox);
        comboBox_waste_liquid_tank_enable->addItem(QString());
        comboBox_waste_liquid_tank_enable->addItem(QString());
        comboBox_waste_liquid_tank_enable->setObjectName(QString::fromUtf8("comboBox_waste_liquid_tank_enable"));

        gridLayout_2->addWidget(comboBox_waste_liquid_tank_enable, 8, 6, 1, 1);

        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_22, 10, 1, 1, 1);

        comboBox_CompanyList = new QComboBox(groupBox);
        comboBox_CompanyList->setObjectName(QString::fromUtf8("comboBox_CompanyList"));

        gridLayout_2->addWidget(comboBox_CompanyList, 6, 6, 1, 1);

        label_41 = new QLabel(groupBox);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_41, 9, 7, 1, 1);

        comboBox_vomit = new QComboBox(groupBox);
        comboBox_vomit->addItem(QString());
        comboBox_vomit->addItem(QString());
        comboBox_vomit->setObjectName(QString::fromUtf8("comboBox_vomit"));

        gridLayout_2->addWidget(comboBox_vomit, 5, 6, 1, 1);

        label_32 = new QLabel(groupBox);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_2->addWidget(label_32, 10, 3, 1, 1);

        label_34 = new QLabel(groupBox);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setMinimumSize(QSize(88, 10));

        gridLayout_2->addWidget(label_34, 6, 4, 1, 1);

        pushButtonPara = new QPushButton(groupBox);
        pushButtonPara->setObjectName(QString::fromUtf8("pushButtonPara"));

        gridLayout_2->addWidget(pushButtonPara, 6, 7, 1, 2);

        comboBox_waste_liquid_tank_enable_2 = new QComboBox(groupBox);
        comboBox_waste_liquid_tank_enable_2->addItem(QString());
        comboBox_waste_liquid_tank_enable_2->addItem(QString());
        comboBox_waste_liquid_tank_enable_2->setObjectName(QString::fromUtf8("comboBox_waste_liquid_tank_enable_2"));

        gridLayout_2->addWidget(comboBox_waste_liquid_tank_enable_2, 10, 6, 1, 1);

        lineEdit_system_wash_volume_2 = new QLineEdit(groupBox);
        lineEdit_system_wash_volume_2->setObjectName(QString::fromUtf8("lineEdit_system_wash_volume_2"));

        gridLayout_2->addWidget(lineEdit_system_wash_volume_2, 10, 2, 1, 1);

        label_30 = new QLabel(groupBox);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_2->addWidget(label_30, 8, 3, 1, 1);

        lineEdit_monthly_maintenance_pump_calibration = new QLineEdit(groupBox);
        lineEdit_monthly_maintenance_pump_calibration->setObjectName(QString::fromUtf8("lineEdit_monthly_maintenance_pump_calibration"));

        gridLayout_2->addWidget(lineEdit_monthly_maintenance_pump_calibration, 5, 2, 1, 1);

        lineEdit_week_finish_time = new QLineEdit(groupBox);
        lineEdit_week_finish_time->setObjectName(QString::fromUtf8("lineEdit_week_finish_time"));

        gridLayout_2->addWidget(lineEdit_week_finish_time, 1, 2, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_13, 3, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_8, 3, 5, 1, 1);

        comboBox_picture_analysis_enable = new QComboBox(groupBox);
        comboBox_picture_analysis_enable->addItem(QString());
        comboBox_picture_analysis_enable->addItem(QString());
        comboBox_picture_analysis_enable->setObjectName(QString::fromUtf8("comboBox_picture_analysis_enable"));

        gridLayout_2->addWidget(comboBox_picture_analysis_enable, 6, 2, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_6, 0, 5, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_14, 4, 1, 1, 1);

        lineEdit_system_filling_volume = new QLineEdit(groupBox);
        lineEdit_system_filling_volume->setObjectName(QString::fromUtf8("lineEdit_system_filling_volume"));

        gridLayout_2->addWidget(lineEdit_system_filling_volume, 8, 2, 1, 1);

        lineEdit_RootPathReport = new QLineEdit(groupBox);
        lineEdit_RootPathReport->setObjectName(QString::fromUtf8("lineEdit_RootPathReport"));

        gridLayout_2->addWidget(lineEdit_RootPathReport, 0, 6, 1, 3);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 3, 1, 1);

        comboBox_beep_enable = new QComboBox(groupBox);
        comboBox_beep_enable->addItem(QString());
        comboBox_beep_enable->addItem(QString());
        comboBox_beep_enable->setObjectName(QString::fromUtf8("comboBox_beep_enable"));
        comboBox_beep_enable->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(comboBox_beep_enable, 7, 6, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_3, 1, 5, 1, 1);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_16, 2, 1, 1, 1);

        txtReportTitle = new QLineEdit(groupBox);
        txtReportTitle->setObjectName(QString::fromUtf8("txtReportTitle"));
        txtReportTitle->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(txtReportTitle, 0, 2, 1, 2);

        label_31 = new QLabel(groupBox);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_2->addWidget(label_31, 9, 3, 1, 1);

        comboBox_language = new QComboBox(groupBox);
        comboBox_language->addItem(QString());
        comboBox_language->addItem(QString());
        comboBox_language->addItem(QString());
        comboBox_language->setObjectName(QString::fromUtf8("comboBox_language"));

        gridLayout_2->addWidget(comboBox_language, 2, 6, 1, 1);

        lineEdit_system_wash_volume_3 = new QLineEdit(groupBox);
        lineEdit_system_wash_volume_3->setObjectName(QString::fromUtf8("lineEdit_system_wash_volume_3"));

        gridLayout_2->addWidget(lineEdit_system_wash_volume_3, 7, 2, 1, 1);

        label_23 = new QLabel(groupBox);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_23, 7, 1, 1, 1);

        label_33 = new QLabel(groupBox);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_2->addWidget(label_33, 7, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 25, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_Test = new QPushButton(groupBox);
        pushButton_Test->setObjectName(QString::fromUtf8("pushButton_Test"));

        horizontalLayout->addWidget(pushButton_Test);

        pushButton_Save = new QPushButton(groupBox);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));

        horizontalLayout->addWidget(pushButton_Save);

        pushButton_Cancel = new QPushButton(groupBox);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));

        horizontalLayout->addWidget(pushButton_Cancel);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        retranslateUi(SystemSet);

        QMetaObject::connectSlotsByName(SystemSet);
    } // setupUi

    void retranslateUi(QWidget *SystemSet)
    {
        SystemSet->setWindowTitle(QApplication::translate("SystemSet", "SystemSet", nullptr));
        groupBox->setTitle(QString());
        label_25->setText(QApplication::translate("SystemSet", "1-10ml", nullptr));
        label_55->setText(QApplication::translate("SystemSet", "\346\257\253\347\261\263\345\257\271\345\272\224\345\203\217\347\264\240\357\274\232", nullptr));
        label_24->setText(QApplication::translate("SystemSet", "5-240\345\210\206\351\222\237", nullptr));
        label_17->setText(QApplication::translate("SystemSet", "\345\221\250\347\273\264\346\212\244\346\265\270\346\263\241\346\227\266\351\227\264\357\274\232", nullptr));
        comboBox_aspirate_sample->setItemText(0, QApplication::translate("SystemSet", "\346\211\223\345\274\200", nullptr));
        comboBox_aspirate_sample->setItemText(1, QApplication::translate("SystemSet", "\345\205\263\351\227\255", nullptr));

        label_36->setText(QString());
        label_28->setText(QApplication::translate("SystemSet", "\350\257\255\350\250\200\351\200\211\346\213\251\357\274\232", nullptr));
        label_11->setText(QApplication::translate("SystemSet", "\347\263\273\347\273\237\346\266\262\345\205\205\347\201\214\344\275\223\347\247\257\357\274\232", nullptr));
        label_26->setText(QApplication::translate("SystemSet", "1-10ml", nullptr));
        label_9->setText(QApplication::translate("SystemSet", "\346\240\267\346\234\254\351\222\210\345\220\270\346\240\267\346\266\262\344\275\215\346\216\242\346\265\213\351\200\211\346\213\251\357\274\232", nullptr));
        label_21->setText(QApplication::translate("SystemSet", "\346\234\210\347\273\264\346\212\244\346\263\265\346\240\241\345\207\206\351\207\217\357\274\232", nullptr));
        label_12->setText(QApplication::translate("SystemSet", "\347\263\273\347\273\237\346\266\262\346\270\205\346\264\227\344\275\223\347\247\257\357\274\232", nullptr));
        label_29->setText(QApplication::translate("SystemSet", "\346\211\223\345\215\260\346\212\245\345\221\212\346\240\207\351\242\230\357\274\232", nullptr));
        label_15->setText(QApplication::translate("SystemSet", "\345\233\276\347\211\207\350\247\243\346\236\220\350\260\203\350\257\225\357\274\232", nullptr));
        lineEdit_Weight->setText(QApplication::translate("SystemSet", "18.481", nullptr));
        label_56->setText(QApplication::translate("SystemSet", "\346\213\215\347\205\247\345\212\237\350\203\275\357\274\232", nullptr));
        label_7->setText(QApplication::translate("SystemSet", "\345\275\223\345\211\215\344\275\277\347\224\250\347\232\204\350\206\234\346\235\241\346\211\200\345\261\236\345\205\254\345\217\270\357\274\232", nullptr));
        label_19->setText(QApplication::translate("SystemSet", "\345\272\237\346\266\262\346\241\266\344\275\277\350\203\275\357\274\232", nullptr));
        label_18->setText(QApplication::translate("SystemSet", "\350\234\202\351\270\243\345\231\250\345\243\260\351\237\263\344\275\277\350\203\275\357\274\232", nullptr));
        label_10->setText(QApplication::translate("SystemSet", "\346\240\267\346\234\254\351\222\210\345\220\220\346\240\267\346\266\262\344\275\215\346\216\242\346\265\213\351\200\211\346\213\251\357\274\232", nullptr));
        label_27->setText(QApplication::translate("SystemSet", "300-700ul", nullptr));
        comboBox_waste_liquid_tank_enable->setItemText(0, QApplication::translate("SystemSet", "\345\220\246", nullptr));
        comboBox_waste_liquid_tank_enable->setItemText(1, QApplication::translate("SystemSet", "\346\230\257", nullptr));

        label_22->setText(QApplication::translate("SystemSet", "\345\205\263\346\234\272\346\216\222\347\251\272\346\266\262\351\207\217\357\274\232", nullptr));
        label_41->setText(QApplication::translate("SystemSet", "mm", nullptr));
        comboBox_vomit->setItemText(0, QApplication::translate("SystemSet", "\346\211\223\345\274\200", nullptr));
        comboBox_vomit->setItemText(1, QApplication::translate("SystemSet", "\345\205\263\351\227\255", nullptr));

        label_32->setText(QApplication::translate("SystemSet", "1-5ml", nullptr));
        label_34->setText(QString());
        pushButtonPara->setText(QApplication::translate("SystemSet", "\346\265\201\347\250\213\350\256\276\347\275\256", nullptr));
        pushButtonPara->setProperty("btnStyle", QVariant(QApplication::translate("SystemSet", "normalBtnRed", nullptr)));
        comboBox_waste_liquid_tank_enable_2->setItemText(0, QApplication::translate("SystemSet", "\345\220\246", nullptr));
        comboBox_waste_liquid_tank_enable_2->setItemText(1, QApplication::translate("SystemSet", "\346\230\257", nullptr));

        label_30->setText(QApplication::translate("SystemSet", "1-5ml", nullptr));
        label_13->setText(QApplication::translate("SystemSet", "\346\234\210\347\273\264\346\212\244\346\263\265\345\205\205\347\201\214\351\207\217\357\274\232", nullptr));
        label_8->setText(QApplication::translate("SystemSet", "\346\227\266\345\272\217\351\200\211\346\213\251\357\274\232", nullptr));
        comboBox_picture_analysis_enable->setItemText(0, QApplication::translate("SystemSet", "\345\220\246", nullptr));
        comboBox_picture_analysis_enable->setItemText(1, QApplication::translate("SystemSet", "\346\230\257", nullptr));

        label_6->setText(QApplication::translate("SystemSet", "\346\265\213\350\257\225\346\212\245\345\221\212\344\277\235\345\255\230\346\240\271\347\233\256\345\275\225\357\274\232", nullptr));
        label_14->setText(QApplication::translate("SystemSet", "\345\221\250\347\273\264\346\212\244\346\263\265\345\205\205\347\201\214\351\207\217\357\274\232", nullptr));
        label_5->setText(QApplication::translate("SystemSet", "5-240\345\210\206\351\222\237", nullptr));
        comboBox_beep_enable->setItemText(0, QApplication::translate("SystemSet", "\345\220\246", nullptr));
        comboBox_beep_enable->setItemText(1, QApplication::translate("SystemSet", "\346\230\257", nullptr));

        label_3->setText(QApplication::translate("SystemSet", "\346\265\213\350\257\225\345\233\276\345\203\217\344\277\235\345\255\230\346\240\271\347\233\256\345\275\225\357\274\232", nullptr));
        label_16->setText(QApplication::translate("SystemSet", "\346\234\210\347\273\264\346\212\244\346\265\270\346\263\241\346\227\266\351\227\264\357\274\232", nullptr));
        label_31->setText(QApplication::translate("SystemSet", "1-5ml", nullptr));
        comboBox_language->setItemText(0, QApplication::translate("SystemSet", "\344\270\255\346\226\207", nullptr));
        comboBox_language->setItemText(1, QApplication::translate("SystemSet", "\344\270\255\346\226\207", nullptr));
        comboBox_language->setItemText(2, QApplication::translate("SystemSet", "EN", nullptr));

        label_23->setText(QApplication::translate("SystemSet", "\346\263\265\345\233\236\346\265\201\346\214\207\345\256\232\346\266\262\351\207\217\357\274\232", nullptr));
        label_33->setText(QApplication::translate("SystemSet", "1-5ml", nullptr));
        pushButton_Test->setText(QApplication::translate("SystemSet", "\351\273\230\350\256\244\345\200\274", nullptr));
        pushButton_Test->setProperty("btnStyle", QVariant(QApplication::translate("SystemSet", "normalBtnGray", nullptr)));
        pushButton_Save->setText(QApplication::translate("SystemSet", "\344\277\235\345\255\230", nullptr));
        pushButton_Save->setProperty("btnStyle", QVariant(QApplication::translate("SystemSet", "normalBtnRed", nullptr)));
        pushButton_Cancel->setText(QApplication::translate("SystemSet", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SystemSet: public Ui_SystemSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMSET_H
