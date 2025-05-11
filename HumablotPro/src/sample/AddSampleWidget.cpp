#include "AddSampleWidget.h"
#include "ui_AddSampleWidget.h"
#include <QDateTime>
#include <QMessageBox>
#include <QMenu>
#include <QPushButton>
#include <QSqlQuery>
#include "../Include/Analysis/analysis.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "model/AddSampleVModel.h"
#include "src/delegate/ComboxDelegate.h"
#include "subDialog/SetFirstPaperPosDialog.h"
#include "subDialog/RepeatSetDialog.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/sample/SampleModel.h"
#include "../Include/Model/sample/SampleTestModel.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/DAO/Analysis/AnalysisDao.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "../Include/Utilities/log.h"
#include "../Include/Utilities/async_task.h"
#include "BatchAddSampleWidgets.h"
#include "src/comm/Global.h"
#include <QThread>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QJsonDocument>
#include <QJsonArray>

AddSampleWidget::AddSampleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddSampleWidget)
  , _vModel(new AddSampleVModel(this))
  , _samplePaperIdMap{}
  , _setPaperPosDialog(new SetFirstPaperPosDialog(this))
  , _listTestData{}
  , _mFromLisByIntervalWidgets(new FromLisByIntervalWidgets(this))
  , _mManualIncubationWidgets(new ManualIncubationWidgets(this))
  , _sampleTestTpVect{}
  , _repeatSetDialog(new RepeatSetDialog(this))
  , m_batchAddSampleWidget(new BatchAddSampleWidgets(this))
  , m_instr(Instrument::instance())
  , m_scanBarcodeError("")
  , m_tcpClient(nullptr)
  , m_LISRepeatBarcord{}
  , m_LISERRDes("")
  , m_samplePos(-1)
  , m_progressDialog(nullptr)
  , m_isLISRequestDataFinish(true)
{
    ui->setupUi(this);
    initUI();
}
void AddSampleWidget::setProgressDialog(ProgressDialog *progressDialog){
    m_progressDialog = progressDialog;
}


AddSampleWidget::~AddSampleWidget()
{
    delete ui;
}

void AddSampleWidget::slotGetSampleBarCodeList(QByteArray resultData)
{
    int star_pos = ui->lineEdit_3->text().toInt();
    int end_pos = ui->lineEdit_4->text().toInt();
    QJsonDocument doc = QJsonDocument::fromJson(resultData);
    if(doc.isNull()||doc.isEmpty())
    {
		scanWorkState(true);
        return;
    }
    QJsonArray jsonArray =doc.array();    
    QString barcode("");
    for(int i=star_pos;i<end_pos+1;i++)
	{
        barcode=jsonArray.at(i-star_pos).toString();
        if(!m_tcpClient->m_connectedState)
            slotGetSampleBarCode(i,barcode);
        auto it(m_barCodePosMap.find(i));
        if(it==m_barCodePosMap.end())
        {
            eLog("scan data wrong,pos:{},barcode:{}",i,barcode.toStdString());
            continue;
        }		
        m_barCodePosMap.insert(i,barcode);
    }

    if(m_tcpClient==nullptr || !m_tcpClient->m_connectedState)
    {
		scanWorkState(true);
        return;
    }

    AsyncTask::post([this]()
    {
        QTime timer;
        for(auto it=m_barCodePosMap.begin();it!=m_barCodePosMap.end();it++)
        {	
            if (!m_tcpClient->m_connectedState)
			{
				emit sglSendRequestDataToLIS("finish");
				eLog("TCP break");
				break;
			}

            if(it.value().isEmpty())
            {
                eLog("data is empty,pos:{}",it.key());
                continue;
            }

            auto sendData(getHL7RequestData(it.value()));
            timer.start();
            while (!m_isLISRequestDataFinish)
            {
                if(timer.elapsed()>8000)
                {
                    eLog("request data failed,data:{}",sendData.toStdString());
                    break;
                }
                Sleep(100);
            }

            m_isLISRequestDataFinish=false;
            m_samplePos=it.key()-1;
            emit sglSendRequestDataToLIS(sendData);
        }

        m_isLISRequestDataFinish=true;
		Sleep(2000);
		timer.restart();
		while (m_progressDialog->isVisible())
		{
			if (timer.elapsed() > 6000)
			{
				emit sglSendRequestDataToLIS("finish");
				break;
			}
			Sleep(100);
		}
    });
}

void AddSampleWidget::slotRecivedLISData(const QString &data)
{
    if (m_samplePos < 0)
    {
        m_isLISRequestDataFinish=true;
        eLog("sample pos error,pos:{}", m_samplePos+1);
        return;
    }
    QString sample_id("");
    QVector<QString> paperIds;
    QStringList segments(data.split("\r"));
    for (int i = 0; i < segments.size(); i++)
    {
        QString need_sz = segments[i];
        QString modifiedString = need_sz.replace("\n", "");
        if (!modifiedString.startsWith("OBR"))
            continue;
        QStringList obrFields = modifiedString.split("|");
        if (obrFields.length() < 6)
        {
            eLog("LIS data wrong:{}", modifiedString.toStdString());
            continue;
        }
        paperIds.push_back(obrFields.at(5).simplified());
        if (sample_id.isEmpty())
            sample_id = obrFields.at(3).simplified();
    }
    if (m_LISRepeatBarcord.contains(sample_id))
            m_LISERRDes += tr("LIS服务器返回重复条码:%1,样本位置:%2\r\n").arg(sample_id).arg(m_samplePos+1);
    QDate currentDate = QDate::currentDate();
    
    QString create_time = currentDate.toString("yyyy-MM-dd");
    auto dao = AnalysisUIDao::instance();
    bool bResult = true;
    if (paperIds.isEmpty())
    {
        m_isLISRequestDataFinish=true;
        return;
    }
    QString sql_insert = "insert into tsample(sampleNo,Id,paperPos,paperId,stateFlag,createDay,samplePos,cupType)values";
    QString valueStr{ "" };
    for (auto paperId : paperIds)
        valueStr += QString("('%1','%1',1,%2,1,'%3',%4,1),").arg(sample_id).arg(paperId).arg(create_time).arg(m_samplePos);
    sql_insert = sql_insert + valueStr.left(valueStr.length() - 1);
    dao->UpdateRecord(&bResult, sql_insert);
    if (!bResult)
        eLog("insert into tsample failed,barcode:{},samplePos:{}", sample_id.toStdString(), m_samplePos);
    m_isLISRequestDataFinish=true;
    if(m_samplePos+1 >= m_barCodePosMap.lastKey())
    {
        ShowTestInfoFromDatabase();
		scanWorkState(true);
		if (!m_LISERRDes.isEmpty())
		{
			MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), m_LISERRDes, MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
			m_LISERRDes = "";
		}
    }
}

