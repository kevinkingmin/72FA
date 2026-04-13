#include "SystemSet.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include <QListView>
#include <QProcess>
#include "src/main/subDialog/MyMessageBox.h"
#include "../comm/GlobalData.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/Model/baseSet/CompanyModel.h"
#include "../Include/DAO/baseSet/CompanyDao.h"
#include "../Include/Model/baseSet/ProcessModel.h"
#include "../Include/DAO/baseSet/ProcessDao.h"
#include "../Include/Model/baseSet/TestPaperModel.h"
#include "../Include/DAO/baseSet/TestPaperDao.h"
#include "../Include/Model/baseSet/CompanyModel.h"
#include "../Include/DAO/baseSet/CompanyDao.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "../Include/DAO/baseSet/SystemSetDao.h"

SystemSet::SystemSet(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setAttribute(Qt::WA_ShowModal, true);
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    QRegExpValidator* validator = new QRegExpValidator(QRegExp("^(?:[5-9]|[1-9][0-9]|[1-2][0-3][0-9]|240)$"), ui.lineEdit_week_finish_time);
    ui.lineEdit_week_finish_time->setValidator(validator);
    ui.lineEdit_RootPathReport->setEnabled(true);
    ui.lineEdit_RootPathPicture->setEnabled(true);
    QString strControlThreshold = dao->SelectControlThreshold(&bResult);
    QString strCutOffThreshold = dao->SelectCutOffThreshold(&bResult);
    QString strRootPathPicture = dao->SelectTestPicturesRootPath(&bResult);
    ui.lineEdit_RootPathPicture->setText(strRootPathPicture);
    QString strRootPathReport = dao->SelectTestReportsRootPath(&bResult);
    ui.lineEdit_RootPathReport->setText(strRootPathReport);

    //样本针取样探测
    ui.comboBox_aspirate_sample->clear();
    ui.comboBox_aspirate_sample->addItem(GlobalData::LoadLanguageInfo("K1698"));
    ui.comboBox_aspirate_sample->addItem(GlobalData::LoadLanguageInfo("K1699"));

    //样本针吐样液位探测
    ui.comboBox_vomit->clear();
    ui.comboBox_vomit->addItem(GlobalData::LoadLanguageInfo("K1698"));
    ui.comboBox_vomit->addItem(GlobalData::LoadLanguageInfo("K1699"));

    //蜂鸣器开启
    ui.comboBox_beep_enable->clear();
    ui.comboBox_beep_enable->addItem(GlobalData::LoadLanguageInfo("K1701"));
    ui.comboBox_beep_enable->addItem(GlobalData::LoadLanguageInfo("K1700"));

    // 废液桶 使能 1、去使能为 0”
    ui.comboBox_waste_liquid_tank_enable->clear();
    ui.comboBox_waste_liquid_tank_enable->addItem(GlobalData::LoadLanguageInfo("K1701"));
    ui.comboBox_waste_liquid_tank_enable->addItem(GlobalData::LoadLanguageInfo("K1700"));

    ui.comboBox_waste_liquid_tank_enable_2->clear();
    ui.comboBox_waste_liquid_tank_enable_2->addItem(GlobalData::LoadLanguageInfo("K1701"));
    ui.comboBox_waste_liquid_tank_enable_2->addItem(GlobalData::LoadLanguageInfo("K1700"));

    // 设置公司
    CompanyDao* companyDao = CompanyDao::instance();
    QVector<CompanyModel> companyModels = companyDao->getAllRows();
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1290"), MyMessageBox::Ok,"OK","");
        return;
    }
    for (CompanyModel& model : companyModels)
    {
        QString itemName = model.getName();
        ui.comboBox_CompanyList->addItem(itemName, QString::number(model.getId()));
    }
    ui.comboBox_CompanyList->setView(new  QListView(this));// 设置样式
    ui.comboBox_CompanyList->setStyleSheet(QString("QComboBox QAbstractItemView {background: rgb(192,192,192);min-height: 40px;}"));
    ui.comboBox_CompanyList->setStyleSheet(QString("QComboBox QAbstractItemView::item {background: rgb(192,192,192);min-height: 40px;}"));


    if (ui.comboBox_CompanyList->count() > 0)
    {
        //当前应用膜条公司名字
        QString PaperInfo = dao->SelectPaperInfo(&bResult);
        //选中单元格 第一行：
        ui.comboBox_CompanyList->setCurrentText(PaperInfo);
        onCompanyComboBoxChanged(PaperInfo);
    }
    connect(ui.comboBox_CompanyList,&QComboBox::currentTextChanged, this, &SystemSet::onCompanyComboBoxChanged);    // 连接切换事件

    // 设置流程样式
    ui.comboBox_run_sequence->setView(new QListView(this));
    ui.comboBox_run_sequence->setStyleSheet(QString("QComboBox QAbstractItemView {background: rgb(192,192,192); min-height: 40px;}"));
    ui.comboBox_run_sequence->setStyleSheet(QString("QComboBox QAbstractItemView::item {background: rgb(192,192,192); min-height: 40px;}"));

    //取出所有的参数
    QString sql = "select * from tsystemset";
    auto all_system_set_para = dao->SelectAll_tsystemset(&bResult, sql);
    while (all_system_set_para.next())
    {
        int pkid = all_system_set_para.value("id").toInt();
        if (pkid == 20005) // 设置语言
        {
            int saveSet = all_system_set_para.value("saveDes").toInt();
            ui.comboBox_language->setCurrentIndex(saveSet);
            ui.comboBox_language->setView(new QListView(this));
            ui.comboBox_language->setStyleSheet(QString("QComboBox QAbstractItemView {background: rgb(192,192,192); min-height: 40px;}"));
            ui.comboBox_language->setStyleSheet(QString("QComboBox QAbstractItemView::item {background: rgb(192,192,192); min-height: 40px;}"));
        }
        else if (pkid == 20) //系统液充灌体积
        {
            int saveSet = all_system_set_para.value("saveSet").toInt()/1000;
            ui.lineEdit_system_filling_volume->setText(QString::number(saveSet));
        }

        else if (pkid == 21)
        {
            //21	600		系统液清洗体积
            int saveSet = all_system_set_para.value("saveSet").toInt()/1000;
            ui.lineEdit_system_wash_volume->setText(QString::number(saveSet));
        }
        else if (pkid == 22)
        {
            //22	300	300, 300, 300	月维护泵充灌
            int saveSet = all_system_set_para.value("saveSet").toInt()/1000;
            ui.lineEdit_month_filling_volume->setText(QString::number(saveSet));
        }
        else if (pkid == 23)
        {
            //23	200	200, 200, 200	周维护泵充灌
            int saveSet = all_system_set_para.value("saveSet").toInt()/1000;
            ui.lineEdit_week_filling_volume->setText(QString::number(saveSet));
        }
        else if (pkid == 24)
        {
            //9992	9999	2022 - 10 - 09 10:50 : 57	月维护完成时间
            int saveSet = all_system_set_para.value("saveSet").toInt()/60000;
            ui.lineEdit_month_finish_time->setText(QString::number(saveSet));
        }
        else if (pkid == 25)
        {
            //25	50		月维护泵校准
            int saveSet = all_system_set_para.value("saveSet").toInt();
            ui.lineEdit_monthly_maintenance_pump_calibration->setText(QString::number(saveSet));
        }
        else if (pkid == 26)
        {
            //26	500	1000	泵校准两次下降最大差值
            int saveSet = all_system_set_para.value("saveSet").toInt();
            ui.lineEdit_between_two_drops_of_pump->setText(QString::number(saveSet));
            int saveSet1 = all_system_set_para.value("saveDes").toInt();
            ui.lineEdit_between_two_drops_of_pump_max->setText(QString::number(saveSet1));
        }
        else if (pkid == 27)
        {
            //9991	9999	2022 - 04 - 29 14:14 : 12	周维护完成时间
            int saveSet = all_system_set_para.value("saveSet").toInt()/60000;
            ui.lineEdit_week_finish_time->setText(QString::number(saveSet));
        }
        else if (pkid == 20006)
        {
            //9992	9999	2022 - 10 - 09 10:50 : 57	月维护完成时间
            double save_des = all_system_set_para.value("saveDes").toDouble();
            ui.lineEdit_Weight->setText(QString("%1").arg(save_des));
        }
        else if (pkid == 20001)
        {
            //20001	0	0	增加蜂鸣器声音“使能 - 1 / 关闭 - 0”按钮
            int saveSet = all_system_set_para.value("saveSet").toInt();
            ui.comboBox_beep_enable->setCurrentIndex(saveSet);
            ui.comboBox_beep_enable->setView(new  QListView(this));
            ui.comboBox_beep_enable->setStyleSheet(QString("QComboBox QAbstractItemView {background: rgb(192,192,192); min-height: 40px;}"));
            ui.comboBox_beep_enable->setStyleSheet(QString("QComboBox QAbstractItemView::item {background: rgb(192,192,192); min-height: 40px;}"));
        }
        else if (pkid == 20002)
        {
            //20002	0	0	废液桶 使能 1、去使能为 0”
            int saveSet = all_system_set_para.value("saveSet").toInt();
            ui.comboBox_waste_liquid_tank_enable->setCurrentIndex(saveSet);
            ui.comboBox_waste_liquid_tank_enable->setView(new  QListView(this));
            ui.comboBox_waste_liquid_tank_enable->setStyleSheet(QString("QComboBox QAbstractItemView {background: rgb(192,192,192); min-height: 40px;}"));
            ui.comboBox_waste_liquid_tank_enable->setStyleSheet(QString("QComboBox QAbstractItemView::item {background: rgb(192,192,192); min-height: 40px;}"));
        }
        else if (pkid == 20008)
        {
            //20008	0	0	 是否拍照  使能 1、去使能为 0”
            int saveSet = all_system_set_para.value("saveSet").toInt();
            ui.comboBox_waste_liquid_tank_enable_2->setCurrentIndex(saveSet);
            ui.comboBox_waste_liquid_tank_enable_2->setView(new  QListView(this));
            ui.comboBox_waste_liquid_tank_enable_2->setStyleSheet(QString("QComboBox QAbstractItemView {background: rgb(192,192,192); min-height: 40px;}"));
            ui.comboBox_waste_liquid_tank_enable_2->setStyleSheet(QString("QComboBox QAbstractItemView::item {background: rgb(192,192,192); min-height: 40px;}"));
        }
        else if (pkid == 20003)
        {
            //20002	0	0	废液桶 使能 1、去使能为 0”
            int saveSet = all_system_set_para.value("saveSet").toInt()/1000;
            ui.lineEdit_system_wash_volume_2->setText(QString::number(saveSet));
        }
        else if (pkid == 20004)
        {
            //20002	0	0	废液桶 使能 1、去使能为 0”
            int saveSet = all_system_set_para.value("saveSet").toInt()/1000;
            ui.lineEdit_system_wash_volume_3->setText(QString::number(saveSet));
        }
        else if (pkid == 7)
        {
            //7	1	sampleNeedle suck	样本针吸样液位探测，1 = 打开，0 = 关闭
            int saveSet = all_system_set_para.value("saveSet").toInt();
            if (saveSet == 0)
            {
                ui.comboBox_aspirate_sample->setCurrentIndex(1);
            }
            else
            {
                ui.comboBox_aspirate_sample->setCurrentIndex(0);
            }
            ui.comboBox_aspirate_sample->setView(new  QListView(this));
            ui.comboBox_aspirate_sample->setStyleSheet(QString("QComboBox QAbstractItemView {background: rgb(192,192,192); min-height: 40px;}"));
            ui.comboBox_aspirate_sample->setStyleSheet(QString("QComboBox QAbstractItemView::item {background: rgb(192,192,192); min-height: 40px;}"));
        }
        else if (pkid == 8)
        {
            //8	1	sampleNeedle spit	样本针吐样液位探测，1 = 打开，0 = 关闭
            int saveSet = all_system_set_para.value("saveSet").toInt();
            if (saveSet == 0)
            {
                ui.comboBox_vomit->setCurrentIndex(1);
            }
            else
            {
                ui.comboBox_vomit->setCurrentIndex(0);
            }
            ui.comboBox_vomit->setView(new  QListView(this));
            ui.comboBox_vomit->setStyleSheet(QString("QComboBox QAbstractItemView {background: rgb(192,192,192); min-height: 40px;}"));
            ui.comboBox_vomit->setStyleSheet(QString("QComboBox QAbstractItemView::item {background: rgb(192,192,192); min-height: 40px;}"));

        }
        else if(pkid == 20010)
        {
            ui.txtReportTitle->setText(all_system_set_para.value("saveDes").toString());
        }

    }
    QString  loginName = GlobalData::getLoginName1();
    uint group_id = GlobalData::getGruopId();
    //不是管理员,
    if (group_id == 3)
    {
        ui.comboBox_CompanyList->setEnabled(false);
        ui.comboBox_run_sequence->setEnabled(false);
    }
    else
    {
        ui.comboBox_CompanyList->setEnabled(true);
        ui.comboBox_run_sequence->setEnabled(true);
    }

    ui.pushButton_Cancel->setVisible(false);

    QRegExpValidator* validator11 = new QRegExpValidator(QRegExp("^(5|[1-9][0-9]?|1[0-9]{2}|2[0-3][0-9]|240)$"), ui.lineEdit_week_finish_time);

    ui.lineEdit_week_finish_time->setValidator(validator11);

    QRegExpValidator* validator1 = new QRegExpValidator(QRegExp("^(5|[1-9][0-9]?|1[0-9]{2}|2[0-3][0-9]|240)$"), ui.lineEdit_month_finish_time);
    ui.lineEdit_month_finish_time->setValidator(validator1);

    QRegExpValidator* validator2 = new QRegExpValidator(QRegExp("^(?:[1-9]|10)$"), ui.lineEdit_month_filling_volume);
    ui.lineEdit_month_filling_volume->setValidator(validator2);

    QRegExpValidator* validator3 = new QRegExpValidator(QRegExp("^(?:[1-9]|10)$"), ui.lineEdit_week_filling_volume);
    ui.lineEdit_week_filling_volume->setValidator(validator3);

    QRegExpValidator* validator4 = new QRegExpValidator(QRegExp("^(3[0-9]{2}|[4-6][0-9]{3}|700)$"), ui.lineEdit_monthly_maintenance_pump_calibration);
    ui.lineEdit_monthly_maintenance_pump_calibration->setValidator(validator4);

    QRegExpValidator* validator5 = new QRegExpValidator(QRegExp("^\\d*$"), ui.lineEdit_between_two_drops_of_pump);
    ui.lineEdit_between_two_drops_of_pump->setValidator(validator5);

    QRegExpValidator* validator6 = new QRegExpValidator(QRegExp("^\\d*$"), ui.lineEdit_between_two_drops_of_pump_max);
    ui.lineEdit_between_two_drops_of_pump_max->setValidator(validator6);

    QRegExpValidator* validator7 = new QRegExpValidator(QRegExp("^[1-5]$"), ui.lineEdit_system_filling_volume);
    ui.lineEdit_system_filling_volume->setValidator(validator7);

    QRegExpValidator* validator8 = new QRegExpValidator(QRegExp("^[1-5]$"), ui.lineEdit_system_wash_volume);
    ui.lineEdit_system_wash_volume->setValidator(validator8);

    QRegExpValidator* validator9 = new QRegExpValidator(QRegExp("^[1-5]$"), ui.lineEdit_system_wash_volume_2);
    ui.lineEdit_system_wash_volume_2->setValidator(validator9);

    QRegExpValidator* validator10 = new QRegExpValidator(QRegExp("^[1-5]$"), ui.lineEdit_system_wash_volume_3);
    ui.lineEdit_system_wash_volume_3->setValidator(validator10);

    QString sz = GlobalData::LoadLanguageInfo("K1188");
    ui.label_17->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1189");
    ui.label_16->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1190");
    ui.label_13->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1191");
    ui.label_14->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1192");
    ui.label_21->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1193");
    ui.label_15->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1194");
    ui.label_4->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1195");
    ui.label_11->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1196");
    ui.label_12->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1197");
    ui.label_22->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1198");
    ui.label_23->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1199");
    ui.label_6->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1200");
    ui.label_3->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1201");
    ui.label_8->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1202");
    ui.label_9->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1203");
    ui.label_10->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1204");
    ui.label_7->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1205");
    ui.label_18->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1206");
    ui.label_19->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1207");

    sz = GlobalData::LoadLanguageInfo("K1587");
    ui.label_28->setText(sz);

    sz = GlobalData::LoadLanguageInfo("K1207");
    ui.label_5->setText("5-240"+sz);
    ui.label_24->setText("5-240" + sz);

    sz = GlobalData::LoadLanguageInfo("K1208");
    ui.pushButton_Test->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1141");
    ui.pushButton_Save->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1134");
    ui.pushButton_Cancel->setText(sz);

    sz = GlobalData::LoadLanguageInfo("K1122");
    ui.label_55->setText(sz);
    ui.pushButtonPara->setVisible(true);

    ui.label_29->setText(GlobalData::LoadLanguageInfo("K2001"));
    ui.label_56->setText(GlobalData::LoadLanguageInfo("K2002"));
    ui.pushButtonPara->setText(GlobalData::LoadLanguageInfo("K1762"));
}

