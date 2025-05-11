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
    QString sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1259");//"�ɹ�";
    QString sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1679");//"ʧ��";


    ui.checkBox->setVisible(true);
    ui.checkBox->setText("�رշ�" + sz1);//"�ɹ�");
    ui.checkBox->setChecked(true);
    ui.checkBox->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //�趨ǰ����ɫ������������ɫ


    ui.checkBox_2->setVisible(true);
    ui.checkBox_2->setText("�ر�ҡ������" + sz1);
    ui.checkBox_2->setChecked(true);
    ui.checkBox_2->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //�趨ǰ����ɫ������������ɫ


    ui.checkBox_3->setVisible(true);
    ui.checkBox_3->setText("��ָʾ��" + sz1);//"�ɹ�");
    ui.checkBox_3->setChecked(true);
    ui.checkBox_3->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //�趨ǰ����ɫ������������ɫ


    ui.checkBox_4->setVisible(true);
    ui.checkBox_4->setText("�رձ���ָʾ��" + sz1);//"�ɹ�");
    ui.checkBox_4->setChecked(true);
    ui.checkBox_4->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //�趨ǰ����ɫ������������ɫ

    ui.checkBox_5->setVisible(true);
    ui.checkBox_5->setText("�رձ����" + sz1);//"�ɹ�");
    ui.checkBox_5->setChecked(true);
    ui.checkBox_5->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //�趨ǰ����ɫ������������ɫ


    ui.checkBox_6->setVisible(true);
    ui.checkBox_6->setText("�رշ�����" + sz1);//"�ɹ�");
    ui.checkBox_6->setChecked(true);
    ui.checkBox_6->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //�趨ǰ����ɫ������������ɫ


    ui.checkBox_7->setVisible(true);
    ui.checkBox_7->setText("XYZ�����ʼ��" + sz1);//"�ɹ�");
    ui.checkBox_7->setChecked(true);
    ui.checkBox_7->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //�趨ǰ����ɫ������������ɫ


    ui.checkBox_8->setVisible(true);
    ui.checkBox_8->setText("�����õ����ʼ��" + sz1);//"�ɹ�");
    ui.checkBox_8->setChecked(true);
    ui.checkBox_8->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //�趨ǰ����ɫ������������ɫ

    ui.checkBox_9->setVisible(true);
    ui.checkBox_9->setText("ҡ�������ʼ��" + sz1);//"�ɹ�");
    ui.checkBox_9->setChecked(true);
    ui.checkBox_9->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //�趨ǰ����ɫ������������ɫ

    ui.checkBox_10->setVisible(true);
    ui.checkBox_10->setText("ɨ�����Լ�" + sz1);//"�ɹ�");
    ui.checkBox_10->setChecked(true);
    ui.checkBox_10->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //�趨ǰ����ɫ������������ɫ

    ui.checkBox_11->setVisible(true);
    ui.checkBox_11->setText("ɨ��ɹ�");
    ui.checkBox_11->setChecked(true);
    ui.checkBox_11->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //�趨ǰ����ɫ������������ɫ

    ui.checkBox_12->setVisible(true);
    ui.checkBox_12->setText("����Լ�ɹ�");
    ui.checkBox_12->setChecked(true);
    ui.checkBox_12->setStyleSheet("QCheckBox{color:rgb(111, 111, 111)}"); //�趨ǰ����ɫ������������ɫ

    ui.label->setStyleSheet("color:rgb(111, 111, 111);font:19pt;����;");
    //ui.label->setStyleSheet("background-color: rgb(111, 111, 111); color: rgb(222, 222, 222);font: 75 30pt;\"����\";");
    //ui.label->setFixedSize(135, 200);
    //ui.label->setScaledContents(true);
}

void SelfCheckResultShowDialog::on_pushButton_clicked()
{
    close();
}
