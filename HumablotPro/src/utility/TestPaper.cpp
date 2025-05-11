#include "TestPaper.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Instrument/Instrument.h"
#include <QDesktopWidget>
#include <QColorDialog>
#include <QGraphicsDropShadowEffect>

#include "../comm/GlobalData.h"
#include "../comm/Global.h"
#include <QProcess>
#include "src/main/subDialog/MyMessageBox.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

TestPaper::TestPaper(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    auto dao = AnalysisUIDao::instance();
    bool bResult;
    g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
    setWindowIcon(QIcon(":/images/buttonIcon/icon.png"));
    setAttribute(Qt::WA_ShowModal, true);
    Set_Item_Control_Array();
    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();
    int screenWidth = screen.width();
    int screenHeight = screen.height();
    move((screenWidth-this->width()) / 2, ((screenHeight-this->height()) / 2)-10);
    _instr = Instrument::instance();
    ui.label_52->setVisible(false);
    ui.label_53->setVisible(false);
    ui.label_56->setVisible(false);
    ui.label_57->setVisible(false);
    ui.label_58->setVisible(false);
    ui.lineEdit_height->setVisible(true);
    ui.groupBox_2 -> setVisible(false);
    ui.lineEdit_TestPaparLenght_2->setEnabled(false);
    connect(ui.pushButton_PickColor, &QPushButton::clicked, this, &TestPaper::color_slots_func);
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(QRegularExpression("^[0-9]\\d*$"), ui.lineEdit_Item_Number);
    ui.lineEdit_Item_Number->setValidator(validator);
    QRegularExpressionValidator* validator1 = new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_TestPaparLenght);
    ui.lineEdit_TestPaparLenght->setValidator(validator1);
    ui.lineEdit_height_percentage->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{1,2}"), ui.lineEdit_height_percentage));
    ui.lineEdit_paper_head_length->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-1]?[0-9]{1,2}|200"), ui.lineEdit_paper_head_length));
    ui.lineEdit_paper_gray_value->setValidator(new QRegularExpressionValidator(QRegularExpression("^([0-4][0-9]|50)$"), ui.lineEdit_paper_gray_value));
    ui.lineEdit_Left_Top_x->setValidator(new QRegularExpressionValidator(QRegularExpression("^(1[0-9]|[2-9][0-9]|1[0-4][0-9]|150)$"), ui.lineEdit_Left_Top_x));
    ui.lineEdit_LeftTop_y->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]*\\.[0-9]{2}$"), ui.lineEdit_LeftTop_y));
    ui.lineEdit_FuncPosition->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_FuncPosition));
    ui.lineEdit_FuncPosition_2->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_FuncPosition_2));
    ui.lineEdit_CutOff_Value->setValidator(new QRegularExpressionValidator(QRegularExpression("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"), ui.lineEdit_CutOff_Value));
    ui.lineEdit_CutOff_Position->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_CutOff_Position));
    ui.lineEdit_Position_1->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_1));
    ui.lineEdit_Position_2->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_2));
    ui.lineEdit_Position_3->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_3));
    ui.lineEdit_Position_4->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_4));
    ui.lineEdit_Position_5->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_5));
    ui.lineEdit_Position_6->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_6));
    ui.lineEdit_Position_7->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_7));
    ui.lineEdit_Position_8->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_8));
    ui.lineEdit_Position_9->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_9));
    ui.lineEdit_Position_10->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_10));
    ui.lineEdit_Position_11->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_11));
    ui.lineEdit_Position_12->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_12));
    ui.lineEdit_Position_13->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_13));
    ui.lineEdit_Position_14->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_14));
    ui.lineEdit_Position_15->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_15));
    ui.lineEdit_Position_16->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_16));
    ui.lineEdit_Position_17->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_17));
    ui.lineEdit_Position_18->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_18));
    ui.lineEdit_Position_19->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_19));
    ui.lineEdit_Position_20->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_20));
    ui.lineEdit_Position_21->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_21));
    ui.lineEdit_Position_22->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_22));
    ui.lineEdit_Position_23->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_23));
    ui.lineEdit_Position_24->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_24));
    ui.lineEdit_Position_25->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_25));
    ui.lineEdit_Position_26->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_26));
    ui.lineEdit_Position_27->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_27));
    ui.lineEdit_Position_28->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_28));
    ui.lineEdit_Position_29->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_29));
    ui.lineEdit_Position_30->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]+"), ui.lineEdit_Position_30));

    ui.label_68->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1112"));
    this->setWindowTitle(GlobalData::LoadLanguageInfo(g_language_type, "K1112"));
    ui.label_39->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1100"));//膜条名称：
    ui.label_37->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1129"));//项目数量：
    ui.label_46->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1101"));//货号
    ui.label_40->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1128"));//膜条总长度：
    ui.label_60->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1127"));//分析区百分比：
    ui.label_63->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1126"));//膜条头：
    ui.label_64->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1130"));//像素
    ui.label->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1125"));//次数：

    ui.label_75->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1705"));//次数：
    ui.label_70->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1706"));//次数：
    ui.label_71->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1707"));//次数：
    ui.label_72->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1708"));//次数：
    ui.label_73->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1709"));//次数：
    ui.label_74->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1710"));//次数：


    ui.label_51->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1124"));//阈值：
    ui.label_54->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1123"));//(<150)、    计算区间：
    ui.label_55->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1122"));//毫米对应像素：
    ui.label_66->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1121"));//颜色值：
    ui.checkBox_CutOff_2->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1120"));//是否有功能线：
    ui.label_42->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1119"));//功能条位置：
    ui.label_67->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1118"));//功能线阈值：
    ui.checkBox_CutOff->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1117"));//是否有CutOff线：
    ui.label_44->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1048"));//位置：
    ui.label_50->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1116"));//CutOff线阈值
    ui.pushButton_PickColor->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1114"));//选择：
    ui.pushButton_Set->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1115"));//设置：


    ui.label_31->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1131"));//项目名称：
    ui.label_32->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1132"));//空白：
    ui.label_38->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1115"));//位置：
    ui.label_47->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1133"));//判读规制：


    ui.label_34->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1131"));//项目名称：
    ui.label_33->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1132"));//空白：
    ui.label_61->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1115"));//位置：
    ui.label_48->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1133"));//判读规制：

    ui.label_36->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1131"));//项目名称：
    ui.label_35->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1132"));//空白：
    ui.label_62->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1115"));//位置：
    ui.label_49->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1133"));//判读规制：

    ui.pushButton_Save->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1038"));//判读规制：
    ui.pushButton_Cancel->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1134"));//判读规制：

    ui.label_55->setVisible(false);
    ui.lineEdit_Weight->setVisible(false);
    ui.label_41->setVisible(false);
    //GlobalData::LoadLanguageInfo(g_language_type, "K1090")

}
//connect(ui->colordlg,8QPushButton::clicked,this,8MyDialog::color slots func)
TestPaper::~TestPaper()
{
}

