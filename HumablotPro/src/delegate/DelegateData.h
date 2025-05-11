#ifndef DELEGATEDATA_H
#define DELEGATEDATA_H
#include<QObject>

struct CheckBoxData
{
    bool isCheck;
    QString text;
    CheckBoxData()
      :isCheck(false)
      ,text("")
    {}
};
Q_DECLARE_METATYPE(CheckBoxData)
#endif // DELEGATEDATA_H
