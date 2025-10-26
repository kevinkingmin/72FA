#include "CompanyModel.h"

CompanyModel::CompanyModel():
     _id(0)
     ,_name("")
{

}

int CompanyModel::getId() const
{
    return _id;
}

void CompanyModel::setId(int id)
{
    _id = id;
}

QString CompanyModel::getName() const
{
    return _name;
}

void CompanyModel::setName(const QString &name)
{
    _name = name;
}

