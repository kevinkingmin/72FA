#ifndef HUMACLIA2000_H
#define HUMACLIA2000_H

#include <QDate>
namespace HumaClia2000 {
//主窗体管理窗口编号
enum MainWindowIndex{
    WindowLogIn=0,        //登录
    WindowMain,           //主窗体
};
//第一级窗口编号
enum FirstWidgetIndex{
    WidgetSample=0,       //样本
    WidgetReview,         //回顾
    WidgetWorkOrder,      //工作单
    WidgetQc,             //质控
    WidgetStatistics,     //统计
    WidgetCalibration,    //校准
    WidgetPerformance,    //性能
    WidgetSetting,        //设置
    WidgetLog,            //日志
    WidgetStatus,         //状态
    WidgetService,        //服务
};
//服务窗口编号
enum ServiceWidgetIndex{
    WidgetGeneralSetting=0,     //常规设置
    WidgetTimeSequential,       //时序
    WidgetOpticalDebug,         //光学调试
    WidgetInstrumentControl,    //仪器控制
};
}
#endif // HUMACLIA2000_H
