#include "..\include\precomp\precompile.h"
#include "LiquidDetectionWidgets.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "src/main/subDialog/ProgressDialog.h"
#include "../Include/Model/Model.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QTextStream>
#include "src/comm/Global.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/main/subDialog/MyMessageBox.h"

LiquidDetectionWidgets::LiquidDetectionWidgets(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::LiquidDetectionWidgetsClass)
	, _InstrumentState(InstrumentStateModel::instance())
	, _instr(Instrument::instance())
	, _emptyFile("rFlowBack128.png")
	, _flushFile("irrigationIcon.png")
	, _readyFile("rReady.png")
	, _delayFile("rDelay.png")
	, _pixPath(":/images/buttonIcon/")

{
	ui->setupUi(this);
	createPumpBtn(ui->pushButton_2, false);
	createPumpBtn(ui->pushButton_3, false);
	createPumpBtn(ui->pushButton_4, false);
	createPumpBtn(ui->pushButton_5, false);
	createPumpBtn(ui->pushButton_6, false);
	createPumpBtn(ui->pushButton_7, false);
	createPumpBtn(ui->pushButton_8, false);
	createPumpBtn(ui->pushButton_9, false);
	createPumpBtn(ui->pushButton_10, false);

	connect(_instr, &Instrument::sglIsStepSuc, this, &LiquidDetectionWidgets::slotIsStepSuc);

    //_instr->inquireZMotorPara();
    //_instr->inquireYMotorParas();

	ui->groupBox->setVisible(false);
	ui->progressBar->setStyleSheet("QProgressBar {border: 1px solid grey; border-radius: 2px; background-color: #FFFFFF; text-align:center; font-size:15px}");

	QString sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1223");
	ui->label_5->setText(sz1);

	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1235");
	ui->label_2->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1236");
	ui->label_3->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1237");
	ui->label_4->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1238");
	ui->label->setText(sz1);

	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1222");
	ui->pushButton->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1239");
	ui->pushButton_11->setText(sz1);


	//K1609 | ��׼�� | ��׼��en
	//	K1610 | ��Ѫ�� | ��Ѫ��en
	//	K1611 | ΢���� | ΢����en
	//ui->comboBox
	QStringList strList;
	strList << GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1609") << GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1610") << GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1611");
	ui->comboBox->addItems(strList);
	
}

LiquidDetectionWidgets::~LiquidDetectionWidgets()
{}


QVector<uchar> LiquidDetectionWidgets::getCheckBtn()
{
	QVector<uchar> outVect;
	if (ui->chk_1->isChecked())
	{
		createPumpBtn(ui->pushButton_2, true);
		outVect.push_back(0);
	}
	else
	{
		createPumpBtn(ui->pushButton_2, false);
	}

	if (ui->chk_2->isChecked())
	{
		createPumpBtn(ui->pushButton_3, true);
		outVect.push_back(1);
	}
	else
	{
		createPumpBtn(ui->pushButton_3, false);
	}

	if (ui->chk_3->isChecked())
	{
		createPumpBtn(ui->pushButton_4, true);
		outVect.push_back(2);
	}
	else
	{
		createPumpBtn(ui->pushButton_4, false);
	}

	if (ui->chk_4->isChecked())
	{
		createPumpBtn(ui->pushButton_5, true);
		outVect.push_back(3);
	}
	else
	{
		createPumpBtn(ui->pushButton_5, false);
	}

	if (ui->chk_5->isChecked())
	{
		createPumpBtn(ui->pushButton_6, true);
		outVect.push_back(4);
	}
	else
	{
		createPumpBtn(ui->pushButton_6, false);
	}

	if (ui->chk_6->isChecked())
	{
		createPumpBtn(ui->pushButton_7, true);
		outVect.push_back(5);
	}
	else
	{
		createPumpBtn(ui->pushButton_7, false);
	}

	if (ui->chk_7->isChecked())
	{
		createPumpBtn(ui->pushButton_8, true);
		outVect.push_back(6);
	}
	else
	{
		createPumpBtn(ui->pushButton_8, false);
	}

	if (ui->chk_8->isChecked())
	{
		createPumpBtn(ui->pushButton_9, true);
		outVect.push_back(7);
	}
	else
	{
		createPumpBtn(ui->pushButton_9, false);
	}

	if (ui->chk_9->isChecked())
	{
		createPumpBtn(ui->pushButton_10, true);
		outVect.push_back(8);
	}
	else
	{
		createPumpBtn(ui->pushButton_10, false);
	}
	mOutVect = outVect;
	return outVect;
}

