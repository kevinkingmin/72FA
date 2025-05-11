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

    bool getIsNull() const;
    void setIsNull(bool IsNull);

    bool operator==(ItemModel &it)const;

private:
    int _ID;
    int _TestPaperID;
    QString _itemName;
    int _PositionNo;
    bool _IsNull;

};

#endif // ITEMMODEL_H
