#include "TestPaper.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include <QDesktopWidget>
#include <QColorDialog>
#include "../comm/GlobalData.h"
#include "../comm/Global.h"
#include <QProcess>
#include <QListView>
#include <QCloseEvent>
#include "src/main/subDialog/MyMessageBox.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/Utilities/log.h"
#include "../Include/Model/baseSet/CompanyModel.h"
#include "../Include/Model/baseSet/ProcessModel.h"
#include "../Include/Model/baseSet/ItemModel.h"
#include "../Include/Model/result/JudgeRules.h"
#include "../Include/Model/baseSet/StandaryCurveModel.h"
#include "../Include/DAO/baseSet/CompanyDao.h"
#include "../Include/DAO/baseSet/ProcessDao.h"
#include "../Include/DAO/baseSet/JudgeDao.h"
#include "../Include/DAO/baseSet/StandardCurveDao.h"
#include "../Include/DAO/baseSet/TestPaperDao.h"
#include "../Include/DAO/baseSet/ItemDao.h"

TestPaper::TestPaper(QWidget *parent)
    : QDialog(parent)
    ,ui(new Ui::TestPaper)
    ,m_gridItemCtl{}
    ,m_itemDataMap{}
    ,m_gridBlockCtl{}
    ,m_blockAndItemDataMap{}
    ,m_blockItemCtlMap{}
    ,m_ruleCmbDatas{}
    ,m_curveCmbDatas{}
    ,m_itemTypeCmbDatas{}
    ,_isNeedUpdate(false)
    ,_paperId("")
    ,m_bModify(false)
    ,m_Company_ID("")
{
    ui->setupUi(this);
    setWindowFlags((windowFlags() & ~(Qt::WindowContextHelpButtonHint/*|Qt::WindowCloseButtonHint*/)));
    setFixedSize(width(), height());    
    setWindowIcon(QIcon(":/images/buttonIcon/icon.png"));
    this->setWindowTitle(GlobalData::LoadLanguageInfo("K1112"));
    connect(ui->pushButton_PickColor, &QPushButton::clicked, this, &TestPaper::color_slots_func);
    initUI();
}

TestPaper::~TestPaper()
{
    delete ui;
	ui = nullptr;
}

