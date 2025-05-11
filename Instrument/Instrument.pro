#-------------------------------------------------
#
# Project created by QtCreator 2020-10-12T14:45:34
#
#-------------------------------------------------

QT       -= gui
QT       += network
QT      += concurrent

CONFIG(release, debug|release){ TARGET = Instrument}
else{ TARGET = Instrumentd }
#TARGET = Instrument
TEMPLATE = lib
CONFIG += c++17
INCLUDEPATH += \
            $$PWD/../Third \
            $$PWD/../Third/spdlog \
            $$PWD/../Third/breakpad

DEFINES += INSTRUMENT_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/Instrument.cpp \
        src/SignalAndSlotHandle.cpp \
        src/cmd/AnalysisReciveCmd.cpp \
        src/cmd/Command.cpp \
        src/component/Buzzle.cpp \
        src/component/Camera.cpp \
        src/component/Component.cpp \
        src/component/Components.cpp \
        src/component/Encoder.cpp \
        src/component/Fan.cpp \
        src/component/Light.cpp \
        src/component/Liquid.cpp \
        src/component/MainController.cpp \
        src/component/Motor.cpp \
        src/component/RockBed.cpp \
        src/component/SampleArm.cpp \
        src/component/Scaner.cpp \
        src/component/Sensor.cpp \
        src/component/Temperature.cpp \
        src/component/Valve.cpp \
        src/component/socket.cpp \
        src/function/Function.cpp \
        src/function/Functions.cpp \
        src/function/maintain/MaintainSystem.cpp \
        src/function/monitor/Monitor.cpp \
        src/function/timing/ActionModel.cpp \
        src/function/timing/Timing.cpp \
        src/local_log.cpp

HEADERS += \
        src/Instrument.h \
        src/SignalAndSlotHandle.h \
        src/cmd/AnalysisReciveCmd.h \
        src/cmd/Command.h \
        src/component/Buzzle.h \
        src/component/Camera.h \
        src/component/Component.h \
        src/component/Components.h \
        src/component/Encoder.h \
        src/component/Fan.h \
        src/component/Light.h \
        src/component/Liquid.h \
        src/component/MainController.h \
        src/component/Motor.h \
        src/component/ObjectInfo.h \
        src/component/RockBed.h \
        src/component/SampleArm.h \
        src/component/Scaner.h \
        src/component/Sensor.h \
        src/component/Temperature.h \
        src/component/Valve.h \
        src/component/socket.h \
        src/function/Function.h \
        src/function/Functions.h \
        src/function/maintain/MaintainSystem.h \
        src/function/monitor/Monitor.h \
        src/function/timing/ActionModel.h \
        src/function/timing/Timing.h \
        src/instrument_global.h \
        src/local_log.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
DLLDESTDIR+=../Bin
DESTDIR+=../Lib
MOC_DIR=moc/
UI_DIR=moc/
win32{
    LIBS+=../Lib/Utilities.lib
    LIBS+=../Lib/Model.lib
    LIBS+=../Lib/BLL.lib    

    CONFIG(release, debug|release) {
        LIBS+=../Lib/SerialPortDriver.lib
    } else {
        LIBS+=../Lib/SerialPortDriverd.lib
    }

    PRECOMPILED_HEADER+=../Include/Precomp/precompile.h
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\instrument_global.h\" \
        \"$$PWD\\..\\Include\\Instrument\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\Instrument.h\" \
        \"$$PWD\\..\\Include\\Instrument\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\SignalAndSlotHandle.h\" \
        \"$$PWD\\..\\Include\\Instrument\\\" /y &

}
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
