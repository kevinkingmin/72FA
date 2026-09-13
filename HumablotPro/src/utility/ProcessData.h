#pragma once

#include <QDialog>
#include "ui_ProcessData.h"
#include <QLineEdit>
#include <QComboBox>
#include <QMap>

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
    void updateSampleUlByType(QComboBox *typeBox, QLineEdit *ulEdit);
private:
    Ui::ProcessData ui;
    bool m_bModify;
    QVector<QWidget*> _txtVect;
    QRegExp _doubleReg;
    QString _stepId;
    QString _processId;
    QVector<QString> _actTypeVect;
    int _currentSelectStep;
    // 当前加样本步骤已配置的样本量 (key=样本类型)
    QMap<int, double> _sampleUlMap;
};