QString AddSampleWidget::getHL7RequestData(const QString &barCode)
{
    QString send_sz = "";
    send_sz += QString("%1MSH | ^ |||||  || OUL ^ R21 |  | P |||| AL | AL || ASCII |||%2").arg(QChar(0x0B)).arg(QChar(0x0D));
    send_sz += QString("PID | %1 ||||||  | 0 |||||||||||||||||||||||%2").arg(barCode).arg(QChar(0x0D));
    send_sz += QString("%1%2").arg(QChar(0x1C)).arg(QChar(0x0D));
    return send_sz;
}

void AddSampleWidget::slotSendRequestDataToLIS(const QString &requstData)
{
    if (m_tcpClient == nullptr || requstData=="finish")
    {
		scanWorkState(true);
		if (m_tcpClient == nullptr)
			eLog("m_tcpClient is null");
		else
			MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("从LIS服务器下载数据出错！"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		ShowTestInfoFromDatabase();
		return;
    }

    if (m_tcpClient->m_connectedState)
    {		
        m_tcpClient->sendData(requstData);
    }
}
void AddSampleWidget::scanWorkState(const bool isFinish)
{
	if (isFinish)
	{
		m_progressDialog->hide();
		ui->btnBCR->setEnabled(true);
		emit ChangeBtnSaveSignal(true);
		emit ChangeBtnNextSignal(true);
	}
	else
	{
		emit ChangeBtnSaveSignal(false);
		emit ChangeBtnNextSignal(false);
		ui->btnBCR->setEnabled(false);
	}
	
}
//得到查询条件，然后传进去查询函数中去。
void AddSampleWidget::slotGetQueryCondition(QString condition1,QString condition2)
{
    QString a = condition1 + "--" + condition2;
    MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), a, MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    //if (condition1 != "" && condition2!="")
        //Send_ID_ToList("Intervalrequest:" + condition1 + "|" + condition2);
}

void AddSampleWidget::showEvent(QShowEvent *e)
{
    Q_UNUSED(e);
    QMap<SampleStrc,QVector<int>>samplePaperIdMap;
    _samplePaperIdMap.swap(samplePaperIdMap);
}

void AddSampleWidget::on_btnBatchAdd_clicked()
{
    OnFromBatchAdd("");
}

