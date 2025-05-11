#ifndef OBJECTTR_H
#define OBJECTTR_H
#include <QObject>

/*菜单信息*/
#define STR_MAINMENU_SET            QObject::tr("测试")           //QObject::tr("基础信息维护")   
#define STR_SAMPLE_MANAGE               QObject::tr("样本信息录入")


#define STR_MAINMENU_MANTANCE       QObject::tr("试剂")      //QObject::tr("仪器维护")
#define STR_MENU_SAMPLETUBE         QObject::tr("样本管管理")     //QObject::tr("样本管管理")



#define STR_MENU_MAGIC              QObject::tr("膜条管理")       //QObject::tr("膜条管理")    
#define STR_MENU_REAGENT            QObject::tr("试剂管理")  	  //QObject::tr("试剂管理")  
//#define STR_MENU_PUMP               QObject::tr("泵启动中")	  // QObject::tr("泵启动中")

#define STR_MAINMENU_HISTORY       QObject::tr("报告")      //QObject::tr("历史记录")
#define STR_MENU_RESULTINFO        QObject::tr("报告查询")       //QObject::tr("样本管管理")
#define STR_MENU_ALARMINFO         QObject::tr("报警信息")  
//#define STR_MENU_TEST_RECORD       QObject::tr("自测记录")                  //  QObject::tr("自测记录")
//#define STR_MENU_MAINTANCE_RECORD  QObject::tr("维护历史")					//  QObject::tr("维护历史")
//#define STR_MENU_COMMUNIT_RECORD   QObject::tr("外部系统的通信列表")		//	  QObject::tr("外部系统的通信列表")
//#define STR_MENU_SOLUTION_RECORD   QObject::tr("方案")						//QObject::tr("方案")

//#define STR_MENU_APPLICATION_SET        QObject::tr("设置")				// QObject::tr("设置")
#define STR_MAINMENU_EDIT				QObject::tr("设置")             //QObject::tr("编辑")
//#define STR_MENU_APPLICATION_LOGIN     QObject::tr("登录")
#define STR_MENU_APPLICATION_LOGIN     QObject::tr("退出登录")          //     QObject::tr("退出登录")
#define STR_MENU_APPLICATION_PASSWORD  QObject::tr("密码更改")			//   QObject::tr("密码更改")

#define STR_MENU_SYSTEMSET				QObject::tr("系统设置")   //QObject::tr("系统参数配置")
#define STR_MENU_APPLICATION_USERS      QObject::tr("用户管理")			//   QObject::tr("管理用户")
#define STR_LIS_SETTING                 QObject::tr("LIS设置")	
#define STR_MENU_CAMAR                  QObject::tr("相机参数设置")   //QObject::tr("相机参数设置")
#define STR_RULES_SETTING               QObject::tr("判读规则设置")	  //QObject::tr("判读规制设置")


//#define STR_MENU_EDIT_GROUP     QObject::tr("试验组列表")       //	QObject::tr("试验组列表")
//#define STR_MENU_EDIT_TEST      QObject::tr("试验记录")			// QObject::tr("试验记录")
//#define STR_MENU_EDIT_REAGENT   QObject::tr("试剂记录")			// QObject::tr("试剂记录")
//#define STR_MENU_EDIT_TUPE      QObject::tr("试管记录")			// QObject::tr("试管记录")
#define STR_MENU_MAN_INCUBAT      QObject::tr("手动孵育")			// QObject::tr("试管记录")

#define STR_MAINMENU_APPLICATION        QObject::tr("维护")       //QObject::tr("应用管理")