void TestPaper::initUI()
{
    ui->lineEdit_Item_Number->setValidator(new QRegExpValidator(QRegExp("^[0-9]|[1-2][0-9]|30$"), this));
    ui->lineEdit_TestItem_Number->setValidator(new QRegExpValidator(QRegExp("^[0-9]|[1-2][0-9]|30$"), this));
    auto doublReg{new QRegExpValidator(QRegExp("^(?:[1-9]\\d{0,3}|0)(?:\\.\\d{1,3})?$"), this)};
    ui->lineEdit_TestPaparLenght->setValidator(doublReg);
    ui->lineEdit_TestPaparHeight->setValidator(doublReg);
    ui->lineEdit_paper_head_length->setValidator(doublReg);
    ui->txtItemSpace->setValidator(doublReg);
    ui->txtItemWidth->setValidator(doublReg);
    ui->txtFunThreshold->setValidator(doublReg);
    ui->txtFunWidth->setValidator(doublReg);
    ui->txtBlackSpotThreshold->setValidator(doublReg);
    ui->txtCutOffThreshold->setValidator(doublReg);
    ui->txtCutOffValue->setValidator(doublReg);
    ui->txtThreshold->setValidator(doublReg);
    ui->txtBackGround->setValidator(doublReg);
    ui->txtItemSearchWidth->setValidator(doublReg);
    ui->txtItemLineWidth->setValidator(doublReg);
    ui->txtPixDistance->setValidator(doublReg);

    auto percentReg{new QRegExpValidator(QRegExp(R"(^(0|[1-9]\d?|100)?$)"), this)};
    ui->txtAnalyzeHeight->setValidator(percentReg);
    ui->txtAnalyzeWidth->setValidator(percentReg);
    // 禁止手动输入, 只能选择
    ui->txtColorValue->setReadOnly(true);

    auto grayReg{new QRegExpValidator(QRegExp(R"(^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9][0-9]|[0-9])?$)"), this)};
    ui->txtBackGround->setValidator(grayReg); // 背景值
    ui->txtThreshold->setValidator(grayReg); // 二值化阈值
    ui->txtCutOffThreshold->setValidator(grayReg); // cutoff阈值
    ui->txtCutOffValue->setValidator(grayReg); // cutoff灰度值
    ui->txtBlackSpotThreshold->setValidator(grayReg); // 黑点检测阈值
    ui->txtFunThreshold->setValidator(grayReg); // 功能先阈值

    // 将待验证的输入框缓存
    m_requiredWidgets << ui-> lineEdit_TestPaparName // 膜条名称
                      << ui->lineEdit_TestPaparLenght // 膜条总长度
                      << ui->lineEdit_TestPaparHeight // 膜条总高度
                      << ui->lineEdit_paper_head_length // 膜条头长度
                      << ui->txtBackGround // 背景值
                      << ui->lineEdit_Item_Number // 条带数量
                      << ui->lineEdit_TestItem_Number // 指标数量
                      << ui->txtThreshold // 二值化阈值
                      << ui->txtColorValue // 颜色值
                      << ui->txtPixDistance //像素距离比
                      << ui->txtFunThreshold // 功能先阈值
                      << ui->txtFunWidth // 功能线查找宽度
                      << ui->txtCutOffThreshold // cutoff阈值
                      << ui->txtCutOffValue // cutoff灰度值
                      << ui->txtItemSearchWidth // 指标查找宽度
                      << ui->txtItemLineWidth // 指标宽度
                      << ui->txtAnalyzeHeight // 分析高度百分比
                      << ui->txtAnalyzeWidth // 分析宽度百分比
                      << ui->txtBlackSpotThreshold // 黑点检测阈值
                      << ui->txtArticleNo; //货号

    ui->lblCompany->setText(GlobalData::LoadLanguageInfo("K1791"));
    ui->cmbCompany->setView(new QListView(this));
    ui->lblPaperType->setText(GlobalData::LoadLanguageInfo("K1554"));
    ui->cmbPaperType->setView(new QListView(this));
    ui->lblProcess->setText(GlobalData::LoadLanguageInfo("K1792"));
    ui->cmbProcess->setView(new QListView(this));

    ui->txtArticleNo->setMaxLength(15);
    ui->lblPaperName->setText(GlobalData::LoadLanguageInfo("K1100"));
    ui->lblPaperLength->setText(GlobalData::LoadLanguageInfo("K1128"));
    ui->lblHeadLength->setText(GlobalData::LoadLanguageInfo("K1126"));
    ui->lblItemSpace->setText(GlobalData::LoadLanguageInfo("K1708"));
    ui->lblItemWidth->setText(GlobalData::LoadLanguageInfo("K1707"));
    ui->lblFunDirection->setText(GlobalData::LoadLanguageInfo("K1123"));
    ui->cmbFunLineFindDirection->setView(new QListView(this));
    //ui->lblFunPostion->setText(GlobalData::LoadLanguageInfo("K1119"));
    ui->lblFunThreshold->setText(GlobalData::LoadLanguageInfo("K1118"));
    ui->lblFunWidth->setText(GlobalData::LoadLanguageInfo("K1709"));
    ui->chkBlackSpot->setText(GlobalData::LoadLanguageInfo("K1710"));
    ui->lblBlackSpotThreshold->setText(GlobalData::LoadLanguageInfo("K1741"));
    //ui->checkBox_CutOff->setText(GlobalData::LoadLanguageInfo("K1117"));
    //ui->lblCutOffPos->setText(GlobalData::LoadLanguageInfo("K1844"));
    ui->lblCutOffThreshold->setText(GlobalData::LoadLanguageInfo("K1116"));
    ui->lblCutOffValue->setText(GlobalData::LoadLanguageInfo("K1800"));
    ui->lblRotate->setText(GlobalData::LoadLanguageInfo("K1802"));
    ui->cmbPaperRotate->setView(new QListView(this));
    ui->lblThreshold->setText(GlobalData::LoadLanguageInfo("K1124"));
    ui->lblBackGround->setText(GlobalData::LoadLanguageInfo("K1705"));
    ui->lblItemSearchWidth->setText(GlobalData::LoadLanguageInfo("K1803"));
    ui->lblAnalyzeHeight->setText(GlobalData::LoadLanguageInfo("K1804"));
    ui->lblAnalyzeWidth->setText(GlobalData::LoadLanguageInfo("K1805"));
    ui->lblPixDistance->setText(GlobalData::LoadLanguageInfo("K1806"));
    ui->lblArticleNo->setText(GlobalData::LoadLanguageInfo("K1101"));
    ui->lblColorValue->setText(GlobalData::LoadLanguageInfo("K1121"));
    ui->pushButton_PickColor->setText(GlobalData::LoadLanguageInfo("K1114"));

    ui->label_77->setText(GlobalData::LoadLanguageInfo("K1133"));
    ui->rdRulesSingle->setText(GlobalData::LoadLanguageInfo("K1795"));
    ui->rdRulesAllSet->setText(GlobalData::LoadLanguageInfo("K1796"));
    ui->label_78->setText(GlobalData::LoadLanguageInfo("K1794"));
    ui->rdCurveSingle->setText(GlobalData::LoadLanguageInfo("K1795"));
    ui->rdCurveAllSet->setText(GlobalData::LoadLanguageInfo("K1796"));
    ui->rdRulesAllSet->setChecked(false);
    ui->rdCurveAllSet->setChecked(false);
    ui->rdRulesSingle->setChecked(true);
    ui->rdCurveSingle->setChecked(true);
    ui->pushButton_Set->setText(GlobalData::LoadLanguageInfo("K1115"));


    ui->lblG1ItemName_3->setText(GlobalData::LoadLanguageInfo("K1811"));
    ui->lblG1ItemName->setText(GlobalData::LoadLanguageInfo("K1131"));
    ui->lblG1IsEmpty->setText(GlobalData::LoadLanguageInfo("K1132"));
    ui->lblG1Position->setText(GlobalData::LoadLanguageInfo("K1115"));
    ui->lblG1Rules->setText(GlobalData::LoadLanguageInfo("K1133"));
    ui->lblG1Curves->setText(GlobalData::LoadLanguageInfo("K1794"));

    ui->label_32->setText(GlobalData::LoadLanguageInfo("K1811"));
    ui->lblG2ItemName->setText(GlobalData::LoadLanguageInfo("K1131"));
    ui->lblG2IsEmpty->setText(GlobalData::LoadLanguageInfo("K1132"));
    ui->lblG2Position->setText(GlobalData::LoadLanguageInfo("K1115"));
    ui->lblG2Rules->setText(GlobalData::LoadLanguageInfo("K1133"));
    ui->lblG2Curves->setText(GlobalData::LoadLanguageInfo("K1794"));

    ui->lblG3ItemCount->setText(GlobalData::LoadLanguageInfo("K1129"));

    ui->lblG4ItemCount->setText(GlobalData::LoadLanguageInfo("K1797"));
    ui->pushButton_Save->setText(GlobalData::LoadLanguageInfo("K1038"));
    ui->pushButton_Cancel->setText(GlobalData::LoadLanguageInfo("K1134"));
    ui->lblTestItemNum->setText(GlobalData::LoadLanguageInfo("K1797"));
    ui->lblItemLineWidth->setText(GlobalData::LoadLanguageInfo("K1799"));

    ui->tbSegment->verticalHeader()->setVisible(false);
    QStringList headerString;
    QString sz1 = GlobalData::LoadLanguageInfo("K1767");
    QString sz2 = GlobalData::LoadLanguageInfo("K1811");
    QString sz3 = GlobalData::LoadLanguageInfo("K1131");
    QString sz4 = GlobalData::LoadLanguageInfo("K1132");
    QString sz5 = GlobalData::LoadLanguageInfo("K1812");
    QString sz6 = GlobalData::LoadLanguageInfo("K1133");
    QString sz7 = GlobalData::LoadLanguageInfo("K1794");
    headerString<<sz1<<sz2<<sz3<<sz4<<sz5<<sz6<<sz7;
    ui->tbSegment->setHorizontalHeaderLabels(headerString);
    ui->tbSegment->horizontalHeader()->setStretchLastSection(true);
    ui->tbSegment->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbSegment->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tbSegment->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->tbSegment->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tbSegment->setSortingEnabled(false);
    ui->tbSegment->setAlternatingRowColors(true);
    ui->tbSegment->setShowGrid(true);
    ui->tbSegment->setColumnWidth(0,65);
    ui->tbSegment->setColumnWidth(1,125);
    ui->tbSegment->setColumnWidth(2,155);
    ui->tbSegment->setColumnWidth(4,155);
    ui->tbSegment->setColumnWidth(5,135);
    //ui->lineEdit_Item_Number->setPlaceholderText("       测试");
    QVector<JudgeRules> rules = JudgeDao::instance()->getAllRows();
    for(JudgeRules r:rules)
    {
        ComboxData cmbData(r.getRuleName(), QString::number(r.getpkid()));
        m_ruleCmbDatas.push_back(cmbData);
    }
    //调用接口,曲线下拉框数据
    QVector<StandaryCurveModel> curves = StandardCurveDao::instance()->getAllRows();
    for(StandaryCurveModel c:curves)
    {
        ComboxData cmbData(c.getCurveName(), QString::number(c.getCurveId()));
        m_curveCmbDatas.push_back(cmbData);
    }
    m_itemTypeCmbDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1807"), QString::number(ItemModel::ITEM_TYPE_FUNC)));
    m_itemTypeCmbDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1837"), QString::number(ItemModel::ITEM_TYPE_CUTOFF)));
    m_itemTypeCmbDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1808"), QString::number(ItemModel::ITEM_TYPE_ITEM)));
    getAllItemControl();
    initComboBox();
}

