#include "TestPaperDao.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include "../Include/Comm/singleton.h"
#include "../Include/Model/baseSet/TestPaperModel.h"

TestPaperDao::TestPaperDao()
{
}

TestPaperDao::~TestPaperDao()
{
}

TestPaperDao *TestPaperDao::instance()
{
    return  Singleton<TestPaperDao>::instance();
}

bool TestPaperDao::deleteById(int id)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;
    query.prepare("DELETE FROM t_testpaper WHERE ID = ?");
    query.addBindValue(id);
    if(!query.exec())
    {
        return false;
    }
    return true;
}

// 获取所有行
QVector<TestPaperModel> TestPaperDao::getAllRows()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return {};

    QString sqlStr="SELECT * FROM t_testpaper";
    if(!query.exec(sqlStr)) return {};
    return getModelFormQuery(query);
}


// 获取名称
QVector<QString> TestPaperDao::getAllNames()
{
    QVector<TestPaperModel> papers = getAllRows();
    QVector<QString> names;
    for(TestPaperModel& paper : papers)
    {
        names.push_back(paper.getPaperName());
    }
    return names;
}

bool TestPaperDao::getModel(const int paperId, TestPaperModel& out)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;
    query.prepare("SELECT * FROM t_testpaper WHERE ID = ?");
    query.addBindValue(paperId);
    if(!query.exec()) return false;
    QVector<TestPaperModel> vect = getModelFormQuery(query);
    if(vect.isEmpty()) return false;
    out = std::move(vect.first());
    return true;
}

