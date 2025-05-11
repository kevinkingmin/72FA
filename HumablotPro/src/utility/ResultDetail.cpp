#include "..\include\precomp\precompile.h"
#include "ResultDetail.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

ResultDetail::ResultDetail(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_ShowModal, true);
}

ResultDetail::~ResultDetail()
{
}