void TestPaper::Set_UI(const QString &paperId, const QString &companyId, bool isModify)
{
    m_bModify=isModify;
    if(!isModify)
    {
        _testPaperModel = TestPaperModel();
        return;
    }
    qDebug()<<"paperId"<<paperId;
    _paperId = paperId;
    bool bResult;
    m_Company_ID = companyId;
    bResult = TestPaperDao::instance()->getModel(paperId.toInt(), _testPaperModel);//接口调用,获取膜条数据
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1263"), MyMessageBox::Ok,"OK","");
        return;
    }
    ui->rdRulesAllSet->setChecked(false);
    ui->rdCurveAllSet->setChecked(false);
    ui->rdRulesSingle->setChecked(true);
    ui->rdCurveSingle->setChecked(true);
    _itemModelVect = ItemDao::instance()->selectItems(paperId.toInt());
    bool isSegmentPaper = _testPaperModel.getPaperType() == TestPaperModel::PAPER_TYPE_SEGMENT;
    ui->cmbCompany->setCurrentIndex(ui->cmbCompany->findData(m_Company_ID));//公司
    auto segmentTag = isSegmentPaper ? "1" : "0";
    ui->cmbPaperType->setCurrentIndex(ui->cmbPaperType->findData(segmentTag));
    ui->cmbProcess->setCurrentIndex(ui->cmbProcess->findData(QString::number(_testPaperModel.getProcessId())));
    ui->lineEdit_Item_Number->setText(QString::number(_testPaperModel.getTotalNumber()));
    ui->lineEdit_TestItem_Number->setText(QString::number(_testPaperModel.getTestItemNumber()));
    ui->lineEdit_TestPaparName->setText(_testPaperModel.getPaperName());
    ui->lineEdit_TestPaparLenght->setText(QString::number(_testPaperModel.getPaperLenght(), 'f', 2));
    ui->lineEdit_TestPaparHeight->setText(QString::number(_testPaperModel.getPaperHeight(), 'f', 2));
    ui->lineEdit_paper_head_length->setText(QString::number(_testPaperModel.getIgnoreHeadLenght(), 'f', 2));
    auto funDirection = _testPaperModel.getFuncFindDir() == TestPaperModel::PAPER_FUNC_FIND_DIR_HEAD?"0":"1";//调用接口
    ui->cmbFunLineFindDirection->setCurrentIndex(ui->cmbFunLineFindDirection->findData(funDirection));
    ui->txtFunThreshold->setText(QString::number(_testPaperModel.getFuncGrayThreshold(), 'f', 2));
    ui->txtFunWidth->setText(QString::number(_testPaperModel.getFuncFindWidth(), 'f', 2));//调用接口,功能线宽度
    bool isCheckBlackSpot=_testPaperModel.getIsBlackPointDetect();//调用接口,是否开启黑点检测
    ui->chkBlackSpot->setChecked(isCheckBlackSpot);
    ui->txtBlackSpotThreshold->setText(QString::number(_testPaperModel.getBlackPointDetectThreshold(), 'f', 2));//调用接口,黑点检测阙值
    ui->txtCutOffThreshold->setText(QString::number(_testPaperModel.getCutOffThreshold(), 'f', 2));//调用接口,CutOff线阈值
    ui->txtCutOffValue->setText(QString::number(_testPaperModel.getCutOffValue(), 'f', 2));
    auto angle=_testPaperModel.getPaperShowAngle()==0?"0":"180";//调用接口
    ui->cmbPaperRotate->setCurrentIndex(ui->cmbPaperRotate->findData(angle));
    ui->txtThreshold->setText(QString::number(_testPaperModel.getPaperBinarizationThreshold(), 'f', 2));
    ui->txtBackGround->setText(QString::number(_testPaperModel.getPaperBackgroundValue(), 'f', 2));
    ui->txtItemSearchWidth->setText(QString::number(_testPaperModel.getItemFindWidth(), 'f', 2));//调用接口,指标查找宽度
    ui->txtItemLineWidth->setText(QString::number(_testPaperModel.getItemLineWidth(), 'f', 2));//调用接口,指标查找宽度
    ui->txtAnalyzeHeight->setText(QString::number(_testPaperModel.getAnalysisPercentOfHeight()));
    ui->txtAnalyzeWidth->setText(QString::number(_testPaperModel.getAnalysisPercentOfWidth()));//调用接口,分析宽度区间比
    ui->txtPixDistance->setText(QString::number(_testPaperModel.getPaperMmToPixel(), 'f', 2));//调用接口,像素距离百分比
    ui->txtArticleNo->setText(_testPaperModel.getArticleNo());
    ui->txtColorValue->setText(_testPaperModel.getPaperColorOnUi());

    uiCtlSet(ui->lineEdit_Item_Number->text().toInt());
    QVector<ItemModel>itemVect = ItemDao::instance()->selectItems(paperId.toInt());
    if(!isSegmentPaper)
    {
        ui->txtItemSpace->setEnabled(false); // 项目块间距
        ui->txtItemWidth->setEnabled(false); // 项目块宽度
        ui->txtItemSpace->setText("0"); // 项目块间距
        ui->txtItemWidth->setText("0"); // 项目块宽度
        for (int i = 0; i<itemVect.count();i++)
        {
            if(i>=m_gridItemCtl.itemCtlMap.count())
            {
                eLog("TestPaperItemQuery error");
                break;
            }
            Item_Control &ctl=m_gridItemCtl.itemCtlMap[i+1];
            ctl.lineEdit_Name->setText(itemVect[i].getItemName());
            ctl.checkBox->setChecked(itemVect[i].getIsNull());
            ctl.lineEdit_Position->setText(QString::number(itemVect[i].getPosition(), 'f', 1));
            ctl.combo_item_type->setCurrentIndex(ctl.combo_item_type->findData(QString::number(itemVect[i].getItemType())));
            ctl.combo_box_rule->setCurrentIndex(ctl.combo_box_rule->findData(QString::number(itemVect[i].getRulesId())));
            //调用接口 ,定标曲线
            ctl.cmbCurve->setCurrentIndex(ctl.cmbCurve->findData(QString::number(itemVect[i].getCurveId())));
            qDebug()<<"combo_box_rule"<<QString::number(itemVect[i].getRulesId())<<QString::number(itemVect[i].getCurveId());
        }
        return;
    }
    ui->txtItemSpace->setEnabled(true); // 项目快间距
    ui->txtItemWidth->setEnabled(true); // 项目块宽度
    ui->txtItemSpace->setText(QString::number(_testPaperModel.getTestBlockSpace(), 'f', 2));//调用接口
    ui->txtItemWidth->setText(QString::number(_testPaperModel.getTestBlockWidth(), 'f', 2)); // 项目块宽度
    if (_itemModelVect.size() == 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1263"), MyMessageBox::Ok,"OK","");
        return;
    }
    // 根据膜条段分组
    QMap<int, QVector<ItemModel>> groupedBySem;
    for (const ItemModel& m : itemVect)
    {
        groupedBySem[m.getSegmentIndex()].append(m);
    }
    int maxSemIdx = groupedBySem.lastKey();
    QVector<BlockData>blockVect;//调用接口,分段膜条所有的块数据
    // 段id起始位置为1
    for(int i = 1; i <= maxSemIdx; i++)
    {
        BlockData block;
        block.serialNo = i;
        block.itemCount = groupedBySem.keys().contains(i) ? groupedBySem[i].count() : 0;
        blockVect.push_back(block);
        qDebug()<<"block.serialNo"<<i<<groupedBySem[i].count();
    }
    if(blockVect.count()>30)
    {
        eLog("vect count over limit");
        return;
    }
    for(BlockData& black : blockVect)
    {
        auto it = m_gridBlockCtl.blockCtlMap.find(black.serialNo);
        if(it==m_gridBlockCtl.blockCtlMap.end())
        {
            eLog("sgItemCtlMap data error,key:{}",black.serialNo);
            continue;
        }
        //auto &b=blockVect.at(i-1);
        auto ctl=it.value();
        ctl.label->setText(QString::number(black.serialNo));
        //if(i!=b.serialNo) eLog("error,i:{},serialNo:{}",i,b.serialNo);
        //调用接口,块对应的项目数据
        QVector<BlockItemData> itemDataVect;
        QVector<ItemModel> itemVectBySem;
        if(groupedBySem.contains(black.serialNo))
        {
            itemVectBySem = groupedBySem[black.serialNo];
        }
        for(ItemModel& model : itemVectBySem)
        {
            BlockItemData block;
            block.curve = model.getCurveId();
            block.ignore = model.getIsNull();
            block.blockNo = model.getSegmentIndex();
            block.judgerule = model.getRulesId();
            block.itemType = model.getItemType();
            block.serialNo = model.getPositionNo();
            block.strItemName = model.getItemName();
            itemDataVect.push_back(block);
        }
        auto count=itemDataVect.count();
        ctl.cmbItemCount->setCurrentText(QString::number(count));
        auto itemCtlIt=m_blockItemCtlMap.find(black.serialNo);
        if(itemCtlIt==m_blockItemCtlMap.end())
        {
            eLog("data error,key:{}",black.serialNo);
            continue;
        }
        int j=0;
        auto &itemCtlVect=itemCtlIt.value();
        for(auto &detailCtl:itemCtlVect)
        {
            if(j>=count)
            {
                eLog("itemDetailVect count error");
                break;
            }
            auto &item=itemDataVect.at(j);
            detailCtl.cmbItemType->setCurrentIndex(detailCtl.cmbItemType->findData(item.itemType));
            detailCtl.itemNameEdit->setText(item.strItemName);
            detailCtl.checkBox->setChecked(item.ignore);
            detailCtl.blockNo=black.serialNo;
            detailCtl.cmbRuleBox->setCurrentIndex(detailCtl.cmbRuleBox->findData(item.judgerule));
            detailCtl.cmbCurveBox->setCurrentIndex(detailCtl.cmbCurveBox->findData(item.curve));
            j++;
        }
    }
}

