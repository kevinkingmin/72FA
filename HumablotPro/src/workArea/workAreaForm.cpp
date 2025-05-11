#include "WorkAreaForm.h"
#include "ui_WorkAreaForm.h"
#include <QAction>
#include <QMessageBox>
#include <QTableView>
#include <QTimer>


WorkAreaForm::WorkAreaForm(QWidget *parent) :
    FirstWidgetBase(parent),
    ui(new Ui::WorkAreaForm)
{
    ui->setupUi(this);
    initUi();
}

WorkAreaForm::~WorkAreaForm()
{
    delete ui;
}

void WorkAreaForm::showEvent(QShowEvent *)
{
}

void WorkAreaForm::hideEvent(QHideEvent*)
{
}

void WorkAreaForm::initUi()
{
}




