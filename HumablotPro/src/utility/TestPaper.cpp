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
    auto doublReg{new QRegExpValidator(QRegExp("^(?:[1-9]\\d{0,3}|0)(?:\\.\\d{1,3})?$"), this)};
    ui->lineEdit_TestPaparLenght->setValidator(doublReg);
    ui->lineEdit_paper_head_length->setValidator(doublReg);
    ui->txtItemSpace->setValidator(doublReg);
    ui->txtItemWidth->setValidator(doublReg);
    ui->lineEdit_FuncPosition->setValidator(doublReg);
    auto intReg{new QIntValidator(0,9999,this)};
    ui->txtFunThreshold->setValidator(intReg);
    ui->txtFunWidth->setValidator(doublReg);
    ui->txtBlackSpotThreshold->setValidator(intReg);
    ui->lineEdit_CutOff_Position->setValidator(doublReg);
    ui->txtCutOffThreshold->setValidator(intReg);
    ui->txtCutOffValue->setValidator(intReg);
    ui->txtThreshold->setValidator(intReg);
    ui->txtBackGround->setValidator(intReg);
    ui->txtItemSearchWidth->setValidator(doublReg);
    ui->txtAnalyzeHeight->setValidator(doublReg);
    ui->txtAnalyzeWidth->setValidator(doublReg);
    ui->txtPixDistance->setValidator(doublReg);

    ui->lblCompany->setText(GlobalData::LoadLanguageInfo("K1791"));
    ui->cmbCompany->setView(new QListView(this));
    ui->lblPaperType->setText(GlobalData::LoadLanguageInfo("K1554"));
    ui->cmbPaperType->setView(new QListView(this));
    ui->lblProcess->setText(GlobalData::LoadLanguageInfo("K1792"));
    ui->cmbProcess->setView(new QListView(this));

    ui->lblPaperName->setText(GlobalData::LoadLanguageInfo("K1100"));
    ui->lblPaperLength->setText(GlobalData::LoadLanguageInfo("K1128"));
    ui->lblHeadLength->setText(GlobalData::LoadLanguageInfo("K1126"));
    ui->lblItemSpace->setText(GlobalData::LoadLanguageInfo("K1708"));
    ui->lblItemWidth->setText(GlobalData::LoadLanguageInfo("K1707"));
    ui->lblFunDirection->setText(GlobalData::LoadLanguageInfo("K1123"));
    ui->cmbFunDirection->setView(new QListView(this));
    ui->lblFunPostion->setText(GlobalData::LoadLanguageInfo("K1119"));
    ui->lblFunThreshold->setText(GlobalData::LoadLanguageInfo("K1118"));
    ui->lblFunWidth->setText(GlobalData::LoadLanguageInfo("K1709"));
    ui->chkBlackSpot->setText(GlobalData::LoadLanguageInfo("K1710"));
    ui->lblBlackSpotThreshold->setText(GlobalData::LoadLanguageInfo("K1741"));
    ui->checkBox_CutOff->setText(GlobalData::LoadLanguageInfo("K1117"));
    ui->lblCutOffPos->setText(GlobalData::LoadLanguageInfo("K1048"));
    ui->lblCutOffThreshold->setText(GlobalData::LoadLanguageInfo("K1116"));
    ui->lblCutOffValue->setText(GlobalData::LoadLanguageInfo("K1800"));
    ui->lblRotate->setText(GlobalData::LoadLanguageInfo("K1802"));
    ui->cmbRotate->setView(new QListView(this));
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
    ui->rdRulesAllSet->setChecked(true);
    ui->rdCurveAllSet->setChecked(true);
    ui->pushButton_Set->setText(GlobalData::LoadLanguageInfo("K1115"));

    ui->lblG1ItemName->setText(GlobalData::LoadLanguageInfo("K1131"));
    ui->lblG1IsEmpty->setText(GlobalData::LoadLanguageInfo("K1132"));
    ui->lblG1Position->setText(GlobalData::LoadLanguageInfo("K1115"));
    ui->lblG1Rules->setText(GlobalData::LoadLanguageInfo("K1133"));
    ui->lblG1Curves->setText(GlobalData::LoadLanguageInfo("K1794"));

    ui->lblG2ItemName->setText(GlobalData::LoadLanguageInfo("K1131"));
    ui->lblG2IsEmpty->setText(GlobalData::LoadLanguageInfo("K1132"));
    ui->lblG2Position->setText(GlobalData::LoadLanguageInfo("K1115"));
    ui->lblG2Rules->setText(GlobalData::LoadLanguageInfo("K1133"));
    ui->lblG2Curves->setText(GlobalData::LoadLanguageInfo("K1794"));

    ui->lblG3IsEmpty->setText(GlobalData::LoadLanguageInfo("K1132"));
    ui->lblG3ItemCount->setText(GlobalData::LoadLanguageInfo("K1797"));
    ui->lblG3ItemStartPos->setText(GlobalData::LoadLanguageInfo("K1798"));
    ui->lblG3ItemDistance->setText(GlobalData::LoadLanguageInfo("K1799"));

    ui->lblG4IsEmpty->setText(GlobalData::LoadLanguageInfo("K1132"));
    ui->lblG4ItemCount->setText(GlobalData::LoadLanguageInfo("K1797"));
    ui->lblG4ItemStartPos->setText(GlobalData::LoadLanguageInfo("K1798"));
    ui->lblG4ItemDistance->setText(GlobalData::LoadLanguageInfo("K1799"));
    ui->pushButton_Save->setText(GlobalData::LoadLanguageInfo("K1038"));
    ui->pushButton_Cancel->setText(GlobalData::LoadLanguageInfo("K1134"));

    ui->tbSegment->verticalHeader()->setVisible(false);
    QStringList headerString;
    QString sz1 = GlobalData::LoadLanguageInfo("K1767");
    QString sz2 = GlobalData::LoadLanguageInfo("K1811");
    QString sz3 = GlobalData::LoadLanguageInfo("K1131");
    QString sz4 = GlobalData::LoadLanguageInfo("K1812");
    QString sz5 = GlobalData::LoadLanguageInfo("K1133");
    QString sz6 = GlobalData::LoadLanguageInfo("K1794");
    headerString<<sz1<<sz2<<sz3<<sz4<<sz5<<sz6;
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
    ui->tbSegment->setColumnWidth(2,165);
    //ui->lineEdit_Item_Number->setPlaceholderText("       测试");
    bool bResult=true;
    auto dao = AnalysisUIDao::instance();
    auto ruleQuery = dao->SelectRulues(&bResult);
    while (ruleQuery.next())
    {
        ComboxData cmbData(GlobalData::LoadLanguageInfo(ruleQuery.value("RuleName").toString()),ruleQuery.value("pkid").toString());
        m_ruleCmbDatas.push_back(cmbData);
    }
    //m_curveCmbDatas //调用接口,曲线下拉框数据
    getAllItemControl();
    initComboBox();
}

