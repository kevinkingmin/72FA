#ifndef	JUDGERULESMODEL_H
#define JUDGERULESMODEL_H
#include <QString>
#include <QVector>
#include "../Model.h"
class MODELSHARED_EXPORT JudgeRules
{
public:
    // 参数
    struct ParameterStrt
    {

        // 显示字符
        QString _k;
        // 灰度值
        double _v;
        ParameterStrt()
            :_k("")
            ,_v(0)
        {}
        ParameterStrt(const QString key, const double value)
            :_k(key)
            ,_v(value)
        {}
        // 重载 == 操作符
        bool operator==(const ParameterStrt& other) const
        {
            return _k == other._k && qAbs(_v - other._v) < 0.001;
        }
    };
    JudgeRules();

	int getpkid() const;
	void setpkid(int pkid);

    QString getRuleName() const;
    void setRuleName(QString name);

    QVector<ParameterStrt> getParameter();
    void setParameter(QVector<ParameterStrt> parameter);
    bool strToParameter(const QString &str);
    QString parameterToStr();

    // 是否重复
    bool hasParameterDuplicates(QVector<JudgeRules::ParameterStrt> parameter);
private:
    int     _pkid;
    QString     _ruleName;
    QVector<ParameterStrt> _parameter;
};

inline uint qHash(const JudgeRules::ParameterStrt& p, uint seed = 0)
{
    Q_UNUSED(seed)

    // 哈希组合策略：
    // 1. _k 是 QString，直接用 qHash
    // 2. _v 是 double，做近似量化处理（保留3位小数精度）
    uint h1 = qHash(p._k);
    uint h2 = qHash(static_cast<int>(p._v * 1000 + 0.5)); // 四舍五入转整数

    // 混合两个哈希值，避免冲突
    return (h1 ^ (h2 << 16)) | (h2 >> 16);
}
#endif 