void TestPaper::Set_UI()
{
    bool bResult;
    int TotalNumber = 0;
    if (m_bModify == false)
        return;
    auto dao = AnalysisUIDao::instance();
    auto TestPaperQuery = dao->SelectTestPaper(m_strTestPaper_ID, &bResult);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1263"), MyMessageBox::Ok,"OK","");
        return;
    }
    QString SelectedRuleName = "";
    if (TestPaperQuery.next())
    {
        ui.lineEdit_TestPaparName->setText(TestPaperQuery.value("PaperName").toString());
        m_strCompany_ID = TestPaperQuery.value("Company_ID").toString();
        m_nTotalNumber = TestPaperQuery.value("TotalNumber").toInt();
        m_nItem_Number = TestPaperQuery.value("Item_Number").toInt();
        m_nNull_Number = TestPaperQuery.value("Null_Number").toInt();
        ui.lineEdit_Item_Number->setText(TestPaperQuery.value("Item_Number").toString());
        //        ui.lineEdit_Null_Number->setText(TestPaperQuery.value("Null_Number").toString());
        ui.lineEdit_TestPaparLenght->setText(TestPaperQuery.value("TestPaparLenght").toString());
        ui.lineEdit_FuncPosition->setText(TestPaperQuery.value("FuncPosition").toString());
        //        ui.lineEdit_TestAeaLenght->setText(TestPaperQuery.value("TestAeaLenght").toString());
        QString articleNo = TestPaperQuery.value("articleNo").toString();
        double rect_Analysis_x = TestPaperQuery.value("rect_Analysis.x").toDouble();
        double rect_Analysis_y = TestPaperQuery.value("rect_Analysis.y").toDouble();
        double rect_Analysis_width = TestPaperQuery.value("rect_Analysis.width").toDouble();
        double rect_Analysis_height = TestPaperQuery.value("rect_Analysis.height").toDouble();
        double analysis_height_percentage = TestPaperQuery.value("analysis_height_percentage").toDouble();
        double head_length = TestPaperQuery.value("head_length").toDouble();
        double cutoff_position = TestPaperQuery.value("cutoffPosition").toDouble();
        double cutoff_value = TestPaperQuery.value("cutoffValue").toDouble();
        //灰度值 判断阈值
        double fun_gray_value = TestPaperQuery.value("funGrayValue").toDouble();
        int isCutOff = TestPaperQuery.value("isCutOff").toInt();
        int left_judge_value = TestPaperQuery.value("left_judge_value").toInt();
        int isFun = TestPaperQuery.value("isFun").toInt();
        //int funGrayValue = TestPaperQuery.value("funGrayValue").toInt();
        QString BGRGB = TestPaperQuery.value("BGRGB").toString();


        int wave_pix_width = TestPaperQuery.value("wave_pix_width").toInt(); // INT DEFAULT 17;
        int wave_pix_width_max = TestPaperQuery.value("wave_pix_width_max").toInt();// INT DEFAULT 24;
        int wave_pix_width_min = TestPaperQuery.value("wave_pix_width_min").toInt();// INT DEFAULT 10;

        int background_values = TestPaperQuery.value("background_values").toInt();// INT DEFAULT 100;
        double zero_value_coefficient = TestPaperQuery.value("zero_value_coefficient").toDouble();// DOUBLE DEFAULT 0.3;
        int bg_difference = TestPaperQuery.value("bg_difference").toInt();// INT DEFAULT 25;


        ui.lineEdit_wave_pix_width->setText(QString::number(wave_pix_width));
        ui.lineEdit_wave_pix_width_max->setText(QString::number(wave_pix_width_max));
        ui.lineEdit_wave_pix_width_min->setText(QString::number(wave_pix_width_min));
        ui.lineEdit_background_values->setText(QString::number(background_values));
        ui.lineEdit_zero_value_coefficient->setText(QString::number(zero_value_coefficient));
        ui.lineEdit_bg_difference->setText(QString::number(bg_difference));



        ui.lineEdit_Left_Top_x->setText(QString::number(rect_Analysis_x));
        ui.lineEdit_LeftTop_y->setText(QString::number(rect_Analysis_y));
        ui.lineEdit_Weight->setText(QString::number(rect_Analysis_width));
        ui.lineEdit_height->setText(QString::number(rect_Analysis_height));
        ui.lineEdit_height_percentage->setText(QString::number(analysis_height_percentage));
        ui.lineEdit_paper_head_length->setText(QString::number(head_length));
        ui.lineEdit_Article_No->setText(articleNo);
        ui.lineEdit_CutOff_Position->setText(QString::number(cutoff_position));
        ui.lineEdit_CutOff_Value->setText(QString::number(cutoff_value));
        ui.lineEdit_paper_gray_value->setText(QString::number(left_judge_value));
        ui.lineEdit_FuncPosition_2->setText(QString::number(fun_gray_value));
        ui.lineEdit_TestPaparLenght_2->setText(BGRGB);
        if (isFun == 1)
        {
            ui.checkBox_CutOff_2->setChecked(true);
            CutOffCheckBoxUpdateUi(2);
        }
        else
        {
            ui.checkBox_CutOff_2->setChecked(false);
            CutOffCheckBoxUpdateUi(0);
        }

        if (isCutOff == 1)
        {
            ui.checkBox_CutOff->setChecked(true);
            CutOffCheckBoxUpdateUi(2);
        }
        else
        {
            ui.checkBox_CutOff->setChecked(false);
            CutOffCheckBoxUpdateUi(0);
        }
        //checkBox_CutOff
        //ui.lineEdit_FuncPosition_Article..lineEdit_Article_No->setText()
        //ui.lineEdit_Article_No->
    }
    on_pushButton_Set_clicked();
    auto TestPaperItemQuery = dao->SelectTestPaperItems(m_strTestPaper_ID, &bResult);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1263"), MyMessageBox::Ok,"OK","");
        return;
    }

    int nPositionNo = 0;
    TestPaper_Item testPaper_Item;
    while (TestPaperItemQuery.next())
    {
        int rule_id = TestPaperItemQuery.value("RulesId").toInt();
        testPaper_Item.isNullArea = TestPaperItemQuery.value("IsNull").toInt();
        testPaper_Item.nPostionNo = TestPaperItemQuery.value("PositionNo").toInt();
        testPaper_Item.strItemName = TestPaperItemQuery.value("itemName").toString();
        testPaper_Item.judgerule = TestPaperItemQuery.value("RulesId").toInt();
        testPaper_Item.position = TestPaperItemQuery.value("position").toDouble();
        Set_Control_Value(testPaper_Item);
    }
}

