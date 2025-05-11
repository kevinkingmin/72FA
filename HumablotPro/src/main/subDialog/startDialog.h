/*************************************************
* @Copyright(C), 2018, 胡曼. human
* @brief         摘要
* @author        xing_liu
* @date          2020-10-12
*************************************************/
#ifndef STARTDIALOG_H
#define STARTDIALOG_H
#include <QButtonGroup>
#include "src/comm/BaseDialog.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

class Instrument;
namespace Ui {
class StartDialog;
}

class StartDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = nullptr);
    virtual~StartDialog()override;
private:
    void initUi();
private slots:
    void on_pushButtonClose_clicked();
    void on_btnCancel_clicked();
    void on_btnReagentInfo_clicked();
    void on_btnCalibrate_clicked();
    void on_btnQC_clicked();
    void on_btnStatistics_clicked();
    void on_btnChangeSample_clicked();
    void on_btnAddConsumable_clicked();
    void on_btnStart_clicked();
signals:
    void sglCurrentPage(int page);
private:
    Ui::StartDialog *ui;
    Instrument *_instr;
    QButtonGroup _btnGroupClinicType;
    InstrumentStateModel *_InstrumentState;
};

#endif // STARTDIALOG_H
