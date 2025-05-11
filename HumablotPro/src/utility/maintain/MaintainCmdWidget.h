#ifndef MAINTAINCMDWIDGET_H
#define MAINTAINCMDWIDGET_H

#include <QWidget>
#include "../Include/Model/baseSet/InstrumentStateModel.h"

class Instrument;
namespace Ui {
class MaintainCmdWidget;
}

class MaintainCmdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaintainCmdWidget(QWidget *parent = nullptr);
    ~MaintainCmdWidget();
    using enumState=InstrumentStateModel::enumState;
private:
    void initUI();
private slots:
    void on_btnRunInit_clicked();

    void on_btnCloseInit_clicked();

    void on_btnSysteReset_clicked();

    void on_btnStartWash_clicked();

    void on_btnWeekWash_clicked();

    void on_btnEmpty_clicked();

    void on_btnFlush_clicked();

    void on_btnCloseWash_clicked();

    void on_btnClose_clicked();

    void on_btnDormant_clicked();

    void on_btnRouse_clicked();

    void on_btnPoolFlush_clicked();

private:
    Ui::MaintainCmdWidget *ui;
    Instrument *_Instrument;
    InstrumentStateModel *_InstrumentState;
};

#endif // MAINTAINCMDWIDGET_H
