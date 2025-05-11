#ifndef SETFIRSTPAPERPOSDIALOG_H
#define SETFIRSTPAPERPOSDIALOG_H

#include "src/comm/BaseDialog.h"
#include <QRegExpValidator>

namespace Ui {
class SetFirstPaperPosDialog;
}

class SetFirstPaperPosDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit SetFirstPaperPosDialog(QWidget *parent = nullptr);
    ~SetFirstPaperPosDialog();
    void setTestId(const quint64 &testId);

protected:
    void showEvent(QShowEvent *);

private slots:
    void on_pushButtonClose_clicked();
    void on_btnConfig_clicked();
public:
    int getStartPos();
    bool getIsCloseBtn() const;
    void setPaperCount(const int &paperCount,const int &totalNum);

private:
    Ui::SetFirstPaperPosDialog *ui;
    QRegExpValidator _StartPosReg;
    quint64 _testId;
    int _paperCount;
    int _totalNum;
    bool _isCloseBtn;
public:
	QString g_language_type = "";
};

#endif // SETFIRSTPAPERPOSDIALOG_H
