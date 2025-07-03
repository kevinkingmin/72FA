#include "TestResultDataAll.h"
#include <QMessageBox>
#include <QLabel>
#include <QSqlQuery>
#include <QDate>
#include <QPainter>
#include <QFileDialog>
#include <QDesktopServices>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include "../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Model/result/JudgeRules.h"
#include "../Include/TCPClient/TcpClient.h"
#include "src/main/subDialog/ProgressDialog.h"
#include "../Include/Utilities/log.h"
#include "../main/mainwindow.h"
#include "src/main/subDialog/MyMessageBox.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "../Include/BLL/baseSet/SexBLL.h"
#include "../Include/Model/baseSet/SexModel.h"
#include "../Include/BLL/baseSet/AgeUnitBLL.h"
#include "../Include/Model/baseSet/AgeUnitModel.h"
#include "../Include/Instrument/Instrument.h"
#include "src/sample/subDialog/PatientDialog.h"
#include "../Include/Analysis/analysis.h"
#include "../Include/BLL/sample/SampleBLL.h"
#define PAGESIZE 27

TestResultDataAll::TestResultDataAll(QWidget *parent)
    : QWidget(parent)
    ,m_tcpClient(nullptr)
    ,m_progressDialog(nullptr)
    ,m_printIndexs{}
    ,m_itemCount(0)
{
    ui.setupUi(this);
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    QString page_size_database = dao->SelectTargetValue(&bResult, "20009");
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui.tableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(getItemDataSlot(int)));//表格双击事件

    bResult = true;

    QStringList headerString;
    QString sz1 = GlobalData::LoadLanguageInfo("K1156");//是否选中
    QString sz = GlobalData::LoadLanguageInfo("K1163");//是否选中
    QString sz2 = GlobalData::LoadLanguageInfo("K1157");
    QString sz3 = GlobalData::LoadLanguageInfo("K1158");
    QString sz4 = GlobalData::LoadLanguageInfo("K1159");
    QString sz5 = GlobalData::LoadLanguageInfo("K1160");
    QString sz6 = GlobalData::LoadLanguageInfo("K1161");
    QString sz7= GlobalData::LoadLanguageInfo("K1162");

    headerString << sz1 << sz2 << sz << sz3 << sz4 << sz5 << sz6 << sz7;
    ui.tableWidget->setHorizontalHeaderLabels(headerString);

    //隔行变色
    ui.tableWidget->setAlternatingRowColors(true);
    //去掉网格线
    ui.tableWidget->setShowGrid(false);
    //SET @auto_id = 0;
    //UPDATE tsample SET pkid = (@auto_id : = @auto_id + 1);
    //ALTER TABLE tsample AUTO_INCREMENT = 1;
    dao->ReNewPkid(&bResult);

    auto TestPaperListQuery = dao->SelectTestPaperIDs(m_test_project_name, &bResult);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1304"), MyMessageBox::Ok, "OK", "");
        return;
    }

    int nTestPaperTypeNumber = TestPaperListQuery.size();
    int nTestPaperID = 0;
    QString strTestPaperName;
    ui.comboBoxPaperID->addItem(GlobalData::LoadLanguageInfo("K1594"));

    m_paper_map.clear();
    while (TestPaperListQuery.next())
    {
        nTestPaperID = TestPaperListQuery.value("paperId").toInt();
        strTestPaperName = TestPaperListQuery.value("PaperName").toString();
        m_paper_map.insert(nTestPaperID, strTestPaperName);
        ui.comboBoxPaperID->addItem(strTestPaperName);
    }
    ui.comboBoxPaperID->setStyleSheet(QString(
        "QComboBox QAbstractItemView {"
        "background: rgb(0,192,192);"
        "   min-height: 70px;"   // 更改 item 高度为 40 像素
        "}"
    ));

    ui.comboBoxPaperID->setStyleSheet(QString(
        "QComboBox QAbstractItemView:item {"
        "background: rgb(0,192,192);"
        "   min-height: 70px;"   // 更改 item 高度为 40 像素
        "}"
    ));

    QDateTime dateTime = QDateTime::currentDateTime();
    QDateTime dateTime2 = dateTime.addSecs(3600 * 24);
    QDateTime dateTime3 = dateTime.addSecs(-3600 * 24*7);
    //QStringList listT = dateTime2.toString("yyyy:MM:dd").split(':');
    //ui.dateEdit_2->setTime(QTime(listT[0].toInt(), listT[1].toInt(), listT[2].toInt() + 1));
    //ui.dateEdit_2->setMaximumDate(QDate::currentDate().addDays(365));  // +365天
    //ui.dateEdit_2->setDisplayFormat("yyyy/MM/dd HH:mm:ss");  // 设置显示格式
    //ui.dateEdit_2->setSelectedSection(QDateTimeEdit::DaySection);  // 设置所选部分
    ui.dateEdit_2->setDateTime(dateTime2);


    ui.dateEdit->setDateTime(dateTime3);

    m_startx = 20;
    m_starty = 70;
    m_width1 = 1035;   //试出来的尺寸像素点
    m_height1 = 530;
    m_titleHeight = 35;
    m_colNum = 30;            //初始化
    m_rowNum = 20;           //计算表格的行数
    m_colWidth = m_width1 / m_colNum;
    m_rowHeight = m_height1 / m_rowNum;
    m_top = 30;
    m_bottom = 685;
    ui.pushButtonTopPage->setEnabled(false);

    ui.pushButtonSelectAll->setText(GlobalData::LoadLanguageInfo("K1081"));
    ui.pushButtonUpdateToLis->setText(GlobalData::LoadLanguageInfo("K1146"));

    ui.pushButtonPrint->setText(GlobalData::LoadLanguageInfo("K1147"));
    ui.pushButtonPrintA->setText(GlobalData::LoadLanguageInfo("K1148"));
    ui.pushButtonPdf->setText(GlobalData::LoadLanguageInfo("K1149"));
    ui.pushButtonPdfAll->setText(GlobalData::LoadLanguageInfo("K1150"));
    ui.label->setText(GlobalData::LoadLanguageInfo("K1151"));
    ui.label_2->setText(GlobalData::LoadLanguageInfo("K1152"));
    ui.label_3->setText(GlobalData::LoadLanguageInfo("K1153"));
    ui.pushButtonQuery->setText(GlobalData::LoadLanguageInfo("K1154"));
    ui.pushButton->setText(GlobalData::LoadLanguageInfo("K1155"));

    if (page_size_database == "")
    {
        ui.lineEditRowsPerPage->setText("24");
    }
    else
    {
        ui.lineEditRowsPerPage->setText(page_size_database);
    }
}

void TestResultDataAll::getItemDataSlot(int row)
{
    QTableWidgetItem *username = new QTableWidgetItem;
    QTableWidgetItem *qtw_sample_no = new QTableWidgetItem;
    username = ui.tableWidget->item(row, 1);
    qtw_sample_no = ui.tableWidget->item(row, 2);
    mytable = new ShowTestResultDetail(this);//实例化表格
    QString testId = username->text();
    QString sample_no = qtw_sample_no->text();
    //dialog->testId = testId;
    dialog = new TestResultDetailDialog(testId, sample_no,this);
    connect(dialog, &TestResultDetailDialog::sglUpdateUI, this, [this]{
        InitTableWidget("",m_currentPage);
    });
    //关联一个single
    dialog->exec();//显示弹窗
    //ui->usernameLineEdit->setText(username->text());
}

void TestResultDataAll::slotUpdateStatus(QString a, QString b)
{
    QString c = a;
    auto dao = AnalysisUIDao::instance();
    bool bResult = true;
    QString sql = QString("update tsample_test set sendLisFlag=3 where sendLisFlag =2 ");
    dao->SelectRecord(&bResult, sql);
    Show_UI_Data("");
}

//bool TestResultDataAll::nativeEvent(const QByteArray &eventType, void *message, long *result)
//{
//	//MSG *param = static_cast<MSG *>(message);
//	//switch (param->message)
//	//{
//	//case WM_COPYDATA:
//	//{
//	//	COPYDATASTRUCT *cds = reinterpret_cast<COPYDATASTRUCT*>(param->lParam);
//	//	QString content = "";
//	//	content = QString("%1").arg(reinterpret_cast<char*>(cds->lpData));//.arg(cds->lpData).arg(cds->lpData);
//	//	QString strMessage = QString::fromLocal8Bit(reinterpret_cast<char*>(cds->lpData), cds->cbData);
//	//	if (strMessage == "发送完成")
//	//	{
//	//		//更新列表
//	//		int finish = 0;
//	//		//emit sigUpdateTestResultData("aaaaaaaaaaaa", "bbbbbbbbbbbbb");
//	//	}
//	//	//QString strMessage1 = QString::fromLatin1(reinterpret_cast<char*>(cds->lpData), cds->cbData);
//	//	//QString strMessage2 = QString::fromStdString(reinterpret_cast<char*>(cds->lpData));
//	//	//QString strMessage3 = QString::fromStdWString(reinterpret_cast<char*>(cds->lpData));
//	//	//QString strMessage4 = QString::fromUtf8(reinterpret_cast<char*>(cds->lpData), cds->cbData);
//	//	QMessageBox::information(this, QStringLiteral(GlobalData::LoadLanguageInfo("K1180")), strMessage);
//	//	*result = 1;
//	//	return true;
//	//}
//	//}
//	int a = 111;
//	return QWidget::nativeEvent(eventType, message, result);
//}
TestResultDataAll::~TestResultDataAll()
{
}

void TestResultDataAll::Show_UI_Data(QString sz)
{
    InitTableWidget(sz, m_currentPage);//初始化状态列表
    m_query_condition1 = sz;



    //const QString VSCROLLBAR_STYLE33 =
    //	"QTableWidget::item:checked{\
    //background - color: rgb(255, 0, 255, 255);\
    //color: rgb(0, 255, 255, 255);\
    //}";

    //ui.tableWidget->setStyleSheet(VSCROLLBAR_STYLE33);

}

void TestResultDataAll::populateTable(int page) {
    // 清空表格
    ui.tableWidget->clearContents();

    // 计算显示的数据范围
    int startRow = (page - 1) * m_rowsPerPage;
    int endRow = startRow + m_rowsPerPage;

    // 设置数据
    for (int row = startRow; row < endRow && row < 1000; ++row) {
        // 设置单元格的内容
        // tableWidget->setItem(...);
    }

    // 更新表格显示
    ui.tableWidget->update();
}



void TestResultDataAll::on_pushButtonPrint_clicked()
{
	if (!getPrintIndexs(true))
		return;
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape); //打印方向 Portrait 纵向，Landscape：横向
    printer.setOutputFormat(QPrinter::NativeFormat);
    QPrintPreviewDialog preview(&printer);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printDocument(QPrinter*)));
    preview.setWindowState(Qt::WindowMaximized);
    preview.exec();
}

void TestResultDataAll::printDirect()
{
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPrinter::A4);
    QPrintDialog printDialog(&printer);
    printer.setOrientation(QPrinter::Landscape); //打印方向
    if (printDialog.exec() == QDialog::Accepted)
    {
        printDocument(&printer);
    }
}

void TestResultDataAll::on_pushButtonPrintA_clicked()
{
	int companyId = 0;
    QVector<QString> testIds = getPDFTestIds(companyId);
    if (m_all_page_number == 0)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1271"), GlobalData::LoadLanguageInfo("K1306"), MyMessageBox::Ok, "OK", "");
        return;
    }
	if (companyId == 6)
	{
        Instrument::instance()->getPDFReport(testIds);
        dLog(testIds.count());
		return;
	}
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait); //打印方向 Portrait 纵向，Landscape：横向
    printer.setOutputFormat(QPrinter::NativeFormat);
    QPrintPreviewDialog preview(&printer);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printDocumentA(QPrinter*)));
    preview.setWindowState(Qt::WindowMaximized);
    preview.exec();
}

void TestResultDataAll::printDirectA()
{
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPrinter::A4);
    QPrintDialog printDialog(&printer);
    printer.setOrientation(QPrinter::Landscape); //打印方向
    if (printDialog.exec() == QDialog::Accepted)
    {
        printDocument(&printer);
    }
}

void  TestResultDataAll::on_pushButtonPdf_clicked()
{
	int companyId = 0;
    QVector<QString> testIds = getPDFTestIds(companyId);
    if (m_all_page_number == 0 )
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1271"), GlobalData::LoadLanguageInfo("K1306"), MyMessageBox::Ok, "OK", "");
        return;
    }
	if (companyId == 6)
	{
        Instrument::instance()->getPDFReport(testIds);
        dLog(testIds.count());
		return;
	}
    SavePdfA();
}

void  TestResultDataAll::on_pushButtonPdfAll_clicked()
{
	if (!getPrintIndexs(true))
		return;
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape); //打印方向 Portrait 纵向，Landscape：横向
    printer.setOutputFormat(QPrinter::NativeFormat);
    printer.setOutputFormat(QPrinter::PdfFormat);//PDF格式
    QString fileName = "";
    QString current_time = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    QString report_path = dao->SelectTargetValueDes(&bResult, "4");
    fileName = QString("%1\\Report_Landscape_%2.pdf").arg(report_path).arg(current_time);
    printer.setOutputFileName(fileName);//输出到桌面
	int rowSize{ m_printIndexs.count() };
	int pagesize{ PAGESIZE };
	int page_count = rowSize / pagesize + (rowSize%pagesize > 0 ? 1 : 0);
	QPainter painter;
    for (int i = 0; i < page_count; i++)
    {
        painter.begin(&printer);
        painter.setPen(Qt::black);
		drawTable(&painter, i, pagesize);
        if (i != page_count - 1)
        {
            printer.newPage(); //新建页
        }
    }
    painter.end();
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName)); //打开PDF文件
}

