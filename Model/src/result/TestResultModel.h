#ifndef	TESTRESULTMODEL_H
#define TESTRESULTMODEL_H
#include <QString>
#include "../Model.h"
class MODELSHARED_EXPORT TestResultModel
{
public:
    int getID() const;
    void setID(int ID);
    int getTestPaperID() const;
    void setTestPaperID(int TestPaperID);
    QString getItemName() const;
    void setItemName(QString itemName);
    int getPositionNo() const;
    void setPositionNo(int PositionNo);
    double getPosition() const;
    void setPosition(double Position);
    bool getIsNull() const;
    void setIsNull(bool IsNull);

private:
    int _ID;
    int _TestPaperID;
    QString _itemName;
    int _PositionNo;
    double _Position;
    bool _IsNull;
};
#endif

