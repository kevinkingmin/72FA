#include "AddReagent.h"
#include <QMessageBox>
#include "../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include <QProcess>
#include <QListView>
#include "src/main/subDialog/MyMessageBox.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

AddReagent::AddReagent(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_ShowModal, true);

	auto dao = AnalysisUIDao::instance();
	bool bResult;
	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");

	QDoubleValidator* validator6 = new QDoubleValidator(0.0, 0.0, 2, ui.lineEdit_big_wash);
	ui.lineEdit_big_wash->setValidator(validator6);

	//QRegExpValidator* validator7 = new QRegExpValidator(QRegExp("^\\d*$"), ui.lineEdit_small_wash);
	QDoubleValidator* validator7 = new QDoubleValidator(0.0, 0.0, 2, ui.lineEdit_small_wash);
	
	ui.lineEdit_small_wash->setValidator(validator7);

	ui.lineEdit_Name->setProperty("preserveTrailingSpaces", true);  // 设置保留尾部输入空格


	ui.label->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1136"));
	ui.label_2->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1142"));
	ui.label_3->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1143"));
	ui.label_4->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1144"));

	ui.label_5->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1137"));
	ui.label_6->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1145"));
	ui.label_7->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1138"));
	ui.label_8->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1139"));

	ui.pushButton_Save->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1141"));
	ui.pushButton_Cancel->setText(GlobalData::LoadLanguageInfo(g_language_type, "K1134"));
	
		

}

AddReagent::~AddReagent()
{
}

void AddReagent::Set_UI()
{
	bool bResult;
    auto dao = AnalysisUIDao::instance();
	m_TestPaperQuery = dao->SelectTestPapers(m_strCompany_ID, &bResult);
	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1272"), MyMessageBox::Ok,"OK","");
		return;
	}
	ui.comboBox_TestPaper->addItem(" ");


	ui.comboBox_TestPaper->setView(new  QListView(this));
	ui.comboBox_TestPaper->setStyleSheet(QString(
		"QComboBox QAbstractItemView{"
		"background: rgb(192,192,192);"
		"min-height: 40px;"   // 更改 item 高度为 40 像素
		"}"
	));

	ui.comboBox_TestPaper->setStyleSheet(QString(
		"QComboBox QAbstractItemView:item{"
		"background: rgb(192,192,192);"
		"min-height: 40px;"   // 更改 item 高度为 40 像素
		"}"
	));


    while (m_TestPaperQuery.next())
	{
        ui.comboBox_TestPaper->addItem(m_TestPaperQuery.value("PaperName").toString());
	}
	if (m_bModify == false)
		return;
    QSqlQuery ReagentQuery = dao->SelectReagent(m_strReagent_ID, &bResult);
	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1527"), MyMessageBox::Ok,"OK","");
		return;
	}
	int nValue = 0;
	int nSize = 0;
	int nTestPaper_ID = 0;
	int nIndex = 0;
	bool bNull = false;
    if (ReagentQuery.next())
	{
        m_strCompany_ID = ReagentQuery.value("CompanyID").toString();
		QString reagent_name = ReagentQuery.value("reagentName").toString();
		QString small_wash_sz = ReagentQuery.value("fluidMeasureSmall").toString();
		QString big_wash_sz = ReagentQuery.value("fluidMeasure").toString();
		int id = ReagentQuery.value("ID").toInt();

        bNull = ReagentQuery.value("paperId").isNull();
		if (bNull == true)
		{
			ui.comboBox_TestPaper->setCurrentIndex(0);
		}
		else
		{
            nValue = ReagentQuery.value("paperId").toInt();
			if (nValue > 0)
			{
                nSize = m_TestPaperQuery.size();
				for (int i = 0; i < nSize; i++)
				{
                    m_TestPaperQuery.seek(i);
                    nTestPaper_ID = m_TestPaperQuery.value("ID").toInt();
					if (nTestPaper_ID == nValue)
					{
						nIndex = i;
					}
				}
				ui.comboBox_TestPaper->setCurrentIndex(nIndex + 1);
			}
		}
        //ui.lineEdit_Name->setText(ReagentQuery.value("reagentName").toString());

		m_language_code = ReagentQuery.value("reagentName").toString();

		m_reagent_name1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), m_language_code);


		if (m_reagent_name1 == "")
		{
			ui.lineEdit_Name->setText(ReagentQuery.value("reagentName").toString());
		}
		else
		{

			ui.lineEdit_Name->setText(m_reagent_name1);
		}

        nValue = ReagentQuery.value("IsNoDrip").toInt();
		if (nValue == 1)
			ui.checkBox_IsNoDrip->setChecked(true);
		else
			ui.checkBox_IsNoDrip->setChecked(false);
        nValue = ReagentQuery.value("IsSkimp").toInt();
		if (nValue == 1)
			ui.checkBox_IsSkimp->setChecked(true);
		else
			ui.checkBox_IsSkimp->setChecked(false);
        nValue = ReagentQuery.value("IsNeedPrepare").toInt();
		if (nValue == 1)
			ui.checkBox_IsNeedPrepare->setChecked(true);
		else
			ui.checkBox_IsNeedPrepare->setChecked(false);
        bNull = ReagentQuery.value("PumpNo").isNull();
		if (bNull == false)
		{
			QString strValue = "";
			int pump_no = ReagentQuery.value("PumpNo").toInt();
			if (pump_no != -1)
			{
				strValue = QString("%1").arg(pump_no + 1);//m_ReagentQuery.value("PumpNo").toString();
			}
			else
			{
				strValue = QString("%1").arg(pump_no);//m_ReagentQuery.value("PumpNo").toString();
			}
			//ui.lineEdit_PumpNo->setText(ReagentQuery.value("PumpNo").toString());
			ui.lineEdit_PumpNo->setText(strValue);
		}

		ui.lineEdit_big_wash->setText(big_wash_sz);
		ui.lineEdit_small_wash->setText(small_wash_sz);
		ui.comboBox_TestPaper->setCurrentText(reagent_name);

		if ((id == 5) || (id == 6) || (id == 7) || (id == 8) || (id == 9) || (id == 10))
		{
			ui.checkBox_IsNeedPrepare->setEnabled(false);
			ui.lineEdit_PumpNo->setEnabled(false);
			ui.lineEdit_Name->setEnabled(false);
			ui.comboBox_TestPaper ->setEnabled(false);
			ui.checkBox_IsSkimp->setEnabled(false);
			ui.checkBox_IsNoDrip->setEnabled(false);
		}
		else
		{
			ui.checkBox_IsNeedPrepare->setEnabled(true);
			ui.lineEdit_PumpNo->setEnabled(true);
			ui.lineEdit_Name->setEnabled(true);
			ui.comboBox_TestPaper->setEnabled(true);
			ui.checkBox_IsSkimp->setEnabled(true);
			ui.checkBox_IsNoDrip->setEnabled(true);
		}
	}
}


