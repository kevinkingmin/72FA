#ifndef EMPTYWASTEBOTTLEWIDGET_H
#define EMPTYWASTEBOTTLEWIDGET_H

#include <QWidget>

namespace Ui {
class EmptyWasteBottleWidget;
}

class Instrument;
class InstrumentStateModel;
class ProgressDialog;

class EmptyWasteBottleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmptyWasteBottleWidget(QWidget *parent = nullptr);
    ~EmptyWasteBottleWidget();

private:
    Ui::EmptyWasteBottleWidget *ui;
	bool m_isPerfusionSystemLiquid;  //∑œ“∫Õ∞ «∑Ò≈≈ø’
	Instrument *m_instr;
	InstrumentStateModel *m_instrState;
	ProgressDialog *m_progressDialog;

private slots:
	void on_btnPerfusionSystemLiquid_clicked();
};

#endif // EMPTYWASTEBOTTLEWIDGET_H
