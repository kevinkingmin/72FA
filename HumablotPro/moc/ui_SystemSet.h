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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemSet
{
public:
    QLineEdit *lineEdit_CutOffThreshold;
    QLineEdit *lineEdit_ControlThreshold;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_20;
    QLineEdit *lineEdit_pip_15_min;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Test;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Cancel;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox_language;
    QComboBox *comboBox_run_sequence;
    QComboBox *comboBox_aspirate_sample;
    QComboBox *comboBox_vomit;
    QComboBox *comboBox_CompanyList;
    QComboBox *comboBox_beep_enable;
    QComboBox *comboBox_waste_liquid_tank_enable;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QLabel *label_3;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout;
    QLabel *label_28;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_7;
    QLabel *label_18;
    QLabel *label_19;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *lineEdit_RootPathReport;
    QLineEdit *lineEdit_RootPathPicture;
    QWidget *layoutWidget5;
    QGridLayout *gridLayout;
    QLabel *label_17;
    QLineEdit *lineEdit_week_finish_time;
    QLabel *label_16;
    QLineEdit *lineEdit_month_finish_time;
    QLabel *label_13;
    QLineEdit *lineEdit_month_filling_volume;
    QLabel *label_14;
    QLineEdit *lineEdit_week_filling_volume;
    QLabel *label_21;
    QLineEdit *lineEdit_monthly_maintenance_pump_calibration;
    QLabel *label_15;
    QLineEdit *lineEdit_between_two_drops_of_pump;
    QLabel *label_4;
    QLineEdit *lineEdit_between_two_drops_of_pump_max;
    QLabel *label_11;
    QLineEdit *lineEdit_system_filling_volume;
    QLabel *label_12;
    QLineEdit *lineEdit_system_wash_volume;
    QLabel *label_22;
    QLineEdit *lineEdit_system_wash_volume_2;
    QLabel *label_23;
    QLineEdit *lineEdit_system_wash_volume_3;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_5;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QWidget *layoutWidget7;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_55;
    QLabel *label_41;
    QLineEdit *lineEdit_Weight;
    QComboBox *comboBox_waste_liquid_tank_enable_2;
    QLabel *label_56;
    QPushButton *pushButtonPara;
    QLabel *label_29;
    QLineEdit *txtReportTitle;

    void setupUi(QWidget *SystemSet)
    {
        if (SystemSet->objectName().isEmpty())
            SystemSet->setObjectName(QString::fromUtf8("SystemSet"));
        SystemSet->resize(1650, 776);
        lineEdit_CutOffThreshold = new QLineEdit(SystemSet);
        lineEdit_CutOffThreshold->setObjectName(QString::fromUtf8("lineEdit_CutOffThreshold"));
        lineEdit_CutOffThreshold->setGeometry(QRect(1370, 817, 133, 20));
        lineEdit_ControlThreshold = new QLineEdit(SystemSet);
        lineEdit_ControlThreshold->setObjectName(QString::fromUtf8("lineEdit_ControlThreshold"));
        lineEdit_ControlThreshold->setGeometry(QRect(1370, 780, 133, 20));
        label_2 = new QLabel(SystemSet);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(1210, 817, 114, 16));
        label = new QLabel(SystemSet);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1230, 780, 96, 16));
        label_20 = new QLabel(SystemSet);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(1190, 780, 132, 16));
        lineEdit_pip_15_min = new QLineEdit(SystemSet);
        lineEdit_pip_15_min->setObjectName(QString::fromUtf8("lineEdit_pip_15_min"));
        lineEdit_pip_15_min->setGeometry(QRect(1320, 770, 133, 20));
        groupBox = new QGroupBox(SystemSet);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(280, 58, 1311, 641));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(1060, 560, 239, 61));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_Test = new QPushButton(layoutWidget);
        pushButton_Test->setObjectName(QString::fromUtf8("pushButton_Test"));

        horizontalLayout->addWidget(pushButton_Test);

        pushButton_Save = new QPushButton(layoutWidget);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));

        horizontalLayout->addWidget(pushButton_Save);

        pushButton_Cancel = new QPushButton(layoutWidget);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));

        horizontalLayout->addWidget(pushButton_Cancel);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(770, 160, 161, 291));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        comboBox_language = new QComboBox(layoutWidget1);
        comboBox_language->addItem(QString());
        comboBox_language->addItem(QString());
        comboBox_language->addItem(QString());
        comboBox_language->setObjectName(QString::fromUtf8("comboBox_language"));

        verticalLayout_2->addWidget(comboBox_language);

        comboBox_run_sequence = new QComboBox(layoutWidget1);
        comboBox_run_sequence->addItem(QString());
        comboBox_run_sequence->addItem(QString());
        comboBox_run_sequence->setObjectName(QString::fromUtf8("comboBox_run_sequence"));

        verticalLayout_2->addWidget(comboBox_run_sequence);

        comboBox_aspirate_sample = new QComboBox(layoutWidget1);
        comboBox_aspirate_sample->addItem(QString());
        comboBox_aspirate_sample->addItem(QString());
        comboBox_aspirate_sample->setObjectName(QString::fromUtf8("comboBox_aspirate_sample"));

        verticalLayout_2->addWidget(comboBox_aspirate_sample);

        comboBox_vomit = new QComboBox(layoutWidget1);
        comboBox_vomit->addItem(QString());
        comboBox_vomit->addItem(QString());
        comboBox_vomit->setObjectName(QString::fromUtf8("comboBox_vomit"));

        verticalLayout_2->addWidget(comboBox_vomit);

        comboBox_CompanyList = new QComboBox(layoutWidget1);
        comboBox_CompanyList->setObjectName(QString::fromUtf8("comboBox_CompanyList"));

        verticalLayout_2->addWidget(comboBox_CompanyList);

        comboBox_beep_enable = new QComboBox(layoutWidget1);
        comboBox_beep_enable->addItem(QString());
        comboBox_beep_enable->addItem(QString());
        comboBox_beep_enable->setObjectName(QString::fromUtf8("comboBox_beep_enable"));
        comboBox_beep_enable->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(comboBox_beep_enable);

        comboBox_waste_liquid_tank_enable = new QComboBox(layoutWidget1);
        comboBox_waste_liquid_tank_enable->addItem(QString());
        comboBox_waste_liquid_tank_enable->addItem(QString());
        comboBox_waste_liquid_tank_enable->setObjectName(QString::fromUtf8("comboBox_waste_liquid_tank_enable"));

        verticalLayout_2->addWidget(comboBox_waste_liquid_tank_enable);

        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(500, 80, 251, 71));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_3->addWidget(label_6);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_3->addWidget(label_3);

        layoutWidget3 = new QWidget(groupBox);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(500, 160, 251, 281));
        verticalLayout = new QVBoxLayout(layoutWidget3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_28 = new QLabel(layoutWidget3);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_28);

        label_8 = new QLabel(layoutWidget3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_8);

        label_9 = new QLabel(layoutWidget3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_9);

        label_10 = new QLabel(layoutWidget3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_10);

        label_7 = new QLabel(layoutWidget3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_7);

        label_18 = new QLabel(layoutWidget3);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_18);

        label_19 = new QLabel(layoutWidget3);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setLayoutDirection(Qt::LeftToRight);
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_19);

        layoutWidget4 = new QWidget(groupBox);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(770, 80, 511, 71));
        verticalLayout_4 = new QVBoxLayout(layoutWidget4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        lineEdit_RootPathReport = new QLineEdit(layoutWidget4);
        lineEdit_RootPathReport->setObjectName(QString::fromUtf8("lineEdit_RootPathReport"));

        verticalLayout_4->addWidget(lineEdit_RootPathReport);

        lineEdit_RootPathPicture = new QLineEdit(layoutWidget4);
        lineEdit_RootPathPicture->setObjectName(QString::fromUtf8("lineEdit_RootPathPicture"));

        verticalLayout_4->addWidget(lineEdit_RootPathPicture);

        layoutWidget5 = new QWidget(groupBox);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(60, 81, 281, 531));
        gridLayout = new QGridLayout(layoutWidget5);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_17 = new QLabel(layoutWidget5);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_17, 0, 0, 1, 1);

        lineEdit_week_finish_time = new QLineEdit(layoutWidget5);
        lineEdit_week_finish_time->setObjectName(QString::fromUtf8("lineEdit_week_finish_time"));

        gridLayout->addWidget(lineEdit_week_finish_time, 0, 1, 1, 1);

        label_16 = new QLabel(layoutWidget5);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_16, 1, 0, 1, 1);

        lineEdit_month_finish_time = new QLineEdit(layoutWidget5);
        lineEdit_month_finish_time->setObjectName(QString::fromUtf8("lineEdit_month_finish_time"));

        gridLayout->addWidget(lineEdit_month_finish_time, 1, 1, 1, 1);

        label_13 = new QLabel(layoutWidget5);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_13, 2, 0, 1, 1);

        lineEdit_month_filling_volume = new QLineEdit(layoutWidget5);
        lineEdit_month_filling_volume->setObjectName(QString::fromUtf8("lineEdit_month_filling_volume"));

        gridLayout->addWidget(lineEdit_month_filling_volume, 2, 1, 1, 1);

        label_14 = new QLabel(layoutWidget5);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_14, 3, 0, 1, 1);

        lineEdit_week_filling_volume = new QLineEdit(layoutWidget5);
        lineEdit_week_filling_volume->setObjectName(QString::fromUtf8("lineEdit_week_filling_volume"));

        gridLayout->addWidget(lineEdit_week_filling_volume, 3, 1, 1, 1);

        label_21 = new QLabel(layoutWidget5);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_21, 4, 0, 1, 1);

        lineEdit_monthly_maintenance_pump_calibration = new QLineEdit(layoutWidget5);
        lineEdit_monthly_maintenance_pump_calibration->setObjectName(QString::fromUtf8("lineEdit_monthly_maintenance_pump_calibration"));

        gridLayout->addWidget(lineEdit_monthly_maintenance_pump_calibration, 4, 1, 1, 1);

        label_15 = new QLabel(layoutWidget5);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_15, 5, 0, 1, 1);

        lineEdit_between_two_drops_of_pump = new QLineEdit(layoutWidget5);
        lineEdit_between_two_drops_of_pump->setObjectName(QString::fromUtf8("lineEdit_between_two_drops_of_pump"));

        gridLayout->addWidget(lineEdit_between_two_drops_of_pump, 5, 1, 1, 1);

        label_4 = new QLabel(layoutWidget5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 6, 0, 1, 1);

        lineEdit_between_two_drops_of_pump_max = new QLineEdit(layoutWidget5);
        lineEdit_between_two_drops_of_pump_max->setObjectName(QString::fromUtf8("lineEdit_between_two_drops_of_pump_max"));

        gridLayout->addWidget(lineEdit_between_two_drops_of_pump_max, 6, 1, 1, 1);

        label_11 = new QLabel(layoutWidget5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_11, 7, 0, 1, 1);

        lineEdit_system_filling_volume = new QLineEdit(layoutWidget5);
        lineEdit_system_filling_volume->setObjectName(QString::fromUtf8("lineEdit_system_filling_volume"));

        gridLayout->addWidget(lineEdit_system_filling_volume, 7, 1, 1, 1);

        label_12 = new QLabel(layoutWidget5);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_12, 8, 0, 1, 1);

        lineEdit_system_wash_volume = new QLineEdit(layoutWidget5);
        lineEdit_system_wash_volume->setObjectName(QString::fromUtf8("lineEdit_system_wash_volume"));

        gridLayout->addWidget(lineEdit_system_wash_volume, 8, 1, 1, 1);

        label_22 = new QLabel(layoutWidget5);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_22, 9, 0, 1, 1);

        lineEdit_system_wash_volume_2 = new QLineEdit(layoutWidget5);
        lineEdit_system_wash_volume_2->setObjectName(QString::fromUtf8("lineEdit_system_wash_volume_2"));

        gridLayout->addWidget(lineEdit_system_wash_volume_2, 9, 1, 1, 1);

        label_23 = new QLabel(layoutWidget5);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_23, 10, 0, 1, 1);

        lineEdit_system_wash_volume_3 = new QLineEdit(layoutWidget5);
        lineEdit_system_wash_volume_3->setObjectName(QString::fromUtf8("lineEdit_system_wash_volume_3"));

        gridLayout->addWidget(lineEdit_system_wash_volume_3, 10, 1, 1, 1);

        layoutWidget6 = new QWidget(groupBox);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(360, 80, 131, 241));
        verticalLayout_6 = new QVBoxLayout(layoutWidget6);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget6);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_6->addWidget(label_5);

        label_24 = new QLabel(layoutWidget6);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        verticalLayout_6->addWidget(label_24);

        label_25 = new QLabel(layoutWidget6);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        verticalLayout_6->addWidget(label_25);

        label_26 = new QLabel(layoutWidget6);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        verticalLayout_6->addWidget(label_26);

        label_27 = new QLabel(layoutWidget6);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        verticalLayout_6->addWidget(label_27);

        layoutWidget7 = new QWidget(groupBox);
        layoutWidget7->setObjectName(QString::fromUtf8("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(360, 420, 131, 191));
        verticalLayout_5 = new QVBoxLayout(layoutWidget7);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_30 = new QLabel(layoutWidget7);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        verticalLayout_5->addWidget(label_30);

        label_31 = new QLabel(layoutWidget7);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        verticalLayout_5->addWidget(label_31);

        label_32 = new QLabel(layoutWidget7);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        verticalLayout_5->addWidget(label_32);

        label_33 = new QLabel(layoutWidget7);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        verticalLayout_5->addWidget(label_33);

        label_55 = new QLabel(groupBox);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        label_55->setGeometry(QRect(630, 480, 120, 18));
        label_55->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_41 = new QLabel(groupBox);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setGeometry(QRect(940, 480, 66, 16));
        label_41->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_Weight = new QLineEdit(groupBox);
        lineEdit_Weight->setObjectName(QString::fromUtf8("lineEdit_Weight"));
        lineEdit_Weight->setGeometry(QRect(775, 470, 151, 41));
        comboBox_waste_liquid_tank_enable_2 = new QComboBox(groupBox);
        comboBox_waste_liquid_tank_enable_2->addItem(QString());
        comboBox_waste_liquid_tank_enable_2->addItem(QString());
        comboBox_waste_liquid_tank_enable_2->setObjectName(QString::fromUtf8("comboBox_waste_liquid_tank_enable_2"));
        comboBox_waste_liquid_tank_enable_2->setGeometry(QRect(770, 530, 159, 31));
        label_56 = new QLabel(groupBox);
        label_56->setObjectName(QString::fromUtf8("label_56"));
        label_56->setGeometry(QRect(630, 536, 120, 18));
        label_56->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButtonPara = new QPushButton(groupBox);
        pushButtonPara->setObjectName(QString::fromUtf8("pushButtonPara"));
        pushButtonPara->setGeometry(QRect(770, 570, 131, 31));
        label_29 = new QLabel(groupBox);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(60, 40, 131, 20));
        label_29->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        txtReportTitle = new QLineEdit(groupBox);
        txtReportTitle->setObjectName(QString::fromUtf8("txtReportTitle"));
        txtReportTitle->setGeometry(QRect(200, 30, 431, 31));

        retranslateUi(SystemSet);

        QMetaObject::connectSlotsByName(SystemSet);
    } // setupUi

    void retranslateUi(QWidget *SystemSet)
    {
        SystemSet->setWindowTitle(QApplication::translate("SystemSet", "SystemSet", nullptr));
        label_2->setText(QApplication::translate("SystemSet", "Cut Off\346\235\241\347\201\260\345\272\246\351\230\210\345\200\274\357\274\232", nullptr));
        label->setText(QApplication::translate("SystemSet", "\345\212\237\350\203\275\346\235\241\347\201\260\345\272\246\351\230\210\345\200\274\357\274\232", nullptr));
        label_20->setText(QApplication::translate("SystemSet", "\346\234\210\347\273\264\346\212\244\347\256\241\350\267\257\346\265\270\346\263\24115\345\210\206\351\222\237\357\274\232", nullptr));
        groupBox->setTitle(QString());
        pushButton_Test->setText(QApplication::translate("SystemSet", "\351\273\230\350\256\244\345\200\274", nullptr));
        pushButton_Test->setProperty("btnStyle", QVariant(QApplication::translate("SystemSet", "normalBtnGray", nullptr)));
        pushButton_Save->setText(QApplication::translate("SystemSet", "\344\277\235\345\255\230", nullptr));
        pushButton_Save->setProperty("btnStyle", QVariant(QApplication::translate("SystemSet", "normalBtnRed", nullptr)));
        pushButton_Cancel->setText(QApplication::translate("SystemSet", "\345\217\226\346\266\210", nullptr));
        comboBox_language->setItemText(0, QApplication::translate("SystemSet", "\344\270\255\346\226\207", nullptr));
        comboBox_language->setItemText(1, QApplication::translate("SystemSet", "\344\270\255\346\226\207", nullptr));
        comboBox_language->setItemText(2, QApplication::translate("SystemSet", "EN", nullptr));

        comboBox_run_sequence->setItemText(0, QApplication::translate("SystemSet", "Process1", nullptr));
        comboBox_run_sequence->setItemText(1, QApplication::translate("SystemSet", "defaultProcess", nullptr));

        comboBox_aspirate_sample->setItemText(0, QApplication::translate("SystemSet", "\346\211\223\345\274\200", nullptr));
        comboBox_aspirate_sample->setItemText(1, QApplication::translate("SystemSet", "\345\205\263\351\227\255", nullptr));

        comboBox_vomit->setItemText(0, QApplication::translate("SystemSet", "\346\211\223\345\274\200", nullptr));
        comboBox_vomit->setItemText(1, QApplication::translate("SystemSet", "\345\205\263\351\227\255", nullptr));

        comboBox_beep_enable->setItemText(0, QApplication::translate("SystemSet", "\345\220\246", nullptr));
        comboBox_beep_enable->setItemText(1, QApplication::translate("SystemSet", "\346\230\257", nullptr));

        comboBox_waste_liquid_tank_enable->setItemText(0, QApplication::translate("SystemSet", "\345\220\246", nullptr));
        comboBox_waste_liquid_tank_enable->setItemText(1, QApplication::translate("SystemSet", "\346\230\257", nullptr));

        label_6->setText(QApplication::translate("SystemSet", "\346\265\213\350\257\225\346\212\245\345\221\212\344\277\235\345\255\230\346\240\271\347\233\256\345\275\225\357\274\232", nullptr));
        label_3->setText(QApplication::translate("SystemSet", "\346\265\213\350\257\225\345\233\276\345\203\217\344\277\235\345\255\230\346\240\271\347\233\256\345\275\225\357\274\232", nullptr));
        label_28->setText(QApplication::translate("SystemSet", "\350\257\255\350\250\200\351\200\211\346\213\251\357\274\232", nullptr));
        label_8->setText(QApplication::translate("SystemSet", "\346\227\266\345\272\217\351\200\211\346\213\251\357\274\232", nullptr));
        label_9->setText(QApplication::translate("SystemSet", "\346\240\267\346\234\254\351\222\210\345\220\270\346\240\267\346\266\262\344\275\215\346\216\242\346\265\213\351\200\211\346\213\251\357\274\232", nullptr));
        label_10->setText(QApplication::translate("SystemSet", "\346\240\267\346\234\254\351\222\210\345\220\220\346\240\267\346\266\262\344\275\215\346\216\242\346\265\213\351\200\211\346\213\251\357\274\232", nullptr));
        label_7->setText(QApplication::translate("SystemSet", "\345\275\223\345\211\215\344\275\277\347\224\250\347\232\204\350\206\234\346\235\241\346\211\200\345\261\236\345\205\254\345\217\270\357\274\232", nullptr));
        label_18->setText(QApplication::translate("SystemSet", "\350\234\202\351\270\243\345\231\250\345\243\260\351\237\263\344\275\277\350\203\275\357\274\232", nullptr));
        label_19->setText(QApplication::translate("SystemSet", "\345\272\237\346\266\262\346\241\266\344\275\277\350\203\275\357\274\232", nullptr));
        label_17->setText(QApplication::translate("SystemSet", "\345\221\250\347\273\264\346\212\244\346\265\270\346\263\241\346\227\266\351\227\264\357\274\232", nullptr));
        label_16->setText(QApplication::translate("SystemSet", "\346\234\210\347\273\264\346\212\244\346\265\270\346\263\241\346\227\266\351\227\264\357\274\232", nullptr));
        label_13->setText(QApplication::translate("SystemSet", "\346\234\210\347\273\264\346\212\244\346\263\265\345\205\205\347\201\214\351\207\217\357\274\232", nullptr));
        label_14->setText(QApplication::translate("SystemSet", "\345\221\250\347\273\264\346\212\244\346\263\265\345\205\205\347\201\214\351\207\217\357\274\232", nullptr));
        label_21->setText(QApplication::translate("SystemSet", "\346\234\210\347\273\264\346\212\244\346\263\265\346\240\241\345\207\206\351\207\217\357\274\232", nullptr));
        label_15->setText(QApplication::translate("SystemSet", "\346\263\265\346\240\241\345\207\206\344\270\213\351\231\220\345\200\274\357\274\232", nullptr));
        label_4->setText(QApplication::translate("SystemSet", "\346\263\265\346\240\241\345\207\206\344\270\212\351\231\220\345\200\274\357\274\232", nullptr));
        label_11->setText(QApplication::translate("SystemSet", "\347\263\273\347\273\237\346\266\262\345\205\205\347\201\214\344\275\223\347\247\257\357\274\232", nullptr));
        label_12->setText(QApplication::translate("SystemSet", "\347\263\273\347\273\237\346\266\262\346\270\205\346\264\227\344\275\223\347\247\257\357\274\232", nullptr));
        label_22->setText(QApplication::translate("SystemSet", "\345\205\263\346\234\272\346\216\222\347\251\272\346\266\262\351\207\217\357\274\232", nullptr));
        label_23->setText(QApplication::translate("SystemSet", "\346\263\265\345\233\236\346\265\201\346\214\207\345\256\232\346\266\262\351\207\217\357\274\232", nullptr));
        label_5->setText(QApplication::translate("SystemSet", "5-240\345\210\206\351\222\237", nullptr));
        label_24->setText(QApplication::translate("SystemSet", "5-240\345\210\206\351\222\237", nullptr));
        label_25->setText(QApplication::translate("SystemSet", "1-10ml", nullptr));
        label_26->setText(QApplication::translate("SystemSet", "1-10ml", nullptr));
        label_27->setText(QApplication::translate("SystemSet", "300-700ul", nullptr));
        label_30->setText(QApplication::translate("SystemSet", "1-5ml", nullptr));
        label_31->setText(QApplication::translate("SystemSet", "1-5ml", nullptr));
        label_32->setText(QApplication::translate("SystemSet", "1-5ml", nullptr));
        label_33->setText(QApplication::translate("SystemSet", "1-5ml", nullptr));
        label_55->setText(QApplication::translate("SystemSet", "\346\257\253\347\261\263\345\257\271\345\272\224\345\203\217\347\264\240\357\274\232", nullptr));
        label_41->setText(QApplication::translate("SystemSet", "mm", nullptr));
        lineEdit_Weight->setText(QApplication::translate("SystemSet", "18.481", nullptr));
        comboBox_waste_liquid_tank_enable_2->setItemText(0, QApplication::translate("SystemSet", "\345\220\246", nullptr));
        comboBox_waste_liquid_tank_enable_2->setItemText(1, QApplication::translate("SystemSet", "\346\230\257", nullptr));

        label_56->setText(QApplication::translate("SystemSet", "\346\213\215\347\205\247\345\212\237\350\203\275\357\274\232", nullptr));
        pushButtonPara->setText(QApplication::translate("SystemSet", "\345\217\202\346\225\260", nullptr));
        label_29->setText(QApplication::translate("SystemSet", "\346\211\223\345\215\260\346\212\245\345\221\212\346\240\207\351\242\230\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SystemSet: public Ui_SystemSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMSET_H
