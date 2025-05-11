#include "..\Include\precomp\precompile.h"
#include "LisSettingWidgets.h"
#include <QMessageBox>
#include <QCoreApplication>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "../Include/Utilities/log.h"
#include <QListView>
#include "src/main/subDialog/MyMessageBox.h"
#include "../comm/GlobalData.h"
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QtXml> //也可以include <QDomDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include <QDateTime>


LisSettingWidgets::LisSettingWidgets(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	QString start_lis_flage = dao->SelectTargetValueDes(&bResult, "9993");
	if (start_lis_flage == "1")
	{
		ui.checkBoxStartLis->setChecked(true);
	}
	else
	{
		ui.checkBoxStartLis->setChecked(false);
	}
	QString auto_update_lis_flage = dao->SelectTargetValueDes(&bResult, "9994");
	if (auto_update_lis_flage == "1")
	{
		ui.checkBoxAutoConnete->setChecked(true);
	}
	else
	{
		ui.checkBoxAutoConnete->setChecked(false);
	}
	QString ip = dao->SelectTargetValueDes(&bResult,"9995");
	QString port = dao->SelectTargetValueDes(&bResult, "9996");
	ui.lineEditPort->setText(port);
	ui.lineEditIP->setText(ip);
	QString protocol_type = dao->SelectTargetValueDes(&bResult, "9997");
	if (protocol_type == "HL7")
	{
		ui.comboBoxPorocolType->setCurrentIndex(0);//->setText(port);
	}
	else if (protocol_type == "ASTM")
	{
		ui.comboBoxPorocolType->setCurrentIndex(1);//->setText(port);
	}
	else if (protocol_type == "自定义")
	{
		ui.comboBoxPorocolType->setCurrentIndex(2);//->setText(port);
	}
	ui.comboBoxPorocolType->setView(new  QListView(this));
	ui.comboBoxPorocolType->setStyleSheet(QString(
		"QComboBox QAbstractItemView {"
		"background: rgb(192,192,192);"
        "   min-height: 40px;"
		"}"
	));

	ui.comboBoxPorocolType->setStyleSheet(QString(
		"QComboBox QAbstractItemView:item {"
		"background: rgb(192,192,192);"
        "   min-height: 40px;"
		"}"
	));
	QRegExp regExp("([0-9]|[1-9]\\d{1,3}|[1-5]\\d{4}|6[0-4]\\d{4}|65[0-4]\\d{2}|655[0-2]\\d|6553[0-5])");
	ui.lineEditPort->setValidator(new QRegExpValidator(regExp, ui.lineEditPort));
	QString IP_V4 = "^(((\\d)|([1-9]\\d)|(1\\d{2})|(2[0-4]\\d)|(25[0-5]))\\.){3}((\\d)|([1-9]\\d)|(1\\d{2})|(2[0-4]\\d)|(25[0-5]))$";
	regExp = QRegExp(IP_V4);
	ui.lineEditIP->setValidator(new QRegExpValidator(regExp, ui.lineEditIP));

    QString sz = GlobalData::LoadLanguageInfo("K1209");

	ui.label_4->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1210");
	ui.checkBoxStartLis->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1211");
	ui.checkBoxAutoConnete->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1212");
	ui.label->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1213");
	ui.label_2->setText(sz);
    sz = GlobalData::LoadLanguageInfo("K1214");
	ui.label_3->setText(sz);

    sz = GlobalData::LoadLanguageInfo("K1732");
	ui.pushButtonSave->setText(sz);

    sz = GlobalData::LoadLanguageInfo("K1733");
	ui.pushButtonSend->setText(sz);

    ui.label_6->setText(GlobalData::LoadLanguageInfo("K1746"));
    ui.label_7->setText(GlobalData::LoadLanguageInfo("K1747"));
    ui.pushButtonSend_5->setText(GlobalData::LoadLanguageInfo("K1748"));
    ui.pushButtonSend_2->setText(GlobalData::LoadLanguageInfo("K1749"));
    ui.pushButtonSend_3->setText(GlobalData::LoadLanguageInfo("K1750"));
    ui.pushButtonSend_4->setText(GlobalData::LoadLanguageInfo("K1748"));
}

void LisSettingWidgets::setTcpClient(TcpClient *tcpClient1)
{
    m_tcpClient = tcpClient1;
    connect(m_tcpClient, &TcpClient::dataReceived, this, &LisSettingWidgets::updateDisplay);
    connect(m_tcpClient, &TcpClient::connectStatus, this, &LisSettingWidgets::slotConnectStatus);
}


void LisSettingWidgets::onConnectClicked()
{
     GlobalData::reconnect(); // Trigger connection attempt
}

LisSettingWidgets::~LisSettingWidgets()
{
}