void TestResultDataAll::SavePdf(QPainter* pPdfPainter,QString test_Id, QString result_data, QString sample_id, QString project_name, QList<float> PrintDataListCutGrayValue)
{

}

void TestResultDataAll::drawTableB(QPainter *painter, QString test_Id, QString result_data, QString sample_id, QString project_name, QList<float> PrintDataListCutGrayValue, QMap<QString, int> map_position)
{
    double max = *std::max_element(PrintDataListCutGrayValue.begin(), PrintDataListCutGrayValue.end());
    QString pic_name = "";
    //DB中取Testitems表数据
    bool bResult = true;
    auto dao = AnalysisUIDao::instance();
    QString paper_name = "";
    QString strPathFileName;
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString analysised_piture_path = "analysised";
    //QString strPath = piture_root_str + "\\" + m_test_project_name + "\\" + analysised_piture_path;
    QString strPath = piture_root_str + "\\" + analysised_piture_path;
    QPixmap pixBig;
    int startx = 30;
    int starty = 30;
    int width = 720;   //试出来的尺寸像素点
    int height = 1020;
    int titleHeight = 35;
    //m_colNum = 10;            //初始化
    //m_rowNum = 40;           //计算表格的行数
    int colWidth = 150; //列宽      //m_width / m_colNum;
    int colWidth1 = 90; //列宽      //m_width / m_colNum;
    int rowHeight = 22; // 行高    //m_height / m_rowNum;
    int top = 30;
    //调整表格整体的高度
    //总框体
    //painter->drawRect(m_startx, m_starty, m_width, m_height);
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //painter->setFont(QFont("宋体", 20));
    //painter->drawText(QRect(m_startx, m_top, m_width1, m_titleHeight), Qt::AlignLeft, QString("测试报表%1").arg(no));
    QImage img(":/images/buttonIcon/printlogo1.png");
    painter->drawImage(QRect(startx + 600, top - 10, 110, 43), img);
    //标题栏
    painter->drawLine(startx, starty + titleHeight, startx + width, starty + titleHeight);

    painter->drawText(QRect(startx, starty + titleHeight + rowHeight * 2, colWidth, rowHeight), Qt::AlignLeft, QString("Test：%1              ").arg(project_name));
    painter->drawText(QRect(startx, starty + titleHeight + rowHeight * 3, colWidth, rowHeight), Qt::AlignLeft, QString("Surname：%1              ").arg(""));
    painter->drawText(QRect(startx, starty + titleHeight + rowHeight * 4, colWidth, rowHeight), Qt::AlignLeft, QString("Name：%1              ").arg(""));
    painter->drawText(QRect(startx, starty + titleHeight + rowHeight * 5, colWidth, rowHeight), Qt::AlignLeft, QString("SampleNo：%1              ").arg(sample_id));

    m_PrintDataListValue.clear();
    m_PrintDataListProject.clear();
    QStringList list = result_data.split("(");//QString字符串分割函数
    m_PrintDataListProject.append("  " + list[0]);

    for (size_t ij = 1; ij < list.count(); ij++)
    {
        QStringList list1 = list[ij].split(")");
        if (ij == list.count() - 1)
        {
            m_PrintDataListValue.append(list1[0]);
        }
        else
        {
            m_PrintDataListValue.append(list1[0]);
            m_PrintDataListProject.append(list1[1]);
        }
    }

    for (size_t ik = 0; ik < m_PrintDataListValue.count(); ik++)
    {
        QString wtext = m_PrintDataListValue[ik];
        QString wtext1 = m_PrintDataListProject[ik];
        int position_value = 0;
        QString trimmedStr = wtext1.trimmed();
        if (map_position.contains(trimmedStr))
        {
            position_value = map_position[trimmedStr];
        }
        //painter->drawText(QRect(startx, starty + titleHeight + (rowHeight * (5 + ik) * 1.33) + 100, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(wtext1));
        //painter->drawText(QRect(startx, starty + titleHeight + ((rowHeight+1) * (5 + ik) * 1.33) + 100, colWidth, rowHeight+1), Qt::AlignLeft, QString("%1").arg(wtext1));
        painter->drawText(QRect(startx - 50, (260 + position_value * 0.4) - 12, colWidth, rowHeight + 1), Qt::AlignRight, QString("%1").arg(wtext1));
    }

    pixBig.load(strPath + "\\" + test_Id + ".png");  //图片路径
    int w1 = pixBig.width();
    if (w1 > 1800)
    {
        w1 = 1800;
    }
    int h1 = pixBig.height();
    painter->rotate(-270);

    if (h1 > 0 && w1 > 0)
    {
        //painter->drawPixmap(QRect(260, -170, 500, rowHeight), pixBig);
        painter->drawPixmap(QRect(260, -170, w1*0.4, h1*0.4), pixBig);
    }
    painter->rotate(-90);
    //第一个矩形
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter->drawRect(200, starty + titleHeight + (rowHeight * (6)) + 64, 225, 24 * rowHeight);
    int yy1 = starty + titleHeight + (rowHeight * (6)) + 64;
    int yy2 = yy1 + 24 * rowHeight + 6;

    //第一个矩形上面的线
    painter->drawLine(200, yy1 - 6, 200 + 225, yy1 - 6);

    painter->drawLine(200, yy1 - 6, 200, yy1 - 12);
    painter->drawText(QRect(200 - 3, yy1 - 28, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg("0"));
    painter->drawLine(275, yy1 - 6, 275, yy1 - 12);
    painter->drawText(QRect(275 - 3, yy1 - 28, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(max / 3));
    painter->drawLine(350, yy1 - 6, 350, yy1 - 12);
    painter->drawText(QRect(350 - 3, yy1 - 28, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(max * 2 / 3));
    painter->drawLine(425, yy1 - 6, 425, yy1 - 12);
    painter->drawText(QRect(425 - 3, yy1 - 28, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(max));
    //第一个矩形下面的线
    painter->drawLine(200, yy2, 200 + 225, yy2);
    painter->drawLine(200, yy2, 200, yy2 + 6);
    painter->drawText(QRect(200 - 3, yy2 + 10, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg("0"));
    painter->drawLine(275, yy2, 275, yy2 + 6);
    painter->drawText(QRect(275 - 3, yy2 + 10, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(max / 3));
    painter->drawLine(350, yy2, 350, yy2 + 6);
    painter->drawText(QRect(350 - 3, yy2 + 10, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(max * 2 / 3));
    painter->drawLine(425, yy2, 425, yy2 + 6);
    painter->drawText(QRect(425 - 3, yy2 + 10, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(max));

    int rect1_y1 = starty + titleHeight + (rowHeight * (6)) + 64;
    int rect1_x1 = 200;
    int rect1_width = 225;
    int rect1_x2 = 200 + 225;
    int line_y1 = 0;
    int line_rect1_x1 = 0;
    int line_x11 = 0;
    painter->setPen(QPen(Qt::black, 1, Qt::DashLine));

    QPen pen_3_dashe;
    pen_3_dashe.setBrush(QBrush(Qt::white));//设置笔刷，你可以不用设置
    QVector<qreal> dashes;
    qreal space = 2;
    dashes << 1 << space << 1 << space;
    pen_3_dashe.setDashPattern(dashes);
    pen_3_dashe.setWidth(2);

    for (size_t ik = 0; ik < 24; ik++)
    {
        line_y1 = ik * rowHeight;
        //painter->setPen(QPen(QBrush(Qt::white), 1, Qt::DashLine));
        painter->setPen(pen_3_dashe);
        if (ik != 0)
        {
            painter->drawLine(rect1_x1 + 2, rect1_y1 + line_y1, rect1_x2 - 2, rect1_y1 + line_y1);
        }
        for (int i = 0; i < 3; i++)
        {
            line_x11 = rect1_x1 + (225 / 3)*i;
            //QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
            //pen.setColor(QColor(242, 242, 242, 242));
            QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
            brush.setColor(QColor(111, 111, 111, 111));
            brush.setStyle(Qt::SolidPattern);
            //painter->setPen(pen);
            painter->setBrush(brush);
            //painter->drawRect(line_x11+2, rect1_y1 + line_y1+2, 75-2, rowHeight-2);
            painter->fillRect(line_x11, rect1_y1 + line_y1, 75, rowHeight, brush);//->drawRect(line_x11 + 2, rect1_y1 + line_y1 + 2, 75 - 2, rowHeight - 2);
        }
    }

    painter->setPen(pen_3_dashe);
    for (int i = 0; i < 3; i++)
    {
        line_rect1_x1 = rect1_x1 + (225 / 3)*i;
        if (i != 0)
        {
            painter->drawLine(line_rect1_x1, rect1_y1 + 2, line_rect1_x1, rect1_y1 + (24 * rowHeight) - 2);
        }
    }

    for (size_t ik = 0; ik < m_PrintDataListValue.count(); ik++)
    {
        QString wtext = m_PrintDataListValue[ik];
        int width = (PrintDataListCutGrayValue[ik] / max) * 225 * 1;
        QBrush brush1;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
        if (wtext == "+++") {
            brush1.setColor(QColor(255, 0, 0, 120));
        }
        else if (wtext == "++")
        {
            brush1.setColor(QColor(211, 167, 0, 200));
        }
        else if (wtext == "+")
        {
            brush1.setColor(QColor(255, 255, 0, 120));
        }
        else {
            brush1.setColor(QColor(242, 255, 255, 120));
        }
        brush1.setStyle(Qt::SolidPattern);
        painter->setBrush(brush1);


        QString wtext1 = m_PrintDataListProject[ik];
        int position_value = 0;
        QString trimmedStr = wtext1.trimmed();
        if (map_position.contains(trimmedStr))
        {
            position_value = map_position[trimmedStr];
        }
        int y_asis = (263 + position_value * 0.4) - 10;
        //painter->fillRect(startx + 170, starty + titleHeight + (rowHeight * (5 + ik) * 1.4) + 100, width, (rowHeight * 2) / 5, brush1);
        painter->fillRect(startx + 170, y_asis, width, (rowHeight * 2) / 5, brush1);
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
        //painter->drawText(QRect(startx + 172+ width, starty + titleHeight + (rowHeight * (5 + ik) * 1.4) + 100, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(wtext));
        if (trimmedStr == "FC" || trimmedStr == "Cut")
        {
            painter->drawText(QRect(startx + 172 + width, y_asis-2, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg("OK"));
        }
        else
        {
            painter->drawText(QRect(startx + 172 + width, y_asis-2, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(wtext));
        }
    }

    QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
    pen.setColor(QColor(255, 255, 255, 120));
    QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
    brush.setColor(QColor(255, 255, 255, 120));
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));

    //第二个矩形的内容画图
    painter->drawRect(200 + 250, starty + titleHeight + (rowHeight * (6)) + 64, colWidth1 * 3, (m_PrintDataListValue.count()*rowHeight) + rowHeight);
    painter->drawLine(200 + 250, starty + titleHeight + (rowHeight * (7)) + 64, 200 + 250 + colWidth1 * 3, starty + titleHeight + (rowHeight * (7)) + 64);
    int x1, y1, x2, y2;
    painter->setFont(QFont("宋体", 10));
    y1 = starty + titleHeight + (rowHeight * (6)) + 64;
    y2 = starty + titleHeight + (rowHeight * (6)) + 64 + (m_PrintDataListValue.count()*rowHeight) + rowHeight;
    x1 = 200 + 250;
    //绘制表格列单元线
    for (int i = 0; i < 3; i++)
    {
        x2 = x1 + colWidth1 * i;
        //painter->drawLine(x2, y1, x2, y2);
        switch (i)
        {
        case 0:
            painter->drawText(QRectF(x2, y1, colWidth1 + 20, rowHeight), Qt::AlignCenter, QString("Name").arg(i));
            painter->drawLine(x2, y1, x2, y2);
            break;
        case 1:
            painter->drawText(QRectF(x2 + 20, y1, colWidth1 - 20, rowHeight), Qt::AlignCenter, QString("Result").arg(i));
            painter->drawLine(x2 + 20, y1, x2 + 20, y2);
            break;
        case 2:
            painter->drawText(QRectF(x2, y1, colWidth1, rowHeight), Qt::AlignCenter, QString("Index").arg(i));
            painter->drawLine(x2, y1, x2, y2);
            break;
        default:
            break;
        }
    }
    int y11 = 0;
    int startx1 = 0;
    int startx2 = 0;
    for (size_t ik = 0; ik < m_PrintDataListValue.count(); ik++)
    {
        y11 = y1 + rowHeight + (rowHeight*ik);
        startx2 = x1 + colWidth1 * 3;
        painter->drawLine(x1, y11, startx2, y11);
        QString wtext = m_PrintDataListValue[ik];
        QString wtext1 = m_PrintDataListProject[ik];
        QString wtext2 = QString("%1").arg(PrintDataListCutGrayValue[ik]);


        QString trimmedStr = wtext1.trimmed();
        for (size_t i = 0; i < 3; i++)
        {
            startx1 = x1 + colWidth1 * i;
            switch (i)
            {
            case 0:
                painter->drawText(QRect(startx1, y11, colWidth1, rowHeight), Qt::AlignCenter, QString("%1").arg(wtext1));
                break;
            case 1:
                if (trimmedStr == "FC" || trimmedStr == "Cut")
                {
                    painter->drawText(QRect(startx1 + 20, y11, colWidth1 - 20, rowHeight), Qt::AlignCenter, QString("%1").arg("OK"));
                }
                else
                {
                    painter->drawText(QRect(startx1 + 20, y11, colWidth1 - 20, rowHeight), Qt::AlignCenter, QString("%1").arg(wtext));
                }
                break;
            case 2:
                painter->drawText(QRect(startx1, y11, colWidth1, rowHeight), Qt::AlignCenter, QString("%1").arg(wtext2));
                break;
            default:
                break;
            }
        }
    }
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter->drawLine(startx, starty + height, startx + width, starty + height);
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    //表最下面的备注
    QString rr = QString("Analysis 分析 %1.%2.%3 %4:%5,created by HumaBlot 72FA on %7").arg(test_Id.mid(0, 4)).arg(test_Id.mid(4, 2)).arg(test_Id.mid(6, 2)).arg(test_Id.mid(8, 2)).arg(test_Id.mid(10, 2)).arg(dateTime);
    painter->drawText(QRect(m_startx, starty + height + 2, 550, 25), Qt::AlignLeft, rr);
    //制表时间 2020-12-28
    //QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    painter->drawLine(startx + 515, starty + height - 40, startx + width, starty + height - 40);
    painter->drawText(QRect(startx + 400, starty + height - 37, 450, 25), Qt::AlignCenter, "Signature");
    //painter->drawText(QRect(m_startx + m_width - 200, m_starty + m_height + 2, 200, m_rowHeight), Qt::AlignRight, "制表时间：" + dateTime);
    //变回原来画笔和画刷
    QPen pen1; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
    pen1.setColor(QColor(255, 255, 255, 255));
    QBrush brush2;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
    brush2.setColor(QColor(255, 255, 255, 255));
    brush2.setStyle(Qt::SolidPattern);
    painter->setPen(pen1);
    painter->setBrush(brush2);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
}

void TestResultDataAll::drawTableA(QPainter *painter, QString test_Id, QString sample_id, QString project_name, const QVector<QSqlRecord> &testResults, QMap<QString, int> map_position)
{   
    QString pic_name = "";
    //DB中取Testitems表数据
    bool bResult = true;
    auto dao = AnalysisUIDao::instance();
    QString paper_name = "";
    QString strPathFileName;
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString analysised_piture_path = "analysised";
    //QString strPath = piture_root_str + "\\" + m_test_project_name + "\\" + analysised_piture_path;
    QString strPath = piture_root_str + "\\" + analysised_piture_path;
    QPixmap pixBig;
    int startx = 30;
    int starty = 30;
    int width = 720;   //试出来的尺寸像素点
    int height = 1020;
    int titleHeight = 35;
    //m_colNum = 10;            //初始化
    //m_rowNum = 40;           //计算表格的行数
    int colWidth = 150; //列宽      //m_width / m_colNum;
    int colWidth1 = 90; //列宽      //m_width / m_colNum;
    int rowHeight = 22; // 行高    //m_height / m_rowNum;
    int top = 30;
    //调整表格整体的高度
    //总框体
    //painter->drawRect(m_startx, m_starty, m_width, m_height);
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //painter->setFont(QFont("宋体", 20));
    //painter->drawText(QRect(m_startx, m_top, m_width1, m_titleHeight), Qt::AlignLeft, QString("测试报表%1").arg(no));
    QImage img(":/images/buttonIcon/printlogo1.png");
    painter->drawImage(QRect(startx+600, top - 10, 110, 43), img);
    //标题栏
    painter->drawLine(startx, starty + titleHeight, startx + width, starty + titleHeight);
    painter->drawText(QRect(startx, starty + titleHeight + rowHeight * 2, colWidth, rowHeight), Qt::AlignLeft, QString("Test：%1              ").arg(project_name));
    painter->drawText(QRect(startx, starty + titleHeight + rowHeight * 3, colWidth, rowHeight), Qt::AlignLeft, QString("Surname：%1              ").arg(""));
    painter->drawText(QRect(startx, starty + titleHeight + rowHeight * 4, colWidth, rowHeight), Qt::AlignLeft, QString("Name：%1              ").arg(""));
    painter->drawText(QRect(startx, starty + titleHeight + rowHeight * 5, colWidth, rowHeight), Qt::AlignLeft, QString("SampleNo：%1              ").arg(sample_id));
    double y_y_space_coefficient = 0.25;
    double y_y_start = 220;

    pixBig.load(strPath + "\\" + test_Id + ".png");  //图片路径
    int w1 = pixBig.width();
    if (w1 > 1800)
    {
        w1 = 2250;
        y_y_space_coefficient = 0.235;
        y_y_start = 247;
    }
    else
    {
        y_y_space_coefficient = 0.4;
        y_y_start = 268;
    }
	double max = 0;
	for (auto rd:testResults)
	{
		QString projectName = rd.value("projectName").toString();
		QString testResult = rd.value("testResult").toString();
		double cutGrayValue = rd.value("cutGrayValue").toDouble();
		if (max < cutGrayValue)
			max = cutGrayValue;
		int position_value = 0;
		if (map_position.contains(projectName.trimmed()))
		{
			position_value = map_position[projectName.trimmed()];
		}
		if (position_value > 0)
		{
			painter->drawText(QRect(startx - 50, (y_y_start + position_value * y_y_space_coefficient) - 12, colWidth, rowHeight + 1), Qt::AlignRight, QString("%1").arg(projectName));
		}
	}    
    int h1 = pixBig.height();
    painter->rotate(-270);
    if (h1 > 0 && w1 > 0)
    {
        //painter->drawPixmap(QRect(260, -170, 500, rowHeight), pixBig);
        painter->drawPixmap(QRect(y_y_start+10, -170, w1*y_y_space_coefficient, h1*y_y_space_coefficient), pixBig);
    }

    painter->rotate(-90);
    //第一个矩形
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter->drawRect(200, starty + titleHeight + (rowHeight * (6)) + 64, 225, 24 * rowHeight);
    int yy1 = starty + titleHeight + (rowHeight * (6)) + 64;
    int yy2 = yy1 + 24 * rowHeight + 6;

    //第一个矩形上面的线
    painter->drawLine(200, yy1 - 6, 200 + 225, yy1 - 6);

    painter->drawLine(200, yy1 - 6, 200, yy1 - 12);
    painter->drawText(QRect(200 - 3, yy1 - 28, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg("0"));
    painter->drawLine(275, yy1 - 6, 275, yy1 - 12);
    painter->drawText(QRect(275 - 3, yy1 - 28, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(max / 3));
    painter->drawLine(350, yy1 - 6, 350, yy1 - 12);
    painter->drawText(QRect(350 - 3, yy1 - 28, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(max * 2 / 3));
    painter->drawLine(425, yy1 - 6, 425, yy1 - 12);
    painter->drawText(QRect(425 - 3, yy1 - 28, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(max));
    //第一个矩形下面的线
    painter->drawLine(200, yy2 , 200 + 225, yy2 );
    painter->drawLine(200, yy2, 200, yy2 + 6);
    painter->drawText(QRect(200 - 3, yy2 + 10, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg("0"));
    painter->drawLine(275, yy2, 275, yy2 + 6);
    painter->drawText(QRect(275 - 3, yy2 + 10, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(max/3));
    painter->drawLine(350, yy2, 350, yy2 + 6);
    painter->drawText(QRect(350 - 3, yy2 + 10, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(max*2/3));
    painter->drawLine(425, yy2, 425, yy2 + 6);
    painter->drawText(QRect(425 - 3, yy2 + 10, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(max));

    int rect1_y1 = starty + titleHeight + (rowHeight * (6)) + 64;
    int rect1_x1 = 200;
    int rect1_width = 225;
    int rect1_x2 = 200 + 225;
    int line_y1 = 0;
    int line_rect1_x1 = 0;
    int line_x11 = 0;
    painter->setPen(QPen(Qt::black, 1, Qt::DashLine));

    QPen pen_3_dashe;
    pen_3_dashe.setBrush(QBrush(Qt::white));//设置笔刷，你可以不用设置
    QVector<qreal> dashes;
    qreal space = 2;
    dashes << 1 << space << 1 << space;
    pen_3_dashe.setDashPattern(dashes);
    pen_3_dashe.setWidth(2);


    for (size_t ik = 0; ik < 24; ik++)
    {
        line_y1 = ik * rowHeight;
        //painter->setPen(QPen(QBrush(Qt::white), 1, Qt::DashLine));
        painter->setPen(pen_3_dashe);
        if (ik != 0)
        {
            painter->drawLine(rect1_x1+2, rect1_y1 + line_y1, rect1_x2-2, rect1_y1 + line_y1);
        }

        for (int i = 0; i < 3; i++)
        {
            line_x11 = rect1_x1 + (225 / 3)*i;
            //QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
            //pen.setColor(QColor(242, 242, 242, 242));
            QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
            brush.setColor(QColor(111, 111, 111, 111));
            brush.setStyle(Qt::SolidPattern);
            //painter->setPen(pen);
            painter->setBrush(brush);
            //painter->drawRect(line_x11+2, rect1_y1 + line_y1+2, 75-2, rowHeight-2);
            painter->fillRect(line_x11, rect1_y1 + line_y1 , 75 , rowHeight , brush);//->drawRect(line_x11 + 2, rect1_y1 + line_y1 + 2, 75 - 2, rowHeight - 2);
        }
    }

    painter->setPen(pen_3_dashe);
    for (int i = 0; i < 3; i++)
    {
        line_rect1_x1 = rect1_x1 + (225 / 3)*i;
        if (i != 0)
        {
            painter->drawLine(line_rect1_x1, rect1_y1+2, line_rect1_x1, rect1_y1 + (24 * rowHeight)-2);
        }
    }


    for (auto rd:testResults)
    {
        QString wtext = rd.value("testResult").toString();
        int width = (rd.value("cutGrayValue").toDouble() / max)*225*1;
        QBrush brush1;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
        if (wtext == "+++") {
            brush1.setColor(QColor(255, 0, 0, 120));
        }
        else if (wtext == "++")
        {
            brush1.setColor(QColor(211, 167, 0, 200));
        }
        else if (wtext == "+")
        {
            brush1.setColor(QColor(255, 255, 0, 120));
        }else {
            brush1.setColor(QColor(242, 255, 255, 120));
        }
        brush1.setStyle(Qt::SolidPattern);
        painter->setBrush(brush1);


        QString wtext1 = rd.value("projectName").toString();
        int position_value = 0;
        QString trimmedStr = wtext1.trimmed();
        if (map_position.contains(trimmedStr))
        {
            position_value = map_position[trimmedStr];
        }
        if (position_value > 0)
        {
            int y_asis = (y_y_start + position_value * y_y_space_coefficient) - 10;
            //painter->fillRect(startx + 170, starty + titleHeight + (rowHeight * (5 + ik) * 1.4) + 100, width, (rowHeight * 2) / 5, brush1);
            painter->fillRect(startx + 170, y_asis, width, (rowHeight * 2) / 5, brush1);
            painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
            //painter->drawText(QRect(startx + 172+ width, starty + titleHeight + (rowHeight * (5 + ik) * 1.4) + 100, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(wtext));
            //painter->drawText(QRect(startx + 172 + width, y_asis, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(wtext));

            if (trimmedStr == "FC" || trimmedStr == "Cut")
            {
                painter->drawText(QRect(startx + 172 + width, y_asis - 2, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg("OK"));
            }
            else
            {
                painter->drawText(QRect(startx + 172 + width, y_asis - 2, colWidth, rowHeight), Qt::AlignLeft, QString("%1").arg(wtext));
            }
        }
    }

    QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
    pen.setColor(QColor(255, 255, 255, 120));
    QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
    brush.setColor(QColor(255, 255, 255, 120));
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));

    //第二个矩形的内容画图
    painter->drawRect(200+250, starty + titleHeight + (rowHeight * (6)) + 64, colWidth1 *3, (testResults.count()*rowHeight)+rowHeight);
    painter->drawLine(200 + 250, starty + titleHeight + (rowHeight * (7)) + 64, 200 + 250+colWidth1 * 3, starty + titleHeight + (rowHeight * (7)) + 64);
    int x1, y1, x2, y2;
    painter->setFont(QFont("宋体", 10));
    y1 = starty + titleHeight + (rowHeight * (6)) + 64;
    y2 = starty + titleHeight + (rowHeight * (6)) + 64 + (testResults.count()*rowHeight) + rowHeight;
    x1 = 200 + 250;
    //绘制表格列单元线
    for (int i = 0; i < 3; i++)
    {
        x2 = x1 + colWidth1 * i;
        //painter->drawLine(x2, y1, x2, y2);
        switch (i)
        {
        case 0:
            painter->drawText(QRectF(x2, y1, colWidth1+20, rowHeight), Qt::AlignCenter, QString("Name").arg(i));
            painter->drawLine(x2, y1, x2, y2);
            break;
        case 1:
            painter->drawText(QRectF(x2+20, y1, colWidth1-20, rowHeight), Qt::AlignCenter, QString("Result").arg(i));
            painter->drawLine(x2+20, y1, x2 + 20, y2);
            break;
        case 2:
            painter->drawText(QRectF(x2, y1, colWidth1, rowHeight), Qt::AlignCenter, QString("Index").arg(i));
            painter->drawLine(x2, y1, x2 , y2);
            break;
        default:
            break;
        }
    }

    int y11 = 0;
    int startx1 = 0;
    int startx2 = 0;

    for (int ik=0;ik<testResults.count();ik++)
    {
		auto rd = testResults.at(ik);
        y11 = y1 + rowHeight + (rowHeight*ik);
        startx2 = x1 + colWidth1 * 3;
        painter->drawLine(x1, y11, startx2, y11);
        QString wtext = rd.value("testResult").toString();
        QString wtext1 = rd.value("projectName").toString();
        QString wtext2 = rd.value("cutGrayValue").toString();

        QString trimmedStr = wtext1.trimmed();
        for (size_t i = 0; i < 3; i++)
        {
            startx1 = x1 + colWidth1 * i;
            switch (i)
            {
            case 0:
                painter->drawText(QRect(startx1, y11, colWidth1, rowHeight), Qt::AlignCenter, QString("%1").arg(wtext1));
                break;
            case 1:
                if (trimmedStr == "FC" || trimmedStr == "Cut")
                {
                    painter->drawText(QRect(startx1 + 20, y11, colWidth1 - 20, rowHeight), Qt::AlignCenter, QString("%1").arg("OK"));
                }
                else
                {
                    painter->drawText(QRect(startx1 + 20, y11, colWidth1 - 20, rowHeight), Qt::AlignCenter, QString("%1").arg(wtext));
                }
                break;
            case 2:
                painter->drawText(QRect(startx1, y11, colWidth1, rowHeight), Qt::AlignCenter, QString("%1").arg(wtext2));
                break;
            default:
                break;
            }
        }
    }

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter->drawLine(startx,starty + height, startx + width, starty + height);
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    //表最下面的备注
    QString rr = QString("Analysis 分析 %1.%2.%3 %4:%5,created by HumaBlot 72FA on %7").arg(test_Id.mid(0, 4)).arg(test_Id.mid(4, 2)).arg(test_Id.mid(6, 2)).arg(test_Id.mid(8, 2)).arg(test_Id.mid(10, 2)).arg(dateTime);
    painter->drawText(QRect(m_startx, starty + height + 2, 550, 25), Qt::AlignLeft, rr);
    //制表时间 2020-12-28
    //QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    painter->drawLine(startx + 515, starty + height - 40, startx + width, starty + height - 40);
    painter->drawText(QRect(startx+400, starty + height - 37, 450, 25), Qt::AlignCenter, "Signature");
    //painter->drawText(QRect(m_startx + m_width - 200, m_starty + m_height + 2, 200, m_rowHeight), Qt::AlignRight, "制表时间：" + dateTime);
}

void TestResultDataAll::drawTableC(QPainter *painter, int no)
{
    //调整表格整体的高度
    //总框体
    //painter->drawRect(m_startx, m_starty, m_width1, m_height1);
    //标题栏
    //painter->drawLine(m_startx, m_starty + m_titleHeight, m_startx + m_width1, m_starty + m_titleHeight);
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //painter->setFont(QFont("宋体", 20));
    //painter->drawText(QRect(m_startx, m_top, m_width1, m_titleHeight), Qt::AlignLeft, QString("测试报表%1").arg(no));
    QImage img(":/images/buttonIcon/printlogo1.png");
    //QRectF r{ m_startx, m_top,228,87 };
    painter->drawImage(QRect(m_startx, m_top - 10, 110, 43), img);
    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine));
    QString prject_name = ui.tableWidget->item(0, 3)->text();
    painter->drawText(QRect(m_startx + 10, m_top + 50, m_width1, m_titleHeight), Qt::AlignLeft, QString("%1").arg(prject_name));
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    //painter->setFont(QFont("宋体", 20));
    //2019 - 6 - 5 下午5:01
    //	HumaBlot 44FA
    painter->drawText(QRect(m_startx, m_top, m_width1, m_titleHeight), Qt::AlignRight, QString("%1   \r\n  HumaBlot 72FA").arg(dateTime));
    //painter->drawLine(m_startx, m_starty + m_height1, m_startx + m_width1, m_starty + m_height1);
    QString pic_name = "";
    //DB中取Testitems表数据
    bool bResult = true;
    auto dao = AnalysisUIDao::instance();
    QString paper_name = "";
    QString strPathFileName;
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString analysised_piture_path = "analysised";
    //QString strPath = piture_root_str + "\\" + m_test_project_name + "\\" + analysised_piture_path;
    QString strPath = piture_root_str + "\\" + analysised_piture_path;
    QPixmap pixBig;
    m_rowNum = 0;
    for (int i = 0; i < ui.tableWidget->rowCount(); i++)
    {
        bool selectRow = ui.tableWidget->item(i, 0)->checkState();//isItemSelected(ui.tableWidget->item(i, 7));
        if (selectRow)
        {
            m_rowNum++;
        }
    }
    m_colWidth = m_width1 / m_colNum;
    //m_rowHeight = m_height1 / m_rowNum;
    m_rowHeight = 20;
    m_height1 = 20 * m_rowNum;

    int x1, y1, x2, y2;
    painter->setFont(QFont("宋体", 10));
    QString testId = "";
    //QMessageBox::warning(nullptr, "设置提示", tip, QMessageBox::Ok);
    QString sample_id = "";
    QString test_Id = "";
    QString result_data = "";
    QString project_name = "";
    //m_colNum = 0;
    int rowNo = 1;
    x1 = m_startx;
    y1 = m_starty + m_titleHeight + m_rowHeight * rowNo;
    x2 = m_startx + m_width1;
    y2 = m_starty + m_titleHeight + m_rowHeight * rowNo;
    painter->drawLine(x1, y1, x2, y2);
    rowNo++;
    for (int i = 0; i < ui.tableWidget->rowCount(); i++)
    {
        bool selectRow = ui.tableWidget->item(i, 0)->checkState();//isItemSelected(ui.tableWidget->item(i, 7));
        if (selectRow)
        {
            test_Id = ui.tableWidget->item(i, 1)->text();
            result_data = dao->GetTestResultByTestId(test_Id);//ui.tableWidget->item(i, 7)->text();
            sample_id = ui.tableWidget->item(i, 2)->text();
            project_name = ui.tableWidget->item(i, 3)->text();
            //m_PrintDataList.append(test_Id + "|" + result_data + "|" + project_name + "|" + sample_id);
            //pixBig.load(strPath + "\\" + QString::number(nSampleID) + +"_" + QString::number(nTestPaperID) + ".png");  //图片路径
            pixBig.load(strPath + "\\" + test_Id + ".png");  //图片路径
            x1 = m_startx;
            y1 = m_starty + m_titleHeight + m_rowHeight * rowNo;
            x2 = m_startx + m_width1;
            y2 = m_starty + m_titleHeight + m_rowHeight * rowNo;
            int w1 = pixBig.width();
            if (w1 > 1416)
            {
                w1 = 1416;
            }
            int h1 = pixBig.height();
            if (h1 > 0 && w1 > 0)
            {
                painter->drawPixmap(QRect(x1 + 40, y1 - m_rowHeight + 5, m_colWidth * 9 - 20, m_rowHeight - 10), pixBig);//->drawPixmap(x, y, pixmap);
                QString str1 = "";
                m_PrintDataListValue.clear();
                m_PrintDataListProject.clear();
                QStringList list = result_data.split("(");//QString字符串分割函数
                m_PrintDataListProject.append("  " + list[0]);
                for (size_t ij = 1; ij < list.count(); ij++)
                {
                    QStringList list1 = list[ij].split(")");
                    if (ij == list.count() - 1)
                    {
                        m_PrintDataListValue.append(list1[0]);
                    }
                    else
                    {
                        m_PrintDataListValue.append(list1[0]);
                        m_PrintDataListProject.append(list1[1]);
                    }
                }
                int wtext_i = 0;
                QString wtext = "";
                QString wtext1 = "";
                int x11 = 0;
                int y11 = 0;
                int x21 = 0;
                for (size_t ik = 10; ik < (10 + m_PrintDataListValue.count()); ik++)
                {
                    wtext = m_PrintDataListValue[wtext_i];
                    wtext1 = m_PrintDataListProject[wtext_i];
                    x11 = m_startx + m_colWidth * ik;
                    y11 = m_starty + m_titleHeight;
                    x21 = m_startx + m_colWidth * ik;
                    //y2 = m_starty + m_height1 + m_titleHeight;
                    if (ik > 9 || ik == 1)
                    {
                        painter->drawLine(x11, y11, x21, y11);
                        if (ik != 1)
                        {
                            //QTransform transform;
                            //transform.rotate(+45.0);
                            //painter->setWorldTransform(transform);
                            //painter->rotate(90);
                            painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
                            painter->rotate(270);
                            painter->drawText(QRectF(-y11 - 30, x11 + 8, m_colWidth * 5, m_rowHeight), Qt::AlignTop | Qt::AlignLeft, QString("%1").arg(wtext1));
                            //painter->drawText(QRectF(x11, y11, m_colWidth, m_rowHeight), Qt::AlignCenter, QString("%1").arg(wtext1));
                            painter->rotate(90);
                            //transform.rotate(+315.0);
                            //painter->setWorldTransform(transform);
                            if (wtext == "+")
                            {
                                QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
                                pen.setColor(QColor(255, 255, 0, 120));
                                QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
                                brush.setColor(QColor(255, 255, 0, 120));
                                brush.setStyle(Qt::SolidPattern);
                                painter->setPen(pen);
                                painter->setBrush(brush);
                                painter->drawRect(x11, y1 - m_rowHeight, m_colWidth, m_rowHeight);
                            }
                            if (wtext == "++")
                            {
                                QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
                                pen.setColor(QColor(211, 167, 0, 200));
                                QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
                                brush.setColor(QColor(211, 167, 0, 200));
                                brush.setStyle(Qt::SolidPattern);
                                painter->setPen(pen);
                                painter->setBrush(brush);
                                painter->drawRect(x11, y1 - m_rowHeight, m_colWidth, m_rowHeight);
                            }
                            if (wtext == "+++")
                            {
                                QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
                                pen.setColor(QColor(255, 0, 0, 120));
                                QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
                                brush.setColor(QColor(255, 0, 0, 120));
                                brush.setStyle(Qt::SolidPattern);
                                painter->setPen(pen);
                                painter->setBrush(brush);
                                painter->drawRect(x11, y1 - m_rowHeight, m_colWidth, m_rowHeight);
                            }
                            painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
                            painter->drawText(QRectF(x11, y1 - m_rowHeight, m_colWidth, m_rowHeight), Qt::AlignCenter, QString("%1").arg(wtext));
                        }
                    }
                    wtext_i++;
                    //wtext_x1 = (m_colWidth-9) * (10+ ik);
                    ////wtext_x2 = m_colWidth * (8 + ik + 1);
                    //wtext = m_PrintDataListValue[ik];
                    //painter->drawText(QRect(wtext_x1 , y1 - m_rowHeight + 5, wtext_x1, m_rowHeight - 10), Qt::AlignCenter, QString("%1").arg(wtext));
                }
            }
            else
            {
                painter->drawText(QRect(x1 + 40, y1 - m_rowHeight + 5, m_colWidth * 9 - 20, m_rowHeight - 10), Qt::AlignCenter, QString("%1").arg("无结果"));
                //painter->drawText(QRect(colwidth*j + 10, iTop, colwidth, lineheihgt), "555555555", detailoption);
            }
            //标题
            if (rowNo > 1)
                painter->drawText(QRect(x1, y1 - m_rowHeight, m_colWidth, m_rowHeight), Qt::AlignCenter, QString("%1").arg(rowNo - 1));
            //行线
            //if (rowNo == m_rowNum) //最后一行不划线
            //{
            //	break;
            //}
            painter->drawLine(x1, y1, x2, y2);
            rowNo++;
        }
    }
    //第一行为序号
    //for (int rowNo = 0; rowNo <= m_rowNum; rowNo++)
    //{
    //	x1 = m_startx;
    //	y1 = m_starty + m_titleHeight + m_rowHeight * rowNo;
    //	x2 = m_startx + m_width1;
    //	y2 = m_starty + m_titleHeight + m_rowHeight * rowNo;
    //	//标题
    //	if (rowNo > 1)
    //		painter->drawText(QRect(x1, y1 - m_rowHeight, m_colWidth, m_rowHeight), Qt::AlignCenter, QString("%1").arg(rowNo - 1));
    //	//行线
    //	//if (rowNo == m_rowNum) //最后一行不划线
    //	//{
    //	//	break;
    //	//}
    //	painter->drawLine(x1, y1, x2, y2);
    //}
    //绘制表格列单元线
    for (int i = 1; i < m_colNum; i++)
    {
        x1 = m_startx + m_colWidth * i;
        y1 = m_starty + m_titleHeight;
        x2 = m_startx + m_colWidth * i;
        //y2 = m_starty + m_height1 + m_titleHeight;
        if (i > 9 || i == 1)
        {
            painter->drawLine(x1, y1, x2, y2);
            if (i != 1)
            {
                //painter->drawText(QRectF(x1, y1, m_colWidth, m_rowHeight), Qt::AlignCenter, QString("%1列").arg(i));
            }
        }
    }
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    //表最下面的备注
    //painter->drawText(QRect(m_startx, y2 + 12, 450, 25), Qt::AlignLeft, "注：测试报表备注信息。");
    //制表时间 2020-12-28
    //QString rr = "Analysis 分析 05.06.19 16:59, created by HumaBlot 44FA on 2019-06-05";
    QString rr = "Analysis 分析 05.06.19 16:59, created by HumaBlot 72FA on 2019-06-05";
    rr = QString("Analysis 分析 %1.%2.%3 %4:%5,created by HumaBlot 72FA on %7").arg(test_Id.mid(0, 4)).arg(test_Id.mid(4, 2)).arg(test_Id.mid(6, 2)).arg(test_Id.mid(8, 2)).arg(test_Id.mid(10, 2)).arg(dateTime); //QString("Analysis 分析 %1.%2.%3 %4:%5,created by HumaBlot 72FA on %7").arg(test_Id.mid(0, 4)));
    //.arg(test_Id.mid(6, 2)).arg(test_Id.mid(8, 2)).arg(test_Id.mid(10, 2)).arg(test_Id.mid(12, 2)).arg(dateTime)
    //painter->drawText(QRect(m_startx, m_bottom, 450, 25), Qt::AlignLeft, "注：测试报表备注信息。");
    painter->drawText(QRect(m_startx, m_bottom, 550, 25), Qt::AlignLeft, rr);
    //painter->drawText(QRect(m_startx + m_width1 - 200, y2 + 12, 200, m_rowHeight), Qt::AlignRight, "制表时间：" + dateTime);
    painter->drawLine(m_startx + m_width1 - 200, m_bottom, m_startx + m_width1, m_bottom);
    painter->drawText(QRect(m_startx + m_width1 - 200, m_bottom, 200, m_rowHeight), Qt::AlignRight, "Signature");
}

void TestResultDataAll::drawTable(QPainter *painter, int no, const int pagesize)
{
	QVector<int>printIndexs{};
	for (int i = no * pagesize; i < pagesize + no * pagesize; i++)
	{
		if (i >= m_printIndexs.count())
			break;
		printIndexs.push_back(m_printIndexs.at(i));
	}

	if (printIndexs.isEmpty())
		return;
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QImage img(":/images/buttonIcon/printlogo1.png");
    painter->drawImage(QRect(m_startx, m_top-10, 110, 43), img);
    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine));
    QString prject_name = ui.tableWidget->item(printIndexs.first(), 3)->text();
    painter->drawText(QRect(m_startx+10, m_top+50, m_width1, m_titleHeight), Qt::AlignLeft, QString("%1").arg(prject_name));
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter->drawText(QRect(m_startx, m_top, m_width1, m_titleHeight), Qt::AlignRight, QString("%1   \r\n  HumaBlot 72FA").arg(dateTime));
    QString pic_name = "";
    bool bResult = true;
    auto dao = AnalysisUIDao::instance();
    QString paper_name = "";
    QString strPathFileName;
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString analysised_piture_path = "analysised";
    //QString strPath = piture_root_str + "\\" + m_test_project_name + "\\" + analysised_piture_path;
    QString strPath = piture_root_str + "\\" + analysised_piture_path;
    QPixmap pixBig;
    m_rowNum = printIndexs.count();
    m_colWidth = m_width1 / m_colNum;
    //m_rowHeight = m_height1 / m_rowNum;
    m_rowHeight = 20;
    m_height1 = 20 * m_rowNum;
    int x1, y1, x2, y2;
    painter->setFont(QFont("宋体", 10));
    QString testId = "";
    //QMessageBox::warning(nullptr, "设置提示", tip, QMessageBox::Ok);
    QString sample_id = "";
    QString test_Id = "";
    QString result_data = "";
    QString project_name = "";
    //m_colNum = 0;
    int rowNo = 1;
    x1 = m_startx;
    y1 = m_starty + m_titleHeight + m_rowHeight * rowNo;
    x2 = m_startx + m_width1;
    y2 = m_starty + m_titleHeight + m_rowHeight * rowNo;
    painter->drawLine(x1, y1, x2, y2);
    rowNo++;

    for (auto index : printIndexs)
    {

        QPen pen1; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
        pen1.setColor(QColor(255, 255, 255, 255));
        QBrush brush2;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
        brush2.setColor(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        painter->setPen(pen1);
        painter->setBrush(brush2);
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));

        bool selectRow = ui.tableWidget->item(index, 0)->checkState();//isItemSelected(ui.tableWidget->item(i, 7));
        if (selectRow)
        {
            test_Id = ui.tableWidget->item(index, 1)->text();

            auto dao = AnalysisUIDao::instance();
			auto SampleTests = dao->SelectSamplesByTestId(test_Id);
            sample_id = ui.tableWidget->item(index, 2)->text();
            project_name = ui.tableWidget->item(index, 3)->text();
            pixBig.load(strPath + "\\" + test_Id + ".png");  //图片路径
            x1 = m_startx;
            y1 = m_starty + m_titleHeight + m_rowHeight * rowNo;
            x2 = m_startx + m_width1;
            y2 = m_starty + m_titleHeight + m_rowHeight * rowNo;
            int w1 = pixBig.width();

            if (w1 > 1416)
            {
                w1 = 1416;
            }

            int h1 = pixBig.height();
            if (h1 > 0 && w1 > 0)
            {
                painter->drawPixmap(QRect(x1 + 40, y1 - m_rowHeight + 5, w1*0.21, h1*0.21), pixBig);
                QString wtext = "";
                QString wtext1 = "";
                int x11 = 0;
                int y11 = 0;
                int x21 = 0;
                for (size_t ik = 12; ik < (12+ SampleTests.count()); ik++)
                {
					auto rd = SampleTests.at(ik - 12);
					wtext = rd.value("testResult").toString();
					wtext1 = "  " + rd.value("projectName").toString();
                    x11 = m_startx + m_colWidth * ik;
                    y11 = m_starty + m_titleHeight;
                    x21 = m_startx + m_colWidth * ik;
					painter->drawLine(x11, y11, x21, y11);
					QString fc_sz = "";
					QString cutoff_sz = "";
					fc_sz = QString("%1").arg(wtext1).replace(" ", "");
					if (fc_sz == "FC" || fc_sz == "Cut")
					{
						painter->setPen(QPen(Qt::white, 2, Qt::SolidLine));
						wtext1 = "";
					}
					else
					{
						painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
					}
					painter->rotate(270);
					painter->drawText(QRectF(-y11 - 30, x11 + 8, m_colWidth * 5, m_rowHeight), Qt::AlignTop | Qt::AlignLeft, QString("%1").arg(wtext1));
					painter->rotate(90);
					if (fc_sz == "FC" || fc_sz == "Cut")
					{
						painter->setPen(QPen(Qt::white, 2, Qt::SolidLine));
						if (fc_sz == "FC")
						{
							painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
							painter->drawText(QRectF(x11 - (m_colWidth * 2) + 5, y1 - m_rowHeight + 3, m_colWidth * 4, m_rowHeight), Qt::AlignLeft, QString("%1").arg(sample_id));
						}
						else
						{
							painter->drawText(QRectF(x11, y1 - m_rowHeight, m_colWidth, m_rowHeight), Qt::AlignCenter, QString("%1").arg(""));
						}

					}
					else if (wtext == "+")
					{
						QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
						pen.setColor(QColor(255, 255, 0, 120));
						QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
						brush.setColor(QColor(255, 255, 0, 120));
						brush.setStyle(Qt::SolidPattern);
						painter->setPen(pen);
						painter->setBrush(brush);
						painter->drawRect(x11, y1 - m_rowHeight, m_colWidth, m_rowHeight);
					}
					else if (wtext == "++")
					{
						QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
						pen.setColor(QColor(211, 167, 0, 200));
						QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
						brush.setColor(QColor(211, 167, 0, 200));
						brush.setStyle(Qt::SolidPattern);
						painter->setPen(pen);
						painter->setBrush(brush);
						painter->drawRect(x11, y1 - m_rowHeight, m_colWidth, m_rowHeight);
					}
					else if (wtext == "+++")
					{
						QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
						pen.setColor(QColor(255, 0, 0, 120));
						QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
						brush.setColor(QColor(255, 0, 0, 120));
						brush.setStyle(Qt::SolidPattern);
						painter->setPen(pen);
						painter->setBrush(brush);
						painter->drawRect(x11, y1 - m_rowHeight, m_colWidth, m_rowHeight);
					}
					if (fc_sz != "FC" && fc_sz != "Cut")
					{
						painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
						painter->drawText(QRectF(x11, y1 - m_rowHeight, m_colWidth, m_rowHeight), Qt::AlignCenter, QString("%1").arg(wtext));
					}
                }
            }
            else
            {
                painter->drawText(QRect(x1 + 40, y1 - m_rowHeight +5, m_colWidth * 9 - 20, m_rowHeight - 10), Qt::AlignCenter, QString("%1").arg("无结果"));
                //painter->drawText(QRect(colwidth*j + 10, iTop, colwidth, lineheihgt), "555555555", detailoption);
            }
            //标题
            if (rowNo > 1)
                painter->drawText(QRect(x1, y1 - m_rowHeight, m_colWidth, m_rowHeight), Qt::AlignCenter, QString("%1").arg(rowNo - 1));
            //行线
            //if (rowNo == m_rowNum) //最后一行不划线
            //{
            //	break;
            //}
            painter->drawLine(x1, y1, x2, y2);
            rowNo++;
        }
    }
    //第一行为序号
    //for (int rowNo = 0; rowNo <= m_rowNum; rowNo++)
    //{
    //	x1 = m_startx;
    //	y1 = m_starty + m_titleHeight + m_rowHeight * rowNo;
    //	x2 = m_startx + m_width1;
    //	y2 = m_starty + m_titleHeight + m_rowHeight * rowNo;
    //	//标题
    //	if (rowNo > 1)
    //		painter->drawText(QRect(x1, y1 - m_rowHeight, m_colWidth, m_rowHeight), Qt::AlignCenter, QString("%1").arg(rowNo - 1));
    //	//行线
    //	//if (rowNo == m_rowNum) //最后一行不划线
    //	//{
    //	//	break;
    //	//}
    //	painter->drawLine(x1, y1, x2, y2);
    //}
    //绘制表格列单元线
    for (int i = 1; i < m_colNum; i++)
    {
        x1 = m_startx + m_colWidth * i;
        y1 = m_starty + m_titleHeight;
        x2 = m_startx + m_colWidth * i;
        //y2 = m_starty + m_height1 + m_titleHeight;
        if (i > 9 || i == 1)
        {
            if (i == 11 || i == 12 || i == 13)
            {
            }
            else
            {
                painter->drawLine(x1, y1, x2, y2);
            }
            if (i != 1)
            {
                //painter->drawText(QRectF(x1, y1, m_colWidth, m_rowHeight), Qt::AlignCenter, QString("%1列").arg(i));
            }
        }
    }
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    //表最下面的备注
    //painter->drawText(QRect(m_startx, y2 + 12, 450, 25), Qt::AlignLeft, "注：测试报表备注信息。");
    //制表时间 2020-12-28
    //QString rr = "Analysis 分析 05.06.19 16:59, created by HumaBlot 44FA on 2019-06-05";
    QString rr = "Analysis 分析 05.06.19 16:59, created by HumaBlot 72FA on 2019-06-05";
    rr = QString("Analysis 分析 %1.%2.%3 %4:%5,created by HumaBlot 72FA on %7").arg(test_Id.mid(0, 4)).arg(test_Id.mid(4, 2)).arg(test_Id.mid(6, 2)).arg(test_Id.mid(8, 2)).arg(test_Id.mid(10, 2)).arg(dateTime); //QString("Analysis 分析 %1.%2.%3 %4:%5,created by HumaBlot 72FA on %7").arg(test_Id.mid(0, 4)));
    //.arg(test_Id.mid(6, 2)).arg(test_Id.mid(8, 2)).arg(test_Id.mid(10, 2)).arg(test_Id.mid(12, 2)).arg(dateTime)
    //painter->drawText(QRect(m_startx, m_bottom, 450, 25), Qt::AlignLeft, "注：测试报表备注信息。");
    painter->drawText(QRect(m_startx, m_bottom, 550, 25), Qt::AlignLeft, rr);
    //painter->drawText(QRect(m_startx + m_width1 - 200, y2 + 12, 200, m_rowHeight), Qt::AlignRight, "制表时间：" + dateTime);
    painter->drawLine(m_startx + m_width1 - 200, m_bottom, m_startx + m_width1, m_bottom);
    painter->drawText(QRect(m_startx + m_width1 - 200, m_bottom, 200, m_rowHeight), Qt::AlignRight, "Signature" );

}

void TestResultDataAll::SavePdfA()
{
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait); //打印方向 Portrait 纵向，Landscape：横向
    printer.setOutputFormat(QPrinter::NativeFormat);
    printer.setOutputFormat(QPrinter::PdfFormat);//PDF格式
    QString fileName = "";
    QString current_time = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    QString report_path = dao->SelectTargetValueDes(&bResult, "4");
    fileName = QString("%1\\Report_%2.pdf").arg(report_path).arg(current_time);
    printer.setOutputFileName(fileName);//输出到桌面
    QPainter painter;
    painter.begin(&printer);//开始在打印区域上绘制类容
    //painter.setRenderHint(QPainter::Antialiasing, true);
    QString test_Id = "";
    QString sample_id = "";
    QString project_name = "";
    int pkid = 0;
    int iii = 0;
    auto pm = SystemSetBLL().getRowById(5);
    int companyId = pm.isNull() ? 1 : pm->getSaveSet();
    for (int i = 0; i < ui.tableWidget->rowCount(); i++)
    {
        bool selectRow = ui.tableWidget->item(i, 0)->checkState();//isItemSelected(ui.tableWidget->item(i, 7));
        if (selectRow)
        {
            test_Id = ui.tableWidget->item(i, 1)->text();
            sample_id = ui.tableWidget->item(i, 2)->text();
            project_name = ui.tableWidget->item(i, 3)->text();
            pkid = ui.tableWidget->item(i, 8)->text().simplified().toInt();
            painter.setPen(Qt::black);
            bool bResult = true;
            auto dao = AnalysisUIDao::instance();
            auto SampleTests = dao->SelectSamplesByTestId(test_Id);
            if (bResult == false)
            {
                MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1304"), MyMessageBox::Ok, "OK", "");
                return;
            }

            QMap<QString, int> map_position;
            auto SelectLeftRightPositionQuery = dao->SelectLeftRightPosition(test_Id, &bResult);
            while (SelectLeftRightPositionQuery.next())
            {
                QString project_name = SelectLeftRightPositionQuery.value("projectName").toString();
                int position_value = SelectLeftRightPositionQuery.value("right_pix_position").toInt();
                map_position.insert(project_name, position_value);
            }
            painter.setPen(Qt::black);
            printOnePageA(&painter, test_Id, sample_id, project_name, SampleTests, map_position, pkid, companyId);
            if (iii != m_all_page_number - 1)
            {
                printer.newPage();
            }
            iii++;
        }
    }
    painter.end();//绘制结束
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName)); //打开PDF文件
}

void TestResultDataAll::SavePdfB()
{
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait); //打印方向 Portrait 纵向，Landscape：横向
    printer.setOutputFormat(QPrinter::NativeFormat);
    printer.setOutputFormat(QPrinter::PdfFormat);//PDF格式
    QString fileName = "";
    QString current_time = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    auto dao = AnalysisUIDao::instance();
    bool bResult;
    QString report_path = dao->SelectTargetValueDes(&bResult, "4");
    fileName = QString("%1\\Report_%2.pdf").arg(report_path).arg(current_time);
    printer.setOutputFileName(fileName);//输出到桌面
    QPainter painter;
    painter.begin(&printer);//开始在打印区域上绘制类容
    //painter.setRenderHint(QPainter::Antialiasing, true);
    QString test_Id = "";
    QString result_data = "";
    QString sample_id = "";
    QString project_name = "";
    int iii = 0;
    for (int i = 0; i < ui.tableWidget->rowCount(); i++)
    {
        bool selectRow = ui.tableWidget->item(i, 0)->checkState();//isItemSelected(ui.tableWidget->item(i, 7));
        if (selectRow)
        {
            test_Id = ui.tableWidget->item(i, 1)->text();
            result_data = dao->GetTestResultByTestId(test_Id);//ui.tableWidget->item(i, 7)->text();
            sample_id = ui.tableWidget->item(i, 2)->text();
            project_name = ui.tableWidget->item(i, 3)->text();
            painter.setPen(Qt::black);
            bool bResult = true;
            auto dao = AnalysisUIDao::instance();
            //灰度值列表
            QList<QString> PrintDataListGrayValue;
            QList<QString> PrintDataListCutGrayValue;
            PrintDataListGrayValue.clear();
            PrintDataListCutGrayValue.clear();
            auto SampleTests = dao->SelectSamplesByTestId(test_Id);
            if (bResult == false)
            {
                MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1304"), MyMessageBox::Ok, "OK", "");
                return;
            }

            QMap<QString, int> map_position;
            map_position.clear();
            auto SelectLeftRightPositionQuery = dao->SelectLeftRightPosition(test_Id, &bResult);
            while (SelectLeftRightPositionQuery.next())
            {
                QString project_name = SelectLeftRightPositionQuery.value("projectName").toString();
                int position_value = SelectLeftRightPositionQuery.value("right_pix_position").toInt();
                map_position.insert(project_name, position_value);
            }

            QList<float> PrintDataListCutGrayValue_list;
            PrintDataListCutGrayValue_list.clear();
            for (auto r : SampleTests)
            {
                PrintDataListCutGrayValue.append(r.value("cutGrayValue").toString());
                PrintDataListCutGrayValue_list.append(r.value("cutGrayValue").toFloat());
                PrintDataListGrayValue.append(r.value("testGrayValue").toString());
            }
            printOnePageB(&painter, test_Id, result_data, sample_id, project_name, PrintDataListCutGrayValue_list, map_position);
            //painter.drawText(printer.width() / 2 - 800, 600, QString("QTxxx1 ").arg(iii));
            if (iii != m_all_page_number - 1) //判断是否最后一页，如果不是最后一页则新建一页
            {
                printer.newPage(); //新建页
            }
            iii++;
        }
    }
    painter.end();//绘制结束
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName)); //打开PDF文件
}

bool TestResultDataAll::getPrintIndexs(const bool isSamePaper)
{
    m_printIndexs.clear();
    int totalItems = ui.tableWidget->rowCount();
    for (int i = 0; i < totalItems; i++)
    {
        if (ui.tableWidget->item(i, 0)->checkState())
            m_printIndexs.push_back(i);
    }
    if (m_printIndexs.isEmpty())
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1271"), GlobalData::LoadLanguageInfo("K1306"), MyMessageBox::Ok, "OK", "");
        return false;
    }
    if (m_printIndexs.count() >= 100)
    {
        QString tip = QString("%2 %1").arg(m_rowNum).arg(GlobalData::LoadLanguageInfo("K1307"));
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1271"), tip, MyMessageBox::Ok, "OK", "");
        return false;
    }

    if (!isSamePaper)
        return true;

    QString paperName{ ui.tableWidget->item(m_printIndexs.first(), 3)->text() };
    int pkId{ ui.tableWidget->item(m_printIndexs.first(), 8)->text().toInt() };
    m_itemCount = AnalysisUIDao::instance()->getPaperItemCountBySampleId(pkId);
    for (auto index : m_printIndexs)
    {
        if (paperName != ui.tableWidget->item(index, 3)->text())
        {
            m_itemCount = 0;
            QString str = QString("概述操作，只能选择一个项目,当前选择的项目有：%1,%2").arg(paperName).arg(ui.tableWidget->item(index, 3)->text());
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1271"), str, MyMessageBox::Ok, "OK", "");
            return false;
        }
    }
    return true;
}

QVector<QString> TestResultDataAll::getPDFTestIds(int & companyId)
{
	m_all_page_number = 0;
    _pkidVect.clear();
    QVector<QString>outVect{};
	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		bool selectRow = ui.tableWidget->item(i, 0)->checkState();//isItemSelected(ui.tableWidget->item(i, 7));
		if (selectRow)
		{
			m_all_page_number++;
            _pkidVect.push_back(ui.tableWidget->item(i, 8)->text().toInt());
            outVect.push_back(ui.tableWidget->item(i, 1)->text());
		}
	}
	auto pm = SystemSetBLL().getRowById(5);
	companyId = pm.isNull() ? 0 : pm->getSaveSet();
    return outVect;
}

void TestResultDataAll::printDocumentA(QPrinter *printer)
{
    QString test_Id = "";
    QString result_data = "";
    QString sample_id = "";
    QString project_name = "";
    QPainter painter;
    int pkid = 0;
    auto dao = AnalysisUIDao::instance();
    //printOnePageA(&painter, test_Id, result_data, sample_id, project_name);
    int iii = 0;
    auto pm = SystemSetBLL().getRowById(5);
    int companyId = pm.isNull() ? 1 : pm->getSaveSet();
    for (int i = 0; i < ui.tableWidget->rowCount(); i++)
    {
        bool selectRow = ui.tableWidget->item(i, 0)->checkState();//isItemSelected(ui.tableWidget->item(i, 7));
        if (selectRow)
        {
            test_Id = ui.tableWidget->item(i, 1)->text() ;
            result_data = dao->GetTestResultByTestId(test_Id);//ui.tableWidget->item(i, 7)->text();
            sample_id = ui.tableWidget->item(i, 2)->text();
            project_name = ui.tableWidget->item(i, 3)->text();
            pkid= ui.tableWidget->item(i, 8)->text().simplified().toInt();
            painter.begin(printer);
            painter.setPen(Qt::black);

            bool bResult = true;
            auto dao = AnalysisUIDao::instance();
            auto SampleTests = dao->SelectSamplesByTestId(test_Id);
            QMap<QString, int> map_position;
            map_position.clear();
            auto SelectLeftRightPositionQuery = dao->SelectLeftRightPosition(test_Id, &bResult);
            while (SelectLeftRightPositionQuery.next())
            {
                QString project_name = SelectLeftRightPositionQuery.value("projectName").toString();
                int position_value = SelectLeftRightPositionQuery.value("right_pix_position").toInt();
                map_position.insert(project_name, position_value);
            }

            if (bResult == false)
            {
                MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1304"), MyMessageBox::Ok, "OK", "");
                return;
            }
            printOnePageA(&painter, test_Id, sample_id, project_name, SampleTests, map_position,pkid, companyId);
            if (iii != m_all_page_number -1) //判断是否最后一页，如果不是最后一页则新建一页
            {
                printer->newPage(); //新建页
                painter.setPen(Qt::black);
            }
            iii++;
        }
    }
    painter.end();
}


void TestResultDataAll::printDocument(QPrinter *printer)
{
	int rowSize{ m_printIndexs.count() };
	int pagesize{ PAGESIZE };
	int page_count = rowSize / pagesize + (rowSize%pagesize > 0 ? 1 : 0);
	QPainter painter;
	for (int i = 0; i < page_count; i++)
	{
		painter.begin(printer);
		painter.setPen(Qt::black);
		drawTable(&painter, i, pagesize);
		if (i != page_count - 1)
		{
			printer->newPage(); //新建页
		}
	}
	painter.end();
}

void TestResultDataAll::printOnePageB(QPainter *painter, QString test_Id, QString result_data, QString sample_id, QString project_name, QList<float> PrintDataListCutGrayValue, QMap<QString, int> map_position)
{
    //    qDebug()<<"reportInfo title: "<<reportInfo->getTitle();
    //正常使用painter 绘制文字、pixmap等在printer上
    drawTableB(painter, test_Id, result_data, sample_id, project_name, PrintDataListCutGrayValue, map_position);
}

void TestResultDataAll::printOnePageC(QPainter *painter, QString test_Id, QString result_data, QString sample_id, QString project_name, QList<float> PrintDataListCutGrayValue, QMap<QString, int> map_position)
{
    //    qDebug()<<"reportInfo title: "<<reportInfo->getTitle();
    //正常使用painter 绘制文字、pixmap等在printer上
    drawTableB(painter, test_Id, result_data, sample_id, project_name, PrintDataListCutGrayValue, map_position);
}

void TestResultDataAll::printOnePageA(QPainter *painter, QString test_Id, QString sample_id, QString project_name, const QVector<QSqlRecord> &testResults, QMap<QString, int> map_position, int pkid, int companyId)
{
    drawTableA(painter, test_Id, sample_id, project_name, testResults, map_position);
}

void TestResultDataAll::paintRequestedHandler(QPrinter *printerPixmap)
{
}

/*给列表单元格添加内容*/
void TestResultDataAll::addContent(int row, int column, QString content, int nColor)
{
    content = content.replace("\n", " ");
    QTableWidgetItem *item = new QTableWidgetItem(content);
    item->setToolTip(content);
    //字体设置为黑色
    if (nColor == 0)
        item->setForeground(QBrush(QColor(0, 0, 0)));
    //黄绿色
    if (nColor == 1)
        item->setForeground(QBrush(QColor(128, 128, 0)));
    //红色
    if (nColor == 2)
        item->setForeground(QBrush(QColor(255, 0, 0)));
    //绿色
    if (nColor == 3)
        item->setForeground(QBrush(QColor(0, 255, 0)));
    //黄色
    if (nColor == 4)
        item->setForeground(QBrush(QColor(246, 180, 4)));
    ui.tableWidget->setItem(row, column, item);
    if (column == 8)
    {
        ui.tableWidget->hideColumn(8);
    }
}

void TestResultDataAll::on_tableWidget_cellClicked(int row, int column)
{
}

//刷新界面
void TestResultDataAll::sltUpdateTestResultDataList(QString a, QString b)
{
    QString c = a;
    auto dao = AnalysisUIDao::instance();
    bool bResult = true;
    QString sql = QString("update tsample_test set sendLisFlag=3 where sendLisFlag =2 ");
    dao->SelectRecord(&bResult, sql);
    Show_UI_Data("");
}

void TestResultDataAll::UpdateTestResultTableSlot(QString testId)
{
    QString a = testId;
}

void TestResultDataAll::on_pushButtonQuery_clicked()
{
    m_currentPage = 1;
    Show_UI_Data("all");
    m_query_condition1 = QString("all");
}

void TestResultDataAll::on_pushButtonSelectAll_clicked()
{

    if (selectedFlage)
    {
        for (int i = 0; i < ui.tableWidget->rowCount(); i++)
        {
            ui.tableWidget->item(i, 0)->setCheckState(Qt::Checked);
        }
        //ui.tableWidget->horizontalHeaderItem(0)->setIcon(QIcon(":/new/prefix1/image/AllSelect.png"));
        selectedFlage = false;
        //K1134|取消|取消en
        ui.pushButtonSelectAll->setText(GlobalData::LoadLanguageInfo("K1134"));
        //ui.pushButtonSelectAll->setText("取消");
    }
    else
    {
        for (int i = 0; i < ui.tableWidget->rowCount(); i++)
        {
            ui.tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
        }
        //ui.tableWidget->horizontalHeaderItem(0)->setIcon(QIcon(":/new/prefix1/image/NoSelect.png"));
        selectedFlage = true;
        ui.pushButtonSelectAll->setText(GlobalData::LoadLanguageInfo("K1081"));//setText("全选");
    }
}

#define WM_MYMESSAGE WM_USER + 1
#define   WM_MYMSG WM_USER + 2001 //WM_USER为系统定义好的值为0x0400
#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

const ULONG_PTR CUSTOM_TYPE = 10000;
const QString c_strTitle = "LisTool";

bool TestResultDataAll::Send_ID_ToList(QString id)
{
    HWND hwnd = NULL;
    LPWSTR path = (LPWSTR)c_strTitle.utf16();  //path = L"SendMessage"
    hwnd = ::FindWindowW(NULL, path);
    if (::IsWindow(hwnd))
    {
        QString filename = id;//"ssssssssssssssss122222222222";//QStringLiteral("进程通讯-Windows消息");
        QByteArray data = filename.toUtf8();//.toLocal8Bit();//.toUtf8();
        COPYDATASTRUCT copydata;
        copydata.dwData = data.size();  // 用户定义数据
        copydata.lpData = data.data();  //数据大小
        copydata.cbData = data.size();  // 指向数据的指针
        HWND sender = (HWND)effectiveWinId();
        //::SendMessage(hwnd, CUSTOM_TYPE, reinterpret_cast<WPARAM>(sender), reinterpret_cast<LPARAM>(&copydata));
        //SendMessage(hwnd, CUSTOM_TYPE, (WPARAM)sender, (LPARAM)&copydata);
        SendMessage(hwnd, WM_COPYDATA, (WPARAM)sender, (LPARAM)&copydata);
        return true;
    }
    else
    {
        return false;
    }
}

void TestResultDataAll::setProgressDialog(ProgressDialog *progressDialog)
{
    m_progressDialog = progressDialog;
}

void TestResultDataAll::setTcpClient(TcpClient *tcpClient)
{
    m_tcpClient=tcpClient;
}

void TestResultDataAll::set_print_doing(int v)
{
    m_print_doing = v;
}

void TestResultDataAll::on_pushButtonUpdateToLis_clicked()
{
    if (m_tcpClient == nullptr)
    {
        eLog("tcpClient is null");
        return;
    }

    if (!m_tcpClient->m_connectedState)
    {
        GlobalData::reconnect();
        if (!m_tcpClient->m_connectedState)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1736"), MyMessageBox::Ok, "OK", "");
            return;
        }
    }
    auto dao(AnalysisUIDao::instance());
    bool bResult(true);
    bool tipFlage(false);
    QString tip("");
    QString id("Send:");
    int i_n(0);
	int company_info = dao->SelectTargetValue(&bResult, "5").toInt();
    QString send_sz("");
    for (int i = 0; i < ui.tableWidget->rowCount(); i++)
    {
        bool selectRow = ui.tableWidget->item(i, 0)->checkState();
        if (selectRow)
        {
            QString testId = ui.tableWidget->item(i, 1)->text();
            if (!m_tcpClient->m_connectedState)
            {
                MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1736"), MyMessageBox::Ok, "OK", "");
                return;
            }
            send_sz=dao->createLISData(testId, company_info);
            if(send_sz.isEmpty())
            {
                eLog("数据发送失败,testId:{}",testId.toStdString());
                continue;
            }
            m_tcpClient->sendData(send_sz);
            if (bResult)
            {
                addContent(i, 6, GlobalData::LoadLanguageInfo("K1685"));//"已完成";
                ui.tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
            }
            i_n++;
            if (bResult)
            {
                if (i_n % 3 == 0)
                {
                    tip += QString("%1，%2\r\n").arg(testId).arg(GlobalData::LoadLanguageInfo("K1308"));
                    id += testId + ",";
                }
                else
                {
                    tip += QString("%1，%2").arg(testId).arg(GlobalData::LoadLanguageInfo("K1308"));
                    id += testId + ",";
                }

            }
            else
            {
                if (i_n % 3 == 0)
                {
                    tip += QString("%1，%2\r\n").arg(testId).arg(GlobalData::LoadLanguageInfo("K1309"));
                }
                else
                {
                    tip += QString("%1，%2").arg(testId).arg(GlobalData::LoadLanguageInfo("K1309"));
                }

            }
            //根据testId修改结果表的上传记录
            tipFlage = true;
        }
    }

    if (id != "Send:")
    {
        if (tipFlage)
        {
            MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), tip, MyMessageBox::Ok, "OK", "");
        }
        else
        {
            MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1310"), MyMessageBox::Ok, "OK", "");
        }
    }
    Show_UI_Data("");
}