void TestPaper::Set_UI(const QString &paperId, const QString &companyId)
{
    if (paperId.isEmpty())
        return;
    m_bModify=true;
    _paperId=paperId;
    m_Company_ID=companyId;
    bool bResult;
    auto dao = AnalysisUIDao::instance();
    TestPaperModel testPaperModel;
    bResult = dao->QueryTestPaper(paperId, testPaperModel);//接口调用,获取膜条数据
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1263"), MyMessageBox::Ok,"OK","");
        return;
    }
    bool isSegmentPaper = testPaperModel.getPaperType() == 1;
    ui->cmbCompany->setCurrentIndex(ui->cmbCompany->findData(m_Company_ID));//公司
    auto segmentTag = isSegmentPaper ? "2" : "1";
    ui->cmbPaperType->setCurrentIndex(ui->cmbPaperType->findData(segmentTag));
    // TODO::实验流程
    auto process="";//paperQuery.value("").toString();//调用接口,实验流程
    ui->cmbProcess->setCurrentIndex(ui->cmbProcess->findData(process));
    ui->lineEdit_Item_Number->setText(QString::number(testPaperModel.getTotalNumber()));
    ui->lineEdit_TestPaparName->setText(testPaperModel.getPaperName());
    ui->lineEdit_TestPaparLenght->setText(QString::number(testPaperModel.getPaperLenght(), 'f', 2));


    ui->lineEdit_paper_head_length->setText(QString::number(testPaperModel.getIgnoreHeadLenght(), 'f', 2));
    // TODO::宽度
    ui->txtItemSpace->setText("");//调用接口
    ui->txtItemWidth->setText(QString::number(testPaperModel.getTestBlockWidth(), 'f', 2));//调用接口
    auto funDirection = testPaperModel.getFuncFindDir()==0?"1":"2";//调用接口
    ui->cmbFunDirection->setCurrentIndex(ui->cmbFunDirection->findData(funDirection));
    ui->lineEdit_FuncPosition->setText(QString::number(testPaperModel.getFuncPosition(), 'f', 2));
    ui->txtFunThreshold->setText(QString::number(testPaperModel.getFuncGrayThreshold(), 'f', 2));
    ui->txtFunWidth->setText(QString::number(testPaperModel.getFuncFindWidth(), 'f', 2));//调用接口,功能线宽度
    bool isCheckBlackSpot=testPaperModel.getIsBlackPointDetect();//调用接口,是否开启黑点检测
    ui->chkBlackSpot->setChecked(isCheckBlackSpot);
    ui->txtBlackSpotThreshold->setText(QString::number(testPaperModel.getBlackPointDetectThreshold(), 'f', 2));//调用接口,黑点检测阙值
    ui->checkBox_CutOff->setChecked(testPaperModel.getIsCutOff());
    ui->lineEdit_CutOff_Position->setText(QString::number(testPaperModel.getCutOffPosition(), 'f', 2));
    ui->lblCutOffThreshold->setText(QString::number(testPaperModel.getCutOffThreshold(), 'f', 2));//调用接口,CutOff线阈值
    ui->txtCutOffValue->setText(QString::number(testPaperModel.getCutOffValue(), 'f', 2));
    auto angle=testPaperModel.getPaperShowAngle()==0?"0":"180";//调用接口
    ui->cmbRotate->setCurrentIndex(ui->cmbRotate->findData(angle));
    ui->txtThreshold->setText(QString::number(testPaperModel.getPaperBinarizationThreshold(), 'f', 2));
    ui->txtBackGround->setText(QString::number(testPaperModel.getPaperBackgroundValue(), 'f', 2));
    ui->txtItemSearchWidth->setText(QString::number(testPaperModel.getItemFindWidth(), 'f', 2));//调用接口,指标查找宽度
    ui->txtAnalyzeHeight->setText(QString::number(testPaperModel.getAnalysisPercentOfHeight()));
    ui->txtAnalyzeWidth->setText(QString::number(testPaperModel.getAnalysisPercentOfWidth()));//调用接口,分析宽度区间比
    ui->txtPixDistance->setText(QString::number(testPaperModel.getPaperMmToPixel(), 'f', 2));//调用接口,像素距离百分比
    ui->txtArticleNo->setText(testPaperModel.getArticleNo());
    ui->txtColorValue->setText(testPaperModel.getPaperColorOnUi());

    uiCtlSet(ui->lineEdit_Item_Number->text().toInt());
    auto TestPaperItemQuery = dao->SelectTestPaperItems(paperId, &bResult);
    //调用接口,加载所有项目
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1263"), MyMessageBox::Ok,"OK","");
        return;
    }

    if(!isSegmentPaper)
    {
        int i=1;
        while (TestPaperItemQuery.next())
        {
            if(i>m_gridItemCtl.itemCtlMap.count())
            {
                eLog("TestPaperItemQuery error");
                break;
            }
            Item_Control &ctl=m_gridItemCtl.itemCtlMap[i];
            ctl.lineEdit_Name->setText(TestPaperItemQuery.value("itemName").toString());
            ctl.checkBox->setChecked(TestPaperItemQuery.value("IsNull").toInt()>0);
            ctl.lineEdit_Position->setText(TestPaperItemQuery.value("position").toString());
            ctl.combo_box_rule->setCurrentIndex(ctl.combo_box_rule->findData(TestPaperItemQuery.value("RulesId").toString()));
            //调用接口 ,定标曲线
            ctl.cmbCurve->setCurrentText(TestPaperItemQuery.value("").toString());
            i++;
        }
        return;
    }

    QVector<BlockData>blockVect;//调用接口,分段膜条所有的块数据
    if(blockVect.count()>30)
    {
        eLog("vect count over limit");
        return;
    }
    for(int i=1;i<=blockVect.count();i++)
    {
        auto it = m_gridBlockCtl.blockCtlMap.find(i);
        if(it==m_gridBlockCtl.blockCtlMap.end())
        {
            eLog("sgItemCtlMap data error,key:{}",i);
            continue;
        }
        auto &b=blockVect.at(i-1);
        auto ctl=it.value();
        ctl.label->setText(QString::number(i));
        if(i!=b.serialNo)
            eLog("error,i:{},serialNo:{}",i,b.serialNo);
        ctl.checkBox->setChecked(b.isNullArea);
        ctl.distanceLineEdit->setText(QString::number(b.distance));
        ctl.startPosLineEdit->setText(QString::number(b.startPos));
        QVector<BlockItemData> itemDataVect;//调用接口,块对应的项目数据
        auto count=itemDataVect.count();
        ctl.cmbItemCount->setCurrentText(QString::number(count));
        auto itemCtlIt=m_blockItemCtlMap.find(i);
        if(itemCtlIt==m_blockItemCtlMap.end())
        {
            eLog("data error,key:{}",i);
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
            detailCtl.blockNo=i;
            detailCtl.cmbRuleBox->setCurrentIndex(detailCtl.cmbRuleBox->findData(item.judgerule));
            detailCtl.cmbCurveBox->setCurrentIndex(detailCtl.cmbCurveBox->findData(item.curve));
            detailCtl.cmbItemType->setCurrentIndex(detailCtl.cmbItemType->findData(item.itemType));
            detailCtl.itemNameEdit->setText(item.strItemName);
            j++;
        }
    }
}

