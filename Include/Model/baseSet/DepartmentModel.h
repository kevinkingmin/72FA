#ifndef DEPARTMENTMODEL_H
#define DEPARTMENTMODEL_H
#include"../Model.h"
#include<QString>

class MODELSHARED_EXPORT DepartmentModel
{
public:
    DepartmentModel();

    uint getID() const;
    void setID(const uint &value);

    QString getDepartmentName() const;
    void setDepartmentName(const QString &value);

    QString getShortKey() const;
    void setShortKey(const QString &value);

    QString getRemark() const;
    void setRemark(const QString &remark);

private:
    uint _ID;
    QString _DepartmentName;
    QString _shortKey;
    QString _remark;
};

#endif // DEPARTMENTMODEL_H
