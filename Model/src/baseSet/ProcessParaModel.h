#ifndef PROCESSPARAMODEL_H
#define PROCESSPARAMODEL_H
#include <QString>
#include <QVector>
#include "../Model.h"

class MODELSHARED_EXPORT ProcessParaModel
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

    ProcessParaModel();
    int getId() const;
    void setId(int id);

    int getCompanyId() const;
    void setCompanyId(int companyId);

    int getGroupId() const;
    void setGroupId(int groupId);

    QString getGroupName() const;
    void setGroupName(const QString &groupName);

    QString getStepName() const;
    void setStepName(const QString &stepName);

    int getActIndex() const;
    void setActIndex(int index);

    int getActId() const;
    void setActId(int actId);

    QString getActName() const;
    void setActName(const QString &actName);

    bool getIsPopWindow() const;
    void setIsPopWindow(bool isPopWindow);

    QString getPopWindowDes() const;
    void setPopWindowDes(const QString &popWindowDes);

    QVector<ParaStrt> getParas() const;
    void setParas(QString &str);

    QString getGroupNameCode() const;
    void setGroupNameCode(const QString &groupNameCode);

    QString getStepNameCode() const;
    void setStepNameCode(const QString &stepNameCode);

    QString getActNameCode() const;
    void setActNameCode(const QString &actNameCode);

    QString getPopWindowDesCode() const;
    void setPopWindowDesCode(const QString &popWindowDesCode);

private:
    QVector<ParaStrt> strToVect(const QString &str);
    QString vectToStr(const QVector<ParaStrt> &vect);
private:
    int     _id;
    int     _companyId;
    int     _groupId;
    QString _groupName;
    QString _groupNameCode;
    QString _stepName;
    QString _stepNameCode;
    int     _actIndex;
    int     _actId;
    QString _actName;
    QString _actNameCode;
    bool    _isPopWindow;
    QString _popWindowDes;
    QString _popWindowDesCode;
    QVector<ParaStrt> _paras;
};

#endif // PROCESSPARAMODEL_H