void TestResultDataAll::on_pushButtonTopPage_clicked()
{
    //bool bResult = true;
    //auto dao = AnalysisUIDao::instance();
    ////int totalPages = dao->SelectTotalNumber().toInt() / m_one_page_number;//1000 / m_rowsPerPage + (1000 % m_rowsPerPage == 0 ? 0 : 1);
    //int test_count = dao->SelectTotalNumber().toInt();
    //int totalPages = test_count / m_one_page_number;//1000 / m_rowsPerPage + (1000 % m_rowsPerPage == 0 ? 0 : 1);
    ui.pushButtonNextPage->setEnabled(false);
    ui.pushButtonTopPage->setEnabled(false);
    QApplication::processEvents();
    //Sleep(500);
    if (m_currentPage > 1) {
        m_currentPage--;

        //InitTableWidget("", m_currentPage);//初始化状态列表
        InitTableWidget(m_query_condition1, m_currentPage);//初始化状态列表
    }

    ui.pushButtonSelectAll->setText(GlobalData::LoadLanguageInfo("K1081"));//setText("全选");

    //if (m_currentPage > 1)
    //{
    //	ui.pushButtonNextPage->setEnabled(true);
    //	ui.pushButtonTopPage->setEnabled(true);

    //}
    //else
    //{
    //	ui.pushButtonNextPage->setEnabled(true);
    //	ui.pushButtonTopPage->setEnabled(false);
    //}

    //QString count_txt = QString("统计：%1,共 %2 页,当前在第%3页。").arg(test_count).arg(totalPages).arg(m_currentPage);
    //ui.labelCount->setText(count_txt);//text(count_txt);
    //ui.lineEditPageIndex->setText(QString("%1").arg(m_currentPage));
}
void TestResultDataAll::on_pushButtonNextPage_clicked()
{
    //bool bResult = true;
    //auto dao = AnalysisUIDao::instance();
    ////int totalPages = dao->SelectTotalNumber().toInt() / m_one_page_number;//1000 / m_rowsPerPage + (1000 % m_rowsPerPage == 0 ? 0 : 1);
    //int test_count = dao->SelectTotalNumber().toInt();
    //int totalPages = test_count / m_one_page_number;//1000 / m_rowsPerPage + (1000 % m_rowsPerPage == 0 ? 0 : 1);
    ui.pushButtonNextPage->setEnabled(false);
    ui.pushButtonTopPage->setEnabled(false);
    QApplication::processEvents();
    //Sleep(1500);
    if (m_currentPage >= m_all_page_number1 )
    {
        MyMessageBox::warning(0, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1311"), MyMessageBox::Ok, "OK", "");
        ui.pushButtonTopPage->setEnabled(true);
        return;
    }
    m_currentPage++;



    //InitTableWidget("", m_currentPage);//初始化状态列表
    InitTableWidget(m_query_condition1, m_currentPage);//初始化状态列表
    ui.pushButtonSelectAll->setText(GlobalData::LoadLanguageInfo("K1081"));//setText("全选");
    //if (m_currentPage > 1)
    //{
    //	ui.pushButtonNextPage->setEnabled(true);
    //	ui.pushButtonTopPage->setEnabled(true);
    //}
    //else
    //{
    //	ui.pushButtonNextPage->setEnabled(false);
    //	ui.pushButtonTopPage->setEnabled(false);
    //}
    //if (m_currentPage < totalPages) {
    //	m_currentPage++;
    //	InitTableWidget("", m_currentPage);//初始化状态列表
    //}
    //QString count_txt = QString("统计：%1,共 %2 页,当前在第%3页。").arg(test_count).arg(totalPages).arg(m_currentPage);
    //ui.labelCount->setText(count_txt);//text(count_txt);
    //ui.lineEditPageIndex->setText(QString("%1").arg(m_currentPage));
}

void TestResultDataAll::on_pushButton_clicked()
{
    InitTableWidget("当天", 1);//初始化状态列表
    m_query_condition1 = QString("当天");
    ui.lineEditPageIndex->setText("1");
    m_currentPage = 1;
}

void TestResultDataAll::InitTableWidget(QString sz, int page_index)//初始化状态列表
{
    ui.tableWidget->setRowCount(0);
    ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑

    const QString VSCROLLBAR_STYLE2 =
        "QScrollBar:vertical {margin: 13px 0px 13px 0px;background-color: rgb(255, 255, 255, 100); border: 0px; width: 55px;}\
             .QScrollBar::handle:vertical {background-color:  rgb(122, 122, 122, 122); width: 55px; }\
             .QScrollBar::add-page:vertical {background-color: white; }\
             .QScrollBar::sub-page:vertical {background-color: white; }\
             .QScrollBar::sub-line:vertical {subcontrol-origin: margin; border: 0px solid red; height:63px}\
             .QScrollBar::up-arrow:vertical { subcontrol-origin: margin; background-color: rgb(255, 255, 255, 255); height:63px}\
             .QScrollBar::down-arrow:vertical { background-color: rgb(255, 255, 255, 255); }\
             .QScrollBar::add-line:vertical {subcontrol-origin: margin; border: 0px solid green; height:63px;subcontrol-position:bottom;}";
    ui.tableWidget->setStyleSheet(VSCROLLBAR_STYLE2);
    if (m_one_page_number == 0)
    {
        MyMessageBox::warning(0, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1312"), MyMessageBox::Ok, "OK", "");
    }
    QString strValue;
    QString strRel;
    QString strItemName;
    int error_code = 0;

    double dRatioToCut;
    QString testResult = "";
    int paperId = 1;
    QString pic_name = "";
    //DB中取Testitems表数据
    bool bResult = true;
    int stateFlag = 88;
    auto dao = AnalysisUIDao::instance();
    QString sampleNo = "";
    int nTestPaperID = 0;
    QString paper_name = "";
    QString strPathFileName;
    QString piture_root_str = dao->SelectTestPicturesRootPath(&bResult);
    QString analysised_piture_path = "analysised";
    QString strPath = piture_root_str + "\\" + analysised_piture_path;
    int row = 0;
    int need_change_bg_color = false;
    int need_change_bg_color_cut_fun = false;
    int need_change_bg_color_fun = false;
    int lis_Status = 0;
    QString paper_name_query = ui.comboBoxPaperID->currentText();
    if (paper_name_query != GlobalData::LoadLanguageInfo("K1594"))
    {
        int targetKey;
        for (auto it = m_paper_map.begin(); it != m_paper_map.end(); ++it) {
            if (it.value() == paper_name_query) {
                targetKey = it.key();
                break;
            }
        }
        paper_name_query = QString("%1").arg(targetKey).arg(sz);
    }

    QString start_time = ui.dateEdit->text();
    QString end_time = ui.dateEdit_2->text();
    int rows_need = ui.lineEditRowsPerPage->text().toInt();

    if (rows_need <= 0)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1313"), MyMessageBox::Ok, "OK", "");
        ui.lineEditRowsPerPage->setText("24");
        ui.lineEditRowsPerPage->setFocus();//.setFocus();
        m_rowsPerPage = 24;
        return;
    }
    else if (rows_need > 100)
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1313"), MyMessageBox::Ok, "OK", "");
        ui.lineEditRowsPerPage->setText("100");
        ui.lineEditRowsPerPage->setFocus();//.setFocus();
        m_rowsPerPage = 100;
    }
    else
    {
        m_rowsPerPage = rows_need;
    }

    if (sz == "当天")
    {
        start_time = QString("%1 00:00:00").arg(QDate::currentDate().toString("yyyy-MM-dd"));//QDate::currentDate().addDays(-1).toString("yyyy-MM-dd");
        end_time = QString("%1 23:59:59").arg(QDate::currentDate().toString("yyyy-MM-dd"));
        m_rowsPerPage = rows_need;
    }
    else
    {
        start_time = QString("%1 00:00:00").arg(start_time);//QDate::currentDate().addDays(-1).toString("yyyy-MM-dd");
        end_time = QString("%1 23:59:59").arg(end_time);
        m_rowsPerPage = rows_need;
    }
    auto dao1 = AnalysisUIDao::instance();
    int test_count1 = dao1->SelectTotalNumber(paper_name_query.toInt(), start_time, end_time).toInt();
    int totalPages = test_count1 / m_rowsPerPage;//m_one_page_number;//1000 / m_rowsPerPage + (1000 % m_rowsPerPage == 0 ? 0 : 1);
    if (test_count1 / m_rowsPerPage < 1)
    {
        totalPages = 1;
    }
    QString sz1 = GlobalData::LoadLanguageInfo("K1164");
    QString sz2 = GlobalData::LoadLanguageInfo("K1165");
    QString sz3 = GlobalData::LoadLanguageInfo("K1166");
    QString sz4 = GlobalData::LoadLanguageInfo("K1167");

    ui.label_5->setText(GlobalData::LoadLanguageInfo("K1168"));
    ui.pushButtonPageNumberSet->setText(GlobalData::LoadLanguageInfo("K1169"));
    ui.pushButtonTopPage->setText(GlobalData::LoadLanguageInfo("K1170"));
    ui.pushButtonNextPage->setText(GlobalData::LoadLanguageInfo("K1171"));
    ui.label_4->setText(GlobalData::LoadLanguageInfo("K1172"));
    ui.label_6->setText(GlobalData::LoadLanguageInfo("K1167"));

    int a = test_count1 % m_rowsPerPage;
    QString count_txt = "";
    if (a == 0)
    {
        m_all_page_number1 = totalPages;
        count_txt = QString(sz1 + "：%1," + sz2 + " %2 " + sz3 + "%3" + sz4 + "。").arg(test_count1).arg(totalPages).arg(m_currentPage);
    }
    else
    {
        if (totalPages == 1 && test_count1< m_rowsPerPage)
        {
            m_all_page_number1 = totalPages;
            count_txt = QString(sz1 + "：%1," + sz2 + " %2 " + sz3 + "%3" + sz4 + "。").arg(test_count1).arg(totalPages).arg(m_currentPage);
        }
        else
        {
            m_all_page_number1 = totalPages + 1;
            count_txt = QString(sz1 + "：%1," + sz2 + " %2 " + sz3 + "%3" + sz4 + "。").arg(test_count1).arg(totalPages + 1).arg(m_currentPage);
        }
    }
    ui.labelCount->setText(count_txt);//text(count_txt);
    ui.lineEditPageIndex->setText(QString("%1").arg(m_currentPage));
    auto SampleQuery = dao->SelectSamplesByQuery(start_time, end_time, paper_name_query, m_test_project_name, &bResult, m_rowsPerPage, page_index);
    if (bResult == false)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1111"), GlobalData::LoadLanguageInfo("K1304"), MyMessageBox::Ok, "OK", "");
        return;
    }
    int test_count = 0;
    int error_number = 0;

    int error_number_cut_off = 0;
    int error_number_fun = 0;
    QString pkid = "";
    while (SampleQuery.next())
    {
        ui.tableWidget->insertRow(row);
        sampleNo = SampleQuery.value("sampleNo").toString();
        paper_name = SampleQuery.value("PaperName").toString();
        pic_name = SampleQuery.value("testId").toString();
        stateFlag = SampleQuery.value("stateFlag").toInt();
        pkid = SampleQuery.value("pkid").toString();
        error_code = 0;

        QTableWidgetItem *itemcheck = new QTableWidgetItem();
        //设置此checkbox属性，Unchecked是不选中，如果要选中改成Qt::checked
        itemcheck->setCheckState(Qt::Unchecked);
        ui.tableWidget->setItem(row, 0, itemcheck);//显示label
        //测试编号
        strValue = pic_name;//QString::number(nSampleID);
        ui.tableWidget->setColumnWidth(1, 80);
        addContent(row, 1, strValue);
        ui.tableWidget->setColumnWidth(2, 160);
        //样本编号
        addContent(row, 2, sampleNo);
        addContent(row, 8, pkid);
        //检测类型
        auto TestPaperQuery = dao->SelectTestPaper(pic_name, &bResult);
        if (bResult == false)
        {
            addContent(row, 3, paper_name);
            addContent(row, 5, GlobalData::LoadLanguageInfo("K1261"));//"异常");
            addContent(row, 6, GlobalData::LoadLanguageInfo("K1686"));//"未知");

            if (stateFlag == 81)
            {
                addContent(row, 7, GlobalData::LoadLanguageInfo("K1687"),4);// "功能线异常，未识别膜条");
            }else if(stateFlag==82)
            {
                addContent(row, 7, GlobalData::LoadLanguageInfo("K1688"),4);//"Cutoff值异常");
            }else if(stateFlag == 83){
                addContent(row, 7, GlobalData::LoadLanguageInfo("K16881"), 4);//"检测线异常");
            }
            else if(stateFlag == 1)
            {
                addContent(row, 7, GlobalData::LoadLanguageInfo("K1689"));//"未完成检测");
            }
            else
            {
                addContent(row, 7, GlobalData::LoadLanguageInfo("K1690"));//"无结果");
            }
        }
        else
        {
            strValue = "";
            if (TestPaperQuery.next())
            {
                strValue = TestPaperQuery.value("PaperName").toString();
            }

            ui.tableWidget->setColumnWidth(3, 120);
            addContent(row, 3, paper_name);
            ui.tableWidget->setColumnHidden(4, true);
            //列表中显示图片
            QFont font("Microsoft YaHei", 7);
            QFontMetrics fm(font);
            int pixelsHigh = fm.height();//字体高度
            int nRowHeight = pixelsHigh;//行高度
            QPixmap pixBig;
            pixBig.load(strPath + "\\" + pic_name + ".png");  //图片路径
            int w1 = pixBig.width();
            int h1 = pixBig.height();
            QLabel *label1 = new QLabel;
            QPixmap pix = pixBig.scaled(600, 35, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            label1->setScaledContents(true);//设置图片适应label
            label1->resize(600, 35);
            label1->setPixmap(pix);
            ui.tableWidget->setColumnWidth(5, 600);
            ui.tableWidget->setCellWidget(row, 5, label1);//显示label
            w1 = m_width / 10;
            h1 = m_height;
            QString strSampleID = sampleNo;
            QString strTestPaper_ID = QString::number(nTestPaperID);
            auto TestDataQuery = dao->SelectTestData(pic_name, strSampleID, strTestPaper_ID, &bResult);

            int lis_Status1 = 0;
            if (bResult == false)
            {
                if (stateFlag == 81)
                {
                    addContent(row, 7, GlobalData::LoadLanguageInfo("K1687"),4);//"功能线异常，未识别膜条");
                }
                else if (stateFlag == 82)
                {
                    addContent(row, 7, GlobalData::LoadLanguageInfo("K1688"),4);//"Cutoff值异常");
                }else if(stateFlag == 83){
                    addContent(row, 7, GlobalData::LoadLanguageInfo("K16881"), 4);//"检测线异常");
                }
                else if (stateFlag == 1)
                {
                    addContent(row, 7, GlobalData::LoadLanguageInfo("K1689"));//"未完成检测");
                }
                else
                {
                    addContent(row, 7, GlobalData::LoadLanguageInfo("K1690"));//"无结果");
                }
            }
            else
            {
                strRel = "";
                lis_Status1 = 0;
                error_code = 0;
                while (TestDataQuery.next())
                {
                    strItemName = TestDataQuery.value("projectName").toString();
                    dRatioToCut = TestDataQuery.value("cutGrayValue").toDouble();
                    paperId = TestDataQuery.value("paperId").toInt();
                    lis_Status = TestDataQuery.value("sendLisFlag").toInt();
                    int error_code1 = TestDataQuery.value("error_code").toInt();
                    testResult = TestDataQuery.value("testResult").toString();
                    if (strItemName == "FC" )
                    {
                        if (error_code1 == 10002 || error_code1 == 10003 )
                        {
                            error_number_fun++;
                        }
                    }

                    if (strItemName == "Cut" )
                    {
                        if (error_code1 == 10002 || error_code1 == 10003)
                        {
                            error_number_cut_off++;
                        }
                    }

                    if (error_code1 == 9990 || error_code1 == 10003)
                    {
                        error_number++;
                    }

                    if (error_code1 > 0)
                    {
                        error_code = error_code1;
                    }
                    if (error_code > 0 && error_code != 10002 )
                    {
                        if (error_code == 10003)
                        {
                        }
                        else
                        {
                            need_change_bg_color = true;
                        }

                    }

                    if (lis_Status == 3)
                    {
                        lis_Status1++;
                    }
                    int pkid = TestDataQuery.value("pkid").toInt();
                    //新的显示方式
                    if (strItemName != "FC" && strItemName != "Cut")
                    {
                        if (error_code1 == 10002)
                        {
                            testResult = "-";
                        }

                        if (error_code1 == 10003)
                        {
                            testResult = "o";
                        }

                        if (strItemName != "FC" && strItemName != "Cut")
                        {
                            if (testResult == "+" || testResult == "++" || testResult == "+++" || testResult == "" || testResult == "++++" || testResult == "+++++" || testResult == "++++++" || testResult == "+++++++")
                            {
                                strRel += strItemName;
                                strRel += "(";
                                strRel += testResult;
                                strRel += ")  ";
                            }
                        }
                        else
                        {
                            if (strItemName == "Cut")
                            {
                                if (error_code == 10002 || error_code == 10003)
                                {
                                    need_change_bg_color_cut_fun = true;
                                }
                            }

                            if (strItemName == "FC")
                            {
                                if (error_code == 10002 || error_code == 10003)
                                {
                                    need_change_bg_color_fun = true;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (strItemName != "FC" && strItemName != "Cut")
                        {
                            if (testResult == "+" || testResult == "++" || testResult == "+++" || testResult == "" || testResult == "++++" || testResult == "+++++" || testResult == "++++++" || testResult == "+++++++")
                            {
                                strRel += strItemName;
                                strRel += "(";
                                strRel += testResult;
                                strRel += ")  ";
                            }
                        }
                        else
                        {
                            if (strItemName == "Cut")
                            {
                                if (error_code == 10002 || error_code == 10003)
                                {
                                    need_change_bg_color_cut_fun = true;

                                }
                            }if (strItemName == "FC")
                            {
                                if (error_code == 10002 || error_code == 10003)
                                {
                                    need_change_bg_color_fun = true;
                                }
                            }

                        }
                    }
                }
                strValue = strRel;
                if (strRel == "")
                {
                    if (stateFlag == 81)
                    {
                        addContent(row, 7, GlobalData::LoadLanguageInfo("K1687"), 4);//"功能线异常，未识别膜条");
                    }
                    else if (stateFlag == 82)
                    {
                        addContent(row, 7, GlobalData::LoadLanguageInfo("K1688"), 4);//"Cutoff值异常");
                    }else if(stateFlag == 83){
                        addContent(row, 7, GlobalData::LoadLanguageInfo("K16881"), 4);//"检测线异常");
                    }
                    else if (need_change_bg_color_fun)
                    {
                        addContent(row, 7, GlobalData::LoadLanguageInfo("K1687"), 4);//"功能线异常，未识别膜条！");
                    }
                    else if (need_change_bg_color_cut_fun)
                    {
                        addContent(row, 7, GlobalData::LoadLanguageInfo("K1688"), 4);//"Cutoff线异常！");
                    }
                    else
                    {
                        if (error_number_fun >0|| error_number_cut_off>0 || error_number>0)
                        {
                            addContent(row, 7, GlobalData::LoadLanguageInfo("K1683"), 4);//"无阳性结果！");
                        }
                        else
                        {
                            addContent(row, 7, GlobalData::LoadLanguageInfo("K1683"),0);//"无阳性结果！");
                        }
                    }
                }
                else
                {
                    if (stateFlag == 81)
                    {
                        addContent(row, 7, GlobalData::LoadLanguageInfo("K1687"),4);//"功能线异常，未识别膜条");
                    }
                    else if (stateFlag == 82)
                    {
                        addContent(row, 7, GlobalData::LoadLanguageInfo("K1688"),4);//"Cutoff值异常");
                    }
                    else if(stateFlag == 83)
                    {
                        addContent(row, 7, GlobalData::LoadLanguageInfo("K16881"), 4);//"检测线异常");
                    }
                    else if (need_change_bg_color_fun)
                    {
                        addContent(row, 7, GlobalData::LoadLanguageInfo("K1687"), 4);//"功能线异常，未识别膜条！");
                    }
                    else if(need_change_bg_color_cut_fun)
                    {
                        addContent(row, 7, GlobalData::LoadLanguageInfo("K1688"), 4);//"Cutoff线异常！");
                    }
                    else
                    {
                        if (error_number_fun > 0 || error_number_cut_off > 0 || error_number > 0)
                        {
                            addContent(row, 7, strValue,4);
                        }
                        else
                        {
                            addContent(row, 7, strValue,0);
                        }
                    }
                }
            }

            if (lis_Status1 > 1)
            {
                lis_Status = 3;
            }

            if (lis_Status == 1)
            {
                addContent(row, 6, GlobalData::LoadLanguageInfo("K1682"));//"等待上传");
            }
            else if (lis_Status == 2)
            {
                addContent(row, 6, GlobalData::LoadLanguageInfo("K1684"));//"上传中");
            }

            else if (lis_Status == 3)
            {
                addContent(row, 6, GlobalData::LoadLanguageInfo("K1685"));//"已完成");
            }
            else
            {
                addContent(row, 6, GlobalData::LoadLanguageInfo("K1686"));//"未知");
            }
            need_change_bg_color = false;
            need_change_bg_color_cut_fun = false;
            need_change_bg_color_fun = false;
            test_count++;
            error_code = 0;
            error_number = 0;
            error_number_cut_off = 0;
            error_number_fun = 0;
            strItemName = "";
            strRel = "";
        }
		row++;
    }
    if (m_currentPage > 1)
    {
        ui.pushButtonNextPage->setEnabled(true);
        ui.pushButtonTopPage->setEnabled(true);
    }
    else
    {
        ui.pushButtonNextPage->setEnabled(true);
        ui.pushButtonTopPage->setEnabled(false);
    }
    ui.pushButtonJumpPage->setEnabled(true);
}

void TestResultDataAll::on_pushButtonPageNumberSet_clicked()
{
    QString str = ui.lineEditRowsPerPage->text();
    int page_size_set_value = 24;
    page_size_set_value = str.toInt();
    bool containsOnlyDigits = true;
    for (QChar chr : str) {
        if (!chr.isDigit()) {
            containsOnlyDigits = false;
            break;
        }
    }
    if (containsOnlyDigits) {
        //qDebug() << "字符串只包含数字";
        //得加个判断
        if (0 < page_size_set_value && page_size_set_value < 100)
        {
            auto dao = AnalysisUIDao::instance();
            bool bResult;
            dao->UpdateSystemSet("20009", str);
            InitTableWidget(m_query_condition1, m_currentPage);//初始化状态列表
        }
    }
    else {
        return;
    }
}

void TestResultDataAll::on_pushButtonJumpPage_clicked()
{
    ui.pushButtonJumpPage->setEnabled(false);
    QApplication::processEvents();
    //得到输入字符串
    QString szText = ui.lineEditPageIndex->text();
    //数字正则表达式
    QRegExp regExp("-?[0-9]*");
    //判断是否为数字
    if (!regExp.exactMatch(szText))
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1314"), MyMessageBox::Ok, "OK", "");
        return;
    }
    //是否为空
    if (szText.isEmpty())
    {
        MyMessageBox::information(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1315"),MyMessageBox::Ok, "OK", "");
        return;
    }
    m_currentPage = szText.toInt();
    if (m_currentPage >m_all_page_number1)
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1316"), MyMessageBox::Ok, "OK", "");
        ui.pushButtonJumpPage->setEnabled(true);
        return;
    }
    InitTableWidget(m_query_condition1, m_currentPage);//初始化状态列表
}

void TestResultDataAll::on_btnSampleInfo_clicked()
{
    int companyid=0;
    getPDFTestIds(companyid);
    if(_pkidVect.isEmpty())
    {
        MyMessageBox::warning(this, GlobalData::LoadLanguageInfo("K1271"), GlobalData::LoadLanguageInfo("K1306"), MyMessageBox::Ok, "OK", "");
        return;
    }
    PatientDialog dialog(this);
    dialog.setPkid(_pkidVect.first());
    dialog.exec();
}