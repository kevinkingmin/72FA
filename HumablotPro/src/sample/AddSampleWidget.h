#ifndef ADDSAMPLEWIDGET_H
#define ADDSAMPLEWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QMap>
#include "subDialog/FromLisByIntervalWidgets.h"
#include "subDialog/ManualIncubationWidgets.h"
#include "../HumablotPro/src/main/subDialog/ProgressDialog.h"
class BatchAddSampleWidgets;
class FromLisIntervalWidgets;
class AddSampleVModel;
class QItemSelection;
class SetFirstPaperPosDialog;
class RepeatSetDialog;
class SampleModel;
class SampleTestModel;
class Instrument;
class QStyledItemDelegate;

namespace Ui {
class AddSampleWidget;
}

class AddSampleWidget : public QWidget
{
    Q_OBJECT
public:
    struct SampleStrc
    {
        int samplePos;
        QString sampleNo;
        int cupType;
        QString patientName;
        int sexID;
        int age;
        QString articleNo;
        SampleStrc()
            :samplePos(0)
            ,sampleNo("")
            ,cupType(1)
            , patientName("")
            , sexID(0)
            , age(10)
            ,articleNo("")
        {}
        bool operator<(const SampleStrc& a)const
        {
            return samplePos<a.samplePos;
        }
    };

    using ptrSample=QSharedPointer<SampleModel>;
    using ptrTest=QSharedPointer<SampleTestModel>;
    explicit AddSampleWidget(QWidget *parent = nullptr);
    ~AddSampleWidget();
    Instrument *m_instr;
    QVector<int> m_barCodePosVect;
    QMap<int, QString> m_barCodePosMap;
    QMap<int, QString> m_barCodePosMapFinshiFlage;
    int mScanBarCodePos = 0;

protected:
    void showEvent(QShowEvent *e);
private:
    void initUI();
    void createSamplePos();
    void drawButton();
    void setBtnCheckStyle();
    QList<int> getPosList();
    bool setSamplePaperIdMap();

signals:
    void ChangeBtnNextSignal(bool flage);
    void ChangeBtnSaveSignal(bool flage);

private slots:
    void slotBtnGroupTuble(QAbstractButton *btn);
    void slotSelectionChanged(const QItemSelection &,const QItemSelection &);
    void slotCheckBoxSeleted();
    void OnShowBtnState();
    void slotGetSampleBarCode(int pos, QString barCode);
    void slotGetQueryCondition(QString condition1, QString condition2);
    void on_tableView_customContextMenuRequested(const QPoint &pos);
    void SlotAction_triggered();
    void OnFromBatchAdd(QString content);
    void on_btnBCR_clicked();
    void on_btnBatchAdd_clicked();
    void slotGetSampleBarCodeList(QByteArray resultData);

public:
    void cancelAction();
    bool nextAction();
    QVector<ptrTest> getListTestData() const;
    QVector<ptrTest> getListTestDataAll() const;
    QVector<std::tuple<ptrSample, QVector<ptrTest>>>getSampleTestTpVect() const;
    void createRepeatTest();
    bool judgeTipInfo();
    void InsertIntoRecord(QVector<SampleTestModel>);
    void SaveSample();
    void DeleteSampleList(int index);
    void DeleteSample();
    void DeleteAllSample();
    void SaveSampleListToDataBase();
    void FromLis();
    void Incubation(int witch, int incubation_time);
    void FromLisByCondition(QString condition1);
    int  GetPaperId(int ii);
    int  GetPaperId1(int ii);
    void ShowTestInfoFromDatabase();
    bool Send_ID_ToList(QString id);
    void FromTestDataByBatchAdd(QString condition);
    void ChangeBtnBCREnabled(bool flage);
    void setProgressDialog(ProgressDialog *progressDialog);

public:
    QMap<int, QString> barCodeList;
    QString g_language_type = "";
private:
    void createSampleTestData(QMap<SampleStrc,QVector<int>>testMap, QVector<ptrTest>&listTestData);
    void sortTestData(QVector<ptrTest> &listTestData);
    void setTestDataSlotPos(int startPos,int totalTest);
    ProgressDialog *m_progressDialog;
private:
    Ui::AddSampleWidget *ui;
    QButtonGroup _btnGroup;
    AddSampleVModel *_vModel;
    QMap<SampleStrc,QVector<int>> _samplePaperIdMap;
    SetFirstPaperPosDialog *_setPaperPosDialog;
    QVector<ptrTest>_listTestData;
    QVector<std::tuple<ptrSample,QVector<ptrTest>>> _sampleTestTpVect;
    RepeatSetDialog *_repeatSetDialog;
    FromLisByIntervalWidgets *_mFromLisByIntervalWidgets;
    ManualIncubationWidgets *_mManualIncubationWidgets;

    BatchAddSampleWidgets *m_batchAddSampleWidget;

    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // ADDSAMPLEWIDGET_H
