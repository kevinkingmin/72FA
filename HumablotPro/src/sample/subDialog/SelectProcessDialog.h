#ifndef SELECTPROCESSDIALOG_H
#define SELECTPROCESSDIALOG_H

#include "src/comm/BaseDialog.h"
#include <QRegExpValidator>
#include <QButtonGroup>
class InstrumentStateModel;

namespace Ui {
class SelectProcessDialog;
}

class SelectProcessDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit SelectProcessDialog(QWidget *parent = nullptr);
    ~SelectProcessDialog();

public:
    QMap<int, QString> getSeletedPGMap();
    QMap<int, QString> getAllPGMap();
    void resetBtn();
    bool getIsCloseBtn() const;

protected:
    void showEvent(QShowEvent *);
    void creatBtns();
private:
    void updateBtnState();
signals:
    void sglProcessChanged();
private slots:
    void on_pushButtonClose_clicked();
    void on_btnConfig_clicked();    
private:
    Ui::SelectProcessDialog *ui;
    QRegExpValidator _StartPosReg;
    QVector<QPushButton*>m_btnVect;
    bool _isCloseBtn;//是否是点击关闭按钮
    InstrumentStateModel *_instrState;
};

#endif // SELECTPROCESSDIALOG_H
