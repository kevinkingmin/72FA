#ifndef PROCESSSTEPMODEL_H
#define PROCESSSTEPMODEL_H
#include <QString>
#include <QVector>
#include "../Model.h"
#include "CommonType.h"

class MODELSHARED_EXPORT ProcessStepModel
{
public:
    struct ParaStrt
    {
        int id;
        QString paraName;
        double paraValue;
        ParaStrt()
            :id(0)
            ,paraName("")
            ,paraValue(0)
        {}
    };

    ProcessStepModel();
    int getId() const;
    void setId(int id);

    QString getTName() const;
    void setTName(const QString &tName);

    int getActTime() const;
    void setActTime(int actTime);

    QString getRemark() const;
    void setRemark(const QString &remark);

    QVector<ParaStrt> getTemplateParas() const;
    void setTemplateParas(const QString &&str);

private:
    QVector<ParaStrt> strToVect(const QString &str);
    QString vectToStr(const QVector<ParaStrt> &vect);
private:
    int _id;
    QString _tName;
    int _actTime;
    QString _remark;
    QVector<ParaStrt>_templateParas;
};
#endif // PROCESSSTEPMODEL_H
