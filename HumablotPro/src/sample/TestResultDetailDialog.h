#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QDesktopWidget>
#include <QPrinter>

class ShowAllPicWidgets;


class TestResultDetailDialog : public QDialog
{
    Q_OBJECT

public:
    TestResultDetailDialog(QString, QString,QWidget *parent);
    ~TestResultDetailDialog();
    QString CaculateResultText(double dItemGrayRatio);
signals:
    void sglUpdateUI();
    //void UpdateTestResultTableSignal(QString testId);
public slots:
    //nodify button active;
    void OnClickModifyOneTestResult();
    void paintRequestedHandler(QPrinter *printerPixmap);
    void exportSlot();
private://定义对话框控件
    QLabel *noLabel;//编号标签
    QLabel *showPicLabel;//编号标签
    QLabel *mark_showPicLabel;//编号标签
    //QLineEdit *noInput;//编号输入框
    QLabel *testIdLabel;//测试编号标签
    QTableWidget *tableWidget;
    QPushButton *saveButton;//保存修改按钮
    QPushButton *cancelButton;//取消修改按钮
    QPushButton *closeButton;//关闭对话框按钮
    QPushButton *show_all_pic_Button;//查看完整图片对话框按钮
    QPushButton *show_all_pic_Button_correction;//查看校正后的图片
    //QPushButton *pdfSaveButton;//生成PDF
    //QPushButton *printButton;//关闭对话框按钮
    QGridLayout *topBarLayout; //
    QGridLayout *bottomBarLayout;//保存上述按钮的布局
    QGridLayout *mainLayout;//对话框主布局
    QString m_testId = "";
    QMap<QString, double> m_mapOneTestData;
};

#endif // MYDIALOG_H
