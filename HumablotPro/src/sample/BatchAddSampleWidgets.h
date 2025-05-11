#pragma once

#include <QMainWindow>
#include "ui_BatchAddSampleWidgets.h"
#include "model/AddSampleVModel.h"
#include "../Include/Model/sample/BatchAddSampleModel.h"
#include <QMap>
#include <QList>

class BatchAddSampleWidgets : public QMainWindow
{
	Q_OBJECT

public:
	BatchAddSampleWidgets(QWidget *parent = nullptr);
	~BatchAddSampleWidgets();
	void GetTestPaperInfo();
	void SaveSample();
	int  GetPaperId(int ii);
	int  GetPaperId1(int ii);
	using dataStrc = AddSampleVModel::dataStrc;
	using HeadStrc = AddSampleVModel::HeadStrc;
	explicit BatchAddSampleWidgets(QObject *parent = nullptr);
	bool isPureNumber(const QString& str);
	AddSampleVModel *_vModel;
	int m_added_paper_number ;
	void updatePage(dataStrc *data);
	QButtonGroup *m_pButtonGroup;
	QString m_paper_name;
	QMap<int, QString> m_PaperinfoMap;
private:
	QStringList        _headerList;
	QVector<HeadStrc>  _headVect;
	dataStrc          *m_data;
	static QVector<std::tuple<int, int>> m_posCountVect;
	QList<BatchAddSampleModel> m_BatchSampleList;
public:
	QString g_language_type = "";
protected:
	void closeEvent(QCloseEvent *);
signals:
	void sglFromBatchSample(QString confition);

public slots:
	void on_pushButtonAdd_clicked();
	void on_pushButtonDelete_clicked();
	void on_pushButtonDeleteAll_clicked();
	void on_pushButtonUpdate_clicked();
	void on_pushButtonOk_clicked();
private:
	Ui::BatchAddSampleWidgetsClass ui;
};
