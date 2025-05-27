#ifndef PATIENTDIALOG_H
#define PATIENTDIALOG_H
#include "src/comm/BaseDialog.h"
#include <QSharedPointer>
#include <QRegExpValidator>
#include "../Include/Model/sample/SampleModel.h"

namespace Ui {
class PatientDialog;
}


class PatientDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit PatientDialog(QWidget *parent = nullptr);
    virtual~PatientDialog()override;
    void setPkid(int pkid);
private:
    void showEvent(QShowEvent *e)override;
    void initUIControl();
	void setUIData();
	void getUIData();
signals:
    void signalSchData(QString sampleNo,QString anamnesisNo,QString patientName,bool isPrev);
private slots:
    void on_pushButtonClose_clicked();
    void on_btnClose_clicked();
    void on_btnSave_clicked();
private:
    Ui::PatientDialog *ui;
    QRegExpValidator   _regLISValid;//符合LIS验证的输入
    QString           _preRemark;
    QString           _preDiagnosis;
    int               _pkid;
};

#endif // PATIENTDIALOG_H
