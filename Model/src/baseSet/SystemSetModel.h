#ifndef SYSTEMSETMODEL_H
#define SYSTEMSETMODEL_H
#include"../Model.h"
#include<QString>

class MODELSHARED_EXPORT SystemSetModel
{
public:
    SystemSetModel();
    uint getId() const;
    void setId(const uint &id);

    int getSaveSet() const;
    void setSaveSet(int saveSet);

    QString getSaveDes() const;
    void setSaveDes(const QString &saveDes);

    QString getRemark() const;
    void setRemark(const QString &remark);

private:
    uint _id;
    int _saveSet;
    QString _saveDes;
    QString _remark;
};

#endif // SYSTEMSETMODEL_H
