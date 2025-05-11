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
    QString sqlStr="SELECT * FROM t_testpaper where isDelete=0 order by sort_idx asc ";
    if(!query.exec(sqlStr))
        return;
    QMap<int,ptrModel>tempMap;
    _map.swap(tempMap);
    int id=0;
	int sort_id = 0;
    while (query.next())
    {
        ptrModel pm(new TestPaperModel);
        id=query.value("ID").toInt();
		sort_id = query.value("sort_idx").toInt();
        pm->setID(id);
        pm->setPaperName(query.value("PaperName").toString());
        pm->setCompanyId(query.value("Company_ID").toInt());
        pm->setTotalNumber(query.value("TotalNumber").toInt());
        pm->setItemNumber(query.value("Item_Number").toInt());
        pm->setTestPaparLenght(query.value("TestPaparLenght").toInt());
        pm->setFuncPosition(query.value("FuncPosition").toInt());
        pm->setTestAeaLenght(query.value("TestAeaLenght").toInt());
        pm->setUsageV(query.value("usageV").toInt());
        pm->setDefaultBGRGB(query.value("defaultBGRGB").toString());
        pm->setBGRGB(query.value("BGRGB").toString());
		pm->setArticleNo(query.value("articleNo").toString());//->setBGRGB(query.value("BGRGB").toString());
        pm->setIsDelete(query.value("isDelete").toInt()==0?false:true);
		pm->setSort_idx(query.value("sort_idx").toInt());
        //_map.insert(sort_id,pm);
		_map.insert(id, pm);
    }
}

void TestPaperDao::queryBindValue(QSqlQuery &query, TestPaperDao::ptrModel pm)
{
    query.bindValue(":ID",pm->getID());
    query.bindValue(":PaperName",pm->getPaperName());
    query.bindValue(":Company_ID",pm->getCompanyId());
    query.bindValue(":TotalNumber",pm->getTotalNumber());
    query.bindValue(":Item_Number",pm->getItemNumber());
    query.bindValue(":TestPaparLenght",pm->getTestPaparLenght());
    query.bindValue(":FuncPosition",pm->getFuncPosition());
    query.bindValue(":TestAeaLenght",pm->getTestAeaLenght());
    query.bindValue(":usageV",pm->getUsageV());
    query.bindValue(":defaultBGRGB",pm->getDefaultBGRGB());
    query.bindValue(":BGRGB",pm->getBGRGB());
	query.bindValue(":articleNo", pm->getBGRGB());
    query.bindValue(":isDelete",pm->getIsDelete()?1:0);
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
    QString delSql="update t_testpaper set isDelete=1 where ID="+QString::number(id);
    if(!query.exec(delSql))
    {
        return false;
    }

    if(!_map.keys().contains(id))
        getTable();
    else
        _map[id]->setIsDelete(true);

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
