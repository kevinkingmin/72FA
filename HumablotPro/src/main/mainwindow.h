#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractNativeEventFilter>
#include "../Include/Model/baseSet/InstrumentStateModel.h"

class MainWidget;
class LogInForm;
class Instrument;
class InitWidgets;
class TestResultDataAll;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    using enumState=InstrumentStateModel::enumState;
private slots:
    void sltLogin(QString userid, QString password);
    void sltLogOut();
    void sltShowMinimized();
	void sltReActiveMainWindow();
	void slotIsStepSuc(int ret);

public:
signals:
	void sigUpdateTestResultData(QString a, QString b);
	void sglUpdateUpdateSampleWidgetUi1();

private:
    void initUi();
    void initSigAndSlt();
private:
    Ui::MainWindow           *ui;
    MainWidget               *_MainWidget;
    LogInForm                *_LogInForm;
	Instrument               *_instrument;
    InstrumentStateModel     *_ptrInstrumentState;

public:
	TestResultDataAll        *_TestResultDataAll;
	//InitWidgets              *_InitWidgets;
public:
        int mOpenSoftwareInitFlage = 2;   //不连机时，把开机初始化临时去掉 运行  //1为未开机初始化，2为已经开机初始化。

	virtual bool winEvent(MSG *message, long *result);
	virtual void shareMemery();
	void readSharedMemQt();
	//bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	//virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	virtual bool eventFilter(QObject *obj, QEvent *event);
	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);

	//int mGroupID;
	//QString mUserName;
};

#endif // MAINWINDOW_H