void AddReagent::on_pushButton_Save_clicked()
{
	QString strName = ui.lineEdit_Name->text().trimmed();
	//ui.lineEdit_Name->set//setStringTrimPolicy(Qt::WhiteSpaceNormal);
	//strName = strName.replace(" ", "");
	if (strName.length() == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1528"), MyMessageBox::Ok,"OK","");
		return ;
	}
	QString strIsNoDrip;
	QString strIsSkimp;
	QString strIsNeedPrepare;
	QString strTestPaper_ID;

	int index = ui.comboBox_TestPaper->currentIndex();
	if (index <= 0)
	{
		strTestPaper_ID = "null";
		if (m_strReagent_ID == "5" || m_strReagent_ID == "6" || m_strReagent_ID == "7" || m_strReagent_ID == "8" || m_strReagent_ID == "9" || m_strReagent_ID == "10")
		{
			strTestPaper_ID = "111";
		}
		else
		{
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1529"), MyMessageBox::Ok,"OK","");
			return;
		}
	}
	else 
	{
        m_TestPaperQuery.seek(index - 1);
        strTestPaper_ID = m_TestPaperQuery.value("ID").toString();
	}

	bool bValue = ui.checkBox_IsNoDrip->isChecked();
	if (bValue == true) 
		strIsNoDrip = "1";
	else
		strIsNoDrip = "0";

	bValue = ui.checkBox_IsSkimp->isChecked();
	if (bValue == true)
		strIsSkimp = "1";
	else
		strIsSkimp = "0";

	bValue = ui.checkBox_IsNeedPrepare->isChecked();
	if (bValue == true)
		strIsNeedPrepare = "1";
	else
		strIsNeedPrepare = "0";

	QString strPumpNo = ui.lineEdit_PumpNo->text();

	strPumpNo = strPumpNo.replace(" ", "");

	if (strPumpNo == "")
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1530"), MyMessageBox::Ok,"OK","");
		return;
	}

	if (strPumpNo.length() == 0)
		strPumpNo = "null";

	QString strValue = "";
	int pump_no = strPumpNo.toInt();
	//if ("系统液" == strName || "稀释缓冲液" == strName || "底物液" == strName || "终止液" == strName || "蒸馏水" == strName || "洗涤缓冲液" == strName)
	if (GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1696") == strName || GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1693") == strName || GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1691") == strName || GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1694") == strName || GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1692") == strName || GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1695") == strName)
	{
		if ((pump_no > 9 || pump_no < 1) && pump_no != -1)
		{
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1131"), MyMessageBox::Ok,"OK","");
			return;
		}
	}
	else
	{
		if (pump_no > 4 || pump_no < 1)
		{
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1531"), MyMessageBox::Ok,"OK","");
			return;
		}
	}

	if (pump_no != -1)
	{
		strValue = QString("%1").arg(pump_no - 1);//m_ReagentQuery.value("PumpNo").toString();
	}
	else
	{
		strValue = QString("%1").arg(pump_no);//m_ReagentQuery.value("PumpNo").toString();
	}

	strPumpNo = strValue;
    auto dao = AnalysisUIDao::instance();
	bool bResult;
	QString big_wash_sz = ui.lineEdit_big_wash->text();
	QString small_wash_sz = ui.lineEdit_small_wash->text();


	big_wash_sz = big_wash_sz.replace(" ","");
	small_wash_sz = small_wash_sz.replace(" ", "");

	float big_wash = ui.lineEdit_big_wash->text().toFloat();
	if (big_wash == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1532"), MyMessageBox::Ok,"OK","");
		return;
	}
	float small_wash = ui.lineEdit_small_wash->text().toFloat();
	if (small_wash == 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1533"), MyMessageBox::Ok,"OK","");
		return;
	}

	if (small_wash > big_wash)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1534"), MyMessageBox::Ok,"OK","");
		return;
	}

	if (m_bModify == false)
	{
		if (m_reagent_name1 == "")
		{
			if (dao->SelectReagentName(strName, 1, m_strReagent_ID.toInt()) == 1)
			{
				MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1535"), MyMessageBox::Ok, "OK", "");
				return;
			}
			bResult = dao->InsertReagent(
				strName,
				m_strCompany_ID,
				strTestPaper_ID,
				strIsNoDrip,
				strIsSkimp,
				strIsNeedPrepare,
				strPumpNo, big_wash_sz, small_wash_sz);
			if (bResult == false)
			{
				MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1536"), MyMessageBox::Ok, "OK", "");
				return;
			}
		}
		else
		{
			if (dao->SelectReagentName(m_language_code, 1, m_strReagent_ID.toInt()) == 1)
			{
				MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1535"), MyMessageBox::Ok, "OK", "");
				return;
			}
			bResult = dao->InsertReagent(
				m_language_code,
				m_strCompany_ID,
				strTestPaper_ID,
				strIsNoDrip,
				strIsSkimp,
				strIsNeedPrepare,
				strPumpNo, big_wash_sz, small_wash_sz);
			if (bResult == false)
			{
				MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1536"), MyMessageBox::Ok, "OK", "");
				return;
			}
		}
		
	}
	else
	{
		if (strTestPaper_ID == NULL || strTestPaper_ID=="null" )
		{
			MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1529"), MyMessageBox::Ok,"OK","");
			return;
		}

		if (m_reagent_name1 == "")
		{
			if (dao->SelectReagentName(strName, 0, m_strReagent_ID.toInt()) == 1)
			{
				MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1535"), MyMessageBox::Ok, "OK", "");
				return;
			}
			bResult = dao->UpdateReagent(
				m_strReagent_ID,
				strName,
				m_strCompany_ID,
				strTestPaper_ID,
				strIsNoDrip,
				strIsSkimp,
				strIsNeedPrepare,
				strPumpNo, big_wash_sz, small_wash_sz);

			if (bResult == false)
			{
				MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1537"), MyMessageBox::Ok, "OK", "");
				return;
			}
		}
		else
		{
			if (dao->SelectReagentName(m_language_code, 0, m_strReagent_ID.toInt()) == 1)
			{
				MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1535"), MyMessageBox::Ok, "OK", "");
				return;
			}

			bResult = dao->UpdateReagent(
				m_strReagent_ID,
				m_language_code,
				m_strCompany_ID,
				strTestPaper_ID,
				strIsNoDrip,
				strIsSkimp,
				strIsNeedPrepare,
				strPumpNo, big_wash_sz, small_wash_sz);

			if (bResult == false)
			{
				MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1537"), MyMessageBox::Ok, "OK", "");
				return;
			}
		}

	}
	emit SetRefresh(true);

	auto ret = MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1278"), MyMessageBox::Ok|MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
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
	this->close();
}

void AddReagent::on_pushButton_Cancel_clicked()
{
	this->close();
}
