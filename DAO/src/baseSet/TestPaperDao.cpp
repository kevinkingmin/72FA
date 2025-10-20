#include "TestPaperDao.h"
#include <QSqlQuery>
#include <QVariant>
#include "../Include/Comm/singleton.h"
#include "../Include/Model/baseSet/TestPaperModel.h"

TestPaperDao::TestPaperDao()
{
}

void TestPaperDao::getTable()
{
    QSqlQuery query;
    if(DAO::createQuery(query)<0)
        return;
    QString sqlStr="SELECT * FROM t_testpaper where IsPaperHide=0 order by PaperSortIdxOnUi asc ";
    if(!query.exec(sqlStr))
        return;
    QMap<int,ptrModel>tempMap;
    _map.swap(tempMap);
    int id=0;
    while (query.next())
    {
        ptrModel pm(new TestPaperModel);
        id = query.value("ID").toInt();
        pm->setId(id);
        pm->setCompanyId(query.value("CompanyID").toInt());
        pm->setPaperName(query.value("PaperName").toString());
        pm->setPaperType(query.value("PaperType").toInt());
        pm->setTotalNumber(query.value("TotalNumber").toInt());
        pm->setTestItemNumber(query.value("ItemNumber").toInt());
        pm->setPaperLenght(query.value("PaperLenght").toDouble());
        pm->setPaperHeight(query.value("PaperHeight").toDouble());
        pm->setPaperMmToPixel(query.value("PaperMmToPixel").toDouble());
        pm->setIgnoreHeadLenght(query.value("IgnoreHeadLenght").toDouble());
        pm->setTestBlockWidth(query.value("TestBlockWidth").toDouble());
        pm->setFuncFindDir(query.value("FuncFindDir").toInt());
        pm->setFuncPosition(query.value("FuncPosition").toDouble());
        pm->setFuncFindWidth(query.value("FuncFindWidth").toDouble());
        pm->setFuncGrayThreshold(query.value("FuncGrayThreshold").toDouble());
        pm->setIsBlackPointDetect(query.value("IsBlackPointDetect").toInt() == 1);
        pm->setBlackPointDetectThreshold(query.value("BlackPointDetectThreshold").toDouble());
        pm->setIsCutOff(query.value("IsCutOff").toInt());
        pm->setCutOffPosition(query.value("CutoffPosition").toDouble());
        pm->setCutOffValue(query.value("CutoffValue").toDouble());
        pm->setCutOffThreshold(query.value("CutOffThreshold").toDouble());
        pm->setPaperShowAngle(query.value("PaperShowAngle").toInt());
        pm->setPaperBinarizationThreshold(query.value("PaperBinarizationThreshold").toInt());
        pm->setPaperBackgroundValue(query.value("PaperBackgroundValue").toDouble());
        pm->setItemFindWidth(query.value("ItemFindWidth").toDouble());
        pm->setItemLineWidth(query.value("ItemLineWidth").toDouble());
        pm->setAnalysisPercentOfWidth(query.value("AnalysisPercentOfWidth").toInt());
        pm->setAnalysisPercentOfHeight(query.value("AnalysisPercentOfHeight").toInt());
        pm->setPaperColorOnUi(query.value("PaperColorOnUi").toString());
        pm->setPaperHide(query.value("IsPaperHide").toInt() == 1);
        pm->setArticleNo(query.value("ArticleNo").toString());
        pm->setPaperSortIdxOnUi(query.value("PaperSortIdxOnUi").toInt());
		_map.insert(id, pm);
    }
}

void TestPaperDao::queryBindValue(QSqlQuery &query, TestPaperDao::ptrModel pm)
{
    query.bindValue(":ID",pm->getId());
    query.bindValue(":CompanyID",pm->getCompanyId());
    query.bindValue(":PaperName",pm->getPaperName());
    query.bindValue(":PaperType",pm->getPaperType());
    query.bindValue(":TotalNumber",pm->getTotalNumber());
    query.bindValue(":ItemNumber",pm->getTestItemNumber());
    query.bindValue(":PaperLenght",pm->getPaperLenght());
    query.bindValue(":PaperHeight",pm->getPaperHeight());
    query.bindValue(":PaperMmToPixel",pm->getPaperMmToPixel());
    query.bindValue(":IgnoreHeadLenght",pm->getIgnoreHeadLenght());
    query.bindValue(":TestBlockWidth",pm->getTestBlockWidth());
    query.bindValue(":FuncFindDir",pm->getFuncFindDir());
    query.bindValue(":FuncPosition",pm->getFuncPosition());
    query.bindValue(":FuncFindWidth",pm->getFuncFindWidth());
    query.bindValue(":FuncGrayThreshold",pm->getFuncGrayThreshold());
    query.bindValue(":IsBlackPointDetect",pm->getIsBlackPointDetect()?1:0);
    query.bindValue(":BlackPointDetectThreshold",pm->getBlackPointDetectThreshold());
    query.bindValue(":IsCutOff",pm->getIsCutOff()?1:0);
    query.bindValue(":CutoffPosition",pm->getCutOffPosition());
    query.bindValue(":CutoffValue",pm->getCutOffValue());
    query.bindValue(":CutOffThreshold",pm->getCutOffThreshold());
    query.bindValue(":PaperShowAngle",pm->getPaperShowAngle());
    query.bindValue(":PaperBinarizationThreshold",pm->getPaperBinarizationThreshold());
    query.bindValue(":PaperBackgroundValue",pm->getPaperBackgroundValue());
    query.bindValue(":ItemFindWidth",pm->getItemFindWidth());
    query.bindValue(":ItemLineWidth",pm->getItemLineWidth());
    query.bindValue(":AnalysisPercentOfWidth",pm->getAnalysisPercentOfWidth());
    query.bindValue(":AnalysisPercentOfHeight",pm->getAnalysisPercentOfHeight());
    query.bindValue(":PaperColorOnUi",pm->getPaperColorOnUi());
    query.bindValue(":IsPaperHide",pm->isPaperHide()?1:0);
    query.bindValue(":ArticleNo",pm->getArticleNo());
    query.bindValue(":PaperSortIdxOnUi",pm->getPaperSortIdxOnUi());
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
    if(DAO::createQuery(query)<0)
        return false;
    QString delSql="update t_testpaper set IsPaperHide=1 where ID="+QString::number(id);
    if(!query.exec(delSql))
    {
        return false;
    }

    if(!_map.keys().contains(id))
        getTable();
    else
        _map[id]->setPaperHide(true);

    return true;
}

QVector<TestPaperDao::ptrModel> TestPaperDao::getAllRows()
{
    if(_map.isEmpty())
        getTable();
    QVector<ptrModel> outVect;
    auto list = _map.values();
    for(auto it:list)
    {
        auto m=*it;
        ptrModel p(new TestPaperModel(std::move(m)));
        outVect.push_back(p);
    }
    return outVect;
}
