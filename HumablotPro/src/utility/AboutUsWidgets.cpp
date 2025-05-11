#include "..\include\precomp\precompile.h"
#include "AboutUsWidgets.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "src/comm/GlobalData.h"
#include "../Include/Instrument/Instrument.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

AboutUsWidgets::AboutUsWidgets(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	_instrument = Instrument::instance();
	QString sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1246");
	ui.label_3->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1247");
	ui.label_2->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1248");
	ui.label_6->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1249");
	ui.label_5->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1672");
	ui.label_8->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1670");
	ui.label_7->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1671");
	ui.label_10->setText(sz1);
	sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1673");
	ui.label_11->setText(sz1);
	connect(_instrument, &Instrument::sglIsStepSuc, this, &AboutUsWidgets::slotIsStepSuc);
    //_instrument->inquireMachineNo();
    //_instrument->inquire_main_controller_version();
}

void AboutUsWidgets::slotIsStepSuc(int ret)
{
	if (ret == 1)
	{
        QString main_version =" _instrument ->get_MCB_Version()";
		QString sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1673")+ main_version;
		ui.label_11->setText(sz1);
	}
	if (ret == 2)
	{
        int hardware_version = 0;//= _instrument->get_maincontroller_hardware_version();
		/**
		 * @brief 获取主控板软件件版本号
		 */
        int software_version =0;// _instrument->get_maincontroller_software_version();
		QString sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1670") + QString::number(hardware_version);
		ui.label_7->setText(sz1);
		sz1 = GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1671") + QString::number(software_version);
		ui.label_10->setText(sz1);
	}
}

AboutUsWidgets::~AboutUsWidgets()
{}
