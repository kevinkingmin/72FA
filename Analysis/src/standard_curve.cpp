#include "standard_curve.h"
#include <QSettings>
#include <QSqlQuery>
#include <QCoreApplication>
#include <QVariant>
#include <QDateTime>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include"iostream"
#include "../Include/DAO/Analysis/AnalysisDao.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../Include/Utilities/log.h"
#include "Wave_Low_Top_Info.h"
#include <opencv2/opencv.hpp>
#include <QtCore/qmath.h>
#include <random>
#include <map>
#include <vector>
#include <QtAlgorithms>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <numeric>
#include <QDebug>
#include "../BLL/src/baseSet/ItemBll.h"
#include "../Include/Model/sample/SampleTestModel.h"
#include "../Include/Utilities/log.h"

using namespace cv;
using namespace std;
#pragma execution_character_set("utf-8")
standard_curve::standard_curve(QObject *parent)
    : QObject(parent)
{
}

standard_curve::~standard_curve()
{
}

bool standard_curve::GetStandardCurveParameter(StandardCurveParameter &parameter, int curveId)
{
    bool bResult;
    auto dao = AnalysisDao::instance();
    auto TestPaperQuery = dao->SelectStandardCurveParameter(QString::number(curveId), &bResult);
    if (bResult == false)
    {
        return false;
    }
    parameter.curveId = curveId;
    if (TestPaperQuery.next())
    {
        parameter.curveType = TestPaperQuery.value("CurveType").toInt();
        if(parameter.curveType == 0 || parameter.curveType == 1)
        {
            QString dataGroup1 = TestPaperQuery.value("DataGroup1").toString();
            QStringList strList = dataGroup1.split(',');
            int idx = 0;
            for (const QString &s : strList) {
                if(idx == 10)
                {
                    return false;
                }
                bool ok;
                double num = s.toDouble(&ok);
                if (ok)
                {
                    parameter.dataGroup1[idx] = num;
                }else
                {
                    return false;
                }
                idx++;
            }
        }else
        {
            parameter.dataGroup1[0] = 1.0;
            parameter.dataGroup1[1] = 0;
        }
    }
    return true;
}


double standard_curve::Calc(StandardCurveParameter &parameter, double value)
{

    double A = 0, B = 0, C = 0, D = 0;
    if(parameter.curveType == 0)
    {
        return parameter.dataGroup1[0] * value + parameter.dataGroup1[1];
    }else if(parameter.curveType == 1)
    {
        A = parameter.dataGroup1[0];
        B = parameter.dataGroup1[1];
        C = parameter.dataGroup1[2];
        D = parameter.dataGroup1[3];
        double tempValue = value-D;
        if(tempValue < 0)
        {
            return 0;
        }
        else
        {
            tempValue = tempValue < 1e-5 ? 1e-5 : tempValue;
            tempValue = (A-value)/tempValue;
            tempValue = tempValue < 0 ? 0 :  C * pow(tempValue, 1/B);
            return tempValue < 0 ? 0 : tempValue;
        }
    }else
    {
        return value;
    }
}
