#pragma once

#include <QWidget>
#include "ui_ProcessDataList.h"
#include "ProcessData.h"

class Instrument;
class ProcessDataList : public QWidget
{
    Q_OBJECT
    struct Process
    {
        QString id;
        QString processName;
        Process()
            :id("")
            ,processName("")
        {}
    };

    struct ProcessStep
    {
        QString id;
        QString stepDes;
        ProcessStep():
            id("")
          ,stepDes("")
        {}
    };

public:
    ProcessDataList(QWidget *parent = Q_NULLPTR);
    ~ProcessDataList();

public:
    void setCurrentCompany(const QString &companyName,const QString &companyId);
private:
    void InitTbProcess();
    void InitTbProcessSteps();
    void addTbProcessContent(int row, int column, QString content);
    void addTbProcessStepContent(int row, int column, QString content);

private slots:
    void on_tbProcess_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_tbProcess_cellClicked();
	void on_Add_Button_clicked();
	void on_Modify_Button_clicked();
	void on_Delete_Button_clicked();
    void on_back_Button_clicked();
    void on_btnAddProcess_clicked();
    void on_btnDeleteProcess_clicked();
signals:
    void sglBackSystemSet();
private:
    Ui::ProcessDataList ui;
    QString m_companyName;
    QString m_companyId;
    ProcessData *_processData;
};
