#include "ProcessDataList.h"
#include "AddProcess.h"
#include <QMessageBox>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../comm/GlobalData.h"
#include <QDebug>
#include "../Include/DAO/baseSet/ProcessParameterDao.h"
#include "../Include/DAO/baseSet/ProcessDao.h"
#include "../Include/Model/baseSet/ProcessParameterModel.h"
#include "../Include/Model/baseSet/ProcessModel.h"

ProcessDataList::ProcessDataList(QWidget *parent): QWidget(parent)
  ,m_companyName("")
  ,m_companyId("")
  ,_processData(new ProcessData(this))
{
	ui.setupUi(this);
    InitTbProcess();
    InitTbProcessSteps();
    ui.Add_Button->setText(GlobalData::LoadLanguageInfo("K1764"));
    ui.Modify_Button->setText(GlobalData::LoadLanguageInfo("K1765"));
    ui.Delete_Button->setText(GlobalData::LoadLanguageInfo("K1766"));
}

ProcessDataList::~ProcessDataList()
{
}

void ProcessDataList::setCurrentCompany(const QString &companyName, const QString &companyId)
{
    m_companyName=companyName;
    m_companyId=companyId;
    ui.label->setText(GlobalData::LoadLanguageInfo("K1763")+":"+companyName);
    ui.tbProcess->setRowCount(0);

    ProcessDao* dao = ProcessDao::instance();
    QVector<ProcessModel> processModelVect = dao->getModels(companyId.toInt());//调用接口,加载流程
    QVector<Process>processVect;
    for(const ProcessModel& model : processModelVect)
    {
        processVect.append(Process(QString::number(model.getId()), model.getProcessName()));
    }

    for(int i=0;i<processVect.count();i++)
    {
        ui.tbProcess->insertRow(i);
        auto p=processVect.at(i);
        addTbProcessContent(i, 0, QString::number(i+1));
        addTbProcessContent(i, 1, p.processName);
        addTbProcessContent(i, 2, p.id);
    }
    if(ui.tbProcess->rowCount()>0)
    {
        ui.tbProcess->selectRow(0);
    }
}

void ProcessDataList::InitTbProcessSteps()
{
    QHeaderView* headerView = ui.tbProcessSteps->verticalHeader();
	headerView->setHidden(true);
    ui.tbProcessSteps->horizontalHeader()->setStretchLastSection(true);
    ui.tbProcessSteps->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tbProcessSteps->setSelectionMode(QAbstractItemView::SingleSelection);
    ui.tbProcessSteps->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.tbProcessSteps->setSortingEnabled(false);
    ui.tbProcessSteps->setAlternatingRowColors(true);
    ui.tbProcessSteps->setShowGrid(true);
	QStringList headerString;
    QString sz1 = GlobalData::LoadLanguageInfo("K1767");
    QString sz2 = GlobalData::LoadLanguageInfo("K1768");
    headerString <<  sz1 << sz2<<"id";
    ui.tbProcessSteps->setHorizontalHeaderLabels(headerString);
    ui.tbProcessSteps->setColumnWidth(0, 55);
    ui.tbProcessSteps->setColumnHidden(2,true);
}

void ProcessDataList::InitTbProcess()
{
    ui.tbProcess->setRowCount(0);
    QHeaderView* headerView = ui.tbProcess->verticalHeader();
	headerView->setHidden(true);
    ui.tbProcess->horizontalHeader()->setStretchLastSection(true);
    ui.tbProcess->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tbProcess->setSelectionMode(QAbstractItemView::SingleSelection);
    ui.tbProcess->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QStringList headerString;
    headerString << GlobalData::LoadLanguageInfo("K1767")<<GlobalData::LoadLanguageInfo("K1769")<<"id";
    ui.tbProcess->setHorizontalHeaderLabels(headerString);
    ui.tbProcess->setShowGrid(true);
    ui.tbProcess->setAlternatingRowColors(true);
    ui.tbProcess->setColumnWidth(0, 55);
    ui.tbProcess->setColumnHidden(2,true);
}


void ProcessDataList::addTbProcessContent(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
    if(column==0)
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui.tbProcess->setItem(row, column, item);
}

void ProcessDataList::addTbProcessStepContent(int row, int column, QString content)
{
    QTableWidgetItem *item = new QTableWidgetItem(content);
    if(column==0)
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui.tbProcessSteps->setItem(row, column, item);
}

void ProcessDataList::on_tbProcess_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(currentRow)
    Q_UNUSED(currentColumn)
    Q_UNUSED(previousRow)
    Q_UNUSED(previousColumn)
