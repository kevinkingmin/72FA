#ifndef ADDSAMPLEVMODEL_H
#define ADDSAMPLEVMODEL_H

#include <QAbstractTableModel>

#include "src/comm/GlobalData.h"

#define PAPERCOUNT 72
#define PAPERSTARPOS 3
class AddSampleVModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    struct HeadStrc
    {
		int id;
        int paperId;
        QString field;
		QString patientName;
		int sexID;
		int age;
		QString articleNo;
        HeadStrc()
            :id(0)
			,paperId(0)
            ,field("")
			,patientName("")
			,sexID(0)
			,age(10)
			,articleNo("")
        {}
    };

    struct dataStrc
    {
		int samplePos;
        QString sampleNo;
        int cupType;
        QString cupTypeText;
		QString patientName;
		int sexID;
		QString sexIDText;
		int age;
        QString articleNo;
        QMap<int,std::tuple<bool,int>>paperCheckedCountMap;
        dataStrc()
            :samplePos(0)
            ,sampleNo("1")
            ,cupType(1)
			,patientName("")
			,sexID(0)
			,sexIDText(GlobalData::mapSexType()[sexID])
			,age(10)
			,articleNo("")
            ,cupTypeText(GlobalData::mapSampleCupType()[cupType])
            ,paperCheckedCountMap{}
        {}
    };

	int m_paper_number;

    explicit AddSampleVModel(QWidget *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags( const QModelIndex &index ) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role)override;


    void updateData();
    QVector<HeadStrc> &getHeadVect();
    QVector<dataStrc> &getVect();
signals:
    void rowSeletedByChecked(int row,int column);
private:
    QVector<HeadStrc> _headVect;
	QString _space;


public :
	QVector<dataStrc> _vect;

	QVector<QVector<bool>> m_data_check;
	QVector<bool> checkboxes_;
	QWidget* g_parent;

};

#endif // ADDSAMPLEVMODEL_H