// 设置按钮
void TestPaper::on_pushButton_Set_clicked()
{
    auto itemCount = ui->lineEdit_Item_Number->text().toInt();
    if (itemCount == 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1593"), MyMessageBox::Ok, "OK", "");
        return ;
    }
    uiCtlSet(itemCount);
}

void TestPaper::color_slots_func()
{
    QColorDialog ColorDlg(Qt::red, this); // 创建对象
    ColorDlg.setOption(QColorDialog::ShowAlphaChannel); //设置ALPHA选项
    ColorDlg.setWindowTitle(GlobalData::LoadLanguageInfo("K1815"));
    ColorDlg.exec();
    QColor color = ColorDlg.currentColor();
    QString sz = QString("%1").arg(color.name());
    ui->txtColorValue->setText(sz);
}

void TestPaper::slotCmbRuleDataSet(int index)
{
	if (!ui->rdRulesAllSet->isChecked())
		return;
    for(auto &ctl:m_gridItemCtl.itemCtlMap)
        ctl.combo_box_rule->blockSignals(true);

    for(auto &ctl:m_gridItemCtl.itemCtlMap)
        ctl.combo_box_rule->setCurrentIndex(index);

    for(auto &ctl:m_gridItemCtl.itemCtlMap)
        ctl.combo_box_rule->blockSignals(false);
}

void TestPaper::slotCmbCurveDataSet(int index)
{
    if (!ui->rdCurveAllSet->isChecked())
        return;

    for(auto &ctl:m_gridItemCtl.itemCtlMap)
        ctl.cmbCurve->blockSignals(true);

    for(auto &ctl:m_gridItemCtl.itemCtlMap)
        ctl.cmbCurve->setCurrentIndex(index);

    for(auto &ctl:m_gridItemCtl.itemCtlMap)
        ctl.cmbCurve->blockSignals(false);
}

void TestPaper::slotRightCmbRuleDataSet(int index)
{
    if (!ui->rdRulesAllSet->isChecked())
        return;
    for(auto &vect:m_blockItemCtlMap)
    {
        for(auto &ctl:vect)
            ctl.cmbRuleBox->blockSignals(true);
    }

    for(auto &vect:m_blockItemCtlMap)
    {
        for(auto &ctl:vect)
            ctl.cmbRuleBox->setCurrentIndex(index);
    }

    for(auto &vect:m_blockItemCtlMap)
    {
        for(auto &ctl:vect)
            ctl.cmbRuleBox->blockSignals(false);
    }
}

void TestPaper::slotRightCurveDataSet(int index)
{
    if (!ui->rdCurveAllSet->isChecked())
        return;
    for(auto &vect:m_blockItemCtlMap)
    {
        for(auto &ctl:vect)
            ctl.cmbCurveBox->blockSignals(true);
    }
    for(auto &vect:m_blockItemCtlMap)
    {
        for(auto &ctl:vect)
            ctl.cmbCurveBox->setCurrentIndex(index);
    }
    for(auto &vect:m_blockItemCtlMap)
    {
        for(auto &ctl:vect)
            ctl.cmbCurveBox->blockSignals(false);
    }
}