void TestPaper::Set_Item_Control_Array()
{
    for (int i = 1; i <= 30; i++)
    {
        switch (i)
        {
        case 1:
            m_Item_Control_Array[i].label = ui.label_1;
            m_Item_Control_Array[i].checkBox = ui.checkBox_1;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_1;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_1;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_1;
            //comboBoxRulesName_1
            break;
        case 2:
            m_Item_Control_Array[i].label = ui.label_2;
            m_Item_Control_Array[i].checkBox = ui.checkBox_2;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_2;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_2;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_2;
            break;
        case 3:
            m_Item_Control_Array[i].label = ui.label_3;
            m_Item_Control_Array[i].checkBox = ui.checkBox_3;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_3;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_3;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_3;
            break;
        case 4:
            m_Item_Control_Array[i].label = ui.label_4;
            m_Item_Control_Array[i].checkBox = ui.checkBox_4;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_4;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_4;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_4;
            break;
        case 5:
            m_Item_Control_Array[i].label = ui.label_5;
            m_Item_Control_Array[i].checkBox = ui.checkBox_5;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_5;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_5;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_5;
            break;
        case 6:
            m_Item_Control_Array[i].label = ui.label_6;
            m_Item_Control_Array[i].checkBox = ui.checkBox_6;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_6;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_6;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_6;
            break;
        case 7:
            m_Item_Control_Array[i].label = ui.label_7;
            m_Item_Control_Array[i].checkBox = ui.checkBox_7;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_7;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_7;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_7;
            break;
        case 8:
            m_Item_Control_Array[i].label = ui.label_8;
            m_Item_Control_Array[i].checkBox = ui.checkBox_8;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_8;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_8;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_8;
            break;
        case 9:
            m_Item_Control_Array[i].label = ui.label_9;
            m_Item_Control_Array[i].checkBox = ui.checkBox_9;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_9;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_9;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_9;
            break;
        case 10:
            m_Item_Control_Array[i].label = ui.label_10;
            m_Item_Control_Array[i].checkBox = ui.checkBox_10;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_10;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_10;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_10;
            break;
        case 11:
            m_Item_Control_Array[i].label = ui.label_11;
            m_Item_Control_Array[i].checkBox = ui.checkBox_11;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_11;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_11;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_11;
            break;
        case 12:
            m_Item_Control_Array[i].label = ui.label_12;
            m_Item_Control_Array[i].checkBox = ui.checkBox_12;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_12;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_12;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_12;
            break;
        case 13:
            m_Item_Control_Array[i].label = ui.label_13;
            m_Item_Control_Array[i].checkBox = ui.checkBox_13;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_13;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_13;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_13;
            break;
        case 14:
            m_Item_Control_Array[i].label = ui.label_14;
            m_Item_Control_Array[i].checkBox = ui.checkBox_14;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_14;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_14;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_14;
            break;
        case 15:
            m_Item_Control_Array[i].label = ui.label_15;
            m_Item_Control_Array[i].checkBox = ui.checkBox_15;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_15;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_15;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_15;
            break;
        case 16:
            m_Item_Control_Array[i].label = ui.label_16;
            m_Item_Control_Array[i].checkBox = ui.checkBox_16;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_16;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_16;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_16;
            break;
        case 17:
            m_Item_Control_Array[i].label = ui.label_17;
            m_Item_Control_Array[i].checkBox = ui.checkBox_17;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_17;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_17;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_17;
            break;
        case 18:
            m_Item_Control_Array[i].label = ui.label_18;
            m_Item_Control_Array[i].checkBox = ui.checkBox_18;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_18;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_18;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_18;
            break;
        case 19:
            m_Item_Control_Array[i].label = ui.label_19;
            m_Item_Control_Array[i].checkBox = ui.checkBox_19;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_19;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_19;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_19;
            break;
        case 20:
            m_Item_Control_Array[i].label = ui.label_20;
            m_Item_Control_Array[i].checkBox = ui.checkBox_20;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_20;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_20;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_20;
            break;
        case 21:
            m_Item_Control_Array[i].label = ui.label_21;
            m_Item_Control_Array[i].checkBox = ui.checkBox_21;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_21;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_21;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_21;
            break;
        case 22:
            m_Item_Control_Array[i].label = ui.label_22;
            m_Item_Control_Array[i].checkBox = ui.checkBox_22;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_22;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_22;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_22;
            break;
        case 23:
            m_Item_Control_Array[i].label = ui.label_23;
            m_Item_Control_Array[i].checkBox = ui.checkBox_23;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_23;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_23;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_23;
            break;
        case 24:
            m_Item_Control_Array[i].label = ui.label_24;
            m_Item_Control_Array[i].checkBox = ui.checkBox_24;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_24;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_24;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_24;
            break;
        case 25:
            m_Item_Control_Array[i].label = ui.label_25;
            m_Item_Control_Array[i].checkBox = ui.checkBox_25;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_25;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_25;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_25;
            break;
        case 26:
            m_Item_Control_Array[i].label = ui.label_26;
            m_Item_Control_Array[i].checkBox = ui.checkBox_26;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_26;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_26;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_26;
            break;
        case 27:
            m_Item_Control_Array[i].label = ui.label_27;
            m_Item_Control_Array[i].checkBox = ui.checkBox_27;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_27;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_27;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_27;
            break;
        case 28:
            m_Item_Control_Array[i].label = ui.label_28;
            m_Item_Control_Array[i].checkBox = ui.checkBox_28;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_28;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_28;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_28;
            break;
        case 29:
            m_Item_Control_Array[i].label = ui.label_29;
            m_Item_Control_Array[i].checkBox = ui.checkBox_29;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_29;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_29;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_29;
            break;
        case 30:
            m_Item_Control_Array[i].label = ui.label_30;
            m_Item_Control_Array[i].checkBox = ui.checkBox_30;
            m_Item_Control_Array[i].lineEdit_Name = ui.lineEdit_Name_30;
            m_Item_Control_Array[i].combo_box_rule = ui.comboBoxRulesName_30;
            m_Item_Control_Array[i].lineEdit_Position = ui.lineEdit_Position_30;
            break;
        default:
            break;
        }
    }
}