bool TestPaperDao::insert(TestPaperModel& model)
{
    QSqlQuery query;
    if (DAO::createQuery(query) < 0) return false;
    // 使用预处理语句进行插入
    query.prepare("INSERT INTO t_testpaper (PaperName,PaperType,CompanyID,TotalNumber,ItemNumber,"
                  "TestPaparLenght,FuncPosition,CutoffPosition,FuncGrayThreshold,IsCutOff,"
                  "CutoffValue,CutoffGrayThreshold,ArticleNo,PaperColorOnUi,IsPaperHide,"
                  "FuncFindWidth,ItemLineWidth,PaperMmToPixel,PaperHeight,AnalysisPercentOfHeight,"
                  "AnalysisPercentOfWidth,IgnoreHeadLenght,TestBlockWidth,FuncFindDir,PaperShowAngle,"
                  "PaperSortIdxOnUi,PaperBinarizationThreshold,PaperBackgroundValue,BlackPointDetectThreshold,IsBlackPointDetect,"
                  "ItemFindWidth, ProcessId) "
                  "VALUES ("
                  "?, ?, ?, ?, ?, "
                  "?, ?, ?, ?, ?,"
                  "?, ?, ?, ?, ?,"
                  "?, ?, ?, ?, ?,"
                  "?, ?, ?, ?, ?,"
                  "?, ?, ?, ?, ?,"
                  "?, ?)");
    query.addBindValue(model.getPaperName());
    query.addBindValue(model.getPaperType());
    query.addBindValue(model.getCompanyId());
    query.addBindValue(model.getTotalNumber());
    query.addBindValue(model.getTestItemNumber());

    query.addBindValue(model.getPaperLenght());
    query.addBindValue(model.getFuncPosition());
    query.addBindValue(model.getCutOffPosition());
    query.addBindValue(model.getFuncGrayThreshold());
    query.addBindValue(model.getIsCutOff());

    query.addBindValue(model.getCutOffValue());
    query.addBindValue(model.getCutOffThreshold());
    query.addBindValue(model.getArticleNo());
    query.addBindValue(model.getPaperColorOnUi());
    query.addBindValue(model.isPaperHide());
    query.addBindValue(model.getFuncFindWidth());
    query.addBindValue(model.getItemLineWidth());
    query.addBindValue(model.getPaperMmToPixel());
    query.addBindValue(model.getPaperHeight());
    query.addBindValue(model.getAnalysisPercentOfHeight());
    query.addBindValue(model.getAnalysisPercentOfWidth());
    query.addBindValue(model.getIgnoreHeadLenght());
    query.addBindValue(model.getTestBlockWidth());
    query.addBindValue(model.getFuncFindDir());
    query.addBindValue(model.getPaperShowAngle());
    query.addBindValue(model.getPaperSortIdxOnUi());
    query.addBindValue(model.getPaperBinarizationThreshold());
    query.addBindValue(model.getPaperBackgroundValue());
    query.addBindValue(model.getBlackPointDetectThreshold());
    query.addBindValue(model.getIsBlackPointDetect());
    query.addBindValue(model.getItemFindWidth());
    query.addBindValue(model.getProcessId());
    if(!query.exec())
    {
        QSqlError err = query.lastError();
        qDebug() << "SQL Insert FAILED!";
        qDebug() << "Error Code:" << err.number();
        qDebug() << "Error Msg:" << err.text();
        qDebug() << "Database Text:" << err.databaseText();
        qDebug() << "Driver Text:" << err.driverText();
        // （Qt 5.13+）可选：查看实际执行的语句（仅占位符，不展开值）
        qDebug() << "Executed Query (with ?):" << query.executedQuery();
        return false;
    }
    // 获取刚插入记录的自增主键 ID
    QVariant lastId = query.lastInsertId();
    if (!lastId.isValid()) {
        return false;
    }
    // 将生成的 ID 设置回 model（假设你有 setId 方法）
    model.setId(lastId.toInt());
    return true;
}
bool TestPaperDao::update(TestPaperModel& model)
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0) return false;
    query.prepare("UPDATE t_testpaper SET PaperName = ?,PaperType = ?,CompanyID = ?,TotalNumber = ?,ItemNumber = ?,"
                  "TestPaparLenght = ?,FuncPosition = ?,CutoffPosition = ?,FuncGrayThreshold = ?,IsCutOff = ?,"
                  "CutoffValue = ?,CutoffGrayThreshold = ?,ArticleNo = ?,PaperColorOnUi = ?,IsPaperHide = ?,"
                  "FuncFindWidth = ?,ItemLineWidth = ?,PaperMmToPixel = ?,PaperHeight = ?,AnalysisPercentOfHeight = ?,"
                  "AnalysisPercentOfWidth = ?,IgnoreHeadLenght = ?,TestBlockWidth = ?,FuncFindDir = ?,PaperShowAngle = ?,"
                  "PaperSortIdxOnUi = ?,PaperBinarizationThreshold = ?,PaperBackgroundValue = ?,BlackPointDetectThreshold = ?,IsBlackPointDetect = ?,"
                  "ItemFindWidth = ?, ProcessId = ? WHERE ID = ?");
    query.addBindValue(model.getPaperName());
    query.addBindValue(model.getPaperType());
    query.addBindValue(model.getCompanyId());
    query.addBindValue(model.getTotalNumber());
    query.addBindValue(model.getTestItemNumber());

    query.addBindValue(model.getPaperLenght());
    query.addBindValue(model.getFuncPosition());
    query.addBindValue(model.getCutOffPosition());
    query.addBindValue(model.getFuncGrayThreshold());
    query.addBindValue(model.getIsCutOff());

    query.addBindValue(model.getCutOffValue());
    query.addBindValue(model.getCutOffThreshold());
    query.addBindValue(model.getArticleNo());
    query.addBindValue(model.getPaperColorOnUi());
    query.addBindValue(model.isPaperHide());
    query.addBindValue(model.getFuncFindWidth());
    query.addBindValue(model.getItemLineWidth());
    query.addBindValue(model.getPaperMmToPixel());
    query.addBindValue(model.getPaperHeight());
    query.addBindValue(model.getAnalysisPercentOfHeight());
    query.addBindValue(model.getAnalysisPercentOfWidth());
    query.addBindValue(model.getIgnoreHeadLenght());
    query.addBindValue(model.getTestBlockWidth());
    query.addBindValue(model.getFuncFindDir());
    query.addBindValue(model.getPaperShowAngle());
    query.addBindValue(model.getPaperSortIdxOnUi());
    query.addBindValue(model.getPaperBinarizationThreshold());
    query.addBindValue(model.getPaperBackgroundValue());
    query.addBindValue(model.getBlackPointDetectThreshold());
    query.addBindValue(model.getIsBlackPointDetect());
    query.addBindValue(model.getItemFindWidth());
    query.addBindValue(model.getProcessId());
    query.addBindValue(model.getId());
    if(!query.exec())
    {
        QSqlError err = query.lastError();
        qDebug() << "SQL Insert FAILED!";
        qDebug() << "Error Code:" << err.number();
        qDebug() << "Error Msg:" << err.text();
        qDebug() << "Database Text:" << err.databaseText();
        qDebug() << "Driver Text:" << err.driverText();
        // （Qt 5.13+）可选：查看实际执行的语句（仅占位符，不展开值）
        qDebug() << "Executed Query (with ?):" << query.executedQuery();
        return false;
    }
    return true;
}

