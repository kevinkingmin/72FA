#ifndef TESTDATALISTVMODEL_H
#define TESTDATALISTVMODEL_H
class SampleTestModel;
#include <QAbstractTableModel>

class TestDataListVModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    using ptrTest=QSharedPointer<SampleTestModel>;
    explicit TestDataListVModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags( const QModelIndex &index ) const override;
    void updatePage(QVector<ptrTest>vect);
private:
    QStringList       _headerList;
    QVector<ptrTest> _vect;
public:
	QString g_language_type = "";
};

#endif // TESTDATALISTVMODEL_H