void TestPaper::slotCreatDetailRows(const QString &data)
{  
    int row=data.toInt();
    QVector<BlockItemCtl>detailVect{};
    QVector<BlockItemCtl> oldCtlVect{};
	auto seqNo = sender()->objectName().toInt();
    qDebug()<<"sender"<<seqNo;
    auto it=m_blockItemCtlMap.find(seqNo);
    if (it != m_blockItemCtlMap.end())
    {
		oldCtlVect = it.value();
        m_blockItemCtlMap.remove(seqNo);
    }
    auto oldCount = oldCtlVect.count();
    for (int i = 0; i < row; i++)
	{
        if (oldCount > i)
		{
            detailVect.push_back(oldCtlVect.at(i));
            continue;
		}

        BlockItemCtl ctl;
        ctl.blockNo = seqNo;
        detailVect.push_back(ctl);
	}
    if(detailVect.count()>0)
        m_blockItemCtlMap.insert(seqNo, detailVect);
    int oldRow=0;
    for(auto it=m_blockItemCtlMap.begin();it!=m_blockItemCtlMap.end();it++)
    {
        for(auto &ctl:it.value())
        {
            if(it.key()<=seqNo && !ctl.isNew)
            {
                oldRow++;
                continue;
            }
            int typeIndex=-1;
            int ruleIndex= -1;
            int curveIndex= -1;
            bool ignoreChecked = false;
            QString itemName="";
			if (ctl.cmbItemType != nullptr)
			{
				typeIndex = ctl.cmbItemType->currentIndex();
				ruleIndex = ctl.cmbRuleBox->currentIndex();
				curveIndex = ctl.cmbCurveBox->currentIndex();
                itemName=ctl.itemNameEdit->text().simplified();
                ignoreChecked=ctl.checkBox->isChecked();
			}
            ctl.isNew=true;
            ctl.itemNameEdit=new QLineEdit(this);
            ctl.itemNameEdit->setText(itemName);

            ctl.cmbItemType = new QComboBox(this);
            ctl.cmbItemType->blockSignals(true); // 阻塞信号
            ctl.cmbItemType->setView(new QListView(ctl.cmbItemType));
            setComBoBoxData(ctl.cmbItemType, m_itemTypeCmbDatas);
            ctl.cmbItemType->setCurrentIndex(typeIndex);
            ctl.cmbItemType->blockSignals(false); // 恢复信号

            ctl.checkBox = new QCheckBox(this);
            ctl.checkBox->setChecked(ignoreChecked);

            ctl.cmbRuleBox = new QComboBox(this);
            ctl.cmbRuleBox->blockSignals(true); // 阻塞信号
            ctl.cmbRuleBox->setView(new QListView(ctl.cmbRuleBox));
            setComBoBoxData(ctl.cmbRuleBox, m_ruleCmbDatas);
            ctl.cmbRuleBox->setCurrentIndex(ruleIndex);
            ctl.cmbRuleBox->blockSignals(false); // 恢复信号
            connect(ctl.cmbRuleBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slotRightCmbRuleDataSet(int)),Qt::UniqueConnection);

            ctl.cmbCurveBox = new QComboBox(this);
            ctl.cmbCurveBox->blockSignals(true); // 阻塞信号
            ctl.cmbCurveBox->setView(new QListView(ctl.cmbCurveBox));
            setComBoBoxData(ctl.cmbCurveBox, m_curveCmbDatas);
            ctl.cmbCurveBox->setCurrentIndex(curveIndex);
            ctl.cmbCurveBox->blockSignals(false); // 恢复信号
            connect(ctl.cmbCurveBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slotRightCurveDataSet(int)),Qt::UniqueConnection);
        }
    }
    tbSegmentAddData(oldRow);
}

// 保存
void TestPaper::on_pushButton_Save_clicked()
{
    int parsePaperState = Parse_TestPaper_Parameters();
    if(parsePaperState == 1)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }else if(parsePaperState == 2)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1910"), MyMessageBox::Ok,"OK","");
        return;
    }
    int parseItemState = Parse_TestPaper_Items();
    if(parseItemState == 1)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }else if(parseItemState == 2)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1793"), MyMessageBox::Ok,"OK","");
        return;
    }
    if(!(Save_TestPaper_Parameters() && Save_TestPaper_Items()))
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }
    MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1378"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo("K1181"), "");

    m_strMachineUID = Global::g_machine_no;
    bool bResult;
    QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo("K1663")).arg(m_strMachineUID).arg("保存").arg(GlobalData::getLoginName1());
    auto dao = AnalysisUIDao::instance();
    dao->SelectRecord(&bResult, sql1_log);
    auto ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1259"), GlobalData::LoadLanguageInfo("K1278"), MyMessageBox::Ok| MyMessageBox::No,tr("YES"), tr("NO"));
    if (ret == MyMessageBox::No)
    {
        this->close();
        return;
    }

    InstrumentStateModel *_InstrumentState(InstrumentStateModel::instance());
    auto state = _InstrumentState->getMachineState().state;
    if (state == _InstrumentState->enumRuning
            || state == _InstrumentState->enumMaintain
            || state==_InstrumentState->enumPause)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1711"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo("K1181"), "");
        this->close();
        return;
    }
    Instrument::instance()->closeSocket();
    QString program = QCoreApplication::applicationFilePath();
    QStringList arguments = QCoreApplication::arguments();
    QProcess::startDetached(program, arguments);
    QCoreApplication::instance()->quit();
}


/**
 * @brief TestPaper::解析界面参数
 * @return true解析成功 false解析失败
 */
int TestPaper::Parse_TestPaper_Parameters()
{
    // 为所有必填控件添加实时验证
    for (QLineEdit* w : m_requiredWidgets)
    {
        if(w->text().trimmed().isEmpty())
        {
            return 1;
        }
    }
    int paperType = ui->cmbPaperType->currentData().toInt();
    // 分段膜条多验证两个参数
    if(paperType == TestPaperModel::PAPER_TYPE_SEGMENT)
    {
        if(ui->txtItemSpace->text().trimmed().isEmpty() || ui->txtItemWidth->text().trimmed().isEmpty())
        {
            return 1;
        }
    }
    QString paperName = ui->lineEdit_TestPaparName->text().simplified(); //膜条名称
    if(!m_bModify && TestPaperDao::instance()->getModel(paperName, _testPaperModel))
    {
        return 2;
    }
    _testPaperModel.setCompanyId(ui->cmbCompany->currentData().toInt());//厂家
    _testPaperModel.setPaperType(ui->cmbPaperType->currentData().toInt());//膜条类型
    _testPaperModel.setProcessId(ui->cmbProcess->currentData().toInt());//实验流程
    // 对于分段膜条是总项目段数, 对于连续模块是总条带数
    _testPaperModel.setTotalNumber(ui->lineEdit_Item_Number->text().simplified().toInt());
    _testPaperModel.setPaperName(paperName);//膜条名称
    _testPaperModel.setPaperLenght(ui->lineEdit_TestPaparLenght->text().simplified().toDouble());//膜条长度
    _testPaperModel.setPaperHeight(ui->lineEdit_TestPaparHeight->text().simplified().toDouble());//膜条高度
    _testPaperModel.setIgnoreHeadLenght(ui->lineEdit_paper_head_length->text().simplified().toDouble());//膜条头长度
    _testPaperModel.setTestBlockWidth(ui->txtItemWidth->text().simplified().toDouble());//项目块宽度
    _testPaperModel.setFuncFindDir(ui->cmbFunLineFindDirection->currentData().toInt());//功能线查找方向
    _testPaperModel.setFuncGrayThreshold(ui->txtFunThreshold->text().simplified().toDouble());//功能线阈值
    _testPaperModel.setFuncFindWidth(ui->txtFunWidth->text().simplified().toDouble());//功能线查找宽度
    _testPaperModel.setIsBlackPointDetect(ui->chkBlackSpot->isChecked());//是否开启黑点检测
    _testPaperModel.setBlackPointDetectThreshold(ui->txtBlackSpotThreshold->text().simplified().toDouble());//黑点检测阙值
    _testPaperModel.setCutOffThreshold(ui->txtCutOffThreshold->text().simplified().toDouble());//CutOff线阈值
    _testPaperModel.setCutOffValue(ui->txtCutOffValue->text().simplified().toDouble());//CutOff灰度值;
    _testPaperModel.setPaperShowAngle(ui->cmbPaperRotate->currentData().toInt());//膜条展示旋转
    _testPaperModel.setPaperBinarizationThreshold(static_cast<int>(ui->txtThreshold->text().simplified().toDouble()));//二值化阈值
    _testPaperModel.setPaperBackgroundValue(ui->txtBackGround->text().simplified().toDouble());//背景值
    _testPaperModel.setItemFindWidth(ui->txtItemSearchWidth->text().simplified().toDouble());//指标查找宽度
    _testPaperModel.setItemLineWidth(ui->txtItemLineWidth->text().simplified().toDouble());//指标线宽度
    _testPaperModel.setAnalysisPercentOfHeight(ui->txtAnalyzeHeight->text().simplified().toInt());//分析高度区间比
    _testPaperModel.setAnalysisPercentOfWidth(ui->txtAnalyzeWidth->text().simplified().toInt());//分析宽度区间比
    _testPaperModel.setPaperMmToPixel(ui->txtPixDistance->text().simplified().toDouble());//像素距离百分比
    _testPaperModel.setArticleNo(ui->txtArticleNo->text().simplified());//货号
    _testPaperModel.setPaperColorOnUi(ui->txtColorValue->text().simplified());//颜色值:

    int inputItemCnt =ui->lineEdit_TestItem_Number->text().simplified().toInt();
    _testPaperModel.setTestItemNumber(inputItemCnt); // 设置测试项目数
    if(ui->cmbPaperType->currentData().toInt()== TestPaperModel::PAPER_TYPE_SEGMENT)//分段
    {
       _testPaperModel.setTestBlockSpace(ui->txtItemSpace->text().simplified().toDouble());//项目块间距
       _testPaperModel.setTestBlockWidth(ui->txtItemWidth->text().simplified().toDouble());//项目块宽度
    }else
    {
       _testPaperModel.setTestBlockSpace(0);//项目块间距
       _testPaperModel.setTestBlockWidth(0);//项目块宽度
    }
    return 0;
}

