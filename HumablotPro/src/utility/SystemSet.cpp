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
#include "ProcessParaWidgets.h"

SystemSet::SystemSet(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setAttribute(Qt::WA_ShowModal, true);
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
    //QRegExp regExp;
    //regExp.setPattern("[1-6]?[0-9]|[7][0-2]|[1-9]");
    //QValidator * q_validator = new QRegExpValidator(regExp, ui.lineEdit_ControlThreshold);
    //ui.lineEdit_ControlThreshold->setValidator(q_validator);
    QRegExpValidator* validator = new QRegExpValidator(QRegExp("^(?:[5-9]|[1-9][0-9]|[1-2][0-3][0-9]|240)$"), ui.lineEdit_week_finish_time);
    ui.lineEdit_week_finish_time->setValidator(validator);
    ui.lineEdit_RootPathReport->setEnabled(true);
    ui.lineEdit_RootPathPicture->setEnabled(true);
    QString strControlThreshold = dao->SelectControlThreshold(&bResult);
    ui.lineEdit_ControlThreshold->setText(strControlThreshold);

    QString strCutOffThreshold = dao->SelectCutOffThreshold(&bResult);
    ui.lineEdit_CutOffThreshold->setText(strCutOffThreshold);

    QString strRootPathPicture = dao->SelectTestPicturesRootPath(&bResult);
    ui.lineEdit_RootPathPicture->setText(strRootPathPicture);

    QString strRootPathReport = dao->SelectTestReportsRootPath(&bResult);
    ui.lineEdit_RootPathReport->setText(strRootPathReport);

    //ui.lineEdit_week_finish_time->setEnabled(false);

    //打开、关闭
    ui.comboBox_aspirate_sample->clear();//.addItem('条目1')
    ui.comboBox_aspirate_sample->addItem(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1698"));//.addItem('条目1')
    ui.comboBox_aspirate_sample->addItem(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1699"));//.addItem('条目1')

    ui.comboBox_vomit->clear();//.addItem('条目1')
    ui.comboBox_vomit->addItem(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1698"));//.addItem('条目1')
    ui.comboBox_vomit->addItem(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1699"));//.addItem('条目1')

    //是、否
    ui.comboBox_beep_enable->clear();
    ui.comboBox_beep_enable->addItem(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1701"));//.addItem('条目1')
    ui.comboBox_beep_enable->addItem(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1700"));//.addItem('条目1')


    ui.comboBox_waste_liquid_tank_enable->clear();
    ui.comboBox_waste_liquid_tank_enable->addItem(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1701"));//.addItem('条目1')
    ui.comboBox_waste_liquid_tank_enable->addItem(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1700"));//.addItem('条目1')


    //当前应用膜条公司名字
    QString PaperInfo = dao->SelectPaperInfo(&bResult);

    QSqlQuery CompanyQuery = dao->SelectCompanys(&bResult);



    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1290"), MyMessageBox::Ok,"OK","");
        return;
    }


    //取出所有的参数
    QString sql = "select * from tsystemset";
    auto all_system_set_para = dao->SelectAll_tsystemset(&bResult, sql);
    while (all_system_set_para.next())
    {
        int pkid = all_system_set_para.value("id").toInt();

        if (pkid == 6)
        {
            int saveSet = all_system_set_para.value("saveSet").toInt();
            ui.comboBox_run_sequence->setCurrentIndex(saveSet);
            ui.comboBox_run_sequence->setView(new  QListView(this));
            ui.comboBox_run_sequence->setStyleSheet(QString(
                                                        "QComboBox QAbstractItemView{"
                                                        "background: rgb(192,192,192);"
                                                        "min-height: 40px;"   // 更改 item 高度为 40 像素
                                                        "}"
                                                        ));

            ui.comboBox_run_sequence->setStyleSheet(QString(
                                                        "QComboBox QAbstractItemView:item{"
                                                        "background: rgb(192,192,192);"
                                                        "min-height: 40px;"   // 更改 item 高度为 40 像素
                                                        "}"
                                                        ));
            //6	1	defaultProcess	默认时序
        }
        if (pkid == 20005)
        {
            int saveSet = all_system_set_para.value("saveDes").toInt();
            ui.comboBox_language->setCurrentIndex(saveSet);
            ui.comboBox_language->setView(new  QListView(this));
            ui.comboBox_language->setStyleSheet(QString(
                                                    "QComboBox QAbstractItemView{"
                                                    "background: rgb(192,192,192);"
                                                    "min-height: 40px;"   // 更改 item 高度为 40 像素
                                                    "}"
                                                    ));

            ui.comboBox_language->setStyleSheet(QString(
                                                    "QComboBox QAbstractItemView:item{"
                                                    "background: rgb(192,192,192);"
                                                    "min-height: 40px;"   // 更改 item 高度为 40 像素
                                                    "}"
                                                    ));
        }


        if (pkid == 20)
        {
            //20	500	systemLiquidIrrigate	系统液充灌体积
            int saveSet = all_system_set_para.value("saveSet").toInt()/1000;
            ui.lineEdit_system_filling_volume->setText(QString::number(saveSet));
        }

        if (pkid == 21)
        {
            //21	600		系统液清洗体积
            int saveSet = all_system_set_para.value("saveSet").toInt()/1000;
            ui.lineEdit_system_wash_volume->setText(QString::number(saveSet));
        }

        if (pkid == 22)
        {
            //22	300	300, 300, 300	月维护泵充灌
            int saveSet = all_system_set_para.value("saveSet").toInt()/1000;
            ui.lineEdit_month_filling_volume->setText(QString::number(saveSet));
        }
        //1	0	40	功能条灰度阈值
        //2	0	18	Cut Off条灰度阈值
        //3	0	D:\HumablotProFiles\TestPictures	测试图像保存根目录
        //4	0	D:\HumablotProFiles\Reports	测试报告保存根目录
        //5	1	human	当前使用的膜条所属公司

        if (pkid == 23)
        {
            //23	200	200, 200, 200	周维护泵充灌
            int saveSet = all_system_set_para.value("saveSet").toInt()/1000;
            ui.lineEdit_week_filling_volume->setText(QString::number(saveSet));
        }

        //if (pkid == 24)
        //{
        //	//24	900000		月维护管路浸泡15分钟
        //	int saveSet = all_system_set_para.value("saveSet").toInt();
        //	ui.lineEdit_pip_15_min->setText(QString::number(saveSet));
        //}

        if (pkid == 25)
        {
            //25	50		月维护泵校准
            int saveSet = all_system_set_para.value("saveSet").toInt();
            ui.lineEdit_monthly_maintenance_pump_calibration->setText(QString::number(saveSet));
        }

        if (pkid == 26)
        {
            //26	500	1000	泵校准两次下降最大差值
            int saveSet = all_system_set_para.value("saveSet").toInt();
            ui.lineEdit_between_two_drops_of_pump->setText(QString::number(saveSet));
            int saveSet1 = all_system_set_para.value("saveDes").toInt();
            ui.lineEdit_between_two_drops_of_pump_max->setText(QString::number(saveSet1));
        }

        if (pkid == 27)
        {
            //9991	9999	2022 - 04 - 29 14:14 : 12	周维护完成时间
            int saveSet = all_system_set_para.value("saveSet").toInt()/60000;
            ui.lineEdit_week_finish_time->setText(QString::number(saveSet));
        }

        if (pkid == 24)
        {
            //9992	9999	2022 - 10 - 09 10:50 : 57	月维护完成时间
            int saveSet = all_system_set_para.value("saveSet").toInt()/60000;
            ui.lineEdit_month_finish_time->setText(QString::number(saveSet));
        }

        if (pkid == 20006)
        {
            //9992	9999	2022 - 10 - 09 10:50 : 57	月维护完成时间
            double save_des = all_system_set_para.value("saveDes").toDouble();
            ui.lineEdit_Weight->setText(QString("%1").arg(save_des));
        }


        if (pkid == 20001)
        {
            //20001	0	0	增加蜂鸣器声音“使能 - 1 / 关闭 - 0”按钮
            int saveSet = all_system_set_para.value("saveSet").toInt();
            ui.comboBox_beep_enable->setCurrentIndex(saveSet);
            ui.comboBox_beep_enable->setView(new  QListView(this));
            ui.comboBox_beep_enable->setStyleSheet(QString(
                                                       "QComboBox QAbstractItemView {"
                                                       "background: rgb(192,192,192);"
                                                       "min-height: 40px;"   // 更改 item 高度为 40 像素
                                                       "}"
                                                       ));

            ui.comboBox_beep_enable->setStyleSheet(QString(
                                                       "QComboBox QAbstractItemView:item{"
                                                       "background: rgb(192,192,192);"
                                                       "min-height: 40px;"   // 更改 item 高度为 40 像素
                                                       "}"
                                                       ));
        }

        if (pkid == 20002)
        {
            //20002	0	0	废液桶 使能 1、去使能为 0”
            int saveSet = all_system_set_para.value("saveSet").toInt();
            ui.comboBox_waste_liquid_tank_enable->setCurrentIndex(saveSet);
            ui.comboBox_waste_liquid_tank_enable->setView(new  QListView(this));
            ui.comboBox_waste_liquid_tank_enable->setStyleSheet(QString(
                                                                    "QComboBox QAbstractItemView {"
                                                                    "background: rgb(192,192,192);"
                                                                    "min-height: 40px;"   // 更改 item 高度为 40 像素
                                                                    "}"
                                                                    ));

            ui.comboBox_waste_liquid_tank_enable->setStyleSheet(QString(
                                                                    "QComboBox QAbstractItemView:item {"
                                                                    "background: rgb(192,192,192);"
                                                                    "min-height: 40px;"   // 更改 item 高度为 40 像素
                                                                    "}"
                                                                    ));
        }

        if (pkid == 20008)
        {
            //20008	0	0	 是否拍照  使能 1、去使能为 0”
            int saveSet = all_system_set_para.value("saveSet").toInt();
            ui.comboBox_waste_liquid_tank_enable_2->setCurrentIndex(saveSet);
            ui.comboBox_waste_liquid_tank_enable_2->setView(new  QListView(this));
            ui.comboBox_waste_liquid_tank_enable_2->setStyleSheet(QString(
                                                                      "QComboBox QAbstractItemView {"
                                                                      "background: rgb(192,192,192);"
                                                                      "min-height: 40px;"   // 更改 item 高度为 40 像素
                                                                      "}"
                                                                      ));

            ui.comboBox_waste_liquid_tank_enable_2->setStyleSheet(QString(
                                                                      "QComboBox QAbstractItemView:item {"
                                                                      "background: rgb(192,192,192);"
                                                                      "min-height: 40px;"   // 更改 item 高度为 40 像素
                                                                      "}"
                                                                      ));
        }



        if (pkid == 20003)
        {
            //20002	0	0	废液桶 使能 1、去使能为 0”
            int saveSet = all_system_set_para.value("saveSet").toInt()/1000;
            ui.lineEdit_system_wash_volume_2->setText(QString::number(saveSet));
        }

        if (pkid == 20004)
        {
            //20002	0	0	废液桶 使能 1、去使能为 0”
            int saveSet = all_system_set_para.value("saveSet").toInt()/1000;
            ui.lineEdit_system_wash_volume_3->setText(QString::number(saveSet));
        }

        if (pkid == 7)
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
            ui.comboBox_aspirate_sample->setStyleSheet(QString(
                                                           "QComboBox QAbstractItemView {"
                                                           "background: rgb(192,192,192);"
                                                           "   min-height: 40px;"   // 更改 item 高度为 40 像素
                                                           "}"
                                                           ));

            ui.comboBox_aspirate_sample->setStyleSheet(QString(
                                                           "QComboBox QAbstractItemView:item {"
                                                           "background: rgb(192,192,192);"
                                                           "   min-height: 40px;"   // 更改 item 高度为 40 像素
                                                           "}"
                                                           ));
        }

        if (pkid == 8)
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

            ui.comboBox_vomit->setStyleSheet(QString(
                                                 "QComboBox QAbstractItemView {"
                                                 "background: rgb(192,192,192);"
                                                 "   min-height: 40px;"   // 更改 item 高度为 40 像素
                                                 "}"
                                                 ));


            ui.comboBox_vomit->setStyleSheet(QString(
                                                 "QComboBox QAbstractItemView:item {"
                                                 "background: rgb(192,192,192);"
                                                 "   min-height: 40px;"   // 更改 item 高度为 40 像素
                                                 "}"
                                                 ));

            //ui.comboBox_vomit->setCurrentIndex(saveSet);
        }


    }

    int row = 0;
    while (CompanyQuery.next())
    {
        QString itemName = CompanyQuery.value("Name").toString();
        //QString itemId = CompanyQuery.value("ID").toString();
        //QString itemString = itemName + "-" + itemId;
        //itemString.sprintf("%s-%s", itemName, itemId);
        //ui.tableWidget_Company->insertRow(row);
        //addCompanyContent(row, 0, itemName);
        ui.comboBox_CompanyList->addItem(itemName); //带图标
        row++;
    }
    ui.comboBox_CompanyList->setView(new  QListView(this));
    ui.comboBox_CompanyList->setStyleSheet(QString(
                                               "QComboBox QAbstractItemView {"
                                               "background: rgb(192,192,192);"
                                               "   min-height: 40px;"   // 更改 item 高度为 40 像素
                                               "}"
                                               ));

    ui.comboBox_CompanyList->setStyleSheet(QString(
                                               "QComboBox QAbstractItemView:item {"
                                               "background: rgb(192,192,192);"
                                               "   min-height: 40px;"   // 更改 item 高度为 40 像素
                                               "}"
                                               ));





    if (row > 0)
    {
        /*设置让某个单元格或某行选中*/
        //选中单元格 第一行：
        ui.comboBox_CompanyList->setCurrentText(PaperInfo);
        ui.comboBox_CompanyList->setView(new  QListView(this));
        ui.comboBox_CompanyList->setStyleSheet(QString(
                                                   "QComboBox QAbstractItemView {"
                                                   "background: rgb(192,192,192);"
                                                   "   min-height: 40px;"   // 更改 item 高度为 40 像素
                                                   "}"
                                                   ));

        ui.comboBox_CompanyList->setStyleSheet(QString(
                                                   "QComboBox QAbstractItemView:item {"
                                                   "background: rgb(192,192,192);"
                                                   "   min-height: 40px;"   // 更改 item 高度为 40 像素
                                                   "}"
                                                   ));

        //ui.tableWidget_Company->setCurrentCell(0, 0, QItemSelectionModel::Select);
    }

    QString  loginName = GlobalData::getLoginName1();

    int group_id = GlobalData::getGruopId();
    //不是管理员,
    if (group_id == 3)
    {
        ui.comboBox_CompanyList->setEnabled(false);
    }
    else
    {
        ui.comboBox_CompanyList->setEnabled(true);
    }

    ui.label->setVisible(false);
    ui.label_2->setVisible(false);
    ui.lineEdit_ControlThreshold->setVisible(false);
    ui.lineEdit_CutOffThreshold->setVisible(false);
    //ui.label_4->setVisible(false);
    //ui.label_5->setVisible(false);
    //ui.pushButton_Test->setVisible(false);
    ui.pushButton_Cancel->setVisible(false);

    ui.lineEdit_pip_15_min->setVisible(false);
    ui.label_20->setVisible(false);

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

    QString sz = GlobalData::LoadLanguageInfo(g_language_type, "K1188");
    ui.label_17->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1189");
    ui.label_16->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1190");
    ui.label_13->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1191");
    ui.label_14->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1192");
    ui.label_21->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1193");
    ui.label_15->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1194");
    ui.label_4->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1195");
    ui.label_11->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1196");
    ui.label_12->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1197");
    ui.label_22->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1198");
    ui.label_23->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1199");
    ui.label_6->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1200");
    ui.label_3->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1201");
    ui.label_8->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1202");
    ui.label_9->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1203");
    ui.label_10->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1204");
    ui.label_7->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1205");
    ui.label_18->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1206");
    ui.label_19->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1207");

    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1587");
    ui.label_28->setText(sz);

    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1207");
    ui.label_5->setText("5-240"+sz);
    ui.label_24->setText("5-240" + sz);

    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1208");
    ui.pushButton_Test->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1141");
    ui.pushButton_Save->setText(sz);
    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1134");
    ui.pushButton_Cancel->setText(sz);

    sz = GlobalData::LoadLanguageInfo(g_language_type, "K1122");
    ui.label_55->setText(sz);

    //ui.pushButtonPara->setHidden(true);//.hide();
    //ui.pushButtonPara->setEnabled(true);// setEnabled(True);
    //ui.pushButtonPara->setStyleSheet("background-color: lightblue; color: white;");
    //ui.pushButtonPara->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none;color: white;border:0px solid;background - color:rgba(0, 0, 0, 0);");
    //ui.pushButtonPara->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none;"); // 将按钮设为透明
    ui.pushButtonPara->setVisible(true);

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

    ui.comboBox_beep_enable->setCurrentText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1700"));//"是");
    ui.comboBox_aspirate_sample->setCurrentText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1698"));//"打开");
    ui.comboBox_vomit->setCurrentText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1698"));//"打开");
    ui.comboBox_waste_liquid_tank_enable->setCurrentText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1700"));//"是");

    ui.lineEdit_system_wash_volume_2->setText("3");
    ui.lineEdit_system_wash_volume_3->setText("3");

}

void SystemSet::on_pushButtonPara_clicked()
{
    //弹出参数配置界面
    ProcessParaWidgets _ProcessParaWidgets;// = new ProcessParaWidgets();
    _ProcessParaWidgets.exec();
    //_ProcessParaWidgets.show();
    //_ProcessParaWidgets.show();
    //MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1287"), MyMessageBox::Ok, "OK", "");
}

void SystemSet::on_pushButton_Save_clicked() 
{
    auto dao = AnalysisUIDao::instance(); 
    bool bResult;


    QString value_set = ui.lineEdit_between_two_drops_of_pump->text();
    QString value_des = ui.lineEdit_between_two_drops_of_pump_max->text();


    int week_finish_time = ui.lineEdit_week_finish_time->text().toInt();
    if (week_finish_time == 0 || week_finish_time < 5 || week_finish_time>240)
    {
        ui.lineEdit_week_finish_time->setFocus();
        ui.lineEdit_week_finish_time->setText("5");
        return;
    }


    int month_finish_time = ui.lineEdit_month_finish_time->text().toInt();

    if (month_finish_time == 0 || month_finish_time < 5 || month_finish_time>240)
    {
        ui.lineEdit_month_finish_time->setFocus();
        ui.lineEdit_month_finish_time->setText("5");
        return;
    }

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
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1289"), MyMessageBox::Ok,"OK","");
        return;
    }

    bResult = dao->UpdateSystemSet("1", ui.lineEdit_ControlThreshold->text());
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1288"), MyMessageBox::Ok,"OK","");
        return;
    }

    bResult = dao->UpdateSystemSet("2", ui.lineEdit_CutOffThreshold->text());
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1287"), MyMessageBox::Ok,"OK","");
        return;
    }

    QString root_path_picture = ui.lineEdit_RootPathPicture->text();
    root_path_picture = root_path_picture.replace("\\", "\\\\");
    bResult = dao->UpdateSystemSet("3", root_path_picture);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1286"), MyMessageBox::Ok,"OK","");
        return;
    }

    QString root_path_resport = ui.lineEdit_RootPathReport->text();
    root_path_resport = root_path_resport.replace("\\","\\\\");
    bResult = dao->UpdateSystemSet("4", root_path_resport);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1285"), MyMessageBox::Ok,"OK","");
        return;
    }

    //当前使用的膜条所属公司
    QString select_paper_company_name = ui.comboBox_CompanyList->currentText();//ui.lineEdit_RootPathReport->text();
    bResult = dao->UpdateSystemSetId5("5", select_paper_company_name);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1284"), MyMessageBox::Ok,"OK","");
        return;
    }

    //当前使用的膜条所属公司
    //QString select_paper_company_name = ui.comboBox_CompanyList->currentText();//ui.lineEdit_RootPathReport->text();
    //bResult = dao->UpdateSystemSetId5("5", select_paper_company_name);
    //if (bResult == false)
    //{
    //	QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "更新膜条所属公司失败！", QMessageBox::Ok);
    //	return;
    //}


    //6	1	defaultProcess	默认时序
    value_set = ui.comboBox_language->currentText();
    if (value_set == "EN")
    {
        bResult = dao->UpdateSystemDes("20005", "2");
    }
    else
    {
        bResult = dao->UpdateSystemDes("20005", "1");
    }



    value_set = ui.comboBox_run_sequence->currentText();
    bResult = dao->UpdateSystemSet("6", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //20	500	systemLiquidIrrigate	系统液充灌体积
    value_set = QString("%1").arg(ui.lineEdit_system_filling_volume->text().toInt()*1000);
    bResult = dao->UpdateSystemSet("20", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //21	600		系统液清洗体积
    //value_set = ui.lineEdit_system_wash_volume->text();
    value_set = QString("%1").arg(ui.lineEdit_system_wash_volume->text().toInt() * 1000);
    bResult = dao->UpdateSystemSet("21", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //value_set = ui.lineEdit_system_wash_volume_2->text();
    value_set = QString("%1").arg(ui.lineEdit_system_wash_volume_2->text().toInt() * 1000);
    bResult = dao->UpdateSystemSet("20003", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    QString des_1 = QString("%1").arg(ui.lineEdit_Weight->text().toDouble());
    bResult = dao->UpdateSystemDes("20006", des_1);

    //value_set = ui.lineEdit_system_wash_volume_3->text();
    value_set = QString("%1").arg(ui.lineEdit_system_wash_volume_3->text().toInt() * 1000);
    bResult = dao->UpdateSystemSet("20004", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //22	300	300, 300, 300	月维护泵充灌
    //value_set = ui.lineEdit_month_filling_volume->text();
    value_set = QString("%1").arg(ui.lineEdit_month_filling_volume->text().toInt() * 1000);
    bResult = dao->UpdateSystemSet("22", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }


    //1	0	40	功能条灰度阈值
    //2	0	18	Cut Off条灰度阈值
    //3	0	D:\HumablotProFiles\TestPictures	测试图像保存根目录
    //4	0	D:\HumablotProFiles\Reports	测试报告保存根目录
    //5	1	human	当前使用的膜条所属公司

    //23	200	200, 200, 200	周维护泵充灌
    value_set = QString("%1").arg(ui.lineEdit_week_filling_volume->text().toInt() * 1000);
    //value_set = ui.lineEdit_week_filling_volume->text();
    bResult = dao->UpdateSystemSet("23", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //24	900000		月维护管路浸泡15分钟
    //value_set = ui.lineEdit_pip_15_min->text();
    //bResult = dao->UpdateSystemSet("24", value_set);
    //if (bResult == false)
    //{
    //	MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
    //	return;
    //}

    //25	50		月维护泵校准
    value_set = ui.lineEdit_monthly_maintenance_pump_calibration->text();
    bResult = dao->UpdateSystemSet("25", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //26	500	1000	泵校准两次下降最大差值
    value_set = ui.lineEdit_between_two_drops_of_pump->text();
    value_des = ui.lineEdit_between_two_drops_of_pump_max->text();
    bResult = dao->UpdateSystemSet("26", value_set);
    bResult = dao->UpdateSystemDes("26", value_des);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //9991	9999	2022 - 04 - 29 14:14 : 12	周维护完成时间
    //value_set = ui.lineEdit_week_finish_time->text();
    value_set = QString("%1").arg(ui.lineEdit_week_finish_time->text().toInt() * 60000);
    bResult = dao->UpdateSystemSet("27", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //9992	9999	2022 - 10 - 09 10:50 : 57	月维护完成时间
    //value_set = ui.lineEdit_month_finish_time->text();
    value_set = QString("%1").arg(ui.lineEdit_month_finish_time->text().toInt() * 60000);
    bResult = dao->UpdateSystemSet("24", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }
    //20001	0	0	增加蜂鸣器声音“使能 - 1 / 关闭 - 0”按钮
    value_set = ui.comboBox_beep_enable->currentText();//ui.lineEdit_RootPathReport->text();
    if (value_set == GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1700"))//"是")
    {
        value_set = "1";
    }
    else
    {
        value_set = "0";
    }
    bResult = dao->UpdateSystemSet("20001", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    if (value_set == GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1700"))//"是")
    {
        value_set = "1";
    }
    else
    {
        value_set = "0";
    }

    //20002	0	0	废液桶 使能 1、去使能为 0”
    value_set = ui.comboBox_waste_liquid_tank_enable->currentText();//ui.lineEdit_RootPathReport->text();
    if (value_set == GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1700"))//"是")
    {
        value_set = "1";
    }
    else
    {
        value_set = "0";
    }
    bResult = dao->UpdateSystemSet("20002", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }


    value_set = ui.comboBox_waste_liquid_tank_enable_2->currentText();//ui.lineEdit_RootPathReport->text();
    if (value_set == GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1700"))//"是")
    {
        value_set = "1";
    }
    else
    {
        value_set = "0";
    }
    bResult = dao->UpdateSystemSet("20008", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok, "OK", "");
        return;
    }


    //7	1	sampleNeedle suck	样本针吸样液位探测，1 = 打开，0 = 关闭

    value_set = ui.comboBox_aspirate_sample->currentText();//ui.lineEdit_RootPathReport->text();
    if (value_set == GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1698"))//"打开")
    {
        value_set = "1";
    }
    else
    {
        value_set = "0";
    }
    bResult = dao->UpdateSystemSet("7", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }

    //8	1	sampleNeedle spit	样本针吐样液位探测，1 = 打开，0 = 关闭	//
    value_set = ui.comboBox_vomit->currentText();//ui.lineEdit_RootPathReport->text();
    if (value_set == GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1698"))//"打开")
    {
        value_set = "1";
    }
    else
    {
        value_set = "0";
    }

    bResult = dao->UpdateSystemSet("8", value_set);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1283"), MyMessageBox::Ok,"OK","");
        return;
    }



    //if (!(state.state == _InstrumentState->enumStandby))
    //{
    //	MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1340"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
    //	return;
    //}

    //QMessageBox::information(this, "成功", "更新系统参数成功，软件将重新启动！", QMessageBox::Ok);
    auto ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1259"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1278"), MyMessageBox::Ok| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if (ret == MyMessageBox::Ok)
    {
        InstrumentStateModel *_InstrumentState(InstrumentStateModel::instance());
        auto state = _InstrumentState->getMachineState();
        if ((state.state == _InstrumentState->enumRuning) || (state.state == _InstrumentState->enumMaintain))
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1711"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
            return;
        }
        // 或者   aApp->closeAllWindows();
        Instrument::instance()->closeSocket();
        QString program = QCoreApplication::applicationFilePath();
        QStringList arguments = QCoreApplication::arguments();
        QProcess::startDetached(program, arguments);
        QCoreApplication::instance()->quit();
    }
    //QMessageBox::information(this, "成功", "所有系统参数配置完成，请重新启软件！", QMessageBox::Ok);
}

void SystemSet::on_pushButton_Cancel_clicked() 
{
    this->close();
}
