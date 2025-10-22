#pragma once

#include <QDialog>
#include "ui_ProcessData.h"
#include <QLineEdit>
#include <QComboBox>

class ProcessData : public QDialog
{
	Q_OBJECT

    struct ComboBoxData
    {
        QString itemData;
        QString itemText;
        ComboBoxData()
            :itemData("")
            ,itemText("")
        {}
        ComboBoxData(const QString &data,const QString &text)
            :itemData(data)
            ,itemText(text)
        {}
    };

public:
    ProcessData(QWidget *parent = Q_NULLPTR);
    ~ProcessData();
private slots:
    void on_pushButton_Save_clicked();
    void on_pushButton_Cancel_clicked();
    void on_cmbStepType_currentIndexChanged(int index);
public:
    void SetUI(bool modify);
    void setBModify(bool bModify);
    void setStepId(const QString &stepId);
    void setProcessId(const QString &processId);
private:
    Ui::ProcessData ui;
    bool m_bModify;
    QVector<QWidget*> _txtVect;
    QRegExp _doubleReg;
    QString _stepId;
    QString _processId;
    QVector<QString> _actTypeVect;
    int _currentSelectStep;
};
