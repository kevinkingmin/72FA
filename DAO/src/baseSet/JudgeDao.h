#ifndef JUDGE_DAO_H
#define JUDGE_DAO_H
#include "../dao.h"
#include <QVector>
#include "../Include/Model/result/JudgeRules.h"

template<class T>
class Singleton;

class QSqlQuery;

class DAOSHARED_EXPORT JudgeDao
{
private:
    JudgeDao();
    JudgeDao(JudgeDao &)=delete;
    JudgeDao(JudgeDao &&)=delete;
    JudgeDao &operator=(const JudgeDao&)=delete;
    JudgeDao &operator=(JudgeDao&&)=delete;
    friend Singleton<JudgeDao>;
public:
    ~JudgeDao();
    static JudgeDao *instance();
    QVector<JudgeRules> getAllRows();
    QVector<QString> getAllNames();
    bool getModel(const int ruleId, JudgeRules& out);
    bool insert(JudgeRules& model);
    bool update(JudgeRules& model);
    bool deleteModel(int id);
    QMap<double, QString> getJudgeValueMap(const QString itemName, const int paperId);
    QMap<double, QString> getJudgeValueMap(const int ruleId);
private:
};

#endif