//void TestPaper::closeEvent(QCloseEvent *event)
//{
//    event->ignore();
//    this->hide();
//}

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
    auto it=m_blockItemCtlMap.find(seqNo);
    if (it != m_blockItemCtlMap.end())
    {
		oldCtlVect = it.value();
        m_blockItemCtlMap.remove(seqNo);
    }
    QVector<ComboxData>ItemTypes{};
    ItemTypes.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1807"),"1"));
    ItemTypes.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1808"),"2"));
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
            QString itemName="";
			if (ctl.cmbItemType != nullptr)
			{
				typeIndex = ctl.cmbItemType->currentIndex();
				ruleIndex = ctl.cmbRuleBox->currentIndex();
				curveIndex = ctl.cmbCurveBox->currentIndex();
                itemName=ctl.itemNameEdit->text().simplified();
			}
            ctl.isNew=true;
            ctl.itemNameEdit=new QLineEdit(this);
            ctl.itemNameEdit->setText(itemName);

            ctl.cmbItemType = new QComboBox(this);
            ctl.cmbItemType->setView(new QListView(ctl.cmbItemType));
            setComBoBoxData(ctl.cmbItemType, ItemTypes);
            ctl.cmbItemType->setCurrentIndex(typeIndex);

            ctl.cmbRuleBox = new QComboBox(this);
            ctl.cmbRuleBox->setView(new QListView(ctl.cmbRuleBox));
            setComBoBoxData(ctl.cmbRuleBox, m_ruleCmbDatas);
            ctl.cmbRuleBox->setCurrentIndex(ruleIndex);
            connect(ctl.cmbRuleBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slotRightCmbRuleDataSet(int)),Qt::UniqueConnection);

            ctl.cmbCurveBox = new QComboBox(this);
            ctl.cmbCurveBox->setView(new QListView(ctl.cmbCurveBox));
            setComBoBoxData(ctl.cmbCurveBox, m_curveCmbDatas);
            ctl.cmbCurveBox->setCurrentIndex(curveIndex);
            connect(ctl.cmbCurveBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slotRightCurveDataSet(int)),Qt::UniqueConnection);
        }
    }
    tbSegmentAddData(oldRow);
}

