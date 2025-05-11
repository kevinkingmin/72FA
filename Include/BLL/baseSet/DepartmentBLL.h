#ifndef DEPARTMENTBLL_H
#define DEPARTMENTBLL_H
#include "../bll.h"
#include <QSharedPointer>
#include <QVector>

class DepartmentModel;
class BLLSHARED_EXPORT DepartmentBLL
{
public:
    DepartmentBLL();
    using ptrModel=QSharedPointer<DepartmentModel>;

    QVector<ptrModel>getAllRows();
    QVector<ptrModel> getRowsByIds(QVector<uint>ids);
    ptrModel getRowById(uint id);
    int updateByModel(ptrModel pm);
    bool deleteById(uint id);
    int insertModel(ptrModel pm);
};

#endif // DEPARTMENTBLL_H
