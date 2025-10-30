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
    if(m_isRule)
    {
        QVector<JudgeRules> rules = JudgeDao::instance()->getAllRows();
        qDebug()<<"tbRuleLoadData count"<<rules.count();
        int row = 0;
        for(JudgeRules& r : rules)
        {
            ui.tbRule->insertRow(row);
            addRuleContent(row, 0, r.getRuleName());
            addRuleContent(row, 1, QString::number(r.getpkid()));
            row++;
        }
        ui.tbRule->selectRow(0);
        int intRow = ui.tbRule->currentRow();
        qDebug()<<"tbRuleLoadData id"<<ui.tbRule->item(intRow,1)->text().simplified();
    }
    else
    {
        //调用接口,曲线
        QVector<StandaryCurveModel> curves = StandardCurveDao::instance()->getAllRows();
        int row = 0;
        for(StandaryCurveModel& curve : curves)
        {
            ui.tbRule->insertRow(row);
            addRuleContent(row, 0, curve.getCurveName());//曲线名
            addRuleContent(row, 1, QString::number(curve.getCurveId()));//id
            row++;
        }
        ui.tbRule->selectRow(0);
    }
}

void RulesSetting::tbRuleItemLoadData(const QString &id)
{
    bool bResult = true;
    qDebug()<<"tbRuleItemLoadData m_isRule"<<m_isRule;
    if(m_isRule)//调用接口,规则数据(目前用的是老的接口)
    {
        ui.tbRuleItem->setRowCount(0);
        JudgeDao* judgeDao = JudgeDao::instance();
        bResult = judgeDao->getModel(id.toInt(), _ruleModel);
        qDebug()<<"tbRuleItemLoadData m_isRule"<<_ruleModel.parameterToStr();
        if (bResult == false)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1263"), MyMessageBox::Ok,"OK","");
            return;
        }

        QVector<JudgeRules::ParameterStrt> parameters = _ruleModel.getParameter();
        for(int i = 0; i < parameters.count(); i++)
        {
            ui.tbRuleItem->insertRow(i);
            addRuleItemContent(i, 0, QString::number(i+1));
            addRuleItemContent(i, 1, QString::number(parameters[i]._v, 'f', 2));
            addRuleItemContent(i, 2, parameters[i]._k);
            addRuleItemContent(i, 3, "0");
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
        StandardCurveDao* curveDao = StandardCurveDao::instance();
        qDebug()<<"curve id"<<id;
        bResult = curveDao->getModel(id.toInt(), _curveModel);
        if (bResult == false)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1263"), MyMessageBox::Ok,"OK","");
            return;
        }
        // 设置拟合方式
        m_cmbBox->setCurrentText(_curveModel.getCurveType()==0?GlobalData::LoadLanguageInfo("K1816"):GlobalData::LoadLanguageInfo("K1817"));
        QVector<double> param = _curveModel.getDataGroup();
        QVector<QString> title = {"a", "b", "c", "d"};
        qDebug()<<"param count"<<param.count();
        if((_curveModel.getCurveType() == 0 && param.count()!=2) || (_curveModel.getCurveType() == 1 && param.count()!=4))
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1263"), MyMessageBox::Ok,"OK","");
            return;
        }
        for(int i = 0; i < param.count(); i++)
        {
            ui.tbRuleItem->insertRow(i);
            addRuleItemContent(i, 0, title[i]);//a、b、c、d
            addRuleItemContent(i, 1, QString::number(param[i]));//a、b、c、d 对应值
            addRuleItemContent(i, 2, "");
            addRuleItemContent(i, 3, "");
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
    if(isRule)
    {
        ui.btnAddRule->setText(GlobalData::LoadLanguageInfo("K1820"));
        ui.btnDeleteRule->setText(GlobalData::LoadLanguageInfo("K1822"));
        ui.label->setText(GlobalData::LoadLanguageInfo("K1022"));
    }else
    {
        ui.label->setText(GlobalData::LoadLanguageInfo("K1836"));
        ui.btnAddRule->setText(GlobalData::LoadLanguageInfo("K1834"));
        ui.btnDeleteRule->setText(GlobalData::LoadLanguageInfo("K1835"));
    }


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
    if(fitType==2) rowCount=4;
    while (ui.tbRuleItem->rowCount()>rowCount)
    {
        ui.tbRuleItem->removeRow(rowCount);
    }
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
        addRuleItemContent(i, 1, "0");
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
    int newId = 0;
    ui.tbRule->insertRow(newRowIndex);
    if(m_isRule)
    {//调用接口,增加规则
        JudgeDao* judgeDao = JudgeDao::instance();
        JudgeRules rule;
        rule.setRuleName(strName);
        QVector<JudgeRules::ParameterStrt> paramStrt;
        paramStrt.push_back(JudgeRules::ParameterStrt("-", 0));
        paramStrt.push_back(JudgeRules::ParameterStrt("+", 10));
        rule.setParameter(paramStrt);
        bool success = judgeDao->insert(rule);
        newId = rule.getpkid();
        if(!success)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"),GlobalData::LoadLanguageInfo("K1301"), MyMessageBox::Ok,"OK","");
            return;
        }
    }
    else
    {//调用接口,增加曲线
        StandardCurveDao* standardDao = StandardCurveDao::instance();
        StandaryCurveModel curve;
        curve.setCurveName(strName);
        curve.setCurveType(0);
        curve.setDataGroup({1.0,1.0});
        curve.setRemark("");
        if(!standardDao->insert(curve))
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"),GlobalData::LoadLanguageInfo("K1301"), MyMessageBox::Ok,"OK","");
            return;
        }
        newId = curve.getCurveId();
    }
    addRuleContent(newRowIndex, 0, strName);
    addRuleContent(newRowIndex, 1, QString::number(newId));
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
    if (row < 0) return;
    auto ret=QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1260"),
                                      GlobalData::LoadLanguageInfo("K1801"),
                                      GlobalData::LoadLanguageInfo("K1181"),
                                      GlobalData::LoadLanguageInfo("K1134"));
    if(ret!=0) return;
    QString id=ui.tbRule->item(row,1)->text().simplified();
    bool bResult = true;
    if(m_isRule)//调用接口,删除规则(老接口)
    {
        JudgeDao::instance()->deleteModel(id.toInt());
    }
    else
    {//调用接口,删除曲线
        StandardCurveDao::instance()->deleteModel(id.toInt());
    }
    if(!bResult)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"),
                              GlobalData::LoadLanguageInfo("K1291"), MyMessageBox::Ok,"OK","");
        return;
    }
    auto dao = AnalysisUIDao::instance();
    QString sqlStr = "insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('"+GlobalData::LoadLanguageInfo("K1658")+"','"+m_strMachineUID+"','"+GlobalData::LoadLanguageInfo("K1662")+"','"+GlobalData::getLoginName1()+"');";
    dao->SelectRecord(&bResult, sqlStr);
    ui.tbRule->removeRow(row);
}