void TestPaper::on_pushButton_Save_clicked()
{
    if(Save_TestPaper_Parameters() == false)
        return;
    if (Save_TestPaper_Items() == false)
        return;

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

    // 或者   aApp->closeAllWindows();
    Instrument::instance()->closeSocket();
    QString program = QCoreApplication::applicationFilePath();
    QStringList arguments = QCoreApplication::arguments();
    QProcess::startDetached(program, arguments);
    QCoreApplication::instance()->quit();
}

//调用接口,保存膜条参数
bool TestPaper::Save_TestPaper_Parameters()
{
    //ui->cmbCompany->currentData().toString();//厂家
    //ui->cmbPaperType->currentData().toString();//膜条类型
    //ui->cmbProcess->currentData().toString();//实验流程
    //lineEdit_Item_Number;//项目数量
    //lineEdit_TestPaparName;//膜条名称
    //lineEdit_TestPaparLenght;//膜条长度
    //lineEdit_paper_head_length;//膜条头长度
    //txtItemSpace;//项目块间距
    //txtItemWidth;//项目块宽度
    //ui->cmbFunDirection->currentData().toString();//功能线查找方向
    //lineEdit_FuncPosition;//功能条位置
    //txtFunThreshold;//功能线阈值
    //txtFunWidth;//功能线查找宽度
    //ui->chkBlackSpot->isChecked();//是否开启黑点检测
    //txtBlackSpotThreshold;//黑点检测阙值
    //ui->checkBox_CutOff->isChecked();// 是否有CufOff线
    //lineEdit_CutOff_Position;//CutOff位置
    //txtCutOffThreshold;//CutOff线阈值
    //txtCutOffValue;//CutOff灰度值;
    //ui->cmbRotate->currentData().toString();//膜条展示旋转
    //txtThreshold;//二值化阈值
    //txtBackGround;//背景值
    //txtItemSearchWidth;//指标查找宽度
    //txtAnalyzeHeight;//分析高度区间比
    //txtAnalyzeWidth;//分析宽度区间比
    //txtPixDistance;//像素距离百分比
    //txtArticleNo;//货号
    //txtColorValue;//颜色值:

    if(m_bModify)
    {
        //调用接口,修改
    }
    else
    {
        //调用接口,新增
    }
    return true;
}