void AddSampleWidget::initUI()
{
    QString sz = GlobalData::LoadLanguageInfo("K1042");
    ui->label_2->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1043");
    ui->label_5->setText(sz);

    sz = GlobalData::LoadLanguageInfo("K1044");
    ui->btnBatchAdd->setText(sz);

    sz = GlobalData::LoadLanguageInfo("K1045");
    ui->btnBCR->setText(sz);

    createSamplePos();

    connect(&_btnGroup,SIGNAL(buttonClicked(QAbstractButton *)),this,SLOT(slotBtnGroupTuble(QAbstractButton *)),Qt::UniqueConnection);
    ui->tvSampleSet->setModel(_vModel);

    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tvSampleSet->verticalHeader()->setDefaultSectionSize(165);
    ui->tvSampleSet->setColumnWidth(0,50);

    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->tvSampleSet->verticalHeader()->setDefaultSectionSize(65);
    ui->tvSampleSet->setColumnWidth(1,150);

    ui->tvSampleSet->horizontalHeader()->setHighlightSections(false);
    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Interactive);
    ui->tvSampleSet->verticalHeader()->setDefaultSectionSize(65);
    ui->tvSampleSet->setColumnWidth(2, 100);

    ui->tvSampleSet->setItemDelegateForColumn(2,new ComboxDelegate(this));
    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    ui->tvSampleSet->verticalHeader()->setDefaultSectionSize(65);
    ui->tvSampleSet->setColumnWidth(3, 80);

    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
    ui->tvSampleSet->verticalHeader()->setDefaultSectionSize(65);
    ui->tvSampleSet->setColumnWidth(4, 80);

    ui->tvSampleSet->horizontalHeader()->setHighlightSections(false);

    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Interactive);
    ui->tvSampleSet->verticalHeader()->setDefaultSectionSize(65);
    ui->tvSampleSet->setColumnWidth(4, 80);

    ui->tvSampleSet->setItemDelegateForColumn(4, new ComboxDelegate(this));
    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    ui->tvSampleSet->verticalHeader()->setDefaultSectionSize(65);
    ui->tvSampleSet->setColumnWidth(5, 60);

    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Fixed);
    ui->tvSampleSet->verticalHeader()->setDefaultSectionSize(65);
    ui->tvSampleSet->setColumnWidth(6, 60);

    auto count=_vModel->columnCount();

    for(int i=7;i<count-1;i++)
    {
        ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Fixed);
        ui->tvSampleSet->verticalHeader()->setDefaultSectionSize(65);
        ui->tvSampleSet->setColumnWidth(i,158);
    }
    ui->tvSampleSet->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->tvSampleSet->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tvSampleSet->setSelectionMode(QTableView::SingleSelection);
    ui->tvSampleSet->horizontalHeader()->setStretchLastSection(true);
    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
    ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    //ui->tvSampleSet->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->tvSampleSet->setColumnWidth(0, 70);
    ui->tvSampleSet->setColumnWidth(1, 220);
    ui->tvSampleSet->setColumnWidth(2, 160);
    ui->tvSampleSet->setColumnWidth(4, 80);
    ui->tvSampleSet->setColumnWidth(5, 80);
    ui->tvSampleSet->verticalHeader()->setDefaultSectionSize(40);
    //隔行变色
    ui->tvSampleSet->setAlternatingRowColors(true);

    _vModel->updateData();

    ShowTestInfoFromDatabase();

    connect(ui->tvSampleSet->selectionModel(),SIGNAL(selectionChanged(const QItemSelection &,const QItemSelection &)),this,SLOT(slotSelectionChanged(const QItemSelection &,const QItemSelection &)),Qt::UniqueConnection);
    auto tv = ui->tvSampleSet;
    auto model = _vModel;
    connect(_vModel,&AddSampleVModel::rowSeletedByChecked,this,[tv,model](int row,int column)
    {
        auto &vect=model->getVect();
        if(row>=vect.count())
            return ;
        tv->selectRow(row);
        auto &pm=vect[row];
        auto &map = pm.paperCheckedCountMap;
        auto it=map.find(column);
        int num = std::get<1>(it.value());
        if(it!=map.end())
        {
            if (std::get<0>(it.value()))
            {
                std::get<1>(it.value()) = num;//1;
            }
            else
            {
                std::get<1>(it.value()) = 1;
            }
        }
    });

    ui->tvSampleSet->setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(ui->checkBoxBCR, SIGNAL(stateChanged(int)), this, SLOT(OnShowBtnState()));
    connect(m_instr, SIGNAL(sglGetSampleBatchNo(int,QString)), this, SLOT(slotGetSampleBarCode(int,QString)));
    //从条件查询窗口得到数据
    connect(_mFromLisByIntervalWidgets, SIGNAL(sglQueryCondition(QString, QString)), this, SLOT(slotGetQueryCondition(QString, QString)));
    connect(m_batchAddSampleWidget, SIGNAL(sglFromBatchSample(QString)), this, SLOT(OnFromBatchAdd(QString)));
    ui->lineEdit_3->setText("1");
    ui->lineEdit_4->setText("72");

    const QString VSCROLLBAR_STYLE =
            "QScrollBar:vertical {margin: 13px 0px 13px 0px;background-color: rgb(255, 255, 255, 100); border: 0px; width: 36px;}\
            .QScrollBar::handle:vertical {background-color: purple; width: 36px; }\
            .QScrollBar::add-page:vertical {background-color: pink; }\
            .QScrollBar::sub-page:vertical {background-color: orange; }\
            .QScrollBar::sub-line:vertical {subcontrol-origin: margin; border: 1px solid red; height:13px}\
            .QScrollBar::up-arrow:vertical { subcontrol-origin: margin; background-color: blue; height:13px}\
            .QScrollBar::down-arrow:vertical { background-color: yellow; }\
            .QScrollBar::add-line:vertical {subcontrol-origin: margin; border: 1px solid green; height:13px;subcontrol-position:bottom;}";
            const QString VSCROLLBAR_STYLE1 =
            "QScrollBar:vertical {margin: 13px 0px 13px 0px;background-color: rgb(255, 255, 255, 100); border: 0px; width: 55px;}\
            .QScrollBar::handle:vertical {background-color: purple; width: 55px; }\
            .QScrollBar::add-page:vertical {background-color: pink; }\
            .QScrollBar::sub-page:vertical {background-color: orange; }\
            .QScrollBar::sub-line:vertical {subcontrol-origin: margin; border: 1px solid red; height:63px}\
            .QScrollBar::up-arrow:vertical { subcontrol-origin: margin; background-color: blue; height:63px}\
            .QScrollBar::down-arrow:vertical { background-color: yellow; }\
            .QScrollBar::add-line:vertical {subcontrol-origin: margin; border: 1px solid green; height:63px;subcontrol-position:bottom;}";
            const QString VSCROLLBAR_STYLE2 =
            "QScrollBar:vertical {margin: 13px 0px 13px 0px;background-color: rgb(255, 255, 255, 100); border: 0px; width: 55px;}\
            .QScrollBar::handle:vertical {background-color:  rgb(122, 122, 122, 122); width: 55px; }\
            .QScrollBar::add-page:vertical {background-color: white; }\
            .QScrollBar::sub-page:vertical {background-color: white; }\
            .QScrollBar::sub-line:vertical {subcontrol-origin: margin; border: 0px solid red; height:63px}\
            .QScrollBar::up-arrow:vertical { subcontrol-origin: margin; background-color: rgb(255, 255, 255, 255); height:63px}\
            .QScrollBar::down-arrow:vertical { background-color: rgb(255, 255, 255, 255); }\
            .QScrollBar::add-line:vertical {subcontrol-origin: margin; border: 0px solid green; height:63px;subcontrol-position:bottom;}";
            //ui->tvSampleSet->verticalHeader()->setStyleSheet(VSCROLLBAR_STYLE);
            const QString VSCROLLBAR_STYLE3=
            "QScrollBar:vertical {margin: 13px 0px 13px 0px;background-color: rgb(255, 255, 255, 100); border: 0px; width: 5px;}\
            .QScrollBar::handle:vertical {background-color:  rgb(122, 122, 122, 122); width: 5px; }\
            .QScrollBar::add-page:vertical {background-color: white; }\
            .QScrollBar::sub-page:vertical {background-color: white; }\
            .QScrollBar::sub-line:vertical {subcontrol-origin: margin; border: 0px solid red; height:63px}\
            .QScrollBar::up-arrow:vertical { subcontrol-origin: margin; background-color: rgb(255, 255, 255, 255); height:63px}\
            .QScrollBar::down-arrow:vertical { background-color: rgb(255, 255, 255, 255); }\
            .QScrollBar::add-line:vertical {subcontrol-origin: margin; border: 0px solid green; height:63px;subcontrol-position:bottom;}";
            ui->tvSampleSet->setStyleSheet(VSCROLLBAR_STYLE3);
    //去掉网格线
    //ui->tvSampleSet->setShowGrid(false);

    ui->tvSampleSet->setDragEnabled(true);
    ui->tvSampleSet->setSelectionMode(QAbstractItemView::SingleSelection); 	//拖动行列必选
    ui->tvSampleSet->setSelectionBehavior(QAbstractItemView::SelectRows);		//拖动行
    //ui->tvSampleSet->setSelectionBehavior(QAbstractItemView::SelectColumns);	//拖动列
    ui->tvSampleSet->setDefaultDropAction(Qt::MoveAction);
    ui->tvSampleSet->setDragDropMode(QAbstractItemView::InternalMove);

    QRegExp regExp;
    regExp.setPattern("[1-6]?[0-9]|[7][0-2]|[1-9]");
    QValidator * editName = new QRegExpValidator(regExp, ui->lineEdit);
    ui->lineEdit_3->setValidator(editName);
    ui->lineEdit_3->setMaxLength(3);
    ui->lineEdit_4->setValidator(editName);
    ui->lineEdit_4->setMaxLength(3);
    auto lineEdit = ui->lineEdit_3;
    connect(lineEdit, &QLineEdit::editingFinished, [lineEdit]() {
        QString sz = lineEdit->text();
        if (sz.isEmpty())
        {
            MyMessageBox::information(lineEdit, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1372"),MyMessageBox::Ok,"OK","");
            lineEdit->setText("1");
        }
    });
    lineEdit = ui->lineEdit_4;
    connect(lineEdit, &QLineEdit::editingFinished, [lineEdit]() {
        QString sz = lineEdit->text();
        if (sz.isEmpty())
        {
            MyMessageBox::information(nullptr, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1372"), MyMessageBox::Ok, "OK", "");
            lineEdit->setText("72");
        }
    });
    //connect(m_instr, &Instrument::sglScanSampleCodeResult, this, &AddSampleWidget::slotGetSampleBarCodeList);
    connect(m_instr, SIGNAL(sglScanSampleCodeResult(QByteArray)), this, SLOT(slotGetSampleBarCodeList(QByteArray)));
}

void AddSampleWidget::ShowTestInfoFromDatabase()
{
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    int company_id = dao->SelectSaveSetById(&bResult, 5).toInt();
    Global::g_company_id = company_id;
    QString createDay = QDate::currentDate().toString("yyyy-MM-dd");
    QString sql = "";
    QString sql_getSample = QString("select A.sampleNo from tsample A,t_testpaper B where A.paperId=B.ID and B.Company_ID='%2' and A.stateFlag=1 and A.createDay='%1' GROUP BY A.sampleNo").arg(createDay).arg(company_id);
    //QString sql_getSample = QString("select sampleNo from tsample where stateFlag=1 and createDay='%1' GROUP BY sampleNo").arg(createDay);
    auto selectSampleList = dao->SelectRecord(&bResult, sql_getSample);
    for (int i =0; i < PAPERCOUNT; i++)
    {
        _vModel->_vect[i].sampleNo = "";
    }
    int count = 0;
    while (selectSampleList.next())
    {
        QString sampleNo1 = selectSampleList.value("sampleNo").toString();
        QString sql_query = QString("select COUNT(*) as number, paperId,sampleNo,PatientName,samplePos from tsample where stateFlag=1 and createDay='%1' and sampleNo='%2' GROUP BY paperId").arg(createDay).arg(sampleNo1);
        auto countNumberQuery = dao->SelectRecord(&bResult, sql_query);
        //select COUNT(*) as number, paperId,sampleNo,PatientName,samplePos from tsample where stateFlag=1 and createDay='2022-06-13' and sampleNo='aaa' GROUP BY paperId
        while (countNumberQuery.next())
        {
            SampleTestModel stm;
            int number = countNumberQuery.value("number").toInt();
            int samplePos = countNumberQuery.value("samplePos").toInt();
            int paperId = countNumberQuery.value("paperId").toInt();
            QString sampleNo = countNumberQuery.value("sampleNo").toString();

            _vModel->_vect[samplePos].sampleNo = sampleNo;

            auto map = _vModel->_vect[samplePos].paperCheckedCountMap;//it.paperCheckedCountMap;
            int paper_id_new = GetPaperId1(paperId);
            std::tuple tp(true, number);
            _vModel->_vect[samplePos].paperCheckedCountMap.insert(paper_id_new, tp);
        }
        count++;
    }
    //InsertIntoRecord(insertVect_list);
    setSamplePaperIdMap();
    setBtnCheckStyle();
    if (count > 0)
        emit ChangeBtnNextSignal(true);
    else
        emit ChangeBtnNextSignal(false);
}

void AddSampleWidget::slotGetSampleBarCode(int pos,QString barCode)
{
    mScanBarCodePos++;
    if (m_barCodePosMap.count()> 0)
    {
        m_barCodePosMap[pos] = barCode;
        _vModel->_vect[pos - 1].sampleNo = barCode;
    }

    if (mScanBarCodePos == m_barCodePosMap.size())
		scanWorkState(true);

    setSamplePaperIdMap();
    setBtnCheckStyle();
    ui->tvSampleSet->show();
    ui->tvSampleSet->setMouseTracking(true);
    ui->tvSampleSet->update();
}

void AddSampleWidget::on_btnBCR_clicked()
{
    m_scanBarcodeError = "";
    if (!m_tcpClient->m_connectedState)
    {
        bool ret= GlobalData::reconnect();
        if (ret && !m_tcpClient->m_connectedState)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1736"), MyMessageBox::Ok, "OK", "");
            return;
        }
    }
    OnShowBtnState();
}

