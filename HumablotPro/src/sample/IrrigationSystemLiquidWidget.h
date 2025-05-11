#ifndef IRRIGATIONSYSTEMLIQUIDWIDGET_H
#define IRRIGATIONSYSTEMLIQUIDWIDGET_H

#include <QWidget>

namespace Ui {
class IrrigationSystemLiquidWidget;
}

class Instrument;
class InstrumentStateModel;
class ProgressDialog;

class IrrigationSystemLiquidWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IrrigationSystemLiquidWidget(QWidget *parent = nullptr);
    ~IrrigationSystemLiquidWidget();

    bool getIsIrrigate() const;
    void setProgressDialog(ProgressDialog *progressDialog);

protected:
    void showEvent(QShowEvent *);
signals:
	void ChangeBtnNextSignal(bool flage);
private slots:
    void on_btnIrrigate_clicked();
    void on_btnWash_clicked();
    void on_btnFill_clicked();

private:
    Ui::IrrigationSystemLiquidWidget *ui;
    bool m_isIrrigate;//系统液是否充灌
    Instrument *m_instr;
    InstrumentStateModel *m_instrState;
    ProgressDialog *m_progressDialog;
public:
	//1为未跳过充灌，2为跳过充灌
	int m_jump_irrigate;
};

#endif // IRRIGATIONSYSTEMLIQUIDWIDGET_H