//调用接口,保存膜条项目
bool TestPaper::Save_TestPaper_Items()
{
    if(ui->cmbPaperType->currentData().toInt()==2)//分段
    {
        getUIBlockAndItemData();
        auto count=ui->lineEdit_Item_Number->text().simplified().toInt();
        if(m_blockAndItemDataMap.count()!=count)
        {
            QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180"),GlobalData::LoadLanguageInfo("K1793"),GlobalData::LoadLanguageInfo("K1181"));
            return false;
        }

        //m_blockAndItemDataMap; //调用接口，保存此变量中的数据，块--项目
        if(m_bModify)//修改
        {

        }
        else
        {//新增

        }
    }
    else
    {
        getUIItemData();
        auto count=ui->lineEdit_Item_Number->text().simplified().toInt();
        if(m_itemDataMap.count()!=count)
        {
            QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180"),GlobalData::LoadLanguageInfo("K1793"),GlobalData::LoadLanguageInfo("K1181"));
            return false;
        }

        //m_itemDataMap;  //调用接口,保存此变量中的数据
        if(m_bModify)//修改
        {

        }
        else
        {//新增

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
        if(glay==nullptr)
            return;
        headVect.clear();
        for (int row = 0; row < glay->rowCount(); ++row)
        {
            Item_Control ctr;    
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
                    ctr.label=static_cast<QLabel *>(widget);
                    if(ctr.label->text().simplified().toInt()>0)
                        k=ctr.label->text().simplified().toInt();
                }
                else if(col==1)
                {
                    ctr.lineEdit_Name=static_cast<QLineEdit *>(widget);
                    ui->lineEdit_Position_1->setValidator(new QRegExpValidator(QRegExp("[0-9.]+"), this));
                }
                else if(col==2)
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
                else if(col==3)
                    ctr.lineEdit_Position=static_cast<QLineEdit *>(widget);
                else if(col==4)
                {
                    ctr.combo_box_rule=static_cast<QComboBox *>(widget);
                    ctr.combo_box_rule->setView(new QListView(widget));
                    setComBoBoxData(ctr.combo_box_rule,m_ruleCmbDatas);
                    connect(ctr.cmbCurve,SIGNAL(currentIndexChanged(int)),this,SLOT(slotCmbCurveDataSet(int)),Qt::UniqueConnection);
                }
                else if(col==5)
                {
                    ctr.cmbCurve=static_cast<QComboBox *>(widget);
                    ctr.cmbCurve->setView(new QListView(widget));
                    setComBoBoxData(ctr.cmbCurve,m_curveCmbDatas);
                    connect(ctr.combo_box_rule,SIGNAL(currentIndexChanged(int)),this,SLOT(slotCmbRuleDataSet(int)),Qt::UniqueConnection);
                }
            }
            if(k>0)
                m_gridItemCtl.itemCtlMap.insert(k,ctr);
        }
    };

    fun(ui->gridLayout_3,m_gridItemCtl.gridHead1);
    fun(ui->gridLayout_2,m_gridItemCtl.gridHead2);
    QVector<ComboxData> boxDatas{};
    for(int i=1;i<=10;i++)
        boxDatas.push_back(ComboxData(QString::number(i),QString::number(i)));
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
                        k=block.label->text().simplified().toInt();
                }
                else if(col==1)
                    block.checkBox=static_cast<QCheckBox *>(widget);
                else if(col==2)
                {
                    block.cmbItemCount=static_cast<QComboBox *>(widget);
                    block.cmbItemCount->setObjectName(QString::number(k));
                    block.cmbItemCount->setView(new QListView(widget));
                    setComBoBoxData(block.cmbItemCount,boxDatas);
                    connect(block.cmbItemCount,SIGNAL(currentTextChanged(const QString &)),this,SLOT(slotCreatDetailRows(const QString &)),Qt::UniqueConnection);
                }
                else if(col==3)
                {
                    block.startPosLineEdit=static_cast<QLineEdit *>(widget);
                }
                else if(col==4)
                {
                    block.distanceLineEdit=static_cast<QLineEdit *>(widget);
                }
            }
            if(k>0)
                m_gridBlockCtl.blockCtlMap.insert(k,block);
        }
    };
    sgfun(ui->gridLayout,m_gridBlockCtl.gridHead1);
    sgfun(ui->gridLayout_6,m_gridBlockCtl.gridHead2);
}

