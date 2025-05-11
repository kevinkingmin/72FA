#include "SelfCheckResultShowDialog.h"
#include "src/comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

SelfCheckResultShowDialog::SelfCheckResultShowDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    setWindowModality(Qt::WindowModal);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
    //K1565

    ui.label->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1565"));
    ui.pushButton->setText(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
    this->setWindowTitle(GlobalData::LoadLanguageInfo(g_language_type, "K1565"));
    ShowSelfCheckInfo();
}

SelfCheckResultShowDialog::~SelfCheckResultShowDialog()
{
}

void SelfCheckResultShowDialog::ShowSelfCheckInfo()
{
    QString sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1259");//"成功";
    QString sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1679");//"失败";


    ui.checkBox->setVisible(true);
    ui.checkBox->setText("关闭阀" + sz1);//"成功");
    ui.checkBox->setChecked(true);
    ui.checkBox->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //设定前景颜色，就是字体颜色


    ui.checkBox_2->setVisible(true);
    ui.checkBox_2->setText("关闭摇床加热" + sz1);
    ui.checkBox_2->setChecked(true);
    ui.checkBox_2->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //设定前景颜色，就是字体颜色


    ui.checkBox_3->setVisible(true);
    ui.checkBox_3->setText("打开指示灯" + sz1);//"成功");
    ui.checkBox_3->setChecked(true);
    ui.checkBox_3->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //设定前景颜色，就是字体颜色


    ui.checkBox_4->setVisible(true);
    ui.checkBox_4->setText("关闭报警指示灯" + sz1);//"成功");
    ui.checkBox_4->setChecked(true);
    ui.checkBox_4->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //设定前景颜色，就是字体颜色

    ui.checkBox_5->setVisible(true);
    ui.checkBox_5->setText("关闭背光灯" + sz1);//"成功");
    ui.checkBox_5->setChecked(true);
    ui.checkBox_5->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //设定前景颜色，就是字体颜色


    ui.checkBox_6->setVisible(true);
    ui.checkBox_6->setText("关闭蜂鸣器" + sz1);//"成功");
    ui.checkBox_6->setChecked(true);
    ui.checkBox_6->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //设定前景颜色，就是字体颜色


    ui.checkBox_7->setVisible(true);
    ui.checkBox_7->setText("XYZ电机初始化" + sz1);//"成功");
    ui.checkBox_7->setChecked(true);
    ui.checkBox_7->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //设定前景颜色，就是字体颜色


    ui.checkBox_8->setVisible(true);
    ui.checkBox_8->setText("柱塞泵电机初始化" + sz1);//"成功");
    ui.checkBox_8->setChecked(true);
    ui.checkBox_8->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //设定前景颜色，就是字体颜色

    ui.checkBox_9->setVisible(true);
    ui.checkBox_9->setText("摇床电机初始化" + sz1);//"成功");
    ui.checkBox_9->setChecked(true);
    ui.checkBox_9->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //设定前景颜色，就是字体颜色

    ui.checkBox_10->setVisible(true);
    ui.checkBox_10->setText("扫码器自检" + sz1);//"成功");
    ui.checkBox_10->setChecked(true);
    ui.checkBox_10->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //设定前景颜色，就是字体颜色

    ui.checkBox_11->setVisible(true);
    ui.checkBox_11->setText("扫码成功");
    ui.checkBox_11->setChecked(true);
    ui.checkBox_11->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //设定前景颜色，就是字体颜色

    ui.checkBox_12->setVisible(true);
    ui.checkBox_12->setText("相机自检成功");
    ui.checkBox_12->setChecked(true);
    ui.checkBox_12->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //设定前景颜色，就是字体颜色

    ui.label->setStyleSheet("color:rgb(111, 111, 111);font:19pt;黑体;");
    //ui.label->setStyleSheet("background-color: rgb(111, 111, 111); color: rgb(222, 222, 222);font: 75 30pt;\"黑体\";");
    //ui.label->setFixedSize(135, 200);
    //ui.label->setScaledContents(true);
}

void SelfCheckResultShowDialog::on_pushButton_clicked()
{
    close();
}
