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

TestResultDetailDialog::TestResultDetailDialog(QString testIda,QString sample_no,QWidget *parent) : QDialog()
{
	setWindowIcon(QIcon(":/favicon.ico"));
	setWindowIcon(QIcon(":/images/buttonIcon/icon.png"));
	bool bResult = true; 
	auto dao = AnalysisUIDao::instance();
	QString company_info = dao->SelectTargetValue(&bResult, "5");
	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
	setWindowTitle(GlobalData::LoadLanguageInfo(g_language_type, "K1704"));
	int windows_width = 0;// 1500;
	if (company_info == "2")
	{
		windows_width = 1900;
	}
	else
	{
		windows_width = 1500;
	}
	QDesktopWidget* desktop = QApplication::desktop(); 
	if (company_info == "2")
	{
		move(((desktop->width() - windows_width) / 2) - 0, ((desktop->height() - this->height()) / 2) - 170);
	}
	else
	{
		move(((desktop->width() - windows_width) / 2) - 30, ((desktop->height() - this->height()) / 2) - 170);
	}
	int width = this->geometry().width();
	int height = this->geometry().height();
	this->setFixedSize(windows_width, height + 300); 
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
	int error_code = 0;
	int top = 0;
	int height1 = 0;
	QString testResult = "";
	QString testGrayValue = "";
	auto TestDataQuery = dao->SelectTestDataByTestId(m_testId,&bResult);
	QString sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1173");
	QString sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1174");
	QString sz3 = GlobalData::LoadLanguageInfo(g_language_type, "K1175");
	if (bResult == false)
	{
		//MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "�������Խ������ʧ�ܣ�", MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		MyMessageBox::warning(this, sz1, sz2,  MyMessageBox::Ok, sz3, "");
		return;
	}
	mainLayout = new QGridLayout(this);
	noLabel = new QLabel;
	testIdLabel = new QLabel;
	topBarLayout = new QGridLayout;//����������ť�Ĳ���
	topBarLayout->addWidget(noLabel, 0, 1);
	topBarLayout->addWidget(testIdLabel, 0, 0);
	QString sz4 = GlobalData::LoadLanguageInfo(g_language_type, "K1049");
	testIdLabel->setText("     "+sz4+":"+sample_no);
	mainLayout->addLayout(topBarLayout, 0, 0);
	tableWidget = new QTableWidget;
	int row_numbers = TestDataQuery.size();
	tableWidget->setColumnCount(6);
	tableWidget->setRowCount(row_numbers);
	QString sz5 = GlobalData::LoadLanguageInfo(g_language_type, "K1175");
	QString sz6 = GlobalData::LoadLanguageInfo(g_language_type, "K1176");
	QString sz7 = GlobalData::LoadLanguageInfo(g_language_type, "K1177");
	QString sz8 = GlobalData::LoadLanguageInfo(g_language_type, "K1178");
	QString sz9 = GlobalData::LoadLanguageInfo(g_language_type, "K1179");
	QString sz10 = GlobalData::LoadLanguageInfo(g_language_type, "K1702");
	tableWidget->setHorizontalHeaderLabels(QStringList() << sz5 << sz6 << sz7 << sz8 << sz9 << sz10);
	tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ�еķ�ʽ
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //��ֹ�޸�
	tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //����Ϊ����ѡ�е���
	tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed); //����Ӧ�и�

	if (company_info == "2")
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
	tableWidget->selectRow(0);
	strRel = "";
	int item_number = 0;
	QString file_name = "";
	auto dao1 = AnalysisUIDao::instance();
	int sampleNo = 0;
	int nTestPaperID = 0;
	QString strPathFileName;
	QString piture_root_str = dao1->SelectTestPicturesRootPath(&bResult);
	QString analysised_piture_path = "analysised";
	QString strPath = piture_root_str + "\\" + analysised_piture_path;
	file_name = QString("%0\\%1.png").arg(strPath).arg(testIda);  //testIda
	QPixmap result_pic = QPixmap(file_name);
	int pic_width = result_pic.width();
	int pic_height = result_pic.height();

	if (result_pic.width() == 0)
	{
		QString sz10 = GlobalData::LoadLanguageInfo(g_language_type, "K1180");
		QString sz11 = GlobalData::LoadLanguageInfo(g_language_type, "K1182");
		QString sz12 = GlobalData::LoadLanguageInfo(g_language_type, "K1181");
		//QMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), tr("��ͼƬ��Ϣ"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"));
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
		while (TestDataQuery.next())
		{
			int tmp_item_number = item_number + 1;
			strItemName = TestDataQuery.value("projectName").toString();
			strItemName = strItemName.replace("\n", ""); // �����з��滻Ϊ���ַ�
			dRatioToCut = TestDataQuery.value("cutGrayValue").toDouble();
			int error_code = TestDataQuery.value("error_code").toInt();
			double tgv = TestDataQuery.value("testGrayValue").toDouble();
			error_code = TestDataQuery.value("error_code").toInt();
			if (tgv > 255)
			{
				testGrayValue = QString("%1").arg(GlobalData::LoadLanguageInfo(g_language_type, "K1261"));
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

			QTableWidgetItem *item_strItemName = new QTableWidgetItem(strItemName);
			item_strItemName->setTextAlignment(Qt::AlignCenter); // �����ı�������ʾ
			tableWidget->setItem(item_number, 0, item_strItemName);
			QString dRatioToCut_sz = "";
			if (strItemName == "FC")
			{
				dRatioToCut_sz = "\\";
			}
			else
			{
				dRatioToCut_sz = QString("%1").arg(dRatioToCut);
			}
			QTableWidgetItem *item_dRatioToCut = new QTableWidgetItem(dRatioToCut_sz);
			item_dRatioToCut->setTextAlignment(Qt::AlignCenter); // �����ı�������ʾ
			tableWidget->setItem(item_number, 1, item_dRatioToCut);

			if (strItemName != "FC" && strItemName != "Cut")
			{
				strRel = "";
				QString sql = "";
				sql.sprintf("select * from t_judge_rules where RulesId = (select RulesId from titem where itemName = '%s' and TestPaperID =%d ) order by GrayValue asc", strItemName.toUtf8().data(), paperId);
				auto JudgeRulesQuery = dao->SelectRecord(&bResult, sql);
				QMap<double, QString> mapJudgeRules;
				testResult = "";
				while (JudgeRulesQuery.next())
				{
					double grayValue = JudgeRulesQuery.value("GrayValue").toDouble();
					QString grayWord = JudgeRulesQuery.value("GrayWord").toString();
					mapJudgeRules.insert(grayValue, grayWord);
				}
				QList<double> key_list;
				QList<QString> value_list;
				QMap<double, QString>::Iterator it = mapJudgeRules.begin();
				int tmp_i = 0;
				while (it != mapJudgeRules.end())
				{
					if (tmp_i == 0)
					{
						key_list.push_back(-1000);
						value_list.push_back(it.value());
					}
					key_list.push_back(it.key());
					value_list.push_back(it.value());

					if (tmp_i == (mapJudgeRules.count()-1))
					{
						key_list.push_back(2000);
						value_list.push_back(it.value());
					}
					tmp_i++;
					it++;
				}
				int key_count = key_list.count();
				//�ҳ��±꣬�Ӷ��ҳ�key��Ӧ��value
				int find_index = 0;
				for (int i = 0; i < key_count; )
				{
					double min = key_list[0];;
					double max = 1000;
					if (i > 0)
					{
						min = key_list[i - 1];
						max = key_list[i];

						if (dRatioToCut > min && dRatioToCut <= max)
						{
							find_index = i;
						}
					}
					i++;
				}
				if (value_list.count() > 0)
				{
					testResult = value_list[find_index];//mapJudgeRules.find(find_index).value();//.key();
				}
				strRel += testResult;
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
			item_resut->setTextAlignment(Qt::AlignCenter); // �����ı�������ʾ
			tableWidget->setItem(item_number, 2, item_resut);

			if (error_code >0 && error_code != 10002 )
			{
				if (error_code == 10003)
				{
                    QString gray_value_str = QString("%1").arg(testGrayValue.toDouble());
					QTableWidgetItem *item = new QTableWidgetItem(gray_value_str);
					tableWidget->setItem(item_number, 3, item);
					item->setTextAlignment(Qt::AlignCenter); // �����ı�������ʾ
					tableWidget->item(item_number, 3)->setBackground(Qt::red); // ���õ�Ԫ�񱳾���ɫΪ��ɫ
				}
				else
				{
                    QString gray_value_str = QString("%1").arg(testGrayValue.toDouble());
					QTableWidgetItem *item = new QTableWidgetItem(gray_value_str);
					item->setTextAlignment(Qt::AlignCenter); // �����ı�������ʾ
					tableWidget->setItem(item_number, 3, item);
				}

			}else
			{
                QString gray_value_str = QString("%1").arg(testGrayValue.toDouble());
				QTableWidgetItem *item = new QTableWidgetItem(gray_value_str);
				tableWidget->setItem(item_number, 3, item);
				item->setTextAlignment(Qt::AlignCenter); // �����ı�������ʾ
				tableWidget->item(item_number, 3)->setBackground(Qt::red); // ���õ�Ԫ�񱳾���ɫΪ��ɫ
			}

			QTableWidgetItem *item4 = new QTableWidgetItem(i_text);
			item4->setTextAlignment(Qt::AlignCenter); // �����ı�������ʾ
			tableWidget->setItem(item_number, 4, item4);
			QString error_code_str = "";

			switch (error_code)
			{
			case 0:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K1703"));//QString("����");
				break;
			case 9990:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K9990"));//"��һ�����ȳ���Χ���ҵ��˵ڶ�����Ч�����ڵ�������Ч����");
				break;
			case 9991:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K9991"));//QString("��һ�����ȳ���Χ�ҵڶ������Ȼ�С����С��δ�ҵ�������");
				break;
			case 9992:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K9992"));//QString(" ��һ�����ȳ���Χ�ҵڶ������Ȼ��������");
				break;
			case 9993:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K9993"));//QString("��һ�����ȳ����ҵڶ������Ȼ��ǳ���");
				break;
			case 9994:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K9994"));//QString("�ӽ�һ��ƽ��");
				break;
			case 9995:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K9995"));//QString("û���ҵ��������������������󲨿�");
				break;
			case 9996:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K9996"));//QString("û���ҵ��������������򲻴�����󲨿�");
				break;
			case 9997:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K9997"));//QString("���½���, ������");
				break;
			case 9998:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K9998"));//QString("��������, ���½���");
				break;
			case 9999:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K9999"));//QString("���½��غ������ص���û����Ч����");
				break;
			case 10000:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K10000"));//QString("δ�ҵ���Ч��������ֵ�������趨����ֵ");
				break;
			case 10001:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K10001"));//QString("���������������쳣��");
				break;
			case 10002:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K10002"));//QString("����������Ч����");
				break;
			case 10003:
				error_code_str = QString(GlobalData::LoadLanguageInfo(g_language_type, "K10003"));//QString("����������Ч����");
				break;
			default:
				error_code_str = QString("");
				break;
			}

			QTableWidgetItem *item5 = new QTableWidgetItem(error_code_str);
			item5->setTextAlignment(Qt::AlignCenter); // �����ı�������ʾ
			if (error_code == 10003 || error_code==9990)
			{
				//item5->setBackground(Qt::yellow); // ���ñ�����ɫΪ��ɫ
				item5->setForeground(QColor(246, 180, 4));  //# ����Ϊ��ɫ
			}
			else
			{
				item5->setBackground(Qt::gray); // ���ñ�����ɫΪ
			}
			tableWidget->setItem(item_number, 5, item5);
			item_number++;
		}

		mainLayout->addWidget(tableWidget, 1, 0);
		mark_showPicLabel = new QLabel;
		p.end();
		pix.save("mark_pic.png");
		QPixmap mark_pic = QPixmap("mark_pic.png");
		mark_showPicLabel->setPixmap(mark_pic);
		mark_showPicLabel->setScaledContents(true);
		mark_showPicLabel->resize(mark_showPicLabel->width(), mark_showPicLabel->height());
		mainLayout->addWidget(mark_showPicLabel, 2, 0);
		QString sz13 = GlobalData::LoadLanguageInfo(g_language_type, "K1183");
		closeButton = new QPushButton(sz13);//�رնԻ���ť
		sz13 = GlobalData::LoadLanguageInfo(g_language_type, "K1184");
		//show_all_pic_Button = new QPushButton(tr("����ͼ��"));//�رնԻ���ť
		show_all_pic_Button = new QPushButton(sz13);//
		sz13 = GlobalData::LoadLanguageInfo(g_language_type, "K1681");
		show_all_pic_Button_correction = new QPushButton(sz13);//
		bottomBarLayout = new QGridLayout;//����������ť�Ĳ���
		bottomBarLayout->setSpacing(5);
		bottomBarLayout->setMargin(5);
		bottomBarLayout->addWidget(closeButton, 0, 0);
		bottomBarLayout->addWidget(show_all_pic_Button, 0, 1);
		bottomBarLayout->addWidget(show_all_pic_Button_correction, 0, 2);
		mainLayout->addLayout(bottomBarLayout, 3, 0);
		connect(closeButton, &QPushButton::clicked, this,
			[=]()
		{
		QWidget:close();
		}
		);
		connect(show_all_pic_Button, &QPushButton::clicked, this,
			[=]()
		{
			QString analysised_piture_path = "original";
			QString strPath = piture_root_str + "\\" + analysised_piture_path;
			QString file_name = QString("%0\\%1.png").arg(strPath).arg(testIda);  //testIda
			QPixmap result_pic = QPixmap(file_name);
			int height = result_pic.height();
			int width = result_pic.width();
			ShowAllPicWidgets show_all_pic_w1 = new ShowAllPicWidgets();
			show_all_pic_w1.ShowPic(file_name);
			show_all_pic_w1.exec();
		}
		);

		connect(show_all_pic_Button_correction, &QPushButton::clicked, this,
				[=]()
		{
			QString analysised_piture_path = "analysised";
			QString strPath = piture_root_str + "\\" + analysised_piture_path;
			QString file_name = QString("%0\\%1_new1.png").arg(strPath).arg(testIda);  //testIda
			QPixmap result_pic = QPixmap(file_name);
			int height = result_pic.height();
			int width = result_pic.width();
			ShowAllPicWidgets show_all_pic_w1 = new ShowAllPicWidgets();
			show_all_pic_w1.ShowPic(file_name);
			show_all_pic_w1.exec();
		}
		);
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
	int paperWidth = printer.width();
	int paperHeigth = printer.height();
	textDocument.print(&printer);
	QPrintDialog dlg(&printer);//������ӡҳ�棬�������ӡ��
	qDebug() << dlg.exec();//��ʾ��ӡ���棬����ֵ�жϵ������0��ʾȡ����1��ʾ��ӡ
}

void TestResultDetailDialog::paintRequestedHandler(QPrinter *printerPixmap)
{
	//QPageLayout("A4", Landscape, l:0 r:0 t:0 b:0 pt);
   //A4ֽ�Ŵ�С��Portrait����Landscape����l/r/t/b��������ҳ�߾ࣻ
	qDebug() << "��ǰҳ�沼�֣�" << printerPixmap->pageLayout();//����Ļ�ͼ�ο��⼸������
	QPainter* pPdfPainter = new QPainter(printerPixmap);   // qt���ƹ���
	// ����,����
	QTextOption option(Qt::AlignHCenter | Qt::AlignVCenter);
	option.setWrapMode(QTextOption::WordWrap); //�ֶ�̫���Զ�����
	// iTop �����ϱ���������
	int iTop = 0;
	int lineheihgt = 30; //�и�
	// �ı����� ȥ��ҳ�߾��ʢ��
	int iContentWidth = 700;// pPdfWriter->width();
	// ����,18����
	QFont font;
	//font.setFamily("simhei.ttf");
	font.setFamily("������");
	int fontSize = 18;

	font.setPointSize(fontSize);
	pPdfPainter->setFont(font);                    // Ϊ���ƹ�����������
	QString str = "";

	QString sz13 = GlobalData::LoadLanguageInfo(g_language_type, "K1185");

	str = sz13;//"�����";
	pPdfPainter->drawText(QRect(0, iTop, iContentWidth, 90), str, option); //��ӡ����
	iTop += 90;
	iTop += 10; //����10�����ؿո�
	fontSize = 11;
	font.setPointSize(fontSize);
	pPdfPainter->setFont(font);
	QTextOption detailoption(Qt::AlignVCenter);
	detailoption.setWrapMode(QTextOption::WordWrap);
	int rows = tableWidget->rowCount(); //ȡ������
	int cols = tableWidget->columnCount() - 1; //ȡ������ �������һ�� idd
	int colwidth = iContentWidth / cols;
	for (int i = 0; i < rows; i++) // ȡ��ÿ�����ӵ�����
	{
		// ������
		pPdfPainter->setRenderHint(QPainter::Antialiasing, true);
		// ���û�����ɫ
		pPdfPainter->setPen(QPen(Qt::black, 2)); //������ɫ�ʹ�ϸ
		// ����ֱ��
		pPdfPainter->drawLine(QPointF(0, iTop), QPointF(iContentWidth, iTop)); //�������
		pPdfPainter->drawLine(QPointF(0, iTop), QPointF(0, iTop + lineheihgt));//��һ������
		pPdfPainter->drawLine(QPointF(iContentWidth, iTop), QPointF(iContentWidth, iTop + lineheihgt));//���һ������
		for (int j = 0; j < cols; j++) {
			pPdfPainter->drawText(QRect(colwidth*j + 10, iTop, colwidth, lineheihgt), tableWidget->item(i, j)->text(), detailoption);
			pPdfPainter->drawLine(QPointF(colwidth*j, iTop), QPointF(colwidth*j, iTop + lineheihgt));//����
		}
		iTop += lineheihgt;
	}

	//��ȡ�ؼ�ͼ��
	bool bResult = false;
	QString file_name = "";
	auto dao1 = AnalysisUIDao::instance();

	QString strPathFileName;
	QString piture_root_str = dao1->SelectTestPicturesRootPath(&bResult);
	QString analysised_piture_path = "analysised";
	QString strPath = piture_root_str + "\\" + analysised_piture_path;
	file_name = QString("%0\\%1.png").arg(strPath).arg(m_testId);  //testIda
	pPdfPainter->drawLine(QPointF(0, iTop), QPointF(iContentWidth, iTop)); //���������
	QPixmap result_pic = QPixmap(file_name);
	QPixmap pixmap(file_name);
	pPdfPainter->scale(0.5, 1);   //�Ŵ�10��
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
	int a = 0;
	//���½���
	emit UpdateTestResultTableOneTypeSignal(m_testId);
	//emit UpdateTestResultTableSignal(testId);
}

void TestResultDetailDialog::on_pdfSaveButton_clicked()
{
	int a = 100;
}

void TestResultDetailDialog::on_printButton_clicked()
{
	int b = 100;
}

TestResultDetailDialog::~TestResultDetailDialog()
{
}
