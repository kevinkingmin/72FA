#ifndef COMPANY_MODEL_H
#define COMPANY_MODEL_H
#include <QString>
#include "../Model.h"

class MODELSHARED_EXPORT CompanyModel
{
public:
    CompanyModel();

    int getId() const;
    void setId(int id);

    // 公司名称
    QString getName() const;
    void setName(const QString &name);

private:
    int _id;
    QString _name;
};
#endif
