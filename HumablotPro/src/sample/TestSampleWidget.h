#ifndef TESTSAMPLEWIDGET_H
#define TESTSAMPLEWIDGET_H
#include <QWidget>
#include <QButtonGroup>
#include "src/comm/GlobalData.h"
#include "QTime"
#include "../HumablotPro/src/main/subDialog/ProgressDialog.h"
#include "../Include/TCPClient/TcpClient.h"

class QProgressBar;

namespace Ui {
class TestSampleWidget;
}
class SampleModel;
class SampleTestModel;
class SelectProcessDialog;
class QHBoxLayout;
class CustomLabel;
class PrepareReagentDialog;
class CustomerPumpStateLable;
class SampleWidget;
class Instrument;
class InstrumentStateModel;

class TestSampleWidget : public QWidget
{
    Q_OBJECT
public:
    enum btnSet
    {
        EnumInit=0
    };
    QMap<int, QString> selectProcessMap;
    QMap<int, QString> m_errorAddSampleMap;
    QMap<int, QString> m_errorAddSampleMap1;
    QString m_current_disk_position = "";
    int m_current_slot_position = 0;
    int m_test_count = 0;
    int m_test_count1 = 0;
    int m_start_slot_postion = 1;
    int m_current_slot_postion = 0;
    QMap<QString,int> selectProcessMap_time;

    QMap<QString, int> selectProcessMap_time_old;

    using PumpPosState=GlobalData::PumpPosState;
    using ptrSample=QSharedPointer<SampleModel>;
    using ptrTest=QSharedPointer<SampleTestModel>;
    friend SampleWidget;
    explicit TestSampleWidget(PrepareReagentDialog *dialog, QWidget *parent = nullptr);
    ~TestSampleWidget();
    void setListTest(QVector<ptrTest> listTest);
    void setPapersState();
    void setPumpLblState();
    void setSampleTestTpVect(QVector<std::tuple<ptrSample, QVector<ptrTest>>> sampleTestTpVect);
    void setSelectPDialog(SelectProcessDialog *selectPDialog);
    void setBtnGroup(QButtonGroup *btnGroup);
    void setIsNewTest(bool isNewTest);
    void SaveTestResult(QVector<std::tuple<ptrSample, QVector<ptrTest>>> sampleTestTpVect);
    void UpdateprogressBarStatus(QString tip, bool visible);
    void writeAlarmInfo(QString sz, QString fileName);
    void TimeShow(QString step_name, QString total_time, QString step_time, QString solution_time, QString plain_time);
    void SaveRunInfo(QString run_info);
    void ShowAlarmInfo(QString sz);
    void ClearTextBrowser();
    void setProgressDialog(ProgressDialog *progressDialog);
    void TestSampleWidget::deleteFilesInDirectory();

private slots:
    void on_btnPause_clicked();
    void on_btnSet_clicked();
    void slotPumpFlush();
    void slotLblClick(int pos);
    void on_btnSubBody_clicked();
    void slotCurrentGroupIdChanged(int groupId,int realTime);
    void slotAlarmInfo1(QString alarm_info,QString code_type);


    void on_btnStop_clicked();

public:
    friend class RunPaperPosThread;

public:
    int mOpenCoverAlarmTip = 1;


    int mWetting_time_old = 0;
    int mWetting_time = 0;
    int mWetting_time_new = 0;

    int mAddSample_time_old = 0;
    int mAddSample_time = 0;
    int mAddSample_time_new = 0;

    int mWash_time_old = 0;
    int mWash_time = 0;
    int mWash_time_new = 0;

    int mAddEnzyme_time_old = 0;
    int mAddEnzyme_time = 0;
    int mAddEnzyme_time_new = 0;

    int mSecondary_wash_time_old = 0;
    int mSecondary_wash_time = 0;
    int mSecondary_wash_time_new = 0;

    int mAddSubstrate_time_old = 0;
    int mAddSubstrate_time = 0;
    int mAddSubstrate_time_new = 0;

    int mAddPureWater_time_old = 0;
    int mAddPureWater_time = 0;
    int mAddPureWater_time_new = 0;

    int mAddTerminationLiquid_time_old = 0;
    int mAddTerminationLiquid_time = 0;
    int mAddTerminationLiquid_time_new = 0;

    int mDry_time_old = 0;
    int mDry_time = 0;
    int mDry_time_new = 0;

    int mPhoto_time = 30;
    int mPause_time = 0;

    int m_need_add_pause_time = 0;
    int mPause_total_time = 0;
    int mToatal_time = 0;

    int mToatal_solution_time = 0;
    QString mStartTime = "";
    int mFloat_time = 0;
    QString traslationSecondToString(int second);
    bool mPause_flage = false;
    int m_i_init_number = 0;
    bool m_test_result_flage = false;

    QString g_language_type = "";
    int m_i_n = 1;

    void setTcpClient(TcpClient *tcpClient);

private:
    void initUI();
    ptrTest searchPmByPos(int pos);
    void createPumpLbl();
    void createPapers();
    void clearLayOut(QHBoxLayout *layOut);
    void updateProgress(int maxValue);
    void setProgressState();
    Ui::TestSampleWidget *ui;
    QVector<ptrTest> m_listTest;
    SelectProcessDialog *m_selectPDialog;
    QTimer *_timer;
    QTime startTime;
    QTime stepTime;//阶段起始时间点
    QTime stepTimeTotal;//阶段预计总用时
    QTime pauseTime;
    QVector<CustomLabel *> _lblPaperVect;
    QVector<CustomerPumpStateLable *> _lblPumpVect;
    QVector<std::tuple<ptrSample,QVector<ptrTest>>> _sampleTestTpVect;
    PrepareReagentDialog *_pReagentDialog;
    QButtonGroup *_btnGroup;
    bool _isNewTest;
    Instrument *_instrument;
    InstrumentStateModel *_instrState;
    int _currentGroupId;
    QMap<int,int> _stepRunTimeMap;

    static QString _imgPath;
    static QString _readyFileName;
    static QString _delayFileName;
    static QString _emptyFileName;
    static QString _usedFileName;

    //void StopSlot();
    RunPaperPosThread *m_run_paper_pos_thread;
    bool SaveDataFromPic();
    QString _stepName;
    int m_current_step_id;
    int m_preview_wash_flage = 0;

    int m_Enzyme_number = 1;
    ProgressDialog *m_progressDialog;
    TcpClient  *m_tcpClient;
public slots:
    void UpdateSlot(int num);
    void slotUpdateTime();
    void slotAlarmInfo(int alarmFlage);
    void slotHandleStepDetail(int stepId, int index, bool isSucess, const QString &stepName);
    void slotIsStepSuc(int ret);
    void slotDetectionStartResult(QString MessageType,QString sample,QString slot,QString step,QString code,QString time);
    void slotDetectionPauseResult(QString code);
    void slotDetectionContinueResult(QString code);
    void slotDetectionStopResult(QString code);
    void slotTestFinish();
signals:
    void preper_save(TestSampleWidget *);
    void ResetSignal();
    void testStop();
    void testFinish();


};
#endif