void TestPaper::getUIItemData()
{
    m_itemDataMap.clear();
	int i = 1;
    for(auto it:m_gridItemCtl.itemCtlMap)
    {
        if(!it.lineEdit_Name->isVisible())
            return;

        if(it.lineEdit_Name->text().simplified().isEmpty() && !it.checkBox->isChecked())
            continue;

        TestPaper_Item itemData;
		itemData.serialNo = it.label->text().simplified().toInt();
        itemData.curve=it.cmbCurve->currentText().simplified();
        itemData.position=it.lineEdit_Position->text().simplified().toDouble();
		itemData.isNullArea = it.checkBox->isChecked();
		itemData.judgerule = it.combo_box_rule->currentData().toInt();
		itemData.strItemName = it.lineEdit_Name->text().simplified();
        if(itemData.isNullArea)
        {
            itemData.strItemName = "";
            itemData.position = 0;
        }
        m_itemDataMap.insert(i,itemData);
		i++;
    }
}

void TestPaper::getUIBlockAndItemData()
{
    m_blockAndItemDataMap.clear();
    auto &map=m_gridBlockCtl.blockCtlMap;
    for(auto &blockCtl:map)
    {
        if(!blockCtl.checkBox->isVisible())
            return;
        if(!blockCtl.checkBox->isChecked() && blockCtl.cmbItemCount->currentText().toInt()<=0)
            continue;

        BlockAndItemData blockItemData;
        BlockData bData;
        QVector<BlockItemData> bItemDatas{};
        bData.serialNo=blockCtl.label->text().toInt();
        bData.isNullArea=blockCtl.checkBox->isChecked();
        bData.itemCount=blockCtl.cmbItemCount->currentText().toInt();
        bData.startPos=blockCtl.distanceLineEdit->text().simplified().toDouble();
        bData.distance=blockCtl.distanceLineEdit->text().simplified().toDouble();
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
            BlockItemData itemData;
            itemData.serialNo=itemCtl.serialNo;
            itemData.curve=itemCtl.cmbCurveBox->currentData().toString();
            itemData.blockNo=itemCtl.blockNo;
            itemData.itemType=itemCtl.cmbItemType->currentData().toString();
            itemData.judgerule=itemCtl.cmbCurveBox->currentData().toInt();
            itemData.strItemName=itemCtl.itemNameEdit->text().simplified();
            bItemDatas.push_back(itemData);
        }
        blockItemData.itemDatas=bItemDatas;
        m_blockAndItemDataMap.insert(bData.serialNo,blockItemData);
    }
}