void LiquidDetectionWidgets::on_chk_1_toggled(bool state)
{
	getCheckBtn();
}

void LiquidDetectionWidgets::on_chk_2_toggled(bool state)
{
	getCheckBtn();
}

void LiquidDetectionWidgets::on_chk_3_toggled(bool state)
{
	getCheckBtn();
}

void LiquidDetectionWidgets::on_chk_4_toggled(bool state)
{
	getCheckBtn();
}
void LiquidDetectionWidgets::on_chk_5_toggled(bool state)
{
	getCheckBtn();
}
void LiquidDetectionWidgets::on_chk_6_toggled(bool state)
{
	getCheckBtn();
}

void LiquidDetectionWidgets::on_chk_7_toggled(bool state)
{
	getCheckBtn();
}

void LiquidDetectionWidgets::on_chk_8_toggled(bool state)
{
	getCheckBtn();
}

void LiquidDetectionWidgets::on_chk_9_toggled(bool state)
{
	getCheckBtn();
}

void LiquidDetectionWidgets::on_pushButton_2_clicked()
{
	if (ui->pushButton_2->isChecked())
	{
		ui->chk_1->setChecked(true);
		ui->pushButton_2->setChecked(true);

	}
	else
	{
		ui->chk_1->setChecked(false);
		ui->pushButton_2->setChecked(false);
	}
}

void LiquidDetectionWidgets::on_pushButton_3_clicked() {
	if (ui->pushButton_3->isChecked())
	{
		ui->chk_2->setChecked(true);
		ui->pushButton_3->setChecked(true);

	}
	else
	{
		ui->chk_2->setChecked(false);
		ui->pushButton_3->setChecked(false);
	}
}

void LiquidDetectionWidgets::on_pushButton_4_clicked() {
	if (ui->pushButton_4->isChecked())
	{
		ui->chk_3->setChecked(true);
		ui->pushButton_4->setChecked(true);

	}
	else
	{
		ui->chk_3->setChecked(false);
		ui->pushButton_4->setChecked(false);
	}
}

void LiquidDetectionWidgets::on_pushButton_5_clicked() {
	if (ui->pushButton_5->isChecked())
	{
		ui->chk_4->setChecked(true);
		ui->pushButton_5->setChecked(true);

	}
	else
	{
		ui->chk_4->setChecked(false);
		ui->pushButton_5->setChecked(false);
	}
}
void LiquidDetectionWidgets::on_pushButton_6_clicked() {

	if (ui->pushButton_6->isChecked())
	{
		ui->chk_5->setChecked(true);
		ui->pushButton_6->setChecked(true);

	}
	else
	{
		ui->chk_5->setChecked(false);
		ui->pushButton_6->setChecked(false);
	}
}
void LiquidDetectionWidgets::on_pushButton_7_clicked() {
	if (ui->pushButton_7->isChecked())
	{
		ui->chk_6->setChecked(true);
		ui->pushButton_7->setChecked(true);
	}
	else
	{
		ui->chk_6->setChecked(false);
		ui->pushButton_7->setChecked(false);
	}
}
void LiquidDetectionWidgets::on_pushButton_8_clicked() {
	if (ui->pushButton_8->isChecked())
	{
		ui->chk_7->setChecked(true);
		ui->pushButton_8->setChecked(true);
	}
	else
	{
		ui->chk_7->setChecked(false);
		ui->pushButton_8->setChecked(false);
	}
}
void LiquidDetectionWidgets::on_pushButton_9_clicked() {

	if (ui->pushButton_9->isChecked())
	{
		ui->chk_8->setChecked(true);
		ui->pushButton_9->setChecked(true);
	}
	else
	{
		ui->chk_8->setChecked(false);
		ui->pushButton_9->setChecked(false);
	}
}
void LiquidDetectionWidgets::on_pushButton_10_clicked() {

	if (ui->pushButton_10->isChecked())
	{
		ui->chk_9->setChecked(true);
		ui->pushButton_10->setChecked(true);
	}
	else
	{
		ui->chk_9->setChecked(false);
		ui->pushButton_10->setChecked(false);
	}
}

