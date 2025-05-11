#-------------------------------------------------
#
# Project created by QtCreator 2019-07-09T17:07:49
#
#-------------------------------------------------
QMAKE_LFLAGS += -Wl,--kill-at  #  避免有些平台如VB调用库出问题
CONFIG += skip_target_version_ext # 避免在dll文件的名字里面自动加数字

VERSION = 1.0.0.20

QMAKE_TARGET_PRODUCT = 72FA免疫印记仪
QMAKE_TARGET_COMPANY = 北京胡曼智造科技有限责任公司
QMAKE_TARGET_DESCRIPTION = 72FA免疫印记仪客户端
QMAKE_TARGET_COPYRIGHT = 北京胡曼智造科技有限责任公司
 
QT       += core gui printsupport
QT      += charts sql
QT      += xml
QT      += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HumablotPro
TEMPLATE = app

INCLUDEPATH += \
            $$PWD/../Include \
            $$PWD/../Include/Model \
            $$PWD/../Include/Model/sample \
            $$PWD/../Third \
            $$PWD/../Third/spdlog \
            $$PWD/../Third/breakpad \
            $$PWD/../opencv_build/include

LIBS+= -L$$PWD/../Lib
LIBS+= -lModel
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

include($$PWD/qtsingleapplication/qtsingleapplication.pri)

SOURCES += \
        src/Camera/Camera.cpp \
        src/Camera/CameraControl.cpp \
        src/Camera/CameraParametersSet.cpp \
        src/Camera/RGBConvert.cpp \
        src/Camera/TestResultDataAll.cpp \
        src/Camera/TestResultDataManage.cpp \
        src/Camera/TestResultDataOneType.cpp \
        src/comm/CustomLabel1.cpp \
        src/comm/BaseDialog.cpp \
        src/comm/CustClickWidget.cpp \
        src/comm/CustomButton.cpp \
        src/comm/CustomLabel.cpp \
        src/comm/CustomerPumpStateLable.cpp \
        src/comm/DataConvertHelper.cpp \        
        src/comm/Global.cpp \
        src/comm/GlobalData.cpp \
        src/comm/LightButton.cpp \
        src/comm/customerTableView.cpp \
        src/comm/freezetableview.cpp \
        src/delegate/ComboxDelegate.cpp \
        src/main/WorkerThread.cpp \
        src/main/CreateDump.cpp \
        src/main/AlarmInfoWidgets.cpp \
        src/main/InitWidgets.cpp \
        src/main/LisSettingWidgets.cpp \
        src/main/MainWidget.cpp \
        src/main/UserManageWidget.cpp \
        src/main/firstwidgetbase.cpp \
        src/main/loginform.cpp \
        src/main/subDialog/MyMessageBox.cpp \
        src/main/main.cpp \
        src/main/mainwindow.cpp \
        src/main/subDialog/ProgressDialog.cpp \
        src/main/subDialog/ShowImageDialog.cpp \
        src/sample/AddSampleWidget.cpp \
        src/sample/EmptyWasteBottleWidget.cpp \
        src/sample/IrrigationSystemLiquidWidget.cpp \
        src/sample/PrepareReagentWidget.cpp \
        src/sample/RunPaperPosThread.cpp \
        src/sample/SampleWidget.cpp \
        src/sample/ShowAllPicWidgets.cpp \
        src/sample/ShowTestResultDetail.cpp \
        src/sample/TestDataListWidget.cpp \
        src/sample/TestResultDetailDialog.cpp \
        src/sample/model/AddSampleVModel.cpp \
        src/sample/model/RepeatSetModel.cpp \
        src/sample/model/TestDataListVModel.cpp \
        src/sample/subDialog/FromLisByIntervalWidgets.cpp \
        src/sample/subDialog/ManualIncubationWidgets.cpp \
        src/sample/subDialog/PrepareReagentDialog.cpp \
        src/sample/subDialog/RepeatSetDialog.cpp \
        src/sample/subDialog/SelectProcessDialog.cpp \
        src/sample/subDialog/SelfCheckResultShowDialog.cpp \
        src/sample/subDialog/SetFirstPaperPosDialog.cpp \
        src/types/HumaClia2000Data.cpp \
        src/utility/AboutUsWidgets.cpp \
        src/utility/AddCompany.cpp \
        src/utility/AddReagent.cpp \
        src/utility/AddTubeStep1.cpp \
        src/utility/AddTubeStep2.cpp \
        src/utility/AddTubeStep3.cpp \
        src/utility/AddTubeStep4.cpp \
        src/utility/QtWidgetstOperateLog.cpp \
        src/utility/ReagentManager.cpp \
        src/utility/ResultDetail.cpp \
        src/utility/ResultManage.cpp \
        src/utility/RulesSetting.cpp \
        src/utility/SystemSet.cpp \
        src/utility/TestPaper.cpp \
        src/utility/TestPaperManage.cpp \
        src/utility/TubeManage.cpp \
        src/utility/UtilityWidget.cpp \
        src/utility/WelcomWidgets.cpp \
        src/utility/maintain/SystemLiquidPipeWashWidgets.cpp \
        src/utility/maintain/PipeRefluxWidgets.cpp \
        src/utility/maintain/PipeWashEmptyingWidgets.cpp \
        src/utility/maintain/CameraCheckWidgets.cpp \
        src/utility/maintain/LiquidDetectionWidgets.cpp \
        src/utility/maintain/MaintainCmdWidget.cpp \
        src/utility/maintain/MonthMaintenanceWidgets.cpp \
        src/utility/maintain/NewPumpRunningWidgets.cpp \
        src/utility/maintain/PipeWashWidgets.cpp \
        src/utility/maintain/PumpAutoCheckWidgets.cpp \
        src/utility/maintain/PumpCalibrateWidget.cpp \
        src/utility/maintain/PumpManaCheckWidgets.cpp \
        src/utility/maintain/WeekMaintenanceWidgets.cpp \
        #src/utility/maintain/thread/MyThread.cpp \
        src/utility/ProcessParaWidgets.cpp \
        src/workArea/workAreaForm.cpp \
        src/sample/TestSampleWidget.cpp \
        src/sample/BatchAddSampleWidgets.cpp \
        src/model/GetLanguageCls.cpp \
        src/model/LanguageInfo.cpp

