#ifndef PUMPCALIBRATEWIDGET_H
#define PUMPCALIBRATEWIDGET_H

#include <QWidget>
class InstrumentStateModel;
class Instrument;
class ProgressDialog;
namespace Ui {
class PumpCalibrateWidget;
}

class PumpCalibrateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PumpCalibrateWidget(QWidget *parent = nullptr);
    ~PumpCalibrateWidget();
    void setProgressDialog(ProgressDialog *progressDialog);

private slots:
    void on_btnStart_clicked();
	void on_checkBox_all_3_toggled(bool state);
private:
    QVector<uchar> getCheckBtn();
private:
    Ui::PumpCalibrateWidget *ui;
    InstrumentStateModel *_InstrumentState;
    Instrument * _instr;
    ProgressDialog *m_progressDialog;
};

#endif // PUMPCALIBRATEWIDGET_H
