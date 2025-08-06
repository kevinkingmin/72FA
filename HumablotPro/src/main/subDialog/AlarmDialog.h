#ifndef ALARMDIALOG_H
#define ALARMDIALOG_H
#include "src/comm/BaseDialog.h"

namespace Ui {
class AlarmDialog;
}


class AlarmDialog : public BaseDialog
{
    Q_OBJECT
public:
    explicit AlarmDialog(QWidget *parent = nullptr);
    virtual~AlarmDialog()override;
public:
    void msgText(const QString &alarmStr,const bool showCancelBtn=false);
    int getRet() const;
    void setFstBtnTest(const QString &text);
    void setSndBtnTest(const QString &text);
protected:
    void showEvent(QShowEvent *)override;
private slots:
    void on_pushButtonClose_clicked();
    void on_btnSave_clicked();
    void on_buttonCancel_clicked();
private:
    void initUi();
private:
    Ui::AlarmDialog *ui;
    int m_ret;
};

#endif // REPEATSETDIALOG_H