void AddSampleWidget::OnShowBtnState()
{
	m_samplePos = -1;
	m_LISERRDes = "";
    int star_pos = ui->lineEdit_3->text().toInt();
    int end_pos = ui->lineEdit_4->text().toInt();
    if (star_pos > end_pos)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1373"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    if (star_pos > 72 || end_pos > 72)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1374"),MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    if (star_pos < 1 || end_pos < 1)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1375"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    m_barCodePosMap.clear();
    mScanBarCodePos = 0;
	m_samplePos = -1;
    for (int ipos = star_pos; ipos < end_pos + 1; ipos++)
    {
        m_barCodePosMap.insert(ipos, "");
    }

    if (m_barCodePosMap.count()>0)
		scanWorkState(false);
    m_instr->scanSampleCode(QString::number(star_pos),QString::number(end_pos));
    m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1712"));
    m_progressDialog->exec();
}

void AddSampleWidget::slotCheckBoxSeleted()
{

}

void AddSampleWidget::createSamplePos()
{
    int row=0;
    int col=0;
    QString text="";
    for (int i = 1; i <= PAPERCOUNT; i++)
    {
        text=QString::number(i);
        auto btn=new QPushButton(this);
        btn->setText(text);
        btn->setObjectName(text);
        btn->setCheckable(true);
        _btnGroup.addButton(btn);
        row=i%2;
        col=(i-1)/2;
        ui->gdLSamplePos->setProperty("lblStyle", "QTableView");

        if(i<=36)
            ui->gdLSamplePos->addWidget(btn,row,col);
        else
            ui->gdLSamplePos->addWidget(btn,row,col+1);

        if(i==36)
        {
            auto lbl=new QLabel(this);
            lbl->setMinimumWidth(30);
            lbl->setMaximumWidth(30);
            lbl->setProperty("lblStyle","SeparatorStyle");
            ui->gdLSamplePos->addWidget(lbl,0,col+1,2,1);
        }
        btn->setStyleSheet("border-image: url((:/images/menu/tube16_d.png)");
    }
}

