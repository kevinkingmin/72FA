/********************************************************************************
** Form generated from reading UI file 'UserManageWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMANAGEWIDGET_H
#define UI_USERMANAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserManageWidget
{
public:
    QTableWidget *tableWidget_Group;
    QLabel *label;
    QLineEdit *lineEditUserName;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget_Users;
    QLabel *label_2;
    QLineEdit *lineEditUserName33;
    QLabel *label_3;
    QLineEdit *lineEditPassword;
    QPushButton *Add_Button;
    QPushButton *Modify_Button;
    QPushButton *Delete_Button;

    void setupUi(QWidget *UserManageWidget)
    {
        if (UserManageWidget->objectName().isEmpty())
            UserManageWidget->setObjectName(QString::fromUtf8("UserManageWidget"));
        UserManageWidget->resize(1200, 675);
        tableWidget_Group = new QTableWidget(UserManageWidget);
        if (tableWidget_Group->columnCount() < 1)
            tableWidget_Group->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_Group->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget_Group->setObjectName(QString::fromUtf8("tableWidget_Group"));
        tableWidget_Group->setGeometry(QRect(50, 50, 256, 581));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(12);
        tableWidget_Group->setFont(font);
        label = new QLabel(UserManageWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 10, 161, 31));
        label->setFont(font);
        lineEditUserName = new QLineEdit(UserManageWidget);
        lineEditUserName->setObjectName(QString::fromUtf8("lineEditUserName"));
        lineEditUserName->setGeometry(QRect(980, 10, 31, 21));
        layoutWidget = new QWidget(UserManageWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(323, 54, 441, 571));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget_Users = new QTableWidget(layoutWidget);
        if (tableWidget_Users->columnCount() < 3)
            tableWidget_Users->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_Users->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_Users->setHorizontalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_Users->setHorizontalHeaderItem(2, __qtablewidgetitem3);
        tableWidget_Users->setObjectName(QString::fromUtf8("tableWidget_Users"));
        tableWidget_Users->setFont(font);

        gridLayout->addWidget(tableWidget_Users, 0, 0, 1, 3);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEditUserName33 = new QLineEdit(layoutWidget);
        lineEditUserName33->setObjectName(QString::fromUtf8("lineEditUserName33"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("3ds"));
        font1.setPointSize(9);
        lineEditUserName33->setFont(font1);

        gridLayout->addWidget(lineEditUserName33, 1, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEditPassword = new QLineEdit(layoutWidget);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));

        gridLayout->addWidget(lineEditPassword, 2, 1, 1, 1);

        Add_Button = new QPushButton(layoutWidget);
        Add_Button->setObjectName(QString::fromUtf8("Add_Button"));
        Add_Button->setFont(font);

        gridLayout->addWidget(Add_Button, 3, 0, 1, 1);

        Modify_Button = new QPushButton(layoutWidget);
        Modify_Button->setObjectName(QString::fromUtf8("Modify_Button"));
        Modify_Button->setFont(font);

        gridLayout->addWidget(Modify_Button, 3, 1, 1, 1);

        Delete_Button = new QPushButton(layoutWidget);
        Delete_Button->setObjectName(QString::fromUtf8("Delete_Button"));
        Delete_Button->setFont(font);

        gridLayout->addWidget(Delete_Button, 3, 2, 1, 1);


        retranslateUi(UserManageWidget);

        QMetaObject::connectSlotsByName(UserManageWidget);
    } // setupUi

    void retranslateUi(QWidget *UserManageWidget)
    {
        UserManageWidget->setWindowTitle(QApplication::translate("UserManageWidget", "UserManageWidget", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_Group->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("UserManageWidget", "\346\235\203\351\231\220\347\273\204\345\220\215", nullptr));
        label->setText(QApplication::translate("UserManageWidget", "\347\224\250\346\210\267\347\256\241\347\220\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_Users->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("UserManageWidget", "No", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_Users->horizontalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("UserManageWidget", "\347\224\250\346\210\267\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_Users->horizontalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("UserManageWidget", "\345\257\206\347\240\201", nullptr));
        label_2->setText(QApplication::translate("UserManageWidget", "\347\224\250 \346\210\267 \345\220\215\357\274\232", nullptr));
        label_3->setText(QApplication::translate("UserManageWidget", "\345\257\206    \347\240\201\357\274\232", nullptr));
        Add_Button->setText(QApplication::translate("UserManageWidget", "\350\277\275\345\212\240", nullptr));
        Add_Button->setProperty("btnStyle", QVariant(QApplication::translate("UserManageWidget", "normalBtnpink", nullptr)));
        Modify_Button->setText(QApplication::translate("UserManageWidget", "\344\277\256\346\224\271", nullptr));
        Modify_Button->setProperty("btnStyle", QVariant(QApplication::translate("UserManageWidget", "normalBtnpink", nullptr)));
        Delete_Button->setText(QApplication::translate("UserManageWidget", "\345\210\240\351\231\244", nullptr));
        Delete_Button->setProperty("btnStyle", QVariant(QApplication::translate("UserManageWidget", "normalBtnpink", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class UserManageWidget: public Ui_UserManageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMANAGEWIDGET_H
