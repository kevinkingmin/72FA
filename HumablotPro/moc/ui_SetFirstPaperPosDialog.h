/********************************************************************************
** Form generated from reading UI file 'SetFirstPaperPosDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETFIRSTPAPERPOSDIALOG_H
#define UI_SETFIRSTPAPERPOSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetFirstPaperPosDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QWidget *widgetTop;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonClose;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QLineEdit *txtStartPos;
    QSpacerItem *horizontalSpacer;
    QLineEdit *txtStartSlot;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnConfig;
    QLabel *label_4;
    QLabel *label_5;
    QComboBox *comboBox;
    QLabel *label_6;
    QComboBox *comboBox_2;
    QLabel *label;
    QLabel *label_3;

    void setupUi(QDialog *SetFirstPaperPosDialog)
    {
        if (SetFirstPaperPosDialog->objectName().isEmpty())
            SetFirstPaperPosDialog->setObjectName(QString::fromUtf8("SetFirstPaperPosDialog"));
        SetFirstPaperPosDialog->resize(403, 294);
        SetFirstPaperPosDialog->setModal(false);
        layoutWidget = new QWidget(SetFirstPaperPosDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 10, 411, 32));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        widgetTop = new QWidget(layoutWidget);
        widgetTop->setObjectName(QString::fromUtf8("widgetTop"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetTop->sizePolicy().hasHeightForWidth());
        widgetTop->setSizePolicy(sizePolicy);
        widgetTop->setMinimumSize(QSize(0, 30));
        widgetTop->setMaximumSize(QSize(16777215, 30));
        layoutWidget1 = new QWidget(widgetTop);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 401, 28));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pushButtonClose = new QPushButton(layoutWidget1);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setMinimumSize(QSize(26, 26));
        pushButtonClose->setMaximumSize(QSize(26, 26));

        horizontalLayout_4->addWidget(pushButtonClose);


        verticalLayout_4->addWidget(widgetTop);

        layoutWidget2 = new QWidget(SetFirstPaperPosDialog);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 270, 101, 68));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        txtStartPos = new QLineEdit(layoutWidget2);
        txtStartPos->setObjectName(QString::fromUtf8("txtStartPos"));
        txtStartPos->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(txtStartPos, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        txtStartSlot = new QLineEdit(layoutWidget2);
        txtStartSlot->setObjectName(QString::fromUtf8("txtStartSlot"));
        txtStartSlot->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(txtStartSlot, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        btnConfig = new QPushButton(SetFirstPaperPosDialog);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(250, 240, 100, 35));
        btnConfig->setMinimumSize(QSize(100, 35));
        btnConfig->setMaximumSize(QSize(100, 16777215));
        label_4 = new QLabel(SetFirstPaperPosDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 40, 401, 20));
        label_5 = new QLabel(SetFirstPaperPosDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 120, 151, 30));
        label_5->setLayoutDirection(Qt::RightToLeft);
        label_5->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox = new QComboBox(SetFirstPaperPosDialog);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(180, 110, 151, 41));
        label_6 = new QLabel(SetFirstPaperPosDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 170, 151, 30));
        label_6->setLayoutDirection(Qt::RightToLeft);
        label_6->setStyleSheet(QString::fromUtf8("margin-right:20px;\n"
"margin-left:10px"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_2 = new QComboBox(SetFirstPaperPosDialog);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(180, 160, 151, 41));
        label = new QLabel(SetFirstPaperPosDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(340, 120, 6, 30));
        label->setStyleSheet(QString::fromUtf8("color:red;"));
        label_3 = new QLabel(SetFirstPaperPosDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(340, 170, 6, 30));
        label_3->setStyleSheet(QString::fromUtf8("color:red;"));

        retranslateUi(SetFirstPaperPosDialog);

        QMetaObject::connectSlotsByName(SetFirstPaperPosDialog);
    } // setupUi

    void retranslateUi(QDialog *SetFirstPaperPosDialog)
    {
        SetFirstPaperPosDialog->setWindowTitle(QApplication::translate("SetFirstPaperPosDialog", "\350\206\234\345\274\217", nullptr));
        SetFirstPaperPosDialog->setProperty("dialogStyle", QVariant(QApplication::translate("SetFirstPaperPosDialog", "BGStyle", nullptr)));
        label_2->setText(QApplication::translate("SetFirstPaperPosDialog", "      \350\206\234\346\235\241\350\265\267\345\247\213\344\275\215\347\275\256\350\256\276\347\275\256", nullptr));
        label_2->setProperty("lblStyle", QVariant(QApplication::translate("SetFirstPaperPosDialog", "lblNormal", nullptr)));
        pushButtonClose->setText(QString());
        txtStartPos->setText(QApplication::translate("SetFirstPaperPosDialog", "1", nullptr));
        txtStartSlot->setText(QApplication::translate("SetFirstPaperPosDialog", "1", nullptr));
        btnConfig->setText(QApplication::translate("SetFirstPaperPosDialog", "\347\241\256  \345\256\232", nullptr));
        btnConfig->setProperty("btnStyle", QVariant(QApplication::translate("SetFirstPaperPosDialog", "normalBtnRed", nullptr)));
        label_4->setText(QApplication::translate("SetFirstPaperPosDialog", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200"
                        "\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
        label_5->setText(QApplication::translate("SetFirstPaperPosDialog", "\346\211\230\347\233\230\344\275\215\347\275\256", nullptr));
        label_5->setProperty("lblStyle", QVariant(QString()));
        comboBox->setItemText(0, QApplication::translate("SetFirstPaperPosDialog", "1", nullptr));
        comboBox->setItemText(1, QApplication::translate("SetFirstPaperPosDialog", "2", nullptr));

        label_6->setText(QApplication::translate("SetFirstPaperPosDialog", "\345\274\200\345\247\213\344\275\215\347\275\256", nullptr));
        label_6->setProperty("lblStyle", QVariant(QString()));
        comboBox_2->setItemText(0, QApplication::translate("SetFirstPaperPosDialog", "1", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("SetFirstPaperPosDialog", "2", nullptr));
        comboBox_2->setItemText(2, QApplication::translate("SetFirstPaperPosDialog", "3", nullptr));
        comboBox_2->setItemText(3, QApplication::translate("SetFirstPaperPosDialog", "4", nullptr));
        comboBox_2->setItemText(4, QApplication::translate("SetFirstPaperPosDialog", "5", nullptr));
        comboBox_2->setItemText(5, QApplication::translate("SetFirstPaperPosDialog", "6", nullptr));
        comboBox_2->setItemText(6, QApplication::translate("SetFirstPaperPosDialog", "7", nullptr));
        comboBox_2->setItemText(7, QApplication::translate("SetFirstPaperPosDialog", "8", nullptr));
        comboBox_2->setItemText(8, QApplication::translate("SetFirstPaperPosDialog", "9", nullptr));
        comboBox_2->setItemText(9, QApplication::translate("SetFirstPaperPosDialog", "10", nullptr));
        comboBox_2->setItemText(10, QApplication::translate("SetFirstPaperPosDialog", "11", nullptr));
        comboBox_2->setItemText(11, QApplication::translate("SetFirstPaperPosDialog", "12", nullptr));
        comboBox_2->setItemText(12, QApplication::translate("SetFirstPaperPosDialog", "13", nullptr));
        comboBox_2->setItemText(13, QApplication::translate("SetFirstPaperPosDialog", "14", nullptr));
        comboBox_2->setItemText(14, QApplication::translate("SetFirstPaperPosDialog", "15", nullptr));
        comboBox_2->setItemText(15, QApplication::translate("SetFirstPaperPosDialog", "16", nullptr));
        comboBox_2->setItemText(16, QApplication::translate("SetFirstPaperPosDialog", "17", nullptr));
        comboBox_2->setItemText(17, QApplication::translate("SetFirstPaperPosDialog", "18", nullptr));
        comboBox_2->setItemText(18, QApplication::translate("SetFirstPaperPosDialog", "19", nullptr));
        comboBox_2->setItemText(19, QApplication::translate("SetFirstPaperPosDialog", "20", nullptr));
        comboBox_2->setItemText(20, QApplication::translate("SetFirstPaperPosDialog", "21", nullptr));
        comboBox_2->setItemText(21, QApplication::translate("SetFirstPaperPosDialog", "22", nullptr));
        comboBox_2->setItemText(22, QApplication::translate("SetFirstPaperPosDialog", "23", nullptr));
        comboBox_2->setItemText(23, QApplication::translate("SetFirstPaperPosDialog", "24", nullptr));
        comboBox_2->setItemText(24, QApplication::translate("SetFirstPaperPosDialog", "25", nullptr));
        comboBox_2->setItemText(25, QApplication::translate("SetFirstPaperPosDialog", "26", nullptr));
        comboBox_2->setItemText(26, QApplication::translate("SetFirstPaperPosDialog", "27", nullptr));
        comboBox_2->setItemText(27, QApplication::translate("SetFirstPaperPosDialog", "28", nullptr));
        comboBox_2->setItemText(28, QApplication::translate("SetFirstPaperPosDialog", "29", nullptr));
        comboBox_2->setItemText(29, QApplication::translate("SetFirstPaperPosDialog", "30", nullptr));
        comboBox_2->setItemText(30, QApplication::translate("SetFirstPaperPosDialog", "31", nullptr));
        comboBox_2->setItemText(31, QApplication::translate("SetFirstPaperPosDialog", "32", nullptr));
        comboBox_2->setItemText(32, QApplication::translate("SetFirstPaperPosDialog", "33", nullptr));
        comboBox_2->setItemText(33, QApplication::translate("SetFirstPaperPosDialog", "34", nullptr));
        comboBox_2->setItemText(34, QApplication::translate("SetFirstPaperPosDialog", "35", nullptr));
        comboBox_2->setItemText(35, QApplication::translate("SetFirstPaperPosDialog", "36", nullptr));

        label->setText(QApplication::translate("SetFirstPaperPosDialog", "*", nullptr));
        label_3->setText(QApplication::translate("SetFirstPaperPosDialog", "*", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetFirstPaperPosDialog: public Ui_SetFirstPaperPosDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETFIRSTPAPERPOSDIALOG_H
