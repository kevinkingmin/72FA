#ifndef INSTRUMENTPARASSETMODEL_H
#define INSTRUMENTPARASSETMODEL_H
#include "../Model.h"
#include <QString>
#include <QVector>

class MODELSHARED_EXPORT InstrumentParasSetModel
{
public:
    InstrumentParasSetModel();
    struct paraStruct
    {
        int id;
        QString paraName;
        double para;
        paraStruct()
            :id(0)
            ,paraName("")
            ,para(0)
        {}
    };
public:

    uint getId() const;
    void setId(const uint &id);

    QVector<paraStruct> getParas() const;
    void setParas(QString &str);

    int getPreIntFileld1() const;
    void setPreIntFileld1(int preIntFileld1);

    QString getRemark() const;
    void setRemark(const QString &remark);

    QString vectToStr(QVector<paraStruct> vect);

private:
    QVector<paraStruct> strToVect(const QString &str);
private:
    uint _id;
    QVector<paraStruct>_paras;
    int _preIntFileld1;
    QString _remark;	
};

#endif // INSTRUMENTPARASSETMODEL_H