#define STR_MENU_NEW_LIQUID_DETECTION			QObject::tr("液位探测测试")	
#define STR_MENU_MONTH_MANTANCE			QObject::tr("月维护")		//QObject::tr("月维护")
#define STR_MENU_WEEK_MANTANCE			QObject::tr("周维护")		//QObject::tr("周维护")
#define STR_MENU_NEW_PERISTALTIC_PUMP_AUTO_CHECK			QObject::tr("泵自动校准")	
#define STR_MENU_NEW_PERISTALTIC_PUMP_MANA_CHECK				QObject::tr("泵手动校准")	
#define STR_MENU_NEW_PUMP_RUNNING_IN			QObject::tr("新泵磨合")	
#define STR_MENU_CAMERA_CHECK			QObject::tr("相机设置")	
#define STR_MENU_NEW_PIPE_WASH			QObject::tr("管路清洗")	

#define STR_MENU_NEW_PIPE_FEFLUX			QObject::tr("管路回流")	


#define STR_MENU_SYSTEM_LIQUID_PIPE_WASH			QObject::tr("系统液管路清洗")	


#define STR_MENU_PIPE_REFLUX				QObject::tr("管路回流")  //QObject::tr("运行自测试")

#define STR_MENU_SYSTEM_LIQUID_PIPE_WASH				QObject::tr("系统液管路清洗")  //QObject::tr("运行自测试")

#define STR_MENU_PIPE_WASH_EMPTY				QObject::tr("关机维护")  //QObject::tr("运行自测试")

#define STR_MENU_CLOSE_BEEP				QObject::tr("关闭蜂鸣器")  //QObject::tr("运行自测试")

#define STR_MENU_SELF_CHECK				QObject::tr("开机自检")  //QObject::tr("运行自测试")
#define STR_MENU_SLIQUID				QObject::tr("系统液")     // QObject::tr("系统液")  
#define STR_MENU_PUMP_CALIBRATE			QObject::tr("泵自动校准")  //QObject::tr("泵自动校准")
//#define STR_MENU_TEST_RECORD       QObject::tr("自测记录")                  //  QObject::tr("自测记录")
//#define STR_MENU_MAINTANCE_RECORD  QObject::tr("维护历史")					//  QObject::tr("维护历史")

//获得支持服务、查看说明书、查看软件信息
#define STR_MENU_HELP                   QObject::tr("帮助") 
#define STR_MENU_APPLICATION_ABOUT      QObject::tr("关于软件")
#define STR_MENU_APPLICATION_WELCOME      QObject::tr("欢迎界面")
#define STR_MENU_HELP_TECHSUPPORT       QObject::tr("获得支持服务")		// QObject::tr("关于应用程序")
#define STR_MENU_HELPMANUAL             QObject::tr("查看说明书")		// QObject::tr("关于应用程序")
#define STR_MENU_HELP_SOFTWAREINFO      QObject::tr("查看软件信息")		// QObject::tr("关于应用程序")
#define STR_MENU_HELP_OPERATELOG        QObject::tr("操作日志查询")		// QObject::tr("操作日志查询")

//#define STR_MENU_APPLICATION_CARDSET   QObject::tr("标记卡阅读器设置")	//   QObject::tr("标记卡阅读器设置")
//#define STR_MENU_APPLICATION_CODEADD   QObject::tr("代码录入")			//   QObject::tr("代码录入")


/* 按键信息 */
#define STR_OK                      QObject::tr("确 定")
#define STR_CANCEL                  QObject::tr("取 消")
#define STR_BACK                    QObject::tr("返 回")
#define STR_SAVE                    QObject::tr("保 存")
#define STR_DELETE                  QObject::tr("删 除")
#define STR_YES                     QObject::tr("是")
#define STR_NO                      QObject::tr("否")

/* 消息提示 */
#define STR_POINT                   QObject::GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180")
#define STR_ERROR                   QObject::tr(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"))
#define STR_ALARM                   QObject::tr("报警")
#define STR_WARNING                 QObject::tr(GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1271"))

#endif // OBJECTTR_H
#define STR_LOGOUT                  QObject::tr("注销")
#define STR_LOGOUT_CONFIRM          QObject::tr("确认注销")
#define STR_SHUT_DOWN               QObject::tr("关机")
#define STR_SHUT_DOWN_CONFIRM       QObject::tr("确定，执行关机维护。\r\n取消，直接退出软件。")