SystemSet::~SystemSet()
{
}
void SystemSet::on_pushButton_Test_clicked()
{
    ui.lineEdit_week_finish_time->setText("15");
    ui.lineEdit_month_finish_time->setText("15");

    ui.lineEdit_month_filling_volume->setText("3");
    ui.lineEdit_week_filling_volume->setText("3");

    ui.lineEdit_monthly_maintenance_pump_calibration->setText("500");

    ui.lineEdit_between_two_drops_of_pump->setText("5000");
    ui.lineEdit_between_two_drops_of_pump_max->setText("7000");

    ui.lineEdit_system_filling_volume->setText("3");
    ui.lineEdit_system_wash_volume->setText("3");

    ui.comboBox_beep_enable->setCurrentText(GlobalData::LoadLanguageInfo("K1700"));//"是");
    ui.comboBox_aspirate_sample->setCurrentText(GlobalData::LoadLanguageInfo("K1698"));//"打开");
    ui.comboBox_vomit->setCurrentText(GlobalData::LoadLanguageInfo("K1698"));//"打开");
    ui.comboBox_waste_liquid_tank_enable->setCurrentText(GlobalData::LoadLanguageInfo("K1700"));//"是");

    ui.lineEdit_system_wash_volume_2->setText("3");
    ui.lineEdit_system_wash_volume_3->setText("3");

}