//调用接口,保存膜条项目
int TestPaper::Parse_TestPaper_Items()
{
    int itemCnt = 0;
    qDebug()<<"ui->cmbPaperType->currentData().toInt()"<<ui->cmbPaperType->currentData().toInt();
    if(ui->cmbPaperType->currentData().toInt()== TestPaperModel::PAPER_TYPE_SEGMENT)//分段
    {
        getUIBlockAndItemData();
        auto count=ui->lineEdit_TestItem_Number->text().simplified().toInt();
        for (auto it = m_blockAndItemDataMap.begin(); it != m_blockAndItemDataMap.end(); ++it)
        {
             for(BlockItemData& blockItem: it->itemDatas)
             {
                 if(blockItem.itemType == 2) itemCnt++;
             }
        }
        qDebug()<<"itemCnt"<<itemCnt<<count;
        if(count != itemCnt)
        {
            return 2;
        }
        qDebug()<<"Save_TestPaper_Items"<<m_blockAndItemDataMap.count()<<count;
    }
    else
    {
        getUIItemData();
        for (auto it = m_itemDataMap.begin(); it != m_itemDataMap.end(); ++it)
        {
            if(it->itemType == 2) itemCnt++;
        }
        auto count=ui->lineEdit_TestItem_Number->text().simplified().toInt();
        if(count!=itemCnt)
        {
            return 2;
        }
    }
    return 0;
}

//调用接口,保存膜条参数
bool TestPaper::Save_TestPaper_Parameters()
{
    bool result = false;
    if(m_bModify)
    {
        //调用接口,修改
        result = TestPaperDao::instance()->update(_testPaperModel);
    }
    else
    {
        //调用接口,新增
        result = TestPaperDao::instance()->insert(_testPaperModel);
        _paperId = QString::number(_testPaperModel.getId());
    }
    return result;
}

//调用接口,保存膜条项目
bool TestPaper::Save_TestPaper_Items()
{
    if(ui->cmbPaperType->currentData().toInt()== TestPaperModel::PAPER_TYPE_SEGMENT)//分段
    {
        // 先删除在插入
        if(!ItemDao::instance()->deleteItems(_paperId.toInt()))
        {
            return false;
        }
        // 更新数据库
        for (auto it = m_blockAndItemDataMap.begin(); it != m_blockAndItemDataMap.end(); ++it)
        {
            int idx = 1; // 项目在段中的位置, 从1开始
            for(BlockItemData& sub:it.value().itemDatas)
            {
                qDebug()<<"item"<<sub.strItemName<<idx;
                ItemModel item;
                item.setSegmentIndex(it.value().blockData.serialNo);
                item.setIsNull(sub.ignore?1:0);
                item.setCurveId(sub.curve);
                item.setRulesId(sub.judgerule);
                item.setPositionNo(idx++);
                item.setPosition(0);
                item.setItemName(sub.itemType, sub.strItemName);
                item.setTestPaperID(_paperId.toInt());
                if(!ItemDao::instance()->insert(item))
                {
                    return false;
                }
            }
        }
    }
    else
    {
        if(!ItemDao::instance()->deleteItems(_paperId.toInt()))
        {
            return false;
        }
        for (auto it = m_itemDataMap.begin(); it != m_itemDataMap.end(); ++it)
        {
            ItemModel item;
            item.setIsNull(it.value().isNullArea?1:0);
            item.setCurveId(it.value().curve);
            item.setSegmentIndex(0);
            item.setRulesId(it.value().judgerule);
            item.setPositionNo(it.value().serialNo);
            item.setPosition(it.value().position);
            item.setItemName(it.value().itemType, it.value().strItemName);
            item.setTestPaperID(_paperId.toInt());
            if(!ItemDao::instance()->insert(item))
            {
                return false;
            }
        }
    }
    return true;
}

