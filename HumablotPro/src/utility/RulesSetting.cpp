#include "RulesSetting.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QFileDialog>
#include "src/comm/Global.h"
#include "src/comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Instrument/Instrument.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QLineEdit>
#include "src/main/subDialog/MyMessageBox.h"
#include <QListView>

RulesSetting::RulesSetting(QWidget *parent)
    : QWidget(parent)
    ,m_layWidget(nullptr)
    ,m_hLay(nullptr)
    ,m_cmbBox(nullptr)
    ,m_lable(nullptr)
    ,m_isRule(true)
    ,m_isCurveData(false)
{
    setAttribute(Qt::WA_ShowModal, true);
    ui.setupUi(this);
    _instr = Instrument::instance();
    m_strMachineUID = "";
    //QRegExpValidator* validator = new QRegExpValidator(QRegExp("[-+]?[0-9]*\\.?[0-9]+"), ui.lineEditGrayValue);
    ui.label->setText(GlobalData::LoadLanguageInfo("K1022"));
    ui.btnRule->setText(GlobalData::LoadLanguageInfo("K1133"));
    ui.btnCurve->setText(GlobalData::LoadLanguageInfo("K1821"));
    ui.btnAddRule->setText(GlobalData::LoadLanguageInfo("K1820"));
    ui.btnDeleteRule->setText(GlobalData::LoadLanguageInfo("K1822"));
    ui.btnAddItem->setText(GlobalData::LoadLanguageInfo("K1819"));
    ui.btnAddItem->setVisible(m_isRule);
    ui.btnSaveItem->setText(GlobalData::LoadLanguageInfo("K1141"));
    ui.btnDelete->setText(GlobalData::LoadLanguageInfo("K1140"));
    loadUIData(m_isRule);    
}

RulesSetting::~RulesSetting()
{
}

void RulesSetting::tbRuleLoadData()
{
    if(m_isRule)//调用接口,规则(目前用的是老的接口)
    {
        bool bResult = true;
        QSqlQuery ruleQuery = AnalysisUIDao::instance()->SelectRulues(&bResult);
        if (bResult == false)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1275"), MyMessageBox::Ok,"OK","");
            return;
        }
        int row = 0;
        while (ruleQuery.next())
        {
            ui.tbRule->insertRow(row);
            addRuleContent(row, 0, GlobalData::LoadLanguageInfo(ruleQuery.value("RuleName").toString()));
            addRuleContent(row,1,ruleQuery.value("pkid").toString());
            row++;
        }
        ui.tbRule->selectRow(0);
        //ui.tbRule->setCurrentCell(0, 0, QItemSelectionModel::Select);
    }
    else
    {
        QSqlQuery ruleQuery;//调用接口,曲线
        int row = 0;
        while (ruleQuery.next())
        {
            ui.tbRule->insertRow(row);
            addRuleContent(row, 0, ruleQuery.value("").toString());//曲线名
            addRuleContent(row,1,ruleQuery.value("").toString());//id
            row++;
        }
        ui.tbRule->selectRow(0);
    }
}

void RulesSetting::tbRuleItemLoadData(const QString &id)
{
    int row = 0;
    bool bResult = true;
    if(m_isRule)//调用接口,规则数据(目前用的是老的接口)
    {
        ui.tbRuleItem->setRowCount(0);
        QString sql = "select * from t_judge_rules where RulesId ='"+id+"' order by GrayValue asc";
        QSqlQuery ruleItemQuery = AnalysisUIDao::instance()->SelectRecord(&bResult, sql);
        if (bResult == false)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1263"), MyMessageBox::Ok,"OK","");
            return;
        }
        while (ruleItemQuery.next())
        {
            ui.tbRuleItem->insertRow(row);
            addRuleItemContent(row, 0, QString::number(row + 1));
            addRuleItemContent(row, 1, ruleItemQuery.value("GrayValue").toString());
            addRuleItemContent(row, 2, ruleItemQuery.value("GrayWord").toString());
            addRuleItemContent(row, 3, ruleItemQuery.value("pkid").toString());
            row++;
        }
    }
    else
    {
        if (id == "0")
        {
            return;
        }
        ui.tbRuleItem->setRowCount(0);
        m_isCurveData=true;
        QSqlQuery curveItemQuery;//调用接口,曲线数据
        m_cmbBox->setCurrentText("");//调用接口,线性或四参数
        while (curveItemQuery.next())
        {
            ui.tbRuleItem->insertRow(row);
            addRuleItemContent(row, 0, curveItemQuery.value("").toString());//a、b、c、d
            addRuleItemContent(row, 1, curveItemQuery.value("").toString());//a、b、c、d 对应值
            addRuleItemContent(row, 2, "");
            addRuleItemContent(row, 3, curveItemQuery.value("pkid").toString());//id
            row++;
        }
        m_isCurveData=false;
    }
    ui.tbRuleItem->selectRow(0);
}

