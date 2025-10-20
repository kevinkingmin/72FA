#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H
#include <QString>
#include "../Model.h"

class MODELSHARED_EXPORT ProcessModel
{
public:
    ProcessModel();

    int getId() const;
    void setId(int id);

    // 公司ID
    int getCompanyId() const;
    void setCompanyId(int id);

    // 流程名称
    QString getProcessName() const;
    void setProcessName(const QString &pName);

    QString getRemark() const;
    void setRemark(const QString &remark);

private:
    int _id;
    int _companyId;
    QString _processName;
    QString _remark;
};
#endif // PROCESSMODEL_H