void TestPaper::on_pushButton_Set_clicked()
{
    m_nNull_Number = 0;// = ui.lineEdit_Null_Number->text().toInt();
    m_nItem_Number = ui.lineEdit_Item_Number->text().toInt();
    m_nTotalNumber = m_nNull_Number + m_nItem_Number;

    QString strItem_Number = QString::number(m_nItem_Number);
    if (m_nItem_Number == 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1593"), MyMessageBox::Ok, "OK", "");
        return ;
    }

    Set_Controls_visible();
}

bool TestPaper::CheckInput()
{
    QString strName = ui.lineEdit_TestPaparName->text();
    if (strName.length() == 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1282"), MyMessageBox::Ok,"OK","");
        return false;
    }
    QString strTotalNumber = QString::number(m_nTotalNumber);
    QString strNull_Number = QString::number(m_nNull_Number);
    QString strItem_Number = QString::number(m_nItem_Number);
    if (m_nItem_Number == 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1593"), MyMessageBox::Ok,"OK","");
        return false;
    }
    QString strTestPaparLenght = ui.lineEdit_TestPaparLenght->text();
    if (strTestPaparLenght.length() == 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1281"), MyMessageBox::Ok,"OK","");
        return false;
    }

    QString strFuncPosition = ui.lineEdit_FuncPosition->text();
    if (strFuncPosition.length() == 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1280"), MyMessageBox::Ok,"OK","");
        return false;
    }

    //QString strTestAeaLenght = ui.lineEdit_TestAeaLenght->text();
    //if (strTestAeaLenght.length() == 0)
    //{
    //	QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "请输入功能条至最末项目的长度！", QMessageBox::Ok);
    //	return false;
    //}

    QString strIsNull;
    QString strPositionNo;
    TestPaper_Item testPaper_Item_Array[31];

    int nNullAreaCount = 0;

    for (int i = 1; i <= m_nTotalNumber; i++)
    {
        Set_TestPaper_Item(testPaper_Item_Array[i], i, m_Item_Control_Array[i].checkBox, m_Item_Control_Array[i].lineEdit_Name, m_Item_Control_Array[i].combo_box_rule, m_Item_Control_Array[i].lineEdit_Position);
        strName = testPaper_Item_Array[i].strItemName;
        strName = strName.remove("\n");
        strIsNull = QString::number(testPaper_Item_Array[i].isNullArea);
        if (testPaper_Item_Array[i].isNullArea == true)
        {
            nNullAreaCount++;
        }
        if (testPaper_Item_Array[i].isNullArea == false)
        {
            if (strName.length() == 0)
            {
                MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1279"), MyMessageBox::Ok,"OK","");
                return false;
            }
        }
    }
    //if (nNullAreaCount != m_nNull_Number)
    //{
    //	QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "输入的空白数量与设置的空白数量不符！", QMessageBox::Ok);
    //	return false;
    //}
    return true;
}