void RulesSetting::addRuleContent(int row, int column, QString content)
{
    QTableWidgetItem *item = new QTableWidgetItem(content);
    ui.tbRule->setItem(row, column, item);
}

void RulesSetting::addRuleItemContent(int row, int column, QString content)
{
    QTableWidgetItem *item = new QTableWidgetItem(content);
    ui.tbRuleItem->setItem(row, column, item);
}

void RulesSetting::createHeadBox()
{
    if(m_layWidget != nullptr)
    {
        m_layWidget = nullptr;
        m_hLay = nullptr;
        m_cmbBox = nullptr;
        m_lable = nullptr;
    }
    m_layWidget=new QLabel;
    m_hLay=new QHBoxLayout(m_layWidget);
    m_cmbBox=new QComboBox(m_layWidget);
    m_cmbBox->setObjectName("titleCmb");
    m_cmbBox->setView(new  QListView(this));
    m_lable=new QLabel(m_layWidget);
    m_lable->setObjectName("titleLbl");
    setStyleSheet("#titleCmb{background-color: white;} #titleLbl{color:white;}");
    m_cmbBox->addItem(GlobalData::LoadLanguageInfo("K1816"),"1");
    m_cmbBox->addItem(GlobalData::LoadLanguageInfo("K1817"),"2");
    m_cmbBox->setCurrentText(GlobalData::LoadLanguageInfo("K1816"));
    m_lable->setText(GlobalData::LoadLanguageInfo("K1818"));
    m_hLay->addItem(new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
    m_hLay->addWidget(m_lable);
    m_hLay->addWidget(m_cmbBox);
    m_hLay->addItem(new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
    m_layWidget->setLayout(m_hLay);
    disconnect(m_cmbBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFitCurveChanged(int)));
    connect(m_cmbBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slotFitCurveChanged(int)),Qt::UniqueConnection);
}

void RulesSetting::initTbRule()
{
    QHeaderView* headerView = ui.tbRule->verticalHeader();
    headerView->setHidden(true);
    ui.tbRule->setColumnHidden(1,true);
    QStringList headerString;
    headerString << GlobalData::LoadLanguageInfo("K1216");
    ui.tbRule->setHorizontalHeaderLabels(headerString);
    ui.tbRule->horizontalHeader()->setStretchLastSection(true);
    ui.tbRule->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tbRule->setSelectionMode(QAbstractItemView::SingleSelection);
    ui.tbRule->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui.tbRule->setSortingEnabled(false);
    ui.tbRule->setAlternatingRowColors(true);
    ui.tbRule->setShowGrid(true);
}