void AddSampleWidget::setBtnCheckStyle()
{
    auto keys=getPosList();
    for(auto btn:_btnGroup.buttons())
    {
        style()->unpolish(btn);
        auto index=btn->text().toInt();
        if(keys.contains(index))
            btn->setProperty("btnStyle","btnPosCheckedStyle");
        else
            btn->setProperty("btnStyle","btnPosStyle");
        style()->polish(btn);
    }
}

QList<int> AddSampleWidget::getPosList()
{
    QList<int>list{};
    auto keys=_samplePaperIdMap.keys();
    for(auto k:keys)
        list.push_back(k.samplePos);
    return list;
}
void AddSampleWidget::DeleteAllSample()
{
    int ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1376"),MyMessageBox::Yes|MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if (ret == 16384)
    {
        return;
    }

    QList<QModelIndex> list = ui->tvSampleSet->selectionModel()->selectedIndexes();
    int rows = ui->tvSampleSet->selectionModel()->Rows;
    for (int i = 0; i <rows; i++)
    {
        DeleteSampleList(i);
    }
}
void AddSampleWidget::DeleteSample()
{
    int ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1377"), MyMessageBox::Yes| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if (ret != 16384)
    {
        return;
    }

    QList<QModelIndex> list = ui->tvSampleSet->selectionModel()->selectedIndexes();
    if (!ui->tvSampleSet->selectionModel()->selectedIndexes().isEmpty())
    {
        int index = list[0].data().toInt();
        auto selected = (ui->tvSampleSet->currentIndex().row()+1);
        if (selected == index)
        {
            //删除
            //
            DeleteSampleList(index - 1);
        }
    }
    setSamplePaperIdMap();
    setBtnCheckStyle();
    ShowTestInfoFromDatabase();
}

void AddSampleWidget::SaveSampleListToDataBase()
{
    SaveSample();
}

#define WM_MYMESSAGE WM_USER + 1 
#define   WM_MYMSG WM_USER + 2001 //WM_USER为系统定义好的值为0x0400

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

const QString c_strTitle = "LisTool";

void AddSampleWidget::Incubation(int witch,int incubation_time)
{
    //m_instr->rockBedWorking(witch);
    _mManualIncubationWidgets->exec();
}

void AddSampleWidget::FromLis()
{
    auto vect = _vModel->getVect();
    auto head = _vModel->getHeadVect();
    QMap<SampleStrc, QVector<int>> tempMap;
    _samplePaperIdMap.swap(tempMap);
    int i = 0;
    QString tip = "";
    QString id = "";
    QString id1 = "";
    for (auto it : vect)
    {
        if (_vModel->_vect[i].sampleNo != "")
        {
            QString sampleNo = _vModel->_vect[i].sampleNo;
            id1 = sampleNo;
            id += sampleNo+"|"+QString::number(i)+",";
            //int paperId = _vModel->_vect[i].;
            QString PatientName = _vModel->_vect[i].patientName;
            int paper_id = 0;
            auto map = _vModel->_vect[i].paperCheckedCountMap;
            QMap<int, std::tuple<bool, int>>paperCheckedCountMap1;
            int ii = 0;
            for (auto m = map.begin(); m != map.end(); m++)
            {
                int paper_id_tmp = m.key();
                auto isChecked = std::get<0>(m.value());
                int number = std::get<1>(m.value());
                for (int jj = 0; jj < number; jj++)
                {
                    std::tuple tp(false, 1);
                    paperCheckedCountMap1.insert(paper_id_tmp, tp);
                    paper_id = GetPaperId(paper_id_tmp);
                    if (isChecked)
                    {
                        ii++;
                    }
                }
            }
            _vModel->_vect[i].paperCheckedCountMap = paperCheckedCountMap1;
        }
        i++;
    }
    if (id != "")
    {

        //每次扫码前先删除掉要请求的数据
        bool bResult;
        auto dao1 = AnalysisUIDao::instance();
        QString sql = "";
        sql += QString("delete from request_lis_data");
        dao1->UpdateRecord(&bResult, sql);
    }
}

void AddSampleWidget::OnFromBatchAdd(QString content)
{
    //SaveSample();
    _vModel->updateData();
    ShowTestInfoFromDatabase();
    FromTestDataByBatchAdd("");
}


void AddSampleWidget::FromTestDataByBatchAdd(QString condition)
{
    m_batchAddSampleWidget->GetTestPaperInfo();
    m_batchAddSampleWidget->show();
}

void AddSampleWidget::FromLisByCondition(QString condition1)
{
    //_repeatSetDialog->setParas(_vModel->index(index, 1).data().toString(), &it);
    //_mFromLisByIntervalWidgets->show();
    _mFromLisByIntervalWidgets->exec();
}

int AddSampleWidget::GetPaperId1(int ii)
{
    int id = 0;
    auto head = _vModel->getHeadVect();
    for (auto it : head)
    {
        if (ii == it.paperId && it.id>6)
        {
            id = it.id;
            break;
        }
    }
    return id;
}


int AddSampleWidget::GetPaperId(int ii)
{
    int paper_id = 0;
    auto head = _vModel->getHeadVect();
    for (auto it : head)
    {
        if (ii == it.id)
        {
            paper_id = it.paperId;
            break;
        }
    }
    return paper_id;
}

