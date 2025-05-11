#ifndef PREPAREREAGENTDIALOG_H
#define PREPAREREAGENTDIALOG_H

#include "src/comm/BaseDialog.h"
#include <QRegExpValidator>
#include "src/comm/GlobalData.h"

class SampleTestModel;
class SelectProcessDialog;
class QButtonGroup;
class PrepareReagentWidget;

namespace Ui {
class PrepareReagentDialog;
}

class PrepareReagentDialog : public BaseDialog
{
    Q_OBJECT

public:
    using PumpPosState=GlobalData::PumpPosState;
    using ptrTest=QSharedPointer<SampleTestModel>;
    explicit PrepareReagentDialog(PrepareReagentWidget * spdialog,QWidget *parent = nullptr);
    ~PrepareReagentDialog();
protected:
    void showEvent(QShowEvent *);
signals:
    void sglPumpStateChange();
private slots:
    void on_pushButtonClose_clicked();
    void on_btnConfig_clicked();
    void on_btnFlash_clicked();
    void on_btnReady_clicked();
    void on_btnDelay_clicked();

	void on_pushButtonSmall_clicked();

	void on_btnSmall_clicked();
	void on_btnBig_clicked();

public:
    bool getIsCloseBtn() const;
    void setSelectProcessDialog(SelectProcessDialog *widget);
public:
	///充灌类型，0为大，1为小
	int m_flushing_type = 0;
	QString g_language_type = "";
private:
    Ui::PrepareReagentDialog *ui;
    bool _isCloseBtn;
    PrepareReagentWidget *_reagentWidget;
};

#endif // PREPAREREAGENTDIALOG_H