void RulesSetting::initTbRuleItem()
{
    ui.btnAddItem->setVisible(m_isRule);
    ui.tbRuleItem->verticalHeader()->setHidden(true);
    ui.tbRuleItem->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tbRuleItem->setSelectionMode(QAbstractItemView::SingleSelection);
    ui.tbRuleItem->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui.tbRuleItem->setSortingEnabled(false);
    ui.tbRuleItem->setAlternatingRowColors(true);
    ui.tbRuleItem->setShowGrid(true);
    QStringList headerString;
    if(!m_isRule)
    {
        createHeadBox();
        auto head = new CustomHeaderView(1, Qt::Horizontal,this);
        head->setWidgetObject(m_layWidget);
        ui.tbRuleItem->setHorizontalHeader(head);
        headerString<<"NO"<<"";
        ui.tbRuleItem->setColumnHidden(2,true);
    }
    else
    {
        ui.tbRuleItem->setHorizontalHeader(new QHeaderView(Qt::Horizontal,this));
        headerString << "NO"<<GlobalData::LoadLanguageInfo("K1187")
                     << GlobalData::LoadLanguageInfo("K1215");
        ui.tbRuleItem->setColumnHidden(2,false);
    }
    ui.tbRuleItem->setHorizontalHeaderLabels(headerString);
    ui.tbRuleItem->setColumnHidden(3, true);
    ui.tbRuleItem->horizontalHeader()->setStretchLastSection(true);
    ui.tbRuleItem->horizontalHeader()->setVisible(true);
}

void RulesSetting::loadUIData(const bool isRule)
{
    m_isRule=isRule;
    ui.btnAddItem->setVisible(isRule);
    ui.btnDelete->setVisible(isRule);
    ui.tbRule->setRowCount(0);
    ui.tbRuleItem->setRowCount(0);
    initTbRule();
    initTbRuleItem();
    tbRuleLoadData();
    int intRow = ui.tbRule->currentRow();
    if (intRow < 0)
    {
        AddFitCurveItem();
        return;
    }
    QString id=ui.tbRule->item(intRow,1)->text().simplified();
    tbRuleItemLoadData(id);

}

void RulesSetting::getNumStr(QString &str)
{
    if(str.isEmpty())
    {
        str=GlobalData::LoadLanguageInfo("K1824")+"001";
        if(m_isRule)
            str=GlobalData::LoadLanguageInfo("K1823")+"001";
        return;
    }
    bool b=true;
    int i=0;
    for(;i<str.length();i++)
    {
        str.right(i+1).toInt(&b);
        if (!b)
            break;
    }
    QString numStr="";
    int num = 0;
    if(i>0)
        num=str.right(i).toInt();
    num++;
    if (num < 10)
        numStr = "00" + QString::number(num);
    else if (num < 100)
        numStr = "0" + QString::number(num);
    else
        numStr = QString::number(num);
    str=str.left(str.length()-i)+numStr;
}

void RulesSetting::AddFitCurveItem()
{
    if(m_isRule || m_isCurveData)
        return;
    auto fitType=m_cmbBox->currentData().toInt();
    int rowCount=2;
    if(fitType==2)
        rowCount=4;
    while (ui.tbRuleItem->rowCount()>rowCount)
        ui.tbRuleItem->removeRow(rowCount);
    for(int i=ui.tbRuleItem->rowCount();i<rowCount;i++)
    {
        ui.tbRuleItem->insertRow(i);
        switch (i)
        {
        case 0:
            addRuleItemContent(i,0,"a");
            break;
        case 1:
            addRuleItemContent(i,0,"b");
            break;
        case 2:
            addRuleItemContent(i,0,"c");
            break;
        case 3:
            addRuleItemContent(i,0,"d");
            break;
        }
        addRuleItemContent(i, 1, "");
    }
}

void RulesSetting::on_btnRule_clicked()
{
    loadUIData(true);
}

void RulesSetting::on_btnCurve_clicked()
{
    loadUIData(false);
}

void RulesSetting::slotFitCurveChanged(int index)
{
    Q_UNUSED(index)
    AddFitCurveItem();
}

void RulesSetting::on_btnAddRule_clicked()
{
    QString strName="";
    if(ui.tbRule->rowCount()>0)
        strName=ui.tbRule->item(ui.tbRule->rowCount()-1,0)->text().simplified();
    getNumStr(strName);
    int newRowIndex = ui.tbRule->rowCount();
    ui.tbRule->insertRow(newRowIndex);
    addRuleContent(newRowIndex,0,strName);
    addRuleContent(newRowIndex,1,"0");
    if(m_isRule)
    {//调用接口,增加规则

    }
    else
    {//调用接口,增加曲线

    }
    ui.tbRule->selectRow(ui.tbRule->rowCount()-1);
}

