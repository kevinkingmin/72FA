#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include "src/comm/BaseDialog.h"
#include <QRegExpValidator>
#include <QDialog>

namespace Ui {
class ProgressDialog;
}
class InstrumentStateModel;
class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget *parent = nullptr);
    ~ProgressDialog();

    void updateProgress(int maxValue);
    void setHead(const QString &str);
    void setMaxValue(int maxValue);
	//void resizeEvent(QResizeEvent* e);
    void setShowTime(int showTime);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
private:
    void setProgressState();
private:
    Ui::ProgressDialog *ui;
    QRegExpValidator _StartPosReg;
    QTimer *_timer;
    InstrumentStateModel *_instrState;
    int _maxValue;
    int _showTime;
};

#endif // ProgressDialog_H