void SystemSet::company_data_refalsh()
{
    auto dao = AnalysisUIDao::instance();
    // 设置公司
    CompanyDao* companyDao = CompanyDao::instance();
    QVector<CompanyModel> companyModels = companyDao->getAllRows();
    for (CompanyModel& model : companyModels)
    {
        QString itemName = model.getName();
        ui.comboBox_CompanyList->addItem(itemName, QString::number(model.getId()));
    }
    bool bResult = false;
    if (ui.comboBox_CompanyList->count() > 0)
    {
        //当前应用膜条公司名字
        QString PaperInfo = dao->SelectPaperInfo(&bResult);
        //选中单元格 第一行：
        ui.comboBox_CompanyList->setCurrentText(PaperInfo);
        onCompanyComboBoxChanged(PaperInfo);
    }
}

void SystemSet::on_pushButtonPara_clicked()
{
    emit sglProcessAction(ui.comboBox_CompanyList->currentText(),ui.comboBox_CompanyList->currentData().toString());
}

void SystemSet::on_pushButton_Save_clicked() 
{
//    auto dao = AnalysisUIDao::instance();
    SystemSetModel setModel;
    bool bResult = false;
    QString value_set = ui.lineEdit_between_two_drops_of_pump->text();
    QString value_des = ui.lineEdit_between_two_drops_of_pump_max->text();

    // 周维护浸泡时间
    int week_finish_time = ui.lineEdit_week_finish_time->text().toInt();
    if (week_finish_time == 0 || week_finish_time < 5 || week_finish_time>240)
    {
        ui.lineEdit_week_finish_time->setFocus();
        ui.lineEdit_week_finish_time->setText("5");
        return;
    }

    // 月维护浸泡时间
    int month_finish_time = ui.lineEdit_month_finish_time->text().toInt();
    if (month_finish_time == 0 || month_finish_time < 5 || month_finish_time>240)
    {
        ui.lineEdit_month_finish_time->setFocus();
        ui.lineEdit_month_finish_time->setText("5");
        return;
    }

    // 月维护泵校准
    int monthly_maintenance_pump_calibration = ui.lineEdit_monthly_maintenance_pump_calibration->text().toInt();
    if (monthly_maintenance_pump_calibration == 0 || monthly_maintenance_pump_calibration < 300 || monthly_maintenance_pump_calibration>700)
    {
        ui.lineEdit_monthly_maintenance_pump_calibration->setFocus();
        ui.lineEdit_monthly_maintenance_pump_calibration->setText("300");
        return;
    }

    int get_value = ui.lineEdit_week_finish_time->text().toInt();
    if (get_value == 0)
    {
        ui.lineEdit_week_finish_time->setFocus();
        return;
    }
    get_value = ui.lineEdit_month_finish_time->text().toInt();
    if (get_value == 0)
    {
        ui.lineEdit_month_finish_time->setFocus();
        return;
    }
    get_value = ui.lineEdit_month_filling_volume->text().toInt();
    if (get_value == 0)
    {
        ui.lineEdit_month_filling_volume->setFocus();
        return;
    }
    get_value = ui.lineEdit_week_filling_volume->text().toInt();
    if (get_value == 0)
    {
        ui.lineEdit_week_filling_volume->setFocus();
        return;
    }
    get_value = ui.lineEdit_monthly_maintenance_pump_calibration->text().toInt();
    if (get_value == 0)
    {
        ui.lineEdit_monthly_maintenance_pump_calibration->setFocus();
        return;
    }
    get_value = ui.lineEdit_between_two_drops_of_pump->text().toInt();
    if (get_value == 0)
    {
        ui.lineEdit_between_two_drops_of_pump->setFocus();
        return;
    }
    get_value = ui.lineEdit_between_two_drops_of_pump_max->text().toInt();
    if (get_value == 0)
    {
        ui.lineEdit_between_two_drops_of_pump_max->setFocus();
        return;
    }
    get_value = ui.lineEdit_system_filling_volume->text().toInt();
    if (get_value == 0)
    {
        ui.lineEdit_system_filling_volume->setFocus();
        return;
    }
    get_value = ui.lineEdit_system_wash_volume->text().toInt();
    if (get_value == 0)
    {
        ui.lineEdit_system_wash_volume->setFocus();
        return;
    }
    get_value = ui.lineEdit_system_wash_volume_2->text().toInt();
    if (get_value == 0)
    {
        ui.lineEdit_system_wash_volume_2->setFocus();
        return;
    }
    get_value = ui.lineEdit_system_wash_volume_3->text().toInt();
    if (get_value == 0)
    {
        ui.lineEdit_system_wash_volume_3->setFocus();
        return;
    }


    if (value_set.toInt() > value_des.toInt())
    {
        ui.lineEdit_between_two_drops_of_pump->setFocus();
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1289"), MyMessageBox::Ok,"OK","");
        return;
    }

    QString root_path_picture = ui.lineEdit_RootPathPicture->text();
    setModel.setId(3);
    setModel.setSaveDes(root_path_picture);
    setModel.setSaveSet(0);
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1286"), MyMessageBox::Ok,"OK","");
        return;
    }

    QString root_path_resport = ui.lineEdit_RootPathReport->text();
    setModel.setId(4);
    setModel.setSaveDes(root_path_resport);
    setModel.setSaveSet(0);
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1285"), MyMessageBox::Ok,"OK","");
        return;
    }

    //当前使用的膜条所属公司
    setModel.setId(5);
    setModel.setSaveDes(ui.comboBox_CompanyList->currentText());
    setModel.setSaveSet(ui.comboBox_CompanyList->currentData().toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1284"), MyMessageBox::Ok,"OK","");
        return;
    }

    //	语言
    setModel.setId(20005);
    setModel.setSaveDes(ui.comboBox_language->currentText());
    setModel.setSaveSet(value_set == "EN"?2:1);
    value_set = ui.comboBox_language->currentText();
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1284"), MyMessageBox::Ok,"OK","");
        return;
    }

    value_set = ui.comboBox_run_sequence->currentText();
    int processId = ui.comboBox_run_sequence->currentData().toInt();
    setModel.setId(6);
    setModel.setSaveDes(value_set);
    setModel.setSaveSet(processId);
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //20	500	systemLiquidIrrigate	系统液充灌体积
    value_set = QString("%1").arg(ui.lineEdit_system_filling_volume->text().toInt()*1000);
    setModel.setId(20);
    setModel.setSaveDes(value_set);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //21	600		系统液清洗体积
    //value_set = ui.lineEdit_system_wash_volume->text();
    value_set = QString("%1").arg(ui.lineEdit_system_wash_volume->text().toInt() * 1000);
    setModel.setId(21);
    setModel.setSaveDes(value_set);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    value_set = QString("%1").arg(ui.lineEdit_system_wash_volume_2->text().toInt() * 1000);
    setModel.setId(20003);
    setModel.setSaveDes(value_set);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }
    value_set = QString("%1").arg(ui.lineEdit_Weight->text().toDouble());
    setModel.setId(20006);
    setModel.setSaveDes(value_set);
    setModel.setSaveSet(value_set.toDouble());
    bResult = SystemSetDao::instance()->updateModel(setModel);

    // 泵回流量
    value_set = QString("%1").arg(ui.lineEdit_system_wash_volume_3->text().toInt() * 1000);
    setModel.setId(20004);
    setModel.setSaveDes(value_set);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //22	300	300, 300, 300	月维护泵充灌
    //value_set = ui.lineEdit_month_filling_volume->text();
    value_set = QString("%1").arg(ui.lineEdit_month_filling_volume->text().toInt() * 1000);
    setModel.setId(22);
    setModel.setSaveDes(value_set);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }


    //1	0	40	功能条灰度阈值
    //2	0	18	Cut Off条灰度阈值
    //3	0	D:\HumablotProFiles\TestPictures	测试图像保存根目录
    //4	0	D:\HumablotProFiles\Reports	测试报告保存根目录
    //5	1	human	当前使用的膜条所属公司

    //23	200	200, 200, 200	周维护泵充灌
    value_set = QString("%1").arg(ui.lineEdit_week_filling_volume->text().toInt() * 1000);
    setModel.setId(23);
    setModel.setSaveDes(value_set);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //25	50		月维护泵校准
    value_set = ui.lineEdit_monthly_maintenance_pump_calibration->text();
    setModel.setId(25);
    setModel.setSaveDes(value_set);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //26	500	1000	泵校准两次下降最大差值
    value_set = ui.lineEdit_between_two_drops_of_pump->text();
    value_des = ui.lineEdit_between_two_drops_of_pump_max->text();
    setModel.setId(26);
    setModel.setSaveDes(value_des);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //9991	9999	2022 - 04 - 29 14:14 : 12	周维护完成时间
    value_set = QString("%1").arg(ui.lineEdit_week_finish_time->text().toInt() * 60000);
    setModel.setId(27);
    setModel.setSaveDes(value_set);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //9992	9999	2022 - 10 - 09 10:50 : 57	月维护完成时间
    value_set = QString("%1").arg(ui.lineEdit_month_finish_time->text().toInt() * 60000);
    setModel.setId(24);
    setModel.setSaveDes(value_set);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }
    //20001	0	0	增加蜂鸣器声音“使能 - 1 / 关闭 - 0”按钮
    value_des = ui.comboBox_beep_enable->currentText();
    if (value_des == GlobalData::LoadLanguageInfo("K1700"))//"是")
    {
        value_set = "1";
    }
    else
    {
        value_set = "0";
    }
    setModel.setId(20001);
    setModel.setSaveDes(value_des);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    if (value_set == GlobalData::LoadLanguageInfo("K1700"))//"是")
    {
        value_set = "1";
    }
    else
    {
        value_set = "0";
    }

    //20002	0	0	废液桶 使能 1、去使能为 0”
    value_des = ui.comboBox_waste_liquid_tank_enable->currentText();//ui.lineEdit_RootPathReport->text();
    if (value_des == GlobalData::LoadLanguageInfo("K1700"))//"是")
    {
        value_set = "1";
    }
    else
    {
        value_des = "0";
    }
    setModel.setId(20002);
    setModel.setSaveDes(value_des);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }


    value_des = ui.comboBox_waste_liquid_tank_enable_2->currentText();//ui.lineEdit_RootPathReport->text();
    if (value_des == GlobalData::LoadLanguageInfo("K1700"))//"是")
    {
        value_set = "1";
    }
    else
    {
        value_set = "0";
    }
    setModel.setId(20008);
    setModel.setSaveDes(value_des);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok, "OK", "");
        return;
    }

    //7	1	sampleNeedle suck	样本针吸样液位探测，1 = 打开，0 = 关闭
    value_des = ui.comboBox_aspirate_sample->currentText();//ui.lineEdit_RootPathReport->text();
    if (value_des == GlobalData::LoadLanguageInfo("K1698"))//"打开")
    {
        value_set = "1";
    }
    else
    {
        value_set = "0";
    }
    setModel.setId(7);
    setModel.setSaveDes(value_des);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //8	1	sampleNeedle spit	样本针吐样液位探测，1 = 打开，0 = 关闭	//
    value_des = ui.comboBox_vomit->currentText();
    if (value_des == GlobalData::LoadLanguageInfo("K1698"))//"打开")
    {
        value_set = "1";
    }
    else
    {
        value_set = "0";
    }
    setModel.setId(8);
    setModel.setSaveDes(value_des);
    setModel.setSaveSet(value_set.toInt());
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }
    setModel.setId(20010);
    setModel.setSaveDes(ui.txtReportTitle->text().simplified());
    setModel.setSaveSet(0);
    bResult = SystemSetDao::instance()->updateModel(setModel);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    auto ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1259"), GlobalData::LoadLanguageInfo("K1278"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo("K1181"), GlobalData::LoadLanguageInfo("K1134"));
    if (ret == MyMessageBox::Ok)
    {
        InstrumentStateModel *_InstrumentState(InstrumentStateModel::instance());
        auto state = _InstrumentState->getMachineState();
        if ((state.state == _InstrumentState->enumRuning) || (state.state == _InstrumentState->enumMaintain))
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1711"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo("K1181"), "");
            return;
        }
        // 或者   aApp->closeAllWindows();
        Instrument::instance()->closeSocket();
        QString program = QCoreApplication::applicationFilePath();
        QStringList arguments = QCoreApplication::arguments();
        QProcess::startDetached(program, arguments);
        QCoreApplication::instance()->quit();
    }
}

void SystemSet::on_pushButton_Cancel_clicked() 
{
    this->close();
}

void SystemSet::onCompanyComboBoxChanged(const QString &text)
{
    ui.comboBox_run_sequence->clear();
    int index = ui.comboBox_CompanyList->findText(text);
    if(index == -1) return;
    int companyId = ui.comboBox_CompanyList->itemData(index, Qt::UserRole).toInt();
    qDebug()<<"name1 text"<<text<<companyId;
    ProcessDao* processDao = ProcessDao::instance();
    QVector<ProcessModel> processVect = processDao->getModels(companyId);
    for(ProcessModel& process:processVect)
    {
        qDebug()<<"name1"<<process.getProcessName();
        ui.comboBox_run_sequence->addItem(process.getProcessName(), process.getId());
    }
    SystemSetModel setModel;
    if(SystemSetDao::instance()->getModel(6, setModel))
    {
        int index = ui.comboBox_run_sequence->findText(setModel.getSaveDes());
        qDebug()<<"process name"<<setModel.getSaveDes()<<index;
        if (index != -1)
        {
            ui.comboBox_run_sequence->setCurrentIndex(index);
        } else
        {
            ui.comboBox_run_sequence->setCurrentIndex(-1);
        }
    }
}
