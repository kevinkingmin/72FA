#ifndef WORKAREAFORM_H
#define WORKAREAFORM_H

#include <QWidget>
#include <QModelIndex>
#include "src/main/firstwidgetbase.h"
#include <QSharedPointer>
namespace Ui {
class WorkAreaForm;
}

class WorkAreaForm : public FirstWidgetBase
{
    Q_OBJECT

public:
    explicit WorkAreaForm(QWidget *parent = nullptr);
    ~WorkAreaForm() override;
protected:
    virtual void showEvent(QShowEvent*) override;
	virtual void hideEvent(QHideEvent*) override;
private:
    void initUi();
private:
    Ui::WorkAreaForm     *ui;
};

#endif // WORKAREAFORM_H
