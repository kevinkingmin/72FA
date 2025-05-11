/********************************************************************************
** Form generated from reading UI file 'Camera.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_H
#define UI_CAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Camera
{
public:
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_CameraSetting;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QPushButton *pushButton_Open;
    QPushButton *pushButton_Display;
    QPushButton *pushButton_Close;
    QPushButton *pushButton_SaveFile;
    QLabel *label;
    QGridLayout *gridLayout_3;
    QPushButton *PushButton_PictureAnalysis;
    QPushButton *PushButton_ResultList;
    QPushButton *pushButtonCutImage;

    void setupUi(QWidget *Camera)
    {
        if (Camera->objectName().isEmpty())
            Camera->setObjectName(QString::fromUtf8("Camera"));
        Camera->resize(1033, 781);
        gridLayout_5 = new QGridLayout(Camera);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        pushButton_CameraSetting = new QPushButton(Camera);
        pushButton_CameraSetting->setObjectName(QString::fromUtf8("pushButton_CameraSetting"));

        gridLayout_2->addWidget(pushButton_CameraSetting, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_Open = new QPushButton(Camera);
        pushButton_Open->setObjectName(QString::fromUtf8("pushButton_Open"));

        gridLayout->addWidget(pushButton_Open, 0, 0, 1, 1);

        pushButton_Display = new QPushButton(Camera);
        pushButton_Display->setObjectName(QString::fromUtf8("pushButton_Display"));

        gridLayout->addWidget(pushButton_Display, 0, 1, 1, 1);

        pushButton_Close = new QPushButton(Camera);
        pushButton_Close->setObjectName(QString::fromUtf8("pushButton_Close"));

        gridLayout->addWidget(pushButton_Close, 0, 2, 1, 1);

        pushButton_SaveFile = new QPushButton(Camera);
        pushButton_SaveFile->setObjectName(QString::fromUtf8("pushButton_SaveFile"));

        gridLayout->addWidget(pushButton_SaveFile, 0, 3, 1, 1);


        gridLayout_4->addLayout(gridLayout, 1, 0, 1, 1);

        label = new QLabel(Camera);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 2, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        PushButton_PictureAnalysis = new QPushButton(Camera);
        PushButton_PictureAnalysis->setObjectName(QString::fromUtf8("PushButton_PictureAnalysis"));

        gridLayout_3->addWidget(PushButton_PictureAnalysis, 0, 0, 1, 1);

        PushButton_ResultList = new QPushButton(Camera);
        PushButton_ResultList->setObjectName(QString::fromUtf8("PushButton_ResultList"));

        gridLayout_3->addWidget(PushButton_ResultList, 0, 1, 1, 1);

        pushButtonCutImage = new QPushButton(Camera);
        pushButtonCutImage->setObjectName(QString::fromUtf8("pushButtonCutImage"));

        gridLayout_3->addWidget(pushButtonCutImage, 0, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 3, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);


        retranslateUi(Camera);

        QMetaObject::connectSlotsByName(Camera);
    } // setupUi

    void retranslateUi(QWidget *Camera)
    {
        Camera->setWindowTitle(QApplication::translate("Camera", "Camera", nullptr));
        pushButton_CameraSetting->setText(QApplication::translate("Camera", "\347\233\270\346\234\272\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        pushButton_Open->setText(QApplication::translate("Camera", "\346\211\223\345\274\200", nullptr));
        pushButton_Display->setText(QApplication::translate("Camera", "\346\230\276\347\244\272", nullptr));
        pushButton_Close->setText(QApplication::translate("Camera", "\345\205\263\351\227\255", nullptr));
        pushButton_SaveFile->setText(QApplication::translate("Camera", "\344\277\235\345\255\230\346\226\207\344\273\266", nullptr));
        label->setText(QApplication::translate("Camera", "TextLabel", nullptr));
        PushButton_PictureAnalysis->setText(QApplication::translate("Camera", "\345\233\276\345\203\217\345\210\206\346\236\220", nullptr));
        PushButton_ResultList->setText(QApplication::translate("Camera", "\345\233\276\345\203\217\345\210\206\346\236\220\347\273\223\346\236\234\345\210\227\350\241\250", nullptr));
        pushButtonCutImage->setText(QApplication::translate("Camera", "\346\210\252\345\233\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Camera: public Ui_Camera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_H