HEADERS += \
        src/Camera/Camera.h \
        src/Camera/CameraControl.h \
        src/Camera/CameraParametersSet.h \
        src/Camera/RGBConvert.h \
        src/Camera/TestResultDataAll.h \
        src/Camera/TestResultDataManage.h \
        src/Camera/TestResultDataOneType.h \
        src/comm/CustomLabel1.h \
        src/comm/BaseDialog.h \
        src/comm/CustClickWidget.h \
        src/comm/CustomButton.h \
        src/comm/CustomLabel.h \
        src/comm/CustomerPumpStateLable.h \
        src/comm/DataConvertHelper.h \
        src/comm/Global.h \
        src/comm/GlobalData.h \    
        src/comm/LightButton.h \
        src/comm/ObjectTr.h \
        src/comm/customerTableView.h \
        src/comm/freezetableview.h \
        src/delegate/ComboxDelegate.h \
        src/delegate/DelegateData.h \
        src/main/WorkerThread.h \
        src/main/CreateDump.h \
        src/main/AlarmInfoWidgets.h \
        src/main/InitWidgets.h \
        src/main/LisSettingWidgets.h \
        src/main/MainWidget.h \
        src/main/UserManageWidget.h \
        src/main/firstwidgetbase.h \
        src/main/loginform.h \
        src/main/subDialog/MyMessageBox.h \
        src/main/mainwindow.h \
        src/main/subDialog/ProgressDialog.h \
        src/main/subDialog/ShowImageDialog.h \
        src/sample/AddSampleWidget.h \
        src/sample/EmptyWasteBottleWidget.h \
        src/sample/IrrigationSystemLiquidWidget.h \
        src/sample/PrepareReagentWidget.h \
        src/sample/RunPaperPosThread.h \
        src/sample/SampleWidget.h \
        src/sample/ShowAllPicWidgets.h \
        src/sample/ShowTestResultDetail.h \
        src/sample/TestDataListWidget.h \
        src/sample/TestResultDetailDialog.h \
        src/sample/model/AddSampleVModel.h \
        src/sample/model/RepeatSetModel.h \
        src/sample/model/TestDataListVModel.h \
        src/sample/subDialog/FromLisByIntervalWidgets.h \
        src/sample/subDialog/ManualIncubationWidgets.h \
        src/sample/subDialog/PrepareReagentDialog.h \
        src/sample/subDialog/RepeatSetDialog.h \
        src/sample/subDialog/SelectProcessDialog.h \
        src/sample/subDialog/SelfCheckResultShowDialog.h \
        src/sample/subDialog/SetFirstPaperPosDialog.h \
        src/types/HumaClia2000.h \
        src/types/HumaClia2000Data.h \
        src/utility/WelcomWidgets.h \
        src/utility/AboutUsWidgets.h \
        src/utility/AddCompany.h \
        src/utility/AddReagent.h \
        src/utility/AddTubeStep1.h \
        src/utility/AddTubeStep2.h \
        src/utility/AddTubeStep3.h \
        src/utility/AddTubeStep4.h \
        src/utility/QtWidgetstOperateLog.h \
        src/utility/ReagentManager.h \
        src/utility/ResultDetail.h \
        src/utility/ResultManage.h \
        src/utility/RulesSetting.h \
        src/utility/SystemSet.h \
        src/utility/TestPaper.h \
        src/utility/TestPaperManage.h \
        src/utility/TubeManage.h \
        src/utility/UtilityWidget.h \
        src/utility/maintain/SystemLiquidPipeWashWidgets.h \
        src/utility/maintain/PipeWashEmptyingWidgets.h \
        src/utility/maintain/PipeRefluxWidgets.h \
        src/utility/maintain/CameraCheckWidgets.h \
        src/utility/maintain/LiquidDetectionWidgets.h \
        src/utility/maintain/MaintainCmdWidget.h \
        src/utility/maintain/MonthMaintenanceWidgets.h \
        src/utility/maintain/NewPumpRunningWidgets.h \
        src/utility/maintain/PipeWashWidgets.h \
        src/utility/maintain/PumpAutoCheckWidgets.h \
        src/utility/maintain/PumpCalibrateWidget.h \
        src/utility/maintain/PumpManaCheckWidgets.h \
        src/utility/maintain/WeekMaintenanceWidgets.h \
        #src/utility/maintain/thread/MyThread.h \
        src/utility/ProcessParaWidgets.h \
        src/workArea/workAreaForm.h \
        src/sample/TestSampleWidget.h \
        src/sample/BatchAddSampleWidgets.h \
        src/model/GetLanguageCls.h \
        src/model/LanguageInfo.h

