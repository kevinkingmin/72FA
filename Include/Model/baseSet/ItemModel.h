#ifndef ITEMMODEL_H
#define ITEMMODEL_H
#include <QString>
#include "../Model.h"

class MODELSHARED_EXPORT ItemModel
{
public:
    ItemModel();
    int getID() const;
    void setID(const int &ID);

    int getTestPaperID() const;
    void setTestPaperID(int TestPaperID);

    QString getItemName() const;
    void setItemName(const QString &itemName);

    int getPositionNo() const;
    void setPositionNo(int PositionNo);

    int getCurveId() const;
    void setCurveId(int curveId);

    int getRulesId() const;
    void setRulesId(int ruleId);

    double getResultOffset() const;
    void setResultOffset(double resultOffset);

    double getPosition() const;
    void setPosition(double position);

    bool getIsNull() const;
    void setIsNull(bool IsNull);

    QString getItemFullName() const;
    void setItemFullName(QString itemFullName);

    bool operator==(ItemModel &it)const;

private:
    int _ID;
    int _TestPaperID;
    QString _itemName;
    int _PositionNo;
    int _CurveId; // 曲线ID
    int _RulesId; // 规则ID
    double _ResultOffset; // 结果补偿
    double _Position; // 位置
    bool _IsNull;
    QString _ItemFullName; // 项目全称
};

#endif
