#pragma once
#include <QWidget>
#include "ui_RulesSetting.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QComboBox>
#include "src/comm/CustomHeaderView.h"
#include "../Include/DAO/baseSet/StandardCurveDao.h"
#include "../Include/Model/baseSet/StandaryCurveModel.h"
#include "../Include/DAO/baseSet/JudgeDao.h"
#include "../Include/Model/result/JudgeRules.h"

class Instrument;

class RulesSetting : public QWidget
{
    Q_OBJECT
public:
    RulesSetting(QWidget *parent = Q_NULLPTR);
    ~RulesSetting();
private:
    void tbRuleLoadData();
    void tbRuleItemLoadData(const QString &id);
    void addRuleContent(int row, int column, QString content);
    void addRuleItemContent(int row, int column, QString content);
    void createHeadBox();
    void initTbRule();
    void initTbRuleItem();
    void loadUIData(const bool isRule);
    void getNumStr(QString &str);
    void AddFitCurveItem();
private slots:
    void on_btnRule_clicked();
    void on_btnCurve_clicked();
    void on_btnAddRule_clicked();
    void on_tbRule_clicked(const QModelIndex &index);
    void on_btnDeleteRule_clicked();
    void on_btnAddItem_clicked();
    void on_btnSaveItem_clicked();
    void on_btnDelete_clicked();
    void slotFitCurveChanged(int index);
    void on_tbRuleItem_itemChanged(QTableWidgetItem *item);
    void on_tbRule_itemChanged(QTableWidgetItem *item);

private:
    Ui::RulesSetting   ui;
    QString            m_strMachineUID;
    Instrument         * _instr;
    QWidget            *m_layWidget;
    QHBoxLayout        *m_hLay;
    QComboBox          *m_cmbBox;
    QLabel             *m_lable;
    bool               m_isRule;
    bool               m_isCurveData;
    StandaryCurveModel _curveModel;
    JudgeRules _ruleModel;
};