void LisSettingWidgets::on_pushButtonSave_clicked()
{
	auto pm{ SystemSetBLL().getRowById(9993) };
	if (pm.isNull())
	{
		eLog("pm is null");
		return;
	}
	int startSet{ ui.checkBoxStartLis->isChecked() ? 1 : 0 };
	pm->setSaveSet(startSet);
	pm->setSaveDes(QString::number(startSet));
	if (!SystemSetBLL().updateByModel(pm))
		eLog("SystemSet update error");

	auto autoSet{ SystemSetBLL().getRowById(9994) };
	if (autoSet.isNull())
	{
		eLog("autoSet is null");
		return;
	}
	auto autoSetV{ ui.checkBoxAutoConnete->isChecked() ? 1 : 0 };
	autoSet->setSaveSet(autoSetV);
	autoSet->setSaveDes(QString::number(autoSetV));
	if (!SystemSetBLL().updateByModel(autoSet))
		eLog("SystemSet update error");
		
	auto ipModel{ SystemSetBLL().getRowById(9995) };
	if (ipModel.isNull())
	{
		eLog("ipModel is null");
		return;
	}
	auto ip{ ui.lineEditIP->text() };
	ipModel->setSaveDes(ip);
	if (!SystemSetBLL().updateByModel(ipModel))
		eLog("ipModel update error");

	auto portModel{ SystemSetBLL().getRowById(9996) };
	if (portModel.isNull())
	{
		eLog("portModel is null");
		return;
	}
	auto port{ ui.lineEditPort->text() };
	portModel->setSaveDes(port);
	if (!SystemSetBLL().updateByModel(portModel))
		eLog("portModel update error");

	auto typeModel{ SystemSetBLL().getRowById(9997) };
	if (typeModel.isNull())
	{
		eLog("typeModel is null");
		return;
	}
	typeModel->setSaveDes(ui.comboBoxPorocolType->currentText());
	if (!SystemSetBLL().updateByModel(typeModel))
		eLog("typeModel update error");
	
	if (startSet>0)
	{
        m_tcpClient->setServerAddress(ip, port.toInt());
        m_tcpClient->reconnect(); // Trigger connection attempt
	}
	else
	{
        m_tcpClient->disconnectFromServer();
        m_tcpClient->m_connectedState = false;
	}
	//得到是否勾选
    MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1317"), MyMessageBox::Ok,"OK","");
}



void  LisSettingWidgets::on_pushButtonSend_5_clicked() {
	ui.textEdit->setText("");
}

void  LisSettingWidgets::on_pushButtonSend_2_clicked() {
	QString send_sz = "";
	send_sz += QString("%1MSH | ^ |||||  202405161559174(样本管编号) || OUL ^ R22 |  | P | 2.5.1 ||| AL | AL || ASCII |||%2").arg(QChar(0x0B)).arg(QChar(0x0D));
	send_sz += QString("PID | 202405161559174(样本管编号) |||||| 202405161559174(样本管编号) | 0 |||||||||||||||||||||||%1").arg(QChar(0x0D));
	send_sz += QString("OBR | 4 | 202405161559174(样本管编号) | 4 | E - LAB ^ ES - 480 | N | 202405161559174 | 202405161559174  ||||||||| ||||  ||||||||||||||||||||||||||||%1").arg(QChar(0x0D));
	send_sz += QString("OBX | |NM | 2024 - 05 - 16 15:59 : 56 || FC | F || 95.4667 |||| F ||| BetchNo || Admin || HumaBlot 72FA |%1").arg(QChar(0x0D));
	send_sz += QString("OBX | |NM | 2024 - 05 - 16 15:59 : 56 || CagA | F++ || 133.583 |||| F ||| BetchNo || Admin || HumaBlot 72FA |%1").arg(QChar(0x0D));
	send_sz += QString("OBX | |NM | 2024 - 05 - 16 15:59 : 56 || VacA95KD | F + || 147.156 |||| F ||| BetchNo || Admin || HumaBlot 72FA |%1").arg(QChar(0x0D));
	send_sz += QString("OBX | |NM | 2024 - 05 - 16 15:59 : 56 || VacA91KD | F + || 149.44 |||| F ||| BetchNo || Admin || HumaBlot 72FA |%1").arg(QChar(0x0D));
	send_sz += QString("OBX | |NM | 2024 - 05 - 16 15:59 : 56 || UreB | F++ || 101.623 |||| F ||| BetchNo || Admin || HumaBlot 72FA |%1").arg(QChar(0x0D));
	send_sz += QString("OBX | |NM | 2024 - 05 - 16 15:59 : 56 || UreA | F++ || 139.924 |||| F ||| BetchNo || Admin || HumaBlot 72FA |%1").arg(QChar(0x0D));
	send_sz += QString("%1%2").arg(QChar(0x1C)).arg(QChar(0x0D));
	ui.textEdit->setText(send_sz);
}

void  LisSettingWidgets::on_pushButtonSend_3_clicked() {
	QString send_sz = "";
	send_sz += QString("%1MSH | ^ |||||  || OUL ^ R21 |  | P |||| AL | AL || ASCII |||%2").arg(QChar(0x0B)).arg(QChar(0x0D));
	send_sz += QString("PID | %1 ||||||  | 0 |||||||||||||||||||||||%2").arg("sample_id_123456789(样本管编号)").arg(QChar(0x0D));
	send_sz += QString("%1%2").arg(QChar(0x1C)).arg(QChar(0x0D));
	ui.textEdit->setText(send_sz);
}

void  LisSettingWidgets::on_pushButtonSend_4_clicked() {
	ui.textEditDisplayWidget->setText("");
}

void LisSettingWidgets::on_pushButtonSend_clicked()
{
	QString send_content = ui.textEdit->toPlainText();
    m_tcpClient->sendData(send_content);
}

void LisSettingWidgets::onSendClicked()
{
	QString data = "LisSettingWidgets";
    m_tcpClient->sendData(data);
	//inputBox->clear();
}

void LisSettingWidgets::updateDisplay(const QString &data)
{
	QString data1 = data;
	ui.textEditDisplayWidget->append(data);
}

void LisSettingWidgets::slotConnectStatus(bool status)
{
	if (status)
	{
        m_tcpClient->m_connectedState = true;
	}
	else
	{
        m_tcpClient->m_connectedState = false;
	}
}