void AddSampleWidget::SaveSample()
{
    if (!judgeTipInfo())
    {
        return;
    }

    QVector<QString> sql_list;
    QVector<QString> Id_list;
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    quint64 id = dao->getMaxId();
    QString createDay = QDate::currentDate().toString("yyyy-MM-dd");
    //id += 1;
    auto vect = _vModel->getVect();
    auto head = _vModel->getHeadVect();
    QMap<SampleStrc, QVector<int>> tempMap;
    _samplePaperIdMap.swap(tempMap);
    int i = 0;
    QString tip = "";
    auto dao1 = AnalysisDao::instance();
    int test_batch_max = dao1->GetTestBacthMax();
    test_batch_max = 1;

    for (auto it : vect)
    {
        if (_vModel->_vect[i].sampleNo !="")
        {
            QString sampleNo = _vModel->_vect[i].sampleNo;
            int samplePos = _vModel->_vect[i].samplePos-1;
            //int paperId = _vModel->_vect[i].;
            QString PatientName = _vModel->_vect[i].patientName;
            int SexID = _vModel->_vect[i].sexID;
            int Age = _vModel->_vect[i].age;
            int paper_id = 0;
            auto map = _vModel->_vect[i].paperCheckedCountMap;
            int ii = 0;
            //QString sql_delete = QString("delete from tsample where sampleNo='%1' and createDay='%2' and samplePos=%3 and stateFlag=1").arg(sampleNo).arg(createDay).arg(samplePos);
            QString sql_delete = QString("delete from tsample where  createDay='%1' and samplePos=%2 and stateFlag=1").arg(createDay).arg(samplePos);
            dao->SelectRecord(&bResult, sql_delete);
            for (auto m = map.begin(); m != map.end(); m++)
            {
                int paper_id_tmp = m.key();
                auto isChecked = std::get<0>(m.value());
                int number = std::get<1>(m.value());
                for (int jj = 0; jj < number; jj++)
                {
                    paper_id = GetPaperId(paper_id_tmp);
                    if (isChecked)
                    {
                        QString sql = "";
                        QString sql_query = QString("select * from tsample where sampleNo='%1' and createDay='%2' and samplePos=%3  and stateFlag=1").arg(sampleNo).arg(createDay).arg(samplePos);
                        auto countNumberQuery = dao->SelectRecord(&bResult, sql_query);
                        int number = 0;
                        while (countNumberQuery.next())
                        {
                            QString id = countNumberQuery.value("Id").toString();
                            Id_list.append(id);
                            number++;
                        }
                        if (number > 0)
                        {
                            QString id11 = Id_list.at(ii);
                            //生成修改sql
                            sql = QString("update tsample set samplePos=%1,paperId=%2,PatientName='%3',SexID=%4,Age=%5,stateFlag=1,paperPos=0 where Id=%6 and samplePos=%1").arg(samplePos).arg(paper_id).arg(PatientName).arg(SexID).arg(Age).arg(id11);
                            sql_list.append(sql);
                        }
                        else
                        {
                            id += 1;
                            //生成添加sql
                            sql = QString("insert tsample(sampleNo,samplePos,paperId,PatientName,SexID,Age,id,stateFlag,paperPos,createDay,test_batch)VALUES('%1',%2,%3,'%4',%5,%6,%7,1,0,'%8',%9)").arg(sampleNo).arg(samplePos).arg(paper_id).arg(PatientName).arg(SexID).arg(Age).arg(id).arg(createDay).arg(test_batch_max);
                            sql_list.append(sql);
                        }
                        ii++;
                    }
                }
            }
            for (int iv = 0; iv < sql_list.size(); ++iv)
            {
                QString sql = "";
                sql = sql_list.at(iv);
                QString sql_query = "";
                dao->addRecord(&bResult, sql);
                if (bResult)
                {
                    tip += GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1378");//"保存成功";
                }
            }
            sql_list.clear();
        }
        i++;
    }
    if (tip != "")
    {
        emit ChangeBtnNextSignal(true);
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1378"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
    }
}

void AddSampleWidget::DeleteSampleList(int index)
{
    //int i = ui->tvSampleSet.//->currentRow();
    ui->tvSampleSet->model()->removeRow(index);//->removeRow(index);
    //->item(i, 2)->text().toUInt();
    QString sampleNo1 = ui->tvSampleSet->model()->index(index, 1).data().toString();

    if (sampleNo1 == "")
    {
        return;
    }
    auto dao = AnalysisUIDao::instance();
    QString sampleNo = QString("%1").arg(sampleNo1);
    bool bResult = true;
    QString sql = "";
    sql = QString("delete from tsample where sampleNo='%0'").arg(sampleNo);
    dao->deleteRecord(&bResult, sql);
    _vModel->updateData();

    setSamplePaperIdMap();
    setBtnCheckStyle();
    ShowTestInfoFromDatabase();
}

void AddSampleWidget::InsertIntoRecord(QVector<SampleTestModel> lis_test)
{
    //auto vect = _vModel->getVect();
    auto head = _vModel->getHeadVect();
    QMap<SampleStrc, QVector<int>> tempMap;
    _samplePaperIdMap.swap(tempMap);
    int i = 0;
    for (auto it : lis_test)
    {
        if (i < 10)
        {
            SampleStrc m;
            QVector<int>paperIds;
            QString sampleNo = "";
            sampleNo = it.getTestId();//QString("10000%1").arg(i);
            _vModel->_vect[i].sampleNo = sampleNo;
            _vModel->_vect[i].patientName = it.getPatientName();// lis_test[i]

            auto map = _vModel->_vect[i].paperCheckedCountMap;//it.paperCheckedCountMap;
            for (auto m = map.begin(); m != map.end(); m++)
            {
                bool ischecked = std::get<0>(m.value());
                auto count = std::get<1>(m.value());
                if (!ischecked)
                    continue;
                if (head.count() <= m.key())
                {

                }
                for (int i = 0; i < count; i++)
                {
                    paperIds.push_back(head[m.key()].paperId);
                }
            }
            _samplePaperIdMap.insert(m, paperIds);
        }
        i++;
    }
}