void TestPaper::getAllItemControl()
{
    if(!m_gridItemCtl.itemCtlMap.isEmpty() || !m_gridBlockCtl.blockCtlMap.isEmpty())
        return;

    m_gridItemCtl.table=ui->tbSegment;
    m_gridBlockCtl.table=ui->tbSegment;
    auto fun=[this](const QGridLayout * glay,QVector<QLabel *>&headVect)
    {
        if(glay==nullptr) return;
        headVect.clear();
        for (int row = 0; row < glay->rowCount(); ++row)
        {
            Item_Control ctr;    
			int k = 0;
            for (int col = 0; col < glay->columnCount(); ++col)
            {
                QLayoutItem *item =  glay->itemAtPosition(row, col);
                if (item == nullptr) continue;
                QWidget *widget = item->widget();
                if (!widget) continue;

                if(row==0)
                {
                    headVect.push_back(static_cast<QLabel *>(widget));
                    continue;
                }              

                if(col==0)
                {
                    ctr.label=static_cast<QLabel *>(widget);
                    if(ctr.label->text().simplified().toInt()>0)
                    {
                        k=ctr.label->text().simplified().toInt();
                    }
                }else if(col==1)
                {
                     ctr.combo_item_type = static_cast<QComboBox *>(widget);
                     ctr.combo_item_type->setView(new QListView(widget));
                     setComBoBoxData(ctr.combo_item_type,m_itemTypeCmbDatas);
                }
                else if(col==2)
                {
                    ctr.lineEdit_Name=static_cast<QLineEdit *>(widget);
                    ui->lineEdit_Position_1->setValidator(new QRegExpValidator(QRegExp("^[+-]?(?:[0-9]+|[0-9]*\\.[0-9]+|\\.[0-9]+)$"), this));
                }
                else if(col==3)
                {
                    ctr.checkBox=static_cast<QCheckBox *>(widget);
                    connect(ctr.checkBox,&QCheckBox::clicked,this,[ctr](bool checked)
                    {
                        if (checked)
                        {
                            ctr.lineEdit_Name->setText("");
                            ctr.lineEdit_Name->setEnabled(false);
                        }
                        else
                        {
                            ctr.lineEdit_Name->setEnabled(true);
                        }
                    });
                }
                else if(col==4)
                {
                    ctr.lineEdit_Position=static_cast<QLineEdit *>(widget);
                }
                else if(col==5)
                {
                    ctr.combo_box_rule=static_cast<QComboBox *>(widget);
                    ctr.combo_box_rule->setView(new QListView(widget));
                    setComBoBoxData(ctr.combo_box_rule,m_ruleCmbDatas);
                    connect(ctr.combo_box_rule,SIGNAL(currentIndexChanged(int)),this,SLOT(slotCmbRuleDataSet(int)),Qt::UniqueConnection);
                }
                else if(col==6)
                {
                    ctr.cmbCurve=static_cast<QComboBox *>(widget);
                    ctr.cmbCurve->setView(new QListView(widget));
                    setComBoBoxData(ctr.cmbCurve,m_curveCmbDatas);
                    connect(ctr.cmbCurve,SIGNAL(currentIndexChanged(int)),this,SLOT(slotCmbCurveDataSet(int)),Qt::UniqueConnection);
                }
            }
            if(k>0) m_gridItemCtl.itemCtlMap.insert(k,ctr);
        }
    };

    fun(ui->gridLayout_3,m_gridItemCtl.gridHead1);
    fun(ui->gridLayout_2,m_gridItemCtl.gridHead2);
    QVector<ComboxData> boxDatas{};
    for(int i=0;i<=10;i++)
    {
        boxDatas.push_back(ComboxData(QString::number(i),QString::number(i)));
    }
    auto sgfun=[this,&boxDatas](const QGridLayout * glay,QVector<QLabel *>&headVect)
    {
        if(glay==nullptr)
            return;
        headVect.clear();
        for (int row = 0; row < glay->rowCount(); ++row)
        {
            BlockControl block;
            int k = 0;
            for (int col = 0; col < glay->columnCount(); ++col)
            {
                QLayoutItem *item =  glay->itemAtPosition(row, col);
                if (item == nullptr)
                    continue;
                QWidget *widget = item->widget();
                if (!widget)
                    continue;

                if(row==0)
                {
                    headVect.push_back(static_cast<QLabel *>(widget));
                    continue;
                }

                if(col==0)
                {
                    block.label=static_cast<QLabel *>(widget);
                    if(block.label->text().simplified().toInt()>0)
                    {
                        k=block.label->text().simplified().toInt();
                    }

                }
                else if(col==1)
                {
                    block.cmbItemCount=static_cast<QComboBox *>(widget);
                    block.cmbItemCount->setObjectName(QString::number(k));
                    block.cmbItemCount->setView(new QListView(widget));
                    setComBoBoxData(block.cmbItemCount,boxDatas);
                    connect(block.cmbItemCount,SIGNAL(currentTextChanged(const QString &)),this,SLOT(slotCreatDetailRows(const QString &)),Qt::UniqueConnection);
                }
            }
            if(k>0) m_gridBlockCtl.blockCtlMap.insert(k,block);
        }
    };
    sgfun(ui->gridLayout,m_gridBlockCtl.gridHead1);
    sgfun(ui->gridLayout_6,m_gridBlockCtl.gridHead2);
}

void TestPaper::getUIItemData()
{
    m_itemDataMap.clear();
    qDebug()<<"m_gridItemCtl.itemCtlMap"<<m_gridItemCtl.itemCtlMap.count();
	int i = 1;
    for(auto it:m_gridItemCtl.itemCtlMap)
    {
        TestPaper_Item itemData;
        itemData.serialNo = it.label->text().simplified().toInt();
        itemData.isNullArea = it.checkBox->isChecked();
        // 如果未选中空白
        if(!it.checkBox->isChecked())
        {
            if(it.combo_item_type->currentIndex() < 0 ||
                    it.combo_box_rule->currentIndex() < 0 ||
                    it.cmbCurve->currentIndex() < 0 ||
                    it.lineEdit_Name->text().simplified().isEmpty() ||
                    it.lineEdit_Position->text().simplified().isEmpty())
            {
                break;
            }
            itemData.curve=it.cmbCurve->currentData().toInt();
            itemData.itemType=it.combo_item_type->currentData().toInt();
            itemData.position=it.lineEdit_Position->text().simplified().toDouble();
            itemData.judgerule = it.combo_box_rule->currentData().toInt();
            itemData.strItemName = it.lineEdit_Name->text().simplified();
        }else
        {
            itemData.strItemName = "";
            itemData.position = 0;
        }

        qDebug()<<"getUIItemData"<<itemData.serialNo<<itemData.curve<<itemData.itemType<<itemData.position<<itemData.isNullArea<<itemData.judgerule<<itemData.strItemName;
        m_itemDataMap.insert(i,itemData);
		i++;
    }
    qDebug()<<"m_gridItemCtl.itemCtlMap"<<m_gridItemCtl.itemCtlMap.count();
}

void TestPaper::getUIBlockAndItemData()
{
    m_blockAndItemDataMap.clear();
    auto &map=m_gridBlockCtl.blockCtlMap;
    for(auto &blockCtl:map)
    {
        if(blockCtl.cmbItemCount->currentIndex()<0) break;
        BlockAndItemData blockItemData;
        BlockData bData;
        QVector<BlockItemData> bItemDatas{};
        bData.serialNo=blockCtl.label->text().toInt();
        bData.itemCount=blockCtl.cmbItemCount->currentText().toInt();
        blockItemData.blockData=bData;
        auto itemIt=m_blockItemCtlMap.find(bData.serialNo);
        if(itemIt==m_blockItemCtlMap.end())
        {
            blockItemData.itemDatas=bItemDatas;
            m_blockAndItemDataMap.insert(bData.serialNo,blockItemData);
            continue;
        }
        auto &vect=itemIt.value();
        for(auto &itemCtl:vect)
        {
            if(itemCtl.cmbCurveBox->currentIndex() < 0 ||
                    itemCtl.cmbItemType->currentIndex() < 0 ||
                    itemCtl.cmbRuleBox->currentIndex() < 0 ||
                    itemCtl.itemNameEdit->text().trimmed().isEmpty())
            {
                break;
            }
            BlockItemData itemData;
            itemData.serialNo=itemCtl.serialNo;
            itemData.curve=itemCtl.cmbCurveBox->currentData().toInt();
            itemData.ignore=itemCtl.checkBox->isChecked();
            itemData.blockNo=itemCtl.blockNo;
            itemData.itemType=itemCtl.cmbItemType->currentData().toInt();
            itemData.judgerule=itemCtl.cmbRuleBox->currentData().toInt();
            itemData.strItemName=itemCtl.itemNameEdit->text().simplified();
            qDebug()<<"getUIBlockAndItemData"<<bData.serialNo<<itemData.serialNo<<itemData.curve<<itemData.blockNo<<itemData.itemType<<itemData.judgerule<<itemData.strItemName;
            bItemDatas.push_back(itemData);
        }
        blockItemData.itemDatas=bItemDatas;
        m_blockAndItemDataMap.insert(bData.serialNo,blockItemData);
    }
}

