#ifndef REPEATSETMODEL_H
#define REPEATSETMODEL_H

#include <QAbstractTableModel>
#include "AddSampleVModel.h"
#include <QMap>

class RepeatSetModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    using dataStrc=AddSampleVModel::dataStrc;
    using HeadStrc=AddSampleVModel::HeadStrc;
    explicit RepeatSetModel(QWidget *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags( const QModelIndex &index ) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;


    void updatePage(dataStrc *data);
private:
    QStringList        _headerList;
    QVector<HeadStrc>  _headVect;
    dataStrc          *m_data;
	static QVector<std::tuple<int, int>> m_posCountVect;
	QWidget *g_parent;
public:
	QString g_language_type = "";
};

#endif // REPEATSETMODEL_H