void TestPaper::color_slots_func()
{
    bool ok;
    QColorDialog ColorDlg(Qt::red, this); // 创建对象
    ColorDlg.setOption(QColorDialog::ShowAlphaChannel); //设置ALPHA选项
    ColorDlg.setWindowTitle("选择实验膜条显示颜色");
    ColorDlg.exec();
    QColor color = ColorDlg.currentColor();
    //QString sz = QString("#%1%2%3").arg(QString::number(color.red(),16)).arg(QString::number(color.green(),16)).arg(QString::number(color.blue(),16));
    QString sz = QString("%1").arg(color.name());
    ui.lineEdit_TestPaparLenght_2->setText(sz);
}

void TestPaper::on_pushButton_Save_clicked()
{
    on_pushButton_Set_clicked();
    if (CheckInput() == false)
        return;

    if(Save_TestPaper_Parameters() == false)
        return;

    if (Save_TestPaper_Items() == false)
        return;

    emit SetRefresh(true);
    this->close();

    m_strMachineUID = Global::g_machine_no;

    bool bResult;
    QString sql1_log = QString("insert into t_operate_log(model_name,machine_id,operate_content,user_name)values('%1','%2','%3','%4')").arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1663")).arg(m_strMachineUID).arg("保存").arg(GlobalData::getLoginName1());
    auto dao = AnalysisUIDao::instance();
    dao->SelectRecord(&bResult, sql1_log);





    //QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), "操作完成！", QMessageBox::Ok);
    auto ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1259"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1278"), MyMessageBox::Ok| MyMessageBox::No,tr("YES"), tr("NO"));
    if (ret == MyMessageBox::No)
    {
    }
    else
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
}