bool AddSampleWidget::judgeTipInfo()
{
    bool return_Value = true;
    if (!setSamplePaperIdMap())
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1379"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        //return false;
        return_Value = false;
    }
    if (_samplePaperIdMap.isEmpty())
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1380"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        //return false;
        return_Value = false;
    }
    QString lackInfo = "";
    QMap<SampleStrc, QVector<int>>testMap;

    int i_n = 1;
    for (auto it = _samplePaperIdMap.begin(); it != _samplePaperIdMap.end(); it++)
    {
        if (!it.value().isEmpty())
        {
            testMap.insert(it.key(), it.value());
        }
        else
        {
            lackInfo += GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1382") + QString::number(it.key().samplePos) + "" + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1049") + it.key().sampleNo +"    ";
            if (i_n % 2==0)
            {
                lackInfo += "\n";
            }
        }
        i_n++;
    }

    if (!lackInfo.isEmpty())
    {
        auto ret = MyMessageBox::question(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1260"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1381")+"\n" + lackInfo, MyMessageBox::Ok|MyMessageBox::Cancel, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
        if (ret == MyMessageBox::Cancel)
        {
            return_Value = false;
        }
        //return false;
    }
    if (testMap.isEmpty())
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1384"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return false;
    }
    int totalTest = 0;
    for (auto it : testMap)
    {
        totalTest += it.count();
    }
    if (totalTest > PAPERCOUNT)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1385") + QString::number(totalTest)+ GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1386") + QString::number(PAPERCOUNT), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        //return false;
        return_Value = false;
    }
    return return_Value;
}

bool AddSampleWidget::setSamplePaperIdMap()
{
    auto vect = _vModel->getVect();
    auto head= _vModel->getHeadVect();
    QMap<SampleStrc,QVector<int>> tempMap;
    _samplePaperIdMap.swap(tempMap);
    for(auto it:vect)
    {
        SampleStrc m;
        QVector<int>paperIds;
        if(it.sampleNo.simplified().isEmpty())
            continue;
        m.samplePos=it.samplePos;
        m.sampleNo=it.sampleNo;
        m.cupType=it.cupType;
        m.articleNo = it.articleNo;
        m.patientName = it.patientName;
        m.sexID = it.sexID;
        m.age = it.age;
        auto map=it.paperCheckedCountMap;
        for(auto t=map.begin();t!=map.end();t++)
        {
            bool ischecked=std::get<0>(t.value());
            auto count=std::get<1>(t.value());
            if(!ischecked)
                continue;
            if(head.count() <= t.key())
            {
                MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1387"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
                return false;
            }
            for(int i=0;i<count;i++)
            {
                paperIds.push_back(head[t.key()].paperId);
            }
        }
        _samplePaperIdMap.insert(m,paperIds);
    }
    return true;
}

void AddSampleWidget::slotBtnGroupTuble(QAbstractButton *btn)
{
    auto index = btn->text().toInt()-1;
    //index=btn->text().toInt()-4;
    btn->setChecked(true);
    ui->tvSampleSet->selectRow(index);
}

void AddSampleWidget::slotSelectionChanged(const QItemSelection &, const QItemSelection &)
{
    if(!setSamplePaperIdMap())
        return;
    setBtnCheckStyle();
    auto index=ui->tvSampleSet->currentIndex().row();
    if(index<0)
        return;
    _btnGroup.buttons()[index]->setChecked(true);
}

void AddSampleWidget::cancelAction()
{

    QMap<SampleStrc,QVector<int>> tempMap;
    _samplePaperIdMap.swap(tempMap);
    _vModel->updateData();
    for(auto btn:_btnGroup.buttons())
    {
        if (btn==nullptr)
            return;
        style()->unpolish(btn);
        btn->setChecked(false);
        btn->setProperty("btnStyle","btnPosStyle");
        style()->polish(btn);
    }

}

bool AddSampleWidget::nextAction()
{
    if(!setSamplePaperIdMap())
    {
        MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1379"),MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return false;
    }
    if(_samplePaperIdMap.isEmpty())
    {
        MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1380"),MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return false;
    }
    int i_n = 1;
    //判断 选项目，但是未填写样本编号，判断未选项目，但是填写样本编号
    QString lackInfo22 = "";
    for (int i = 0; i < PAPERCOUNT; i++)
    {
        QString sampleNo = _vModel->_vect[i].sampleNo;
        QMap<int, std::tuple<bool, int>>paperCheckedCountMap = _vModel->_vect[i].paperCheckedCountMap;
        QMap<int, std::tuple<bool, int>>::iterator itor;
        bool selected_project_flage = false;
        for (itor = paperCheckedCountMap.begin(); itor != paperCheckedCountMap.end(); ++itor)
        {
            if (std::get<0>(itor.value()))
            {
                selected_project_flage = true;
            }
        }

        if (sampleNo == "" && selected_project_flage)
        {
            //K1382
            lackInfo22 += GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1382") + QString::number(i + 1) + "  ";
            if (i_n % 3 == 0)
            {
                lackInfo22 += "\n";

            }
            i_n++;
            //QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("存在样本编号未填写"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
        }
    }

    if (lackInfo22 != "")
    {
        //
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1630")+ "\n\r" +lackInfo22, MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return false;
    }

    QString lackInfo="";
    QMap<SampleStrc,QVector<int>>testMap;

    i_n = 1;
    for(auto it=_samplePaperIdMap.begin();it!=_samplePaperIdMap.end();it++)
    {
        if (!it.value().isEmpty())
        {
            testMap.insert(it.key(), it.value());
        }
        else
        {
            lackInfo+= GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1382") +QString::number(it.key().samplePos)+" "+" "+ GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1049") +" :  "+it.key().sampleNo+"    ";
            if (i_n % 3 == 0)
            {
                lackInfo += "\n";
            }
        }
        i_n++;
    }


    if(!lackInfo.isEmpty())
    {
        auto ret= MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1260"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1381")+"\n"+lackInfo, MyMessageBox::Cancel| MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"),GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
        if(ret== MyMessageBox::Ok)
            return false;
    }
    if(testMap.isEmpty())
    {
        MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1384"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");


        return false;
    }
    int totalTest=0;
    for (auto it : testMap)
    {
        totalTest += it.count();
    }
    if(totalTest>PAPERCOUNT)
    {
        MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"),GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1385") +QString::number(totalTest)+ GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1386") +QString::number(PAPERCOUNT), MyMessageBox::Ok,"OK","");
        return false;
    }
    setBtnCheckStyle();
    _setPaperPosDialog->setPaperCount(totalTest,PAPERCOUNT);
    _setPaperPosDialog->exec();
    if (_setPaperPosDialog->getIsCloseBtn())
    {
        return false;
    }
    auto startPos=_setPaperPosDialog->getStartPos();
    if(startPos<=0)
    {
        MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1389"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return false;
    }
    QVector<ptrTest>listTestData;
    createSampleTestData(testMap,listTestData);
    sortTestData(listTestData);
    setTestDataSlotPos(startPos,totalTest);
    return true;
}