void LiquidDetectionWidgets::on_pushButton_11_clicked() {
	//QString text = textBrowser.toPlainText();
	QString text = ui->textBrowser->toPlainText();
	//��ȡ�ļ�Ŀ¼
	QString filename = QFileDialog::getExistingDirectory(this, tr("file dialog"), "D:");
	//�ļ���
	QDateTime time = QDateTime::currentDateTime();//��ȡϵͳ���ڵ�ʱ��
	QString date = time.toString("yyyy-MM-dd-HH-mm-ss");//������ʾ�ĸ�ʽ
	filename += "//" + date;
	filename += ".txt";
	//�ļ�����
	QFile file(filename);
	//ֻд��ʽ��
	if (!file.open(QFile::WriteOnly | QFile::Text))//ֻд�ķ�ʽ��
	{
		MyMessageBox::warning(this, tr("double file edit"), tr("no write ").arg(filename).arg(file.errorString()), MyMessageBox::Ok,"OK","");
		return;
	}
	QTextStream out(&file);
	out << ui->textBrowser->toPlainText() << endl << QObject::tr("");
	file.close();
}

void LiquidDetectionWidgets::on_cb_all_toggled(bool state)
{
	if (state)
	{
		ui->chk_1->setChecked(true);
		ui->chk_2->setChecked(true);
		ui->chk_3->setChecked(true);
		ui->chk_4->setChecked(true);
		ui->chk_5->setChecked(true);
		ui->chk_6->setChecked(true);
		ui->chk_7->setChecked(true);
		ui->chk_8->setChecked(true);
		ui->chk_9->setChecked(true);
	}
	else
	{
		ui->chk_1->setChecked(false);
		ui->chk_2->setChecked(false);
		ui->chk_3->setChecked(false);
		ui->chk_4->setChecked(false);
		ui->chk_5->setChecked(false);
		ui->chk_6->setChecked(false);
		ui->chk_7->setChecked(false);
		ui->chk_8->setChecked(false);
		ui->chk_9->setChecked(false);
	}
	getCheckBtn();
}
void LiquidDetectionWidgets::createPumpBtn(QPushButton *pushButton, bool selected_status)
{
	auto empty = "irrigationIcon.png";
	QImage image(_pixPath + empty);
	//ui->pumpLB1_1->setPixmap(QPixmap::fromImage(image));
	QPixmap fitpixmap = QPixmap::fromImage(image).scaled(image.width(), image.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	pushButton->setIcon(QIcon(fitpixmap));
	pushButton->setProperty("btnStyle", "btnReagentPosStyle");
	pushButton->setProperty(GlobalData::getPropertyName(), PumpPosState::enumEmpty);
	pushButton->setIconSize(QSize(image.width(), image.height()));
	if (selected_status)
	{
		pushButton->setChecked(true);//->setCheckable(true);
	}
	else
	{
		pushButton->setChecked(false);
	}
}

void LiquidDetectionWidgets::slotIsStepSuc(int ret) {

	if (!start_liquid_detection)
	{
		return;
	}

	auto state = _InstrumentState->getMachineState();
	if (state.state == enumState::enumError)
	{
		return;
	}

	if (ret >= 0 && m_action_id== ret)
	{
		/**
		 * @brief getYMotorPara:��ȡY���λ��
		 * @param fstRackPos//��һ��������λ��
		 * @param scdRackPos//�ڶ���������λ��
		 * @param needleWashPos//��������ϴλ��
		 * @param startDrawWastePos//�������Һλ��
		 * @param spitYPos//���������Y��λ��
		 * @param startWasteSlotPos//��Һ�۴������Һλ��
		 */
		int fstRackPos = 0;
		int scdRackPos = 0;
		int needleWashPos = 0;
		int startDrawWastePos = 0;
		int spitYPos = 0;
		int startWasteSlotPos = 0;
		/**
		 * @brief getZMotorPara:��ȡZ���λ��
		 * @param washHeight//��ϴλ�߶�
		 * @param standartCupHeight//��׼Ʒ���߶�
		 * @param bloodingCupHeight//��Ѫ�ܸ߶�
		 * @param microCupHeight//΢�����߶�
		 * @param startDetectLevelHeight//Һλ̽����ʼ�߶�
		 * @param spitHeight//��Һ�߶�
		 * @param detectLevel2ndDescendHeight//Һλ̽������½��߶�
		 * @param wasteSlotHeight//��Һ�۸߶�
		 */
		int washHeight = 0;
		int standartCupHeight = 0;
		int bloodingCupHeight = 0;
		int microCupHeight = 0;
		int startDetectLevelHeight = 0;
		int spitHeight = 0;
		int detectLevel2ndDescendHeight = 0;
		int wasteSlotHeight = 0;

		if (m_action_id == 20 || m_action_id == 8)
		{
            //_instr->getZMotorPara(washHeight, standartCupHeight, bloodingCupHeight, microCupHeight, startDetectLevelHeight, spitHeight, detectLevel2ndDescendHeight, wasteSlotHeight);
			m_standartCupHeight = standartCupHeight;
			m_bloodingCupHeight = bloodingCupHeight;
			m_microCupHeight = microCupHeight;
		}


		//if (!getgetZMotorPara_finish)
		//{
		//	_instr->getZMotorPara(washHeight, standartCupHeight, bloodingCupHeight, microCupHeight, startDetectLevelHeight, spitHeight, detectLevel2ndDescendHeight, wasteSlotHeight);
		//	m_standartCupHeight = standartCupHeight;
		//	m_bloodingCupHeight = bloodingCupHeight;
		//	m_microCupHeight = microCupHeight;
		//	getgetZMotorPara_finish = true;
		//}

		if (!m_initialize_flage) 
		{
			//Y������ʼ��
			if (z_finish_flage && !loop_finish)
			{
                //_instr->motorInitialize(0x02, 60000);
				m_action_id = 8;
				z_finish_flage = false;
				y_finish_flage = true;
				ret = -1;
			}
			//X������ʼ��
			if (y_finish_flage && ret >= 0 && !loop_finish) {
                //_instr->motorInitialize(0x01, 60000);
				m_action_id = 8;
				y_finish_flage = false;
				x_finish_flage = true;
				ret = -1;
			}
			//���������õ��
			if (x_finish_flage && ret >= 0 && !loop_finish)
			{
                //_instr->motorInitialize(0x04, 60000);
				m_action_id = 8;
				x_finish_flage = false;
				sample_finish_flage1 = true;
				m_initialize_flage = true;
				ret = -1;
			}
		}

		//���ø���ָ���������ϴ�������ʱ��1000�����Һʱ��2000
		//if (sample_finish_flage1 && ret >= 0)
		//{
		//	_instr->sampleArmWash(1000, 1000, 2000);
		//	m_action_id = 19;
		//	sample_finish_flage1 = false;
		//	sample_finish_flage = true;
		//	ret = -1;
		//}

	A:
		{
			if (sample_finish_flage1 && ret >= 0)
			{
                //_instr->sampleArmWash(1000, 1000, 3000);
				m_action_id = 19;
				sample_finish_flage1 = false;
				sample_finish_flage = true;
				ret = -1;
				y_needleWashPos_flage = true;
			}
		}

		//���ø���ָ���������Һ��
		if (sample_finish_flage && ret >= 0 && !loop_finish)
		{
            //_instr->sampleArmSuck(m_vol, true, m_cup_type, m_pump_pos);
			m_action_id = 18;
			sample_finish_flage = false;
			get_pos_value = true;
			//��Һ���
			sample_arm_suck_finish = true;
			ret = -1;
		}

		if (sample_arm_suck_finish && ret >= 0 && !loop_finish)
		{

			if (get_pos_value)
			{
                //m_pos = _instr->getSampleSuckPos();
				m_first_value = m_pos;
				int cup_height = 0;
				int m_pos11 = 0;
				QString cup_type_sz = "";
				if (m_cup_type == 0)
				{
					cup_height = m_standartCupHeight;
					cup_type_sz = "��׼���߶�";
				}

				if (m_cup_type == 1)
				{
					cup_height = m_bloodingCupHeight;
					cup_type_sz = "��Ѫ�ܸ߶�";
				}

				if (m_cup_type == 2)
				{
					cup_height = m_microCupHeight;
					cup_type_sz = "΢�����߶�";
				}

				m_pos11 = m_pos;

				if (m_loop_number1 == 1)
				{
					if (cup_height == m_pos)
					{
						pos_info = QString("%4--%1--%5--%2��###--- %3 ").arg(m_loop_number1).arg(m_pos11).arg(cup_height).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1677")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1678"));
					}
					else if (abs((m_first_value - m_old_value)) > 1000)
					{
						pos_info = QString("%4--%1--%5--%2��    --- %3 ").arg(m_loop_number1).arg(m_pos11).arg(cup_height).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1677")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1678"));
						m_success_flage = false;
					}
					else
					{
						pos_info = QString("%4--%1--%5--%2��    --- %3 ").arg(m_loop_number1).arg(m_pos11).arg(cup_height).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1677")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1678"));
						m_success_flage = true;
					}

				}
				else if (m_loop_number1 > 1)
				{
					if (cup_height - m_pos == 0)
					{
						pos_info = QString("%4--%1--%5--%2��### --- %3 ").arg(m_loop_number1).arg(m_pos11).arg(cup_height).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1677")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1678"));
					}
					else if (abs((m_first_value - m_old_value)) > 1000)
					{
						pos_info = QString("%4--%1--%5--%2��*** --- %3 ").arg(m_loop_number1).arg(m_pos11).arg(cup_height).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1677")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1678"));
						m_success_flage = false;
					}
					else
					{
						pos_info = QString("%4--%1--%5--%2��    --- %3 ").arg(m_loop_number1).arg(m_pos11).arg(cup_height).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1677")).arg(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1678"));
						m_success_flage = true;
					}
				}
				m_old_value = m_pos;
				ui->textBrowser->append(pos_info);
				x_finish_flage = true;
				get_pos_value = false;
				x_finish_flage = false;
				zz_finish_flage = true;
				m_loop_number -= 1;
				m_loop_number1++;
				sample_finish_flage1 = true;
				if (m_loop_number == 0 || m_loop_number < 0)
				{
					sample_finish_flage1 = false;
					sample_finish_flage2 = true;
					zz_finish_flage = false;
					//Y�����˶�����ϴλ
					//X������ʼ��
					loop_finish = true;
					//ret = -1;
					sample_finish_flage1 = true;
					goto A;
				}
			}
			//��ȥ��ϴ
			sample_finish_flage1 = true;
			goto A;
		}

		//���
		if (loop_finish)
		{
			/**
			 * @brief getYMotorPara:��ȡY���λ��
			 * @param fstRackPos//��һ��������λ��
			 * @param scdRackPos//�ڶ���������λ��
			 * @param needleWashPos//��������ϴλ��
			 * @param startDrawWastePos//�������Һλ��
			 * @param spitYPos//���������Y��λ��
			 * @param startWasteSlotPos//��Һ�۴������Һλ��
			 */
			 //_instr->getYMotorPara(fstRackPos, scdRackPos, needleWashPos, startDrawWastePos, spitYPos, startWasteSlotPos);
			 /**
			  * @brief motorMoveToAbsolutePos:�����ת���̶�λ�ã��ź�sglIsStepSuc
			  * @param motorAddress:�����ַ
			  * @param photoelectricEnable:����Ƿ�ʹ��
			  * @param direction:����
			  * @param pulse:����
			  */

			  //---------------------------------------------------------
			//if (sample_finish_flage2)
			//{
			//	_instr->sampleArmWash(1000, 1000, 2000);
			//	m_action_id = 19;
			//	sample_finish_flage2 = false;
			//	y_needleWashPos_flage = true;
			//	ret = -1;
			//}

			if (y_needleWashPos_flage && ret >= 0)
			{
                //_instr->motorInitialize(0x01, 60000);
				m_action_id = 8;
				y_needleWashPos_flage = false;
				_InstrumentState->setMachineState(enumState::enumStandby);
				loop_finish = false;
				ret = -1;
			}

			if (!y_needleWashPos_flage && !loop_finish)
			{
				loop_finish = false;
				ret = -1;
				if (m_success_flage)
				{
					ui->textBrowser->append(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1675"));//"���Խ�����Һλ̽������");
				}
				else
				{
					ui->textBrowser->append(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1676"));//"���Խ�����Һλ̽���쳣");
				}
				start_liquid_detection = false;
			}
			//y_needleWashPos_flage = true;
		}
		//--------------------------------------------------------------------
	}
	else
	{
		//start_liquid_detection = false;
	}
}
//������
void LiquidDetectionWidgets::on_pushButton_clicked()
{
	if (!_InstrumentState->enumStandby)
	{
		return;
	}

	int a = 0;
	bool result = false;
	QString selectText = "";
	selectText = ui->comboBox->currentText();
	if (selectText == GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1609"))//"��׼��")
	{
		m_cup_type = 0;
	}
	if (selectText == GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1610"))//"��Ѫ��")
	{
		m_cup_type = 1;
	}
	if (selectText == GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1611"))//"΢����")
	{
		m_cup_type = 2;
	}
	Global::g_run_or_maintenance_flage = 1;
	m_pump_pos = ui->spinBox->text().toInt();
	m_vol = ui->edit_vol->text().toInt();
	int loop_number = ui->edit_time->text().toInt();
	m_loop_number = loop_number;
	m_loop_number1 = 1;
	//��Χ��0 - 10ul
	//	1 - 200��
	if (m_vol > 10 || m_vol <= 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1438"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		ui->edit_vol->setFocus();
		return;
	}
	if (loop_number > 500 || loop_number <= 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1439"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		ui->edit_time->setFocus();
		return;
	}
	m_initialize_flage = false;
	m_success_flage = false;
	start_liquid_detection = true;
	sample_arm_suck_finish = false;
    //_instr->inquireZMotorPara();
	m_action_id = 20;
	m_first_value = 0;
	m_old_value = 0;
	//Z������ʼ��
    //_instr->motorInitialize(0x03, 60000);
	m_action_id = 8;
	z_finish_flage = true;
	loop_finish = false;
	_InstrumentState->setMachineState(enumState::enumMaintain);
	m_progressDialog->setHead(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1617"));//"Һλ��������......");
	m_progressDialog->exec();
}

void LiquidDetectionWidgets::setProgressDialog(ProgressDialog *progressDialog)
{
	m_progressDialog = progressDialog;
}