bool TestPaper::Save_TestPaper_Parameters()
{
    QString strName = ui.lineEdit_TestPaparName->text();
    QString strTotalNumber = QString::number(m_nTotalNumber);
    //QString strNull_Number = QString::number(m_nNull_Number);
    QString strItem_Number = QString::number(m_nItem_Number);
    QString strTestPaparLenght = ui.lineEdit_TestPaparLenght->text();
    QString strFuncPosition = ui.lineEdit_FuncPosition->text();
    //	QString strTestAeaLenght = ui.lineEdit_TestAeaLenght->text();
    QString strArticleNo = ui.lineEdit_Article_No->text();
    QString rect_Analysis_x = ui.lineEdit_Left_Top_x->text(); //->setText(QString::number(rect_Analysis_x));
    QString rect_Analysis_y = ui.lineEdit_LeftTop_y->text(); //->setText(QString::number(rect_Analysis_y));
    QString rect_Analysis_width = ui.lineEdit_Weight->text(); //->setText(QString::number(rect_Analysis_width));
    QString rect_Analysis_height = ui.lineEdit_height->text(); //->setText(QString::number(rect_Analysis_height));
    QString analysis_height_percentage = ui.lineEdit_height_percentage->text();//->setText(QString::number(analysis_height_percentage));
    QString head_length = ui.lineEdit_paper_head_length->text(); //->setText(QString::number(head_length));
    QString cut_off_position = ui.lineEdit_CutOff_Position->text();
    QString cut_off_value = ui.lineEdit_CutOff_Value->text();
    QString BGRGB = ui.lineEdit_TestPaparLenght_2->text();

    bool ok;
    int value = analysis_height_percentage.toInt(&ok);
    if (ok)
    {
        if (value > 0)
        {
        }else
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1127") + GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1313"), MyMessageBox::Ok, "OK", "");
            return false;
        }
    }

    QString wave_pix_width = ui.lineEdit_wave_pix_width->text();
    QString wave_pix_width_max = ui.lineEdit_wave_pix_width_max->text();
    QString wave_pix_width_min = ui.lineEdit_wave_pix_width_min->text();
    QString background_values = ui.lineEdit_background_values->text();
    QString zero_value_coefficient = ui.lineEdit_zero_value_coefficient->text();
    QString bg_difference = ui.lineEdit_bg_difference->text();

    if (rect_Analysis_y.toDouble() > 3.0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1277"), MyMessageBox::Ok,"OK","");
        return false;
    }

    QString funGrayValue = ui.lineEdit_FuncPosition_2->text();

    if (cut_off_value.size() == 0)
    {
        cut_off_value = "0";
    }
    int left_judge_value = ui.lineEdit_paper_gray_value->text().toInt();

    int isCutOff = ui.checkBox_CutOff->checkState();
    int isFun = ui.checkBox_CutOff_2->checkState();

    if (isFun == 2)
    {
        isFun = 1;
    }
    else
    {
        isFun = 0;
    }

    if (isCutOff == 2)
    {
        isCutOff = 1;
    }
    else
    {
        isCutOff = 0;
    }

    auto dao = AnalysisUIDao::instance();
    bool bResult;
    QString strTestPaper_ID = dao->GetTestPaper_ID(m_strCompany_ID, strName, &bResult);
    QString max_sort_id = dao->GetTestPaper_sort_max(m_strCompany_ID, strName, &bResult);
    int sort_id = 0;
    sort_id = max_sort_id.toInt();
    sort_id += 1;
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1272"), MyMessageBox::Ok,"OK","");
        return false;
    }

    if (strTestPaper_ID != "")
    {
        if (strTestPaper_ID != m_strTestPaper_ID)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1276"), MyMessageBox::Ok,"OK","");
            return false;
        }
    }

    if (m_bModify == false)
    {
        bResult = dao->InsertTestPaper(strName, m_strCompany_ID, strTotalNumber, strItem_Number, strTestPaparLenght, strFuncPosition, strArticleNo,
                                       rect_Analysis_x, rect_Analysis_y, rect_Analysis_width, rect_Analysis_height, analysis_height_percentage,
                                       head_length, isCutOff, cut_off_position, cut_off_value, left_judge_value, sort_id, BGRGB, funGrayValue.toInt(),isFun, wave_pix_width, wave_pix_width_max, wave_pix_width_min
                                       ,background_values, zero_value_coefficient, bg_difference);

        if (bResult == false)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1267"), MyMessageBox::Ok,"OK","");
            return false;
        }
    }
    else
    {
        bResult = dao->UpdateTestPaper(m_strTestPaper_ID, strName, m_strCompany_ID, strTotalNumber, strItem_Number,
                                       strTestPaparLenght, strFuncPosition, strArticleNo, rect_Analysis_x, rect_Analysis_y, rect_Analysis_width, rect_Analysis_height,
                                       analysis_height_percentage, head_length, isCutOff, cut_off_position,
                                       cut_off_value, left_judge_value, sort_id, BGRGB, funGrayValue.toInt(),isFun, wave_pix_width, wave_pix_width_max, wave_pix_width_min, background_values, zero_value_coefficient, bg_difference);


        if (bResult == false)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1269"), MyMessageBox::Ok,"OK","");
            return false;
        }
    }
    return true;
}

bool TestPaper::Save_TestPaper_Items()
{
    TestPaper_Item testPaper_Item_Array[31];
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    if (m_bModify == true)
    {
        bResult = dao->DeleteTestPaperItems(m_strTestPaper_ID);
        if (bResult == false)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1268"), MyMessageBox::Ok,"OK","");
            return false;
        }
    }
    QString strID;
    QString strIsNull;
    QString strName;
    QString strTestPaper_ID;
    QString strPositionNo;
    if (m_bModify == true)
    {
        strTestPaper_ID = m_strTestPaper_ID;
    }
    else
    {
        strTestPaper_ID = dao->GetTestPaper_ID(m_strCompany_ID,ui.lineEdit_TestPaparName->text(), &bResult);
    }
    int RulesId = 1;
    //QString rule_name = ui.comboBoxRulesName->currentText();
    //QMap<QString, int>::iterator iter = m_RulesName.begin();
    //while (iter != m_RulesName.end())
    //{
    //	if (iter.key() == rule_name)
    //	{
    //		RulesId = iter.value();
    //	}
    //	iter++;
    //}

    for (int i = 1; i <= m_nTotalNumber; i++)
    {
        Set_TestPaper_Item(testPaper_Item_Array[i], i, m_Item_Control_Array[i].checkBox, m_Item_Control_Array[i].lineEdit_Name, m_Item_Control_Array[i].combo_box_rule, m_Item_Control_Array[i].lineEdit_Position);
        strPositionNo = QString::number(testPaper_Item_Array[i].nPostionNo);
        strName = testPaper_Item_Array[i].strItemName;
        strName = strName.remove('\n');
        strIsNull = QString::number(testPaper_Item_Array[i].isNullArea);
        if (strTestPaper_ID.length() == 1)
        {
            strID = "00" + strTestPaper_ID;
        }
        if (strTestPaper_ID.length() == 2)
        {
            strID = "0" + strTestPaper_ID;
        }
        if (strPositionNo.length() == 2)
        {
            strID += strPositionNo;
        }
        else
        {
            strID += ("0" + strPositionNo);
        }
        QString rule_name = m_Item_Control_Array[i].combo_box_rule->currentText();
        QMap<QString, int>::iterator iter = m_RulesName.begin();
        while (iter != m_RulesName.end())
        {
            if (iter.key() == rule_name)
            {
                RulesId = iter.value();
            }
            iter++;
        }

        QString position = m_Item_Control_Array[i].lineEdit_Position->text();
        if (position != "")
        {
            bResult = dao->InsertTestPaperItem(RulesId, strID, strIsNull, strName, strTestPaper_ID, position, strPositionNo);
            if (bResult == false)
            {
                MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1267"), MyMessageBox::Ok, "OK", "");
                return false;
            }
        }

    }
    return true;
}

