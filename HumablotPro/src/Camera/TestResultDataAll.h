#pragma once

#include <QWidget>
#include "ui_TestResultDataAll.h"
#include "../sample/TestResultDetailDialog.h"
#include "../sample/ShowTestResultDetail.h"
#include "../main/mainwindow.h"
#include <QPdfWriter>
class TcpClient;
class ProgressDialog;

class TestResultDataAll : public QWidget
{
	Q_OBJECT
public:
	TestResultDataAll(QWidget *parent = Q_NULLPTR);
	~TestResultDataAll();
	QString m_test_project_name;
	bool selectedFlage = true;
	void Show_UI_Data(QString sz);
	bool Send_ID_ToList(QString id);
	//bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	//表格
	ShowTestResultDetail *mytable;
	//对话框
    TestResultDetailDialog *dialog;
    void setProgressDialog(ProgressDialog *progressDialog);
    void setTcpClient(TcpClient *tcpClient);
	void set_print_doing(int v);
private:	
	void InitTableWidget(QString sz,int page_index);//初始化列表
	/*给项目列表单元格添加内容*/
	void addContent(int row, int column, QString content, int nColor = 0);
	void printDirect();
	void printDirectA();
	void printOnePage(QPainter *painter, int no);
	void printOnePageA(QPainter *painter, QString test_Id, QString result_data, QString sample_id, QString project_name, QList<float> PrintDataListCutGrayValue, QMap<QString, int> map_position,int pkid,int companyId);
	void printOnePageB(QPainter *painter, QString test_Id, QString result_data, QString sample_id, QString project_name, QList<float> PrintDataListCutGrayValue, QMap<QString, int> map_position);
	void printOnePageC(QPainter *painter, QString test_Id, QString result_data, QString sample_id, QString project_name, QList<float> PrintDataListCutGrayValue, QMap<QString, int> map_position);
	void drawTable(QPainter *painter, int no);
	void drawTableC(QPainter *painter, int no);
	void drawTableA(QPainter *painter,  QString test_Id, QString result_data, QString sample_id, QString project_name, QList<float> PrintDataListCutGrayValue,QMap<QString, int> map_position);
	void drawTableB(QPainter *painter, QString test_Id, QString result_data, QString sample_id, QString project_name, QList<float> PrintDataListCutGrayValue, QMap<QString, int> map_position);
	//void drawTableC(QPainter *painter, QString test_Id, QString result_data, QString sample_id, QString project_name, QList<float> PrintDataListCutGrayValue);
	void SavePdf(QPainter* pPdfPainter ,QString test_Id, QString result_data, QString sample_id, QString project_name, QList<float> PrintDataListCutGrayValue);
	void SavePdfA();
	void SavePdfB();
	bool getPrintIndexs(const bool isSamePaper);
	QString getPDFTestIds(int &companyId);
signals:
	void sglUpdateStatus(QString a, QString b);
private slots:
	void on_tableWidget_cellClicked(int row, int column);
	void UpdateTestResultTableSlot(QString testId);
	void getItemDataSlot(int row);
	void on_pushButtonSelectAll_clicked();
	void on_pushButtonUpdateToLis_clicked();
	void on_pushButtonQuery_clicked();
	void on_pushButtonPrint_clicked();
	void on_pushButtonPrintA_clicked();
	void on_pushButtonPdf_clicked();
	void on_pushButtonPdfAll_clicked();
	void on_pushButtonPageNumberSet_clicked();
	void on_pushButtonTopPage_clicked();
	void on_pushButtonNextPage_clicked();
	void on_pushButtonJumpPage_clicked();
	void on_pushButton_clicked();
    void on_btnSampleInfo_clicked();

public slots:
	void sltUpdateTestResultDataList(QString a, QString b);
	void paintRequestedHandler(QPrinter *printerPixmap);
	void slotUpdateStatus(QString a, QString b);
	void printDocument(QPrinter *printer);
	void printDocumentA(QPrinter *printer);
private:
	Ui::TestResultDataAll ui;
	int m_nImageColumnWidth = 0;
	int m_width = 850;
	int m_height = 50;
	int m_startx;    //整体表格在A4纸中的起始x坐标
	int m_starty;    //整体表格在A4纸中的起始y坐标
	int m_width1;     //整体表格的宽
	int m_height1;    //整体表格的高
	int m_titleHeight;    //标题栏的高
	int m_colNum;   //表格的总列数
	int m_rowNum;   //表格的总行数
	int m_rowHeight; //单元表格高
	int m_colWidth;  //单元表格宽	
	int m_all_page_number = 0;
	int m_all_page_number1 = 0;
	int min_pkid = 0;
	int max_pkid = 30;
	//一页查询数量
	int m_one_page_number = 24;
	int m_rowsPerPage = 24;  // 每页显示的行数
	int m_currentPage = 1;  // 当前页数
	void populateTable(int page);
	QMap<int, QString> m_paper_map;
	int m_top;
	int m_bottom;
	QList<QString> m_PrintDataList;
	QList<QString> m_PrintDataListProject;
	QList<QString> m_PrintDataListValue;
	TcpClient *m_tcpClient;
	ProgressDialog *m_progressDialog;
	QString m_query_condition1 = "";
	int m_print_doing = 0; //1为正在打印，0为未打印。
	QVector<int>  m_printIndexs;
	int           m_itemCount;
    QVector<int>  _pkidVect;
};
