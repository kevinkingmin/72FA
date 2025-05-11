#ifndef BARCODERULE_H
#define BARCODERULE_H
#include <QString>
#include <QVector>
#include "../bll.h"
//试剂条码解析
   //试剂码类别标识（2 位）+ 试剂组分标识（2 位）+ 项目代码（5 位）+ 批号代码（10 位）
   //+ 序列号代码（5 位）+ 有效日期（6 位）+ 试剂类型（1 位）+ 预留位(1 位)。
   //2+2+5+10+5+6+1+1=32  ----试剂
   //试剂条码举例：HC0110001CP200500010000122052010
     /*
      * HC---是胡曼智造化学发光
      * 01---试剂条码（01 - 试剂条码，05 – 稀释液条码，06 – 底物液条码）
      * 10001---项目号
      * CP20050001--批号
      * 00001---序列号
      * 220520---表示试剂有效期
      * 1---试剂类型（1 - 代表 R0、R1、R2，3 - 代表 R3、R4）
      */

//试剂码类别标识（2 位）+ 试剂组分标识（2 位）+ 批号代码（10 位）
//+ 序列号代码（5 位）+有效日期（6 位）+ 试剂类型（1 位）+ 预留位(1 位)。

//稀释液条码：
    //HC05CP200500010000122052010
//底物
    //HC06CP200500010000122052010

/**
 * @brief 试剂、定标、质控，如果是同一批，则 【项目代码（5 位）+ 批号代码（10 位）】相同
 */
class BLLSHARED_EXPORT BarCodeRule
{
public:
    BarCodeRule();
    enum BarCodeType
    {
        enumReagent=1,
        enumCalibrate=2,
        enumCalCuve=3,
        enumQC=4,
        enumDiluent=5,
        enumSubstrate=6
    };

    enum ReagentClass
    {
        enumR012=1,
        enumR34=3,
    };

    QString getLeader() const;
    void setLeader(const QString &leader);

    int getBarCodeType() const;
    void setBarCodeType(const int &barCodeType);

    int getItemID() const;
    void setItemID(const int &ItemID);

    QString getBarCode() const;
    void setBarCode(const QString &barCode);

    qint64 getStability() const;
    void setStability(const qint64 &stability);

    QString getSerialnumber() const;
    void setSerialnumber(const QString &serialnumber);

    int getReagentClass() const;
    void setReagentClass(const int &val);

    bool getReagentBarCode(const QString &barCode);
    bool getUniversalReagentBarCode(const QString &barCode);
private:    
    bool barCodeValidAndGet(const QString &barCode);
private:
    QString _leader;
    int _barCodeType;//试剂、定标等
    int    _ItemID;
    QString _barCode;
    qint64 _stability;
    QString _serialnumber;
    int _reagentClass;//(底物A,底物B)
    static QVector<int>_CodeTypeVect;
};

#endif // BARCODERULE_H