void TestPaper::Set_Controls_visible()
{
    auto dao = AnalysisUIDao::instance();
    bool bResult = true;

    if (m_nTotalNumber >= 1)
    {
        ui.label_31->setVisible(true);
        ui.label_32->setVisible(true);
    }
    else
    {
        ui.label_31->setVisible(false);
        ui.label_32->setVisible(false);
    }

    if (m_nTotalNumber >= 11)
    {
        ui.label_33->setVisible(true);
        ui.label_34->setVisible(true);
        ui.label_48->setVisible(true);
        ui.label_61->setVisible(true);
    }
    else
    {
        ui.label_33->setVisible(false);
        ui.label_34->setVisible(false);
        ui.label_48->setVisible(false);
        ui.label_61->setVisible(false);
    }

    if (m_nTotalNumber >= 21)
    {
        ui.label_35->setVisible(true);
        ui.label_36->setVisible(true);
        ui.label_49->setVisible(true);
        ui.label_62->setVisible(true);
    }
    else
    {
        ui.label_35->setVisible(false);
        ui.label_36->setVisible(false);
        ui.label_49->setVisible(false);
        ui.label_62->setVisible(false);
    }
    for (int i = 1; i <= 30; i++)
    {
        if (m_nTotalNumber >= i)
        {
            m_Item_Control_Array[i].label->setVisible(true);
            m_Item_Control_Array[i].checkBox->setVisible(true);
            m_Item_Control_Array[i].lineEdit_Name->setVisible(true);
            m_Item_Control_Array[i].combo_box_rule->setVisible(true);
            m_Item_Control_Array[i].lineEdit_Position->setVisible(true);
            //添加下拉框内容
            auto m_RuleNameQuery = dao->SelectRulues(&bResult);
            if (bResult == false)
            {
                MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1275"), MyMessageBox::Ok,"OK","");
                return;
            }
            int row = 0;
            while (m_RuleNameQuery.next())
            {
                QString itemName = m_RuleNameQuery.value("RuleName").toString();
                int ruleId = m_RuleNameQuery.value("pkid").toInt();
                //m_RulesName.insert(itemName, ruleId);
                m_RulesName.insert(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), itemName), ruleId);
                m_Item_Control_Array[i].combo_box_rule->addItem(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), itemName));//itemName);
                row++;
            }
        }
        else
        {
            m_Item_Control_Array[i].label->setVisible(false);
            m_Item_Control_Array[i].checkBox->setVisible(false);
            m_Item_Control_Array[i].lineEdit_Name->setVisible(false);
            m_Item_Control_Array[i].combo_box_rule->setVisible(false);
            m_Item_Control_Array[i].lineEdit_Position->setVisible(false);
        }
    }
}

void TestPaper::on_checkBox_1_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[1].lineEdit_Name);
}

void TestPaper::on_checkBox_2_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[2].lineEdit_Name);
}

void TestPaper::on_checkBox_3_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[3].lineEdit_Name);
}

void TestPaper::on_checkBox_4_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[4].lineEdit_Name);
}

void TestPaper::on_checkBox_5_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[5].lineEdit_Name);
}

void TestPaper::on_checkBox_6_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[6].lineEdit_Name);
}

void TestPaper::on_checkBox_7_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[7].lineEdit_Name);
}

void TestPaper::on_checkBox_8_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[8].lineEdit_Name);
}

void TestPaper::on_checkBox_9_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[9].lineEdit_Name);
}

void TestPaper::on_checkBox_10_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[10].lineEdit_Name);
}

void TestPaper::on_checkBox_11_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[11].lineEdit_Name);
}

void TestPaper::on_checkBox_12_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[12].lineEdit_Name);
}

void TestPaper::on_checkBox_13_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[13].lineEdit_Name);
}

void TestPaper::on_checkBox_14_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[14].lineEdit_Name);
}

void TestPaper::on_checkBox_15_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[15].lineEdit_Name);
}

void TestPaper::on_checkBox_16_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[16].lineEdit_Name);
}

void TestPaper::on_checkBox_17_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[17].lineEdit_Name);
}


void TestPaper::on_checkBox_18_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[18].lineEdit_Name);

}

void TestPaper::on_checkBox_19_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[19].lineEdit_Name);
}

void TestPaper::on_checkBox_20_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[20].lineEdit_Name);
}

void TestPaper::on_checkBox_21_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[21].lineEdit_Name);

}

void TestPaper::on_checkBox_22_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[22].lineEdit_Name);

}

