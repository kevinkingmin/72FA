#ifndef REPEATSETDIALOG_H
#define REPEATSETDIALOG_H
#include "src/comm/BaseDialog.h"
#include "src/sample/model/RepeatSetModel.h"

namespace Ui {
class RepeatSetDialog;
}


class RepeatSetDialog : public BaseDialog
{
    Q_OBJECT
public:
    using dataStrc=AddSampleVModel::dataStrc;
    explicit RepeatSetDialog(QWidget *parent = nullptr);
    virtual~RepeatSetDialog()override;

    bool setParas(const QString &sampleNo,dataStrc *data);
public:
	QString g_language_type = "";
protected:
    void showEvent(QShowEvent *)override;
private slots:
    void on_pushButtonClose_clicked();
    void on_btnSave_clicked();
    void on_buttonCancel_clicked();
private:
    void initUi();
    void resetValue();

private:
    Ui::RepeatSetDialog *ui;
    RepeatSetModel *_vModel;
    QString _sampleNo;
    dataStrc *   m_data;
    QMap<int,int> _posAndCountMap;//记录未改变时各膜条的测试次数。

};

#endif // REPEATSETDIALOG_H