FORMS += \
        src/Camera/Camera.ui \
        src/Camera/TestResultDataAll.ui \
        src/Camera/TestResultDataManage.ui \
        src/Camera/TestResultDataOneType.ui \
        src/main/AlarmInfoWidgets.ui \
        src/main/InitWidgets.ui \
        src/main/LisSettingWidgets.ui \
        src/main/UserManageWidget.ui \
        src/main/subDialog/ShowImageDialog.ui \
        src/sample/ShowAllPicWidgets.ui \
        src/sample/subDialog/SelfCheckResultShowDialog.ui \
        src/utility/WelcomWidgets.ui \
        src/utility/AboutUsWidgets.ui \
        src/utility/AddCompany.ui \
        src/utility/AddReagent.ui \
        src/utility/AddTubeStep1.ui \
        src/utility/AddTubeStep2.ui \
        src/utility/AddTubeStep3.ui \
        src/utility/AddTubeStep4.ui \
        src/utility/QtWidgetstOperateLog.ui \
        src/utility/ReagentManager.ui \
        src/utility/ResultDetail.ui \
        src/utility/ResultManage.ui \
        src/utility/RulesSetting.ui \
        src/utility/SystemSet.ui \
        src/utility/TestPaper.ui \
        src/utility/TestPaperManage.ui \
        src/utility/TubeManage.ui \
        src/utility/maintain/SystemLiquidPipeWashWidgets.ui \
        src/utility/maintain/PipeWashEmptyingWidgets.ui \
        src/utility/maintain/PipeRefluxWidgets.ui \
        src/utility/maintain/CameraCheckWidgets.ui \
        src/utility/maintain/LiquidDetectionWidgets.ui \
        src/utility/maintain/MonthMaintenanceWidgets.ui \
        src/utility/maintain/NewPumpRunningWidgets.ui \
        src/utility/maintain/PipeWashWidgets.ui \
        src/utility/maintain/PumpAutoCheckWidgets.ui \
        src/utility/maintain/PumpManaCheckWidgets.ui \
        src/utility/maintain/WeekMaintenanceWidgets.ui \
        ui/sample/subDialog/FromLisByIntervalWidgets.ui \
        ui/sample/subDialog/ManualIncubationWidgets.ui \
        ui/utility/maintain/PumpCalibrateWidget.ui \
        ui/main/subDialog/ProgressDialog.ui \
        ui/sample/PrepareReagentWidget.ui \
        ui/sample/EmptyWasteBottleWidget.ui \
        ui/sample/IrrigationSystemLiquidWidget.ui \
        ui/sample/SampleWidget.ui \
        src/utility/ProcessParaWidgets.ui \
        ui/main/MainWidget.ui \
        ui/sample/BatchAddSampleWidgets.ui \
        ui/sample/TestDataListWidget.ui \
        ui/sample/TestSampleWidget.ui \
        ui/sample/subDialog/PrepareReagentDialog.ui \
        ui/sample/subDialog/RepeatSetDialog.ui \
        ui/sample/subDialog/SelectProcessDialog.ui \
        ui/sample/subDialog/SetFirstPaperPosDialog.ui \
        ui/utility/maintain/MaintainCmdWidget.ui \
        ui/utility/UtilityWidget.ui \
        ui/main/loginform.ui \
        ui/main/mainwindow.ui \
        ui/sample/AddSampleWidget.ui \
        ui/workArea/workAreaForm.ui

DESTDIR +=../Bin
MOC_DIR  =moc/
UI_DIR   =moc/
win32{
    PRECOMPILED_HEADER+= $$PWD\\..\\Include\\Precomp\\precompile.h
    LIBS+=  \
            $$PWD/../Lib/Model.lib \
            $$PWD/../Lib/BLL.lib \
            $$PWD/../Lib/Utilities.lib \
            $$PWD/../Lib/DAO.lib \
            $$PWD/../Lib/Analysis.lib \
            $$PWD/../Lib/Camera/ImageConvert.lib \
            $$PWD/../Lib/Camera/MVSDKmd.lib \
            $$PWD/../Lib/Camera/VideoRender.lib

    CONFIG(debug, debug|release) {
         LIBS += ../Lib/OpenCV/opencv_world340d.lib
         LIBS += ../Lib/Databased.lib
         LIBS += ../Lib/Instrumentd.lib
         LIBS += ../Lib/TCPClientd.lib
    } else {
         LIBS += ../Lib/OpenCV/opencv_world340.lib
         LIBS += ../Lib/Database.lib
         LIBS += ../Lib/Instrument.lib
         LIBS += ../Lib/TCPClient.lib
    }
}