QVector<TestPaperModel> TestPaperDao::getModelFormQuery(QSqlQuery& query)
{
    QVector<TestPaperModel> vect;
    while (query.next())
    {
        TestPaperModel model;
        model.setId(query.value("ID").toInt());
        model.setCompanyId(query.value("CompanyID").toInt());
        model.setProcessId(query.value("ProcessId").toInt());
        model.setPaperName(query.value("PaperName").toString());
        model.setPaperType(query.value("PaperType").toInt());
        model.setTotalNumber(query.value("TotalNumber").toInt());
        model.setTestItemNumber(query.value("ItemNumber").toInt());
        model.setPaperLenght(query.value("TestPaparLenght").toDouble());
        model.setFuncPosition(query.value("FuncPosition").toDouble());
        model.setCutOffPosition(query.value("CutoffPosition").toDouble());
        model.setFuncGrayThreshold(query.value("FuncGrayThreshold").toDouble());
        model.setIsCutOff(query.value("IsCutOff").toInt());
        model.setCutOffValue(query.value("CutoffValue").toDouble());
        model.setCutOffThreshold(query.value("CutoffGrayThreshold").toDouble());
        model.setArticleNo(query.value("ArticleNo").toString());
        model.setPaperColorOnUi(query.value("PaperColorOnUi").toString());
        model.setPaperHide(query.value("IsPaperHide").toInt() == 1);
        model.setFuncFindWidth(query.value("FuncFindWidth").toDouble());
        model.setItemLineWidth(query.value("ItemLineWidth").toDouble());
        model.setPaperMmToPixel(query.value("PaperMmToPixel").toDouble());
        model.setPaperHeight(query.value("PaperHeight").toDouble());
        model.setAnalysisPercentOfHeight(query.value("AnalysisPercentOfHeight").toInt());
        model.setAnalysisPercentOfWidth(query.value("AnalysisPercentOfWidth").toInt());
        model.setIgnoreHeadLenght(query.value("IgnoreHeadLenght").toDouble());
        model.setTestBlockWidth(query.value("TestBlockWidth").toDouble());
        model.setFuncFindDir(query.value("FuncFindDir").toInt());
        model.setPaperShowAngle(query.value("PaperShowAngle").toInt());
        model.setPaperSortIdxOnUi(query.value("PaperSortIdxOnUi").toInt());
        model.setPaperBinarizationThreshold(query.value("PaperBinarizationThreshold").toInt());
        model.setPaperBackgroundValue(query.value("PaperBackgroundValue").toDouble());
        model.setBlackPointDetectThreshold(query.value("BlackPointDetectThreshold").toDouble());
        model.setIsBlackPointDetect(query.value("IsBlackPointDetect").toInt() == 1);
        model.setItemFindWidth(query.value("ItemFindWidth").toDouble());

        vect.push_back(std::move(model));
    }
    return vect;
}
