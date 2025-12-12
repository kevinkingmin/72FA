#ifndef ITEMMODEL_H
#define ITEMMODEL_H
#include <QString>
#include "../Model.h"

class MODELSHARED_EXPORT ItemModel
{
public:
    static const int ITEM_TYPE_FUNC;
    static const int ITEM_TYPE_CUTOFF;
    static const int ITEM_TYPE_ITEM;

    static const QString FC_NAME;
    static const QString CUTOFF_NAME;

    ItemModel();
    int getID() const;
    void setID(const int &ID);

    int getTestPaperID() const;
    void setTestPaperID(int TestPaperID);

    QString getItemName() const;
    void setItemName(const int itemType, const QString &itemName);

    int getItemType() const;

    int getSegmentIndex() const;
    void setSegmentIndex(int segmentIndex);

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
    int _itemType;
    int _segmentIndex; // 段序号
    int _PositionNo;
    int _CurveId; // 曲线ID
    int _RulesId; // 规则ID
    double _ResultOffset; // 结果补偿
    double _Position; // 位置
    bool _IsNull;
    QString _ItemFullName; // 项目全称
};

#endif