void TestPaper::on_checkBox_23_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[23].lineEdit_Name);
}

void TestPaper::on_checkBox_24_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[24].lineEdit_Name);

}

void TestPaper::on_checkBox_25_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[25].lineEdit_Name);
}

void TestPaper::on_checkBox_26_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[26].lineEdit_Name);
}


void TestPaper::on_checkBox_27_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[27].lineEdit_Name);
}

void TestPaper::on_checkBox_28_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[28].lineEdit_Name);
}

void TestPaper::on_checkBox_29_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[29].lineEdit_Name);
}

void TestPaper::on_checkBox_30_stateChanged(int state)
{
    Set_checkBox_stateChanged(state, m_Item_Control_Array[1].lineEdit_Name);
}

void TestPaper::CutOffCheckBoxUpdateUi(int state) {
    //if (state == 2)
    //{
    //	//ui.checkBox_CutOff->setVisible(true);
    //	ui.label_50->setVisible(false);
    //	ui.lineEdit_CutOff_Value->setVisible(false);
    //	ui.label_44->setVisible(true);
    //	ui.lineEdit_CutOff_Position->setVisible(true);
    //	ui.label_45->setVisible(true);
    //}

    //if (state == 0)
    //{
    //	//ui.checkBox_CutOff->setVisible(true);
    //	ui.label_50->setVisible(true);
    //	ui.lineEdit_CutOff_Value->setVisible(true);
    //	ui.label_44->setVisible(false);
    //	ui.lineEdit_CutOff_Position->setVisible(false);
    //	ui.label_45->setVisible(false);
    //}
}

void TestPaper::on_checkBox_CutOff_stateChanged(int state)
{
    //Set_checkBox_stateChanged(state, m_Item_Control_Array[30].lineEdit_Name);
    //勾选上
    CutOffCheckBoxUpdateUi(state);
}

void TestPaper::Set_checkBox_stateChanged(int state, QLineEdit * lineEdit_Name)
{
    if (state == Qt::Checked) // "选中"
    {
        lineEdit_Name->setText("");
        lineEdit_Name->setEnabled(false);
    }
    else
    {
        lineEdit_Name->setEnabled(true);
    }
}

void TestPaper::Set_Control_Value(TestPaper_Item testPaper_Item) 
{
    if (testPaper_Item.isNullArea == false)
    {
        m_Item_Control_Array[testPaper_Item.nPostionNo].checkBox->setChecked(false);
        m_Item_Control_Array[testPaper_Item.nPostionNo].lineEdit_Name->setText(testPaper_Item.strItemName);
        bool bResult = true;
        auto dao = AnalysisUIDao::instance();
        //填充规制下拉框
        QString itemName;
        int ruleId;
        //DB中取Testitems表数据
        //auto dao = AnalysisUIDao::instance();
        auto m_RuleNameQuery = dao->SelectRulues(&bResult);
        if (bResult == false)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1275"), MyMessageBox::Ok,"OK","");
            return;
        }
        //int row = 0;
        //while (m_RuleNameQuery.next())
        //{
        //	itemName = m_RuleNameQuery.value("RuleName").toString();
        //	ruleId = m_RuleNameQuery.value("pkid").toInt();
        //	m_RulesName.insert(itemName, ruleId);
        //	m_Item_Control_Array[testPaper_Item.nPostionNo].combo_box_rule->addItem(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), itemName));//itemName); //
        //	//ui.comboBoxRulesName->addItem(itemName); //
        //	//ui.tableWidget_Rule->insertRow(row);
        //	//addRuleContent(row, 0, itemName);
        //	row++;
        //}
        QString SelectedRuleName = "";
        QMap<QString, int>::iterator iter = m_RulesName.begin();
        while (iter != m_RulesName.end())
        {
            if (iter.value() == testPaper_Item.judgerule)
            {
                SelectedRuleName = iter.key();
            }
            iter++;
        }
        m_Item_Control_Array[testPaper_Item.nPostionNo].combo_box_rule->setCurrentText(SelectedRuleName);

        m_Item_Control_Array[testPaper_Item.nPostionNo].lineEdit_Position->setText(QString::number(testPaper_Item.position));

    }
    else
    {
        m_Item_Control_Array[testPaper_Item.nPostionNo].checkBox->setChecked(true);
        m_Item_Control_Array[testPaper_Item.nPostionNo].lineEdit_Name->setText("");
    }
}

void TestPaper::Set_TestPaper_Item(TestPaper_Item& testPaper_Item,int nPostionNo,QCheckBox *checkBox,QLineEdit *lineEdit_Name, QComboBox * combo_box_rule,QLineEdit *lineEdit_Position)
{
    if (checkBox->isChecked())
    {
        testPaper_Item.isNullArea = true;
        testPaper_Item.nPostionNo = nPostionNo;
        testPaper_Item.strItemName = "";
        testPaper_Item.position = 0;
    }
    else
    {
        testPaper_Item.isNullArea = false;
        testPaper_Item.nPostionNo = nPostionNo;
        testPaper_Item.strItemName = lineEdit_Name->text();
        testPaper_Item.position = lineEdit_Position->text().toDouble();
    }
}


void TestPaper::on_pushButton_Cancel_clicked() 
{
    this->close();
}