void TestPaper::initComboBox()
{    
    QVector<ComboxData>boxDatas;
    //boxDatas= //调用接口,选择厂家
    setComBoBoxData(ui->cmbCompany,boxDatas);
    connect(ui->cmbCompany,&QComboBox::currentTextChanged,this,&TestPaper::slotCmbCompanyTextChanged);

    boxDatas.clear();
    boxDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1809"),"1"));
    boxDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1810"),"2"));
    setComBoBoxData(ui->cmbPaperType,boxDatas);
    ui->cmbPaperType->setCurrentText(GlobalData::LoadLanguageInfo("K1809"));

    boxDatas.clear();
    boxDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1813"),"1"));
    boxDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("K1814"),"2"));
    setComBoBoxData(ui->cmbFunDirection,boxDatas);
    ui->cmbFunDirection->setCurrentText(GlobalData::LoadLanguageInfo("K1813"));

    boxDatas.clear();
    boxDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("0°"),"0"));
    boxDatas.push_back(ComboxData(GlobalData::LoadLanguageInfo("180°"),"180"));
    setComBoBoxData(ui->cmbRotate,boxDatas);
    ui->cmbRotate->setCurrentText(GlobalData::LoadLanguageInfo("0°"));
}

void TestPaper::setComBoBoxData(QComboBox *cmb, const QVector<ComboxData> &datas)
{
    if(cmb==nullptr)
        return;
    cmb->clear();
    cmb->addItem("","");
    for(auto data:datas)
        cmb->addItem(data.cmbText,data.cmbData);
}

void TestPaper::uiCtlSet(const int itemCount)
{
    int data{ui->cmbPaperType->currentData().toInt()};
    if(data==2)
    {
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
            ui->tbSegment->setItem(count,3,new QTableWidgetItem(QString::number(ctl.blockNo)));
            ui->tbSegment->setCellWidget(count,4,ctl.cmbRuleBox);
            ui->tbSegment->setCellWidget(count,5,ctl.cmbCurveBox);
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
    //QString currentData=ui->cmbCompany->currentData().toString();//厂家ID
    QVector<ComboxData>boxDatas;
    //boxDatas= //调用接口,实验流程
    setComBoBoxData(ui->cmbProcess,boxDatas);
}
