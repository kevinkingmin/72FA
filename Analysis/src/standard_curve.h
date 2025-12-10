#pragma once

#include <QObject>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <QPoint>
#include<vector>
#include <map>


typedef struct {
    int curveId;
    int curveType;
    double dataGroup1[10];
    double dataGroup2[10];
    double dataGroup3[10];
    double dataGroup4[10];
    double dataGroup5[10];
    double dataGroup6[10];
    double dataGroup7[10];
    double dataGroup8[10];
    double dataGroup9[10];
    double dataGroup10[10];
}StandardCurveParameter, *LPStandardCurveParameter;

class standard_curve : public QObject
{
    Q_OBJECT

public:
    standard_curve(QObject *parent);
    ~standard_curve();

    double Calc(StandardCurveParameter &parameter, double value);
    bool GetStandardCurveParameter(StandardCurveParameter &parapeter, int curveId);
private:
};