//    on_tbProcess_cellClicked();
}

void ProcessDataList::on_tbProcess_cellClicked()
{
    qDebug()<<"on_tbProcess_cellClicked"<<ui.tbProcess->rowCount()<<ui.tbProcess->currentRow();
    if(ui.tbProcess->rowCount()<=0) return;
    // 获取选中行
    int currentRow = ui.tbProcess->currentRow();
    // 获取流程名称
	currentRow = currentRow >= 0 ? currentRow : 0;
    QString processName = ui.tbProcess->item(currentRow, 1)->text();
    ui.tbProcessSteps->setRowCount(0);
    QVector<ProcessStep> processStepsVect;//调用接口,加载流程步骤
    ProcessParameterDao* dao = ProcessParameterDao::instance();
    //调用接口,加载流程
    int intRow = ui.tbProcess->currentRow();
    int processId = (ui.tbProcess->item(intRow, 2)->text()).toInt();
    QVector<ProcessParameterModel> models = dao->getAllRows(processId);
    qDebug()<<"processId"<<processId<<models.count();
    for (auto &model : models)
    {
        model.parsingParas();
        qDebug()<<"model"<<model.getActCode()<<model.toShowString();
        ProcessStep step;
        step.id = QString::number(model.getId());
        step.stepDes = model.toShowString();
        processStepsVect.append(step);
    }

    for(int i=0;i<processStepsVect.count();i++)
    {
        ui.tbProcessSteps->insertRow(i);
        ProcessStep step=processStepsVect.at(i);
        addTbProcessStepContent(i, 0, QString::number(i));
        addTbProcessStepContent(i,1,step.stepDes);
        addTbProcessStepContent(i,2,step.id);
    }
}

void ProcessDataList::on_Add_Button_clicked()
{
    int intRow = ui.tbProcess->currentRow();
    if(intRow<0)
    {
        QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180"),GlobalData::LoadLanguageInfo("K1788"),GlobalData::LoadLanguageInfo("K1181"));
        return;
    }
    _processData->setBModify(false);
    _processData->setProcessId(ui.tbProcess->item(intRow, 2)->text());
    _processData->SetUI(false);
    _processData->exec();
    on_tbProcess_cellClicked();
}

void ProcessDataList::on_Modify_Button_clicked()
{
    int processRow = ui.tbProcess->currentRow();
    int stepRow = ui.tbProcessSteps->currentRow();
    if(stepRow<0 || processRow < 0)
    {
        QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180"),GlobalData::LoadLanguageInfo("K1787"),GlobalData::LoadLanguageInfo("K1181"));
        return;
    }
    _processData->setBModify(true);
    _processData->setProcessId(ui.tbProcess->item(processRow, 2)->text());
    _processData->setStepId(ui.tbProcessSteps->item(stepRow,2)->text());
    _processData->SetUI(true);
    _processData->exec();
    on_tbProcess_cellClicked();
}

void ProcessDataList::on_Delete_Button_clicked()
{
    int intRow = ui.tbProcessSteps->currentRow();
    if(intRow<0)
    {
        QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180"),GlobalData::LoadLanguageInfo("K1407"),GlobalData::LoadLanguageInfo("K1181"));
        return;
    }
    int ret = QMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1801"), GlobalData::LoadLanguageInfo("K1181"), GlobalData::LoadLanguageInfo("K1134"));
    if (ret != 0)
	{
		return;
    }
    int stepId = ui.tbProcessSteps->item(intRow,2)->text().toInt();
    // 删除
    ProcessParameterDao* dao = ProcessParameterDao::instance();
    dao->delectModel(stepId);
    on_tbProcess_cellClicked();
}

void ProcessDataList::on_back_Button_clicked()
{
    emit sglBackSystemSet();
}

void ProcessDataList::on_btnAddProcess_clicked()
{
    AddProcess d(this);
    d.setStrCompany_ID(m_companyId);
    d.exec();
    setCurrentCompany(m_companyName, m_companyId);
}

void ProcessDataList::on_btnDeleteProcess_clicked()
{
    int intRow = ui.tbProcess->currentRow();
    if(intRow<0)
    {
        QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180"),GlobalData::LoadLanguageInfo("K1407"),GlobalData::LoadLanguageInfo("K1181"));
        return;
    }
    int ret = QMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1801"), GlobalData::LoadLanguageInfo("K1181"), GlobalData::LoadLanguageInfo("K1134"));
    if (ret != 0)
        return;
    QString deleteId=ui.tbProcess->item(intRow,2)->text();
    //调用接口，删除流程

   // ui.tbProcessSteps->setRowCount(0);
}