void TestPaper::initComboBox()
{    
    QVector<ComboxData>boxDatas;
    CompanyDao* companyDao = CompanyDao::instance();
    QVector<CompanyModel> companyModels = companyDao->getAllRows();
    for(CompanyModel& model : companyModels)
    {
        qDebug()<<"company name"<<model.getName();
        boxDatas.push_back(ComboxData(model.getName(), QString::number(model.getId())));
    }
    setComBoBoxData(ui->cmbCompany,boxDatas);
    connect(ui->cmbCompany,&QComboBox::currentTextChanged,this,&TestPaper::slotCmbCompanyTextChanged);

    boxDatas.clear();
    boxDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1809"),QString::number(TestPaperModel::PAPER_TYPE_CONTINUOUS)));
    boxDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1810"),QString::number(TestPaperModel::PAPER_TYPE_SEGMENT)));
    setComBoBoxData(ui->cmbPaperType,boxDatas);
    ui->cmbPaperType->setCurrentText(GlobalData::LoadLanguageInfo("K1809"));

    boxDatas.clear();
    boxDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1813"),QString::number(TestPaperModel::PAPER_FUNC_FIND_DIR_HEAD)));
    boxDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1814"),QString::number(TestPaperModel::PAPER_FUNC_FIND_DIR_TAIL)));
    setComBoBoxData(ui->cmbFunLineFindDirection,boxDatas);
    ui->cmbFunLineFindDirection->setCurrentText(GlobalData::LoadLanguageInfo("K1813"));

    boxDatas.clear();
    boxDatas.push_back(ComboxData("0°", QString::number(TestPaperModel::PAPER_SHOW_DRAGE_0)));
    boxDatas.push_back(ComboxData("180°",QString::number(TestPaperModel::PAPER_SHOW_DRAGE_180)));
    setComBoBoxData(ui->cmbPaperRotate,boxDatas);
    ui->cmbPaperRotate->setCurrentText("0°");
}

void TestPaper::setComBoBoxData(QComboBox *cmb, const QVector<ComboxData> &datas)
{
    if (!cmb) return;
    cmb->blockSignals(true);      // 1. 阻塞信号，防止填充时触发业务槽函数
    cmb->clear();                 // clear() 后 currentIndex() 自动变为 -1
    for (const auto& data : datas) {
        cmb->addItem(data.cmbText, data.cmbData);
    }
    cmb->blockSignals(false);     // 2. 恢复信号
    cmb->setCurrentIndex(-1);     // 3. 强制回到“未选择”状态，与校验逻辑一致
}

void TestPaper::uiCtlSet(const int itemCount)
{
    int data{ui->cmbPaperType->currentData().toInt()};
    // 0为连续膜条 1为分段膜条
    if(data == TestPaperModel::PAPER_TYPE_SEGMENT)
    {
        ui->txtItemWidth->setEnabled(true);
        ui->txtItemSpace->setEnabled(true);
        ui->gridLayout_3->setContentsMargins(0,0,0,0);
        ui->lblItemNum->setText(GlobalData::LoadLanguageInfo("K1127"));
        m_gridItemCtl.hiddeAll();
        if(itemCount<0)
            m_gridBlockCtl.showAllCtl();
        else
            m_gridBlockCtl.showCtlByCount(itemCount);
    }
    else
    {
        ui->txtItemWidth->setEnabled(false);
        ui->txtItemSpace->setEnabled(false);
        ui->gridLayout_3->setContentsMargins(40,0,0,0);
        ui->lblItemNum->setText(GlobalData::LoadLanguageInfo("K1129"));
        m_gridBlockCtl.hiddeAll();
        if(itemCount<0)
            m_gridItemCtl.showAllCtl();
        else
            m_gridItemCtl.showCtlByCount(itemCount);
    }
}

void TestPaper::tbSegmentAddData(const int oldRow)
{
    if(ui->tbSegment->isHidden())
        return;

    while (oldRow<ui->tbSegment->rowCount())
        ui->tbSegment->removeRow(oldRow);

    int count=ui->tbSegment->rowCount();
    for(auto &vect:m_blockItemCtlMap)
    {
        for(auto &ctl:vect)
        {
            if(!ctl.isNew)
                continue;
            ui->tbSegment->insertRow(count);
            ctl.serialNo=count+1;
            ui->tbSegment->setItem(count,0,new QTableWidgetItem(QString::number(count+1)));
            ui->tbSegment->setCellWidget(count,1,ctl.cmbItemType);
            ui->tbSegment->setCellWidget(count,2,ctl.itemNameEdit);
            ui->tbSegment->setCellWidget(count,3,ctl.checkBox);
            ui->tbSegment->setItem(count,4,new QTableWidgetItem(QString::number(ctl.blockNo)));
            ui->tbSegment->setCellWidget(count,5,ctl.cmbRuleBox);
            ui->tbSegment->setCellWidget(count,6,ctl.cmbCurveBox);
            ctl.isNew=false;
            count++;
        }
    }
}

void TestPaper::on_pushButton_Cancel_clicked() 
{
    this->close();
}

void TestPaper::on_cmbPaperType_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    bool b=true;
    int count=ui->lineEdit_Item_Number->text().simplified().toInt(&b);
    if(!b)
        count=-1;
    uiCtlSet(count);
}

void TestPaper::slotCmbCompanyTextChanged(const QString &text)
{
    Q_UNUSED(text)
    //text 为厂家名称，根据厂家名称获取实验流程接口
    QString currentData=ui->cmbCompany->currentData().toString();//厂家ID
    ProcessDao* dao = ProcessDao::instance();
    // 只选择与本厂家相关的膜条ID
    QVector<ProcessModel> processVect = dao->getModels(ui->cmbCompany->currentData().toInt());
    QVector<ComboxData> boxDatas;
    //调用接口,实验流程
    for(ProcessModel &model : processVect)
    {
        boxDatas.push_back(ComboxData(model.getProcessName(), QString::number(model.getId())));
    }
    setComBoBoxData(ui->cmbProcess,boxDatas);
}
