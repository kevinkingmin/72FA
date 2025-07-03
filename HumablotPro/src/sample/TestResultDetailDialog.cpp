#include "TestResultDetailDialog.h"
#include <qdebug.h>
#include <QMessageBox>
#include <QFileInfo>
#include <QLabel>
#include <QTextEdit>
#include <QSqlQuery>
#include <QApplication>
#include <QPainter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QDesktopServices>
#include <QPrintPreviewDialog> 
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QtWidgets>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "ShowAllPicWidgets.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "../comm/GlobalData.h"

TestResultDetailDialog::TestResultDetailDialog(QString testIda,QString sample_no,QWidget *parent)
    : QDialog(parent)
{
	setWindowIcon(QIcon(":/favicon.ico"));
	setWindowIcon(QIcon(":/images/buttonIcon/icon.png"));
	bool bResult = true; 
	auto dao = AnalysisUIDao::instance();
    int company_info = dao->SelectTargetValue(&bResult, "5").toInt();
    setWindowTitle(GlobalData::LoadLanguageInfo("K1704"));
	int windows_width = 0;// 1500;
    if (company_info == 2)
	{
		windows_width = 1900;
	}
	else
	{
		windows_width = 1500;
	}
	QDesktopWidget* desktop = QApplication::desktop(); 
    this->setFixedSize(windows_width, 855);
	move((desktop->width() - windows_width) / 2, (desktop->height() - this->height()) / 2);
	m_testId = testIda;
	QString strRel;
	QString strValue;
	QString strItemName;
	int paperId = 1;
	QString paper_name = "";
	double dRatioToCut;
	int pos = 0;
	int left_pix_position = 0;
	int right_pix_position = 0;
	int top = 0;
	int height1 = 0;
	QString testResult = "";
	QString testGrayValue = "";
	auto TestDataQuery = dao->SelectTestDataByTestId(m_testId,&bResult);
    QString sz1 = GlobalData::LoadLanguageInfo("K1173");
    QString sz2 = GlobalData::LoadLanguageInfo("K1174");
    QString sz3 = GlobalData::LoadLanguageInfo("K1175");
	if (bResult == false)
	{
		MyMessageBox::warning(this, sz1, sz2,  MyMessageBox::Ok, sz3, "");
		return;
	}
	mainLayout = new QGridLayout(this);
	noLabel = new QLabel(this);
	testIdLabel = new QLabel(this);
    topBarLayout = new QGridLayout(this);
	topBarLayout->addWidget(noLabel, 0, 1);
	topBarLayout->addWidget(testIdLabel, 0, 0);
    QString sz4 = GlobalData::LoadLanguageInfo("K1049");
	testIdLabel->setText("     "+sz4+":"+sample_no);
	mainLayout->addLayout(topBarLayout, 0, 0);
	tableWidget = new QTableWidget(this);
	tableWidget->setObjectName("resultData");
	int row_numbers = TestDataQuery.size();
	tableWidget->setColumnCount(7);
	tableWidget->setRowCount(row_numbers);
    QString sz5 = GlobalData::LoadLanguageInfo("K1175");
    QString sz6 = GlobalData::LoadLanguageInfo("K1176");
    QString sz7 = GlobalData::LoadLanguageInfo("K1177");
    QString sz8 = GlobalData::LoadLanguageInfo("K1178");
    QString sz9 = GlobalData::LoadLanguageInfo("K1179");
    QString sz10 = GlobalData::LoadLanguageInfo("K1702");
	tableWidget->setHorizontalHeaderLabels(QStringList() << sz5 << sz6 << sz7 << sz8 << sz9 << sz10<<"pkid");
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    if (company_info == 2)
	{
		tableWidget->setColumnWidth(0, 250);
		tableWidget->setColumnWidth(1, 400);
		tableWidget->setColumnWidth(2, 400);
		tableWidget->setColumnWidth(3, 200);
		tableWidget->setColumnWidth(4, 50);
		tableWidget->setColumnWidth(5, 550);
	}
	else
	{
		tableWidget->setColumnWidth(0, 250);
		tableWidget->setColumnWidth(1, 250);
		tableWidget->setColumnWidth(2, 250);
		tableWidget->setColumnWidth(3, 150);
		tableWidget->setColumnWidth(4, 50);
		tableWidget->setColumnWidth(5, 350);
	}
	tableWidget->hideColumn(6);
	tableWidget->selectRow(0);
	strRel = "";
	int item_number = 0;
	QString file_name = "";
	QString strPathFileName;
	QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
	QString analysised_piture_path = "analysised";
	QString strPath = piture_root_str + "\\" + analysised_piture_path;
	file_name = QString("%0\\%1.png").arg(strPath).arg(testIda);  //testIda
	QPixmap result_pic = QPixmap(file_name);
	if (result_pic.width() == 0)
	{
        QString sz10 = GlobalData::LoadLanguageInfo("K1180");
        QString sz11 = GlobalData::LoadLanguageInfo("K1182");
        QString sz12 = GlobalData::LoadLanguageInfo("K1181");
		MyMessageBox::information(this, sz10, sz11, MyMessageBox::Ok, sz12, "");
		noLabel->setVisible(false);
		testIdLabel->setVisible(false);
		return;
	}
	else
	{
		QPixmap pix(result_pic.width(), result_pic.height() * 2);
		pix.fill(Qt::white);
		QPainter p(&pix);
		p.setBrush(Qt::white);
		p.drawPixmap(0, result_pic.height(), result_pic.width(), result_pic.height(), result_pic.scaled(result_pic.width(), result_pic.height(), Qt::KeepAspectRatio));
		p.setBrush(Qt::white);
		p.setRenderHint(QPainter::Antialiasing, true);
		QLinearGradient Linear(1000, 10, 10, 5);     
		Linear.setColorAt(0, Qt::gray);
		Linear.setColorAt(1, Qt::gray);
		p.setBrush(Linear);
		p.setPen(Qt::transparent);
		QPen pen(Qt::gray, 1, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
		p.setPen(pen);
		QFont font(this->font());
		int font_size = 17;
		font.setPointSize(font_size);
		p.setFont(font);
		QString pkid = "";
		while (TestDataQuery.next())
		{
			int tmp_item_number = item_number + 1;
			strItemName = TestDataQuery.value("projectName").toString();
            strItemName = strItemName.replace("\n", "");
			dRatioToCut = TestDataQuery.value("cutGrayValue").toDouble();
			int error_code = TestDataQuery.value("error_code").toInt();
			double tgv = TestDataQuery.value("testGrayValue").toDouble();
			error_code = TestDataQuery.value("error_code").toInt();
            testResult = TestDataQuery.value("testResult").toString();
			pkid= TestDataQuery.value("pkid").toString();
			if (tgv > 255)
			{
                testGrayValue = QString("%1").arg(GlobalData::LoadLanguageInfo("K1261"));
			}
			else
			{
				testGrayValue = QString("%1").arg(tgv);
			}
			paperId = TestDataQuery.value("paperId").toInt();
			pos = TestDataQuery.value("slotPos").toInt();
			left_pix_position = TestDataQuery.value("left_pix_position").toInt();
			right_pix_position = TestDataQuery.value("right_pix_position").toInt();
			top = TestDataQuery.value("top").toInt();

			height1 = TestDataQuery.value("height").toInt();
			QString i_text = QString::fromUtf8("%1").arg(tmp_item_number);

			if (item_number % 2 == 0)
			{
				p.drawRect(left_pix_position, top + 10, right_pix_position - left_pix_position, height1);
				p.drawText(pos - 10, 15, i_text);
			}
			else
			{
				p.drawRect(left_pix_position, top + 25, right_pix_position - left_pix_position, height1);
				p.drawText(pos - 10, 30, i_text);
			}
			tableWidget->setItem(item_number, 6, new QTableWidgetItem(pkid));
			QTableWidgetItem *item_strItemName = new QTableWidgetItem(strItemName);
            item_strItemName->setTextAlignment(Qt::AlignCenter);
			tableWidget->setItem(item_number, 0, item_strItemName);
			QString dRatioToCut_sz = "";
			if (strItemName == "FC")
			{
				dRatioToCut_sz = "\\";
			}
			else
			{
				dRatioToCut_sz = dao->convetItemCutValue(company_info, strItemName, dRatioToCut);
			}
			QTableWidgetItem *item_dRatioToCut = new QTableWidgetItem(dRatioToCut_sz);
            item_dRatioToCut->setTextAlignment(Qt::AlignCenter);
			tableWidget->setItem(item_number, 1, item_dRatioToCut);

			if (strItemName != "FC" && strItemName != "Cut")
			{
                strRel = testResult;
			}

			if (error_code == 10002)
			{
				if (strItemName == "FC" || strItemName == "Cut")
				{
					strRel = "\\";
				}
				else
				{
					strRel = "-";
				}
			}

			if (error_code == 10003)
			{
				if (strItemName == "FC" || strItemName == "Cut")
				{
					strRel = "\\";
				}
				else
				{
					strRel = "o";
				}
			}
			QTableWidgetItem *item_resut = new QTableWidgetItem(strRel);
            item_resut->setTextAlignment(Qt::AlignCenter);
			tableWidget->setItem(item_number, 2, item_resut);

			if (error_code >0 && error_code != 10002 )
			{
				if (error_code == 10003)
				{
                    QString gray_value_str = QString("%1").arg(testGrayValue.toDouble());
					QTableWidgetItem *item = new QTableWidgetItem(gray_value_str);
					tableWidget->setItem(item_number, 3, item);
                    item->setTextAlignment(Qt::AlignCenter);
                    tableWidget->item(item_number, 3)->setBackground(Qt::red);
				}
				else
				{
                    QString gray_value_str = QString("%1").arg(testGrayValue.toDouble());
					QTableWidgetItem *item = new QTableWidgetItem(gray_value_str);
                    item->setTextAlignment(Qt::AlignCenter);
					tableWidget->setItem(item_number, 3, item);
				}

			}else
			{
                QString gray_value_str = QString("%1").arg(testGrayValue.toDouble());
				QTableWidgetItem *item = new QTableWidgetItem(gray_value_str);
				tableWidget->setItem(item_number, 3, item);
                item->setTextAlignment(Qt::AlignCenter);
                tableWidget->item(item_number, 3)->setBackground(Qt::red);
			}

			QTableWidgetItem *item4 = new QTableWidgetItem(i_text);
            item4->setTextAlignment(Qt::AlignCenter);
			tableWidget->setItem(item_number, 4, item4);
			QString error_code_str = "";

			switch (error_code)
			{
			case 0:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K1703"));
				break;
			case 9990:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K9990"));
				break;
			case 9991:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K9991"));
				break;
			case 9992:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K9992"));
				break;
			case 9993:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K9993"));
				break;
			case 9994:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K9994"));
				break;
			case 9995:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K9995"));
				break;
			case 9996:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K9996"));
				break;
			case 9997:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K9997"));
				break;
			case 9998:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K9998"));
				break;
			case 9999:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K9999"));
				break;
			case 10000:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K10000"));
				break;
			case 10001:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K10001"));
				break;
			case 10002:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K10002"));
				break;
			case 10003:
                error_code_str = QString(GlobalData::LoadLanguageInfo("K10003"));
				break;
			default:
				error_code_str = QString("");
				break;
			}

			QTableWidgetItem *item5 = new QTableWidgetItem(error_code_str);
            item5->setTextAlignment(Qt::AlignCenter);
			if (error_code == 10003 || error_code==9990)
			{
                item5->setForeground(QColor(246, 180, 4));
			}
			else
			{
                item5->setBackground(Qt::gray);
			}
			tableWidget->setItem(item_number, 5, item5);
			item_number++;
		}

		mainLayout->addWidget(tableWidget, 1, 0);
		mark_showPicLabel = new QLabel(this);
		p.end();
		pix.save("mark_pic.png");
		QPixmap mark_pic = QPixmap("mark_pic.png");
		mark_showPicLabel->setPixmap(mark_pic);
		mark_showPicLabel->setScaledContents(true);
		mark_showPicLabel->resize(mark_showPicLabel->width(), mark_showPicLabel->height());
		mainLayout->addWidget(mark_showPicLabel, 2, 0);
        closeButton = new QPushButton(GlobalData::LoadLanguageInfo("K1183"),this);
		show_all_pic_Button = new QPushButton(GlobalData::LoadLanguageInfo("K1184"),this);
		show_all_pic_Button_correction = new QPushButton(GlobalData::LoadLanguageInfo("K1681"),this);
		saveButton = new QPushButton(GlobalData::LoadLanguageInfo("K1141"), this);
        bottomBarLayout = new QGridLayout(this);
		bottomBarLayout->setSpacing(5);
		bottomBarLayout->setMargin(5);
		bottomBarLayout->addWidget(closeButton, 0, 0);
		bottomBarLayout->addWidget(show_all_pic_Button, 0, 1);
		bottomBarLayout->addWidget(show_all_pic_Button_correction, 0, 2);
		bottomBarLayout->addWidget(saveButton, 0, 3);
		mainLayout->addLayout(bottomBarLayout, 3, 0);
        connect(closeButton, &QPushButton::clicked, this,[=]()
		{
            close();
        });
        connect(show_all_pic_Button, &QPushButton::clicked, this,[=]()
		{
			QString analysised_piture_path = "original";
			QString strPath = piture_root_str + "\\" + analysised_piture_path;
			QString file_name = QString("%0\\%1.png").arg(strPath).arg(testIda);  //testIda
			QPixmap result_pic = QPixmap(file_name);
			ShowAllPicWidgets show_all_pic_w1 = new ShowAllPicWidgets();
			show_all_pic_w1.ShowPic(file_name);
			show_all_pic_w1.exec();
        });

        connect(show_all_pic_Button_correction, &QPushButton::clicked, this,[=]()
		{
			QString analysised_piture_path = "analysised";
			QString strPath = piture_root_str + "\\" + analysised_piture_path;
			QString file_name = QString("%0\\%1_new1.png").arg(strPath).arg(testIda);  //testIda
			QPixmap result_pic = QPixmap(file_name);
			ShowAllPicWidgets show_all_pic_w1 = new ShowAllPicWidgets();
			show_all_pic_w1.ShowPic(file_name);
			show_all_pic_w1.exec();
        });

		connect(saveButton, &QPushButton::clicked, this, [=]() 
		{
            QVector <QVector<QString>> results{};
			for (int i = 0; i < row_numbers; i++)
			{
				QVector<QString> values{};
				values.push_back(tableWidget->item(i, 6)->text());
				values.push_back(tableWidget->item(i, 1)->text());
				values.push_back(tableWidget->item(i, 2)->text());
				values.push_back(tableWidget->item(i, 3)->text());
                results.push_back(values);
			}
            if(!dao->updateTestResult(results))
                QMessageBox::information(this,GlobalData::LoadLanguageInfo("K1180"),GlobalData::LoadLanguageInfo("K1294"),GlobalData::LoadLanguageInfo("K1181"));
            else
                emit sglUpdateUI();
		});
	}

    for (int row = 0; row < tableWidget->rowCount(); ++row)
    {
        for (int column = 0; column < tableWidget->columnCount(); ++column)
        {
            auto item = tableWidget->item(row, column);
            if (column == 0 || column == 4 || column == 5 || column == 6)
                item->setFlags(Qt::ItemIsEnabled);// 第0列不可编辑
            else
                item->setForeground(QBrush(QColor(0, 0, 250)));
            tableWidget->setItem(row, column, item);
        }
    }
}

void TestResultDetailDialog::exportSlot()
{
	QTextDocument  textDocument;
	QPrinter printer(QPrinter::ScreenResolution);
	printer.setPaperSize(QPrinter::A4);
	printer.setPageMargins(30, 30, 30, 30, QPrinter::DevicePixel);
	printer.setOutputFormat(QPrinter::PdfFormat);
	QString file_name = "";
	file_name = QString("tmp%1").arg(".pdf");
	printer.setOutputFileName(file_name);
	QPainter painter(&printer);
	QFont font;
	font.setPixelSize(15);
	painter.setFont(font);
	QTextOption textOption(Qt::AlignCenter);
	QPen pen;
	pen.setColor(Qt::black);
	pen.setWidth(1);
	painter.setPen(pen);
	textDocument.print(&printer);
    QPrintDialog dlg(&printer);
    qDebug() << dlg.exec();
}

void TestResultDetailDialog::paintRequestedHandler(QPrinter *printerPixmap)
{
	//QPageLayout("A4", Landscape, l:0 r:0 t:0 b:0 pt);   
    QPainter* pPdfPainter = new QPainter(printerPixmap);
	QTextOption option(Qt::AlignHCenter | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WordWrap);
	int iTop = 0;
    int lineheihgt = 30;
	int iContentWidth = 700;// pPdfWriter->width();
	QFont font;
    font.setFamily("宋体");
	int fontSize = 18;

	font.setPointSize(fontSize);
    pPdfPainter->setFont(font);
	QString str = "";

    QString sz13 = GlobalData::LoadLanguageInfo("K1185");

    str = sz13;
    pPdfPainter->drawText(QRect(0, iTop, iContentWidth, 90), str, option);
	iTop += 90;
    iTop += 10;
	fontSize = 11;
	font.setPointSize(fontSize);
	pPdfPainter->setFont(font);
	QTextOption detailoption(Qt::AlignVCenter);
	detailoption.setWrapMode(QTextOption::WordWrap);
    int rows = tableWidget->rowCount();
    int cols = tableWidget->columnCount() - 1;
	int colwidth = iContentWidth / cols;
    for (int i = 0; i < rows; i++)
	{
		pPdfPainter->setRenderHint(QPainter::Antialiasing, true);
        pPdfPainter->setPen(QPen(Qt::black, 2));
        pPdfPainter->drawLine(QPointF(0, iTop), QPointF(iContentWidth, iTop));
        pPdfPainter->drawLine(QPointF(0, iTop), QPointF(0, iTop + lineheihgt));
        pPdfPainter->drawLine(QPointF(iContentWidth, iTop), QPointF(iContentWidth, iTop + lineheihgt));
		for (int j = 0; j < cols; j++) {
			pPdfPainter->drawText(QRect(colwidth*j + 10, iTop, colwidth, lineheihgt), tableWidget->item(i, j)->text(), detailoption);
            pPdfPainter->drawLine(QPointF(colwidth*j, iTop), QPointF(colwidth*j, iTop + lineheihgt));
		}
		iTop += lineheihgt;
	}
	bool bResult = false;
	QString file_name = "";
	auto dao1 = AnalysisUIDao::instance();

	QString strPathFileName;
	QString piture_root_str = dao1->SelectTestPicturesRootPath(&bResult);
	QString analysised_piture_path = "analysised";
	QString strPath = piture_root_str + "\\" + analysised_piture_path;
	file_name = QString("%0\\%1.png").arg(strPath).arg(m_testId);  //testIda
    pPdfPainter->drawLine(QPointF(0, iTop), QPointF(iContentWidth, iTop));
	QPixmap result_pic = QPixmap(file_name);
	QPixmap pixmap(file_name);
    pPdfPainter->scale(0.5, 1);
	pPdfPainter->drawPixmap(0, iTop + 50, pixmap);
	pPdfPainter->setPen(QColor(0, 0, 0));
	delete pPdfPainter;

}

QString TestResultDetailDialog::CaculateResultText(double dItemGrayRatio)
{
	QString resultText = "";
	if (dItemGrayRatio <= 0.8)
	{
		resultText = "-";
	}
	if (dItemGrayRatio > 0.8 && dItemGrayRatio <= 1.2)
	{
		resultText = "O";
	}
	if (dItemGrayRatio > 1.2 && dItemGrayRatio <= 2.5)
	{
		resultText = "+";
	}
	if (dItemGrayRatio > 2.5 && dItemGrayRatio <= 4)
	{
		resultText = "++";
	}
	if (dItemGrayRatio > 4)
	{
		resultText = "+++";
	}
    return resultText;
}

void TestResultDetailDialog::OnClickModifyOneTestResult()
{
	//emit UpdateTestResultTableSignal(testId);
}

TestResultDetailDialog::~TestResultDetailDialog()
{
}
