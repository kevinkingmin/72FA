#include "..\include\precomp\precompile.h"
#include "ShowAllPicWidgets.h"


ShowAllPicWidgets::ShowAllPicWidgets(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

ShowAllPicWidgets::~ShowAllPicWidgets()
{}

void ShowAllPicWidgets::ShowPic(QString strPath)
{
	QImage image(strPath);
	ui.label->setPixmap(QPixmap::fromImage(image));
	ui.label->setScaledContents(true);
	update();
}