// 给测试项目赋值的地方
void AddSampleWidget::createSampleTestData(QMap<SampleStrc,QVector<int>>testMap,QVector<ptrTest> &listTestData)
{
    QVector<std::tuple<ptrSample,QVector<ptrTest>>> tpVect;
    _sampleTestTpVect.swap(tpVect);
    QString tempSampleId="";
    QString solution_name = ui->lineEdit->text();
    QString author = GlobalData::getLoginName1();//ui->lineEdit_2->text();

    QDateTime nowTime = QDateTime::currentDateTime();
    QString strTestDateTime = nowTime.toString("yyyyMMddhhmmss");
    int testIndex = 1;
    for(auto it=testMap.begin();it!=testMap.end();it++)
    {
        tempSampleId = QString("%1").arg(testIndex);
        //tempSampleId++;
        QVector<ptrTest>testVect;
        ptrSample psample(new SampleModel);
        auto k=it.key();
        auto tvect=it.value();
        psample->setId(tempSampleId);
        int samplePos = k.samplePos;
        psample->setSamplePos(samplePos);
        QString sample_pos = "";
        sample_pos.sprintf("%d", k.samplePos);
        psample->setSampleNo(k.sampleNo);
        psample->setCupType(k.cupType);
        psample->setArticleNo(k.articleNo);
        //psample->setPaperPos(2);
        for(auto pid:tvect)
        {
            QString testId = "";
            testId.sprintf("%d", testIndex);
            testId = strTestDateTime + testId;
            ptrTest test(new SampleTestModel);
            QString sampleNo = k.sampleNo;//.toInt();//样本的位置
            test->setSampleId(sampleNo);
            test->setSamplePos(k.samplePos);
            //test->setSampleId(tempSampleId);
            test->setPaperId(pid);
            test->setRemark(k.sampleNo);
            test->setSolutionName(solution_name);
            test->setManageName(author);
            test->setCupType(k.cupType);
            test->setArticleNo(k.articleNo);
            test->setTestId(testId);
            testVect.push_back(test);
            listTestData.push_back(test);
            testIndex++;
        }
        std::tuple<ptrSample,QVector<ptrTest>>tp(psample,testVect);
        _sampleTestTpVect.push_back(tp);
    }
}

void AddSampleWidget::sortTestData(QVector<ptrTest> &listTestData)
{
    _listTestData.swap(listTestData);
//    QVector<ptrTest>tempList;
//    _listTestData.swap(tempList);
//    if(listTestData.isEmpty())
//        return;
//    _listTestData.push_back(listTestData[0]);
//    listTestData.remove(0);
//NEXT:
//    auto last=_listTestData.last();
//    for(int i=0;i<listTestData.count();i++)
//    {
//        if(listTestData.count()==1)
//        {
//            _listTestData.push_back(listTestData[0]);
//            break;
//        }

//        if(i==listTestData.count()-1)
//        {
//            if(last->getPaperId()==listTestData[i]->getPaperId())
//            {
//                _listTestData.push_back(listTestData[i]);
//                listTestData.remove(i);
//            }
//            else
//            {
//                _listTestData.push_back(listTestData[0]);
//                listTestData.remove(0);
//            }
//            goto NEXT;
//        }

//        if(last->getPaperId()==listTestData[i]->getPaperId())
//        {
//            _listTestData.push_back(listTestData[i]);
//            listTestData.remove(i);
//            goto NEXT;
//        }
//    }
}

void AddSampleWidget::setTestDataSlotPos(int startPos, int totalTest)
{
    for(int i=0;i<PAPERCOUNT;i++)
    {
        if (i >= totalTest)
            break;
        auto &pm = _listTestData[i];
        if (startPos + i <= PAPERCOUNT)
            pm->setSlotPos(startPos + i);
        else
            pm->setSlotPos(startPos + i - PAPERCOUNT);
    }
}

void AddSampleWidget::setTcpClient(TcpClient *tcpClient)
{
    m_tcpClient = tcpClient;
    disconnect(m_tcpClient, &TcpClient::dataReceived, this, &AddSampleWidget::slotRecivedLISData);
    disconnect(this, &AddSampleWidget::sglSendRequestDataToLIS, this, &AddSampleWidget::slotSendRequestDataToLIS);
    connect(m_tcpClient, &TcpClient::dataReceived, this, &AddSampleWidget::slotRecivedLISData,Qt::UniqueConnection);
    connect(this, &AddSampleWidget::sglSendRequestDataToLIS, this, &AddSampleWidget::slotSendRequestDataToLIS,Qt::QueuedConnection);
}

QVector<std::tuple<AddSampleWidget::ptrSample, QVector<AddSampleWidget::ptrTest>>>AddSampleWidget::getSampleTestTpVect() const
{
    return _sampleTestTpVect;
}

void AddSampleWidget::createRepeatTest()
{
    auto index=ui->tvSampleSet->currentIndex().row();
    if(index<0)
    {
        MyMessageBox::information(this,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1390"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
        return;
    }
    auto &vect = _vModel->getVect();
    auto samplePos = _vModel->index(index,0).data().toInt();
    QVector<int> paperColumnNos;
    for(auto &it:vect)
    {
        if(it.samplePos==samplePos)
        {
            //it.paperCheckedCountMap = _vModel->getVect()[samplePos].paperCheckedCountMap;
            auto map = it.paperCheckedCountMap;
            for(auto m=map.begin();m!=map.end();m++)
            {
                auto isChecked=std::get<0>(m.value());
                if(isChecked)
                    paperColumnNos.push_back(m.key());
            }
            _repeatSetDialog->setParas(_vModel->index(index,1).data().toString(),&it);
            _repeatSetDialog->exec();
            break;
        }
    }
}

QVector<AddSampleWidget::ptrTest> AddSampleWidget::getListTestData() const
{
    return _listTestData;
}
