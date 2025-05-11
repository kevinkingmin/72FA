#ifndef SAMPLEBLL_H
#define SAMPLEBLL_H
#include <QSharedPointer>
#include <QVector>
#include <QMap>
#include "../bll.h"

class SampleDao;
class ItemModel;
class SampleModel;
class SampleTestModel;

class BLLSHARED_EXPORT SampleBLL
{
public:
    using ptrSample=QSharedPointer<SampleModel>;
    using ptrTest=QSharedPointer<SampleTestModel>;
    using ptrItem = QSharedPointer<ItemModel>;
    SampleBLL();
    QVector<ptrSample> getRowsByIds(QVector<QString> ids);
    ptrSample getRowById(QString id);
    ptrSample getUnTestSampleByBarcode(const QString &barcode);
    QVector<ptrSample>getUnTestSampleByBarcode(const QVector<QString>&vect);

    //按启动键后，才真正往数据库插入数据。否则改变的都是内存中的数据。
    bool insertModel(ptrSample pm,QVector<ptrTest> &tests);
    bool insertModel(QVector<std::tuple<ptrSample ,QVector<ptrTest>>>tps);
    bool updateModel(ptrSample pm,QVector<ptrTest>tests);
    bool updateModel(QVector<ptrSample> vect);
    bool deleteByIds(const QVector<QString>&ids);
	QList<SampleModel> getSampleList(QString paper_id);

private:
    inline QVector<ptrSample> getUnTestSamples();
    ptrSample getUnTestSampleByPos(int samplePos);
	QString creatSampleNo(QString sampleNo,QString preSampleNo="");
private:    
    SampleDao *_dao;
};

#endif // SAMPLEBLL_H
