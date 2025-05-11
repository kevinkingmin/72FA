#include "RepeatSetDialog.h"
#include "ui_RepeatSetDialog.h"
#include <QMessageBox>
#include <QIntValidator>
#include "../Include/Model/sample/SampleModel.h"
#include "../Include/BLL/sample/SampleBLL.h"
#include "src/comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

RepeatSetDialog::RepeatSetDialog(QWidget *parent) :
    BaseDialog(parent),    
    ui(new Ui::RepeatSetDialog)
  ,_sampleNo("1")
  ,m_data(nullptr)
  ,_posAndCountMap{}
{
    ui->setupUi(this);
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
    initUi();
}

RepeatSetDialog::~RepeatSetDialog()
{
    delete ui;
}

bool RepeatSetDialog::setParas(const QString &sampleNo, dataStrc *data)
{
    if(data==nullptr)
        return false;
    _sampleNo=sampleNo;
    m_data=data;
    QMap<int,int> map;

    auto mp=data->paperCheckedCountMap;
    for(auto it=mp.begin();it!=mp.end();it++)
    {
        map.insert(it.key(),std::get<1>(it.value()));
    }
    _posAndCountMap.swap(map);
    return true;
}

void RepeatSetDialog::on_pushButtonClose_clicked()
{
    resetValue();
    this->hide();
}

void RepeatSetDialog::on_btnSave_clicked()
{
    this->hide();
}

void RepeatSetDialog::on_buttonCancel_clicked()
{
    resetValue();
    this->hide();
}

void RepeatSetDialog::initUi()
{
    _vModel=new RepeatSetModel(this);

    ui->ItemTable->setModel(_vModel);
    ui->ItemTable->setColumnHidden(0,true);
    ui->ItemTable->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->ItemTable->setSelectionMode(QTableView::SingleSelection);
    ui->ItemTable->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->ItemTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


	ui->label_2->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1552"));
	ui->lblSampleNo->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1049"));
	ui->btnSave->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1181"));
	ui->buttonCancel->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1134"));


}

void RepeatSetDialog::resetValue()
{
    auto &map=m_data->paperCheckedCountMap;
    for(auto it=map.begin();it!=map.end();it++)
    {
        auto &key=it.key();
        auto &v=it.value();
        auto pm=_posAndCountMap.find(key);
        if(pm==_posAndCountMap.end())
        {
            std::get<1>(v)=1;
            continue;
        }
        std::get<1>(v)=pm.value();
    }
}

void RepeatSetDialog::showEvent(QShowEvent *)
{
    centerDisplay();
    //ui->lblSampleNo->setText("样本编号:<b color='blue'>"+_sampleNo+"</b>");
	ui->lblSampleNo->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1163") +":<b color='blue'>" + _sampleNo + "</b>");
    _vModel->updatePage(m_data);
}
