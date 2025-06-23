#include "SampleBLL.h"
#include "SampleTestBLL.h"
#include "src/baseSet/ItemBll.h"
#include "../Include/DAO/sample/SampleDao.h"
#include "../Include/Model/sample/SampleModel.h"
//#include "../Include/Model/baseSet/ItemModel.h"
#include "../Include/DAO/baseSet/ItemDao.h"
#include "../Include/Utilities/log.h"
#include "../Include/Model/sample/SampleTestModel.h"

SampleBLL::SampleBLL() :
    _dao(SampleDao::instance())
{
}

QVector<SampleBLL::ptrSample> SampleBLL::getRowsByIds(QVector<QString> ids)
{
    QVector<ptrSample>outVect;
    if (ids.isEmpty())
        return outVect;
    QString queryStr= " where ";
    for(int i=0;i<ids.size();i++){
        if(i==0){
            queryStr+=" id = '"+ids.data()[i]+"'";
        }else{
            queryStr+=" or id = '"+ids.data()[i]+"'";
        }
    }
    QList<SampleModel> sampleList= getSampleList(queryStr);
    for (auto it : sampleList)
    {
        ptrSample sampleResult(new SampleModel(it));
        outVect.push_back(sampleResult);
    }
    return outVect;
}

QList<SampleModel> SampleBLL::getSampleList(QString query_condition)
{
    QList<SampleModel> item_model_list;
    item_model_list = SampleDao::instance()->getSampleList(query_condition);
    return item_model_list;
}

SampleBLL::ptrSample SampleBLL::getRowById(QString id)
{
    QList<SampleModel> sampleList= getSampleList(" where id='"+id+"'");
    ptrSample sampleResult(new SampleModel(sampleList.at(0)));
    return sampleResult;
}

SampleBLL::ptrSample SampleBLL::getRowByPkId(const int pkid)
{
    QList<SampleModel> sampleList= getSampleList(QString(" where pkid=%1").arg(pkid));
    if(sampleList.isEmpty())
        return nullptr;
    ptrSample sampleResult(new SampleModel(sampleList.at(0)));
    return sampleResult;
}

SampleBLL::ptrSample SampleBLL::getUnTestSampleByBarcode(const QString &barcode)
{
    ptrSample sm=nullptr;
    if(barcode.isEmpty())
        return sm;
    auto vect = getUnTestSamples();
    for (auto it : vect)
    {
        if(!it->getBarcode().compare(barcode,Qt::CaseInsensitive) && it->getStateFlag()==1)
            return it;
    }
    return sm;
}

QVector<SampleBLL::ptrSample> SampleBLL::getUnTestSampleByBarcode(const QVector<QString> &vect)
{
    QVector<ptrSample>outVect;
    if(vect.isEmpty())
        return outVect;
    auto tvect = getUnTestSamples();
    for(auto it:tvect)
    {
        if(it->getBarcode().isEmpty())
            continue;
        if(vect.contains(it->getBarcode()))
        {
            outVect.push_back(it);
            if(vect.count()==outVect.count())
                return outVect;
        }
    }
    return outVect;
}

bool SampleBLL::insertModel(ptrSample pm, QVector<ptrTest> &tests)
{
    if(pm.isNull())
    {
        eLog("pm is null");
        return false;
    }
    using ResultSct=SampleTestModel::TestResultSct;
    for(auto it:tests)
    {
        QVector<ResultSct>resultVect;
        auto paperId=it->getPaperId();
        auto itemVect=ItemBll().getRowsByPaperId(paperId);
        if(itemVect.isEmpty())
        {
            //eLog("没有给当前膜条配制项目,sampleId:{},testId:{},paperId:{}",pm->getId(),it->getId(),paperId);
            return false;
        }
        for(auto item:itemVect)
        {
            ResultSct r;
            r.itemId=item->getID();
            r.orderNo=item->getPositionNo();
            resultVect.push_back(r);
        }
        //it->setResultVect(resultVect);
    }
    std::tuple<ptrSample, QVector<ptrTest>>tp(pm,tests);
    return _dao->insertModel({tp});
}

bool SampleBLL::insertModel(QVector<std::tuple<SampleBLL::ptrSample, QVector<SampleBLL::ptrTest>>>tps)
{
    if(tps.isEmpty())
        return false;
    return _dao->insertModel(tps);
}

bool SampleBLL::updateModel(QVector<ptrSample> vect)
{
    if(vect.isEmpty())
        return false;
    for(auto it:vect)
    {
        if(it.isNull() || it->getId()<=0)
        {
            eLog("vect中存在为null的对象");
            return false;
        }
    }
    return _dao->updateModel(vect);
}

bool SampleBLL::deleteByIds(const QVector<QString> &ids)
{
    bool result = _dao->deleteHardByIds(ids);
    if(!result)
        eLog("hardDelete faild");
    return result;
}

QVector<SampleBLL::ptrSample> SampleBLL::getUnTestSamples()
{
    QVector<ptrSample>outVect;
    QString queryStr= " where stateFlag=1";
    QList<SampleModel> sampleList= getSampleList(queryStr);
    for (auto it : sampleList)
    {
        ptrSample sampleResult(new SampleModel(it));
        outVect.push_back(sampleResult);
    }
    return outVect;
}

SampleBLL::ptrSample SampleBLL::getUnTestSampleByPos(int samplePos)
{
    QVector<ptrSample>outVect;
    QString queryStr= " where stateFlag=1 and samplePos="+QString(samplePos);
    QList<SampleModel> sampleList= getSampleList(queryStr);
    if(sampleList.empty()){
        return  nullptr;
    }
    ptrSample sampleResult(new SampleModel(sampleList.at(0)));
    return sampleResult;
}

//自动编号
QString SampleBLL::creatSampleNo(QString sampleNo, QString preSampleNo)
{
    QString str = "";
    QString strPre = "0000000000000000000000000000000000000000000000000000000000000000000000";
    bool is_number = false;
    int index = 0;
    int len = sampleNo.length();
    uint64_t iTemp = sampleNo.toULongLong(&is_number);

    if (is_number && !sampleNo.contains("."))
    {
        iTemp += 1;
        str = QString::number(iTemp);
        if (str.length() >= len)
        {
            return preSampleNo + str;
        }

        if (strPre.length() < len - str.length())
        {
            str = strPre + str;
        }
        else
        {
            str = strPre.left(len - str.length()) + str;
        }
        return preSampleNo + str;
    }

    for (int n = 1; n <= sampleNo.size() && sampleNo.size() >= 1; n++)
    {
        bool ok = false;
        sampleNo.right(n).toInt(&ok, 10);
        if (!ok)
        {
            break;
        }
        else
        {
            is_number = true;
            index = n;
        }
    }

    if (is_number)
    {
        uint64_t tmp = sampleNo.right(index).toULongLong();
        tmp += 1;
        str = QString::number(tmp);
        if (str.length() >= index)
        {
            sampleNo = sampleNo.left(sampleNo.size() - index) + QString::number(tmp);
        }
        else
        {
            if (strPre.length() < index - str.length())
            {
                str = strPre + str;
            }
            else
            {
                str = strPre.left(index - str.length()) + str;
            }
            sampleNo = sampleNo.left(sampleNo.size() - index) + str;
        }
    }
    return preSampleNo + sampleNo;
}
