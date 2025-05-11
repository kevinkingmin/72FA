#ifndef INSTRUMENTPARASSETBLL_H
#define INSTRUMENTPARASSETBLL_H

#include "../bll.h"
#include <QVector>
class InstrumentParasSetModel;
class InstrumentParasSetDao;
class BLLSHARED_EXPORT InstrumentParasSetBLL
{
public:
    InstrumentParasSetBLL();
    QVector<InstrumentParasSetModel>getAllRows();
    QVector<InstrumentParasSetModel> getRowsByIds(QVector<uint>ids);
    InstrumentParasSetModel getRowById(uint id);
    bool updateByModel(InstrumentParasSetModel pm);
private:
    InstrumentParasSetDao *_dao;
};

#endif // INSTRUMENTPARASSETBLL_H
