#ifndef UTILITYWIDGET_H
#define UTILITYWIDGET_H

#include "ReagentManager.h"
#include "TestPaperManage.h"
#include "TubeManage.h"
#include "SystemSet.h"
#include "ResultManage.h"

#include <QWidget>
class MaintainCmdWidget;
namespace Ui {
class UtilityWidget;
}

class UtilityWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UtilityWidget(QWidget *parent = nullptr);
    ~UtilityWidget();
    void setMaintainShow();
private:
    void initUi();
private slots:
    void on_btnMaintain_clicked();

    void on_btnSystemSet_clicked();

	void on_btnItemSet_clicked();

private:
    Ui::UtilityWidget *ui;
    MaintainCmdWidget *_MaintainCmdWidget;

	ReagentManager *_ReagentManager;
	TestPaperManage *_TestPaperManage;
	TubeManage *_TubeManage;
	ResultManage *_ResultManage;

	SystemSet *_SystemSet;
};

#endif // UTILITYWIDGET_H