void RulesSetting::on_tbRule_clicked(const QModelIndex &index)
{
    if(!index.isValid())
        return;
    QString id= ui.tbRule->item(index.row(),1)->text().simplified();
    tbRuleItemLoadData(id);
}

void RulesSetting::on_btnDeleteRule_clicked()
{
    int row=ui.tbRule->currentRow();
    if (row < 0)
        return;
    auto ret=QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1260"),
                                      GlobalData::LoadLanguageInfo("K1801"),
                                      GlobalData::LoadLanguageInfo("K1181"),
                                      GlobalData::LoadLanguageInfo("K1134"));
    if(ret!=0)
        return;
    QString id=ui.tbRule->item(row,1)->text().simplified();
    QString sqlStr="delete from t_judge_rules where pkid = "+id+";";
    bool bResult = true;
    auto dao = AnalysisUIDao::instance();
    if(m_isRule)//调用接口,删除规则(老接口)
    {
        dao->SelectRecord(&bResult, sqlStr);
    }
    else
    {//调用接口,删除曲线

    }
    if(!bResult)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"),
                              GlobalData::LoadLanguageInfo("K1291"), MyMessageBox::Ok,"OK","");
        return;
    }
    sqlStr = "insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('"+GlobalData::LoadLanguageInfo("K1658")+"','"+m_strMachineUID+"','"+GlobalData::LoadLanguageInfo("K1662")+"','"+GlobalData::getLoginName1()+"');";
    dao->SelectRecord(&bResult, sqlStr);
    ui.tbRule->removeRow(row);
}

void RulesSetting::on_btnAddItem_clicked()
{
    if(!m_isRule)
        return;
    int newRowIndex=ui.tbRuleItem->rowCount();
    ui.tbRuleItem->insertRow(newRowIndex);
    addRuleItemContent(newRowIndex, 0, "");
    addRuleItemContent(newRowIndex, 1, "");
    addRuleItemContent(newRowIndex, 2, "");
    addRuleItemContent(newRowIndex, 3, "");
}

void RulesSetting::on_btnSaveItem_clicked()
{
    int row=ui.tbRule->currentRow();
    if(row<0)
    {
        QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180")
                                 ,GlobalData::LoadLanguageInfo("K1825")
                                 ,GlobalData::LoadLanguageInfo("K1181"));
        return;
    }

    if(m_isRule)
    {//调用接口,保存规则项目

    }
    else
    {//调用接口,保存曲线项目

    }
}

void RulesSetting::on_btnDelete_clicked()
{
    if(!m_isRule)
        return;
    int row=ui.tbRuleItem->currentRow();
    if(row<0)
        return;
	auto item = ui.tbRuleItem->item(row, 3);
	if (item == nullptr)
		return;
    auto ret=QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1260"),
                                      GlobalData::LoadLanguageInfo("K1801"),
                                      GlobalData::LoadLanguageInfo("K1181"),
                                      GlobalData::LoadLanguageInfo("K1134"));
	if (ret != 0)
		return;
	QString id = item->text();
    //调用接口,删除项目数据
	

	ui.tbRuleItem->removeRow(row);
}

void RulesSetting::on_tbRuleItem_itemChanged(QTableWidgetItem *item)
{
    if(item == nullptr || item->column() != 1)
        return;
    bool b=true;
    item->text().toDouble(&b);
    if(b)
        return;
    item->setText("");
}

void RulesSetting::on_tbRule_itemChanged(QTableWidgetItem *item)
{
	if (item == nullptr || item->column() != 0)
		return;
	auto nItem = ui.tbRule->item(item->row(), 1);
	if (nItem == nullptr)
		return;
    QString id= nItem->text();
    QString strName=item->text();
    if(m_isRule)//调用接口，保存修改的数据，规则
    {

    }
    else//调用接口，保存修改的数据，曲线
    {

    }
}
