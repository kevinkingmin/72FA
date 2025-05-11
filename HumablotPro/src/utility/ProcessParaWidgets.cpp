#include "..\include\precomp\precompile.h"
#include "ProcessParaWidgets.h"
#include "QLabel"
#include "QLineEdit"
#include "QVBoxLayout"
#include "QTreeWidgetItem"

#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Model/baseSet/ProcessParaModel.h"

ProcessParaWidgets::ProcessParaWidgets(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
	int company_id = dao->SelectSaveSetById(&bResult, 5).toInt();
	QVector<ProcessParaModel> vect;
	vect = dao->MProcessPara(&bResult, company_id);

	//QMap<QString, QVariant> objectProperties = //..getProperties(); // Replace with actual method to retrieve object properties

	//for (const auto& propertyName : objectProperties.keys()) {
	//	QLabel* label = new QLabel(propertyName);
	//	QLineEdit* lineEdit = new QLineEdit(objectProperties.value(propertyName).toString());

	//	// Add label and lineEdit to your layout or widget
	//	// For example: layout->addWidget(label);
	//	//              layout->addWidget(lineEdit);
	//}



// Assuming you have a layout to which you want to add the dynamically generated controls
	QVBoxLayout* layout = new QVBoxLayout;

	for (int i = 0; i < 10; ++i) {
		QLabel* label = new QLabel("Label " + QString::number(i));
		label->move(i * 10, i * 10);

		QLineEdit* lineEdit = new QLineEdit;
		lineEdit->move(i * 10, i * 10);
		// Add the label and line edit to the layout
		layout->addWidget(label);
		layout->addWidget(lineEdit);
	}

	// Set the layout for your widget
	//QWidget* widget = new QWidget;
	ui.widget->setLayout(layout);


	// Assuming you have a QTreeWidget instance called treeWidget
	ui.treeWidget->clear();  // Clear any existing items in the tree widget

	// Assuming your ProcessParaModel has methods like getName() and getValue()
	for (const auto& processModel : vect) {
		QTreeWidgetItem *item = new QTreeWidgetItem(ui.treeWidget);
		item->setText(0, processModel.getStepName());//.getName());
		QString sz = QString("%1: %2").arg(processModel.getParas()[0].paraName).arg(processModel.getParas()[0].paraValue);
		item->setText(1, sz);

		// Add more columns as needed using setText method
		// For example: item->setText(2, additionalValue);

		// Optionally, you can create child items for nested data structures within each ProcessParaModel
		// For example: item->addChild(new QTreeWidgetItem(item), "Child Item");
	}

	// Adjust column headers if necessary
	ui.treeWidget->setHeaderLabels({ "Name", "Value" });  // Set appropriate column headers based on your data




	//for (const auto& processModel : vect) {

	//	QLabel* label = new QLabel("xx");
	//	QLineEdit* lineEdit = new QLineEdit("3333");

	//	// Add label and lineEdit to your layout or widget
	//	// For example: layout->addWidget(label);
	//	//              layout->addWidget(lineEdit);
	//}



}

ProcessParaWidgets::~ProcessParaWidgets()
{}