// 增加规则条目, 新增条目默认填充为上一条的内容
void RulesSetting::on_btnAddItem_clicked()
{
    if(!m_isRule) return;
    int newRowIndex=ui.tbRuleItem->rowCount();
    ui.tbRuleItem->insertRow(newRowIndex);
    if(newRowIndex == 0)
    {
        addRuleItemContent(newRowIndex, 0, QString::number(newRowIndex+1));
        addRuleItemContent(newRowIndex, 1, "-");
        addRuleItemContent(newRowIndex, 2, "0.1");
        addRuleItemContent(newRowIndex, 3, "");
    }else
    {
        addRuleItemContent(newRowIndex, 0, QString::number(newRowIndex+1));
        addRuleItemContent(newRowIndex, 1, ui.tbRuleItem->item(newRowIndex-1, 1)->text().simplified());
        addRuleItemContent(newRowIndex, 2, ui.tbRuleItem->item(newRowIndex-1, 2)->text().simplified());
        addRuleItemContent(newRowIndex, 3, "");
    }
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
        QVector<JudgeRules::ParameterStrt> parameter;
        int rowCount = ui.tbRuleItem->rowCount();
        for(int i = 0; i < rowCount; i++)
        {
            parameter.push_back(JudgeRules::ParameterStrt(
                                    ui.tbRuleItem->item(i, 2)->text().simplified(),
                                    ui.tbRuleItem->item(i, 1)->text().simplified().toDouble())
                                );
        }
        if(_ruleModel.hasParameterDuplicates(parameter))
        {
            QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180")
                                     ,GlobalData::LoadLanguageInfo("K1283")
                                     ,GlobalData::LoadLanguageInfo("K1181"));
             return;
        }
        int currentRuleRow = ui.tbRule->currentRow();
        QString ruleName =ui.tbRule->item(currentRuleRow, 0)->text().simplified();
        _ruleModel.setRuleName(ruleName);
        _ruleModel.setParameter(parameter);
        qDebug()<<"ruleName"<<ruleName;
        qDebug()<<"update id"<<_ruleModel.getpkid();
        if(!JudgeDao::instance()->update(_ruleModel))
        {
            QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180")
                                     ,GlobalData::LoadLanguageInfo("K1283")
                                     ,GlobalData::LoadLanguageInfo("K1181"));
            return;
        }
        QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180")
                                 ,GlobalData::LoadLanguageInfo("K1378")
                                 ,GlobalData::LoadLanguageInfo("K1181"));
    }
    else
    {//调用接口,保存曲线项目
        QVector<double> parameter;
        int rowCount = ui.tbRuleItem->rowCount();
        for(int i = 0; i < rowCount; i++)
        {
            parameter.push_back(ui.tbRuleItem->item(i, 1)->text().simplified().toDouble());
        }
        int currentRuleRow = ui.tbRule->currentRow();
        QString curveName =ui.tbRule->item(currentRuleRow, 0)->text().simplified();
        int curveType = m_cmbBox->currentText() == GlobalData::LoadLanguageInfo("K1816")?0:1;
        _curveModel.setCurveType(curveType);
        _curveModel.setCurveName(curveName);
        _curveModel.setDataGroup(parameter);
        qDebug()<<"curveName"<<curveName;
        qDebug()<<"update id"<<_curveModel.getCurveId();
        if(!StandardCurveDao::instance()->update(_curveModel))
        {
            QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180")
                                     ,GlobalData::LoadLanguageInfo("K1283")
                                     ,GlobalData::LoadLanguageInfo("K1181"));
            return;
        }
        QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180")
                                 ,GlobalData::LoadLanguageInfo("K1378")
                                 ,GlobalData::LoadLanguageInfo("K1181"));
    }
}

void RulesSetting::on_btnDelete_clicked()
{
    if(!m_isRule) return;
    int row=ui.tbRuleItem->currentRow();
    if(row<0) return;
	auto item = ui.tbRuleItem->item(row, 3);
    if (item == nullptr) return;
    auto ret=QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1260"),
                                      GlobalData::LoadLanguageInfo("K1801"),
                                      GlobalData::LoadLanguageInfo("K1181"),
                                      GlobalData::LoadLanguageInfo("K1134"));
    if (ret != 0) return;
	QString id = item->text();
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
